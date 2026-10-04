# HP-Socket 6.0.9 UDP 组件整合说明

把 HP-Socket 6.0.9（Windows 版）的 **UDP 组件**提取整合成两个文件，用法与 TCP 版
（`hp-socket.h` / `hp-socket.cpp`）完全一致：**拷进 VS 工程就能编译使用**。

```
hp-udpSocket/
├── hp-udpSocket.h      13,593 行
└── hp-udpSocket.cpp     8,942 行
                        ─────────
                        22,535 行
```

> 这两个文件与 TCP 版**完全独立**，可以单独使用，也可以和 TCP 版一起放进同一个工程
> （见第 8 节）。

---

## 1. 包含的组件

| 组件 | 类名 | 主要接口 |
|---|---|---|
| UDP Server | `CUdpServer` | `IUdpServer` |
| UDP Client | `CUdpClient` | `IUdpClient` |
| UDP ARQ Client | `CUdpArqClient` | `IArqClient` + `IUdpClient` |
| **UDP ARQ Server** | `CUdpArqServer` | `IArqSocket` + `IUdpServer` |
| UDP Cast（组播/广播） | `CUdpCast` | `IUdpCast` |
| UDP Node（点对点） | `CUdpNode` | `IUdpNode` |

回调基类：`CUdpServerListener`、`CUdpClientListener`、`CUdpCastListener`、
`CUdpNodeListener`。

### 关于 UdpArqServer 的说明

你最初列的清单里没有 `UdpArqServer`，我**主动把它加进来了**，理由是：
`CUdpArqClient` 无法与普通 `CUdpServer` 通信——KCP 握手需要两端都是 ARQ 端点。
只给 ARQ 客户端而给不了 ARQ 服务端，这个组件实际上不可用。
额外代价只有约 25 行头文件 + 1 个源文件。

如果你确实不要它，从 `build/gen-udp.ps1` 的 `$componentHeaders` 和
`$sourceUnits` 里删掉对应两行重新生成即可。

### 关于 KCP

`CUdpArqClient` / `CUdpArqServer` 的可靠传输基于 **KCP**（`Common/kcp/ikcp.c`，
1,431 行 C 代码）。它已经**一并内联进 `hp-udpSocket.cpp`**，你不需要单独添加。

### 关于 UdpCast 的适用范围

`CUdpCast` **只能用于组播（multicast）和广播（broadcast）**，不能做单播点对点。
依据是 `UdpCast.cpp:43` 的 `ASSERT(usLocalPort == 0)` 和 `UdpCast.cpp:87`
的 `CheckParams` 要求 `CM_MULTICAST <= m_enCastMode <= CM_BROADCAST`。
单播场景请用 `CUdpClient`。

---

## 2. 在你的 Visual Studio 工程里使用

### 2.1 加文件与工程属性

1. 把 `hp-udpSocket.h`、`hp-udpSocket.cpp` 复制到工程目录，加入工程；
2. 工程属性：

| 属性 | 值 |
|---|---|
| C++ 语言标准 | **C++17 或更高** |
| 字符集 | Unicode 或 MBCS 均可（都实测通过） |
| ATL | **需要**（VS 自带，装 VS 时勾选"用于最新 v143 生成工具的 C++ ATL"） |
| MFC | 不需要 |
| 运行库 | `/MD` 或 `/MDd` 均可 |

3. **不需要**做的事：不用配 include 目录、不用手动链接
   （`hp-udpSocket.cpp` 内有 `#pragma comment(lib, "ws2_32")` 和 `"Winmm"`）、
   不用定义任何宏（文件自带 `HPSOCKET_STATIC_LIB` 以及关闭 SSL/HTTP/压缩的开关）。

> **注意**：`hp-udpSocket.h` 里**没有**定义 `_UDP_DISABLED`，因为 UDP 就是它的内容。
> 它只关闭 `_SSL_DISABLED` / `_HTTP_DISABLED` / `_ZLIB_DISABLED` / `_BROTLI_DISABLED`。

### 2.2 服务端示例（UDP Server）

