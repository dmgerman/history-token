multiline_comment|/* This is a file to handle the &quot;simple&quot; NAT cases (redirect and&n;   masquerade) required for the compatibility layer.&n;&n;   `bind to foreign address&squot; and `getpeername&squot; hacks are not&n;   supported.&n;&n;   FIXME: Timing is overly simplistic.  If anyone complains, make it&n;   use conntrack.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
r_static
id|DECLARE_LOCK
c_func
(paren
id|redir_lock
)paren
suffix:semicolon
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_LOCKED(&amp;redir_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_LOCKED(&amp;redir_lock)
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|macro|IP_NF_ASSERT
mdefine_line|#define IP_NF_ASSERT(x)&t;&t;&t;&t;&t;&t;&t; &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;if (!(x))&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;/* Wooah!  I&squot;m tripping my conntrack in a frenzy of&t; &bslash;&n;&t;&t;   netplay... */&t;&t;&t;&t;&t; &bslash;&n;&t;&t;printk(&quot;ASSERT: %s:%i(%s)&bslash;n&quot;,&t;&t;&t;&t; &bslash;&n;&t;&t;       __FILE__, __LINE__, __FUNCTION__);&t;&t; &bslash;&n;} while(0);
macro_line|#else
DECL|macro|IP_NF_ASSERT
mdefine_line|#define IP_NF_ASSERT(x)
macro_line|#endif
r_static
id|u_int16_t
DECL|function|cheat_check
id|cheat_check
c_func
(paren
id|u_int32_t
id|oldvalinv
comma
id|u_int32_t
id|newval
comma
id|u_int16_t
id|oldcheck
)paren
(brace
id|u_int32_t
id|diffs
(braket
)braket
op_assign
(brace
id|oldvalinv
comma
id|newval
)brace
suffix:semicolon
r_return
id|csum_fold
c_func
(paren
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|diffs
comma
r_sizeof
(paren
id|diffs
)paren
comma
id|oldcheck
op_xor
l_int|0xFFFF
)paren
)paren
suffix:semicolon
)brace
DECL|struct|redir_core
r_struct
id|redir_core
(brace
DECL|member|orig_srcip
DECL|member|orig_dstip
id|u_int32_t
id|orig_srcip
comma
id|orig_dstip
suffix:semicolon
DECL|member|orig_sport
DECL|member|orig_dport
id|u_int16_t
id|orig_sport
comma
id|orig_dport
suffix:semicolon
DECL|member|new_dstip
id|u_int32_t
id|new_dstip
suffix:semicolon
DECL|member|new_dport
id|u_int16_t
id|new_dport
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|redir
r_struct
id|redir
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|core
r_struct
id|redir_core
id|core
suffix:semicolon
DECL|member|destroyme
r_struct
id|timer_list
id|destroyme
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|redirs
)paren
suffix:semicolon
r_static
r_int
DECL|function|redir_cmp
id|redir_cmp
c_func
(paren
r_const
r_struct
id|redir
op_star
id|i
comma
id|u_int32_t
id|orig_srcip
comma
id|u_int32_t
id|orig_dstip
comma
id|u_int16_t
id|orig_sport
comma
id|u_int16_t
id|orig_dport
)paren
(brace
r_return
(paren
id|i-&gt;core.orig_srcip
op_eq
id|orig_srcip
op_logical_and
id|i-&gt;core.orig_dstip
op_eq
id|orig_dstip
op_logical_and
id|i-&gt;core.orig_sport
op_eq
id|orig_sport
op_logical_and
id|i-&gt;core.orig_dport
op_eq
id|orig_dport
)paren
suffix:semicolon
)brace
multiline_comment|/* Search for an existing redirection of the TCP packet. */
r_static
r_struct
id|redir
op_star
DECL|function|find_redir
id|find_redir
c_func
(paren
id|u_int32_t
id|orig_srcip
comma
id|u_int32_t
id|orig_dstip
comma
id|u_int16_t
id|orig_sport
comma
id|u_int16_t
id|orig_dport
)paren
(brace
r_return
id|LIST_FIND
c_func
(paren
op_amp
id|redirs
comma
id|redir_cmp
comma
r_struct
id|redir
op_star
comma
id|orig_srcip
comma
id|orig_dstip
comma
id|orig_sport
comma
id|orig_dport
)paren
suffix:semicolon
)brace
DECL|function|do_tcp_redir
r_static
r_void
id|do_tcp_redir
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|redir
op_star
id|redir
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
id|cheat_check
c_func
(paren
op_complement
id|redir-&gt;core.orig_dstip
comma
id|redir-&gt;core.new_dstip
comma
id|cheat_check
c_func
(paren
id|redir-&gt;core.orig_dport
op_xor
l_int|0xFFFF
comma
id|redir-&gt;core.new_dport
comma
id|tcph-&gt;check
)paren
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
id|cheat_check
c_func
(paren
op_complement
id|redir-&gt;core.orig_dstip
comma
id|redir-&gt;core.new_dstip
comma
id|iph-&gt;check
)paren
suffix:semicolon
id|tcph-&gt;dest
op_assign
id|redir-&gt;core.new_dport
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|redir-&gt;core.new_dstip
suffix:semicolon
id|skb-&gt;nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
)brace
r_static
r_int
DECL|function|unredir_cmp
id|unredir_cmp
c_func
(paren
r_const
r_struct
id|redir
op_star
id|i
comma
id|u_int32_t
id|new_dstip
comma
id|u_int32_t
id|orig_srcip
comma
id|u_int16_t
id|new_dport
comma
id|u_int16_t
id|orig_sport
)paren
(brace
r_return
(paren
id|i-&gt;core.orig_srcip
op_eq
id|orig_srcip
op_logical_and
id|i-&gt;core.new_dstip
op_eq
id|new_dstip
op_logical_and
id|i-&gt;core.orig_sport
op_eq
id|orig_sport
op_logical_and
id|i-&gt;core.new_dport
op_eq
id|new_dport
)paren
suffix:semicolon
)brace
multiline_comment|/* Match reply packet against redir */
r_static
r_struct
id|redir
op_star
DECL|function|find_unredir
id|find_unredir
c_func
(paren
id|u_int32_t
id|new_dstip
comma
id|u_int32_t
id|orig_srcip
comma
id|u_int16_t
id|new_dport
comma
id|u_int16_t
id|orig_sport
)paren
(brace
r_return
id|LIST_FIND
c_func
(paren
op_amp
id|redirs
comma
id|unredir_cmp
comma
r_struct
id|redir
op_star
comma
id|new_dstip
comma
id|orig_srcip
comma
id|new_dport
comma
id|orig_sport
)paren
suffix:semicolon
)brace
multiline_comment|/* `unredir&squot; a reply packet. */
DECL|function|do_tcp_unredir
r_static
r_void
id|do_tcp_unredir
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|redir
op_star
id|redir
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
id|cheat_check
c_func
(paren
op_complement
id|redir-&gt;core.new_dstip
comma
id|redir-&gt;core.orig_dstip
comma
id|cheat_check
c_func
(paren
id|redir-&gt;core.new_dport
op_xor
l_int|0xFFFF
comma
id|redir-&gt;core.orig_dport
comma
id|tcph-&gt;check
)paren
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
id|cheat_check
c_func
(paren
op_complement
id|redir-&gt;core.new_dstip
comma
id|redir-&gt;core.orig_dstip
comma
id|iph-&gt;check
)paren
suffix:semicolon
id|tcph-&gt;source
op_assign
id|redir-&gt;core.orig_dport
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|redir-&gt;core.orig_dstip
suffix:semicolon
id|skb-&gt;nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
)brace
multiline_comment|/* REDIRECT a packet. */
r_int
r_int
DECL|function|do_redirect
id|do_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|dev
comma
id|u_int16_t
id|redirpt
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|u_int32_t
id|newdst
suffix:semicolon
multiline_comment|/* Figure out address: not loopback. */
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|NF_DROP
suffix:semicolon
multiline_comment|/* Grab first address on interface. */
id|newdst
op_assign
(paren
(paren
r_struct
id|in_device
op_star
)paren
id|dev-&gt;ip_ptr
)paren
op_member_access_from_pointer
id|ifa_list-&gt;ifa_local
suffix:semicolon
r_switch
c_cond
(paren
id|iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_UDP
suffix:colon
(brace
multiline_comment|/* Simple mangle. */
r_struct
id|udphdr
op_star
id|udph
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udph-&gt;check
)paren
multiline_comment|/* 0 is a special case meaning no checksum */
id|udph-&gt;check
op_assign
id|cheat_check
c_func
(paren
op_complement
id|iph-&gt;daddr
comma
id|newdst
comma
id|cheat_check
c_func
(paren
id|udph-&gt;dest
op_xor
l_int|0xFFFF
comma
id|redirpt
comma
id|udph-&gt;check
)paren
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
id|cheat_check
c_func
(paren
op_complement
id|iph-&gt;daddr
comma
id|newdst
comma
id|iph-&gt;check
)paren
suffix:semicolon
id|udph-&gt;dest
op_assign
id|redirpt
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|newdst
suffix:semicolon
id|skb-&gt;nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_case
id|IPPROTO_TCP
suffix:colon
(brace
multiline_comment|/* Mangle, maybe record. */
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
r_struct
id|redir
op_star
id|redir
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Doing tcp redirect. %08X:%u %08X:%u -&gt; %08X:%u&bslash;n&quot;
comma
id|iph-&gt;saddr
comma
id|tcph-&gt;source
comma
id|iph-&gt;daddr
comma
id|tcph-&gt;dest
comma
id|newdst
comma
id|redirpt
)paren
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
id|redir
op_assign
id|find_redir
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|tcph-&gt;source
comma
id|tcph-&gt;dest
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|redir
)paren
(brace
id|redir
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|redir
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|redir
)paren
(brace
id|ret
op_assign
id|NF_DROP
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|list_prepend
c_func
(paren
op_amp
id|redirs
comma
id|redir
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|redir-&gt;destroyme
)paren
suffix:semicolon
id|redir-&gt;destroyme.expires
op_assign
id|jiffies
op_plus
l_int|75
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|redir-&gt;destroyme
)paren
suffix:semicolon
)brace
multiline_comment|/* In case mangling has changed, rewrite this part. */
id|redir-&gt;core
op_assign
(paren
(paren
r_struct
id|redir_core
)paren
(brace
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|tcph-&gt;source
comma
id|tcph-&gt;dest
comma
id|newdst
comma
id|redirpt
)brace
)paren
suffix:semicolon
id|do_tcp_redir
c_func
(paren
id|skb
comma
id|redir
)paren
suffix:semicolon
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
id|out
suffix:colon
id|UNLOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_default
suffix:colon
multiline_comment|/* give up if not TCP or UDP. */
r_return
id|NF_DROP
suffix:semicolon
)brace
)brace
DECL|function|destroyme
r_static
r_void
id|destroyme
c_func
(paren
r_int
r_int
id|me
)paren
(brace
id|LOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
id|LIST_DELETE
c_func
(paren
op_amp
id|redirs
comma
(paren
r_struct
id|redir
op_star
)paren
id|me
)paren
suffix:semicolon
id|UNLOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Incoming packet: is it a reply to a masqueraded connection, or&n;   part of an already-redirected TCP connection? */
r_void
DECL|function|check_for_redirect
id|check_for_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
r_struct
id|redir
op_star
id|redir
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;protocol
op_ne
id|IPPROTO_TCP
)paren
r_return
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
id|redir
op_assign
id|find_redir
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|tcph-&gt;source
comma
id|tcph-&gt;dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|redir
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Doing tcp redirect again.&bslash;n&quot;
)paren
suffix:semicolon
id|do_tcp_redir
c_func
(paren
id|skb
comma
id|redir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph-&gt;rst
op_logical_or
id|tcph-&gt;fin
)paren
(brace
id|redir-&gt;destroyme.function
op_assign
id|destroyme
suffix:semicolon
id|redir-&gt;destroyme.data
op_assign
(paren
r_int
r_int
)paren
id|redir
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|redir-&gt;destroyme
comma
l_int|75
op_star
id|HZ
)paren
suffix:semicolon
)brace
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
)brace
r_void
DECL|function|check_for_unredirect
id|check_for_unredirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
r_struct
id|redir
op_star
id|redir
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;protocol
op_ne
id|IPPROTO_TCP
)paren
r_return
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
id|redir
op_assign
id|find_unredir
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|tcph-&gt;source
comma
id|tcph-&gt;dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|redir
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Doing tcp unredirect.&bslash;n&quot;
)paren
suffix:semicolon
id|do_tcp_unredir
c_func
(paren
id|skb
comma
id|redir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph-&gt;rst
op_logical_or
id|tcph-&gt;fin
)paren
(brace
id|redir-&gt;destroyme.function
op_assign
id|destroyme
suffix:semicolon
id|redir-&gt;destroyme.data
op_assign
(paren
r_int
r_int
)paren
id|redir
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|redir-&gt;destroyme
comma
l_int|75
op_star
id|HZ
)paren
suffix:semicolon
)brace
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|redir_lock
)paren
suffix:semicolon
)brace
eof
