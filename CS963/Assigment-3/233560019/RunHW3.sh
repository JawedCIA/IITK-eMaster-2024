#!/bin/bash

echo "----------------------"
echo "Name: Mohammed,Jawed"
echo "RollNumber: 233560019"
echo "Module: CN 1"
echo "Home Work Assignment 3"
echo "Date: 27 Feb 2024"
echo "----------------------"

# Check if Python is installed
if ! command -v python &> /dev/null; then
    echo "Python is not installed. Installing..."
    # Download and install Python
    wget https://www.python.org/ftp/python/3.10.2/Python-3.10.2.tgz
    tar -xzvf Python-3.10.2.tgz
    cd Python-3.10.2/
    ./configure --enable-optimizations
    make -j$(nproc)
    sudo make altinstall
    cd ..
    rm -rf Python-3.10.2*
fi

# Check if colorama is installed
if ! python -c "import colorama" &> /dev/null; then
    echo "Installing colorama..."
    # Install colorama using pip
    python -m pip install colorama
fi

# Run Python script
echo "Running HW3 Q1 Python script..."
python HW3_1.py

# Pause to see the output (optional)
read -p "Press Enter to continue..."
