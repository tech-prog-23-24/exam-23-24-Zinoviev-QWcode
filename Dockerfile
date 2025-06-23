FROM ubuntu:18.04

LABEL author="Зиновьев Сергей 241-326"

RUN apt-get update && apt-get install -y g++

RUN mkdir -p /MyProj_241-326_Zinoviev

COPY main.cpp SessionManager.h SessionManager.cpp /MyProj_241-326_Zinoviev/

WORKDIR /MyProj_241-326_Zinoviev

RUN g++ -std=c++11 main.cpp SessionManager.cpp -o my_Program

ENV DEFAULT_TIMEOUT=10

CMD ["./my_Program", "status"]