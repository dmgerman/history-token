multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/generic.c&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * Code common to all PXA machines.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Since this file should be linked before any other machine specific file,&n; * the __initcall() here will be executed first.  This serves as default&n; * initialization stuff for PXA machines which can be overriden later if&n; * need be.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/*&n; * Return the current lclk requency in units of 10kHz&n; */
DECL|function|get_lclk_frequency_10khz
r_int
r_int
id|get_lclk_frequency_10khz
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
id|l
op_assign
id|CCCR
op_amp
l_int|0x1f
suffix:semicolon
r_switch
c_cond
(paren
id|l
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
l_int|9953
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
l_int|11796
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_int|13271
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
l_int|14746
suffix:semicolon
r_case
l_int|5
suffix:colon
r_return
l_int|16589
suffix:semicolon
r_case
l_int|0xf
suffix:colon
r_return
l_int|3320
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|get_lclk_frequency_10khz
id|EXPORT_SYMBOL
c_func
(paren
id|get_lclk_frequency_10khz
)paren
suffix:semicolon
multiline_comment|/*&n; * Handy function to set GPIO alternate functions&n; */
DECL|function|pxa_gpio_mode
r_void
id|pxa_gpio_mode
c_func
(paren
r_int
id|gpio_mode
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
id|gpio
op_assign
id|gpio_mode
op_amp
id|GPIO_MD_MASK_NR
suffix:semicolon
r_int
id|fn
op_assign
(paren
id|gpio_mode
op_amp
id|GPIO_MD_MASK_FN
)paren
op_rshift
l_int|8
suffix:semicolon
r_int
id|gafr
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpio_mode
op_amp
id|GPIO_MD_MASK_DIR
)paren
id|GPDR
c_func
(paren
id|gpio
)paren
op_or_assign
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
r_else
id|GPDR
c_func
(paren
id|gpio
)paren
op_and_assign
op_complement
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
id|gafr
op_assign
id|GAFR
c_func
(paren
id|gpio
)paren
op_amp
op_complement
(paren
l_int|0x3
op_lshift
(paren
(paren
(paren
id|gpio
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|GAFR
c_func
(paren
id|gpio
)paren
op_assign
id|gafr
op_or
(paren
id|fn
op_lshift
(paren
(paren
(paren
id|gpio
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|pxa_gpio_mode
id|EXPORT_SYMBOL
c_func
(paren
id|pxa_gpio_mode
)paren
suffix:semicolon
multiline_comment|/*&n; * Note that 0xfffe0000-0xffffffff is reserved for the vector table and&n; * cache flush area.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|standard_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xf6000000
comma
l_int|0x20000000
comma
l_int|0x01000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA0 IO */
(brace
l_int|0xf7000000
comma
l_int|0x30000000
comma
l_int|0x01000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA1 IO */
(brace
l_int|0xfc000000
comma
l_int|0x40000000
comma
l_int|0x01400000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Devs */
(brace
l_int|0xfe000000
comma
l_int|0x44000000
comma
l_int|0x00200000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* LCD */
(brace
l_int|0xff000000
comma
l_int|0x48000000
comma
l_int|0x00200000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Mem Ctl */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|pxa_map_io
r_void
id|__init
id|pxa_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|standard_io_desc
)paren
suffix:semicolon
)brace
eof