```cpp
#include "hp-udpSocket.h"

class CMyUdpServer : public CUdpServerListener
{
public:
    virtual EnHandleResult OnPrepareListen(IUdpServer* pSender, SOCKET soListen) { return HR_IGNORE; }
    virtual EnHandleResult OnAccept(IUdpServer* pSender, CONNID dwConnID, UINT_PTR soClient) { return HR_IGNORE; }
    virtual EnHandleResult OnHandShake(IUdpServer* pSender, CONNID dwConnID) { return HR_IGNORE; }
    virtual EnHandleResult OnSend(IUdpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) { return HR_IGNORE; }
    virtual EnHandleResult OnClose(IUdpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) { return HR_IGNORE; }
    virtual EnHandleResult OnShutdown(IUdpServer* pSender) { return HR_IGNORE; }

    virtual EnHandleResult OnReceive(IUdpServer* pSender, CONNID dwConnID,
                                     const BYTE* pData, int iLength)
    {
        pSender->Send(dwConnID, pData, iLength);       // 回显
        return HR_OK;
    }
};

int main()
{
    CMyUdpServer listener;

    CUdpServer server(&listener);
    if (!server.Start("0.0.0.0", 5555))
    {
        printf("Start failed\n");
        return 1;
    }

    printf("UDP listening on 5555, press Enter to stop\n");
    getchar();

    server.Stop();       // 析构时也会自动 Stop
    return 0;
}
```

### 2.3 客户端示例（UDP Client）

```cpp
#include "hp-udpSocket.h"

class CMyUdpClient : public CUdpClientListener
{
public:
    virtual EnHandleResult OnConnect(IUdpClient* pSender, CONNID dwConnID)
    {
        m_connected = true;
        return HR_IGNORE;
    }
    virtual EnHandleResult OnHandShake(IUdpClient* pSender, CONNID dwConnID) { return HR_IGNORE; }
    virtual EnHandleResult OnSend(IUdpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) { return HR_IGNORE; }
    virtual EnHandleResult OnClose(IUdpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) { return HR_IGNORE; }

    virtual EnHandleResult OnReceive(IUdpClient* pSender, CONNID dwConnID,
                                     const BYTE* pData, int iLength)
    {
        printf("recv %d bytes\n", iLength);
        return HR_OK;
    }

    bool m_connected = false;
};

int main()
{
    CMyUdpClient listener;

    CUdpClient client(&listener);
    //   第 3 个参数 bAsyncConnect: TRUE 异步连接
    //   注意：UDP 服务端要靠客户端先发包才能获知其地址，
    //   所以要尽早 Send，或像这里用同步连接后再发
    client.Start("127.0.0.1", 5555, FALSE);

    if (client.IsConnected())
        client.Send((const BYTE*)"hello", 5);

    Sleep(1000);
    client.Stop();
    return 0;
}
```

### 2.4 ARQ 客户端（可靠 UDP，基于 KCP）

```cpp
#include "hp-udpSocket.h"

class CMyArqClient : public CUdpClientListener
{
public:
    virtual EnHandleResult OnConnect(IUdpClient*, CONNID) { return HR_IGNORE; }
    virtual EnHandleResult OnHandShake(IUdpClient*, CONNID) { m_ready = true; return HR_IGNORE; }
    virtual EnHandleResult OnSend(IUdpClient*, CONNID, const BYTE*, int) { return HR_IGNORE; }
    virtual EnHandleResult OnClose(IUdpClient*, CONNID, EnSocketOperation, int) { return HR_IGNORE; }
    virtual EnHandleResult OnReceive(IUdpClient*, CONNID, const BYTE* pData, int iLength) { return HR_OK; }

    bool m_ready = false;
};

int main()
{
    CMyArqClient listener;

    CUdpArqClient arq(&listener);
    arq.Start("127.0.0.1", 5555, FALSE);           // 对端必须是 CUdpArqServer

    // 等握手完成
    for (int i = 0; i < 250 && !listener.m_ready; i++) Sleep(20);

    // 等组件进入 connected 状态再发送
    for (int i = 0; i < 250 && !arq.IsConnected(); i++) Sleep(20);

    BOOL ok = arq.Send((const BYTE*)"reliable", 8);
    // ⚠️ 见第 6 节：当前版本 Send() 恒返回 FALSE，但数据会送达
    printf("Send() returned %d (see README section 6)\n", ok);

    Sleep(2000);
    arq.Stop();
    return 0;
}
```

