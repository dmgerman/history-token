multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; * Copyright (C) Steven Whitehouse GW7RRM (stevew@acm.org)&n; * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)&n; * Copyright (C) Hans-Joachim Hetscher DD8NE (dd8ne@bnv-bamberg.de)&n; * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
DECL|variable|ax25_route_list
r_static
id|ax25_route
op_star
id|ax25_route_list
suffix:semicolon
DECL|variable|ax25_route_lock
r_static
id|rwlock_t
id|ax25_route_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
r_static
id|ax25_route
op_star
id|ax25_get_route
c_func
(paren
id|ax25_address
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * small macro to drop non-digipeated digipeaters and reverse path&n; */
DECL|function|ax25_route_invert
r_static
r_inline
r_void
id|ax25_route_invert
c_func
(paren
id|ax25_digi
op_star
id|in
comma
id|ax25_digi
op_star
id|out
)paren
(brace
r_int
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|in-&gt;ndigi
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|in-&gt;repeated
(braket
id|k
)braket
)paren
r_break
suffix:semicolon
id|in-&gt;ndigi
op_assign
id|k
suffix:semicolon
id|ax25_digi_invert
c_func
(paren
id|in
comma
id|out
)paren
suffix:semicolon
)brace
DECL|function|ax25_rt_device_down
r_void
id|ax25_rt_device_down
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_route
op_star
id|s
comma
op_star
id|t
comma
op_star
id|ax25_rt
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
r_while
c_loop
(paren
id|ax25_rt
op_ne
l_int|NULL
)paren
(brace
id|s
op_assign
id|ax25_rt
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;dev
op_eq
id|dev
)paren
(brace
r_if
c_cond
(paren
id|ax25_route_list
op_eq
id|s
)paren
(brace
id|ax25_route_list
op_assign
id|s-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;digipeat
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|s-&gt;digipeat
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|t
op_assign
id|ax25_route_list
suffix:semicolon
id|t
op_ne
l_int|NULL
suffix:semicolon
id|t
op_assign
id|t-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;next
op_eq
id|s
)paren
(brace
id|t-&gt;next
op_assign
id|s-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;digipeat
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|s-&gt;digipeat
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
)brace
DECL|function|ax25_rt_add
r_static
r_int
id|ax25_rt_add
c_func
(paren
r_struct
id|ax25_routes_struct
op_star
id|route
)paren
(brace
id|ax25_route
op_star
id|ax25_rt
suffix:semicolon
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
r_int
id|i
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
id|route-&gt;port_addr
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
id|route-&gt;digi_count
OG
id|AX25_MAX_DIGIS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
r_while
c_loop
(paren
id|ax25_rt
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
comma
op_amp
id|route-&gt;dest_addr
)paren
op_eq
l_int|0
op_logical_and
id|ax25_rt-&gt;dev
op_eq
id|ax25_dev-&gt;dev
)paren
(brace
r_if
c_cond
(paren
id|ax25_rt-&gt;digipeat
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|ax25_rt-&gt;digipeat
)paren
suffix:semicolon
id|ax25_rt-&gt;digipeat
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|route-&gt;digi_count
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|ax25_rt-&gt;digipeat
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ax25_digi
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ax25_rt-&gt;digipeat-&gt;lastrepeat
op_assign
op_minus
l_int|1
suffix:semicolon
id|ax25_rt-&gt;digipeat-&gt;ndigi
op_assign
id|route-&gt;digi_count
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|route-&gt;digi_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ax25_rt-&gt;digipeat-&gt;repeated
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|ax25_rt-&gt;digipeat-&gt;calls
(braket
id|i
)braket
op_assign
id|route-&gt;digi_addr
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ax25_rt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ax25_route
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|ax25_rt-&gt;ref
comma
l_int|0
)paren
suffix:semicolon
id|ax25_rt-&gt;callsign
op_assign
id|route-&gt;dest_addr
suffix:semicolon
id|ax25_rt-&gt;dev
op_assign
id|ax25_dev-&gt;dev
suffix:semicolon
id|ax25_rt-&gt;digipeat
op_assign
l_int|NULL
suffix:semicolon
id|ax25_rt-&gt;ip_mode
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
id|route-&gt;digi_count
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|ax25_rt-&gt;digipeat
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ax25_digi
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ax25_rt
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ax25_rt-&gt;digipeat-&gt;lastrepeat
op_assign
op_minus
l_int|1
suffix:semicolon
id|ax25_rt-&gt;digipeat-&gt;ndigi
op_assign
id|route-&gt;digi_count
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|route-&gt;digi_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ax25_rt-&gt;digipeat-&gt;repeated
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|ax25_rt-&gt;digipeat-&gt;calls
(braket
id|i
)braket
op_assign
id|route-&gt;digi_addr
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
id|ax25_rt-&gt;next
op_assign
id|ax25_route_list
suffix:semicolon
id|ax25_route_list
op_assign
id|ax25_rt
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ax25_rt_destroy
r_static
r_void
id|ax25_rt_destroy
c_func
(paren
id|ax25_route
op_star
id|ax25_rt
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ax25_rt-&gt;ref
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ax25_rt-&gt;digipeat
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|ax25_rt-&gt;digipeat
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ax25_rt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Uh...  Route is still in use; we can&squot;t yet destroy it.  Retry later.&n;&t; */
id|init_timer
c_func
(paren
op_amp
id|ax25_rt-&gt;timer
)paren
suffix:semicolon
id|ax25_rt-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|ax25_rt
suffix:semicolon
id|ax25_rt-&gt;timer.function
op_assign
(paren
r_void
op_star
)paren
id|ax25_rt_destroy
suffix:semicolon
id|ax25_rt-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25_rt-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_rt_del
r_static
r_int
id|ax25_rt_del
c_func
(paren
r_struct
id|ax25_routes_struct
op_star
id|route
)paren
(brace
id|ax25_route
op_star
id|s
comma
op_star
id|t
comma
op_star
id|ax25_rt
suffix:semicolon
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
id|ax25_addr_ax25dev
c_func
(paren
op_amp
id|route-&gt;port_addr
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
r_while
c_loop
(paren
id|ax25_rt
op_ne
l_int|NULL
)paren
(brace
id|s
op_assign
id|ax25_rt
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;dev
op_eq
id|ax25_dev-&gt;dev
op_logical_and
id|ax25cmp
c_func
(paren
op_amp
id|route-&gt;dest_addr
comma
op_amp
id|s-&gt;callsign
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ax25_route_list
op_eq
id|s
)paren
(brace
id|ax25_route_list
op_assign
id|s-&gt;next
suffix:semicolon
id|ax25_rt_destroy
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|t
op_assign
id|ax25_route_list
suffix:semicolon
id|t
op_ne
l_int|NULL
suffix:semicolon
id|t
op_assign
id|t-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;next
op_eq
id|s
)paren
(brace
id|t-&gt;next
op_assign
id|s-&gt;next
suffix:semicolon
id|ax25_rt_destroy
c_func
(paren
id|s
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ax25_rt_opt
r_static
r_int
id|ax25_rt_opt
c_func
(paren
r_struct
id|ax25_route_opt_struct
op_star
id|rt_option
)paren
(brace
id|ax25_route
op_star
id|ax25_rt
suffix:semicolon
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
r_int
id|err
op_assign
l_int|0
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
id|rt_option-&gt;port_addr
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
r_while
c_loop
(paren
id|ax25_rt
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ax25_rt-&gt;dev
op_eq
id|ax25_dev-&gt;dev
op_logical_and
id|ax25cmp
c_func
(paren
op_amp
id|rt_option-&gt;dest_addr
comma
op_amp
id|ax25_rt-&gt;callsign
)paren
op_eq
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|rt_option-&gt;cmd
)paren
(brace
r_case
id|AX25_SET_RT_IPMODE
suffix:colon
r_switch
c_cond
(paren
id|rt_option-&gt;arg
)paren
(brace
r_case
l_char|&squot; &squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;V&squot;
suffix:colon
id|ax25_rt-&gt;ip_mode
op_assign
id|rt_option-&gt;arg
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
suffix:semicolon
)brace
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ax25_rt_ioctl
r_int
id|ax25_rt_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|ax25_route_opt_struct
id|rt_option
suffix:semicolon
r_struct
id|ax25_routes_struct
id|route
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
id|route
comma
id|arg
comma
r_sizeof
(paren
id|route
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ax25_rt_add
c_func
(paren
op_amp
id|route
)paren
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
id|route
comma
id|arg
comma
r_sizeof
(paren
id|route
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ax25_rt_del
c_func
(paren
op_amp
id|route
)paren
suffix:semicolon
r_case
id|SIOCAX25OPTRT
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rt_option
comma
id|arg
comma
r_sizeof
(paren
id|rt_option
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ax25_rt_opt
c_func
(paren
op_amp
id|rt_option
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|ax25_rt_seq_start
r_static
r_void
op_star
id|ax25_rt_seq_start
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
r_struct
id|ax25_route
op_star
id|ax25_rt
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
op_eq
l_int|0
)paren
r_return
id|SEQ_START_TOKEN
suffix:semicolon
r_for
c_loop
(paren
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
id|ax25_rt
op_ne
l_int|NULL
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
op_star
id|pos
)paren
r_return
id|ax25_rt
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ax25_rt_seq_next
r_static
r_void
op_star
id|ax25_rt_seq_next
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
op_increment
op_star
id|pos
suffix:semicolon
r_return
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
ques
c_cond
id|ax25_route_list
suffix:colon
(paren
(paren
r_struct
id|ax25_route
op_star
)paren
id|v
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
DECL|function|ax25_rt_seq_stop
r_static
r_void
id|ax25_rt_seq_stop
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
id|read_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
)brace
DECL|function|ax25_rt_seq_show
r_static
r_int
id|ax25_rt_seq_show
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
op_eq
id|SEQ_START_TOKEN
)paren
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;callsign  dev  mode digipeaters&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_struct
id|ax25_route
op_star
id|ax25_rt
op_assign
id|v
suffix:semicolon
r_const
r_char
op_star
id|callsign
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
comma
op_amp
id|null_ax25_address
)paren
op_eq
l_int|0
)paren
id|callsign
op_assign
l_string|&quot;default&quot;
suffix:semicolon
r_else
id|callsign
op_assign
id|ax2asc
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-9s %-4s&quot;
comma
id|callsign
comma
id|ax25_rt-&gt;dev
ques
c_cond
id|ax25_rt-&gt;dev-&gt;name
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ax25_rt-&gt;ip_mode
)paren
(brace
r_case
l_char|&squot;V&squot;
suffix:colon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;   vc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;   dg&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;    *&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25_rt-&gt;digipeat
op_ne
l_int|NULL
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ax25_rt-&gt;digipeat-&gt;ndigi
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %s&quot;
comma
id|ax2asc
c_func
(paren
op_amp
id|ax25_rt-&gt;digipeat-&gt;calls
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ax25_rt_seqops
r_static
r_struct
id|seq_operations
id|ax25_rt_seqops
op_assign
(brace
dot
id|start
op_assign
id|ax25_rt_seq_start
comma
dot
id|next
op_assign
id|ax25_rt_seq_next
comma
dot
id|stop
op_assign
id|ax25_rt_seq_stop
comma
dot
id|show
op_assign
id|ax25_rt_seq_show
comma
)brace
suffix:semicolon
DECL|function|ax25_rt_info_open
r_static
r_int
id|ax25_rt_info_open
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
id|ax25_rt_seqops
)paren
suffix:semicolon
)brace
DECL|variable|ax25_route_fops
r_struct
id|file_operations
id|ax25_route_fops
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
id|ax25_rt_info_open
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
macro_line|#endif
multiline_comment|/*&n; *&t;Find AX.25 route&n; *&n; *&t;Only routes with a refernce rout of zero can be destroyed.&n; */
DECL|function|ax25_get_route
r_static
id|ax25_route
op_star
id|ax25_get_route
c_func
(paren
id|ax25_address
op_star
id|addr
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_route
op_star
id|ax25_spe_rt
op_assign
l_int|NULL
suffix:semicolon
id|ax25_route
op_star
id|ax25_def_rt
op_assign
l_int|NULL
suffix:semicolon
id|ax25_route
op_star
id|ax25_rt
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Bind to the physical interface we heard them on, or the default&n;&t; *&t;route if none is found;&n;&t; */
r_for
c_loop
(paren
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
id|ax25_rt
op_ne
l_int|NULL
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
comma
id|addr
)paren
op_eq
l_int|0
op_logical_and
id|ax25_rt-&gt;dev
op_ne
l_int|NULL
)paren
id|ax25_spe_rt
op_assign
id|ax25_rt
suffix:semicolon
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
comma
op_amp
id|null_ax25_address
)paren
op_eq
l_int|0
op_logical_and
id|ax25_rt-&gt;dev
op_ne
l_int|NULL
)paren
id|ax25_def_rt
op_assign
id|ax25_rt
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
comma
id|addr
)paren
op_eq
l_int|0
op_logical_and
id|ax25_rt-&gt;dev
op_eq
id|dev
)paren
id|ax25_spe_rt
op_assign
id|ax25_rt
suffix:semicolon
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|ax25_rt-&gt;callsign
comma
op_amp
id|null_ax25_address
)paren
op_eq
l_int|0
op_logical_and
id|ax25_rt-&gt;dev
op_eq
id|dev
)paren
id|ax25_def_rt
op_assign
id|ax25_rt
suffix:semicolon
)brace
)brace
id|ax25_rt
op_assign
id|ax25_def_rt
suffix:semicolon
r_if
c_cond
(paren
id|ax25_spe_rt
op_ne
l_int|NULL
)paren
id|ax25_rt
op_assign
id|ax25_spe_rt
suffix:semicolon
r_if
c_cond
(paren
id|ax25_rt
op_ne
l_int|NULL
)paren
id|atomic_inc
c_func
(paren
op_amp
id|ax25_rt-&gt;ref
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_return
id|ax25_rt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Adjust path: If you specify a default route and want to connect&n; *      a target on the digipeater path but w/o having a special route&n; *&t;set before, the path has to be truncated from your target on.&n; */
DECL|function|ax25_adjust_path
r_static
r_inline
r_void
id|ax25_adjust_path
c_func
(paren
id|ax25_address
op_star
id|addr
comma
id|ax25_digi
op_star
id|digipeat
)paren
(brace
r_int
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|digipeat-&gt;ndigi
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
id|addr
comma
op_amp
id|digipeat-&gt;calls
(braket
id|k
)braket
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|digipeat-&gt;ndigi
op_assign
id|k
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Find which interface to use.&n; */
DECL|function|ax25_rt_autobind
r_int
id|ax25_rt_autobind
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
id|ax25_address
op_star
id|addr
)paren
(brace
id|ax25_route
op_star
id|ax25_rt
suffix:semicolon
id|ax25_address
op_star
id|call
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_rt
op_assign
id|ax25_get_route
c_func
(paren
id|addr
comma
l_int|NULL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EHOSTUNREACH
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25-&gt;ax25_dev
op_assign
id|ax25_dev_ax25dev
c_func
(paren
id|ax25_rt-&gt;dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|EHOSTUNREACH
suffix:semicolon
r_goto
id|put
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|call
op_assign
id|ax25_findbyuid
c_func
(paren
id|current-&gt;euid
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ax25_uid_policy
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_BIND_SERVICE
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|put
suffix:semicolon
)brace
id|call
op_assign
(paren
id|ax25_address
op_star
)paren
id|ax25-&gt;ax25_dev-&gt;dev-&gt;dev_addr
suffix:semicolon
)brace
id|ax25-&gt;source_addr
op_assign
op_star
id|call
suffix:semicolon
r_if
c_cond
(paren
id|ax25_rt-&gt;digipeat
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|ax25-&gt;digipeat
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ax25_digi
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|put
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|ax25-&gt;digipeat
comma
id|ax25_rt-&gt;digipeat
comma
r_sizeof
(paren
id|ax25_digi
)paren
)paren
suffix:semicolon
id|ax25_adjust_path
c_func
(paren
id|addr
comma
id|ax25-&gt;digipeat
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
)paren
(brace
id|bh_lock_sock
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
id|ax25-&gt;sk-&gt;sk_zapped
op_assign
l_int|0
suffix:semicolon
id|bh_unlock_sock
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
)brace
id|put
suffix:colon
id|ax25_put_route
c_func
(paren
id|ax25_rt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ax25_rt_find_route
id|ax25_route
op_star
id|ax25_rt_find_route
c_func
(paren
id|ax25_route
op_star
id|route
comma
id|ax25_address
op_star
id|addr
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_route
op_star
id|ax25_rt
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_rt
op_assign
id|ax25_get_route
c_func
(paren
id|addr
comma
id|dev
)paren
)paren
)paren
r_return
id|ax25_rt
suffix:semicolon
id|route-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|route-&gt;ref
comma
l_int|1
)paren
suffix:semicolon
id|route-&gt;callsign
op_assign
op_star
id|addr
suffix:semicolon
id|route-&gt;dev
op_assign
id|dev
suffix:semicolon
id|route-&gt;digipeat
op_assign
l_int|NULL
suffix:semicolon
id|route-&gt;ip_mode
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_return
id|route
suffix:semicolon
)brace
DECL|function|ax25_rt_build_path
r_struct
id|sk_buff
op_star
id|ax25_rt_build_path
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|digi
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
op_star
id|bp
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|digi-&gt;ndigi
op_star
id|AX25_ADDR_LEN
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|len
)paren
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|len
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;AX.25: ax25_dg_build_path - out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;sk
op_ne
l_int|NULL
)paren
id|skb_set_owner_w
c_func
(paren
id|skbn
comma
id|skb-&gt;sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skbn
suffix:semicolon
)brace
id|bp
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|ax25_addr_build
c_func
(paren
id|bp
comma
id|src
comma
id|dest
comma
id|digi
comma
id|AX25_COMMAND
comma
id|AX25_MODULUS
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Free all memory associated with routing structures.&n; */
DECL|function|ax25_rt_free
r_void
id|__exit
id|ax25_rt_free
c_func
(paren
r_void
)paren
(brace
id|ax25_route
op_star
id|s
comma
op_star
id|ax25_rt
op_assign
id|ax25_route_list
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ax25_rt
op_ne
l_int|NULL
)paren
(brace
id|s
op_assign
id|ax25_rt
suffix:semicolon
id|ax25_rt
op_assign
id|ax25_rt-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;digipeat
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|s-&gt;digipeat
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_route_lock
)paren
suffix:semicolon
)brace
eof
