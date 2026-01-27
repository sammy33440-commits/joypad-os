/*
 * CONFIGURATION FORCE BRUTE - WAVESHARE PIZERO (RP2040)
 * REPLIQUE DE LA CONFIGURATION GP2040-CE (PINS 28/29)
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

// ===================================================================
// 🚨 ACTIVATION OBLIGATOIRE (NO WIRES) 🚨
// On force le driver PIO-USB à démarrer sur les pins 28 et 29
// On le place EN DEHORS de tout bloc #if pour être sûr qu'il est lu.
// ===================================================================

// 1. On active le driver logiciel USB (PIO)
#define CFG_TUH_RPI_PIO_USB         1

// 2. On définit les pins physiques (Ceux qui marchent sur GP2040)
#undef PICO_USB_HOST_DP_PIN
#undef PICO_USB_HOST_DM_PIN
#define PICO_USB_HOST_DP_PIN        28
#define PICO_USB_HOST_DM_PIN        29

// 3. On force le mode "Dual" (PC sur port droit, Manette sur port gauche)
#define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE
#define CFG_TUSB_RHPORT1_MODE       OPT_MODE_HOST

// ===================================================================

#ifndef CFG_TUSB_MCU
  #error CFG_TUSB_MCU must be defined
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS                  OPT_OS_NONE
#endif

#undef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG           1

// Mémoire et Buffers (Standard)
#ifndef CFG_TUD_MEM_SECTION
#define CFG_TUD_MEM_SECTION
#endif
#ifndef CFG_TUD_MEM_ALIGN
#define CFG_TUD_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif
#define CFG_TUH_ENUMERATION_BUFSIZE 1280
#ifndef CFG_TUH_MEM_SECTION
#define CFG_TUH_MEM_SECTION
#endif
#ifndef CFG_TUH_MEM_ALIGN
#define CFG_TUH_MEM_ALIGN        __attribute__ ((aligned(4)))
#endif

#define CFG_TUH_HUB                 1
#define CFG_TUH_CDC                 0
#define CFG_TUH_HID                 8
#define CFG_TUH_MSC                 0
#define CFG_TUH_VENDOR              0
#define CFG_TUH_XINPUT              4
#ifdef ENABLE_BTSTACK
#define CFG_TUH_BTD                 1
#else
#define CFG_TUH_BTD                 0
#endif
#define CFG_TUH_DEVICE_MAX          (4*CFG_TUH_HUB + 1)
#define CFG_TUH_API_EDPT_XFER       1
#define CFG_TUH_HID_EPIN_BUFSIZE    64
#define CFG_TUH_HID_EPOUT_BUFSIZE   64

// Buffers Device (PC)
#define CFG_TUD_ENDPOINT0_SIZE    64
#define CFG_TUD_HID               4
#define CFG_TUD_XID               1
#define CFG_TUD_XID_EP_BUFSIZE    32
#define CFG_TUD_XINPUT            1
#define CFG_TUD_XINPUT_EP_BUFSIZE 32
#define CFG_TUD_GC_ADAPTER        1
#define CFG_TUD_GC_ADAPTER_EP_BUFSIZE 37
#ifndef USBR_CDC_DEBUG
#define USBR_CDC_DEBUG            1
#endif
#define CFG_TUD_CDC               (1 + USBR_CDC_DEBUG)
#define CFG_TUD_MSC               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_VENDOR            0
#define CFG_TUD_HID_EP_BUFSIZE    64
#define CFG_TUD_CDC_RX_BUFSIZE    256
#define CFG_TUD_CDC_TX_BUFSIZE    1024
#define CFG_TUD_CDC_EP_BUFSIZE    64

#ifdef __cplusplus
 }
#endif

#endif
