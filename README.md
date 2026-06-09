<div align="center">

### WAnime RPC Examples

[English](README.md) | [日本語](README_jp.md) | [台灣中文](README_tw.md)

Blazingly fast RPC framework built by [wanime.io](https://wanime.io)

</div>

---

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Dev Setup](#dev-setup)
3. [C++](#c)
4. [Odin](#odin)
5. [Rust](#rust)
6. [Go](#go)
7. [WebTransport](#webtransport)
8. [Licensing](#licensing)

> [!TIP]
> U can find detailed docs here > [wanime.io/warpc](https://wanime.io/warpc)

## Prerequisites

### Platforms

waRPC supports following platforms:

- MacOS:
  - Intel x64
  - Apple Silicon arm64
- Linux:
  - x64
  - arm64
- IOS:
  - 16.3+
  - arm64

### Tools

In order to proceed with the examples, you will need to install the following tools:

- wapm - WAnime package manager
- wrsc - WAnime RPC schema compiler

Installing wapm && wrsc:

```sh
curl -fsSL https://wapm.wanime.io/install.sh | sh
```

```sh
curl -fsSL https://wrsc.wanime.io/install.sh | sh
```

### waRPC Core Libs

After installing `wapm`, you will also need to install a few of the core `waRPC` libraries:

- wanime-sdk: Bundle of core waRPC SDK libraries
- polyglot: Serialization protocol

Install via `wapm`

```sh
TODO
```

> [!IMPORTANT]
> Please note that, each package in `wapm` has its own license attached to it! </br>
> Some of the packages may also require a `license key`.

## Dev Setup

Compile `.wa.rpc` schema files

```sh
j wrsc
```

> [!TIP]
> `waRPC` is language agnostic, so u can do smth like this:
>
> - `c++ client` <-> `odin server`
> - `c++ client` <-> `go server`
> - `odin client` <-> `rust server`

## C++

Building `c++` examples.

```

j cpp_build

```

Start server.

```

j cpp_serve

```

Run client.

```

j cpp_client

```

## Odin

Start server.

```

j odin_serve

```

Run client.

```

j odin_client

```

## Rust

Start server.

```

j rust_serve

```

Run client.

```

j rust_client

```

## Go


Start server.

```

j go_serve

```

Run client.

```

j go_client

````

## WebTransport

Spin up any `waRPC` server:

```sh
j cpp_serve|odin_serve|rust_serve|go_serve
````

## Licensing

- [WAnime RPC Non-Commercial](https://)
- [WAnime RPC Commercial](https://)
- [WAnime RPC Enterprise](https://)
