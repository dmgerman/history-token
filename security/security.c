multiline_comment|/*&n; * Security plug functions&n; *&n; * Copyright (C) 2001 WireX Communications, Inc &lt;chris@wirex.com&gt;&n; * Copyright (C) 2001 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (C) 2001 Networks Associates Technology, Inc &lt;ssmalley@nai.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/security.h&gt;
DECL|macro|SECURITY_SCAFFOLD_VERSION
mdefine_line|#define SECURITY_SCAFFOLD_VERSION&t;&quot;1.0.0&quot;
r_extern
r_struct
id|security_operations
id|dummy_security_ops
suffix:semicolon
multiline_comment|/* lives in dummy.c */
DECL|variable|security_ops
r_struct
id|security_operations
op_star
id|security_ops
suffix:semicolon
multiline_comment|/* Initialized to NULL */
multiline_comment|/* This macro checks that all pointers in a struct are non-NULL.  It &n; * can be fooled by struct padding for object tile alignment and when&n; * pointers to data and pointers to functions aren&squot;t the same size.&n; * Yes it&squot;s ugly, we&squot;ll replace it if it becomes a problem.&n; */
DECL|macro|VERIFY_STRUCT
mdefine_line|#define VERIFY_STRUCT(struct_type, s, e) &bslash;&n;&t;do { &bslash;&n;&t;&t;unsigned long * __start = (unsigned long *)(s); &bslash;&n;&t;&t;unsigned long * __end = __start + &bslash;&n;&t;&t;&t;&t;sizeof(struct_type)/sizeof(unsigned long *); &bslash;&n;&t;&t;while (__start != __end) { &bslash;&n;&t;&t;&t;if (!*__start) { &bslash;&n;&t;&t;&t;&t;printk(KERN_INFO &quot;%s is missing something&bslash;n&quot;,&bslash;&n;&t;&t;&t;&t;&t;#struct_type); &bslash;&n;&t;&t;&t;&t;e++; &bslash;&n;&t;&t;&t;&t;break; &bslash;&n;&t;&t;&t;} &bslash;&n;&t;&t;&t;__start++; &bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
DECL|function|verify
r_static
r_int
r_inline
id|verify
(paren
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* verify the security_operations structure exists */
r_if
c_cond
(paren
op_logical_neg
id|ops
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Passed a NULL security_operations &quot;
l_string|&quot;pointer, &quot;
id|__FUNCTION__
l_string|&quot; failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Perform a little sanity checking on our inputs */
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This first check scans the whole security_ops struct for&n;&t; * missing structs or functions.&n;&t; *&n;&t; * (There is no further check now, but will leave as is until&n;&t; *  the lazy registration stuff is done -- JM).&n;&t; */
id|VERIFY_STRUCT
c_func
(paren
r_struct
id|security_operations
comma
id|ops
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Not enough functions specified in the &quot;
l_string|&quot;security_operation structure, &quot;
id|__FUNCTION__
l_string|&quot; failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * security_scaffolding_startup - initialzes the security scaffolding framework&n; *&n; * This should be called early in the kernel initialization sequence.&n; */
DECL|function|security_scaffolding_startup
r_int
id|security_scaffolding_startup
(paren
r_void
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Security Scaffold v&quot;
id|SECURITY_SCAFFOLD_VERSION
l_string|&quot; initialized&bslash;n&quot;
)paren
suffix:semicolon
id|security_ops
op_assign
op_amp
id|dummy_security_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * register_security - registers a security framework with the kernel&n; * @ops: a pointer to the struct security_options that is to be registered&n; *&n; * This function is to allow a security module to register itself with the&n; * kernel security subsystem.  Some rudimentary checking is done on the @ops&n; * value passed to this function.  A call to unregister_security() should be&n; * done to remove this security_options structure from the kernel.&n; *&n; * If the @ops structure does not contain function pointers for all hooks in&n; * the structure, or there is already a security module registered with the&n; * kernel, an error will be returned.  Otherwise 0 is returned on success.&n; */
DECL|function|register_security
r_int
id|register_security
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
(paren
id|ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|__FUNCTION__
l_string|&quot; could not verify &quot;
l_string|&quot;security_operations structure.&bslash;n&quot;
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
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;There is already a security &quot;
l_string|&quot;framework initialized, &quot;
id|__FUNCTION__
l_string|&quot; failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
(paren
id|KERN_INFO
id|__FUNCTION__
l_string|&quot;: trying to unregister &quot;
l_string|&quot;a security_opts structure that is not &quot;
l_string|&quot;registered, failing.&bslash;n&quot;
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
(paren
id|ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|__FUNCTION__
l_string|&quot; could not verify &quot;
l_string|&quot;security operations.&bslash;n&quot;
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
(paren
id|KERN_INFO
id|__FUNCTION__
l_string|&quot; security operations &quot;
l_string|&quot;already registered.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|security_ops-&gt;register_security
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
(paren
id|KERN_INFO
id|__FUNCTION__
l_string|&quot; invalid attempt to unregister &quot;
l_string|&quot; primary security ops.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|security_ops-&gt;unregister_security
(paren
id|name
comma
id|ops
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * capable - calls the currently loaded security module&squot;s capable() function with the specified capability&n; * @cap: the requested capability level.&n; *&n; * This function calls the currently loaded security module&squot;s cabable()&n; * function with a pointer to the current task and the specified @cap value.&n; *&n; * This allows the security module to implement the capable function call&n; * however it chooses to.&n; */
DECL|function|capable
r_int
id|capable
(paren
r_int
id|cap
)paren
(brace
r_if
c_cond
(paren
id|security_ops-&gt;capable
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
multiline_comment|/**&n; * sys_security - security syscall multiplexor.&n; * @id: module id&n; * @call: call identifier&n; * @args: arg list for call&n; *&n; * Similar to sys_socketcall.  Can use id to help identify which module user&n; * app is talking to.  The recommended convention for creating the&n; * hexadecimal id value is:&n; * &squot;echo &quot;Name_of_module&quot; | md5sum | cut -c -8&squot;.&n; * By following this convention, there&squot;s no need for a central registry.&n; */
DECL|function|sys_security
id|asmlinkage
r_int
id|sys_security
(paren
r_int
r_int
id|id
comma
r_int
r_int
id|call
comma
r_int
r_int
op_star
id|args
)paren
(brace
r_return
id|security_ops-&gt;sys_security
(paren
id|id
comma
id|call
comma
id|args
)paren
suffix:semicolon
)brace
DECL|variable|register_security
id|EXPORT_SYMBOL
(paren
id|register_security
)paren
suffix:semicolon
DECL|variable|unregister_security
id|EXPORT_SYMBOL
(paren
id|unregister_security
)paren
suffix:semicolon
DECL|variable|mod_reg_security
id|EXPORT_SYMBOL
(paren
id|mod_reg_security
)paren
suffix:semicolon
DECL|variable|mod_unreg_security
id|EXPORT_SYMBOL
(paren
id|mod_unreg_security
)paren
suffix:semicolon
DECL|variable|capable
id|EXPORT_SYMBOL
(paren
id|capable
)paren
suffix:semicolon
DECL|variable|security_ops
id|EXPORT_SYMBOL
(paren
id|security_ops
)paren
suffix:semicolon
eof
