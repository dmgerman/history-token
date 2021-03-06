multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  NET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Token-ring handlers.&n; *&n; * Version:&t;@(#)eth.h&t;1.0.4&t;05/13/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;Relocated to include/linux where it belongs by Alan Cox &n; *&t;&t;&t;&t;&t;&t;&t;&lt;gw4pts@gw4pts.ampr.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;WARNING: This move may well be temporary. This file will get merged with others RSN.&n; *&n; */
macro_line|#ifndef _LINUX_TRDEVICE_H
DECL|macro|_LINUX_TRDEVICE_H
mdefine_line|#define _LINUX_TRDEVICE_H
macro_line|#include &lt;linux/if_tr.h&gt;
macro_line|#ifdef __KERNEL__
r_extern
r_int
r_int
id|tr_type_trans
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|tr_source_route
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|alloc_trdev
c_func
(paren
r_int
id|sizeof_priv
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _LINUX_TRDEVICE_H */
eof
