multiline_comment|/* pmc - Driver implementation for power management functions&n; * of Power Management Controller (PMC) on SPARCstation-Voyager.&n; *&n; * Copyright (c) 2002 Eric Brower (ebrower@usa.net)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
multiline_comment|/* Debug&n; *&n; * #define PMC_DEBUG_LED&n; * #define PMC_NO_IDLE&n; */
DECL|macro|PMC_MINOR
mdefine_line|#define PMC_MINOR&t;MISC_DYNAMIC_MINOR
DECL|macro|PMC_OBPNAME
mdefine_line|#define PMC_OBPNAME&t;&quot;SUNW,pmc&quot;
DECL|macro|PMC_DEVNAME
mdefine_line|#define PMC_DEVNAME &quot;pmc&quot;
DECL|macro|PMC_IDLE_REG
mdefine_line|#define PMC_IDLE_REG&t;0x00
DECL|macro|PMC_IDLE_ON
mdefine_line|#define PMC_IDLE_ON&t;&t;0x01
DECL|variable|regs
r_volatile
r_static
id|u8
op_star
id|regs
suffix:semicolon
DECL|variable|pmc_regsize
r_static
r_int
id|pmc_regsize
suffix:semicolon
DECL|macro|pmc_readb
mdefine_line|#define pmc_readb(offs)&t;&t;&t;(sbus_readb(regs+offs))
DECL|macro|pmc_writeb
mdefine_line|#define pmc_writeb(val, offs) &t;(sbus_writeb(val, regs+offs))
multiline_comment|/* &n; * CPU idle callback function&n; * See .../arch/sparc/kernel/process.c&n; */
DECL|function|pmc_swift_idle
r_void
id|pmc_swift_idle
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef PMC_DEBUG_LED
id|set_auxio
c_func
(paren
l_int|0x00
comma
id|AUXIO_LED
)paren
suffix:semicolon
macro_line|#endif
id|pmc_writeb
c_func
(paren
id|pmc_readb
c_func
(paren
id|PMC_IDLE_REG
)paren
op_or
id|PMC_IDLE_ON
comma
id|PMC_IDLE_REG
)paren
suffix:semicolon
macro_line|#ifdef PMC_DEBUG_LED
id|set_auxio
c_func
(paren
id|AUXIO_LED
comma
l_int|0x00
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|pmc_free
r_static
r_inline
r_void
id|pmc_free
c_func
(paren
r_void
)paren
(brace
id|sbus_iounmap
c_func
(paren
(paren
r_int
r_int
)paren
id|regs
comma
id|pmc_regsize
)paren
suffix:semicolon
)brace
DECL|function|pmc_probe
r_static
r_int
id|__init
id|pmc_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
op_assign
l_int|NULL
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
id|for_each_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
id|PMC_OBPNAME
)paren
)paren
(brace
r_goto
id|sbus_done
suffix:semicolon
)brace
)brace
)brace
id|sbus_done
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sdev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pmc_regsize
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
suffix:semicolon
id|regs
op_assign
(paren
id|u8
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
id|pmc_regsize
comma
id|PMC_OBPNAME
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to map registers&bslash;n&quot;
comma
id|PMC_DEVNAME
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifndef PMC_NO_IDLE
multiline_comment|/* Assign power management IDLE handler */
id|pm_idle
op_assign
id|pmc_swift_idle
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: power management initialized&bslash;n&quot;
comma
id|PMC_DEVNAME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This driver is not critical to the boot process&n; * and is easiest to ioremap when SBus is already&n; * initialized, so we install ourselves thusly:&n; */
DECL|variable|pmc_probe
id|__initcall
c_func
(paren
id|pmc_probe
)paren
suffix:semicolon
eof
