multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;Started coding.&n; */
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
id|x25_route
op_star
id|x25_route_list
multiline_comment|/* = NULL initially */
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
id|x25_route
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_for
c_loop
(paren
id|x25_route
op_assign
id|x25_route_list
suffix:semicolon
id|x25_route
op_ne
l_int|NULL
suffix:semicolon
id|x25_route
op_assign
id|x25_route-&gt;next
)paren
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|x25_route-&gt;address
comma
id|address
comma
id|sigdigits
)paren
op_eq
l_int|0
op_logical_and
id|x25_route-&gt;sigdigits
op_eq
id|sigdigits
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x25_route
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|x25_route
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|strcpy
c_func
(paren
id|x25_route-&gt;address.x25_addr
comma
l_string|&quot;000000000000000&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|x25_route-&gt;address.x25_addr
comma
id|address-&gt;x25_addr
comma
id|sigdigits
)paren
suffix:semicolon
id|x25_route-&gt;sigdigits
op_assign
id|sigdigits
suffix:semicolon
id|x25_route-&gt;dev
op_assign
id|dev
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|x25_route-&gt;next
op_assign
id|x25_route_list
suffix:semicolon
id|x25_route_list
op_assign
id|x25_route
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|x25_remove_route
r_static
r_void
id|x25_remove_route
c_func
(paren
r_struct
id|x25_route
op_star
id|x25_route
)paren
(brace
r_struct
id|x25_route
op_star
id|s
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|s
op_assign
id|x25_route_list
)paren
op_eq
id|x25_route
)paren
(brace
id|x25_route_list
op_assign
id|x25_route-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|x25_route
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|s
op_ne
l_int|NULL
op_logical_and
id|s-&gt;next
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;next
op_eq
id|x25_route
)paren
(brace
id|s-&gt;next
op_assign
id|x25_route-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|x25_route
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|s
op_assign
id|s-&gt;next
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
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
id|x25_route
suffix:semicolon
r_for
c_loop
(paren
id|x25_route
op_assign
id|x25_route_list
suffix:semicolon
id|x25_route
op_ne
l_int|NULL
suffix:semicolon
id|x25_route
op_assign
id|x25_route-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|x25_route-&gt;address
comma
id|address
comma
id|sigdigits
)paren
op_eq
l_int|0
op_logical_and
id|x25_route-&gt;sigdigits
op_eq
id|sigdigits
op_logical_and
id|x25_route-&gt;dev
op_eq
id|dev
)paren
(brace
id|x25_remove_route
c_func
(paren
id|x25_route
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
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
id|route
comma
op_star
id|x25_route
op_assign
id|x25_route_list
suffix:semicolon
r_while
c_loop
(paren
id|x25_route
op_ne
l_int|NULL
)paren
(brace
id|route
op_assign
id|x25_route
suffix:semicolon
id|x25_route
op_assign
id|x25_route-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|route-&gt;dev
op_eq
id|dev
)paren
id|x25_remove_route
c_func
(paren
id|route
)paren
suffix:semicolon
)brace
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
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|dev_get_by_name
c_func
(paren
id|devname
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
op_logical_and
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_X25
macro_line|#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
op_logical_or
id|dev-&gt;type
op_eq
id|ARPHRD_ETHER
macro_line|#endif
)paren
)paren
r_return
id|dev
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Find a device given an X.25 address.&n; */
DECL|function|x25_get_route
r_struct
id|net_device
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
id|route
comma
op_star
id|use
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|route
op_assign
id|x25_route_list
suffix:semicolon
id|route
op_ne
l_int|NULL
suffix:semicolon
id|route
op_assign
id|route-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|route-&gt;address
comma
id|addr
comma
id|route-&gt;sigdigits
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|use
op_eq
l_int|NULL
)paren
(brace
id|use
op_assign
id|route
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|route-&gt;sigdigits
OG
id|use-&gt;sigdigits
)paren
id|use
op_assign
id|route
suffix:semicolon
)brace
)brace
)brace
r_return
(paren
id|use
op_ne
l_int|NULL
)paren
ques
c_cond
id|use-&gt;dev
suffix:colon
l_int|NULL
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
id|x25_route
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCADDRT
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|x25_route
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|x25_route_struct
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
id|x25_route.sigdigits
template_param
l_int|15
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|x25_dev_get
c_func
(paren
id|x25_route.device
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|x25_add_route
c_func
(paren
op_amp
id|x25_route.address
comma
id|x25_route.sigdigits
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
r_return
id|err
suffix:semicolon
r_case
id|SIOCDELRT
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|x25_route
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|x25_route_struct
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
id|x25_route.sigdigits
template_param
l_int|15
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|x25_dev_get
c_func
(paren
id|x25_route.device
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|x25_del_route
c_func
(paren
op_amp
id|x25_route.address
comma
id|x25_route.sigdigits
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
r_return
id|err
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
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
id|x25_route
suffix:semicolon
r_int
id|len
op_assign
l_int|0
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;address          digits  device&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x25_route
op_assign
id|x25_route_list
suffix:semicolon
id|x25_route
op_ne
l_int|NULL
suffix:semicolon
id|x25_route
op_assign
id|x25_route-&gt;next
)paren
(brace
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
id|x25_route-&gt;address.x25_addr
comma
id|x25_route-&gt;sigdigits
comma
(paren
id|x25_route-&gt;dev
op_ne
l_int|NULL
)paren
ques
c_cond
id|x25_route-&gt;dev-&gt;name
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
id|sti
c_func
(paren
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
id|route
comma
op_star
id|x25_route
op_assign
id|x25_route_list
suffix:semicolon
r_while
c_loop
(paren
id|x25_route
op_ne
l_int|NULL
)paren
(brace
id|route
op_assign
id|x25_route
suffix:semicolon
id|x25_route
op_assign
id|x25_route-&gt;next
suffix:semicolon
id|x25_remove_route
c_func
(paren
id|route
)paren
suffix:semicolon
)brace
)brace
eof
