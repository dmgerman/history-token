multiline_comment|/*&n; * This is a module which is used for setting the skb-&gt;priority field&n; * of an skb for qdisc classification.&n; */
multiline_comment|/* (C) 2001-2002 Patrick McHardy &lt;kaber@trash.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_CLASSIFY.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Patrick McHardy &lt;kaber@trash.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables qdisc classification target module&quot;
)paren
suffix:semicolon
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
r_int
r_int
id|hooknum
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
r_const
r_struct
id|ipt_classify_target_info
op_star
id|clinfo
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|priority
op_ne
id|clinfo-&gt;priority
)paren
(brace
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|priority
op_assign
id|clinfo-&gt;priority
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
id|ipt_classify_target_info
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CLASSIFY: invalid size (%u != %Zu).&bslash;n&quot;
comma
id|targinfosize
comma
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_classify_target_info
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
id|hook_mask
op_amp
op_complement
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CLASSIFY: only valid in POST_ROUTING.&bslash;n&quot;
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
l_string|&quot;CLASSIFY: can only be called from &quot;
l_string|&quot;&bslash;&quot;mangle&bslash;&quot; table, not &bslash;&quot;%s&bslash;&quot;.&bslash;n&quot;
comma
id|tablename
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
DECL|variable|ipt_classify_reg
r_static
r_struct
id|ipt_target
id|ipt_classify_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CLASSIFY&quot;
comma
dot
id|target
op_assign
id|target
comma
dot
id|checkentry
op_assign
id|checkentry
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
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_classify_reg
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_classify_reg
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
eof
