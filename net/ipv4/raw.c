multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;RAW - implementation of IP &quot;raw&quot; sockets.&n; *&n; * Version:&t;$Id: raw.c,v 1.64 2002/02/01 22:01:04 davem Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;verify_area() fixed up&n; *&t;&t;Alan Cox&t;:&t;ICMP error handling&n; *&t;&t;Alan Cox&t;:&t;EMSGSIZE if you send too big a packet&n; *&t;&t;Alan Cox&t;: &t;Now uses generic datagrams and shared&n; *&t;&t;&t;&t;&t;skbuff library. No more peek crashes,&n; *&t;&t;&t;&t;&t;no more backlogs&n; *&t;&t;Alan Cox&t;:&t;Checks sk-&gt;broadcast.&n; *&t;&t;Alan Cox&t;:&t;Uses skb_free_datagram/skb_copy_datagram&n; *&t;&t;Alan Cox&t;:&t;Raw passes ip options too&n; *&t;&t;Alan Cox&t;:&t;Setsocketopt added&n; *&t;&t;Alan Cox&t;:&t;Fixed error return for broadcasts&n; *&t;&t;Alan Cox&t;:&t;Removed wake_up calls&n; *&t;&t;Alan Cox&t;:&t;Use ttl/tos&n; *&t;&t;Alan Cox&t;:&t;Cleaned up old debugging&n; *&t;&t;Alan Cox&t;:&t;Use new kernel side addresses&n; *&t;Arnt Gulbrandsen&t;:&t;Fixed MSG_DONTROUTE in raw sockets.&n; *&t;&t;Alan Cox&t;:&t;BSD style RAW socket demultiplexing.&n; *&t;&t;Alan Cox&t;:&t;Beginnings of mrouted support.&n; *&t;&t;Alan Cox&t;:&t;Added IP_HDRINCL option.&n; *&t;&t;Alan Cox&t;:&t;Skip broadcast check if BSDism set.&n; *&t;&t;David S. Miller&t;:&t;New socket lookup architecture.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/raw.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
DECL|variable|raw_v4_htable
r_struct
id|sock
op_star
id|raw_v4_htable
(braket
id|RAWV4_HTABLE_SIZE
)braket
suffix:semicolon
DECL|variable|raw_v4_lock
id|rwlock_t
id|raw_v4_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|raw_v4_hash
r_static
r_void
id|raw_v4_hash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sock
op_star
op_star
id|skp
op_assign
op_amp
id|raw_v4_htable
(braket
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
op_amp
(paren
id|RAWV4_HTABLE_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sk-&gt;next
op_assign
op_star
id|skp
)paren
op_ne
l_int|NULL
)paren
(paren
op_star
id|skp
)paren
op_member_access_from_pointer
id|pprev
op_assign
op_amp
id|sk-&gt;next
suffix:semicolon
op_star
id|skp
op_assign
id|sk
suffix:semicolon
id|sk-&gt;pprev
op_assign
id|skp
suffix:semicolon
id|sock_prot_inc_use
c_func
(paren
id|sk-&gt;prot
)paren
suffix:semicolon
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
)brace
DECL|function|raw_v4_unhash
r_static
r_void
id|raw_v4_unhash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;pprev
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;next
)paren
id|sk-&gt;next-&gt;pprev
op_assign
id|sk-&gt;pprev
suffix:semicolon
op_star
id|sk-&gt;pprev
op_assign
id|sk-&gt;next
suffix:semicolon
id|sk-&gt;pprev
op_assign
l_int|NULL
suffix:semicolon
id|sock_prot_dec_use
c_func
(paren
id|sk-&gt;prot
)paren
suffix:semicolon
id|__sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
)brace
DECL|function|__raw_v4_lookup
r_struct
id|sock
op_star
id|__raw_v4_lookup
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|num
comma
r_int
r_int
id|raddr
comma
r_int
r_int
id|laddr
comma
r_int
id|dif
)paren
(brace
r_struct
id|sock
op_star
id|s
op_assign
id|sk
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|sk
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet-&gt;num
op_eq
id|num
op_logical_and
op_logical_neg
(paren
id|inet-&gt;daddr
op_logical_and
id|inet-&gt;daddr
op_ne
id|raddr
)paren
op_logical_and
op_logical_neg
(paren
id|inet-&gt;rcv_saddr
op_logical_and
id|inet-&gt;rcv_saddr
op_ne
id|laddr
)paren
op_logical_and
op_logical_neg
(paren
id|s-&gt;bound_dev_if
op_logical_and
id|s-&gt;bound_dev_if
op_ne
id|dif
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* gotcha */
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;0 - deliver&n; *&t;1 - block&n; */
DECL|function|icmp_filter
r_static
id|__inline__
r_int
id|icmp_filter
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
(brace
r_int
id|type
suffix:semicolon
id|type
op_assign
id|skb-&gt;h.icmph-&gt;type
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|32
)paren
(brace
id|__u32
id|data
op_assign
id|raw4_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|filter.data
suffix:semicolon
r_return
(paren
(paren
l_int|1
op_lshift
id|type
)paren
op_amp
id|data
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Do not block unknown ICMP types */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* IP input processing comes here for RAW socket delivery.&n; * Caller owns SKB, so we must make clones.&n; *&n; * RFC 1122: SHOULD pass TOS value up to the transport layer.&n; * -&gt; It does. And not only TOS, but all IP header.&n; */
DECL|function|raw_v4_input
r_void
id|raw_v4_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|hash
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sk
op_assign
id|raw_v4_htable
(braket
id|hash
)braket
)paren
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|sk
op_assign
id|__raw_v4_lookup
c_func
(paren
id|sk
comma
id|iph-&gt;protocol
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|skb-&gt;dev-&gt;ifindex
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sk
)paren
(brace
r_if
c_cond
(paren
id|iph-&gt;protocol
op_ne
id|IPPROTO_ICMP
op_logical_or
op_logical_neg
id|icmp_filter
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|clone
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* Not releasing hash table! */
r_if
c_cond
(paren
id|clone
)paren
id|raw_rcv
c_func
(paren
id|sk
comma
id|clone
)paren
suffix:semicolon
)brace
id|sk
op_assign
id|__raw_v4_lookup
c_func
(paren
id|sk-&gt;next
comma
id|iph-&gt;protocol
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|skb-&gt;dev-&gt;ifindex
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
)brace
DECL|function|raw_err
r_void
id|raw_err
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
comma
id|u32
id|info
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_int
id|type
op_assign
id|skb-&gt;h.icmph-&gt;type
suffix:semicolon
r_int
id|code
op_assign
id|skb-&gt;h.icmph-&gt;code
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|harderr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Report error on raw socket, if:&n;&t;   1. User requested ip_recverr.&n;&t;   2. Socket is connected (otherwise the error indication&n;&t;      is useless without ip_recverr and error is hard.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|inet-&gt;recverr
op_logical_and
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_default
suffix:colon
r_case
id|ICMP_TIME_EXCEEDED
suffix:colon
id|err
op_assign
id|EHOSTUNREACH
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_SOURCE_QUENCH
suffix:colon
r_return
suffix:semicolon
r_case
id|ICMP_PARAMETERPROB
suffix:colon
id|err
op_assign
id|EPROTO
suffix:semicolon
id|harderr
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_DEST_UNREACH
suffix:colon
id|err
op_assign
id|EHOSTUNREACH
suffix:semicolon
r_if
c_cond
(paren
id|code
OG
id|NR_ICMP_UNREACH
)paren
r_break
suffix:semicolon
id|err
op_assign
id|icmp_err_convert
(braket
id|code
)braket
dot
id|errno
suffix:semicolon
id|harderr
op_assign
id|icmp_err_convert
(braket
id|code
)braket
dot
id|fatal
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
id|ICMP_FRAG_NEEDED
)paren
(brace
id|harderr
op_assign
id|inet-&gt;pmtudisc
op_ne
id|IP_PMTUDISC_DONT
suffix:semicolon
id|err
op_assign
id|EMSGSIZE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|inet-&gt;recverr
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|u8
op_star
id|payload
op_assign
id|skb-&gt;data
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet-&gt;hdrincl
)paren
id|payload
op_assign
id|skb-&gt;data
suffix:semicolon
id|ip_icmp_error
c_func
(paren
id|sk
comma
id|skb
comma
id|err
comma
l_int|0
comma
id|info
comma
id|payload
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet-&gt;recverr
op_logical_or
id|harderr
)paren
(brace
id|sk-&gt;err
op_assign
id|err
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
DECL|function|raw_rcv_skb
r_static
r_int
id|raw_rcv_skb
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
(brace
multiline_comment|/* Charge it to the socket. */
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
OL
l_int|0
)paren
(brace
id|IP_INC_STATS
c_func
(paren
id|IpInDiscards
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
id|IP_INC_STATS
c_func
(paren
id|IpInDelivers
)paren
suffix:semicolon
r_return
id|NET_RX_SUCCESS
suffix:semicolon
)brace
DECL|function|raw_rcv
r_int
id|raw_rcv
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
(brace
id|skb_push
c_func
(paren
id|skb
comma
id|skb-&gt;data
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
id|raw_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|rawfakehdr
r_struct
id|rawfakehdr
(brace
DECL|member|iov
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
DECL|member|saddr
id|u32
id|saddr
suffix:semicolon
DECL|member|dst
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Send a RAW IP packet.&n; */
multiline_comment|/*&n; *&t;Callback support is trivial for SOCK_RAW&n; */
DECL|function|raw_getfrag
r_static
r_int
id|raw_getfrag
c_func
(paren
r_const
r_void
op_star
id|p
comma
r_char
op_star
id|to
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|fraglen
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|rawfakehdr
op_star
id|rfh
op_assign
(paren
r_struct
id|rawfakehdr
op_star
)paren
id|p
suffix:semicolon
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
multiline_comment|/* Is there any good place to set it? */
r_return
id|memcpy_fromiovecend
c_func
(paren
id|to
comma
id|rfh-&gt;iov
comma
id|offset
comma
id|fraglen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;IPPROTO_RAW needs extra work.&n; */
DECL|function|raw_getrawfrag
r_static
r_int
id|raw_getrawfrag
c_func
(paren
r_const
r_void
op_star
id|p
comma
r_char
op_star
id|to
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|fraglen
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|rawfakehdr
op_star
id|rfh
op_assign
(paren
r_struct
id|rawfakehdr
op_star
)paren
id|p
suffix:semicolon
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
multiline_comment|/* Is there any good place to set it? */
r_if
c_cond
(paren
id|memcpy_fromiovecend
c_func
(paren
id|to
comma
id|rfh-&gt;iov
comma
id|offset
comma
id|fraglen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|to
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iph-&gt;saddr
)paren
id|iph-&gt;saddr
op_assign
id|rfh-&gt;saddr
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|fraglen
)paren
suffix:semicolon
multiline_comment|/* This is right as you can&squot;t&n;&t;&t;&t;&t;&t;&t;  frag RAW packets */
multiline_comment|/*&n;&t; &t; *&t;Deliberate breach of modularity to keep &n;&t; &t; *&t;ip_build_xmit clean (well less messy).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|iph-&gt;id
)paren
id|ip_select_ident
c_func
(paren
id|iph
comma
id|rfh-&gt;dst
comma
l_int|NULL
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_sendmsg
r_static
r_int
id|raw_sendmsg
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|ipcm_cookie
id|ipc
suffix:semicolon
r_struct
id|rawfakehdr
id|rfh
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
op_assign
l_int|NULL
suffix:semicolon
r_int
id|free
op_assign
l_int|0
suffix:semicolon
id|u32
id|daddr
suffix:semicolon
id|u8
id|tos
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* This check is ONLY to check for arithmetic overflow&n;&t;   on integer(!) len. Not more! Real check will be made&n;&t;   in ip_build_xmit --ANK&n;&n;&t;   BTW socket.c -&gt; af_*.c -&gt; ... make multiple&n;&t;   invalid conversions size_t -&gt; int. We MUST repair it f.e.&n;&t;   by replacing all of them with size_t and revise all&n;&t;   the places sort of len += sizeof(struct iphdr)&n;&t;   If len was ULONG_MAX-10 it would be cathastrophe  --ANK&n;&t; */
id|err
op_assign
op_minus
id|EMSGSIZE
suffix:semicolon
r_if
c_cond
(paren
id|len
template_param
l_int|0xFFFF
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check the flags.&n;&t; */
id|err
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_OOB
)paren
multiline_comment|/* Mirror BSD error message */
r_goto
id|out
suffix:semicolon
multiline_comment|/* compatibility */
multiline_comment|/*&n;&t; *&t;Get and verify the address. &n;&t; */
r_if
c_cond
(paren
id|msg-&gt;msg_namelen
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|usin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_namelen
OL
r_sizeof
(paren
op_star
id|usin
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|usin-&gt;sin_family
op_ne
id|AF_INET
)paren
(brace
r_static
r_int
id|complained
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|complained
op_increment
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s forgot to set AF_INET in &quot;
l_string|&quot;raw sendmsg. Fix it!&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|usin-&gt;sin_family
)paren
r_goto
id|out
suffix:semicolon
)brace
id|daddr
op_assign
id|usin-&gt;sin_addr.s_addr
suffix:semicolon
multiline_comment|/* ANK: I did not forget to get protocol from port field.&n;&t;&t; * I just do not know, who uses this weirdness.&n;&t;&t; * IP_HDRINCL is much more convenient.&n;&t;&t; */
)brace
r_else
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_goto
id|out
suffix:semicolon
id|daddr
op_assign
id|inet-&gt;daddr
suffix:semicolon
)brace
id|ipc.addr
op_assign
id|inet-&gt;saddr
suffix:semicolon
id|ipc.opt
op_assign
l_int|NULL
suffix:semicolon
id|ipc.oif
op_assign
id|sk-&gt;bound_dev_if
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_controllen
)paren
(brace
id|err
op_assign
id|ip_cmsg_send
c_func
(paren
id|msg
comma
op_amp
id|ipc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ipc.opt
)paren
id|free
op_assign
l_int|1
suffix:semicolon
)brace
id|rfh.saddr
op_assign
id|ipc.addr
suffix:semicolon
id|ipc.addr
op_assign
id|daddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipc.opt
)paren
id|ipc.opt
op_assign
id|inet-&gt;opt
suffix:semicolon
r_if
c_cond
(paren
id|ipc.opt
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Linux does not mangle headers on raw sockets,&n;&t;&t; * so that IP options + IP_HDRINCL is non-sense.&n;&t;&t; */
r_if
c_cond
(paren
id|inet-&gt;hdrincl
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|ipc.opt-&gt;srr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|daddr
)paren
r_goto
id|done
suffix:semicolon
id|daddr
op_assign
id|ipc.opt-&gt;faddr
suffix:semicolon
)brace
)brace
id|tos
op_assign
id|RT_TOS
c_func
(paren
id|inet-&gt;tos
)paren
op_or
id|sk-&gt;localroute
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_DONTROUTE
)paren
id|tos
op_or_assign
id|RTO_ONLINK
suffix:semicolon
r_if
c_cond
(paren
id|MULTICAST
c_func
(paren
id|daddr
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ipc.oif
)paren
id|ipc.oif
op_assign
id|inet-&gt;mc_index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rfh.saddr
)paren
id|rfh.saddr
op_assign
id|inet-&gt;mc_addr
suffix:semicolon
)brace
(brace
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
id|daddr
comma
dot
id|saddr
op_assign
id|rfh.saddr
comma
dot
id|tos
op_assign
id|tos
)brace
)brace
comma
dot
id|oif
op_assign
id|ipc.oif
)brace
suffix:semicolon
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
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
suffix:semicolon
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_BROADCAST
op_logical_and
op_logical_neg
id|sk-&gt;broadcast
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_CONFIRM
)paren
r_goto
id|do_confirm
suffix:semicolon
id|back_from_confirm
suffix:colon
id|rfh.iov
op_assign
id|msg-&gt;msg_iov
suffix:semicolon
id|rfh.saddr
op_assign
id|rt-&gt;rt_src
suffix:semicolon
id|rfh.dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipc.addr
)paren
id|ipc.addr
op_assign
id|rt-&gt;rt_dst
suffix:semicolon
id|err
op_assign
id|ip_build_xmit
c_func
(paren
id|sk
comma
id|inet-&gt;hdrincl
ques
c_cond
id|raw_getrawfrag
suffix:colon
id|raw_getfrag
comma
op_amp
id|rfh
comma
id|len
comma
op_amp
id|ipc
comma
id|rt
comma
id|msg-&gt;msg_flags
)paren
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|free
)paren
id|kfree
c_func
(paren
id|ipc.opt
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
id|len
suffix:semicolon
id|do_confirm
suffix:colon
id|dst_confirm
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_PROBE
)paren
op_logical_or
id|len
)paren
r_goto
id|back_from_confirm
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
DECL|function|raw_close
r_static
r_void
id|raw_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|timeout
)paren
(brace
multiline_comment|/*&n;&t; * Raw sockets may have direct kernel refereneces. Kill them.&n;&t; */
id|ip_ra_control
c_func
(paren
id|sk
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|inet_sock_release
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/* This gets rid of all the nasties in af_inet. -DaveM */
DECL|function|raw_bind
r_static
r_int
id|raw_bind
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|addr
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|uaddr
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
id|chk_addr_ret
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_CLOSE
op_logical_or
id|addr_len
OL
r_sizeof
(paren
r_struct
id|sockaddr_in
)paren
)paren
r_goto
id|out
suffix:semicolon
id|chk_addr_ret
op_assign
id|inet_addr_type
c_func
(paren
id|addr-&gt;sin_addr.s_addr
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;sin_addr.s_addr
op_logical_and
id|chk_addr_ret
op_ne
id|RTN_LOCAL
op_logical_and
id|chk_addr_ret
op_ne
id|RTN_MULTICAST
op_logical_and
id|chk_addr_ret
op_ne
id|RTN_BROADCAST
)paren
r_goto
id|out
suffix:semicolon
id|inet-&gt;rcv_saddr
op_assign
id|inet-&gt;saddr
op_assign
id|addr-&gt;sin_addr.s_addr
suffix:semicolon
r_if
c_cond
(paren
id|chk_addr_ret
op_eq
id|RTN_MULTICAST
op_logical_or
id|chk_addr_ret
op_eq
id|RTN_BROADCAST
)paren
id|inet-&gt;saddr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Use device */
id|sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This should be easy, if there is something there&n; *&t;we return it, otherwise we block.&n; */
DECL|function|raw_recvmsg
r_int
id|raw_recvmsg
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_int
op_star
id|addr_len
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_OOB
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
op_star
id|addr_len
op_assign
r_sizeof
(paren
op_star
id|sin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_ERRQUEUE
)paren
(brace
id|err
op_assign
id|ip_recv_error
c_func
(paren
id|sk
comma
id|msg
comma
id|len
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|skb
op_assign
id|skb_recv_datagram
c_func
(paren
id|sk
comma
id|flags
comma
id|noblock
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|out
suffix:semicolon
id|copied
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|copied
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
id|copied
op_assign
id|len
suffix:semicolon
)brace
id|err
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
l_int|0
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
suffix:semicolon
id|sock_recv_timestamp
c_func
(paren
id|msg
comma
id|sk
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Copy the address. */
r_if
c_cond
(paren
id|sin
)paren
(brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sin-&gt;sin_zero
comma
l_int|0
comma
r_sizeof
(paren
id|sin-&gt;sin_zero
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet-&gt;cmsg_flags
)paren
id|ip_cmsg_recv
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
id|done
suffix:colon
id|skb_free_datagram
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
ques
c_cond
suffix:colon
id|copied
suffix:semicolon
)brace
DECL|function|raw_init
r_static
r_int
id|raw_init
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|raw_opt
op_star
id|tp
op_assign
id|raw4_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
op_eq
id|IPPROTO_ICMP
)paren
id|memset
c_func
(paren
op_amp
id|tp-&gt;filter
comma
l_int|0
comma
r_sizeof
(paren
id|tp-&gt;filter
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_seticmpfilter
r_static
r_int
id|raw_seticmpfilter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|optlen
OG
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
)paren
id|optlen
op_assign
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|raw4_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|filter
comma
id|optval
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_geticmpfilter
r_static
r_int
id|raw_geticmpfilter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_int
id|len
comma
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
)paren
id|len
op_assign
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
op_logical_or
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|raw4_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|filter
comma
id|len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|raw_setsockopt
r_static
r_int
id|raw_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|level
op_ne
id|SOL_RAW
)paren
r_return
id|ip_setsockopt
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|ICMP_FILTER
)paren
(brace
r_if
c_cond
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
op_ne
id|IPPROTO_ICMP
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
r_return
id|raw_seticmpfilter
c_func
(paren
id|sk
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
DECL|function|raw_getsockopt
r_static
r_int
id|raw_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|level
op_ne
id|SOL_RAW
)paren
r_return
id|ip_getsockopt
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|ICMP_FILTER
)paren
(brace
r_if
c_cond
(paren
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
op_ne
id|IPPROTO_ICMP
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
r_return
id|raw_geticmpfilter
c_func
(paren
id|sk
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
DECL|function|raw_ioctl
r_static
r_int
id|raw_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCOUTQ
suffix:colon
(brace
r_int
id|amount
op_assign
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;wmem_alloc
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|amount
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_case
id|SIOCINQ
suffix:colon
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|amount
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sk-&gt;receive_queue.lock
)paren
suffix:semicolon
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_ne
l_int|NULL
)paren
id|amount
op_assign
id|skb-&gt;len
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sk-&gt;receive_queue.lock
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|amount
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_default
suffix:colon
macro_line|#ifdef CONFIG_IP_MROUTE
r_return
id|ipmr_ioctl
c_func
(paren
id|sk
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|get_raw_sock
r_static
r_void
id|get_raw_sock
c_func
(paren
r_struct
id|sock
op_star
id|sp
comma
r_char
op_star
id|tmpbuf
comma
r_int
id|i
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sp
)paren
suffix:semicolon
r_int
r_int
id|dest
op_assign
id|inet-&gt;daddr
comma
id|src
op_assign
id|inet-&gt;rcv_saddr
suffix:semicolon
id|__u16
id|destp
op_assign
l_int|0
comma
id|srcp
op_assign
id|inet-&gt;num
suffix:semicolon
id|sprintf
c_func
(paren
id|tmpbuf
comma
l_string|&quot;%4d: %08X:%04X %08X:%04X&quot;
l_string|&quot; %02X %08X:%08X %02X:%08lX %08X %5d %8d %lu %d %p&quot;
comma
id|i
comma
id|src
comma
id|srcp
comma
id|dest
comma
id|destp
comma
id|sp-&gt;state
comma
id|atomic_read
c_func
(paren
op_amp
id|sp-&gt;wmem_alloc
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|sp-&gt;rmem_alloc
)paren
comma
l_int|0
comma
l_int|0L
comma
l_int|0
comma
id|sock_i_uid
c_func
(paren
id|sp
)paren
comma
l_int|0
comma
id|sock_i_ino
c_func
(paren
id|sp
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|sp-&gt;refcnt
)paren
comma
id|sp
)paren
suffix:semicolon
)brace
DECL|function|raw_get_info
r_int
id|raw_get_info
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
op_assign
l_int|0
comma
id|num
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|128
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
r_char
id|tmpbuf
(braket
l_int|129
)braket
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|128
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-127s&bslash;n&quot;
comma
l_string|&quot;  sl  local_address rem_address   st tx_queue &quot;
l_string|&quot;rx_queue tr tm-&gt;when retrnsmt   uid  timeout &quot;
l_string|&quot;inode&quot;
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|raw_v4_lock
)paren
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
id|RAWV4_HTABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|raw_v4_htable
(braket
id|i
)braket
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
comma
id|num
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;family
op_ne
id|PF_INET
)paren
r_continue
suffix:semicolon
id|pos
op_add_assign
l_int|128
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_le
id|offset
)paren
r_continue
suffix:semicolon
id|get_raw_sock
c_func
(paren
id|sk
comma
id|tmpbuf
comma
id|i
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
l_string|&quot;%-127s&bslash;n&quot;
comma
id|tmpbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|length
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|raw_v4_lock
)paren
suffix:semicolon
id|begin
op_assign
id|len
op_minus
(paren
id|pos
op_minus
id|offset
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
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
DECL|variable|raw_prot
r_struct
id|proto
id|raw_prot
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;RAW&quot;
comma
dot
id|close
op_assign
id|raw_close
comma
dot
id|connect
op_assign
id|udp_connect
comma
dot
id|disconnect
op_assign
id|udp_disconnect
comma
dot
id|ioctl
op_assign
id|raw_ioctl
comma
dot
id|init
op_assign
id|raw_init
comma
dot
id|setsockopt
op_assign
id|raw_setsockopt
comma
dot
id|getsockopt
op_assign
id|raw_getsockopt
comma
dot
id|sendmsg
op_assign
id|raw_sendmsg
comma
dot
id|recvmsg
op_assign
id|raw_recvmsg
comma
dot
id|bind
op_assign
id|raw_bind
comma
dot
id|backlog_rcv
op_assign
id|raw_rcv_skb
comma
dot
id|hash
op_assign
id|raw_v4_hash
comma
dot
id|unhash
op_assign
id|raw_v4_unhash
comma
)brace
suffix:semicolon
eof
