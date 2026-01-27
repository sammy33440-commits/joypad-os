#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// On ajoute les "dictionnaires" pour que le code comprenne input_usb
#include "input/usb_input.h"
#include "output/usb_output.h"

#define ENABLE_USB_HOST
#define ENABLE_USB_DEVICE

// On définit qui est l'entrée et qui est la sortie
#define APP_INPUT_INTERFACES  &input_usb
#define APP_OUTPUT_INTERFACES &output_usb

#define APP_POLL_INTERVAL_MS 1

#endif
