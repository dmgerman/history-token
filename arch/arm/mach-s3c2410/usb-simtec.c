multiline_comment|/* linux/arch/arm/mach-s3c2410/usb-simtec.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.simtec.co.uk/products/EB2410ITX/&n; *&n; * Simtec BAST and Thorcom VR1000 USB port support functions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *&t;14-Sep-2004 BJD  Created&n;*/
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/arch/bast-map.h&gt;
macro_line|#include &lt;asm/arch/bast-irq.h&gt;
macro_line|#include &lt;asm/arch/usb-control.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;devs.h&quot;
macro_line|#include &quot;usb-simtec.h&quot;
multiline_comment|/* control power and monitor over-current events on various Simtec&n; * designed boards.&n;*/
r_static
r_void
DECL|function|usb_simtec_powercontrol
id|usb_simtec_powercontrol
c_func
(paren
r_int
id|port
comma
r_int
id|to
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;usb_simtec_powercontrol(%d,%d)&bslash;n&quot;
comma
id|port
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|1
)paren
(brace
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPB4
comma
id|to
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;GPBDAT now %08x&bslash;n&quot;
comma
id|__raw_readl
c_func
(paren
id|S3C2410_GPBDAT
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
id|irqreturn_t
DECL|function|usb_simtec_ocirq
id|usb_simtec_ocirq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|pw
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|s3c2410_hcd_info
op_star
id|info
op_assign
(paren
r_struct
id|s3c2410_hcd_info
op_star
)paren
id|pw
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_gpio_getpin
c_func
(paren
id|S3C2410_GPG10
)paren
op_eq
l_int|0
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;usb_simtec: over-current irq (oc detected)&bslash;n&quot;
)paren
suffix:semicolon
id|s3c2410_report_oc
c_func
(paren
id|info
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;usb_simtec: over-current irq (oc cleared)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|usb_simtec_enableoc
r_static
r_void
id|usb_simtec_enableoc
c_func
(paren
r_struct
id|s3c2410_hcd_info
op_star
id|info
comma
r_int
id|on
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;claiming usb overccurent&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|IRQ_USBOC
comma
id|usb_simtec_ocirq
comma
id|SA_INTERRUPT
comma
l_string|&quot;usb-oc&quot;
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;failed to request usb oc irq&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_irq_type
c_func
(paren
id|IRQ_USBOC
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
)brace
r_else
(brace
id|free_irq
c_func
(paren
id|IRQ_USBOC
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
DECL|variable|usb_simtec_info
r_static
r_struct
id|s3c2410_hcd_info
id|usb_simtec_info
op_assign
(brace
dot
id|port
(braket
l_int|0
)braket
op_assign
(brace
dot
id|flags
op_assign
id|S3C_HCDFLG_USED
)brace
comma
dot
id|port
(braket
l_int|1
)braket
op_assign
(brace
dot
id|flags
op_assign
id|S3C_HCDFLG_USED
)brace
comma
dot
id|power_control
op_assign
id|usb_simtec_powercontrol
comma
dot
id|enable_oc
op_assign
id|usb_simtec_enableoc
comma
)brace
suffix:semicolon
DECL|function|usb_simtec_init
r_int
id|usb_simtec_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;USB Power Control, (c) 2004 Simtec Electronics&bslash;n&quot;
)paren
suffix:semicolon
id|s3c_device_usb.dev.platform_data
op_assign
op_amp
id|usb_simtec_info
suffix:semicolon
id|s3c2410_gpio_cfgpin
c_func
(paren
id|S3C2410_GPB4
comma
id|S3C2410_GPB4_OUTP
)paren
suffix:semicolon
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPB4
comma
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;GPB: CON=%08x, DAT=%08x&bslash;n&quot;
comma
id|__raw_readl
c_func
(paren
id|S3C2410_GPBCON
)paren
comma
id|__raw_readl
c_func
(paren
id|S3C2410_GPBDAT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|s3c2410_modify_misccr
c_func
(paren
id|S3C2410_MISCCR_USBHOST
comma
id|S3C2410_MISCCR_USBDEV
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
