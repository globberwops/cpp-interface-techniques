FROM ubuntu:mantic

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-format \
    clang-tidy \
    clang-tools \
    clangd \
    cmake \
    cmake-format \
    cppcheck \
    cpplint \
    curl \
    git \
    iwyu \
    libclang-dev \
    libgmock-dev \
    libgtest-dev \
    lld \
    lldb \
    ninja-build \
    sudo \
    vim \
    wget \
    && rm -rf /var/lib/apt/lists/*

ARG USERNAME=ubuntu
RUN echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
USER $USERNAME
