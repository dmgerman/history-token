multiline_comment|/* FTP extension for TCP NAT alteration. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_ftp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|macro|MAX_PORTS
mdefine_line|#define MAX_PORTS 8
DECL|variable|ports
r_static
r_int
id|ports
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|ports_c
r_static
r_int
id|ports_c
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE_PARM
id|MODULE_PARM
c_func
(paren
id|ports
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|ip_ftp_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_ftp_lock
)paren
suffix:semicolon
multiline_comment|/* FIXME: Time out? --RR */
r_static
r_int
r_int
DECL|function|ftp_nat_expected
id|ftp_nat_expected
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_nat_info
op_star
id|info
)paren
(brace
r_struct
id|ip_nat_multi_range
id|mr
suffix:semicolon
id|u_int32_t
id|newdstip
comma
id|newsrcip
comma
id|newip
suffix:semicolon
r_struct
id|ip_ct_ftp_expect
op_star
id|exp_ftp_info
suffix:semicolon
r_struct
id|ip_conntrack
op_star
id|master
op_assign
id|master_ct
c_func
(paren
id|ct
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|info
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|master
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
op_logical_neg
(paren
id|info-&gt;initialized
op_amp
(paren
l_int|1
op_lshift
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
)paren
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: We have a connection!&bslash;n&quot;
)paren
suffix:semicolon
id|exp_ftp_info
op_assign
op_amp
id|ct-&gt;master-&gt;help.exp_ftp_info
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp_ftp_info-&gt;ftptype
op_eq
id|IP_CT_FTP_PORT
op_logical_or
id|exp_ftp_info-&gt;ftptype
op_eq
id|IP_CT_FTP_EPRT
)paren
(brace
multiline_comment|/* PORT command: make connection go to the client. */
id|newdstip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|newsrcip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.ip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: PORT cmd. %u.%u.%u.%u-&gt;%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|newsrcip
)paren
comma
id|NIPQUAD
c_func
(paren
id|newdstip
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* PASV command: make the connection go to the server */
id|newdstip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|newsrcip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: PASV cmd. %u.%u.%u.%u-&gt;%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|newsrcip
)paren
comma
id|NIPQUAD
c_func
(paren
id|newdstip
)paren
)paren
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|newip
op_assign
id|newsrcip
suffix:semicolon
r_else
id|newip
op_assign
id|newdstip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: IP to %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|newip
)paren
)paren
suffix:semicolon
id|mr.rangesize
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We don&squot;t want to manip the per-protocol, just the IPs... */
id|mr.range
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IP_NAT_RANGE_MAP_IPS
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|min_ip
op_assign
id|mr.range
(braket
l_int|0
)braket
dot
id|max_ip
op_assign
id|newip
suffix:semicolon
multiline_comment|/* ... unless we&squot;re doing a MANIP_DST, in which case, make&n;&t;   sure we map to the correct port */
r_if
c_cond
(paren
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
op_eq
id|IP_NAT_MANIP_DST
)paren
(brace
id|mr.range
(braket
l_int|0
)braket
dot
id|flags
op_or_assign
id|IP_NAT_RANGE_PROTO_SPECIFIED
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|min
op_assign
id|mr.range
(braket
l_int|0
)braket
dot
id|max
op_assign
(paren
(paren
r_union
id|ip_conntrack_manip_proto
)paren
(brace
dot
id|tcp
op_assign
(brace
id|htons
c_func
(paren
id|exp_ftp_info-&gt;port
)paren
)brace
)brace
)paren
suffix:semicolon
)brace
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|mr
comma
id|hooknum
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|mangle_rfc959_packet
id|mangle_rfc959_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
id|u_int32_t
id|newip
comma
id|u_int16_t
id|port
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;nnn,nnn,nnn,nnn,nnn,nnn&quot;
)paren
)braket
suffix:semicolon
id|MUST_BE_LOCKED
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%u,%u,%u,%u,%u,%u&quot;
comma
id|NIPQUAD
c_func
(paren
id|newip
)paren
comma
id|port
op_rshift
l_int|8
comma
id|port
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;calling ip_nat_mangle_tcp_packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ip_nat_mangle_tcp_packet
c_func
(paren
id|pskb
comma
id|ct
comma
id|ctinfo
comma
id|matchoff
comma
id|matchlen
comma
id|buffer
comma
id|strlen
c_func
(paren
id|buffer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* |1|132.235.1.2|6275| */
r_static
r_int
DECL|function|mangle_eprt_packet
id|mangle_eprt_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
id|u_int32_t
id|newip
comma
id|u_int16_t
id|port
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;|1|255.255.255.255|65535|&quot;
)paren
)braket
suffix:semicolon
id|MUST_BE_LOCKED
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;|1|%u.%u.%u.%u|%u|&quot;
comma
id|NIPQUAD
c_func
(paren
id|newip
)paren
comma
id|port
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;calling ip_nat_mangle_tcp_packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ip_nat_mangle_tcp_packet
c_func
(paren
id|pskb
comma
id|ct
comma
id|ctinfo
comma
id|matchoff
comma
id|matchlen
comma
id|buffer
comma
id|strlen
c_func
(paren
id|buffer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* |1|132.235.1.2|6275| */
r_static
r_int
DECL|function|mangle_epsv_packet
id|mangle_epsv_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
id|u_int32_t
id|newip
comma
id|u_int16_t
id|port
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;|||65535|&quot;
)paren
)braket
suffix:semicolon
id|MUST_BE_LOCKED
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;|||%u|&quot;
comma
id|port
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;calling ip_nat_mangle_tcp_packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ip_nat_mangle_tcp_packet
c_func
(paren
id|pskb
comma
id|ct
comma
id|ctinfo
comma
id|matchoff
comma
id|matchlen
comma
id|buffer
comma
id|strlen
c_func
(paren
id|buffer
)paren
)paren
suffix:semicolon
)brace
DECL|variable|mangle
r_static
r_int
(paren
op_star
id|mangle
(braket
)braket
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
comma
id|u_int32_t
comma
id|u_int16_t
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|ip_conntrack
op_star
comma
r_enum
id|ip_conntrack_info
)paren
op_assign
(brace
(braket
id|IP_CT_FTP_PORT
)braket
op_assign
id|mangle_rfc959_packet
comma
(braket
id|IP_CT_FTP_PASV
)braket
op_assign
id|mangle_rfc959_packet
comma
(braket
id|IP_CT_FTP_EPRT
)braket
op_assign
id|mangle_eprt_packet
comma
(braket
id|IP_CT_FTP_EPSV
)braket
op_assign
id|mangle_epsv_packet
)brace
suffix:semicolon
DECL|function|ftp_data_fixup
r_static
r_int
id|ftp_data_fixup
c_func
(paren
r_const
r_struct
id|ip_ct_ftp_expect
op_star
id|ct_ftp_info
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_struct
id|ip_conntrack_expect
op_star
id|expect
)paren
(brace
id|u_int32_t
id|newip
suffix:semicolon
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
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|u_int16_t
id|port
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|newtuple
suffix:semicolon
id|MUST_BE_LOCKED
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;FTP_NAT: seq %u + %u in %u&bslash;n&quot;
comma
id|expect-&gt;seq
comma
id|ct_ftp_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
)paren
suffix:semicolon
multiline_comment|/* Change address inside packet to match way we&squot;re mapping&n;&t;   this connection. */
r_if
c_cond
(paren
id|ct_ftp_info-&gt;ftptype
op_eq
id|IP_CT_FTP_PASV
op_logical_or
id|ct_ftp_info-&gt;ftptype
op_eq
id|IP_CT_FTP_EPSV
)paren
(brace
multiline_comment|/* PASV/EPSV response: must be where client thinks server&n;&t;&t;   is */
id|newip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.ip
suffix:semicolon
multiline_comment|/* Expect something from client-&gt;server */
id|newtuple.src.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|newtuple.dst.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.ip
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* PORT command: must be where server thinks client is */
id|newip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
suffix:semicolon
multiline_comment|/* Expect something from server-&gt;client */
id|newtuple.src.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|newtuple.dst.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
suffix:semicolon
)brace
id|newtuple.dst.protonum
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|newtuple.src.u.tcp.port
op_assign
id|expect-&gt;tuple.src.u.tcp.port
suffix:semicolon
multiline_comment|/* Try to get same port: if not, try to change it. */
r_for
c_loop
(paren
id|port
op_assign
id|ct_ftp_info-&gt;port
suffix:semicolon
id|port
op_ne
l_int|0
suffix:semicolon
id|port
op_increment
)paren
(brace
id|newtuple.dst.u.tcp.port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip_conntrack_change_expect
c_func
(paren
id|expect
comma
op_amp
id|newtuple
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mangle
(braket
id|ct_ftp_info-&gt;ftptype
)braket
(paren
id|pskb
comma
id|newip
comma
id|port
comma
id|expect-&gt;seq
op_minus
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ct_ftp_info-&gt;len
comma
id|ct
comma
id|ctinfo
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|help
r_static
r_int
r_int
id|help
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
r_struct
id|ip_nat_info
op_star
id|info
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|hooknum
comma
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
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|datalen
suffix:semicolon
r_int
id|dir
suffix:semicolon
r_struct
id|ip_ct_ftp_expect
op_star
id|ct_ftp_info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
)paren
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_ftp: no exp!!&quot;
)paren
suffix:semicolon
id|ct_ftp_info
op_assign
op_amp
id|exp-&gt;help.exp_ftp_info
suffix:semicolon
multiline_comment|/* Only mangle things once: original direction in POST_ROUTING&n;&t;   and reply direction on PRE_ROUTING. */
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
op_logical_and
id|dir
op_eq
id|IP_CT_DIR_ORIGINAL
)paren
op_logical_or
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
op_logical_and
id|dir
op_eq
id|IP_CT_DIR_REPLY
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;nat_ftp: Not touching dir %s at hook %s&bslash;n&quot;
comma
id|dir
op_eq
id|IP_CT_DIR_ORIGINAL
ques
c_cond
l_string|&quot;ORIG&quot;
suffix:colon
l_string|&quot;REPLY&quot;
comma
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
ques
c_cond
l_string|&quot;POSTROUTING&quot;
suffix:colon
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
ques
c_cond
l_string|&quot;PREROUTING&quot;
suffix:colon
id|hooknum
op_eq
id|NF_IP_LOCAL_OUT
ques
c_cond
l_string|&quot;OUTPUT&quot;
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|datalen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
op_minus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s in the right range... */
r_if
c_cond
(paren
id|between
c_func
(paren
id|exp-&gt;seq
op_plus
id|ct_ftp_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ftp_data_fixup
c_func
(paren
id|ct_ftp_info
comma
id|ct
comma
id|pskb
comma
id|ctinfo
comma
id|exp
)paren
)paren
(brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Half a match?  This means a partial retransmisison.&n;&t;&t;   It&squot;s a cracker being funky. */
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FTP_NAT: partial packet %u/%u in %u/%u&bslash;n&quot;
comma
id|exp-&gt;seq
comma
id|ct_ftp_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
)paren
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|variable|ftp
r_static
r_struct
id|ip_nat_helper
id|ftp
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|ftp_names
r_static
r_char
id|ftp_names
(braket
id|MAX_PORTS
)braket
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Not __exit: called from init() */
DECL|function|fini
r_static
r_void
id|fini
c_func
(paren
r_void
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
id|ports_c
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_ftp: unregistering port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ip_nat_helper_unregister
c_func
(paren
op_amp
id|ftp
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
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
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|tmpname
suffix:semicolon
r_if
c_cond
(paren
id|ports
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
id|ports
(braket
l_int|0
)braket
op_assign
id|FTP_PORT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|MAX_PORTS
)paren
op_logical_and
id|ports
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ftp
(braket
id|i
)braket
dot
id|tuple.dst.protonum
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|tuple.src.u.tcp.port
op_assign
id|htons
c_func
(paren
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|mask.dst.protonum
op_assign
l_int|0xFFFF
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|mask.src.u.tcp.port
op_assign
l_int|0xFFFF
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|help
op_assign
id|help
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|me
op_assign
id|THIS_MODULE
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|expect
op_assign
id|ftp_nat_expected
suffix:semicolon
id|tmpname
op_assign
op_amp
id|ftp_names
(braket
id|i
)braket
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
op_eq
id|FTP_PORT
)paren
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;ftp&quot;
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;ftp-%d&quot;
comma
id|i
)paren
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|name
op_assign
id|tmpname
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_ftp: Trying to register for port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
id|ip_nat_helper_register
c_func
(paren
op_amp
id|ftp
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_ftp: error registering &quot;
l_string|&quot;helper for port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|fini
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ports_c
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ftp
id|NEEDS_CONNTRACK
c_func
(paren
id|ftp
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
