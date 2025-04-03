FROM ubuntu:22.04

RUN apt update

# Get Curl
RUN apt install -y curl

# Get Unzip
RUN apt install -y unzip

# Get Make
# apt install make

# Get Ninja
RUN curl -OL https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-linux.zip
RUN unzip ninja-linux.zip -d /bin

# Get CMake
RUN curl -OL https://github.com/Kitware/CMake/releases/download/v3.29.7/cmake-3.29.7-linux-x86_64.sh
RUN mv cmake-3.29.7-linux-x86_64.sh home/cmake_install.sh
RUN chmod +x home/cmake_install.sh
RUN cd home && ./cmake_install.sh --skip-license
ENV PATH="$PATH:/home/bin"

# Get git (So we can cmake fetchcontent_declare)
RUN apt install -y git

# Get Build Essentials like gcc (Change to only install gcc)
RUN apt install -y build-essential

# Get gdb to debug unit tests
RUN apt install -y gdb
