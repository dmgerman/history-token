multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine,&n; *&t;randomly fail to work with new releases, misbehave and/or generally&n; *&t;screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.4 with seq_file support&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;2002/10/06&t;Arnaldo Carvalho de Melo  seq_file support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/x25.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|x25_get_route_idx
r_static
id|__inline__
r_struct
id|x25_route
op_star
id|x25_get_route_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|route_entry
suffix:semicolon
r_struct
id|x25_route
op_star
id|rt
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each
c_func
(paren
id|route_entry
comma
op_amp
id|x25_route_list
)paren
(brace
id|rt
op_assign
id|list_entry
c_func
(paren
id|route_entry
comma
r_struct
id|x25_route
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|pos
)paren
r_break
suffix:semicolon
)brace
r_return
id|rt
suffix:semicolon
)brace
DECL|function|x25_seq_route_start
r_static
r_void
op_star
id|x25_seq_route_start
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
id|x25_route_list_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|x25_get_route_idx
c_func
(paren
op_decrement
id|l
)paren
suffix:colon
id|SEQ_START_TOKEN
suffix:semicolon
)brace
DECL|function|x25_seq_route_next
r_static
r_void
op_star
id|x25_seq_route_next
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
id|x25_route
op_star
id|rt
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
id|SEQ_START_TOKEN
)paren
(brace
id|rt
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|x25_route_list
)paren
)paren
id|rt
op_assign
id|list_entry
c_func
(paren
id|x25_route_list.next
comma
r_struct
id|x25_route
comma
id|node
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|rt
op_assign
id|v
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;node.next
op_ne
op_amp
id|x25_route_list
)paren
id|rt
op_assign
id|list_entry
c_func
(paren
id|rt-&gt;node.next
comma
r_struct
id|x25_route
comma
id|node
)paren
suffix:semicolon
r_else
id|rt
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
r_return
id|rt
suffix:semicolon
)brace
DECL|function|x25_seq_route_stop
r_static
r_void
id|x25_seq_route_stop
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
id|x25_route_list_lock
)paren
suffix:semicolon
)brace
DECL|function|x25_seq_route_show
r_static
r_int
id|x25_seq_route_show
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
id|x25_route
op_star
id|rt
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
(brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Address          Digits  Device&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
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
l_string|&quot;%-15s  %-6d  %-5s&bslash;n&quot;
comma
id|rt-&gt;address.x25_addr
comma
id|rt-&gt;sigdigits
comma
id|rt-&gt;dev
ques
c_cond
id|rt-&gt;dev-&gt;name
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|x25_get_socket_idx
r_static
id|__inline__
r_struct
id|sock
op_star
id|x25_get_socket_idx
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
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
id|sk_for_each
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|x25_list
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
r_goto
id|found
suffix:semicolon
id|s
op_assign
l_int|NULL
suffix:semicolon
id|found
suffix:colon
r_return
id|s
suffix:semicolon
)brace
DECL|function|x25_seq_socket_start
r_static
r_void
op_star
id|x25_seq_socket_start
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
id|x25_list_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|x25_get_socket_idx
c_func
(paren
op_decrement
id|l
)paren
suffix:colon
id|SEQ_START_TOKEN
suffix:semicolon
)brace
DECL|function|x25_seq_socket_next
r_static
r_void
op_star
id|x25_seq_socket_next
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
id|s
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
id|SEQ_START_TOKEN
)paren
(brace
id|s
op_assign
id|sk_head
c_func
(paren
op_amp
id|x25_list
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s
op_assign
id|sk_next
c_func
(paren
id|v
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|s
suffix:semicolon
)brace
DECL|function|x25_seq_socket_stop
r_static
r_void
id|x25_seq_socket_stop
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
id|x25_list_lock
)paren
suffix:semicolon
)brace
DECL|function|x25_seq_socket_show
r_static
r_int
id|x25_seq_socket_show
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
id|x25_opt
op_star
id|x25
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_const
r_char
op_star
id|devname
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;dest_addr  src_addr   dev   lci st vs vr &quot;
l_string|&quot;va   t  t2 t21 t22 t23 Snd-Q Rcv-Q inode&bslash;n&quot;
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
id|x25
op_assign
id|x25_sk
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x25-&gt;neighbour
op_logical_or
(paren
id|dev
op_assign
id|x25-&gt;neighbour-&gt;dev
)paren
op_eq
l_int|NULL
)paren
id|devname
op_assign
l_string|&quot;???&quot;
suffix:semicolon
r_else
id|devname
op_assign
id|x25-&gt;neighbour-&gt;dev-&gt;name
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-10s %-10s %-5s %3.3X  %d  %d  %d  %d %3lu %3lu &quot;
l_string|&quot;%3lu %3lu %3lu %5d %5d %ld&bslash;n&quot;
comma
op_logical_neg
id|x25-&gt;dest_addr.x25_addr
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot;*&quot;
suffix:colon
id|x25-&gt;dest_addr.x25_addr
comma
op_logical_neg
id|x25-&gt;source_addr.x25_addr
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot;*&quot;
suffix:colon
id|x25-&gt;source_addr.x25_addr
comma
id|devname
comma
id|x25-&gt;lci
op_amp
l_int|0x0FFF
comma
id|x25-&gt;state
comma
id|x25-&gt;vs
comma
id|x25-&gt;vr
comma
id|x25-&gt;va
comma
id|x25_display_timer
c_func
(paren
id|s
)paren
op_div
id|HZ
comma
id|x25-&gt;t2
op_div
id|HZ
comma
id|x25-&gt;t21
op_div
id|HZ
comma
id|x25-&gt;t22
op_div
id|HZ
comma
id|x25-&gt;t23
op_div
id|HZ
comma
id|atomic_read
c_func
(paren
op_amp
id|s-&gt;sk_wmem_alloc
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|s-&gt;sk_rmem_alloc
)paren
comma
id|s-&gt;sk_socket
ques
c_cond
id|SOCK_INODE
c_func
(paren
id|s-&gt;sk_socket
)paren
op_member_access_from_pointer
id|i_ino
suffix:colon
l_int|0L
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|x25_seq_route_ops
r_struct
id|seq_operations
id|x25_seq_route_ops
op_assign
(brace
dot
id|start
op_assign
id|x25_seq_route_start
comma
dot
id|next
op_assign
id|x25_seq_route_next
comma
dot
id|stop
op_assign
id|x25_seq_route_stop
comma
dot
id|show
op_assign
id|x25_seq_route_show
comma
)brace
suffix:semicolon
DECL|variable|x25_seq_socket_ops
r_struct
id|seq_operations
id|x25_seq_socket_ops
op_assign
(brace
dot
id|start
op_assign
id|x25_seq_socket_start
comma
dot
id|next
op_assign
id|x25_seq_socket_next
comma
dot
id|stop
op_assign
id|x25_seq_socket_stop
comma
dot
id|show
op_assign
id|x25_seq_socket_show
comma
)brace
suffix:semicolon
DECL|function|x25_seq_socket_open
r_static
r_int
id|x25_seq_socket_open
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
id|x25_seq_socket_ops
)paren
suffix:semicolon
)brace
DECL|function|x25_seq_route_open
r_static
r_int
id|x25_seq_route_open
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
id|x25_seq_route_ops
)paren
suffix:semicolon
)brace
DECL|variable|x25_seq_socket_fops
r_static
r_struct
id|file_operations
id|x25_seq_socket_fops
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
id|x25_seq_socket_open
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
DECL|variable|x25_seq_route_fops
r_static
r_struct
id|file_operations
id|x25_seq_route_fops
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
id|x25_seq_route_open
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
DECL|variable|x25_proc_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|x25_proc_dir
suffix:semicolon
DECL|function|x25_proc_init
r_int
id|__init
id|x25_proc_init
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
id|x25_proc_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;x25&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x25_proc_dir
)paren
r_goto
id|out
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
id|x25_proc_dir
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
id|x25_seq_route_fops
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
id|x25_proc_dir
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
id|x25_seq_socket_fops
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
id|x25_proc_dir
)paren
suffix:semicolon
id|out_route
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;x25&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|x25_proc_exit
r_void
id|__exit
id|x25_proc_exit
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;route&quot;
comma
id|x25_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;socket&quot;
comma
id|x25_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;x25&quot;
comma
id|proc_net
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PROC_FS */
DECL|function|x25_proc_init
r_int
id|__init
id|x25_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|x25_proc_exit
r_void
id|__exit
id|x25_proc_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
