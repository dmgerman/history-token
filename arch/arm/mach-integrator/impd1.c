multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/impd1.c&n; *&n; *  Copyright (C) 2003 Deep Blue Solutions Ltd, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file provides the core support for the IM-PD1 module.&n; *&n; * Module / boot parameters.&n; *   id=n   impd1.id=n - set the logic module position in stack to &squot;n&squot;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware/icst525.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/arch/impd1.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
DECL|variable|module_id
r_static
r_int
id|module_id
suffix:semicolon
id|module_param_named
c_func
(paren
id|lmid
comma
id|module_id
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|lmid
comma
l_string|&quot;logic module stack position&quot;
)paren
suffix:semicolon
DECL|macro|ROM_OFFSET
mdefine_line|#define ROM_OFFSET&t;0x0fffff00
DECL|macro|ROM_SIZE
mdefine_line|#define ROM_SIZE&t;256
DECL|struct|impd1_module
r_struct
id|impd1_module
(brace
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|impd1_vco_params
r_static
r_const
r_struct
id|icst525_params
id|impd1_vco_params
op_assign
(brace
dot
id|ref
op_assign
l_int|24000
comma
multiline_comment|/* 24 MHz */
dot
id|vco_max
op_assign
l_int|200000
comma
multiline_comment|/* 200 MHz */
dot
id|vd_min
op_assign
l_int|12
comma
dot
id|vd_max
op_assign
l_int|519
comma
dot
id|rd_min
op_assign
l_int|3
comma
dot
id|rd_max
op_assign
l_int|120
comma
)brace
suffix:semicolon
DECL|function|impd1_set_vco
r_void
id|impd1_set_vco
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|vconr
comma
r_int
r_int
id|period
)paren
(brace
r_struct
id|impd1_module
op_star
id|impd1
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|icst525_vco
id|vco
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|vco
op_assign
id|icst525_ps_to_vco
c_func
(paren
op_amp
id|impd1_vco_params
comma
id|period
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Guessed VCO reg params: S=%d R=%d V=%d&bslash;n&quot;
comma
id|vco.s
comma
id|vco.r
comma
id|vco.v
)paren
suffix:semicolon
id|val
op_assign
id|vco.v
op_or
(paren
id|vco.r
op_lshift
l_int|9
)paren
op_or
(paren
id|vco.s
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xa05f
comma
id|impd1-&gt;base
op_plus
id|IMPD1_LOCK
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|vconr
)paren
(brace
r_case
l_int|1
suffix:colon
id|writel
c_func
(paren
id|val
comma
id|impd1-&gt;base
op_plus
id|IMPD1_OSC1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|writel
c_func
(paren
id|val
comma
id|impd1-&gt;base
op_plus
id|IMPD1_OSC2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|writel
c_func
(paren
l_int|0
comma
id|impd1-&gt;base
op_plus
id|IMPD1_LOCK
)paren
suffix:semicolon
macro_line|#if DEBUG
id|vco.v
op_assign
id|val
op_amp
l_int|0x1ff
suffix:semicolon
id|vco.r
op_assign
(paren
id|val
op_rshift
l_int|9
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|vco.s
op_assign
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|7
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;IM-PD1: VCO%d clock is %ld kHz&bslash;n&quot;
comma
id|vconr
comma
id|icst525_khz
c_func
(paren
op_amp
id|impd1_vco_params
comma
id|vco
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|impd1_set_vco
id|EXPORT_SYMBOL
c_func
(paren
id|impd1_set_vco
)paren
suffix:semicolon
DECL|function|impd1_tweak_control
r_void
id|impd1_tweak_control
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|mask
comma
id|u32
id|val
)paren
(brace
r_struct
id|impd1_module
op_star
id|impd1
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|u32
id|cur
suffix:semicolon
id|val
op_and_assign
id|mask
suffix:semicolon
id|cur
op_assign
id|readl
c_func
(paren
id|impd1-&gt;base
op_plus
id|IMPD1_CTRL
)paren
op_amp
op_complement
id|mask
suffix:semicolon
id|writel
c_func
(paren
id|cur
op_or
id|val
comma
id|impd1-&gt;base
op_plus
id|IMPD1_CTRL
)paren
suffix:semicolon
)brace
DECL|variable|impd1_tweak_control
id|EXPORT_SYMBOL
c_func
(paren
id|impd1_tweak_control
)paren
suffix:semicolon
DECL|struct|impd1_device
r_struct
id|impd1_device
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|impd1_devs
r_static
r_struct
id|impd1_device
id|impd1_devs
(braket
)braket
op_assign
(brace
(brace
dot
id|offset
op_assign
l_int|0x03000000
comma
dot
id|id
op_assign
l_int|0x00041190
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00100000
comma
dot
id|irq
op_assign
(brace
l_int|1
)brace
comma
dot
id|id
op_assign
l_int|0x00141011
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00200000
comma
dot
id|irq
op_assign
(brace
l_int|2
)brace
comma
dot
id|id
op_assign
l_int|0x00141011
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00300000
comma
dot
id|irq
op_assign
(brace
l_int|3
)brace
comma
dot
id|id
op_assign
l_int|0x00041022
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00400000
comma
dot
id|irq
op_assign
(brace
l_int|4
)brace
comma
dot
id|id
op_assign
l_int|0x00041061
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00500000
comma
dot
id|irq
op_assign
(brace
l_int|5
)brace
comma
dot
id|id
op_assign
l_int|0x00041061
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00600000
comma
dot
id|irq
op_assign
(brace
l_int|6
)brace
comma
dot
id|id
op_assign
l_int|0x00041130
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00700000
comma
dot
id|irq
op_assign
(brace
l_int|7
comma
l_int|8
)brace
comma
dot
id|id
op_assign
l_int|0x00041181
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x00800000
comma
dot
id|irq
op_assign
(brace
l_int|9
)brace
comma
dot
id|id
op_assign
l_int|0x00041041
comma
)brace
comma
(brace
dot
id|offset
op_assign
l_int|0x01000000
comma
dot
id|irq
op_assign
(brace
l_int|11
)brace
comma
dot
id|id
op_assign
l_int|0x00041110
comma
)brace
)brace
suffix:semicolon
DECL|function|impd1_probe
r_static
r_int
id|impd1_probe
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
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|pdev-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|impd1_module
op_star
id|impd1
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;id
op_ne
id|module_id
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|res-&gt;start
comma
id|SZ_4K
comma
l_string|&quot;LM registers&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|impd1
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|impd1_module
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|impd1
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|release_lm
suffix:semicolon
)brace
id|memset
c_func
(paren
id|impd1
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|impd1_module
)paren
)paren
suffix:semicolon
id|impd1-&gt;base
op_assign
id|ioremap
c_func
(paren
id|res-&gt;start
comma
id|SZ_4K
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|impd1-&gt;base
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|free_impd1
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|impd1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IM-PD1 found at 0x%08lx&bslash;n&quot;
comma
id|res-&gt;start
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
id|ARRAY_SIZE
c_func
(paren
id|impd1_devs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|impd1_device
op_star
id|idev
op_assign
id|impd1_devs
op_plus
id|i
suffix:semicolon
r_struct
id|amba_device
op_star
id|d
suffix:semicolon
r_int
r_int
id|pc_base
suffix:semicolon
id|pc_base
op_assign
id|res-&gt;start
op_plus
id|idev-&gt;offset
suffix:semicolon
id|d
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|amba_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_continue
suffix:semicolon
id|memset
c_func
(paren
id|d
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|amba_device
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|d-&gt;dev.bus_id
comma
r_sizeof
(paren
id|d-&gt;dev.bus_id
)paren
comma
l_string|&quot;lm%x:%5.5x&quot;
comma
id|pdev-&gt;id
comma
id|idev-&gt;offset
op_rshift
l_int|12
)paren
suffix:semicolon
id|d-&gt;dev.parent
op_assign
op_amp
id|pdev-&gt;dev
suffix:semicolon
id|d-&gt;res.start
op_assign
id|res-&gt;start
op_plus
id|idev-&gt;offset
suffix:semicolon
id|d-&gt;res.end
op_assign
id|d-&gt;res.start
op_plus
id|SZ_4K
op_minus
l_int|1
suffix:semicolon
id|d-&gt;res.flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|d-&gt;irq
op_assign
id|pdev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|d-&gt;periphid
op_assign
id|idev-&gt;id
suffix:semicolon
id|ret
op_assign
id|amba_device_register
c_func
(paren
id|d
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unable to register device %s: %d&bslash;n&quot;
comma
id|d-&gt;dev.bus_id
comma
id|ret
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|free_impd1
suffix:colon
r_if
c_cond
(paren
id|impd1
op_logical_and
id|impd1-&gt;base
)paren
id|iounmap
c_func
(paren
id|impd1-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|impd1
)paren
id|kfree
c_func
(paren
id|impd1
)paren
suffix:semicolon
id|release_lm
suffix:colon
id|release_mem_region
c_func
(paren
id|res-&gt;start
comma
id|SZ_4K
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|impd1_remove
r_static
r_int
id|impd1_remove
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
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|pdev-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|impd1_module
op_star
id|impd1
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|l
comma
op_star
id|n
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|l
comma
id|n
comma
op_amp
id|dev-&gt;children
)paren
(brace
r_struct
id|device
op_star
id|d
op_assign
id|list_to_dev
c_func
(paren
id|l
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|impd1-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|impd1
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|res-&gt;start
comma
id|SZ_4K
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|impd1_driver
r_static
r_struct
id|device_driver
id|impd1_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lm&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|impd1_probe
comma
dot
id|remove
op_assign
id|impd1_remove
comma
)brace
suffix:semicolon
DECL|function|impd1_init
r_static
r_int
id|__init
id|impd1_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|impd1_driver
)paren
suffix:semicolon
)brace
DECL|function|impd1_exit
r_static
r_void
id|__exit
id|impd1_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|impd1_driver
)paren
suffix:semicolon
)brace
DECL|variable|impd1_init
id|module_init
c_func
(paren
id|impd1_init
)paren
suffix:semicolon
DECL|variable|impd1_exit
id|module_exit
c_func
(paren
id|impd1_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Integrator/IM-PD1 logic module core driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Deep Blue Solutions Ltd&quot;
)paren
suffix:semicolon
eof
