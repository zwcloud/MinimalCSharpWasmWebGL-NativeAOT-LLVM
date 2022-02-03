# Minimal C# WebAssembly WebGL Example
a minimal example of C# wasm WebGL app based on NativeAOT-LLVM WebAssembly

This example is ported from [timhutton/opengl-canvas-wasm](https://github.com/timhutton/opengl-canvas-wasm) based on SDL2 and OpenGLES 2.0.

## Build
```
dotnet publish -r browser-wasm -c Debug /p:TargetArchitecture=wasm --self-contained /p:PlatformTarget=AnyCPU /p:MSBuildEnableWorkloadResolver=false /p:EmccExtraArgs='Test.c -s WASM=1 -s USE_SDL=2'
```

Note `Test.c` is passed as a `EmccExtraArgs` parameter to `emcc`.

## Run

In browser:  
Host a web-site under `.\bin\Debug\net6.0\browser-wasm\native\`. Open the html page, for example http:\127.0.0.1:81\wasm.html, in the browser.

## Result

![](Result.png)
