FROM gcc:11.2.0

RUN sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list\
    && apt-get clean\
    && apt-get -qq update \
    && apt-get -qq install --no-install-recommends openssh-server \
    && apt-get -qq install --no-install-recommends sudo \
    && apt-get -qq install --no-install-recommends cmake \
    && apt-get -qq install --no-install-recommends rsync \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# setup ssh for use ubuntu, password scucpp
RUN useradd -rm -d /home/ubuntu -s /bin/bash -g root -G sudo -u 1000 ubuntu 
RUN  echo 'ubuntu:scucpp' | chpasswd
RUN service ssh start
EXPOSE 22

# install google test
WORKDIR /usr/src/libraries
RUN git clone --depth=1 -b main https://github.com/google/googletest.git
WORKDIR /usr/src/libraries/googletest/build
RUN cmake .. \
    && make \
    && make install
WORKDIR /

CMD ["./main"]

