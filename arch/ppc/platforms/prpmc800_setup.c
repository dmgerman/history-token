multiline_comment|/*&n; *&n; * Author: Dale Farnsworth &lt;dale.farnsworth@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;platforms/prpmc800.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/harrier.h&gt;
DECL|macro|HARRIER_REVI_REG
mdefine_line|#define HARRIER_REVI_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_REVI_OFF)
DECL|macro|HARRIER_UCTL_REG
mdefine_line|#define HARRIER_UCTL_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_UCTL_OFF)
DECL|macro|HARRIER_MISC_CSR_REG
mdefine_line|#define HARRIER_MISC_CSR_REG  (PRPMC800_HARRIER_XCSR_BASE+HARRIER_MISC_CSR_OFF)
DECL|macro|HARRIER_IFEVP_REG
mdefine_line|#define HARRIER_IFEVP_REG   (PRPMC800_HARRIER_MPIC_BASE+HARRIER_MPIC_IFEVP_OFF)
DECL|macro|HARRIER_IFEDE_REG
mdefine_line|#define HARRIER_IFEDE_REG   (PRPMC800_HARRIER_MPIC_BASE+HARRIER_MPIC_IFEDE_OFF)
DECL|macro|HARRIER_FEEN_REG
mdefine_line|#define HARRIER_FEEN_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_FEEN_OFF)
DECL|macro|HARRIER_FEMA_REG
mdefine_line|#define HARRIER_FEMA_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_FEMA_OFF)
r_extern
r_void
id|prpmc800_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mpic_init
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
DECL|variable|__initdata
r_static
id|u_char
id|prpmc800_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
l_int|1
comma
multiline_comment|/* PRPMC800_INT_HOSTINT0 */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_DEBUGINT */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_HARRIER_WDT */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_HOSTINT1 */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_HOSTINT2 */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_HOSTINT3 */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_PMC_INTA */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_PMC_INTB */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_PMC_INTC */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_PMC_INTD */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
l_int|1
comma
multiline_comment|/* PRPMC800_INT_HARRIER_INT (UARTS, ABORT, DMA) */
)brace
suffix:semicolon
r_static
r_int
DECL|function|prpmc800_show_cpuinfo
id|prpmc800_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: PrPMC800&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|prpmc800_setup_arch
id|prpmc800_setup_arch
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
id|prpmc800_find_bridges
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
id|OpenPIC_InitSenses
op_assign
id|prpmc800_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|prpmc800_openpic_initsenses
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PrPMC800 port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Compute the PrPMC800&squot;s tbl frequency using the baud clock as a reference.&n; */
r_static
r_void
id|__init
DECL|function|prpmc800_calibrate_decr
id|prpmc800_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tbl_start
comma
id|tbl_end
suffix:semicolon
r_int
r_int
id|current_state
comma
id|old_state
comma
id|tb_ticks_per_second
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|harrier_revision
suffix:semicolon
id|harrier_revision
op_assign
id|readb
c_func
(paren
id|HARRIER_REVI_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|harrier_revision
OL
l_int|2
)paren
(brace
multiline_comment|/* XTAL64 was broken in harrier revision 1 */
id|printk
c_func
(paren
l_string|&quot;time_init: Harrier revision %d, assuming 100 Mhz bus&bslash;n&quot;
comma
id|harrier_revision
)paren
suffix:semicolon
id|tb_ticks_per_second
op_assign
l_int|100000000
op_div
l_int|4
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|tb_ticks_per_second
op_div
id|HZ
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|tb_ticks_per_second
comma
l_int|1000000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The XTAL64 bit oscillates at the 1/64 the base baud clock&n;&t; * Set count to XTAL64 cycles per second.  Since we&squot;ll count&n;&t; * half-cycles, we&squot;ll reach the count in half a second.&n;&t; */
id|count
op_assign
id|PRPMC800_BASE_BAUD
op_div
l_int|64
suffix:semicolon
multiline_comment|/* Find the first edge of the baud clock */
id|old_state
op_assign
id|readb
c_func
(paren
id|HARRIER_UCTL_REG
)paren
op_amp
id|HARRIER_XTAL64_MASK
suffix:semicolon
r_do
(brace
id|current_state
op_assign
id|readb
c_func
(paren
id|HARRIER_UCTL_REG
)paren
op_amp
id|HARRIER_XTAL64_MASK
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old_state
op_eq
id|current_state
)paren
(brace
suffix:semicolon
)brace
id|old_state
op_assign
id|current_state
suffix:semicolon
multiline_comment|/* Get the starting time base value */
id|tbl_start
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Loop until we have found a number of edges (half-cycles)&n;&t; * equal to the count (half a second)&n;&t; */
r_do
(brace
r_do
(brace
id|current_state
op_assign
id|readb
c_func
(paren
id|HARRIER_UCTL_REG
)paren
op_amp
id|HARRIER_XTAL64_MASK
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old_state
op_eq
id|current_state
)paren
(brace
suffix:semicolon
)brace
id|old_state
op_assign
id|current_state
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|count
)paren
suffix:semicolon
multiline_comment|/* Get the ending time base value */
id|tbl_end
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We only counted for half a second, so double to get ticks/second */
id|tb_ticks_per_second
op_assign
(paren
id|tbl_end
op_minus
id|tbl_start
)paren
op_star
l_int|2
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|tb_ticks_per_second
op_div
id|HZ
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|tb_ticks_per_second
comma
l_int|1000000
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|prpmc800_restart
id|prpmc800_restart
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
id|writeb
c_func
(paren
id|HARRIER_RSTOUT_MASK
comma
id|HARRIER_MISC_CSR_REG
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
DECL|function|prpmc800_halt
id|prpmc800_halt
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
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|prpmc800_power_off
id|prpmc800_power_off
c_func
(paren
r_void
)paren
(brace
id|prpmc800_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Resolves the open_pic.c build without including i8259.c */
DECL|function|i8259_poll
r_int
id|i8259_poll
c_func
(paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|prpmc800_init_IRQ
id|prpmc800_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|openpic_init
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
DECL|macro|PRIORITY
mdefine_line|#define PRIORITY&t;15
DECL|macro|VECTOR
mdefine_line|#define VECTOR&t; &t;16
DECL|macro|PROCESSOR
mdefine_line|#define PROCESSOR&t;0
multiline_comment|/* initialize the harrier&squot;s internal interrupt priority 15, irq 1 */
id|out_be32
c_func
(paren
(paren
id|u32
op_star
)paren
id|HARRIER_IFEVP_REG
comma
(paren
id|PRIORITY
op_lshift
l_int|16
)paren
op_or
id|VECTOR
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|u32
op_star
)paren
id|HARRIER_IFEDE_REG
comma
(paren
l_int|1
op_lshift
id|PROCESSOR
)paren
)paren
suffix:semicolon
multiline_comment|/* enable functional exceptions for uarts and abort */
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|HARRIER_FEEN_REG
comma
(paren
id|HARRIER_FE_UA0
op_or
id|HARRIER_FE_UA1
)paren
)paren
suffix:semicolon
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|HARRIER_FEMA_REG
comma
op_complement
(paren
id|HARRIER_FE_UA0
op_or
id|HARRIER_FE_UA1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space.&n; */
r_static
id|__inline__
r_void
DECL|function|prpmc800_set_bat
id|prpmc800_set_bat
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
r_static
r_int
id|mapping_set
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping_set
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; lis %0,0xf000&bslash;n &bslash;&n;&t;&t;&t;&t;ori %1,%0,0x002a&bslash;n &bslash;&n;&t;&t;&t;&t;ori %0,%0,0x1ffe&bslash;n &bslash;&n;&t;&t;&t;&t;mtspr 0x21e,%0&bslash;n &bslash;&n;&t;&t;&t;&t;mtspr 0x21f,%1&bslash;n &bslash;&n;&t;&t;&t;&t;isync&bslash;n &bslash;&n;&t;&t;&t;&t;sync &quot;
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
id|mapping_set
op_assign
l_int|1
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#ifdef  CONFIG_SERIAL_TEXT_DEBUG
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|variable|rs_table
r_static
r_struct
id|serial_state
id|rs_table
(braket
id|RS_TABLE_SIZE
)braket
op_assign
(brace
id|SERIAL_PORT_DFNS
multiline_comment|/* Defined in &lt;asm/serial.h&gt; */
)brace
suffix:semicolon
r_void
DECL|function|prpmc800_progress
id|prpmc800_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_volatile
r_char
id|c
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|com_port
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|com_port_lsr
suffix:semicolon
id|com_port
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|rs_table
(braket
l_int|0
)braket
dot
id|port
suffix:semicolon
id|com_port_lsr
op_assign
id|com_port
op_plus
id|UART_LSR
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
id|com_port_lsr
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
id|com_port
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
id|com_port_lsr
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
id|com_port
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
multiline_comment|/*&n; * We need to read the Harrier memory controller&n; * to properly determine this value&n; */
r_static
r_int
r_int
id|__init
DECL|function|prpmc800_find_end_of_memory
id|prpmc800_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Cover the harrier registers with a BAT */
id|prpmc800_set_bat
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Read the memory size from the Harrier XCSR */
r_return
id|harrier_get_mem_size
c_func
(paren
id|PRPMC800_HARRIER_XCSR_BASE
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|prpmc800_map_io
id|prpmc800_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0x80000000
comma
l_int|0x80000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
l_int|0xf0000000
comma
l_int|0xf0000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
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
id|prpmc800_set_bat
c_func
(paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|PRPMC800_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|PRPMC800_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|PRPMC800_PCI_DRAM_OFFSET
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|prpmc800_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|prpmc800_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|prpmc800_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|prpmc800_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|prpmc800_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|prpmc800_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|prpmc800_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|prpmc800_halt
suffix:semicolon
multiline_comment|/* PrPMC800 has no timekeeper part */
id|ppc_md.time_init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|prpmc800_calibrate_decr
suffix:semicolon
macro_line|#ifdef  CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|prpmc800_progress
suffix:semicolon
macro_line|#else   /* !CONFIG_SERIAL_TEXT_DEBUG */
id|ppc_md.progress
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif  /* CONFIG_SERIAL_TEXT_DEBUG */
)brace
eof
