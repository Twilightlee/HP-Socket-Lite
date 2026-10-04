# HP-Socket 6.0.9 合并版（TCP + UDP）整合说明

把 HP-Socket 6.0.9（Windows 版）的 **TCP 6 个组件 + UDP 6 个组件**整合成两个文件，
用法与 SQLite 的 `sqlite3.c` / `sqlite3.h` 一样：**拷进 VS 工程就能编译使用**。

```
hp-allSocket/
├── hp-allSocket.h      14,694 行
└── hp-allSocket.cpp    11,232 行
                         ─────────
                         25,926 行
```

> **本文件的定位**：如果你**同时**需要 TCP 和 UDP，用这一套。
> 只用其中一种的话，用单族版本更小（见第 7 节的对照表）。

---

## 1. 为什么需要合并版

单独生成的 TCP 版和 UDP 版**各自内联了一份共享底座**
（`SocketHelper.cpp`、`MiscHelper.cpp`、`Common/*.cpp` 等）。
它们**单独编译都没问题**，但如果把两个 `.cpp` **同时**放进一个工程链接，
就会产生**重复符号**（LNK2005）。

合并版解决这个问题的方式是：**共享底座只内联一份**，两族组件放在一份底座之上。

具体做法：`hp-allSocket.cpp` 的结构是

```
hp-allSocket.cpp
├── #include "hp-allSocket.h"
├── SHARED BASE  ← 只此一份
│     Common/SysHelper.cpp, FuncHelper.cpp, WaitFor.cpp,
│     BufferPool.cpp, RWLock.cpp, kcp/ikcp.c,
│     SocketHelper.cpp, MiscHelper.cpp, ArqHelper.cpp
├── TCP COMPONENTS
│     TcpServer.cpp, TcpClient.cpp
└── UDP COMPONENTS
      UdpServer.cpp, UdpClient.cpp, UdpArqClient.cpp,
      UdpArqServer.cpp, UdpCast.cpp, UdpNode.cpp
```

---

## 2. 包含的组件

| 族 | 组件 | 类名 |
|---|---|---|
| **TCP** | TCP Server | `CTcpServer` |
| | TCP Pull Server | `CTcpPullServer` |
| | TCP Pack Server | `CTcpPackServer` |
| | TCP Client | `CTcpClient` |
| | TCP Pull Client | `CTcpPullClient` |
| | TCP Pack Client | `CTcpPackClient` |
| **UDP** | UDP Server | `CUdpServer` |
| | UDP Client | `CUdpClient` |
| | UDP ARQ Client | `CUdpArqClient` |
| | UDP ARQ Server | `CUdpArqServer` |
| | UDP Cast（组播/广播） | `CUdpCast` |
| | UDP Node（点对点） | `CUdpNode` |

回调基类共 10 个：`CTcpServerListener`、`CTcpPullServerListener`、
`CTcpClientListener`、`CTcpPullClientListener`、`CUdpServerListener`、
`CUdpClientListener`、`CUdpCastListener`、`CUdpNodeListener`
（Pack 组件复用 `CTcpServerListener` / `CTcpClientListener`）。

---

## 3. 在你的 Visual Studio 工程里使用

### 3.1 加文件与工程属性

1. 把 `hp-allSocket.h`、`hp-allSocket.cpp` 复制到工程目录，加入工程；
2. 工程属性：

| 属性 | 值 |
|---|---|
| C++ 语言标准 | **C++17 或更高** |
| 字符集 | Unicode 或 MBCS 均可（都实测通过） |
| ATL | **需要**（VS 自带，装 VS 时勾选"用于最新 v143 生成工具的 C++ ATL"） |
| MFC | 不需要 |
| 运行库 | `/MD` 或 `/MDd` 均可 |

3. **不需要**做的事：不用配 include 目录、不用手动链接
   （文件内有 `#pragma comment(lib, "ws2_32")` 和 `"Winmm"`）、
   不用定义任何宏。

> `hp-allSocket.h` 只关闭 `_SSL_DISABLED` / `_HTTP_DISABLED` /
> `_ZLIB_DISABLED` / `_BROTLI_DISABLED`，**不关闭 UDP**，所以 TCP 和 UDP 都可用。

### 3.2 同时使用 TCP 与 UDP

