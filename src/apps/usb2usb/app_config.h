#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// Active le pont USB
#define ENABLE_USB_HOST
#define ENABLE_USB_DEVICE

// Définit les interfaces de routage (nécessaire pour router.c)
#define APP_INPUT_INTERFACES  &input_usb
#define APP_OUTPUT_INTERFACES &output_usb

#define APP_POLL_INTERVAL_MS 1

#endif
