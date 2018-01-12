﻿# module Repository!

[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/sunriax) [![Build Status](https://travis-ci.org/sunriax/module.svg?branch=master)](https://travis-ci.org/sunriax/module) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Slack: Join](https://img.shields.io/badge/Slack-Join-blue.svg)](https://join.slack.com/t/sunriax-technology/shared_invite/enQtMjg3OTE2MjIyMTE2LTU1MmEwNmY5Y2Y3MTNjNzFhYzE5NTFkYWY4NzE0YmQzNzA5NjBkMWQ3ODkyNDI1NjJmMGIwYzMwOGI5ZjA2MDg)

## Description

The module repository is a set of library's used for different microchips and or semiconductors. It uses the [STK500](https://github.com/sunriax/STK500) library set which abstracts the hardware from the software. The module repository can easily be ported to other hardware abstraction libraries. It is only necessary that the functions at the ground are the same like they are in the [STK500](https://github.com/sunriax/STK500) repository libraries.

1. Supported Controller
   * STK500 (Atmel ATmega8/16/32)Atmel
   * Linux (Arietta G25/Raspberry PI)
1. Development Hardware
   * STK500 ([Atmel](http://www.microchip.com/webdoc/stk500/index.html))
   * Megacard ([HTL-Rankweil](http://www.htl-rankweil.at/))
   * Arietta G25 ([ACME](http://www.acmesystems.it/))
   * Raspberry PI ([rPI](https://www.raspberrypi.org/))
1. Additional Hardware
   * MAX7219 ([HD44780](https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf))
   * TWI EEPROM
   * 
1. Development Software
   * Atmel Studio (uC C/C++)
   * Eclipse IDE (C/C++)

## Abstraction

![Graphical Description](https://raw.githubusercontent.com/sunriax/manual/master/docs/image/STK500_abstraction.png "Graphical Description")

## Getting Started

Every project has a demo application as side car (e.g. MAX7219 has MAX7219demo). This demo can be used as quick start guide. We also try to keep our [WIKI](https://wiki.sunriax.at) up-to-date. Also there is a short description at the libraries folder:

* [MAX7219](./MAX7219/MAX7219.md)
* [AT24C02](./AT24C02/AT24C02.md)

## Important Notice

This files are valid for all repositories at the SUNriaX Github!
* [Readme](https://github.com/sunriax/manual/blob/master/README.md)
* [License](https://github.com/sunriax/manual/blob/master/LICENSE.md)
* [Warranty](https://github.com/sunriax/manual/blob/master/WARRANTY.md)

## Additional Information

You can find more additional information in the [manual](https://github.com/sunriax/manual/tree/master/docs) repository and/or visit the [SUNriaX Project Wikipedia](https://wiki.sunriax.at/) for further information (currently under construction).

If there are any further questions feel free to start an issue or contact us, we try to react as quick as possible.

---
**R. GÄCHTER, Rankweil JAN/2018**