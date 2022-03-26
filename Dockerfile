# vim: ft=dockerfile
FROM python:latest
ARG QMK_VERSION=0.16.0
ARG QMK_REPO_URL=https://github.com/qmk/qmk_firmware
ENV QMK_HOME=/qmk_firmware
WORKDIR /qmk_firmware
RUN apt-get update \
 && apt-get -yq install \
    bash git build-essential clang-format diffutils gcc git unzip wget zip \
    python3-pip binutils-avr gcc-avr avr-libc binutils-arm-none-eabi \
    gcc-arm-none-eabi libnewlib-arm-none-eabi avrdude dfu-programmer \
    dfu-util teensy-loader-cli libhidapi-hidraw0 libusb-dev \
 && git clone --branch $QMK_VERSION --depth 1 $QMK_REPO_URL . \
 && make git-submodule \
 && python3 -m pip install -r requirements.txt \
 && python3 -m pip install qmk \
 && mkdir .build \
 && touch quantum/version.h \
 && chmod -R 0777 .
