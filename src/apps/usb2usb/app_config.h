#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// Active le mode USB vers USB
#define ENABLE_USB_HOST
#define ENABLE_USB_DEVICE

// On ne met PAS d'include ici, Joypad-OS les gère ailleurs
#define APP_INPUT_INTERFACES  &input_usb
#define APP_OUTPUT_INTERFACES &output_usb

#define APP_POLL_INTERVAL_MS 1

#endif
