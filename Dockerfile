
FROM ubuntu:bionic

RUN \
  apt-get update \
  && apt-get install -y software-properties-common \
  && add-apt-repository ppa:ubuntu-toolchain-r/test \
  && apt-get update \
  && apt-get install -y \
  gcc-multilib g++-multilib \
  gcc-9 g++-9 \
  python \
  python-pip \
  && pip install cmake --upgrade \
  && pip install conan

WORKDIR /usr/src/app
COPY conan/conanfile.txt conanfile.txt

RUN conan install . --build -s arch=x86 -s build_type=Release
RUN conan install . --build -s arch=x86 -s build_type=Debug
RUN conan install . --build -s arch=x86_64 -s build_type=Release
RUN conan install . --build -s arch=x86_64 -s build_type=Debug

RUN rm -r /usr/src/app/*
