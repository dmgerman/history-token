multiline_comment|/*&n; *&t;AX.25 release 037&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Other kernels modules in this kit are generally BSD derived. See the copyright headers.&n; *&n; *&n; *&t;History&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Split from ax25_route.c.&n; */
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
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|ax25_dev_list
id|ax25_dev
op_star
id|ax25_dev_list
suffix:semicolon
DECL|variable|ax25_dev_lock
id|spinlock_t
id|ax25_dev_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|ax25_dev_ax25dev
id|ax25_dev
op_star
id|ax25_dev_ax25dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_dev
op_star
id|ax25_dev
comma
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ax25_dev
op_assign
id|ax25_dev_list
suffix:semicolon
id|ax25_dev
op_ne
l_int|NULL
suffix:semicolon
id|ax25_dev
op_assign
id|ax25_dev-&gt;next
)paren
r_if
c_cond
(paren
id|ax25_dev-&gt;dev
op_eq
id|dev
)paren
(brace
id|res
op_assign
id|ax25_dev
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|ax25_addr_ax25dev
id|ax25_dev
op_star
id|ax25_addr_ax25dev
c_func
(paren
id|ax25_address
op_star
id|addr
)paren
(brace
id|ax25_dev
op_star
id|ax25_dev
comma
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ax25_dev
op_assign
id|ax25_dev_list
suffix:semicolon
id|ax25_dev
op_ne
l_int|NULL
suffix:semicolon
id|ax25_dev
op_assign
id|ax25_dev-&gt;next
)paren
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
id|addr
comma
(paren
id|ax25_address
op_star
)paren
id|ax25_dev-&gt;dev-&gt;dev_addr
)paren
op_eq
l_int|0
)paren
(brace
id|res
op_assign
id|ax25_dev
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This is called when an interface is brought up. These are&n; *&t;reasonable defaults.&n; */
DECL|function|ax25_dev_device_up
r_void
id|ax25_dev_device_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ax25_dev
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AX.25: ax25_dev_device_up - out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ax25_unregister_sysctl
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ax25_dev
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|ax25_dev
)paren
)paren
suffix:semicolon
id|ax25_dev-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ax25_dev-&gt;forward
op_assign
l_int|NULL
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_IPDEFMODE
)braket
op_assign
id|AX25_DEF_IPDEFMODE
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_AXDEFMODE
)braket
op_assign
id|AX25_DEF_AXDEFMODE
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_BACKOFF
)braket
op_assign
id|AX25_DEF_BACKOFF
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_CONMODE
)braket
op_assign
id|AX25_DEF_CONMODE
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_WINDOW
)braket
op_assign
id|AX25_DEF_WINDOW
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_EWINDOW
)braket
op_assign
id|AX25_DEF_EWINDOW
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_T1
)braket
op_assign
id|AX25_DEF_T1
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_T2
)braket
op_assign
id|AX25_DEF_T2
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_T3
)braket
op_assign
id|AX25_DEF_T3
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_IDLE
)braket
op_assign
id|AX25_DEF_IDLE
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_N2
)braket
op_assign
id|AX25_DEF_N2
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_PACLEN
)braket
op_assign
id|AX25_DEF_PACLEN
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
op_assign
id|AX25_DEF_PROTOCOL
suffix:semicolon
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_DS_TIMEOUT
)braket
op_assign
id|AX25_DEF_DS_TIMEOUT
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
id|ax25_dev-&gt;next
op_assign
id|ax25_dev_list
suffix:semicolon
id|ax25_dev_list
op_assign
id|ax25_dev
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
id|ax25_register_sysctl
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ax25_dev_device_down
r_void
id|ax25_dev_device_down
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_dev
op_star
id|s
comma
op_star
id|ax25_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|ax25_dev_ax25dev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|ax25_unregister_sysctl
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
id|ax25_ds_del_timer
c_func
(paren
id|ax25_dev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Remove any packet forwarding that points to this device.&n;&t; */
r_for
c_loop
(paren
id|s
op_assign
id|ax25_dev_list
suffix:semicolon
id|s
op_ne
l_int|NULL
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
r_if
c_cond
(paren
id|s-&gt;forward
op_eq
id|dev
)paren
id|s-&gt;forward
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|s
op_assign
id|ax25_dev_list
)paren
op_eq
id|ax25_dev
)paren
(brace
id|ax25_dev_list
op_assign
id|s-&gt;next
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ax25_dev
)paren
suffix:semicolon
id|ax25_register_sysctl
c_func
(paren
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
id|ax25_dev
)paren
(brace
id|s-&gt;next
op_assign
id|ax25_dev-&gt;next
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ax25_dev
)paren
suffix:semicolon
id|ax25_register_sysctl
c_func
(paren
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
id|ax25_register_sysctl
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ax25_fwd_ioctl
r_int
id|ax25_fwd_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_struct
id|ax25_fwd_struct
op_star
id|fwd
)paren
(brace
id|ax25_dev
op_star
id|ax25_dev
comma
op_star
id|fwd_dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|ax25_addr_ax25dev
c_func
(paren
op_amp
id|fwd-&gt;port_from
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCAX25ADDFWD
suffix:colon
r_if
c_cond
(paren
(paren
id|fwd_dev
op_assign
id|ax25_addr_ax25dev
c_func
(paren
op_amp
id|fwd-&gt;port_to
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ax25_dev-&gt;forward
op_ne
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ax25_dev-&gt;forward
op_assign
id|fwd_dev-&gt;dev
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCAX25DELFWD
suffix:colon
r_if
c_cond
(paren
id|ax25_dev-&gt;forward
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ax25_dev-&gt;forward
op_assign
l_int|NULL
suffix:semicolon
r_break
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
DECL|function|ax25_fwd_dev
r_struct
id|net_device
op_star
id|ax25_fwd_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|ax25_dev_ax25dev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|ax25_dev-&gt;forward
op_eq
l_int|NULL
)paren
r_return
id|dev
suffix:semicolon
r_return
id|ax25_dev-&gt;forward
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Free all memory associated with device structures.&n; */
DECL|function|ax25_dev_free
r_void
id|__exit
id|ax25_dev_free
c_func
(paren
r_void
)paren
(brace
id|ax25_dev
op_star
id|s
comma
op_star
id|ax25_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
id|ax25_dev
op_assign
id|ax25_dev_list
suffix:semicolon
r_while
c_loop
(paren
id|ax25_dev
op_ne
l_int|NULL
)paren
(brace
id|s
op_assign
id|ax25_dev
suffix:semicolon
id|ax25_dev
op_assign
id|ax25_dev-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
id|ax25_dev_list
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ax25_dev_lock
comma
id|flags
)paren
suffix:semicolon
)brace
eof
