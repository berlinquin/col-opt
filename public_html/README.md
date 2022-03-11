# ColOpt for Wasm

This project adapts the C++ source for the web
using WebAssembly and the emscripten toolchain.

## Building

To build the project, run `make` from this directory.

This requires the [emscripten](https://emscripten.org/index.html) toolchain
to be installed on your machine.

## Viewing

Running `make` produces the index.html file
and produces the required JavaScript and Wasm files.

To view the project, you will likely need to have a web server installed
that can serve this directory.

I use apache on my debian machine,
configured with a VirtualHost entry and an entry in /etc/hosts,
and it works well for local development.

