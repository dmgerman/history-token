multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) Cisco 1999,2000&n; * Copyright (c) Motorola 1999,2000,2001&n; * Copyright (c) International Business Machines Corp., 2001,2002&n; * Copyright (c) La Monte H.P. Yarroll 2001&n; *&n; * This file is part of the SCTP kernel reference implementation.&n; *&n; * A collection class to handle the storage of transport addresses.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Daisy Chang           &lt;daisyc@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/if_inet6.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Forward declarations for internal helpers. */
r_static
r_int
id|sctp_copy_one_addr
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
comma
r_union
id|sctp_addr
op_star
comma
id|sctp_scope_t
id|scope
comma
r_int
id|gfp
comma
r_int
id|flags
)paren
suffix:semicolon
r_static
r_void
id|sctp_bind_addr_clean
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
)paren
suffix:semicolon
multiline_comment|/* First Level Abstractions. */
multiline_comment|/* Copy &squot;src&squot; to &squot;dest&squot; taking &squot;scope&squot; into account.  Omit addresses&n; * in &squot;src&squot; which have a broader scope than &squot;scope&squot;.&n; */
DECL|function|sctp_bind_addr_copy
r_int
id|sctp_bind_addr_copy
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|dest
comma
r_const
r_struct
id|sctp_bind_addr
op_star
id|src
comma
id|sctp_scope_t
id|scope
comma
r_int
id|gfp
comma
r_int
id|flags
)paren
(brace
r_struct
id|sctp_sockaddr_entry
op_star
id|addr
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* All addresses share the same port.  */
id|dest-&gt;port
op_assign
id|src-&gt;port
suffix:semicolon
multiline_comment|/* Extract the addresses which are relevant for this scope.  */
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|src-&gt;address_list
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
id|sctp_sockaddr_entry
comma
id|list
)paren
suffix:semicolon
id|error
op_assign
id|sctp_copy_one_addr
c_func
(paren
id|dest
comma
op_amp
id|addr-&gt;a
comma
id|scope
comma
id|gfp
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* If there are no addresses matching the scope and&n;&t; * this is global scope, try to get a link scope address, with&n;&t; * the assumption that we must be sitting behind a NAT.&n;&t; */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|dest-&gt;address_list
)paren
op_logical_and
(paren
id|SCTP_SCOPE_GLOBAL
op_eq
id|scope
)paren
)paren
(brace
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|src-&gt;address_list
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
id|sctp_sockaddr_entry
comma
id|list
)paren
suffix:semicolon
id|error
op_assign
id|sctp_copy_one_addr
c_func
(paren
id|dest
comma
op_amp
id|addr-&gt;a
comma
id|SCTP_SCOPE_LINK
comma
id|gfp
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|error
)paren
id|sctp_bind_addr_clean
c_func
(paren
id|dest
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* Create a new SCTP_bind_addr from nothing.  */
DECL|function|sctp_bind_addr_new
r_struct
id|sctp_bind_addr
op_star
id|sctp_bind_addr_new
c_func
(paren
r_int
id|gfp
)paren
(brace
r_struct
id|sctp_bind_addr
op_star
id|retval
suffix:semicolon
id|retval
op_assign
id|t_new
c_func
(paren
r_struct
id|sctp_bind_addr
comma
id|gfp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
r_goto
id|nomem
suffix:semicolon
id|sctp_bind_addr_init
c_func
(paren
id|retval
comma
l_int|0
)paren
suffix:semicolon
id|retval-&gt;malloced
op_assign
l_int|1
suffix:semicolon
id|SCTP_DBG_OBJCNT_INC
c_func
(paren
id|bind_addr
)paren
suffix:semicolon
id|nomem
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Initialize the SCTP_bind_addr structure for either an endpoint or&n; * an association.&n; */
DECL|function|sctp_bind_addr_init
r_void
id|sctp_bind_addr_init
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
comma
id|__u16
id|port
)paren
(brace
id|bp-&gt;malloced
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|bp-&gt;address_list
)paren
suffix:semicolon
id|bp-&gt;port
op_assign
id|port
suffix:semicolon
)brace
multiline_comment|/* Dispose of the address list. */
DECL|function|sctp_bind_addr_clean
r_static
r_void
id|sctp_bind_addr_clean
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
)paren
(brace
r_struct
id|sctp_sockaddr_entry
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
multiline_comment|/* Empty the bind address list. */
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|temp
comma
op_amp
id|bp-&gt;address_list
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
id|sctp_sockaddr_entry
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
id|SCTP_DBG_OBJCNT_DEC
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Dispose of an SCTP_bind_addr structure  */
DECL|function|sctp_bind_addr_free
r_void
id|sctp_bind_addr_free
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
)paren
(brace
multiline_comment|/* Empty the bind address list. */
id|sctp_bind_addr_clean
c_func
(paren
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;malloced
)paren
(brace
id|kfree
c_func
(paren
id|bp
)paren
suffix:semicolon
id|SCTP_DBG_OBJCNT_DEC
c_func
(paren
id|bind_addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Add an address to the bind address list in the SCTP_bind_addr structure. */
DECL|function|sctp_add_bind_addr
r_int
id|sctp_add_bind_addr
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
comma
r_union
id|sctp_addr
op_star
r_new
comma
r_int
id|gfp
)paren
(brace
r_struct
id|sctp_sockaddr_entry
op_star
id|addr
suffix:semicolon
multiline_comment|/* Add the address to the bind address list.  */
id|addr
op_assign
id|t_new
c_func
(paren
r_struct
id|sctp_sockaddr_entry
comma
id|gfp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|addr-&gt;a
comma
r_new
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
multiline_comment|/* Fix up the port if it has not yet been set.&n;&t; * Both v4 and v6 have the port at the same offset.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;a.v4.sin_port
)paren
id|addr-&gt;a.v4.sin_port
op_assign
id|bp-&gt;port
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
id|bp-&gt;address_list
)paren
suffix:semicolon
id|SCTP_DBG_OBJCNT_INC
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Delete an address from the bind address list in the SCTP_bind_addr&n; * structure.&n; */
DECL|function|sctp_del_bind_addr
r_int
id|sctp_del_bind_addr
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
comma
r_union
id|sctp_addr
op_star
id|del_addr
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|temp
suffix:semicolon
r_struct
id|sctp_sockaddr_entry
op_star
id|addr
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|temp
comma
op_amp
id|bp-&gt;address_list
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
id|sctp_sockaddr_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sctp_cmp_addr_exact
c_func
(paren
op_amp
id|addr-&gt;a
comma
id|del_addr
)paren
)paren
(brace
multiline_comment|/* Found the exact match. */
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
id|SCTP_DBG_OBJCNT_DEC
c_func
(paren
id|addr
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
multiline_comment|/* Create a network byte-order representation of all the addresses&n; * formated as SCTP parameters.&n; *&n; * The second argument is the return value for the length.&n; */
DECL|function|sctp_bind_addrs_to_raw
r_union
id|sctp_params
id|sctp_bind_addrs_to_raw
c_func
(paren
r_const
r_struct
id|sctp_bind_addr
op_star
id|bp
comma
r_int
op_star
id|addrs_len
comma
r_int
id|gfp
)paren
(brace
r_union
id|sctp_params
id|addrparms
suffix:semicolon
r_union
id|sctp_params
id|retval
suffix:semicolon
r_int
id|addrparms_len
suffix:semicolon
r_union
id|sctp_addr_param
id|rawaddr
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|sctp_sockaddr_entry
op_star
id|addr
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|addrparms_len
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Allocate enough memory at once. */
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|bp-&gt;address_list
)paren
(brace
id|len
op_add_assign
r_sizeof
(paren
r_union
id|sctp_addr_param
)paren
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t even bother embedding an address if there&n;&t; * is only one.&n;&t; */
r_if
c_cond
(paren
id|len
op_eq
r_sizeof
(paren
r_union
id|sctp_addr_param
)paren
)paren
(brace
id|retval.v
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|end_raw
suffix:semicolon
)brace
id|retval.v
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|gfp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval.v
)paren
r_goto
id|end_raw
suffix:semicolon
id|addrparms
op_assign
id|retval
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|bp-&gt;address_list
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
id|sctp_sockaddr_entry
comma
id|list
)paren
suffix:semicolon
id|len
op_assign
id|sockaddr2sctp_addr
c_func
(paren
op_amp
id|addr-&gt;a
comma
op_amp
id|rawaddr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|addrparms.v
comma
op_amp
id|rawaddr
comma
id|len
)paren
suffix:semicolon
id|addrparms.v
op_add_assign
id|len
suffix:semicolon
id|addrparms_len
op_add_assign
id|len
suffix:semicolon
)brace
id|end_raw
suffix:colon
op_star
id|addrs_len
op_assign
id|addrparms_len
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Create an address list out of the raw address list format (IPv4 and IPv6&n; * address parameters).&n; */
DECL|function|sctp_raw_to_bind_addrs
r_int
id|sctp_raw_to_bind_addrs
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
comma
id|__u8
op_star
id|raw_addr_list
comma
r_int
id|addrs_len
comma
id|__u16
id|port
comma
r_int
id|gfp
)paren
(brace
r_union
id|sctp_addr_param
op_star
id|rawaddr
suffix:semicolon
r_struct
id|sctp_paramhdr
op_star
id|param
suffix:semicolon
r_union
id|sctp_addr
id|addr
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* Convert the raw address to standard address format */
r_while
c_loop
(paren
id|addrs_len
)paren
(brace
id|param
op_assign
(paren
r_struct
id|sctp_paramhdr
op_star
)paren
id|raw_addr_list
suffix:semicolon
id|rawaddr
op_assign
(paren
r_union
id|sctp_addr_param
op_star
)paren
id|raw_addr_list
suffix:semicolon
r_switch
c_cond
(paren
id|param-&gt;type
)paren
(brace
r_case
id|SCTP_PARAM_IPV4_ADDRESS
suffix:colon
r_case
id|SCTP_PARAM_IPV6_ADDRESS
suffix:colon
id|sctp_param2sockaddr
c_func
(paren
op_amp
id|addr
comma
id|rawaddr
comma
id|port
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|sctp_add_bind_addr
c_func
(paren
id|bp
comma
op_amp
id|addr
comma
id|gfp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
multiline_comment|/* Can&squot;t finish building the list, clean up. */
id|sctp_bind_addr_clean
c_func
(paren
id|bp
)paren
suffix:semicolon
r_break
suffix:semicolon
suffix:semicolon
)brace
id|len
op_assign
id|ntohs
c_func
(paren
id|param-&gt;length
)paren
suffix:semicolon
id|addrs_len
op_sub_assign
id|len
suffix:semicolon
id|raw_addr_list
op_add_assign
id|len
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Corrupted raw addr list! */
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|sctp_bind_addr_clean
c_func
(paren
id|bp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/********************************************************************&n; * 2nd Level Abstractions&n; ********************************************************************/
multiline_comment|/* Does this contain a specified address?  Allow wildcarding. */
DECL|function|sctp_bind_addr_match
r_int
id|sctp_bind_addr_match
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|bp
comma
r_const
r_union
id|sctp_addr
op_star
id|addr
comma
r_struct
id|sctp_opt
op_star
id|opt
)paren
(brace
r_struct
id|sctp_sockaddr_entry
op_star
id|laddr
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|bp-&gt;address_list
)paren
(brace
id|laddr
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|sctp_sockaddr_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;pf
op_member_access_from_pointer
id|cmp_addr
c_func
(paren
op_amp
id|laddr-&gt;a
comma
id|addr
comma
id|opt
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Copy out addresses from the global local address list. */
DECL|function|sctp_copy_one_addr
r_static
r_int
id|sctp_copy_one_addr
c_func
(paren
r_struct
id|sctp_bind_addr
op_star
id|dest
comma
r_union
id|sctp_addr
op_star
id|addr
comma
id|sctp_scope_t
id|scope
comma
r_int
id|gfp
comma
r_int
id|flags
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sctp_is_any
c_func
(paren
id|addr
)paren
)paren
(brace
id|error
op_assign
id|sctp_copy_local_addr_list
c_func
(paren
id|dest
comma
id|scope
comma
id|gfp
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sctp_in_scope
c_func
(paren
id|addr
comma
id|scope
)paren
)paren
(brace
multiline_comment|/* Now that the address is in scope, check to see if&n;&t;&t; * the address type is supported by local sock as&n;&t;&t; * well as the remote peer.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
(paren
id|AF_INET
op_eq
id|addr-&gt;sa.sa_family
)paren
op_logical_and
(paren
id|flags
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
id|addr-&gt;sa.sa_family
)paren
op_logical_and
(paren
id|flags
op_amp
id|SCTP_ADDR6_ALLOWED
)paren
op_logical_and
(paren
id|flags
op_amp
id|SCTP_ADDR6_PEERSUPP
)paren
)paren
)paren
)paren
id|error
op_assign
id|sctp_add_bind_addr
c_func
(paren
id|dest
comma
id|addr
comma
id|gfp
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* Is this a wildcard address?  */
DECL|function|sctp_is_any
r_int
id|sctp_is_any
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_struct
id|sctp_af
op_star
id|af
op_assign
id|sctp_get_af_specific
c_func
(paren
id|addr-&gt;sa.sa_family
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|af
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|af
op_member_access_from_pointer
id|is_any
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Is &squot;addr&squot; valid for &squot;scope&squot;?  */
DECL|function|sctp_in_scope
r_int
id|sctp_in_scope
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr
comma
id|sctp_scope_t
id|scope
)paren
(brace
id|sctp_scope_t
id|addr_scope
op_assign
id|sctp_scope
c_func
(paren
id|addr
)paren
suffix:semicolon
multiline_comment|/* The unusable SCTP addresses will not be considered with&n;&t; * any defined scopes.&n;&t; */
r_if
c_cond
(paren
id|SCTP_SCOPE_UNUSABLE
op_eq
id|addr_scope
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * For INIT and INIT-ACK address list, let L be the level of&n;&t; * of requested destination address, sender and receiver&n;&t; * SHOULD include all of its addresses with level greater&n;&t; * than or equal to L.&n;&t; */
r_if
c_cond
(paren
id|addr_scope
op_le
id|scope
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/********************************************************************&n; * 3rd Level Abstractions&n; ********************************************************************/
multiline_comment|/* What is the scope of &squot;addr&squot;?  */
DECL|function|sctp_scope
id|sctp_scope_t
id|sctp_scope
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr
)paren
(brace
r_struct
id|sctp_af
op_star
id|af
suffix:semicolon
id|af
op_assign
id|sctp_get_af_specific
c_func
(paren
id|addr-&gt;sa.sa_family
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|af
)paren
r_return
id|SCTP_SCOPE_UNUSABLE
suffix:semicolon
r_return
id|af
op_member_access_from_pointer
id|scope
c_func
(paren
(paren
r_union
id|sctp_addr
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
eof
