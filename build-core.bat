@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_BASE_PATH=%BAT_BASE_PATH%
set BIN_PATH=%PRJ_BASE_PATH%\bin
set PRJ_PATH=%PRJ_BASE_PATH%\core

MD "%BIN_PATH%"
clang -I"%PRJ_PATH%\include" -o "%BIN_PATH%\core.lib" "%PRJ_PATH%\src\*.c" -fuse-ld=llvm-lib