### 2.5 UDP Node（点对点，无需连接）

```cpp
#include "hp-udpSocket.h"

class CMyNode : public CUdpNodeListener
{
public:
    virtual EnHandleResult OnPrepareListen(IUdpNode*, SOCKET) { return HR_IGNORE; }
    virtual EnHandleResult OnSend(IUdpNode*, LPCTSTR, USHORT, const BYTE*, int) { return HR_IGNORE; }
    virtual EnHandleResult OnError(IUdpNode*, EnSocketOperation, int, LPCTSTR, USHORT, const BYTE*, int) { return HR_IGNORE; }
    virtual EnHandleResult OnShutdown(IUdpNode*) { return HR_IGNORE; }

    virtual EnHandleResult OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress,
                                     USHORT usRemotePort, const BYTE* pData, int iLength)
    {
        // 给对方回一发
        pSender->Send(lpszRemoteAddress, usRemotePort, pData, iLength);
        return HR_OK;
    }
};

int main()
{
    CMyNode listener;

    CUdpNode node(&listener);
    node.Start("127.0.0.1", 6000);

    // 直接发往对端地址，无需先建立连接
    node.Send("127.0.0.1", 6001, (const BYTE*)"ping", 4);

    Sleep(1000);
    node.Stop();
    return 0;
}
```

### 2.6 内联工厂函数

`hp-udpSocket.h` 末尾提供 6 个内联工厂，代替原版那套 `HP_Create_*`：

```cpp
CUdpServer    *srv    = CreateUdpServer   (&listener);
CUdpClient    *cli    = CreateUdpClient   (&listener);
CUdpArqClient *arq    = CreateUdpArqClient(&listener);
CUdpArqServer *arqSrv = CreateUdpArqServer(&listener);
CUdpCast      *cast   = CreateUdpCast     (&listener);
CUdpNode      *node   = CreateUdpNode     (&listener);

DestroyUdpServer(srv);      // 用完销毁
DestroyUdpClient(cli);
DestroyUdpArqClient(arq);
DestroyUdpArqServer(arqSrv);
DestroyUdpCast(cast);
DestroyUdpNode(node);
```

---

## 3. 实测验证结果

**MSVC v19.44.35229（VS 2022 Build Tools 17.14）+ Windows SDK 10.0.26100.0**

冒烟测试 `build/smoke-udp.cpp`（45 项断言）跑真实 UDP 往返：

| 配置 | 字符集 | 编译 | 运行 |
|---|---|---|---|
| Debug `/MDd /Zi` | MBCS | 0 错误 0 警告 | ✅ 45/45 |
| Debug `/MDd /Zi` | UNICODE | 0 错误 0 警告 | ✅ 45/45 |
| Release `/O2 /MD /DNDEBUG` | MBCS | 0 错误 0 警告 | ✅ 45/45 |
| Release `/O2 /MD /DNDEBUG` | UNICODE | 0 错误 0 警告 | ✅ 45/45 |

隔离部署也验证过：在只含 `hp-udpSocket.h` / `hp-udpSocket.cpp` 两个文件的
空目录里，`/O2` 编译零错误、45/45 全绿 —— 确认真正自包含。

覆盖内容：

- 6 个组件的构造 / 状态查询 / 析构
- **UdpServer ↔ UdpClient** 真实数据报往返 + 回显
- **UdpArqClient ↔ UdpArqServer** KCP 双向握手 + 可靠收发 + 回显
- **UdpNode ↔ UdpNode** 点对点双向收发 + 回显
- **UdpCast** 构造、组播参数读写、以及"单播模式被正确拒绝"
- 6 个内联工厂的创建与销毁
- 数据**逐字节精确比对**：31 字节载荷，含**内嵌 `\0`** 和**结尾 `\0`**

复现方式（`build/` 目录下）：

