if (!(Test-Path "out")) { New-Item -ItemType Directory -Path "out" }

zig c++ src/main.cpp -o out/app.exe; out\app.exe
