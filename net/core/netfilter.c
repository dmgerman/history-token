multiline_comment|/* netfilter.c: look after the filters for various protocols. &n; * Heavily influenced by the old firewall.c by David Bonn and Alan Cox.&n; *&n; * Thanks to Rob `CmdrTaco&squot; Malda for not influencing this code in any&n; * way.&n; *&n; * Rusty Russell (C)2000 -- This code is GPL.&n; *&n; * February 2000: Modified by James Morris to have 1 queue per protocol.&n; * 15-Mar-2000:   Added NF_REPEAT --RR.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
multiline_comment|/* In this code, we can be waiting indefinitely for userspace to&n; * service a packet if a hook returns NF_QUEUE.  We could keep a count&n; * of skbuffs queued for userspace, and not deregister a hook unless&n; * this is zero, but that sucks.  Now, we simply check when the&n; * packets come back: if the hook is gone, the packet is discarded. */
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|macro|NFDEBUG
mdefine_line|#define NFDEBUG(format, args...)  printk(format , ## args)
macro_line|#else
DECL|macro|NFDEBUG
mdefine_line|#define NFDEBUG(format, args...)
macro_line|#endif
multiline_comment|/* Sockopts only registered and called from user context, so&n;   BR_NETPROTO_LOCK would be overkill.  Also, [gs]etsockopt calls may&n;   sleep. */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|nf_sockopt_mutex
)paren
suffix:semicolon
DECL|variable|nf_hooks
r_struct
id|list_head
id|nf_hooks
(braket
id|NPROTO
)braket
(braket
id|NF_MAX_HOOKS
)braket
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|nf_sockopts
)paren
suffix:semicolon
multiline_comment|/* &n; * A queue handler may be registered for each protocol.  Each is protected by&n; * long term mutex.  The handler must provide an an outfn() to accept packets&n; * for queueing and must reinject all packets it receives, no matter what.&n; */
DECL|struct|nf_queue_handler_t
r_static
r_struct
id|nf_queue_handler_t
(brace
DECL|member|outfn
id|nf_queue_outfn_t
id|outfn
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|variable|queue_handler
)brace
id|queue_handler
(braket
id|NPROTO
)braket
suffix:semicolon
DECL|function|nf_register_hook
r_int
id|nf_register_hook
c_func
(paren
r_struct
id|nf_hook_ops
op_star
id|reg
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_hooks
(braket
id|reg-&gt;pf
)braket
(braket
id|reg-&gt;hooknum
)braket
dot
id|next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_hooks
(braket
id|reg-&gt;pf
)braket
(braket
id|reg-&gt;hooknum
)braket
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|reg-&gt;priority
OL
(paren
(paren
r_struct
id|nf_hook_ops
op_star
)paren
id|i
)paren
op_member_access_from_pointer
id|priority
)paren
r_break
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|reg-&gt;list
comma
id|i-&gt;prev
)paren
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nf_unregister_hook
r_void
id|nf_unregister_hook
c_func
(paren
r_struct
id|nf_hook_ops
op_star
id|reg
)paren
(brace
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|reg-&gt;list
)paren
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
)brace
multiline_comment|/* Do exclusive ranges overlap? */
DECL|function|overlap
r_static
r_inline
r_int
id|overlap
c_func
(paren
r_int
id|min1
comma
r_int
id|max1
comma
r_int
id|min2
comma
r_int
id|max2
)paren
(brace
r_return
id|max1
OG
id|min2
op_logical_and
id|min1
OL
id|max2
suffix:semicolon
)brace
multiline_comment|/* Functions to register sockopt ranges (exclusive). */
DECL|function|nf_register_sockopt
r_int
id|nf_register_sockopt
c_func
(paren
r_struct
id|nf_sockopt_ops
op_star
id|reg
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_sockopts.next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_sockopts
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_struct
id|nf_sockopt_ops
op_star
id|ops
op_assign
(paren
r_struct
id|nf_sockopt_ops
op_star
)paren
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;pf
op_eq
id|reg-&gt;pf
op_logical_and
(paren
id|overlap
c_func
(paren
id|ops-&gt;set_optmin
comma
id|ops-&gt;set_optmax
comma
id|reg-&gt;set_optmin
comma
id|reg-&gt;set_optmax
)paren
op_logical_or
id|overlap
c_func
(paren
id|ops-&gt;get_optmin
comma
id|ops-&gt;get_optmax
comma
id|reg-&gt;get_optmin
comma
id|reg-&gt;get_optmax
)paren
)paren
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_sock overlap: %u-%u/%u-%u v %u-%u/%u-%u&bslash;n&quot;
comma
id|ops-&gt;set_optmin
comma
id|ops-&gt;set_optmax
comma
id|ops-&gt;get_optmin
comma
id|ops-&gt;get_optmax
comma
id|reg-&gt;set_optmin
comma
id|reg-&gt;set_optmax
comma
id|reg-&gt;get_optmin
comma
id|reg-&gt;get_optmax
)paren
suffix:semicolon
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
id|list_add
c_func
(paren
op_amp
id|reg-&gt;list
comma
op_amp
id|nf_sockopts
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|nf_unregister_sockopt
r_void
id|nf_unregister_sockopt
c_func
(paren
r_struct
id|nf_sockopt_ops
op_star
id|reg
)paren
(brace
multiline_comment|/* No point being interruptible: we&squot;re probably in cleanup_module() */
id|restart
suffix:colon
id|down
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;use
op_ne
l_int|0
)paren
(brace
multiline_comment|/* To be woken by nf_sockopt call... */
multiline_comment|/* FIXME: Stuart Young&squot;s name appears gratuitously. */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|reg-&gt;cleanup_task
op_assign
id|current
suffix:semicolon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|reg-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
DECL|function|debug_print_hooks_ip
r_static
r_void
id|debug_print_hooks_ip
c_func
(paren
r_int
r_int
id|nf_debug
)paren
(brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PRE_ROUTING &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LOCAL_IN &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FORWARD &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LOCAL_OUT &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;POST_ROUTING &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
)paren
id|printk
c_func
(paren
l_string|&quot;Crap bits: 0x%04X&quot;
comma
id|nf_debug
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|nf_dump_skb
r_void
id|nf_dump_skb
c_func
(paren
r_int
id|pf
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;skb: pf=%i %s dev=%s len=%u&bslash;n&quot;
comma
id|pf
comma
id|skb-&gt;sk
ques
c_cond
l_string|&quot;(owned)&quot;
suffix:colon
l_string|&quot;(unowned)&quot;
comma
id|skb-&gt;dev
ques
c_cond
id|skb-&gt;dev-&gt;name
suffix:colon
l_string|&quot;(no dev)&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pf
)paren
(brace
r_case
id|PF_INET
suffix:colon
(brace
r_const
r_struct
id|iphdr
op_star
id|ip
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|__u32
op_star
id|opt
op_assign
(paren
id|__u32
op_star
)paren
(paren
id|ip
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|opti
suffix:semicolon
id|__u16
id|src_port
op_assign
l_int|0
comma
id|dst_port
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;protocol
op_eq
id|IPPROTO_TCP
op_logical_or
id|ip-&gt;protocol
op_eq
id|IPPROTO_UDP
)paren
(brace
r_struct
id|tcphdr
op_star
id|tcp
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|__u32
op_star
)paren
id|ip
op_plus
id|ip-&gt;ihl
)paren
suffix:semicolon
id|src_port
op_assign
id|ntohs
c_func
(paren
id|tcp-&gt;source
)paren
suffix:semicolon
id|dst_port
op_assign
id|ntohs
c_func
(paren
id|tcp-&gt;dest
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PROTO=%d %u.%u.%u.%u:%hu %u.%u.%u.%u:%hu&quot;
l_string|&quot; L=%hu S=0x%2.2hX I=%hu F=0x%4.4hX T=%hu&quot;
comma
id|ip-&gt;protocol
comma
id|NIPQUAD
c_func
(paren
id|ip-&gt;saddr
)paren
comma
id|src_port
comma
id|NIPQUAD
c_func
(paren
id|ip-&gt;daddr
)paren
comma
id|dst_port
comma
id|ntohs
c_func
(paren
id|ip-&gt;tot_len
)paren
comma
id|ip-&gt;tos
comma
id|ntohs
c_func
(paren
id|ip-&gt;id
)paren
comma
id|ntohs
c_func
(paren
id|ip-&gt;frag_off
)paren
comma
id|ip-&gt;ttl
)paren
suffix:semicolon
r_for
c_loop
(paren
id|opti
op_assign
l_int|0
suffix:semicolon
id|opti
OL
(paren
id|ip-&gt;ihl
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|opti
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; O=0x%8.8X&quot;
comma
op_star
id|opt
op_increment
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|nf_debug_ip_local_deliver
r_void
id|nf_debug_ip_local_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/* If it&squot;s a loopback packet, it must have come through&n;&t; * NF_IP_LOCAL_OUT, NF_IP_RAW_INPUT, NF_IP_PRE_ROUTING and&n;&t; * NF_IP_LOCAL_IN.  Otherwise, must have gone through&n;&t; * NF_IP_RAW_INPUT and NF_IP_PRE_ROUTING.  */
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;dev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_local_deliver: skb-&gt;dev is NULL.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|skb-&gt;dev-&gt;name
comma
l_string|&quot;lo&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_local_deliver: bad loopback skb: &quot;
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_local_deliver: bad non-lo skb: &quot;
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|nf_debug_ip_loopback_xmit
r_void
id|nf_debug_ip_loopback_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|newskb
)paren
(brace
r_if
c_cond
(paren
id|newskb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_dev_loopback_xmit: bad owned skb = %p: &quot;
comma
id|newskb
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|newskb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|newskb
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear to avoid confusing input check */
id|newskb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|nf_debug_ip_finish_output2
r_void
id|nf_debug_ip_finish_output2
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/* If it&squot;s owned, it must have gone through the&n;&t; * NF_IP_LOCAL_OUT and NF_IP_POST_ROUTING.&n;&t; * Otherwise, must have gone through&n;&t; * NF_IP_PRE_ROUTING, NF_IP_FORWARD and NF_IP_POST_ROUTING.&n;&t; */
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_finish_output: bad owned skb = %p: &quot;
comma
id|skb
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
)paren
(brace
multiline_comment|/* Fragments, entunnelled packets, TCP RSTs&n;                           generated by ipt_REJECT will have no&n;                           owners, but still may be local */
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_finish_output:&quot;
l_string|&quot; bad unowned skb = %p: &quot;
comma
id|skb
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#endif /*CONFIG_NETFILTER_DEBUG*/
multiline_comment|/* Call get/setsockopt() */
DECL|function|nf_sockopt
r_static
r_int
id|nf_sockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|pf
comma
r_int
id|val
comma
r_char
op_star
id|opt
comma
r_int
op_star
id|len
comma
r_int
id|get
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
r_struct
id|nf_sockopt_ops
op_star
id|ops
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_sockopts.next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_sockopts
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
id|ops
op_assign
(paren
r_struct
id|nf_sockopt_ops
op_star
)paren
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;pf
op_eq
id|pf
)paren
(brace
r_if
c_cond
(paren
id|get
)paren
(brace
r_if
c_cond
(paren
id|val
op_ge
id|ops-&gt;get_optmin
op_logical_and
id|val
OL
id|ops-&gt;get_optmax
)paren
(brace
id|ops-&gt;use
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|get
c_func
(paren
id|sk
comma
id|val
comma
id|opt
comma
id|len
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|val
op_ge
id|ops-&gt;set_optmin
op_logical_and
id|val
OL
id|ops-&gt;set_optmax
)paren
(brace
id|ops-&gt;use
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|set
c_func
(paren
id|sk
comma
id|val
comma
id|opt
comma
op_star
id|len
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
)brace
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
id|out
suffix:colon
id|down
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
id|ops-&gt;use
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;cleanup_task
)paren
id|wake_up_process
c_func
(paren
id|ops-&gt;cleanup_task
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|nf_setsockopt
r_int
id|nf_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|pf
comma
r_int
id|val
comma
r_char
op_star
id|opt
comma
r_int
id|len
)paren
(brace
r_return
id|nf_sockopt
c_func
(paren
id|sk
comma
id|pf
comma
id|val
comma
id|opt
comma
op_amp
id|len
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|nf_getsockopt
r_int
id|nf_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|pf
comma
r_int
id|val
comma
r_char
op_star
id|opt
comma
r_int
op_star
id|len
)paren
(brace
r_return
id|nf_sockopt
c_func
(paren
id|sk
comma
id|pf
comma
id|val
comma
id|opt
comma
id|len
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|nf_iterate
r_static
r_int
r_int
id|nf_iterate
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_int
id|hook
comma
r_const
r_struct
id|net_device
op_star
id|indev
comma
r_const
r_struct
id|net_device
op_star
id|outdev
comma
r_struct
id|list_head
op_star
op_star
id|i
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
comma
r_int
id|hook_thresh
)paren
(brace
r_for
c_loop
(paren
op_star
id|i
op_assign
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
op_star
id|i
op_ne
id|head
suffix:semicolon
op_star
id|i
op_assign
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_struct
id|nf_hook_ops
op_star
id|elem
op_assign
(paren
r_struct
id|nf_hook_ops
op_star
)paren
op_star
id|i
suffix:semicolon
r_if
c_cond
(paren
id|hook_thresh
OG
id|elem-&gt;priority
)paren
r_continue
suffix:semicolon
multiline_comment|/* Optimization: we don&squot;t need to hold module&n;                   reference here, since function can&squot;t sleep. --RR */
r_switch
c_cond
(paren
id|elem
op_member_access_from_pointer
id|hook
c_func
(paren
id|hook
comma
id|skb
comma
id|indev
comma
id|outdev
comma
id|okfn
)paren
)paren
(brace
r_case
id|NF_QUEUE
suffix:colon
r_return
id|NF_QUEUE
suffix:semicolon
r_case
id|NF_STOLEN
suffix:colon
r_return
id|NF_STOLEN
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
r_return
id|NF_DROP
suffix:semicolon
r_case
id|NF_REPEAT
suffix:colon
op_star
id|i
op_assign
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|prev
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_case
id|NF_ACCEPT
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|NFDEBUG
c_func
(paren
l_string|&quot;Evil return from %p(%u).&bslash;n&quot;
comma
id|elem-&gt;hook
comma
id|hook
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|function|nf_register_queue_handler
r_int
id|nf_register_queue_handler
c_func
(paren
r_int
id|pf
comma
id|nf_queue_outfn_t
id|outfn
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|ret
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_handler
(braket
id|pf
)braket
dot
id|outfn
)paren
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_else
(brace
id|queue_handler
(braket
id|pf
)braket
dot
id|outfn
op_assign
id|outfn
suffix:semicolon
id|queue_handler
(braket
id|pf
)braket
dot
id|data
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* The caller must flush their queue before this */
DECL|function|nf_unregister_queue_handler
r_int
id|nf_unregister_queue_handler
c_func
(paren
r_int
id|pf
)paren
(brace
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|queue_handler
(braket
id|pf
)braket
dot
id|outfn
op_assign
l_int|NULL
suffix:semicolon
id|queue_handler
(braket
id|pf
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Any packet that leaves via this function must come back &n; * through nf_reinject().&n; */
DECL|function|nf_queue
r_static
r_int
id|nf_queue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|list_head
op_star
id|elem
comma
r_int
id|pf
comma
r_int
r_int
id|hook
comma
r_struct
id|net_device
op_star
id|indev
comma
r_struct
id|net_device
op_star
id|outdev
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
r_int
id|status
suffix:semicolon
r_struct
id|nf_info
op_star
id|info
suffix:semicolon
macro_line|#if defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE)
r_struct
id|net_device
op_star
id|physindev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|net_device
op_star
id|physoutdev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
multiline_comment|/* QUEUE == DROP if noone is waiting, to be safe. */
r_if
c_cond
(paren
op_logical_neg
id|queue_handler
(braket
id|pf
)braket
dot
id|outfn
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
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
id|KERN_ERR
l_string|&quot;OOM queueing packet %p&bslash;n&quot;
comma
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
op_star
id|info
op_assign
(paren
r_struct
id|nf_info
)paren
(brace
(paren
r_struct
id|nf_hook_ops
op_star
)paren
id|elem
comma
id|pf
comma
id|hook
comma
id|indev
comma
id|outdev
comma
id|okfn
)brace
suffix:semicolon
multiline_comment|/* If it&squot;s going away, ignore hook. */
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|info-&gt;elem-&gt;owner
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Bump dev refs so they don&squot;t vanish while packet is out */
r_if
c_cond
(paren
id|indev
)paren
id|dev_hold
c_func
(paren
id|indev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|outdev
)paren
id|dev_hold
c_func
(paren
id|outdev
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE)
r_if
c_cond
(paren
id|skb-&gt;nf_bridge
)paren
(brace
id|physindev
op_assign
id|skb-&gt;nf_bridge-&gt;physindev
suffix:semicolon
r_if
c_cond
(paren
id|physindev
)paren
id|dev_hold
c_func
(paren
id|physindev
)paren
suffix:semicolon
id|physoutdev
op_assign
id|skb-&gt;nf_bridge-&gt;physoutdev
suffix:semicolon
r_if
c_cond
(paren
id|physoutdev
)paren
id|dev_hold
c_func
(paren
id|physoutdev
)paren
suffix:semicolon
)brace
macro_line|#endif
id|status
op_assign
id|queue_handler
(braket
id|pf
)braket
dot
id|outfn
c_func
(paren
id|skb
comma
id|info
comma
id|queue_handler
(braket
id|pf
)braket
dot
id|data
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
multiline_comment|/* James M doesn&squot;t say fuck enough. */
r_if
c_cond
(paren
id|indev
)paren
id|dev_put
c_func
(paren
id|indev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|outdev
)paren
id|dev_put
c_func
(paren
id|outdev
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE)
r_if
c_cond
(paren
id|physindev
)paren
id|dev_put
c_func
(paren
id|physindev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|physoutdev
)paren
id|dev_put
c_func
(paren
id|physoutdev
)paren
suffix:semicolon
macro_line|#endif
id|module_put
c_func
(paren
id|info-&gt;elem-&gt;owner
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|nf_hook_slow
r_int
id|nf_hook_slow
c_func
(paren
r_int
id|pf
comma
r_int
r_int
id|hook
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|indev
comma
r_struct
id|net_device
op_star
id|outdev
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
comma
r_int
id|hook_thresh
)paren
(brace
r_struct
id|list_head
op_star
id|elem
suffix:semicolon
r_int
r_int
id|verdict
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
(brace
r_if
c_cond
(paren
id|outdev
op_eq
l_int|NULL
)paren
(brace
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
r_else
(brace
id|skb_checksum_help
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* We may already have this, but read-locks nest anyway */
id|br_read_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_amp
(paren
l_int|1
op_lshift
id|hook
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nf_hook: hook %i already set.&bslash;n&quot;
comma
id|hook
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|pf
comma
id|skb
)paren
suffix:semicolon
)brace
id|skb-&gt;nf_debug
op_or_assign
(paren
l_int|1
op_lshift
id|hook
)paren
suffix:semicolon
macro_line|#endif
id|elem
op_assign
op_amp
id|nf_hooks
(braket
id|pf
)braket
(braket
id|hook
)braket
suffix:semicolon
id|next_hook
suffix:colon
id|verdict
op_assign
id|nf_iterate
c_func
(paren
op_amp
id|nf_hooks
(braket
id|pf
)braket
(braket
id|hook
)braket
comma
op_amp
id|skb
comma
id|hook
comma
id|indev
comma
id|outdev
comma
op_amp
id|elem
comma
id|okfn
comma
id|hook_thresh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verdict
op_eq
id|NF_QUEUE
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: Verdict = QUEUE.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nf_queue
c_func
(paren
id|skb
comma
id|elem
comma
id|pf
comma
id|hook
comma
id|indev
comma
id|outdev
comma
id|okfn
)paren
)paren
r_goto
id|next_hook
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|verdict
)paren
(brace
r_case
id|NF_ACCEPT
suffix:colon
id|ret
op_assign
id|okfn
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|br_read_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|nf_reinject
r_void
id|nf_reinject
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
r_int
r_int
id|verdict
)paren
(brace
r_struct
id|list_head
op_star
id|elem
op_assign
op_amp
id|info-&gt;elem-&gt;list
suffix:semicolon
r_struct
id|list_head
op_star
id|i
suffix:semicolon
multiline_comment|/* We don&squot;t have BR_NETPROTO_LOCK here */
id|br_read_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
multiline_comment|/* Drop reference to owner of hook which queued us. */
id|module_put
c_func
(paren
id|info-&gt;elem-&gt;owner
)paren
suffix:semicolon
multiline_comment|/* Continue traversal iff userspace said ok... */
r_if
c_cond
(paren
id|verdict
op_eq
id|NF_REPEAT
)paren
(brace
id|elem
op_assign
id|elem-&gt;prev
suffix:semicolon
id|verdict
op_assign
id|NF_ACCEPT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verdict
op_eq
id|NF_ACCEPT
)paren
(brace
id|next_hook
suffix:colon
id|verdict
op_assign
id|nf_iterate
c_func
(paren
op_amp
id|nf_hooks
(braket
id|info-&gt;pf
)braket
(braket
id|info-&gt;hook
)braket
comma
op_amp
id|skb
comma
id|info-&gt;hook
comma
id|info-&gt;indev
comma
id|info-&gt;outdev
comma
op_amp
id|elem
comma
id|info-&gt;okfn
comma
id|INT_MIN
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|verdict
)paren
(brace
r_case
id|NF_ACCEPT
suffix:colon
id|info
op_member_access_from_pointer
id|okfn
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_QUEUE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|nf_queue
c_func
(paren
id|skb
comma
id|elem
comma
id|info-&gt;pf
comma
id|info-&gt;hook
comma
id|info-&gt;indev
comma
id|info-&gt;outdev
comma
id|info-&gt;okfn
)paren
)paren
r_goto
id|next_hook
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|br_read_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
multiline_comment|/* Release those devices we held, or Alexey will kill me. */
r_if
c_cond
(paren
id|info-&gt;indev
)paren
id|dev_put
c_func
(paren
id|info-&gt;indev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;outdev
)paren
id|dev_put
c_func
(paren
id|info-&gt;outdev
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE)
r_if
c_cond
(paren
id|skb-&gt;nf_bridge
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_bridge-&gt;physindev
)paren
id|dev_put
c_func
(paren
id|skb-&gt;nf_bridge-&gt;physindev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;nf_bridge-&gt;physoutdev
)paren
id|dev_put
c_func
(paren
id|skb-&gt;nf_bridge-&gt;physoutdev
)paren
suffix:semicolon
)brace
macro_line|#endif
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_INET
multiline_comment|/* route_me_harder function, used by iptable_nat, iptable_mangle + ip_queue */
DECL|function|ip_route_me_harder
r_int
id|ip_route_me_harder
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
id|iph-&gt;daddr
comma
dot
id|saddr
op_assign
id|iph-&gt;saddr
comma
dot
id|tos
op_assign
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
dot
id|fwmark
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
macro_line|#endif
)brace
)brace
comma
dot
id|oif
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
ques
c_cond
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk-&gt;bound_dev_if
suffix:colon
l_int|0
comma
)brace
suffix:semicolon
r_struct
id|net_device
op_star
id|dev_src
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* accommodate ip_route_output_slow(), which expects the key src to be&n;&t;   0 or a local address; however some non-standard hacks like&n;&t;   ipt_REJECT.c:send_reset() can cause packets with foreign&n;           saddr to be appear on the NF_IP_LOCAL_OUT hook -MB */
r_if
c_cond
(paren
id|fl.fl4_src
op_logical_and
op_logical_neg
(paren
id|dev_src
op_assign
id|ip_dev_find
c_func
(paren
id|fl.fl4_src
)paren
)paren
)paren
(brace
id|fl.fl4_src
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|fl
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;route_me_harder: ip_route_output_key(dst=%u.%u.%u.%u, src=%u.%u.%u.%u, oif=%d, tos=0x%x, fwmark=0x%lx) error %d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
ques
c_cond
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk-&gt;bound_dev_if
suffix:colon
l_int|0
comma
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
comma
macro_line|#else
l_int|0UL
comma
macro_line|#endif
id|err
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Drop old route. */
id|dst_release
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
)paren
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* Change in oif may mean change in hh_len. */
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
op_star
id|pskb
)paren
OL
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst-&gt;dev-&gt;hard_header_len
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
id|nskb
op_assign
id|skb_realloc_headroom
c_func
(paren
op_star
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst-&gt;dev-&gt;hard_header_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
)paren
id|skb_set_owner_w
c_func
(paren
id|nskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
op_star
id|pskb
op_assign
id|nskb
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|dev_src
)paren
id|dev_put
c_func
(paren
id|dev_src
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_INET*/
multiline_comment|/* This does not belong here, but ipt_REJECT needs it if connection&n;   tracking in use: without this, connection may not be in hash table,&n;   and hence manufactured ICMP or RST packets will not be associated&n;   with it. */
DECL|variable|ip_ct_attach
r_void
(paren
op_star
id|ip_ct_attach
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|nf_ct_info
op_star
)paren
suffix:semicolon
DECL|function|netfilter_init
r_void
id|__init
id|netfilter_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|h
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
id|NPROTO
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|NF_MAX_HOOKS
suffix:semicolon
id|h
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|nf_hooks
(braket
id|i
)braket
(braket
id|h
)braket
)paren
suffix:semicolon
)brace
)brace
eof
