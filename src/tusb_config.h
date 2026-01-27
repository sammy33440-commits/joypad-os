#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#include "tusb_option.h"

#ifdef __cplusplus
 extern "C" {
#endif

// Configuration de base RP2040
#define CFG_TUSB_MCU                OPT_MCU_RP2040
#define CFG_TUSB_OS                 OPT_OS_NONE
#define CFG_TUSB_DEBUG              0

// CONFIGURATION DES PORTS (6/7 pour PiZero)
#define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE
#define CFG_TUSB_RHPORT1_MODE       (OPT_MODE_HOST | OPT_MODE_FULL_SPEED)
#define CFG_TUH_RPI_PIO_USB         1

#define PICO_USB_HOST_DP_PIN        6
#define PICO_USB_HOST_DM_PIN        7

// CONFIGURATION HOST (MANETTE)
#define CFG_TUH_ENABLED             1
#define CFG_TUH_HUB                 1
#define CFG_TUH_HID                 4
#define CFG_TUH_XINPUT              4
#define CFG_TUH_DEVICE_MAX          (CFG_TUH_HUB ? 5 : 1)
#define CFG_TUH_ENUMERATION_BUFSIZE 256

// CONFIGURATION DEVICE (CONSOLE)
#define CFG_TUD_ENABLED             1
#define CFG_TUD_MAX_SPEED           OPT_MODE_FULL_SPEED
#define CFG_TUD_ENDPOINT0_SIZE      64
#define CFG_TUD_HID                 1
#define CFG_TUD_CDC                 1
#define CFG_TUD_XINPUT              1

#ifdef __cplusplus
 }
#endif
#endif
