multiline_comment|/*&n; *  Capabilities Linux Security Module&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
DECL|variable|capability_ops
r_static
r_struct
id|security_operations
id|capability_ops
op_assign
(brace
dot
id|ptrace
op_assign
id|cap_ptrace
comma
dot
id|capget
op_assign
id|cap_capget
comma
dot
id|capset_check
op_assign
id|cap_capset_check
comma
dot
id|capset_set
op_assign
id|cap_capset_set
comma
dot
id|capable
op_assign
id|cap_capable
comma
dot
id|settime
op_assign
id|cap_settime
comma
dot
id|netlink_send
op_assign
id|cap_netlink_send
comma
dot
id|netlink_recv
op_assign
id|cap_netlink_recv
comma
dot
id|bprm_apply_creds
op_assign
id|cap_bprm_apply_creds
comma
dot
id|bprm_set_security
op_assign
id|cap_bprm_set_security
comma
dot
id|bprm_secureexec
op_assign
id|cap_bprm_secureexec
comma
dot
id|inode_setxattr
op_assign
id|cap_inode_setxattr
comma
dot
id|inode_removexattr
op_assign
id|cap_inode_removexattr
comma
dot
id|task_post_setuid
op_assign
id|cap_task_post_setuid
comma
dot
id|task_reparent_to_init
op_assign
id|cap_task_reparent_to_init
comma
dot
id|syslog
op_assign
id|cap_syslog
comma
dot
id|vm_enough_memory
op_assign
id|cap_vm_enough_memory
comma
)brace
suffix:semicolon
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME __stringify(KBUILD_MODNAME)
multiline_comment|/* flag to keep track of how we were registered */
DECL|variable|secondary
r_static
r_int
id|secondary
suffix:semicolon
DECL|variable|capability_disable
r_static
r_int
id|capability_disable
suffix:semicolon
id|module_param_named
c_func
(paren
id|disable
comma
id|capability_disable
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|disable
comma
l_string|&quot;To disable capabilities module set disable = 1&quot;
)paren
suffix:semicolon
DECL|function|capability_init
r_static
r_int
id|__init
id|capability_init
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|capability_disable
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Capabilities disabled at initialization&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* register ourselves with the security framework */
r_if
c_cond
(paren
id|register_security
(paren
op_amp
id|capability_ops
)paren
)paren
(brace
multiline_comment|/* try registering with primary module */
r_if
c_cond
(paren
id|mod_reg_security
(paren
id|MY_NAME
comma
op_amp
id|capability_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure registering capabilities &quot;
l_string|&quot;with primary security module.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|secondary
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Capability LSM initialized%s&bslash;n&quot;
comma
id|secondary
ques
c_cond
l_string|&quot; as secondary&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|capability_exit
r_static
r_void
id|__exit
id|capability_exit
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|capability_disable
)paren
r_return
suffix:semicolon
multiline_comment|/* remove ourselves from the security framework */
r_if
c_cond
(paren
id|secondary
)paren
(brace
r_if
c_cond
(paren
id|mod_unreg_security
(paren
id|MY_NAME
comma
op_amp
id|capability_ops
)paren
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure unregistering capabilities &quot;
l_string|&quot;with primary module.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unregister_security
(paren
op_amp
id|capability_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure unregistering capabilities with the kernel&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|capability_init
id|security_initcall
(paren
id|capability_init
)paren
suffix:semicolon
DECL|variable|capability_exit
id|module_exit
(paren
id|capability_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Standard Linux Capabilities Security Module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
