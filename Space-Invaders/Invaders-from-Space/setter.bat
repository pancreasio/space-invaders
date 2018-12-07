@echo off

set target=%1
set solution=%2

mkdir "%target%res"
mkdir "%target%res\assets"
xcopy "%solution%res\assets" "%target%res\assets" /E /Y /S