multiline_comment|/*&n; *&t;ip6_flowlabel.c&t;&t;IPv6 flowlabel manager.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/rawv6.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|FL_MIN_LINGER
mdefine_line|#define FL_MIN_LINGER&t;6&t;/* Minimal linger. It is set to 6sec specified&n;&t;&t;&t;&t;   in old IPv6 RFC. Well, it was reasonable value.&n;&t;&t;&t;&t; */
DECL|macro|FL_MAX_LINGER
mdefine_line|#define FL_MAX_LINGER&t;60&t;/* Maximal linger timeout */
multiline_comment|/* FL hash table */
DECL|macro|FL_MAX_PER_SOCK
mdefine_line|#define FL_MAX_PER_SOCK&t;32
DECL|macro|FL_MAX_SIZE
mdefine_line|#define FL_MAX_SIZE&t;4096
DECL|macro|FL_HASH_MASK
mdefine_line|#define FL_HASH_MASK&t;255
DECL|macro|FL_HASH
mdefine_line|#define FL_HASH(l)&t;(ntohl(l)&amp;FL_HASH_MASK)
DECL|variable|fl_size
r_static
id|atomic_t
id|fl_size
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|fl_ht
r_static
r_struct
id|ip6_flowlabel
op_star
id|fl_ht
(braket
id|FL_HASH_MASK
op_plus
l_int|1
)braket
suffix:semicolon
r_static
r_void
id|ip6_fl_gc
c_func
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
DECL|variable|ip6_fl_gc_timer
r_static
r_struct
id|timer_list
id|ip6_fl_gc_timer
op_assign
id|TIMER_INITIALIZER
c_func
(paren
id|ip6_fl_gc
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* FL hash table lock: it protects only of GC */
DECL|variable|ip6_fl_lock
r_static
id|rwlock_t
id|ip6_fl_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Big socket sock */
DECL|variable|ip6_sk_fl_lock
r_static
id|rwlock_t
id|ip6_sk_fl_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|__fl_lookup
r_static
id|__inline__
r_struct
id|ip6_flowlabel
op_star
id|__fl_lookup
c_func
(paren
id|u32
id|label
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
suffix:semicolon
r_for
c_loop
(paren
id|fl
op_assign
id|fl_ht
(braket
id|FL_HASH
c_func
(paren
id|label
)paren
)braket
suffix:semicolon
id|fl
suffix:semicolon
id|fl
op_assign
id|fl-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|fl-&gt;label
op_eq
id|label
)paren
r_return
id|fl
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|fl_lookup
r_static
r_struct
id|ip6_flowlabel
op_star
id|fl_lookup
c_func
(paren
id|u32
id|label
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
id|fl
op_assign
id|__fl_lookup
c_func
(paren
id|label
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl
)paren
id|atomic_inc
c_func
(paren
op_amp
id|fl-&gt;users
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
r_return
id|fl
suffix:semicolon
)brace
DECL|function|fl_free
r_static
r_void
id|fl_free
c_func
(paren
r_struct
id|ip6_flowlabel
op_star
id|fl
)paren
(brace
r_if
c_cond
(paren
id|fl-&gt;opt
)paren
id|kfree
c_func
(paren
id|fl-&gt;opt
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fl
)paren
suffix:semicolon
)brace
DECL|function|fl_release
r_static
r_void
id|fl_release
c_func
(paren
r_struct
id|ip6_flowlabel
op_star
id|fl
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
id|fl-&gt;lastuse
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|fl-&gt;users
)paren
)paren
(brace
r_int
r_int
id|ttd
op_assign
id|fl-&gt;lastuse
op_plus
id|fl-&gt;linger
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|ttd
comma
id|fl-&gt;expires
)paren
)paren
id|fl-&gt;expires
op_assign
id|ttd
suffix:semicolon
id|ttd
op_assign
id|fl-&gt;expires
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;opt
op_logical_and
id|fl-&gt;share
op_eq
id|IPV6_FL_S_EXCL
)paren
(brace
r_struct
id|ipv6_txoptions
op_star
id|opt
op_assign
id|fl-&gt;opt
suffix:semicolon
id|fl-&gt;opt
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|opt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|ip6_fl_gc_timer
)paren
op_logical_or
id|time_after
c_func
(paren
id|ip6_fl_gc_timer.expires
comma
id|ttd
)paren
)paren
id|mod_timer
c_func
(paren
op_amp
id|ip6_fl_gc_timer
comma
id|ttd
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
)brace
DECL|function|ip6_fl_gc
r_static
r_void
id|ip6_fl_gc
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_int
r_int
id|sched
op_assign
l_int|0
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|FL_HASH_MASK
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
comma
op_star
op_star
id|flp
suffix:semicolon
id|flp
op_assign
op_amp
id|fl_ht
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|fl
op_assign
op_star
id|flp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|fl-&gt;users
)paren
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|ttd
op_assign
id|fl-&gt;lastuse
op_plus
id|fl-&gt;linger
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|ttd
comma
id|fl-&gt;expires
)paren
)paren
id|fl-&gt;expires
op_assign
id|ttd
suffix:semicolon
id|ttd
op_assign
id|fl-&gt;expires
suffix:semicolon
r_if
c_cond
(paren
id|time_after_eq
c_func
(paren
id|now
comma
id|ttd
)paren
)paren
(brace
op_star
id|flp
op_assign
id|fl-&gt;next
suffix:semicolon
id|fl_free
c_func
(paren
id|fl
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|fl_size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sched
op_logical_or
id|time_before
c_func
(paren
id|ttd
comma
id|sched
)paren
)paren
id|sched
op_assign
id|ttd
suffix:semicolon
)brace
id|flp
op_assign
op_amp
id|fl-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sched
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|fl_size
)paren
)paren
id|sched
op_assign
id|now
op_plus
id|FL_MAX_LINGER
suffix:semicolon
r_if
c_cond
(paren
id|sched
)paren
(brace
id|ip6_fl_gc_timer.expires
op_assign
id|sched
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ip6_fl_gc_timer
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
)brace
DECL|function|fl_intern
r_static
r_int
id|fl_intern
c_func
(paren
r_struct
id|ip6_flowlabel
op_star
id|fl
comma
id|__u32
id|label
)paren
(brace
id|fl-&gt;label
op_assign
id|label
op_amp
id|IPV6_FLOWLABEL_MASK
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|label
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|fl-&gt;label
op_assign
id|htonl
c_func
(paren
id|net_random
c_func
(paren
)paren
)paren
op_amp
id|IPV6_FLOWLABEL_MASK
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;label
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|lfl
suffix:semicolon
id|lfl
op_assign
id|__fl_lookup
c_func
(paren
id|fl-&gt;label
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lfl
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
id|fl-&gt;lastuse
op_assign
id|jiffies
suffix:semicolon
id|fl-&gt;next
op_assign
id|fl_ht
(braket
id|FL_HASH
c_func
(paren
id|fl-&gt;label
)paren
)braket
suffix:semicolon
id|fl_ht
(braket
id|FL_HASH
c_func
(paren
id|fl-&gt;label
)paren
)braket
op_assign
id|fl
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|fl_size
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Socket flowlabel lists */
DECL|function|fl6_sock_lookup
r_struct
id|ip6_flowlabel
op_star
id|fl6_sock_lookup
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u32
id|label
)paren
(brace
r_struct
id|ipv6_fl_socklist
op_star
id|sfl
suffix:semicolon
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|label
op_and_assign
id|IPV6_FLOWLABEL_MASK
suffix:semicolon
r_for
c_loop
(paren
id|sfl
op_assign
id|np-&gt;ipv6_fl_list
suffix:semicolon
id|sfl
suffix:semicolon
id|sfl
op_assign
id|sfl-&gt;next
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
op_assign
id|sfl-&gt;fl
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;label
op_eq
id|label
)paren
(brace
id|fl-&gt;lastuse
op_assign
id|jiffies
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|fl-&gt;users
)paren
suffix:semicolon
r_return
id|fl
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|fl6_free_socklist
r_void
id|fl6_free_socklist
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|ipv6_fl_socklist
op_star
id|sfl
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sfl
op_assign
id|np-&gt;ipv6_fl_list
)paren
op_ne
l_int|NULL
)paren
(brace
id|np-&gt;ipv6_fl_list
op_assign
id|sfl-&gt;next
suffix:semicolon
id|fl_release
c_func
(paren
id|sfl-&gt;fl
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sfl
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Service routines */
multiline_comment|/*&n;   It is the only difficult place. flowlabel enforces equal headers&n;   before and including routing header, however user may supply options&n;   following rthdr.&n; */
DECL|function|fl6_merge_options
r_struct
id|ipv6_txoptions
op_star
id|fl6_merge_options
c_func
(paren
r_struct
id|ipv6_txoptions
op_star
id|opt_space
comma
r_struct
id|ip6_flowlabel
op_star
id|fl
comma
r_struct
id|ipv6_txoptions
op_star
id|fopt
)paren
(brace
r_struct
id|ipv6_txoptions
op_star
id|fl_opt
op_assign
id|fl-&gt;opt
suffix:semicolon
r_if
c_cond
(paren
id|fopt
op_eq
l_int|NULL
op_logical_or
id|fopt-&gt;opt_flen
op_eq
l_int|0
)paren
r_return
id|fl_opt
suffix:semicolon
r_if
c_cond
(paren
id|fl_opt
op_ne
l_int|NULL
)paren
(brace
id|opt_space-&gt;hopopt
op_assign
id|fl_opt-&gt;hopopt
suffix:semicolon
id|opt_space-&gt;dst0opt
op_assign
id|fl_opt-&gt;dst0opt
suffix:semicolon
id|opt_space-&gt;srcrt
op_assign
id|fl_opt-&gt;srcrt
suffix:semicolon
id|opt_space-&gt;opt_nflen
op_assign
id|fl_opt-&gt;opt_nflen
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|fopt-&gt;opt_nflen
op_eq
l_int|0
)paren
r_return
id|fopt
suffix:semicolon
id|opt_space-&gt;hopopt
op_assign
l_int|NULL
suffix:semicolon
id|opt_space-&gt;dst0opt
op_assign
l_int|NULL
suffix:semicolon
id|opt_space-&gt;srcrt
op_assign
l_int|NULL
suffix:semicolon
id|opt_space-&gt;opt_nflen
op_assign
l_int|0
suffix:semicolon
)brace
id|opt_space-&gt;dst1opt
op_assign
id|fopt-&gt;dst1opt
suffix:semicolon
id|opt_space-&gt;auth
op_assign
id|fopt-&gt;auth
suffix:semicolon
id|opt_space-&gt;opt_flen
op_assign
id|fopt-&gt;opt_flen
suffix:semicolon
r_return
id|opt_space
suffix:semicolon
)brace
DECL|function|check_linger
r_static
r_int
r_int
id|check_linger
c_func
(paren
r_int
r_int
id|ttl
)paren
(brace
r_if
c_cond
(paren
id|ttl
OL
id|FL_MIN_LINGER
)paren
r_return
id|FL_MIN_LINGER
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|ttl
OG
id|FL_MAX_LINGER
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ttl
op_star
id|HZ
suffix:semicolon
)brace
DECL|function|fl6_renew
r_static
r_int
id|fl6_renew
c_func
(paren
r_struct
id|ip6_flowlabel
op_star
id|fl
comma
r_int
r_int
id|linger
comma
r_int
r_int
id|expires
)paren
(brace
id|linger
op_assign
id|check_linger
c_func
(paren
id|linger
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|linger
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|expires
op_assign
id|check_linger
c_func
(paren
id|expires
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|expires
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|fl-&gt;lastuse
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|fl-&gt;linger
comma
id|linger
)paren
)paren
id|fl-&gt;linger
op_assign
id|linger
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|expires
comma
id|fl-&gt;linger
)paren
)paren
id|expires
op_assign
id|fl-&gt;linger
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|fl-&gt;expires
comma
id|fl-&gt;lastuse
op_plus
id|expires
)paren
)paren
id|fl-&gt;expires
op_assign
id|fl-&gt;lastuse
op_plus
id|expires
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|ip6_flowlabel
op_star
DECL|function|fl_create
id|fl_create
c_func
(paren
r_struct
id|in6_flowlabel_req
op_star
id|freq
comma
r_char
id|__user
op_star
id|optval
comma
r_int
id|optlen
comma
r_int
op_star
id|err_p
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
suffix:semicolon
r_int
id|olen
suffix:semicolon
r_int
id|addr_type
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|fl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fl
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
id|memset
c_func
(paren
id|fl
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fl
)paren
)paren
suffix:semicolon
id|olen
op_assign
id|optlen
op_minus
id|CMSG_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|freq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|olen
OG
l_int|0
)paren
(brace
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|flowi
id|flowi
suffix:semicolon
r_int
id|junk
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|fl-&gt;opt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fl-&gt;opt
)paren
op_plus
id|olen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;opt
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
id|memset
c_func
(paren
id|fl-&gt;opt
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fl-&gt;opt
)paren
)paren
suffix:semicolon
id|fl-&gt;opt-&gt;tot_len
op_assign
r_sizeof
(paren
op_star
id|fl-&gt;opt
)paren
op_plus
id|olen
suffix:semicolon
id|err
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
id|fl-&gt;opt
op_plus
l_int|1
comma
id|optval
op_plus
id|CMSG_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|freq
)paren
)paren
comma
id|olen
)paren
)paren
r_goto
id|done
suffix:semicolon
id|msg.msg_controllen
op_assign
id|olen
suffix:semicolon
id|msg.msg_control
op_assign
(paren
r_void
op_star
)paren
(paren
id|fl-&gt;opt
op_plus
l_int|1
)paren
suffix:semicolon
id|flowi.oif
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|datagram_send_ctl
c_func
(paren
op_amp
id|msg
comma
op_amp
id|flowi
comma
id|fl-&gt;opt
comma
op_amp
id|junk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;opt-&gt;opt_flen
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;opt-&gt;opt_nflen
op_eq
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|fl-&gt;opt
)paren
suffix:semicolon
id|fl-&gt;opt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|fl-&gt;expires
op_assign
id|jiffies
suffix:semicolon
id|err
op_assign
id|fl6_renew
c_func
(paren
id|fl
comma
id|freq-&gt;flr_linger
comma
id|freq-&gt;flr_expires
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
suffix:semicolon
id|fl-&gt;share
op_assign
id|freq-&gt;flr_share
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|freq-&gt;flr_dst
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MAPPED
)paren
op_logical_or
id|addr_type
op_eq
id|IPV6_ADDR_ANY
)paren
r_goto
id|done
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|fl-&gt;dst
comma
op_amp
id|freq-&gt;flr_dst
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|fl-&gt;users
comma
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|fl-&gt;share
)paren
(brace
r_case
id|IPV6_FL_S_EXCL
suffix:colon
r_case
id|IPV6_FL_S_ANY
suffix:colon
r_break
suffix:semicolon
r_case
id|IPV6_FL_S_PROCESS
suffix:colon
id|fl-&gt;owner
op_assign
id|current-&gt;pid
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_FL_S_USER
suffix:colon
id|fl-&gt;owner
op_assign
id|current-&gt;euid
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
id|done
suffix:semicolon
)brace
r_return
id|fl
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|fl
)paren
id|fl_free
c_func
(paren
id|fl
)paren
suffix:semicolon
op_star
id|err_p
op_assign
id|err
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|mem_check
r_static
r_int
id|mem_check
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|ipv6_fl_socklist
op_star
id|sfl
suffix:semicolon
r_int
id|room
op_assign
id|FL_MAX_SIZE
op_minus
id|atomic_read
c_func
(paren
op_amp
id|fl_size
)paren
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|room
OG
id|FL_MAX_SIZE
op_minus
id|FL_MAX_PER_SOCK
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|sfl
op_assign
id|np-&gt;ipv6_fl_list
suffix:semicolon
id|sfl
suffix:semicolon
id|sfl
op_assign
id|sfl-&gt;next
)paren
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|room
op_le
l_int|0
op_logical_or
(paren
(paren
id|count
op_ge
id|FL_MAX_PER_SOCK
op_logical_or
(paren
id|count
OG
l_int|0
op_logical_and
id|room
OL
id|FL_MAX_SIZE
op_div
l_int|2
)paren
op_logical_or
id|room
OL
id|FL_MAX_SIZE
op_div
l_int|4
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipv6_hdr_cmp
r_static
r_int
id|ipv6_hdr_cmp
c_func
(paren
r_struct
id|ipv6_opt_hdr
op_star
id|h1
comma
r_struct
id|ipv6_opt_hdr
op_star
id|h2
)paren
(brace
r_if
c_cond
(paren
id|h1
op_eq
id|h2
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|h1
op_eq
l_int|NULL
op_logical_or
id|h2
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|h1-&gt;hdrlen
op_ne
id|h2-&gt;hdrlen
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|memcmp
c_func
(paren
id|h1
op_plus
l_int|1
comma
id|h2
op_plus
l_int|1
comma
(paren
(paren
id|h1-&gt;hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
op_minus
r_sizeof
(paren
op_star
id|h1
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_opt_cmp
r_static
r_int
id|ipv6_opt_cmp
c_func
(paren
r_struct
id|ipv6_txoptions
op_star
id|o1
comma
r_struct
id|ipv6_txoptions
op_star
id|o2
)paren
(brace
r_if
c_cond
(paren
id|o1
op_eq
id|o2
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|o1
op_eq
l_int|NULL
op_logical_or
id|o2
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|o1-&gt;opt_nflen
op_ne
id|o2-&gt;opt_nflen
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_hdr_cmp
c_func
(paren
id|o1-&gt;hopopt
comma
id|o2-&gt;hopopt
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_hdr_cmp
c_func
(paren
id|o1-&gt;dst0opt
comma
id|o2-&gt;dst0opt
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_hdr_cmp
c_func
(paren
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|o1-&gt;srcrt
comma
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|o2-&gt;srcrt
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipv6_flowlabel_opt
r_int
id|ipv6_flowlabel_opt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_char
id|__user
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|in6_flowlabel_req
id|freq
suffix:semicolon
r_struct
id|ipv6_fl_socklist
op_star
id|sfl1
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ipv6_fl_socklist
op_star
id|sfl
comma
op_star
op_star
id|sflp
suffix:semicolon
r_struct
id|ip6_flowlabel
op_star
id|fl
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OL
r_sizeof
(paren
id|freq
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|freq
comma
id|optval
comma
r_sizeof
(paren
id|freq
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|freq.flr_action
)paren
(brace
r_case
id|IPV6_FL_A_PUT
suffix:colon
id|write_lock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sflp
op_assign
op_amp
id|np-&gt;ipv6_fl_list
suffix:semicolon
(paren
id|sfl
op_assign
op_star
id|sflp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|sflp
op_assign
op_amp
id|sfl-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sfl-&gt;fl-&gt;label
op_eq
id|freq.flr_label
)paren
(brace
r_if
c_cond
(paren
id|freq.flr_label
op_eq
(paren
id|np-&gt;flow_label
op_amp
id|IPV6_FLOWLABEL_MASK
)paren
)paren
id|np-&gt;flow_label
op_and_assign
op_complement
id|IPV6_FLOWLABEL_MASK
suffix:semicolon
op_star
id|sflp
op_assign
id|sfl-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
id|fl_release
c_func
(paren
id|sfl-&gt;fl
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sfl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
r_case
id|IPV6_FL_A_RENEW
suffix:colon
id|read_lock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sfl
op_assign
id|np-&gt;ipv6_fl_list
suffix:semicolon
id|sfl
suffix:semicolon
id|sfl
op_assign
id|sfl-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sfl-&gt;fl-&gt;label
op_eq
id|freq.flr_label
)paren
(brace
id|err
op_assign
id|fl6_renew
c_func
(paren
id|sfl-&gt;fl
comma
id|freq.flr_linger
comma
id|freq.flr_expires
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq.flr_share
op_eq
id|IPV6_FL_S_NONE
op_logical_and
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
id|fl
op_assign
id|fl_lookup
c_func
(paren
id|freq.flr_label
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl
)paren
(brace
id|err
op_assign
id|fl6_renew
c_func
(paren
id|fl
comma
id|freq.flr_linger
comma
id|freq.flr_expires
)paren
suffix:semicolon
id|fl_release
c_func
(paren
id|fl
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ESRCH
suffix:semicolon
r_case
id|IPV6_FL_A_GET
suffix:colon
r_if
c_cond
(paren
id|freq.flr_label
op_amp
op_complement
id|IPV6_FLOWLABEL_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|fl
op_assign
id|fl_create
c_func
(paren
op_amp
id|freq
comma
id|optval
comma
id|optlen
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl
op_eq
l_int|NULL
)paren
r_return
id|err
suffix:semicolon
id|sfl1
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sfl1
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq.flr_label
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl1
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sfl
op_assign
id|np-&gt;ipv6_fl_list
suffix:semicolon
id|sfl
suffix:semicolon
id|sfl
op_assign
id|sfl-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sfl-&gt;fl-&gt;label
op_eq
id|freq.flr_label
)paren
(brace
r_if
c_cond
(paren
id|freq.flr_flags
op_amp
id|IPV6_FL_F_EXCL
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|fl1
op_assign
id|sfl-&gt;fl
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|fl-&gt;users
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl1
op_eq
l_int|NULL
)paren
id|fl1
op_assign
id|fl_lookup
c_func
(paren
id|freq.flr_label
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl1
)paren
(brace
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|freq.flr_flags
op_amp
id|IPV6_FL_F_EXCL
)paren
r_goto
id|release
suffix:semicolon
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|fl1-&gt;share
op_eq
id|IPV6_FL_S_EXCL
op_logical_or
id|fl1-&gt;share
op_ne
id|fl-&gt;share
op_logical_or
id|fl1-&gt;owner
op_ne
id|fl-&gt;owner
)paren
r_goto
id|release
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|fl1-&gt;dst
comma
op_amp
id|fl-&gt;dst
)paren
op_logical_or
id|ipv6_opt_cmp
c_func
(paren
id|fl1-&gt;opt
comma
id|fl-&gt;opt
)paren
)paren
r_goto
id|release
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|sfl1
op_eq
l_int|NULL
)paren
r_goto
id|release
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;linger
OG
id|fl1-&gt;linger
)paren
id|fl1-&gt;linger
op_assign
id|fl-&gt;linger
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|fl-&gt;expires
op_minus
id|fl1-&gt;expires
)paren
OG
l_int|0
)paren
id|fl1-&gt;expires
op_assign
id|fl-&gt;expires
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
id|sfl1-&gt;fl
op_assign
id|fl1
suffix:semicolon
id|sfl1-&gt;next
op_assign
id|np-&gt;ipv6_fl_list
suffix:semicolon
id|np-&gt;ipv6_fl_list
op_assign
id|sfl1
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ip6_sk_fl_lock
)paren
suffix:semicolon
id|fl_free
c_func
(paren
id|fl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|release
suffix:colon
id|fl_release
c_func
(paren
id|fl1
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|freq.flr_flags
op_amp
id|IPV6_FL_F_CREATE
)paren
)paren
r_goto
id|done
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|sfl1
op_eq
l_int|NULL
op_logical_or
(paren
id|err
op_assign
id|mem_check
c_func
(paren
id|sk
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|done
suffix:semicolon
id|err
op_assign
id|fl_intern
c_func
(paren
id|fl
comma
id|freq.flr_label
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* Do not check for fault */
r_if
c_cond
(paren
op_logical_neg
id|freq.flr_label
)paren
id|copy_to_user
c_func
(paren
id|optval
op_plus
(paren
(paren
id|u8
op_star
)paren
op_amp
id|freq.flr_label
op_minus
(paren
id|u8
op_star
)paren
op_amp
id|freq
)paren
comma
op_amp
id|fl-&gt;label
comma
r_sizeof
(paren
id|fl-&gt;label
)paren
)paren
suffix:semicolon
id|sfl1-&gt;fl
op_assign
id|fl
suffix:semicolon
id|sfl1-&gt;next
op_assign
id|np-&gt;ipv6_fl_list
suffix:semicolon
id|np-&gt;ipv6_fl_list
op_assign
id|sfl1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|done
suffix:colon
r_if
c_cond
(paren
id|fl
)paren
id|fl_free
c_func
(paren
id|fl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sfl1
)paren
id|kfree
c_func
(paren
id|sfl1
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|struct|ip6fl_iter_state
r_struct
id|ip6fl_iter_state
(brace
DECL|member|bucket
r_int
id|bucket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ip6fl_seq_private
mdefine_line|#define ip6fl_seq_private(seq)&t;((struct ip6fl_iter_state *)(seq)-&gt;private)
DECL|function|ip6fl_get_first
r_static
r_struct
id|ip6_flowlabel
op_star
id|ip6fl_get_first
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ip6fl_iter_state
op_star
id|state
op_assign
id|ip6fl_seq_private
c_func
(paren
id|seq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|state-&gt;bucket
op_assign
l_int|0
suffix:semicolon
id|state-&gt;bucket
op_le
id|FL_HASH_MASK
suffix:semicolon
op_increment
id|state-&gt;bucket
)paren
(brace
r_if
c_cond
(paren
id|fl_ht
(braket
id|state-&gt;bucket
)braket
)paren
(brace
id|fl
op_assign
id|fl_ht
(braket
id|state-&gt;bucket
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|fl
suffix:semicolon
)brace
DECL|function|ip6fl_get_next
r_static
r_struct
id|ip6_flowlabel
op_star
id|ip6fl_get_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|ip6_flowlabel
op_star
id|fl
)paren
(brace
r_struct
id|ip6fl_iter_state
op_star
id|state
op_assign
id|ip6fl_seq_private
c_func
(paren
id|seq
)paren
suffix:semicolon
id|fl
op_assign
id|fl-&gt;next
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|fl
)paren
(brace
r_if
c_cond
(paren
op_increment
id|state-&gt;bucket
op_le
id|FL_HASH_MASK
)paren
id|fl
op_assign
id|fl_ht
(braket
id|state-&gt;bucket
)braket
suffix:semicolon
)brace
r_return
id|fl
suffix:semicolon
)brace
DECL|function|ip6fl_get_idx
r_static
r_struct
id|ip6_flowlabel
op_star
id|ip6fl_get_idx
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|ip6_flowlabel
op_star
id|fl
op_assign
id|ip6fl_get_first
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl
)paren
r_while
c_loop
(paren
id|pos
op_logical_and
(paren
id|fl
op_assign
id|ip6fl_get_next
c_func
(paren
id|seq
comma
id|fl
)paren
)paren
op_ne
l_int|NULL
)paren
op_decrement
id|pos
suffix:semicolon
r_return
id|pos
ques
c_cond
l_int|NULL
suffix:colon
id|fl
suffix:semicolon
)brace
DECL|function|ip6fl_seq_start
r_static
r_void
op_star
id|ip6fl_seq_start
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
id|read_lock_bh
c_func
(paren
op_amp
id|ip6_fl_lock
)paren
suffix:semicolon
r_return
op_star
id|pos
ques
c_cond
id|ip6fl_get_idx
c_func
(paren
id|seq
comma
op_star
id|pos
op_minus
l_int|1
)paren
suffix:colon
id|SEQ_START_TOKEN
suffix:semicolon
)brace
DECL|function|ip6fl_seq_next
r_static
r_void
op_star
id|ip6fl_seq_next
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
id|ip6_flowlabel
op_star
id|fl
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
id|fl
op_assign
id|ip6fl_get_first
c_func
(paren
id|seq
)paren
suffix:semicolon
r_else
id|fl
op_assign
id|ip6fl_get_next
c_func
(paren
id|seq
comma
id|v
)paren
suffix:semicolon
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|fl
suffix:semicolon
)brace
DECL|function|ip6fl_seq_stop
r_static
r_void
id|ip6fl_seq_stop
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
id|ip6_fl_lock
)paren
suffix:semicolon
)brace
DECL|function|ip6fl_fl_seq_show
r_static
r_void
id|ip6fl_fl_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|ip6_flowlabel
op_star
id|fl
)paren
(brace
r_while
c_loop
(paren
id|fl
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%05X %-1d %-6d %-6d %-6ld %-8ld &quot;
l_string|&quot;%02x%02x%02x%02x%02x%02x%02x%02x &quot;
l_string|&quot;%-4d&bslash;n&quot;
comma
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|fl-&gt;label
)paren
comma
id|fl-&gt;share
comma
(paren
r_int
)paren
id|fl-&gt;owner
comma
id|atomic_read
c_func
(paren
op_amp
id|fl-&gt;users
)paren
comma
id|fl-&gt;linger
op_div
id|HZ
comma
(paren
r_int
)paren
(paren
id|fl-&gt;expires
op_minus
id|jiffies
)paren
op_div
id|HZ
comma
id|NIP6
c_func
(paren
id|fl-&gt;dst
)paren
comma
id|fl-&gt;opt
ques
c_cond
id|fl-&gt;opt-&gt;opt_nflen
suffix:colon
l_int|0
)paren
suffix:semicolon
id|fl
op_assign
id|fl-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|ip6fl_seq_show
r_static
r_int
id|ip6fl_seq_show
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
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;Label S Owner  Users  Linger Expires  &quot;
l_string|&quot;Dst                              Opt&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|ip6fl_fl_seq_show
c_func
(paren
id|seq
comma
id|v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip6fl_seq_ops
r_static
r_struct
id|seq_operations
id|ip6fl_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|ip6fl_seq_start
comma
dot
id|next
op_assign
id|ip6fl_seq_next
comma
dot
id|stop
op_assign
id|ip6fl_seq_stop
comma
dot
id|show
op_assign
id|ip6fl_seq_show
comma
)brace
suffix:semicolon
DECL|function|ip6fl_seq_open
r_static
r_int
id|ip6fl_seq_open
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
id|seq
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_struct
id|ip6fl_iter_state
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|ip6fl_seq_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out_kfree
suffix:semicolon
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
id|s
suffix:semicolon
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|s
)paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|ip6fl_seq_fops
r_static
r_struct
id|file_operations
id|ip6fl_seq_fops
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
id|ip6fl_seq_open
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
id|seq_release_private
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|ip6_flowlabel_init
r_void
id|ip6_flowlabel_init
c_func
(paren
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_fops_create
c_func
(paren
l_string|&quot;ip6_flowlabel&quot;
comma
id|S_IRUGO
comma
op_amp
id|ip6fl_seq_fops
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ip6_flowlabel_cleanup
r_void
id|ip6_flowlabel_cleanup
c_func
(paren
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ip6_fl_gc_timer
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_remove
c_func
(paren
l_string|&quot;ip6_flowlabel&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
