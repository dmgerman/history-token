multiline_comment|/*&n; * card.c - contains functions for managing groups of PnP devices&n; *&n; * Copyright 2002 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#ifdef CONFIG_PNP_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|variable|pnp_cards
id|LIST_HEAD
c_func
(paren
id|pnp_cards
)paren
suffix:semicolon
DECL|function|match_card
r_static
r_const
r_struct
id|pnp_card_id
op_star
id|match_card
c_func
(paren
r_struct
id|pnpc_driver
op_star
id|drv
comma
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
r_const
r_struct
id|pnp_card_id
op_star
id|drv_id
op_assign
id|drv-&gt;id_table
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
id|card-&gt;id
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
DECL|function|card_bus_match
r_static
r_int
id|card_bus_match
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
id|pnp_card
op_star
id|card
op_assign
id|to_pnp_card
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pnpc_driver
op_star
id|pnp_drv
op_assign
id|to_pnpc_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_card
c_func
(paren
id|pnp_drv
comma
id|card
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
DECL|variable|pnpc_bus_type
r_struct
id|bus_type
id|pnpc_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pnp_card&quot;
comma
dot
id|match
op_assign
id|card_bus_match
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * pnpc_add_id - adds an EISA id to the specified card&n; * @id: pointer to a pnp_id structure&n; * @card: pointer to the desired card&n; *&n; */
DECL|function|pnpc_add_id
r_int
id|pnpc_add_id
c_func
(paren
r_struct
id|pnp_id
op_star
id|id
comma
r_struct
id|pnp_card
op_star
id|card
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
id|card
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
id|card-&gt;id
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
id|card-&gt;id
op_assign
id|id
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpc_free_ids
r_static
r_void
id|pnpc_free_ids
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
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
id|card
)paren
r_return
suffix:semicolon
id|id
op_assign
id|card-&gt;id
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
DECL|function|pnp_release_card
r_static
r_void
id|pnp_release_card
c_func
(paren
r_struct
id|device
op_star
id|dmdev
)paren
(brace
r_struct
id|pnp_card
op_star
id|card
op_assign
id|to_pnp_card
c_func
(paren
id|dmdev
)paren
suffix:semicolon
id|pnpc_free_ids
c_func
(paren
id|card
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pnpc_add_card - adds a PnP card to the PnP Layer&n; * @card: pointer to the card to add&n; */
DECL|function|pnpc_add_card
r_int
id|pnpc_add_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
op_logical_or
op_logical_neg
id|card-&gt;protocol
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;dev.bus_id
comma
l_string|&quot;%02x:%02x&quot;
comma
id|card-&gt;protocol-&gt;number
comma
id|card-&gt;number
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|card-&gt;rdevs
)paren
suffix:semicolon
id|card-&gt;dev.parent
op_assign
op_amp
id|card-&gt;protocol-&gt;dev
suffix:semicolon
id|card-&gt;dev.bus
op_assign
op_amp
id|pnpc_bus_type
suffix:semicolon
id|card-&gt;dev.release
op_assign
op_amp
id|pnp_release_card
suffix:semicolon
id|card-&gt;status
op_assign
id|PNP_READY
suffix:semicolon
id|error
op_assign
id|device_register
c_func
(paren
op_amp
id|card-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
r_struct
id|list_head
op_star
id|pos
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
id|card-&gt;global_list
comma
op_amp
id|pnp_cards
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|card-&gt;protocol_list
comma
op_amp
id|card-&gt;protocol-&gt;cards
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|card-&gt;devices
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|card_to_pnp_dev
c_func
(paren
id|pos
)paren
suffix:semicolon
id|__pnp_add_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)def_block
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * pnpc_remove_card - removes a PnP card from the PnP Layer&n; * @card: pointer to the card to remove&n; */
DECL|function|pnpc_remove_card
r_void
id|pnpc_remove_card
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
r_return
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|card-&gt;dev
)paren
suffix:semicolon
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
id|card-&gt;global_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|card-&gt;protocol_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
(def_block
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|temp
comma
op_amp
id|card-&gt;devices
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|card_to_pnp_dev
c_func
(paren
id|pos
)paren
suffix:semicolon
id|pnpc_remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)def_block
)brace
multiline_comment|/**&n; * pnpc_add_device - adds a device to the specified card&n; * @card: pointer to the card to add to&n; * @dev: pointer to the device to add&n; */
DECL|function|pnpc_add_device
r_int
id|pnpc_add_device
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
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
op_logical_neg
id|card
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;dev.parent
op_assign
op_amp
id|card-&gt;dev
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;dev.bus_id
comma
l_string|&quot;%02x:%02x.%02x&quot;
comma
id|dev-&gt;protocol-&gt;number
comma
id|card-&gt;number
comma
id|dev-&gt;number
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|dev-&gt;card
op_assign
id|card
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;card_list
comma
op_amp
id|card-&gt;devices
)paren
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
multiline_comment|/**&n; * pnpc_remove_device- removes a device from the specified card&n; * @card: pointer to the card to remove from&n; * @dev: pointer to the device to remove&n; */
DECL|function|pnpc_remove_device
r_void
id|pnpc_remove_device
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
id|dev-&gt;card
op_assign
l_int|NULL
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;card_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|__pnp_remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_request_card_device - Searches for a PnP device under the specified card&n; * @card: pointer to the card to search under, cannot be NULL&n; * @id: pointer to a PnP ID structure that explains the rules for finding the device&n; * @from: Starting place to search from. If NULL it will start from the begining.&n; *&n; * Will activate the device&n; */
DECL|function|pnp_request_card_device
r_struct
id|pnp_dev
op_star
id|pnp_request_card_device
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_const
r_char
op_star
id|id
comma
r_struct
id|pnp_dev
op_star
id|from
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pnpc_driver
op_star
id|cdrv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
op_logical_or
op_logical_neg
id|id
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|from
)paren
(brace
id|pos
op_assign
id|card-&gt;devices.next
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|from-&gt;card
op_ne
id|card
)paren
r_goto
id|done
suffix:semicolon
id|pos
op_assign
id|from-&gt;card_list.next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pos
op_ne
op_amp
id|card-&gt;devices
)paren
(brace
id|dev
op_assign
id|card_to_pnp_dev
c_func
(paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compare_pnp_id
c_func
(paren
id|dev-&gt;id
comma
id|id
)paren
)paren
r_goto
id|found
suffix:semicolon
id|pos
op_assign
id|pos-&gt;next
suffix:semicolon
)brace
id|done
suffix:colon
r_return
l_int|NULL
suffix:semicolon
id|found
suffix:colon
r_if
c_cond
(paren
id|pnp_device_attach
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|cdrv
op_assign
id|to_pnpc_driver
c_func
(paren
id|card-&gt;dev.driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;active
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cdrv-&gt;flags
op_amp
id|PNPC_DRIVER_DO_NOT_ACTIVATE
)paren
)paren
(brace
r_if
c_cond
(paren
id|pnp_activate_dev
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|pnp_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|cdrv-&gt;flags
op_amp
id|PNPC_DRIVER_DO_NOT_ACTIVATE
)paren
)paren
id|pnp_disable_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
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
id|dev-&gt;rdev_list
comma
op_amp
id|card-&gt;rdevs
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_release_card_device - call this when the driver no longer needs the device&n; * @dev: pointer to the PnP device stucture&n; *&n; * Will disable the device&n; */
DECL|function|pnp_release_card_device
r_void
id|pnp_release_card_device
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
id|dev-&gt;rdev_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pnp_lock
)paren
suffix:semicolon
id|pnp_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|pnpc_recover_devices
r_static
r_void
id|pnpc_recover_devices
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|temp
suffix:semicolon
(def_block
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|temp
comma
op_amp
id|card-&gt;rdevs
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|pnp_dev
comma
id|rdev_list
)paren
suffix:semicolon
id|pnp_release_card_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)def_block
)brace
DECL|function|pnpc_attach
r_int
id|pnpc_attach
c_func
(paren
r_struct
id|pnp_card
op_star
id|pnp_card
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
id|pnp_card-&gt;status
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
id|pnp_card-&gt;status
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
DECL|function|pnpc_detach
r_void
id|pnpc_detach
c_func
(paren
r_struct
id|pnp_card
op_star
id|pnp_card
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
id|pnp_card-&gt;status
op_eq
id|PNP_ATTACHED
)paren
id|pnp_card-&gt;status
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
id|pnpc_recover_devices
c_func
(paren
id|pnp_card
)paren
suffix:semicolon
)brace
DECL|function|pnpc_card_probe
r_static
r_int
id|pnpc_card_probe
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
op_assign
l_int|0
suffix:semicolon
r_struct
id|pnpc_driver
op_star
id|drv
op_assign
id|to_pnpc_driver
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
r_struct
id|pnp_card
op_star
id|card
op_assign
id|to_pnp_card
c_func
(paren
id|dev
)paren
suffix:semicolon
r_const
r_struct
id|pnp_card_id
op_star
id|card_id
op_assign
l_int|NULL
suffix:semicolon
id|pnp_dbg
c_func
(paren
l_string|&quot;pnp: match found with the PnP card &squot;%s&squot; and the driver &squot;%s&squot;&quot;
comma
id|dev-&gt;bus_id
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|error
op_assign
id|pnpc_attach
c_func
(paren
id|card
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
id|drv-&gt;probe
)paren
(brace
id|card_id
op_assign
id|match_card
c_func
(paren
id|drv
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card_id
op_ne
l_int|NULL
)paren
id|error
op_assign
id|drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|card
comma
id|card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
(brace
id|card-&gt;driver
op_assign
id|drv
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|pnpc_detach
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pnpc_card_remove
r_static
r_int
id|pnpc_card_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|pnp_card
op_star
id|card
op_assign
id|to_pnp_card
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pnpc_driver
op_star
id|drv
op_assign
id|card-&gt;driver
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
id|card
)paren
suffix:semicolon
id|card-&gt;driver
op_assign
l_int|NULL
suffix:semicolon
)brace
id|pnpc_detach
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pnpc_register_driver - registers a PnP card driver with the PnP Layer&n; * @cdrv: pointer to the driver to register&n; */
DECL|function|pnpc_register_driver
r_int
id|pnpc_register_driver
c_func
(paren
r_struct
id|pnpc_driver
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
id|drv-&gt;driver.name
op_assign
id|drv-&gt;name
suffix:semicolon
id|drv-&gt;driver.bus
op_assign
op_amp
id|pnpc_bus_type
suffix:semicolon
id|drv-&gt;driver.probe
op_assign
id|pnpc_card_probe
suffix:semicolon
id|drv-&gt;driver.remove
op_assign
id|pnpc_card_remove
suffix:semicolon
id|pnp_dbg
c_func
(paren
l_string|&quot;the card driver &squot;%s&squot; has been registered&quot;
comma
id|drv-&gt;name
)paren
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
multiline_comment|/**&n; * pnpc_unregister_driver - unregisters a PnP card driver from the PnP Layer&n; * @cdrv: pointer to the driver to unregister&n; *&n; * Automatically disables requested devices&n; */
DECL|function|pnpc_unregister_driver
r_void
id|pnpc_unregister_driver
c_func
(paren
r_struct
id|pnpc_driver
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
l_string|&quot;the card driver &squot;%s&squot; has been unregistered&quot;
comma
id|drv-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|pnp_card_init
r_static
r_int
id|__init
id|pnp_card_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pnp: Enabling Plug and Play Card Services.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|bus_register
c_func
(paren
op_amp
id|pnpc_bus_type
)paren
suffix:semicolon
)brace
DECL|variable|pnp_card_init
id|subsys_initcall
c_func
(paren
id|pnp_card_init
)paren
suffix:semicolon
DECL|variable|pnpc_add_card
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_add_card
)paren
suffix:semicolon
DECL|variable|pnpc_remove_card
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_remove_card
)paren
suffix:semicolon
DECL|variable|pnpc_add_device
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_add_device
)paren
suffix:semicolon
DECL|variable|pnpc_remove_device
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_remove_device
)paren
suffix:semicolon
DECL|variable|pnp_request_card_device
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_request_card_device
)paren
suffix:semicolon
DECL|variable|pnp_release_card_device
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_release_card_device
)paren
suffix:semicolon
DECL|variable|pnpc_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_register_driver
)paren
suffix:semicolon
DECL|variable|pnpc_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_unregister_driver
)paren
suffix:semicolon
DECL|variable|pnpc_add_id
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_add_id
)paren
suffix:semicolon
DECL|variable|pnpc_attach
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_attach
)paren
suffix:semicolon
DECL|variable|pnpc_detach
id|EXPORT_SYMBOL
c_func
(paren
id|pnpc_detach
)paren
suffix:semicolon
eof
