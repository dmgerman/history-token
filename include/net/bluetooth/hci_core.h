multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/* &n; * $Id: hci_core.h,v 1.3 2002/04/17 18:55:21 maxk Exp $ &n; */
macro_line|#ifndef __HCI_CORE_H
DECL|macro|__HCI_CORE_H
mdefine_line|#define __HCI_CORE_H
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/bluetooth/hci.h&gt;
multiline_comment|/* HCI upper protocols */
DECL|macro|HCI_PROTO_L2CAP
mdefine_line|#define HCI_PROTO_L2CAP&t;0
DECL|macro|HCI_PROTO_SCO
mdefine_line|#define HCI_PROTO_SCO&t;1
DECL|macro|HCI_INIT_TIMEOUT
mdefine_line|#define HCI_INIT_TIMEOUT (HZ * 10)
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_bt_hci
suffix:semicolon
multiline_comment|/* HCI Core structures */
DECL|struct|inquiry_entry
r_struct
id|inquiry_entry
(brace
DECL|member|next
r_struct
id|inquiry_entry
op_star
id|next
suffix:semicolon
DECL|member|timestamp
id|__u32
id|timestamp
suffix:semicolon
DECL|member|info
r_struct
id|inquiry_info
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|inquiry_cache
r_struct
id|inquiry_cache
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|timestamp
id|__u32
id|timestamp
suffix:semicolon
DECL|member|list
r_struct
id|inquiry_entry
op_star
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_conn_hash
r_struct
id|hci_conn_hash
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_dev
r_struct
id|hci_dev
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|id
id|__u16
id|id
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|features
id|__u8
id|features
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pkt_type
id|__u16
id|pkt_type
suffix:semicolon
DECL|member|link_policy
id|__u16
id|link_policy
suffix:semicolon
DECL|member|link_mode
id|__u16
id|link_mode
suffix:semicolon
DECL|member|cmd_cnt
id|atomic_t
id|cmd_cnt
suffix:semicolon
DECL|member|acl_cnt
r_int
r_int
id|acl_cnt
suffix:semicolon
DECL|member|sco_cnt
r_int
r_int
id|sco_cnt
suffix:semicolon
DECL|member|acl_mtu
r_int
r_int
id|acl_mtu
suffix:semicolon
DECL|member|sco_mtu
r_int
r_int
id|sco_mtu
suffix:semicolon
DECL|member|acl_pkts
r_int
r_int
id|acl_pkts
suffix:semicolon
DECL|member|sco_pkts
r_int
r_int
id|sco_pkts
suffix:semicolon
DECL|member|cmd_last_tx
r_int
r_int
id|cmd_last_tx
suffix:semicolon
DECL|member|acl_last_tx
r_int
r_int
id|acl_last_tx
suffix:semicolon
DECL|member|sco_last_tx
r_int
r_int
id|sco_last_tx
suffix:semicolon
DECL|member|cmd_task
r_struct
id|tasklet_struct
id|cmd_task
suffix:semicolon
DECL|member|rx_task
r_struct
id|tasklet_struct
id|rx_task
suffix:semicolon
DECL|member|tx_task
r_struct
id|tasklet_struct
id|tx_task
suffix:semicolon
DECL|member|rx_q
r_struct
id|sk_buff_head
id|rx_q
suffix:semicolon
DECL|member|raw_q
r_struct
id|sk_buff_head
id|raw_q
suffix:semicolon
DECL|member|cmd_q
r_struct
id|sk_buff_head
id|cmd_q
suffix:semicolon
DECL|member|sent_cmd
r_struct
id|sk_buff
op_star
id|sent_cmd
suffix:semicolon
DECL|member|req_lock
r_struct
id|semaphore
id|req_lock
suffix:semicolon
DECL|member|req_wait_q
id|wait_queue_head_t
id|req_wait_q
suffix:semicolon
DECL|member|req_status
id|__u32
id|req_status
suffix:semicolon
DECL|member|req_result
id|__u32
id|req_result
suffix:semicolon
DECL|member|inq_cache
r_struct
id|inquiry_cache
id|inq_cache
suffix:semicolon
DECL|member|conn_hash
r_struct
id|hci_conn_hash
id|conn_hash
suffix:semicolon
DECL|member|stat
r_struct
id|hci_dev_stats
id|stat
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
DECL|member|core_data
r_void
op_star
id|core_data
suffix:semicolon
DECL|member|promisc
id|atomic_t
id|promisc
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|proc
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
macro_line|#endif
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
DECL|member|flush
r_int
(paren
op_star
id|flush
)paren
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
DECL|member|send
r_int
(paren
op_star
id|send
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|destruct
r_void
(paren
op_star
id|destruct
)paren
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_conn
r_struct
id|hci_conn
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|dst
id|bdaddr_t
id|dst
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|state
id|__u16
id|state
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|out
id|__u8
id|out
suffix:semicolon
DECL|member|link_mode
id|__u32
id|link_mode
suffix:semicolon
DECL|member|pend
r_int
r_int
id|pend
suffix:semicolon
DECL|member|sent
r_int
r_int
id|sent
suffix:semicolon
DECL|member|data_q
r_struct
id|sk_buff_head
id|data_q
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|hdev
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
DECL|member|l2cap_data
r_void
op_star
id|l2cap_data
suffix:semicolon
DECL|member|sco_data
r_void
op_star
id|sco_data
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|link
r_struct
id|hci_conn
op_star
id|link
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|hci_proto
op_star
id|hci_proto
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|list_head
id|hci_dev_list
suffix:semicolon
r_extern
id|rwlock_t
id|hci_dev_list_lock
suffix:semicolon
multiline_comment|/* ----- Inquiry cache ----- */
DECL|macro|INQUIRY_CACHE_AGE_MAX
mdefine_line|#define INQUIRY_CACHE_AGE_MAX   (HZ*30)   
singleline_comment|// 30 seconds
DECL|macro|INQUIRY_ENTRY_AGE_MAX
mdefine_line|#define INQUIRY_ENTRY_AGE_MAX   (HZ*60)   
singleline_comment|// 60 seconds
DECL|macro|inquiry_cache_lock
mdefine_line|#define inquiry_cache_lock(c)&t;&t;spin_lock(&amp;c-&gt;lock)
DECL|macro|inquiry_cache_unlock
mdefine_line|#define inquiry_cache_unlock(c)&t;&t;spin_unlock(&amp;c-&gt;lock)
DECL|macro|inquiry_cache_lock_bh
mdefine_line|#define inquiry_cache_lock_bh(c)&t;spin_lock_bh(&amp;c-&gt;lock)
DECL|macro|inquiry_cache_unlock_bh
mdefine_line|#define inquiry_cache_unlock_bh(c)&t;spin_unlock_bh(&amp;c-&gt;lock)
DECL|function|inquiry_cache_init
r_static
r_inline
r_void
id|inquiry_cache_init
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|inquiry_cache
op_star
id|c
op_assign
op_amp
id|hdev-&gt;inq_cache
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|c-&gt;lock
)paren
suffix:semicolon
id|c-&gt;list
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|inquiry_cache_age
r_static
r_inline
r_int
id|inquiry_cache_age
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|inquiry_cache
op_star
id|c
op_assign
op_amp
id|hdev-&gt;inq_cache
suffix:semicolon
r_return
id|jiffies
op_minus
id|c-&gt;timestamp
suffix:semicolon
)brace
DECL|function|inquiry_entry_age
r_static
r_inline
r_int
id|inquiry_entry_age
c_func
(paren
r_struct
id|inquiry_entry
op_star
id|e
)paren
(brace
r_return
id|jiffies
op_minus
id|e-&gt;timestamp
suffix:semicolon
)brace
r_struct
id|inquiry_entry
op_star
id|inquiry_cache_lookup
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|bdaddr_t
op_star
id|bdaddr
)paren
suffix:semicolon
r_void
id|inquiry_cache_update
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_struct
id|inquiry_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|inquiry_cache_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
r_int
id|inquiry_cache_dump
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
id|num
comma
id|__u8
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* ----- HCI Connections ----- */
r_enum
(brace
DECL|enumerator|HCI_CONN_AUTH_PEND
id|HCI_CONN_AUTH_PEND
comma
DECL|enumerator|HCI_CONN_ENCRYPT_PEND
id|HCI_CONN_ENCRYPT_PEND
)brace
suffix:semicolon
DECL|function|hci_conn_hash_init
r_static
r_inline
r_void
id|hci_conn_hash_init
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
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|h-&gt;list
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|h-&gt;lock
)paren
suffix:semicolon
id|h-&gt;num
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|hci_conn_hash_add
r_static
r_inline
r_void
id|hci_conn_hash_add
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_struct
id|hci_conn
op_star
id|c
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
id|list_add
c_func
(paren
op_amp
id|c-&gt;list
comma
op_amp
id|h-&gt;list
)paren
suffix:semicolon
id|h-&gt;num
op_increment
suffix:semicolon
)brace
DECL|function|hci_conn_hash_del
r_static
r_inline
r_void
id|hci_conn_hash_del
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_struct
id|hci_conn
op_star
id|c
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
id|list_del
c_func
(paren
op_amp
id|c-&gt;list
)paren
suffix:semicolon
id|h-&gt;num
op_decrement
suffix:semicolon
)brace
DECL|function|hci_conn_hash_lookup_handle
r_static
r_inline
r_struct
id|hci_conn
op_star
id|hci_conn_hash_lookup_handle
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|__u16
id|handle
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
r_struct
id|hci_conn
op_star
id|c
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|h-&gt;list
)paren
(brace
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
r_if
c_cond
(paren
id|c-&gt;handle
op_eq
id|handle
)paren
r_return
id|c
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hci_conn_hash_lookup_ba
r_static
r_inline
r_struct
id|hci_conn
op_star
id|hci_conn_hash_lookup_ba
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|__u8
id|type
comma
id|bdaddr_t
op_star
id|ba
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
r_struct
id|hci_conn
op_star
id|c
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|h-&gt;list
)paren
(brace
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
r_if
c_cond
(paren
id|c-&gt;type
op_eq
id|type
op_logical_and
op_logical_neg
id|bacmp
c_func
(paren
op_amp
id|c-&gt;dst
comma
id|ba
)paren
)paren
r_return
id|c
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
id|hci_acl_connect
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
r_int
id|hci_conn_del
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
suffix:semicolon
r_void
id|hci_conn_hash_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
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
id|src
)paren
suffix:semicolon
r_int
id|hci_conn_auth
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
suffix:semicolon
r_int
id|hci_conn_encrypt
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
suffix:semicolon
DECL|function|hci_conn_set_timer
r_static
r_inline
r_void
id|hci_conn_set_timer
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
r_int
id|timeout
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|conn-&gt;timer
comma
id|jiffies
op_plus
id|timeout
)paren
suffix:semicolon
)brace
DECL|function|hci_conn_del_timer
r_static
r_inline
r_void
id|hci_conn_del_timer
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|conn-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|hci_conn_hold
r_static
r_inline
r_void
id|hci_conn_hold
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|conn-&gt;refcnt
)paren
suffix:semicolon
id|hci_conn_del_timer
c_func
(paren
id|conn
)paren
suffix:semicolon
)brace
DECL|function|hci_conn_put
r_static
r_inline
r_void
id|hci_conn_put
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|conn-&gt;refcnt
)paren
op_logical_and
id|conn-&gt;out
)paren
id|hci_conn_set_timer
c_func
(paren
id|conn
comma
id|HCI_DISCONN_TIMEOUT
)paren
suffix:semicolon
)brace
multiline_comment|/* ----- HCI tasks ----- */
DECL|function|hci_sched_cmd
r_static
r_inline
r_void
id|hci_sched_cmd
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|tasklet_schedule
c_func
(paren
op_amp
id|hdev-&gt;cmd_task
)paren
suffix:semicolon
)brace
DECL|function|hci_sched_rx
r_static
r_inline
r_void
id|hci_sched_rx
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|tasklet_schedule
c_func
(paren
op_amp
id|hdev-&gt;rx_task
)paren
suffix:semicolon
)brace
DECL|function|hci_sched_tx
r_static
r_inline
r_void
id|hci_sched_tx
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|tasklet_schedule
c_func
(paren
op_amp
id|hdev-&gt;tx_task
)paren
suffix:semicolon
)brace
multiline_comment|/* ----- HCI Devices ----- */
DECL|function|hci_dev_put
r_static
r_inline
r_void
id|hci_dev_put
c_func
(paren
r_struct
id|hci_dev
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|d-&gt;refcnt
)paren
)paren
id|d
op_member_access_from_pointer
id|destruct
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
DECL|macro|hci_dev_hold
mdefine_line|#define hci_dev_hold(d)&t;&t;atomic_inc(&amp;d-&gt;refcnt)
DECL|macro|hci_dev_lock
mdefine_line|#define hci_dev_lock(d)&t;&t;spin_lock(&amp;d-&gt;lock)
DECL|macro|hci_dev_unlock
mdefine_line|#define hci_dev_unlock(d)&t;spin_unlock(&amp;d-&gt;lock)
DECL|macro|hci_dev_lock_bh
mdefine_line|#define hci_dev_lock_bh(d)&t;spin_lock_bh(&amp;d-&gt;lock)
DECL|macro|hci_dev_unlock_bh
mdefine_line|#define hci_dev_unlock_bh(d)&t;spin_unlock_bh(&amp;d-&gt;lock)
r_struct
id|hci_dev
op_star
id|hci_dev_get
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hci_get_route
c_func
(paren
id|bdaddr_t
op_star
id|src
comma
id|bdaddr_t
op_star
id|dst
)paren
suffix:semicolon
r_int
id|hci_register_dev
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
r_int
id|hci_unregister_dev
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
r_int
id|hci_suspend_dev
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
r_int
id|hci_resume_dev
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
r_int
id|hci_dev_open
c_func
(paren
id|__u16
id|dev
)paren
suffix:semicolon
r_int
id|hci_dev_close
c_func
(paren
id|__u16
id|dev
)paren
suffix:semicolon
r_int
id|hci_dev_reset
c_func
(paren
id|__u16
id|dev
)paren
suffix:semicolon
r_int
id|hci_dev_reset_stat
c_func
(paren
id|__u16
id|dev
)paren
suffix:semicolon
r_int
id|hci_dev_cmd
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|hci_get_dev_list
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|hci_get_dev_info
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|hci_get_conn_list
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
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
suffix:semicolon
r_int
id|hci_inquiry
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
r_void
id|hci_event_packet
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Receive frame from HCI drivers */
DECL|function|hci_recv_frame
r_static
r_inline
r_int
id|hci_recv_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
(paren
r_struct
id|hci_dev
op_star
)paren
id|skb-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
op_logical_or
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_UP
comma
op_amp
id|hdev-&gt;flags
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_INIT
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Incomming skb */
id|bt_cb
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|incoming
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Time stamp */
id|do_gettimeofday
c_func
(paren
op_amp
id|skb-&gt;stamp
)paren
suffix:semicolon
multiline_comment|/* Queue frame for rx task */
id|skb_queue_tail
c_func
(paren
op_amp
id|hdev-&gt;rx_q
comma
id|skb
)paren
suffix:semicolon
id|hci_sched_rx
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|hci_dev_proc_init
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
r_void
id|hci_dev_proc_cleanup
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
suffix:semicolon
multiline_comment|/* ----- LMP capabilities ----- */
DECL|macro|lmp_rswitch_capable
mdefine_line|#define lmp_rswitch_capable(dev) (dev-&gt;features[0] &amp; LMP_RSWITCH)
DECL|macro|lmp_encrypt_capable
mdefine_line|#define lmp_encrypt_capable(dev) (dev-&gt;features[0] &amp; LMP_ENCRYPT)
multiline_comment|/* ----- HCI protocols ----- */
DECL|struct|hci_proto
r_struct
id|hci_proto
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|connect_ind
r_int
(paren
op_star
id|connect_ind
)paren
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|bdaddr_t
op_star
id|bdaddr
comma
id|__u8
id|type
)paren
suffix:semicolon
DECL|member|connect_cfm
r_int
(paren
op_star
id|connect_cfm
)paren
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|status
)paren
suffix:semicolon
DECL|member|disconn_ind
r_int
(paren
op_star
id|disconn_ind
)paren
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|reason
)paren
suffix:semicolon
DECL|member|recv_acldata
r_int
(paren
op_star
id|recv_acldata
)paren
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u16
id|flags
)paren
suffix:semicolon
DECL|member|recv_scodata
r_int
(paren
op_star
id|recv_scodata
)paren
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|auth_cfm
r_int
(paren
op_star
id|auth_cfm
)paren
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|status
)paren
suffix:semicolon
DECL|member|encrypt_cfm
r_int
(paren
op_star
id|encrypt_cfm
)paren
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|status
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hci_proto_connect_ind
r_static
r_inline
r_int
id|hci_proto_connect_ind
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|bdaddr_t
op_star
id|bdaddr
comma
id|__u8
id|type
)paren
(brace
r_register
r_struct
id|hci_proto
op_star
id|hp
suffix:semicolon
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_L2CAP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;connect_ind
)paren
id|mask
op_or_assign
id|hp
op_member_access_from_pointer
id|connect_ind
c_func
(paren
id|hdev
comma
id|bdaddr
comma
id|type
)paren
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_SCO
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;connect_ind
)paren
id|mask
op_or_assign
id|hp
op_member_access_from_pointer
id|connect_ind
c_func
(paren
id|hdev
comma
id|bdaddr
comma
id|type
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|hci_proto_connect_cfm
r_static
r_inline
r_void
id|hci_proto_connect_cfm
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|status
)paren
(brace
r_register
r_struct
id|hci_proto
op_star
id|hp
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_L2CAP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;connect_cfm
)paren
id|hp
op_member_access_from_pointer
id|connect_cfm
c_func
(paren
id|conn
comma
id|status
)paren
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_SCO
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;connect_cfm
)paren
id|hp
op_member_access_from_pointer
id|connect_cfm
c_func
(paren
id|conn
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|hci_proto_disconn_ind
r_static
r_inline
r_void
id|hci_proto_disconn_ind
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
r_register
r_struct
id|hci_proto
op_star
id|hp
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_L2CAP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;disconn_ind
)paren
id|hp
op_member_access_from_pointer
id|disconn_ind
c_func
(paren
id|conn
comma
id|reason
)paren
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_SCO
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;disconn_ind
)paren
id|hp
op_member_access_from_pointer
id|disconn_ind
c_func
(paren
id|conn
comma
id|reason
)paren
suffix:semicolon
)brace
DECL|function|hci_proto_auth_cfm
r_static
r_inline
r_void
id|hci_proto_auth_cfm
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|status
)paren
(brace
r_register
r_struct
id|hci_proto
op_star
id|hp
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_L2CAP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;auth_cfm
)paren
id|hp
op_member_access_from_pointer
id|auth_cfm
c_func
(paren
id|conn
comma
id|status
)paren
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_SCO
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;auth_cfm
)paren
id|hp
op_member_access_from_pointer
id|auth_cfm
c_func
(paren
id|conn
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|hci_proto_encrypt_cfm
r_static
r_inline
r_void
id|hci_proto_encrypt_cfm
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
id|__u8
id|status
)paren
(brace
r_register
r_struct
id|hci_proto
op_star
id|hp
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_L2CAP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;encrypt_cfm
)paren
id|hp
op_member_access_from_pointer
id|encrypt_cfm
c_func
(paren
id|conn
comma
id|status
)paren
suffix:semicolon
id|hp
op_assign
id|hci_proto
(braket
id|HCI_PROTO_SCO
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_logical_and
id|hp-&gt;encrypt_cfm
)paren
id|hp
op_member_access_from_pointer
id|encrypt_cfm
c_func
(paren
id|conn
comma
id|status
)paren
suffix:semicolon
)brace
r_int
id|hci_register_proto
c_func
(paren
r_struct
id|hci_proto
op_star
id|hproto
)paren
suffix:semicolon
r_int
id|hci_unregister_proto
c_func
(paren
r_struct
id|hci_proto
op_star
id|hproto
)paren
suffix:semicolon
r_int
id|hci_register_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_int
id|hci_unregister_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_int
id|hci_send_cmd
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|__u16
id|ogf
comma
id|__u16
id|ocf
comma
id|__u32
id|plen
comma
r_void
op_star
id|param
)paren
suffix:semicolon
r_int
id|hci_send_acl
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u16
id|flags
)paren
suffix:semicolon
r_int
id|hci_send_sco
c_func
(paren
r_struct
id|hci_conn
op_star
id|conn
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|hci_send_raw
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
op_star
id|hci_sent_cmd_data
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
id|__u16
id|ogf
comma
id|__u16
id|ocf
)paren
suffix:semicolon
r_void
id|hci_si_event
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
r_int
id|dlen
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* ----- HCI Sockets ----- */
r_void
id|hci_send_to_sock
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* HCI info for socket */
DECL|macro|hci_pi
mdefine_line|#define hci_pi(sk)&t;((struct hci_pinfo *) sk-&gt;protinfo)
DECL|struct|hci_pinfo
r_struct
id|hci_pinfo
(brace
DECL|member|hdev
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
DECL|member|filter
r_struct
id|hci_filter
id|filter
suffix:semicolon
DECL|member|cmsg_mask
id|__u32
id|cmsg_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* HCI security filter */
DECL|macro|HCI_SFLT_MAX_OGF
mdefine_line|#define HCI_SFLT_MAX_OGF 4
DECL|struct|hci_sec_filter
r_struct
id|hci_sec_filter
(brace
DECL|member|type_mask
r_int
r_int
id|type_mask
suffix:semicolon
DECL|member|event_mask
r_int
r_int
id|event_mask
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ocf_mask
r_int
r_int
id|ocf_mask
(braket
id|HCI_SFLT_MAX_OGF
op_plus
l_int|1
)braket
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----- HCI requests ----- */
DECL|macro|HCI_REQ_DONE
mdefine_line|#define HCI_REQ_DONE&t;  0
DECL|macro|HCI_REQ_PEND
mdefine_line|#define HCI_REQ_PEND&t;  1
DECL|macro|HCI_REQ_CANCELED
mdefine_line|#define HCI_REQ_CANCELED  2
DECL|macro|hci_req_lock
mdefine_line|#define hci_req_lock(d)&t;&t;down(&amp;d-&gt;req_lock)
DECL|macro|hci_req_unlock
mdefine_line|#define hci_req_unlock(d)&t;up(&amp;d-&gt;req_lock)
r_void
id|hci_req_complete
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
id|result
)paren
suffix:semicolon
r_void
id|hci_req_cancel
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
comma
r_int
id|err
)paren
suffix:semicolon
macro_line|#endif /* __HCI_CORE_H */
eof
