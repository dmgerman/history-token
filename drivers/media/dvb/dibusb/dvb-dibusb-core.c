multiline_comment|/*&n; * Driver for mobile USB Budget DVB-T devices based on reference &n; * design made by DiBcom (http://www.dibcom.fr/)&n; * &n; * dvb-dibusb-core.c&n; * &n; * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)&n; * &n; * based on GPL code from DiBcom, which has&n; * Copyright (C) 2004 Amaury Demol for DiBcom (ademol@dibcom.fr)&n; *&n; * Remote control code added by David Matthews (dm@prolingua.co.uk)&n; * &n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * Acknowledgements&n; * &n; *  Amaury Demol (ademol@dibcom.fr) from DiBcom for providing specs and driver&n; *  sources, on which this driver (and the dib3000mb/mc/p frontends) are based.&n; * &n; * see Documentation/dvb/README.dibusb for more information&n; */
macro_line|#include &quot;dvb-dibusb.h&quot;
macro_line|#include &lt;linux/moduleparam.h&gt;
multiline_comment|/* debug */
macro_line|#ifdef CONFIG_DVB_DIBCOM_DEBUG
DECL|variable|debug
r_int
id|debug
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;set debugging level (1=info,2=xfer,4=alotmore,8=ts,16=err,32=rc (|-able)).&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|pid_parse
r_int
id|pid_parse
suffix:semicolon
id|module_param
c_func
(paren
id|pid_parse
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|pid_parse
comma
l_string|&quot;enable pid parsing (filtering) when running at USB2.0&quot;
)paren
suffix:semicolon
DECL|variable|rc_query_interval
r_int
id|rc_query_interval
suffix:semicolon
id|module_param
c_func
(paren
id|rc_query_interval
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rc_query_interval
comma
l_string|&quot;interval in msecs for remote control query (default: 100; min: 40)&quot;
)paren
suffix:semicolon
multiline_comment|/* Vendor IDs */
DECL|macro|USB_VID_ANCHOR
mdefine_line|#define USB_VID_ANCHOR&t;&t;&t;&t;&t;&t;0x0547
DECL|macro|USB_VID_AVERMEDIA
mdefine_line|#define USB_VID_AVERMEDIA&t;&t;&t;&t;&t;0x14aa
DECL|macro|USB_VID_COMPRO
mdefine_line|#define USB_VID_COMPRO&t;&t;&t;&t;&t;&t;0x185b
DECL|macro|USB_VID_COMPRO_UNK
mdefine_line|#define USB_VID_COMPRO_UNK&t;&t;&t;&t;&t;0x145f
DECL|macro|USB_VID_CYPRESS
mdefine_line|#define USB_VID_CYPRESS&t;&t;&t;&t;&t;&t;0x04b4
DECL|macro|USB_VID_DIBCOM
mdefine_line|#define USB_VID_DIBCOM&t;&t;&t;&t;&t;&t;0x10b8
DECL|macro|USB_VID_EMPIA
mdefine_line|#define USB_VID_EMPIA&t;&t;&t;&t;&t;&t;0xeb1a
DECL|macro|USB_VID_GRANDTEC
mdefine_line|#define USB_VID_GRANDTEC&t;&t;&t;&t;&t;0x5032
DECL|macro|USB_VID_HYPER_PALTEK
mdefine_line|#define USB_VID_HYPER_PALTEK&t;&t;&t;&t;0x1025
DECL|macro|USB_VID_HANFTEK
mdefine_line|#define USB_VID_HANFTEK&t;&t;&t;&t;&t;&t;0x15f4
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
DECL|macro|USB_PID_COMPRO_DVBU2000_UNK_COLD
mdefine_line|#define USB_PID_COMPRO_DVBU2000_UNK_COLD&t;0x010c
DECL|macro|USB_PID_COMPRO_DVBU2000_UNK_WARM
mdefine_line|#define USB_PID_COMPRO_DVBU2000_UNK_WARM&t;0x010d
DECL|macro|USB_PID_DIBCOM_MOD3000_COLD
mdefine_line|#define USB_PID_DIBCOM_MOD3000_COLD&t;&t;&t;0x0bb8
DECL|macro|USB_PID_DIBCOM_MOD3000_WARM
mdefine_line|#define USB_PID_DIBCOM_MOD3000_WARM&t;&t;&t;0x0bb9
DECL|macro|USB_PID_DIBCOM_MOD3001_COLD
mdefine_line|#define USB_PID_DIBCOM_MOD3001_COLD&t;&t;&t;0x0bc6
DECL|macro|USB_PID_DIBCOM_MOD3001_WARM
mdefine_line|#define USB_PID_DIBCOM_MOD3001_WARM&t;&t;&t;0x0bc7
DECL|macro|USB_PID_DIBCOM_ANCHOR_2135_COLD
mdefine_line|#define USB_PID_DIBCOM_ANCHOR_2135_COLD&t;&t;0x2131
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
DECL|macro|USB_PID_ULTIMA_TVBOX_USB2_COLD
mdefine_line|#define USB_PID_ULTIMA_TVBOX_USB2_COLD&t;&t;0x8109
DECL|macro|USB_PID_ULTIMA_TVBOX_USB2_FX_COLD
mdefine_line|#define USB_PID_ULTIMA_TVBOX_USB2_FX_COLD&t;0x8613
DECL|macro|USB_PID_ULTIMA_TVBOX_USB2_FX_WARM
mdefine_line|#define USB_PID_ULTIMA_TVBOX_USB2_FX_WARM&t;0x1002
DECL|macro|USB_PID_UNK_HYPER_PALTEK_COLD
mdefine_line|#define USB_PID_UNK_HYPER_PALTEK_COLD&t;&t;0x005e
DECL|macro|USB_PID_UNK_HYPER_PALTEK_WARM
mdefine_line|#define USB_PID_UNK_HYPER_PALTEK_WARM&t;&t;0x005f
DECL|macro|USB_PID_HANFTEK_UMT_010_COLD
mdefine_line|#define USB_PID_HANFTEK_UMT_010_COLD&t;&t;0x0001
DECL|macro|USB_PID_HANFTEK_UMT_010_WARM
mdefine_line|#define USB_PID_HANFTEK_UMT_010_WARM&t;&t;0x0025
DECL|macro|USB_PID_YAKUMO_DTT200U_COLD
mdefine_line|#define USB_PID_YAKUMO_DTT200U_COLD&t;&t;&t;0x0201
DECL|macro|USB_PID_YAKUMO_DTT200U_WARM
mdefine_line|#define USB_PID_YAKUMO_DTT200U_WARM&t;&t;&t;0x0301
multiline_comment|/* USB Driver stuff&n; * table of devices that this driver is working with&n; *&n; * ATTENTION: Never ever change the order of this table, the particular &n; * devices depend on this order &n; *&n; * Each entry is used as a reference in the device_struct. Currently this is &n; * the only non-redundant way of assigning USB ids to actual devices I&squot;m aware &n; * of, because there is only one place in the code where the assignment of &n; * vendor and product id is done, here.&n; */
DECL|variable|dib_table
r_static
r_struct
id|usb_device_id
id|dib_table
(braket
)braket
op_assign
(brace
multiline_comment|/* 00 */
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
multiline_comment|/* 01 */
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
multiline_comment|/* 02 */
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
multiline_comment|/* the following device is actually not supported, but when loading the &n; * correct firmware (ie. its usb ids will change) everything works fine then &n; */
multiline_comment|/* 03 */
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
multiline_comment|/* 04 */
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
multiline_comment|/* 05 */
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
multiline_comment|/* 06 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_COMPRO_UNK
comma
id|USB_PID_COMPRO_DVBU2000_UNK_COLD
)paren
)brace
comma
multiline_comment|/* 07 */
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
multiline_comment|/* 08 */
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
multiline_comment|/* 09 */
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
multiline_comment|/* 10 */
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
multiline_comment|/* 11 */
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
multiline_comment|/* 12 */
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
multiline_comment|/* 13 */
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
multiline_comment|/* 14 */
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
multiline_comment|/* 15 */
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
multiline_comment|/* 16 */
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
multiline_comment|/* 17 */
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
multiline_comment|/* 18 */
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
multiline_comment|/* 19 */
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
multiline_comment|/* 20 */
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
multiline_comment|/* 21 */
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
multiline_comment|/* 22 */
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
multiline_comment|/* 23 */
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
multiline_comment|/* 24 */
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
multiline_comment|/* 25 */
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
multiline_comment|/* 26 */
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
multiline_comment|/* 27 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ULTIMA_ELECTRONIC
comma
id|USB_PID_ULTIMA_TVBOX_USB2_COLD
)paren
)brace
comma
multiline_comment|/* 28 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_HANFTEK
comma
id|USB_PID_HANFTEK_UMT_010_COLD
)paren
)brace
comma
multiline_comment|/* 29 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_HANFTEK
comma
id|USB_PID_HANFTEK_UMT_010_WARM
)paren
)brace
comma
multiline_comment|/* &n; * activate the following define when you have one of the devices and want to &n; * build it from build-2.6 in dvb-kernel&n; */
singleline_comment|// #define CONFIG_DVB_DIBUSB_MISDESIGNED_DEVICES 
macro_line|#ifdef CONFIG_DVB_DIBUSB_MISDESIGNED_DEVICES
multiline_comment|/* 30 */
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
multiline_comment|/* 31 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_CYPRESS
comma
id|USB_PID_ULTIMA_TVBOX_USB2_FX_COLD
)paren
)brace
comma
multiline_comment|/* 32 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ANCHOR
comma
id|USB_PID_ULTIMA_TVBOX_USB2_FX_WARM
)paren
)brace
comma
multiline_comment|/* 33 */
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VID_ANCHOR
comma
id|USB_PID_DIBCOM_ANCHOR_2135_COLD
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
id|dib_table
)paren
suffix:semicolon
DECL|variable|dibusb_usb_ctrl
r_static
r_struct
id|dibusb_usb_controller
id|dibusb_usb_ctrl
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;Cypress AN2135&quot;
comma
dot
id|cpu_cs_register
op_assign
l_int|0x7f92
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Cypress AN2235&quot;
comma
dot
id|cpu_cs_register
op_assign
l_int|0x7f92
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Cypress FX2&quot;
comma
dot
id|cpu_cs_register
op_assign
l_int|0xe600
)brace
comma
)brace
suffix:semicolon
DECL|variable|dibusb_tuner
r_struct
id|dibusb_tuner
id|dibusb_tuner
(braket
)braket
op_assign
(brace
(brace
id|DIBUSB_TUNER_CABLE_THOMSON
comma
l_int|0x61
)brace
comma
(brace
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV57H1XD5
comma
l_int|0x60
)brace
comma
(brace
id|DIBUSB_TUNER_CABLE_LG_TDTP_E102P
comma
l_int|0x61
)brace
comma
(brace
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5
comma
l_int|0x60
)brace
comma
)brace
suffix:semicolon
DECL|variable|dibusb_demod
r_static
r_struct
id|dibusb_demod
id|dibusb_demod
(braket
)braket
op_assign
(brace
(brace
id|DIBUSB_DIB3000MB
comma
l_int|16
comma
(brace
l_int|0x8
comma
l_int|0
)brace
comma
)brace
comma
(brace
id|DIBUSB_DIB3000MC
comma
l_int|32
comma
(brace
l_int|0x9
comma
l_int|0xa
comma
l_int|0xb
comma
l_int|0xc
)brace
comma
)brace
comma
(brace
id|DIBUSB_MT352
comma
l_int|254
comma
(brace
l_int|0xf
comma
l_int|0
)brace
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|dibusb_device_classes
r_static
r_struct
id|dibusb_device_class
id|dibusb_device_classes
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
id|DIBUSB1_1
comma
dot
id|usb_ctrl
op_assign
op_amp
id|dibusb_usb_ctrl
(braket
l_int|0
)braket
comma
dot
id|firmware
op_assign
l_string|&quot;dvb-dibusb-5.0.0.11.fw&quot;
comma
dot
id|pipe_cmd
op_assign
l_int|0x01
comma
dot
id|pipe_data
op_assign
l_int|0x02
comma
dot
id|urb_count
op_assign
l_int|3
comma
dot
id|urb_buffer_size
op_assign
l_int|4096
comma
id|DIBUSB_RC_NEC_PROTOCOL
comma
op_amp
id|dibusb_demod
(braket
id|DIBUSB_DIB3000MB
)braket
comma
op_amp
id|dibusb_tuner
(braket
id|DIBUSB_TUNER_CABLE_THOMSON
)braket
comma
)brace
comma
(brace
id|DIBUSB1_1_AN2235
comma
op_amp
id|dibusb_usb_ctrl
(braket
l_int|1
)braket
comma
l_string|&quot;dvb-dibusb-an2235-1.fw&quot;
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|3
comma
l_int|4096
comma
id|DIBUSB_RC_NEC_PROTOCOL
comma
op_amp
id|dibusb_demod
(braket
id|DIBUSB_DIB3000MB
)braket
comma
op_amp
id|dibusb_tuner
(braket
id|DIBUSB_TUNER_CABLE_THOMSON
)braket
comma
)brace
comma
(brace
id|DIBUSB2_0
comma
op_amp
id|dibusb_usb_ctrl
(braket
l_int|2
)braket
comma
l_string|&quot;dvb-dibusb-6.0.0.5.fw&quot;
comma
l_int|0x01
comma
l_int|0x06
comma
l_int|3
comma
l_int|188
op_star
l_int|210
comma
id|DIBUSB_RC_NEC_PROTOCOL
comma
op_amp
id|dibusb_demod
(braket
id|DIBUSB_DIB3000MC
)braket
comma
op_amp
id|dibusb_tuner
(braket
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV57H1XD5
)braket
comma
)brace
comma
(brace
id|UMT2_0
comma
op_amp
id|dibusb_usb_ctrl
(braket
l_int|2
)braket
comma
l_string|&quot;dvb-dibusb-umt-1.fw&quot;
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|15
comma
l_int|188
op_star
l_int|21
comma
id|DIBUSB_RC_NO
comma
op_amp
id|dibusb_demod
(braket
id|DIBUSB_MT352
)braket
comma
singleline_comment|//&t;  &amp;dibusb_tuner[DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5],
op_amp
id|dibusb_tuner
(braket
id|DIBUSB_TUNER_CABLE_LG_TDTP_E102P
)braket
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|dibusb_devices
r_static
r_struct
id|dibusb_usb_device
id|dibusb_devices
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;TwinhanDTV USB1.1 / Magic Box / HAMA USB1.1 DVB-T device&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|19
)braket
comma
op_amp
id|dib_table
(braket
l_int|21
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|20
)braket
comma
op_amp
id|dib_table
(braket
l_int|22
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;KWorld V-Stream XPERT DTV - DVB-T USB1.1&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|11
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|12
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Grandtec USB1.1 DVB-T&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|13
)braket
comma
op_amp
id|dib_table
(braket
l_int|15
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|14
)braket
comma
op_amp
id|dib_table
(braket
l_int|16
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;DiBcom USB1.1 DVB-T reference design (MOD3000)&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|7
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|8
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Artec T1 USB1.1 TVBOX with AN2135&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|23
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|24
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Artec T1 USB1.1 TVBOX with AN2235&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1_AN2235
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|25
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|26
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Avermedia AverTV DVBT USB1.1&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|0
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|1
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Compro Videomate DVB-U2000 - DVB-T USB1.1 (please confirm to linux-dvb)&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|4
)braket
comma
op_amp
id|dib_table
(braket
l_int|6
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|5
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Unkown USB1.1 DVB-T device ???? please report the name to the author&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|17
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|18
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;DiBcom USB2.0 DVB-T reference design (MOD3000P)&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB2_0
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|9
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|10
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Artec T1 USB2.0 TVBOX (please report the warm ID)&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB2_0
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|27
)braket
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;AVermedia/Yakumo/Hama/Typhoon DVB-T USB2.0&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|UMT2_0
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|2
)braket
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Hanftek UMT-010 DVB-T USB2.0&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|UMT2_0
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|28
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|29
)braket
comma
l_int|NULL
)brace
comma
)brace
comma
macro_line|#ifdef CONFIG_DVB_DIBUSB_MISDESIGNED_DEVICES
(brace
l_string|&quot;Artec T1 USB1.1 TVBOX with AN2235 (misdesigned)&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1_AN2235
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|30
)braket
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
)brace
comma
)brace
comma
(brace
l_string|&quot;Artec T1 USB2.0 TVBOX with FX2 IDs (misdesigned, please report the warm ID)&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB2_0
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|31
)braket
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|dib_table
(braket
l_int|32
)braket
comma
l_int|NULL
)brace
comma
multiline_comment|/* undefined, it could be that the device will get another USB ID in warm state */
)brace
comma
(brace
l_string|&quot;DiBcom USB1.1 DVB-T reference design (MOD3000) with AN2135 default IDs&quot;
comma
op_amp
id|dibusb_device_classes
(braket
id|DIBUSB1_1
)braket
comma
(brace
op_amp
id|dib_table
(braket
l_int|33
)braket
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
)brace
comma
)brace
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|dibusb_exit
r_static
r_int
id|dibusb_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;init_state before exiting everything: %x&bslash;n&quot;
comma
id|dib-&gt;init_state
)paren
suffix:semicolon
id|dibusb_remote_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
id|dibusb_fe_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
id|dibusb_i2c_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
id|dibusb_pid_list_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
id|dibusb_dvb_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
id|dibusb_urb_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;init_state should be zero now: %x&bslash;n&quot;
comma
id|dib-&gt;init_state
)paren
suffix:semicolon
id|dib-&gt;init_state
op_assign
id|DIBUSB_STATE_INIT
suffix:semicolon
id|kfree
c_func
(paren
id|dib
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_init
r_static
r_int
id|dibusb_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|dib-&gt;usb_sem
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|dib-&gt;i2c_sem
comma
l_int|1
)paren
suffix:semicolon
id|dib-&gt;init_state
op_assign
id|DIBUSB_STATE_INIT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|dibusb_urb_init
c_func
(paren
id|dib
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|dibusb_dvb_init
c_func
(paren
id|dib
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|dibusb_pid_list_init
c_func
(paren
id|dib
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|dibusb_i2c_init
c_func
(paren
id|dib
)paren
)paren
)paren
(brace
id|dibusb_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|dibusb_fe_init
c_func
(paren
id|dib
)paren
)paren
)paren
id|err
c_func
(paren
l_string|&quot;could not initialize a frontend.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|dibusb_remote_init
c_func
(paren
id|dib
)paren
)paren
)paren
id|err
c_func
(paren
l_string|&quot;could not initialize remote control.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_find_device
r_static
r_struct
id|dibusb_usb_device
op_star
id|dibusb_find_device
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_int
op_star
id|cold
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
op_star
id|cold
op_assign
op_minus
l_int|1
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
r_sizeof
(paren
id|dibusb_devices
)paren
op_div
r_sizeof
(paren
r_struct
id|dibusb_usb_device
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|DIBUSB_ID_MAX_NUM
op_logical_and
id|dibusb_devices
(braket
id|i
)braket
dot
id|cold_ids
(braket
id|j
)braket
op_ne
l_int|NULL
suffix:semicolon
id|j
op_increment
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;check for cold %x %x&bslash;n&quot;
comma
id|dibusb_devices
(braket
id|i
)braket
dot
id|cold_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idVendor
comma
id|dibusb_devices
(braket
id|i
)braket
dot
id|cold_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idProduct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dibusb_devices
(braket
id|i
)braket
dot
id|cold_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idVendor
op_eq
id|udev-&gt;descriptor.idVendor
op_logical_and
id|dibusb_devices
(braket
id|i
)braket
dot
id|cold_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idProduct
op_eq
id|udev-&gt;descriptor.idProduct
)paren
(brace
op_star
id|cold
op_assign
l_int|1
suffix:semicolon
r_return
op_amp
id|dibusb_devices
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|DIBUSB_ID_MAX_NUM
op_logical_and
id|dibusb_devices
(braket
id|i
)braket
dot
id|warm_ids
(braket
id|j
)braket
op_ne
l_int|NULL
suffix:semicolon
id|j
op_increment
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;check for warm %x %x&bslash;n&quot;
comma
id|dibusb_devices
(braket
id|i
)braket
dot
id|warm_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idVendor
comma
id|dibusb_devices
(braket
id|i
)braket
dot
id|warm_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idProduct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dibusb_devices
(braket
id|i
)braket
dot
id|warm_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idVendor
op_eq
id|udev-&gt;descriptor.idVendor
op_logical_and
id|dibusb_devices
(braket
id|i
)braket
dot
id|warm_ids
(braket
id|j
)braket
op_member_access_from_pointer
id|idProduct
op_eq
id|udev-&gt;descriptor.idProduct
)paren
(brace
op_star
id|cold
op_assign
l_int|0
suffix:semicolon
r_return
op_amp
id|dibusb_devices
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * USB &n; */
DECL|function|dibusb_probe
r_static
r_int
id|dibusb_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dibusb_usb_device
op_star
id|dibdev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOMEM
comma
id|cold
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dibdev
op_assign
id|dibusb_find_device
c_func
(paren
id|udev
comma
op_amp
id|cold
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;something went very wrong, &quot;
l_string|&quot;unknown product ID: %.4x&quot;
comma
id|udev-&gt;descriptor.idProduct
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cold
op_eq
l_int|1
)paren
(brace
id|info
c_func
(paren
l_string|&quot;found a &squot;%s&squot; in cold state, will try to load a firmware&quot;
comma
id|dibdev-&gt;name
)paren
suffix:semicolon
id|ret
op_assign
id|dibusb_loadfirmware
c_func
(paren
id|udev
comma
id|dibdev
)paren
suffix:semicolon
)brace
r_else
(brace
id|info
c_func
(paren
l_string|&quot;found a &squot;%s&squot; in warm state.&quot;
comma
id|dibdev-&gt;name
)paren
suffix:semicolon
id|dib
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_dibusb
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;no memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dib
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|usb_dibusb
)paren
)paren
suffix:semicolon
id|dib-&gt;udev
op_assign
id|udev
suffix:semicolon
id|dib-&gt;dibdev
op_assign
id|dibdev
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|dib
)paren
suffix:semicolon
id|ret
op_assign
id|dibusb_init
c_func
(paren
id|dib
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|info
c_func
(paren
l_string|&quot;%s successfully initialized and connected.&quot;
comma
id|dibdev-&gt;name
)paren
suffix:semicolon
r_else
id|info
c_func
(paren
l_string|&quot;%s error while loading driver (%d)&quot;
comma
id|dibdev-&gt;name
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dibusb_disconnect
r_static
r_void
id|dibusb_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
id|usb_get_intfdata
c_func
(paren
id|intf
)paren
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|DRIVER_DESC
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib
op_ne
l_int|NULL
op_logical_and
id|dib-&gt;dibdev
op_ne
l_int|NULL
)paren
(brace
id|name
op_assign
id|dib-&gt;dibdev-&gt;name
suffix:semicolon
id|dibusb_exit
c_func
(paren
id|dib
)paren
suffix:semicolon
)brace
id|info
c_func
(paren
l_string|&quot;%s successfully deinitialized and disconnected.&quot;
comma
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/* usb specific object needed to register this driver with the usb subsystem */
DECL|variable|dibusb_driver
r_struct
id|usb_driver
id|dibusb_driver
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
id|DRIVER_DESC
comma
dot
id|probe
op_assign
id|dibusb_probe
comma
dot
id|disconnect
op_assign
id|dibusb_disconnect
comma
dot
id|id_table
op_assign
id|dib_table
comma
)brace
suffix:semicolon
multiline_comment|/* module stuff */
DECL|function|usb_dibusb_init
r_static
r_int
id|__init
id|usb_dibusb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|usb_register
c_func
(paren
op_amp
id|dibusb_driver
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;usb_register failed. Error number %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_dibusb_exit
r_static
r_void
id|__exit
id|usb_dibusb_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* deregister this driver from the USB subsystem */
id|usb_deregister
c_func
(paren
op_amp
id|dibusb_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_dibusb_init
id|module_init
(paren
id|usb_dibusb_init
)paren
suffix:semicolon
DECL|variable|usb_dibusb_exit
id|module_exit
(paren
id|usb_dibusb_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
