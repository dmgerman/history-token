multiline_comment|/*&n;  Keyspan USB to Serial Converter driver&n; &n;  (C) Copyright (C) 2000-2001&n;      Hugh Blemings &lt;hugh@blemings.org&gt;&n;   &n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2 of the License, or&n;  (at your option) any later version.&n;&n;  See http://misc.nu/hugh/keyspan.html for more information.&n;  &n;  Code in this driver inspired by and in a number of places taken&n;  from Brian Warner&squot;s original Keyspan-PDA driver.&n;&n;  This driver has been put together with the support of Innosys, Inc.&n;  and Keyspan, Inc the manufacturers of the Keyspan USB-serial products.&n;  Thanks Guys :)&n;  &n;  Thanks to Paulus for miscellaneous tidy ups, some largish chunks&n;  of much nicer and/or completely new code and (perhaps most uniquely)&n;  having the patience to sit down and explain why and where he&squot;d changed&n;  stuff.&n;&n;  Tip &squot;o the hat to IBM (and previously Linuxcare :) for supporting &n;  staff in their work on open source projects.&n;  &n;  See keyspan.c for update history.&n;&n;*/
macro_line|#ifndef __LINUX_USB_SERIAL_KEYSPAN_H
DECL|macro|__LINUX_USB_SERIAL_KEYSPAN_H
mdefine_line|#define __LINUX_USB_SERIAL_KEYSPAN_H
multiline_comment|/* Function prototypes for Keyspan serial converter */
r_static
r_int
id|keyspan_open
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_void
id|keyspan_close
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_int
id|keyspan_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|keyspan_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|keyspan_rx_throttle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|keyspan_rx_unthrottle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|keyspan_write_room
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|keyspan_write
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|keyspan_send_setup
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|reset_port
)paren
suffix:semicolon
r_static
r_int
id|keyspan_chars_in_buffer
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|keyspan_ioctl
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_void
id|keyspan_set_termios
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|termios
op_star
id|old
)paren
suffix:semicolon
r_static
r_void
id|keyspan_break_ctl
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|break_state
)paren
suffix:semicolon
r_static
r_int
id|keyspan_fake_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_int
id|keyspan_usa19_calc_baud
(paren
id|u32
id|baud_rate
comma
id|u32
id|baudclk
comma
id|u8
op_star
id|rate_hi
comma
id|u8
op_star
id|rate_low
comma
id|u8
op_star
id|prescaler
comma
r_int
id|portnum
)paren
suffix:semicolon
r_static
r_int
id|keyspan_usa19w_calc_baud
(paren
id|u32
id|baud_rate
comma
id|u32
id|baudclk
comma
id|u8
op_star
id|rate_hi
comma
id|u8
op_star
id|rate_low
comma
id|u8
op_star
id|prescaler
comma
r_int
id|portnum
)paren
suffix:semicolon
r_static
r_int
id|keyspan_usa28_calc_baud
(paren
id|u32
id|baud_rate
comma
id|u32
id|baudclk
comma
id|u8
op_star
id|rate_hi
comma
id|u8
op_star
id|rate_low
comma
id|u8
op_star
id|prescaler
comma
r_int
id|portnum
)paren
suffix:semicolon
r_static
r_int
id|keyspan_usa28_send_setup
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|reset_port
)paren
suffix:semicolon
r_static
r_int
id|keyspan_usa26_send_setup
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|reset_port
)paren
suffix:semicolon
r_static
r_int
id|keyspan_usa49_send_setup
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|reset_port
)paren
suffix:semicolon
multiline_comment|/* Struct used for firmware - increased size of data section&n;   to allow Keyspan&squot;s &squot;C&squot; firmware struct to be used unmodified */
DECL|struct|ezusb_hex_record
r_struct
id|ezusb_hex_record
(brace
DECL|member|address
id|__u16
id|address
suffix:semicolon
DECL|member|data_size
id|__u8
id|data_size
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Conditionally include firmware images, if they aren&squot;t&n;   included create a null pointer instead.  Current &n;   firmware images aren&squot;t optimised to remove duplicate&n;   addresses in the image itself. */
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA28
macro_line|#include &quot;keyspan_usa28_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa28_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa28_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA28X
macro_line|#include &quot;keyspan_usa28x_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa28x_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa28x_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA28XA
macro_line|#include &quot;keyspan_usa28xa_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa28xa_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa28xa_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA28XB
macro_line|#include &quot;keyspan_usa28xb_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa28xb_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa28xb_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA19
macro_line|#include &quot;keyspan_usa19_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa19_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa19_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA19QI
macro_line|#include &quot;keyspan_usa19qi_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa19qi_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa19qi_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_MPR
macro_line|#include &quot;keyspan_mpr_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_mpr_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_mpr_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA19QW
macro_line|#include &quot;keyspan_usa19qw_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa19qw_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa19qw_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA18X
macro_line|#include &quot;keyspan_usa18x_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa18x_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa18x_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA19W
macro_line|#include &quot;keyspan_usa19w_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa19w_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa19w_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA49W
macro_line|#include &quot;keyspan_usa49w_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa49w_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa49w_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_SERIAL_KEYSPAN_USA49WLC
macro_line|#include &quot;keyspan_usa49wlc_fw.h&quot;
macro_line|#else
DECL|variable|keyspan_usa49wlc_firmware
r_static
r_const
r_struct
id|ezusb_hex_record
op_star
id|keyspan_usa49wlc_firmware
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
multiline_comment|/* Values used for baud rate calculation - device specific */
DECL|macro|KEYSPAN_INVALID_BAUD_RATE
mdefine_line|#define&t;KEYSPAN_INVALID_BAUD_RATE&t;&t;(-1)
DECL|macro|KEYSPAN_BAUD_RATE_OK
mdefine_line|#define&t;KEYSPAN_BAUD_RATE_OK&t;&t;&t;(0)
DECL|macro|KEYSPAN_USA18X_BAUDCLK
mdefine_line|#define&t;KEYSPAN_USA18X_BAUDCLK&t;&t;&t;(12000000L)&t;/* a guess */
DECL|macro|KEYSPAN_USA19_BAUDCLK
mdefine_line|#define&t;KEYSPAN_USA19_BAUDCLK&t;&t;&t;(12000000L)
DECL|macro|KEYSPAN_USA19W_BAUDCLK
mdefine_line|#define&t;KEYSPAN_USA19W_BAUDCLK&t;&t;&t;(24000000L)
DECL|macro|KEYSPAN_USA28_BAUDCLK
mdefine_line|#define&t;KEYSPAN_USA28_BAUDCLK&t;&t;&t;(1843200L)
DECL|macro|KEYSPAN_USA28X_BAUDCLK
mdefine_line|#define&t;KEYSPAN_USA28X_BAUDCLK&t;&t;&t;(12000000L)
DECL|macro|KEYSPAN_USA49W_BAUDCLK
mdefine_line|#define&t;KEYSPAN_USA49W_BAUDCLK&t;&t;&t;(48000000L)
multiline_comment|/* Some constants used to characterise each device.  */
DECL|macro|KEYSPAN_MAX_NUM_PORTS
mdefine_line|#define&t;&t;KEYSPAN_MAX_NUM_PORTS&t;&t;(4)
DECL|macro|KEYSPAN_MAX_FLIPS
mdefine_line|#define&t;&t;KEYSPAN_MAX_FLIPS&t;&t;(2)
multiline_comment|/* Device info for the Keyspan serial converter, used&n;   by the overall usb-serial probe function */
DECL|macro|KEYSPAN_VENDOR_ID
mdefine_line|#define KEYSPAN_VENDOR_ID&t;&t;&t;(0x06cd)
multiline_comment|/* Product IDs for the products supported, pre-renumeration */
DECL|macro|keyspan_usa18x_pre_product_id
mdefine_line|#define&t;keyspan_usa18x_pre_product_id&t;&t;0x0105
DECL|macro|keyspan_usa19_pre_product_id
mdefine_line|#define&t;keyspan_usa19_pre_product_id&t;&t;0x0103
DECL|macro|keyspan_usa19qi_pre_product_id
mdefine_line|#define&t;keyspan_usa19qi_pre_product_id&t;&t;0x010b
DECL|macro|keyspan_mpr_pre_product_id
mdefine_line|#define&t;keyspan_mpr_pre_product_id&t;&t;0x011b
DECL|macro|keyspan_usa19qw_pre_product_id
mdefine_line|#define&t;keyspan_usa19qw_pre_product_id&t;&t;0x0118
DECL|macro|keyspan_usa19w_pre_product_id
mdefine_line|#define&t;keyspan_usa19w_pre_product_id&t;&t;0x0106
DECL|macro|keyspan_usa28_pre_product_id
mdefine_line|#define&t;keyspan_usa28_pre_product_id&t;&t;0x0101
DECL|macro|keyspan_usa28x_pre_product_id
mdefine_line|#define&t;keyspan_usa28x_pre_product_id&t;&t;0x0102
DECL|macro|keyspan_usa28xa_pre_product_id
mdefine_line|#define&t;keyspan_usa28xa_pre_product_id&t;&t;0x0114
DECL|macro|keyspan_usa28xb_pre_product_id
mdefine_line|#define&t;keyspan_usa28xb_pre_product_id&t;&t;0x0113
DECL|macro|keyspan_usa49w_pre_product_id
mdefine_line|#define&t;keyspan_usa49w_pre_product_id&t;&t;0x0109
DECL|macro|keyspan_usa49wlc_pre_product_id
mdefine_line|#define&t;keyspan_usa49wlc_pre_product_id&t;&t;0x011a
multiline_comment|/* Product IDs post-renumeration.  Note that the 28x and 28xb&n;   have the same id&squot;s post-renumeration but behave identically&n;   so it&squot;s not an issue. */
DECL|macro|keyspan_usa18x_product_id
mdefine_line|#define&t;keyspan_usa18x_product_id&t;&t;0x0112
DECL|macro|keyspan_usa19_product_id
mdefine_line|#define&t;keyspan_usa19_product_id&t;&t;0x0107
DECL|macro|keyspan_usa19qi_product_id
mdefine_line|#define&t;keyspan_usa19qi_product_id&t;&t;0x010c
DECL|macro|keyspan_mpr_product_id
mdefine_line|#define&t;keyspan_mpr_product_id&t;&t;&t;0x011c
DECL|macro|keyspan_usa19qw_product_id
mdefine_line|#define&t;keyspan_usa19qw_product_id&t;&t;0x0119
DECL|macro|keyspan_usa19w_product_id
mdefine_line|#define&t;keyspan_usa19w_product_id&t;&t;0x0108
DECL|macro|keyspan_usa28_product_id
mdefine_line|#define&t;keyspan_usa28_product_id&t;&t;0x010f
DECL|macro|keyspan_usa28x_product_id
mdefine_line|#define&t;keyspan_usa28x_product_id&t;&t;0x0110
DECL|macro|keyspan_usa28xa_product_id
mdefine_line|#define&t;keyspan_usa28xa_product_id&t;&t;0x0115
DECL|macro|keyspan_usa28xb_product_id
mdefine_line|#define&t;keyspan_usa28xb_product_id&t;&t;0x0110
DECL|macro|keyspan_usa49w_product_id
mdefine_line|#define&t;keyspan_usa49w_product_id&t;&t;0x010a
DECL|macro|keyspan_usa49wlc_product_id
mdefine_line|#define&t;keyspan_usa49wlc_product_id&t;&t;0x012a
DECL|struct|keyspan_device_details
r_struct
id|keyspan_device_details
(brace
multiline_comment|/* product ID value */
DECL|member|product_id
r_int
id|product_id
suffix:semicolon
DECL|enumerator|msg_usa26
DECL|enumerator|msg_usa28
DECL|enumerator|msg_usa49
DECL|member|msg_format
r_enum
(brace
id|msg_usa26
comma
id|msg_usa28
comma
id|msg_usa49
)brace
id|msg_format
suffix:semicolon
multiline_comment|/* Number of physical ports */
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
multiline_comment|/* 1 if endpoint flipping used on input, 0 if not */
DECL|member|indat_endp_flip
r_int
id|indat_endp_flip
suffix:semicolon
multiline_comment|/* 1 if endpoint flipping used on output, 0 if not */
DECL|member|outdat_endp_flip
r_int
id|outdat_endp_flip
suffix:semicolon
multiline_comment|/* Table mapping input data endpoint IDs to physical&n;&t;&t;   port number and flip if used */
DECL|member|indat_endpoints
r_int
id|indat_endpoints
(braket
id|KEYSPAN_MAX_NUM_PORTS
)braket
suffix:semicolon
multiline_comment|/* Same for output endpoints */
DECL|member|outdat_endpoints
r_int
id|outdat_endpoints
(braket
id|KEYSPAN_MAX_NUM_PORTS
)braket
suffix:semicolon
multiline_comment|/* Input acknowledge endpoints */
DECL|member|inack_endpoints
r_int
id|inack_endpoints
(braket
id|KEYSPAN_MAX_NUM_PORTS
)braket
suffix:semicolon
multiline_comment|/* Output control endpoints */
DECL|member|outcont_endpoints
r_int
id|outcont_endpoints
(braket
id|KEYSPAN_MAX_NUM_PORTS
)braket
suffix:semicolon
multiline_comment|/* Endpoint used for input status */
DECL|member|instat_endpoint
r_int
id|instat_endpoint
suffix:semicolon
multiline_comment|/* Endpoint used for global control functions */
DECL|member|glocont_endpoint
r_int
id|glocont_endpoint
suffix:semicolon
DECL|member|calculate_baud_rate
r_int
(paren
op_star
id|calculate_baud_rate
)paren
(paren
id|u32
id|baud_rate
comma
id|u32
id|baudclk
comma
id|u8
op_star
id|rate_hi
comma
id|u8
op_star
id|rate_low
comma
id|u8
op_star
id|prescaler
comma
r_int
id|portnum
)paren
suffix:semicolon
DECL|member|baudclk
id|u32
id|baudclk
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Now for each device type we setup the device detail&n;   structure with the appropriate information (provided&n;   in Keyspan&squot;s documentation) */
DECL|variable|usa18x_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa18x_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa18x_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa26
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|indat_endp_flip
op_assign
l_int|0
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x85
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x05
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19w_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA18X_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa19_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa19_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa19_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa28
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|indat_endp_flip
op_assign
l_int|1
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x83
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x03
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x84
comma
dot
id|glocont_endpoint
op_assign
op_minus
l_int|1
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA19_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa19qi_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa19qi_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa19qi_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa28
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|indat_endp_flip
op_assign
l_int|1
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x83
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x03
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x84
comma
dot
id|glocont_endpoint
op_assign
op_minus
l_int|1
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa28_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA19_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa19qw_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa19qw_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa19qw_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa26
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|indat_endp_flip
op_assign
l_int|0
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x85
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x05
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19w_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA19W_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa19w_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa19w_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa19w_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa26
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|indat_endp_flip
op_assign
l_int|0
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x85
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x05
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19w_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA19W_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa28_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa28_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa28_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa28
comma
dot
id|num_ports
op_assign
l_int|2
comma
dot
id|indat_endp_flip
op_assign
l_int|1
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
comma
l_int|0x83
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
comma
l_int|0x03
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x85
comma
l_int|0x86
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x05
comma
l_int|0x06
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa28_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA28_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa28x_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa28x_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa28x_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa26
comma
dot
id|num_ports
op_assign
l_int|2
comma
dot
id|indat_endp_flip
op_assign
l_int|0
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
comma
l_int|0x83
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
comma
l_int|0x03
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x85
comma
l_int|0x86
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x05
comma
l_int|0x06
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19w_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA28X_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa28xa_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa28xa_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa28xa_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa26
comma
dot
id|num_ports
op_assign
l_int|2
comma
dot
id|indat_endp_flip
op_assign
l_int|0
comma
dot
id|outdat_endp_flip
op_assign
l_int|1
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
comma
l_int|0x83
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
comma
l_int|0x03
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
l_int|0x85
comma
l_int|0x86
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
l_int|0x05
comma
l_int|0x06
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19w_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA28X_BAUDCLK
comma
)brace
suffix:semicolon
multiline_comment|/* We don&squot;t need a separate entry for the usa28xb as it appears as a 28x anyway */
DECL|variable|usa49w_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa49w_device_details
op_assign
(brace
dot
id|product_id
op_assign
id|keyspan_usa49w_product_id
comma
dot
id|msg_format
op_assign
id|msg_usa49
comma
dot
id|num_ports
op_assign
l_int|4
comma
dot
id|indat_endp_flip
op_assign
l_int|0
comma
dot
id|outdat_endp_flip
op_assign
l_int|0
comma
dot
id|indat_endpoints
op_assign
(brace
l_int|0x81
comma
l_int|0x82
comma
l_int|0x83
comma
l_int|0x84
)brace
comma
dot
id|outdat_endpoints
op_assign
(brace
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
)brace
comma
dot
id|inack_endpoints
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
dot
id|outcont_endpoints
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
dot
id|instat_endpoint
op_assign
l_int|0x87
comma
dot
id|glocont_endpoint
op_assign
l_int|0x07
comma
dot
id|calculate_baud_rate
op_assign
id|keyspan_usa19w_calc_baud
comma
dot
id|baudclk
op_assign
id|KEYSPAN_USA49W_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|usa49wlc_device_details
r_static
r_const
r_struct
id|keyspan_device_details
id|usa49wlc_device_details
op_assign
(brace
id|product_id
suffix:colon
id|keyspan_usa49wlc_product_id
comma
id|msg_format
suffix:colon
id|msg_usa49
comma
id|num_ports
suffix:colon
l_int|4
comma
id|indat_endp_flip
suffix:colon
l_int|0
comma
id|outdat_endp_flip
suffix:colon
l_int|0
comma
id|indat_endpoints
suffix:colon
(brace
l_int|0x81
comma
l_int|0x82
comma
l_int|0x83
comma
l_int|0x84
)brace
comma
id|outdat_endpoints
suffix:colon
(brace
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
)brace
comma
id|inack_endpoints
suffix:colon
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
id|outcont_endpoints
suffix:colon
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
id|instat_endpoint
suffix:colon
l_int|0x87
comma
id|glocont_endpoint
suffix:colon
l_int|0x07
comma
id|calculate_baud_rate
suffix:colon
id|keyspan_usa19w_calc_baud
comma
id|baudclk
suffix:colon
id|KEYSPAN_USA19W_BAUDCLK
comma
)brace
suffix:semicolon
DECL|variable|keyspan_devices
r_static
r_const
r_struct
id|keyspan_device_details
op_star
id|keyspan_devices
(braket
)braket
op_assign
(brace
op_amp
id|usa18x_device_details
comma
op_amp
id|usa19_device_details
comma
op_amp
id|usa19qi_device_details
comma
op_amp
id|usa19qw_device_details
comma
op_amp
id|usa19w_device_details
comma
op_amp
id|usa28_device_details
comma
op_amp
id|usa28x_device_details
comma
op_amp
id|usa28xa_device_details
comma
multiline_comment|/* 28xb not required as it renumerates as a 28x */
op_amp
id|usa49w_device_details
comma
op_amp
id|usa49wlc_device_details
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|keyspan_ids_combined
r_static
r_struct
id|usb_device_id
id|keyspan_ids_combined
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa18x_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19w_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qi_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qw_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_mpr_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28x_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xa_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xb_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49w_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49wlc_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa18x_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19w_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qi_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qw_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_mpr_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28x_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xa_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xb_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49w_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49wlc_product_id
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|keyspan_ids_combined
)paren
suffix:semicolon
DECL|variable|keyspan_driver
r_static
r_struct
id|usb_driver
id|keyspan_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;keyspan&quot;
comma
dot
id|probe
op_assign
id|usb_serial_probe
comma
dot
id|disconnect
op_assign
id|usb_serial_disconnect
comma
dot
id|id_table
op_assign
id|keyspan_ids_combined
comma
)brace
suffix:semicolon
multiline_comment|/* usb_device_id table for the pre-firmware download keyspan devices */
DECL|variable|keyspan_pre_ids
r_static
r_struct
id|usb_device_id
id|keyspan_pre_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa18x_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qi_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qw_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19w_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_mpr_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28x_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xa_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xb_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49w_pre_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49wlc_pre_product_id
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
DECL|variable|keyspan_1port_ids
r_static
r_struct
id|usb_device_id
id|keyspan_1port_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa18x_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qi_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19qw_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa19w_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_mpr_pre_product_id
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
DECL|variable|keyspan_2port_ids
r_static
r_struct
id|usb_device_id
id|keyspan_2port_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28x_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xa_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa28xb_product_id
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
DECL|variable|keyspan_4port_ids
r_static
r_struct
id|usb_device_id
id|keyspan_4port_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49w_product_id
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|KEYSPAN_VENDOR_ID
comma
id|keyspan_usa49wlc_product_id
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
multiline_comment|/* Structs for the devices, pre and post renumeration. */
DECL|variable|keyspan_pre_device
r_static
r_struct
id|usb_serial_device_type
id|keyspan_pre_device
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Keyspan - (without firmware)&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;keyspan_no_firm&quot;
comma
dot
id|id_table
op_assign
id|keyspan_pre_ids
comma
dot
id|num_interrupt_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_out
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|attach
op_assign
id|keyspan_fake_startup
comma
)brace
suffix:semicolon
DECL|variable|keyspan_1port_device
r_static
r_struct
id|usb_serial_device_type
id|keyspan_1port_device
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Keyspan 1 port adapter&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;keyspan_1&quot;
comma
dot
id|id_table
op_assign
id|keyspan_1port_ids
comma
dot
id|num_interrupt_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_in
op_assign
l_int|3
comma
dot
id|num_bulk_out
op_assign
l_int|4
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|open
op_assign
id|keyspan_open
comma
dot
id|close
op_assign
id|keyspan_close
comma
dot
id|write
op_assign
id|keyspan_write
comma
dot
id|write_room
op_assign
id|keyspan_write_room
comma
dot
id|chars_in_buffer
op_assign
id|keyspan_chars_in_buffer
comma
dot
id|throttle
op_assign
id|keyspan_rx_throttle
comma
dot
id|unthrottle
op_assign
id|keyspan_rx_unthrottle
comma
dot
id|ioctl
op_assign
id|keyspan_ioctl
comma
dot
id|set_termios
op_assign
id|keyspan_set_termios
comma
dot
id|break_ctl
op_assign
id|keyspan_break_ctl
comma
dot
id|attach
op_assign
id|keyspan_startup
comma
dot
id|shutdown
op_assign
id|keyspan_shutdown
comma
)brace
suffix:semicolon
DECL|variable|keyspan_2port_device
r_static
r_struct
id|usb_serial_device_type
id|keyspan_2port_device
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Keyspan 2 port adapter&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;keyspan_2&quot;
comma
dot
id|id_table
op_assign
id|keyspan_2port_ids
comma
dot
id|num_interrupt_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_out
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_ports
op_assign
l_int|2
comma
dot
id|open
op_assign
id|keyspan_open
comma
dot
id|close
op_assign
id|keyspan_close
comma
dot
id|write
op_assign
id|keyspan_write
comma
dot
id|write_room
op_assign
id|keyspan_write_room
comma
dot
id|chars_in_buffer
op_assign
id|keyspan_chars_in_buffer
comma
dot
id|throttle
op_assign
id|keyspan_rx_throttle
comma
dot
id|unthrottle
op_assign
id|keyspan_rx_unthrottle
comma
dot
id|ioctl
op_assign
id|keyspan_ioctl
comma
dot
id|set_termios
op_assign
id|keyspan_set_termios
comma
dot
id|break_ctl
op_assign
id|keyspan_break_ctl
comma
dot
id|attach
op_assign
id|keyspan_startup
comma
dot
id|shutdown
op_assign
id|keyspan_shutdown
comma
)brace
suffix:semicolon
DECL|variable|keyspan_4port_device
r_static
r_struct
id|usb_serial_device_type
id|keyspan_4port_device
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Keyspan 4 port adapter&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;keyspan_4&quot;
comma
dot
id|id_table
op_assign
id|keyspan_4port_ids
comma
dot
id|num_interrupt_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_in
op_assign
l_int|5
comma
dot
id|num_bulk_out
op_assign
l_int|5
comma
dot
id|num_ports
op_assign
l_int|4
comma
dot
id|open
op_assign
id|keyspan_open
comma
dot
id|close
op_assign
id|keyspan_close
comma
dot
id|write
op_assign
id|keyspan_write
comma
dot
id|write_room
op_assign
id|keyspan_write_room
comma
dot
id|chars_in_buffer
op_assign
id|keyspan_chars_in_buffer
comma
dot
id|throttle
op_assign
id|keyspan_rx_throttle
comma
dot
id|unthrottle
op_assign
id|keyspan_rx_unthrottle
comma
dot
id|ioctl
op_assign
id|keyspan_ioctl
comma
dot
id|set_termios
op_assign
id|keyspan_set_termios
comma
dot
id|break_ctl
op_assign
id|keyspan_break_ctl
comma
dot
id|attach
op_assign
id|keyspan_startup
comma
dot
id|shutdown
op_assign
id|keyspan_shutdown
comma
)brace
suffix:semicolon
macro_line|#endif
eof
