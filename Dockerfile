FROM ubuntu:22.04
ARG DEBIAN_FRONTEND=noninteractive

USER root

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y --no-install-recommends install \
        build-essential \
        git \
        python3 \
        python3-pip \
        vim \
        wget \
        can-utils \
        gdb-multiarch \
        gcc-multilib \
        g++-multilib \
        can-utils \
        openocd \
        valgrind \
        libncurses5 \
        libncurses5-dev \
        cmake \
        gdb && \
    apt-get -y clean

RUN git config --global --add safe.directory /workspace

RUN ln -s /usr/bin/python3 /usr/bin/python

RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 && \
    tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
ENV PATH="/gcc-arm-none-eabi-10.3-2021.10/bin:${PATH}"

CMD ["/bin/bash"]

WORKDIR /workspace/
