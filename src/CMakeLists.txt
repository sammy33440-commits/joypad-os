cmake_minimum_required(VERSION 3.12)

# Pull in SDK from local submodule (must be before project)
set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/pico-sdk)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(joypad C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ============================================================================
# 🚨 FORÇAGE MATÉRIEL WAVESHARE PIZERO (GPIO 6/7) 🚨
# ============================================================================
add_compile_definitions(PICO_USB_HOST_DP_PIN=6)
add_compile_definitions(PICO_USB_HOST_DM_PIN=7)
add_compile_definitions(PICO_PIO_USB_CLOCK_KHZ=120000)
add_compile_definitions(CONFIG_PIO_USB_DP_PIN=6)

# Initialize the SDK
pico_sdk_init()

set(FAMILY rp2040)

# ============================================================================
# VERSION AND BUILD INFO
# ============================================================================

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../VERSION" JOYPAD_VERSION)
string(STRIP "${JOYPAD_VERSION}" JOYPAD_VERSION)

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
if(NOT GIT_COMMIT)
    set(GIT_COMMIT "unknown")
endif()

string(TIMESTAMP BUILD_TIME "%Y-%m-%d %H:%M:%S")

message(STATUS "Joypad Version: ${JOYPAD_VERSION}")
message(STATUS "Git Commit: ${GIT_COMMIT}")
message(STATUS "Build Time: ${BUILD_TIME}")

# External libraries
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/tusb_xinput xinput_host)

# Pico-PIO-USB for dual USB
set(PICO_PIO_USB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/Pico-PIO-USB)
if(EXISTS ${PICO_PIO_USB_PATH})
    add_library(tinyusb_pico_pio_usb INTERFACE)
    target_sources(tinyusb_pico_pio_usb INTERFACE
        ${PICO_PIO_USB_PATH}/src/pio_usb.c
        ${PICO_PIO_USB_PATH}/src/pio_usb_host.c
        ${PICO_PIO_USB_PATH}/src/pio_usb_device.c
        ${PICO_PIO_USB_PATH}/src/usb_crc.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/tinyusb/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
    )
    target_include_directories(tinyusb_pico_pio_usb INTERFACE ${PICO_PIO_USB_PATH}/src)
    target_link_libraries(tinyusb_pico_pio_usb INTERFACE hardware_pio hardware_dma pico_stdlib)
    
    # 🚨 Ici aussi on force le pin 6 par défaut 🚨
    target_compile_definitions(tinyusb_pico_pio_usb INTERFACE 
        PIO_USB_USE_TINYUSB=1 
        PIO_USB_DP_PIN_DEFAULT=6
    )
    
    pico_generate_pio_header(tinyusb_pico_pio_usb ${PICO_PIO_USB_PATH}/src/usb_tx.pio)
    pico_generate_pio_header(tinyusb_pico_pio_usb ${PICO_PIO_USB_PATH}/src/usb_rx.pio)
endif()

# ============================================================================
# SOURCE LISTS
# ============================================================================

set(CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/router/router.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/leds/leds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/leds/neopixel/ws2812.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/storage/storage.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/storage/flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/button/button.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/codes/codes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/hotkeys/hotkeys.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/players/manager.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/players/feedback.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/profiles/profile.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/profiles/profile_indicator.c
)

set(USB_HOST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/usbh.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/hid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/hid_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/hid_registry.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/generic/hid_keyboard.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/generic/hid_mouse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/generic/hid_parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/generic/hid_gamepad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/8bitdo/8bitdo_bta.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/8bitdo/8bitdo_m30.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/8bitdo/8bitdo_pce.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/nintendo/gamecube_adapter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/nintendo/switch_pro.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/nintendo/switch2_pro.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/sony/sony_ds3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/sony/sony_ds4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/sony/sony_ds5.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/sony/sony_psc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/hori/hori_horipad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/hori/hori_pokken.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/logitech/logitech_wingman.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/sega/sega_astrocity.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/google/google_stadia.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/hid/devices/vendors/raphnet/raphnet_pce.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/xinput/xinput.c
)

set(BTHID_DEVICE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/bthid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/bthid_registry.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/generic/bthid_gamepad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/sony/ds3_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/sony/ds4_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/sony/ds5_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/nintendo/switch_pro_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/nintendo/switch2_ble.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/nintendo/wii_u_pro_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/nintendo/wiimote_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/microsoft/xbox_bt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/microsoft/xbox_ble.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/bthid/devices/vendors/google/stadia_bt.c
)

