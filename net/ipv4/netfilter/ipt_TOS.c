multiline_comment|/* This is a module which is used for setting the TOS field of a packet. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_TOS.h&gt;
r_static
r_int
r_int
DECL|function|target
id|target
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
id|targinfo
comma
r_void
op_star
id|userinfo
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
r_const
r_struct
id|ipt_tos_target_info
op_star
id|tosinfo
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|iph-&gt;tos
op_amp
id|IPTOS_TOS_MASK
)paren
op_ne
id|tosinfo-&gt;tos
)paren
(brace
id|u_int16_t
id|diffs
(braket
l_int|2
)braket
suffix:semicolon
id|diffs
(braket
l_int|0
)braket
op_assign
id|htons
c_func
(paren
id|iph-&gt;tos
)paren
op_xor
l_int|0xFFFF
suffix:semicolon
id|iph-&gt;tos
op_assign
(paren
id|iph-&gt;tos
op_amp
id|IPTOS_PREC_MASK
)paren
op_or
id|tosinfo-&gt;tos
suffix:semicolon
id|diffs
(braket
l_int|1
)braket
op_assign
id|htons
c_func
(paren
id|iph-&gt;tos
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
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
id|iph-&gt;check
op_xor
l_int|0xFFFF
)paren
)paren
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
)brace
r_return
id|IPT_CONTINUE
suffix:semicolon
)brace
r_static
r_int
DECL|function|checkentry
id|checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
id|u_int8_t
id|tos
op_assign
(paren
(paren
r_struct
id|ipt_tos_target_info
op_star
)paren
id|targinfo
)paren
op_member_access_from_pointer
id|tos
suffix:semicolon
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_tos_target_info
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TOS: targinfosize %u != %Zu&bslash;n&quot;
comma
id|targinfosize
comma
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_tos_target_info
)paren
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
id|strcmp
c_func
(paren
id|tablename
comma
l_string|&quot;mangle&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TOS: can only be called from &bslash;&quot;mangle&bslash;&quot; table, not &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|tablename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tos
op_ne
id|IPTOS_LOWDELAY
op_logical_and
id|tos
op_ne
id|IPTOS_THROUGHPUT
op_logical_and
id|tos
op_ne
id|IPTOS_RELIABILITY
op_logical_and
id|tos
op_ne
id|IPTOS_MINCOST
op_logical_and
id|tos
op_ne
id|IPTOS_NORMALSVC
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TOS: bad tos value %#x&bslash;n&quot;
comma
id|tos
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ipt_tos_reg
r_static
r_struct
id|ipt_target
id|ipt_tos_reg
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;TOS&quot;
comma
id|target
comma
id|checkentry
comma
l_int|NULL
comma
id|THIS_MODULE
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
r_if
c_cond
(paren
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_tos_reg
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_tos_reg
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
