multiline_comment|/*&n; * llc_core.c - Minimum needed routines for sap handling and module init/exit&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;net/llc.h&gt;
DECL|variable|llc_sap_list
id|LIST_HEAD
c_func
(paren
id|llc_sap_list
)paren
suffix:semicolon
DECL|variable|llc_sap_list_lock
id|rwlock_t
id|llc_sap_list_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|llc_station_mac_sa
r_int
r_char
id|llc_station_mac_sa
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/**&n; *&t;llc_sap_alloc - allocates and initializes sap.&n; *&n; *&t;Allocates and initializes sap.&n; */
DECL|function|llc_sap_alloc
r_struct
id|llc_sap
op_star
id|llc_sap_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sap
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap
)paren
(brace
id|memset
c_func
(paren
id|sap
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sap
)paren
)paren
suffix:semicolon
id|sap-&gt;state
op_assign
id|LLC_SAP_STATE_ACTIVE
suffix:semicolon
id|memcpy
c_func
(paren
id|sap-&gt;laddr.mac
comma
id|llc_station_mac_sa
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_add_sap - add sap to station list&n; *&t;@sap: Address of the sap&n; *&n; *&t;Adds a sap to the LLC&squot;s station sap list.&n; */
DECL|function|llc_add_sap
r_void
id|llc_add_sap
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|llc_sap_list_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|sap-&gt;node
comma
op_amp
id|llc_sap_list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|llc_sap_list_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_del_sap - del sap from station list&n; *&t;@sap: Address of the sap&n; *&n; *&t;Removes a sap to the LLC&squot;s station sap list.&n; */
DECL|function|llc_del_sap
r_void
id|llc_del_sap
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|llc_sap_list_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sap-&gt;node
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|llc_sap_list_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_find - searchs a SAP in station&n; *&t;@sap_value: sap to be found&n; *&n; *&t;Searchs for a sap in the sap list of the LLC&squot;s station upon the sap ID.&n; *&t;Returns the sap or %NULL if not found.&n; */
DECL|function|llc_sap_find
r_struct
id|llc_sap
op_star
id|llc_sap_find
c_func
(paren
r_int
r_char
id|sap_value
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|llc_sap_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|llc_sap_list
)paren
(brace
id|sap
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|llc_sap
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap-&gt;laddr.lsap
op_eq
id|sap_value
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry
op_eq
op_amp
id|llc_sap_list
)paren
multiline_comment|/* not found */
id|sap
op_assign
l_int|NULL
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|llc_sap_list_lock
)paren
suffix:semicolon
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_open - open interface to the upper layers.&n; *&t;@lsap: SAP number.&n; *&t;@func: rcv func for datalink protos&n; *&n; *&t;Interface function to upper layer. Each one who wants to get a SAP&n; *&t;(for example NetBEUI) should call this function. Returns the opened&n; *&t;SAP for success, NULL for failure.&n; */
DECL|function|llc_sap_open
r_struct
id|llc_sap
op_star
id|llc_sap_open
c_func
(paren
r_int
r_char
id|lsap
comma
r_int
(paren
op_star
id|func
)paren
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
comma
r_struct
id|packet_type
op_star
id|pt
)paren
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
id|llc_sap_find
c_func
(paren
id|lsap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap
)paren
(brace
multiline_comment|/* SAP already exists */
id|sap
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sap
op_assign
id|llc_sap_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sap
)paren
r_goto
id|out
suffix:semicolon
id|sap-&gt;laddr.lsap
op_assign
id|lsap
suffix:semicolon
id|sap-&gt;rcv_func
op_assign
id|func
suffix:semicolon
id|llc_add_sap
c_func
(paren
id|sap
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_close - close interface for upper layers.&n; *&t;@sap: SAP to be closed.&n; *&n; *&t;Close interface function to upper layer. Each one who wants to&n; *&t;close an open SAP (for example NetBEUI) should call this function.&n; * &t;Removes this sap from the list of saps in the station and then&n; * &t;frees the memory for this sap.&n; */
DECL|function|llc_sap_close
r_void
id|llc_sap_close
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|WARN_ON
c_func
(paren
op_logical_neg
id|hlist_empty
c_func
(paren
op_amp
id|sap-&gt;sk_list.list
)paren
)paren
suffix:semicolon
id|llc_del_sap
c_func
(paren
id|sap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sap
)paren
suffix:semicolon
)brace
DECL|variable|llc_packet_type
r_static
r_struct
id|packet_type
id|llc_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_802_2
)paren
comma
dot
id|func
op_assign
id|llc_rcv
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|llc_tr_packet_type
r_static
r_struct
id|packet_type
id|llc_tr_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_TR_802_2
)paren
comma
dot
id|func
op_assign
id|llc_rcv
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
comma
)brace
suffix:semicolon
DECL|function|llc_init
r_static
r_int
id|__init
id|llc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|dev_base-&gt;next
)paren
id|memcpy
c_func
(paren
id|llc_station_mac_sa
comma
id|dev_base-&gt;next-&gt;dev_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|llc_station_mac_sa
comma
l_int|0
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|llc_packet_type
)paren
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|llc_tr_packet_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|llc_exit
r_static
r_void
id|__exit
id|llc_exit
c_func
(paren
r_void
)paren
(brace
id|dev_remove_pack
c_func
(paren
op_amp
id|llc_packet_type
)paren
suffix:semicolon
id|dev_remove_pack
c_func
(paren
op_amp
id|llc_tr_packet_type
)paren
suffix:semicolon
)brace
DECL|variable|llc_init
id|module_init
c_func
(paren
id|llc_init
)paren
suffix:semicolon
DECL|variable|llc_exit
id|module_exit
c_func
(paren
id|llc_exit
)paren
suffix:semicolon
DECL|variable|llc_station_mac_sa
id|EXPORT_SYMBOL
c_func
(paren
id|llc_station_mac_sa
)paren
suffix:semicolon
DECL|variable|llc_sap_list
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_list
)paren
suffix:semicolon
DECL|variable|llc_sap_list_lock
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_list_lock
)paren
suffix:semicolon
DECL|variable|llc_sap_find
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_find
)paren
suffix:semicolon
DECL|variable|llc_sap_open
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_open
)paren
suffix:semicolon
DECL|variable|llc_sap_close
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_close
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Procom 1997, Jay Schullist 2001, Arnaldo C. Melo 2001-2003&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;LLC IEEE 802.2 core support&quot;
)paren
suffix:semicolon
eof
