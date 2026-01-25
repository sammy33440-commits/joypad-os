#!/bin/sh
cmake -G "Unix Makefiles" -DFAMILY=rp2350 -DPICO_BOARD=waveshare_rp2350_usb_a -DPICO_USB_HOST_DP_PIN=28 -DPICO_USB_HOST_DM_PIN=29 -DPICO_DEFAULT_LED_PIN=-1 -B build