set(BT_HOST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/btd/hci_transport_h2_tinyusb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/transport/bt_transport.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/transport/bt_transport_usb.c
    ${BTHID_DEVICE_SOURCES}
)

set(PICO_BTSTACK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk/lib/btstack)
set(BTSTACK_SOURCES
    ${PICO_BTSTACK_PATH}/src/btstack_linked_list.c
    ${PICO_BTSTACK_PATH}/src/btstack_memory.c
    ${PICO_BTSTACK_PATH}/src/btstack_memory_pool.c
    ${PICO_BTSTACK_PATH}/src/btstack_run_loop.c
    ${PICO_BTSTACK_PATH}/src/btstack_run_loop_base.c
    ${PICO_BTSTACK_PATH}/src/btstack_util.c
    ${PICO_BTSTACK_PATH}/src/btstack_tlv.c
    ${PICO_BTSTACK_PATH}/src/btstack_tlv_none.c
    ${PICO_BTSTACK_PATH}/src/btstack_crypto.c
    ${PICO_BTSTACK_PATH}/src/hci.c
    ${PICO_BTSTACK_PATH}/src/hci_cmd.c
    ${PICO_BTSTACK_PATH}/src/hci_dump.c
    ${PICO_BTSTACK_PATH}/src/hci_event.c
    ${PICO_BTSTACK_PATH}/src/hci_event_builder.c
    ${PICO_BTSTACK_PATH}/src/l2cap.c
    ${PICO_BTSTACK_PATH}/src/l2cap_signaling.c
    ${PICO_BTSTACK_PATH}/src/ad_parser.c
    ${PICO_BTSTACK_PATH}/src/ble/sm.c
    ${PICO_BTSTACK_PATH}/src/ble/att_dispatch.c
    ${PICO_BTSTACK_PATH}/src/ble/att_db.c
    ${PICO_BTSTACK_PATH}/src/ble/gatt_client.c
    ${PICO_BTSTACK_PATH}/src/ble/gatt_service_client.c
    ${PICO_BTSTACK_PATH}/src/ble/le_device_db_memory.c
    ${PICO_BTSTACK_PATH}/src/ble/le_device_db_tlv.c
    ${PICO_BTSTACK_PATH}/src/ble/gatt-service/hids_client.c
    ${PICO_BTSTACK_PATH}/src/classic/sdp_client.c
    ${PICO_BTSTACK_PATH}/src/classic/sdp_server.c
    ${PICO_BTSTACK_PATH}/src/classic/sdp_util.c
    ${PICO_BTSTACK_PATH}/src/classic/device_id_server.c
    ${PICO_BTSTACK_PATH}/src/classic/hid_host.c
    ${PICO_BTSTACK_PATH}/src/classic/btstack_link_key_db_memory.c
    ${PICO_BTSTACK_PATH}/src/classic/btstack_link_key_db_tlv.c
    ${PICO_BTSTACK_PATH}/3rd-party/micro-ecc/uECC.c
    ${PICO_BTSTACK_PATH}/3rd-party/rijndael/rijndael.c
    ${PICO_BTSTACK_PATH}/platform/embedded/btstack_run_loop_embedded.c
    ${PICO_BTSTACK_PATH}/platform/embedded/hci_dump_embedded_stdout.c
    ${PICO_BTSTACK_PATH}/platform/embedded/btstack_tlv_flash_bank.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk/src/rp2_common/pico_btstack/btstack_flash_bank.c
)

set(USB_DEVICE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/usbd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/hid_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/xinput_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/switch_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/ps3_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/psclassic_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/ps4_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/xid_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/xbone_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/xac_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/kbmouse_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/modes/gc_adapter_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/cdc/cdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/cdc/cdc_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/cdc/cdc_commands.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/drivers/tud_xid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/drivers/tud_xinput.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/drivers/tud_xbone.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/drivers/xgip_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd/kbmouse/kbmouse.c
)

set(SNES_HOST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/native/host/snes/snes_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/SNESpad/src/snespad.c
)

set(N64_HOST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/native/host/n64/n64_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/joybus-pio/src/joybus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/joybus-pio/src/N64Controller.c
)

set(GC_HOST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/native/host/gc/gc_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/joybus-pio/src/joybus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/joybus-pio/src/GamecubeController.c
)

set(CONTROLLER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pad/pad_input.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/speaker/speaker.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/services/display/display.c
    ${CMAKE_CURRENT_SOURCE_DIR}/native/device/uart/uart_device.c
    ${CMAKE_CURRENT_SOURCE_DIR}/native/host/uart/uart_host.c
)

