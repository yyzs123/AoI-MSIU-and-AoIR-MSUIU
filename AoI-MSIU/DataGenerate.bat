@echo off
g++ DataGenerate.cpp Content.cpp -o DataGenerate -std=c++11

start /b DataGenerate 40 40 50
start /b DataGenerate 80 80 50
