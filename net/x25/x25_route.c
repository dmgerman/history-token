multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine,&n; *&t;randomly fail to work with new releases, misbehave and/or generally&n; *&t;screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;Started coding.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/termios.h&gt;&t;/* For TIOCINQ/OUTQ */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/x25.h&gt;
DECL|variable|x25_route_list
r_static
r_struct
id|list_head
id|x25_route_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|x25_route_list
)paren
suffix:semicolon
DECL|variable|x25_route_list_lock
r_static
id|rwlock_t
id|x25_route_list_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *&t;Add a new route.&n; */
DECL|function|x25_add_route
r_static
r_int
id|x25_add_route
c_func
(paren
r_struct
id|x25_address
op_star
id|address
comma
r_int
r_int
id|sigdigits
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|x25_route
op_star
id|rt
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
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
id|entry
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
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|rt-&gt;address
comma
id|address
comma
id|sigdigits
)paren
op_logical_and
id|rt-&gt;sigdigits
op_eq
id|sigdigits
)paren
r_goto
id|out
suffix:semicolon
)brace
id|rt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rt
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rt
)paren
r_goto
id|out
suffix:semicolon
id|strcpy
c_func
(paren
id|rt-&gt;address.x25_addr
comma
l_string|&quot;000000000000000&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|rt-&gt;address.x25_addr
comma
id|address-&gt;x25_addr
comma
id|sigdigits
)paren
suffix:semicolon
id|rt-&gt;sigdigits
op_assign
id|sigdigits
suffix:semicolon
id|rt-&gt;dev
op_assign
id|dev
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|rt-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|rt-&gt;node
comma
op_amp
id|x25_route_list
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|write_unlock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; * __x25_remove_route - remove route from x25_route_list&n; * @rt - route to remove&n; *&n; * Remove route from x25_route_list. If it was there.&n; * Caller must hold x25_route_list_lock.&n; */
DECL|function|__x25_remove_route
r_static
r_void
id|__x25_remove_route
c_func
(paren
r_struct
id|x25_route
op_star
id|rt
)paren
(brace
r_if
c_cond
(paren
id|rt-&gt;node.next
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|rt-&gt;node
)paren
suffix:semicolon
id|x25_route_put
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
)brace
DECL|function|x25_del_route
r_static
r_int
id|x25_del_route
c_func
(paren
r_struct
id|x25_address
op_star
id|address
comma
r_int
r_int
id|sigdigits
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|x25_route
op_star
id|rt
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
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
id|entry
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
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|rt-&gt;address
comma
id|address
comma
id|sigdigits
)paren
op_logical_and
id|rt-&gt;sigdigits
op_eq
id|sigdigits
op_logical_and
id|rt-&gt;dev
op_eq
id|dev
)paren
(brace
id|__x25_remove_route
c_func
(paren
id|rt
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A device has been removed, remove its routes.&n; */
DECL|function|x25_route_device_down
r_void
id|x25_route_device_down
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|x25_route
op_star
id|rt
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|tmp
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|entry
comma
id|tmp
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
id|entry
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
id|rt-&gt;dev
op_eq
id|dev
)paren
id|__x25_remove_route
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Check that the device given is a valid X.25 interface that is &quot;up&quot;.&n; */
DECL|function|x25_dev_get
r_struct
id|net_device
op_star
id|x25_dev_get
c_func
(paren
r_char
op_star
id|devname
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_get_by_name
c_func
(paren
id|devname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_logical_and
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
op_logical_or
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_X25
macro_line|#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
op_logical_and
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
macro_line|#endif
)paren
)paren
)paren
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;x25_get_route -&t;Find a route given an X.25 address.&n; * &t;@addr - address to find a route for&n; *&n; * &t;Find a route given an X.25 address.&n; */
DECL|function|x25_get_route
r_struct
id|x25_route
op_star
id|x25_get_route
c_func
(paren
r_struct
id|x25_address
op_star
id|addr
)paren
(brace
r_struct
id|x25_route
op_star
id|rt
comma
op_star
id|use
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
id|x25_route_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
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
id|entry
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
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|rt-&gt;address
comma
id|addr
comma
id|rt-&gt;sigdigits
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|use
)paren
id|use
op_assign
id|rt
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rt-&gt;sigdigits
OG
id|use-&gt;sigdigits
)paren
id|use
op_assign
id|rt
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|use
)paren
id|x25_route_hold
c_func
(paren
id|use
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
r_return
id|use
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle the ioctls that control the routing functions.&n; */
DECL|function|x25_route_ioctl
r_int
id|x25_route_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|x25_route_struct
id|rt
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCADDRT
op_logical_and
id|cmd
op_ne
id|SIOCDELRT
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rt
comma
id|arg
comma
r_sizeof
(paren
id|rt
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rt.sigdigits
template_param
l_int|15
)paren
r_goto
id|out
suffix:semicolon
id|dev
op_assign
id|x25_dev_get
c_func
(paren
id|rt.device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|SIOCADDRT
)paren
id|rc
op_assign
id|x25_add_route
c_func
(paren
op_amp
id|rt.address
comma
id|rt.sigdigits
comma
id|dev
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|x25_del_route
c_func
(paren
op_amp
id|rt.address
comma
id|rt.sigdigits
comma
id|dev
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|x25_routes_get_info
r_int
id|x25_routes_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_struct
id|x25_route
op_star
id|rt
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;address          digits  device&bslash;n&quot;
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
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
id|entry
comma
r_struct
id|x25_route
comma
id|node
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
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
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
r_break
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Release all memory associated with X.25 routing structures.&n; */
DECL|function|x25_route_free
r_void
id|__exit
id|x25_route_free
c_func
(paren
r_void
)paren
(brace
r_struct
id|x25_route
op_star
id|rt
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|tmp
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|entry
comma
id|tmp
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
id|entry
comma
r_struct
id|x25_route
comma
id|node
)paren
suffix:semicolon
id|__x25_remove_route
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|x25_route_list_lock
)paren
suffix:semicolon
)brace
eof
