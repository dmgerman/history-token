multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/generic.c&n; *&n; * Author: Nicolas Pitre&n; *&n; * Code common to all SA11x0 machines.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
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
macro_line|#if defined(CONFIG_CPU_FREQ_SA1100) || defined(CONFIG_CPU_FREQ_SA1110)
multiline_comment|/* rounds up(!)  */
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
l_int|0
suffix:semicolon
id|i
OL
id|NR_FREQS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cclk_frequency_100khz
(braket
id|i
)braket
op_ge
id|khz
)paren
r_break
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|sa11x0_ppcr_to_freq
r_int
r_int
id|sa11x0_ppcr_to_freq
c_func
(paren
r_int
r_int
id|idx
)paren
(brace
r_int
r_int
id|freq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
id|NR_FREQS
)paren
id|freq
op_assign
id|cclk_frequency_100khz
(braket
id|idx
)braket
op_star
l_int|100
suffix:semicolon
r_return
id|freq
suffix:semicolon
)brace
multiline_comment|/* make sure that only the &quot;userspace&quot; governor is run -- anything else wouldn&squot;t make sense on&n; * this platform, anyway.&n; */
DECL|function|sa11x0_verify_speed
r_int
id|sa11x0_verify_speed
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;cpu
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
id|policy-&gt;cpuinfo.min_freq
comma
id|policy-&gt;cpuinfo.max_freq
)paren
suffix:semicolon
multiline_comment|/* make sure that at least one frequency is within the policy */
id|tmp
op_assign
id|cclk_frequency_100khz
(braket
id|sa11x0_freq_to_ppcr
c_func
(paren
id|policy-&gt;min
)paren
)braket
op_star
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|policy-&gt;max
)paren
id|policy-&gt;max
op_assign
id|tmp
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
id|policy-&gt;cpuinfo.min_freq
comma
id|policy-&gt;cpuinfo.max_freq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa11x0_getspeed
r_int
r_int
id|sa11x0_getspeed
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
op_star
l_int|100
suffix:semicolon
)brace
DECL|variable|sa11x0_getspeed
id|EXPORT_SYMBOL
c_func
(paren
id|sa11x0_getspeed
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
multiline_comment|/*&n; * This is the SA11x0 sched_clock implementation.  This has&n; * a resolution of 271ns, and a maximum value of 1165s.&n; *  ( * 1E9 / 3686400 =&gt; * 78125 / 288)&n; */
DECL|function|sched_clock
r_int
r_int
r_int
id|sched_clock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|v
suffix:semicolon
id|v
op_assign
(paren
r_int
r_int
r_int
)paren
id|OSCR
op_star
l_int|78125
suffix:semicolon
id|do_div
c_func
(paren
id|v
comma
l_int|288
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
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
DECL|variable|sa11x0udc_resources
r_static
r_struct
id|resource
id|sa11x0udc_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x80000000
comma
dot
id|end
op_assign
l_int|0x8000ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa11x0udc_dma_mask
r_static
id|u64
id|sa11x0udc_dma_mask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|sa11x0udc_device
r_static
r_struct
id|platform_device
id|sa11x0udc_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-udc&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|sa11x0udc_dma_mask
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa11x0udc_resources
)paren
comma
dot
id|resource
op_assign
id|sa11x0udc_resources
comma
)brace
suffix:semicolon
DECL|variable|sa11x0uart1_resources
r_static
r_struct
id|resource
id|sa11x0uart1_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x80010000
comma
dot
id|end
op_assign
l_int|0x8001ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa11x0uart1_device
r_static
r_struct
id|platform_device
id|sa11x0uart1_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-uart&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa11x0uart1_resources
)paren
comma
dot
id|resource
op_assign
id|sa11x0uart1_resources
comma
)brace
suffix:semicolon
DECL|variable|sa11x0uart3_resources
r_static
r_struct
id|resource
id|sa11x0uart3_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x80050000
comma
dot
id|end
op_assign
l_int|0x8005ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa11x0uart3_device
r_static
r_struct
id|platform_device
id|sa11x0uart3_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-uart&quot;
comma
dot
id|id
op_assign
l_int|3
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa11x0uart3_resources
)paren
comma
dot
id|resource
op_assign
id|sa11x0uart3_resources
comma
)brace
suffix:semicolon
DECL|variable|sa11x0mcp_resources
r_static
r_struct
id|resource
id|sa11x0mcp_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x80060000
comma
dot
id|end
op_assign
l_int|0x8006ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa11x0mcp_dma_mask
r_static
id|u64
id|sa11x0mcp_dma_mask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|sa11x0mcp_device
r_static
r_struct
id|platform_device
id|sa11x0mcp_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-mcp&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|sa11x0mcp_dma_mask
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa11x0mcp_resources
)paren
comma
dot
id|resource
op_assign
id|sa11x0mcp_resources
comma
)brace
suffix:semicolon
DECL|variable|sa11x0ssp_resources
r_static
r_struct
id|resource
id|sa11x0ssp_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x80070000
comma
dot
id|end
op_assign
l_int|0x8007ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa11x0ssp_dma_mask
r_static
id|u64
id|sa11x0ssp_dma_mask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|sa11x0ssp_device
r_static
r_struct
id|platform_device
id|sa11x0ssp_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-ssp&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|sa11x0ssp_dma_mask
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa11x0ssp_resources
)paren
comma
dot
id|resource
op_assign
id|sa11x0ssp_resources
comma
)brace
suffix:semicolon
DECL|variable|sa11x0fb_resources
r_static
r_struct
id|resource
id|sa11x0fb_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0xb0100000
comma
dot
id|end
op_assign
l_int|0xb010ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|IRQ_LCD
comma
dot
id|end
op_assign
id|IRQ_LCD
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa11x0fb_device
r_static
r_struct
id|platform_device
id|sa11x0fb_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-fb&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa11x0fb_resources
)paren
comma
dot
id|resource
op_assign
id|sa11x0fb_resources
comma
)brace
suffix:semicolon
DECL|variable|sa11x0pcmcia_device
r_static
r_struct
id|platform_device
id|sa11x0pcmcia_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-pcmcia&quot;
comma
dot
id|id
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|sa11x0_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|sa11x0udc_device
comma
op_amp
id|sa11x0uart1_device
comma
op_amp
id|sa11x0uart3_device
comma
op_amp
id|sa11x0mcp_device
comma
op_amp
id|sa11x0ssp_device
comma
op_amp
id|sa11x0pcmcia_device
comma
op_amp
id|sa11x0fb_device
comma
)brace
suffix:semicolon
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
id|platform_add_devices
c_func
(paren
id|sa11x0_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|sa11x0_devices
)paren
)paren
suffix:semicolon
)brace
DECL|variable|sa1100_init
id|arch_initcall
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
