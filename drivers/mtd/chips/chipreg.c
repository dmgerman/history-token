multiline_comment|/*&n; * $Id: chipreg.c,v 1.12 2001/10/02 15:29:53 dwmw2 Exp $&n; *&n; * Registration for chip drivers&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
DECL|variable|chip_drvs_lock
id|spinlock_t
id|chip_drvs_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|chip_drvs_list
)paren
suffix:semicolon
DECL|function|register_mtd_chip_driver
r_void
id|register_mtd_chip_driver
c_func
(paren
r_struct
id|mtd_chip_driver
op_star
id|drv
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|chip_drvs_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|drv-&gt;list
comma
op_amp
id|chip_drvs_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip_drvs_lock
)paren
suffix:semicolon
)brace
DECL|function|unregister_mtd_chip_driver
r_void
id|unregister_mtd_chip_driver
c_func
(paren
r_struct
id|mtd_chip_driver
op_star
id|drv
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|chip_drvs_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|drv-&gt;list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip_drvs_lock
)paren
suffix:semicolon
)brace
DECL|function|get_mtd_chip_driver
r_static
r_struct
id|mtd_chip_driver
op_star
id|get_mtd_chip_driver
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|mtd_chip_driver
op_star
id|ret
op_assign
l_int|NULL
comma
op_star
id|this
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|chip_drvs_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|chip_drvs_list
)paren
(brace
id|this
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|typeof
c_func
(paren
op_star
id|this
)paren
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this-&gt;name
comma
id|name
)paren
)paren
(brace
id|ret
op_assign
id|this
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ret
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|ret-&gt;module
)paren
)paren
(brace
multiline_comment|/* Eep. Failed. */
id|ret
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|chip_drvs_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Hide all the horrid details, like some silly person taking&n;&t;   get_module_symbol() away from us, from the caller. */
DECL|function|do_map_probe
r_struct
id|mtd_info
op_star
id|do_map_probe
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|map_info
op_star
id|map
)paren
(brace
r_struct
id|mtd_chip_driver
op_star
id|drv
suffix:semicolon
r_struct
id|mtd_info
op_star
id|ret
suffix:semicolon
id|drv
op_assign
id|get_mtd_chip_driver
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
op_logical_and
op_logical_neg
id|request_module
c_func
(paren
l_string|&quot;%s&quot;
comma
id|name
)paren
)paren
id|drv
op_assign
id|get_mtd_chip_driver
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
)paren
r_return
l_int|NULL
suffix:semicolon
id|ret
op_assign
id|drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|map
)paren
suffix:semicolon
multiline_comment|/* We decrease the use count here. It may have been a &n;&t;   probe-only module, which is no longer required from this&n;&t;   point, having given us a handle on (and increased the use&n;&t;   count of) the actual driver code.&n;&t;*/
id|module_put
c_func
(paren
id|drv-&gt;module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|register_mtd_chip_driver
id|EXPORT_SYMBOL
c_func
(paren
id|register_mtd_chip_driver
)paren
suffix:semicolon
DECL|variable|unregister_mtd_chip_driver
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_mtd_chip_driver
)paren
suffix:semicolon
DECL|variable|do_map_probe
id|EXPORT_SYMBOL
c_func
(paren
id|do_map_probe
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Core routines for registering and invoking MTD chip drivers&quot;
)paren
suffix:semicolon
eof
