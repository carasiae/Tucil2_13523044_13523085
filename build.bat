@echo off
setlocal

rem Set variables
set "CC=gcc"
set "SOURCE_FOLDER=src"
set "OUTPUT_FOLDER=bin"
set "FLAG=-O"

rem Check for argument
if "%1"=="" (
    echo Usage: build.bat [build^|clean^|run^|all^|dep]
    goto end
)

rem Dispatch commands
if "%1"=="build" goto build
if "%1"=="clean" goto clean
if "%1"=="run" goto run
if "%1"=="all" goto all
if "%1"=="dep" goto dep

echo Unknown command: %1
goto end

:build
if not exist "%OUTPUT_FOLDER%" mkdir "%OUTPUT_FOLDER%"
%CC% %FLAG% %SOURCE_FOLDER%\*.c -o %OUTPUT_FOLDER%\app.exe -lm
goto end

:clean
del /f /q %OUTPUT_FOLDER%\app.exe 2>nul
goto end

:run
%OUTPUT_FOLDER%\app.exe
goto end

:all
call "%~f0" clean
call "%~f0" build
call "%~f0" run
goto end

:dep
echo Downloading dependencies...
curl -L https://github.com/nothings/stb/blob/master/stb_image.h?raw=true -o ./src/stb_image.h
curl -L https://github.com/nothings/stb/blob/master/stb_image_write.h?raw=true -o ./src/stb_image_write.h
curl -L https://github.com/charlietangora/gif-h/blob/master/gif.h?raw=true -o ./src/gif.h
goto end

:end
endlocal
