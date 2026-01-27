#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// On laisse le système inclure les fichiers lui-même
#define ENABLE_USB_HOST
#define ENABLE_USB_DEVICE

#define APP_INPUT_INTERFACES  &input_usb
#define APP_OUTPUT_INTERFACES &output_usb

#define APP_POLL_INTERVAL_MS 1

#endif
