# WebGPU (Dawn) test repository

### Setup

```sh
git clone --recurse-submodules git@github.com:matteokeole/dawn_cmake_test.git
```

### Building

- [Desktop build script](https://github.com/matteokeole/dawn_cmake_test/blob/main/build_desktop.bat)
- [Web build script](https://github.com/matteokeole/dawn_cmake_test/blob/main/build_web.bat)

### Dawn version note

This test uses the [`chromium/5895`](https://dawn.googlesource.com/dawn/+/refs/heads/chromium/5895) branch of the [Dawn](https://dawn.googlesource.com/dawn/) repository. I couldn't build with CMake on the 5896 and the 5932 had over 17Gb of data.