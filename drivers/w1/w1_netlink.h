multiline_comment|/*&n; * w1_netlink.h&n; *&n; * Copyright (c) 2003 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; *&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef __W1_NETLINK_H
DECL|macro|__W1_NETLINK_H
mdefine_line|#define __W1_NETLINK_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &quot;w1.h&quot;
DECL|struct|w1_netlink_msg
r_struct
id|w1_netlink_msg
(brace
r_union
(brace
DECL|member|id
r_struct
id|w1_reg_num
id|id
suffix:semicolon
DECL|member|w1_id
id|__u64
id|w1_id
suffix:semicolon
DECL|member|id
)brace
id|id
suffix:semicolon
DECL|member|val
id|__u64
id|val
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_void
id|w1_netlink_send
c_func
(paren
r_struct
id|w1_master
op_star
comma
r_struct
id|w1_netlink_msg
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __W1_NETLINK_H */
eof
