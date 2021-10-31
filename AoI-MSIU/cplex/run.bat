@echo off
g++ transform.cpp -o transform -std=c++11
set n=40
for /l %%m in (5, 5, 40) do (
    transform %%m %n% 50
    python optimal.py --ns=%%m --cs=%n% --alpha=0.5 --ca=50
    python optimal.py --ns=%%m --cs=%n% --alpha=1.0 --ca=50
    python optimal.py --ns=%%m --cs=%n% --alpha=1.5 --ca=50
    python optimal.py --ns=%%m --cs=%n% --alpha=2.0 --ca=50
)
set m=80
for /l %%n in (10, 10, 80) do (
    transform %m% %%n 50
    python optimal.py --ns=%m% --cs=%%n --alpha=0.5 --ca=50
    python optimal.py --ns=%m% --cs=%%n --alpha=1.0 --ca=50
    python optimal.py --ns=%m% --cs=%%n --alpha=1.5 --ca=50
    python optimal.py --ns=%m% --cs=%%n --alpha=2.0 --ca=50
)