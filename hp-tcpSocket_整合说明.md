# HP-Socket 6.0.9 TCP 组件整合说明

把 HP-Socket 6.0.9（Windows 版）的 **6 个 TCP 组件**提取整合成两个文件，用法和
SQLite 的 `sqlite3.c` / `sqlite3.h` 一样：**拷进你的 VS 工程就能编译使用**。

```
hp-tcpSocket/
├── hp-tcpSocket.h      12,316 行
└── hp-tcpSocket.cpp     5,471 行
                      ─────────
                      17,787 行
```

---

## 1. 包含的组件

| 组件 | 类名 | 接口 |
|---|---|---|
| TCP Server | `CTcpServer` | `ITcpServer` |
| TCP Pull Server | `CTcpPullServer` | `IPullSocket` + `ITcpServer` |
| TCP Pack Server | `CTcpPackServer` | `IPackSocket` + `ITcpServer` |
| TCP Client | `CTcpClient` | `ITcpClient` |
| TCP Pull Client | `CTcpPullClient` | `IPullClient` + `ITcpClient` |
| TCP Pack Client | `CTcpPackClient` | `IPackClient` + `ITcpClient` |

回调基类：`CTcpServerListener`、`CTcpPullServerListener`、
`CTcpClientListener`、`CTcpPullClientListener`。

---

## 2. 在你的 Visual Studio 工程里使用

### 2.1 把文件加到工程

1. 把 `hp-tcpSocket.h`、`hp-tcpSocket.cpp` 复制到你的工程目录；
2. VS 里 **添加 → 现有项**，把两个文件都加进来；
3. 打开 `hp-tcpSocket.cpp`，确认它参与了编译（不是被排除的状态）。

### 2.2 工程属性

| 属性 | 值 | 说明 |
|---|---|---|
| C++ 语言标准 | **C++17 或更高** | 代码里有 `inline` 变量，低版本会报 C7525 |
| 字符集 | Unicode 或 MBCS 均可 | 两种都实测通过 |
| ATL | **需要** | 用 `CStringA` / `CAtlFile`，VS 自带，无需额外安装 |
| MFC | **不需要** | |
| 运行库 | `/MD` 或 `/MDd` 均可 | 两种都实测通过 |

### 2.3 不需要做的事

- ❌ 不用配置额外的 include 目录
- ❌ 不用手动链接 `ws2_32.lib` / `winmm.lib`（`hp-tcpSocket.cpp` 里有 `#pragma comment(lib, ...)`）
- ❌ 不用定义 `HPSOCKET_STATIC_LIB`（`hp-tcpSocket.h` 已自带）
- ❌ 不用改动任何其他 HP-Socket 文件（原 `Windows/Src` 一行未改）

### 2.4 服务端示例

```cpp
#include "hp-tcpSocket.h"

class CMyServer : public CTcpServerListener
{
public:
    virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
    {
        return HR_OK;
    }

    virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
    {
        printf("client connected, connID=%llu\n", (unsigned long long)dwConnID);
        return HR_OK;
    }

    virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID,
                                     const BYTE* pData, int iLength)
    {
        pSender->Send(dwConnID, pData, iLength);   // 回显
        return HR_OK;
    }

    virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID,
                                   EnSocketOperation enOperation, int iErrorCode)
    {
        printf("closed, connID=%llu, err=%d\n", (unsigned long long)dwConnID, iErrorCode);
        return HR_OK;
    }

    virtual EnHandleResult OnShutdown(ITcpServer* pSender)
    {
        return HR_OK;
    }
};

int main()
{
    CMyServer listener;

    CTcpServer server(&listener);                 // 直接实例化
    if (!server.Start("0.0.0.0", 5555))
    {
        printf("Start failed: %s\n", (const char*)server.GetLastErrorDesc());
        return 1;
    }

    printf("listening on 5555, press Enter to stop\n");
    getchar();

    server.Stop();                                // 析构时也会自动 Stop
    return 0;
}
```

### 2.5 客户端示例

```cpp
#include "hp-tcpSocket.h"

class CMyClient : public CTcpClientListener
{
public:
    virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID)
    {
        pSender->Send((const BYTE*)"hello", 5);
        return HR_OK;
    }

    virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID,
                                     const BYTE* pData, int iLength)
    {
        printf("recv %d bytes\n", iLength);
        return HR_OK;
    }

    virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID,
                                   EnSocketOperation enOperation, int iErrorCode)
    {
        return HR_OK;
    }
};

int main()
{
    CMyClient listener;

    CTcpClient client(&listener);
    client.Start("127.0.0.1", 5555, TRUE);        // TRUE = 异步连接
    client.Wait(5000);                            // 等连接完成

    client.Send((const BYTE*)"ping", 4);
    Sleep(1000);

    client.Stop();
    return 0;
}
```

