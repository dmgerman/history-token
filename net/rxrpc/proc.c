multiline_comment|/* proc.c: /proc interface for RxRPC&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;rxrpc/message.h&gt;
macro_line|#include &quot;internal.h&quot;
DECL|variable|proc_rxrpc
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_rxrpc
suffix:semicolon
r_static
r_int
id|rxrpc_proc_transports_open
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
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_transports_start
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_transports_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
id|rxrpc_proc_transports_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
suffix:semicolon
r_static
r_int
id|rxrpc_proc_transports_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
DECL|variable|rxrpc_proc_transports_ops
r_static
r_struct
id|seq_operations
id|rxrpc_proc_transports_ops
op_assign
(brace
dot
id|start
op_assign
id|rxrpc_proc_transports_start
comma
dot
id|next
op_assign
id|rxrpc_proc_transports_next
comma
dot
id|stop
op_assign
id|rxrpc_proc_transports_stop
comma
dot
id|show
op_assign
id|rxrpc_proc_transports_show
comma
)brace
suffix:semicolon
DECL|variable|rxrpc_proc_transports_fops
r_static
r_struct
id|file_operations
id|rxrpc_proc_transports_fops
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
id|rxrpc_proc_transports_open
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
r_static
r_int
id|rxrpc_proc_peers_open
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
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_peers_start
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_peers_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
id|rxrpc_proc_peers_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
suffix:semicolon
r_static
r_int
id|rxrpc_proc_peers_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
DECL|variable|rxrpc_proc_peers_ops
r_static
r_struct
id|seq_operations
id|rxrpc_proc_peers_ops
op_assign
(brace
dot
id|start
op_assign
id|rxrpc_proc_peers_start
comma
dot
id|next
op_assign
id|rxrpc_proc_peers_next
comma
dot
id|stop
op_assign
id|rxrpc_proc_peers_stop
comma
dot
id|show
op_assign
id|rxrpc_proc_peers_show
comma
)brace
suffix:semicolon
DECL|variable|rxrpc_proc_peers_fops
r_static
r_struct
id|file_operations
id|rxrpc_proc_peers_fops
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
id|rxrpc_proc_peers_open
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
r_static
r_int
id|rxrpc_proc_conns_open
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
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_conns_start
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_conns_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
id|rxrpc_proc_conns_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
suffix:semicolon
r_static
r_int
id|rxrpc_proc_conns_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
DECL|variable|rxrpc_proc_conns_ops
r_static
r_struct
id|seq_operations
id|rxrpc_proc_conns_ops
op_assign
(brace
dot
id|start
op_assign
id|rxrpc_proc_conns_start
comma
dot
id|next
op_assign
id|rxrpc_proc_conns_next
comma
dot
id|stop
op_assign
id|rxrpc_proc_conns_stop
comma
dot
id|show
op_assign
id|rxrpc_proc_conns_show
comma
)brace
suffix:semicolon
DECL|variable|rxrpc_proc_conns_fops
r_static
r_struct
id|file_operations
id|rxrpc_proc_conns_fops
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
id|rxrpc_proc_conns_open
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
r_static
r_int
id|rxrpc_proc_calls_open
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
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_calls_start
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
op_star
id|rxrpc_proc_calls_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
r_void
id|rxrpc_proc_calls_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
suffix:semicolon
r_static
r_int
id|rxrpc_proc_calls_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
DECL|variable|rxrpc_proc_calls_ops
r_static
r_struct
id|seq_operations
id|rxrpc_proc_calls_ops
op_assign
(brace
dot
id|start
op_assign
id|rxrpc_proc_calls_start
comma
dot
id|next
op_assign
id|rxrpc_proc_calls_next
comma
dot
id|stop
op_assign
id|rxrpc_proc_calls_stop
comma
dot
id|show
op_assign
id|rxrpc_proc_calls_show
comma
)brace
suffix:semicolon
DECL|variable|rxrpc_proc_calls_fops
r_static
r_struct
id|file_operations
id|rxrpc_proc_calls_fops
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
id|rxrpc_proc_calls_open
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
DECL|variable|rxrpc_call_states7
r_static
r_const
r_char
op_star
id|rxrpc_call_states7
(braket
)braket
op_assign
(brace
l_string|&quot;complet&quot;
comma
l_string|&quot;error  &quot;
comma
l_string|&quot;rcv_op &quot;
comma
l_string|&quot;rcv_arg&quot;
comma
l_string|&quot;got_arg&quot;
comma
l_string|&quot;snd_rpl&quot;
comma
l_string|&quot;fin_ack&quot;
comma
l_string|&quot;snd_arg&quot;
comma
l_string|&quot;rcv_rpl&quot;
comma
l_string|&quot;got_rpl&quot;
)brace
suffix:semicolon
DECL|variable|rxrpc_call_error_states7
r_static
r_const
r_char
op_star
id|rxrpc_call_error_states7
(braket
)braket
op_assign
(brace
l_string|&quot;no_err &quot;
comma
l_string|&quot;loc_abt&quot;
comma
l_string|&quot;rmt_abt&quot;
comma
l_string|&quot;loc_err&quot;
comma
l_string|&quot;rmt_err&quot;
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the /proc/net/rxrpc/ directory&n; */
DECL|function|rxrpc_proc_init
r_int
id|rxrpc_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|proc_rxrpc
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;rxrpc&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_rxrpc
)paren
r_goto
id|error
suffix:semicolon
id|proc_rxrpc-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;calls&quot;
comma
l_int|0
comma
id|proc_rxrpc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|error_proc
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|rxrpc_proc_calls_fops
suffix:semicolon
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;connections&quot;
comma
l_int|0
comma
id|proc_rxrpc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|error_calls
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|rxrpc_proc_conns_fops
suffix:semicolon
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;peers&quot;
comma
l_int|0
comma
id|proc_rxrpc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|error_calls
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|rxrpc_proc_peers_fops
suffix:semicolon
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;transports&quot;
comma
l_int|0
comma
id|proc_rxrpc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|error_conns
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|rxrpc_proc_transports_fops
suffix:semicolon
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_conns
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;conns&quot;
comma
id|proc_rxrpc
)paren
suffix:semicolon
id|error_calls
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;calls&quot;
comma
id|proc_rxrpc
)paren
suffix:semicolon
id|error_proc
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;rxrpc&quot;
comma
id|proc_net
)paren
suffix:semicolon
id|error
suffix:colon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up the /proc/net/rxrpc/ directory&n; */
DECL|function|rxrpc_proc_cleanup
r_void
id|rxrpc_proc_cleanup
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;transports&quot;
comma
id|proc_rxrpc
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;peers&quot;
comma
id|proc_rxrpc
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;connections&quot;
comma
id|proc_rxrpc
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;calls&quot;
comma
id|proc_rxrpc
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;rxrpc&quot;
comma
id|proc_net
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_cleanup() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * open &quot;/proc/net/rxrpc/transports&quot; which provides a summary of extant transports&n; */
DECL|function|rxrpc_proc_transports_open
r_static
r_int
id|rxrpc_proc_transports_open
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
r_struct
id|seq_file
op_star
id|m
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|rxrpc_proc_transports_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_transports_open() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * set up the iterator to start reading from the transports list and return the first item&n; */
DECL|function|rxrpc_proc_transports_start
r_static
r_void
op_star
id|rxrpc_proc_transports_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|_pos
)paren
(brace
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
id|loff_t
id|pos
op_assign
op_star
id|_pos
suffix:semicolon
multiline_comment|/* lock the list against modification */
id|down_read
c_func
(paren
op_amp
id|rxrpc_proc_transports_sem
)paren
suffix:semicolon
multiline_comment|/* allow for the header line */
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
id|pos
op_decrement
suffix:semicolon
multiline_comment|/* find the n&squot;th element in the list */
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|rxrpc_proc_transports
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
r_break
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_proc_transports
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_transports_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * move to next call in transports list&n; */
DECL|function|rxrpc_proc_transports_next
r_static
r_void
op_star
id|rxrpc_proc_transports_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
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
id|list_head
op_star
id|_p
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
id|_p
op_assign
id|v
suffix:semicolon
id|_p
op_assign
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
ques
c_cond
id|rxrpc_proc_transports.next
suffix:colon
id|_p-&gt;next
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_proc_transports
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_transports_next() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up after reading from the transports list&n; */
DECL|function|rxrpc_proc_transports_stop
r_static
r_void
id|rxrpc_proc_transports_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|rxrpc_proc_transports_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_transports_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * display a header line followed by a load of call lines&n; */
DECL|function|rxrpc_proc_transports_show
r_static
r_int
id|rxrpc_proc_transports_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|rxrpc_transport
op_star
id|trans
op_assign
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|rxrpc_transport
comma
id|proc_link
)paren
suffix:semicolon
multiline_comment|/* display header on line 1 */
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
id|m
comma
l_string|&quot;LOCAL USE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* display one transport per line on subsequent lines */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%5hu %3d&bslash;n&quot;
comma
id|trans-&gt;port
comma
id|atomic_read
c_func
(paren
op_amp
id|trans-&gt;usage
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_transports_show() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * open &quot;/proc/net/rxrpc/peers&quot; which provides a summary of extant peers&n; */
DECL|function|rxrpc_proc_peers_open
r_static
r_int
id|rxrpc_proc_peers_open
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
r_struct
id|seq_file
op_star
id|m
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|rxrpc_proc_peers_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_peers_open() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * set up the iterator to start reading from the peers list and return the first item&n; */
DECL|function|rxrpc_proc_peers_start
r_static
r_void
op_star
id|rxrpc_proc_peers_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|_pos
)paren
(brace
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
id|loff_t
id|pos
op_assign
op_star
id|_pos
suffix:semicolon
multiline_comment|/* lock the list against modification */
id|down_read
c_func
(paren
op_amp
id|rxrpc_peers_sem
)paren
suffix:semicolon
multiline_comment|/* allow for the header line */
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
id|pos
op_decrement
suffix:semicolon
multiline_comment|/* find the n&squot;th element in the list */
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|rxrpc_peers
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
r_break
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_peers
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_peers_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * move to next conn in peers list&n; */
DECL|function|rxrpc_proc_peers_next
r_static
r_void
op_star
id|rxrpc_proc_peers_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
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
id|list_head
op_star
id|_p
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
id|_p
op_assign
id|v
suffix:semicolon
id|_p
op_assign
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
ques
c_cond
id|rxrpc_peers.next
suffix:colon
id|_p-&gt;next
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_peers
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_peers_next() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up after reading from the peers list&n; */
DECL|function|rxrpc_proc_peers_stop
r_static
r_void
id|rxrpc_proc_peers_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|rxrpc_peers_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_peers_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * display a header line followed by a load of conn lines&n; */
DECL|function|rxrpc_proc_peers_show
r_static
r_int
id|rxrpc_proc_peers_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|rxrpc_peer
op_star
id|peer
op_assign
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|rxrpc_peer
comma
id|proc_link
)paren
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* display header on line 1 */
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
id|m
comma
l_string|&quot;LOCAL REMOTE   USAGE CONNS  TIMEOUT   MTU RTT(uS)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* display one peer per line on subsequent lines */
id|timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|peer-&gt;timeout.link
)paren
)paren
id|timeout
op_assign
(paren
r_int
r_int
)paren
id|peer-&gt;timeout.timo_jif
op_minus
(paren
r_int
r_int
)paren
id|jiffies
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%5hu %08x %5d %5d %8ld %5Zu %7lu&bslash;n&quot;
comma
id|peer-&gt;trans-&gt;port
comma
id|ntohl
c_func
(paren
id|peer-&gt;addr.s_addr
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;conn_count
)paren
comma
id|timeout
comma
id|peer-&gt;if_mtu
comma
(paren
r_int
)paren
id|peer-&gt;rtt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_peers_show() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * open &quot;/proc/net/rxrpc/connections&quot; which provides a summary of extant connections&n; */
DECL|function|rxrpc_proc_conns_open
r_static
r_int
id|rxrpc_proc_conns_open
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
r_struct
id|seq_file
op_star
id|m
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|rxrpc_proc_conns_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_conns_open() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * set up the iterator to start reading from the conns list and return the first item&n; */
DECL|function|rxrpc_proc_conns_start
r_static
r_void
op_star
id|rxrpc_proc_conns_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|_pos
)paren
(brace
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
id|loff_t
id|pos
op_assign
op_star
id|_pos
suffix:semicolon
multiline_comment|/* lock the list against modification */
id|down_read
c_func
(paren
op_amp
id|rxrpc_conns_sem
)paren
suffix:semicolon
multiline_comment|/* allow for the header line */
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
id|pos
op_decrement
suffix:semicolon
multiline_comment|/* find the n&squot;th element in the list */
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|rxrpc_conns
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
r_break
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_conns
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_conns_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * move to next conn in conns list&n; */
DECL|function|rxrpc_proc_conns_next
r_static
r_void
op_star
id|rxrpc_proc_conns_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
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
id|list_head
op_star
id|_p
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
id|_p
op_assign
id|v
suffix:semicolon
id|_p
op_assign
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
ques
c_cond
id|rxrpc_conns.next
suffix:colon
id|_p-&gt;next
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_conns
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_conns_next() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up after reading from the conns list&n; */
DECL|function|rxrpc_proc_conns_stop
r_static
r_void
id|rxrpc_proc_conns_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|rxrpc_conns_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_conns_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * display a header line followed by a load of conn lines&n; */
DECL|function|rxrpc_proc_conns_show
r_static
r_int
id|rxrpc_proc_conns_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|rxrpc_connection
op_star
id|conn
op_assign
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|rxrpc_connection
comma
id|proc_link
)paren
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* display header on line 1 */
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
id|m
comma
l_string|&quot;LOCAL REMOTE   RPORT SRVC CONN     END SERIALNO CALLNO     MTU  TIMEOUT&quot;
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* display one conn per line on subsequent lines */
id|timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|conn-&gt;timeout.link
)paren
)paren
id|timeout
op_assign
(paren
r_int
r_int
)paren
id|conn-&gt;timeout.timo_jif
op_minus
(paren
r_int
r_int
)paren
id|jiffies
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%5hu %08x %5hu %04hx %08x %-3.3s %08x %08x %5Zu %8ld&bslash;n&quot;
comma
id|conn-&gt;trans-&gt;port
comma
id|ntohl
c_func
(paren
id|conn-&gt;addr.sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|conn-&gt;addr.sin_port
)paren
comma
id|ntohs
c_func
(paren
id|conn-&gt;service_id
)paren
comma
id|ntohl
c_func
(paren
id|conn-&gt;conn_id
)paren
comma
id|conn-&gt;out_clientflag
ques
c_cond
l_string|&quot;CLT&quot;
suffix:colon
l_string|&quot;SRV&quot;
comma
id|conn-&gt;serial_counter
comma
id|conn-&gt;call_counter
comma
id|conn-&gt;mtu_size
comma
id|timeout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_conns_show() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * open &quot;/proc/net/rxrpc/calls&quot; which provides a summary of extant calls&n; */
DECL|function|rxrpc_proc_calls_open
r_static
r_int
id|rxrpc_proc_calls_open
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
r_struct
id|seq_file
op_star
id|m
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|rxrpc_proc_calls_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_calls_open() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * set up the iterator to start reading from the calls list and return the first item&n; */
DECL|function|rxrpc_proc_calls_start
r_static
r_void
op_star
id|rxrpc_proc_calls_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|_pos
)paren
(brace
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
id|loff_t
id|pos
op_assign
op_star
id|_pos
suffix:semicolon
multiline_comment|/* lock the list against modification */
id|down_read
c_func
(paren
op_amp
id|rxrpc_calls_sem
)paren
suffix:semicolon
multiline_comment|/* allow for the header line */
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
id|pos
op_decrement
suffix:semicolon
multiline_comment|/* find the n&squot;th element in the list */
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|rxrpc_calls
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
r_break
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_calls
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_calls_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * move to next call in calls list&n; */
DECL|function|rxrpc_proc_calls_next
r_static
r_void
op_star
id|rxrpc_proc_calls_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
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
id|list_head
op_star
id|_p
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
id|_p
op_assign
id|v
suffix:semicolon
id|_p
op_assign
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
ques
c_cond
id|rxrpc_calls.next
suffix:colon
id|_p-&gt;next
suffix:semicolon
r_return
id|_p
op_ne
op_amp
id|rxrpc_calls
ques
c_cond
id|_p
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_calls_next() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up after reading from the calls list&n; */
DECL|function|rxrpc_proc_calls_stop
r_static
r_void
id|rxrpc_proc_calls_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|rxrpc_calls_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_calls_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * display a header line followed by a load of call lines&n; */
DECL|function|rxrpc_proc_calls_show
r_static
r_int
id|rxrpc_proc_calls_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|rxrpc_call
op_star
id|call
op_assign
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|rxrpc_call
comma
id|call_link
)paren
suffix:semicolon
multiline_comment|/* display header on line 1 */
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
id|m
comma
l_string|&quot;LOCAL REMOT SRVC CONN     CALL     DIR USE &quot;
l_string|&quot; L STATE   OPCODE ABORT    ERRNO&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* display one call per line on subsequent lines */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%5hu %5hu %04hx %08x %08x %s %3u%c&quot;
l_string|&quot; %c %-7.7s %6d %08x %5d&bslash;n&quot;
comma
id|call-&gt;conn-&gt;trans-&gt;port
comma
id|ntohs
c_func
(paren
id|call-&gt;conn-&gt;addr.sin_port
)paren
comma
id|ntohs
c_func
(paren
id|call-&gt;conn-&gt;service_id
)paren
comma
id|ntohl
c_func
(paren
id|call-&gt;conn-&gt;conn_id
)paren
comma
id|ntohl
c_func
(paren
id|call-&gt;call_id
)paren
comma
id|call-&gt;conn-&gt;service
ques
c_cond
l_string|&quot;SVC&quot;
suffix:colon
l_string|&quot;CLT&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
comma
id|waitqueue_active
c_func
(paren
op_amp
id|call-&gt;waitq
)paren
ques
c_cond
l_char|&squot;w&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|call-&gt;app_last_rcv
ques
c_cond
l_char|&squot;Y&squot;
suffix:colon
l_char|&squot;-&squot;
comma
(paren
id|call-&gt;app_call_state
op_ne
id|RXRPC_CSTATE_ERROR
ques
c_cond
id|rxrpc_call_states7
(braket
id|call-&gt;app_call_state
)braket
suffix:colon
id|rxrpc_call_error_states7
(braket
id|call-&gt;app_err_state
)braket
)paren
comma
id|call-&gt;app_opcode
comma
id|call-&gt;app_abort_code
comma
id|call-&gt;app_errno
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_proc_calls_show() */
eof
