#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#include "input/usb_input.h"
#include "output/usb_output.h"

// Active le pont USB entre les deux ports
#define ENABLE_USB_HOST
#define ENABLE_USB_DEVICE

// Définit les interfaces (obligatoire pour router.c)
#define APP_INPUT_INTERFACES  &input_usb
#define APP_OUTPUT_INTERFACES &output_usb

#define APP_POLL_INTERVAL_MS 1

#endif
