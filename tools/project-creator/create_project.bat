@echo off  
set /p projectName=��������Ŀ���ƣ�  
if "%projectName%"=="" goto inputError1  
set /p packageName=���������ʾ����  
if "%packageName%"=="" goto inputError2  
set /p language=���������ԣ�  
if "%language%"=="" goto inputError3  
create_project.py -project %projectName% -package %packageName% -language %language%  
pause  
exit  
:inputError1  
@echo ��Ŀ���Ʋ���Ϊ�գ�  
:inputError2  
@echo ����ʾ������Ϊ�գ�  
:inputError3  
@echo ѡ�����Բ���Ϊ�գ�  
pause  
