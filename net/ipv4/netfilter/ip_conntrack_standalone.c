multiline_comment|/* This file contains all the functions required for the standalone&n;   ip_conntrack module.&n;&n;   These are not required by the compatibility layer.&n;*/
multiline_comment|/* (c) 1999 Paul `Rusty&squot; Russell.  Licenced under the GNU General&n;   Public Licence. */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_conntrack_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_conntrack_lock)
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|kill_proto
r_static
r_int
id|kill_proto
c_func
(paren
r_const
r_struct
id|ip_conntrack
op_star
id|i
comma
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|i-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.protonum
op_eq
op_star
(paren
(paren
id|u_int8_t
op_star
)paren
id|data
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|print_tuple
id|print_tuple
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_struct
id|ip_conntrack_protocol
op_star
id|proto
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;src=%u.%u.%u.%u dst=%u.%u.%u.%u &quot;
comma
id|NIPQUAD
c_func
(paren
id|tuple-&gt;src.ip
)paren
comma
id|NIPQUAD
c_func
(paren
id|tuple-&gt;dst.ip
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|proto
op_member_access_from_pointer
id|print_tuple
c_func
(paren
id|buffer
op_plus
id|len
comma
id|tuple
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* FIXME: Don&squot;t print source proto part. --RR */
r_static
r_int
r_int
DECL|function|print_expect
id|print_expect
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack_expect
op_star
id|expect
)paren
(brace
r_int
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|expect-&gt;expectant-&gt;helper-&gt;timeout
)paren
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;EXPECTING: %lu &quot;
comma
id|timer_pending
c_func
(paren
op_amp
id|expect-&gt;timeout
)paren
ques
c_cond
(paren
id|expect-&gt;timeout.expires
op_minus
id|jiffies
)paren
op_div
id|HZ
suffix:colon
l_int|0
)paren
suffix:semicolon
r_else
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;EXPECTING: - &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;use=%u proto=%u &quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|expect-&gt;use
)paren
comma
id|expect-&gt;tuple.dst.protonum
)paren
suffix:semicolon
id|len
op_add_assign
id|print_tuple
c_func
(paren
id|buffer
op_plus
id|len
comma
op_amp
id|expect-&gt;tuple
comma
id|__ip_ct_find_proto
c_func
(paren
id|expect-&gt;tuple.dst.protonum
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|print_conntrack
id|print_conntrack
c_func
(paren
r_char
op_star
id|buffer
comma
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
(brace
r_int
r_int
id|len
suffix:semicolon
r_struct
id|ip_conntrack_protocol
op_star
id|proto
op_assign
id|__ip_ct_find_proto
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.protonum
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-8s %u %lu &quot;
comma
id|proto-&gt;name
comma
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.protonum
comma
id|timer_pending
c_func
(paren
op_amp
id|conntrack-&gt;timeout
)paren
ques
c_cond
(paren
id|conntrack-&gt;timeout.expires
op_minus
id|jiffies
)paren
op_div
id|HZ
suffix:colon
l_int|0
)paren
suffix:semicolon
id|len
op_add_assign
id|proto
op_member_access_from_pointer
id|print_conntrack
c_func
(paren
id|buffer
op_plus
id|len
comma
id|conntrack
)paren
suffix:semicolon
id|len
op_add_assign
id|print_tuple
c_func
(paren
id|buffer
op_plus
id|len
comma
op_amp
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple
comma
id|proto
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|test_bit
c_func
(paren
id|IPS_SEEN_REPLY_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
)paren
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;[UNREPLIED] &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|print_tuple
c_func
(paren
id|buffer
op_plus
id|len
comma
op_amp
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
comma
id|proto
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IPS_ASSURED_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;[ASSURED] &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;use=%u &quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|conntrack-&gt;ct_general.use
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* Returns true when finished. */
r_static
r_inline
r_int
DECL|function|conntrack_iterate
id|conntrack_iterate
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple_hash
op_star
id|hash
comma
r_char
op_star
id|buffer
comma
id|off_t
id|offset
comma
id|off_t
op_star
id|upto
comma
r_int
r_int
op_star
id|len
comma
r_int
r_int
id|maxlen
)paren
(brace
r_int
r_int
id|newlen
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|hash-&gt;ctrack
)paren
suffix:semicolon
id|MUST_BE_READ_LOCKED
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* Only count originals */
r_if
c_cond
(paren
id|DIRECTION
c_func
(paren
id|hash
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|upto
)paren
op_increment
OL
id|offset
)paren
r_return
l_int|0
suffix:semicolon
id|newlen
op_assign
id|print_conntrack
c_func
(paren
id|buffer
op_plus
op_star
id|len
comma
id|hash-&gt;ctrack
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|len
op_plus
id|newlen
OG
id|maxlen
)paren
r_return
l_int|1
suffix:semicolon
r_else
op_star
id|len
op_add_assign
id|newlen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|list_conntracks
id|list_conntracks
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
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|upto
op_assign
l_int|0
suffix:semicolon
r_struct
id|list_head
op_star
id|e
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* Traverse hash; print originals then reply. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ip_conntrack_htable_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|LIST_FIND
c_func
(paren
op_amp
id|ip_conntrack_hash
(braket
id|i
)braket
comma
id|conntrack_iterate
comma
r_struct
id|ip_conntrack_tuple_hash
op_star
comma
id|buffer
comma
id|offset
comma
op_amp
id|upto
comma
op_amp
id|len
comma
id|length
)paren
)paren
r_goto
id|finished
suffix:semicolon
)brace
multiline_comment|/* Now iterate through expecteds. */
r_for
c_loop
(paren
id|e
op_assign
id|ip_conntrack_expect_list.next
suffix:semicolon
id|e
op_ne
op_amp
id|ip_conntrack_expect_list
suffix:semicolon
id|e
op_assign
id|e-&gt;next
)paren
(brace
r_int
r_int
id|last_len
suffix:semicolon
r_struct
id|ip_conntrack_expect
op_star
id|expect
op_assign
(paren
r_struct
id|ip_conntrack_expect
op_star
)paren
id|e
suffix:semicolon
r_if
c_cond
(paren
id|upto
op_increment
OL
id|offset
)paren
r_continue
suffix:semicolon
id|last_len
op_assign
id|len
suffix:semicolon
id|len
op_add_assign
id|print_expect
c_func
(paren
id|buffer
op_plus
id|len
comma
id|expect
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|last_len
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
)brace
id|finished
suffix:colon
id|READ_UNLOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* `start&squot; hack - see fs/proc/generic.c line ~165 */
op_star
id|start
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|upto
op_minus
id|offset
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|ip_confirm
r_static
r_int
r_int
id|ip_confirm
c_func
(paren
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
multiline_comment|/* We&squot;ve seen it coming out the other side: confirm it */
r_return
id|ip_conntrack_confirm
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
)brace
DECL|function|ip_refrag
r_static
r_int
r_int
id|ip_refrag
c_func
(paren
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
r_struct
id|rtable
op_star
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
suffix:semicolon
multiline_comment|/* We&squot;ve seen it coming out the other side: confirm */
r_if
c_cond
(paren
id|ip_confirm
c_func
(paren
id|hooknum
comma
id|pskb
comma
id|in
comma
id|out
comma
id|okfn
)paren
op_ne
id|NF_ACCEPT
)paren
r_return
id|NF_DROP
suffix:semicolon
multiline_comment|/* Local packets are never produced too large for their&n;&t;   interface.  We degfragment them at LOCAL_OUT, however,&n;&t;   so we have to refragment them here. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
OG
id|dst_pmtu
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
)paren
(brace
multiline_comment|/* No hook can be after us, so this should be OK. */
id|ip_fragment
c_func
(paren
op_star
id|pskb
comma
id|okfn
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|function|ip_conntrack_local
r_static
r_int
r_int
id|ip_conntrack_local
c_func
(paren
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
multiline_comment|/* root is playing with raw sockets. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;ipt_hook: happy cracking.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_return
id|ip_conntrack_in
c_func
(paren
id|hooknum
comma
id|pskb
comma
id|in
comma
id|out
comma
id|okfn
)paren
suffix:semicolon
)brace
multiline_comment|/* Connection tracking may drop packets, but never alters them, so&n;   make it the first hook. */
DECL|variable|ip_conntrack_in_ops
r_static
r_struct
id|nf_hook_ops
id|ip_conntrack_in_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_conntrack_in
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_PRE_ROUTING
comma
dot
id|priority
op_assign
id|NF_IP_PRI_CONNTRACK
comma
)brace
suffix:semicolon
DECL|variable|ip_conntrack_local_out_ops
r_static
r_struct
id|nf_hook_ops
id|ip_conntrack_local_out_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_conntrack_local
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_LOCAL_OUT
comma
dot
id|priority
op_assign
id|NF_IP_PRI_CONNTRACK
comma
)brace
suffix:semicolon
multiline_comment|/* Refragmenter; last chance. */
DECL|variable|ip_conntrack_out_ops
r_static
r_struct
id|nf_hook_ops
id|ip_conntrack_out_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_refrag
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_POST_ROUTING
comma
dot
id|priority
op_assign
id|NF_IP_PRI_LAST
comma
)brace
suffix:semicolon
DECL|variable|ip_conntrack_local_in_ops
r_static
r_struct
id|nf_hook_ops
id|ip_conntrack_local_in_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_confirm
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_LOCAL_IN
comma
dot
id|priority
op_assign
id|NF_IP_PRI_LAST
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|init_or_cleanup
r_static
r_int
id|init_or_cleanup
c_func
(paren
r_int
id|init
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init
)paren
r_goto
id|cleanup
suffix:semicolon
id|ret
op_assign
id|ip_conntrack_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|cleanup_nothing
suffix:semicolon
id|proc
op_assign
id|proc_net_create
c_func
(paren
l_string|&quot;ip_conntrack&quot;
comma
l_int|0
comma
id|list_conntracks
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc
)paren
r_goto
id|cleanup_init
suffix:semicolon
id|proc-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_conntrack_in_ops
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
id|printk
c_func
(paren
l_string|&quot;ip_conntrack: can&squot;t register pre-routing hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_proc
suffix:semicolon
)brace
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_conntrack_local_out_ops
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
id|printk
c_func
(paren
l_string|&quot;ip_conntrack: can&squot;t register local out hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_inops
suffix:semicolon
)brace
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_conntrack_out_ops
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
id|printk
c_func
(paren
l_string|&quot;ip_conntrack: can&squot;t register post-routing hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_inandlocalops
suffix:semicolon
)brace
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_conntrack_local_in_ops
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
id|printk
c_func
(paren
l_string|&quot;ip_conntrack: can&squot;t register local in hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_inoutandlocalops
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
id|cleanup
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_conntrack_local_in_ops
)paren
suffix:semicolon
id|cleanup_inoutandlocalops
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_conntrack_out_ops
)paren
suffix:semicolon
id|cleanup_inandlocalops
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_conntrack_local_out_ops
)paren
suffix:semicolon
id|cleanup_inops
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_conntrack_in_ops
)paren
suffix:semicolon
id|cleanup_proc
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;ip_conntrack&quot;
)paren
suffix:semicolon
id|cleanup_init
suffix:colon
id|ip_conntrack_cleanup
c_func
(paren
)paren
suffix:semicolon
id|cleanup_nothing
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* FIXME: Allow NULL functions and sub in pointers to generic for&n;   them. --RR */
DECL|function|ip_conntrack_protocol_register
r_int
id|ip_conntrack_protocol_register
c_func
(paren
r_struct
id|ip_conntrack_protocol
op_star
id|proto
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|list_head
op_star
id|i
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|protocol_list.next
suffix:semicolon
id|i
op_ne
op_amp
id|protocol_list
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_struct
id|ip_conntrack_protocol
op_star
)paren
id|i
)paren
op_member_access_from_pointer
id|proto
op_eq
id|proto-&gt;proto
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|list_prepend
c_func
(paren
op_amp
id|protocol_list
comma
id|proto
)paren
suffix:semicolon
id|out
suffix:colon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ip_conntrack_protocol_unregister
r_void
id|ip_conntrack_protocol_unregister
c_func
(paren
r_struct
id|ip_conntrack_protocol
op_star
id|proto
)paren
(brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* ip_ct_find_proto() returns proto_generic in case there is no protocol &n;&t; * helper. So this should be enough - HW */
id|LIST_DELETE
c_func
(paren
op_amp
id|protocol_list
comma
id|proto
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* Somebody could be still looking at the proto in bh. */
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Remove all contrack entries for this protocol */
id|ip_ct_selective_cleanup
c_func
(paren
id|kill_proto
comma
op_amp
id|proto-&gt;proto
)paren
suffix:semicolon
)brace
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|init_or_cleanup
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|init_or_cleanup
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
multiline_comment|/* Some modules need us, but don&squot;t depend directly on any symbol.&n;   They should call this. */
DECL|function|need_ip_conntrack
r_void
id|need_ip_conntrack
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|ip_conntrack_protocol_register
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_protocol_register
)paren
suffix:semicolon
DECL|variable|ip_conntrack_protocol_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_protocol_unregister
)paren
suffix:semicolon
DECL|variable|invert_tuplepr
id|EXPORT_SYMBOL
c_func
(paren
id|invert_tuplepr
)paren
suffix:semicolon
DECL|variable|ip_conntrack_alter_reply
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_alter_reply
)paren
suffix:semicolon
DECL|variable|ip_conntrack_destroyed
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_destroyed
)paren
suffix:semicolon
DECL|variable|ip_conntrack_get
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_get
)paren
suffix:semicolon
DECL|variable|need_ip_conntrack
id|EXPORT_SYMBOL
c_func
(paren
id|need_ip_conntrack
)paren
suffix:semicolon
DECL|variable|ip_conntrack_helper_register
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_helper_register
)paren
suffix:semicolon
DECL|variable|ip_conntrack_helper_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_helper_unregister
)paren
suffix:semicolon
DECL|variable|ip_ct_selective_cleanup
id|EXPORT_SYMBOL
c_func
(paren
id|ip_ct_selective_cleanup
)paren
suffix:semicolon
DECL|variable|ip_ct_refresh
id|EXPORT_SYMBOL
c_func
(paren
id|ip_ct_refresh
)paren
suffix:semicolon
DECL|variable|ip_ct_find_proto
id|EXPORT_SYMBOL
c_func
(paren
id|ip_ct_find_proto
)paren
suffix:semicolon
DECL|variable|__ip_ct_find_proto
id|EXPORT_SYMBOL
c_func
(paren
id|__ip_ct_find_proto
)paren
suffix:semicolon
DECL|variable|ip_ct_find_helper
id|EXPORT_SYMBOL
c_func
(paren
id|ip_ct_find_helper
)paren
suffix:semicolon
DECL|variable|ip_conntrack_expect_related
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_expect_related
)paren
suffix:semicolon
DECL|variable|ip_conntrack_change_expect
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_change_expect
)paren
suffix:semicolon
DECL|variable|ip_conntrack_unexpect_related
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_unexpect_related
)paren
suffix:semicolon
DECL|variable|ip_conntrack_expect_find_get
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ip_conntrack_expect_find_get
)paren
suffix:semicolon
DECL|variable|ip_conntrack_expect_put
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ip_conntrack_expect_put
)paren
suffix:semicolon
DECL|variable|ip_conntrack_tuple_taken
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_tuple_taken
)paren
suffix:semicolon
DECL|variable|ip_ct_gather_frags
id|EXPORT_SYMBOL
c_func
(paren
id|ip_ct_gather_frags
)paren
suffix:semicolon
DECL|variable|ip_conntrack_htable_size
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_htable_size
)paren
suffix:semicolon
DECL|variable|ip_conntrack_expect_list
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_expect_list
)paren
suffix:semicolon
DECL|variable|ip_conntrack_lock
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_lock
)paren
suffix:semicolon
DECL|variable|ip_conntrack_hash
id|EXPORT_SYMBOL
c_func
(paren
id|ip_conntrack_hash
)paren
suffix:semicolon
DECL|variable|ip_conntrack_find_get
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ip_conntrack_find_get
)paren
suffix:semicolon
DECL|variable|ip_conntrack_put
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ip_conntrack_put
)paren
suffix:semicolon
eof