```cpp
#include "hp-allSocket.h"

class CMyTcpListener : public CTcpServerListener
{
public:
    virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID,
                                     const BYTE* pData, int iLength)
    {
        pSender->Send(dwConnID, pData, iLength);   // 回显
        return HR_OK;
    }
    virtual EnHandleResult OnClose(ITcpServer*, CONNID, EnSocketOperation, int) { return HR_OK; }
};

class CMyUdpListener : public CUdpServerListener
{
public:
    virtual EnHandleResult OnPrepareListen(IUdpServer*, SOCKET) { return HR_IGNORE; }
    virtual EnHandleResult OnAccept(IUdpServer*, CONNID, UINT_PTR) { return HR_IGNORE; }
    virtual EnHandleResult OnHandShake(IUdpServer*, CONNID) { return HR_IGNORE; }
    virtual EnHandleResult OnSend(IUdpServer*, CONNID, const BYTE*, int) { return HR_IGNORE; }
    virtual EnHandleResult OnClose(IUdpServer*, CONNID, EnSocketOperation, int) { return HR_IGNORE; }
    virtual EnHandleResult OnShutdown(IUdpServer*) { return HR_IGNORE; }

    virtual EnHandleResult OnReceive(IUdpServer* pSender, CONNID dwConnID,
                                     const BYTE* pData, int iLength)
    {
        pSender->Send(dwConnID, pData, iLength);   // 回显
        return HR_OK;
    }
};

int main()
{
    CMyTcpListener tcpListener;
    CMyUdpListener udpListener;

    CTcpServer tcp(&tcpListener);
    CUdpServer udp(&udpListener);

    tcp.Start("0.0.0.0", 5555);
    udp.Start("0.0.0.0", 5556);

    printf("TCP on 5555, UDP on 5556. Press Enter to stop.\n");
    getchar();

    tcp.Stop();
    udp.Stop();
    return 0;
}
```

这就是合并版的核心价值：**两族组件在同一个进程里、同一份底座之上协同工作**。

### 3.3 各族的完整示例

各组件更详细的用法（含 UdpArqClient 握手、UdpNode 点对点、UdpCast 参数、
Pull/Pack 模型）请看另外两份说明：

- TCP：`hp-socket/README_整合说明.md`
- UDP：`hp-udpSocket/README_整合说明.md`

### 3.4 内联工厂函数（12 个）

`hp-allSocket.h` 末尾提供两族各 6 个内联工厂：

```cpp
// TCP
ITcpServer  *t1 = CreateTcpServer    (&listener);
IPullSocket *t2 = CreateTcpPullServer(&listener);
IPackSocket *t3 = CreateTcpPackServer(&listener);
ITcpClient  *t4 = CreateTcpClient    (&listener);
IPullClient *t5 = CreateTcpPullClient(&listener);
IPackClient *t6 = CreateTcpPackClient(&listener);

// UDP
CUdpServer    *u1 = CreateUdpServer   (&listener);
CUdpClient    *u2 = CreateUdpClient   (&listener);
CUdpArqClient *u3 = CreateUdpArqClient(&listener);
CUdpArqServer *u4 = CreateUdpArqServer(&listener);
CUdpCast      *u5 = CreateUdpCast     (&listener);
CUdpNode      *u6 = CreateUdpNode     (&listener);

DestroyTcpServer(t1);   DestroyUdpServer(u1);   // 用完销毁
```

> **关于返回类型**：Pull/Pack 组件的真实声明是
> `DualInterface<IPullSocket, CTcpServer>`，其中 `ITcpServer` 是**二义基类**，
> 无法直接命名。所以工厂返回无二义的 socket 接口（`IPullSocket*` /
> `IPackSocket*`），需要更宽的 API 时自己向上转型。

### 3.5 与单族版本的关键差异

`hp-allSocket.h` 与 `hp-tcpSocket.h` / `hp-udpSocket.h` **不要混用**：

| 场景 | 该用哪套 |
|---|---|
| 只要 TCP | `hp-tcpSocket.h` + `hp-tcpSocket.cpp` |
| 只要 UDP | `hp-udpSocket.h` + `hp-udpSocket.cpp` |
| TCP 和 UDP 都要 | **`hp-allSocket.h` + `hp-allSocket.cpp`** |

把 `hp-tcpSocket.cpp` 和 `hp-udpSocket.cpp` 同时加进一个工程会重复符号。
把 `hp-allSocket.cpp` 与其中任何一个单族 `.cpp` 同时加进去，**同样会重复符号**。

---

## 4. 实测验证结果

**MSVC v19.44.35229（VS 2022 Build Tools 17.14）+ Windows SDK 10.0.26100.0**

冒烟测试 `build/smoke-all.cpp`（68 项断言）跑真实网络收发：

