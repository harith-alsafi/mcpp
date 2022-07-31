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
                    gcc-8 \
                    g++-8 \
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

RUN cd /home/mcpp && \
    cd build && \
    cmake .. -DNO-TEST=False && \
    make && \
    make install 



