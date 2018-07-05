# vim: ft=dockerfile
FROM alpine:latest
WORKDIR /build
RUN apk --no-cache add bash wget build-base gcc-avr avr-libc
RUN wget -O /tmp/qmk.tar.gz https://github.com/qmk/qmk_firmware/archive/0.6.57.tar.gz && \
    tar zxvf /tmp/qmk.tar.gz -C /build --strip-components=1