```cmd
gen-udp.ps1                     :: 重新生成两个文件
build-udp.bat MBCS              :: 只编译
smoke-udp.bat MBCS Debug        :: Debug 链接 + 运行
smoke-udp.bat UNICODE Release   :: Release + Unicode
```

---

## 4. 已剔除的内容

| 剔除项 | 说明 |
|---|---|
| **SSL / HTTPS** | 去掉 openssl 依赖 |
| **HTTP / WebSocket** | 非 UDP |
| **TCP 全部组件** | 本文件不含 TCP Server/Client（用另一套 `hp-socket.h`） |
| **Agent（多客户端）** | 只要 Server / Client / Node |
| **C (4C) 接口** | 只保留 C++ API |
| **zlib / brotli 压缩** | HTTP 专用 |
| **线程池** | 只被原 `HP_Create_*` 门面使用 |
| **零使用文件** | `Common/SE.h`、`Common/Win32Helper.h`、`Common/Thread.*`、`Common/debug/win32_crtdbg.*` |

### 复用了 TCP 的基础设施（这是无法避免的）

UDP 组件依赖 `SocketHelper.h`（提供 `TUdpSocketObj`、`TUdpBufferObj`、
IOCP 投递、地址解析等），而 `SocketHelper.h` 同时包含 TCP 侧的基础设施。
所以 `hp-udpSocket.h` 里会有约 6,000 行"TCP 基础设施"代码 —— 但它们只是
**被 UDP 依赖的公共底座**，文件里**没有** `CTcpServer` / `CTcpClient` 等
TCP 组件类。

---

## 5. ARQ 缺陷的完整复现方法

如果你想自己在官方源码里验证这个缺陷，或者将来核对修复情况：

```cpp
CUdpArqServer srv(&srvListener);
CUdpArqClient arq(&cliListener);

srv.Start("127.0.0.1", 5555);
arq.Start("127.0.0.1", 5555, FALSE);

for (int i = 0; i < 250 && !cliListener.m_handshaked; i++) Sleep(20);
for (int i = 0; i < 250 && !arq.IsConnected();     i++) Sleep(20);

BOOL ok = arq.Send((const BYTE*)"x", 1);
printf("Send()=%d  GetLastError()=%lu\n", ok, GetLastError());

// 实际输出: Send()=0  GetLastError()=1
// 注意 GetLastError() 恰好等于你传入的 iLength
```

判据：**`GetLastError()` 返回值等于载荷长度**时，说明 `rs` 未经过负数改写、
被原样返回了。

---

## 6. ⚠️ 已知缺陷：ARQ 发送返回值错误（HP-Socket 6.0.9 原版缺陷）

### 现象

`CUdpArqClient::Send()` 和 `CUdpArqServer::Send()` **恒返回 `FALSE`**，
同时 `GetLastError()` 被设为一个"等于载荷长度"的数值。
但**数据实际会送达对端**，功能本身可用。

### 根因

`Windows/Src/ArqHelper.h` 第 325-346 行，`CArqSessionT::Send()`：

```cpp
int Send(const BYTE* pBuffer, int iLength)
{
    if(!IsReady())
        return ERROR_INVALID_STATE;

    int rs = NO_ERROR;

    {
        CCriSecLock sendlock(m_csSend);
        if(!IsReady())
            return ERROR_INVALID_STATE;

        rs = ::ikcp_send(m_kcp, (const char*)pBuffer, iLength);
        if(rs < 0) rs = ERROR_INCORRECT_SIZE;   // 仅失败时改写
    }

    if(rs == NO_ERROR)          // ← 成功时 rs == iLength，永远不等于 0
        Flush(TRUE);            // ← 因此 Flush 被跳过

    return rs;                  // ← 返回 iLength，被上层当作成功码 0 比较
}
```

KCP 的 `ikcp_send()` 成功时返回**被接受的字节数**（见 `Common/kcp/ikcp.c`
第 517、546 行 `return sent;` / `return len;`），而不是 0。

### 两个实际后果

1. **`Flush(TRUE)` 被跳过**：数据不会立即发出，而是等下一次
   `dwFlushInterval`（默认 60 ms）的定时器驱动 `ikcp_flush`。
   在延迟敏感场景下会引入最多约 60 ms 的额外延迟。
