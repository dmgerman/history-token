macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/of_device.h&gt;
multiline_comment|/**&n; * of_match_device - Tell if an of_device structure has a matching&n; * of_match structure&n; * @ids: array of of device match structures to search in&n; * @dev: the of device structure to match against&n; * &n; * Used by a driver to check whether an of_device present in the&n; * system is in its list of supported devices. &n; */
DECL|function|of_match_device
r_const
r_struct
id|of_match
op_star
id|of_match_device
c_func
(paren
r_const
r_struct
id|of_match
op_star
id|matches
comma
r_const
r_struct
id|of_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;node
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|matches-&gt;name
op_logical_or
id|matches-&gt;type
op_logical_or
id|matches-&gt;compatible
)paren
(brace
r_int
id|match
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|matches-&gt;name
op_logical_and
id|matches-&gt;name
op_ne
id|OF_ANY_MATCH
)paren
id|match
op_and_assign
id|dev-&gt;node-&gt;name
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|matches-&gt;name
comma
id|dev-&gt;node-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|matches-&gt;type
op_logical_and
id|matches-&gt;type
op_ne
id|OF_ANY_MATCH
)paren
id|match
op_and_assign
id|dev-&gt;node-&gt;type
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|matches-&gt;type
comma
id|dev-&gt;node-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|matches-&gt;compatible
op_logical_and
id|matches-&gt;compatible
op_ne
id|OF_ANY_MATCH
)paren
id|match
op_and_assign
id|device_is_compatible
c_func
(paren
id|dev-&gt;node
comma
id|matches-&gt;compatible
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
)paren
r_return
id|matches
suffix:semicolon
id|matches
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|of_platform_bus_match
r_static
r_int
id|of_platform_bus_match
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
id|of_device
op_star
id|of_dev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|of_platform_driver
op_star
id|of_drv
op_assign
id|to_of_platform_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_const
r_struct
id|of_match
op_star
id|matches
op_assign
id|of_drv-&gt;match_table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|matches
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|of_match_device
c_func
(paren
id|matches
comma
id|of_dev
)paren
op_ne
l_int|NULL
suffix:semicolon
)brace
DECL|function|of_dev_get
r_struct
id|of_device
op_star
id|of_dev_get
c_func
(paren
r_struct
id|of_device
op_star
id|dev
)paren
(brace
r_struct
id|device
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|get_device
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
r_return
id|to_of_device
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|of_dev_put
r_void
id|of_dev_put
c_func
(paren
r_struct
id|of_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
id|put_device
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|of_device_probe
r_static
r_int
id|of_device_probe
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
op_minus
id|ENODEV
suffix:semicolon
r_struct
id|of_platform_driver
op_star
id|drv
suffix:semicolon
r_struct
id|of_device
op_star
id|of_dev
suffix:semicolon
r_const
r_struct
id|of_match
op_star
id|match
suffix:semicolon
id|drv
op_assign
id|to_of_platform_driver
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
id|of_dev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv-&gt;probe
)paren
r_return
id|error
suffix:semicolon
id|of_dev_get
c_func
(paren
id|of_dev
)paren
suffix:semicolon
id|match
op_assign
id|of_match_device
c_func
(paren
id|drv-&gt;match_table
comma
id|of_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
)paren
id|error
op_assign
id|drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|of_dev
comma
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|of_dev_put
c_func
(paren
id|of_dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|of_device_remove
r_static
r_int
id|of_device_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|of_device
op_star
id|of_dev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|of_platform_driver
op_star
id|drv
op_assign
id|to_of_platform_driver
c_func
(paren
id|of_dev-&gt;dev.driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
op_logical_and
id|drv-&gt;remove
)paren
id|drv
op_member_access_from_pointer
id|remove
c_func
(paren
id|of_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|of_device_suspend
r_static
r_int
id|of_device_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
r_struct
id|of_device
op_star
id|of_dev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|of_platform_driver
op_star
id|drv
op_assign
id|to_of_platform_driver
c_func
(paren
id|of_dev-&gt;dev.driver
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drv
op_logical_and
id|drv-&gt;suspend
)paren
id|error
op_assign
id|drv
op_member_access_from_pointer
id|suspend
c_func
(paren
id|of_dev
comma
id|state
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|of_device_resume
r_static
r_int
id|of_device_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|of_device
op_star
id|of_dev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|of_platform_driver
op_star
id|drv
op_assign
id|to_of_platform_driver
c_func
(paren
id|of_dev-&gt;dev.driver
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drv
op_logical_and
id|drv-&gt;resume
)paren
id|error
op_assign
id|drv
op_member_access_from_pointer
id|resume
c_func
(paren
id|of_dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|of_platform_bus_type
r_struct
id|bus_type
id|of_platform_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;of_platform&quot;
comma
dot
id|match
op_assign
id|of_platform_bus_match
comma
dot
id|suspend
op_assign
id|of_device_suspend
comma
dot
id|resume
op_assign
id|of_device_resume
comma
)brace
suffix:semicolon
DECL|function|of_bus_driver_init
r_static
r_int
id|__init
id|of_bus_driver_init
c_func
(paren
r_void
)paren
(brace
r_return
id|bus_register
c_func
(paren
op_amp
id|of_platform_bus_type
)paren
suffix:semicolon
)brace
DECL|variable|of_bus_driver_init
id|postcore_initcall
c_func
(paren
id|of_bus_driver_init
)paren
suffix:semicolon
DECL|function|of_register_driver
r_int
id|of_register_driver
c_func
(paren
r_struct
id|of_platform_driver
op_star
id|drv
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* initialize common driver fields */
id|drv-&gt;driver.name
op_assign
id|drv-&gt;name
suffix:semicolon
id|drv-&gt;driver.bus
op_assign
op_amp
id|of_platform_bus_type
suffix:semicolon
id|drv-&gt;driver.probe
op_assign
id|of_device_probe
suffix:semicolon
id|drv-&gt;driver.remove
op_assign
id|of_device_remove
suffix:semicolon
multiline_comment|/* register with core */
id|count
op_assign
id|driver_register
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
r_return
id|count
ques
c_cond
id|count
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|of_unregister_driver
r_void
id|of_unregister_driver
c_func
(paren
r_struct
id|of_platform_driver
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
)brace
DECL|function|dev_show_devspec
r_static
id|ssize_t
id|dev_show_devspec
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|of_device
op_star
id|ofdev
suffix:semicolon
id|ofdev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&quot;
comma
id|ofdev-&gt;node-&gt;full_name
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|devspec
comma
id|S_IRUGO
comma
id|dev_show_devspec
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; * of_release_dev - free an of device structure when all users of it are finished.&n; * @dev: device that&squot;s been disconnected&n; *&n; * Will be called only by the device core when all users of this of device are&n; * done.&n; */
DECL|function|of_release_dev
r_void
id|of_release_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|of_device
op_star
id|ofdev
suffix:semicolon
id|ofdev
op_assign
id|to_of_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ofdev
)paren
suffix:semicolon
)brace
DECL|function|of_device_register
r_int
id|of_device_register
c_func
(paren
r_struct
id|of_device
op_star
id|ofdev
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|of_device
op_star
op_star
id|odprop
suffix:semicolon
id|BUG_ON
c_func
(paren
id|ofdev-&gt;node
op_eq
l_int|NULL
)paren
suffix:semicolon
id|odprop
op_assign
(paren
r_struct
id|of_device
op_star
op_star
)paren
id|get_property
c_func
(paren
id|ofdev-&gt;node
comma
l_string|&quot;linux,device&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|odprop
)paren
(brace
r_struct
id|property
op_star
id|new_prop
suffix:semicolon
id|new_prop
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|property
)paren
op_plus
r_sizeof
(paren
r_struct
id|of_device
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_prop
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|new_prop-&gt;name
op_assign
l_string|&quot;linux,device&quot;
suffix:semicolon
id|new_prop-&gt;length
op_assign
r_sizeof
(paren
r_sizeof
(paren
r_struct
id|of_device
op_star
)paren
)paren
suffix:semicolon
id|new_prop-&gt;value
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|new_prop
(braket
l_int|1
)braket
suffix:semicolon
id|odprop
op_assign
(paren
r_struct
id|of_device
op_star
op_star
)paren
id|new_prop-&gt;value
suffix:semicolon
op_star
id|odprop
op_assign
l_int|NULL
suffix:semicolon
id|prom_add_property
c_func
(paren
id|ofdev-&gt;node
comma
id|new_prop
)paren
suffix:semicolon
)brace
op_star
id|odprop
op_assign
id|ofdev
suffix:semicolon
id|rc
op_assign
id|device_register
c_func
(paren
op_amp
id|ofdev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|ofdev-&gt;dev
comma
op_amp
id|dev_attr_devspec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|of_device_unregister
r_void
id|of_device_unregister
c_func
(paren
r_struct
id|of_device
op_star
id|ofdev
)paren
(brace
r_struct
id|of_device
op_star
op_star
id|odprop
suffix:semicolon
id|device_remove_file
c_func
(paren
op_amp
id|ofdev-&gt;dev
comma
op_amp
id|dev_attr_devspec
)paren
suffix:semicolon
id|odprop
op_assign
(paren
r_struct
id|of_device
op_star
op_star
)paren
id|get_property
c_func
(paren
id|ofdev-&gt;node
comma
l_string|&quot;linux,device&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|odprop
)paren
op_star
id|odprop
op_assign
l_int|NULL
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|ofdev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|of_platform_device_create
r_struct
id|of_device
op_star
id|of_platform_device_create
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
r_const
r_char
op_star
id|bus_id
)paren
(brace
r_struct
id|of_device
op_star
id|dev
suffix:semicolon
id|u32
op_star
id|reg
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;node
op_assign
id|np
suffix:semicolon
id|dev-&gt;dma_mask
op_assign
l_int|0xffffffffUL
suffix:semicolon
id|dev-&gt;dev.dma_mask
op_assign
op_amp
id|dev-&gt;dma_mask
suffix:semicolon
id|dev-&gt;dev.parent
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;dev.bus
op_assign
op_amp
id|of_platform_bus_type
suffix:semicolon
id|dev-&gt;dev.release
op_assign
id|of_release_dev
suffix:semicolon
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|dev-&gt;dev.bus_id
comma
id|bus_id
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|of_device_register
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
)brace
DECL|variable|of_match_device
id|EXPORT_SYMBOL
c_func
(paren
id|of_match_device
)paren
suffix:semicolon
DECL|variable|of_platform_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|of_platform_bus_type
)paren
suffix:semicolon
DECL|variable|of_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|of_register_driver
)paren
suffix:semicolon
DECL|variable|of_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|of_unregister_driver
)paren
suffix:semicolon
DECL|variable|of_device_register
id|EXPORT_SYMBOL
c_func
(paren
id|of_device_register
)paren
suffix:semicolon
DECL|variable|of_device_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|of_device_unregister
)paren
suffix:semicolon
DECL|variable|of_dev_get
id|EXPORT_SYMBOL
c_func
(paren
id|of_dev_get
)paren
suffix:semicolon
DECL|variable|of_dev_put
id|EXPORT_SYMBOL
c_func
(paren
id|of_dev_put
)paren
suffix:semicolon
DECL|variable|of_platform_device_create
id|EXPORT_SYMBOL
c_func
(paren
id|of_platform_device_create
)paren
suffix:semicolon
DECL|variable|of_release_dev
id|EXPORT_SYMBOL
c_func
(paren
id|of_release_dev
)paren
suffix:semicolon
eof
