multiline_comment|/*&n; * IBM PowerPC Virtual I/O Infrastructure Support.&n; *&n; *    Copyright (c) 2003 IBM Corp.&n; *     Dave Engebretsen engebret@us.ibm.com&n; *     Santiago Leon santil@us.ibm.com&n; *     Hollis Blanchard &lt;hollisb@us.ibm.com&gt;&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/vio.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
DECL|macro|DBGENTER
mdefine_line|#define DBGENTER() pr_debug(&quot;%s entered&bslash;n&quot;, __FUNCTION__)
r_extern
r_struct
id|subsystem
id|devices_subsys
suffix:semicolon
multiline_comment|/* needed for vio_find_name() */
r_struct
id|iommu_table
op_star
id|vio_build_iommu_table
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|vio_num_address_cells
r_static
r_int
id|vio_num_address_cells
suffix:semicolon
DECL|variable|vio_bus_device
r_static
r_struct
id|vio_dev
op_star
id|vio_bus_device
suffix:semicolon
multiline_comment|/* fake &quot;parent&quot; device */
multiline_comment|/* convert from struct device to struct vio_dev and pass to driver.&n; * dev-&gt;driver has already been set by generic code because vio_bus_match&n; * succeeded. */
DECL|function|vio_bus_probe
r_static
r_int
id|vio_bus_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|vio_dev
op_star
id|viodev
op_assign
id|to_vio_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|vio_driver
op_star
id|viodrv
op_assign
id|to_vio_driver
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
r_const
r_struct
id|vio_device_id
op_star
id|id
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|viodrv-&gt;probe
)paren
r_return
id|error
suffix:semicolon
id|id
op_assign
id|vio_match_device
c_func
(paren
id|viodrv-&gt;id_table
comma
id|viodev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
)paren
(brace
id|error
op_assign
id|viodrv
op_member_access_from_pointer
id|probe
c_func
(paren
id|viodev
comma
id|id
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* convert from struct device to struct vio_dev and pass to driver. */
DECL|function|vio_bus_remove
r_static
r_int
id|vio_bus_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|vio_dev
op_star
id|viodev
op_assign
id|to_vio_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|vio_driver
op_star
id|viodrv
op_assign
id|to_vio_driver
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|viodrv-&gt;remove
)paren
(brace
r_return
id|viodrv
op_member_access_from_pointer
id|remove
c_func
(paren
id|viodev
)paren
suffix:semicolon
)brace
multiline_comment|/* driver can&squot;t remove */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * vio_register_driver: - Register a new vio driver&n; * @drv:&t;The vio_driver structure to be registered.&n; */
DECL|function|vio_register_driver
r_int
id|vio_register_driver
c_func
(paren
r_struct
id|vio_driver
op_star
id|viodrv
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: driver %s registering&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|viodrv-&gt;name
)paren
suffix:semicolon
multiline_comment|/* fill in &squot;struct driver&squot; fields */
id|viodrv-&gt;driver.name
op_assign
id|viodrv-&gt;name
suffix:semicolon
id|viodrv-&gt;driver.bus
op_assign
op_amp
id|vio_bus_type
suffix:semicolon
id|viodrv-&gt;driver.probe
op_assign
id|vio_bus_probe
suffix:semicolon
id|viodrv-&gt;driver.remove
op_assign
id|vio_bus_remove
suffix:semicolon
r_return
id|driver_register
c_func
(paren
op_amp
id|viodrv-&gt;driver
)paren
suffix:semicolon
)brace
DECL|variable|vio_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|vio_register_driver
)paren
suffix:semicolon
multiline_comment|/**&n; * vio_unregister_driver - Remove registration of vio driver.&n; * @driver:&t;The vio_driver struct to be removed form registration&n; */
DECL|function|vio_unregister_driver
r_void
id|vio_unregister_driver
c_func
(paren
r_struct
id|vio_driver
op_star
id|viodrv
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|viodrv-&gt;driver
)paren
suffix:semicolon
)brace
DECL|variable|vio_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|vio_unregister_driver
)paren
suffix:semicolon
multiline_comment|/**&n; * vio_match_device: - Tell if a VIO device has a matching VIO device id structure.&n; * @ids: &t;array of VIO device id structures to search in&n; * @dev: &t;the VIO device structure to match against&n; *&n; * Used by a driver to check whether a VIO device present in the&n; * system is in its list of supported devices. Returns the matching&n; * vio_device_id structure or NULL if there is no match.&n; */
DECL|function|vio_match_device
r_const
r_struct
id|vio_device_id
op_star
id|vio_match_device
c_func
(paren
r_const
r_struct
id|vio_device_id
op_star
id|ids
comma
r_const
r_struct
id|vio_dev
op_star
id|dev
)paren
(brace
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ids-&gt;type
)paren
(brace
r_if
c_cond
(paren
(paren
id|strncmp
c_func
(paren
id|dev-&gt;archdata-&gt;type
comma
id|ids-&gt;type
comma
id|strlen
c_func
(paren
id|ids-&gt;type
)paren
)paren
op_eq
l_int|0
)paren
op_logical_and
id|device_is_compatible
c_func
(paren
(paren
r_struct
id|device_node
op_star
)paren
id|dev-&gt;archdata
comma
id|ids-&gt;compat
)paren
)paren
r_return
id|ids
suffix:semicolon
id|ids
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * vio_bus_init: - Initialize the virtual IO bus&n; */
DECL|function|vio_bus_init
r_static
r_int
id|__init
id|vio_bus_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|node_vroot
comma
op_star
id|of_node
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|bus_register
c_func
(paren
op_amp
id|vio_bus_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;failed to register VIO bus&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* the fake parent of all vio devices, just to give us a nice directory */
id|vio_bus_device
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vio_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vio_bus_device
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|vio_bus_device
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vio_dev
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|vio_bus_device-&gt;dev.bus_id
comma
l_string|&quot;vio&quot;
)paren
suffix:semicolon
id|err
op_assign
id|device_register
c_func
(paren
op_amp
id|vio_bus_device-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: device_register returned %i&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vio_bus_device
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|node_vroot
op_assign
id|find_devices
c_func
(paren
l_string|&quot;vdevice&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node_vroot
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|node_vroot-&gt;child
op_eq
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* this machine doesn&squot;t do virtual IO, and that&squot;s ok */
r_return
l_int|0
suffix:semicolon
)brace
id|vio_num_address_cells
op_assign
id|prom_n_addr_cells
c_func
(paren
id|node_vroot-&gt;child
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create struct vio_devices for each virtual device in the device tree.&n;&t; * Drivers will associate with them later.&n;&t; */
r_for
c_loop
(paren
id|of_node
op_assign
id|node_vroot-&gt;child
suffix:semicolon
id|of_node
op_ne
l_int|NULL
suffix:semicolon
id|of_node
op_assign
id|of_node-&gt;sibling
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: processing %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|of_node
)paren
suffix:semicolon
id|vio_register_device
c_func
(paren
id|of_node
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vio_bus_init
id|__initcall
c_func
(paren
id|vio_bus_init
)paren
suffix:semicolon
multiline_comment|/* vio_dev refcount hit 0 */
DECL|function|vio_dev_release
r_static
r_void
id|__devinit
id|vio_dev_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|vio_dev
op_star
id|viodev
op_assign
id|to_vio_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX free TCE table */
id|of_node_put
c_func
(paren
id|viodev-&gt;archdata
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|viodev
)paren
suffix:semicolon
)brace
DECL|function|viodev_show_name
r_static
id|ssize_t
id|viodev_show_name
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
id|vio_dev
op_star
id|viodev
op_assign
id|to_vio_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|of_node
op_assign
id|viodev-&gt;archdata
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|of_node-&gt;name
)paren
suffix:semicolon
)brace
id|DEVICE_ATTR
c_func
(paren
id|name
comma
id|S_IRUSR
op_or
id|S_IRGRP
op_or
id|S_IROTH
comma
id|viodev_show_name
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; * vio_register_device: - Register a new vio device.&n; * @of_node:&t;The OF node for this device.&n; *&n; * Creates and initializes a vio_dev structure from the data in&n; * of_node (archdata) and adds it to the list of virtual devices.&n; * Returns a pointer to the created vio_dev or NULL if node has&n; * NULL device_type or compatible fields.&n; */
DECL|function|vio_register_device
r_struct
id|vio_dev
op_star
id|__devinit
id|vio_register_device
c_func
(paren
r_struct
id|device_node
op_star
id|of_node
)paren
(brace
r_struct
id|vio_dev
op_star
id|viodev
suffix:semicolon
r_int
r_int
op_star
id|unit_address
suffix:semicolon
r_int
r_int
op_star
id|irq_p
suffix:semicolon
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* we need the &squot;device_type&squot; property, in order to match with drivers */
r_if
c_cond
(paren
(paren
l_int|NULL
op_eq
id|of_node-&gt;type
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: node %s missing &squot;device_type&squot;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|of_node-&gt;name
ques
c_cond
id|of_node-&gt;name
suffix:colon
l_string|&quot;&lt;unknown&gt;&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|unit_address
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|of_node
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unit_address
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: node %s missing &squot;reg&squot;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|of_node-&gt;name
ques
c_cond
id|of_node-&gt;name
suffix:colon
l_string|&quot;&lt;unknown&gt;&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* allocate a vio_dev for this node */
id|viodev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vio_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|viodev
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|viodev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vio_dev
)paren
)paren
suffix:semicolon
id|viodev-&gt;archdata
op_assign
(paren
r_void
op_star
)paren
id|of_node_get
c_func
(paren
id|of_node
)paren
suffix:semicolon
id|viodev-&gt;unit_address
op_assign
op_star
id|unit_address
suffix:semicolon
id|viodev-&gt;iommu_table
op_assign
id|vio_build_iommu_table
c_func
(paren
id|viodev
)paren
suffix:semicolon
id|viodev-&gt;irq
op_assign
id|NO_IRQ
suffix:semicolon
id|irq_p
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|of_node
comma
l_string|&quot;interrupts&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_p
)paren
(brace
r_int
id|virq
op_assign
id|virt_irq_create_mapping
c_func
(paren
op_star
id|irq_p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virq
op_eq
id|NO_IRQ
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to allocate interrupt &quot;
l_string|&quot;number for %s&bslash;n&quot;
comma
id|of_node-&gt;full_name
)paren
suffix:semicolon
)brace
r_else
id|viodev-&gt;irq
op_assign
id|irq_offset_up
c_func
(paren
id|virq
)paren
suffix:semicolon
)brace
multiline_comment|/* init generic &squot;struct device&squot; fields: */
id|viodev-&gt;dev.parent
op_assign
op_amp
id|vio_bus_device-&gt;dev
suffix:semicolon
id|viodev-&gt;dev.bus
op_assign
op_amp
id|vio_bus_type
suffix:semicolon
id|snprintf
c_func
(paren
id|viodev-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%x&quot;
comma
id|viodev-&gt;unit_address
)paren
suffix:semicolon
id|viodev-&gt;dev.release
op_assign
id|vio_dev_release
suffix:semicolon
multiline_comment|/* register with generic device framework */
r_if
c_cond
(paren
id|device_register
c_func
(paren
op_amp
id|viodev-&gt;dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to register device %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|viodev-&gt;dev.bus_id
)paren
suffix:semicolon
multiline_comment|/* XXX free TCE table */
id|kfree
c_func
(paren
id|viodev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|device_create_file
c_func
(paren
op_amp
id|viodev-&gt;dev
comma
op_amp
id|dev_attr_name
)paren
suffix:semicolon
r_return
id|viodev
suffix:semicolon
)brace
DECL|variable|vio_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|vio_register_device
)paren
suffix:semicolon
DECL|function|vio_unregister_device
r_void
id|__devinit
id|vio_unregister_device
c_func
(paren
r_struct
id|vio_dev
op_star
id|viodev
)paren
(brace
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|viodev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|variable|vio_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|vio_unregister_device
)paren
suffix:semicolon
multiline_comment|/**&n; * vio_get_attribute: - get attribute for virtual device&n; * @vdev:&t;The vio device to get property.&n; * @which:&t;The property/attribute to be extracted.&n; * @length:&t;Pointer to length of returned data size (unused if NULL).&n; *&n; * Calls prom.c&squot;s get_property() to return the value of the&n; * attribute specified by the preprocessor constant @which&n;*/
DECL|function|vio_get_attribute
r_const
r_void
op_star
id|vio_get_attribute
c_func
(paren
r_struct
id|vio_dev
op_star
id|vdev
comma
r_void
op_star
id|which
comma
r_int
op_star
id|length
)paren
(brace
r_return
id|get_property
c_func
(paren
(paren
r_struct
id|device_node
op_star
)paren
id|vdev-&gt;archdata
comma
(paren
r_char
op_star
)paren
id|which
comma
id|length
)paren
suffix:semicolon
)brace
DECL|variable|vio_get_attribute
id|EXPORT_SYMBOL
c_func
(paren
id|vio_get_attribute
)paren
suffix:semicolon
multiline_comment|/* vio_find_name() - internal because only vio.c knows how we formatted the&n; * kobject name&n; * XXX once vio_bus_type.devices is actually used as a kset in&n; * drivers/base/bus.c, this function should be removed in favor of&n; * &quot;device_find(kobj_name, &amp;vio_bus_type)&quot;&n; */
DECL|function|vio_find_name
r_static
r_struct
id|vio_dev
op_star
id|vio_find_name
c_func
(paren
r_const
r_char
op_star
id|kobj_name
)paren
(brace
r_struct
id|kobject
op_star
id|found
suffix:semicolon
id|found
op_assign
id|kset_find_obj
c_func
(paren
op_amp
id|devices_subsys.kset
comma
id|kobj_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|to_vio_dev
c_func
(paren
id|container_of
c_func
(paren
id|found
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vio_find_node - find an already-registered vio_dev&n; * @vnode: device_node of the virtual device we&squot;re looking for&n; */
DECL|function|vio_find_node
r_struct
id|vio_dev
op_star
id|vio_find_node
c_func
(paren
r_struct
id|device_node
op_star
id|vnode
)paren
(brace
r_uint32
op_star
id|unit_address
suffix:semicolon
r_char
id|kobj_name
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
multiline_comment|/* construct the kobject name from the device node */
id|unit_address
op_assign
(paren
r_uint32
op_star
)paren
id|get_property
c_func
(paren
id|vnode
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unit_address
)paren
r_return
l_int|NULL
suffix:semicolon
id|snprintf
c_func
(paren
id|kobj_name
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%x&quot;
comma
op_star
id|unit_address
)paren
suffix:semicolon
r_return
id|vio_find_name
c_func
(paren
id|kobj_name
)paren
suffix:semicolon
)brace
DECL|variable|vio_find_node
id|EXPORT_SYMBOL
c_func
(paren
id|vio_find_node
)paren
suffix:semicolon
multiline_comment|/**&n; * vio_build_iommu_table: - gets the dma information from OF and builds the TCE tree.&n; * @dev: the virtual device.&n; *&n; * Returns a pointer to the built tce tree, or NULL if it can&squot;t&n; * find property.&n;*/
DECL|function|vio_build_iommu_table
r_struct
id|iommu_table
op_star
id|vio_build_iommu_table
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
(brace
r_int
r_int
op_star
id|dma_window
suffix:semicolon
r_struct
id|iommu_table
op_star
id|newTceTable
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|dma_window_property_size
suffix:semicolon
id|dma_window
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
(paren
r_struct
id|device_node
op_star
)paren
id|dev-&gt;archdata
comma
l_string|&quot;ibm,my-dma-window&quot;
comma
op_amp
id|dma_window_property_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_window
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|newTceTable
op_assign
(paren
r_struct
id|iommu_table
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iommu_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* RPA docs say that #address-cells is always 1 for virtual&n;&t;&t;devices, but some older boxes&squot; OF returns 2.  This should&n;&t;&t;be removed by GA, unless there is legacy OFs that still&n;&t;&t;have 2 for #address-cells */
id|size
op_assign
(paren
(paren
id|dma_window
(braket
l_int|1
op_plus
id|vio_num_address_cells
)braket
op_rshift
id|PAGE_SHIFT
)paren
op_lshift
l_int|3
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* This is just an ugly kludge. Remove as soon as the OF for all&n;&t;machines actually follow the spec and encodes the offset field&n;&t;as phys-encode (that is, #address-cells wide)*/
r_if
c_cond
(paren
id|dma_window_property_size
op_eq
l_int|12
)paren
(brace
id|size
op_assign
(paren
(paren
id|dma_window
(braket
l_int|1
)braket
op_rshift
id|PAGE_SHIFT
)paren
op_lshift
l_int|3
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dma_window_property_size
op_eq
l_int|20
)paren
(brace
id|size
op_assign
(paren
(paren
id|dma_window
(braket
l_int|4
)braket
op_rshift
id|PAGE_SHIFT
)paren
op_lshift
l_int|3
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vio_build_iommu_table: Invalid size of ibm,my-dma-window=%i, using 0x80 for size&bslash;n&quot;
comma
id|dma_window_property_size
)paren
suffix:semicolon
id|size
op_assign
l_int|0x80
suffix:semicolon
)brace
multiline_comment|/*  There should be some code to extract the phys-encoded offset&n;&t;&t;using prom_n_addr_cells(). However, according to a comment&n;&t;&t;on earlier versions, it&squot;s always zero, so we don&squot;t bother */
id|offset
op_assign
id|dma_window
(braket
l_int|1
)braket
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* TCE table size - measured in units of pages of tce table */
id|newTceTable-&gt;it_size
op_assign
id|size
suffix:semicolon
multiline_comment|/* offset for VIO should always be 0 */
id|newTceTable-&gt;it_offset
op_assign
id|offset
suffix:semicolon
id|newTceTable-&gt;it_busno
op_assign
l_int|0
suffix:semicolon
id|newTceTable-&gt;it_index
op_assign
(paren
r_int
r_int
)paren
id|dma_window
(braket
l_int|0
)braket
suffix:semicolon
id|newTceTable-&gt;it_type
op_assign
id|TCE_VB
suffix:semicolon
id|newTceTable-&gt;it_entrysize
op_assign
r_sizeof
(paren
r_union
id|tce_entry
)paren
suffix:semicolon
r_return
id|iommu_init_table
c_func
(paren
id|newTceTable
)paren
suffix:semicolon
)brace
DECL|function|vio_enable_interrupts
r_int
id|vio_enable_interrupts
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
(brace
r_int
id|rc
op_assign
id|h_vio_signal
c_func
(paren
id|dev-&gt;unit_address
comma
id|VIO_IRQ_ENABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|H_Success
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vio: Error 0x%x enabling interrupts&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|vio_enable_interrupts
id|EXPORT_SYMBOL
c_func
(paren
id|vio_enable_interrupts
)paren
suffix:semicolon
DECL|function|vio_disable_interrupts
r_int
id|vio_disable_interrupts
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
(brace
r_int
id|rc
op_assign
id|h_vio_signal
c_func
(paren
id|dev-&gt;unit_address
comma
id|VIO_IRQ_DISABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|H_Success
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vio: Error 0x%x disabling interrupts&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|vio_disable_interrupts
id|EXPORT_SYMBOL
c_func
(paren
id|vio_disable_interrupts
)paren
suffix:semicolon
DECL|function|vio_map_single
id|dma_addr_t
id|vio_map_single
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
id|dma_addr_t
id|dma_handle
op_assign
id|DMA_ERROR_CODE
suffix:semicolon
r_int
r_int
id|uaddr
suffix:semicolon
r_int
r_int
id|npages
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|uaddr
op_assign
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
id|npages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|uaddr
op_plus
id|size
)paren
op_minus
(paren
id|uaddr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|npages
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|tbl
op_assign
id|dev-&gt;iommu_table
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
id|dma_handle
op_assign
id|iommu_alloc
c_func
(paren
id|tbl
comma
id|vaddr
comma
id|npages
comma
id|direction
)paren
suffix:semicolon
id|dma_handle
op_or_assign
(paren
id|uaddr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
)brace
r_return
id|dma_handle
suffix:semicolon
)brace
DECL|variable|vio_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|vio_map_single
)paren
suffix:semicolon
DECL|function|vio_unmap_single
r_void
id|vio_unmap_single
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
r_int
r_int
id|npages
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|npages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|dma_handle
op_plus
id|size
)paren
op_minus
(paren
id|dma_handle
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|npages
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|tbl
op_assign
id|dev-&gt;iommu_table
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
id|iommu_free
c_func
(paren
id|tbl
comma
id|dma_handle
comma
id|npages
)paren
suffix:semicolon
)brace
)brace
DECL|variable|vio_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|vio_unmap_single
)paren
suffix:semicolon
DECL|function|vio_map_sg
r_int
id|vio_map_sg
c_func
(paren
r_struct
id|vio_dev
op_star
id|vdev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nelems
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|tbl
op_assign
id|vdev-&gt;iommu_table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tbl
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|iommu_alloc_sg
c_func
(paren
id|tbl
comma
op_amp
id|vdev-&gt;dev
comma
id|sglist
comma
id|nelems
comma
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|vio_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|vio_map_sg
)paren
suffix:semicolon
DECL|function|vio_unmap_sg
r_void
id|vio_unmap_sg
c_func
(paren
r_struct
id|vio_dev
op_star
id|vdev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|tbl
op_assign
id|vdev-&gt;iommu_table
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
id|iommu_free_sg
c_func
(paren
id|tbl
comma
id|sglist
comma
id|nelems
)paren
suffix:semicolon
)brace
DECL|variable|vio_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|vio_unmap_sg
)paren
suffix:semicolon
DECL|function|vio_alloc_consistent
r_void
op_star
id|vio_alloc_consistent
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|npages
comma
id|order
suffix:semicolon
id|dma_addr_t
id|tce
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|npages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/* Client asked for way to much space.  This is checked later anyway */
multiline_comment|/* It is easier to debug here for the drivers than in the tce tables.*/
r_if
c_cond
(paren
id|order
op_ge
id|IOMAP_MAX_ORDER
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VIO_DMA: vio_alloc_consistent size too large: 0x%lx &bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|tbl
op_assign
id|dev-&gt;iommu_table
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
multiline_comment|/* Alloc enough pages (and possibly more) */
id|ret
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* Page allocation succeeded */
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|npages
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/* Set up tces to cover the allocated range */
id|tce
op_assign
id|iommu_alloc
c_func
(paren
id|tbl
comma
id|ret
comma
id|npages
comma
id|DMA_BIDIRECTIONAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tce
op_eq
id|DMA_ERROR_CODE
)paren
(brace
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;vio_alloc_consistent: iommu_alloc failed&bslash;n&quot;
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|ret
comma
id|order
)paren
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
op_star
id|dma_handle
op_assign
id|tce
suffix:semicolon
)brace
)brace
r_else
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;vio_alloc_consistent: __get_free_pages failed for size = %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
)brace
r_else
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;vio_alloc_consistent: get_iommu_table failed for 0x%016lx&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;&bslash;tvio_alloc_consistent: dma_handle = 0x%16.16lx&bslash;n&quot;
comma
op_star
id|dma_handle
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;&bslash;tvio_alloc_consistent: return     = 0x%16.16lx&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|vio_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|vio_alloc_consistent
)paren
suffix:semicolon
DECL|function|vio_free_consistent
r_void
id|vio_free_consistent
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
r_int
r_int
id|npages
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;vio_free_consistent:&bslash;n&quot;
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;&bslash;tdev = 0x%16.16lx, size = 0x%16.16lx, dma_handle = 0x%16.16lx, vaddr = 0x%16.16lx&bslash;n&quot;
comma
id|dev
comma
id|size
comma
id|dma_handle
comma
id|vaddr
)paren
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|npages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tbl
op_assign
id|dev-&gt;iommu_table
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
id|iommu_free
c_func
(paren
id|tbl
comma
id|dma_handle
comma
id|npages
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|vio_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|vio_free_consistent
)paren
suffix:semicolon
DECL|function|vio_bus_match
r_static
r_int
id|vio_bus_match
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
r_const
r_struct
id|vio_dev
op_star
id|vio_dev
op_assign
id|to_vio_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|vio_driver
op_star
id|vio_drv
op_assign
id|to_vio_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_const
r_struct
id|vio_device_id
op_star
id|ids
op_assign
id|vio_drv-&gt;id_table
suffix:semicolon
r_const
r_struct
id|vio_device_id
op_star
id|found_id
suffix:semicolon
id|DBGENTER
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ids
)paren
r_return
l_int|0
suffix:semicolon
id|found_id
op_assign
id|vio_match_device
c_func
(paren
id|ids
comma
id|vio_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_id
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vio_bus_type
r_struct
id|bus_type
id|vio_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vio&quot;
comma
dot
id|match
op_assign
id|vio_bus_match
comma
)brace
suffix:semicolon
DECL|variable|vio_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|vio_bus_type
)paren
suffix:semicolon
eof
