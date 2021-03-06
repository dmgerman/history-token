multiline_comment|/*&n; *&t;&t;INETPEER - A storage for permanent information about peers&n; *&n; *  Version:&t;$Id: inetpeer.h,v 1.2 2002/01/12 07:54:56 davem Exp $&n; *&n; *  Authors:&t;Andrey V. Savochkin &lt;saw@msu.ru&gt;&n; */
macro_line|#ifndef _NET_INETPEER_H
DECL|macro|_NET_INETPEER_H
mdefine_line|#define _NET_INETPEER_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|inet_peer
r_struct
id|inet_peer
(brace
DECL|member|avl_left
DECL|member|avl_right
r_struct
id|inet_peer
op_star
id|avl_left
comma
op_star
id|avl_right
suffix:semicolon
DECL|member|unused_next
DECL|member|unused_prevp
r_struct
id|inet_peer
op_star
id|unused_next
comma
op_star
op_star
id|unused_prevp
suffix:semicolon
DECL|member|dtime
r_int
r_int
id|dtime
suffix:semicolon
multiline_comment|/* the time of last use of not&n;&t;&t;&t;&t;&t;&t; * referenced entries */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|v4daddr
id|__u32
id|v4daddr
suffix:semicolon
multiline_comment|/* peer&squot;s address */
DECL|member|avl_height
id|__u16
id|avl_height
suffix:semicolon
DECL|member|ip_id_count
id|__u16
id|ip_id_count
suffix:semicolon
multiline_comment|/* IP ID for the next packet */
DECL|member|tcp_ts
id|__u32
id|tcp_ts
suffix:semicolon
DECL|member|tcp_ts_stamp
r_int
r_int
id|tcp_ts_stamp
suffix:semicolon
)brace
suffix:semicolon
r_void
id|inet_initpeers
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* can be called with or without local BH being disabled */
r_struct
id|inet_peer
op_star
id|inet_getpeer
c_func
(paren
id|__u32
id|daddr
comma
r_int
id|create
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|inet_peer_unused_lock
suffix:semicolon
r_extern
r_struct
id|inet_peer
op_star
op_star
id|inet_peer_unused_tailp
suffix:semicolon
multiline_comment|/* can be called from BH context or outside */
DECL|function|inet_putpeer
r_static
r_inline
r_void
id|inet_putpeer
c_func
(paren
r_struct
id|inet_peer
op_star
id|p
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|p-&gt;refcnt
)paren
)paren
(brace
id|p-&gt;unused_prevp
op_assign
id|inet_peer_unused_tailp
suffix:semicolon
id|p-&gt;unused_next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|inet_peer_unused_tailp
op_assign
id|p
suffix:semicolon
id|inet_peer_unused_tailp
op_assign
op_amp
id|p-&gt;unused_next
suffix:semicolon
id|p-&gt;dtime
op_assign
id|jiffies
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_peer_unused_lock
)paren
suffix:semicolon
)brace
r_extern
id|spinlock_t
id|inet_peer_idlock
suffix:semicolon
multiline_comment|/* can be called with or without local BH being disabled */
DECL|function|inet_getid
r_static
r_inline
id|__u16
id|inet_getid
c_func
(paren
r_struct
id|inet_peer
op_star
id|p
comma
r_int
id|more
)paren
(brace
id|__u16
id|id
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|inet_peer_idlock
)paren
suffix:semicolon
id|id
op_assign
id|p-&gt;ip_id_count
suffix:semicolon
id|p-&gt;ip_id_count
op_add_assign
l_int|1
op_plus
id|more
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_peer_idlock
)paren
suffix:semicolon
r_return
id|id
suffix:semicolon
)brace
macro_line|#endif /* _NET_INETPEER_H */
eof
