multiline_comment|/*&n; * $Id: ctctty.h,v 1.2 2001/01/30 22:09:28 uweigand Exp $&n; *&n; * CTC / ESCON network driver, tty interface.&n; *&n; * Copyright (C) 2001 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Fritz Elfert (elfert@de.ibm.com, felfert@millenux.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _CTCTTY_H_
DECL|macro|_CTCTTY_H_
mdefine_line|#define _CTCTTY_H_
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; 0x020300
DECL|typedef|net_device
r_typedef
r_struct
id|device
id|net_device
suffix:semicolon
macro_line|#else
DECL|typedef|net_device
r_typedef
r_struct
id|net_device
id|net_device
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|ctc_tty_register_netdev
c_func
(paren
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|ctc_tty_unregister_netdev
c_func
(paren
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|ctc_tty_netif_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|ctc_tty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ctc_tty_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
