multiline_comment|/*&n; * proc_llc.c - proc interface for LLC&n; *&n; * Copyright (c) 2001 by Jay Schulist &lt;jschlst@samba.org&gt;&n; *&t;&t; 2002-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/llc_c_ac.h&gt;
macro_line|#include &lt;net/llc_c_ev.h&gt;
macro_line|#include &lt;net/llc_c_st.h&gt;
macro_line|#include &lt;net/llc_conn.h&gt;
macro_line|#include &lt;net/llc_mac.h&gt;
macro_line|#include &lt;net/llc_main.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
DECL|function|llc_ui_format_mac
r_static
r_void
id|llc_ui_format_mac
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_int
r_char
op_star
id|mac
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%02X:%02X:%02X:%02X:%02X:%02X&quot;
comma
id|mac
(braket
l_int|0
)braket
comma
id|mac
(braket
l_int|1
)braket
comma
id|mac
(braket
l_int|2
)braket
comma
id|mac
(braket
l_int|3
)braket
comma
id|mac
(braket
l_int|4
)braket
comma
id|mac
(braket
l_int|5
)braket
)paren
suffix:semicolon
)brace
DECL|function|llc_get_sk_idx
r_static
r_struct
id|sock
op_star
id|llc_get_sk_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|sap_entry
suffix:semicolon
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each
c_func
(paren
id|sap_entry
comma
op_amp
id|llc_main_station.sap_list.list
)paren
(brace
id|sap
op_assign
id|list_entry
c_func
(paren
id|sap_entry
comma
r_struct
id|llc_sap
comma
id|node
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|sap-&gt;sk_list.list
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sk
)paren
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|sk
suffix:semicolon
)brace
DECL|function|llc_seq_start
r_static
r_void
op_star
id|llc_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|llc_get_sk_idx
c_func
(paren
op_decrement
id|l
)paren
suffix:colon
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
DECL|function|llc_seq_next
r_static
r_void
op_star
id|llc_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|llc_opt
op_star
id|llc
suffix:semicolon
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
op_increment
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
id|sk
op_assign
id|llc_get_sk_idx
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sk
op_assign
id|v
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;next
)paren
(brace
id|sk
op_assign
id|sk-&gt;next
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sap
op_assign
id|llc-&gt;sap
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
id|sk
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|sap-&gt;node.next
op_eq
op_amp
id|llc_main_station.sap_list.list
)paren
r_break
suffix:semicolon
id|sap
op_assign
id|list_entry
c_func
(paren
id|sap-&gt;node.next
comma
r_struct
id|llc_sap
comma
id|node
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap-&gt;sk_list.list
)paren
(brace
id|sk
op_assign
id|sap-&gt;sk_list.list
suffix:semicolon
r_break
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|sk
suffix:semicolon
)brace
DECL|function|llc_seq_stop
r_static
r_void
id|llc_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|v
suffix:semicolon
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|llc_sap
op_star
id|sap
op_assign
id|llc-&gt;sap
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
)brace
DECL|function|llc_seq_socket_show
r_static
r_int
id|llc_seq_socket_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|llc_opt
op_star
id|llc
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;SKt Mc local_mac_sap        remote_mac_sap   &quot;
l_string|&quot;    tx_queue rx_queue st uid link&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sk
op_assign
id|v
suffix:semicolon
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%2X  %2X &quot;
comma
id|sk-&gt;type
comma
op_logical_neg
id|llc_mac_null
c_func
(paren
id|llc-&gt;addr.sllc_mmac
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|llc-&gt;dev
op_logical_and
id|llc_mac_null
c_func
(paren
id|llc-&gt;addr.sllc_mmac
)paren
)paren
id|llc_ui_format_mac
c_func
(paren
id|seq
comma
id|llc-&gt;dev-&gt;dev_addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|llc_mac_null
c_func
(paren
id|llc-&gt;addr.sllc_mmac
)paren
)paren
id|llc_ui_format_mac
c_func
(paren
id|seq
comma
id|llc-&gt;addr.sllc_mmac
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;00:00:00:00:00:00&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;@%02X &quot;
comma
id|llc-&gt;sap-&gt;laddr.lsap
)paren
suffix:semicolon
id|llc_ui_format_mac
c_func
(paren
id|seq
comma
id|llc-&gt;addr.sllc_dmac
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;@%02X %8d %8d %2d %3d %4d&bslash;n&quot;
comma
id|llc-&gt;addr.sllc_dsap
comma
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;wmem_alloc
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;rmem_alloc
)paren
comma
id|sk-&gt;state
comma
id|sk-&gt;socket
ques
c_cond
id|SOCK_INODE
c_func
(paren
id|sk-&gt;socket
)paren
op_member_access_from_pointer
id|i_uid
suffix:colon
op_minus
l_int|1
comma
id|llc-&gt;link
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|llc_conn_state_names
r_static
r_char
op_star
id|llc_conn_state_names
(braket
)braket
op_assign
(brace
(braket
id|LLC_CONN_STATE_ADM
)braket
op_assign
l_string|&quot;adm&quot;
comma
(braket
id|LLC_CONN_STATE_SETUP
)braket
op_assign
l_string|&quot;setup&quot;
comma
(braket
id|LLC_CONN_STATE_NORMAL
)braket
op_assign
l_string|&quot;normal&quot;
comma
(braket
id|LLC_CONN_STATE_BUSY
)braket
op_assign
l_string|&quot;busy&quot;
comma
(braket
id|LLC_CONN_STATE_REJ
)braket
op_assign
l_string|&quot;rej&quot;
comma
(braket
id|LLC_CONN_STATE_AWAIT
)braket
op_assign
l_string|&quot;await&quot;
comma
(braket
id|LLC_CONN_STATE_AWAIT_BUSY
)braket
op_assign
l_string|&quot;await_busy&quot;
comma
(braket
id|LLC_CONN_STATE_AWAIT_REJ
)braket
op_assign
l_string|&quot;await_rej&quot;
comma
(braket
id|LLC_CONN_STATE_D_CONN
)braket
op_assign
l_string|&quot;d_conn&quot;
comma
(braket
id|LLC_CONN_STATE_RESET
)braket
op_assign
l_string|&quot;reset&quot;
comma
(braket
id|LLC_CONN_STATE_ERROR
)braket
op_assign
l_string|&quot;error&quot;
comma
(braket
id|LLC_CONN_STATE_TEMP
)braket
op_assign
l_string|&quot;temp&quot;
comma
)brace
suffix:semicolon
DECL|function|llc_seq_core_show
r_static
r_int
id|llc_seq_core_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|llc_opt
op_star
id|llc
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Connection list:&bslash;n&quot;
l_string|&quot;dsap state      retr txw rxw pf ff sf df rs cs &quot;
l_string|&quot;tack tpfc trs tbs blog busr&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sk
op_assign
id|v
suffix:semicolon
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %02X  %-10s %3d  %3d %3d %2d %2d %2d %2d %2d %2d &quot;
l_string|&quot;%4d %4d %3d %3d %4d %4d&bslash;n&quot;
comma
id|llc-&gt;daddr.lsap
comma
id|llc_conn_state_names
(braket
id|llc-&gt;state
)braket
comma
id|llc-&gt;retry_count
comma
id|llc-&gt;k
comma
id|llc-&gt;rw
comma
id|llc-&gt;p_flag
comma
id|llc-&gt;f_flag
comma
id|llc-&gt;s_flag
comma
id|llc-&gt;data_flag
comma
id|llc-&gt;remote_busy_flag
comma
id|llc-&gt;cause_flag
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;ack_timer.timer
)paren
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;pf_cycle_timer.timer
)paren
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;rej_sent_timer.timer
)paren
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;busy_state_timer.timer
)paren
comma
op_logical_neg
op_logical_neg
id|sk-&gt;backlog.tail
comma
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|llc_seq_socket_ops
r_struct
id|seq_operations
id|llc_seq_socket_ops
op_assign
(brace
dot
id|start
op_assign
id|llc_seq_start
comma
dot
id|next
op_assign
id|llc_seq_next
comma
dot
id|stop
op_assign
id|llc_seq_stop
comma
dot
id|show
op_assign
id|llc_seq_socket_show
comma
)brace
suffix:semicolon
DECL|variable|llc_seq_core_ops
r_struct
id|seq_operations
id|llc_seq_core_ops
op_assign
(brace
dot
id|start
op_assign
id|llc_seq_start
comma
dot
id|next
op_assign
id|llc_seq_next
comma
dot
id|stop
op_assign
id|llc_seq_stop
comma
dot
id|show
op_assign
id|llc_seq_core_show
comma
)brace
suffix:semicolon
DECL|function|llc_seq_socket_open
r_static
r_int
id|llc_seq_socket_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|llc_seq_socket_ops
)paren
suffix:semicolon
)brace
DECL|function|llc_seq_core_open
r_static
r_int
id|llc_seq_core_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|llc_seq_core_ops
)paren
suffix:semicolon
)brace
DECL|variable|llc_seq_socket_fops
r_static
r_struct
id|file_operations
id|llc_seq_socket_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|llc_seq_socket_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|variable|llc_seq_core_fops
r_static
r_struct
id|file_operations
id|llc_seq_core_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|llc_seq_core_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|variable|llc_proc_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|llc_proc_dir
suffix:semicolon
DECL|function|llc_proc_init
r_int
id|__init
id|llc_proc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|llc_proc_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;llc&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|llc_proc_dir
)paren
r_goto
id|out
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;socket&quot;
comma
id|S_IRUGO
comma
id|llc_proc_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|out_socket
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|llc_seq_socket_fops
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;core&quot;
comma
id|S_IRUGO
comma
id|llc_proc_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|out_core
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|llc_seq_core_fops
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_core
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;socket&quot;
comma
id|llc_proc_dir
)paren
suffix:semicolon
id|out_socket
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;llc&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|llc_proc_exit
r_void
id|llc_proc_exit
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;socket&quot;
comma
id|llc_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;core&quot;
comma
id|llc_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;llc&quot;
comma
id|proc_net
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PROC_FS */
DECL|function|llc_proc_init
r_int
id|__init
id|llc_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|llc_proc_exit
r_void
id|llc_proc_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
