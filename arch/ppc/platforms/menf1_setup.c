multiline_comment|/*&n; * arch/ppc/platforms/menf1_setup.c&n; &n; * Board setup routines for MEN F1&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
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
macro_line|#include &quot;menf1.h&quot;
r_extern
r_void
id|menf1_find_bridges
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
multiline_comment|/* Dummy variable to satisfy mpc10x_common.o */
DECL|variable|OpenPIC_Addr
r_void
op_star
id|OpenPIC_Addr
suffix:semicolon
r_static
r_int
DECL|function|menf1_show_cpuinfo
id|menf1_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: MEN F1&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|menf1_setup_arch
id|menf1_setup_arch
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
id|menf1_find_bridges
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
id|Root_HDA2
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
l_string|&quot;MEN F1 port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|menf1_restart
id|menf1_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_int
id|picr1
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Firmware doesn&squot;t like re-entry using Map B (CHRP), so make sure the&n;&t; * PCI bridge is using MAP A (PReP).&n;&t; */
id|pdev
op_assign
id|pci_find_slot
c_func
(paren
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pdev
op_eq
l_int|NULL
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* paranoia */
id|pci_read_config_dword
c_func
(paren
id|pdev
comma
id|MPC10X_CFG_PICR1_REG
comma
op_amp
id|picr1
)paren
suffix:semicolon
id|picr1
op_assign
(paren
id|picr1
op_amp
op_complement
id|MPC10X_CFG_PICR1_ADDR_MAP_MASK
)paren
op_or
id|MPC10X_CFG_PICR1_ADDR_MAP_A
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|pdev
comma
id|MPC10X_CFG_PICR1_REG
comma
id|picr1
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
multiline_comment|/* SRR0 has system reset vector, SRR1 has default MSR value */
multiline_comment|/* rfi restores MSR from SRR1 and sets the PC to the SRR0 value */
id|__asm__
id|__volatile__
(paren
"&quot;&bslash;"
id|n
"&bslash;"
id|lis
l_int|3
comma
l_int|0xfff0
id|ori
l_int|3
comma
l_int|3
comma
l_int|0x0100
id|mtspr
l_int|26
comma
l_int|3
id|li
l_int|3
comma
l_int|0
id|mtspr
l_int|27
comma
l_int|3
id|rfi
"&quot;"
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
DECL|function|menf1_halt
id|menf1_halt
c_func
(paren
r_void
)paren
(brace
id|__cli
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
DECL|function|menf1_power_off
id|menf1_power_off
c_func
(paren
r_void
)paren
(brace
id|menf1_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|menf1_init_IRQ
id|menf1_init_IRQ
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
id|NUM_8259_INTERRUPTS
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
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|menf1_get_irq
r_static
r_int
id|menf1_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|i8259_poll
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xF0000000.&n; */
r_static
id|__inline__
r_void
DECL|function|menf1_set_bat
id|menf1_set_bat
c_func
(paren
r_void
)paren
(brace
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
multiline_comment|/* wait for all outstanding memory accesses to complete */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup DBATs */
id|mtspr
c_func
(paren
id|DBAT3U
comma
l_int|0xf0001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT3L
comma
l_int|0xf000002a
)paren
suffix:semicolon
multiline_comment|/* wait for updates */
id|mb
c_func
(paren
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
r_static
r_int
r_int
id|__init
DECL|function|menf1_find_end_of_memory
id|menf1_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Cover the I/O with a BAT */
id|menf1_set_bat
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Read the memory size from the MPC107 SMC */
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
DECL|function|menf1_map_io
id|menf1_map_io
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
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
multiline_comment|/* IDE functions */
r_static
r_void
id|__init
DECL|function|menf1_ide_init_hwif_ports
id|menf1_ide_init_hwif_ports
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
id|data_port
suffix:semicolon
r_int
id|i
op_assign
l_int|8
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
suffix:semicolon
id|reg
op_add_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_port
)paren
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
r_else
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|hw-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_plus
l_int|0x206
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|menf1_ide_default_irq
id|menf1_ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
id|MENF1_IDE0_BASE_ADDR
)paren
r_return
l_int|14
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
id|MENF1_IDE1_BASE_ADDR
)paren
r_return
l_int|15
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ide_ioreg_t
DECL|function|menf1_ide_default_io_base
id|menf1_ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|index
op_eq
l_int|0
)paren
r_return
id|MENF1_IDE0_BASE_ADDR
suffix:semicolon
r_else
r_if
c_cond
(paren
id|index
op_eq
l_int|1
)paren
r_return
id|MENF1_IDE1_BASE_ADDR
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
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
id|menf1_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|menf1_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|menf1_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|menf1_get_irq
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|menf1_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|menf1_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|menf1_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|menf1_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|menf1_halt
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T59
comma
id|MENF1_NVRAM_AS0
comma
id|MENF1_NVRAM_AS1
comma
id|MENF1_NVRAM_DATA
comma
l_int|7
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
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
id|ppc_ide_md.default_io_base
op_assign
id|menf1_ide_default_io_base
suffix:semicolon
id|ppc_ide_md.default_irq
op_assign
id|menf1_ide_default_irq
suffix:semicolon
id|ppc_ide_md.ide_init_hwif
op_assign
id|menf1_ide_init_hwif_ports
suffix:semicolon
macro_line|#endif
)brace
eof
