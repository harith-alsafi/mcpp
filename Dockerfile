FROM ubuntu:18.04

LABEL maintainer="Harith Al-Safi" \
      description="mcpp" \
      version="1.0"

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/London

RUN apt-get update -y && \
    apt-get install -y tzdata
RUN apt-get install -y \
                    git \
                    curl \
                    gcc-7 \
                    g++-7 \
                    clang-10 \
                    build-essential \
                    cmake \
                    unzip \
                    tar \
                    wget \
                    python \
                    libpthread-stubs0-dev \
                    ca-certificates && \
    apt-get autoclean && \
    apt-get autoremove && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* \
    mkdir /home/mcpp 

COPY . /home/mcpp
RUN rm -f -R /home/mcpp/build
RUN mkdir /home/mcpp/build

RUN CMAKE_URL="https://cmake.org/files/v3.19/cmake-3.19.0-Linux-x86_64.tar.gz" && \
    cd /home/mcpp && \
    mkdir cmake && wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake 

RUN gcc --version 
RUN cmake --version 
RUN g++ --version 


RUN cd /home/mcpp && \
    cd build && \
    ../cmake/bin/cmake .. -DNO-TEST=False && \
    make



