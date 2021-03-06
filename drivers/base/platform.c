multiline_comment|/*&n; * platform.c - platform &squot;pseudo&squot; bus for legacy devices&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; *&n; * This file is released under the GPLv2&n; *&n; * Please see Documentation/driver-model/platform.txt for more&n; * information.&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/err.h&gt;
DECL|variable|platform_bus
r_struct
id|device
id|platform_bus
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;platform&quot;
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;platform_get_resource - get a resource for a device&n; *&t;@dev: platform device&n; *&t;@type: resource type&n; *&t;@num: resource index&n; */
r_struct
id|resource
op_star
DECL|function|platform_get_resource
id|platform_get_resource
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|num
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;num_resources
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;flags
op_amp
(paren
id|IORESOURCE_IO
op_or
id|IORESOURCE_MEM
op_or
id|IORESOURCE_IRQ
op_or
id|IORESOURCE_DMA
)paren
)paren
op_eq
id|type
)paren
r_if
c_cond
(paren
id|num
op_decrement
op_eq
l_int|0
)paren
r_return
id|r
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_get_irq - get an IRQ for a device&n; *&t;@dev: platform device&n; *&t;@num: IRQ number index&n; */
DECL|function|platform_get_irq
r_int
id|platform_get_irq
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
comma
r_int
r_int
id|num
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
id|platform_get_resource
c_func
(paren
id|dev
comma
id|IORESOURCE_IRQ
comma
id|num
)paren
suffix:semicolon
r_return
id|r
ques
c_cond
id|r-&gt;start
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_get_resource_byname - get a resource for a device by name&n; *&t;@dev: platform device&n; *&t;@type: resource type&n; *&t;@name: resource name&n; */
r_struct
id|resource
op_star
DECL|function|platform_get_resource_byname
id|platform_get_resource_byname
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;num_resources
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;flags
op_amp
(paren
id|IORESOURCE_IO
op_or
id|IORESOURCE_MEM
op_or
id|IORESOURCE_IRQ
op_or
id|IORESOURCE_DMA
)paren
)paren
op_eq
id|type
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|r-&gt;name
comma
id|name
)paren
)paren
r_return
id|r
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_get_irq - get an IRQ for a device&n; *&t;@dev: platform device&n; *&t;@name: IRQ name&n; */
DECL|function|platform_get_irq_byname
r_int
id|platform_get_irq_byname
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
id|platform_get_resource_byname
c_func
(paren
id|dev
comma
id|IORESOURCE_IRQ
comma
id|name
)paren
suffix:semicolon
r_return
id|r
ques
c_cond
id|r-&gt;start
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_add_devices - add a numbers of platform devices&n; *&t;@devs: array of platform devices to add&n; *&t;@num: number of platform devices in array&n; */
DECL|function|platform_add_devices
r_int
id|platform_add_devices
c_func
(paren
r_struct
id|platform_device
op_star
op_star
id|devs
comma
r_int
id|num
)paren
(brace
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|platform_device_register
c_func
(paren
id|devs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
id|platform_device_unregister
c_func
(paren
id|devs
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_device_register - add a platform-level device&n; *&t;@dev:&t;platform device we&squot;re adding&n; *&n; */
DECL|function|platform_device_register
r_int
id|platform_device_register
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev-&gt;dev.parent
)paren
id|pdev-&gt;dev.parent
op_assign
op_amp
id|platform_bus
suffix:semicolon
id|pdev-&gt;dev.bus
op_assign
op_amp
id|platform_bus_type
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;id
op_ne
op_minus
l_int|1
)paren
id|snprintf
c_func
(paren
id|pdev-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%s.%u&quot;
comma
id|pdev-&gt;name
comma
id|pdev-&gt;id
)paren
suffix:semicolon
r_else
id|strlcpy
c_func
(paren
id|pdev-&gt;dev.bus_id
comma
id|pdev-&gt;name
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pdev-&gt;num_resources
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|p
comma
op_star
id|r
op_assign
op_amp
id|pdev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;name
op_eq
l_int|NULL
)paren
id|r-&gt;name
op_assign
id|pdev-&gt;dev.bus_id
suffix:semicolon
id|p
op_assign
id|r-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|p
op_assign
op_amp
id|iomem_resource
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|p
op_assign
op_amp
id|ioport_resource
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_logical_and
id|request_resource
c_func
(paren
id|p
comma
id|r
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to claim resource %d&bslash;n&quot;
comma
id|pdev-&gt;dev.bus_id
comma
id|i
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
)brace
id|pr_debug
c_func
(paren
l_string|&quot;Registering platform device &squot;%s&squot;. Parent at %s&bslash;n&quot;
comma
id|pdev-&gt;dev.bus_id
comma
id|pdev-&gt;dev.parent-&gt;bus_id
)paren
suffix:semicolon
id|ret
op_assign
id|device_register
c_func
(paren
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|failed
suffix:colon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
r_if
c_cond
(paren
id|pdev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
(paren
id|IORESOURCE_MEM
op_or
id|IORESOURCE_IO
)paren
)paren
id|release_resource
c_func
(paren
op_amp
id|pdev-&gt;resource
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_device_unregister - remove a platform-level device&n; *&t;@dev:&t;platform device we&squot;re removing&n; *&n; *&t;Note that this function will also release all memory- and port-based&n; *&t;resources owned by the device (@dev-&gt;resource).&n; */
DECL|function|platform_device_unregister
r_void
id|platform_device_unregister
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pdev-&gt;num_resources
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|pdev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
(paren
id|IORESOURCE_MEM
op_or
id|IORESOURCE_IO
)paren
)paren
id|release_resource
c_func
(paren
id|r
)paren
suffix:semicolon
)brace
id|device_unregister
c_func
(paren
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
)brace
)brace
DECL|struct|platform_object
r_struct
id|platform_object
(brace
DECL|member|pdev
r_struct
id|platform_device
id|pdev
suffix:semicolon
DECL|member|resources
r_struct
id|resource
id|resources
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|platform_device_release_simple
r_static
r_void
id|platform_device_release_simple
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|container_of
c_func
(paren
id|pdev
comma
r_struct
id|platform_object
comma
id|pdev
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_device_register_simple&n; *&t;@name:  base name of the device we&squot;re adding&n; *&t;@id:    instance id&n; *&t;@res:   set of resources that needs to be allocated for the device&n; *&t;@num:&t;number of resources&n; *&n; *&t;This function creates a simple platform device that requires minimal&n; *&t;resource and memory management. Canned release function freeing&n; *&t;memory allocated for the device allows drivers using such devices&n; *&t;to be unloaded iwithout waiting for the last reference to the device&n; *&t;to be dropped.&n; */
DECL|function|platform_device_register_simple
r_struct
id|platform_device
op_star
id|platform_device_register_simple
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|id
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|num
)paren
(brace
r_struct
id|platform_object
op_star
id|pobj
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|pobj
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|platform_object
)paren
op_plus
r_sizeof
(paren
r_struct
id|resource
)paren
op_star
id|num
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pobj
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|memset
c_func
(paren
id|pobj
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pobj
)paren
)paren
suffix:semicolon
id|pobj-&gt;pdev.name
op_assign
id|name
suffix:semicolon
id|pobj-&gt;pdev.id
op_assign
id|id
suffix:semicolon
id|pobj-&gt;pdev.dev.release
op_assign
id|platform_device_release_simple
suffix:semicolon
r_if
c_cond
(paren
id|num
)paren
(brace
id|memcpy
c_func
(paren
id|pobj-&gt;resources
comma
id|res
comma
r_sizeof
(paren
r_struct
id|resource
)paren
op_star
id|num
)paren
suffix:semicolon
id|pobj-&gt;pdev.resource
op_assign
id|pobj-&gt;resources
suffix:semicolon
id|pobj-&gt;pdev.num_resources
op_assign
id|num
suffix:semicolon
)brace
id|retval
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|pobj-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|error
suffix:semicolon
r_return
op_amp
id|pobj-&gt;pdev
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|pobj
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|retval
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_match - bind platform device to platform driver.&n; *&t;@dev:&t;device.&n; *&t;@drv:&t;driver.&n; *&n; *&t;Platform device IDs are assumed to be encoded like this:&n; *&t;&quot;&lt;name&gt;&lt;instance&gt;&quot;, where &lt;name&gt; is a short description of the&n; *&t;type of device, like &quot;pci&quot; or &quot;floppy&quot;, and &lt;instance&gt; is the&n; *&t;enumerated instance of the device, like &squot;0&squot; or &squot;42&squot;.&n; *&t;Driver IDs are simply &quot;&lt;name&gt;&quot;.&n; *&t;So, extract the &lt;name&gt; from the platform_device structure,&n; *&t;and compare it against the name of the driver. Return whether&n; *&t;they match or not.&n; */
DECL|function|platform_match
r_static
r_int
id|platform_match
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
id|platform_device
op_star
id|pdev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|platform_device
comma
id|dev
)paren
suffix:semicolon
r_return
(paren
id|strncmp
c_func
(paren
id|pdev-&gt;name
comma
id|drv-&gt;name
comma
id|BUS_ID_SIZE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|platform_suspend
r_static
r_int
id|platform_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|pm_message_t
id|state
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;suspend
)paren
(brace
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
comma
id|SUSPEND_DISABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
comma
id|SUSPEND_SAVE_STATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
comma
id|SUSPEND_POWER_DOWN
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|platform_resume
r_static
r_int
id|platform_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;resume
)paren
(brace
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|RESUME_POWER_ON
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|RESUME_RESTORE_STATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|RESUME_ENABLE
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|platform_bus_type
r_struct
id|bus_type
id|platform_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;platform&quot;
comma
dot
id|match
op_assign
id|platform_match
comma
dot
id|suspend
op_assign
id|platform_suspend
comma
dot
id|resume
op_assign
id|platform_resume
comma
)brace
suffix:semicolon
DECL|function|platform_bus_init
r_int
id|__init
id|platform_bus_init
c_func
(paren
r_void
)paren
(brace
id|device_register
c_func
(paren
op_amp
id|platform_bus
)paren
suffix:semicolon
r_return
id|bus_register
c_func
(paren
op_amp
id|platform_bus_type
)paren
suffix:semicolon
)brace
macro_line|#ifndef ARCH_HAS_DMA_GET_REQUIRED_MASK
DECL|function|dma_get_required_mask
id|u64
id|dma_get_required_mask
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|u32
id|low_totalram
op_assign
(paren
(paren
id|max_pfn
op_minus
l_int|1
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|u32
id|high_totalram
op_assign
(paren
(paren
id|max_pfn
op_minus
l_int|1
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|u64
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|high_totalram
)paren
(brace
multiline_comment|/* convert to mask just covering totalram */
id|low_totalram
op_assign
(paren
l_int|1
op_lshift
(paren
id|fls
c_func
(paren
id|low_totalram
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|low_totalram
op_add_assign
id|low_totalram
op_minus
l_int|1
suffix:semicolon
id|mask
op_assign
id|low_totalram
suffix:semicolon
)brace
r_else
(brace
id|high_totalram
op_assign
(paren
l_int|1
op_lshift
(paren
id|fls
c_func
(paren
id|high_totalram
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|high_totalram
op_add_assign
id|high_totalram
op_minus
l_int|1
suffix:semicolon
id|mask
op_assign
(paren
(paren
(paren
id|u64
)paren
id|high_totalram
)paren
op_lshift
l_int|32
)paren
op_plus
l_int|0xffffffff
suffix:semicolon
)brace
r_return
id|mask
op_amp
op_star
id|dev-&gt;dma_mask
suffix:semicolon
)brace
DECL|variable|dma_get_required_mask
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dma_get_required_mask
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|platform_bus
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_bus
)paren
suffix:semicolon
DECL|variable|platform_bus_type
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_bus_type
)paren
suffix:semicolon
DECL|variable|platform_device_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_device_register
)paren
suffix:semicolon
DECL|variable|platform_device_register_simple
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_device_register_simple
)paren
suffix:semicolon
DECL|variable|platform_device_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_device_unregister
)paren
suffix:semicolon
DECL|variable|platform_get_irq
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_get_irq
)paren
suffix:semicolon
DECL|variable|platform_get_resource
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_get_resource
)paren
suffix:semicolon
DECL|variable|platform_get_irq_byname
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_get_irq_byname
)paren
suffix:semicolon
DECL|variable|platform_get_resource_byname
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|platform_get_resource_byname
)paren
suffix:semicolon
eof
