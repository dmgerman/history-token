multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * Initialization/cleanup for SCTP protocol support.  &n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; *    Sridhar Samudrala &lt;sri@us.ibm.com&gt;&n; *    Daisy Chang &lt;daisyc@us.ibm.com&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
multiline_comment|/* Global data structures. */
DECL|variable|sctp_proto
id|sctp_protocol_t
id|sctp_proto
suffix:semicolon
DECL|variable|proc_net_sctp
r_struct
id|proc_dir_entry
op_star
id|proc_net_sctp
suffix:semicolon
multiline_comment|/* This is the global socket data structure used for responding to&n; * the Out-of-the-blue (OOTB) packets.  A control sock will be created&n; * for this socket at the initialization time.&n; */
DECL|variable|sctp_ctl_socket
r_static
r_struct
id|socket
op_star
id|sctp_ctl_socket
suffix:semicolon
r_extern
r_struct
id|net_proto_family
id|inet_family_ops
suffix:semicolon
multiline_comment|/* Return the address of the control sock. */
DECL|function|sctp_get_ctl_sock
r_struct
id|sock
op_star
id|sctp_get_ctl_sock
c_func
(paren
r_void
)paren
(brace
r_return
id|sctp_ctl_socket-&gt;sk
suffix:semicolon
)brace
multiline_comment|/* Set up the proc fs entry for the SCTP protocol. */
DECL|function|sctp_proc_init
r_void
id|sctp_proc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|proc_net_sctp
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;net/sctp&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|proc_net_sctp
op_assign
id|ent
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Clean up the proc fs entry for the SCTP protocol. */
DECL|function|sctp_proc_exit
r_void
id|sctp_proc_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|proc_net_sctp
)paren
(brace
id|proc_net_sctp
op_assign
l_int|NULL
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;net/sctp&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Private helper to extract ipv4 address and stash them in&n; * the protocol structure.&n; */
DECL|function|sctp_v4_get_local_addr_list
r_static
r_inline
r_void
id|sctp_v4_get_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
r_struct
id|in_ifaddr
op_star
id|ifa
suffix:semicolon
r_struct
id|sockaddr_storage_list
op_star
id|addr
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|in_dev
op_assign
id|__in_dev_get
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|in_dev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ifa
op_assign
id|in_dev-&gt;ifa_list
suffix:semicolon
id|ifa
suffix:semicolon
id|ifa
op_assign
id|ifa-&gt;ifa_next
)paren
(brace
multiline_comment|/* Add the address to the local list.  */
multiline_comment|/* XXX BUG: sleeping allocation with lock held -DaveM */
id|addr
op_assign
id|t_new
c_func
(paren
r_struct
id|sockaddr_storage_list
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|addr-&gt;list
)paren
suffix:semicolon
id|addr-&gt;a.v4.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|addr-&gt;a.v4.sin_port
op_assign
l_int|0
suffix:semicolon
id|addr-&gt;a.v4.sin_addr.s_addr
op_assign
id|ifa-&gt;ifa_local
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|addr-&gt;list
comma
op_amp
id|proto-&gt;local_addr_list
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|in_dev-&gt;lock
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Private helper to extract ipv6 address and stash them in&n; * the protocol structure.&n; * FIXME: Make this an address family function.&n; */
DECL|function|sctp_v6_get_local_addr_list
r_static
r_inline
r_void
id|sctp_v6_get_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
macro_line|#ifdef SCTP_V6_SUPPORT
multiline_comment|/* FIXME: The testframe doesn&squot;t support this function. */
macro_line|#ifndef TEST_FRAME
r_struct
id|inet6_dev
op_star
id|in6_dev
suffix:semicolon
r_struct
id|inet6_ifaddr
op_star
id|ifp
suffix:semicolon
r_struct
id|sockaddr_storage_list
op_star
id|addr
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|in6_dev
op_assign
id|__in6_dev_get
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|read_lock_bh
c_func
(paren
op_amp
id|in6_dev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ifp
op_assign
id|in6_dev-&gt;addr_list
suffix:semicolon
id|ifp
suffix:semicolon
id|ifp
op_assign
id|ifp-&gt;if_next
)paren
(brace
multiline_comment|/* Add the address to the local list.  */
multiline_comment|/* XXX BUG: sleeping allocation with lock held -DaveM */
id|addr
op_assign
id|t_new
c_func
(paren
r_struct
id|sockaddr_storage_list
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
(brace
id|addr-&gt;a.v6.sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;a.v6.sin6_port
op_assign
l_int|0
suffix:semicolon
id|addr-&gt;a.v6.sin6_addr
op_assign
id|ifp-&gt;addr
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|addr-&gt;list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|addr-&gt;list
comma
op_amp
id|proto-&gt;local_addr_list
)paren
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|in6_dev-&gt;lock
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
macro_line|#endif /* TEST_FRAME */
macro_line|#endif /* SCTP_V6_SUPPORT */
)brace
multiline_comment|/* Extract our IP addresses from the system and stash them in the&n; * protocol structure.&n; */
DECL|function|__sctp_get_local_addr_list
r_static
r_void
id|__sctp_get_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|dev_base
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
id|sctp_v4_get_local_addr_list
c_func
(paren
id|proto
comma
id|dev
)paren
suffix:semicolon
id|sctp_v6_get_local_addr_list
c_func
(paren
id|proto
comma
id|dev
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
)brace
DECL|function|sctp_get_local_addr_list
r_static
r_void
id|sctp_get_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
)paren
(brace
r_int
id|flags
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|sctp_proto.local_addr_lock
comma
id|flags
)paren
suffix:semicolon
id|__sctp_get_local_addr_list
c_func
(paren
op_amp
id|sctp_proto
)paren
suffix:semicolon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|sctp_proto.local_addr_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the existing local addresses.  */
DECL|function|__sctp_free_local_addr_list
r_static
r_void
id|__sctp_free_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
)paren
(brace
r_struct
id|sockaddr_storage_list
op_star
id|addr
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|temp
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|temp
comma
op_amp
id|proto-&gt;local_addr_list
)paren
(brace
id|addr
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|sockaddr_storage_list
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|pos
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Free the existing local addresses.  */
DECL|function|sctp_free_local_addr_list
r_static
r_void
id|sctp_free_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
)paren
(brace
r_int
id|flags
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|proto-&gt;local_addr_lock
comma
id|flags
)paren
suffix:semicolon
id|__sctp_free_local_addr_list
c_func
(paren
id|proto
)paren
suffix:semicolon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|proto-&gt;local_addr_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the local addresses which are valid for &squot;scope&squot; into &squot;bp&squot;.  */
DECL|function|sctp_copy_local_addr_list
r_int
id|sctp_copy_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
id|proto
comma
id|sctp_bind_addr_t
op_star
id|bp
comma
id|sctp_scope_t
id|scope
comma
r_int
id|priority
comma
r_int
id|copy_flags
)paren
(brace
r_struct
id|sockaddr_storage_list
op_star
id|addr
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_int
id|flags
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|proto-&gt;local_addr_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|proto-&gt;local_addr_list
)paren
(brace
id|addr
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|sockaddr_storage_list
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sctp_in_scope
c_func
(paren
op_amp
id|addr-&gt;a
comma
id|scope
)paren
)paren
(brace
multiline_comment|/* Now that the address is in scope, check to see if&n;&t;&t;&t; * the address type is really supported by the local&n;&t;&t;&t; * sock as well as the remote peer.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
(paren
id|AF_INET
op_eq
id|addr-&gt;a.sa.sa_family
)paren
op_logical_and
(paren
id|copy_flags
op_amp
id|SCTP_ADDR4_PEERSUPP
)paren
)paren
)paren
op_logical_or
(paren
(paren
(paren
id|AF_INET6
op_eq
id|addr-&gt;a.sa.sa_family
)paren
op_logical_and
(paren
id|copy_flags
op_amp
id|SCTP_ADDR6_ALLOWED
)paren
op_logical_and
(paren
id|copy_flags
op_amp
id|SCTP_ADDR6_PEERSUPP
)paren
)paren
)paren
)paren
(brace
id|error
op_assign
id|sctp_add_bind_addr
c_func
(paren
id|bp
comma
op_amp
id|addr-&gt;a
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|end_copy
suffix:semicolon
)brace
)brace
)brace
id|end_copy
suffix:colon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|proto-&gt;local_addr_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* Returns the mtu for the given v4 destination address.  */
DECL|function|sctp_v4_get_dst_mtu
r_int
id|sctp_v4_get_dst_mtu
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|address
)paren
(brace
r_int
id|dst_mtu
op_assign
id|SCTP_DEFAULT_MAXSEGMENT
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|rt_key
id|key
op_assign
(brace
dot
id|dst
op_assign
id|address-&gt;v4.sin_addr.s_addr
comma
dot
id|src
op_assign
l_int|0
comma
dot
id|iif
op_assign
l_int|0
comma
dot
id|oif
op_assign
l_int|0
comma
dot
id|tos
op_assign
l_int|0
comma
dot
id|scope
op_assign
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|key
)paren
)paren
(brace
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;sctp_v4_get_dst_mtu:ip_route_output_key&quot;
l_string|&quot; failed, returning %d as dst_mtu&bslash;n&quot;
comma
id|dst_mtu
)paren
suffix:semicolon
)brace
r_else
(brace
id|dst_mtu
op_assign
id|rt-&gt;u.dst.pmtu
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;sctp_v4_get_dst_mtu: &quot;
l_string|&quot;ip_route_output_key: dev:%s pmtu:%d&bslash;n&quot;
comma
id|rt-&gt;u.dst.dev-&gt;name
comma
id|dst_mtu
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
r_return
id|dst_mtu
suffix:semicolon
)brace
multiline_comment|/* Event handler for inet device events.&n; * Basically, whenever there is an event, we re-build our local address list.&n; */
DECL|function|sctp_netdev_event
r_static
r_int
id|sctp_netdev_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
id|flags
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|sctp_proto.local_addr_lock
comma
id|flags
)paren
suffix:semicolon
id|__sctp_free_local_addr_list
c_func
(paren
op_amp
id|sctp_proto
)paren
suffix:semicolon
id|__sctp_get_local_addr_list
c_func
(paren
op_amp
id|sctp_proto
)paren
suffix:semicolon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|sctp_proto.local_addr_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the control inode/socket with a control endpoint data&n; * structure.  This endpoint is reserved exclusively for the OOTB processing.&n; */
DECL|function|sctp_ctl_sock_init
r_int
id|sctp_ctl_sock_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|family
op_assign
id|PF_INET
suffix:semicolon
id|SCTP_V6
c_func
(paren
id|family
op_assign
id|PF_INET6
suffix:semicolon
)paren
id|err
op_assign
id|sock_create
c_func
(paren
id|family
comma
id|SOCK_SEQPACKET
comma
id|IPPROTO_SCTP
comma
op_amp
id|sctp_ctl_socket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SCTP: Failed to create the SCTP control socket.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|sctp_ctl_socket-&gt;sk-&gt;allocation
op_assign
id|GFP_ATOMIC
suffix:semicolon
id|inet_sk
c_func
(paren
id|sctp_ctl_socket-&gt;sk
)paren
op_member_access_from_pointer
id|ttl
op_assign
id|MAXTTL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the table of functions for manipulating a particular address&n; * family.&n; */
DECL|function|sctp_get_af_specific
id|sctp_func_t
op_star
id|sctp_get_af_specific
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|address
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|sctp_protocol_t
op_star
id|proto
op_assign
id|sctp_get_protocol
c_func
(paren
)paren
suffix:semicolon
id|sctp_func_t
op_star
id|retval
comma
op_star
id|af
suffix:semicolon
id|retval
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Cycle through all AF specific functions looking for a&n;&t; * match.&n;&t; */
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|proto-&gt;address_families
)paren
(brace
id|af
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|sctp_func_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address-&gt;sa.sa_family
op_eq
id|af-&gt;sa_family
)paren
(brace
id|retval
op_assign
id|af
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Registration for netdev events.  */
DECL|variable|sctp_netdev_notifier
r_struct
id|notifier_block
id|sctp_netdev_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|sctp_netdev_event
comma
)brace
suffix:semicolon
multiline_comment|/* Socket operations.  */
DECL|variable|inet_seqpacket_ops
r_struct
id|proto_ops
id|inet_seqpacket_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_INET
comma
dot
id|release
op_assign
id|inet_release
comma
multiline_comment|/* Needs to be wrapped... */
dot
id|bind
op_assign
id|inet_bind
comma
dot
id|connect
op_assign
id|inet_dgram_connect
comma
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
dot
id|accept
op_assign
id|inet_accept
comma
dot
id|getname
op_assign
id|inet_getname
comma
multiline_comment|/* Semantics are different.  */
dot
id|poll
op_assign
id|sctp_poll
comma
dot
id|ioctl
op_assign
id|inet_ioctl
comma
dot
id|listen
op_assign
id|sctp_inet_listen
comma
dot
id|shutdown
op_assign
id|inet_shutdown
comma
multiline_comment|/* Looks harmless.  */
dot
id|setsockopt
op_assign
id|inet_setsockopt
comma
multiline_comment|/* IP_SOL IP_OPTION is a problem. */
dot
id|getsockopt
op_assign
id|inet_getsockopt
comma
dot
id|sendmsg
op_assign
id|inet_sendmsg
comma
dot
id|recvmsg
op_assign
id|inet_recvmsg
comma
dot
id|mmap
op_assign
id|sock_no_mmap
comma
dot
id|sendpage
op_assign
id|sock_no_sendpage
comma
)brace
suffix:semicolon
multiline_comment|/* Registration with AF_INET family.  */
DECL|variable|sctp_protosw
r_struct
id|inet_protosw
id|sctp_protosw
op_assign
(brace
dot
id|type
op_assign
id|SOCK_SEQPACKET
comma
dot
id|protocol
op_assign
id|IPPROTO_SCTP
comma
dot
id|prot
op_assign
op_amp
id|sctp_prot
comma
dot
id|ops
op_assign
op_amp
id|inet_seqpacket_ops
comma
dot
id|capability
op_assign
op_minus
l_int|1
comma
dot
id|no_check
op_assign
l_int|0
comma
dot
id|flags
op_assign
id|SCTP_PROTOSW_FLAG
)brace
suffix:semicolon
multiline_comment|/* Register with IP layer.  */
DECL|variable|sctp_protocol
r_static
r_struct
id|inet_protocol
id|sctp_protocol
op_assign
(brace
dot
id|handler
op_assign
id|sctp_rcv
comma
multiline_comment|/* SCTP input handler.  */
dot
id|err_handler
op_assign
id|sctp_v4_err
comma
multiline_comment|/* SCTP error control   */
dot
id|protocol
op_assign
id|IPPROTO_SCTP
comma
multiline_comment|/* protocol ID          */
dot
id|name
op_assign
l_string|&quot;SCTP&quot;
multiline_comment|/* name                 */
)brace
suffix:semicolon
multiline_comment|/* IPv4 address related functions.  */
DECL|variable|sctp_ipv4_specific
id|sctp_func_t
id|sctp_ipv4_specific
op_assign
(brace
dot
id|queue_xmit
op_assign
id|ip_queue_xmit
comma
dot
id|setsockopt
op_assign
id|ip_setsockopt
comma
dot
id|getsockopt
op_assign
id|ip_getsockopt
comma
dot
id|get_dst_mtu
op_assign
id|sctp_v4_get_dst_mtu
comma
dot
id|net_header_len
op_assign
r_sizeof
(paren
r_struct
id|iphdr
)paren
comma
dot
id|sockaddr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_in
)paren
comma
dot
id|sa_family
op_assign
id|AF_INET
comma
)brace
suffix:semicolon
multiline_comment|/* Initialize the universe into something sensible.  */
DECL|function|sctp_init
r_int
id|sctp_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Add SCTP to inetsw linked list.  */
id|inet_register_protosw
c_func
(paren
op_amp
id|sctp_protosw
)paren
suffix:semicolon
multiline_comment|/* Add SCTP to inet_protos hash table.  */
id|inet_add_protocol
c_func
(paren
op_amp
id|sctp_protocol
)paren
suffix:semicolon
multiline_comment|/* Initialize proc fs directory.  */
id|sctp_proc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize object count debugging.  */
id|sctp_dbg_objcnt_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * 14. Suggested SCTP Protocol Parameter Values&n;         */
multiline_comment|/* The following protocol parameters are RECOMMENDED:  */
multiline_comment|/* RTO.Initial              - 3  seconds */
id|sctp_proto.rto_initial
op_assign
id|SCTP_RTO_INITIAL
suffix:semicolon
multiline_comment|/* RTO.Min                  - 1  second */
id|sctp_proto.rto_min
op_assign
id|SCTP_RTO_MIN
suffix:semicolon
multiline_comment|/* RTO.Max                 -  60 seconds */
id|sctp_proto.rto_max
op_assign
id|SCTP_RTO_MAX
suffix:semicolon
multiline_comment|/* RTO.Alpha                - 1/8 */
id|sctp_proto.rto_alpha
op_assign
id|SCTP_RTO_ALPHA
suffix:semicolon
multiline_comment|/* RTO.Beta                 - 1/4 */
id|sctp_proto.rto_beta
op_assign
id|SCTP_RTO_BETA
suffix:semicolon
multiline_comment|/* Valid.Cookie.Life        - 60  seconds */
id|sctp_proto.valid_cookie_life
op_assign
l_int|60
op_star
id|HZ
suffix:semicolon
multiline_comment|/* Max.Burst&t;&t;    - 4 */
id|sctp_proto.max_burst
op_assign
id|SCTP_MAX_BURST
suffix:semicolon
multiline_comment|/* Association.Max.Retrans  - 10 attempts&n;&t; * Path.Max.Retrans         - 5  attempts (per destination address)&n;&t; * Max.Init.Retransmits     - 8  attempts&n;&t; */
id|sctp_proto.max_retrans_association
op_assign
l_int|10
suffix:semicolon
id|sctp_proto.max_retrans_path
op_assign
l_int|5
suffix:semicolon
id|sctp_proto.max_retrans_init
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* HB.interval              - 30 seconds */
id|sctp_proto.hb_interval
op_assign
l_int|30
op_star
id|HZ
suffix:semicolon
multiline_comment|/* Implementation specific variables. */
multiline_comment|/* Initialize default stream count setup information.&n;&t; * Note: today the stream accounting data structures are very&n;&t; * fixed size, so one really does need to make sure that these have&n;&t; * upper/lower limits when changing.&n;&t; */
id|sctp_proto.max_instreams
op_assign
id|SCTP_MAX_STREAM
suffix:semicolon
id|sctp_proto.max_outstreams
op_assign
id|SCTP_MAX_STREAM
suffix:semicolon
multiline_comment|/* Allocate and initialize the association hash table.  */
id|sctp_proto.assoc_hashsize
op_assign
l_int|4096
suffix:semicolon
id|sctp_proto.assoc_hashbucket
op_assign
(paren
id|sctp_hashbucket_t
op_star
)paren
id|kmalloc
c_func
(paren
l_int|4096
op_star
r_sizeof
(paren
id|sctp_hashbucket_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_proto.assoc_hashbucket
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;SCTP: Failed association hash alloc.&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_ahash_alloc
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sctp_proto.assoc_hashsize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sctp_proto.assoc_hashbucket
(braket
id|i
)braket
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|sctp_proto.assoc_hashbucket
(braket
id|i
)braket
dot
id|chain
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Allocate and initialize the endpoint hash table.  */
id|sctp_proto.ep_hashsize
op_assign
l_int|64
suffix:semicolon
id|sctp_proto.ep_hashbucket
op_assign
(paren
id|sctp_hashbucket_t
op_star
)paren
id|kmalloc
c_func
(paren
l_int|64
op_star
r_sizeof
(paren
id|sctp_hashbucket_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_proto.ep_hashbucket
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;SCTP: Failed endpoint_hash alloc.&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_ehash_alloc
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sctp_proto.ep_hashsize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sctp_proto.ep_hashbucket
(braket
id|i
)braket
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|sctp_proto.ep_hashbucket
(braket
id|i
)braket
dot
id|chain
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Allocate and initialize the SCTP port hash table.  */
id|sctp_proto.port_hashsize
op_assign
l_int|4096
suffix:semicolon
id|sctp_proto.port_hashtable
op_assign
(paren
id|sctp_bind_hashbucket_t
op_star
)paren
id|kmalloc
c_func
(paren
l_int|4096
op_star
r_sizeof
(paren
id|sctp_bind_hashbucket_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_proto.port_hashtable
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;SCTP: Failed bind hash alloc.&quot;
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_bhash_alloc
suffix:semicolon
)brace
id|sctp_proto.port_alloc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|sctp_proto.port_rover
op_assign
id|sysctl_local_port_range
(braket
l_int|0
)braket
op_minus
l_int|1
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
id|sctp_proto.port_hashsize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sctp_proto.port_hashtable
(braket
id|i
)braket
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|sctp_proto.port_hashtable
(braket
id|i
)braket
dot
id|chain
op_assign
l_int|NULL
suffix:semicolon
)brace
id|sctp_sysctl_register
c_func
(paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|sctp_proto.address_families
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|sctp_ipv4_specific.list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|sctp_ipv4_specific.list
comma
op_amp
id|sctp_proto.address_families
)paren
suffix:semicolon
id|status
op_assign
id|sctp_v6_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_goto
id|err_v6_init
suffix:semicolon
multiline_comment|/* Initialize the control inode/socket for handling OOTB packets.  */
r_if
c_cond
(paren
(paren
id|status
op_assign
id|sctp_ctl_sock_init
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;SCTP: Failed to initialize the SCTP control sock.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_ctl_sock_init
suffix:semicolon
)brace
multiline_comment|/* Initialize the local address list. */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|sctp_proto.local_addr_list
)paren
suffix:semicolon
id|sctp_proto.local_addr_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|register_inetaddr_notifier
c_func
(paren
op_amp
id|sctp_netdev_notifier
)paren
suffix:semicolon
id|sctp_get_local_addr_list
c_func
(paren
op_amp
id|sctp_proto
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_ctl_sock_init
suffix:colon
id|sctp_v6_exit
c_func
(paren
)paren
suffix:semicolon
id|err_v6_init
suffix:colon
id|sctp_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sctp_ipv4_specific.list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sctp_proto.port_hashtable
)paren
suffix:semicolon
id|err_bhash_alloc
suffix:colon
id|kfree
c_func
(paren
id|sctp_proto.ep_hashbucket
)paren
suffix:semicolon
id|err_ehash_alloc
suffix:colon
id|kfree
c_func
(paren
id|sctp_proto.assoc_hashbucket
)paren
suffix:semicolon
id|err_ahash_alloc
suffix:colon
id|sctp_dbg_objcnt_exit
c_func
(paren
)paren
suffix:semicolon
id|sctp_proc_exit
c_func
(paren
)paren
suffix:semicolon
id|inet_del_protocol
c_func
(paren
op_amp
id|sctp_protocol
)paren
suffix:semicolon
id|inet_unregister_protosw
c_func
(paren
op_amp
id|sctp_protosw
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/* Exit handler for the SCTP protocol.  */
DECL|function|sctp_exit
r_void
id|sctp_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* BUG.  This should probably do something useful like clean&n;&t; * up all the remaining associations and all that memory.&n;&t; */
multiline_comment|/* Free the local address list.  */
id|unregister_inetaddr_notifier
c_func
(paren
op_amp
id|sctp_netdev_notifier
)paren
suffix:semicolon
id|sctp_free_local_addr_list
c_func
(paren
op_amp
id|sctp_proto
)paren
suffix:semicolon
multiline_comment|/* Free the control endpoint.  */
id|sock_release
c_func
(paren
id|sctp_ctl_socket
)paren
suffix:semicolon
id|sctp_v6_exit
c_func
(paren
)paren
suffix:semicolon
id|sctp_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sctp_ipv4_specific.list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sctp_proto.assoc_hashbucket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sctp_proto.ep_hashbucket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sctp_proto.port_hashtable
)paren
suffix:semicolon
id|sctp_dbg_objcnt_exit
c_func
(paren
)paren
suffix:semicolon
id|sctp_proc_exit
c_func
(paren
)paren
suffix:semicolon
id|inet_del_protocol
c_func
(paren
op_amp
id|sctp_protocol
)paren
suffix:semicolon
id|inet_unregister_protosw
c_func
(paren
op_amp
id|sctp_protosw
)paren
suffix:semicolon
)brace
DECL|variable|sctp_init
id|module_init
c_func
(paren
id|sctp_init
)paren
suffix:semicolon
DECL|variable|sctp_exit
id|module_exit
c_func
(paren
id|sctp_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Linux Kernel SCTP developers &lt;lksctp-developers@lists.sourceforge.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Support for the SCTP protocol (RFC2960)&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof