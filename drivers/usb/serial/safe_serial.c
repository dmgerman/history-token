multiline_comment|/*&n; * Safe Encapsulated USB Serial Driver&n; *&n; *      Copyright (c) 2001 Lineo&n; *      Copyright (c) 2001 Hewlett-Packard&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * By:&n; *      Stuart Lynne &lt;sl@lineo.com&gt;, Tom Rushworth &lt;tbr@lineo.com&gt;&n; */
multiline_comment|/* &n; * The encapsultaion is designed to overcome difficulties with some USB hardware.&n; *&n; * While the USB protocol has a CRC over the data while in transit, i.e. while&n; * being carried over the bus, there is no end to end protection. If the hardware&n; * has any problems getting the data into or out of the USB transmit and receive&n; * FIFO&squot;s then data can be lost. &n; *&n; * This protocol adds a two byte trailer to each USB packet to specify the number&n; * of bytes of valid data and a 10 bit CRC that will allow the receiver to verify&n; * that the entire USB packet was received without error.&n; *&n; * Because in this case the sender and receiver are the class and function drivers&n; * there is now end to end protection.&n; *&n; * There is an additional option that can be used to force all transmitted packets&n; * to be padded to the maximum packet size. This provides a work around for some&n; * devices which have problems with small USB packets.&n; *&n; * Assuming a packetsize of N:&n; *&n; *      0..N-2  data and optional padding&n; *&n; *      N-2     bits 7-2 - number of bytes of valid data&n; *              bits 1-0 top two bits of 10 bit CRC&n; *      N-1     bottom 8 bits of 10 bit CRC&n; *&n; *&n; *      | Data Length       | 10 bit CRC                                |&n; *      + 7 . 6 . 5 . 4 . 3 . 2 . 1 . 0 | 7 . 6 . 5 . 4 . 3 . 2 . 1 . 0 +&n; *&n; * The 10 bit CRC is computed across the sent data, followed by the trailer with&n; * the length set and the CRC set to zero. The CRC is then OR&squot;d into the trailer.&n; *&n; * When received a 10 bit CRC is computed over the entire frame including the trailer&n; * and should be equal to zero.&n; *&n; * Two module parameters are used to control the encapsulation, if both are&n; * turned of the module works as a simple serial device with NO&n; * encapsulation.&n; *&n; * See linux/drivers/usbd/serial_fd for a device function driver&n; * implementation of this.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#ifndef CONFIG_USB_SERIAL_DEBUG
DECL|macro|CONFIG_USB_SERIAL_DEBUG
mdefine_line|#define CONFIG_USB_SERIAL_DEBUG 0
macro_line|#endif
macro_line|#ifndef CONFIG_USB_SAFE_PADDED
DECL|macro|CONFIG_USB_SAFE_PADDED
mdefine_line|#define CONFIG_USB_SAFE_PADDED 0
macro_line|#endif
DECL|variable|debug
r_static
r_int
id|debug
op_assign
id|CONFIG_USB_SERIAL_DEBUG
suffix:semicolon
macro_line|#include &quot;usb-serial.h&quot;&t;&t;
singleline_comment|// must follow the declaration of debug
DECL|variable|safe
r_static
r_int
id|safe
op_assign
l_int|1
suffix:semicolon
DECL|variable|padded
r_static
r_int
id|padded
op_assign
id|CONFIG_USB_SAFE_PADDED
suffix:semicolon
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.0b&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;sl@lineo.com, tbr@lineo.com&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Safe Encapsulated Serial&quot;
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_USBD_SAFE_SERIAL_VENDOR) &amp;&amp; !defined(CONFIG_USBD_SAFE_SERIAL_PRODUCT)
macro_line|#abort &quot;SAFE_SERIAL_VENDOR defined without SAFE_SERIAL_PRODUCT&quot;
macro_line|#endif
macro_line|#if ! defined(CONFIG_USBD_SAFE_SERIAL_VENDOR)
DECL|variable|vendor
r_static
id|__u16
id|vendor
suffix:semicolon
singleline_comment|// no default
DECL|variable|product
r_static
id|__u16
id|product
suffix:semicolon
singleline_comment|// no default
id|MODULE_PARM
(paren
id|vendor
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
(paren
id|product
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|vendor
comma
l_string|&quot;User specified USB idVendor (required)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|product
comma
l_string|&quot;User specified USB idProduct (required)&quot;
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_PARM
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
(paren
id|safe
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
(paren
id|padded
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|debug
comma
l_string|&quot;Debug enabled or not&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|safe
comma
l_string|&quot;Turn Safe Encapsulation On/Off&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|padded
comma
l_string|&quot;Pad to full wMaxPacketSize On/Off&quot;
)paren
suffix:semicolon
DECL|macro|CDC_DEVICE_CLASS
mdefine_line|#define CDC_DEVICE_CLASS                        0x02
DECL|macro|CDC_INTERFACE_CLASS
mdefine_line|#define CDC_INTERFACE_CLASS                     0x02
DECL|macro|CDC_INTERFACE_SUBCLASS
mdefine_line|#define CDC_INTERFACE_SUBCLASS                  0x06
DECL|macro|LINEO_INTERFACE_CLASS
mdefine_line|#define LINEO_INTERFACE_CLASS                   0xff
DECL|macro|LINEO_INTERFACE_SUBCLASS_SAFENET
mdefine_line|#define LINEO_INTERFACE_SUBCLASS_SAFENET        0x01
DECL|macro|LINEO_SAFENET_CRC
mdefine_line|#define LINEO_SAFENET_CRC                       0x01
DECL|macro|LINEO_SAFENET_CRC_PADDED
mdefine_line|#define LINEO_SAFENET_CRC_PADDED                0x02
DECL|macro|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
mdefine_line|#define LINEO_INTERFACE_SUBCLASS_SAFESERIAL     0x02
DECL|macro|LINEO_SAFESERIAL_CRC
mdefine_line|#define LINEO_SAFESERIAL_CRC                    0x01
DECL|macro|LINEO_SAFESERIAL_CRC_PADDED
mdefine_line|#define LINEO_SAFESERIAL_CRC_PADDED             0x02
DECL|macro|MY_USB_DEVICE
mdefine_line|#define MY_USB_DEVICE(vend,prod,dc,ic,isc) &bslash;&n;        match_flags: USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_CLASS | &bslash;&n;                USB_DEVICE_ID_MATCH_INT_CLASS | USB_DEVICE_ID_MATCH_INT_SUBCLASS, &bslash;&n;        idVendor: (vend), &bslash;&n;        idProduct: (prod),&bslash;&n;        bDeviceClass: (dc),&bslash;&n;        bInterfaceClass: (ic), &bslash;&n;        bInterfaceSubClass: (isc),
DECL|variable|id_table
r_static
r_struct
id|usb_device_id
id|id_table
(braket
)braket
op_assign
(brace
(brace
id|MY_USB_DEVICE
(paren
l_int|0x49f
comma
l_int|0xffff
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Itsy
(brace
id|MY_USB_DEVICE
(paren
l_int|0x3f0
comma
l_int|0x2101
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Calypso
(brace
id|MY_USB_DEVICE
(paren
l_int|0x4dd
comma
l_int|0x8001
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Iris 
(brace
id|MY_USB_DEVICE
(paren
l_int|0x4dd
comma
l_int|0x8002
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Collie 
(brace
id|MY_USB_DEVICE
(paren
l_int|0x4dd
comma
l_int|0x8003
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Collie 
(brace
id|MY_USB_DEVICE
(paren
l_int|0x4dd
comma
l_int|0x8004
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Collie 
(brace
id|MY_USB_DEVICE
(paren
l_int|0x5f9
comma
l_int|0xffff
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
singleline_comment|// Sharp tmp
macro_line|#if defined(CONFIG_USB_SAFE_SERIAL_VENDOR)
(brace
id|MY_USB_DEVICE
(paren
id|CONFIG_USB_SAFE_SERIAL_VENDOR
comma
id|CONFIG_USB_SAFE_SERIAL_PRODUCT
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
macro_line|#endif
singleline_comment|// extra null entry for module 
singleline_comment|// vendor/produc parameters
(brace
id|MY_USB_DEVICE
(paren
l_int|0
comma
l_int|0
comma
id|CDC_DEVICE_CLASS
comma
id|LINEO_INTERFACE_CLASS
comma
id|LINEO_INTERFACE_SUBCLASS_SAFESERIAL
)paren
)brace
comma
(brace
)brace
singleline_comment|// terminating entry 
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|id_table
)paren
suffix:semicolon
DECL|variable|safe_driver
r_static
r_struct
id|usb_driver
id|safe_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;safe_serial&quot;
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
id|id_table
comma
)brace
suffix:semicolon
DECL|variable|crc10_table
r_static
id|__u16
id|crc10_table
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x000
comma
l_int|0x233
comma
l_int|0x255
comma
l_int|0x066
comma
l_int|0x299
comma
l_int|0x0aa
comma
l_int|0x0cc
comma
l_int|0x2ff
comma
l_int|0x301
comma
l_int|0x132
comma
l_int|0x154
comma
l_int|0x367
comma
l_int|0x198
comma
l_int|0x3ab
comma
l_int|0x3cd
comma
l_int|0x1fe
comma
l_int|0x031
comma
l_int|0x202
comma
l_int|0x264
comma
l_int|0x057
comma
l_int|0x2a8
comma
l_int|0x09b
comma
l_int|0x0fd
comma
l_int|0x2ce
comma
l_int|0x330
comma
l_int|0x103
comma
l_int|0x165
comma
l_int|0x356
comma
l_int|0x1a9
comma
l_int|0x39a
comma
l_int|0x3fc
comma
l_int|0x1cf
comma
l_int|0x062
comma
l_int|0x251
comma
l_int|0x237
comma
l_int|0x004
comma
l_int|0x2fb
comma
l_int|0x0c8
comma
l_int|0x0ae
comma
l_int|0x29d
comma
l_int|0x363
comma
l_int|0x150
comma
l_int|0x136
comma
l_int|0x305
comma
l_int|0x1fa
comma
l_int|0x3c9
comma
l_int|0x3af
comma
l_int|0x19c
comma
l_int|0x053
comma
l_int|0x260
comma
l_int|0x206
comma
l_int|0x035
comma
l_int|0x2ca
comma
l_int|0x0f9
comma
l_int|0x09f
comma
l_int|0x2ac
comma
l_int|0x352
comma
l_int|0x161
comma
l_int|0x107
comma
l_int|0x334
comma
l_int|0x1cb
comma
l_int|0x3f8
comma
l_int|0x39e
comma
l_int|0x1ad
comma
l_int|0x0c4
comma
l_int|0x2f7
comma
l_int|0x291
comma
l_int|0x0a2
comma
l_int|0x25d
comma
l_int|0x06e
comma
l_int|0x008
comma
l_int|0x23b
comma
l_int|0x3c5
comma
l_int|0x1f6
comma
l_int|0x190
comma
l_int|0x3a3
comma
l_int|0x15c
comma
l_int|0x36f
comma
l_int|0x309
comma
l_int|0x13a
comma
l_int|0x0f5
comma
l_int|0x2c6
comma
l_int|0x2a0
comma
l_int|0x093
comma
l_int|0x26c
comma
l_int|0x05f
comma
l_int|0x039
comma
l_int|0x20a
comma
l_int|0x3f4
comma
l_int|0x1c7
comma
l_int|0x1a1
comma
l_int|0x392
comma
l_int|0x16d
comma
l_int|0x35e
comma
l_int|0x338
comma
l_int|0x10b
comma
l_int|0x0a6
comma
l_int|0x295
comma
l_int|0x2f3
comma
l_int|0x0c0
comma
l_int|0x23f
comma
l_int|0x00c
comma
l_int|0x06a
comma
l_int|0x259
comma
l_int|0x3a7
comma
l_int|0x194
comma
l_int|0x1f2
comma
l_int|0x3c1
comma
l_int|0x13e
comma
l_int|0x30d
comma
l_int|0x36b
comma
l_int|0x158
comma
l_int|0x097
comma
l_int|0x2a4
comma
l_int|0x2c2
comma
l_int|0x0f1
comma
l_int|0x20e
comma
l_int|0x03d
comma
l_int|0x05b
comma
l_int|0x268
comma
l_int|0x396
comma
l_int|0x1a5
comma
l_int|0x1c3
comma
l_int|0x3f0
comma
l_int|0x10f
comma
l_int|0x33c
comma
l_int|0x35a
comma
l_int|0x169
comma
l_int|0x188
comma
l_int|0x3bb
comma
l_int|0x3dd
comma
l_int|0x1ee
comma
l_int|0x311
comma
l_int|0x122
comma
l_int|0x144
comma
l_int|0x377
comma
l_int|0x289
comma
l_int|0x0ba
comma
l_int|0x0dc
comma
l_int|0x2ef
comma
l_int|0x010
comma
l_int|0x223
comma
l_int|0x245
comma
l_int|0x076
comma
l_int|0x1b9
comma
l_int|0x38a
comma
l_int|0x3ec
comma
l_int|0x1df
comma
l_int|0x320
comma
l_int|0x113
comma
l_int|0x175
comma
l_int|0x346
comma
l_int|0x2b8
comma
l_int|0x08b
comma
l_int|0x0ed
comma
l_int|0x2de
comma
l_int|0x021
comma
l_int|0x212
comma
l_int|0x274
comma
l_int|0x047
comma
l_int|0x1ea
comma
l_int|0x3d9
comma
l_int|0x3bf
comma
l_int|0x18c
comma
l_int|0x373
comma
l_int|0x140
comma
l_int|0x126
comma
l_int|0x315
comma
l_int|0x2eb
comma
l_int|0x0d8
comma
l_int|0x0be
comma
l_int|0x28d
comma
l_int|0x072
comma
l_int|0x241
comma
l_int|0x227
comma
l_int|0x014
comma
l_int|0x1db
comma
l_int|0x3e8
comma
l_int|0x38e
comma
l_int|0x1bd
comma
l_int|0x342
comma
l_int|0x171
comma
l_int|0x117
comma
l_int|0x324
comma
l_int|0x2da
comma
l_int|0x0e9
comma
l_int|0x08f
comma
l_int|0x2bc
comma
l_int|0x043
comma
l_int|0x270
comma
l_int|0x216
comma
l_int|0x025
comma
l_int|0x14c
comma
l_int|0x37f
comma
l_int|0x319
comma
l_int|0x12a
comma
l_int|0x3d5
comma
l_int|0x1e6
comma
l_int|0x180
comma
l_int|0x3b3
comma
l_int|0x24d
comma
l_int|0x07e
comma
l_int|0x018
comma
l_int|0x22b
comma
l_int|0x0d4
comma
l_int|0x2e7
comma
l_int|0x281
comma
l_int|0x0b2
comma
l_int|0x17d
comma
l_int|0x34e
comma
l_int|0x328
comma
l_int|0x11b
comma
l_int|0x3e4
comma
l_int|0x1d7
comma
l_int|0x1b1
comma
l_int|0x382
comma
l_int|0x27c
comma
l_int|0x04f
comma
l_int|0x029
comma
l_int|0x21a
comma
l_int|0x0e5
comma
l_int|0x2d6
comma
l_int|0x2b0
comma
l_int|0x083
comma
l_int|0x12e
comma
l_int|0x31d
comma
l_int|0x37b
comma
l_int|0x148
comma
l_int|0x3b7
comma
l_int|0x184
comma
l_int|0x1e2
comma
l_int|0x3d1
comma
l_int|0x22f
comma
l_int|0x01c
comma
l_int|0x07a
comma
l_int|0x249
comma
l_int|0x0b6
comma
l_int|0x285
comma
l_int|0x2e3
comma
l_int|0x0d0
comma
l_int|0x11f
comma
l_int|0x32c
comma
l_int|0x34a
comma
l_int|0x179
comma
l_int|0x386
comma
l_int|0x1b5
comma
l_int|0x1d3
comma
l_int|0x3e0
comma
l_int|0x21e
comma
l_int|0x02d
comma
l_int|0x04b
comma
l_int|0x278
comma
l_int|0x087
comma
l_int|0x2b4
comma
l_int|0x2d2
comma
l_int|0x0e1
comma
)brace
suffix:semicolon
DECL|macro|CRC10_INITFCS
mdefine_line|#define CRC10_INITFCS     0x000&t;
singleline_comment|// Initial FCS value
DECL|macro|CRC10_GOODFCS
mdefine_line|#define CRC10_GOODFCS     0x000&t;
singleline_comment|// Good final FCS value
DECL|macro|CRC10_FCS
mdefine_line|#define CRC10_FCS(fcs, c) ( (((fcs) &lt;&lt; 8) &amp; 0x3ff) ^ crc10_table[((fcs) &gt;&gt; 2) &amp; 0xff] ^ (c))
multiline_comment|/**     &n; * fcs_compute10 - memcpy and calculate 10 bit CRC across buffer&n; * @sp: pointer to buffer&n; * @len: number of bytes&n; * @fcs: starting FCS&n; *&n; * Perform a memcpy and calculate fcs using ppp 10bit CRC algorithm. Return&n; * new 10 bit FCS.&n; */
DECL|function|fcs_compute10
r_static
id|__u16
id|__inline__
id|fcs_compute10
(paren
r_int
r_char
op_star
id|sp
comma
r_int
id|len
comma
id|__u16
id|fcs
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|len
op_decrement
OG
l_int|0
suffix:semicolon
id|fcs
op_assign
id|CRC10_FCS
(paren
id|fcs
comma
op_star
id|sp
op_increment
)paren
)paren
suffix:semicolon
r_return
id|fcs
suffix:semicolon
)brace
DECL|function|safe_read_bulk_callback
r_static
r_void
id|safe_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_serial_port
op_star
id|port
op_assign
(paren
r_struct
id|usb_serial_port
op_star
)paren
id|urb-&gt;context
suffix:semicolon
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|get_usb_serial
(paren
id|port
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
r_char
id|length
op_assign
id|urb-&gt;actual_length
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dbg
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - bad serial pointer, exiting&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - nonzero read bulk status received: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;safe_read_bulk_callback length: %d&quot;
comma
id|port-&gt;read_urb-&gt;actual_length
)paren
suffix:semicolon
macro_line|#ifdef ECHO_RCV
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|cp
op_assign
id|port-&gt;read_urb-&gt;transfer_buffer
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|port-&gt;read_urb-&gt;actual_length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|32
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;nru[%02x] &quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;%02x &quot;
comma
op_star
id|cp
op_increment
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|safe
)paren
(brace
id|__u16
id|fcs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fcs
op_assign
id|fcs_compute10
(paren
id|data
comma
id|length
comma
id|CRC10_INITFCS
)paren
)paren
)paren
(brace
r_int
id|actual_length
op_assign
id|data
(braket
id|length
op_minus
l_int|2
)braket
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|actual_length
op_le
(paren
id|length
op_minus
l_int|2
)paren
)paren
(brace
id|info
(paren
l_string|&quot;%s - actual: %d&quot;
comma
id|__FUNCTION__
comma
id|actual_length
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|actual_length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tty_insert_flip_char
(paren
id|port-&gt;tty
comma
id|data
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tty_flip_buffer_push
(paren
id|port-&gt;tty
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
(paren
l_string|&quot;%s - inconsistant lengths %d:%d&quot;
comma
id|__FUNCTION__
comma
id|actual_length
comma
id|length
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|err
(paren
l_string|&quot;%s - bad CRC %x&quot;
comma
id|__FUNCTION__
comma
id|fcs
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tty_insert_flip_char
(paren
id|port-&gt;tty
comma
id|data
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tty_flip_buffer_push
(paren
id|port-&gt;tty
)paren
suffix:semicolon
)brace
multiline_comment|/* Continue trying to always read  */
id|usb_fill_bulk_urb
(paren
id|urb
comma
id|serial-&gt;dev
comma
id|usb_rcvbulkpipe
(paren
id|serial-&gt;dev
comma
id|port-&gt;bulk_in_endpointAddress
)paren
comma
id|urb-&gt;transfer_buffer
comma
id|urb-&gt;transfer_buffer_length
comma
id|safe_read_bulk_callback
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|usb_submit_urb
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|err
(paren
l_string|&quot;%s - failed resubmitting read urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
)brace
)brace
DECL|function|safe_write
r_static
r_int
id|safe_write
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
(brace
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|packet_length
suffix:semicolon
id|dbg
(paren
l_string|&quot;safe_write port: %p %d urb: %p count: %d&quot;
comma
id|port
comma
id|port-&gt;number
comma
id|port-&gt;write_urb
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;write_urb
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - write urb NULL&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;safe_write write_urb: %d transfer_buffer_length&quot;
comma
id|port-&gt;write_urb-&gt;transfer_buffer_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;write_urb-&gt;transfer_buffer_length
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - write urb transfer_buffer_length zero&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - write request of 0 bytes&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;write_urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - already writing&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|packet_length
op_assign
id|port-&gt;bulk_out_size
suffix:semicolon
singleline_comment|// get max packetsize
id|i
op_assign
id|packet_length
op_minus
(paren
id|safe
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
singleline_comment|// get bytes to send
id|count
op_assign
(paren
id|count
OG
id|i
)paren
ques
c_cond
id|i
suffix:colon
id|count
suffix:semicolon
singleline_comment|// get the data into the transfer buffer
id|data
op_assign
id|port-&gt;write_urb-&gt;transfer_buffer
suffix:semicolon
id|memset
(paren
id|data
comma
l_char|&squot;0&squot;
comma
id|packet_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
(paren
id|data
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|memcpy
(paren
id|data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|safe
)paren
(brace
id|__u16
id|fcs
suffix:semicolon
singleline_comment|// pad if necessary
r_if
c_cond
(paren
op_logical_neg
id|padded
)paren
(brace
id|packet_length
op_assign
id|count
op_plus
l_int|2
suffix:semicolon
)brace
singleline_comment|// set count
id|data
(braket
id|packet_length
op_minus
l_int|2
)braket
op_assign
id|count
op_lshift
l_int|2
suffix:semicolon
id|data
(braket
id|packet_length
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
singleline_comment|// compute fcs and insert into trailer
id|fcs
op_assign
id|fcs_compute10
(paren
id|data
comma
id|packet_length
comma
id|CRC10_INITFCS
)paren
suffix:semicolon
id|data
(braket
id|packet_length
op_minus
l_int|2
)braket
op_or_assign
id|fcs
op_rshift
l_int|8
suffix:semicolon
id|data
(braket
id|packet_length
op_minus
l_int|1
)braket
op_or_assign
id|fcs
op_amp
l_int|0xff
suffix:semicolon
singleline_comment|// set length to send
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
id|packet_length
suffix:semicolon
)brace
r_else
(brace
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
id|count
suffix:semicolon
)brace
id|usb_serial_debug_data
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|count
comma
id|port-&gt;write_urb-&gt;transfer_buffer
)paren
suffix:semicolon
macro_line|#ifdef ECHO_TX
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|cp
op_assign
id|port-&gt;write_urb-&gt;transfer_buffer
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|port-&gt;write_urb-&gt;transfer_buffer_length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|32
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;nsu[%02x] &quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;%02x &quot;
comma
op_star
id|cp
op_increment
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|port-&gt;write_urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;write_urb
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
(paren
l_string|&quot;%s - failed submitting write urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;%s urb: %p submitted&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;write_urb
)paren
suffix:semicolon
r_return
(paren
id|count
)paren
suffix:semicolon
)brace
DECL|function|safe_write_room
r_static
r_int
id|safe_write_room
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_int
id|room
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Default: no room
id|dbg
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;write_urb-&gt;status
op_ne
op_minus
id|EINPROGRESS
)paren
id|room
op_assign
id|port-&gt;bulk_out_size
op_minus
(paren
id|safe
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|room
)paren
(brace
id|dbg
(paren
l_string|&quot;safe_write_room returns %d&quot;
comma
id|room
)paren
suffix:semicolon
)brace
r_return
(paren
id|room
)paren
suffix:semicolon
)brace
DECL|function|safe_startup
r_static
r_int
id|safe_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_switch
c_cond
(paren
id|serial-&gt;interface-&gt;altsetting-&gt;desc.bInterfaceProtocol
)paren
(brace
r_case
id|LINEO_SAFESERIAL_CRC
suffix:colon
r_break
suffix:semicolon
r_case
id|LINEO_SAFESERIAL_CRC_PADDED
suffix:colon
id|padded
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|safe_device
r_static
r_struct
id|usb_serial_device_type
id|safe_device
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
l_string|&quot;Safe&quot;
comma
dot
id|id_table
op_assign
id|id_table
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
id|write
op_assign
id|safe_write
comma
dot
id|write_room
op_assign
id|safe_write_room
comma
dot
id|read_bulk_callback
op_assign
id|safe_read_bulk_callback
comma
dot
id|attach
op_assign
id|safe_startup
comma
)brace
suffix:semicolon
DECL|function|safe_init
r_static
r_int
id|__init
id|safe_init
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|info
(paren
id|DRIVER_VERSION
l_string|&quot; &quot;
id|DRIVER_AUTHOR
)paren
suffix:semicolon
id|info
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|info
(paren
l_string|&quot;vendor: %x product: %x safe: %d padded: %d&bslash;n&quot;
comma
id|vendor
comma
id|product
comma
id|safe
comma
id|padded
)paren
suffix:semicolon
singleline_comment|// if we have vendor / product parameters patch them into id list
r_if
c_cond
(paren
id|vendor
op_logical_or
id|product
)paren
(brace
id|info
(paren
l_string|&quot;vendor: %x product: %x&bslash;n&quot;
comma
id|vendor
comma
id|product
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|id_table
)paren
op_div
r_sizeof
(paren
r_struct
id|usb_device_id
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|id_table
(braket
id|i
)braket
dot
id|idVendor
op_logical_and
op_logical_neg
id|id_table
(braket
id|i
)braket
dot
id|idProduct
)paren
(brace
id|id_table
(braket
id|i
)braket
dot
id|idVendor
op_assign
id|vendor
suffix:semicolon
id|id_table
(braket
id|i
)braket
dot
id|idProduct
op_assign
id|product
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|usb_serial_register
(paren
op_amp
id|safe_device
)paren
suffix:semicolon
id|usb_register
(paren
op_amp
id|safe_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|safe_exit
r_static
r_void
id|__exit
id|safe_exit
(paren
r_void
)paren
(brace
id|usb_deregister
(paren
op_amp
id|safe_driver
)paren
suffix:semicolon
id|usb_serial_deregister
(paren
op_amp
id|safe_device
)paren
suffix:semicolon
)brace
DECL|variable|safe_init
id|module_init
(paren
id|safe_init
)paren
suffix:semicolon
DECL|variable|safe_exit
id|module_exit
(paren
id|safe_exit
)paren
suffix:semicolon
eof
