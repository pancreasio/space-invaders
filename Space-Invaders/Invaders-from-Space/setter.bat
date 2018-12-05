@echo off

set target=%1
set solution=%2

mkdir "%target%res"
xcopy "%solution%res" "%target%res" /E /Y /S