set(COMMON_SOURCES ${CORE_SOURCES} ${USB_HOST_SOURCES})
set(COMMON_LIBRARIES pico_stdlib pico_multicore hardware_pio tinyusb_host tinyusb_board xinput_host)

set(BTSTACK_DEFINITIONS ENABLE_BTSTACK=1)

set(BTSTACK_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/btstack
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/btd
    ${PICO_BTSTACK_PATH}/src
    ${PICO_BTSTACK_PATH}/src/ble
    ${PICO_BTSTACK_PATH}/platform/embedded
    ${PICO_BTSTACK_PATH}/3rd-party/micro-ecc
    ${PICO_BTSTACK_PATH}/3rd-party/rijndael
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk/src/rp2_common/pico_btstack/include
)

set(BTSTACK_EXTRA_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/bt/btstack/btstack_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbh/btd/btstack_hal.c
)

set(CONTROLLER_LIBRARIES pico_stdlib pico_multicore hardware_pio hardware_adc hardware_i2c hardware_pwm hardware_spi tinyusb_device tinyusb_board)

# ============================================================================
# HELPER FUNCTIONS
# ============================================================================

function(joypad_target_common TARGET)
    target_compile_options(${TARGET} PRIVATE -O3)
    pico_add_extra_outputs(${TARGET})
    pico_generate_pio_header(${TARGET} ${CMAKE_CURRENT_LIST_DIR}/core/services/leds/neopixel/ws2812.pio)
    target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/common)
    target_compile_definitions(${TARGET} PRIVATE
        JOYPAD_VERSION="${JOYPAD_VERSION}"
        GIT_COMMIT="${GIT_COMMIT}"
        BUILD_TIME="${BUILD_TIME}"
        BOARD_NAME="${PICO_BOARD}"
    )
endfunction()

function(joypad_add_btstack TARGET)
    target_compile_definitions(${TARGET} PRIVATE ${BTSTACK_DEFINITIONS})
    target_sources(${TARGET} PRIVATE
        ${BT_HOST_SOURCES}
        ${BTSTACK_SOURCES}
        ${BTSTACK_EXTRA_SOURCES}
    )
    target_include_directories(${TARGET} PUBLIC ${BTSTACK_INCLUDES})
    target_link_libraries(${TARGET} PRIVATE hardware_flash pico_flash)
endfunction()

# ============================================================================
# APPS (SÉLECTIONNÉES)
# ============================================================================

# PCEngine
add_executable(joypad_pce)
target_compile_definitions(joypad_pce PRIVATE CONFIG_PCE=1)
target_sources(joypad_pce PUBLIC ${COMMON_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/native/device/pcengine/pcengine_device.c
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/usb2pce/app.c
)
target_include_directories(joypad_pce PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/usb2pce
    ${CMAKE_CURRENT_SOURCE_DIR}/native/device/pcengine
)
target_link_libraries(joypad_pce PRIVATE ${COMMON_LIBRARIES})
joypad_target_common(joypad_pce)
joypad_add_btstack(joypad_pce)
pico_generate_pio_header(joypad_pce ${CMAKE_CURRENT_LIST_DIR}/native/device/pcengine/plex.pio)
pico_generate_pio_header(joypad_pce ${CMAKE_CURRENT_LIST_DIR}/native/device/pcengine/clock.pio)
pico_generate_pio_header(joypad_pce ${CMAKE_CURRENT_LIST_DIR}/native/device/pcengine/select.pio)

# USB to USB (RP2040-Zero / Waveshare PiZero)
# 🚨 MODIFIÉ POUR GPIO 6/7 🚨
add_executable(joypad_usb_rp2040zero)
target_compile_definitions(joypad_usb_rp2040zero PRIVATE
    CONFIG_USB=1
    CONFIG_PIO_USB_DP_PIN=6
    PICO_DEFAULT_PIO_USB_DP_PIN=6
    BOARD_TUH_RHPORT=1
    WS2812_PIN=16
    USE_BOOTSEL_BUTTON=1
)
target_sources(joypad_usb_rp2040zero PUBLIC ${COMMON_SOURCES} ${USB_DEVICE_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/usb2usb/app.c
)
target_include_directories(joypad_usb_rp2040zero PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/usb2usb
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usbd
)
target_link_libraries(joypad_usb_rp2040zero PRIVATE ${COMMON_LIBRARIES} tinyusb_device tinyusb_pico_pio_usb)
joypad_target_common(joypad_usb_rp2040zero)
joypad_add_btstack(joypad_usb_rp2040zero)

# ============================================================================
# DEBUG BUILD CONFIGURATION
# ============================================================================

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og")
else()
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
endif()
