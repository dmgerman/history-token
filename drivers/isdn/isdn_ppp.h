multiline_comment|/* $Id: isdn_ppp.h,v 1.17.6.1 2001/09/23 22:24:32 kai Exp $&n; *&n; * header for Linux ISDN subsystem, functions for synchronous PPP (linklevel).&n; *&n; * Copyright 1995,96 by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/ppp_defs.h&gt;     /* for PPP_PROTOCOL */
macro_line|#include &lt;linux/isdn_ppp.h&gt;&t;/* for isdn_ppp info */
r_extern
r_struct
id|file_operations
id|isdn_ppp_fops
suffix:semicolon
r_extern
r_int
id|isdn_ppp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_ppp_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_free
c_func
(paren
id|isdn_net_local
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_bind
c_func
(paren
id|isdn_net_local
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_ppp_receive
c_func
(paren
id|isdn_net_dev
op_star
comma
id|isdn_net_local
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_dev_ioctl
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|ifreq
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_dial_slave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_ppp_wakeup_daemon
c_func
(paren
id|isdn_net_local
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_register_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
id|ipc
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_unregister_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
id|ipc
)paren
suffix:semicolon
DECL|macro|IPPP_OPEN
mdefine_line|#define IPPP_OPEN&t;0x01
DECL|macro|IPPP_CONNECT
mdefine_line|#define IPPP_CONNECT&t;0x02
DECL|macro|IPPP_CLOSEWAIT
mdefine_line|#define IPPP_CLOSEWAIT&t;0x04
DECL|macro|IPPP_NOBLOCK
mdefine_line|#define IPPP_NOBLOCK&t;0x08
DECL|macro|IPPP_ASSIGNED
mdefine_line|#define IPPP_ASSIGNED&t;0x10
DECL|macro|IPPP_MAX_HEADER
mdefine_line|#define IPPP_MAX_HEADER 10
eof
