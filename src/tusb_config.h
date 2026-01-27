/*
 * CONFIGURATION WAVESHARE RP2040-PIZERO - PIN 10/11 FORCE
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

// --- FORÇAGE ABSOLU ---
// On efface tout doute
#undef PICO_USB_HOST_DP_PIN
#undef PICO_USB_HOST_DM_PIN

// On impose GPIO 10 et 11
#define PICO_USB_HOST_DP_PIN 10
#define PICO_USB_HOST_DM_PIN 11
// ----------------------

#ifndef CFG_TUSB_MCU
  #error CFG_TUSB_MCU must be defined
#endif

// USB role configuration
#if defined(DISABLE_USB_HOST)
  #define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE
#elif defined(CONFIG_USB)
  #define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE
  #define CFG_TUSB_RHPORT1_MODE       OPT_MODE_HOST
  #define CFG_TUH_RPI_PIO_USB         1
  
  // ICI IL Y AVAIT L'ERREUR (Le 6). JE L'AI SUPPRIMÉ.
  // On confirme juste que c'est bien 10 pour être parano :
  #undef PICO_USB_HOST_DP_PIN
  #define PICO_USB_HOST_DP_PIN        10
#else
  #define CFG_TUSB_RHPORT0_MODE       OPT_MODE_HOST
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS                  OPT_OS_NONE
#endif

#undef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG           1

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

#if defined(CONFIG_USB) || defined(DISABLE_USB_HOST)
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
#endif

#ifdef __cplusplus
 }
#endif

#endif
