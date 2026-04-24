# Setup

Install wapm(WAnime Package Manager)

```sh
curl -fsSL https://wapm.wanime.io/install.sh | sh
```

Install waRPC codegen CLI

```sh
curl -fsSL https://warpc.wanime.io/install.sh | sh
```

Install server & client SDKs

```sh
wapm add waRPC-server
wapm add waRPC-client
```

# Running Examples

To run a specific example:

```sh
gh repo clone TimeTo10X/waRPC-examples
cd waRPC=examples/<example_name>

# Configure and build example project
just init
```

Then to start a server

```sh
just run server
```

And for the client

```sh
just run client
```

# Docs

All of the API documentation can be found at [wanime.io/warpc](https://wanime.io/warpc)

# License

All of the projects inside this repo are licensed under MIT license.
