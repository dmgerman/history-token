multiline_comment|/*&n; *&t;IPX proc routines&n; *&n; * &t;Copyright(C) Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;, 2002&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;net/ipx.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|ipx_get_interface_idx
r_static
id|__inline__
r_struct
id|ipx_interface
op_star
id|ipx_get_interface_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|ipx_interface
op_star
id|i
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|i
comma
op_amp
id|ipx_interfaces
comma
id|node
)paren
r_if
c_cond
(paren
op_logical_neg
id|pos
op_decrement
)paren
r_goto
id|out
suffix:semicolon
id|i
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ipx_interfaces_next
r_static
r_struct
id|ipx_interface
op_star
id|ipx_interfaces_next
c_func
(paren
r_struct
id|ipx_interface
op_star
id|i
)paren
(brace
r_struct
id|ipx_interface
op_star
id|rc
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;node.next
op_ne
op_amp
id|ipx_interfaces
)paren
id|rc
op_assign
id|list_entry
c_func
(paren
id|i-&gt;node.next
comma
r_struct
id|ipx_interface
comma
id|node
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|ipx_seq_interface_start
r_static
r_void
op_star
id|ipx_seq_interface_start
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
id|ipx_interfaces_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|ipx_get_interface_idx
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
DECL|function|ipx_seq_interface_next
r_static
r_void
op_star
id|ipx_seq_interface_next
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
id|ipx_interface
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
id|i
op_assign
id|ipx_interfaces_head
c_func
(paren
)paren
suffix:semicolon
r_else
id|i
op_assign
id|ipx_interfaces_next
c_func
(paren
id|v
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ipx_seq_interface_stop
r_static
r_void
id|ipx_seq_interface_stop
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
id|ipx_interfaces_lock
)paren
suffix:semicolon
)brace
DECL|function|ipx_seq_interface_show
r_static
r_int
id|ipx_seq_interface_show
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
id|ipx_interface
op_star
id|i
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
l_string|&quot;Network    Node_Address   Primary  Device     &quot;
l_string|&quot;Frame_Type&quot;
)paren
suffix:semicolon
macro_line|#ifdef IPX_REFCNT_DEBUG
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;  refcnt&quot;
)paren
suffix:semicolon
macro_line|#endif
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|i
op_assign
id|v
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%08lX   &quot;
comma
(paren
r_int
r_int
r_int
)paren
id|ntohl
c_func
(paren
id|i-&gt;if_netnum
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%02X%02X%02X%02X%02X%02X   &quot;
comma
id|i-&gt;if_node
(braket
l_int|0
)braket
comma
id|i-&gt;if_node
(braket
l_int|1
)braket
comma
id|i-&gt;if_node
(braket
l_int|2
)braket
comma
id|i-&gt;if_node
(braket
l_int|3
)braket
comma
id|i-&gt;if_node
(braket
l_int|4
)braket
comma
id|i-&gt;if_node
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-9s&quot;
comma
id|i
op_eq
id|ipx_primary_net
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-11s&quot;
comma
id|ipx_device_name
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-9s&quot;
comma
id|ipx_frame_name
c_func
(paren
id|i-&gt;if_dlink_type
)paren
)paren
suffix:semicolon
macro_line|#ifdef IPX_REFCNT_DEBUG
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%6d&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|i-&gt;refcnt
)paren
)paren
suffix:semicolon
macro_line|#endif
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipx_get_route_idx
r_static
id|__inline__
r_struct
id|ipx_route
op_star
id|ipx_get_route_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|ipx_route
op_star
id|r
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|ipx_routes
suffix:semicolon
id|pos
op_logical_and
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;ir_next
)paren
op_decrement
id|pos
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|ipx_seq_route_start
r_static
r_void
op_star
id|ipx_seq_route_start
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
id|ipx_routes_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|ipx_get_route_idx
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
DECL|function|ipx_seq_route_next
r_static
r_void
op_star
id|ipx_seq_route_next
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
id|ipx_route
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
id|ipx_routes
)paren
id|r
op_assign
id|ipx_routes
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
id|r-&gt;ir_next
suffix:semicolon
id|out
suffix:colon
r_return
id|r
suffix:semicolon
)brace
DECL|function|ipx_seq_route_stop
r_static
r_void
id|ipx_seq_route_stop
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
id|ipx_routes_lock
)paren
suffix:semicolon
)brace
DECL|function|ipx_seq_route_show
r_static
r_int
id|ipx_seq_route_show
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
id|ipx_route
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
l_string|&quot;Network    Router_Net   Router_Node&bslash;n&quot;
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
l_string|&quot;%08lX   &quot;
comma
(paren
r_int
r_int
r_int
)paren
id|ntohl
c_func
(paren
id|rt-&gt;ir_net
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;ir_routed
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%08lX     %02X%02X%02X%02X%02X%02X&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|ntohl
c_func
(paren
id|rt-&gt;ir_intrfc-&gt;if_netnum
)paren
comma
id|rt-&gt;ir_router_node
(braket
l_int|0
)braket
comma
id|rt-&gt;ir_router_node
(braket
l_int|1
)braket
comma
id|rt-&gt;ir_router_node
(braket
l_int|2
)braket
comma
id|rt-&gt;ir_router_node
(braket
l_int|3
)braket
comma
id|rt-&gt;ir_router_node
(braket
l_int|4
)braket
comma
id|rt-&gt;ir_router_node
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_else
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Directly     Connected&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipx_get_socket_idx
r_static
id|__inline__
r_struct
id|sock
op_star
id|ipx_get_socket_idx
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
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ipx_interface
op_star
id|i
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|i
comma
op_amp
id|ipx_interfaces
comma
id|node
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_break
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|i-&gt;if_sklist
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
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
id|spin_unlock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
)paren
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|ipx_seq_socket_start
r_static
r_void
op_star
id|ipx_seq_socket_start
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
id|ipx_interfaces_lock
)paren
suffix:semicolon
r_return
id|l
ques
c_cond
id|ipx_get_socket_idx
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
DECL|function|ipx_seq_socket_next
r_static
r_void
op_star
id|ipx_seq_socket_next
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
id|ipx_interface
op_star
id|i
suffix:semicolon
r_struct
id|ipx_opt
op_star
id|ipxs
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
l_int|NULL
suffix:semicolon
id|i
op_assign
id|ipx_interfaces_head
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_goto
id|out
suffix:semicolon
id|sk
op_assign
id|i-&gt;if_sklist
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
id|spin_lock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
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
id|ipxs
op_assign
id|ipx_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|i
op_assign
id|ipxs-&gt;intrfc
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
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
id|i
op_assign
id|ipx_interfaces_next
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_break
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;if_sklist
)paren
(brace
id|sk
op_assign
id|i-&gt;if_sklist
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|i-&gt;if_sklist_lock
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|sk
suffix:semicolon
)brace
DECL|function|ipx_seq_socket_show
r_static
r_int
id|ipx_seq_socket_show
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
id|ipx_opt
op_star
id|ipxs
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
macro_line|#ifdef CONFIG_IPX_INTERN
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Local_Address               &quot;
l_string|&quot;Remote_Address              Tx_Queue  &quot;
l_string|&quot;Rx_Queue  State  Uid&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Local_Address  Remote_Address              &quot;
l_string|&quot;Tx_Queue  Rx_Queue  State  Uid&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out
suffix:semicolon
)brace
id|s
op_assign
id|v
suffix:semicolon
id|ipxs
op_assign
id|ipx_sk
c_func
(paren
id|s
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPX_INTERN
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%08lX:%02X%02X%02X%02X%02X%02X:%04X  &quot;
comma
(paren
r_int
r_int
)paren
id|htonl
c_func
(paren
id|ipxs-&gt;intrfc-&gt;if_netnum
)paren
comma
id|ipxs-&gt;node
(braket
l_int|0
)braket
comma
id|ipxs-&gt;node
(braket
l_int|1
)braket
comma
id|ipxs-&gt;node
(braket
l_int|2
)braket
comma
id|ipxs-&gt;node
(braket
l_int|3
)braket
comma
id|ipxs-&gt;node
(braket
l_int|4
)braket
comma
id|ipxs-&gt;node
(braket
l_int|5
)braket
comma
id|htons
c_func
(paren
id|ipxs-&gt;port
)paren
)paren
suffix:semicolon
macro_line|#else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%08lX:%04X  &quot;
comma
(paren
r_int
r_int
)paren
id|htonl
c_func
(paren
id|ipxs-&gt;intrfc-&gt;if_netnum
)paren
comma
id|htons
c_func
(paren
id|ipxs-&gt;port
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_IPX_INTERN */
r_if
c_cond
(paren
id|s-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-28s&quot;
comma
l_string|&quot;Not_Connected&quot;
)paren
suffix:semicolon
r_else
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%08lX:%02X%02X%02X%02X%02X%02X:%04X  &quot;
comma
(paren
r_int
r_int
)paren
id|htonl
c_func
(paren
id|ipxs-&gt;dest_addr.net
)paren
comma
id|ipxs-&gt;dest_addr.node
(braket
l_int|0
)braket
comma
id|ipxs-&gt;dest_addr.node
(braket
l_int|1
)braket
comma
id|ipxs-&gt;dest_addr.node
(braket
l_int|2
)braket
comma
id|ipxs-&gt;dest_addr.node
(braket
l_int|3
)braket
comma
id|ipxs-&gt;dest_addr.node
(braket
l_int|4
)braket
comma
id|ipxs-&gt;dest_addr.node
(braket
l_int|5
)braket
comma
id|htons
c_func
(paren
id|ipxs-&gt;dest_addr.sock
)paren
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%08X  %08X  %02X     %03d&bslash;n&quot;
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
DECL|variable|ipx_seq_interface_ops
r_struct
id|seq_operations
id|ipx_seq_interface_ops
op_assign
(brace
dot
id|start
op_assign
id|ipx_seq_interface_start
comma
dot
id|next
op_assign
id|ipx_seq_interface_next
comma
dot
id|stop
op_assign
id|ipx_seq_interface_stop
comma
dot
id|show
op_assign
id|ipx_seq_interface_show
comma
)brace
suffix:semicolon
DECL|variable|ipx_seq_route_ops
r_struct
id|seq_operations
id|ipx_seq_route_ops
op_assign
(brace
dot
id|start
op_assign
id|ipx_seq_route_start
comma
dot
id|next
op_assign
id|ipx_seq_route_next
comma
dot
id|stop
op_assign
id|ipx_seq_route_stop
comma
dot
id|show
op_assign
id|ipx_seq_route_show
comma
)brace
suffix:semicolon
DECL|variable|ipx_seq_socket_ops
r_struct
id|seq_operations
id|ipx_seq_socket_ops
op_assign
(brace
dot
id|start
op_assign
id|ipx_seq_socket_start
comma
dot
id|next
op_assign
id|ipx_seq_socket_next
comma
dot
id|stop
op_assign
id|ipx_seq_interface_stop
comma
dot
id|show
op_assign
id|ipx_seq_socket_show
comma
)brace
suffix:semicolon
DECL|function|ipx_seq_route_open
r_static
r_int
id|ipx_seq_route_open
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
id|ipx_seq_route_ops
)paren
suffix:semicolon
)brace
DECL|function|ipx_seq_interface_open
r_static
r_int
id|ipx_seq_interface_open
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
id|ipx_seq_interface_ops
)paren
suffix:semicolon
)brace
DECL|function|ipx_seq_socket_open
r_static
r_int
id|ipx_seq_socket_open
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
id|ipx_seq_socket_ops
)paren
suffix:semicolon
)brace
DECL|variable|ipx_seq_interface_fops
r_static
r_struct
id|file_operations
id|ipx_seq_interface_fops
op_assign
(brace
dot
id|open
op_assign
id|ipx_seq_interface_open
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
DECL|variable|ipx_seq_route_fops
r_static
r_struct
id|file_operations
id|ipx_seq_route_fops
op_assign
(brace
dot
id|open
op_assign
id|ipx_seq_route_open
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
DECL|variable|ipx_seq_socket_fops
r_static
r_struct
id|file_operations
id|ipx_seq_socket_fops
op_assign
(brace
dot
id|open
op_assign
id|ipx_seq_socket_open
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
DECL|variable|ipx_proc_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|ipx_proc_dir
suffix:semicolon
DECL|function|ipx_proc_init
r_int
id|__init
id|ipx_proc_init
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
id|ipx_proc_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;ipx&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipx_proc_dir
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
id|ipx_proc_dir
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
id|ipx_seq_interface_fops
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
id|ipx_proc_dir
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
id|ipx_seq_route_fops
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
id|ipx_proc_dir
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
id|ipx_seq_socket_fops
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
id|ipx_proc_dir
)paren
suffix:semicolon
id|out_route
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;interface&quot;
comma
id|ipx_proc_dir
)paren
suffix:semicolon
id|out_interface
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;ipx&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ipx_proc_exit
r_void
id|__exit
id|ipx_proc_exit
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
id|ipx_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;route&quot;
comma
id|ipx_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;socket&quot;
comma
id|ipx_proc_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;ipx&quot;
comma
id|proc_net
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PROC_FS */
DECL|function|ipx_proc_init
r_int
id|__init
id|ipx_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipx_proc_exit
r_void
id|__exit
id|ipx_proc_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
