multiline_comment|/*&n; * Support code for the SCOOP interface found on various Sharp PDAs&n; *&n; * Copyright (c) 2004 Richard Purdie&n; *&n; *&t;Based on code written by Sharp/Lineo for 2.4 kernels&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware/scoop.h&gt;
DECL|macro|SCOOP_REG
mdefine_line|#define SCOOP_REG(d,adr) (*(volatile unsigned short*)(d +(adr)))
DECL|struct|scoop_dev
r_struct
id|scoop_dev
(brace
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|scoop_lock
id|spinlock_t
id|scoop_lock
suffix:semicolon
DECL|member|scoop_gpwr
id|u32
id|scoop_gpwr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|reset_scoop
r_void
id|reset_scoop
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_MCR
)paren
op_assign
l_int|0x0100
suffix:semicolon
singleline_comment|// 00
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_CDR
)paren
op_assign
l_int|0x0000
suffix:semicolon
singleline_comment|// 04
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_CPR
)paren
op_assign
l_int|0x0000
suffix:semicolon
singleline_comment|// 0C
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_CCR
)paren
op_assign
l_int|0x0000
suffix:semicolon
singleline_comment|// 10
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_IMR
)paren
op_assign
l_int|0x0000
suffix:semicolon
singleline_comment|// 18
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_IRM
)paren
op_assign
l_int|0x00FF
suffix:semicolon
singleline_comment|// 14
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_ISR
)paren
op_assign
l_int|0x0000
suffix:semicolon
singleline_comment|// 1C
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_IRM
)paren
op_assign
l_int|0x0000
suffix:semicolon
)brace
DECL|function|set_scoop_gpio
r_int
r_int
id|set_scoop_gpio
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|bit
)paren
(brace
r_int
r_int
id|gpio_bit
suffix:semicolon
r_int
r_int
id|flag
suffix:semicolon
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sdev-&gt;scoop_lock
comma
id|flag
)paren
suffix:semicolon
id|gpio_bit
op_assign
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
op_or
id|bit
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
op_assign
id|gpio_bit
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sdev-&gt;scoop_lock
comma
id|flag
)paren
suffix:semicolon
r_return
id|gpio_bit
suffix:semicolon
)brace
DECL|function|reset_scoop_gpio
r_int
r_int
id|reset_scoop_gpio
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|bit
)paren
(brace
r_int
r_int
id|gpio_bit
suffix:semicolon
r_int
r_int
id|flag
suffix:semicolon
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sdev-&gt;scoop_lock
comma
id|flag
)paren
suffix:semicolon
id|gpio_bit
op_assign
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
op_amp
op_complement
id|bit
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
op_assign
id|gpio_bit
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sdev-&gt;scoop_lock
comma
id|flag
)paren
suffix:semicolon
r_return
id|gpio_bit
suffix:semicolon
)brace
DECL|variable|set_scoop_gpio
id|EXPORT_SYMBOL
c_func
(paren
id|set_scoop_gpio
)paren
suffix:semicolon
DECL|variable|reset_scoop_gpio
id|EXPORT_SYMBOL
c_func
(paren
id|reset_scoop_gpio
)paren
suffix:semicolon
DECL|function|read_scoop_reg
r_int
r_int
id|read_scoop_reg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|reg
)paren
(brace
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|function|write_scoop_reg
r_void
id|write_scoop_reg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|reg
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|variable|reset_scoop
id|EXPORT_SYMBOL
c_func
(paren
id|reset_scoop
)paren
suffix:semicolon
DECL|variable|read_scoop_reg
id|EXPORT_SYMBOL
c_func
(paren
id|read_scoop_reg
)paren
suffix:semicolon
DECL|variable|write_scoop_reg
id|EXPORT_SYMBOL
c_func
(paren
id|write_scoop_reg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|function|scoop_suspend
r_static
r_int
id|scoop_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_uint32
id|state
comma
r_uint32
id|level
)paren
(brace
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_POWER_DOWN
)paren
(brace
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sdev-&gt;scoop_gpwr
op_assign
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scoop_resume
r_static
r_int
id|scoop_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_uint32
id|level
)paren
(brace
r_if
c_cond
(paren
id|level
op_eq
id|RESUME_POWER_ON
)paren
(brace
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|sdev-&gt;base
comma
id|SCOOP_GPWR
)paren
op_assign
id|sdev-&gt;scoop_gpwr
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|scoop_suspend
mdefine_line|#define scoop_suspend&t;NULL
DECL|macro|scoop_resume
mdefine_line|#define scoop_resume&t;NULL
macro_line|#endif
DECL|function|scoop_probe
r_int
id|__init
id|scoop_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|scoop_dev
op_star
id|devptr
suffix:semicolon
r_struct
id|scoop_config
op_star
id|inf
suffix:semicolon
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
id|mem
op_assign
id|platform_get_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_MEM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|devptr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scoop_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|devptr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|devptr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|scoop_dev
)paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|devptr-&gt;scoop_lock
)paren
suffix:semicolon
id|inf
op_assign
id|dev-&gt;platform_data
suffix:semicolon
id|devptr-&gt;base
op_assign
id|ioremap
c_func
(paren
id|mem-&gt;start
comma
id|mem-&gt;end
op_minus
id|mem-&gt;start
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|devptr-&gt;base
)paren
(brace
id|kfree
c_func
(paren
id|devptr
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|devptr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Sharp Scoop Device found at 0x%08x -&gt; 0x%08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|mem-&gt;start
comma
(paren
r_int
r_int
)paren
id|devptr-&gt;base
)paren
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|devptr-&gt;base
comma
id|SCOOP_MCR
)paren
op_assign
l_int|0x0140
suffix:semicolon
id|reset_scoop
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|devptr-&gt;base
comma
id|SCOOP_GPCR
)paren
op_assign
id|inf-&gt;io_dir
op_amp
l_int|0xffff
suffix:semicolon
id|SCOOP_REG
c_func
(paren
id|devptr-&gt;base
comma
id|SCOOP_GPWR
)paren
op_assign
id|inf-&gt;io_out
op_amp
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scoop_remove
r_static
r_int
id|scoop_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|scoop_dev
op_star
id|sdev
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev
)paren
(brace
id|iounmap
c_func
(paren
id|sdev-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|scoop_driver
r_static
r_struct
id|device_driver
id|scoop_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sharp-scoop&quot;
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
id|scoop_probe
comma
dot
id|remove
op_assign
id|scoop_remove
comma
dot
id|suspend
op_assign
id|scoop_suspend
comma
dot
id|resume
op_assign
id|scoop_resume
comma
)brace
suffix:semicolon
DECL|function|scoop_init
r_int
id|__init
id|scoop_init
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
id|scoop_driver
)paren
suffix:semicolon
)brace
DECL|variable|scoop_init
id|subsys_initcall
c_func
(paren
id|scoop_init
)paren
suffix:semicolon
eof
