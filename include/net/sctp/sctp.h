multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001-2002 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * The base lksctp header.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Xingang Guo           &lt;xingang.guo@intel.com&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Daisy Chang&t;    &lt;daisyc@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#ifndef __net_sctp_h__
DECL|macro|__net_sctp_h__
mdefine_line|#define __net_sctp_h__
multiline_comment|/* Header Strategy.&n; *    Start getting some control over the header file depencies:&n; *       includes&n; *       constants&n; *       structs&n; *       prototypes&n; *       macros, externs, and inlines&n; *&n; *   Move test_frame specific items out of the kernel headers&n; *   and into the test frame headers.   This is not perfect in any sense&n; *   and will continue to evolve.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef TEST_FRAME
DECL|macro|CONFIG_PROC_FS
macro_line|#undef CONFIG_PROC_FS
DECL|macro|CONFIG_SCTP_DBG_OBJCNT
macro_line|#undef CONFIG_SCTP_DBG_OBJCNT
DECL|macro|CONFIG_SYSCTL
macro_line|#undef CONFIG_SYSCTL
macro_line|#endif /* TEST_FRAME */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/sctp/structs.h&gt;
macro_line|#include &lt;net/sctp/constants.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Set SCTP_DEBUG flag via config if not already set. */
macro_line|#ifndef SCTP_DEBUG
macro_line|#ifdef CONFIG_SCTP_DBG_MSG
DECL|macro|SCTP_DEBUG
mdefine_line|#define SCTP_DEBUG&t;1
macro_line|#else
DECL|macro|SCTP_DEBUG
mdefine_line|#define SCTP_DEBUG      0
macro_line|#endif /* CONFIG_SCTP_DBG */
macro_line|#endif /* SCTP_DEBUG */
macro_line|#ifdef CONFIG_IP_SCTP_MODULE
DECL|macro|SCTP_PROTOSW_FLAG
mdefine_line|#define SCTP_PROTOSW_FLAG 0
macro_line|#else /* static! */
DECL|macro|SCTP_PROTOSW_FLAG
mdefine_line|#define SCTP_PROTOSW_FLAG INET_PROTOSW_PERMANENT
macro_line|#endif
multiline_comment|/* Certain internal static functions need to be exported when&n; * compiled into the test frame.&n; */
macro_line|#ifndef SCTP_STATIC
DECL|macro|SCTP_STATIC
mdefine_line|#define SCTP_STATIC static
macro_line|#endif
multiline_comment|/*&n; * Function declarations.&n; */
multiline_comment|/*&n; * sctp_protocol.c&n; */
r_extern
id|sctp_protocol_t
id|sctp_proto
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|sctp_get_ctl_sock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sctp_copy_local_addr_list
c_func
(paren
id|sctp_protocol_t
op_star
comma
id|sctp_bind_addr_t
op_star
comma
id|sctp_scope_t
comma
r_int
id|priority
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_struct
id|sctp_pf
op_star
id|sctp_get_pf_specific
c_func
(paren
id|sa_family_t
id|family
)paren
suffix:semicolon
r_extern
r_int
id|sctp_register_pf
c_func
(paren
r_struct
id|sctp_pf
op_star
comma
id|sa_family_t
)paren
suffix:semicolon
multiline_comment|/*&n; * sctp_socket.c&n; */
r_extern
r_int
id|sctp_backlog_rcv
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|sctp_inet_listen
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|backlog
)paren
suffix:semicolon
r_extern
r_void
id|sctp_write_space
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sctp_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|socket
op_star
id|sock
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n; * sctp_primitive.c&n; */
r_extern
r_int
id|sctp_primitive_ASSOCIATE
c_func
(paren
id|sctp_association_t
op_star
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|sctp_primitive_SHUTDOWN
c_func
(paren
id|sctp_association_t
op_star
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|sctp_primitive_ABORT
c_func
(paren
id|sctp_association_t
op_star
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|sctp_primitive_SEND
c_func
(paren
id|sctp_association_t
op_star
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|sctp_primitive_REQUESTHEARTBEAT
c_func
(paren
id|sctp_association_t
op_star
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; * sctp_crc32c.c&n; */
r_extern
id|__u32
id|count_crc
c_func
(paren
id|__u8
op_star
id|ptr
comma
id|__u16
id|count
)paren
suffix:semicolon
multiline_comment|/*&n; * sctp_input.c&n; */
r_extern
r_int
id|sctp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|sctp_v4_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|info
)paren
suffix:semicolon
r_extern
r_void
id|sctp_hash_established
c_func
(paren
id|sctp_association_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__sctp_hash_established
c_func
(paren
id|sctp_association_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sctp_unhash_established
c_func
(paren
id|sctp_association_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__sctp_unhash_established
c_func
(paren
id|sctp_association_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sctp_hash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__sctp_hash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sctp_unhash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__sctp_unhash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * sctp_hashdriver.c&n; */
r_extern
r_void
id|sctp_hash_digest
c_func
(paren
r_const
r_char
op_star
id|secret
comma
r_const
r_int
id|secret_len
comma
r_const
r_char
op_star
id|text
comma
r_const
r_int
id|text_len
comma
id|__u8
op_star
id|digest
)paren
suffix:semicolon
multiline_comment|/*&n; *  Section:  Macros, externs, and inlines&n; */
macro_line|#ifdef TEST_FRAME
macro_line|#include &lt;test_frame.h&gt;
macro_line|#else
multiline_comment|/* spin lock wrappers. */
DECL|macro|sctp_spin_lock_irqsave
mdefine_line|#define sctp_spin_lock_irqsave(lock, flags) spin_lock_irqsave(lock, flags)
DECL|macro|sctp_spin_unlock_irqrestore
mdefine_line|#define sctp_spin_unlock_irqrestore(lock, flags)  &bslash;&n;       spin_unlock_irqrestore(lock, flags)
DECL|macro|sctp_local_bh_disable
mdefine_line|#define sctp_local_bh_disable() local_bh_disable()
DECL|macro|sctp_local_bh_enable
mdefine_line|#define sctp_local_bh_enable() local_bh_enable()
DECL|macro|sctp_spin_lock
mdefine_line|#define sctp_spin_lock(lock) spin_lock(lock)
DECL|macro|sctp_spin_unlock
mdefine_line|#define sctp_spin_unlock(lock) spin_unlock(lock)
DECL|macro|sctp_write_lock
mdefine_line|#define sctp_write_lock(lock) write_lock(lock)
DECL|macro|sctp_write_unlock
mdefine_line|#define sctp_write_unlock(lock) write_unlock(lock)
DECL|macro|sctp_read_lock
mdefine_line|#define sctp_read_lock(lock) read_lock(lock)
DECL|macro|sctp_read_unlock
mdefine_line|#define sctp_read_unlock(lock) read_unlock(lock)
multiline_comment|/* sock lock wrappers. */
DECL|macro|sctp_lock_sock
mdefine_line|#define sctp_lock_sock(sk) lock_sock(sk)
DECL|macro|sctp_release_sock
mdefine_line|#define sctp_release_sock(sk) release_sock(sk)
DECL|macro|sctp_bh_lock_sock
mdefine_line|#define sctp_bh_lock_sock(sk) bh_lock_sock(sk)
DECL|macro|sctp_bh_unlock_sock
mdefine_line|#define sctp_bh_unlock_sock(sk) bh_unlock_sock(sk)
DECL|macro|SCTP_SOCK_SLEEP_PRE
mdefine_line|#define SCTP_SOCK_SLEEP_PRE(sk) SOCK_SLEEP_PRE(sk)
DECL|macro|SCTP_SOCK_SLEEP_POST
mdefine_line|#define SCTP_SOCK_SLEEP_POST(sk) SOCK_SLEEP_POST(sk)
multiline_comment|/* SCTP SNMP MIB stats handlers */
r_extern
r_struct
id|sctp_mib
id|sctp_statistics
(braket
id|NR_CPUS
op_star
l_int|2
)braket
suffix:semicolon
DECL|macro|SCTP_INC_STATS
mdefine_line|#define SCTP_INC_STATS(field)&t;&t;SNMP_INC_STATS(sctp_statistics, field)
DECL|macro|SCTP_INC_STATS_BH
mdefine_line|#define SCTP_INC_STATS_BH(field)&t;SNMP_INC_STATS_BH(sctp_statistics, field)
DECL|macro|SCTP_INC_STATS_USER
mdefine_line|#define SCTP_INC_STATS_USER(field)&t;SNMP_INC_STATS_USER(sctp_statistics, field)
multiline_comment|/* Determine if this is a valid kernel address.  */
DECL|function|sctp_is_valid_kaddr
r_static
r_inline
r_int
id|sctp_is_valid_kaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/* Make sure the address is not in the user address space. */
r_if
c_cond
(paren
id|addr
OL
id|PAGE_OFFSET
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|addr
)paren
suffix:semicolon
multiline_comment|/* Is this page valid? */
r_if
c_cond
(paren
op_logical_neg
id|virt_addr_valid
c_func
(paren
id|addr
)paren
op_logical_or
id|PageReserved
c_func
(paren
id|page
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* !TEST_FRAME */
multiline_comment|/* Print debugging messages.  */
macro_line|#if SCTP_DEBUG
r_extern
r_int
id|sctp_debug_flag
suffix:semicolon
DECL|macro|SCTP_DEBUG_PRINTK
mdefine_line|#define SCTP_DEBUG_PRINTK(whatever...) &bslash;&n;&t;((void) (sctp_debug_flag &amp;&amp; printk(KERN_DEBUG whatever)))
DECL|macro|SCTP_ENABLE_DEBUG
mdefine_line|#define SCTP_ENABLE_DEBUG { sctp_debug_flag = 1; }
DECL|macro|SCTP_DISABLE_DEBUG
mdefine_line|#define SCTP_DISABLE_DEBUG { sctp_debug_flag = 0; }
DECL|macro|SCTP_ASSERT
mdefine_line|#define SCTP_ASSERT(expr, str, func) &bslash;&n;&t;if (!(expr)) { &bslash;&n;&t;&t;SCTP_DEBUG_PRINTK(&quot;Assertion Failed: %s(%s) at %s:%s:%d&bslash;n&quot;, &bslash;&n;&t;&t;&t;str, (#expr), __FILE__, __FUNCTION__, __LINE__); &bslash;&n;&t;&t;func; &bslash;&n;&t;}
macro_line|#else&t;/* SCTP_DEBUG */
DECL|macro|SCTP_DEBUG_PRINTK
mdefine_line|#define SCTP_DEBUG_PRINTK(whatever...)
DECL|macro|SCTP_ENABLE_DEBUG
mdefine_line|#define SCTP_ENABLE_DEBUG
DECL|macro|SCTP_DISABLE_DEBUG
mdefine_line|#define SCTP_DISABLE_DEBUG
DECL|macro|SCTP_ASSERT
mdefine_line|#define SCTP_ASSERT(expr, str, func)
macro_line|#endif /* SCTP_DEBUG */
multiline_comment|/*&n; * Macros for keeping a global reference of object allocations.&n; */
macro_line|#ifdef CONFIG_SCTP_DBG_OBJCNT
r_extern
id|atomic_t
id|sctp_dbg_objcnt_sock
suffix:semicolon
r_extern
id|atomic_t
id|sctp_dbg_objcnt_ep
suffix:semicolon
r_extern
id|atomic_t
id|sctp_dbg_objcnt_assoc
suffix:semicolon
r_extern
id|atomic_t
id|sctp_dbg_objcnt_transport
suffix:semicolon
r_extern
id|atomic_t
id|sctp_dbg_objcnt_chunk
suffix:semicolon
r_extern
id|atomic_t
id|sctp_dbg_objcnt_bind_addr
suffix:semicolon
r_extern
id|atomic_t
id|sctp_dbg_objcnt_addr
suffix:semicolon
multiline_comment|/* Macros to atomically increment/decrement objcnt counters.  */
DECL|macro|SCTP_DBG_OBJCNT_INC
mdefine_line|#define SCTP_DBG_OBJCNT_INC(name) &bslash;&n;atomic_inc(&amp;sctp_dbg_objcnt_## name)
DECL|macro|SCTP_DBG_OBJCNT_DEC
mdefine_line|#define SCTP_DBG_OBJCNT_DEC(name) &bslash;&n;atomic_dec(&amp;sctp_dbg_objcnt_## name)
DECL|macro|SCTP_DBG_OBJCNT
mdefine_line|#define SCTP_DBG_OBJCNT(name) &bslash;&n;atomic_t sctp_dbg_objcnt_## name = ATOMIC_INIT(0)
multiline_comment|/* Macro to help create new entries in in the global array of&n; * objcnt counters.&n; */
DECL|macro|SCTP_DBG_OBJCNT_ENTRY
mdefine_line|#define SCTP_DBG_OBJCNT_ENTRY(name) &bslash;&n;{.label= #name, .counter= &amp;sctp_dbg_objcnt_## name}
r_extern
r_void
id|sctp_dbg_objcnt_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sctp_dbg_objcnt_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|SCTP_DBG_OBJCNT_INC
mdefine_line|#define SCTP_DBG_OBJCNT_INC(name)
DECL|macro|SCTP_DBG_OBJCNT_DEC
mdefine_line|#define SCTP_DBG_OBJCNT_DEC(name)
DECL|function|sctp_dbg_objcnt_init
r_static
r_inline
r_void
id|sctp_dbg_objcnt_init
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|sctp_dbg_objcnt_exit
r_static
r_inline
r_void
id|sctp_dbg_objcnt_exit
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SCTP_DBG_OBJCOUNT */
macro_line|#if defined CONFIG_SYSCTL
r_extern
r_void
id|sctp_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sctp_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|sctp_sysctl_register
r_static
r_inline
r_void
id|sctp_sysctl_register
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|sctp_sysctl_unregister
r_static
r_inline
r_void
id|sctp_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
r_extern
r_int
id|sctp_v6_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sctp_v6_exit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|sctp_ipv6_addr_type
r_static
r_inline
r_int
id|sctp_ipv6_addr_type
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_return
id|ipv6_addr_type
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|SCTP_SAT_LEN
mdefine_line|#define SCTP_SAT_LEN (sizeof(sctp_paramhdr_t) + 2 * sizeof(__u16))
multiline_comment|/* Note: These V6 macros are obsolescent.  */
multiline_comment|/* Use this macro to enclose code fragments which are V6-dependent. */
DECL|macro|SCTP_V6
mdefine_line|#define SCTP_V6(m...)&t;m
DECL|macro|SCTP_V6_SUPPORT
mdefine_line|#define SCTP_V6_SUPPORT 1
macro_line|#else /* #ifdef defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE) */
DECL|macro|sctp_ipv6_addr_type
mdefine_line|#define sctp_ipv6_addr_type(a) 0
DECL|macro|SCTP_SAT_LEN
mdefine_line|#define SCTP_SAT_LEN (sizeof(sctp_paramhdr_t) + 1 * sizeof(__u16))
DECL|macro|SCTP_V6
mdefine_line|#define SCTP_V6(m...) /* Do nothing. */
DECL|macro|SCTP_V6_SUPPORT
macro_line|#undef SCTP_V6_SUPPORT
DECL|function|sctp_v6_init
r_static
r_inline
r_int
id|sctp_v6_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sctp_v6_exit
r_static
r_inline
r_void
id|sctp_v6_exit
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif /* #ifdef defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE) */
multiline_comment|/* Map an association to an assoc_id. */
DECL|function|sctp_assoc2id
r_static
r_inline
id|sctp_assoc_t
id|sctp_assoc2id
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
)paren
(brace
r_return
(paren
id|sctp_assoc_t
)paren
id|asoc
suffix:semicolon
)brace
multiline_comment|/* Look up the association by its id.  */
DECL|function|sctp_id2assoc
r_static
r_inline
id|sctp_association_t
op_star
id|sctp_id2assoc
c_func
(paren
r_const
r_struct
id|sock
op_star
id|sk
comma
id|sctp_assoc_t
id|id
)paren
(brace
id|sctp_association_t
op_star
id|asoc
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* First, verify that this is a kernel address. */
r_if
c_cond
(paren
id|sctp_is_valid_kaddr
c_func
(paren
(paren
r_int
r_int
)paren
id|id
)paren
)paren
(brace
id|sctp_association_t
op_star
id|temp
op_assign
(paren
id|sctp_association_t
op_star
)paren
id|id
suffix:semicolon
multiline_comment|/* Verify that this _is_ an sctp_association_t&n;&t;&t; * data structure and if so, that the socket matches.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|SCTP_ASSOC_EYECATCHER
op_eq
id|temp-&gt;eyecatcher
)paren
op_logical_and
(paren
id|temp-&gt;base.sk
op_eq
id|sk
)paren
)paren
id|asoc
op_assign
id|temp
suffix:semicolon
)brace
r_return
id|asoc
suffix:semicolon
)brace
multiline_comment|/* A macro to walk a list of skbs.  */
DECL|macro|sctp_skb_for_each
mdefine_line|#define sctp_skb_for_each(pos, head, tmp) &bslash;&n;for (pos = (head)-&gt;next;&bslash;&n;     tmp = (pos)-&gt;next, pos != ((struct sk_buff *)(head));&bslash;&n;     pos = tmp)
multiline_comment|/* A helper to append an entire skb list (list) to another (head). */
DECL|function|sctp_skb_list_tail
r_static
r_inline
r_void
id|sctp_skb_list_tail
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
comma
r_struct
id|sk_buff_head
op_star
id|head
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
id|head-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|sctp_spin_lock
c_func
(paren
op_amp
id|list-&gt;lock
)paren
suffix:semicolon
id|list_splice
c_func
(paren
(paren
r_struct
id|list_head
op_star
)paren
id|list
comma
(paren
r_struct
id|list_head
op_star
)paren
id|head-&gt;prev
)paren
suffix:semicolon
id|head-&gt;qlen
op_add_assign
id|list-&gt;qlen
suffix:semicolon
id|list-&gt;qlen
op_assign
l_int|0
suffix:semicolon
id|sctp_spin_unlock
c_func
(paren
op_amp
id|list-&gt;lock
)paren
suffix:semicolon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|head-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sctp_list_dequeue - remove from the head of the queue&n; *&t;@list: list to dequeue from&n; *&n; *&t;Remove the head of the list. The head item is&n; *&t;returned or %NULL if the list is empty.&n; */
DECL|function|sctp_list_dequeue
r_static
r_inline
r_struct
id|list_head
op_star
id|sctp_list_dequeue
c_func
(paren
r_struct
id|list_head
op_star
id|list
)paren
(brace
r_struct
id|list_head
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;next
op_ne
id|list
)paren
(brace
id|result
op_assign
id|list-&gt;next
suffix:semicolon
id|list-&gt;next
op_assign
id|result-&gt;next
suffix:semicolon
id|list-&gt;next-&gt;prev
op_assign
id|list
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Calculate the size (in bytes) occupied by the data of an iovec.  */
DECL|function|get_user_iov_size
r_static
r_inline
r_int
id|get_user_iov_size
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|iovlen
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|iovlen
OG
l_int|0
suffix:semicolon
op_decrement
id|iovlen
)paren
(brace
id|retval
op_add_assign
id|iov-&gt;iov_len
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Walk through a list of TLV parameters.  Don&squot;t trust the&n; * individual parameter lengths and instead depend on&n; * the chunk length to indicate when to stop.  Make sure&n; * there is room for a param header too.&n; */
DECL|macro|sctp_walk_params
mdefine_line|#define sctp_walk_params(pos, chunk, member)&bslash;&n;_sctp_walk_params((pos), (chunk), ntohs((chunk)-&gt;chunk_hdr.length), member)
DECL|macro|_sctp_walk_params
mdefine_line|#define _sctp_walk_params(pos, chunk, end, member)&bslash;&n;for (pos.v = chunk-&gt;member;&bslash;&n;     pos.v &lt;= (void *)chunk + end - sizeof(sctp_paramhdr_t) &amp;&amp;&bslash;&n;     pos.v &lt;= (void *)chunk + end - WORD_ROUND(ntohs(pos.p-&gt;length)); &bslash;&n;     pos.v += WORD_ROUND(ntohs(pos.p-&gt;length)))
multiline_comment|/* Round an int up to the next multiple of 4.  */
DECL|macro|WORD_ROUND
mdefine_line|#define WORD_ROUND(s) (((s)+3)&amp;~3)
multiline_comment|/* Make a new instance of type.  */
DECL|macro|t_new
mdefine_line|#define t_new(type, flags)&t;(type *)kmalloc(sizeof(type), flags)
multiline_comment|/* Compare two timevals.  */
DECL|macro|tv_lt
mdefine_line|#define tv_lt(s, t) &bslash;&n;   (s.tv_sec &lt; t.tv_sec || (s.tv_sec == t.tv_sec &amp;&amp; s.tv_usec &lt; t.tv_usec))
multiline_comment|/* Stolen from net/profile.h.  Using it from there is more grief than&n; * it is worth.&n; */
DECL|function|tv_add
r_static
r_inline
r_void
id|tv_add
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
)paren
(brace
id|time_t
id|usecs
op_assign
id|leaved-&gt;tv_usec
op_plus
id|entered-&gt;tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|leaved-&gt;tv_sec
op_plus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
op_ge
l_int|1000000
)paren
(brace
id|usecs
op_sub_assign
l_int|1000000
suffix:semicolon
id|secs
op_increment
suffix:semicolon
)brace
id|leaved-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|leaved-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
multiline_comment|/* External references. */
r_extern
r_struct
id|proto
id|sctp_prot
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_net_sctp
suffix:semicolon
r_extern
r_void
id|sctp_put_port
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
multiline_comment|/* Static inline functions. */
multiline_comment|/* Return the SCTP protocol structure. */
DECL|function|sctp_get_protocol
r_static
r_inline
id|sctp_protocol_t
op_star
id|sctp_get_protocol
c_func
(paren
r_void
)paren
(brace
r_return
op_amp
id|sctp_proto
suffix:semicolon
)brace
multiline_comment|/* Convert from an IP version number to an Address Family symbol.  */
DECL|function|ipver2af
r_static
r_inline
r_int
id|ipver2af
c_func
(paren
id|__u8
id|ipver
)paren
(brace
r_int
id|family
suffix:semicolon
r_switch
c_cond
(paren
id|ipver
)paren
(brace
r_case
l_int|4
suffix:colon
id|family
op_assign
id|AF_INET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|family
op_assign
id|AF_INET6
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|family
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|family
suffix:semicolon
)brace
multiline_comment|/* Warning: The following hash functions assume a power of two &squot;size&squot;. */
multiline_comment|/* This is the hash function for the SCTP port hash table. */
DECL|function|sctp_phashfn
r_static
r_inline
r_int
id|sctp_phashfn
c_func
(paren
id|__u16
id|lport
)paren
(brace
id|sctp_protocol_t
op_star
id|sctp_proto
op_assign
id|sctp_get_protocol
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|lport
op_amp
(paren
id|sctp_proto-&gt;port_hashsize
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This is the hash function for the endpoint hash table. */
DECL|function|sctp_ep_hashfn
r_static
r_inline
r_int
id|sctp_ep_hashfn
c_func
(paren
id|__u16
id|lport
)paren
(brace
id|sctp_protocol_t
op_star
id|sctp_proto
op_assign
id|sctp_get_protocol
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|lport
op_amp
(paren
id|sctp_proto-&gt;ep_hashsize
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This is the hash function for the association hash table. */
DECL|function|sctp_assoc_hashfn
r_static
r_inline
r_int
id|sctp_assoc_hashfn
c_func
(paren
id|__u16
id|lport
comma
id|__u16
id|rport
)paren
(brace
id|sctp_protocol_t
op_star
id|sctp_proto
op_assign
id|sctp_get_protocol
c_func
(paren
)paren
suffix:semicolon
r_int
id|h
op_assign
(paren
id|lport
op_lshift
l_int|16
)paren
op_plus
id|rport
suffix:semicolon
id|h
op_xor_assign
id|h
op_rshift
l_int|8
suffix:semicolon
r_return
(paren
id|h
op_amp
(paren
id|sctp_proto-&gt;assoc_hashsize
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This is the hash function for the association hash table.  This is&n; * not used yet, but could be used as a better hash function when&n; * we have a vtag.&n; */
DECL|function|sctp_vtag_hashfn
r_static
r_inline
r_int
id|sctp_vtag_hashfn
c_func
(paren
id|__u16
id|lport
comma
id|__u16
id|rport
comma
id|__u32
id|vtag
)paren
(brace
id|sctp_protocol_t
op_star
id|sctp_proto
op_assign
id|sctp_get_protocol
c_func
(paren
)paren
suffix:semicolon
r_int
id|h
op_assign
(paren
id|lport
op_lshift
l_int|16
)paren
op_plus
id|rport
suffix:semicolon
id|h
op_xor_assign
id|vtag
suffix:semicolon
r_return
(paren
id|h
op_amp
(paren
id|sctp_proto-&gt;assoc_hashsize
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* WARNING: Do not change the layout of the members in sctp_sock! */
DECL|struct|sctp_sock
r_struct
id|sctp_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
macro_line|#endif /* CONFIG_IPV6 || CONFIG_IPV6_MODULE */
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
DECL|member|sctp
r_struct
id|sctp_opt
id|sctp
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
DECL|struct|sctp6_sock
r_struct
id|sctp6_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
DECL|member|sctp
r_struct
id|sctp_opt
id|sctp
suffix:semicolon
DECL|member|inet6
r_struct
id|ipv6_pinfo
id|inet6
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_IPV6 || CONFIG_IPV6_MODULE */
DECL|macro|sctp_sk
mdefine_line|#define sctp_sk(__sk) (&amp;((struct sctp_sock *)__sk)-&gt;sctp)
macro_line|#endif /* __net_sctp_h__ */
eof
