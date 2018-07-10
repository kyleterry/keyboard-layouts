# Keyboard layouts

These are my various keyboard layouts. They are being kept here so I don't have
to make a pull request to the QMK upstream project everytime I want to make a
change.

## How it works

Layouts are structured under `keyboards/<board name>/<layout name>`. When you
want to build a board, `make` will pull down the qmk build image from docker
hub, mount `keyboards/<board name>/<layout name>` under a unique namespace in
the container and then runs QMK's `make` target like normal.

## Usage

`make keyboards/keyboard/layout`

Resulting firmware will be in `./out/keyboard-layout.hex`.

### Flashing

Flash the resulting firmware with dfu-programmer:

```
$ sudo dfu-programmer atmega32u4 erase
$ sudo dfu-programmer atmega32u4 flash out/dz60-default.hex
$ sudo dfu-programmer atmega32u4 reset
```

## Useful stuff

The proper udev rules need to be added in order to access the MCU and flash the
chip on your microcontroller: https://github.com/qmk/qmk_firmware/blob/master/docs/faq_build.md#linux-udev-rules
