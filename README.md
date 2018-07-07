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

`make keyboard/layout`

Resulting firmware will be in `./out/keyboard-layout.hex`.
