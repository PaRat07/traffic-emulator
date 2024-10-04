FROM ubuntu:18.04
RUN apt-get update && apt-get install -y sudo build-essential git cmake curl unzip tar
WORKDIR /home
RUN git clone https://github.com/Microsoft/vcpkg.git
WORKDIR /home/vcpkg
RUN ./bootstrap-vcpkg.sh