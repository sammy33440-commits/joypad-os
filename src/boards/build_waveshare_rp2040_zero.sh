#!/bin/sh
# ON TROMPE LE SYSTEME EN DISANT QUE C'EST UNE PICO STANDARD
# Cela force le compilateur à accepter nos Pins 6 et 7 sans discuter.

cmake -G "Unix Makefiles" \
  -DFAMILY=rp2040 \
  -DPICO_BOARD=pico \
  -DPICO_USB_HOST_DP_PIN=6 \
  -DPICO_USB_HOST_DM_PIN=7 \
  -DCONFIG_USB=1 \
  -B build
