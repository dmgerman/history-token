multiline_comment|/*&n; * dvb-dibusb.h&n; *&n; * Copyright (C) 2004 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * for more information see dvb-dibusb.c .&n; */
macro_line|#ifndef __DVB_DIBUSB_H__
DECL|macro|__DVB_DIBUSB_H__
mdefine_line|#define __DVB_DIBUSB_H__
macro_line|#include &quot;dib3000.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|DIBUSB1_1
id|DIBUSB1_1
op_assign
l_int|0
comma
DECL|enumerator|DIBUSB2_0
id|DIBUSB2_0
comma
DECL|enumerator|DIBUSB1_1_AN2235
id|DIBUSB1_1_AN2235
comma
DECL|typedef|dibusb_type
)brace
id|dibusb_type
suffix:semicolon
DECL|variable|dibusb_fw_filenames1_1
r_static
r_const
r_char
op_star
id|dibusb_fw_filenames1_1
(braket
)braket
op_assign
(brace
l_string|&quot;dvb-dibusb-5.0.0.11.fw&quot;
)brace
suffix:semicolon
DECL|variable|dibusb_fw_filenames1_1_an2235
r_static
r_const
r_char
op_star
id|dibusb_fw_filenames1_1_an2235
(braket
)braket
op_assign
(brace
l_string|&quot;dvb-dibusb-an2235-1.fw&quot;
)brace
suffix:semicolon
DECL|variable|dibusb_fw_filenames2_0
r_static
r_const
r_char
op_star
id|dibusb_fw_filenames2_0
(braket
)braket
op_assign
(brace
l_string|&quot;dvb-dibusb-6.0.0.5.fw&quot;
)brace
suffix:semicolon
DECL|struct|dibusb_device_parameter
r_struct
id|dibusb_device_parameter
(brace
DECL|member|type
id|dibusb_type
id|type
suffix:semicolon
DECL|member|demod_addr
id|u8
id|demod_addr
suffix:semicolon
DECL|member|fw_filenames
r_const
r_char
op_star
op_star
id|fw_filenames
suffix:semicolon
DECL|member|usb_controller
r_const
r_char
op_star
id|usb_controller
suffix:semicolon
DECL|member|usb_cpu_csreg
id|u16
id|usb_cpu_csreg
suffix:semicolon
DECL|member|num_urbs
r_int
id|num_urbs
suffix:semicolon
DECL|member|urb_buf_size
r_int
id|urb_buf_size
suffix:semicolon
DECL|member|default_size
r_int
id|default_size
suffix:semicolon
DECL|member|firmware_bug
r_int
id|firmware_bug
suffix:semicolon
DECL|member|cmd_pipe
r_int
id|cmd_pipe
suffix:semicolon
DECL|member|result_pipe
r_int
id|result_pipe
suffix:semicolon
DECL|member|data_pipe
r_int
id|data_pipe
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dibusb_dev_parm
r_static
r_struct
id|dibusb_device_parameter
id|dibusb_dev_parm
(braket
l_int|3
)braket
op_assign
(brace
(brace
dot
id|type
op_assign
id|DIBUSB1_1
comma
dot
id|demod_addr
op_assign
l_int|0x10
comma
dot
id|fw_filenames
op_assign
id|dibusb_fw_filenames1_1
comma
dot
id|usb_controller
op_assign
l_string|&quot;Cypress AN2135&quot;
comma
dot
id|usb_cpu_csreg
op_assign
l_int|0x7f92
comma
dot
id|num_urbs
op_assign
l_int|3
comma
dot
id|urb_buf_size
op_assign
l_int|4096
comma
dot
id|default_size
op_assign
l_int|188
op_star
l_int|21
comma
dot
id|firmware_bug
op_assign
l_int|1
comma
dot
id|cmd_pipe
op_assign
l_int|0x01
comma
dot
id|result_pipe
op_assign
l_int|0x81
comma
dot
id|data_pipe
op_assign
l_int|0x82
comma
)brace
comma
(brace
dot
id|type
op_assign
id|DIBUSB2_0
comma
dot
id|demod_addr
op_assign
l_int|0x10
comma
dot
id|fw_filenames
op_assign
id|dibusb_fw_filenames2_0
comma
dot
id|usb_controller
op_assign
l_string|&quot;Cypress FX2&quot;
comma
dot
id|usb_cpu_csreg
op_assign
l_int|0xe600
comma
dot
id|num_urbs
op_assign
l_int|3
comma
dot
id|urb_buf_size
op_assign
l_int|40960
comma
dot
id|default_size
op_assign
l_int|188
op_star
l_int|210
comma
dot
id|firmware_bug
op_assign
l_int|0
comma
dot
id|cmd_pipe
op_assign
l_int|0x01
comma
dot
id|result_pipe
op_assign
l_int|0x81
comma
dot
id|data_pipe
op_assign
l_int|0x86
comma
)brace
comma
(brace
dot
id|type
op_assign
id|DIBUSB1_1_AN2235
comma
dot
id|demod_addr
op_assign
l_int|0x10
comma
dot
id|fw_filenames
op_assign
id|dibusb_fw_filenames1_1_an2235
comma
dot
id|usb_controller
op_assign
l_string|&quot;Cypress CY7C64613 (AN2235)&quot;
comma
dot
id|usb_cpu_csreg
op_assign
l_int|0x7f92
comma
dot
id|num_urbs
op_assign
l_int|3
comma
dot
id|urb_buf_size
op_assign
l_int|4096
comma
dot
id|default_size
op_assign
l_int|188
op_star
l_int|21
comma
dot
id|firmware_bug
op_assign
l_int|1
comma
dot
id|cmd_pipe
op_assign
l_int|0x01
comma
dot
id|result_pipe
op_assign
l_int|0x81
comma
dot
id|data_pipe
op_assign
l_int|0x82
comma
)brace
)brace
suffix:semicolon
DECL|struct|dibusb_device
r_struct
id|dibusb_device
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|cold_product_id
id|u16
id|cold_product_id
suffix:semicolon
DECL|member|warm_product_id
id|u16
id|warm_product_id
suffix:semicolon
DECL|member|parm
r_struct
id|dibusb_device_parameter
op_star
id|parm
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Vendor IDs */
DECL|macro|USB_VID_ANCHOR
mdefine_line|#define USB_VID_ANCHOR&t;&t;&t;&t;&t;&t;0x0547
DECL|macro|USB_VID_AVERMEDIA
mdefine_line|#define USB_VID_AVERMEDIA&t;&t;&t;&t;&t;0x14aa
DECL|macro|USB_VID_COMPRO
mdefine_line|#define USB_VID_COMPRO&t;&t;&t;&t;&t;&t;0x185b
DECL|macro|USB_VID_DIBCOM
mdefine_line|#define USB_VID_DIBCOM&t;&t;&t;&t;&t;&t;0x10b8
DECL|macro|USB_VID_EMPIA
mdefine_line|#define USB_VID_EMPIA&t;&t;&t;&t;&t;&t;0xeb1a
DECL|macro|USB_VID_GRANDTEC
mdefine_line|#define USB_VID_GRANDTEC&t;&t;&t;&t;&t;0x5032
DECL|macro|USB_VID_HYPER_PALTEK
mdefine_line|#define USB_VID_HYPER_PALTEK&t;&t;&t;&t;0x1025
DECL|macro|USB_VID_IMC_NETWORKS
mdefine_line|#define USB_VID_IMC_NETWORKS&t;&t;&t;&t;0x13d3
DECL|macro|USB_VID_TWINHAN
mdefine_line|#define USB_VID_TWINHAN&t;&t;&t;&t;&t;&t;0x1822
DECL|macro|USB_VID_ULTIMA_ELECTRONIC
mdefine_line|#define USB_VID_ULTIMA_ELECTRONIC&t;&t;&t;0x05d8
multiline_comment|/* Product IDs */
DECL|macro|USB_PID_AVERMEDIA_DVBT_USB_COLD
mdefine_line|#define USB_PID_AVERMEDIA_DVBT_USB_COLD&t;&t;0x0001
DECL|macro|USB_PID_AVERMEDIA_DVBT_USB_WARM
mdefine_line|#define USB_PID_AVERMEDIA_DVBT_USB_WARM&t;&t;0x0002
DECL|macro|USB_PID_COMPRO_DVBU2000_COLD
mdefine_line|#define USB_PID_COMPRO_DVBU2000_COLD&t;&t;0xd000
DECL|macro|USB_PID_COMPRO_DVBU2000_WARM
mdefine_line|#define USB_PID_COMPRO_DVBU2000_WARM&t;&t;0xd001
DECL|macro|USB_PID_DIBCOM_MOD3000_COLD
mdefine_line|#define USB_PID_DIBCOM_MOD3000_COLD&t;&t;&t;0x0bb8
DECL|macro|USB_PID_DIBCOM_MOD3000_WARM
mdefine_line|#define USB_PID_DIBCOM_MOD3000_WARM&t;&t;&t;0x0bb9
DECL|macro|USB_PID_DIBCOM_MOD3001_COLD
mdefine_line|#define USB_PID_DIBCOM_MOD3001_COLD&t;&t;&t;0x0bc6
DECL|macro|USB_PID_DIBCOM_MOD3001_WARM
mdefine_line|#define USB_PID_DIBCOM_MOD3001_WARM&t;&t;&t;0x0bc7
DECL|macro|USB_PID_GRANDTEC_DVBT_USB_COLD
mdefine_line|#define USB_PID_GRANDTEC_DVBT_USB_COLD&t;&t;0x0fa0
DECL|macro|USB_PID_GRANDTEC_DVBT_USB_WARM
mdefine_line|#define USB_PID_GRANDTEC_DVBT_USB_WARM&t;&t;0x0fa1
DECL|macro|USB_PID_KWORLD_VSTREAM_COLD
mdefine_line|#define USB_PID_KWORLD_VSTREAM_COLD&t;&t;&t;0x17de
DECL|macro|USB_PID_KWORLD_VSTREAM_WARM
mdefine_line|#define USB_PID_KWORLD_VSTREAM_WARM&t;&t;&t;0x17df
DECL|macro|USB_PID_TWINHAN_VP7041_COLD
mdefine_line|#define USB_PID_TWINHAN_VP7041_COLD&t;&t;&t;0x3201
DECL|macro|USB_PID_TWINHAN_VP7041_WARM
mdefine_line|#define USB_PID_TWINHAN_VP7041_WARM&t;&t;&t;0x3202
DECL|macro|USB_PID_ULTIMA_TVBOX_COLD
mdefine_line|#define USB_PID_ULTIMA_TVBOX_COLD&t;&t;&t;0x8105
DECL|macro|USB_PID_ULTIMA_TVBOX_WARM
mdefine_line|#define USB_PID_ULTIMA_TVBOX_WARM&t;&t;&t;0x8106
DECL|macro|USB_PID_ULTIMA_TVBOX_AN2235_COLD
mdefine_line|#define USB_PID_ULTIMA_TVBOX_AN2235_COLD&t;0x8107
DECL|macro|USB_PID_ULTIMA_TVBOX_AN2235_WARM
mdefine_line|#define USB_PID_ULTIMA_TVBOX_AN2235_WARM&t;0x8108
DECL|macro|USB_PID_ULTIMA_TVBOX_ANCHOR_COLD
mdefine_line|#define USB_PID_ULTIMA_TVBOX_ANCHOR_COLD&t;0x2235
DECL|macro|USB_PID_UNK_HYPER_PALTEK_COLD
mdefine_line|#define USB_PID_UNK_HYPER_PALTEK_COLD&t;&t;0x005e
DECL|macro|USB_PID_UNK_HYPER_PALTEK_WARM
mdefine_line|#define USB_PID_UNK_HYPER_PALTEK_WARM&t;&t;0x005f
DECL|macro|USB_PID_YAKUMO_DTT200U_COLD
mdefine_line|#define USB_PID_YAKUMO_DTT200U_COLD&t;&t;&t;0x0201
DECL|macro|USB_PID_YAKUMO_DTT200U_WARM
mdefine_line|#define USB_PID_YAKUMO_DTT200U_WARM&t;&t;&t;0x0301
DECL|macro|DIBUSB_SUPPORTED_DEVICES
mdefine_line|#define DIBUSB_SUPPORTED_DEVICES&t;12
multiline_comment|/* USB Driver stuff */
DECL|variable|dibusb_devices
r_static
r_struct
id|dibusb_device
id|dibusb_devices
(braket
id|DIBUSB_SUPPORTED_DEVICES
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;TwinhanDTV USB1.1 / Magic Box / HAMA USB1.1 DVB-T device&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_TWINHAN_VP7041_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_TWINHAN_VP7041_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;KWorld V-Stream XPERT DTV - DVB-T USB1.1&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_KWORLD_VSTREAM_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_KWORLD_VSTREAM_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Grandtec USB1.1 DVB-T/DiBcom USB1.1 DVB-T reference design (MOD3000)&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_DIBCOM_MOD3000_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_DIBCOM_MOD3000_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Artec T1 USB1.1 TVBOX with AN2135&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_ULTIMA_TVBOX_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_ULTIMA_TVBOX_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Artec T1 USB1.1 TVBOX with AN2235&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_ULTIMA_TVBOX_AN2235_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_ULTIMA_TVBOX_AN2235_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|2
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Artec T1 USB1.1 TVBOX with AN2235 (misdesigned)&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_ULTIMA_TVBOX_ANCHOR_COLD
comma
dot
id|warm_product_id
op_assign
l_int|0
comma
multiline_comment|/* undefined, this design becomes USB_PID_DIBCOM_MOD3000_WARM in warm state */
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|2
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Compro Videomate DVB-U2000 - DVB-T USB1.1&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_COMPRO_DVBU2000_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_COMPRO_DVBU2000_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Unkown USB1.1 DVB-T device ???? please report the name to the author&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_UNK_HYPER_PALTEK_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_UNK_HYPER_PALTEK_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;DiBcom USB2.0 DVB-T reference design (MOD3000P)&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_DIBCOM_MOD3001_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_DIBCOM_MOD3001_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|1
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Grandtec DVB-T USB1.1&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_GRANDTEC_DVBT_USB_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_GRANDTEC_DVBT_USB_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Avermedia AverTV DVBT USB1.1&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_AVERMEDIA_DVBT_USB_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_AVERMEDIA_DVBT_USB_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|0
)braket
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Yakumo DVB-T mobile USB2.0&quot;
comma
dot
id|cold_product_id
op_assign
id|USB_PID_YAKUMO_DTT200U_COLD
comma
dot
id|warm_product_id
op_assign
id|USB_PID_YAKUMO_DTT200U_WARM
comma
dot
id|parm
op_assign
op_amp
id|dibusb_dev_parm
(braket
l_int|1
)braket
comma
)brace
)brace
suffix:semicolon
multiline_comment|/* USB Driver stuff */
multiline_comment|/* table of devices that work with this driver */
DECL|variable|dibusb_table
r_static
r_struct
id|usb_device_id
id|dibusb_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_AVERMEDIA
comma
id|USB_PID_AVERMEDIA_DVBT_USB_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_AVERMEDIA
comma
id|USB_PID_AVERMEDIA_DVBT_USB_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_COMPRO
comma
id|USB_PID_COMPRO_DVBU2000_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_COMPRO
comma
id|USB_PID_COMPRO_DVBU2000_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_DIBCOM
comma
id|USB_PID_DIBCOM_MOD3000_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_DIBCOM
comma
id|USB_PID_DIBCOM_MOD3000_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_DIBCOM
comma
id|USB_PID_DIBCOM_MOD3001_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_DIBCOM
comma
id|USB_PID_DIBCOM_MOD3001_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_EMPIA
comma
id|USB_PID_KWORLD_VSTREAM_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_EMPIA
comma
id|USB_PID_KWORLD_VSTREAM_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_GRANDTEC
comma
id|USB_PID_GRANDTEC_DVBT_USB_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_GRANDTEC
comma
id|USB_PID_GRANDTEC_DVBT_USB_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_GRANDTEC
comma
id|USB_PID_DIBCOM_MOD3000_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_GRANDTEC
comma
id|USB_PID_DIBCOM_MOD3000_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_HYPER_PALTEK
comma
id|USB_PID_UNK_HYPER_PALTEK_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_HYPER_PALTEK
comma
id|USB_PID_UNK_HYPER_PALTEK_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_IMC_NETWORKS
comma
id|USB_PID_TWINHAN_VP7041_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_IMC_NETWORKS
comma
id|USB_PID_TWINHAN_VP7041_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_TWINHAN
comma
id|USB_PID_TWINHAN_VP7041_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_TWINHAN
comma
id|USB_PID_TWINHAN_VP7041_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ULTIMA_ELECTRONIC
comma
id|USB_PID_ULTIMA_TVBOX_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ULTIMA_ELECTRONIC
comma
id|USB_PID_ULTIMA_TVBOX_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ULTIMA_ELECTRONIC
comma
id|USB_PID_ULTIMA_TVBOX_AN2235_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ULTIMA_ELECTRONIC
comma
id|USB_PID_ULTIMA_TVBOX_AN2235_WARM
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_AVERMEDIA
comma
id|USB_PID_YAKUMO_DTT200U_COLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_AVERMEDIA
comma
id|USB_PID_YAKUMO_DTT200U_WARM
)paren
)brace
comma
multiline_comment|/*&n; * activate the following define when you have the device and want to compile&n; * build from build-2.6 in dvb-kernel&n; */
singleline_comment|// #define CONFIG_DVB_DIBUSB_MISDESIGNED_AN2235
macro_line|#ifdef CONFIG_DVB_DIBUSB_MISDESIGNED_AN2235
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ANCHOR
comma
id|USB_PID_ULTIMA_TVBOX_ANCHOR_COLD
)paren
)brace
comma
macro_line|#endif
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|dibusb_table
)paren
suffix:semicolon
DECL|macro|DIBUSB_I2C_TIMEOUT
mdefine_line|#define DIBUSB_I2C_TIMEOUT &t;&t;&t;&t;HZ*5
DECL|struct|usb_dibusb
r_struct
id|usb_dibusb
(brace
multiline_comment|/* usb */
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|dibdev
r_struct
id|dibusb_device
op_star
id|dibdev
suffix:semicolon
DECL|member|feedcount
r_int
id|feedcount
suffix:semicolon
DECL|member|xfer_ops
r_struct
id|dib3000_xfer_ops
id|xfer_ops
suffix:semicolon
DECL|member|urb_list
r_struct
id|urb
op_star
op_star
id|urb_list
suffix:semicolon
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
multiline_comment|/* I2C */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|i2c_client
r_struct
id|i2c_client
id|i2c_client
suffix:semicolon
multiline_comment|/* locking */
DECL|member|usb_sem
r_struct
id|semaphore
id|usb_sem
suffix:semicolon
DECL|member|i2c_sem
r_struct
id|semaphore
id|i2c_sem
suffix:semicolon
multiline_comment|/* dvb */
DECL|member|dvb_is_ready
r_int
id|dvb_is_ready
suffix:semicolon
DECL|member|adapter
r_struct
id|dvb_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|dvb_net
r_struct
id|dvb_net
id|dvb_net
suffix:semicolon
DECL|member|fe
r_struct
id|dvb_frontend
op_star
id|fe
suffix:semicolon
multiline_comment|/* remote control */
DECL|member|rc_input_dev
r_struct
id|input_dev
id|rc_input_dev
suffix:semicolon
DECL|member|rc_query_work
r_struct
id|work_struct
id|rc_query_work
suffix:semicolon
DECL|member|rc_input_event
r_int
id|rc_input_event
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* types of first byte of each buffer */
DECL|macro|DIBUSB_REQ_START_READ
mdefine_line|#define DIBUSB_REQ_START_READ&t;&t;&t;0x00
DECL|macro|DIBUSB_REQ_START_DEMOD
mdefine_line|#define DIBUSB_REQ_START_DEMOD&t;&t;&t;0x01
DECL|macro|DIBUSB_REQ_I2C_READ
mdefine_line|#define DIBUSB_REQ_I2C_READ  &t;&t;&t;0x02
DECL|macro|DIBUSB_REQ_I2C_WRITE
mdefine_line|#define DIBUSB_REQ_I2C_WRITE &t;&t;&t;0x03
multiline_comment|/* prefix for reading the current RC key */
DECL|macro|DIBUSB_REQ_POLL_REMOTE
mdefine_line|#define DIBUSB_REQ_POLL_REMOTE&t;&t;&t;0x04
DECL|macro|DIBUSB_RC_NEC_EMPTY
mdefine_line|#define DIBUSB_RC_NEC_EMPTY&t;&t;&t;&t;0x00
DECL|macro|DIBUSB_RC_NEC_KEY_PRESSED
mdefine_line|#define DIBUSB_RC_NEC_KEY_PRESSED&t;&t;0x01
DECL|macro|DIBUSB_RC_NEC_KEY_REPEATED
mdefine_line|#define DIBUSB_RC_NEC_KEY_REPEATED&t;&t;0x02
multiline_comment|/* 0x05 0xXX */
DECL|macro|DIBUSB_REQ_SET_STREAMING_MODE
mdefine_line|#define DIBUSB_REQ_SET_STREAMING_MODE&t;0x05
multiline_comment|/* interrupt the internal read loop, when blocking */
DECL|macro|DIBUSB_REQ_INTR_READ
mdefine_line|#define DIBUSB_REQ_INTR_READ&t;&t;   &t;0x06
multiline_comment|/* IO control&n; * 0x07 &lt;cmd 1 byte&gt; &lt;param 32 bytes&gt;&n; */
DECL|macro|DIBUSB_REQ_SET_IOCTL
mdefine_line|#define DIBUSB_REQ_SET_IOCTL&t;&t;&t;0x07
multiline_comment|/* IOCTL commands */
multiline_comment|/* change the power mode in firmware */
DECL|macro|DIBUSB_IOCTL_CMD_POWER_MODE
mdefine_line|#define DIBUSB_IOCTL_CMD_POWER_MODE&t;&t;0x00
DECL|macro|DIBUSB_IOCTL_POWER_SLEEP
mdefine_line|#define DIBUSB_IOCTL_POWER_SLEEP&t;&t;&t;0x00
DECL|macro|DIBUSB_IOCTL_POWER_WAKEUP
mdefine_line|#define DIBUSB_IOCTL_POWER_WAKEUP&t;&t;&t;0x01
macro_line|#endif
eof
