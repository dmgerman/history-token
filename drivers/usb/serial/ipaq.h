multiline_comment|/*&n; * USB Compaq iPAQ driver&n; *&n; *&t;Copyright (C) 2001&n; *&t;    Ganesh Varadarajan &lt;ganesh@veritas.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * &n; */
macro_line|#ifndef __LINUX_USB_SERIAL_IPAQ_H
DECL|macro|__LINUX_USB_SERIAL_IPAQ_H
mdefine_line|#define __LINUX_USB_SERIAL_IPAQ_H
DECL|macro|IPAQ_VENDOR_ID
mdefine_line|#define IPAQ_VENDOR_ID&t;&t;&t;0x049f
DECL|macro|IPAQ_PRODUCT_ID
mdefine_line|#define IPAQ_PRODUCT_ID&t;&t;&t;0x0003
multiline_comment|/*&n; * Since we can&squot;t queue our bulk write urbs (don&squot;t know why - it just&n; * doesn&squot;t work), we can send down only one write urb at a time. The simplistic&n; * approach taken by the generic usbserial driver will work, but it&squot;s not good&n; * for performance. Therefore, we buffer upto URBDATA_QUEUE_MAX bytes of write&n; * requests coming from the line discipline. This is done by chaining them&n; * in lists of struct ipaq_packet, each packet holding a maximum of&n; * PACKET_SIZE bytes.&n; *&n; * ipaq_write() can be called from bottom half context; hence we can&squot;t&n; * allocate memory for packets there. So we initialize a pool of packets at&n; * the first open and maintain a freelist.&n; *&n; * The value of PACKET_SIZE was empirically determined by&n; * checking the maximum write sizes sent down by the ppp ldisc.&n; * URBDATA_QUEUE_MAX is set to 64K, which is the maximum TCP window size&n; * supported by the iPAQ.&n; */
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
