multiline_comment|/*&n; *  Universal TUN/TAP device driver.&n; *  Copyright (C) 1999-2000 Maxim Krasnyansky &lt;max_mk@yahoo.com&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *  GNU General Public License for more details.&n; *&n; *  $Id: if_tun.h,v 1.1 2000/08/23 05:59:28 davem Exp $&n; */
macro_line|#ifndef __IF_TUN_H
DECL|macro|__IF_TUN_H
mdefine_line|#define __IF_TUN_H
multiline_comment|/* Uncomment to enable debugging */
multiline_comment|/* #define TUN_DEBUG 1 */
macro_line|#ifdef __KERNEL__
macro_line|#ifdef TUN_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG  if(tun-&gt;debug)printk
DECL|macro|DBG1
mdefine_line|#define DBG1 if(debug==2)printk
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG( a... )
DECL|macro|DBG1
mdefine_line|#define DBG1( a... )
macro_line|#endif
DECL|struct|tun_struct
r_struct
id|tun_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
id|dev
suffix:semicolon
DECL|member|txq
r_struct
id|sk_buff_head
id|txq
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
macro_line|#ifdef TUN_DEBUG&t;
DECL|member|debug
r_int
id|debug
suffix:semicolon
macro_line|#endif  
)brace
suffix:semicolon
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ( (a)&lt;(b) ? (a):(b) ) 
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* Number of devices */
DECL|macro|TUN_MAX_DEV
mdefine_line|#define TUN_MAX_DEV&t;255
multiline_comment|/* TX queue size */
DECL|macro|TUN_TXQ_SIZE
mdefine_line|#define TUN_TXQ_SIZE&t;10
multiline_comment|/* Max frame size */
DECL|macro|TUN_MAX_FRAME
mdefine_line|#define TUN_MAX_FRAME&t;4096
multiline_comment|/* TUN device flags */
DECL|macro|TUN_TUN_DEV
mdefine_line|#define TUN_TUN_DEV &t;0x0001&t;
DECL|macro|TUN_TAP_DEV
mdefine_line|#define TUN_TAP_DEV&t;0x0002
DECL|macro|TUN_TYPE_MASK
mdefine_line|#define TUN_TYPE_MASK   0x000f
DECL|macro|TUN_FASYNC
mdefine_line|#define TUN_FASYNC&t;0x0010
DECL|macro|TUN_NOCHECKSUM
mdefine_line|#define TUN_NOCHECKSUM&t;0x0020
DECL|macro|TUN_NO_PI
mdefine_line|#define TUN_NO_PI&t;0x0040
DECL|macro|TUN_IFF_SET
mdefine_line|#define TUN_IFF_SET&t;0x1000
multiline_comment|/* Ioctl defines */
DECL|macro|TUNSETNOCSUM
mdefine_line|#define TUNSETNOCSUM ((&squot;T&squot;&lt;&lt; 8) | 200) 
DECL|macro|TUNSETDEBUG
mdefine_line|#define TUNSETDEBUG  ((&squot;T&squot;&lt;&lt; 8) | 201) 
DECL|macro|TUNSETIFF
mdefine_line|#define TUNSETIFF    ((&squot;T&squot;&lt;&lt; 8) | 202) 
multiline_comment|/* TUNSETIFF ifr flags */
DECL|macro|IFF_TUN
mdefine_line|#define IFF_TUN&t;&t;0x0001
DECL|macro|IFF_TAP
mdefine_line|#define IFF_TAP&t;&t;0x0002
DECL|macro|IFF_NO_PI
mdefine_line|#define IFF_NO_PI&t;0x1000
DECL|struct|tun_pi
r_struct
id|tun_pi
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|proto
r_int
r_int
id|proto
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TUN_PKT_STRIP
mdefine_line|#define TUN_PKT_STRIP&t;0x0001
macro_line|#endif /* __IF_TUN_H */
eof
