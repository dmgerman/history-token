multiline_comment|/* Copyright (c) 2004 Coraid, Inc.  See COPYING for GPL terms. */
multiline_comment|/*&n; * aoenet.c&n; * Ethernet portion of AoE driver&n; */
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;aoe.h&quot;
DECL|macro|NECODES
mdefine_line|#define NECODES 5
DECL|variable|aoe_errlist
r_static
r_char
op_star
id|aoe_errlist
(braket
)braket
op_assign
(brace
l_string|&quot;no such error&quot;
comma
l_string|&quot;unrecognized command code&quot;
comma
l_string|&quot;bad argument parameter&quot;
comma
l_string|&quot;device unavailable&quot;
comma
l_string|&quot;config string present&quot;
comma
l_string|&quot;unsupported version&quot;
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IFLISTSZ
id|IFLISTSZ
op_assign
l_int|1024
comma
)brace
suffix:semicolon
DECL|variable|aoe_iflist
r_static
r_char
id|aoe_iflist
(braket
id|IFLISTSZ
)braket
suffix:semicolon
r_int
DECL|function|is_aoe_netif
id|is_aoe_netif
c_func
(paren
r_struct
id|net_device
op_star
id|ifp
)paren
(brace
r_register
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_register
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|aoe_iflist
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|aoe_iflist
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_assign
id|q
op_plus
id|strspn
c_func
(paren
id|q
comma
id|WHITESPACE
)paren
)paren
(brace
id|q
op_assign
id|p
op_plus
id|strcspn
c_func
(paren
id|p
comma
id|WHITESPACE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
op_ne
id|p
)paren
id|len
op_assign
id|q
op_minus
id|p
suffix:semicolon
r_else
id|len
op_assign
id|strlen
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* last token in aoe_iflist */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|ifp-&gt;name
)paren
op_eq
id|len
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|ifp-&gt;name
comma
id|p
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|q
op_eq
id|p
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|set_aoe_iflist
id|set_aoe_iflist
c_func
(paren
r_const
r_char
id|__user
op_star
id|user_str
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
op_ge
id|IFLISTSZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|aoe_iflist
comma
id|user_str
comma
id|size
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: %s: copy from user failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|aoe_iflist
(braket
id|size
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|u64
DECL|function|mac_addr
id|mac_addr
c_func
(paren
r_char
id|addr
(braket
l_int|6
)braket
)paren
(brace
id|u64
id|n
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
op_amp
id|n
suffix:semicolon
id|memcpy
c_func
(paren
id|p
op_plus
l_int|2
comma
id|addr
comma
l_int|6
)paren
suffix:semicolon
multiline_comment|/* (sizeof addr != 6) */
r_return
id|__be64_to_cpu
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|skb_check
id|skb_check
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb_is_nonlinear
c_func
(paren
id|skb
)paren
)paren
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_share_check
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_if
c_cond
(paren
id|skb_linearize
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
OL
l_int|0
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
r_void
DECL|function|aoenet_xmit
id|aoenet_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|sl
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|sl
)paren
)paren
(brace
id|sl
op_assign
id|sl-&gt;next
suffix:semicolon
id|skb-&gt;next
op_assign
id|skb-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * (1) len doesn&squot;t include the header by default.  I want this. &n; */
r_static
r_int
DECL|function|aoenet_rcv
id|aoenet_rcv
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
id|ifp
comma
r_struct
id|packet_type
op_star
id|pt
)paren
(brace
r_struct
id|aoe_hdr
op_star
id|h
suffix:semicolon
id|ulong
id|n
suffix:semicolon
id|skb
op_assign
id|skb_check
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_aoe_netif
c_func
(paren
id|ifp
)paren
)paren
r_goto
m_exit
suffix:semicolon
singleline_comment|//skb-&gt;len += ETH_HLEN;&t;/* (1) */
id|skb_push
c_func
(paren
id|skb
comma
id|ETH_HLEN
)paren
suffix:semicolon
multiline_comment|/* (1) */
id|h
op_assign
(paren
r_struct
id|aoe_hdr
op_star
)paren
id|skb-&gt;mac.raw
suffix:semicolon
id|n
op_assign
id|__be32_to_cpu
c_func
(paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|h-&gt;tag
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|h-&gt;verfl
op_amp
id|AOEFL_RSP
)paren
op_eq
l_int|0
op_logical_or
(paren
id|n
op_amp
l_int|1
op_lshift
l_int|31
)paren
)paren
r_goto
m_exit
suffix:semicolon
r_if
c_cond
(paren
id|h-&gt;verfl
op_amp
id|AOEFL_ERR
)paren
(brace
id|n
op_assign
id|h-&gt;err
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|NECODES
)paren
id|n
op_assign
l_int|0
suffix:semicolon
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
l_string|&quot;aoe: aoenet_rcv: error packet from %d.%d; &quot;
l_string|&quot;ecode=%d &squot;%s&squot;&bslash;n&quot;
comma
id|__be16_to_cpu
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|h-&gt;major
)paren
)paren
comma
id|h-&gt;minor
comma
id|h-&gt;err
comma
id|aoe_errlist
(braket
id|n
)braket
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|h-&gt;cmd
)paren
(brace
r_case
id|AOECMD_ATA
suffix:colon
id|aoecmd_ata_rsp
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AOECMD_CFG
suffix:colon
id|aoecmd_cfg_rsp
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: aoenet_rcv: unknown cmd %d&bslash;n&quot;
comma
id|h-&gt;cmd
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|aoe_pt
r_static
r_struct
id|packet_type
id|aoe_pt
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_AOE
)paren
comma
dot
id|func
op_assign
id|aoenet_rcv
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|aoenet_init
id|aoenet_init
c_func
(paren
r_void
)paren
(brace
id|dev_add_pack
c_func
(paren
op_amp
id|aoe_pt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|aoenet_exit
id|aoenet_exit
c_func
(paren
r_void
)paren
(brace
id|dev_remove_pack
c_func
(paren
op_amp
id|aoe_pt
)paren
suffix:semicolon
)brace
eof