2. **返回值语义错误**：`Send()` 对调用方报告失败。更糟的是
   `UdpArqClient.cpp:112-113` 的 `SendPackets()` 单缓冲区分支**直接把
   `Send()` 的返回值当成错误码返回**，所以错误码会变成载荷长度本身。

### 我的处理方式

**我没有修改它。** 两个整合文件对 `ArqHelper.h` 是逐行复制，未做任何语义改动，
以保证：
- 行为与官方 HP-Socket 6.0.9 完全一致；
- 整合过程可复现、可审查；
- 你能明确区分"官方行为"和"我改动过的地方"。

但我在冒烟测试里加了一条**显式断言把这个缺陷钉住**：

```
[PASS] ARQ Send() reproduces the known upstream return-value defect
       (Send()=FALSE, GetLastError()=31 == payload length 31, as expected)
```

这样将来官方修复、或你自己打了补丁，这条断言会立刻失败并提醒你行为变了。

### 如果你想修

`hp-udpSocket.cpp` 里搜 `ArqHelper.h` 的 banner 注释，找到 `CArqSessionT::Send()`
（大约在文件 60% 位置），把

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

改完后那条"钉住缺陷"的断言会失败，**这是预期的**，同时 ARQ 的
`Send()` 会开始正确返回 `TRUE`、数据立即发送。

> 是否要我应用这个补丁？告诉我一声即可，我会同时更新测试断言和本文档。

---

## 7. 与 UDP 版原库的迁移对照

| 原写法 | 迁移后 |
|---|---|
| `#include <hpsocket/HPSocket.h>` | `#include "hp-udpSocket.h"` |
| `HP_Create_UdpServer(&listener)` | `CreateUdpServer(&listener)` |
| `HP_Destroy_UdpServer(p)` | `DestroyUdpServer(p)` |
| 链接 `hpsocket.lib` + 拷 `hpsocket.dll` | 什么都不用做，源码级编译 |
| 回调基类、事件签名、`Start/Send/Stop` 等 | **完全不变** |

枚举名、常量名、方法签名与原版一致，现有业务代码可原样保留。

---

## 8. 与 TCP 版一起使用

两套文件**完全独立**，可以同时放进一个工程：

```cpp
#include "hp-socket.h"        // TCP: CTcpServer / CTcpClient / ...
#include "hp-udpSocket.h"     // UDP: CUdpServer / CUdpClient / ...

int main()
{
    CTcpServer tcp(&tcpListener);
    CUdpServer udp(&udpListener);

    tcp.Start("0.0.0.0", 5555);
    udp.Start("0.0.0.0", 5556);
    // ...
}
```

### 但要注意：`SocketHelper` 等基础设施会被编译两份

因为两个 `.cpp` 都各自内联了 `SocketHelper.cpp`、`Common/*.cpp` 等公共部分，
同时使用会产生**重复符号**。

三种处理办法，任选其一：

**办法 A（推荐）：只保留一份公共底座，两个文件共用**

如果你同时需要 TCP 和 UDP，最干净的做法是让我**生成一套合并版**
（`hp-socket-all.h` / `hp-socket-all.cpp`），把 TCP + UDP 放在一起、
公共底座只留一份。告诉我一声即可。

**办法 B：把公共部分抽出来**

从 `hp-udpSocket.cpp` 里删除与 `hp-socket.cpp` 重复的段落
（两个文件的 banner 注释标明了每一段的来源，便于定位）——
具体是 `Common/*.cpp`、`SocketHelper.cpp`、`MiscHelper.cpp` 这几段。

**办法 C：只用一个**

如果你的工程确实只需要其中一套，那就没有这个问题。

> 注意：即使不做任何处理，**同一个 .cpp 单独编译也没问题**——
> 冲突只发生在把两个 `.cpp` 都放进同一个链接单元时。

---

## 9. 关于许可

HP-Socket 采用 **Apache License 2.0**，允许修改和再分发。两个整合文件的文件头
保留了原始出处（Bruce Liang / ldcsaa）和授权声明。
KCP（`ikcp.c`）为 MIT 许可，同样允许再分发。
