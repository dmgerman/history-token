multiline_comment|/*&n; *  TUN - Universal TUN/TAP device driver.&n; *  Copyright (C) 1999-2002 Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *  GNU General Public License for more details.&n; *&n; *  $Id: tun.c,v 1.15 2002/03/01 02:44:24 maxk Exp $&n; */
multiline_comment|/*&n; *  Daniel Podlejski &lt;underley@underley.eu.org&gt;&n; *    Modifications for 2.3.99-pre5 kernel.&n; */
DECL|macro|TUN_VER
mdefine_line|#define TUN_VER &quot;1.5&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_tun.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef TUN_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
macro_line|#endif
multiline_comment|/* Network device part of the driver */
multiline_comment|/* Net device open. */
DECL|function|tun_net_open
r_static
r_int
id|tun_net_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Net device close. */
DECL|function|tun_net_close
r_static
r_int
id|tun_net_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Net device start xmit */
DECL|function|tun_net_xmit
r_static
r_int
id|tun_net_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_net_xmit %d&bslash;n&quot;
comma
id|tun-&gt;name
comma
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* Drop packet if interface is not attached */
r_if
c_cond
(paren
op_logical_neg
id|tun-&gt;attached
)paren
r_goto
id|drop
suffix:semicolon
multiline_comment|/* Queue packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tun-&gt;flags
op_amp
id|TUN_ONE_QUEUE
)paren
)paren
(brace
multiline_comment|/* Normal queueing mode.&n;&t;&t; * Packet scheduler handles dropping. */
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|tun-&gt;readq
)paren
op_ge
id|TUN_READQ_SIZE
)paren
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Single queue mode.&n;&t;&t; * Driver handles dropping itself. */
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|tun-&gt;readq
)paren
op_ge
id|dev-&gt;tx_queue_len
)paren
r_goto
id|drop
suffix:semicolon
)brace
id|skb_queue_tail
c_func
(paren
op_amp
id|tun-&gt;readq
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Notify and wake up reader process */
r_if
c_cond
(paren
id|tun-&gt;flags
op_amp
id|TUN_FASYNC
)paren
id|kill_fasync
c_func
(paren
op_amp
id|tun-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tun-&gt;read_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|drop
suffix:colon
id|tun-&gt;stats.tx_dropped
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tun_net_mclist
r_static
r_void
id|tun_net_mclist
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Nothing to do for multicast filters. &n;&t; * We always accept all frames. */
r_return
suffix:semicolon
)brace
DECL|function|tun_net_stats
r_static
r_struct
id|net_device_stats
op_star
id|tun_net_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|tun-&gt;stats
suffix:semicolon
)brace
multiline_comment|/* Initialize net device. */
DECL|function|tun_net_init
r_int
id|tun_net_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_net_init&bslash;n&quot;
comma
id|tun-&gt;name
)paren
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|tun_net_open
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|tun_net_xmit
suffix:semicolon
id|dev-&gt;stop
op_assign
id|tun_net_close
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|tun_net_stats
suffix:semicolon
r_switch
c_cond
(paren
id|tun-&gt;flags
op_amp
id|TUN_TYPE_MASK
)paren
(brace
r_case
id|TUN_TUN_DEV
suffix:colon
multiline_comment|/* Point-to-Point TUN Device */
id|dev-&gt;hard_header_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
multiline_comment|/* Type PPP seems most suitable */
id|dev-&gt;type
op_assign
id|ARPHRD_PPP
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_POINTOPOINT
op_or
id|IFF_NOARP
op_or
id|IFF_MULTICAST
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUN_TAP_DEV
suffix:colon
multiline_comment|/* Ethernet TAP Device */
id|dev-&gt;set_multicast_list
op_assign
id|tun_net_mclist
suffix:semicolon
multiline_comment|/* Generate random Ethernet address.  */
op_star
(paren
id|u16
op_star
)paren
id|dev-&gt;dev_addr
op_assign
id|htons
c_func
(paren
l_int|0x00FF
)paren
suffix:semicolon
id|get_random_bytes
c_func
(paren
id|dev-&gt;dev_addr
op_plus
r_sizeof
(paren
id|u16
)paren
comma
l_int|4
)paren
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Character device part */
multiline_comment|/* Poll */
DECL|function|tun_chr_poll
r_static
r_int
r_int
id|tun_chr_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tun
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_chr_poll&bslash;n&quot;
comma
id|tun-&gt;name
)paren
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|tun-&gt;read_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|tun-&gt;readq
)paren
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/* Get packet from user space buffer(already verified) */
DECL|function|tun_get_user
r_static
id|__inline__
id|ssize_t
id|tun_get_user
c_func
(paren
r_struct
id|tun_struct
op_star
id|tun
comma
r_struct
id|iovec
op_star
id|iv
comma
r_int
id|count
)paren
(brace
r_struct
id|tun_pi
id|pi
op_assign
(brace
l_int|0
comma
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
)brace
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tun-&gt;flags
op_amp
id|TUN_NO_PI
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
r_sizeof
(paren
id|pi
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy_fromiovec
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|pi
comma
id|iv
comma
r_sizeof
(paren
id|pi
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
op_plus
l_int|2
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|tun-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|memcpy_fromiovec
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|iv
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
op_amp
id|tun-&gt;dev
suffix:semicolon
r_switch
c_cond
(paren
id|tun-&gt;flags
op_amp
id|TUN_TYPE_MASK
)paren
(brace
r_case
id|TUN_TUN_DEV
suffix:colon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|pi.proto
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUN_TAP_DEV
suffix:colon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
op_amp
id|tun-&gt;dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|tun-&gt;flags
op_amp
id|TUN_NOCHECKSUM
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
id|netif_rx_ni
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tun-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|tun-&gt;stats.rx_bytes
op_add_assign
id|len
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* Writev */
DECL|function|tun_chr_writev
r_static
id|ssize_t
id|tun_chr_writev
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|iovec
op_star
id|iv
comma
r_int
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tun
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_chr_write %d&bslash;n&quot;
comma
id|tun-&gt;name
comma
id|count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|iv
(braket
id|i
)braket
dot
id|iov_base
comma
id|iv
(braket
id|i
)braket
dot
id|iov_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|len
op_add_assign
id|iv
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
r_return
id|tun_get_user
c_func
(paren
id|tun
comma
(paren
r_struct
id|iovec
op_star
)paren
id|iv
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* Write */
DECL|function|tun_chr_write
r_static
id|ssize_t
id|tun_chr_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|iovec
id|iv
op_assign
(brace
(paren
r_void
op_star
)paren
id|buf
comma
id|count
)brace
suffix:semicolon
r_return
id|tun_chr_writev
c_func
(paren
id|file
comma
op_amp
id|iv
comma
l_int|1
comma
id|pos
)paren
suffix:semicolon
)brace
multiline_comment|/* Put packet to the user space buffer (already verified) */
DECL|function|tun_put_user
r_static
id|__inline__
id|ssize_t
id|tun_put_user
c_func
(paren
r_struct
id|tun_struct
op_star
id|tun
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|iovec
op_star
id|iv
comma
r_int
id|len
)paren
(brace
r_struct
id|tun_pi
id|pi
op_assign
(brace
l_int|0
comma
id|skb-&gt;protocol
)brace
suffix:semicolon
id|ssize_t
id|total
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tun-&gt;flags
op_amp
id|TUN_NO_PI
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
r_sizeof
(paren
id|pi
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|skb-&gt;len
)paren
(brace
multiline_comment|/* Packet will be striped */
id|pi.flags
op_or_assign
id|TUN_PKT_STRIP
suffix:semicolon
)brace
id|memcpy_toiovec
c_func
(paren
id|iv
comma
(paren
r_void
op_star
)paren
op_amp
id|pi
comma
r_sizeof
(paren
id|pi
)paren
)paren
suffix:semicolon
id|total
op_add_assign
r_sizeof
(paren
id|pi
)paren
suffix:semicolon
)brace
id|len
op_assign
id|min_t
c_func
(paren
r_int
comma
id|skb-&gt;len
comma
id|len
)paren
suffix:semicolon
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
l_int|0
comma
id|iv
comma
id|len
)paren
suffix:semicolon
id|total
op_add_assign
id|len
suffix:semicolon
id|tun-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|tun-&gt;stats.tx_bytes
op_add_assign
id|len
suffix:semicolon
r_return
id|total
suffix:semicolon
)brace
multiline_comment|/* Readv */
DECL|function|tun_chr_readv
r_static
id|ssize_t
id|tun_chr_readv
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|iovec
op_star
id|iv
comma
r_int
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|ssize_t
id|len
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tun
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_chr_read&bslash;n&quot;
comma
id|tun-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|iv
(braket
id|i
)braket
dot
id|iov_base
comma
id|iv
(braket
id|i
)braket
dot
id|iov_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|len
op_add_assign
id|iv
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|tun-&gt;read_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
multiline_comment|/* Read frames from the queue */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|tun-&gt;readq
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Nothing to read, let&squot;s sleep */
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|netif_start_queue
c_func
(paren
op_amp
id|tun-&gt;dev
)paren
suffix:semicolon
id|ret
op_assign
id|tun_put_user
c_func
(paren
id|tun
comma
id|skb
comma
(paren
r_struct
id|iovec
op_star
)paren
id|iv
comma
id|len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|tun-&gt;read_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Read */
DECL|function|tun_chr_read
r_static
id|ssize_t
id|tun_chr_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|iovec
id|iv
op_assign
(brace
id|buf
comma
id|count
)brace
suffix:semicolon
r_return
id|tun_chr_readv
c_func
(paren
id|file
comma
op_amp
id|iv
comma
l_int|1
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|tun_set_iff
r_static
r_int
id|tun_set_iff
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dev
op_assign
id|__dev_get_by_name
c_func
(paren
id|ifr-&gt;ifr_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
multiline_comment|/* Device exist */
id|tun
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;init
op_ne
id|tun_net_init
op_logical_or
id|tun-&gt;attached
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Check permissions */
r_if
c_cond
(paren
id|tun-&gt;owner
op_ne
op_minus
l_int|1
)paren
r_if
c_cond
(paren
id|current-&gt;euid
op_ne
id|tun-&gt;owner
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_else
(brace
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Allocate new device */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tun
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tun_struct
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|tun
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tun_struct
)paren
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|tun-&gt;readq
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|tun-&gt;read_wait
)paren
suffix:semicolon
id|tun-&gt;owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|tun-&gt;dev.init
op_assign
id|tun_net_init
suffix:semicolon
id|tun-&gt;dev.priv
op_assign
id|tun
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
op_amp
id|tun-&gt;dev
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Set dev type */
r_if
c_cond
(paren
id|ifr-&gt;ifr_flags
op_amp
id|IFF_TUN
)paren
(brace
multiline_comment|/* TUN device */
id|tun-&gt;flags
op_or_assign
id|TUN_TUN_DEV
suffix:semicolon
id|name
op_assign
l_string|&quot;tun%d&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ifr-&gt;ifr_flags
op_amp
id|IFF_TAP
)paren
(brace
multiline_comment|/* TAP device */
id|tun-&gt;flags
op_or_assign
id|TUN_TAP_DEV
suffix:semicolon
id|name
op_assign
l_string|&quot;tap%d&quot;
suffix:semicolon
)brace
r_else
r_goto
id|failed
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ifr-&gt;ifr_name
)paren
id|name
op_assign
id|ifr-&gt;ifr_name
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|dev_alloc_name
c_func
(paren
op_amp
id|tun-&gt;dev
comma
id|name
)paren
)paren
OL
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_netdevice
c_func
(paren
op_amp
id|tun-&gt;dev
)paren
)paren
)paren
r_goto
id|failed
suffix:semicolon
id|tun-&gt;name
op_assign
id|tun-&gt;dev.name
suffix:semicolon
)brace
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_set_iff&bslash;n&quot;
comma
id|tun-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifr-&gt;ifr_flags
op_amp
id|IFF_NO_PI
)paren
id|tun-&gt;flags
op_or_assign
id|TUN_NO_PI
suffix:semicolon
r_if
c_cond
(paren
id|ifr-&gt;ifr_flags
op_amp
id|IFF_ONE_QUEUE
)paren
id|tun-&gt;flags
op_or_assign
id|TUN_ONE_QUEUE
suffix:semicolon
id|file-&gt;private_data
op_assign
id|tun
suffix:semicolon
id|tun-&gt;attached
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|ifr-&gt;ifr_name
comma
id|tun-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|failed
suffix:colon
id|kfree
c_func
(paren
id|tun
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|tun_chr_ioctl
r_static
r_int
id|tun_chr_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|TUNSETIFF
op_logical_and
op_logical_neg
id|tun
)paren
(brace
r_struct
id|ifreq
id|ifr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ifr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ifr
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ifr.ifr_name
(braket
id|IFNAMSIZ
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|tun_set_iff
c_func
(paren
id|file
comma
op_amp
id|ifr
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|ifr
comma
r_sizeof
(paren
id|ifr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tun
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_chr_ioctl cmd %d&bslash;n&quot;
comma
id|tun-&gt;name
comma
id|cmd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TUNSETNOCSUM
suffix:colon
multiline_comment|/* Disable/Enable checksum */
r_if
c_cond
(paren
id|arg
)paren
id|tun-&gt;flags
op_or_assign
id|TUN_NOCHECKSUM
suffix:semicolon
r_else
id|tun-&gt;flags
op_and_assign
op_complement
id|TUN_NOCHECKSUM
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: checksum %s&bslash;n&quot;
comma
id|tun-&gt;name
comma
id|arg
ques
c_cond
l_string|&quot;disabled&quot;
suffix:colon
l_string|&quot;enabled&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNSETPERSIST
suffix:colon
multiline_comment|/* Disable/Enable persist mode */
r_if
c_cond
(paren
id|arg
)paren
id|tun-&gt;flags
op_or_assign
id|TUN_PERSIST
suffix:semicolon
r_else
id|tun-&gt;flags
op_and_assign
op_complement
id|TUN_PERSIST
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: persist %s&bslash;n&quot;
comma
id|tun-&gt;name
comma
id|arg
ques
c_cond
l_string|&quot;disabled&quot;
suffix:colon
l_string|&quot;enabled&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNSETOWNER
suffix:colon
multiline_comment|/* Set owner of the device */
id|tun-&gt;owner
op_assign
(paren
id|uid_t
)paren
id|arg
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: owner set to %d&bslash;n&quot;
comma
id|tun-&gt;owner
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef TUN_DEBUG
r_case
id|TUNSETDEBUG
suffix:colon
id|tun-&gt;debug
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tun_chr_fasync
r_static
r_int
id|tun_chr_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|on
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tun
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_chr_fasync %d&bslash;n&quot;
comma
id|tun-&gt;name
comma
id|on
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|file
comma
id|on
comma
op_amp
id|tun-&gt;fasync
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
id|ret
op_assign
id|f_setown
c_func
(paren
id|file
comma
id|current-&gt;pid
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|tun-&gt;flags
op_or_assign
id|TUN_FASYNC
suffix:semicolon
)brace
r_else
id|tun-&gt;flags
op_and_assign
op_complement
id|TUN_FASYNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tun_chr_open
r_static
r_int
id|tun_chr_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|DBG1
c_func
(paren
id|KERN_INFO
l_string|&quot;tunX: tun_chr_open&bslash;n&quot;
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tun_chr_close
r_static
r_int
id|tun_chr_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|tun_struct
op_star
id|tun
op_assign
(paren
r_struct
id|tun_struct
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tun
)paren
r_return
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: tun_chr_close&bslash;n&quot;
comma
id|tun-&gt;name
)paren
suffix:semicolon
id|tun_chr_fasync
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Detach from net device */
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|tun-&gt;attached
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Drop read queue */
id|skb_queue_purge
c_func
(paren
op_amp
id|tun-&gt;readq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tun-&gt;flags
op_amp
id|TUN_PERSIST
)paren
)paren
(brace
id|dev_close
c_func
(paren
op_amp
id|tun-&gt;dev
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
op_amp
id|tun-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tun
)paren
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tun_fops
r_static
r_struct
id|file_operations
id|tun_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|tun_chr_read
comma
dot
id|readv
op_assign
id|tun_chr_readv
comma
dot
id|write
op_assign
id|tun_chr_write
comma
dot
id|writev
op_assign
id|tun_chr_writev
comma
dot
id|poll
op_assign
id|tun_chr_poll
comma
dot
id|ioctl
op_assign
id|tun_chr_ioctl
comma
dot
id|open
op_assign
id|tun_chr_open
comma
dot
id|release
op_assign
id|tun_chr_close
comma
dot
id|fasync
op_assign
id|tun_chr_fasync
)brace
suffix:semicolon
DECL|variable|tun_miscdev
r_static
r_struct
id|miscdevice
id|tun_miscdev
op_assign
(brace
id|TUN_MINOR
comma
l_string|&quot;net/tun&quot;
comma
op_amp
id|tun_fops
)brace
suffix:semicolon
DECL|function|tun_init
r_int
id|__init
id|tun_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Universal TUN/TAP device driver %s &quot;
l_string|&quot;(C)1999-2002 Maxim Krasnyansky&bslash;n&quot;
comma
id|TUN_VER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|tun_miscdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tun: Can&squot;t register misc device %d&bslash;n&quot;
comma
id|TUN_MINOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tun_cleanup
r_void
id|tun_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|tun_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|tun_init
id|module_init
c_func
(paren
id|tun_init
)paren
suffix:semicolon
DECL|variable|tun_cleanup
id|module_exit
c_func
(paren
id|tun_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
