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
macro_line|#ifdef CONFIG_CPU_FREQ
DECL|function|sa11x0_freq_to_ppcr
r_int
r_int
id|sa11x0_freq_to_ppcr
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
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * Validate the speed in khz.  If we can&squot;t generate the precise&n; * frequency requested, round it down (to be on the safe side).&n; */
DECL|function|sa11x0_validatespeed
r_int
r_int
id|sa11x0_validatespeed
c_func
(paren
r_int
r_int
id|khz
)paren
(brace
r_return
id|cclk_frequency_100khz
(braket
id|sa11x0_freq_to_ppcr
c_func
(paren
id|khz
)paren
)braket
op_star
l_int|100
suffix:semicolon
)brace
DECL|function|sa11x0_init_clock
r_static
r_int
id|__init
id|sa11x0_init_clock
c_func
(paren
r_void
)paren
(brace
id|cpufreq_init
c_func
(paren
id|cclk_frequency_100khz
(braket
id|PPCR
op_amp
l_int|0xf
)braket
op_star
l_int|100
comma
l_int|59000
comma
l_int|287000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa11x0_init_clock
id|__initcall
c_func
(paren
id|sa11x0_init_clock
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; * We still need to provide this so building without cpufreq works.&n; */
DECL|function|cpufreq_get
r_int
r_int
id|cpufreq_get
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cclk_frequency_100khz
(braket
id|PPCR
op_amp
l_int|0xf
)braket
op_star
l_int|100
suffix:semicolon
)brace
DECL|variable|cpufreq_get
id|EXPORT_SYMBOL
c_func
(paren
id|cpufreq_get
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
id|local_irq_disable
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
DECL|function|sa1100_init
r_static
r_int
id|__init
id|sa1100_init
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
DECL|variable|sa1100_init
id|__initcall
c_func
(paren
id|sa1100_init
)paren
suffix:semicolon
DECL|variable|sa1100fb_backlight_power
r_void
(paren
op_star
id|sa1100fb_backlight_power
)paren
(paren
r_int
id|on
)paren
suffix:semicolon
DECL|variable|sa1100fb_lcd_power
r_void
(paren
op_star
id|sa1100fb_lcd_power
)paren
(paren
r_int
id|on
)paren
suffix:semicolon
DECL|variable|sa1100fb_backlight_power
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100fb_backlight_power
)paren
suffix:semicolon
DECL|variable|sa1100fb_lcd_power
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100fb_lcd_power
)paren
suffix:semicolon
multiline_comment|/*&n; * Common I/O mapping:&n; *&n; * Typically, static virtual address mappings are as follow:&n; *&n; * 0xf0000000-0xf3ffffff:&t;miscellaneous stuff (CPLDs, etc.)&n; * 0xf4000000-0xf4ffffff:&t;SA-1111&n; * 0xf5000000-0xf5ffffff:&t;reserved (used by cache flushing area)&n; * 0xf6000000-0xfffeffff:&t;reserved (internal SA1100 IO defined above)&n; * 0xffff0000-0xffff0fff:&t;SA1100 exception vectors&n; * 0xffff2000-0xffff2fff:&t;Minicache copy_user_page area&n; *&n; * Below 0xe8000000 is reserved for vm allocation.&n; *&n; * The machine specific code must provide the extra mapping beside the&n; * default mapping provided here.&n; */
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
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf8000000
comma
l_int|0x80000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
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
id|MT_DEVICE
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
id|MT_DEVICE
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
id|MT_DEVICE
)brace
multiline_comment|/* LCD + DMA */
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
comma
id|ARRAY_SIZE
c_func
(paren
id|standard_io_desc
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Disable the memory bus request/grant signals on the SA1110 to&n; * ensure that we don&squot;t receive spurious memory requests.  We set&n; * the MBGNT signal false to ensure the SA1111 doesn&squot;t own the&n; * SDRAM bus.&n; */
DECL|function|sa1110_mb_disable
r_void
id|__init
id|sa1110_mb_disable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|PGSR
op_and_assign
op_complement
id|GPIO_MBGNT
suffix:semicolon
id|GPCR
op_assign
id|GPIO_MBGNT
suffix:semicolon
id|GPDR
op_assign
(paren
id|GPDR
op_amp
op_complement
id|GPIO_MBREQ
)paren
op_or
id|GPIO_MBGNT
suffix:semicolon
id|GAFR
op_and_assign
op_complement
(paren
id|GPIO_MBGNT
op_or
id|GPIO_MBREQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If the system is going to use the SA-1111 DMA engines, set up&n; * the memory bus request/grant pins.&n; */
DECL|function|sa1110_mb_enable
r_void
id|__init
id|sa1110_mb_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|PGSR
op_and_assign
op_complement
id|GPIO_MBGNT
suffix:semicolon
id|GPCR
op_assign
id|GPIO_MBGNT
suffix:semicolon
id|GPDR
op_assign
(paren
id|GPDR
op_amp
op_complement
id|GPIO_MBREQ
)paren
op_or
id|GPIO_MBGNT
suffix:semicolon
id|GAFR
op_or_assign
(paren
id|GPIO_MBGNT
op_or
id|GPIO_MBREQ
)paren
suffix:semicolon
id|TUCR
op_or_assign
id|TUCR_MR
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
