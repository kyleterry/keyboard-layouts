# vim: ft=dockerfile
FROM alpine:latest
ARG QMK_VERSION=0.6.210
WORKDIR /build
RUN apk --no-cache add bash wget build-base gcc-avr avr-libc
RUN wget -O /tmp/qmk_$QMK_VERSION.tar.gz https://github.com/qmk/qmk_firmware/archive/$QMK_VERSION.tar.gz && \
    tar zxvf /tmp/qmk_$QMK_VERSION.tar.gz -C /build --strip-components=1
