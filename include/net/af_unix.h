macro_line|#ifndef __LINUX_NET_AFUNIX_H
DECL|macro|__LINUX_NET_AFUNIX_H
mdefine_line|#define __LINUX_NET_AFUNIX_H
r_extern
r_void
id|unix_inflight
c_func
(paren
r_struct
id|file
op_star
id|fp
)paren
suffix:semicolon
r_extern
r_void
id|unix_notinflight
c_func
(paren
r_struct
id|file
op_star
id|fp
)paren
suffix:semicolon
r_extern
r_void
id|unix_gc
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|UNIX_HASH_SIZE
mdefine_line|#define UNIX_HASH_SIZE&t;256
r_extern
r_struct
id|hlist_head
id|unix_socket_table
(braket
id|UNIX_HASH_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
r_extern
id|rwlock_t
id|unix_table_lock
suffix:semicolon
r_extern
id|atomic_t
id|unix_tot_inflight
suffix:semicolon
DECL|function|first_unix_socket
r_static
r_inline
r_struct
id|sock
op_star
id|first_unix_socket
c_func
(paren
r_int
op_star
id|i
)paren
(brace
r_for
c_loop
(paren
op_star
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|i
op_le
id|UNIX_HASH_SIZE
suffix:semicolon
(paren
op_star
id|i
)paren
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hlist_empty
c_func
(paren
op_amp
id|unix_socket_table
(braket
op_star
id|i
)braket
)paren
)paren
r_return
id|__sk_head
c_func
(paren
op_amp
id|unix_socket_table
(braket
op_star
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|next_unix_socket
r_static
r_inline
r_struct
id|sock
op_star
id|next_unix_socket
c_func
(paren
r_int
op_star
id|i
comma
r_struct
id|sock
op_star
id|s
)paren
(brace
r_struct
id|sock
op_star
id|next
op_assign
id|sk_next
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* More in this chain? */
r_if
c_cond
(paren
id|next
)paren
r_return
id|next
suffix:semicolon
multiline_comment|/* Look for next non-empty chain. */
r_for
c_loop
(paren
(paren
op_star
id|i
)paren
op_increment
suffix:semicolon
op_star
id|i
op_le
id|UNIX_HASH_SIZE
suffix:semicolon
(paren
op_star
id|i
)paren
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hlist_empty
c_func
(paren
op_amp
id|unix_socket_table
(braket
op_star
id|i
)braket
)paren
)paren
r_return
id|__sk_head
c_func
(paren
op_amp
id|unix_socket_table
(braket
op_star
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|macro|forall_unix_sockets
mdefine_line|#define forall_unix_sockets(i, s) &bslash;&n;&t;for (s = first_unix_socket(&amp;(i)); s; s = next_unix_socket(&amp;(i),(s)))
DECL|struct|unix_address
r_struct
id|unix_address
(brace
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|hash
r_int
id|hash
suffix:semicolon
DECL|member|name
r_struct
id|sockaddr_un
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|unix_skb_parms
r_struct
id|unix_skb_parms
(brace
DECL|member|creds
r_struct
id|ucred
id|creds
suffix:semicolon
multiline_comment|/* Skb credentials&t;*/
DECL|member|fp
r_struct
id|scm_fp_list
op_star
id|fp
suffix:semicolon
multiline_comment|/* Passed files&t;&t;*/
)brace
suffix:semicolon
DECL|macro|UNIXCB
mdefine_line|#define UNIXCB(skb) &t;(*(struct unix_skb_parms*)&amp;((skb)-&gt;cb))
DECL|macro|UNIXCREDS
mdefine_line|#define UNIXCREDS(skb)&t;(&amp;UNIXCB((skb)).creds)
DECL|macro|unix_state_rlock
mdefine_line|#define unix_state_rlock(s)&t;read_lock(&amp;unix_sk(s)-&gt;lock)
DECL|macro|unix_state_runlock
mdefine_line|#define unix_state_runlock(s)&t;read_unlock(&amp;unix_sk(s)-&gt;lock)
DECL|macro|unix_state_wlock
mdefine_line|#define unix_state_wlock(s)&t;write_lock(&amp;unix_sk(s)-&gt;lock)
DECL|macro|unix_state_wunlock
mdefine_line|#define unix_state_wunlock(s)&t;write_unlock(&amp;unix_sk(s)-&gt;lock)
macro_line|#ifdef __KERNEL__
multiline_comment|/* The AF_UNIX socket */
DECL|struct|unix_sock
r_struct
id|unix_sock
(brace
multiline_comment|/* WARNING: sk has to be the first member */
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|addr
r_struct
id|unix_address
op_star
id|addr
suffix:semicolon
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
DECL|member|mnt
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
DECL|member|readsem
r_struct
id|semaphore
id|readsem
suffix:semicolon
DECL|member|other
r_struct
id|sock
op_star
id|other
suffix:semicolon
DECL|member|gc_tree
r_struct
id|sock
op_star
id|gc_tree
suffix:semicolon
DECL|member|inflight
id|atomic_t
id|inflight
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|peer_wait
id|wait_queue_head_t
id|peer_wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|unix_sk
mdefine_line|#define unix_sk(__sk) ((struct unix_sock *)__sk)
macro_line|#endif
macro_line|#endif
eof
