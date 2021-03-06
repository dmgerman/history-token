multiline_comment|/*&n; *  ebt_stp&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bdschuym@pandora.be&gt;&n; *&t;Stephen Hemminger &lt;shemminger@osdl.org&gt;&n; *&n; *  July, 2003&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_stp.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|macro|BPDU_TYPE_CONFIG
mdefine_line|#define BPDU_TYPE_CONFIG 0
DECL|macro|BPDU_TYPE_TCN
mdefine_line|#define BPDU_TYPE_TCN 0x80
DECL|struct|stp_header
r_struct
id|stp_header
(brace
DECL|member|dsap
r_uint8
id|dsap
suffix:semicolon
DECL|member|ssap
r_uint8
id|ssap
suffix:semicolon
DECL|member|ctrl
r_uint8
id|ctrl
suffix:semicolon
DECL|member|pid
r_uint8
id|pid
suffix:semicolon
DECL|member|vers
r_uint8
id|vers
suffix:semicolon
DECL|member|type
r_uint8
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stp_config_pdu
r_struct
id|stp_config_pdu
(brace
DECL|member|flags
r_uint8
id|flags
suffix:semicolon
DECL|member|root
r_uint8
id|root
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|root_cost
r_uint8
id|root_cost
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|sender
r_uint8
id|sender
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|port
r_uint8
id|port
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|msg_age
r_uint8
id|msg_age
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|max_age
r_uint8
id|max_age
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hello_time
r_uint8
id|hello_time
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|forward_delay
r_uint8
id|forward_delay
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NR16
mdefine_line|#define NR16(p) (p[0] &lt;&lt; 8 | p[1])
DECL|macro|NR32
mdefine_line|#define NR32(p) ((p[0] &lt;&lt; 24) | (p[1] &lt;&lt; 16) | (p[2] &lt;&lt; 8) | p[3])
DECL|function|ebt_filter_config
r_static
r_int
id|ebt_filter_config
c_func
(paren
r_struct
id|ebt_stp_info
op_star
id|info
comma
r_struct
id|stp_config_pdu
op_star
id|stpc
)paren
(brace
r_struct
id|ebt_stp_config_info
op_star
id|c
suffix:semicolon
r_uint16
id|v16
suffix:semicolon
r_uint32
id|v32
suffix:semicolon
r_int
id|verdict
comma
id|i
suffix:semicolon
id|c
op_assign
op_amp
id|info-&gt;config
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_FLAGS
)paren
op_logical_and
id|FWINV
c_func
(paren
id|c-&gt;flags
op_ne
id|stpc-&gt;flags
comma
id|EBT_STP_FLAGS
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_ROOTPRIO
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;root_priou
comma
id|EBT_STP_ROOTPRIO
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_ROOTADDR
)paren
(brace
id|verdict
op_assign
l_int|0
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|verdict
op_or_assign
(paren
id|stpc-&gt;root
(braket
l_int|2
op_plus
id|i
)braket
op_xor
id|c-&gt;root_addr
(braket
id|i
)braket
)paren
op_amp
id|c-&gt;root_addrmsk
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|verdict
op_ne
l_int|0
comma
id|EBT_STP_ROOTADDR
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_ROOTCOST
)paren
(brace
id|v32
op_assign
id|NR32
c_func
(paren
id|stpc-&gt;root_cost
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v32
template_param
id|c-&gt;root_costu
comma
id|EBT_STP_ROOTCOST
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_SENDERPRIO
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;sender
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;sender_priou
comma
id|EBT_STP_SENDERPRIO
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_SENDERADDR
)paren
(brace
id|verdict
op_assign
l_int|0
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|verdict
op_or_assign
(paren
id|stpc-&gt;sender
(braket
l_int|2
op_plus
id|i
)braket
op_xor
id|c-&gt;sender_addr
(braket
id|i
)braket
)paren
op_amp
id|c-&gt;sender_addrmsk
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|verdict
op_ne
l_int|0
comma
id|EBT_STP_SENDERADDR
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_PORT
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;portu
comma
id|EBT_STP_PORT
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_MSGAGE
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;msg_age
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;msg_ageu
comma
id|EBT_STP_MSGAGE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_MAXAGE
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;max_age
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;max_ageu
comma
id|EBT_STP_MAXAGE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_HELLOTIME
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;hello_time
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;hello_timeu
comma
id|EBT_STP_HELLOTIME
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_FWDD
)paren
(brace
id|v16
op_assign
id|NR16
c_func
(paren
id|stpc-&gt;forward_delay
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|v16
template_param
id|c-&gt;forward_delayu
comma
id|EBT_STP_FWDD
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_return
id|EBT_MATCH
suffix:semicolon
)brace
DECL|function|ebt_filter_stp
r_static
r_int
id|ebt_filter_stp
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
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
id|ebt_stp_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_stp_info
op_star
)paren
id|data
suffix:semicolon
r_struct
id|stp_header
id|_stph
comma
op_star
id|sp
suffix:semicolon
r_uint8
id|header
(braket
l_int|6
)braket
op_assign
(brace
l_int|0x42
comma
l_int|0x42
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
id|sp
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
id|_stph
)paren
comma
op_amp
id|_stph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_eq
l_int|NULL
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
multiline_comment|/* The stp code only considers these */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sp
comma
id|header
comma
r_sizeof
(paren
id|header
)paren
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_TYPE
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;type
op_ne
id|sp-&gt;type
comma
id|EBT_STP_TYPE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|sp-&gt;type
op_eq
id|BPDU_TYPE_CONFIG
op_logical_and
id|info-&gt;bitmask
op_amp
id|EBT_STP_CONFIG_MASK
)paren
(brace
r_struct
id|stp_config_pdu
id|_stpc
comma
op_star
id|st
suffix:semicolon
id|st
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|_stph
)paren
comma
r_sizeof
(paren
id|_stpc
)paren
comma
op_amp
id|_stpc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st
op_eq
l_int|NULL
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_return
id|ebt_filter_config
c_func
(paren
id|info
comma
id|st
)paren
suffix:semicolon
)brace
r_return
id|EBT_MATCH
suffix:semicolon
)brace
DECL|function|ebt_stp_check
r_static
r_int
id|ebt_stp_check
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
id|ebt_stp_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_stp_info
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
op_assign
id|EBT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ebt_stp_info
)paren
)paren
suffix:semicolon
r_uint8
id|bridge_ula
(braket
l_int|6
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x80
comma
l_int|0xc2
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
r_uint8
id|msk
(braket
l_int|6
)braket
op_assign
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
op_complement
id|EBT_STP_MASK
op_logical_or
id|info-&gt;invflags
op_amp
op_complement
id|EBT_STP_MASK
op_logical_or
op_logical_neg
(paren
id|info-&gt;bitmask
op_amp
id|EBT_STP_MASK
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|datalen
op_ne
id|len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Make sure the match only receives stp frames */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|e-&gt;destmac
comma
id|bridge_ula
comma
id|ETH_ALEN
)paren
op_logical_or
id|memcmp
c_func
(paren
id|e-&gt;destmsk
comma
id|msk
comma
id|ETH_ALEN
)paren
op_logical_or
op_logical_neg
(paren
id|e-&gt;bitmask
op_amp
id|EBT_DESTMAC
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_stp
r_static
r_struct
id|ebt_match
id|filter_stp
op_assign
(brace
dot
id|name
op_assign
id|EBT_STP_MATCH
comma
dot
id|match
op_assign
id|ebt_filter_stp
comma
dot
id|check
op_assign
id|ebt_stp_check
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
id|ebt_register_match
c_func
(paren
op_amp
id|filter_stp
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
id|ebt_unregister_match
c_func
(paren
op_amp
id|filter_stp
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
