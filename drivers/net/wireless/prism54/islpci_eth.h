multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef _ISLPCI_ETH_H
DECL|macro|_ISLPCI_ETH_H
mdefine_line|#define _ISLPCI_ETH_H
macro_line|#include &quot;isl_38xx.h&quot;
macro_line|#include &quot;islpci_dev.h&quot;
r_void
id|islpci_eth_cleanup_transmit
c_func
(paren
id|islpci_private
op_star
comma
id|isl38xx_control_block
op_star
)paren
suffix:semicolon
r_int
id|islpci_eth_transmit
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
r_int
id|islpci_eth_receive
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_void
id|islpci_eth_tx_timeout
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|islpci_do_reset_and_wake
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ISL_GEN_H */
eof
