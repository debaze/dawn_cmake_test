@echo off

cmake -B build/desktop
cmake --build build/desktop

call "build/desktop/Debug/app.exe"