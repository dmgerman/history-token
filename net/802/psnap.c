multiline_comment|/*&n; *&t;SNAP data link layer. Derived from 802.2&n; *&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;,&n; *&t;&t;from the 802.2 layer by Greg Page.&n; *&t;&t;Merged in additions from Greg Page&squot;s psnap.c.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;net/psnap.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
DECL|variable|snap_list
id|LIST_HEAD
c_func
(paren
id|snap_list
)paren
suffix:semicolon
DECL|variable|snap_sap
r_static
r_struct
id|llc_sap
op_star
id|snap_sap
suffix:semicolon
multiline_comment|/*&n; *&t;Find a snap client by matching the 5 bytes.&n; */
DECL|function|find_snap_client
r_static
r_struct
id|datalink_proto
op_star
id|find_snap_client
c_func
(paren
r_int
r_char
op_star
id|desc
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|datalink_proto
op_star
id|proto
op_assign
l_int|NULL
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|snap_list
)paren
)paren
r_goto
id|out
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|snap_list
)paren
(brace
id|p
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|datalink_proto
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p-&gt;type
comma
id|desc
comma
l_int|5
)paren
)paren
(brace
id|proto
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_return
id|proto
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A SNAP packet has arrived&n; */
DECL|function|snap_indicate
r_static
r_int
id|snap_indicate
c_func
(paren
r_struct
id|llc_prim_if_block
op_star
id|prim
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|datalink_proto
op_star
id|proto
suffix:semicolon
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
r_static
r_struct
id|packet_type
id|psnap_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_SNAP
)paren
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|prim-&gt;prim
op_ne
id|LLC_DATAUNIT_PRIM
)paren
r_goto
id|out
suffix:semicolon
id|skb
op_assign
id|prim-&gt;data-&gt;udata.skb
suffix:semicolon
id|proto
op_assign
id|find_snap_client
c_func
(paren
id|skb-&gt;h.raw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proto
)paren
(brace
multiline_comment|/* Pass the frame on. */
id|skb-&gt;h.raw
op_add_assign
l_int|5
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|5
)paren
suffix:semicolon
id|rc
op_assign
id|proto
op_member_access_from_pointer
id|rcvfunc
c_func
(paren
id|skb
comma
id|skb-&gt;dev
comma
op_amp
id|psnap_packet_type
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Put a SNAP header on a frame and pass to 802.2&n; */
DECL|function|snap_request
r_static
r_int
id|snap_request
c_func
(paren
r_struct
id|datalink_proto
op_star
id|dl
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dest
)paren
(brace
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|5
)paren
comma
id|dl-&gt;type
comma
l_int|5
)paren
suffix:semicolon
id|llc_build_and_send_ui_pkt
c_func
(paren
id|snap_sap
comma
id|skb
comma
id|dest
comma
id|snap_sap-&gt;laddr.lsap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set up the SNAP layer&n; */
DECL|variable|register_snap_client
id|EXPORT_SYMBOL
c_func
(paren
id|register_snap_client
)paren
suffix:semicolon
DECL|variable|unregister_snap_client
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_snap_client
)paren
suffix:semicolon
DECL|function|snap_init
r_static
r_int
id|__init
id|snap_init
c_func
(paren
r_void
)paren
(brace
id|snap_sap
op_assign
id|llc_sap_open
c_func
(paren
id|snap_indicate
comma
l_int|NULL
comma
l_int|0xAA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snap_sap
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SNAP - unable to register with 802.2&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snap_init
id|module_init
c_func
(paren
id|snap_init
)paren
suffix:semicolon
DECL|function|snap_exit
r_static
r_void
id|__exit
id|snap_exit
c_func
(paren
r_void
)paren
(brace
id|llc_sap_close
c_func
(paren
id|snap_sap
)paren
suffix:semicolon
)brace
DECL|variable|snap_exit
id|module_exit
c_func
(paren
id|snap_exit
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Register SNAP clients. We don&squot;t yet use this for IP.&n; */
DECL|function|register_snap_client
r_struct
id|datalink_proto
op_star
id|register_snap_client
c_func
(paren
r_int
r_char
op_star
id|desc
comma
r_int
(paren
op_star
id|rcvfunc
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|packet_type
op_star
)paren
)paren
(brace
r_struct
id|datalink_proto
op_star
id|proto
op_assign
l_int|NULL
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|find_snap_client
c_func
(paren
id|desc
)paren
)paren
r_goto
id|out
suffix:semicolon
id|proto
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|proto
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proto
)paren
(brace
id|memcpy
c_func
(paren
id|proto-&gt;type
comma
id|desc
comma
l_int|5
)paren
suffix:semicolon
id|proto-&gt;rcvfunc
op_assign
id|rcvfunc
suffix:semicolon
id|proto-&gt;header_length
op_assign
l_int|5
op_plus
l_int|3
suffix:semicolon
multiline_comment|/* snap + 802.2 */
id|proto-&gt;request
op_assign
id|snap_request
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|proto-&gt;node
comma
op_amp
id|snap_list
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
id|proto
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Unregister SNAP clients. Protocols no longer want to play with us ...&n; */
DECL|function|unregister_snap_client
r_void
id|unregister_snap_client
c_func
(paren
r_struct
id|datalink_proto
op_star
id|proto
)paren
(brace
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|proto-&gt;node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|proto
)paren
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
