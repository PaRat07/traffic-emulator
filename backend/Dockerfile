FROM ghcr.io/userver-framework/ubuntu-22.04-userver-pg:latest
RUN apt update
RUN apt upgrade -y
RUN apt install -y build-essential cmake tar wget curl zip git pkg-config ninja-build
RUN apt install -y gdb mold
WORKDIR /app
COPY . .
RUN cmake . -G Ninja
RUN cmake --build .