| 配置 | 字符集 | 编译 | 运行 |
|---|---|---|---|
| Debug `/MDd /Zi` | MBCS | 0 错误 0 警告 | ✅ 68/68 |
| Debug `/MDd /Zi` | UNICODE | 0 错误 0 警告 | ✅ 68/68 |
| Release `/O2 /MD /DNDEBUG` | MBCS | 0 错误 0 警告 | ✅ 68/68 |
| Release `/O2 /MD /DNDEBUG` | UNICODE | 0 错误 0 警告 | ✅ 68/68 |

**无任何 `LNK2005` / `LNK4006` 重复符号告警。**

隔离部署也验证过：在只含 `hp-allSocket.h` / `hp-allSocket.cpp` 两个文件的
空目录里，`/O2` 编译零错误、68/68 全绿。

### 这个测试专门验证了单族测试无法验证的两件事

1. **12 个组件在同一个翻译单元里共存，没有重复符号**
   （若底座被内联两次，链接会直接失败）；
2. **TCP 与 UDP 同时工作**：第 3 节里同时开着 TCP Server/Client 和
   UDP Server/Client/ARQ，先跑完 UDP（含 KCP 握手），
   再回头验证 TCP 仍在正常收发。

### 测试覆盖

- 12 个组件的构造 / 状态查询 / 析构
- **三种 TCP 模型同时运行**：Push / Pull / Pack，各自独立端口，全部往返 + 回显 + 逐字节比对
- **UDP 与 TCP 并发**：UDP Server/Client 往返、UDP ARQ 握手与可靠收发，期间 TCP 保持在线
- **UdpNode 点对点**往返 + 回显
- **UdpCast** 构造与默认模式
- **12 个工厂函数**的创建与销毁
- 载荷含**内嵌 `\0`** 与**结尾 `\0`**，逐字节精确比对

复现方式（`build/` 目录下）：

```cmd
gen-all.ps1                    :: 重新生成两个文件
check-parity.ps1               :: 校验合并版清单 == TCP 清单 ∪ UDP 清单
smoke-all.bat MBCS Debug       :: Debug 链接 + 运行
smoke-all.bat UNICODE Release  :: Release + Unicode
```

---

## 5. ⚠️ 已知缺陷：UDP ARQ 发送返回值错误（HP-Socket 6.0.9 原版缺陷）

`CUdpArqClient::Send()` / `CUdpArqServer::Send()` **恒返回 `FALSE`**，
且 `GetLastError()` 会被设为一个**等于载荷长度**的数值，但**数据实际会送达**。

根因在 `Windows/Src/ArqHelper.h` 第 325-346 行：

```cpp
rs = ::ikcp_send(m_kcp, (const char*)pBuffer, iLength);
if(rs < 0) rs = ERROR_INCORRECT_SIZE;   // 仅失败时改写

if(rs == NO_ERROR)          // ← 成功时 rs == iLength，永远不等于 0
    Flush(TRUE);            // ← 因此 Flush 被跳过

return rs;                  // ← 返回 iLength，被上层当作成功码 0 比较
```

KCP 的 `ikcp_send()` 成功时返回**被接受的字节数**（`Common/kcp/ikcp.c:517/546`），
不是 0。后果有两个：

1. **`Flush(TRUE)` 被跳过**：数据要等 60 ms（`dwFlushInterval`）的定时器才发出，
   延迟敏感场景会有额外延迟；
2. **返回值语义错误**：`Send()` 报告失败；且 `UdpArqClient.cpp:112-113` 的
   `SendPackets()` 单缓冲区分支**直接把它当错误码返回**。

### 实测证据

```
[PASS] ARQ Send() reproduces the known upstream defect
       (Send()=FALSE, GetLastError()=17 == payload length 17, as expected)
```

判据：**`GetLastError()` 返回值等于载荷长度**。

### 我的处理方式

**我没有修改它。** `hp-allSocket.cpp` 对 `ArqHelper.h` 是逐行复制，未做语义改动，
以保证行为与官方 HP-Socket 6.0.9 完全一致、整合过程可复现。
但我在冒烟测试里加了一条**断言把这个缺陷钉住**，将来官方修复或你打补丁时，
测试会立刻失败并提醒你行为变了。

### 如果你要修

在 `hp-allSocket.cpp` 里搜 `ArqHelper.h` 的 banner 注释，找到 `CArqSessionT::Send()`，
把

```cpp
        rs = ::ikcp_send(m_kcp, (const char*)pBuffer, iLength);
        if(rs < 0) rs = ERROR_INCORRECT_SIZE;
    }

    if(rs == NO_ERROR)
        Flush(TRUE);

    return rs;
```

