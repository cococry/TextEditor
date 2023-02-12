@echo off
SetLocal EnableDelayedExpansion

pushd ..\src
set sourceFiles=
for /R %%f in (*.c) do (
    set sourceFiles=!sourceFiles! %%f
)
popd

cd ..\
set includeDirs= -Ivendor/ezglfw/include -Ivendor/ezglad/include -Ivendor/stb_image
set vendorFiles=vendor/ezglad/src/glad.c vendor/stb_image/stb_image.c
set linkerDirs=-Lvendor/ezglfw/lib 
set libraryFiles=-lglfw3_mt -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lopengl32 -llibucrt
set compilerFlags=-g -Wall -Wvarargs -o bin/editor.exe
set preDefinedMacros=-D_CRT_SECURE_NO_WARNINGS -DGLFW_INCLUDE_NONE 
echo Starting editor build process...
clang %sourceFiles% %vendorFiles% %includeDirs% %linkerDirs% %libraryFiles% %compilerFlags% %preDefinedMacros%
IF %ERRORLEVEL% NEQ 0 (
  echo Failed to build editor - error code: %ERRORLEVEL%
)