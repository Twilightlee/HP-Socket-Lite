# hp-tcpSocket / hp-udpSocket / hp-allSocket

从 [HP-Socket](https://github.com/ldcsaa/HP-Socket) 中分离、精简、融合出来的独立 Socket 组件。

## 简介

本项目从 HP-Socket 中提取出 TCP、UDP 相关组件，去除 SSL 支持、无关依赖和冗余代码，**精简融合为极少的文件**，做到 **standalone**——不依赖 HP-Socket 原项目的任何其他文件，可直接复制进你的项目使用。
本项目为第三方独立提取版本，非 HP-Socket 官方项目，与原作者无隶属或背书关系。

## 三个模块

| 模块 | 内容 | 文件 |
|---|---|---|
| **hp-tcpSocket** | 从 HP-Socket 中分离出来的 **TCP 相关组件** | 少量文件，无其它依赖 |
| **hp-udpSocket** | 从 HP-Socket 中分离出来的 **UDP 相关组件** | 少量文件，无其它依赖 |
| **hp-allSocket** | 从 HP-Socket 中分离出来的 **TCP + UDP 相关组件** | 仅两个文件，无其它依赖 |

> 三个模块按需选用：只用 TCP 选 `hp-tcpSocket`，只用 UDP 选 `hp-udpSocket`，两者都要选 `hp-allSocket`。

## 特点

- **精简**：剥离了 SSL 支持、UDP/TCP 交叉依赖等无关内容，只保留核心 Socket 功能。
- **融合**：原项目中分散在多个文件里的组件，被整合为极少的文件。
- **独立（standalone）**：不依赖 HP-Socket 原项目的其他文件，复制即可用。
- **单头文件友好**：`hp-allSocket` 仅两个文件（`.h` + `.cpp`），也可进一步合并为 single-header library。

## 文件说明

以 `hp-allSocket` 为例：

    hp-allSocket.h    // 声明（可选：用宏控制实现）
    hp-allSocket.cpp  // 实现

`hp-tcpSocket`、`hp-udpSocket` 同理，仅保留各自协议相关的部分。

## 使用方式

1. 将对应模块的文件复制到你的项目中。
2. 把 `.cpp` 加入构建（或按 single-header 方式 `#define` 宏后 include）。
3. `#include` 对应头文件即可使用。

示例：

    #include "hp-allSocket.h"

    // 使用 TCP / UDP 组件

## 来源与致谢

本项目基于 [HP-Socket](https://github.com/ldcsaa/HP-Socket) 提取整理。HP-Socket 是一个高性能的 TCP/UDP Socket 通信框架，感谢原作者 [ldcsaa](https://github.com/ldcsaa) 及所有贡献者。

## 说明

- 本项目仅做**提取、精简与融合**，核心逻辑来源于 HP-Socket。
- 如需完整功能（SSL、HTTP、各类 Agent 等），请使用原项目 HP-Socket。

## License

本项目包含基于 HP-Socket (Apache License 2.0) 修改的代码。原始版权归 HP-Socket 作者所有。本项目的分发遵循 Apache License 2.0，详见 LICENSE。

## AS IS 声明

本项目按 **“原样”（AS IS）** 提供，不附带任何形式的明示或暗示担保，包括但不限于对适销性、特定用途适用性及非侵权性的担保。

在任何情况下，作者或版权持有人均不对任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权行为还是其他方面，亦无论是否与本软件或本软件的使用或其他交易有关。

使用本项目即表示你自行承担全部风险。因使用或无法使用本项目而导致的任何直接、间接、附带、特殊、惩罚性或后果性损害，作者概不负责。

本项目为对 HP-Socket 的提取、精简与融合版本，请同时遵守原项目 HP-Socket 的许可证及免责声明。