改为

```cpp
        rs = ::ikcp_send(m_kcp, (const char*)pBuffer, iLength);
        if(rs < 0) { rs = ERROR_INCORRECT_SIZE; }
        else       { rs = NO_ERROR; }          // 成功时归一化为 NO_ERROR
    }

    if(rs == NO_ERROR)
        Flush(TRUE);

    return rs;
```

> 需要我应用这个补丁吗？告诉我即可，我会同时更新测试断言和文档。

---

## 6. 已剔除的内容

| 剔除项 | 说明 |
|---|---|
| **SSL / HTTPS** | 去掉 openssl 依赖（你确认只用 TCP + UDP） |
| **HTTP / WebSocket** | 非本次范围 |
| **Agent（多客户端）** | 只要 Server / Client / Node |
| **C (4C) 接口** | 只保留 C++ API |
| **TCP 之外的压缩** | zlib / brotli 是 HTTP 专用 |
| **线程池** | 只被原 `HP_Create_*` 门面使用 |
| **零使用文件** | `Common/SE.h`、`Common/Win32Helper.h`、`Common/Thread.*`、`Common/debug/win32_crtdbg.*` |

### 如何恢复 SSL

1. 把 `SSLServer.*`、`SSLClient.*`、`SSLHelper.*` 加进 `build/gen-all.ps1`
   的 `$TcpSources`（以及 `$TcpHeaders` 里的 `SSLServer.h` 等）；
2. 注释掉 `hp-allSocket.h` 开头的 `#define _SSL_DISABLED`；
3. 安装 OpenSSL 并链接 `libssl.lib` / `libcrypto.lib` / `crypt32.lib`；
4. 重新运行 `gen-all.ps1` 和 `check-parity.ps1`。

---

## 7. 三套交付物对照

| | `hp-tcpSocket` | `hp-udpSocket` | `hp-allSocket` |
|---|---|---|---|
| 内容 | TCP 6 组件 | UDP 6 组件 | TCP + UDP 12 组件 |
| 行数 | 17,786 | 22,535 | 25,926 |
| 依赖 | ATL、C++17 | ATL、C++17 | ATL、C++17 |
| 内联 KCP | — | ✅ | ✅ |
| 与其它套共存 | ❌ 会重复符号 | ❌ 会重复符号 | ❌ 会重复符号 |
| 冒烟测试 | 36 项 | 45 项 | 68 项 |
| 适用 | 只要 TCP | 只要 UDP | **两者都要** |

**三者只能选一套**加进同一个工程。

### 为什么合并版比两套之和（40,321 行）小得多

因为共享底座只保留了一份。这个底座（`Common/*` + `SocketHelper` +
`MiscHelper` + `ArqHelper` + `ikcp`）本身约 1.4 万行，
在两套单族版本里各存了一份。

---

## 8. 整合质量保证

### 8.1 清单自动比对

`build/check-parity.ps1` 会从三个生成器脚本里**自动解析**组件清单，
断言合并版恰好等于"TCP 清单 ∪ UDP 清单"，不多不少。当前结果：

```
component headers
  [OK]   combined == TCP union UDP: 12 entries, exact match
  [OK]   TCP group order: relative order preserved
  [OK]   UDP group order: relative order preserved
component sources
  [OK]   combined == TCP union UDP: 8 entries, exact match
shared base
  [OK]   combined base == TCP base union UDP base: 9 entries, exact match
  [OK]   combined base: no file inlined twice
PARITY CHECK PASSED
```

这个脚本刻意包含**防空断言**——如果清单解析出 0 项会直接判失败，
避免"0 等于 0"式的假阳性通过。

### 8.2 逐行可追溯

两个整合文件里每个代码段前都有 banner 注释标明**来源文件**：

```c
/* ========================================================================== */
/*  TcpServer.cpp
/*  source: Windows\Src\TcpServer.cpp
/* ========================================================================== */
```

被注释掉的内部 include 也保留了原文，便于定位：

```c
/* [amalgamated] #include "stdafx.h" */
```

### 8.3 原件未改动

整合全程**没有修改** `Windows/Src` 下任何文件（104 个文件，时间戳未变）。

---

## 9. 关于许可

HP-Socket 采用 **Apache License 2.0**，允许修改和再分发。两个整合文件的文件头
保留了原始出处（Bruce Liang / ldcsaa）和授权声明。
KCP（`ikcp.c`）为 MIT 许可，同样允许再分发。
