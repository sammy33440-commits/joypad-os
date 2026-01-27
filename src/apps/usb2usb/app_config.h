#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// --- CONFIGURATION DES PORTS USB ---
#define ENABLE_USB_HOST
#define ENABLE_USB_DEVICE

// On déclare les interfaces sans include pour éviter les erreurs de chemin
struct input_interface;
struct output_interface;
extern struct input_interface input_usb;
extern struct output_interface output_usb;

#define APP_INPUT_INTERFACES  &input_usb
#define APP_OUTPUT_INTERFACES &output_usb
#define APP_POLL_INTERVAL_MS 1

// --- CONFIGURATION DES LEDS (ORIGINALE) ---
#define LED_P1_R 0
#define LED_P1_G 40
#define LED_P1_B 40
#define LED_P1_PATTERN 0b00100

#define LED_P2_R 0
#define LED_P2_G 0
#define LED_P2_B 64
#define LED_P2_PATTERN 0b01010

#define LED_P3_R 64
#define LED_P3_G 0
#define LED_P3_B 0
#define LED_P3_PATTERN 0b10101

#define LED_P4_R 0
#define LED_P4_G 64
#define LED_P4_B 0
#define LED_P4_PATTERN 0b11011

#define LED_P5_R 64
#define LED_P5_G 64
#define LED_P5_B 0
#define LED_P5_PATTERN 0b11111

#define LED_DEFAULT_R 32
#define LED_DEFAULT_G 32
#define LED_DEFAULT_B 32
#define LED_DEFAULT_PATTERN 0

#define NEOPIXEL_PATTERN_0 pattern_blues
#define NEOPIXEL_PATTERN_1 pattern_blue
#define NEOPIXEL_PATTERN_2 pattern_br
#define NEOPIXEL_PATTERN_3 pattern_brg
#define NEOPIXEL_PATTERN_4 pattern_brgp
#define NEOPIXEL_PATTERN_5 pattern_brgpy

#endif
