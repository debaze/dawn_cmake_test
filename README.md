# Cross-platform WebGPU with Dawn and Emscripten

### Setup

```sh
git clone --recurse-submodules git@github.com:matteokeole/dawn_cmake_test.git
```

Make sure you have [Cmake](https://cmake.org/download) and [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) installed, as well as a C/C++ compiler.

### Building & running

#### Desktop

Build the app with the [desktop script](https://github.com/matteokeole/dawn_cmake_test/blob/main/build_desktop.bat). Then, run `build/desktop/Debug/app.exe`.

#### Web

Build the app with the [web build script](https://github.com/matteokeole/dawn_cmake_test/blob/main/build_web.bat). Then, start a local web server and open [web/index.html](https://github.com/matteokeole/dawn_cmake_test/blob/main/web/index.html).

> #### Dawn version note
> 
> This test uses the [`chromium/5895`](https://dawn.googlesource.com/dawn/+/refs/heads/chromium/5895) branch of the [Dawn repository](https://dawn.googlesource.com/dawn/). The CMake build was failing on the 5896 and the 5932 was too heavy.