multiline_comment|/* peer.c: Rx RPC peer management&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;rxrpc/message.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &quot;internal.h&quot;
DECL|variable|rxrpc_peer_count
id|__RXACCT_DECL
c_func
(paren
id|atomic_t
id|rxrpc_peer_count
)paren
suffix:semicolon
DECL|variable|rxrpc_peers
id|LIST_HEAD
c_func
(paren
id|rxrpc_peers
)paren
suffix:semicolon
DECL|variable|rxrpc_peers_sem
id|DECLARE_RWSEM
c_func
(paren
id|rxrpc_peers_sem
)paren
suffix:semicolon
DECL|function|__rxrpc_peer_timeout
r_static
r_void
id|__rxrpc_peer_timeout
c_func
(paren
id|rxrpc_timer_t
op_star
id|timer
)paren
(brace
r_struct
id|rxrpc_peer
op_star
id|peer
op_assign
id|list_entry
c_func
(paren
id|timer
comma
r_struct
id|rxrpc_peer
comma
id|timeout
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;Rx PEER TIMEOUT [%p{u=%d}]&quot;
comma
id|peer
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
)paren
suffix:semicolon
id|rxrpc_peer_do_timeout
c_func
(paren
id|peer
)paren
suffix:semicolon
)brace
DECL|variable|rxrpc_peer_timer_ops
r_static
r_const
r_struct
id|rxrpc_timer_ops
id|rxrpc_peer_timer_ops
op_assign
(brace
dot
id|timed_out
op_assign
id|__rxrpc_peer_timeout
comma
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * create a peer record&n; */
DECL|function|__rxrpc_create_peer
r_static
r_int
id|__rxrpc_create_peer
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
id|u32
id|addr
comma
r_struct
id|rxrpc_peer
op_star
op_star
id|_peer
)paren
(brace
r_struct
id|rxrpc_peer
op_star
id|peer
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p,%08x&quot;
comma
id|trans
comma
id|ntohl
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
multiline_comment|/* allocate and initialise a peer record */
id|peer
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|rxrpc_peer
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|peer
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ENOMEM&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|peer
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rxrpc_peer
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|peer-&gt;usage
comma
l_int|1
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;link
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;proc_link
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;conn_active
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;conn_graveyard
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|peer-&gt;conn_gylock
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|peer-&gt;conn_gy_waitq
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|peer-&gt;conn_lock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|peer-&gt;conn_count
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|peer-&gt;lock
)paren
suffix:semicolon
id|rxrpc_timer_init
c_func
(paren
op_amp
id|peer-&gt;timeout
comma
op_amp
id|rxrpc_peer_timer_ops
)paren
suffix:semicolon
id|peer-&gt;addr.s_addr
op_assign
id|addr
suffix:semicolon
id|peer-&gt;trans
op_assign
id|trans
suffix:semicolon
id|peer-&gt;ops
op_assign
id|trans-&gt;peer_ops
suffix:semicolon
id|__RXACCT
c_func
(paren
id|atomic_inc
c_func
(paren
op_amp
id|rxrpc_peer_count
)paren
)paren
suffix:semicolon
op_star
id|_peer
op_assign
id|peer
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 (%p)&quot;
comma
id|peer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end __rxrpc_create_peer() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * find a peer record on the specified transport&n; * - returns (if successful) with peer record usage incremented&n; * - resurrects it from the graveyard if found there&n; */
DECL|function|rxrpc_peer_lookup
r_int
id|rxrpc_peer_lookup
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
comma
id|u32
id|addr
comma
r_struct
id|rxrpc_peer
op_star
op_star
id|_peer
)paren
(brace
r_struct
id|rxrpc_peer
op_star
id|peer
comma
op_star
id|candidate
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{%hu},%08x&quot;
comma
id|trans
comma
id|trans-&gt;port
comma
id|ntohl
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
multiline_comment|/* [common case] search the transport&squot;s active list first */
id|read_lock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|trans-&gt;peer_active
)paren
(brace
id|peer
op_assign
id|list_entry
c_func
(paren
id|_p
comma
r_struct
id|rxrpc_peer
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer-&gt;addr.s_addr
op_eq
id|addr
)paren
r_goto
id|found_active
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
multiline_comment|/* [uncommon case] not active - create a candidate for a new record */
id|ret
op_assign
id|__rxrpc_create_peer
c_func
(paren
id|trans
comma
id|addr
comma
op_amp
id|candidate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* search the active list again, just in case it appeared whilst we were busy */
id|write_lock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|trans-&gt;peer_active
)paren
(brace
id|peer
op_assign
id|list_entry
c_func
(paren
id|_p
comma
r_struct
id|rxrpc_peer
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer-&gt;addr.s_addr
op_eq
id|addr
)paren
r_goto
id|found_active_second_chance
suffix:semicolon
)brace
multiline_comment|/* search the transport&squot;s graveyard list */
id|spin_lock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|trans-&gt;peer_graveyard
)paren
(brace
id|peer
op_assign
id|list_entry
c_func
(paren
id|_p
comma
r_struct
id|rxrpc_peer
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer-&gt;addr.s_addr
op_eq
id|addr
)paren
r_goto
id|found_in_graveyard
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
multiline_comment|/* we can now add the new candidate to the list&n;&t; * - tell the application layer that this peer has been added&n;&t; */
id|rxrpc_get_transport
c_func
(paren
id|trans
)paren
suffix:semicolon
id|peer
op_assign
id|candidate
suffix:semicolon
id|candidate
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|peer-&gt;ops
op_logical_and
id|peer-&gt;ops-&gt;adding
)paren
(brace
id|ret
op_assign
id|peer-&gt;ops
op_member_access_from_pointer
id|adding
c_func
(paren
id|peer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_peer_count
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|peer
)paren
suffix:semicolon
id|rxrpc_put_transport
c_func
(paren
id|trans
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
id|atomic_inc
c_func
(paren
op_amp
id|trans-&gt;peer_count
)paren
suffix:semicolon
id|make_active
suffix:colon
id|list_add_tail
c_func
(paren
op_amp
id|peer-&gt;link
comma
op_amp
id|trans-&gt;peer_active
)paren
suffix:semicolon
id|success_uwfree
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|candidate
)paren
(brace
id|__RXACCT
c_func
(paren
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_peer_count
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|candidate
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|peer-&gt;proc_link
)paren
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|rxrpc_peers_sem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|peer-&gt;proc_link
comma
op_amp
id|rxrpc_peers
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|rxrpc_peers_sem
)paren
suffix:semicolon
)brace
id|success
suffix:colon
op_star
id|_peer
op_assign
id|peer
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 (%p{u=%d cc=%d})&quot;
comma
id|peer
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;conn_count
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* handle the peer being found in the active list straight off */
id|found_active
suffix:colon
id|rxrpc_get_peer
c_func
(paren
id|peer
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
r_goto
id|success
suffix:semicolon
multiline_comment|/* handle resurrecting a peer from the graveyard */
id|found_in_graveyard
suffix:colon
id|rxrpc_get_peer
c_func
(paren
id|peer
)paren
suffix:semicolon
id|rxrpc_get_transport
c_func
(paren
id|peer-&gt;trans
)paren
suffix:semicolon
id|rxrpc_krxtimod_del_timer
c_func
(paren
op_amp
id|peer-&gt;timeout
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|peer-&gt;link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
r_goto
id|make_active
suffix:semicolon
multiline_comment|/* handle finding the peer on the second time through the active list */
id|found_active_second_chance
suffix:colon
id|rxrpc_get_peer
c_func
(paren
id|peer
)paren
suffix:semicolon
r_goto
id|success_uwfree
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_peer_lookup() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * finish with a peer record&n; * - it gets sent to the graveyard from where it can be resurrected or timed out&n; */
DECL|function|rxrpc_put_peer
r_void
id|rxrpc_put_peer
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
(brace
r_struct
id|rxrpc_transport
op_star
id|trans
op_assign
id|peer-&gt;trans
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{cc=%d a=%08x}&quot;
comma
id|peer
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;conn_count
)paren
comma
id|ntohl
c_func
(paren
id|peer-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
op_le
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|atomic_dec_and_test
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* move to graveyard queue */
id|list_del
c_func
(paren
op_amp
id|peer-&gt;link
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|peer-&gt;link
comma
op_amp
id|trans-&gt;peer_graveyard
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|peer-&gt;conn_active
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* discard in 600 secs */
id|rxrpc_krxtimod_add_timer
c_func
(paren
op_amp
id|peer-&gt;timeout
comma
l_int|100
op_star
id|HZ
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
id|rxrpc_put_transport
c_func
(paren
id|trans
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; [killed]&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_put_peer() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle a peer timing out in the graveyard&n; * - called from krxtimod&n; */
DECL|function|rxrpc_peer_do_timeout
r_void
id|rxrpc_peer_do_timeout
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
)paren
(brace
r_struct
id|rxrpc_transport
op_star
id|trans
op_assign
id|peer-&gt;trans
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{u=%d cc=%d a=%08x}&quot;
comma
id|peer
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;conn_count
)paren
comma
id|ntohl
c_func
(paren
id|peer-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
OL
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* remove from graveyard if still dead */
id|spin_lock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|peer-&gt;usage
)paren
op_eq
l_int|0
)paren
id|list_del_init
c_func
(paren
op_amp
id|peer-&gt;link
)paren
suffix:semicolon
r_else
id|peer
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|peer
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* resurrected */
)brace
multiline_comment|/* clear all connections on this peer */
id|rxrpc_conn_clearall
c_func
(paren
id|peer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|peer-&gt;conn_active
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|peer-&gt;conn_graveyard
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* inform the application layer */
r_if
c_cond
(paren
id|peer-&gt;ops
op_logical_and
id|peer-&gt;ops-&gt;discarding
)paren
id|peer-&gt;ops
op_member_access_from_pointer
id|discarding
c_func
(paren
id|peer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|peer-&gt;proc_link
)paren
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|rxrpc_peers_sem
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|peer-&gt;proc_link
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|rxrpc_peers_sem
)paren
suffix:semicolon
)brace
id|__RXACCT
c_func
(paren
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_peer_count
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|peer
)paren
suffix:semicolon
multiline_comment|/* if the graveyard is now empty, wake up anyone waiting for that */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|trans-&gt;peer_count
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|trans-&gt;peer_gy_waitq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; [destroyed]&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_peer_do_timeout() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clear all peer records from a transport endpoint&n; */
DECL|function|rxrpc_peer_clearall
r_void
id|rxrpc_peer_clearall
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|myself
comma
id|current
)paren
suffix:semicolon
r_struct
id|rxrpc_peer
op_star
id|peer
suffix:semicolon
r_int
id|err
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p&quot;
comma
id|trans
)paren
suffix:semicolon
multiline_comment|/* there shouldn&squot;t be any active peers remaining */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|trans-&gt;peer_active
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* manually timeout all peers in the graveyard */
id|spin_lock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|trans-&gt;peer_graveyard
)paren
)paren
(brace
id|peer
op_assign
id|list_entry
c_func
(paren
id|trans-&gt;peer_graveyard.next
comma
r_struct
id|rxrpc_peer
comma
id|link
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;Clearing peer %p&bslash;n&quot;
comma
id|peer
)paren
suffix:semicolon
id|err
op_assign
id|rxrpc_krxtimod_del_timer
c_func
(paren
op_amp
id|peer-&gt;timeout
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
id|rxrpc_peer_do_timeout
c_func
(paren
id|peer
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;peer_gylock
)paren
suffix:semicolon
multiline_comment|/* wait for the the peer graveyard to be completely cleared */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|trans-&gt;peer_gy_waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|trans-&gt;peer_count
)paren
op_ne
l_int|0
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|trans-&gt;peer_gy_waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_peer_clearall() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * calculate and cache the Round-Trip-Time for a message and its response&n; */
DECL|function|rxrpc_peer_calculate_rtt
r_void
id|rxrpc_peer_calculate_rtt
c_func
(paren
r_struct
id|rxrpc_peer
op_star
id|peer
comma
r_struct
id|rxrpc_message
op_star
id|msg
comma
r_struct
id|rxrpc_message
op_star
id|resp
)paren
(brace
r_int
r_int
r_int
id|rtt
suffix:semicolon
r_int
id|loop
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p,%p,%p&quot;
comma
id|peer
comma
id|msg
comma
id|resp
)paren
suffix:semicolon
multiline_comment|/* calculate the latest RTT */
id|rtt
op_assign
id|resp-&gt;stamp.tv_sec
op_minus
id|msg-&gt;stamp.tv_sec
suffix:semicolon
id|rtt
op_mul_assign
l_int|1000000UL
suffix:semicolon
id|rtt
op_add_assign
id|resp-&gt;stamp.tv_usec
op_minus
id|msg-&gt;stamp.tv_usec
suffix:semicolon
multiline_comment|/* add to cache */
id|peer-&gt;rtt_cache
(braket
id|peer-&gt;rtt_point
)braket
op_assign
id|rtt
suffix:semicolon
id|peer-&gt;rtt_point
op_increment
suffix:semicolon
id|peer-&gt;rtt_point
op_mod_assign
id|RXRPC_RTT_CACHE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|peer-&gt;rtt_usage
OL
id|RXRPC_RTT_CACHE_SIZE
)paren
id|peer-&gt;rtt_usage
op_increment
suffix:semicolon
multiline_comment|/* recalculate RTT */
r_for
c_loop
(paren
id|loop
op_assign
id|peer-&gt;rtt_usage
op_minus
l_int|1
suffix:semicolon
id|loop
op_ge
l_int|0
suffix:semicolon
id|loop
op_decrement
)paren
id|rtt
op_add_assign
id|peer-&gt;rtt_cache
(braket
id|loop
)braket
suffix:semicolon
id|peer-&gt;rtt
op_assign
id|do_div
c_func
(paren
id|rtt
comma
id|peer-&gt;rtt_usage
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; RTT=%lu.%lums&quot;
comma
id|peer-&gt;rtt
op_div
l_int|1000
comma
id|peer-&gt;rtt
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_peer_calculate_rtt() */
eof
