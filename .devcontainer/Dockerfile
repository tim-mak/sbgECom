FROM ubuntu:22.04

# Avoid prompts during package installation
ARG DEBIAN_FRONTEND=noninteractive

# Update and install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    make \
    gcc \
    g++ \
    gdb \
    git \
    curl \
    wget \
    pkg-config \
    zip \
    unzip \
    ca-certificates \
    --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /workspace

# Set the default shell to bash
SHELL ["/bin/bash", "-c"]