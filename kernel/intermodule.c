multiline_comment|/* Deprecated, do not use.  Moved from module.c to here. --RR */
multiline_comment|/* Written by Keith Owens &lt;kaos@ocs.com.au&gt; Oct 2000 */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
multiline_comment|/* inter_module functions are always available, even when the kernel is&n; * compiled without modules.  Consumers of inter_module_xxx routines&n; * will always work, even when both are built into the kernel, this&n; * approach removes lots of #ifdefs in mainline code.&n; */
DECL|variable|ime_list
r_static
r_struct
id|list_head
id|ime_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|ime_list
)paren
suffix:semicolon
DECL|variable|ime_lock
r_static
id|spinlock_t
id|ime_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|kmalloc_failed
r_static
r_int
id|kmalloc_failed
suffix:semicolon
DECL|struct|inter_module_entry
r_struct
id|inter_module_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|im_name
r_const
r_char
op_star
id|im_name
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|userdata
r_const
r_void
op_star
id|userdata
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * inter_module_register - register a new set of inter module data.&n; * @im_name: an arbitrary string to identify the data, must be unique&n; * @owner: module that is registering the data, always use THIS_MODULE&n; * @userdata: pointer to arbitrary userdata to be registered&n; *&n; * Description: Check that the im_name has not already been registered,&n; * complain if it has.  For new data, add it to the inter_module_entry&n; * list.&n; */
DECL|function|inter_module_register
r_void
id|inter_module_register
c_func
(paren
r_const
r_char
op_star
id|im_name
comma
r_struct
id|module
op_star
id|owner
comma
r_const
r_void
op_star
id|userdata
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|inter_module_entry
op_star
id|ime
comma
op_star
id|ime_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ime_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ime
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
multiline_comment|/* Overloaded kernel, not fatal */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Aiee, inter_module_register: cannot kmalloc entry for &squot;%s&squot;&bslash;n&quot;
comma
id|im_name
)paren
suffix:semicolon
id|kmalloc_failed
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ime_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ime_new
)paren
)paren
suffix:semicolon
id|ime_new-&gt;im_name
op_assign
id|im_name
suffix:semicolon
id|ime_new-&gt;owner
op_assign
id|owner
suffix:semicolon
id|ime_new-&gt;userdata
op_assign
id|userdata
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|ime_list
)paren
(brace
id|ime
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inter_module_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ime-&gt;im_name
comma
id|im_name
)paren
op_eq
l_int|0
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ime_new
)paren
suffix:semicolon
multiline_comment|/* Program logic error, fatal */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;inter_module_register: duplicate im_name &squot;%s&squot;&quot;
comma
id|im_name
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|list_add
c_func
(paren
op_amp
(paren
id|ime_new-&gt;list
)paren
comma
op_amp
id|ime_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * inter_module_unregister - unregister a set of inter module data.&n; * @im_name: an arbitrary string to identify the data, must be unique&n; *&n; * Description: Check that the im_name has been registered, complain if&n; * it has not.  For existing data, remove it from the&n; * inter_module_entry list.&n; */
DECL|function|inter_module_unregister
r_void
id|inter_module_unregister
c_func
(paren
r_const
r_char
op_star
id|im_name
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|inter_module_entry
op_star
id|ime
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|ime_list
)paren
(brace
id|ime
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inter_module_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ime-&gt;im_name
comma
id|im_name
)paren
op_eq
l_int|0
)paren
(brace
id|list_del
c_func
(paren
op_amp
(paren
id|ime-&gt;list
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ime
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kmalloc_failed
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;inter_module_unregister: no entry for &squot;%s&squot;, &quot;
l_string|&quot;probably caused by previous kmalloc failure&bslash;n&quot;
comma
id|im_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Program logic error, fatal */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;inter_module_unregister: no entry for &squot;%s&squot;&quot;
comma
id|im_name
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * inter_module_get - return arbitrary userdata from another module.&n; * @im_name: an arbitrary string to identify the data, must be unique&n; *&n; * Description: If the im_name has not been registered, return NULL.&n; * Try to increment the use count on the owning module, if that fails&n; * then return NULL.  Otherwise return the userdata.&n; */
DECL|function|inter_module_get
r_const
r_void
op_star
id|inter_module_get
c_func
(paren
r_const
r_char
op_star
id|im_name
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|inter_module_entry
op_star
id|ime
suffix:semicolon
r_const
r_void
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|ime_list
)paren
(brace
id|ime
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inter_module_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ime-&gt;im_name
comma
id|im_name
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|try_module_get
c_func
(paren
id|ime-&gt;owner
)paren
)paren
id|result
op_assign
id|ime-&gt;userdata
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * inter_module_get_request - im get with automatic request_module.&n; * @im_name: an arbitrary string to identify the data, must be unique&n; * @modname: module that is expected to register im_name&n; *&n; * Description: If inter_module_get fails, do request_module then retry.&n; */
DECL|function|inter_module_get_request
r_const
r_void
op_star
id|inter_module_get_request
c_func
(paren
r_const
r_char
op_star
id|im_name
comma
r_const
r_char
op_star
id|modname
)paren
(brace
r_const
r_void
op_star
id|result
op_assign
id|inter_module_get
c_func
(paren
id|im_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
id|result
op_assign
id|inter_module_get
c_func
(paren
id|im_name
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * inter_module_put - release use of data from another module.&n; * @im_name: an arbitrary string to identify the data, must be unique&n; *&n; * Description: If the im_name has not been registered, complain,&n; * otherwise decrement the use count on the owning module.&n; */
DECL|function|inter_module_put
r_void
id|inter_module_put
c_func
(paren
r_const
r_char
op_star
id|im_name
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|inter_module_entry
op_star
id|ime
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|ime_list
)paren
(brace
id|ime
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inter_module_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ime-&gt;im_name
comma
id|im_name
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ime-&gt;owner
)paren
id|module_put
c_func
(paren
id|ime-&gt;owner
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|ime_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;inter_module_put: no entry for &squot;%s&squot;&quot;
comma
id|im_name
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|inter_module_register
id|EXPORT_SYMBOL
c_func
(paren
id|inter_module_register
)paren
suffix:semicolon
DECL|variable|inter_module_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|inter_module_unregister
)paren
suffix:semicolon
DECL|variable|inter_module_get
id|EXPORT_SYMBOL
c_func
(paren
id|inter_module_get
)paren
suffix:semicolon
DECL|variable|inter_module_get_request
id|EXPORT_SYMBOL
c_func
(paren
id|inter_module_get_request
)paren
suffix:semicolon
DECL|variable|inter_module_put
id|EXPORT_SYMBOL
c_func
(paren
id|inter_module_put
)paren
suffix:semicolon
eof
