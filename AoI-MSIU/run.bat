@echo off
g++ Zero-wait.cpp Content.cpp -o Zero-wait -std=c++11
g++ LCFS.cpp Content.cpp -o LCFS -std=c++11
g++ Periodical.cpp Content.cpp -o Periodical -std=c++11
g++ Greedy.cpp -o Greedy -std=c++11
set n=40
for /l %%m in (5, 5, 40) do (
    Zero-wait %%m %n% 50 0.5
    Zero-wait %%m %n% 50 1.0
    Zero-wait %%m %n% 50 1.5
    Zero-wait %%m %n% 50 2.0

    LCFS %%m %n% 50 0.5
    LCFS %%m %n% 50 1.0
    LCFS %%m %n% 50 1.5
    LCFS %%m %n% 50 2.0

    periodical %%m %n% 50 0.5
    periodical %%m %n% 50 1.0
    periodical %%m %n% 50 1.5
    periodical %%m %n% 50 2.0
    
    Greedy %%m %n% 50 0.5
    Greedy %%m %n% 50 1.0
    Greedy %%m %n% 50 1.5
    Greedy %%m %n% 50 2.0
    
)

set m=80
for /l %%n in (10, 10, 80) do (
    Zero-wait %m% %%n 50 0.5
    Zero-wait %m% %%n 50 1.0
    Zero-wait %m% %%n 50 1.5
    Zero-wait %m% %%n 50 2.0

    LCFS %m% %%n 50 0.5
    LCFS %m% %%n 50 1.0
    LCFS %m% %%n 50 1.5
    LCFS %m% %%n 50 2.0
    
    periodical %m% %%n 50 0.5
    periodical %m% %%n 50 1.0
    periodical %m% %%n 50 1.5
    periodical %m% %%n 50 2.0
    
    Greedy %m% %%n 50 0.5
    Greedy %m% %%n 50 1.0
    Greedy %m% %%n 50 1.5
    Greedy %m% %%n 50 2.0
)
echo finished