### 2.6 内联工厂函数

为方便从原有代码迁移，`hp-tcpSocket.h` 末尾提供了 6 个内联工厂，
代替原库 `HPSocket.h` 里的 `HP_Create_*`（那套会把线程池子系统一起拖进来）：

```cpp
ITcpServer  *srv = CreateTcpServer(&listener);
ITcpPullServer  → 返回 IPullSocket*
ITcpPackServer  → 返回 IPackSocket*
ITcpClient  *cli = CreateTcpClient(&listener);
ITcpPullClient  → 返回 IPullClient*
ITcpPackClient  → 返回 IPackClient*

// 用完销毁
DestroyTcpServer(srv);
DestroyTcpClient(cli);
```

> **关于返回类型**：Pull/Pack 组件的真实声明是
> `DualInterface<IPullSocket, CTcpServer>`，其中 `ITcpServer` 是二义基类，
> 无法直接命名。所以工厂返回的是无二义的 socket 接口；
> 需要更宽的 API 时自己向上转型到 `CTcpServer` 或 `IPullSocket`。

---

## 3. 实测验证结果

全部在 **MSVC v19.44.35229（VS 2022 Build Tools 17.14）+ Windows SDK 10.0.26100.0**
上实测，用 `build/smoke.cpp`（36 项断言）跑真实网络往返：

| 配置 | 字符集 | 编译 | 运行 |
|---|---|---|---|
| Debug `/MDd /Zi` | MBCS | 0 错误 0 警告 | ✅ 36/36 |
| Debug `/MDd /Zi` | UNICODE | 0 错误 0 警告 | ✅ 36/36 |
| Release `/O2 /MD /DNDEBUG` | MBCS | 0 错误 0 警告 | ✅ 36/36 |
| Release `/O2 /MD /DNDEBUG` | UNICODE | 0 错误 0 警告 | ✅ 36/36 |

冒烟测试实际覆盖：

- 6 个组件的构造 / 状态查询 / 析构
- **TcpServer ↔ TcpClient** 真实 TCP 往返 + 回显
- **TcpPullServer ↔ TcpPullClient** 真实往返 + `Fetch()` + 回显
- **TcpPackServer ↔ TcpPackClient** 真实往返 + 组包/拆包 + 回显
- 数据**逐字节精确比对**：34 字节载荷，故意包含**内嵌 `\0`** 和**结尾 `\0`**，
  证明帧处理对二进制数据正确（不是"当字符串能跑就行"）
- 6 个内联工厂函数的创建与销毁
- `GetSocketErrorDesc()` 辅助函数
- 库版本号读取（返回 `100665601` = 6.0.9.1）

复现方式（`build/` 目录下）：

```cmd
gen.ps1                  :: 重新生成两个文件
build.bat MBCS           :: Debug 只编译
smoke.bat MBCS           :: Debug 链接 + 运行冒烟测试
smoke.bat UNICODE
smoke-release.bat MBCS   :: Release 链接 + 运行
smoke-release.bat UNICODE
```

---

## 4. 已剔除的内容

整合时只保留 TCP 必要部分，以下全部移除（**不是禁用，是不参与编译**）：

| 剔除项 | 原文件 | 剔除原因 |
|---|---|---|
| **SSL / HTTPS** | `SSLServer.*` `SSLClient.*` `SSLAgent.*` `SSLHelper.*` | 你确认只用 TCP，去掉 openssl 依赖 |
| **HTTP / WebSocket** | `HttpServer.*` `HttpAgent.*` `HttpClient.*` `HttpCookie.*` `HttpHelper.*` | 非 TCP |
| **UDP / ARQ / KCP** | `UdpServer.*` `UdpClient.*` `UdpCast.*` `UdpNode.*` `UdpArq*` `ArqHelper.*` `Common/kcp/*` | 非 TCP |
| **Agent（多客户端）** | `TcpAgent.*` `TcpPullAgent.*` `TcpPackAgent.*` | 你只要 Server 和 Client |
| **C (4C) 接口** | `HPSocket4C.cpp` `SocketObject4C.h` `HPSocket4C.h` | 你确认只保留 C++ API |
| **zlib / brotli 压缩** | `SocketHelper.cpp` 后半段 | HTTP 专用 |
| **线程池** | `HPThreadPool.*` | 只被原 `HP_Create_*` 门面使用 |
| **零使用文件** | `Common/SE.h` `Common/Win32Helper.h` `Common/Thread.*` `Common/debug/win32_crtdbg.*` | 经全树引用检查确认无引用 |
| **llhttp** | `Common/http/*` | HTTP 专用 |

