# ─────────────────────────────
# 1. Base image (small, secure)
# ─────────────────────────────
FROM arm64v8/ubuntu:22.04

# ─────────────────────────────
# 2. Metadata (optional but good practice)
# ─────────────────────────────
LABEL maintainer="Soulaimane Oulad Belayachi <soulaimane.ouladbelayachi@gmail.com>"

# ─────────────────────────────
# 3. Environment variables
#    - Avoid hardcoding secrets
#    - Configure app via env vars
# ─────────────────────────────
ENV DEBIAN_FRONTEND=noninteractive

# ─────────────────────────────
# 4. System dependencies
# ─────────────────────────────
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    git \
    make \
    python3 \
    python3-pip \
    udev \
    libusb-1.0-0-dev \
    sudo \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    gdb-multiarch \
    ruby \
    ruby-dev \
    cppcheck \
    clang-tools \
    flawfinder \
    software-properties-common \
    curl \
    --fix-missing \
    && \
    rm -rf /var/lib/apt/lists/*

# Verify Python installation and install Python packages
RUN python3 --version && \
    python3 -m pip --version && \
    python3 -m pip install --upgrade pip
    
# Install Python packages for embedded development
RUN python3 -m pip install \
        pyocd \
        pylink-square    

# Install PyOCD STM32F429 pack (may fail if PyOCD installation failed)
RUN pyocd pack --install stm32f429 || echo "Warning: Failed to install STM32F429 pack"

# Install Ceedling for unit testing
RUN gem install ceedling

WORKDIR /stm32f429_ci

# Default command
CMD ["/bin/bash"]

