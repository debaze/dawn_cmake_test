# Cross-platform WebGPU with Dawn and Emscripten

## Setup

```sh
git clone git@github.com:matteokeole/dawn_cmake_test.git
cd dawn_cmake_test
git submodule update --init
```

Make sure you have [Cmake](https://cmake.org/download) and [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) installed, as well as a C/C++ compiler.

## Project structure

```sh
├─ 📂 build
├─ 📂 src
│  └─ 📄 main.cpp
├─ 📂 vendor
│  └─ 📁 dawn
├─ 📂 web
│  ├─ 📁 assets
│  │  ├─ 📁 css
│  │  │  └─ 📄 main.css
│  │  └─ 📁 js
│  │     └─ 📄 main.js
│  └─ 📄 index.html
├─ 📄 .gitignore
├─ 📄 .gitmodules
├─ 📄 build_desktop.bat
├─ 📄 build_web.bat
├─ 📄 CMakeLists.txt
├─ 📄 LICENSE
└─ 📃 README.md
```

## Building & running

### Desktop

Build the app with the [desktop script](https://github.com/matteokeole/dawn_cmake_test/blob/main/build_desktop.bat). Then, run `build/desktop/Debug/app.exe`.

### Web

Build the app with the [web build script](https://github.com/matteokeole/dawn_cmake_test/blob/main/build_web.bat). Then, start a local web server and open [web/index.html](https://github.com/matteokeole/dawn_cmake_test/blob/main/web/index.html).
