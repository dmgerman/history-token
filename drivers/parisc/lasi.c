multiline_comment|/*&n; *&t;LASI Device Driver&n; *&n; *&t;(c) Copyright 1999 Red Hat Software&n; *&t;Portions (c) Copyright 1999 The Puffin Group Inc.&n; *&t;Portions (c) Copyright 1999 Hewlett-Packard&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *&t;by Alan Cox &lt;alan@redhat.com&gt; and &n; * &t;   Alex deVries &lt;alex@onefishtwo.ca&gt;&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &quot;gsc.h&quot;
DECL|macro|LASI_VER
mdefine_line|#define LASI_VER&t;0xC008&t;/* LASI Version */
DECL|macro|LASI_IO_CONF
mdefine_line|#define LASI_IO_CONF&t;0x7FFFE&t;/* LASI primary configuration register */
DECL|macro|LASI_IO_CONF2
mdefine_line|#define LASI_IO_CONF2&t;0x7FFFF&t;/* LASI secondary configuration register */
DECL|function|lasi_choose_irq
r_static
r_void
id|lasi_choose_irq
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
comma
r_void
op_star
id|ctrl
)paren
(brace
r_int
id|irq
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;id.sversion
)paren
(brace
r_case
l_int|0x74
suffix:colon
id|irq
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Centronics */
r_case
l_int|0x7B
suffix:colon
id|irq
op_assign
l_int|13
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Audio */
r_case
l_int|0x81
suffix:colon
id|irq
op_assign
l_int|14
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Lasi itself */
r_case
l_int|0x82
suffix:colon
id|irq
op_assign
l_int|9
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* SCSI */
r_case
l_int|0x83
suffix:colon
id|irq
op_assign
l_int|20
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Floppy */
r_case
l_int|0x84
suffix:colon
id|irq
op_assign
l_int|26
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* PS/2 Keyboard */
r_case
l_int|0x87
suffix:colon
id|irq
op_assign
l_int|18
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* ISDN */
r_case
l_int|0x8A
suffix:colon
id|irq
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* LAN */
r_case
l_int|0x8C
suffix:colon
id|irq
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* RS232 */
r_case
l_int|0x8D
suffix:colon
id|irq
op_assign
(paren
id|dev-&gt;hw_path
op_eq
l_int|13
)paren
ques
c_cond
l_int|16
suffix:colon
l_int|17
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Telephone */
r_default
suffix:colon
r_return
suffix:semicolon
multiline_comment|/* unknown */
)brace
id|gsc_asic_assign_irq
c_func
(paren
id|ctrl
comma
id|irq
comma
op_amp
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|lasi_init_irq
id|lasi_init_irq
c_func
(paren
r_struct
id|gsc_asic
op_star
id|this_lasi
)paren
(brace
r_int
r_int
id|lasi_base
op_assign
id|this_lasi-&gt;hpa
suffix:semicolon
multiline_comment|/* Stop LASI barking for a bit */
id|gsc_writel
c_func
(paren
l_int|0x00000000
comma
id|lasi_base
op_plus
id|OFFSET_IMR
)paren
suffix:semicolon
multiline_comment|/* clear pending interrupts */
id|gsc_readl
c_func
(paren
id|lasi_base
op_plus
id|OFFSET_IRR
)paren
suffix:semicolon
multiline_comment|/* We&squot;re not really convinced we want to reset the onboard&n;         * devices. Firmware does it for us...&n;&t; */
multiline_comment|/* Resets */
multiline_comment|/* gsc_writel(0xFFFFFFFF, lasi_base+0x2000);*/
multiline_comment|/* Parallel */
r_if
c_cond
(paren
id|pdc_add_valid
c_func
(paren
id|lasi_base
op_plus
l_int|0x4004
)paren
op_eq
id|PDC_OK
)paren
(brace
id|gsc_writel
c_func
(paren
l_int|0xFFFFFFFF
comma
id|lasi_base
op_plus
l_int|0x4004
)paren
suffix:semicolon
)brace
multiline_comment|/* Audio */
multiline_comment|/* gsc_writel(0xFFFFFFFF, lasi_base+0x5000);*/
multiline_comment|/* Serial */
multiline_comment|/* gsc_writel(0xFFFFFFFF, lasi_base+0x6000);*/
multiline_comment|/* SCSI */
id|gsc_writel
c_func
(paren
l_int|0xFFFFFFFF
comma
id|lasi_base
op_plus
l_int|0x7000
)paren
suffix:semicolon
multiline_comment|/* LAN */
id|gsc_writel
c_func
(paren
l_int|0xFFFFFFFF
comma
id|lasi_base
op_plus
l_int|0x8000
)paren
suffix:semicolon
multiline_comment|/* Keyboard */
id|gsc_writel
c_func
(paren
l_int|0xFFFFFFFF
comma
id|lasi_base
op_plus
l_int|0xA000
)paren
suffix:semicolon
multiline_comment|/* FDC */
multiline_comment|/* Ok we hit it on the head with a hammer, our Dog is now&n;&t;** comatose and muzzled.  Devices will now unmask LASI&n;&t;** interrupts as they are registered as irq&squot;s in the LASI range.&n;&t;*/
multiline_comment|/* XXX: I thought it was `awks that got `it on the `ead with an&n;&t; * `ammer.  -- willy&n;&t; */
)brace
multiline_comment|/*&n;   ** lasi_led_init()&n;   ** &n;   ** lasi_led_init() initializes the LED controller on the LASI.&n;   **&n;   ** Since Mirage and Electra machines use a different LED&n;   ** address register, we need to check for these machines &n;   ** explicitly.&n; */
macro_line|#ifndef CONFIG_CHASSIS_LCD_LED
DECL|macro|lasi_led_init
mdefine_line|#define lasi_led_init(x)&t;/* nothing */
macro_line|#else
DECL|function|lasi_led_init
r_void
id|__init
id|lasi_led_init
c_func
(paren
r_int
r_int
id|lasi_hpa
)paren
(brace
r_int
r_int
id|datareg
suffix:semicolon
r_switch
c_cond
(paren
id|CPU_HVERSION
)paren
(brace
multiline_comment|/* Gecko machines have only one single LED, which can be permanently &n;&t;   turned on by writing a zero into the power control register. */
r_case
l_int|0x600
suffix:colon
multiline_comment|/* Gecko (712/60) */
r_case
l_int|0x601
suffix:colon
multiline_comment|/* Gecko (712/80) */
r_case
l_int|0x602
suffix:colon
multiline_comment|/* Gecko (712/100) */
r_case
l_int|0x603
suffix:colon
multiline_comment|/* Anole 64 (743/64) */
r_case
l_int|0x604
suffix:colon
multiline_comment|/* Anole 100 (743/100) */
r_case
l_int|0x605
suffix:colon
multiline_comment|/* Gecko (712/120) */
id|datareg
op_assign
id|lasi_hpa
op_plus
l_int|0x0000C000
suffix:semicolon
id|gsc_writeb
c_func
(paren
l_int|0
comma
id|datareg
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* no need to register the LED interrupt-function */
multiline_comment|/* Mirage and Electra machines need special offsets */
r_case
l_int|0x60A
suffix:colon
multiline_comment|/* Mirage Jr (715/64) */
r_case
l_int|0x60B
suffix:colon
multiline_comment|/* Mirage 100 */
r_case
l_int|0x60C
suffix:colon
multiline_comment|/* Mirage 100+ */
r_case
l_int|0x60D
suffix:colon
multiline_comment|/* Electra 100 */
r_case
l_int|0x60E
suffix:colon
multiline_comment|/* Electra 120 */
id|datareg
op_assign
id|lasi_hpa
op_minus
l_int|0x00020000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|datareg
op_assign
id|lasi_hpa
op_plus
l_int|0x0000C000
suffix:semicolon
r_break
suffix:semicolon
)brace
id|register_led_driver
c_func
(paren
id|DISPLAY_MODEL_LASI
comma
id|LED_CMD_REG_NONE
comma
(paren
r_char
op_star
)paren
id|datareg
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * lasi_power_off&n; *&n; * Function for lasi to turn off the power.  This is accomplished by setting a&n; * 1 to PWR_ON_L in the Power Control Register&n; * &n; */
DECL|variable|lasi_power_off_hpa
r_static
r_int
r_int
id|lasi_power_off_hpa
suffix:semicolon
DECL|function|lasi_power_off
r_static
r_void
id|lasi_power_off
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|datareg
suffix:semicolon
multiline_comment|/* calculate addr of the Power Control Register */
id|datareg
op_assign
id|lasi_power_off_hpa
op_plus
l_int|0x0000C000
suffix:semicolon
multiline_comment|/* Power down the machine */
id|gsc_writel
c_func
(paren
l_int|0x02
comma
id|datareg
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|lasi_init_chip
id|lasi_init_chip
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_struct
id|gsc_asic
op_star
id|lasi
suffix:semicolon
r_struct
id|gsc_irq
id|gsc_irq
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lasi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|lasi
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lasi
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|lasi-&gt;name
op_assign
l_string|&quot;Lasi&quot;
suffix:semicolon
id|lasi-&gt;hpa
op_assign
id|dev-&gt;hpa
suffix:semicolon
multiline_comment|/* Check the 4-bit (yes, only 4) version register */
id|lasi-&gt;version
op_assign
id|gsc_readl
c_func
(paren
id|lasi-&gt;hpa
op_plus
id|LASI_VER
)paren
op_amp
l_int|0xf
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s version %d at 0x%lx found.&bslash;n&quot;
comma
id|lasi-&gt;name
comma
id|lasi-&gt;version
comma
id|lasi-&gt;hpa
)paren
suffix:semicolon
multiline_comment|/* initialize the chassis LEDs really early */
id|lasi_led_init
c_func
(paren
id|lasi-&gt;hpa
)paren
suffix:semicolon
multiline_comment|/* Stop LASI barking for a bit */
id|lasi_init_irq
c_func
(paren
id|lasi
)paren
suffix:semicolon
multiline_comment|/* the IRQ lasi should use */
id|dev-&gt;irq
op_assign
id|gsc_alloc_irq
c_func
(paren
op_amp
id|gsc_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): cannot get GSC irq&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lasi
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|lasi-&gt;eim
op_assign
(paren
(paren
id|u32
)paren
id|gsc_irq.txn_addr
)paren
op_or
id|gsc_irq.txn_data
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|gsc_irq.irq
comma
id|gsc_asic_intr
comma
l_int|0
comma
l_string|&quot;lasi&quot;
comma
id|lasi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|lasi
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* enable IRQ&squot;s for devices below LASI */
id|gsc_writel
c_func
(paren
id|lasi-&gt;eim
comma
id|lasi-&gt;hpa
op_plus
id|OFFSET_IAR
)paren
suffix:semicolon
multiline_comment|/* Done init&squot;ing, register this driver */
id|ret
op_assign
id|gsc_common_setup
c_func
(paren
id|dev
comma
id|lasi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree
c_func
(paren
id|lasi
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|gsc_fixup_irqs
c_func
(paren
id|dev
comma
id|lasi
comma
id|lasi_choose_irq
)paren
suffix:semicolon
multiline_comment|/* initialize the power off function */
multiline_comment|/* FIXME: Record the LASI HPA for the power off function.  This should&n;&t; * ensure that only the first LASI (the one controlling the power off)&n;&t; * should set the HPA here */
id|lasi_power_off_hpa
op_assign
id|lasi-&gt;hpa
suffix:semicolon
id|pm_power_off
op_assign
id|lasi_power_off
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|lasi_tbl
r_static
r_struct
id|parisc_device_id
id|lasi_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_BA
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00081
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|lasi_driver
r_struct
id|parisc_driver
id|lasi_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Lasi&quot;
comma
dot
id|id_table
op_assign
id|lasi_tbl
comma
dot
id|probe
op_assign
id|lasi_init_chip
comma
)brace
suffix:semicolon
eof
