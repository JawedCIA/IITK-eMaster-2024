@echo off
echo ----------------------
echo Name: Mohammed,Jawed
echo RollNumber: 233560019
echo Module: CN 1
echo Home Work Assignment 3
echo Date: 27 Feb 2024
echo ----------------------
REM Check if Python is installed
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Python is not installed. Installing...
    REM Download and install Python (adjust the download link and installation path as needed)
    start /wait "" https://www.python.org/ftp/python/3.10.2/python-3.10.2-amd64.exe /passive InstallAllUsers=1 PrependPath=1
)

REM Check if colorama is installed
python -c "import colorama" >nul 2>&1
if %errorlevel% neq 0 (
    REM Install colorama using pip
    echo Installing colorama...
    python -m pip install colorama
)

REM Run Python script
echo Running HW3 Q1 Python script...
python HW3_1.py

REM Pause to see the output (optional)
pause
