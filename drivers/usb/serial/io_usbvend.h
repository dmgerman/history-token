multiline_comment|/************************************************************************&n; *&n; *&t;USBVEND.H&t;&t;Vendor-specific USB definitions&n; *&n; *&t;NOTE: This must be kept in sync with the Edgeport firmware and&n; *&t;must be kept backward-compatible with older firmware.&n; *&n; ************************************************************************&n; *&n; *&t;Copyright (C) 1998 Inside Out Networks, Inc.&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; ************************************************************************/
macro_line|#if !defined(_USBVEND_H)
DECL|macro|_USBVEND_H
mdefine_line|#define&t;_USBVEND_H
multiline_comment|/************************************************************************&n; *&n; *&t;&t;D e f i n e s   /   T y p e d e f s&n; *&n; ************************************************************************/
singleline_comment|//
singleline_comment|// Definitions of USB product IDs
singleline_comment|// 
DECL|macro|USB_VENDOR_ID_ION
mdefine_line|#define&t;USB_VENDOR_ID_ION&t;0x1608&t;&t;
singleline_comment|// Our VID
DECL|macro|USB_VENDOR_ID_TI
mdefine_line|#define&t;USB_VENDOR_ID_TI&t;0x0451&t;&t;
singleline_comment|// TI VID
singleline_comment|//
singleline_comment|// Definitions of USB product IDs (PID)
singleline_comment|// We break the USB-defined PID into an OEM Id field (upper 6 bits)
singleline_comment|// and a Device Id (bottom 10 bits). The Device Id defines what
singleline_comment|// device this actually is regardless of what the OEM wants to
singleline_comment|// call it.
singleline_comment|//
singleline_comment|// ION-device OEM IDs
DECL|macro|ION_OEM_ID_ION
mdefine_line|#define&t;ION_OEM_ID_ION&t;&t;0&t;&t;
singleline_comment|// 00h Inside Out Networks
DECL|macro|ION_OEM_ID_NLYNX
mdefine_line|#define&t;ION_OEM_ID_NLYNX&t;1&t;&t;
singleline_comment|// 01h NLynx Systems
DECL|macro|ION_OEM_ID_GENERIC
mdefine_line|#define&t;ION_OEM_ID_GENERIC&t;2&t;&t;
singleline_comment|// 02h Generic OEM
DECL|macro|ION_OEM_ID_MAC
mdefine_line|#define&t;ION_OEM_ID_MAC&t;&t;3&t;&t;
singleline_comment|// 03h Mac Version
DECL|macro|ION_OEM_ID_MEGAWOLF
mdefine_line|#define&t;ION_OEM_ID_MEGAWOLF&t;4&t;&t;
singleline_comment|// 04h Lupusb OEM Mac version (MegaWolf)
DECL|macro|ION_OEM_ID_MULTITECH
mdefine_line|#define&t;ION_OEM_ID_MULTITECH&t;5&t;&t;
singleline_comment|// 05h Multitech Rapidports
DECL|macro|ION_OEM_ID_AGILENT
mdefine_line|#define&t;ION_OEM_ID_AGILENT&t;6&t;&t;
singleline_comment|// 06h AGILENT board
singleline_comment|// ION-device Device IDs
singleline_comment|// Product IDs - assigned to match middle digit of serial number (No longer true)
DECL|macro|ION_DEVICE_ID_80251_NETCHIP
mdefine_line|#define ION_DEVICE_ID_80251_NETCHIP&t;0x020&t;
singleline_comment|// This bit is set in the PID if this edgeport hardware$
singleline_comment|// is based on the 80251+Netchip.  
DECL|macro|ION_DEVICE_ID_GENERATION_1
mdefine_line|#define ION_DEVICE_ID_GENERATION_1&t;0x00&t;
singleline_comment|// Value for 930 based edgeports
DECL|macro|ION_DEVICE_ID_GENERATION_2
mdefine_line|#define ION_DEVICE_ID_GENERATION_2&t;0x01&t;
singleline_comment|// Value for 80251+Netchip.
DECL|macro|ION_DEVICE_ID_GENERATION_3
mdefine_line|#define ION_DEVICE_ID_GENERATION_3&t;0x02&t;
singleline_comment|// Value for Texas Instruments TUSB5052 chip
DECL|macro|ION_DEVICE_ID_GENERATION_4
mdefine_line|#define ION_DEVICE_ID_GENERATION_4&t;0x03&t;
singleline_comment|// Watchport Family of products
DECL|macro|ION_GENERATION_MASK
mdefine_line|#define ION_GENERATION_MASK&t;&t;0x03
DECL|macro|ION_DEVICE_ID_HUB_MASK
mdefine_line|#define ION_DEVICE_ID_HUB_MASK&t;&t;0x0080&t;
singleline_comment|// This bit in the PID designates a HUB device
singleline_comment|// for example 8C would be a 421 4 port hub
singleline_comment|// and 8D would be a 2 port embedded hub
DECL|macro|EDGEPORT_DEVICE_ID_MASK
mdefine_line|#define EDGEPORT_DEVICE_ID_MASK&t;&t;&t;0x0ff&t;
singleline_comment|// Not including OEM or GENERATION fields
DECL|macro|ION_DEVICE_ID_UNCONFIGURED_EDGE_DEVICE
mdefine_line|#define&t;ION_DEVICE_ID_UNCONFIGURED_EDGE_DEVICE&t;0x000&t;
singleline_comment|// In manufacturing only
DECL|macro|ION_DEVICE_ID_EDGEPORT_4
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4&t;&t;0x001&t;
singleline_comment|// Edgeport/4 RS232
DECL|macro|ION_DEVICE_ID_EDGEPORT_8R
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_8R&t;&t;0x002&t;
singleline_comment|// Edgeport with RJ45 no Ring
DECL|macro|ION_DEVICE_ID_RAPIDPORT_4
mdefine_line|#define ION_DEVICE_ID_RAPIDPORT_4&t;&t;0x003&t;
singleline_comment|// Rapidport/4
DECL|macro|ION_DEVICE_ID_EDGEPORT_4T
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4T&t;&t;0x004&t;
singleline_comment|// Edgeport/4 RS232 for Telxon (aka &quot;Fleetport&quot;)
DECL|macro|ION_DEVICE_ID_EDGEPORT_2
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2&t;&t;0x005&t;
singleline_comment|// Edgeport/2 RS232
DECL|macro|ION_DEVICE_ID_EDGEPORT_4I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4I&t;&t;0x006&t;
singleline_comment|// Edgeport/4 RS422
DECL|macro|ION_DEVICE_ID_EDGEPORT_2I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2I&t;&t;0x007&t;
singleline_comment|// Edgeport/2 RS422/RS485
DECL|macro|ION_DEVICE_ID_EDGEPORT_8RR
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_8RR&t;&t;0x008&t;
singleline_comment|// Edgeport with RJ45 with Data and RTS/CTS only
singleline_comment|//&t;ION_DEVICE_ID_EDGEPORT_8_HANDBUILT&t;0x009&t;// Hand-built Edgeport/8 (Placeholder, used in middle digit of serial number only!)
singleline_comment|//&t;ION_DEVICE_ID_MULTIMODEM_4X56&t;&t;0x00A&t;// MultiTech version of RP/4 (Placeholder, used in middle digit of serial number only!)
DECL|macro|ION_DEVICE_ID_EDGEPORT_PARALLEL_PORT
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_PARALLEL_PORT&t;0x00B&t;
singleline_comment|// Edgeport/(4)21 Parallel port (USS720)
DECL|macro|ION_DEVICE_ID_EDGEPORT_421
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_421&t;&t;0x00C&t;
singleline_comment|// Edgeport/421 Hub+RS232+Parallel
DECL|macro|ION_DEVICE_ID_EDGEPORT_21
mdefine_line|#define&t;ION_DEVICE_ID_EDGEPORT_21&t;&t;0x00D&t;
singleline_comment|// Edgeport/21  RS232+Parallel
DECL|macro|ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU&t;0x00E&t;
singleline_comment|// Half of an Edgeport/8 (the kind with 2 EP/4s on 1 PCB)
DECL|macro|ION_DEVICE_ID_EDGEPORT_8
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8&t;&t;0x00F&t;
singleline_comment|// Edgeport/8 (single-CPU)
DECL|macro|ION_DEVICE_ID_EDGEPORT_2_DIN
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2_DIN&t;&t;0x010&t;
singleline_comment|// Edgeport/2 RS232 with Apple DIN connector
DECL|macro|ION_DEVICE_ID_EDGEPORT_4_DIN
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4_DIN&t;&t;0x011&t;
singleline_comment|// Edgeport/4 RS232 with Apple DIN connector
DECL|macro|ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU&t;0x012&t;
singleline_comment|// Half of an Edgeport/16 (the kind with 2 EP/8s)
DECL|macro|ION_DEVICE_ID_EDGEPORT_COMPATIBLE
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_COMPATIBLE&t;0x013&t;
singleline_comment|// Edgeport Compatible, for NCR, Axiohm etc. testing
DECL|macro|ION_DEVICE_ID_EDGEPORT_8I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8I&t;&t;0x014&t;
singleline_comment|// Edgeport/8 RS422 (single-CPU)
DECL|macro|ION_DEVICE_ID_EDGEPORT_1
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_1&t;&t;0x015&t;
singleline_comment|// Edgeport/1 RS232
DECL|macro|ION_DEVICE_ID_EPOS44
mdefine_line|#define ION_DEVICE_ID_EPOS44&t;&t;&t;0x016&t;
singleline_comment|// Half of an EPOS/44 (TIUMP BASED)
DECL|macro|ION_DEVICE_ID_EDGEPORT_42
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_42&t;&t;0x017&t;
singleline_comment|// Edgeport/42
DECL|macro|ION_DEVICE_ID_EDGEPORT_412_8
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_412_8&t;&t;0x018&t;
singleline_comment|// Edgeport/412 8 port part
DECL|macro|ION_DEVICE_ID_EDGEPORT_412_4
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_412_4&t;&t;0x019&t;
singleline_comment|// Edgeport/412&t;4 port part
DECL|macro|ION_DEVICE_ID_EDGEPORT_22I
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_22I&t;&t;0x01A&t;
singleline_comment|// Edgeport/22I is an Edgeport/4 with ports 1&amp;2 RS422 and ports 3&amp;4 RS232
singleline_comment|// Compact Form factor TI based devices  2c, 21c, 22c, 221c
DECL|macro|ION_DEVICE_ID_EDGEPORT_2C
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_2C&t;&t;0x01B&t;
singleline_comment|// Edgeport/2c is a TI based Edgeport/2 - Small I2c
DECL|macro|ION_DEVICE_ID_EDGEPORT_221C
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_221C&t;&t;0x01C&t;
singleline_comment|// Edgeport/221c is a TI based Edgeport/2 with lucent chip and
singleline_comment|// 2 external hub ports - Large I2C
DECL|macro|ION_DEVICE_ID_EDGEPORT_22C
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_22C&t;&t;0x01D&t;
singleline_comment|// Edgeport/22c is a TI based Edgeport/2 with
singleline_comment|// 2 external hub ports - Large I2C
DECL|macro|ION_DEVICE_ID_EDGEPORT_21C
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_21C&t;&t;0x01E&t;
singleline_comment|// Edgeport/21c is a TI based Edgeport/2 with lucent chip
singleline_comment|// Small I2C
multiline_comment|/*&n; *  DANGER DANGER The 0x20 bit was used to indicate a 8251/netchip GEN 2 device.&n; *  Since the MAC, Linux, and Optimal drivers still used the old code&n; *  I suggest that you skip the 0x20 bit when creating new PIDs&n; */
singleline_comment|// Generation 3 devices -- 3410 based edgport/1 (256 byte I2C)
DECL|macro|ION_DEVICE_ID_TI3410_EDGEPORT_1
mdefine_line|#define ION_DEVICE_ID_TI3410_EDGEPORT_1&t;&t;0x040&t;
singleline_comment|// Edgeport/1 RS232
DECL|macro|ION_DEVICE_ID_TI3410_EDGEPORT_1I
mdefine_line|#define ION_DEVICE_ID_TI3410_EDGEPORT_1I&t;0x041&t;
singleline_comment|// Edgeport/1i- RS422 model
singleline_comment|// Ti based software switchable RS232/RS422/RS485 devices
DECL|macro|ION_DEVICE_ID_EDGEPORT_4S
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_4S&t;&t;0x042&t;
singleline_comment|// Edgeport/4s - software switchable model
DECL|macro|ION_DEVICE_ID_EDGEPORT_8S
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_8S&t;&t;0x043&t;
singleline_comment|// Edgeport/8s - software switchable model
singleline_comment|// Usb to Ethernet dongle
DECL|macro|ION_DEVICE_ID_EDGEPORT_E
mdefine_line|#define ION_DEVICE_ID_EDGEPORT_E&t;&t;0x0E0&t;
singleline_comment|// Edgeport/E Usb to Ethernet
singleline_comment|// Edgeport TI based devices
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_4
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_4&t;&t;0x0201&t;
singleline_comment|// Edgeport/4 RS232
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_2
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_2&t;&t;0x0205&t;
singleline_comment|// Edgeport/2 RS232
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_4I
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_4I&t;&t;0x0206&t;
singleline_comment|// Edgeport/4i RS422
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_2I
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_2I&t;&t;0x0207&t;
singleline_comment|// Edgeport/2i RS422/RS485
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_421
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_421&t;&t;0x020C&t;
singleline_comment|// Edgeport/421 4 hub 2 RS232 + Parallel (lucent on a different hub port)
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_21
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_21&t;&t;0x020D&t;
singleline_comment|// Edgeport/21 2 RS232 + Parallel (lucent on a different hub port)
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_8
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_8&t;&t;0x020F&t;
singleline_comment|// Edgeport/8 (single-CPU)
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_1
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_1&t;&t;0x0215&t;
singleline_comment|// Edgeport/1 RS232
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_42
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_42&t;&t;0x0217&t;
singleline_comment|// Edgeport/42 4 hub 2 RS232
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_22I
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_22I  &t;&t;0x021A&t;
singleline_comment|// Edgeport/22I is an Edgeport/4 with ports 1&amp;2 RS422 and ports 3&amp;4 RS232
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_2C
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_2C&t;&t;0x021B&t;
singleline_comment|// Edgeport/2c RS232
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_221C
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_221C&t;&t;0x021C&t;
singleline_comment|// Edgeport/221c is a TI based Edgeport/2 with lucent chip and
singleline_comment|// 2 external hub ports - Large I2C
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_22C
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_22C&t;&t;0x021D&t;
singleline_comment|// Edgeport/22c is a TI based Edgeport/2 with
singleline_comment|// 2 external hub ports - Large I2C
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_21C
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_21C&t;&t;0x021E&t;
singleline_comment|// Edgeport/21c is a TI based Edgeport/2 with lucent chip
singleline_comment|// Generation 3 devices -- 3410 based edgport/1 (256 byte I2C) 
DECL|macro|ION_DEVICE_ID_TI_TI3410_EDGEPORT_1
mdefine_line|#define ION_DEVICE_ID_TI_TI3410_EDGEPORT_1&t;0x240&t;
singleline_comment|// Edgeport/1 RS232
DECL|macro|ION_DEVICE_ID_TI_TI3410_EDGEPORT_1I
mdefine_line|#define ION_DEVICE_ID_TI_TI3410_EDGEPORT_1I&t;0x241&t;
singleline_comment|// Edgeport/1i- RS422 model
singleline_comment|// Ti based software switchable RS232/RS422/RS485 devices
DECL|macro|ION_DEVICE_ID_TI_EDGEPORT_4S
mdefine_line|#define ION_DEVICE_ID_TI_EDGEPORT_4S&t;&t;0x242&t;
singleline_comment|// Edgeport/4s - software switchable model
DECL|macro|ION_DEVICE_ID_IT_EDGEPORT_8S
mdefine_line|#define ION_DEVICE_ID_IT_EDGEPORT_8S&t;&t;0x243&t;
singleline_comment|// Edgeport/8s - software switchable model
multiline_comment|/************************************************************************&n; *&n; *                        Generation 4 devices&n; *&n; ************************************************************************/
singleline_comment|// Watchport based on 3410 both 1-wire and binary products (16K I2C)
DECL|macro|ION_DEVICE_ID_WP_UNSERIALIZED
mdefine_line|#define ION_DEVICE_ID_WP_UNSERIALIZED&t;&t;0x300&t;
singleline_comment|// Watchport based on 3410 both 1-wire and binary products
DECL|macro|ION_DEVICE_ID_WP_PROXIMITY
mdefine_line|#define ION_DEVICE_ID_WP_PROXIMITY&t;&t;0x301&t;
singleline_comment|// Watchport/P Discontinued
DECL|macro|ION_DEVICE_ID_WP_MOTION
mdefine_line|#define ION_DEVICE_ID_WP_MOTION&t;&t;&t;0x302&t;
singleline_comment|// Watchport/M
DECL|macro|ION_DEVICE_ID_WP_MOISTURE
mdefine_line|#define ION_DEVICE_ID_WP_MOISTURE&t;&t;0x303&t;
singleline_comment|// Watchport/W
DECL|macro|ION_DEVICE_ID_WP_TEMPERATURE
mdefine_line|#define ION_DEVICE_ID_WP_TEMPERATURE&t;&t;0x304&t;
singleline_comment|// Watchport/T
DECL|macro|ION_DEVICE_ID_WP_HUMIDITY
mdefine_line|#define ION_DEVICE_ID_WP_HUMIDITY&t;&t;0x305&t;
singleline_comment|// Watchport/H
DECL|macro|ION_DEVICE_ID_WP_POWER
mdefine_line|#define ION_DEVICE_ID_WP_POWER&t;&t;&t;0x306&t;
singleline_comment|// Watchport
DECL|macro|ION_DEVICE_ID_WP_LIGHT
mdefine_line|#define ION_DEVICE_ID_WP_LIGHT&t;&t;&t;0x307&t;
singleline_comment|// Watchport
DECL|macro|ION_DEVICE_ID_WP_RADIATION
mdefine_line|#define ION_DEVICE_ID_WP_RADIATION&t;&t;0x308&t;
singleline_comment|// Watchport
DECL|macro|ION_DEVICE_ID_WP_ACCELERATION
mdefine_line|#define ION_DEVICE_ID_WP_ACCELERATION&t;&t;0x309&t;
singleline_comment|// Watchport/A
DECL|macro|ION_DEVICE_ID_WP_DISTANCE
mdefine_line|#define ION_DEVICE_ID_WP_DISTANCE&t;&t;0x30A&t;
singleline_comment|// Watchport/D Discontinued
DECL|macro|ION_DEVICE_ID_WP_PROX_DIST
mdefine_line|#define ION_DEVICE_ID_WP_PROX_DIST&t;&t;0x30B&t;
singleline_comment|// Watchport/D uses distance sensor
singleline_comment|// Default to /P function
DECL|macro|ION_DEVICE_ID_PLUS_PWR_HP4CD
mdefine_line|#define ION_DEVICE_ID_PLUS_PWR_HP4CD&t;&t;0x30C&t;
singleline_comment|// 5052 Plus Power HubPort/4CD+ (for Dell)
DECL|macro|ION_DEVICE_ID_PLUS_PWR_HP4C
mdefine_line|#define ION_DEVICE_ID_PLUS_PWR_HP4C&t;&t;0x30D&t;
singleline_comment|// 5052 Plus Power HubPort/4C+ 
DECL|macro|ION_DEVICE_ID_PLUS_PWR_PCI
mdefine_line|#define ION_DEVICE_ID_PLUS_PWR_PCI&t;&t;0x30E&t;
singleline_comment|// 3410 Plus Power PCI Host Controller 4 port
singleline_comment|//
singleline_comment|// Definitions for AXIOHM USB product IDs
singleline_comment|//
DECL|macro|USB_VENDOR_ID_AXIOHM
mdefine_line|#define&t;USB_VENDOR_ID_AXIOHM&t;&t;&t;0x05D9&t;
singleline_comment|// Axiohm VID
DECL|macro|AXIOHM_DEVICE_ID_MASK
mdefine_line|#define AXIOHM_DEVICE_ID_MASK&t;&t;&t;0xffff
DECL|macro|AXIOHM_DEVICE_ID_EPIC_A758
mdefine_line|#define AXIOHM_DEVICE_ID_EPIC_A758&t;&t;0xA758
DECL|macro|AXIOHM_DEVICE_ID_EPIC_A794
mdefine_line|#define AXIOHM_DEVICE_ID_EPIC_A794&t;&t;0xA794
DECL|macro|AXIOHM_DEVICE_ID_EPIC_A225
mdefine_line|#define AXIOHM_DEVICE_ID_EPIC_A225&t;&t;0xA225
singleline_comment|//
singleline_comment|// Definitions for NCR USB product IDs
singleline_comment|//
DECL|macro|USB_VENDOR_ID_NCR
mdefine_line|#define&t;USB_VENDOR_ID_NCR&t;&t;&t;0x0404&t;
singleline_comment|// NCR VID
DECL|macro|NCR_DEVICE_ID_MASK
mdefine_line|#define NCR_DEVICE_ID_MASK&t;&t;&t;0xffff
DECL|macro|NCR_DEVICE_ID_EPIC_0202
mdefine_line|#define NCR_DEVICE_ID_EPIC_0202&t;&t;&t;0x0202
DECL|macro|NCR_DEVICE_ID_EPIC_0203
mdefine_line|#define NCR_DEVICE_ID_EPIC_0203&t;&t;&t;0x0203
DECL|macro|NCR_DEVICE_ID_EPIC_0310
mdefine_line|#define NCR_DEVICE_ID_EPIC_0310&t;&t;&t;0x0310
DECL|macro|NCR_DEVICE_ID_EPIC_0311
mdefine_line|#define NCR_DEVICE_ID_EPIC_0311&t;&t;&t;0x0311
DECL|macro|NCR_DEVICE_ID_EPIC_0312
mdefine_line|#define NCR_DEVICE_ID_EPIC_0312&t;&t;&t;0x0312
singleline_comment|//
singleline_comment|// Definitions for SYMBOL USB product IDs
singleline_comment|//
DECL|macro|USB_VENDOR_ID_SYMBOL
mdefine_line|#define USB_VENDOR_ID_SYMBOL&t;&t;&t;0x05E0&t;
singleline_comment|// Symbol VID
DECL|macro|SYMBOL_DEVICE_ID_MASK
mdefine_line|#define SYMBOL_DEVICE_ID_MASK&t;&t;&t;0xffff
DECL|macro|SYMBOL_DEVICE_ID_KEYFOB
mdefine_line|#define SYMBOL_DEVICE_ID_KEYFOB&t;&t;&t;0x0700
singleline_comment|//
singleline_comment|// Definitions for other product IDs
DECL|macro|ION_DEVICE_ID_MT4X56USB
mdefine_line|#define ION_DEVICE_ID_MT4X56USB&t;&t;&t;0x1403&t;
singleline_comment|// OEM device
DECL|macro|GENERATION_ID_FROM_USB_PRODUCT_ID
mdefine_line|#define&t;GENERATION_ID_FROM_USB_PRODUCT_ID( ProductId )&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) ((ProductId &gt;&gt; 8) &amp; (ION_GENERATION_MASK)) )
DECL|macro|MAKE_USB_PRODUCT_ID
mdefine_line|#define&t;MAKE_USB_PRODUCT_ID( OemId, DeviceId )&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) (((OemId) &lt;&lt; 10) || (DeviceId)) )
DECL|macro|DEVICE_ID_FROM_USB_PRODUCT_ID
mdefine_line|#define&t;DEVICE_ID_FROM_USB_PRODUCT_ID( ProductId )&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) ((ProductId) &amp; (EDGEPORT_DEVICE_ID_MASK)) )
DECL|macro|OEM_ID_FROM_USB_PRODUCT_ID
mdefine_line|#define&t;OEM_ID_FROM_USB_PRODUCT_ID( ProductId )&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;( (__u16) (((ProductId) &gt;&gt; 10) &amp; 0x3F) )
singleline_comment|//
singleline_comment|// Definitions of parameters for download code. Note that these are
singleline_comment|// specific to a given version of download code and must change if the
singleline_comment|// corresponding download code changes.
singleline_comment|//
singleline_comment|// TxCredits value below which driver won&squot;t bother sending (to prevent too many small writes).
singleline_comment|// Send only if above 25%
DECL|macro|EDGE_FW_GET_TX_CREDITS_SEND_THRESHOLD
mdefine_line|#define EDGE_FW_GET_TX_CREDITS_SEND_THRESHOLD(InitialCredit, MaxPacketSize) (max( ((InitialCredit) / 4), (MaxPacketSize) ))
DECL|macro|EDGE_FW_BULK_MAX_PACKET_SIZE
mdefine_line|#define&t;EDGE_FW_BULK_MAX_PACKET_SIZE&t;&t;64&t;
singleline_comment|// Max Packet Size for Bulk In Endpoint (EP1)
DECL|macro|EDGE_FW_BULK_READ_BUFFER_SIZE
mdefine_line|#define EDGE_FW_BULK_READ_BUFFER_SIZE&t;&t;1024&t;
singleline_comment|// Size to use for Bulk reads
DECL|macro|EDGE_FW_INT_MAX_PACKET_SIZE
mdefine_line|#define&t;EDGE_FW_INT_MAX_PACKET_SIZE&t;&t;32&t;
singleline_comment|// Max Packet Size for Interrupt In Endpoint
singleline_comment|// Note that many units were shipped with MPS=16, we
singleline_comment|// force an upgrade to this value).
DECL|macro|EDGE_FW_INT_INTERVAL
mdefine_line|#define EDGE_FW_INT_INTERVAL&t;&t;&t;2&t;
singleline_comment|// 2ms polling on IntPipe
singleline_comment|//
singleline_comment|// Definitions of I/O Networks vendor-specific requests
singleline_comment|// for default endpoint
singleline_comment|//
singleline_comment|//&t;bmRequestType = 01000000&t;Set vendor-specific, to device
singleline_comment|//&t;bmRequestType = 11000000&t;Get vendor-specific, to device
singleline_comment|//
singleline_comment|// These are the definitions for the bRequest field for the
singleline_comment|// above bmRequestTypes.
singleline_comment|//
singleline_comment|// For the read/write Edgeport memory commands, the parameters
singleline_comment|// are as follows:
singleline_comment|//&t;&t;wValue = 16-bit address
singleline_comment|//&t;&t;wIndex = unused (though we could put segment 00: or FF: here)
singleline_comment|//&t;&t;wLength = # bytes to read/write (max 64)
singleline_comment|//&t;&t;&t;&t;&t;&t;&t;
DECL|macro|USB_REQUEST_ION_RESET_DEVICE
mdefine_line|#define USB_REQUEST_ION_RESET_DEVICE&t;0&t;
singleline_comment|// Warm reboot Edgeport, retaining USB address
DECL|macro|USB_REQUEST_ION_GET_EPIC_DESC
mdefine_line|#define USB_REQUEST_ION_GET_EPIC_DESC&t;1&t;
singleline_comment|// Get Edgeport Compatibility Descriptor
singleline_comment|// unused&t;&t;&t;&t;2&t;// Unused, available
DECL|macro|USB_REQUEST_ION_READ_RAM
mdefine_line|#define USB_REQUEST_ION_READ_RAM&t;3&t;
singleline_comment|// Read  EdgePort RAM at specified addr
DECL|macro|USB_REQUEST_ION_WRITE_RAM
mdefine_line|#define USB_REQUEST_ION_WRITE_RAM&t;4&t;
singleline_comment|// Write EdgePort RAM at specified addr
DECL|macro|USB_REQUEST_ION_READ_ROM
mdefine_line|#define USB_REQUEST_ION_READ_ROM&t;5&t;
singleline_comment|// Read  EdgePort ROM at specified addr
DECL|macro|USB_REQUEST_ION_WRITE_ROM
mdefine_line|#define USB_REQUEST_ION_WRITE_ROM&t;6&t;
singleline_comment|// Write EdgePort ROM at specified addr
DECL|macro|USB_REQUEST_ION_EXEC_DL_CODE
mdefine_line|#define USB_REQUEST_ION_EXEC_DL_CODE&t;7&t;
singleline_comment|// Begin execution of RAM-based download
singleline_comment|// code by jumping to address in wIndex:wValue
singleline_comment|//&t;&t;&t;&t;&t;8&t;// Unused, available
DECL|macro|USB_REQUEST_ION_ENABLE_SUSPEND
mdefine_line|#define USB_REQUEST_ION_ENABLE_SUSPEND&t;9&t;
singleline_comment|// Enable/Disable suspend feature
singleline_comment|// (wValue != 0: Enable; wValue = 0: Disable)
DECL|macro|USB_REQUEST_ION_SEND_IOSP
mdefine_line|#define USB_REQUEST_ION_SEND_IOSP&t;10&t;
singleline_comment|// Send an IOSP command to the edgeport over the control pipe&t;
DECL|macro|USB_REQUEST_ION_RECV_IOSP
mdefine_line|#define USB_REQUEST_ION_RECV_IOSP&t;11&t;
singleline_comment|// Receive an IOSP command from the edgeport over the control pipe
DECL|macro|USB_REQUEST_ION_DIS_INT_TIMER
mdefine_line|#define USB_REQUEST_ION_DIS_INT_TIMER&t;0x80&t;
singleline_comment|// Sent to Axiohm to enable/ disable
singleline_comment|// interrupt token timer
singleline_comment|// wValue = 1, enable (default)
singleline_comment|// wValue = 0, disable
singleline_comment|//
singleline_comment|// Define parameter values for our vendor-specific commands
singleline_comment|//
singleline_comment|//
singleline_comment|// Edgeport Compatiblity Descriptor
singleline_comment|//
singleline_comment|// This descriptor is only returned by Edgeport-compatible devices
singleline_comment|// supporting the EPiC spec. True ION devices do not return this
singleline_comment|// descriptor, but instead return STALL on receipt of the
singleline_comment|// GET_EPIC_DESC command. The driver interprets a STALL to mean that
singleline_comment|// this is a &quot;real&quot; Edgeport.
singleline_comment|//
DECL|struct|edge_compatibility_bits
r_struct
id|edge_compatibility_bits
(brace
singleline_comment|// This __u32 defines which Vendor-specific commands/functionality
singleline_comment|// the device supports on the default EP0 pipe.
DECL|member|VendEnableSuspend
id|__u32
id|VendEnableSuspend
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0001 Set if device supports ION_ENABLE_SUSPEND
DECL|member|VendUnused
id|__u32
id|VendUnused
suffix:colon
l_int|31
suffix:semicolon
singleline_comment|// Available for future expansion, must be 0
singleline_comment|// This __u32 defines which IOSP commands are supported over the
singleline_comment|// bulk pipe EP1.
singleline_comment|// xxxx Set if device supports:
DECL|member|IOSPOpen
id|__u32
id|IOSPOpen
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0001&t;OPEN / OPEN_RSP (Currently must be 1)
DECL|member|IOSPClose
id|__u32
id|IOSPClose
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0002&t;CLOSE
DECL|member|IOSPChase
id|__u32
id|IOSPChase
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0004&t;CHASE / CHASE_RSP
DECL|member|IOSPSetRxFlow
id|__u32
id|IOSPSetRxFlow
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0008&t;SET_RX_FLOW
DECL|member|IOSPSetTxFlow
id|__u32
id|IOSPSetTxFlow
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0010&t;SET_TX_FLOW
DECL|member|IOSPSetXChar
id|__u32
id|IOSPSetXChar
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0020&t;SET_XON_CHAR/SET_XOFF_CHAR
DECL|member|IOSPRxCheck
id|__u32
id|IOSPRxCheck
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0040&t;RX_CHECK_REQ/RX_CHECK_RSP
DECL|member|IOSPSetClrBreak
id|__u32
id|IOSPSetClrBreak
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0080&t;SET_BREAK/CLEAR_BREAK
DECL|member|IOSPWriteMCR
id|__u32
id|IOSPWriteMCR
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0100&t;MCR register writes (set/clr DTR/RTS)
DECL|member|IOSPWriteLCR
id|__u32
id|IOSPWriteLCR
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0200&t;LCR register writes (wordlen/stop/parity)
DECL|member|IOSPSetBaudRate
id|__u32
id|IOSPSetBaudRate
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0400&t;setting Baud rate (writes to LCR.80h and DLL/DLM register)
DECL|member|IOSPDisableIntPipe
id|__u32
id|IOSPDisableIntPipe
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0800 Do not use the interrupt pipe for TxCredits or RxButesAvailable
DECL|member|IOSPRxDataAvail
id|__u32
id|IOSPRxDataAvail
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 1000 Return status of RX Fifo (Data available in Fifo)
DECL|member|IOSPTxPurge
id|__u32
id|IOSPTxPurge
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 2000 Purge TXBuffer and/or Fifo in Edgeport hardware
DECL|member|IOSPUnused
id|__u32
id|IOSPUnused
suffix:colon
l_int|18
suffix:semicolon
singleline_comment|// Available for future expansion, must be 0
singleline_comment|// This __u32 defines which &squot;general&squot; features are supported
DECL|member|TrueEdgeport
id|__u32
id|TrueEdgeport
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0001&t;Set if device is a &squot;real&squot; Edgeport
singleline_comment|// (Used only by driver, NEVER set by an EPiC device)
DECL|member|GenUnused
id|__u32
id|GenUnused
suffix:colon
l_int|31
suffix:semicolon
singleline_comment|// Available for future expansion, must be 0
)brace
suffix:semicolon
DECL|struct|edge_compatibility_descriptor
r_struct
id|edge_compatibility_descriptor
(brace
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
singleline_comment|// Descriptor Length (per USB spec)
DECL|member|DescType
id|__u8
id|DescType
suffix:semicolon
singleline_comment|// Descriptor Type (per USB spec, =DEVICE type)
DECL|member|EpicVer
id|__u8
id|EpicVer
suffix:semicolon
singleline_comment|// Version of EPiC spec supported
singleline_comment|// (Currently must be 1)
DECL|member|NumPorts
id|__u8
id|NumPorts
suffix:semicolon
singleline_comment|// Number of serial ports supported
DECL|member|iDownloadFile
id|__u8
id|iDownloadFile
suffix:semicolon
singleline_comment|// Index of string containing download code filename
singleline_comment|// 0=no download, FF=download compiled into driver.
DECL|member|Unused
id|__u8
id|Unused
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// Available for future expansion, must be 0
singleline_comment|// (Currently must be 0).
DECL|member|MajorVersion
id|__u8
id|MajorVersion
suffix:semicolon
singleline_comment|// Firmware version: xx.
DECL|member|MinorVersion
id|__u8
id|MinorVersion
suffix:semicolon
singleline_comment|//  yy.
DECL|member|BuildNumber
id|__le16
id|BuildNumber
suffix:semicolon
singleline_comment|//  zzzz (LE format)
singleline_comment|// The following structure contains __u32s, with each bit
singleline_comment|// specifying whether the EPiC device supports the given
singleline_comment|// command or functionality.
DECL|member|Supports
r_struct
id|edge_compatibility_bits
id|Supports
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// Values for iDownloadFile
DECL|macro|EDGE_DOWNLOAD_FILE_NONE
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_NONE&t;&t;0&t;
singleline_comment|// No download requested
DECL|macro|EDGE_DOWNLOAD_FILE_INTERNAL
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_INTERNAL&t;0xFF&t;
singleline_comment|// Download the file compiled into driver (930 version)
DECL|macro|EDGE_DOWNLOAD_FILE_I930
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_I930&t;&t;0xFF&t;
singleline_comment|// Download the file compiled into driver (930 version)
DECL|macro|EDGE_DOWNLOAD_FILE_80251
mdefine_line|#define&t;EDGE_DOWNLOAD_FILE_80251&t;0xFE&t;
singleline_comment|// Download the file compiled into driver (80251 version)
multiline_comment|/*&n; *&t;Special addresses for READ/WRITE_RAM/ROM&n; */
singleline_comment|// Version 1 (original) format of DeviceParams
DECL|macro|EDGE_MANUF_DESC_ADDR_V1
mdefine_line|#define&t;EDGE_MANUF_DESC_ADDR_V1&t;&t;0x00FF7F00
DECL|macro|EDGE_MANUF_DESC_LEN_V1
mdefine_line|#define&t;EDGE_MANUF_DESC_LEN_V1&t;&t;sizeof(EDGE_MANUF_DESCRIPTOR_V1)
singleline_comment|// Version 2 format of DeviceParams. This format is longer (3C0h)
singleline_comment|// and starts lower in memory, at the uppermost 1K in ROM.
DECL|macro|EDGE_MANUF_DESC_ADDR
mdefine_line|#define&t;EDGE_MANUF_DESC_ADDR&t;&t;0x00FF7C00
DECL|macro|EDGE_MANUF_DESC_LEN
mdefine_line|#define&t;EDGE_MANUF_DESC_LEN&t;&t;sizeof(struct edge_manuf_descriptor)
singleline_comment|// Boot params descriptor
DECL|macro|EDGE_BOOT_DESC_ADDR
mdefine_line|#define&t;EDGE_BOOT_DESC_ADDR&t;&t;0x00FF7FC0
DECL|macro|EDGE_BOOT_DESC_LEN
mdefine_line|#define&t;EDGE_BOOT_DESC_LEN&t;&t;sizeof(struct edge_boot_descriptor)
singleline_comment|// Define the max block size that may be read or written
singleline_comment|// in a read/write RAM/ROM command.
DECL|macro|MAX_SIZE_REQ_ION_READ_MEM
mdefine_line|#define&t;MAX_SIZE_REQ_ION_READ_MEM&t;( (__u16) 64 )
DECL|macro|MAX_SIZE_REQ_ION_WRITE_MEM
mdefine_line|#define&t;MAX_SIZE_REQ_ION_WRITE_MEM&t;( (__u16) 64 )
singleline_comment|//
singleline_comment|// Notes for the following two ION vendor-specific param descriptors:
singleline_comment|//
singleline_comment|//&t;1.&t;These have a standard USB descriptor header so they look like a
singleline_comment|//&t;&t;normal descriptor.
singleline_comment|//&t;2.&t;Any strings in the structures are in USB-defined string
singleline_comment|//&t;&t;descriptor format, so that they may be separately retrieved,
singleline_comment|//&t;&t;if necessary, with a minimum of work on the 930. This also
singleline_comment|//&t;&t;requires them to be in UNICODE format, which, for English at
singleline_comment|//&t;&t;least, simply means extending each __u8 into a __u16.
singleline_comment|//&t;3.&t;For all fields, 00 means &squot;uninitialized&squot;.
singleline_comment|//&t;4.&t;All unused areas should be set to 00 for future expansion.
singleline_comment|//
singleline_comment|// This structure is ver 2 format. It contains ALL USB descriptors as
singleline_comment|// well as the configuration parameters that were in the original V1
singleline_comment|// structure. It is NOT modified when new boot code is downloaded; rather,
singleline_comment|// these values are set or modified by manufacturing. It is located at
singleline_comment|// xC00-xFBF (length 3C0h) in the ROM.
singleline_comment|// This structure is a superset of the v1 structure and is arranged so
singleline_comment|// that all of the v1 fields remain at the same address. We are just
singleline_comment|// adding more room to the front of the structure to hold the descriptors.
singleline_comment|//
singleline_comment|// The actual contents of this structure are defined in a 930 assembly
singleline_comment|// file, converted to a binary image, and then written by the serialization
singleline_comment|// program. The C definition of this structure just defines a dummy
singleline_comment|// area for general USB descriptors and the descriptor tables (the root
singleline_comment|// descriptor starts at xC00). At the bottom of the structure are the
singleline_comment|// fields inherited from the v1 structure.
DECL|macro|MAX_SERIALNUMBER_LEN
mdefine_line|#define MAX_SERIALNUMBER_LEN&t;12
DECL|macro|MAX_ASSEMBLYNUMBER_LEN
mdefine_line|#define MAX_ASSEMBLYNUMBER_LEN&t;14
DECL|struct|edge_manuf_descriptor
r_struct
id|edge_manuf_descriptor
(brace
DECL|member|RootDescTable
id|__u16
id|RootDescTable
(braket
l_int|0x10
)braket
suffix:semicolon
singleline_comment|// C00 Root of descriptor tables (just a placeholder)
DECL|member|DescriptorArea
id|__u8
id|DescriptorArea
(braket
l_int|0x2E0
)braket
suffix:semicolon
singleline_comment|// C20 Descriptors go here, up to 2E0h (just a placeholder)
singleline_comment|//     Start of v1-compatible section
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
singleline_comment|// F00 Desc length for what follows, per USB (= C0h )
DECL|member|DescType
id|__u8
id|DescType
suffix:semicolon
singleline_comment|// F01 Desc type, per USB (=DEVICE type)
DECL|member|DescVer
id|__u8
id|DescVer
suffix:semicolon
singleline_comment|// F02 Desc version/format (currently 2)
DECL|member|NumRootDescEntries
id|__u8
id|NumRootDescEntries
suffix:semicolon
singleline_comment|// F03 # entries in RootDescTable
DECL|member|RomSize
id|__u8
id|RomSize
suffix:semicolon
singleline_comment|// F04 Size of ROM/E2PROM in K
DECL|member|RamSize
id|__u8
id|RamSize
suffix:semicolon
singleline_comment|// F05 Size of external RAM in K
DECL|member|CpuRev
id|__u8
id|CpuRev
suffix:semicolon
singleline_comment|// F06 CPU revision level (chg only if s/w visible)
DECL|member|BoardRev
id|__u8
id|BoardRev
suffix:semicolon
singleline_comment|// F07 PCB revision level (chg only if s/w visible)
DECL|member|NumPorts
id|__u8
id|NumPorts
suffix:semicolon
singleline_comment|// F08 Number of ports
DECL|member|DescDate
id|__u8
id|DescDate
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// F09 MM/DD/YY when descriptor template was compiler,
singleline_comment|//     so host can track changes to USB-only descriptors.
DECL|member|SerNumLength
id|__u8
id|SerNumLength
suffix:semicolon
singleline_comment|// F0C USB string descriptor len
DECL|member|SerNumDescType
id|__u8
id|SerNumDescType
suffix:semicolon
singleline_comment|// F0D USB descriptor type (=STRING type)
DECL|member|SerialNumber
id|__le16
id|SerialNumber
(braket
id|MAX_SERIALNUMBER_LEN
)braket
suffix:semicolon
singleline_comment|// F0E &quot;01-01-000100&quot; Unicode Serial Number
DECL|member|AssemblyNumLength
id|__u8
id|AssemblyNumLength
suffix:semicolon
singleline_comment|// F26 USB string descriptor len
DECL|member|AssemblyNumDescType
id|__u8
id|AssemblyNumDescType
suffix:semicolon
singleline_comment|// F27 USB descriptor type (=STRING type)
DECL|member|AssemblyNumber
id|__le16
id|AssemblyNumber
(braket
id|MAX_ASSEMBLYNUMBER_LEN
)braket
suffix:semicolon
singleline_comment|// F28 &quot;350-1000-01-A &quot; assembly number
DECL|member|OemAssyNumLength
id|__u8
id|OemAssyNumLength
suffix:semicolon
singleline_comment|// F44 USB string descriptor len
DECL|member|OemAssyNumDescType
id|__u8
id|OemAssyNumDescType
suffix:semicolon
singleline_comment|// F45 USB descriptor type (=STRING type)
DECL|member|OemAssyNumber
id|__le16
id|OemAssyNumber
(braket
id|MAX_ASSEMBLYNUMBER_LEN
)braket
suffix:semicolon
singleline_comment|// F46 &quot;xxxxxxxxxxxxxx&quot; OEM assembly number
DECL|member|ManufDateLength
id|__u8
id|ManufDateLength
suffix:semicolon
singleline_comment|// F62 USB string descriptor len
DECL|member|ManufDateDescType
id|__u8
id|ManufDateDescType
suffix:semicolon
singleline_comment|// F63 USB descriptor type (=STRING type)
DECL|member|ManufDate
id|__le16
id|ManufDate
(braket
l_int|6
)braket
suffix:semicolon
singleline_comment|// F64 &quot;MMDDYY&quot; manufacturing date
DECL|member|Reserved3
id|__u8
id|Reserved3
(braket
l_int|0x4D
)braket
suffix:semicolon
singleline_comment|// F70 -- unused, set to 0 --
DECL|member|UartType
id|__u8
id|UartType
suffix:semicolon
singleline_comment|// FBD Uart Type
DECL|member|IonPid
id|__u8
id|IonPid
suffix:semicolon
singleline_comment|// FBE Product ID, == LSB of USB DevDesc.PID
singleline_comment|//      (Note: Edgeport/4s before 11/98 will have
singleline_comment|//       00 here instead of 01)
DECL|member|IonConfig
id|__u8
id|IonConfig
suffix:semicolon
singleline_comment|// FBF Config byte for ION manufacturing use
singleline_comment|// FBF end of structure, total len = 3C0h
)brace
suffix:semicolon
DECL|macro|MANUF_DESC_VER_1
mdefine_line|#define MANUF_DESC_VER_1&t;1&t;
singleline_comment|// Original definition of MANUF_DESC
DECL|macro|MANUF_DESC_VER_2
mdefine_line|#define MANUF_DESC_VER_2&t;2&t;
singleline_comment|// Ver 2, starts at xC00h len 3C0h
singleline_comment|// Uart Types
singleline_comment|// Note: Since this field was added only recently, all Edgeport/4 units
singleline_comment|// shipped before 11/98 will have 00 in this field. Therefore,
singleline_comment|// both 00 and 01 values mean &squot;654.
DECL|macro|MANUF_UART_EXAR_654_EARLY
mdefine_line|#define MANUF_UART_EXAR_654_EARLY&t;0&t;
singleline_comment|// Exar 16C654 in Edgeport/4s before 11/98
DECL|macro|MANUF_UART_EXAR_654
mdefine_line|#define MANUF_UART_EXAR_654&t;&t;1&t;
singleline_comment|// Exar 16C654
DECL|macro|MANUF_UART_EXAR_2852
mdefine_line|#define MANUF_UART_EXAR_2852&t;&t;2&t;
singleline_comment|// Exar 16C2852
singleline_comment|//
singleline_comment|// Note: The CpuRev and BoardRev values do not conform to manufacturing
singleline_comment|// revisions; they are to be incremented only when the CPU or hardware
singleline_comment|// changes in a software-visible way, such that the 930 software or
singleline_comment|// the host driver needs to handle the hardware differently.
singleline_comment|//
singleline_comment|// Values of bottom 5 bits of CpuRev &amp; BoardRev for
singleline_comment|// Implementation 0 (ie, 930-based)
DECL|macro|MANUF_CPU_REV_AD4
mdefine_line|#define&t;MANUF_CPU_REV_AD4&t;&t;1&t;
singleline_comment|// 930 AD4, with EP1 Rx bug (needs RXSPM)
DECL|macro|MANUF_CPU_REV_AD5
mdefine_line|#define&t;MANUF_CPU_REV_AD5&t;&t;2&t;
singleline_comment|// 930 AD5, with above bug (supposedly) fixed
DECL|macro|MANUF_CPU_80251
mdefine_line|#define&t;MANUF_CPU_80251&t;&t;&t;0x20&t;
singleline_comment|// Intel 80251
DECL|macro|MANUF_BOARD_REV_A
mdefine_line|#define MANUF_BOARD_REV_A&t;&t;1&t;
singleline_comment|// Original version, == Manuf Rev A
DECL|macro|MANUF_BOARD_REV_B
mdefine_line|#define MANUF_BOARD_REV_B&t;&t;2&t;
singleline_comment|// Manuf Rev B, wakeup interrupt works
DECL|macro|MANUF_BOARD_REV_C
mdefine_line|#define MANUF_BOARD_REV_C&t;&t;3&t;
singleline_comment|// Manuf Rev C, 2/4 ports, rs232/rs422
DECL|macro|MANUF_BOARD_REV_GENERATION_2
mdefine_line|#define MANUF_BOARD_REV_GENERATION_2&t;0x20&t;
singleline_comment|// Second generaiton edgeport
singleline_comment|// Values of bottom 5 bits of CpuRev &amp; BoardRev for
singleline_comment|// Implementation 1 (ie, 251+Netchip-based)
DECL|macro|MANUF_CPU_REV_1
mdefine_line|#define&t;MANUF_CPU_REV_1&t;&t;&t;1&t;
singleline_comment|// C251TB Rev 1 (Need actual Intel rev here)
DECL|macro|MANUF_BOARD_REV_A
mdefine_line|#define MANUF_BOARD_REV_A&t;&t;1&t;
singleline_comment|// First rev of 251+Netchip design
DECL|macro|MANUF_SERNUM_LENGTH
mdefine_line|#define&t;MANUF_SERNUM_LENGTH&t;&t;sizeof(((struct edge_manuf_descriptor *)0)-&gt;SerialNumber)
DECL|macro|MANUF_ASSYNUM_LENGTH
mdefine_line|#define&t;MANUF_ASSYNUM_LENGTH&t;&t;sizeof(((struct edge_manuf_descriptor *)0)-&gt;AssemblyNumber)
DECL|macro|MANUF_OEMASSYNUM_LENGTH
mdefine_line|#define&t;MANUF_OEMASSYNUM_LENGTH&t;&t;sizeof(((struct edge_manuf_descriptor *)0)-&gt;OemAssyNumber)
DECL|macro|MANUF_MANUFDATE_LENGTH
mdefine_line|#define&t;MANUF_MANUFDATE_LENGTH&t;&t;sizeof(((struct edge_manuf_descriptor *)0)-&gt;ManufDate)
DECL|macro|MANUF_ION_CONFIG_DIAG_NO_LOOP
mdefine_line|#define&t;MANUF_ION_CONFIG_DIAG_NO_LOOP&t;0x20&t;
singleline_comment|// As below but no ext loopback test
DECL|macro|MANUF_ION_CONFIG_DIAG
mdefine_line|#define&t;MANUF_ION_CONFIG_DIAG&t;&t;0x40&t;
singleline_comment|// 930 based device: 1=Run h/w diags, 0=norm
singleline_comment|// TIUMP Device    : 1=IONSERIAL needs to run Final Test
DECL|macro|MANUF_ION_CONFIG_MASTER
mdefine_line|#define&t;MANUF_ION_CONFIG_MASTER&t;&t;0x80&t;
singleline_comment|// 930 based device:  1=Master mode, 0=Normal
singleline_comment|// TIUMP Device    :  1=First device on a multi TIUMP Device
singleline_comment|//
singleline_comment|// This structure describes parameters for the boot code, and
singleline_comment|// is programmed along with new boot code. These are values
singleline_comment|// which are specific to a given build of the boot code. It
singleline_comment|// is exactly 64 bytes long and is fixed at address FF:xFC0
singleline_comment|// - FF:xFFF. Note that the 930-mandated UCONFIG bytes are
singleline_comment|// included in this structure.
singleline_comment|//
DECL|struct|edge_boot_descriptor
r_struct
id|edge_boot_descriptor
(brace
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
singleline_comment|// C0 Desc length, per USB (= 40h)
DECL|member|DescType
id|__u8
id|DescType
suffix:semicolon
singleline_comment|// C1 Desc type, per USB (= DEVICE type)
DECL|member|DescVer
id|__u8
id|DescVer
suffix:semicolon
singleline_comment|// C2 Desc version/format
DECL|member|Reserved1
id|__u8
id|Reserved1
suffix:semicolon
singleline_comment|// C3 -- unused, set to 0 --
DECL|member|BootCodeLength
id|__le16
id|BootCodeLength
suffix:semicolon
singleline_comment|// C4 Boot code goes from FF:0000 to FF:(len-1)
singleline_comment|//&t;  (LE format)
DECL|member|MajorVersion
id|__u8
id|MajorVersion
suffix:semicolon
singleline_comment|// C6 Firmware version: xx.
DECL|member|MinorVersion
id|__u8
id|MinorVersion
suffix:semicolon
singleline_comment|// C7&t;&t;&t;yy.
DECL|member|BuildNumber
id|__le16
id|BuildNumber
suffix:semicolon
singleline_comment|// C8&t;&t;&t;zzzz (LE format)
DECL|member|EnumRootDescTable
id|__u16
id|EnumRootDescTable
suffix:semicolon
singleline_comment|// CA Root of ROM-based descriptor table
DECL|member|NumDescTypes
id|__u8
id|NumDescTypes
suffix:semicolon
singleline_comment|// CC Number of supported descriptor types
DECL|member|Reserved4
id|__u8
id|Reserved4
suffix:semicolon
singleline_comment|// CD Fix Compiler Packing
DECL|member|Capabilities
id|__le16
id|Capabilities
suffix:semicolon
singleline_comment|// CE-CF Capabilities flags (LE format)
DECL|member|Reserved2
id|__u8
id|Reserved2
(braket
l_int|0x28
)braket
suffix:semicolon
singleline_comment|// D0 -- unused, set to 0 --
DECL|member|UConfig0
id|__u8
id|UConfig0
suffix:semicolon
singleline_comment|// F8 930-defined CPU configuration byte 0
DECL|member|UConfig1
id|__u8
id|UConfig1
suffix:semicolon
singleline_comment|// F9 930-defined CPU configuration byte 1
DECL|member|Reserved3
id|__u8
id|Reserved3
(braket
l_int|6
)braket
suffix:semicolon
singleline_comment|// FA -- unused, set to 0 --
singleline_comment|// FF end of structure, total len = 80
)brace
suffix:semicolon
DECL|macro|BOOT_DESC_VER_1
mdefine_line|#define BOOT_DESC_VER_1&t;&t;1&t;
singleline_comment|// Original definition of BOOT_PARAMS
DECL|macro|BOOT_DESC_VER_2
mdefine_line|#define BOOT_DESC_VER_2&t;&t;2&t;
singleline_comment|// 2nd definition, descriptors not included in boot
singleline_comment|// Capabilities flags
DECL|macro|BOOT_CAP_RESET_CMD
mdefine_line|#define&t;BOOT_CAP_RESET_CMD&t;0x0001&t;
singleline_comment|// If set, boot correctly supports ION_RESET_DEVICE
multiline_comment|/************************************************************************&n;                 T I   U M P   D E F I N I T I O N S&n; ***********************************************************************/
singleline_comment|// Chip definitions in I2C
DECL|macro|UMP5152
mdefine_line|#define UMP5152&t;&t;&t;0x52
DECL|macro|UMP3410
mdefine_line|#define UMP3410&t;&t;&t;0x10
singleline_comment|//************************************************************************
singleline_comment|//&t;TI I2C Format Definitions
singleline_comment|//************************************************************************
DECL|macro|I2C_DESC_TYPE_INFO_BASIC
mdefine_line|#define I2C_DESC_TYPE_INFO_BASIC&t;0x01
DECL|macro|I2C_DESC_TYPE_FIRMWARE_BASIC
mdefine_line|#define I2C_DESC_TYPE_FIRMWARE_BASIC&t;0x02
DECL|macro|I2C_DESC_TYPE_DEVICE
mdefine_line|#define I2C_DESC_TYPE_DEVICE&t;&t;0x03
DECL|macro|I2C_DESC_TYPE_CONFIG
mdefine_line|#define I2C_DESC_TYPE_CONFIG&t;&t;0x04
DECL|macro|I2C_DESC_TYPE_STRING
mdefine_line|#define I2C_DESC_TYPE_STRING&t;&t;0x05
DECL|macro|I2C_DESC_TYPE_FIRMWARE_AUTO
mdefine_line|#define I2C_DESC_TYPE_FIRMWARE_AUTO&t;0x07&t;
singleline_comment|// for 3410 download
DECL|macro|I2C_DESC_TYPE_CONFIG_KLUDGE
mdefine_line|#define I2C_DESC_TYPE_CONFIG_KLUDGE&t;0x14&t;
singleline_comment|// for 3410
DECL|macro|I2C_DESC_TYPE_WATCHPORT_VERSION
mdefine_line|#define I2C_DESC_TYPE_WATCHPORT_VERSION&t;0x15&t;
singleline_comment|// firmware version number for watchport
DECL|macro|I2C_DESC_TYPE_WATCHPORT_CALIBRATION_DATA
mdefine_line|#define I2C_DESC_TYPE_WATCHPORT_CALIBRATION_DATA 0x16&t;
singleline_comment|// Watchport Calibration Data
DECL|macro|I2C_DESC_TYPE_FIRMWARE_BLANK
mdefine_line|#define I2C_DESC_TYPE_FIRMWARE_BLANK&t;0xf2
singleline_comment|// Special section defined by ION
DECL|macro|I2C_DESC_TYPE_ION
mdefine_line|#define I2C_DESC_TYPE_ION&t;&t;0&t;
singleline_comment|// Not defined by TI
DECL|struct|ti_i2c_desc
r_struct
id|ti_i2c_desc
(brace
DECL|member|Type
id|__u8
id|Type
suffix:semicolon
singleline_comment|// Type of descriptor
DECL|member|Size
id|__u16
id|Size
suffix:semicolon
singleline_comment|// Size of data only not including header
DECL|member|CheckSum
id|__u8
id|CheckSum
suffix:semicolon
singleline_comment|// Checksum (8 bit sum of data only)
DECL|member|Data
id|__u8
id|Data
(braket
l_int|0
)braket
suffix:semicolon
singleline_comment|// Data starts here
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
singleline_comment|// for 5152 devices only (type 2 record)
singleline_comment|// for 3410 the version is stored in the WATCHPORT_FIRMWARE_VERSION descriptor
DECL|struct|ti_i2c_firmware_rec
r_struct
id|ti_i2c_firmware_rec
(brace
DECL|member|Ver_Major
id|__u8
id|Ver_Major
suffix:semicolon
singleline_comment|// Firmware Major version number
DECL|member|Ver_Minor
id|__u8
id|Ver_Minor
suffix:semicolon
singleline_comment|// Firmware Minor version number
DECL|member|Data
id|__u8
id|Data
(braket
l_int|0
)braket
suffix:semicolon
singleline_comment|// Download starts here
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|watchport_firmware_version
r_struct
id|watchport_firmware_version
(brace
singleline_comment|// Added 2 bytes for version number
DECL|member|Version_Major
id|__u8
id|Version_Major
suffix:semicolon
singleline_comment|//  Download Version (for Watchport)
DECL|member|Version_Minor
id|__u8
id|Version_Minor
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
singleline_comment|// Structure of header of download image in fw_down.h
DECL|struct|ti_i2c_image_header
r_struct
id|ti_i2c_image_header
(brace
DECL|member|Length
id|__le16
id|Length
suffix:semicolon
DECL|member|CheckSum
id|__u8
id|CheckSum
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ti_basic_descriptor
r_struct
id|ti_basic_descriptor
(brace
DECL|member|Power
id|__u8
id|Power
suffix:semicolon
singleline_comment|// Self powered
singleline_comment|// bit 7: 1 - power switching supported
singleline_comment|//        0 - power switching not supported
singleline_comment|//
singleline_comment|// bit 0: 1 - self powered
singleline_comment|//        0 - bus powered
singleline_comment|//
singleline_comment|//
DECL|member|HubVid
id|__u16
id|HubVid
suffix:semicolon
singleline_comment|// VID HUB
DECL|member|HubPid
id|__u16
id|HubPid
suffix:semicolon
singleline_comment|// PID HUB
DECL|member|DevPid
id|__u16
id|DevPid
suffix:semicolon
singleline_comment|// PID Edgeport
DECL|member|HubTime
id|__u8
id|HubTime
suffix:semicolon
singleline_comment|// Time for power on to power good
DECL|member|HubCurrent
id|__u8
id|HubCurrent
suffix:semicolon
singleline_comment|// HUB Current = 100ma
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
singleline_comment|// CPU / Board Rev Definitions
DECL|macro|TI_CPU_REV_5052
mdefine_line|#define TI_CPU_REV_5052&t;&t;&t;2&t;
singleline_comment|// 5052 based edgeports
DECL|macro|TI_CPU_REV_3410
mdefine_line|#define TI_CPU_REV_3410&t;&t;&t;3&t;
singleline_comment|// 3410 based edgeports
DECL|macro|TI_BOARD_REV_TI_EP
mdefine_line|#define TI_BOARD_REV_TI_EP&t;&t;0&t;
singleline_comment|// Basic ti based edgeport
DECL|macro|TI_BOARD_REV_COMPACT
mdefine_line|#define TI_BOARD_REV_COMPACT&t;&t;1&t;
singleline_comment|// Compact board
DECL|macro|TI_BOARD_REV_WATCHPORT
mdefine_line|#define TI_BOARD_REV_WATCHPORT&t;&t;2&t;
singleline_comment|// Watchport
DECL|macro|TI_GET_CPU_REVISION
mdefine_line|#define TI_GET_CPU_REVISION(x)&t;&t;(__u8)((((x)&gt;&gt;4)&amp;0x0f))
DECL|macro|TI_GET_BOARD_REVISION
mdefine_line|#define TI_GET_BOARD_REVISION(x)&t;(__u8)(((x)&amp;0x0f))
DECL|macro|TI_I2C_SIZE_MASK
mdefine_line|#define TI_I2C_SIZE_MASK&t;&t;0x1f  
singleline_comment|// 5 bits
DECL|macro|TI_GET_I2C_SIZE
mdefine_line|#define TI_GET_I2C_SIZE(x)&t;&t;((((x) &amp; TI_I2C_SIZE_MASK)+1)*256)
DECL|macro|TI_MAX_I2C_SIZE
mdefine_line|#define TI_MAX_I2C_SIZE&t;&t;&t;( 16 * 1024 )
DECL|macro|TI_MANUF_VERSION_0
mdefine_line|#define TI_MANUF_VERSION_0&t;&t;0&t;
singleline_comment|// IonConig2 flags
DECL|macro|TI_CONFIG2_RS232
mdefine_line|#define TI_CONFIG2_RS232&t;&t;0x01
DECL|macro|TI_CONFIG2_RS422
mdefine_line|#define TI_CONFIG2_RS422&t;&t;0x02
DECL|macro|TI_CONFIG2_RS485
mdefine_line|#define TI_CONFIG2_RS485&t;&t;0x04
DECL|macro|TI_CONFIG2_SWITCHABLE
mdefine_line|#define TI_CONFIG2_SWITCHABLE&t;&t;0x08
DECL|macro|TI_CONFIG2_WATCHPORT
mdefine_line|#define TI_CONFIG2_WATCHPORT&t;&t;0x10
DECL|struct|edge_ti_manuf_descriptor
r_struct
id|edge_ti_manuf_descriptor
(brace
DECL|member|IonConfig
id|__u8
id|IonConfig
suffix:semicolon
singleline_comment|//  Config byte for ION manufacturing use
DECL|member|IonConfig2
id|__u8
id|IonConfig2
suffix:semicolon
singleline_comment|//  Expansion
DECL|member|Version
id|__u8
id|Version
suffix:semicolon
singleline_comment|//  Version
DECL|member|CpuRev_BoardRev
id|__u8
id|CpuRev_BoardRev
suffix:semicolon
singleline_comment|//  CPU revision level (0xF0) and Board Rev Level (0x0F)
DECL|member|NumPorts
id|__u8
id|NumPorts
suffix:semicolon
singleline_comment|//  Number of ports&t;for this UMP
DECL|member|NumVirtualPorts
id|__u8
id|NumVirtualPorts
suffix:semicolon
singleline_comment|//  Number of Virtual ports
DECL|member|HubConfig1
id|__u8
id|HubConfig1
suffix:semicolon
singleline_comment|//  Used to configure the Hub
DECL|member|HubConfig2
id|__u8
id|HubConfig2
suffix:semicolon
singleline_comment|//  Used to configure the Hub
DECL|member|TotalPorts
id|__u8
id|TotalPorts
suffix:semicolon
singleline_comment|//  Total Number of Com Ports for the entire device (All UMPs)
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
singleline_comment|//  Reserved
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
singleline_comment|// if !defined(_USBVEND_H)
eof
