multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the HIPPI handlers.&n; *&n; * Version:&t;@(#)hippidevice.h&t;1.0.0&t;05/26/97&n; *&n; * Author:&t;Jes Sorensen, &lt;Jes.Sorensen@cern.ch&gt;&n; *&n; *&t;&t;hippidevice.h is based on previous fddidevice.h work by&n; *&t;&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&t;&t;&t;Lawrence V. Stefani, &lt;stefani@lkg.dec.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_HIPPIDEVICE_H
DECL|macro|_LINUX_HIPPIDEVICE_H
mdefine_line|#define _LINUX_HIPPIDEVICE_H
macro_line|#include &lt;linux/if_hippi.h&gt;
macro_line|#ifdef __KERNEL__
r_extern
r_int
r_int
id|hippi_type_trans
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
r_struct
id|net_device
op_star
id|alloc_hippi_dev
c_func
(paren
r_int
id|sizeof_priv
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _LINUX_HIPPIDEVICE_H */
eof
