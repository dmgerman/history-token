multiline_comment|/*&n; * Linux ISDN subsystem, CISCO HDLC network interfaces&n; *&n; * Copyright 1994-1998  by Fritz Elfert (fritz@isdn4linux.de)&n; *           1995,96    by Thinking Objects Software GmbH Wuerzburg&n; *           1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *           1999-2002  by Kai Germaschewski &lt;kai@germaschewski.name&gt;&n; *           2001       by Bjoern A. Zeeb &lt;i4l@zabbadoz.net&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For info on the protocol, see http://i4l.zabbadoz.net/i4l/cisco-hdlc.txt&n; */
macro_line|#include &quot;isdn_common.h&quot;
macro_line|#include &quot;isdn_net.h&quot;
macro_line|#include &quot;isdn_ciscohdlck.h&quot;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
multiline_comment|/* &n; * CISCO HDLC keepalive specific stuff&n; */
r_static
r_struct
id|sk_buff
op_star
DECL|function|isdn_net_ciscohdlck_alloc_skb
id|isdn_net_ciscohdlck_alloc_skb
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
r_int
id|len
)paren
(brace
id|isdn_net_dev
op_star
id|idev
op_assign
id|lp-&gt;netdev
suffix:semicolon
r_int
r_int
id|hl
op_assign
id|isdn_slot_hdrlen
c_func
(paren
id|idev-&gt;isdn_slot
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|hl
op_plus
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
id|printk
c_func
(paren
l_string|&quot;isdn out of mem at %s:%d!&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|hl
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/* cisco hdlck device private ioctls */
r_static
r_int
DECL|function|isdn_ciscohdlck_dev_ioctl
id|isdn_ciscohdlck_dev_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
(brace
id|isdn_net_local
op_star
id|lp
op_assign
(paren
id|isdn_net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|isdn_net_dev
op_star
id|idev
op_assign
id|lp-&gt;netdev
suffix:semicolon
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|expires
op_assign
l_int|0
suffix:semicolon
r_int
id|tmp
op_assign
l_int|0
suffix:semicolon
r_int
id|period
op_assign
id|lp-&gt;cisco_keepalive_period
suffix:semicolon
r_char
id|debserint
op_assign
id|lp-&gt;cisco_debserint
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;p_encap
op_ne
id|ISDN_NET_ENCAP_CISCOHDLCK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* get/set keepalive period */
r_case
id|SIOCGKEEPPERIOD
suffix:colon
id|len
op_assign
(paren
r_int
r_int
)paren
r_sizeof
(paren
id|lp-&gt;cisco_keepalive_period
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|ifr-&gt;ifr_ifru.ifru_data
comma
(paren
r_int
op_star
)paren
op_amp
id|lp-&gt;cisco_keepalive_period
comma
id|len
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCSKEEPPERIOD
suffix:colon
id|tmp
op_assign
id|lp-&gt;cisco_keepalive_period
suffix:semicolon
id|len
op_assign
(paren
r_int
r_int
)paren
r_sizeof
(paren
id|lp-&gt;cisco_keepalive_period
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_int
op_star
)paren
op_amp
id|period
comma
(paren
r_char
op_star
)paren
id|ifr-&gt;ifr_ifru.ifru_data
comma
id|len
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|period
OG
l_int|0
)paren
op_logical_and
(paren
id|period
op_le
l_int|32767
)paren
)paren
id|lp-&gt;cisco_keepalive_period
op_assign
id|period
suffix:semicolon
r_else
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_and
(paren
id|tmp
op_ne
id|lp-&gt;cisco_keepalive_period
)paren
)paren
(brace
id|expires
op_assign
(paren
r_int
r_int
)paren
(paren
id|jiffies
op_plus
id|lp-&gt;cisco_keepalive_period
op_star
id|HZ
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|lp-&gt;cisco_timer
comma
id|expires
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Keepalive period set &quot;
l_string|&quot;to %d seconds.&bslash;n&quot;
comma
id|idev-&gt;name
comma
id|lp-&gt;cisco_keepalive_period
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* get/set debugging */
r_case
id|SIOCGDEBSERINT
suffix:colon
id|len
op_assign
(paren
r_int
r_int
)paren
r_sizeof
(paren
id|lp-&gt;cisco_debserint
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|ifr-&gt;ifr_ifru.ifru_data
comma
(paren
r_char
op_star
)paren
op_amp
id|lp-&gt;cisco_debserint
comma
id|len
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCSDEBSERINT
suffix:colon
id|len
op_assign
(paren
r_int
r_int
)paren
r_sizeof
(paren
id|lp-&gt;cisco_debserint
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|debserint
comma
(paren
r_char
op_star
)paren
id|ifr-&gt;ifr_ifru.ifru_data
comma
id|len
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|debserint
op_ge
l_int|0
)paren
op_logical_and
(paren
id|debserint
op_le
l_int|64
)paren
)paren
id|lp-&gt;cisco_debserint
op_assign
id|debserint
suffix:semicolon
r_else
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
(paren
id|rc
)paren
suffix:semicolon
)brace
multiline_comment|/* called via cisco_timer.function */
r_static
r_void
DECL|function|isdn_net_ciscohdlck_slarp_send_keepalive
id|isdn_net_ciscohdlck_slarp_send_keepalive
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|isdn_net_local
op_star
id|lp
op_assign
(paren
id|isdn_net_local
op_star
)paren
id|data
suffix:semicolon
id|isdn_net_dev
op_star
id|idev
op_assign
id|lp-&gt;netdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_int
r_int
id|last_cisco_myseq
op_assign
id|lp-&gt;cisco_myseq
suffix:semicolon
r_int
id|myseq_diff
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;cisco_myseq
op_increment
suffix:semicolon
id|myseq_diff
op_assign
(paren
id|lp-&gt;cisco_myseq
op_minus
id|lp-&gt;cisco_mineseen
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lp-&gt;cisco_line_state
)paren
op_logical_and
(paren
(paren
id|myseq_diff
op_ge
l_int|3
)paren
op_logical_or
(paren
id|myseq_diff
op_le
op_minus
l_int|3
)paren
)paren
)paren
(brace
multiline_comment|/* line up -&gt; down */
id|lp-&gt;cisco_line_state
op_assign
l_int|0
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;UPDOWN: Line protocol on Interface %s,&quot;
l_string|&quot; changed state to down&bslash;n&quot;
comma
id|idev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* should stop routing higher-level data accross */
)brace
r_else
r_if
c_cond
(paren
(paren
op_logical_neg
id|lp-&gt;cisco_line_state
)paren
op_logical_and
(paren
id|myseq_diff
op_ge
l_int|0
)paren
op_logical_and
(paren
id|myseq_diff
op_le
l_int|2
)paren
)paren
(brace
multiline_comment|/* line down -&gt; up */
id|lp-&gt;cisco_line_state
op_assign
l_int|1
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;UPDOWN: Line protocol on Interface %s,&quot;
l_string|&quot; changed state to up&bslash;n&quot;
comma
id|idev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* restart routing higher-level data accross */
)brace
r_if
c_cond
(paren
id|lp-&gt;cisco_debserint
)paren
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: HDLC &quot;
l_string|&quot;myseq %lu, mineseen %lu%c, yourseen %lu, %s&bslash;n&quot;
comma
id|idev-&gt;name
comma
id|last_cisco_myseq
comma
id|lp-&gt;cisco_mineseen
comma
(paren
id|last_cisco_myseq
op_eq
id|lp-&gt;cisco_mineseen
)paren
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_int|040
comma
id|lp-&gt;cisco_yourseq
comma
(paren
id|lp-&gt;cisco_line_state
)paren
ques
c_cond
l_string|&quot;line up&quot;
suffix:colon
l_string|&quot;line down&quot;
)paren
suffix:semicolon
id|skb
op_assign
id|isdn_net_ciscohdlck_alloc_skb
c_func
(paren
id|lp
comma
l_int|4
op_plus
l_int|14
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
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
op_plus
l_int|14
)paren
suffix:semicolon
multiline_comment|/* cisco header */
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_ADDR_UNICAST
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_CTRL
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
id|CISCO_TYPE_SLARP
)paren
suffix:semicolon
multiline_comment|/* slarp keepalive */
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|CISCO_SLARP_KEEPALIVE
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|lp-&gt;cisco_myseq
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|lp-&gt;cisco_yourseq
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
l_int|0xffff
)paren
suffix:semicolon
singleline_comment|// reliablity, always 0xffff
id|isdn_net_write_super
c_func
(paren
id|idev
comma
id|skb
)paren
suffix:semicolon
id|lp-&gt;cisco_timer.expires
op_assign
id|jiffies
op_plus
id|lp-&gt;cisco_keepalive_period
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|lp-&gt;cisco_timer
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_net_ciscohdlck_slarp_send_request
id|isdn_net_ciscohdlck_slarp_send_request
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
id|isdn_net_dev
op_star
id|idev
op_assign
id|lp-&gt;netdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
id|skb
op_assign
id|isdn_net_ciscohdlck_alloc_skb
c_func
(paren
id|lp
comma
l_int|4
op_plus
l_int|14
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
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
op_plus
l_int|14
)paren
suffix:semicolon
multiline_comment|/* cisco header */
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_ADDR_UNICAST
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_CTRL
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
id|CISCO_TYPE_SLARP
)paren
suffix:semicolon
multiline_comment|/* slarp request */
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|CISCO_SLARP_REQUEST
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// address
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// netmask
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// unused
id|isdn_net_write_super
c_func
(paren
id|idev
comma
id|skb
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_ciscohdlck_connected
id|isdn_ciscohdlck_connected
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
id|lp-&gt;cisco_myseq
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;cisco_mineseen
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;cisco_yourseq
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;cisco_keepalive_period
op_assign
id|ISDN_TIMER_KEEPINT
suffix:semicolon
id|lp-&gt;cisco_last_slarp_in
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;cisco_line_state
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;cisco_debserint
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;p_encap
op_eq
id|ISDN_NET_ENCAP_CISCOHDLCK
)paren
(brace
multiline_comment|/* send slarp request because interface/seq.no.s reset */
id|isdn_net_ciscohdlck_slarp_send_request
c_func
(paren
id|lp
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|lp-&gt;cisco_timer
)paren
suffix:semicolon
id|lp-&gt;cisco_timer.data
op_assign
(paren
r_int
r_int
)paren
id|lp
suffix:semicolon
id|lp-&gt;cisco_timer.function
op_assign
id|isdn_net_ciscohdlck_slarp_send_keepalive
suffix:semicolon
id|lp-&gt;cisco_timer.expires
op_assign
id|jiffies
op_plus
id|lp-&gt;cisco_keepalive_period
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|lp-&gt;cisco_timer
)paren
suffix:semicolon
)brace
id|isdn_net_dev_wake_queue
c_func
(paren
id|lp-&gt;netdev
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_ciscohdlck_disconnected
id|isdn_ciscohdlck_disconnected
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
r_if
c_cond
(paren
id|lp-&gt;p_encap
op_eq
id|ISDN_NET_ENCAP_CISCOHDLCK
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|lp-&gt;cisco_timer
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|isdn_net_ciscohdlck_slarp_send_reply
id|isdn_net_ciscohdlck_slarp_send_reply
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
id|isdn_net_dev
op_star
id|idev
op_assign
id|lp-&gt;netdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* local ipv4 address */
id|u32
id|mask
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* local netmask */
r_if
c_cond
(paren
(paren
id|in_dev
op_assign
id|lp-&gt;netdev-&gt;dev.ip_ptr
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* take primary(first) address of interface */
r_struct
id|in_ifaddr
op_star
id|ifa
op_assign
id|in_dev-&gt;ifa_list
suffix:semicolon
r_if
c_cond
(paren
id|ifa
op_ne
l_int|NULL
)paren
(brace
id|addr
op_assign
id|ifa-&gt;ifa_local
suffix:semicolon
id|mask
op_assign
id|ifa-&gt;ifa_mask
suffix:semicolon
)brace
)brace
id|skb
op_assign
id|isdn_net_ciscohdlck_alloc_skb
c_func
(paren
id|lp
comma
l_int|4
op_plus
l_int|14
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
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
op_plus
l_int|14
)paren
suffix:semicolon
multiline_comment|/* cisco header */
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_ADDR_UNICAST
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_CTRL
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
id|CISCO_TYPE_SLARP
)paren
suffix:semicolon
multiline_comment|/* slarp reply, send own ip/netmask; if values are nonsense remote&n;&t; * should think we are unable to provide it with an address via SLARP */
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|CISCO_SLARP_REPLY
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|addr
)paren
suffix:semicolon
singleline_comment|// address
id|p
op_add_assign
id|put_u32
c_func
(paren
id|p
comma
id|mask
)paren
suffix:semicolon
singleline_comment|// netmask
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// unused
id|isdn_net_write_super
c_func
(paren
id|idev
comma
id|skb
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_net_ciscohdlck_slarp_in
id|isdn_net_ciscohdlck_slarp_in
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|isdn_net_dev
op_star
id|idev
op_assign
id|lp-&gt;netdev
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_int
id|period
suffix:semicolon
id|u32
id|code
suffix:semicolon
id|u32
id|my_seq
comma
id|addr
suffix:semicolon
id|u32
id|your_seq
comma
id|mask
suffix:semicolon
id|u32
id|local
suffix:semicolon
id|u16
id|unused
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
l_int|14
)paren
r_return
suffix:semicolon
id|p
op_assign
id|skb-&gt;data
suffix:semicolon
id|p
op_add_assign
id|get_u32
c_func
(paren
id|p
comma
op_amp
id|code
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|CISCO_SLARP_REQUEST
suffix:colon
id|lp-&gt;cisco_yourseq
op_assign
l_int|0
suffix:semicolon
id|isdn_net_ciscohdlck_slarp_send_reply
c_func
(paren
id|lp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CISCO_SLARP_REPLY
suffix:colon
id|addr
op_assign
id|ntohl
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|p
)paren
suffix:semicolon
id|mask
op_assign
id|ntohl
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
(paren
id|p
op_plus
l_int|4
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_ne
l_int|0xfffffffc
)paren
r_goto
id|slarp_reply_out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_eq
l_int|0
op_logical_or
(paren
id|addr
op_amp
l_int|3
)paren
op_eq
l_int|3
)paren
r_goto
id|slarp_reply_out
suffix:semicolon
id|local
op_assign
id|addr
op_xor
l_int|3
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: got slarp reply: &quot;
l_string|&quot;remote ip: %d.%d.%d.%d, &quot;
l_string|&quot;local ip: %d.%d.%d.%d &quot;
l_string|&quot;mask: %d.%d.%d.%d&bslash;n&quot;
comma
id|idev-&gt;name
comma
id|HIPQUAD
c_func
(paren
id|addr
)paren
comma
id|HIPQUAD
c_func
(paren
id|local
)paren
comma
id|HIPQUAD
c_func
(paren
id|mask
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
id|slarp_reply_out
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: got invalid slarp &quot;
l_string|&quot;reply (%d.%d.%d.%d/%d.%d.%d.%d) &quot;
l_string|&quot;- ignored&bslash;n&quot;
comma
id|idev-&gt;name
comma
id|HIPQUAD
c_func
(paren
id|addr
)paren
comma
id|HIPQUAD
c_func
(paren
id|mask
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CISCO_SLARP_KEEPALIVE
suffix:colon
id|period
op_assign
(paren
r_int
)paren
(paren
(paren
id|jiffies
op_minus
id|lp-&gt;cisco_last_slarp_in
op_plus
id|HZ
op_div
l_int|2
op_minus
l_int|1
)paren
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;cisco_debserint
op_logical_and
(paren
id|period
op_ne
id|lp-&gt;cisco_keepalive_period
)paren
op_logical_and
id|lp-&gt;cisco_last_slarp_in
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Keepalive period mismatch - &quot;
l_string|&quot;is %d but should be %d.&bslash;n&quot;
comma
id|idev-&gt;name
comma
id|period
comma
id|lp-&gt;cisco_keepalive_period
)paren
suffix:semicolon
)brace
id|lp-&gt;cisco_last_slarp_in
op_assign
id|jiffies
suffix:semicolon
id|p
op_add_assign
id|get_u32
c_func
(paren
id|p
comma
op_amp
id|my_seq
)paren
suffix:semicolon
id|p
op_add_assign
id|get_u32
c_func
(paren
id|p
comma
op_amp
id|your_seq
)paren
suffix:semicolon
id|p
op_add_assign
id|get_u16
c_func
(paren
id|p
comma
op_amp
id|unused
)paren
suffix:semicolon
id|lp-&gt;cisco_yourseq
op_assign
id|my_seq
suffix:semicolon
id|lp-&gt;cisco_mineseen
op_assign
id|your_seq
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|isdn_ciscohdlck_receive
id|isdn_ciscohdlck_receive
c_func
(paren
id|isdn_net_dev
op_star
id|idev
comma
id|isdn_net_local
op_star
id|olp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|isdn_net_local
op_star
id|lp
op_assign
op_amp
id|idev-&gt;local
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
id|u8
id|addr
suffix:semicolon
id|u8
id|ctrl
suffix:semicolon
id|u16
id|type
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
l_int|4
)paren
r_goto
id|out_free
suffix:semicolon
id|p
op_assign
id|skb-&gt;data
suffix:semicolon
id|p
op_add_assign
id|get_u8
(paren
id|p
comma
op_amp
id|addr
)paren
suffix:semicolon
id|p
op_add_assign
id|get_u8
(paren
id|p
comma
op_amp
id|ctrl
)paren
suffix:semicolon
id|p
op_add_assign
id|get_u16
c_func
(paren
id|p
comma
op_amp
id|type
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_ne
id|CISCO_ADDR_UNICAST
op_logical_and
id|addr
op_ne
id|CISCO_ADDR_BROADCAST
)paren
op_logical_or
id|ctrl
op_ne
id|CISCO_CTRL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Unknown Cisco header %#02x %#02x&bslash;n&quot;
comma
id|idev-&gt;name
comma
id|addr
comma
id|ctrl
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|CISCO_TYPE_SLARP
suffix:colon
id|isdn_net_ciscohdlck_slarp_in
c_func
(paren
id|lp
comma
id|skb
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
r_case
id|CISCO_TYPE_CDP
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;cisco_debserint
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Received CDP packet. use &quot;
l_string|&quot;&bslash;&quot;no cdp enable&bslash;&quot; on cisco.&bslash;n&quot;
comma
id|idev-&gt;name
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* no special cisco protocol */
id|isdn_net_reset_huptimer
c_func
(paren
id|idev
comma
id|olp-&gt;netdev
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|out_free
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|isdn_ciscohdlck_header
id|isdn_ciscohdlck_header
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
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|plen
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_ADDR_UNICAST
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|CISCO_CTRL
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
id|type
)paren
suffix:semicolon
r_return
l_int|4
suffix:semicolon
)brace
DECL|variable|ciscohdlck_ops
r_struct
id|isdn_netif_ops
id|ciscohdlck_ops
op_assign
(brace
dot
id|hard_header
op_assign
id|isdn_ciscohdlck_header
comma
dot
id|do_ioctl
op_assign
id|isdn_ciscohdlck_dev_ioctl
comma
dot
id|flags
op_assign
id|IFF_NOARP
op_or
id|IFF_POINTOPOINT
comma
dot
id|type
op_assign
id|ARPHRD_CISCO
comma
dot
id|receive
op_assign
id|isdn_ciscohdlck_receive
comma
dot
id|connected
op_assign
id|isdn_ciscohdlck_connected
comma
dot
id|disconnected
op_assign
id|isdn_ciscohdlck_disconnected
comma
)brace
suffix:semicolon
eof