`_SSL_SUPPORT` / `_HTTP_SUPPORT` / `_UDP_SUPPORT` / `_ZLIB_SUPPORT` / `_BROTLI_SUPPORT`
四个开关在 `hp-tcpSocket.h` 开头统一关闭，代码里原有的 `#ifdef` 桩函数仍在，
**将来要恢复某个子系统时改动面很小**。

### 4.1 如何恢复 SSL（举例）

1. 把 `SSLServer.*` `SSLClient.*` `SSLHelper.*` 加回生成脚本的源文件清单；
2. 注释掉 `hp-tcpSocket.h` 开头的 `#define _SSL_DISABLED`；
3. 安装 OpenSSL 并链接 `libssl.lib` / `libcrypto.lib` / `crypt32.lib`；
4. 重新生成。

---

## 5. 需要你知道的两个技术点

### 5.1 需要 ATL（但不需 MFC）

TCP 路径用到这些 ATL 类型：

| ATL 类型 | 用在哪 |
|---|---|
| `CStringA` | `SocketHelper.h` 的 `TSocketObj` 远端主机名、`TcpClient` 的 `m_strHost` |
| `CAtlFile` / `CAtlFileMapping<>` | `SendSmallFile()` 零拷贝发文件 |
| `ATLASSERT` / `ATLVERIFY` / `ATLENSURE` | `ASSERT` / `VERIFY` / `ENSURE` 宏的底层 |
| `CT2A` | 主机名解析 |
| `CString` | 工作线程命名 |

**ATL 是 Visual Studio 自带的**，装 VS 时勾上"用于最新 v143 生成工具的 C++ ATL"
即可，不需要装第三方库，也不需要额外 .lib。MFC 完全不需要。

### 5.2 必须用 MSVC，不能用 MinGW/GCC

TCP 路径上就有 **120 处 `__super` 关键字**（`Common/BufferPool.h`、
`Common/STLHelper.h`、`TcpPackClient.h`、`TcpPullServer.h` 等），
这是 MSVC 专有语法。另外上述 ATL 依赖在 MinGW 下不存在。
**你的目标是 Visual Studio，所以这一点不构成任何问题。**

---

## 6. 与原版的迁移对照

| 原写法 | 迁移后 |
|---|---|
| `#include <hpsocket/HPSocket.h>` | `#include "hp-tcpSocket.h"` |
| `CTcpServerPtr p(&listener);` | `CTcpServer srv(&listener);` 或 `CreateTcpServer(&listener)` |
| `HP_Create_TcpClient(&listener)` | `CreateTcpClient(&listener)` |
| `HP_Destroy_TcpClient(p)` | `DestroyTcpClient(p)` |
| 链接 `hpsocket.lib` + 拷贝 `hpsocket.dll` | 什么都不用做，源码级编译 |
| 回调基类、事件签名、`Start/Send/Stop` 等 API | **完全不变** |

回调基类名、虚函数签名、组件方法、枚举名、常量名**全部与原版一致**，
所以你现有业务代码里的 Listener 实现和调用逻辑可以原样保留。

---

## 7. 整合过程中发现并修正的两个原始判断误差

供你参考，也说明结果是经编译器实测校验的，不是纸上推演：

1. **`Common/Singleton.h` 并非"零使用"**。它除了单例类，还定义了
   `DECLARE_NO_COPY_CLASS` 宏（`Singleton.h:73`），而 `STLHelper.h` 和
   `RingBuffer.h` 都在用。最初按"无引用"剔除后，编译报出 12 处语法错误，
   加回后解决。

2. **`ITcpPullServer` / `ITcpPackServer` 无法从具体类直接转型**。
   它们是 `DualInterface<IPullSocket, CTcpServer>` 的 typedef，
   `ITcpServer` 在里面是**二义基类**。工厂函数因此返回
   `IPullSocket*` / `IPackSocket*` 这类无二义接口。

另外 `_WINSOCK_SUPPORT` 段（`GeneralHelper.h:248-252`）在整个工程里从未定义，
是死代码，原样保留无副作用。

---

## 8. 关于许可

hp-tcpSocket 采用 **Apache License 2.0**，允许修改和再分发。
两个整合文件的文件头已保留原始出处（Bruce Liang / ldcsaa）和授权声明。
如果你的项目需要，建议在文档里一并说明使用了 HP-Socket。
