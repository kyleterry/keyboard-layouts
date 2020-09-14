# vim: ft=dockerfile
FROM python:alpine
ARG QMK_VERSION=0.10.9
ENV QMK_HOME=/qmk
WORKDIR /qmk
RUN apk --no-cache add bash wget git build-base gcc-avr avr-libc \
 && python3 -m pip install qmk \
 && git clone --branch $QMK_VERSION --depth 1 https://github.com/qmk/qmk_firmware . \
 && make git-submodule \
 && mkdir .build \
 && touch quantum/version.h \
 && chmod -R 0777 .
