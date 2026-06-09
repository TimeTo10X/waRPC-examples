default: h

wa_toolchain := env("LLVM_TOOLCHAIN_PATH")
wa_module := env("WARPC_MODULE_PATH")
warpc_odin := env("WARPC_ODIN_PATH")
warpc_go := env("WARPC_GO_PATH")
warpc_rust := env("WARPC_RS_PATH")
polyglot_odin := env("POLYGLOT_ODIN_PATH")

cc := if os() == "macos" {
    "/opt/homebrew/opt/llvm/bin/clang"
} else {
    "/usr/bin/clang"
}

cxx := if os() == "macos" {
    "/opt/homebrew/opt/llvm/bin/clang++"
} else {
    "/usr/bin/clang++"
}

mac_compilers := if os() == "macos" {
    "-DCMAKE_C_COMPILER=" + `xcrun -f clang` + " -DCMAKE_CXX_COMPILER=" + `xcrun -f clang++`
} else {
    ""
}

export CC := cc
export CXX := cxx

wrsc:
    wrsc -c schema --xlang cxx
    wrsc -c schema --xlang odin
    wrsc -c schema --xlang rust
    wrsc -c schema --xlang go

h:
    echo "rtfm! ^_^"

c:
    rm -rf build

certs:
    #!/usr/bin/env bash
    set -euo pipefail
    mkdir -p certs
    cat > certs/localhost.conf <<'EOF'
    [req]
    distinguished_name = req_distinguished_name
    req_extensions = v3_req
    prompt = no
    [req_distinguished_name]
    C = JP
    ST = Tokyo
    L = Tokyo
    O = Test
    CN = localhost
    [v3_req]
    keyUsage = keyEncipherment, digitalSignature
    extendedKeyUsage = serverAuth
    subjectAltName = @alt_names
    [alt_names]
    DNS.1 = localhost
    IP.1 = 127.0.0.1
    IP.2 = ::1
    EOF
    openssl req -x509 -nodes -days 14 \
        -newkey ec:<(openssl ecparam -name prime256v1) \
        -keyout certs/localhost-ec.key \
        -out certs/localhost-ec.pem \
        -config certs/localhost.conf \
        -extensions v3_req
    openssl x509 -in certs/localhost-ec.pem -noout -subject -dates
    openssl x509 -in certs/localhost-ec.pem -noout -text | grep -A1 "Subject Alternative Name"

trust-certs: certs
    #!/usr/bin/env bash
    set -euo pipefail
    case "$(uname -s)" in
        Darwin)
            security add-trusted-cert -d -r trustRoot \
                -k ~/Library/Keychains/login.keychain-db \
                certs/localhost-ec.pem
            ;;
        Linux)
            if command -v update-ca-certificates >/dev/null 2>&1; then
                sudo cp certs/localhost-ec.pem /usr/local/share/ca-certificates/localhost-ec.crt
                sudo update-ca-certificates
            elif command -v update-ca-trust >/dev/null 2>&1; then
                sudo cp certs/localhost-ec.pem /etc/pki/ca-trust/source/anchors/localhost-ec.pem
                sudo update-ca-trust
            else
                echo "Unsupported Linux: no update-ca-certificates or update-ca-trust found" >&2
                exit 1
            fi
            ;;
        *)
            echo "Unsupported OS: $(uname -s)" >&2
            exit 1
            ;;
    esac
    echo "Cert trusted. Restart your client / browser to pick it up."

untrust-certs:
    #!/usr/bin/env bash
    set -euo pipefail
    case "$(uname -s)" in
        Darwin)
            security delete-certificate -c localhost ~/Library/Keychains/login.keychain-db || true
            ;;
        Linux)
            if [ -f /usr/local/share/ca-certificates/localhost-ec.crt ]; then
                sudo rm /usr/local/share/ca-certificates/localhost-ec.crt
                sudo update-ca-certificates --fresh
            elif [ -f /etc/pki/ca-trust/source/anchors/localhost-ec.pem ]; then
                sudo rm /etc/pki/ca-trust/source/anchors/localhost-ec.pem
                sudo update-ca-trust
            fi
            ;;
    esac

cpp_build:
    cmake -S c++ -B build -G Ninja \
        -DCMAKE_MODULE_PATH={{wa_module}} \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_STANDARD=23 \
        -DCMAKE_CXX_STANDARD_REQUIRED=ON \
        {{mac_compilers}} \
    && ln -sf build/compile_commands.json ./compile_commands.json \
    && ninja -C build

cpp_client:
    ./build/client/client --port 4433 --server "::1" --profile "default"

cpp_serve:
    ./build/server/server \
        --port 4433 \
        --peer-bidi-stream-count 65000 \
        --peer-unidi-stream-count 65000 \
        --cert-file ./certs/localhost-ec.pem \
        --key-file ./certs/localhost-ec.key \
        --execution-profile "real-time" \
        --profile "default"

odin_client:
    ~/Odin/odin run odin/client \
        -target:darwin_arm64 \
        -collection:polyglot={{polyglot_odin}} \
        -collection:wanime={{warpc_odin}} \
        -extra-linker-flags:"-L/usr/local/lib -lc++ -lc++abi -lmsquic -lwanime-client-sdk -Wl,-rpath,/usr/local/lib" \
        -- --port 4433 --server "::1" --profile "default"


odin_serve cert="./certs/localhost-ec.pem" key="./certs/localhost-ec.key" profile="real-time" *args="":
    ~/Odin/odin run odin/server \
    -target:darwin_arm64 \
    -collection:wanime={{warpc_odin}} \
    -collection:polyglot={{polyglot_odin}} \
    -extra-linker-flags:"-L/usr/local/lib -lc++ -lc++abi -lmsquic -lwanime-server-sdk -Wl,-rpath,/usr/local/lib" \
    -- --port 4433 --peer-bidi-stream-count 65000 \
    --peer-unidi-stream-count 65000 \
    --cert-file {{cert}} \
    --key-file {{key}} \
    --ipv 6 \
    --execution-profile "{{profile}}" \
    --profile "default" {{args}}

rust_client:
    cargo run --bin client 

rust_serve:
    cargo run --bin server

go_client:
    SDKROOT=$(xcrun --show-sdk-path) \
    CC=$(xcrun -f clang) \
    CXX=$(xcrun -f clang++) \
    go -C go run ./client

go_serve:
    SDKROOT=$(xcrun --show-sdk-path) \
    CC=$(xcrun -f clang) \
    CXX=$(xcrun -f clang++) \
    go -C go run ./server

wt_run:
    cd ./webtransport/ && deno run dev
