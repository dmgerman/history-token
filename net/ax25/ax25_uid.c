multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
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
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/arp.h&gt;
multiline_comment|/*&n; *&t;Callsign/UID mapper. This is in kernel space for security on multi-amateur machines.&n; */
DECL|variable|ax25_uid_list
r_static
id|ax25_uid_assoc
op_star
id|ax25_uid_list
suffix:semicolon
DECL|variable|ax25_uid_lock
r_static
id|rwlock_t
id|ax25_uid_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|ax25_uid_policy
r_int
id|ax25_uid_policy
op_assign
l_int|0
suffix:semicolon
DECL|function|ax25_findbyuid
id|ax25_address
op_star
id|ax25_findbyuid
c_func
(paren
id|uid_t
id|uid
)paren
(brace
id|ax25_uid_assoc
op_star
id|ax25_uid
suffix:semicolon
id|ax25_address
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ax25_uid
op_assign
id|ax25_uid_list
suffix:semicolon
id|ax25_uid
op_ne
l_int|NULL
suffix:semicolon
id|ax25_uid
op_assign
id|ax25_uid-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ax25_uid-&gt;uid
op_eq
id|uid
)paren
(brace
id|res
op_assign
op_amp
id|ax25_uid-&gt;call
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ax25_uid_ioctl
r_int
id|ax25_uid_ioctl
c_func
(paren
r_int
id|cmd
comma
r_struct
id|sockaddr_ax25
op_star
id|sax
)paren
(brace
id|ax25_uid_assoc
op_star
id|s
comma
op_star
id|ax25_uid
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCAX25GETUID
suffix:colon
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ax25_uid
op_assign
id|ax25_uid_list
suffix:semicolon
id|ax25_uid
op_ne
l_int|NULL
suffix:semicolon
id|ax25_uid
op_assign
id|ax25_uid-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|sax-&gt;sax25_call
comma
op_amp
id|ax25_uid-&gt;call
)paren
op_eq
l_int|0
)paren
(brace
id|res
op_assign
id|ax25_uid-&gt;uid
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
r_case
id|SIOCAX25ADDUID
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|ax25_findbyuid
c_func
(paren
id|sax-&gt;sax25_uid
)paren
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|sax-&gt;sax25_uid
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_uid
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ax25_uid
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ax25_uid-&gt;uid
op_assign
id|sax-&gt;sax25_uid
suffix:semicolon
id|ax25_uid-&gt;call
op_assign
id|sax-&gt;sax25_call
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
id|ax25_uid-&gt;next
op_assign
id|ax25_uid_list
suffix:semicolon
id|ax25_uid_list
op_assign
id|ax25_uid
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SIOCAX25DELUID
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ax25_uid
op_assign
id|ax25_uid_list
suffix:semicolon
id|ax25_uid
op_ne
l_int|NULL
suffix:semicolon
id|ax25_uid
op_assign
id|ax25_uid-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|sax-&gt;sax25_call
comma
op_amp
id|ax25_uid-&gt;call
)paren
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ax25_uid
op_eq
l_int|NULL
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|s
op_assign
id|ax25_uid_list
)paren
op_eq
id|ax25_uid
)paren
(brace
id|ax25_uid_list
op_assign
id|s-&gt;next
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ax25_uid
)paren
suffix:semicolon
r_return
l_int|0
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
id|ax25_uid
)paren
(brace
id|s-&gt;next
op_assign
id|ax25_uid-&gt;next
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ax25_uid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|s
op_assign
id|s-&gt;next
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*NOTREACHED */
)brace
DECL|function|ax25_uid_get_info
r_int
id|ax25_uid_get_info
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
id|ax25_uid_assoc
op_star
id|pt
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
id|read_lock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Policy: %d&bslash;n&quot;
comma
id|ax25_uid_policy
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|ax25_uid_list
suffix:semicolon
id|pt
op_ne
l_int|NULL
suffix:semicolon
id|pt
op_assign
id|pt-&gt;next
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
l_string|&quot;%6d %s&bslash;n&quot;
comma
id|pt-&gt;uid
comma
id|ax2asc
c_func
(paren
op_amp
id|pt-&gt;call
)paren
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
id|read_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
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
id|offset
op_minus
id|begin
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
multiline_comment|/*&n; *&t;Free all memory associated with UID/Callsign structures.&n; */
DECL|function|ax25_uid_free
r_void
id|__exit
id|ax25_uid_free
c_func
(paren
r_void
)paren
(brace
id|ax25_uid_assoc
op_star
id|s
comma
op_star
id|ax25_uid
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
id|ax25_uid
op_assign
id|ax25_uid_list
suffix:semicolon
r_while
c_loop
(paren
id|ax25_uid
op_ne
l_int|NULL
)paren
(brace
id|s
op_assign
id|ax25_uid
suffix:semicolon
id|ax25_uid
op_assign
id|ax25_uid-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
id|ax25_uid_list
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ax25_uid_lock
)paren
suffix:semicolon
)brace
eof
