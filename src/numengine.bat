@echo off

SET SCRIPT_DIR=%~dp0
SET PYTHON=%SCRIPT_DIR%\..\src\venv\Scripts\python.exe
SET MAIN=%SCRIPT_DIR%\..\src\main.py

"%PYTHON%" "%MAIN%"
