multiline_comment|/*&n; * &t;atalk_proc.c - proc support for Appletalk&n; *&n; * &t;Copyright(c) Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify it&n; *&t;under the terms of the GNU General Public License as published by the&n; *&t;Free Software Foundation, version 2.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/atalk.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|atalk_get_interface_idx
r_static
id|__inline__
r_struct
id|atalk_iface
op_star
id|atalk_get_interface_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|atalk_iface
op_star
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|atalk_interfaces
suffix:semicolon
id|pos
op_logical_and
id|i
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
op_decrement
id|pos
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|atalk_seq_interface_start
r_static
r_void
op_star
id|atalk_seq_interface_start
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
id|spin_lock_bh
c_func
(paren
op_amp
id|atalk_interfaces_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|atalk_get_interface_idx
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
DECL|function|atalk_seq_interface_next
r_static
r_void
op_star
id|atalk_seq_interface_next
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
id|atalk_iface
op_star
id|i
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
id|i
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|atalk_interfaces
)paren
id|i
op_assign
id|atalk_interfaces
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|i
op_assign
id|v
suffix:semicolon
id|i
op_assign
id|i-&gt;next
suffix:semicolon
id|out
suffix:colon
r_return
id|i
suffix:semicolon
)brace
DECL|function|atalk_seq_interface_stop
r_static
r_void
id|atalk_seq_interface_stop
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
id|spin_unlock_bh
c_func
(paren
op_amp
id|atalk_interfaces_lock
)paren
suffix:semicolon
)brace
DECL|function|atalk_seq_interface_show
r_static
r_int
id|atalk_seq_interface_show
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
id|atalk_iface
op_star
id|iface
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
l_string|&quot;Interface&t;  Address   Networks   &quot;
l_string|&quot;Status&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|iface
op_assign
id|v
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-16s %04X:%02X  %04X-%04X  %d&bslash;n&quot;
comma
id|iface-&gt;dev-&gt;name
comma
id|ntohs
c_func
(paren
id|iface-&gt;address.s_net
)paren
comma
id|iface-&gt;address.s_node
comma
id|ntohs
c_func
(paren
id|iface-&gt;nets.nr_firstnet
)paren
comma
id|ntohs
c_func
(paren
id|iface-&gt;nets.nr_lastnet
)paren
comma
id|iface-&gt;status
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atalk_get_route_idx
r_static
id|__inline__
r_struct
id|atalk_route
op_star
id|atalk_get_route_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|atalk_route
op_star
id|r
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|atalk_routes
suffix:semicolon
id|pos
op_logical_and
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;next
)paren
op_decrement
id|pos
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|atalk_seq_route_start
r_static
r_void
op_star
id|atalk_seq_route_start
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
id|atalk_routes_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|atalk_get_route_idx
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
DECL|function|atalk_seq_route_next
r_static
r_void
op_star
id|atalk_seq_route_next
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
id|atalk_route
op_star
id|r
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
id|r
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|atalk_routes
)paren
id|r
op_assign
id|atalk_routes
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|r
op_assign
id|v
suffix:semicolon
id|r
op_assign
id|r-&gt;next
suffix:semicolon
id|out
suffix:colon
r_return
id|r
suffix:semicolon
)brace
DECL|function|atalk_seq_route_stop
r_static
r_void
id|atalk_seq_route_stop
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
id|read_unlock_bh
c_func
(paren
op_amp
id|atalk_routes_lock
)paren
suffix:semicolon
)brace
DECL|function|atalk_seq_route_show
r_static
r_int
id|atalk_seq_route_show
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
id|atalk_route
op_star
id|rt
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
l_string|&quot;Target        Router  Flags Dev&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atrtr_default.dev
)paren
(brace
id|rt
op_assign
op_amp
id|atrtr_default
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;Default     %04X:%02X  %-4d  %s&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|rt-&gt;gateway.s_net
)paren
comma
id|rt-&gt;gateway.s_node
comma
id|rt-&gt;flags
comma
id|rt-&gt;dev-&gt;name
)paren
suffix:semicolon
)brace
id|rt
op_assign
id|v
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%04X:%02X     %04X:%02X  %-4d  %s&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|rt-&gt;target.s_net
)paren
comma
id|rt-&gt;target.s_node
comma
id|ntohs
c_func
(paren
id|rt-&gt;gateway.s_net
)paren
comma
id|rt-&gt;gateway.s_node
comma
id|rt-&gt;flags
comma
id|rt-&gt;dev-&gt;name
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atalk_get_socket_idx
r_static
id|__inline__
r_struct
id|sock
op_star
id|atalk_get_socket_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|sock
op_star
id|s
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|atalk_sockets
suffix:semicolon
id|pos
op_logical_and
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
op_decrement
id|pos
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|atalk_seq_socket_start
r_static
r_void
op_star
id|atalk_seq_socket_start
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
id|spin_lock_bh
c_func
(paren
op_amp
id|atalk_sockets_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|atalk_get_socket_idx
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
DECL|function|atalk_seq_socket_next
r_static
r_void
op_star
id|atalk_seq_socket_next
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
id|i
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
id|i
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|atalk_sockets
)paren
id|i
op_assign
id|atalk_sockets
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|i
op_assign
id|v
suffix:semicolon
id|i
op_assign
id|i-&gt;next
suffix:semicolon
id|out
suffix:colon
r_return
id|i
suffix:semicolon
)brace
DECL|function|atalk_seq_socket_stop
r_static
r_void
id|atalk_seq_socket_stop
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
id|spin_unlock_bh
c_func
(paren
op_amp
id|atalk_sockets_lock
)paren
suffix:semicolon
)brace
DECL|function|atalk_seq_socket_show
r_static
r_int
id|atalk_seq_socket_show
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
id|s
suffix:semicolon
r_struct
id|atalk_sock
op_star
id|at
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
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;Type Local_addr  Remote_addr Tx_queue &quot;
l_string|&quot;Rx_queue St UID&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s
op_assign
id|v
suffix:semicolon
id|at
op_assign
id|at_sk
c_func
(paren
id|s
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%02X   %04X:%02X:%02X  %04X:%02X:%02X  %08X:%08X &quot;
l_string|&quot;%02X %d&bslash;n&quot;
comma
id|s-&gt;type
comma
id|ntohs
c_func
(paren
id|at-&gt;src_net
)paren
comma
id|at-&gt;src_node
comma
id|at-&gt;src_port
comma
id|ntohs
c_func
(paren
id|at-&gt;dest_net
)paren
comma
id|at-&gt;dest_node
comma
id|at-&gt;dest_port
comma
id|atomic_read
c_func
(paren
op_amp
id|s-&gt;wmem_alloc
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|s-&gt;rmem_alloc
)paren
comma
id|s-&gt;state
comma
id|SOCK_INODE
c_func
(paren
id|s-&gt;socket
)paren
op_member_access_from_pointer
id|i_uid
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atalk_seq_interface_ops
r_struct
id|seq_operations
id|atalk_seq_interface_ops
op_assign
(brace
dot
id|start
op_assign
id|atalk_seq_interface_start
comma
dot
id|next
op_assign
id|atalk_seq_interface_next
comma
dot
id|stop
op_assign
id|atalk_seq_interface_stop
comma
dot
id|show
op_assign
id|atalk_seq_interface_show
comma
)brace
suffix:semicolon
DECL|variable|atalk_seq_route_ops
r_struct
id|seq_operations
id|atalk_seq_route_ops
op_assign
(brace
dot
id|start
op_assign
id|atalk_seq_route_start
comma
dot
id|next
op_assign
id|atalk_seq_route_next
comma
dot
id|stop
op_assign
id|atalk_seq_route_stop
comma
dot
id|show
op_assign
id|atalk_seq_route_show
comma
)brace
suffix:semicolon
DECL|variable|atalk_seq_socket_ops
r_struct
id|seq_operations
id|atalk_seq_socket_ops
op_assign
(brace
dot
id|start
op_assign
id|atalk_seq_socket_start
comma
dot
id|next
op_assign
id|atalk_seq_socket_next
comma
dot
id|stop
op_assign
id|atalk_seq_socket_stop
comma
dot
id|show
op_assign
id|atalk_seq_socket_show
comma
)brace
suffix:semicolon
DECL|function|atalk_seq_interface_open
r_static
r_int
id|atalk_seq_interface_open
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
id|atalk_seq_interface_ops
)paren
suffix:semicolon
)brace
DECL|function|atalk_seq_route_open
r_static
r_int
id|atalk_seq_route_open
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
id|atalk_seq_route_ops
)paren
suffix:semicolon
)brace
DECL|function|atalk_seq_socket_open
r_static
r_int
id|atalk_seq_socket_open
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
id|atalk_seq_socket_ops
)paren
suffix:semicolon
)brace
DECL|variable|atalk_seq_interface_fops
r_static
r_struct
id|file_operations
id|atalk_seq_interface_fops
op_assign
(brace
dot
id|open
op_assign
id|atalk_seq_interface_open
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
DECL|variable|atalk_seq_route_fops
r_static
r_struct
id|file_operations
id|atalk_seq_route_fops
op_assign
(brace
dot
id|open
op_assign
id|atalk_seq_route_open
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
DECL|variable|atalk_seq_socket_fops
r_static
r_struct
id|file_operations
id|atalk_seq_socket_fops
op_assign
(brace
dot
id|open
op_assign
id|atalk_seq_socket_open
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
DECL|variable|atalk_proc_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|atalk_proc_dir
suffix:semicolon
DECL|function|atalk_proc_init
r_int
id|__init
id|atalk_proc_init
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
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|atalk_proc_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;atalk&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atalk_proc_dir
)paren
r_goto
id|out
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;interface&quot;
comma
id|S_IRUGO
comma
id|atalk_proc_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|out_interface
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|atalk_seq_interface_fops
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;route&quot;
comma
id|S_IRUGO
comma
id|atalk_proc_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|out_route
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|atalk_seq_route_fops
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
id|atalk_proc_dir
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
id|atalk_seq_socket_fops
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
id|out_socket
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;route&quot;
comma
id|atalk_proc_dir
)paren
suffix:semicolon
id|out_route
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;interface&quot;
comma
id|atalk_proc_dir
)paren
suffix:semicolon
id|out_interface
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;atalk&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|atalk_proc_exit
r_void
id|__exit
id|atalk_proc_exit
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;interface&quot;
comma
id|atalk_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;route&quot;
comma
id|atalk_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;socket&quot;
comma
id|atalk_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;atalk&quot;
comma
id|proc_net
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PROC_FS */
DECL|function|atalk_proc_init
r_int
id|__init
id|atalk_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atalk_proc_exit
r_void
id|__exit
id|atalk_proc_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
