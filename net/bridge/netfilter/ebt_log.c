multiline_comment|/*&n; *  ebt_log&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bdschuym@pandora.be&gt;&n; *&n; *  April, 2002&n; *&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_log.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|variable|ebt_log_lock
r_static
id|spinlock_t
id|ebt_log_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|ebt_log_check
r_static
r_int
id|ebt_log_check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hookmask
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_log_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_log_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|datalen
op_ne
id|EBT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ebt_log_info
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
op_complement
id|EBT_LOG_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;loglevel
op_ge
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|info-&gt;prefix
(braket
id|EBT_LOG_PREFIX_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|tcpudphdr
r_struct
id|tcpudphdr
(brace
DECL|member|src
r_uint16
id|src
suffix:semicolon
DECL|member|dst
r_uint16
id|dst
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arppayload
r_struct
id|arppayload
(brace
DECL|member|mac_src
r_int
r_char
id|mac_src
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ip_src
r_int
r_char
id|ip_src
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|mac_dst
r_int
r_char
id|mac_dst
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ip_dst
r_int
r_char
id|ip_dst
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|print_MAC
r_static
r_void
id|print_MAC
c_func
(paren
r_int
r_char
op_star
id|p
)paren
(brace
r_int
id|i
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
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x%c&quot;
comma
op_star
id|p
comma
id|i
op_eq
id|ETH_ALEN
op_minus
l_int|1
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;:&squot;
)paren
suffix:semicolon
)brace
DECL|macro|myNIPQUAD
mdefine_line|#define myNIPQUAD(a) a[0], a[1], a[2], a[3]
DECL|function|ebt_log
r_static
r_void
id|ebt_log
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|hooknr
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
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_log_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_log_info
op_star
)paren
id|data
suffix:semicolon
r_char
id|level_string
(braket
l_int|4
)braket
op_assign
l_string|&quot;&lt; &gt;&quot;
suffix:semicolon
r_union
(brace
r_struct
id|iphdr
id|iph
suffix:semicolon
r_struct
id|tcpudphdr
id|ports
suffix:semicolon
r_struct
id|arphdr
id|arph
suffix:semicolon
r_struct
id|arppayload
id|arpp
suffix:semicolon
)brace
id|u
suffix:semicolon
id|level_string
(braket
l_int|1
)braket
op_assign
l_char|&squot;0&squot;
op_plus
id|info-&gt;loglevel
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|ebt_log_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|level_string
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s IN=%s OUT=%s &quot;
comma
id|info-&gt;prefix
comma
id|in
ques
c_cond
id|in-&gt;name
suffix:colon
l_string|&quot;&quot;
comma
id|out
ques
c_cond
id|out-&gt;name
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MAC source = &quot;
)paren
suffix:semicolon
id|print_MAC
c_func
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_source
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MAC dest = &quot;
)paren
suffix:semicolon
id|print_MAC
c_func
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_dest
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;proto = 0x%04x&quot;
comma
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
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;bitmask
op_amp
id|EBT_LOG_IP
)paren
op_logical_and
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
r_struct
id|iphdr
id|_iph
comma
op_star
id|ih
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_iph
)paren
comma
op_amp
id|_iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; INCOMPLETE IP header&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; IP SRC=%u.%u.%u.%u IP DST=%u.%u.%u.%u,&quot;
comma
id|NIPQUAD
c_func
(paren
id|ih-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|ih-&gt;daddr
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; IP tos=0x%02X, IP proto=%d&quot;
comma
id|u.iph.tos
comma
id|ih-&gt;protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih-&gt;protocol
op_eq
id|IPPROTO_TCP
op_logical_or
id|ih-&gt;protocol
op_eq
id|IPPROTO_UDP
)paren
(brace
r_struct
id|tcpudphdr
id|_ports
comma
op_star
id|pptr
suffix:semicolon
id|pptr
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ih-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_ports
)paren
comma
op_amp
id|_ports
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pptr
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; INCOMPLETE TCP/UDP header&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; SPT=%u DPT=%u&quot;
comma
id|ntohs
c_func
(paren
id|pptr-&gt;src
)paren
comma
id|ntohs
c_func
(paren
id|pptr-&gt;dst
)paren
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|info-&gt;bitmask
op_amp
id|EBT_LOG_ARP
)paren
op_logical_and
(paren
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_ARP
)paren
)paren
op_logical_or
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_RARP
)paren
)paren
)paren
)paren
(brace
r_struct
id|arphdr
id|_arph
comma
op_star
id|ah
suffix:semicolon
id|ah
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_arph
)paren
comma
op_amp
id|_arph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ah
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; INCOMPLETE ARP header&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; ARP HTYPE=%d, PTYPE=0x%04x, OPCODE=%d&quot;
comma
id|ntohs
c_func
(paren
id|ah-&gt;ar_hrd
)paren
comma
id|ntohs
c_func
(paren
id|ah-&gt;ar_pro
)paren
comma
id|ntohs
c_func
(paren
id|ah-&gt;ar_op
)paren
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s for Ethernet and the lengths are OK,&n;&t;&t; * then log the ARP payload */
r_if
c_cond
(paren
id|ah-&gt;ar_hrd
op_eq
id|htons
c_func
(paren
l_int|1
)paren
op_logical_and
id|ah-&gt;ar_hln
op_eq
id|ETH_ALEN
op_logical_and
id|ah-&gt;ar_pln
op_eq
r_sizeof
(paren
r_uint32
)paren
)paren
(brace
r_struct
id|arppayload
id|_arpp
comma
op_star
id|ap
suffix:semicolon
id|ap
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|u.arph
)paren
comma
r_sizeof
(paren
id|_arpp
)paren
comma
op_amp
id|_arpp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ap
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; INCOMPLETE ARP payload&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; ARP MAC SRC=&quot;
)paren
suffix:semicolon
id|print_MAC
c_func
(paren
id|ap-&gt;mac_src
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ARP IP SRC=%u.%u.%u.%u&quot;
comma
id|myNIPQUAD
c_func
(paren
id|ap-&gt;ip_src
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ARP MAC DST=&quot;
)paren
suffix:semicolon
id|print_MAC
c_func
(paren
id|ap-&gt;mac_dst
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ARP IP DST=%u.%u.%u.%u&quot;
comma
id|myNIPQUAD
c_func
(paren
id|ap-&gt;ip_dst
)paren
)paren
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|ebt_log_lock
)paren
suffix:semicolon
)brace
DECL|variable|log
r_static
r_struct
id|ebt_watcher
id|log
op_assign
(brace
dot
id|name
op_assign
id|EBT_LOG_WATCHER
comma
dot
id|watcher
op_assign
id|ebt_log
comma
dot
id|check
op_assign
id|ebt_log_check
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
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
id|ebt_register_watcher
c_func
(paren
op_amp
id|log
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
id|ebt_unregister_watcher
c_func
(paren
op_amp
id|log
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
