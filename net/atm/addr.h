multiline_comment|/* net/atm/addr.h - Local ATM address registry */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef NET_ATM_ADDR_H
DECL|macro|NET_ATM_ADDR_H
mdefine_line|#define NET_ATM_ADDR_H
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
r_void
id|atm_reset_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|atm_add_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|sockaddr_atmsvc
op_star
id|addr
)paren
suffix:semicolon
r_int
id|atm_del_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|sockaddr_atmsvc
op_star
id|addr
)paren
suffix:semicolon
r_int
id|atm_get_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|sockaddr_atmsvc
op_star
id|u_buf
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif
eof
