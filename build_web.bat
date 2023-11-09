@echo off

call C:/emsdk/emsdk_env.bat
call emcmake cmake -B build/web
cmake --build build/web

call "./build/desktop/Debug/app.exe"