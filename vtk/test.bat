@echo off 
setlocal ENABLEDELAYEDEXPANSION  
::===在这里设置你的后缀名 
set houzhui=.jpg .gif .png .swf 
::===在这里设置你要搜索的路径,这里设置为批处理所在目录 
set pwd=%~dp0 
for /R "%pwd%" %%i in (*) do ( 
::===这里是记录文件名,根据要求记录吧 
set filename=%%~nxi 
call :check %%~xi 
) 
pause 
 
:check 
for %%i in (%houzhui%) do ( 
::===判断后输出噢,根据自己喜欢输出吧 
if "%1"=="%%i" echo !filename! && echo ./find.sh !filename! >>kk.txt 
) 
goto :eof 
pause 