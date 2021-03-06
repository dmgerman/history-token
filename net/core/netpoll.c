multiline_comment|/*&n; * Common framework for low-level network console, dump, and debugger code&n; *&n; * Sep 8 2003  Matt Mackall &lt;mpm@selenic.com&gt;&n; *&n; * based on the netconsole code from:&n; *&n; * Copyright (C) 2001  Ingo Molnar &lt;mingo@redhat.com&gt;&n; * Copyright (C) 2002  Red Hat, Inc.&n; */
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netpoll.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
multiline_comment|/*&n; * We maintain a small pool of fully-sized skbs, to make sure the&n; * message gets out even in extreme OOM situations.&n; */
DECL|macro|MAX_UDP_CHUNK
mdefine_line|#define MAX_UDP_CHUNK 1460
DECL|macro|MAX_SKBS
mdefine_line|#define MAX_SKBS 32
DECL|macro|MAX_QUEUE_DEPTH
mdefine_line|#define MAX_QUEUE_DEPTH (MAX_SKBS / 2)
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|skb_list_lock
)paren
suffix:semicolon
DECL|variable|nr_skbs
r_static
r_int
id|nr_skbs
suffix:semicolon
DECL|variable|skbs
r_static
r_struct
id|sk_buff
op_star
id|skbs
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|queue_lock
)paren
suffix:semicolon
DECL|variable|queue_depth
r_static
r_int
id|queue_depth
suffix:semicolon
DECL|variable|queue_head
DECL|variable|queue_tail
r_static
r_struct
id|sk_buff
op_star
id|queue_head
comma
op_star
id|queue_tail
suffix:semicolon
DECL|variable|trapped
r_static
id|atomic_t
id|trapped
suffix:semicolon
DECL|macro|NETPOLL_RX_ENABLED
mdefine_line|#define NETPOLL_RX_ENABLED  1
DECL|macro|NETPOLL_RX_DROP
mdefine_line|#define NETPOLL_RX_DROP     2
DECL|macro|MAX_SKB_SIZE
mdefine_line|#define MAX_SKB_SIZE &bslash;&n;&t;&t;(MAX_UDP_CHUNK + sizeof(struct udphdr) + &bslash;&n;&t;&t;&t;&t;sizeof(struct iphdr) + sizeof(struct ethhdr))
r_static
r_void
id|zap_completion_queue
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|queue_process
r_static
r_void
id|queue_process
c_func
(paren
r_void
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
id|queue_head
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue_lock
comma
id|flags
)paren
suffix:semicolon
id|skb
op_assign
id|queue_head
suffix:semicolon
id|queue_head
op_assign
id|skb-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
id|queue_tail
)paren
id|queue_head
op_assign
l_int|NULL
suffix:semicolon
id|queue_depth
op_decrement
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue_lock
comma
id|flags
)paren
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
r_static
id|DECLARE_WORK
c_func
(paren
id|send_queue
comma
id|queue_process
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|netpoll_queue
r_void
id|netpoll_queue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|queue_depth
op_eq
id|MAX_QUEUE_DEPTH
)paren
(brace
id|__kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue_head
)paren
id|queue_head
op_assign
id|skb
suffix:semicolon
r_else
id|queue_tail-&gt;next
op_assign
id|skb
suffix:semicolon
id|queue_tail
op_assign
id|skb
suffix:semicolon
id|queue_depth
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue_lock
comma
id|flags
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|send_queue
)paren
suffix:semicolon
)brace
DECL|function|checksum_udp
r_static
r_int
id|checksum_udp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|udphdr
op_star
id|uh
comma
r_int
r_int
id|ulen
comma
id|u32
id|saddr
comma
id|u32
id|daddr
)paren
(brace
r_if
c_cond
(paren
id|uh-&gt;check
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
r_return
id|csum_tcpudp_magic
c_func
(paren
id|saddr
comma
id|daddr
comma
id|ulen
comma
id|IPPROTO_UDP
comma
id|skb-&gt;csum
)paren
suffix:semicolon
id|skb-&gt;csum
op_assign
id|csum_tcpudp_nofold
c_func
(paren
id|saddr
comma
id|daddr
comma
id|ulen
comma
id|IPPROTO_UDP
comma
l_int|0
)paren
suffix:semicolon
r_return
id|csum_fold
c_func
(paren
id|skb_checksum
c_func
(paren
id|skb
comma
l_int|0
comma
id|skb-&gt;len
comma
id|skb-&gt;csum
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether delayed processing was scheduled for our NIC. If so,&n; * we attempt to grab the poll lock and use -&gt;poll() to pump the card.&n; * If this fails, either we&squot;ve recursed in -&gt;poll() or it&squot;s already&n; * running on another CPU.&n; *&n; * Note: we don&squot;t mask interrupts with this lock because we&squot;re using&n; * trylock here and interrupts are already disabled in the softirq&n; * case. Further, we test the poll_owner to avoid recursion on UP&n; * systems where the lock doesn&squot;t exist.&n; *&n; * In cases where there is bi-directional communications, reading only&n; * one message at a time can lead to packets being dropped by the&n; * network adapter, forcing superfluous retries and possibly timeouts.&n; * Thus, we set our budget to greater than 1.&n; */
DECL|function|poll_napi
r_static
r_void
id|poll_napi
c_func
(paren
r_struct
id|netpoll
op_star
id|np
)paren
(brace
r_int
id|budget
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|__LINK_STATE_RX_SCHED
comma
op_amp
id|np-&gt;dev-&gt;state
)paren
op_logical_and
id|np-&gt;poll_owner
op_ne
id|smp_processor_id
c_func
(paren
)paren
op_logical_and
id|spin_trylock
c_func
(paren
op_amp
id|np-&gt;poll_lock
)paren
)paren
(brace
id|np-&gt;rx_flags
op_or_assign
id|NETPOLL_RX_DROP
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|trapped
)paren
suffix:semicolon
id|np-&gt;dev
op_member_access_from_pointer
id|poll
c_func
(paren
id|np-&gt;dev
comma
op_amp
id|budget
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|trapped
)paren
suffix:semicolon
id|np-&gt;rx_flags
op_and_assign
op_complement
id|NETPOLL_RX_DROP
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|np-&gt;poll_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|netpoll_poll
r_void
id|netpoll_poll
c_func
(paren
r_struct
id|netpoll
op_star
id|np
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;dev
op_logical_or
op_logical_neg
id|netif_running
c_func
(paren
id|np-&gt;dev
)paren
op_logical_or
op_logical_neg
id|np-&gt;dev-&gt;poll_controller
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Process pending work on NIC */
id|np-&gt;dev
op_member_access_from_pointer
id|poll_controller
c_func
(paren
id|np-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;dev-&gt;poll
)paren
id|poll_napi
c_func
(paren
id|np
)paren
suffix:semicolon
id|zap_completion_queue
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|refill_skbs
r_static
r_void
id|refill_skbs
c_func
(paren
r_void
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|skb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr_skbs
OL
id|MAX_SKBS
)paren
(brace
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|MAX_SKB_SIZE
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
r_break
suffix:semicolon
id|skb-&gt;next
op_assign
id|skbs
suffix:semicolon
id|skbs
op_assign
id|skb
suffix:semicolon
id|nr_skbs
op_increment
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|skb_list_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|zap_completion_queue
r_static
r_void
id|zap_completion_queue
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|softnet_data
op_star
id|sd
op_assign
op_amp
id|get_cpu_var
c_func
(paren
id|softnet_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sd-&gt;completion_queue
)paren
(brace
r_struct
id|sk_buff
op_star
id|clist
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|clist
op_assign
id|sd-&gt;completion_queue
suffix:semicolon
id|sd-&gt;completion_queue
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|clist
op_ne
l_int|NULL
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|clist
suffix:semicolon
id|clist
op_assign
id|clist-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;destructor
)paren
(brace
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* put this one back */
r_else
id|__kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
id|put_cpu_var
c_func
(paren
id|softnet_data
)paren
suffix:semicolon
)brace
DECL|function|find_skb
r_static
r_struct
id|sk_buff
op_star
id|find_skb
c_func
(paren
r_struct
id|netpoll
op_star
id|np
comma
r_int
id|len
comma
r_int
id|reserve
)paren
(brace
r_int
id|once
op_assign
l_int|1
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
l_int|NULL
suffix:semicolon
id|zap_completion_queue
c_func
(paren
)paren
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
id|nr_skbs
OL
id|MAX_SKBS
)paren
id|refill_skbs
c_func
(paren
)paren
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
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
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|skb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|skb
op_assign
id|skbs
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|skbs
op_assign
id|skb-&gt;next
suffix:semicolon
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|nr_skbs
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|skb_list_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|once
op_logical_and
(paren
id|count
op_eq
l_int|1000000
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;out of netpoll skbs!&bslash;n&quot;
)paren
suffix:semicolon
id|once
op_assign
l_int|0
suffix:semicolon
)brace
id|netpoll_poll
c_func
(paren
id|np
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|skb-&gt;users
comma
l_int|1
)paren
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|reserve
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
DECL|function|netpoll_send_skb
r_static
r_void
id|netpoll_send_skb
c_func
(paren
r_struct
id|netpoll
op_star
id|np
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|status
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|np
op_logical_or
op_logical_neg
id|np-&gt;dev
op_logical_or
op_logical_neg
id|netif_running
c_func
(paren
id|np-&gt;dev
)paren
)paren
(brace
id|__kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* avoid recursion */
r_if
c_cond
(paren
id|np-&gt;poll_owner
op_eq
id|smp_processor_id
c_func
(paren
)paren
op_logical_or
id|np-&gt;dev-&gt;xmit_lock_owner
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|np-&gt;drop
)paren
id|np
op_member_access_from_pointer
id|drop
c_func
(paren
id|skb
)paren
suffix:semicolon
r_else
id|__kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|np-&gt;dev-&gt;xmit_lock
)paren
suffix:semicolon
id|np-&gt;dev-&gt;xmit_lock_owner
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * network drivers do not expect to be called if the queue is&n;&t; * stopped.&n;&t; */
r_if
c_cond
(paren
id|netif_queue_stopped
c_func
(paren
id|np-&gt;dev
)paren
)paren
(brace
id|np-&gt;dev-&gt;xmit_lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|np-&gt;dev-&gt;xmit_lock
)paren
suffix:semicolon
id|netpoll_poll
c_func
(paren
id|np
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|status
op_assign
id|np-&gt;dev
op_member_access_from_pointer
id|hard_start_xmit
c_func
(paren
id|skb
comma
id|np-&gt;dev
)paren
suffix:semicolon
id|np-&gt;dev-&gt;xmit_lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|np-&gt;dev-&gt;xmit_lock
)paren
suffix:semicolon
multiline_comment|/* transmit busy */
r_if
c_cond
(paren
id|status
)paren
(brace
id|netpoll_poll
c_func
(paren
id|np
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
)brace
DECL|function|netpoll_send_udp
r_void
id|netpoll_send_udp
c_func
(paren
r_struct
id|netpoll
op_star
id|np
comma
r_const
r_char
op_star
id|msg
comma
r_int
id|len
)paren
(brace
r_int
id|total_len
comma
id|eth_len
comma
id|ip_len
comma
id|udp_len
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|udphdr
op_star
id|udph
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
id|udp_len
op_assign
id|len
op_plus
r_sizeof
(paren
op_star
id|udph
)paren
suffix:semicolon
id|ip_len
op_assign
id|eth_len
op_assign
id|udp_len
op_plus
r_sizeof
(paren
op_star
id|iph
)paren
suffix:semicolon
id|total_len
op_assign
id|eth_len
op_plus
id|ETH_HLEN
op_plus
id|NET_IP_ALIGN
suffix:semicolon
id|skb
op_assign
id|find_skb
c_func
(paren
id|np
comma
id|total_len
comma
id|total_len
op_minus
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
id|msg
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;len
op_add_assign
id|len
suffix:semicolon
id|udph
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|udph
)paren
)paren
suffix:semicolon
id|udph-&gt;source
op_assign
id|htons
c_func
(paren
id|np-&gt;local_port
)paren
suffix:semicolon
id|udph-&gt;dest
op_assign
id|htons
c_func
(paren
id|np-&gt;remote_port
)paren
suffix:semicolon
id|udph-&gt;len
op_assign
id|htons
c_func
(paren
id|udp_len
)paren
suffix:semicolon
id|udph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|iph
)paren
)paren
suffix:semicolon
multiline_comment|/* iph-&gt;version = 4; iph-&gt;ihl = 5; */
id|put_unaligned
c_func
(paren
l_int|0x45
comma
(paren
r_int
r_char
op_star
)paren
id|iph
)paren
suffix:semicolon
id|iph-&gt;tos
op_assign
l_int|0
suffix:semicolon
id|put_unaligned
c_func
(paren
id|htons
c_func
(paren
id|ip_len
)paren
comma
op_amp
(paren
id|iph-&gt;tot_len
)paren
)paren
suffix:semicolon
id|iph-&gt;id
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;ttl
op_assign
l_int|64
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|IPPROTO_UDP
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|put_unaligned
c_func
(paren
id|htonl
c_func
(paren
id|np-&gt;local_ip
)paren
comma
op_amp
(paren
id|iph-&gt;saddr
)paren
)paren
suffix:semicolon
id|put_unaligned
c_func
(paren
id|htonl
c_func
(paren
id|np-&gt;remote_ip
)paren
comma
op_amp
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
id|ip_fast_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
comma
id|iph-&gt;ihl
)paren
suffix:semicolon
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|ETH_HLEN
)paren
suffix:semicolon
id|eth-&gt;h_proto
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eth-&gt;h_source
comma
id|np-&gt;local_mac
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eth-&gt;h_dest
comma
id|np-&gt;remote_mac
comma
l_int|6
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|np-&gt;dev
suffix:semicolon
id|netpoll_send_skb
c_func
(paren
id|np
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|arp_reply
r_static
r_void
id|arp_reply
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|arphdr
op_star
id|arp
suffix:semicolon
r_int
r_char
op_star
id|arp_ptr
suffix:semicolon
r_int
id|size
comma
id|type
op_assign
id|ARPOP_REPLY
comma
id|ptype
op_assign
id|ETH_P_ARP
suffix:semicolon
id|u32
id|sip
comma
id|tip
suffix:semicolon
r_struct
id|sk_buff
op_star
id|send_skb
suffix:semicolon
r_struct
id|netpoll
op_star
id|np
op_assign
id|skb-&gt;dev-&gt;np
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np
)paren
r_return
suffix:semicolon
multiline_comment|/* No arp on this interface */
r_if
c_cond
(paren
id|skb-&gt;dev-&gt;flags
op_amp
id|IFF_NOARP
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
(paren
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
(paren
l_int|2
op_star
id|skb-&gt;dev-&gt;addr_len
)paren
op_plus
(paren
l_int|2
op_star
r_sizeof
(paren
id|u32
)paren
)paren
)paren
)paren
)paren
r_return
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|arp
op_assign
id|skb-&gt;nh.arph
suffix:semicolon
r_if
c_cond
(paren
(paren
id|arp-&gt;ar_hrd
op_ne
id|htons
c_func
(paren
id|ARPHRD_ETHER
)paren
op_logical_and
id|arp-&gt;ar_hrd
op_ne
id|htons
c_func
(paren
id|ARPHRD_IEEE802
)paren
)paren
op_logical_or
id|arp-&gt;ar_pro
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
op_logical_or
id|arp-&gt;ar_op
op_ne
id|htons
c_func
(paren
id|ARPOP_REQUEST
)paren
)paren
r_return
suffix:semicolon
id|arp_ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
op_plus
id|skb-&gt;dev-&gt;addr_len
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sip
comma
id|arp_ptr
comma
l_int|4
)paren
suffix:semicolon
id|arp_ptr
op_add_assign
l_int|4
op_plus
id|skb-&gt;dev-&gt;addr_len
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tip
comma
id|arp_ptr
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Should we ignore arp? */
r_if
c_cond
(paren
id|tip
op_ne
id|htonl
c_func
(paren
id|np-&gt;local_ip
)paren
op_logical_or
id|LOOPBACK
c_func
(paren
id|tip
)paren
op_logical_or
id|MULTICAST
c_func
(paren
id|tip
)paren
)paren
r_return
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
l_int|2
op_star
(paren
id|skb-&gt;dev-&gt;addr_len
op_plus
l_int|4
)paren
suffix:semicolon
id|send_skb
op_assign
id|find_skb
c_func
(paren
id|np
comma
id|size
op_plus
id|LL_RESERVED_SPACE
c_func
(paren
id|np-&gt;dev
)paren
comma
id|LL_RESERVED_SPACE
c_func
(paren
id|np-&gt;dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|send_skb
)paren
r_return
suffix:semicolon
id|send_skb-&gt;nh.raw
op_assign
id|send_skb-&gt;data
suffix:semicolon
id|arp
op_assign
(paren
r_struct
id|arphdr
op_star
)paren
id|skb_put
c_func
(paren
id|send_skb
comma
id|size
)paren
suffix:semicolon
id|send_skb-&gt;dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|send_skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_ARP
)paren
suffix:semicolon
multiline_comment|/* Fill the device header for the ARP frame */
r_if
c_cond
(paren
id|np-&gt;dev-&gt;hard_header
op_logical_and
id|np-&gt;dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|send_skb
comma
id|skb-&gt;dev
comma
id|ptype
comma
id|np-&gt;remote_mac
comma
id|np-&gt;local_mac
comma
id|send_skb-&gt;len
)paren
OL
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|send_skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Fill out the arp protocol part.&n;&t; *&n;&t; * we only support ethernet device type,&n;&t; * which (according to RFC 1390) should always equal 1 (Ethernet).&n;&t; */
id|arp-&gt;ar_hrd
op_assign
id|htons
c_func
(paren
id|np-&gt;dev-&gt;type
)paren
suffix:semicolon
id|arp-&gt;ar_pro
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|arp-&gt;ar_hln
op_assign
id|np-&gt;dev-&gt;addr_len
suffix:semicolon
id|arp-&gt;ar_pln
op_assign
l_int|4
suffix:semicolon
id|arp-&gt;ar_op
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
id|arp_ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|arp_ptr
comma
id|np-&gt;dev-&gt;dev_addr
comma
id|np-&gt;dev-&gt;addr_len
)paren
suffix:semicolon
id|arp_ptr
op_add_assign
id|np-&gt;dev-&gt;addr_len
suffix:semicolon
id|memcpy
c_func
(paren
id|arp_ptr
comma
op_amp
id|tip
comma
l_int|4
)paren
suffix:semicolon
id|arp_ptr
op_add_assign
l_int|4
suffix:semicolon
id|memcpy
c_func
(paren
id|arp_ptr
comma
id|np-&gt;remote_mac
comma
id|np-&gt;dev-&gt;addr_len
)paren
suffix:semicolon
id|arp_ptr
op_add_assign
id|np-&gt;dev-&gt;addr_len
suffix:semicolon
id|memcpy
c_func
(paren
id|arp_ptr
comma
op_amp
id|sip
comma
l_int|4
)paren
suffix:semicolon
id|netpoll_send_skb
c_func
(paren
id|np
comma
id|send_skb
)paren
suffix:semicolon
)brace
DECL|function|__netpoll_rx
r_int
id|__netpoll_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|proto
comma
id|len
comma
id|ulen
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
suffix:semicolon
r_struct
id|netpoll
op_star
id|np
op_assign
id|skb-&gt;dev-&gt;np
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;rx_hook
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* check if netpoll clients need ARP */
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|__constant_htons
c_func
(paren
id|ETH_P_ARP
)paren
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|trapped
)paren
)paren
(brace
id|arp_reply
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|proto
op_assign
id|ntohs
c_func
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proto
op_ne
id|ETH_P_IP
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|PACKET_OTHERHOST
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|skb_shared
c_func
(paren
id|skb
)paren
)paren
r_goto
id|out
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;ihl
OL
l_int|5
op_logical_or
id|iph-&gt;version
op_ne
l_int|4
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ip_fast_csum
c_func
(paren
(paren
id|u8
op_star
)paren
id|iph
comma
id|iph-&gt;ihl
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|len
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
id|len
op_logical_or
id|len
OL
id|iph-&gt;ihl
op_star
l_int|4
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;protocol
op_ne
id|IPPROTO_UDP
)paren
r_goto
id|out
suffix:semicolon
id|len
op_sub_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
op_plus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|ulen
op_assign
id|ntohs
c_func
(paren
id|uh-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ulen
op_ne
id|len
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|checksum_udp
c_func
(paren
id|skb
comma
id|uh
comma
id|ulen
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;local_ip
op_logical_and
id|np-&gt;local_ip
op_ne
id|ntohl
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;remote_ip
op_logical_and
id|np-&gt;remote_ip
op_ne
id|ntohl
c_func
(paren
id|iph-&gt;saddr
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;local_port
op_logical_and
id|np-&gt;local_port
op_ne
id|ntohs
c_func
(paren
id|uh-&gt;dest
)paren
)paren
r_goto
id|out
suffix:semicolon
id|np
op_member_access_from_pointer
id|rx_hook
c_func
(paren
id|np
comma
id|ntohs
c_func
(paren
id|uh-&gt;source
)paren
comma
(paren
r_char
op_star
)paren
(paren
id|uh
op_plus
l_int|1
)paren
comma
id|ulen
op_minus
r_sizeof
(paren
r_struct
id|udphdr
)paren
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
id|out
suffix:colon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|trapped
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netpoll_parse_options
r_int
id|netpoll_parse_options
c_func
(paren
r_struct
id|netpoll
op_star
id|np
comma
r_char
op_star
id|opt
)paren
(brace
r_char
op_star
id|cur
op_assign
id|opt
comma
op_star
id|delim
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_ne
l_char|&squot;@&squot;
)paren
(brace
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;@&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;local_port
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|cur
op_assign
id|delim
suffix:semicolon
)brace
id|cur
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: local port %d&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;local_port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;/&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;local_ip
op_assign
id|ntohl
c_func
(paren
id|in_aton
c_func
(paren
id|cur
)paren
)paren
suffix:semicolon
id|cur
op_assign
id|delim
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: local IP %d.%d.%d.%d&bslash;n&quot;
comma
id|np-&gt;name
comma
id|HIPQUAD
c_func
(paren
id|np-&gt;local_ip
)paren
)paren
suffix:semicolon
)brace
id|cur
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_ne
l_char|&squot;,&squot;
)paren
(brace
multiline_comment|/* parse out dev name */
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;,&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|strlcpy
c_func
(paren
id|np-&gt;dev_name
comma
id|cur
comma
r_sizeof
(paren
id|np-&gt;dev_name
)paren
)paren
suffix:semicolon
id|cur
op_assign
id|delim
suffix:semicolon
)brace
id|cur
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: interface %s&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;dev_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_ne
l_char|&squot;@&squot;
)paren
(brace
multiline_comment|/* dst port */
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;@&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_port
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|cur
op_assign
id|delim
suffix:semicolon
)brace
id|cur
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: remote port %d&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;remote_port
)paren
suffix:semicolon
multiline_comment|/* dst ip */
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;/&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_ip
op_assign
id|ntohl
c_func
(paren
id|in_aton
c_func
(paren
id|cur
)paren
)paren
suffix:semicolon
id|cur
op_assign
id|delim
op_plus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: remote IP %d.%d.%d.%d&bslash;n&quot;
comma
id|np-&gt;name
comma
id|HIPQUAD
c_func
(paren
id|np-&gt;remote_ip
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_ne
l_int|0
)paren
(brace
multiline_comment|/* MAC address */
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_mac
(braket
l_int|0
)braket
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|cur
op_assign
id|delim
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_mac
(braket
l_int|1
)braket
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|cur
op_assign
id|delim
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_mac
(braket
l_int|2
)braket
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|cur
op_assign
id|delim
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_mac
(braket
l_int|3
)braket
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|cur
op_assign
id|delim
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|delim
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|parse_failed
suffix:semicolon
op_star
id|delim
op_assign
l_int|0
suffix:semicolon
id|np-&gt;remote_mac
(braket
l_int|4
)braket
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|cur
op_assign
id|delim
op_plus
l_int|1
suffix:semicolon
id|np-&gt;remote_mac
(braket
l_int|5
)braket
op_assign
id|simple_strtol
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: remote ethernet address &quot;
l_string|&quot;%02x:%02x:%02x:%02x:%02x:%02x&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;remote_mac
(braket
l_int|0
)braket
comma
id|np-&gt;remote_mac
(braket
l_int|1
)braket
comma
id|np-&gt;remote_mac
(braket
l_int|2
)braket
comma
id|np-&gt;remote_mac
(braket
l_int|3
)braket
comma
id|np-&gt;remote_mac
(braket
l_int|4
)braket
comma
id|np-&gt;remote_mac
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|parse_failed
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: couldn&squot;t parse config at %s!&bslash;n&quot;
comma
id|np-&gt;name
comma
id|cur
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|netpoll_setup
r_int
id|netpoll_setup
c_func
(paren
r_struct
id|netpoll
op_star
id|np
)paren
(brace
r_struct
id|net_device
op_star
id|ndev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
id|np-&gt;poll_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|np-&gt;poll_owner
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;dev_name
)paren
id|ndev
op_assign
id|dev_get_by_name
c_func
(paren
id|np-&gt;dev_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ndev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: %s doesn&squot;t exist, aborting.&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;dev_name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|np-&gt;dev
op_assign
id|ndev
suffix:semicolon
id|ndev-&gt;np
op_assign
id|np
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ndev-&gt;poll_controller
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: %s doesn&squot;t support polling, aborting.&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;dev_name
)paren
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|netif_running
c_func
(paren
id|ndev
)paren
)paren
(brace
r_int
r_int
id|atmost
comma
id|atleast
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: device %s not up yet, forcing it&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;dev_name
)paren
suffix:semicolon
id|rtnl_shlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_change_flags
c_func
(paren
id|ndev
comma
id|ndev-&gt;flags
op_or
id|IFF_UP
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to open %s&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;dev_name
)paren
suffix:semicolon
id|rtnl_shunlock
c_func
(paren
)paren
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
id|rtnl_shunlock
c_func
(paren
)paren
suffix:semicolon
id|atleast
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|atmost
op_assign
id|jiffies
op_plus
l_int|4
op_star
id|HZ
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|netif_carrier_ok
c_func
(paren
id|ndev
)paren
)paren
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|atmost
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: timeout waiting for carrier&bslash;n&quot;
comma
id|np-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* If carrier appears to come up instantly, we don&squot;t&n;&t;&t; * trust it and pause so that we don&squot;t pump all our&n;&t;&t; * queued console messages into the bitbucket.&n;&t;&t; */
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|atleast
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: carrier detect appears&quot;
l_string|&quot; untrustworthy, waiting 4 seconds&bslash;n&quot;
comma
id|np-&gt;name
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|4000
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|np-&gt;local_mac
comma
l_string|&quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
comma
l_int|6
)paren
op_logical_and
id|ndev-&gt;dev_addr
)paren
id|memcpy
c_func
(paren
id|np-&gt;local_mac
comma
id|ndev-&gt;dev_addr
comma
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;local_ip
)paren
(brace
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|in_dev
op_assign
id|__in_dev_get
c_func
(paren
id|ndev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_dev
op_logical_or
op_logical_neg
id|in_dev-&gt;ifa_list
)paren
(brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no IP address for %s, aborting&bslash;n&quot;
comma
id|np-&gt;name
comma
id|np-&gt;dev_name
)paren
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
id|np-&gt;local_ip
op_assign
id|ntohl
c_func
(paren
id|in_dev-&gt;ifa_list-&gt;ifa_local
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: local IP %d.%d.%d.%d&bslash;n&quot;
comma
id|np-&gt;name
comma
id|HIPQUAD
c_func
(paren
id|np-&gt;local_ip
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rx_hook
)paren
(brace
id|np-&gt;rx_flags
op_assign
id|NETPOLL_RX_ENABLED
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|release
suffix:colon
id|ndev-&gt;np
op_assign
l_int|NULL
suffix:semicolon
id|np-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|dev_put
c_func
(paren
id|ndev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|netpoll_cleanup
r_void
id|netpoll_cleanup
c_func
(paren
r_struct
id|netpoll
op_star
id|np
)paren
(brace
r_if
c_cond
(paren
id|np-&gt;dev
)paren
id|np-&gt;dev-&gt;np
op_assign
l_int|NULL
suffix:semicolon
id|dev_put
c_func
(paren
id|np-&gt;dev
)paren
suffix:semicolon
id|np-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|netpoll_trap
r_int
id|netpoll_trap
c_func
(paren
r_void
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|trapped
)paren
suffix:semicolon
)brace
DECL|function|netpoll_set_trap
r_void
id|netpoll_set_trap
c_func
(paren
r_int
id|trap
)paren
(brace
r_if
c_cond
(paren
id|trap
)paren
id|atomic_inc
c_func
(paren
op_amp
id|trapped
)paren
suffix:semicolon
r_else
id|atomic_dec
c_func
(paren
op_amp
id|trapped
)paren
suffix:semicolon
)brace
DECL|variable|netpoll_set_trap
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_set_trap
)paren
suffix:semicolon
DECL|variable|netpoll_trap
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_trap
)paren
suffix:semicolon
DECL|variable|netpoll_parse_options
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_parse_options
)paren
suffix:semicolon
DECL|variable|netpoll_setup
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_setup
)paren
suffix:semicolon
DECL|variable|netpoll_cleanup
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_cleanup
)paren
suffix:semicolon
DECL|variable|netpoll_send_udp
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_send_udp
)paren
suffix:semicolon
DECL|variable|netpoll_poll
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_poll
)paren
suffix:semicolon
DECL|variable|netpoll_queue
id|EXPORT_SYMBOL
c_func
(paren
id|netpoll_queue
)paren
suffix:semicolon
eof
