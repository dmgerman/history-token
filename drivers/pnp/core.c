multiline_comment|/*&n; * core.c - contains all core device and protocol registration functions&n; *&n; * Copyright 2002 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|variable|pnp_protocols
id|LIST_HEAD
c_func
(paren
id|pnp_protocols
)paren
suffix:semicolon
DECL|variable|pnp_global
id|LIST_HEAD
c_func
(paren
id|pnp_global
)paren
suffix:semicolon
DECL|variable|pnp_lock
id|spinlock_t
id|pnp_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|pnp_alloc
r_void
op_star
id|pnp_alloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|result
suffix:semicolon
id|result
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pnp: Out of Memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|result
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_protocol_register - adds a pnp protocol to the pnp layer&n; * @protocol: pointer to the corresponding pnp_protocol structure&n; *&n; *  Ex protocols: ISAPNP, PNPBIOS, etc&n; */
DECL|function|pnp_register_protocol
r_int
id|pnp_register_protocol
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
(brace
r_int
id|nodenum
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|protocol
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|protocol-&gt;devices
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|protocol-&gt;cards
)paren
suffix:semicolon
id|nodenum
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
multiline_comment|/* assign the lowest unused number */
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|pnp_protocols
)paren
(brace
r_struct
id|pnp_protocol
op_star
id|cur
op_assign
id|to_pnp_protocol
c_func
(paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur-&gt;number
op_eq
id|nodenum
)paren
(brace
id|pos
op_assign
op_amp
id|pnp_protocols
suffix:semicolon
id|nodenum
op_increment
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|protocol-&gt;protocol_list
comma
op_amp
id|pnp_protocols
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|protocol-&gt;number
op_assign
id|nodenum
suffix:semicolon
id|sprintf
c_func
(paren
id|protocol-&gt;dev.bus_id
comma
l_string|&quot;pnp%d&quot;
comma
id|nodenum
)paren
suffix:semicolon
r_return
id|device_register
c_func
(paren
op_amp
id|protocol-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_protocol_unregister - removes a pnp protocol from the pnp layer&n; * @protocol: pointer to the corresponding pnp_protocol structure&n; *&n; */
DECL|function|pnp_unregister_protocol
r_void
id|pnp_unregister_protocol
c_func
(paren
r_struct
id|pnp_protocol
op_star
id|protocol
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|protocol-&gt;protocol_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|protocol-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|pnp_free_ids
r_static
r_void
id|pnp_free_ids
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_struct
id|pnp_id
op_star
id|id
suffix:semicolon
r_struct
id|pnp_id
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
suffix:semicolon
id|id
op_assign
id|dev-&gt;id
suffix:semicolon
r_while
c_loop
(paren
id|id
)paren
(brace
id|next
op_assign
id|id-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|id
)paren
suffix:semicolon
id|id
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|pnp_release_device
r_static
r_void
id|pnp_release_device
c_func
(paren
r_struct
id|device
op_star
id|dmdev
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dmdev
)paren
suffix:semicolon
id|pnp_free_option
c_func
(paren
id|dev-&gt;independent
)paren
suffix:semicolon
id|pnp_free_option
c_func
(paren
id|dev-&gt;dependent
)paren
suffix:semicolon
id|pnp_free_ids
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|__pnp_add_device
r_int
id|__pnp_add_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_int
id|ret
suffix:semicolon
id|pnp_fixup_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;dev.bus
op_assign
op_amp
id|pnp_bus_type
suffix:semicolon
id|dev-&gt;dev.release
op_assign
op_amp
id|pnp_release_device
suffix:semicolon
id|dev-&gt;status
op_assign
id|PNP_READY
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;global_list
comma
op_amp
id|pnp_global
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;protocol_list
comma
op_amp
id|dev-&gt;protocol-&gt;devices
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|ret
op_assign
id|device_register
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|pnp_interface_attach_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * pnp_add_device - adds a pnp device to the pnp layer&n; * @dev: pointer to dev to add&n; *&n; *  adds to driver model, name database, fixups, interface, etc.&n; */
DECL|function|pnp_add_device
r_int
id|pnp_add_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;protocol
op_logical_or
id|dev-&gt;card
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;dev.parent
op_assign
op_amp
id|dev-&gt;protocol-&gt;dev
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;dev.bus_id
comma
l_string|&quot;%02x:%02x&quot;
comma
id|dev-&gt;protocol-&gt;number
comma
id|dev-&gt;number
)paren
suffix:semicolon
r_return
id|__pnp_add_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|__pnp_remove_device
r_void
id|__pnp_remove_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;global_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;protocol_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_remove_device - removes a pnp device from the pnp layer&n; * @dev: pointer to dev to add&n; *&n; * this function will free all mem used by dev&n; */
DECL|function|pnp_remove_device
r_void
id|pnp_remove_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
id|dev-&gt;card
)paren
r_return
suffix:semicolon
id|__pnp_remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|pnp_init
r_static
r_int
id|__init
id|pnp_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux Plug and Play Support v0.97 (c) Adam Belay&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|bus_register
c_func
(paren
op_amp
id|pnp_bus_type
)paren
suffix:semicolon
)brace
DECL|variable|pnp_init
id|subsys_initcall
c_func
(paren
id|pnp_init
)paren
suffix:semicolon
DECL|variable|pnp_register_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_protocol
)paren
suffix:semicolon
DECL|variable|pnp_unregister_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_unregister_protocol
)paren
suffix:semicolon
DECL|variable|pnp_add_device
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_add_device
)paren
suffix:semicolon
DECL|variable|pnp_remove_device
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_remove_device
)paren
suffix:semicolon
eof
