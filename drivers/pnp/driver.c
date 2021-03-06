multiline_comment|/*&n; * driver.c - device id matching, driver model, etc.&n; *&n; * Copyright 2002 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#ifdef CONFIG_PNP_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|function|compare_func
r_static
r_int
id|compare_func
c_func
(paren
r_const
r_char
op_star
id|ida
comma
r_const
r_char
op_star
id|idb
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* we only need to compare the last 4 chars */
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ida
(braket
id|i
)braket
op_ne
l_char|&squot;X&squot;
op_logical_and
id|idb
(braket
id|i
)braket
op_ne
l_char|&squot;X&squot;
op_logical_and
id|toupper
c_func
(paren
id|ida
(braket
id|i
)braket
)paren
op_ne
id|toupper
c_func
(paren
id|idb
(braket
id|i
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|compare_pnp_id
r_int
id|compare_pnp_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|pos
comma
r_const
r_char
op_star
id|id
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pos
op_logical_or
op_logical_neg
id|id
op_logical_or
(paren
id|strlen
c_func
(paren
id|id
)paren
op_ne
l_int|7
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|id
comma
l_string|&quot;ANYDEVS&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|pos
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|pos-&gt;id
comma
id|id
comma
l_int|3
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|compare_func
c_func
(paren
id|pos-&gt;id
comma
id|id
)paren
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
id|pos
op_assign
id|pos-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|match_device
r_static
r_const
r_struct
id|pnp_device_id
op_star
id|match_device
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
comma
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_const
r_struct
id|pnp_device_id
op_star
id|drv_id
op_assign
id|drv-&gt;id_table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv_id
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|drv_id-&gt;id
)paren
(brace
r_if
c_cond
(paren
id|compare_pnp_id
c_func
(paren
id|dev-&gt;id
comma
id|drv_id-&gt;id
)paren
)paren
r_return
id|drv_id
suffix:semicolon
id|drv_id
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pnp_device_attach
r_int
id|pnp_device_attach
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pnp_dev-&gt;status
op_ne
id|PNP_READY
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pnp_dev-&gt;status
op_assign
id|PNP_ATTACHED
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_device_detach
r_void
id|pnp_device_detach
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pnp_dev-&gt;status
op_eq
id|PNP_ATTACHED
)paren
id|pnp_dev-&gt;status
op_assign
id|PNP_READY
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|pnp_disable_dev
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
)brace
DECL|function|pnp_device_probe
r_static
r_int
id|pnp_device_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|pnp_driver
op_star
id|pnp_drv
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|pnp_dev
suffix:semicolon
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|pnp_dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pnp_drv
op_assign
id|to_pnp_driver
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
id|pnp_dbg
c_func
(paren
l_string|&quot;match found with the PnP device &squot;%s&squot; and the driver &squot;%s&squot;&quot;
comma
id|dev-&gt;bus_id
comma
id|pnp_drv-&gt;name
)paren
suffix:semicolon
id|error
op_assign
id|pnp_device_attach
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|pnp_dev-&gt;active
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pnp_drv-&gt;flags
op_amp
id|PNP_DRIVER_RES_DO_NOT_CHANGE
)paren
)paren
(brace
id|error
op_assign
id|pnp_activate_dev
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|pnp_drv-&gt;flags
op_amp
id|PNP_DRIVER_RES_DISABLE
)paren
op_eq
id|PNP_DRIVER_RES_DISABLE
)paren
(brace
id|error
op_assign
id|pnp_disable_dev
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pnp_drv-&gt;probe
)paren
(brace
id|dev_id
op_assign
id|match_device
c_func
(paren
id|pnp_drv
comma
id|pnp_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_id
op_ne
l_int|NULL
)paren
id|error
op_assign
id|pnp_drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|pnp_dev
comma
id|dev_id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
(brace
id|pnp_dev-&gt;driver
op_assign
id|pnp_drv
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_goto
id|fail
suffix:semicolon
r_return
id|error
suffix:semicolon
id|fail
suffix:colon
id|pnp_device_detach
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|pnp_device_remove
r_static
r_int
id|pnp_device_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|pnp_dev
op_star
id|pnp_dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pnp_driver
op_star
id|drv
op_assign
id|pnp_dev-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;remove
)paren
id|drv
op_member_access_from_pointer
id|remove
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
id|pnp_dev-&gt;driver
op_assign
l_int|NULL
suffix:semicolon
)brace
id|pnp_device_detach
c_func
(paren
id|pnp_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_bus_match
r_static
r_int
id|pnp_bus_match
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|pnp_dev
op_star
id|pnp_dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pnp_driver
op_star
id|pnp_drv
op_assign
id|to_pnp_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_device
c_func
(paren
id|pnp_drv
comma
id|pnp_dev
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pnp_bus_type
r_struct
id|bus_type
id|pnp_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pnp&quot;
comma
dot
id|match
op_assign
id|pnp_bus_match
comma
)brace
suffix:semicolon
DECL|function|pnp_register_driver
r_int
id|pnp_register_driver
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
)paren
(brace
r_int
id|count
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|pnp_dbg
c_func
(paren
l_string|&quot;the driver &squot;%s&squot; has been registered&quot;
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|drv-&gt;driver.name
op_assign
id|drv-&gt;name
suffix:semicolon
id|drv-&gt;driver.bus
op_assign
op_amp
id|pnp_bus_type
suffix:semicolon
id|drv-&gt;driver.probe
op_assign
id|pnp_device_probe
suffix:semicolon
id|drv-&gt;driver.remove
op_assign
id|pnp_device_remove
suffix:semicolon
id|count
op_assign
id|driver_register
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
multiline_comment|/* get the number of initial matches */
r_if
c_cond
(paren
id|count
op_ge
l_int|0
)paren
(brace
id|count
op_assign
l_int|0
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|drv-&gt;driver.devices
)paren
(brace
id|count
op_increment
suffix:semicolon
)brace
)def_block
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|pnp_unregister_driver
r_void
id|pnp_unregister_driver
c_func
(paren
r_struct
id|pnp_driver
op_star
id|drv
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
id|pnp_dbg
c_func
(paren
l_string|&quot;the driver &squot;%s&squot; has been unregistered&quot;
comma
id|drv-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_add_id - adds an EISA id to the specified device&n; * @id: pointer to a pnp_id structure&n; * @dev: pointer to the desired device&n; *&n; */
DECL|function|pnp_add_id
r_int
id|pnp_add_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|id
comma
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_struct
id|pnp_id
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|id
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|id-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|ptr
op_assign
id|dev-&gt;id
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_logical_and
id|ptr-&gt;next
)paren
id|ptr
op_assign
id|ptr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|ptr-&gt;next
op_assign
id|id
suffix:semicolon
r_else
id|dev-&gt;id
op_assign
id|id
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pnp_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_driver
)paren
suffix:semicolon
DECL|variable|pnp_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_unregister_driver
)paren
suffix:semicolon
DECL|variable|pnp_add_id
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_add_id
)paren
suffix:semicolon
DECL|variable|pnp_device_attach
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_device_attach
)paren
suffix:semicolon
DECL|variable|pnp_device_detach
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_device_detach
)paren
suffix:semicolon
eof
