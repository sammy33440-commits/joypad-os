#ifndef APP_USB2USB_H
#define APP_USB2USB_H

// ============================================================================
// APP METADATA
// ============================================================================
#ifndef APP_NAME
#define APP_NAME "usb2usb"
#endif
#define APP_DESCRIPTION "USB to USB HID gamepad adapter"
#define APP_AUTHOR "RobertDaleSmith"

// ============================================================================
// CORE DEPENDENCIES
// ============================================================================

// Indispensable pour activer le deuxième cœur (Core 1) pour le PIO-USB
#define REQUIRE_USB_HOST 1
#define MAX_USB_DEVICES 4

// Indispensable pour le port de droite (Native USB)
#define REQUIRE_USB_DEVICE 1
#define USB_OUTPUT_PORTS 1

// Services
#define REQUIRE_FLASH_SETTINGS 0
#define REQUIRE_PROFILE_SYSTEM 0
#define REQUIRE_PLAYER_MANAGEMENT 1

// ============================================================================
// ROUTING CONFIGURATION
// ============================================================================
#define ROUTING_MODE ROUTING_MODE_MERGE
#define MERGE_MODE MERGE_BLEND
#define APP_MAX_ROUTES 4
#define TRANSFORM_FLAGS TRANSFORM_MOUSE_TO_ANALOG

// ============================================================================
// PLAYER MANAGEMENT
// ============================================================================
#define PLAYER_SLOT_MODE PLAYER_SLOT_FIXED
#define MAX_PLAYER_SLOTS 4
#define AUTO_ASSIGN_ON_PRESS 1

// ============================================================================
// HARDWARE CONFIGURATION (MODIFICATIONS ICI)
// ============================================================================

// 1. CHANGE LA CARTE : "ada_feather_usbhost" n'a pas les mêmes pins que toi.
#define BOARD "waveshare_rp2040_zero"

// 2. FORCE L'OVERCLOCK : Le PIO-USB (port de gauche) est instable à 125MHz. 
// Il faut impérativement 120MHz (120000) ou 240MHz (240000).
#define CPU_OVERCLOCK_KHZ 120000

#define UART_DEBUG 1

// ============================================================================
// APP FEATURES
// ============================================================================
#define FEATURE_PROFILES 0
#define FEATURE_OUTPUT_MODE_SELECT 0

void app_init(void);
void app_task(void);

#endif // APP_USB2USB_H
