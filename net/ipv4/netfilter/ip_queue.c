multiline_comment|/*&n; * This is a module which is used for queueing IPv4 packets and&n; * communicating with userspace via netlink.&n; *&n; * (C) 2000-2002 James Morris, this code is GPL.&n; *&n; * 2000-03-27: Simplified code (thanks to Andi Kleen for clues).&n; * 2000-05-20: Fixed notifier problems (following Miguel Freitas&squot; report).&n; * 2000-06-19: Fixed so nfmark is copied to metadata (reported by Sebastian &n; *             Zander).&n; * 2000-08-01: Added Nick Williams&squot; MAC support.&n; * 2002-06-25: Code cleanup.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_queue.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/route.h&gt;
DECL|macro|IPQ_QMAX_DEFAULT
mdefine_line|#define IPQ_QMAX_DEFAULT 1024
DECL|macro|IPQ_PROC_FS_NAME
mdefine_line|#define IPQ_PROC_FS_NAME &quot;ip_queue&quot;
DECL|macro|NET_IPQ_QMAX
mdefine_line|#define NET_IPQ_QMAX 2088
DECL|macro|NET_IPQ_QMAX_NAME
mdefine_line|#define NET_IPQ_QMAX_NAME &quot;ip_queue_maxlen&quot;
DECL|struct|ipq_rt_info
r_struct
id|ipq_rt_info
(brace
DECL|member|tos
id|__u8
id|tos
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipq_queue_entry
r_struct
id|ipq_queue_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|info
r_struct
id|nf_info
op_star
id|info
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|rt_info
r_struct
id|ipq_rt_info
id|rt_info
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|ipq_cmpfn
r_typedef
r_int
(paren
op_star
id|ipq_cmpfn
)paren
(paren
r_struct
id|ipq_queue_entry
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|copy_mode
r_static
r_int
r_char
id|copy_mode
op_assign
id|IPQ_COPY_NONE
suffix:semicolon
DECL|variable|queue_maxlen
r_static
r_int
r_int
id|queue_maxlen
op_assign
id|IPQ_QMAX_DEFAULT
suffix:semicolon
DECL|variable|queue_lock
r_static
id|rwlock_t
id|queue_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|peer_pid
r_static
r_int
id|peer_pid
suffix:semicolon
DECL|variable|copy_range
r_static
r_int
r_int
id|copy_range
suffix:semicolon
DECL|variable|queue_total
r_static
r_int
r_int
id|queue_total
suffix:semicolon
DECL|variable|ipqnl
r_static
r_struct
id|sock
op_star
id|ipqnl
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|queue_list
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|ipqnl_sem
)paren
suffix:semicolon
r_static
r_void
DECL|function|ipq_issue_verdict
id|ipq_issue_verdict
c_func
(paren
r_struct
id|ipq_queue_entry
op_star
id|entry
comma
r_int
id|verdict
)paren
(brace
id|nf_reinject
c_func
(paren
id|entry-&gt;skb
comma
id|entry-&gt;info
comma
id|verdict
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ipq_enqueue_entry
id|__ipq_enqueue_entry
c_func
(paren
r_struct
id|ipq_queue_entry
op_star
id|entry
)paren
(brace
r_if
c_cond
(paren
id|queue_total
op_ge
id|queue_maxlen
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
id|KERN_WARNING
l_string|&quot;ip_queue: full at %d entries, &quot;
l_string|&quot;dropping packet(s).&bslash;n&quot;
comma
id|queue_total
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|entry-&gt;list
comma
op_amp
id|queue_list
)paren
suffix:semicolon
id|queue_total
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find and return a queued entry matched by cmpfn, or return the last&n; * entry if cmpfn is NULL.&n; */
r_static
r_inline
r_struct
id|ipq_queue_entry
op_star
DECL|function|__ipq_find_entry
id|__ipq_find_entry
c_func
(paren
id|ipq_cmpfn
id|cmpfn
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|list_for_each_prev
c_func
(paren
id|p
comma
op_amp
id|queue_list
)paren
(brace
r_struct
id|ipq_queue_entry
op_star
id|entry
op_assign
(paren
r_struct
id|ipq_queue_entry
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmpfn
op_logical_or
id|cmpfn
c_func
(paren
id|entry
comma
id|data
)paren
)paren
r_return
id|entry
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ipq_dequeue_entry
id|__ipq_dequeue_entry
c_func
(paren
r_struct
id|ipq_queue_entry
op_star
id|entry
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|entry-&gt;list
)paren
suffix:semicolon
id|queue_total
op_decrement
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|ipq_queue_entry
op_star
DECL|function|__ipq_find_dequeue_entry
id|__ipq_find_dequeue_entry
c_func
(paren
id|ipq_cmpfn
id|cmpfn
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|ipq_queue_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|__ipq_find_entry
c_func
(paren
id|cmpfn
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|__ipq_dequeue_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ipq_flush
id|__ipq_flush
c_func
(paren
r_int
id|verdict
)paren
(brace
r_struct
id|ipq_queue_entry
op_star
id|entry
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|__ipq_find_dequeue_entry
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
)paren
)paren
id|ipq_issue_verdict
c_func
(paren
id|entry
comma
id|verdict
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ipq_set_mode
id|__ipq_set_mode
c_func
(paren
r_int
r_char
id|mode
comma
r_int
r_int
id|range
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|IPQ_COPY_NONE
suffix:colon
r_case
id|IPQ_COPY_META
suffix:colon
id|copy_mode
op_assign
id|mode
suffix:semicolon
id|copy_range
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPQ_COPY_PACKET
suffix:colon
id|copy_mode
op_assign
id|mode
suffix:semicolon
id|copy_range
op_assign
id|range
suffix:semicolon
r_if
c_cond
(paren
id|copy_range
OG
l_int|0xFFFF
)paren
id|copy_range
op_assign
l_int|0xFFFF
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ipq_reset
id|__ipq_reset
c_func
(paren
r_void
)paren
(brace
id|peer_pid
op_assign
l_int|0
suffix:semicolon
id|__ipq_set_mode
c_func
(paren
id|IPQ_COPY_NONE
comma
l_int|0
)paren
suffix:semicolon
id|__ipq_flush
c_func
(paren
id|NF_DROP
)paren
suffix:semicolon
)brace
r_static
r_struct
id|ipq_queue_entry
op_star
DECL|function|ipq_find_dequeue_entry
id|ipq_find_dequeue_entry
c_func
(paren
id|ipq_cmpfn
id|cmpfn
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|ipq_queue_entry
op_star
id|entry
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|entry
op_assign
id|__ipq_find_dequeue_entry
c_func
(paren
id|cmpfn
comma
id|data
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
r_static
r_void
DECL|function|ipq_flush
id|ipq_flush
c_func
(paren
r_int
id|verdict
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|__ipq_flush
c_func
(paren
id|verdict
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|ipq_build_packet_message
id|ipq_build_packet_message
c_func
(paren
r_struct
id|ipq_queue_entry
op_star
id|entry
comma
r_int
op_star
id|errp
)paren
(brace
r_int
r_char
op_star
id|old_tail
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_int
id|data_len
op_assign
l_int|0
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|ipq_packet_msg
op_star
id|pmsg
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|copy_mode
)paren
(brace
r_case
id|IPQ_COPY_META
suffix:colon
r_case
id|IPQ_COPY_NONE
suffix:colon
id|size
op_assign
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
op_star
id|pmsg
)paren
)paren
suffix:semicolon
id|data_len
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPQ_COPY_PACKET
suffix:colon
r_if
c_cond
(paren
id|copy_range
op_eq
l_int|0
op_logical_or
id|copy_range
OG
id|entry-&gt;skb-&gt;len
)paren
id|data_len
op_assign
id|entry-&gt;skb-&gt;len
suffix:semicolon
r_else
id|data_len
op_assign
id|copy_range
suffix:semicolon
id|size
op_assign
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
op_star
id|pmsg
)paren
op_plus
id|data_len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|errp
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|nlmsg_failure
suffix:semicolon
id|old_tail
op_assign
id|skb-&gt;tail
suffix:semicolon
id|nlh
op_assign
id|NLMSG_PUT
c_func
(paren
id|skb
comma
l_int|0
comma
l_int|0
comma
id|IPQM_PACKET
comma
id|size
op_minus
r_sizeof
(paren
op_star
id|nlh
)paren
)paren
suffix:semicolon
id|pmsg
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pmsg
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pmsg
)paren
)paren
suffix:semicolon
id|pmsg-&gt;packet_id
op_assign
(paren
r_int
r_int
)paren
id|entry
suffix:semicolon
id|pmsg-&gt;data_len
op_assign
id|data_len
suffix:semicolon
id|pmsg-&gt;timestamp_sec
op_assign
id|entry-&gt;skb-&gt;stamp.tv_sec
suffix:semicolon
id|pmsg-&gt;timestamp_usec
op_assign
id|entry-&gt;skb-&gt;stamp.tv_usec
suffix:semicolon
id|pmsg-&gt;mark
op_assign
id|entry-&gt;skb-&gt;nfmark
suffix:semicolon
id|pmsg-&gt;hook
op_assign
id|entry-&gt;info-&gt;hook
suffix:semicolon
id|pmsg-&gt;hw_protocol
op_assign
id|entry-&gt;skb-&gt;protocol
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;info-&gt;indev
)paren
id|strcpy
c_func
(paren
id|pmsg-&gt;indev_name
comma
id|entry-&gt;info-&gt;indev-&gt;name
)paren
suffix:semicolon
r_else
id|pmsg-&gt;indev_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;info-&gt;outdev
)paren
id|strcpy
c_func
(paren
id|pmsg-&gt;outdev_name
comma
id|entry-&gt;info-&gt;outdev-&gt;name
)paren
suffix:semicolon
r_else
id|pmsg-&gt;outdev_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;info-&gt;indev
op_logical_and
id|entry-&gt;skb-&gt;dev
)paren
(brace
id|pmsg-&gt;hw_type
op_assign
id|entry-&gt;skb-&gt;dev-&gt;type
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;skb-&gt;dev-&gt;hard_header_parse
)paren
id|pmsg-&gt;hw_addrlen
op_assign
id|entry-&gt;skb-&gt;dev
op_member_access_from_pointer
id|hard_header_parse
c_func
(paren
id|entry-&gt;skb
comma
id|pmsg-&gt;hw_addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data_len
)paren
id|memcpy
c_func
(paren
id|pmsg-&gt;payload
comma
id|entry-&gt;skb-&gt;data
comma
id|data_len
)paren
suffix:semicolon
id|nlh-&gt;nlmsg_len
op_assign
id|skb-&gt;tail
op_minus
id|old_tail
suffix:semicolon
r_return
id|skb
suffix:semicolon
id|nlmsg_failure
suffix:colon
r_if
c_cond
(paren
id|skb
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
op_star
id|errp
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ip_queue: error creating packet message&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipq_enqueue_packet
id|ipq_enqueue_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nf_info
op_star
id|info
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
r_struct
id|ipq_queue_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|copy_mode
op_eq
id|IPQ_COPY_NONE
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ip_queue: OOM in ipq_enqueue_packet()&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|entry-&gt;info
op_assign
id|info
suffix:semicolon
id|entry-&gt;skb
op_assign
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;info-&gt;hook
op_eq
id|NF_IP_LOCAL_OUT
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|entry-&gt;rt_info.tos
op_assign
id|iph-&gt;tos
suffix:semicolon
id|entry-&gt;rt_info.daddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|entry-&gt;rt_info.saddr
op_assign
id|iph-&gt;saddr
suffix:semicolon
)brace
id|nskb
op_assign
id|ipq_build_packet_message
c_func
(paren
id|entry
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nskb
op_eq
l_int|NULL
)paren
r_goto
id|err_out_free
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|peer_pid
)paren
r_goto
id|err_out_unlock
suffix:semicolon
id|status
op_assign
id|netlink_unicast
c_func
(paren
id|ipqnl
comma
id|nskb
comma
id|peer_pid
comma
id|MSG_DONTWAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_goto
id|err_out_unlock
suffix:semicolon
id|status
op_assign
id|__ipq_enqueue_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_goto
id|err_out_unlock
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
id|err_out_unlock
suffix:colon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|err_out_free
suffix:colon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipq_mangle_ipv4
id|ipq_mangle_ipv4
c_func
(paren
id|ipq_verdict_msg_t
op_star
id|v
comma
r_struct
id|ipq_queue_entry
op_star
id|e
)paren
(brace
r_int
id|diff
suffix:semicolon
r_struct
id|iphdr
op_star
id|user_iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|v-&gt;payload
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;data_len
OL
r_sizeof
(paren
op_star
id|user_iph
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|diff
op_assign
id|v-&gt;data_len
op_minus
id|e-&gt;skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|diff
OL
l_int|0
)paren
id|skb_trim
c_func
(paren
id|e-&gt;skb
comma
id|v-&gt;data_len
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|diff
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|v-&gt;data_len
OG
l_int|0xFFFF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|diff
OG
id|skb_tailroom
c_func
(paren
id|e-&gt;skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|newskb
suffix:semicolon
id|newskb
op_assign
id|skb_copy_expand
c_func
(paren
id|e-&gt;skb
comma
id|skb_headroom
c_func
(paren
id|e-&gt;skb
)paren
comma
id|diff
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newskb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ip_queue: OOM &quot;
l_string|&quot;in mangle, dropping packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|e-&gt;skb-&gt;sk
)paren
id|skb_set_owner_w
c_func
(paren
id|newskb
comma
id|e-&gt;skb-&gt;sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|e-&gt;skb
)paren
suffix:semicolon
id|e-&gt;skb
op_assign
id|newskb
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|e-&gt;skb
comma
id|diff
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|e-&gt;skb-&gt;data
comma
id|v-&gt;payload
comma
id|v-&gt;data_len
)paren
suffix:semicolon
id|e-&gt;skb-&gt;nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
multiline_comment|/*&n;&t; * Extra routing may needed on local out, as the QUEUE target never&n;&t; * returns control to the table.&n;&t; */
r_if
c_cond
(paren
id|e-&gt;info-&gt;hook
op_eq
id|NF_IP_LOCAL_OUT
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|e-&gt;skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iph-&gt;tos
op_eq
id|e-&gt;rt_info.tos
op_logical_and
id|iph-&gt;daddr
op_eq
id|e-&gt;rt_info.daddr
op_logical_and
id|iph-&gt;saddr
op_eq
id|e-&gt;rt_info.saddr
)paren
)paren
r_return
id|ip_route_me_harder
c_func
(paren
op_amp
id|e-&gt;skb
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|id_cmp
id|id_cmp
c_func
(paren
r_struct
id|ipq_queue_entry
op_star
id|e
comma
r_int
r_int
id|id
)paren
(brace
r_return
(paren
id|id
op_eq
(paren
r_int
r_int
)paren
id|e
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipq_set_verdict
id|ipq_set_verdict
c_func
(paren
r_struct
id|ipq_verdict_msg
op_star
id|vmsg
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|ipq_queue_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|vmsg-&gt;value
OG
id|NF_MAX_VERDICT
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|entry
op_assign
id|ipq_find_dequeue_entry
c_func
(paren
id|id_cmp
comma
id|vmsg-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_else
(brace
r_int
id|verdict
op_assign
id|vmsg-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|vmsg-&gt;data_len
op_logical_and
id|vmsg-&gt;data_len
op_eq
id|len
)paren
r_if
c_cond
(paren
id|ipq_mangle_ipv4
c_func
(paren
id|vmsg
comma
id|entry
)paren
OL
l_int|0
)paren
id|verdict
op_assign
id|NF_DROP
suffix:semicolon
id|ipq_issue_verdict
c_func
(paren
id|entry
comma
id|verdict
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|ipq_set_mode
id|ipq_set_mode
c_func
(paren
r_int
r_char
id|mode
comma
r_int
r_int
id|range
)paren
(brace
r_int
id|status
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|status
op_assign
id|__ipq_set_mode
c_func
(paren
id|mode
comma
id|range
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipq_receive_peer
id|ipq_receive_peer
c_func
(paren
r_struct
id|ipq_peer_msg
op_star
id|pmsg
comma
r_int
r_char
id|type
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
op_star
id|pmsg
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|IPQM_MODE
suffix:colon
id|status
op_assign
id|ipq_set_mode
c_func
(paren
id|pmsg-&gt;msg.mode.value
comma
id|pmsg-&gt;msg.mode.range
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPQM_VERDICT
suffix:colon
r_if
c_cond
(paren
id|pmsg-&gt;msg.verdict.value
OG
id|NF_MAX_VERDICT
)paren
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
id|status
op_assign
id|ipq_set_verdict
c_func
(paren
op_amp
id|pmsg-&gt;msg.verdict
comma
id|len
op_minus
r_sizeof
(paren
op_star
id|pmsg
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|dev_cmp
id|dev_cmp
c_func
(paren
r_struct
id|ipq_queue_entry
op_star
id|entry
comma
r_int
r_int
id|ifindex
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;info-&gt;indev
)paren
r_if
c_cond
(paren
id|entry-&gt;info-&gt;indev-&gt;ifindex
op_eq
id|ifindex
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;info-&gt;outdev
)paren
r_if
c_cond
(paren
id|entry-&gt;info-&gt;outdev-&gt;ifindex
op_eq
id|ifindex
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|ipq_dev_drop
id|ipq_dev_drop
c_func
(paren
r_int
id|ifindex
)paren
(brace
r_struct
id|ipq_queue_entry
op_star
id|entry
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|ipq_find_dequeue_entry
c_func
(paren
id|dev_cmp
comma
id|ifindex
)paren
)paren
op_ne
l_int|NULL
)paren
id|ipq_issue_verdict
c_func
(paren
id|entry
comma
id|NF_DROP
)paren
suffix:semicolon
)brace
DECL|macro|RCV_SKB_FAIL
mdefine_line|#define RCV_SKB_FAIL(err) do { netlink_ack(skb, nlh, (err)); return; } while (0)
r_static
r_inline
r_void
DECL|function|ipq_rcv_skb
id|ipq_rcv_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|status
comma
id|type
comma
id|pid
comma
id|flags
comma
id|nlmsglen
comma
id|skblen
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
id|skblen
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|skblen
OL
r_sizeof
(paren
op_star
id|nlh
)paren
)paren
r_return
suffix:semicolon
id|nlh
op_assign
(paren
r_struct
id|nlmsghdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|nlmsglen
op_assign
id|nlh-&gt;nlmsg_len
suffix:semicolon
r_if
c_cond
(paren
id|nlmsglen
OL
r_sizeof
(paren
op_star
id|nlh
)paren
op_logical_or
id|skblen
OL
id|nlmsglen
)paren
r_return
suffix:semicolon
id|pid
op_assign
id|nlh-&gt;nlmsg_pid
suffix:semicolon
id|flags
op_assign
id|nlh-&gt;nlmsg_flags
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_le
l_int|0
op_logical_or
op_logical_neg
(paren
id|flags
op_amp
id|NLM_F_REQUEST
)paren
op_logical_or
id|flags
op_amp
id|NLM_F_MULTI
)paren
(brace
id|RCV_SKB_FAIL
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_TRUNC
)paren
id|RCV_SKB_FAIL
c_func
(paren
op_minus
id|ECOMM
)paren
suffix:semicolon
id|type
op_assign
id|nlh-&gt;nlmsg_type
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
id|NLMSG_NOOP
op_logical_or
id|type
op_ge
id|IPQM_MAX
)paren
id|RCV_SKB_FAIL
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_le
id|IPQM_BASE
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|security_netlink_recv
c_func
(paren
id|skb
)paren
)paren
id|RCV_SKB_FAIL
c_func
(paren
op_minus
id|EPERM
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer_pid
)paren
(brace
r_if
c_cond
(paren
id|peer_pid
op_ne
id|pid
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|RCV_SKB_FAIL
c_func
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
)brace
)brace
r_else
id|peer_pid
op_assign
id|pid
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|status
op_assign
id|ipq_receive_peer
c_func
(paren
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
comma
id|type
comma
id|skblen
op_minus
id|NLMSG_LENGTH
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|RCV_SKB_FAIL
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|NLM_F_ACK
)paren
id|netlink_ack
c_func
(paren
id|skb
comma
id|nlh
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|ipq_rcv_sk
id|ipq_rcv_sk
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
(brace
r_do
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|ipqnl_sem
)paren
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|ipq_rcv_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|ipqnl_sem
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ipqnl
op_logical_and
id|ipqnl-&gt;receive_queue.qlen
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipq_rcv_dev_event
id|ipq_rcv_dev_event
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|ptr
suffix:semicolon
multiline_comment|/* Drop any packets associated with the downed device */
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_DOWN
)paren
id|ipq_dev_drop
c_func
(paren
id|dev-&gt;ifindex
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|ipq_dev_notifier
r_static
r_struct
id|notifier_block
id|ipq_dev_notifier
op_assign
(brace
id|ipq_rcv_dev_event
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
DECL|function|ipq_rcv_nl_event
id|ipq_rcv_nl_event
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
r_struct
id|netlink_notify
op_star
id|n
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
id|NETLINK_URELEASE
op_logical_and
id|n-&gt;protocol
op_eq
id|NETLINK_FIREWALL
op_logical_and
id|n-&gt;pid
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;pid
op_eq
id|peer_pid
)paren
id|__ipq_reset
c_func
(paren
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|ipq_nl_notifier
r_static
r_struct
id|notifier_block
id|ipq_nl_notifier
op_assign
(brace
id|ipq_rcv_nl_event
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|sysctl_maxlen
r_static
r_int
id|sysctl_maxlen
op_assign
id|IPQ_QMAX_DEFAULT
suffix:semicolon
DECL|variable|ipq_sysctl_header
r_static
r_struct
id|ctl_table_header
op_star
id|ipq_sysctl_header
suffix:semicolon
DECL|variable|ipq_table
r_static
id|ctl_table
id|ipq_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IPQ_QMAX
comma
id|NET_IPQ_QMAX_NAME
comma
op_amp
id|sysctl_maxlen
comma
r_sizeof
(paren
id|sysctl_maxlen
)paren
comma
l_int|0644
comma
l_int|NULL
comma
id|proc_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ipq_dir_table
r_static
id|ctl_table
id|ipq_dir_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IPV4
comma
l_string|&quot;ipv4&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipq_table
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ipq_root_table
r_static
id|ctl_table
id|ipq_root_table
(braket
)braket
op_assign
(brace
(brace
id|CTL_NET
comma
l_string|&quot;net&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipq_dir_table
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_static
r_int
DECL|function|ipq_get_info
id|ipq_get_info
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
id|len
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Peer PID          : %d&bslash;n&quot;
l_string|&quot;Copy mode         : %hu&bslash;n&quot;
l_string|&quot;Copy range        : %u&bslash;n&quot;
l_string|&quot;Queue length      : %u&bslash;n&quot;
l_string|&quot;Queue max. length : %u&bslash;n&quot;
comma
id|peer_pid
comma
id|copy_mode
comma
id|copy_range
comma
id|queue_total
comma
id|queue_maxlen
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|queue_lock
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
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
r_else
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|init_or_cleanup
id|init_or_cleanup
c_func
(paren
r_int
id|init
)paren
(brace
r_int
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|proc
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
id|netlink_register_notifier
c_func
(paren
op_amp
id|ipq_nl_notifier
)paren
suffix:semicolon
id|ipqnl
op_assign
id|netlink_kernel_create
c_func
(paren
id|NETLINK_FIREWALL
comma
id|ipq_rcv_sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipqnl
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ip_queue: failed to create netlink socket&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_netlink_notifier
suffix:semicolon
)brace
id|proc
op_assign
id|proc_net_create
c_func
(paren
id|IPQ_PROC_FS_NAME
comma
l_int|0
comma
id|ipq_get_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc
)paren
id|proc-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ip_queue: failed to create proc entry&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_ipqnl
suffix:semicolon
)brace
id|register_netdevice_notifier
c_func
(paren
op_amp
id|ipq_dev_notifier
)paren
suffix:semicolon
id|ipq_sysctl_header
op_assign
id|register_sysctl_table
c_func
(paren
id|ipq_root_table
comma
l_int|0
)paren
suffix:semicolon
id|status
op_assign
id|nf_register_queue_handler
c_func
(paren
id|PF_INET
comma
id|ipq_enqueue_packet
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ip_queue: failed to register queue handler&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_sysctl
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
id|cleanup
suffix:colon
id|nf_unregister_queue_handler
c_func
(paren
id|PF_INET
)paren
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|ipq_flush
c_func
(paren
id|NF_DROP
)paren
suffix:semicolon
id|cleanup_sysctl
suffix:colon
id|unregister_sysctl_table
c_func
(paren
id|ipq_sysctl_header
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|ipq_dev_notifier
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
id|IPQ_PROC_FS_NAME
)paren
suffix:semicolon
id|cleanup_ipqnl
suffix:colon
id|sock_release
c_func
(paren
id|ipqnl-&gt;socket
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ipqnl_sem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ipqnl_sem
)paren
suffix:semicolon
id|cleanup_netlink_notifier
suffix:colon
id|netlink_unregister_notifier
c_func
(paren
op_amp
id|ipq_nl_notifier
)paren
suffix:semicolon
r_return
id|status
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
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv4 packet queue handler&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Morris &lt;jmorris@intercode.com.au&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
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
eof
