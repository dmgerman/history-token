multiline_comment|/*&n; * arch/ppc/platforms/pcore_setup.c&n; *&n; * Setup routines for Force PCORE boards&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;pcore.h&quot;
r_extern
r_int
id|pcore_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|variable|board_type
r_static
r_int
id|board_type
suffix:semicolon
multiline_comment|/* Dummy variable to satisfy mpc10x_common.o */
DECL|variable|OpenPIC_Addr
r_void
op_star
id|OpenPIC_Addr
suffix:semicolon
r_static
r_int
DECL|function|pcore_show_cpuinfo
id|pcore_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Force Computers&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_type
op_eq
id|PCORE_TYPE_6750
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: PowerCore 6750&bslash;n&quot;
)paren
suffix:semicolon
r_else
multiline_comment|/* PCORE_TYPE_680 */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: PowerCore 680&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;L2&bslash;t&bslash;t: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_type
op_eq
id|PCORE_TYPE_6750
)paren
r_switch
c_cond
(paren
id|readb
c_func
(paren
id|PCORE_DCCR_REG
)paren
op_amp
id|PCORE_DCCR_L2_MASK
)paren
(brace
r_case
id|PCORE_DCCR_L2_0KB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;nocache&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCORE_DCCR_L2_256KB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;256KB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCORE_DCCR_L2_1MB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;1MB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCORE_DCCR_L2_512KB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;512KB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;error&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
multiline_comment|/* PCORE_TYPE_680 */
r_switch
c_cond
(paren
id|readb
c_func
(paren
id|PCORE_DCCR_REG
)paren
op_amp
id|PCORE_DCCR_L2_MASK
)paren
(brace
r_case
id|PCORE_DCCR_L2_2MB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;2MB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCORE_DCCR_L2_256KB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;reserved&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCORE_DCCR_L2_1MB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;1MB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCORE_DCCR_L2_512KB
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;512KB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;error&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pcore_setup_arch
id|pcore_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* Lookup PCI host bridges */
id|board_type
op_assign
id|pcore_find_bridges
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
macro_line|#ifdef CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_SDA2
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Force PCore port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pcore_restart
id|pcore_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Hard reset */
id|writeb
c_func
(paren
l_int|0x11
comma
l_int|0xfe000332
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|pcore_halt
id|pcore_halt
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn off user LEDs */
id|writeb
c_func
(paren
l_int|0x00
comma
l_int|0xfe000300
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pcore_power_off
id|pcore_power_off
c_func
(paren
r_void
)paren
(brace
id|pcore_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pcore_init_IRQ
id|pcore_init_IRQ
c_func
(paren
r_void
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
id|i8259_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space.&n; */
r_static
id|__inline__
r_void
DECL|function|pcore_set_bat
id|pcore_set_bat
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|bat3u
comma
id|bat3l
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; lis %0,0xf000&bslash;n &bslash;&n;&t;&t;&t;ori %1,%0,0x002a&bslash;n &bslash;&n;&t;&t;&t;ori %0,%0,0x1ffe&bslash;n &bslash;&n;&t;&t;&t;mtspr 0x21e,%0&bslash;n &bslash;&n;&t;&t;&t;mtspr 0x21f,%1&bslash;n &bslash;&n;&t;&t;&t;isync&bslash;n &bslash;&n;&t;&t;&t;sync &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|bat3u
)paren
comma
l_string|&quot;=r&quot;
(paren
id|bat3l
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
id|__init
DECL|function|pcore_find_end_of_memory
id|pcore_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Cover I/O space with a BAT */
multiline_comment|/* yuck, better hope your ram size is a power of 2  -- paulus */
id|pcore_set_bat
c_func
(paren
)paren
suffix:semicolon
r_return
id|mpc10x_get_mem_size
c_func
(paren
id|MPC10X_MEM_MAP_B
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pcore_map_io
id|pcore_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0xfe000000
comma
l_int|0xfe000000
comma
l_int|0x02000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|MPC10X_MAPB_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|MPC10X_MAPB_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|MPC10X_MAPB_DRAM_OFFSET
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|pcore_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|pcore_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|pcore_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|i8259_irq
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|pcore_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|pcore_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|pcore_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|pcore_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|pcore_halt
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T59
comma
id|PCORE_NVRAM_AS0
comma
id|PCORE_NVRAM_AS1
comma
id|PCORE_NVRAM_DATA
comma
l_int|8
)paren
suffix:semicolon
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|todc_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_m48txx_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_m48txx_write_val
suffix:semicolon
)brace
eof
