@echo off

call C:/emsdk/emsdk_env.bat
call emcmake cmake -B build/web
call cmake --build build/web