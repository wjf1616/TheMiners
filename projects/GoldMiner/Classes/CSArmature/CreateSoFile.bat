@setlocal ENABLEDELAYEDEXPANSION
@if exist so.txt del so.txt
@echo ============Code By ����================
@echo ============�����������================
@echo --------------��ʼ����------------------
@pause
@for /f "delims=" %%i in ('dir /b /a-d /s *.cpp') do @(
@set buffer=%%i
@set buffer=!buffer:^\=^/!
@echo !buffer!^\>> so.txt
)
@echo ---------------���ɽ���-----------------
@pause