multiline_comment|/*&n; * Filtering ARP tables module.&n; *&n; * Copyright (C) 2002 David S. Miller (davem@redhat.com)&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_arp/arp_tables.h&gt;
DECL|macro|FILTER_VALID_HOOKS
mdefine_line|#define FILTER_VALID_HOOKS ((1 &lt;&lt; NF_ARP_IN) | (1 &lt;&lt; NF_ARP_OUT))
multiline_comment|/* Standard entry. */
DECL|struct|arpt_standard
r_struct
id|arpt_standard
(brace
DECL|member|entry
r_struct
id|arpt_entry
id|entry
suffix:semicolon
DECL|member|target
r_struct
id|arpt_standard_target
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arpt_error_target
r_struct
id|arpt_error_target
(brace
DECL|member|target
r_struct
id|arpt_entry_target
id|target
suffix:semicolon
DECL|member|errorname
r_char
id|errorname
(braket
id|ARPT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arpt_error
r_struct
id|arpt_error
(brace
DECL|member|entry
r_struct
id|arpt_entry
id|entry
suffix:semicolon
DECL|member|target
r_struct
id|arpt_error_target
id|target
suffix:semicolon
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|repl
r_struct
id|arpt_replace
id|repl
suffix:semicolon
DECL|member|entries
r_struct
id|arpt_standard
id|entries
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|term
r_struct
id|arpt_error
id|term
suffix:semicolon
DECL|variable|__initdata
)brace
id|initial_table
id|__initdata
op_assign
(brace
(brace
l_string|&quot;filter&quot;
comma
id|FILTER_VALID_HOOKS
comma
l_int|3
comma
r_sizeof
(paren
r_struct
id|arpt_standard
)paren
op_star
l_int|2
op_plus
r_sizeof
(paren
r_struct
id|arpt_error
)paren
comma
(brace
(braket
id|NF_ARP_IN
)braket
l_int|0
comma
(braket
id|NF_ARP_OUT
)braket
r_sizeof
(paren
r_struct
id|arpt_standard
)paren
)brace
comma
(brace
(braket
id|NF_ARP_IN
)braket
l_int|0
comma
(braket
id|NF_ARP_OUT
)braket
r_sizeof
(paren
r_struct
id|arpt_standard
)paren
comma
)brace
comma
l_int|0
comma
l_int|NULL
comma
(brace
)brace
)brace
comma
(brace
multiline_comment|/* ARP_IN */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
(brace
(brace
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
(brace
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
)brace
comma
r_sizeof
(paren
r_struct
id|arpt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|arpt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|ARPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|arpt_standard_target
)paren
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* ARP_OUT */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
(brace
(brace
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
(brace
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
)brace
comma
r_sizeof
(paren
r_struct
id|arpt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|arpt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|ARPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|arpt_standard_target
)paren
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
)brace
comma
multiline_comment|/* ERROR */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
(brace
(brace
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
(brace
l_int|0
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
)brace
comma
r_sizeof
(paren
r_struct
id|arpt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|arpt_error
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|ARPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|arpt_error_target
)paren
)paren
comma
id|ARPT_ERROR_TARGET
)brace
)brace
comma
(brace
)brace
)brace
comma
l_string|&quot;ERROR&quot;
)brace
)brace
)brace
suffix:semicolon
DECL|variable|packet_filter
r_static
r_struct
id|arpt_table
id|packet_filter
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;filter&quot;
comma
op_amp
id|initial_table.repl
comma
id|FILTER_VALID_HOOKS
comma
id|RW_LOCK_UNLOCKED
comma
l_int|NULL
comma
id|THIS_MODULE
)brace
suffix:semicolon
multiline_comment|/* The work comes in here from netfilter.c */
DECL|function|arpt_hook
r_static
r_int
r_int
id|arpt_hook
c_func
(paren
r_int
r_int
id|hook
comma
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
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
r_return
id|arpt_do_table
c_func
(paren
id|pskb
comma
id|hook
comma
id|in
comma
id|out
comma
op_amp
id|packet_filter
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|arpt_ops
r_static
r_struct
id|nf_hook_ops
id|arpt_ops
(braket
)braket
op_assign
(brace
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|arpt_hook
comma
id|NF_ARP
comma
id|NF_ARP_IN
comma
l_int|0
)brace
comma
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|arpt_hook
comma
id|NF_ARP
comma
id|NF_ARP_OUT
comma
l_int|0
)brace
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
r_int
id|ret
suffix:semicolon
multiline_comment|/* Register table */
id|ret
op_assign
id|arpt_register_table
c_func
(paren
op_amp
id|packet_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* Register hooks */
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|arpt_ops
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|cleanup_table
suffix:semicolon
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|arpt_ops
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|cleanup_hook0
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|cleanup_hook0
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|arpt_ops
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|cleanup_table
suffix:colon
id|arpt_unregister_table
c_func
(paren
op_amp
id|packet_filter
)paren
suffix:semicolon
r_return
id|ret
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
r_int
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
r_sizeof
(paren
id|arpt_ops
)paren
op_div
r_sizeof
(paren
r_struct
id|nf_hook_ops
)paren
suffix:semicolon
id|i
op_increment
)paren
id|nf_unregister_hook
c_func
(paren
op_amp
id|arpt_ops
(braket
id|i
)braket
)paren
suffix:semicolon
id|arpt_unregister_table
c_func
(paren
op_amp
id|packet_filter
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