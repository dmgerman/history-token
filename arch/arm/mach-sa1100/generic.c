multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/generic.c&n; *&n; * Author: Nicolas Pitre&n; *&n; * Code common to all SA11x0 machines.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Since this file should be linked before any other machine specific file,&n; * the __initcall() here will be executed first.  This serves as default&n; * initialization stuff for SA1100 machines which can be overriden later if&n; * need be.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|macro|NR_FREQS
mdefine_line|#define NR_FREQS&t;16
multiline_comment|/*&n; * This table is setup for a 3.6864MHz Crystal.&n; */
DECL|variable|cclk_frequency_100khz
r_static
r_const
r_int
r_int
id|cclk_frequency_100khz
(braket
id|NR_FREQS
)braket
op_assign
(brace
l_int|590
comma
multiline_comment|/*  59.0 MHz */
l_int|737
comma
multiline_comment|/*  73.7 MHz */
l_int|885
comma
multiline_comment|/*  88.5 MHz */
l_int|1032
comma
multiline_comment|/* 103.2 MHz */
l_int|1180
comma
multiline_comment|/* 118.0 MHz */
l_int|1327
comma
multiline_comment|/* 132.7 MHz */
l_int|1475
comma
multiline_comment|/* 147.5 MHz */
l_int|1622
comma
multiline_comment|/* 162.2 MHz */
l_int|1769
comma
multiline_comment|/* 176.9 MHz */
l_int|1917
comma
multiline_comment|/* 191.7 MHz */
l_int|2064
comma
multiline_comment|/* 206.4 MHz */
l_int|2212
comma
multiline_comment|/* 221.2 MHz */
l_int|2359
comma
multiline_comment|/* 235.9 MHz */
l_int|2507
comma
multiline_comment|/* 250.7 MHz */
l_int|2654
comma
multiline_comment|/* 265.4 MHz */
l_int|2802
multiline_comment|/* 280.2 MHz */
)brace
suffix:semicolon
multiline_comment|/*&n; * Return the current CPU clock frequency in units of 100kHz&n; */
DECL|function|get_cclk_frequency
r_int
r_int
id|get_cclk_frequency
c_func
(paren
r_void
)paren
(brace
r_return
id|cclk_frequency_100khz
(braket
id|PPCR
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
DECL|variable|get_cclk_frequency
id|EXPORT_SYMBOL
c_func
(paren
id|get_cclk_frequency
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ
multiline_comment|/*&n; * Validate the speed in khz.  If we can&squot;t generate the precise&n; * frequency requested, round it down (to be on the safe side).&n; */
DECL|function|sa1100_validatespeed
r_int
r_int
id|sa1100_validatespeed
c_func
(paren
r_int
r_int
id|khz
)paren
(brace
r_int
id|i
suffix:semicolon
id|khz
op_div_assign
l_int|100
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|NR_FREQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|cclk_frequency_100khz
(braket
id|i
)braket
op_le
id|khz
)paren
r_break
suffix:semicolon
r_return
id|cclk_frequency_100khz
(braket
id|i
)braket
op_star
l_int|100
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, set the CPU frequency.  Since we&squot;ve done the validation&n; * above, we can match for an exact frequency.  If we don&squot;t find&n; * an exact match, we will to set the lowest frequency to be safe.&n; */
DECL|function|sa1100_setspeed
r_void
id|sa1100_setspeed
c_func
(paren
r_int
r_int
id|khz
)paren
(brace
r_int
id|i
suffix:semicolon
id|khz
op_div_assign
l_int|100
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|NR_FREQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|cclk_frequency_100khz
(braket
id|i
)braket
op_eq
id|khz
)paren
r_break
suffix:semicolon
singleline_comment|//printk(&quot;setting ppcr to %d&bslash;n&quot;, i);
id|PPCR
op_assign
id|i
suffix:semicolon
)brace
DECL|function|sa1100_init_clock
r_static
r_int
id|__init
id|sa1100_init_clock
c_func
(paren
r_void
)paren
(brace
id|cpufreq_init
c_func
(paren
id|get_cclk_frequency
c_func
(paren
)paren
op_star
l_int|100
)paren
suffix:semicolon
id|cpufreq_setfunctions
c_func
(paren
id|sa1100_validatespeed
comma
id|sa1100_setspeed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100_init_clock
id|__initcall
c_func
(paren
id|sa1100_init_clock
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Default power-off for SA1100&n; */
DECL|function|sa1100_power_off
r_static
r_void
id|sa1100_power_off
c_func
(paren
r_void
)paren
(brace
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* disable internal oscillator, float CS lines */
id|PCFR
op_assign
(paren
id|PCFR_OPDE
op_or
id|PCFR_FP
op_or
id|PCFR_FS
)paren
suffix:semicolon
multiline_comment|/* enable wake-up on GPIO0 (Assabet...) */
id|PWER
op_assign
id|GFER
op_assign
id|GRER
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * set scratchpad to zero, just in case it is used as a&n;&t; * restart address by the bootloader.&n;&t; */
id|PSPR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* enter sleep mode */
id|PMCR
op_assign
id|PMCR_SF
suffix:semicolon
)brace
DECL|function|sa1100_set_poweroff
r_static
r_int
id|__init
id|sa1100_set_poweroff
c_func
(paren
r_void
)paren
(brace
id|pm_power_off
op_assign
id|sa1100_power_off
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100_set_poweroff
id|__initcall
c_func
(paren
id|sa1100_set_poweroff
)paren
suffix:semicolon
multiline_comment|/*&n; * Common I/O mapping:&n; *&n; * Typically, static virtual address mappings are as follow:&n; *&n; * 0xe8000000-0xefffffff:&t;flash memory (especially when multiple flash&n; * &t;&t;&t;&t;banks need to be mapped contigously)&n; * 0xf0000000-0xf3ffffff:&t;miscellaneous stuff (CPLDs, etc.)&n; * 0xf4000000-0xf4ffffff:&t;SA-1111&n; * 0xf5000000-0xf5ffffff:&t;reserved (used by cache flushing area)&n; * 0xf6000000-0xffffffff:&t;reserved (internal SA1100 IO defined above)&n; *&n; * Below 0xe8000000 is reserved for vm allocation.&n; *&n; * The machine specific code must provide the extra mapping beside the&n; * default mapping provided here.&n; */
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
l_int|1
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
l_int|1
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
l_int|0xf8000000
comma
l_int|0x80000000
comma
l_int|0x00100000
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
multiline_comment|/* PCM */
(brace
l_int|0xfa000000
comma
l_int|0x90000000
comma
l_int|0x00100000
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
multiline_comment|/* SCM */
(brace
l_int|0xfc000000
comma
l_int|0xa0000000
comma
l_int|0x00100000
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
multiline_comment|/* MER */
(brace
l_int|0xfe000000
comma
l_int|0xb0000000
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
multiline_comment|/* LCD + DMA */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|sa1100_map_io
r_void
id|__init
id|sa1100_map_io
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
