multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * HCI Connection handling.&n; *&n; * $Id: hci_conn.c,v 1.2 2002/04/17 17:37:16 maxk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#ifndef CONFIG_BT_HCI_CORE_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
macro_line|#endif
DECL|function|hci_acl_connect
r_void
id|hci_acl_connect
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|conn-&gt;hdev
suffix:semicolon
r_struct
id|inquiry_entry
op_star
id|ie
suffix:semicolon
r_struct
id|hci_cp_create_conn
id|cp
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%p&quot;
comma
id|conn
)paren
suffix:semicolon
id|conn-&gt;state
op_assign
id|BT_CONNECT
suffix:semicolon
id|conn-&gt;out
op_assign
l_int|1
suffix:semicolon
id|conn-&gt;link_mode
op_assign
id|HCI_LM_MASTER
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cp
comma
l_int|0
comma
r_sizeof
(paren
id|cp
)paren
)paren
suffix:semicolon
id|bacpy
c_func
(paren
op_amp
id|cp.bdaddr
comma
op_amp
id|conn-&gt;dst
)paren
suffix:semicolon
id|cp.pscan_rep_mode
op_assign
l_int|0x02
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ie
op_assign
id|inquiry_cache_lookup
c_func
(paren
id|hdev
comma
op_amp
id|conn-&gt;dst
)paren
)paren
op_logical_and
id|inquiry_entry_age
c_func
(paren
id|ie
)paren
op_le
id|INQUIRY_ENTRY_AGE_MAX
)paren
(brace
id|cp.pscan_rep_mode
op_assign
id|ie-&gt;info.pscan_rep_mode
suffix:semicolon
id|cp.pscan_mode
op_assign
id|ie-&gt;info.pscan_mode
suffix:semicolon
id|cp.clock_offset
op_assign
id|ie-&gt;info.clock_offset
op_or
id|__cpu_to_le16
c_func
(paren
l_int|0x8000
)paren
suffix:semicolon
)brace
id|cp.pkt_type
op_assign
id|__cpu_to_le16
c_func
(paren
id|hdev-&gt;pkt_type
op_amp
id|ACL_PTYPE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lmp_rswitch_capable
c_func
(paren
id|hdev
)paren
op_logical_and
op_logical_neg
(paren
id|hdev-&gt;link_mode
op_amp
id|HCI_LM_MASTER
)paren
)paren
id|cp.role_switch
op_assign
l_int|0x01
suffix:semicolon
r_else
id|cp.role_switch
op_assign
l_int|0x00
suffix:semicolon
id|hci_send_cmd
c_func
(paren
id|hdev
comma
id|OGF_LINK_CTL
comma
id|OCF_CREATE_CONN
comma
r_sizeof
(paren
id|cp
)paren
comma
op_amp
id|cp
)paren
suffix:semicolon
)brace
DECL|function|hci_acl_disconn
r_void
id|hci_acl_disconn
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|reason
)paren
(brace
r_struct
id|hci_cp_disconnect
id|cp
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%p&quot;
comma
id|conn
)paren
suffix:semicolon
id|conn-&gt;state
op_assign
id|BT_DISCONN
suffix:semicolon
id|cp.handle
op_assign
id|__cpu_to_le16
c_func
(paren
id|conn-&gt;handle
)paren
suffix:semicolon
id|cp.reason
op_assign
id|reason
suffix:semicolon
id|hci_send_cmd
c_func
(paren
id|conn-&gt;hdev
comma
id|OGF_LINK_CTL
comma
id|OCF_DISCONNECT
comma
r_sizeof
(paren
id|cp
)paren
comma
op_amp
id|cp
)paren
suffix:semicolon
)brace
DECL|function|hci_add_sco
r_void
id|hci_add_sco
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u16
id|handle
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|conn-&gt;hdev
suffix:semicolon
r_struct
id|hci_cp_add_sco
id|cp
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%p&quot;
comma
id|conn
)paren
suffix:semicolon
id|conn-&gt;state
op_assign
id|BT_CONNECT
suffix:semicolon
id|conn-&gt;out
op_assign
l_int|1
suffix:semicolon
id|cp.pkt_type
op_assign
id|__cpu_to_le16
c_func
(paren
id|hdev-&gt;pkt_type
op_amp
id|SCO_PTYPE_MASK
)paren
suffix:semicolon
id|cp.handle
op_assign
id|__cpu_to_le16
c_func
(paren
id|handle
)paren
suffix:semicolon
id|hci_send_cmd
c_func
(paren
id|hdev
comma
id|OGF_LINK_CTL
comma
id|OCF_ADD_SCO
comma
r_sizeof
(paren
id|cp
)paren
comma
op_amp
id|cp
)paren
suffix:semicolon
)brace
DECL|function|hci_conn_timeout
r_static
r_void
id|hci_conn_timeout
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hci_conn
op_star
id|conn
op_assign
(paren
r_void
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|conn-&gt;hdev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;conn %p state %d&quot;
comma
id|conn
comma
id|conn-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|conn-&gt;refcnt
)paren
)paren
r_return
suffix:semicolon
id|hci_dev_lock
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;state
op_eq
id|BT_CONNECTED
)paren
id|hci_acl_disconn
c_func
(paren
id|conn
comma
l_int|0x13
)paren
suffix:semicolon
r_else
id|conn-&gt;state
op_assign
id|BT_CLOSED
suffix:semicolon
id|hci_dev_unlock
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|hci_conn_init_timer
r_static
r_void
id|hci_conn_init_timer
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|conn-&gt;timer
)paren
suffix:semicolon
id|conn-&gt;timer.function
op_assign
id|hci_conn_timeout
suffix:semicolon
id|conn-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|conn
suffix:semicolon
)brace
DECL|function|hci_conn_add
r_struct
id|hci_conn
op_star
id|hci_conn_add
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
id|type
comma
id|bdaddr_t
op_star
id|dst
)paren
(brace
r_struct
id|hci_conn
op_star
id|conn
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%s dst %s&quot;
comma
id|hdev-&gt;name
comma
id|batostr
c_func
(paren
id|dst
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|conn
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hci_conn
)paren
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|conn
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hci_conn
)paren
)paren
suffix:semicolon
id|bacpy
c_func
(paren
op_amp
id|conn-&gt;dst
comma
id|dst
)paren
suffix:semicolon
id|conn-&gt;type
op_assign
id|type
suffix:semicolon
id|conn-&gt;hdev
op_assign
id|hdev
suffix:semicolon
id|conn-&gt;state
op_assign
id|BT_OPEN
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|conn-&gt;data_q
)paren
suffix:semicolon
id|hci_conn_init_timer
c_func
(paren
id|conn
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|conn-&gt;refcnt
comma
l_int|0
)paren
suffix:semicolon
id|hci_dev_hold
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|tasklet_disable
c_func
(paren
op_amp
id|hdev-&gt;tx_task
)paren
suffix:semicolon
id|hci_conn_hash_add
c_func
(paren
id|hdev
comma
id|conn
)paren
suffix:semicolon
id|tasklet_enable
c_func
(paren
op_amp
id|hdev-&gt;tx_task
)paren
suffix:semicolon
r_return
id|conn
suffix:semicolon
)brace
DECL|function|hci_conn_del
r_int
id|hci_conn_del
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|conn-&gt;hdev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%s conn %p handle %d&quot;
comma
id|hdev-&gt;name
comma
id|conn
comma
id|conn-&gt;handle
)paren
suffix:semicolon
id|hci_conn_del_timer
c_func
(paren
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;type
op_eq
id|SCO_LINK
)paren
(brace
r_struct
id|hci_conn
op_star
id|acl
op_assign
id|conn-&gt;link
suffix:semicolon
r_if
c_cond
(paren
id|acl
)paren
(brace
id|acl-&gt;link
op_assign
l_int|NULL
suffix:semicolon
id|hci_conn_put
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|hci_conn
op_star
id|sco
op_assign
id|conn-&gt;link
suffix:semicolon
r_if
c_cond
(paren
id|sco
)paren
id|sco-&gt;link
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Unacked frames */
id|hdev-&gt;acl_cnt
op_add_assign
id|conn-&gt;sent
suffix:semicolon
)brace
id|tasklet_disable
c_func
(paren
op_amp
id|hdev-&gt;tx_task
)paren
suffix:semicolon
id|hci_conn_hash_del
c_func
(paren
id|hdev
comma
id|conn
)paren
suffix:semicolon
id|tasklet_enable
c_func
(paren
op_amp
id|hdev-&gt;tx_task
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|conn-&gt;data_q
)paren
suffix:semicolon
id|hci_dev_put
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_get_route
r_struct
id|hci_dev
op_star
id|hci_get_route
c_func
(paren
id|bdaddr_t
op_star
id|dst
comma
id|bdaddr_t
op_star
id|src
)paren
(brace
r_int
id|use_src
op_assign
id|bacmp
c_func
(paren
id|src
comma
id|BDADDR_ANY
)paren
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%s -&gt; %s&quot;
comma
id|batostr
c_func
(paren
id|src
)paren
comma
id|batostr
c_func
(paren
id|dst
)paren
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|hci_dev_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|hci_dev_list
)paren
(brace
r_struct
id|hci_dev
op_star
id|d
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|hci_dev
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_UP
comma
op_amp
id|d-&gt;flags
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Simple routing: &n;&t; &t; * &t;No source address - find interface with bdaddr != dst &n;&t; &t; *&t;Source address &t;  - find interface with bdaddr == src &n;&t; &t; */
r_if
c_cond
(paren
id|use_src
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bacmp
c_func
(paren
op_amp
id|d-&gt;bdaddr
comma
id|src
)paren
)paren
(brace
id|hdev
op_assign
id|d
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|bacmp
c_func
(paren
op_amp
id|d-&gt;bdaddr
comma
id|dst
)paren
)paren
(brace
id|hdev
op_assign
id|d
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|hdev
)paren
id|hdev
op_assign
id|hci_dev_hold
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|hci_dev_list_lock
)paren
suffix:semicolon
r_return
id|hdev
suffix:semicolon
)brace
multiline_comment|/* Create SCO or ACL connection.&n; * Device _must_ be locked */
DECL|function|hci_connect
r_struct
id|hci_conn
op_star
id|hci_connect
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
id|type
comma
id|bdaddr_t
op_star
id|dst
)paren
(brace
r_struct
id|hci_conn
op_star
id|acl
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%s dst %s&quot;
comma
id|hdev-&gt;name
comma
id|batostr
c_func
(paren
id|dst
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|acl
op_assign
id|hci_conn_hash_lookup_ba
c_func
(paren
id|hdev
comma
id|ACL_LINK
comma
id|dst
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|acl
op_assign
id|hci_conn_add
c_func
(paren
id|hdev
comma
id|ACL_LINK
comma
id|dst
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
id|hci_conn_hold
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl-&gt;state
op_eq
id|BT_OPEN
op_logical_or
id|acl-&gt;state
op_eq
id|BT_CLOSED
)paren
id|hci_acl_connect
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|SCO_LINK
)paren
(brace
r_struct
id|hci_conn
op_star
id|sco
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sco
op_assign
id|hci_conn_hash_lookup_ba
c_func
(paren
id|hdev
comma
id|SCO_LINK
comma
id|dst
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sco
op_assign
id|hci_conn_add
c_func
(paren
id|hdev
comma
id|SCO_LINK
comma
id|dst
)paren
)paren
)paren
(brace
id|hci_conn_put
c_func
(paren
id|acl
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|acl-&gt;link
op_assign
id|sco
suffix:semicolon
id|sco-&gt;link
op_assign
id|acl
suffix:semicolon
id|hci_conn_hold
c_func
(paren
id|sco
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl-&gt;state
op_eq
id|BT_CONNECTED
op_logical_and
(paren
id|sco-&gt;state
op_eq
id|BT_OPEN
op_logical_or
id|sco-&gt;state
op_eq
id|BT_CLOSED
)paren
)paren
id|hci_add_sco
c_func
(paren
id|sco
comma
id|acl-&gt;handle
)paren
suffix:semicolon
r_return
id|sco
suffix:semicolon
)brace
r_else
(brace
r_return
id|acl
suffix:semicolon
)brace
)brace
multiline_comment|/* Authenticate remote device */
DECL|function|hci_conn_auth
r_int
id|hci_conn_auth
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;conn %p&quot;
comma
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;link_mode
op_amp
id|HCI_LM_AUTH
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|HCI_CONN_AUTH_PEND
comma
op_amp
id|conn-&gt;pend
)paren
)paren
(brace
r_struct
id|hci_cp_auth_requested
id|cp
suffix:semicolon
id|cp.handle
op_assign
id|__cpu_to_le16
c_func
(paren
id|conn-&gt;handle
)paren
suffix:semicolon
id|hci_send_cmd
c_func
(paren
id|conn-&gt;hdev
comma
id|OGF_LINK_CTL
comma
id|OCF_AUTH_REQUESTED
comma
r_sizeof
(paren
id|cp
)paren
comma
op_amp
id|cp
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable encryption */
DECL|function|hci_conn_encrypt
r_int
id|hci_conn_encrypt
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;conn %p&quot;
comma
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;link_mode
op_amp
id|HCI_LM_ENCRYPT
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|HCI_CONN_ENCRYPT_PEND
comma
op_amp
id|conn-&gt;pend
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hci_conn_auth
c_func
(paren
id|conn
)paren
)paren
(brace
r_struct
id|hci_cp_set_conn_encrypt
id|cp
suffix:semicolon
id|cp.handle
op_assign
id|__cpu_to_le16
c_func
(paren
id|conn-&gt;handle
)paren
suffix:semicolon
id|cp.encrypt
op_assign
l_int|1
suffix:semicolon
id|hci_send_cmd
c_func
(paren
id|conn-&gt;hdev
comma
id|OGF_LINK_CTL
comma
id|OCF_SET_CONN_ENCRYPT
comma
r_sizeof
(paren
id|cp
)paren
comma
op_amp
id|cp
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Drop all connection on the device */
DECL|function|hci_conn_hash_flush
r_void
id|hci_conn_hash_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|hci_conn_hash
op_star
id|h
op_assign
op_amp
id|hdev-&gt;conn_hash
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %s&quot;
comma
id|hdev-&gt;name
)paren
suffix:semicolon
id|p
op_assign
id|h-&gt;list.next
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
op_amp
id|h-&gt;list
)paren
(brace
r_struct
id|hci_conn
op_star
id|c
suffix:semicolon
id|c
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|hci_conn
comma
id|list
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|c-&gt;state
op_assign
id|BT_CLOSED
suffix:semicolon
id|hci_proto_disconn_ind
c_func
(paren
id|c
comma
l_int|0x16
)paren
suffix:semicolon
id|hci_conn_del
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
DECL|function|hci_get_conn_list
r_int
id|hci_get_conn_list
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hci_conn_list_req
id|req
comma
op_star
id|cl
suffix:semicolon
r_struct
id|hci_conn_info
op_star
id|ci
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_int
id|n
op_assign
l_int|0
comma
id|size
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|req
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|req
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req.conn_num
op_logical_or
id|req.conn_num
OG
(paren
id|PAGE_SIZE
op_star
l_int|2
)paren
op_div
r_sizeof
(paren
op_star
id|ci
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|req
)paren
op_plus
id|req.conn_num
op_star
r_sizeof
(paren
op_star
id|ci
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cl
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hdev
op_assign
id|hci_dev_get
c_func
(paren
id|req.dev_id
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|cl
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ci
op_assign
id|cl-&gt;conn_info
suffix:semicolon
id|hci_dev_lock_bh
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|hdev-&gt;conn_hash.list
)paren
(brace
r_register
r_struct
id|hci_conn
op_star
id|c
suffix:semicolon
id|c
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|hci_conn
comma
id|list
)paren
suffix:semicolon
id|bacpy
c_func
(paren
op_amp
(paren
id|ci
op_plus
id|n
)paren
op_member_access_from_pointer
id|bdaddr
comma
op_amp
id|c-&gt;dst
)paren
suffix:semicolon
(paren
id|ci
op_plus
id|n
)paren
op_member_access_from_pointer
id|handle
op_assign
id|c-&gt;handle
suffix:semicolon
(paren
id|ci
op_plus
id|n
)paren
op_member_access_from_pointer
id|type
op_assign
id|c-&gt;type
suffix:semicolon
(paren
id|ci
op_plus
id|n
)paren
op_member_access_from_pointer
id|out
op_assign
id|c-&gt;out
suffix:semicolon
(paren
id|ci
op_plus
id|n
)paren
op_member_access_from_pointer
id|state
op_assign
id|c-&gt;state
suffix:semicolon
(paren
id|ci
op_plus
id|n
)paren
op_member_access_from_pointer
id|link_mode
op_assign
id|c-&gt;link_mode
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|n
op_ge
id|req.conn_num
)paren
r_break
suffix:semicolon
)brace
id|hci_dev_unlock_bh
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|cl-&gt;dev_id
op_assign
id|hdev-&gt;id
suffix:semicolon
id|cl-&gt;conn_num
op_assign
id|n
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|req
)paren
op_plus
id|n
op_star
r_sizeof
(paren
op_star
id|ci
)paren
suffix:semicolon
id|hci_dev_put
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|cl
comma
id|size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cl
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|hci_get_conn_info
r_int
id|hci_get_conn_info
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hci_conn_info_req
id|req
suffix:semicolon
r_struct
id|hci_conn_info
id|ci
suffix:semicolon
r_struct
id|hci_conn
op_star
id|conn
suffix:semicolon
r_char
op_star
id|ptr
op_assign
(paren
r_void
op_star
)paren
id|arg
op_plus
r_sizeof
(paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|req
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|req
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|hci_dev_lock_bh
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|conn
op_assign
id|hci_conn_hash_lookup_ba
c_func
(paren
id|hdev
comma
id|req.type
comma
op_amp
id|req.bdaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn
)paren
(brace
id|bacpy
c_func
(paren
op_amp
id|ci.bdaddr
comma
op_amp
id|conn-&gt;dst
)paren
suffix:semicolon
id|ci.handle
op_assign
id|conn-&gt;handle
suffix:semicolon
id|ci.type
op_assign
id|conn-&gt;type
suffix:semicolon
id|ci.out
op_assign
id|conn-&gt;out
suffix:semicolon
id|ci.state
op_assign
id|conn-&gt;state
suffix:semicolon
id|ci.link_mode
op_assign
id|conn-&gt;link_mode
suffix:semicolon
)brace
id|hci_dev_unlock_bh
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conn
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|ptr
comma
op_amp
id|ci
comma
r_sizeof
(paren
id|ci
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
