#!/bin/sh
# SOLUTION ULTIME : FORCE 6/7 + DISABLE VBUS CHECK
# On utilise PICO_BOARD=pico pour éviter les surcouches Waveshare
# On force -1 sur VBUS pour que le driver démarre sans attendre

cmake -G "Unix Makefiles" \
  -DFAMILY=rp2040 \
  -DPICO_BOARD=pico \
  -DPICO_USB_HOST_DP_PIN=6 \
  -DPICO_USB_HOST_DM_PIN=7 \
  -DPIO_USB_DP_PIN=6 \
  -DPIO_USB_VBUS_PIN=-1 \
  -DCONFIG_USB=1 \
  -B build
