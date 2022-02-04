# Minimal C# WebAssembly WebGL Example
a minimal example of C# wasm WebGL app based on [dotnet/runtimelab/NativeAOT-LLVM WebAssembly](https://github.com/dotnet/runtimelab/blob/feature/NativeAOT-LLVM/docs/using-nativeaot/compiling.md#webassembly)

This example is ported from [emscripten\tests\minimal_webgl](https://github.com/emscripten-core/emscripten/tree/main/tests/minimal_webgl).

## Live demo
https://zwcloud.github.io/MinimalCSharpWasmWebGL-NativeAOT-LLVM/

## Build
```
dotnet publish -r browser-wasm -c Debug /p:TargetArchitecture=wasm --self-contained /p:PlatformTarget=AnyCPU /p:MSBuildEnableWorkloadResolver=false /p:EmccExtraArgs='WebGL.c main.c --js-library library_js.js -s USE_WEBGL2=1 -lGL'
```

Note `WebGL.c` and `main.c` is passed as a `EmccExtraArgs` parameter to `emcc`.

## Run

In browser:  
Host a web-site under `.\bin\Debug\net6.0\browser-wasm\native\`. Open the html page, for example http:\127.0.0.1:81\wasm.html, in the browser.

## Result

![](/result.png)
