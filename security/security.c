multiline_comment|/*&n; * Security plug functions&n; *&n; * Copyright (C) 2001 WireX Communications, Inc &lt;chris@wirex.com&gt;&n; * Copyright (C) 2001-2002 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (C) 2001 Networks Associates Technology, Inc &lt;ssmalley@nai.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/security.h&gt;
DECL|macro|SECURITY_FRAMEWORK_VERSION
mdefine_line|#define SECURITY_FRAMEWORK_VERSION&t;&quot;1.0.0&quot;
multiline_comment|/* things that live in dummy.c */
r_extern
r_struct
id|security_operations
id|dummy_security_ops
suffix:semicolon
r_extern
r_void
id|security_fixup_ops
c_func
(paren
r_struct
id|security_operations
op_star
id|ops
)paren
suffix:semicolon
DECL|variable|security_ops
r_struct
id|security_operations
op_star
id|security_ops
suffix:semicolon
multiline_comment|/* Initialized to NULL */
DECL|function|verify
r_static
r_inline
r_int
id|verify
c_func
(paren
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
multiline_comment|/* verify the security_operations structure exists */
r_if
c_cond
(paren
op_logical_neg
id|ops
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|security_fixup_ops
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_security_initcalls
r_static
r_void
id|__init
id|do_security_initcalls
c_func
(paren
r_void
)paren
(brace
id|initcall_t
op_star
id|call
suffix:semicolon
id|call
op_assign
op_amp
id|__security_initcall_start
suffix:semicolon
r_while
c_loop
(paren
id|call
OL
op_amp
id|__security_initcall_end
)paren
(brace
(paren
op_star
id|call
)paren
(paren
)paren
suffix:semicolon
id|call
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * security_init - initializes the security framework&n; *&n; * This should be called early in the kernel initialization sequence.&n; */
DECL|function|security_init
r_int
id|__init
id|security_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Security Framework v&quot;
id|SECURITY_FRAMEWORK_VERSION
l_string|&quot; initialized&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify
c_func
(paren
op_amp
id|dummy_security_ops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s could not verify &quot;
l_string|&quot;dummy_security_ops structure.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|security_ops
op_assign
op_amp
id|dummy_security_ops
suffix:semicolon
id|do_security_initcalls
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * register_security - registers a security framework with the kernel&n; * @ops: a pointer to the struct security_options that is to be registered&n; *&n; * This function is to allow a security module to register itself with the&n; * kernel security subsystem.  Some rudimentary checking is done on the @ops&n; * value passed to this function.  A call to unregister_security() should be&n; * done to remove this security_options structure from the kernel.&n; *&n; * If there is already a security module registered with the kernel,&n; * an error will be returned.  Otherwise 0 is returned on success.&n; */
DECL|function|register_security
r_int
id|register_security
c_func
(paren
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_if
c_cond
(paren
id|verify
c_func
(paren
id|ops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s could not verify &quot;
l_string|&quot;security_operations structure.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|security_ops
op_ne
op_amp
id|dummy_security_ops
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|security_ops
op_assign
id|ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * unregister_security - unregisters a security framework with the kernel&n; * @ops: a pointer to the struct security_options that is to be registered&n; *&n; * This function removes a struct security_operations variable that had&n; * previously been registered with a successful call to register_security().&n; *&n; * If @ops does not match the valued previously passed to register_security()&n; * an error is returned.  Otherwise the default security options is set to the&n; * the dummy_security_ops structure, and 0 is returned.&n; */
DECL|function|unregister_security
r_int
id|unregister_security
c_func
(paren
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_if
c_cond
(paren
id|ops
op_ne
id|security_ops
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: trying to unregister &quot;
l_string|&quot;a security_opts structure that is not &quot;
l_string|&quot;registered, failing.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|security_ops
op_assign
op_amp
id|dummy_security_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * mod_reg_security - allows security modules to be &quot;stacked&quot;&n; * @name: a pointer to a string with the name of the security_options to be registered&n; * @ops: a pointer to the struct security_options that is to be registered&n; *&n; * This function allows security modules to be stacked if the currently loaded&n; * security module allows this to happen.  It passes the @name and @ops to the&n; * register_security function of the currently loaded security module.&n; *&n; * The return value depends on the currently loaded security module, with 0 as&n; * success.&n; */
DECL|function|mod_reg_security
r_int
id|mod_reg_security
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_if
c_cond
(paren
id|verify
c_func
(paren
id|ops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s could not verify &quot;
l_string|&quot;security operations.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops
op_eq
id|security_ops
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s security operations &quot;
l_string|&quot;already registered.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|security_ops
op_member_access_from_pointer
id|register_security
c_func
(paren
id|name
comma
id|ops
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * mod_unreg_security - allows a security module registered with mod_reg_security() to be unloaded&n; * @name: a pointer to a string with the name of the security_options to be removed&n; * @ops: a pointer to the struct security_options that is to be removed&n; *&n; * This function allows security modules that have been successfully registered&n; * with a call to mod_reg_security() to be unloaded from the system.&n; * This calls the currently loaded security module&squot;s unregister_security() call&n; * with the @name and @ops variables.&n; *&n; * The return value depends on the currently loaded security module, with 0 as&n; * success.&n; */
DECL|function|mod_unreg_security
r_int
id|mod_unreg_security
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_if
c_cond
(paren
id|ops
op_eq
id|security_ops
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s invalid attempt to unregister &quot;
l_string|&quot; primary security ops.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|security_ops
op_member_access_from_pointer
id|unregister_security
c_func
(paren
id|name
comma
id|ops
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * capable - calls the currently loaded security module&squot;s capable() function with the specified capability&n; * @cap: the requested capability level.&n; *&n; * This function calls the currently loaded security module&squot;s capable()&n; * function with a pointer to the current task and the specified @cap value.&n; *&n; * This allows the security module to implement the capable function call&n; * however it chooses to.&n; */
DECL|function|capable
r_int
id|capable
c_func
(paren
r_int
id|cap
)paren
(brace
r_if
c_cond
(paren
id|security_ops
op_member_access_from_pointer
id|capable
c_func
(paren
id|current
comma
id|cap
)paren
)paren
(brace
multiline_comment|/* capability denied */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* capability granted */
id|current-&gt;flags
op_or_assign
id|PF_SUPERPRIV
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|register_security
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|register_security
)paren
suffix:semicolon
DECL|variable|unregister_security
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|unregister_security
)paren
suffix:semicolon
DECL|variable|mod_reg_security
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|mod_reg_security
)paren
suffix:semicolon
DECL|variable|mod_unreg_security
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|mod_unreg_security
)paren
suffix:semicolon
DECL|variable|capable
id|EXPORT_SYMBOL
c_func
(paren
id|capable
)paren
suffix:semicolon
DECL|variable|security_ops
id|EXPORT_SYMBOL
c_func
(paren
id|security_ops
)paren
suffix:semicolon
eof
