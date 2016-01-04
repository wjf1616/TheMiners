@setlocal ENABLEDELAYEDEXPANSION
@if exist so.txt del so.txt
@echo ============Code By 熊宇================
@echo ============有问题请提出================
@echo --------------开始生成------------------
@pause
@for /f "delims=" %%i in ('dir /b /a-d /s *.cpp') do @(
@set buffer=%%i
@set buffer=!buffer:^\=^/!
@echo !buffer!^\>> so.txt
)
@echo ---------------生成结束-----------------
@pause