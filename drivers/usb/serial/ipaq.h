multiline_comment|/*&n; * USB Compaq iPAQ driver&n; *&n; *&t;Copyright (C) 2001 - 2002&n; *&t;    Ganesh Varadarajan &lt;ganesh@veritas.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; */
macro_line|#ifndef __LINUX_USB_SERIAL_IPAQ_H
DECL|macro|__LINUX_USB_SERIAL_IPAQ_H
mdefine_line|#define __LINUX_USB_SERIAL_IPAQ_H
DECL|macro|ASKEY_VENDOR_ID
mdefine_line|#define ASKEY_VENDOR_ID&t;&t;0x1690
DECL|macro|ASKEY_PRODUCT_ID
mdefine_line|#define ASKEY_PRODUCT_ID&t;0x0601
DECL|macro|BCOM_VENDOR_ID
mdefine_line|#define BCOM_VENDOR_ID&t;&t;0x0960
DECL|macro|BCOM_0065_ID
mdefine_line|#define BCOM_0065_ID&t;&t;0x0065
DECL|macro|BCOM_0066_ID
mdefine_line|#define BCOM_0066_ID&t;&t;0x0066
DECL|macro|BCOM_0067_ID
mdefine_line|#define BCOM_0067_ID&t;&t;0x0067
DECL|macro|CASIO_VENDOR_ID
mdefine_line|#define CASIO_VENDOR_ID&t;&t;0x07cf
DECL|macro|CASIO_2001_ID
mdefine_line|#define CASIO_2001_ID&t;&t;0x2001
DECL|macro|CASIO_EM500_ID
mdefine_line|#define CASIO_EM500_ID&t;&t;0x2002
DECL|macro|COMPAQ_VENDOR_ID
mdefine_line|#define COMPAQ_VENDOR_ID&t;0x049f
DECL|macro|COMPAQ_IPAQ_ID
mdefine_line|#define COMPAQ_IPAQ_ID&t;&t;0x0003
DECL|macro|COMPAQ_0032_ID
mdefine_line|#define COMPAQ_0032_ID&t;&t;0x0032
DECL|macro|DELL_VENDOR_ID
mdefine_line|#define DELL_VENDOR_ID&t;&t;0x413c
DECL|macro|DELL_AXIM_ID
mdefine_line|#define DELL_AXIM_ID&t;&t;0x4001
DECL|macro|FSC_VENDOR_ID
mdefine_line|#define FSC_VENDOR_ID&t;&t;0x0bf8
DECL|macro|FSC_LOOX_ID
mdefine_line|#define FSC_LOOX_ID&t;&t;0x1001
DECL|macro|HP_VENDOR_ID
mdefine_line|#define HP_VENDOR_ID&t;&t;0x03f0
DECL|macro|HP_JORNADA_548_ID
mdefine_line|#define HP_JORNADA_548_ID&t;0x1016
DECL|macro|HP_JORNADA_568_ID
mdefine_line|#define HP_JORNADA_568_ID&t;0x1116
DECL|macro|HP_2016_ID
mdefine_line|#define HP_2016_ID&t;&t;0x2016
DECL|macro|HP_2116_ID
mdefine_line|#define HP_2116_ID&t;&t;0x2116
DECL|macro|HP_2216_ID
mdefine_line|#define HP_2216_ID&t;&t;0x2216
DECL|macro|HP_3016_ID
mdefine_line|#define HP_3016_ID&t;&t;0x3016
DECL|macro|HP_3116_ID
mdefine_line|#define HP_3116_ID&t;&t;0x3116
DECL|macro|HP_3216_ID
mdefine_line|#define HP_3216_ID&t;&t;0x3216
DECL|macro|HP_4016_ID
mdefine_line|#define HP_4016_ID&t;&t;0x4016
DECL|macro|HP_4116_ID
mdefine_line|#define HP_4116_ID&t;&t;0x4116
DECL|macro|HP_4216_ID
mdefine_line|#define HP_4216_ID&t;&t;0x4216
DECL|macro|HP_5016_ID
mdefine_line|#define HP_5016_ID&t;&t;0x5016
DECL|macro|HP_5116_ID
mdefine_line|#define HP_5116_ID&t;&t;0x5116
DECL|macro|HP_5216_ID
mdefine_line|#define HP_5216_ID&t;&t;0x5216
DECL|macro|LINKUP_VENDOR_ID
mdefine_line|#define LINKUP_VENDOR_ID&t;0x094b
DECL|macro|LINKUP_PRODUCT_ID
mdefine_line|#define LINKUP_PRODUCT_ID&t;0x0001
DECL|macro|MICROSOFT_VENDOR_ID
mdefine_line|#define MICROSOFT_VENDOR_ID&t;0x045e
DECL|macro|MICROSOFT_00CE_ID
mdefine_line|#define MICROSOFT_00CE_ID&t;0x00ce
DECL|macro|PORTATEC_VENDOR_ID
mdefine_line|#define PORTATEC_VENDOR_ID&t;0x0961
DECL|macro|PORTATEC_PRODUCT_ID
mdefine_line|#define PORTATEC_PRODUCT_ID&t;0x0010
DECL|macro|ROVER_VENDOR_ID
mdefine_line|#define ROVER_VENDOR_ID&t;&t;0x047b
DECL|macro|ROVER_P5_ID
mdefine_line|#define ROVER_P5_ID&t;&t;0x3000
DECL|macro|SAGEM_VENDOR_ID
mdefine_line|#define SAGEM_VENDOR_ID&t;&t;0x5e04
DECL|macro|SAGEM_WIRELESS_ID
mdefine_line|#define SAGEM_WIRELESS_ID&t;0xce00
DECL|macro|SOCKET_VENDOR_ID
mdefine_line|#define SOCKET_VENDOR_ID&t;0x0104
DECL|macro|SOCKET_PRODUCT_ID
mdefine_line|#define SOCKET_PRODUCT_ID&t;0x00be
DECL|macro|TOSHIBA_VENDOR_ID
mdefine_line|#define TOSHIBA_VENDOR_ID&t;0x0930
DECL|macro|TOSHIBA_PRODUCT_ID
mdefine_line|#define TOSHIBA_PRODUCT_ID&t;0x0700
DECL|macro|TOSHIBA_E310_ID
mdefine_line|#define TOSHIBA_E310_ID&t;&t;0x0705
DECL|macro|TOSHIBA_E740_ID
mdefine_line|#define TOSHIBA_E740_ID&t;&t;0x0706
DECL|macro|TOSHIBA_E335_ID
mdefine_line|#define TOSHIBA_E335_ID&t;&t;0x0707
DECL|macro|HTC_VENDOR_ID
mdefine_line|#define HTC_VENDOR_ID&t;&t;0x0bb4
DECL|macro|HTC_PRODUCT_ID
mdefine_line|#define HTC_PRODUCT_ID&t;&t;0x00ce
DECL|macro|NEC_VENDOR_ID
mdefine_line|#define NEC_VENDOR_ID&t;&t;0x0409
DECL|macro|NEC_PRODUCT_ID
mdefine_line|#define NEC_PRODUCT_ID&t;&t;0x00d5
DECL|macro|ASUS_VENDOR_ID
mdefine_line|#define ASUS_VENDOR_ID&t;&t;0x0b05
DECL|macro|ASUS_A600_PRODUCT_ID
mdefine_line|#define ASUS_A600_PRODUCT_ID&t;0x4201
multiline_comment|/*&n; * Since we can&squot;t queue our bulk write urbs (don&squot;t know why - it just&n; * doesn&squot;t work), we can send down only one write urb at a time. The simplistic&n; * approach taken by the generic usbserial driver will work, but it&squot;s not good&n; * for performance. Therefore, we buffer upto URBDATA_QUEUE_MAX bytes of write&n; * requests coming from the line discipline. This is done by chaining them&n; * in lists of struct ipaq_packet, each packet holding a maximum of&n; * PACKET_SIZE bytes.&n; *&n; * ipaq_write() can be called from bottom half context; hence we can&squot;t&n; * allocate memory for packets there. So we initialize a pool of packets at&n; * the first open and maintain a freelist.&n; *&n; * The value of PACKET_SIZE was empirically determined by&n; * checking the maximum write sizes sent down by the ppp ldisc.&n; * URBDATA_QUEUE_MAX is set to 64K, which is the maximum TCP window size.&n; */
DECL|struct|ipaq_packet
r_struct
id|ipaq_packet
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|written
r_int
id|written
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipaq_private
r_struct
id|ipaq_private
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|queue_len
r_int
id|queue_len
suffix:semicolon
DECL|member|free_len
r_int
id|free_len
suffix:semicolon
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|freelist
r_struct
id|list_head
id|freelist
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|URBDATA_SIZE
mdefine_line|#define URBDATA_SIZE&t;&t;4096
DECL|macro|URBDATA_QUEUE_MAX
mdefine_line|#define URBDATA_QUEUE_MAX&t;(64 * 1024)
DECL|macro|PACKET_SIZE
mdefine_line|#define PACKET_SIZE&t;&t;256
macro_line|#endif
eof
