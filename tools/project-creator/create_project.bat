@echo off  
set /p projectName=请输入项目名称：  
if "%projectName%"=="" goto inputError1  
set /p packageName=请输入包标示名：  
if "%packageName%"=="" goto inputError2  
set /p language=请输入语言：  
if "%language%"=="" goto inputError3  
create_project.py -project %projectName% -package %packageName% -language %language%  
pause  
exit  
:inputError1  
@echo 项目名称不能为空！  
:inputError2  
@echo 包标示名不能为空！  
:inputError3  
@echo 选择语言不能为空！  
pause  
