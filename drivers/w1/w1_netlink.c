multiline_comment|/*&n; * w1_netlink.c&n; *&n; * Copyright (c) 2003 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; *&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &quot;w1.h&quot;
macro_line|#include &quot;w1_log.h&quot;
macro_line|#include &quot;w1_netlink.h&quot;
macro_line|#ifndef NETLINK_DISABLED
DECL|function|w1_netlink_send
r_void
id|w1_netlink_send
c_func
(paren
r_struct
id|w1_master
op_star
id|dev
comma
r_struct
id|w1_netlink_msg
op_star
id|msg
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|w1_netlink_msg
op_star
id|data
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;nls
)paren
r_return
suffix:semicolon
id|size
op_assign
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
r_struct
id|w1_netlink_msg
)paren
)paren
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;skb_alloc() failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nlh
op_assign
id|NLMSG_PUT
c_func
(paren
id|skb
comma
l_int|0
comma
id|dev-&gt;seq
op_increment
comma
id|NLMSG_DONE
comma
id|size
op_minus
r_sizeof
(paren
op_star
id|nlh
)paren
)paren
suffix:semicolon
id|data
op_assign
(paren
r_struct
id|w1_netlink_msg
op_star
)paren
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|data
comma
id|msg
comma
r_sizeof
(paren
r_struct
id|w1_netlink_msg
)paren
)paren
suffix:semicolon
id|NETLINK_CB
c_func
(paren
id|skb
)paren
dot
id|dst_groups
op_assign
id|dev-&gt;groups
suffix:semicolon
id|netlink_broadcast
c_func
(paren
id|dev-&gt;nls
comma
id|skb
comma
l_int|0
comma
id|dev-&gt;groups
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|nlmsg_failure
suffix:colon
r_return
suffix:semicolon
)brace
macro_line|#else
macro_line|#warning Netlink support is disabled. Please compile with NET support enabled.
DECL|function|w1_netlink_send
r_void
id|w1_netlink_send
c_func
(paren
r_struct
id|w1_master
op_star
id|dev
comma
r_struct
id|w1_netlink_msg
op_star
id|msg
)paren
(brace
)brace
macro_line|#endif
eof
