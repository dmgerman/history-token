multiline_comment|/*&n; * arch/ppc/platforms/zx4500_setup.c&n; *&n; * Board setup routines for Znyx ZX4500 family of cPCI boards.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2000, 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * This file adds support for the Znyx ZX4500 series of cPCI boards.&n; * These boards have an 8240, UART on the processor bus, a PPMC slot (for now&n; * the card in this slot can _not_ be a monarch), Broadcom BCM5600, and an&n; * Intel 21554 bridge.&n; *&n; * Currently, this port assumes that the 8240 is the master and performs PCI&n; * arbitration, etc.  It is also assumed that the 8240 is wired to come up&n; * using memory MAP B (CHRP map).&n; *&n; * Note: This board port will not work properly as it is.  You must apply the&n; *&t; patch that is at ftp://ftp.mvista.com/pub/Area51/zx4500/zx_patch_2_5&n; */
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
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;zx4500.h&quot;
DECL|variable|__initdata
r_static
id|u_char
id|zx4500_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* 0-15 are not used on an 8240 EPIC */
l_int|0
comma
multiline_comment|/* 1 */
l_int|0
comma
multiline_comment|/* 2 */
l_int|0
comma
multiline_comment|/* 3 */
l_int|0
comma
multiline_comment|/* 4 */
l_int|0
comma
multiline_comment|/* 5 */
l_int|0
comma
multiline_comment|/* 6 */
l_int|0
comma
multiline_comment|/* 7 */
l_int|0
comma
multiline_comment|/* 8 */
l_int|0
comma
multiline_comment|/* 9 */
l_int|0
comma
multiline_comment|/* 10 */
l_int|0
comma
multiline_comment|/* 11 */
l_int|0
comma
multiline_comment|/* 12 */
l_int|0
comma
multiline_comment|/* 13 */
l_int|0
comma
multiline_comment|/* 14 */
l_int|0
comma
multiline_comment|/* 15 */
l_int|1
comma
multiline_comment|/* 16: EPIC IRQ 0: Active Low -- PMC #INTA &amp; #INTC */
l_int|1
comma
multiline_comment|/* 17: EPIC IRQ 1: Active Low -- UART */
l_int|1
comma
multiline_comment|/* 18: EPIC IRQ 2: Active Low -- BCM5600 #INTA */
l_int|1
comma
multiline_comment|/* 19: EPIC IRQ 3: Active Low -- 21554 #SINTA */
l_int|1
comma
multiline_comment|/* 20: EPIC IRQ 4: Active Low -- PMC #INTB &amp; #INTD */
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|zx4500_setup_arch
id|zx4500_setup_arch
c_func
(paren
r_void
)paren
(brace
r_char
id|boot_string
(braket
id|ZX4500_BOOT_STRING_LEN
op_plus
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|boot_arg
suffix:semicolon
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
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
macro_line|#if&t;defined(CONFIG_ROOT_NFS)
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_SDA1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Get boot string from flash */
id|strncpy
c_func
(paren
id|boot_string
comma
(paren
r_char
op_star
)paren
id|ZX4500_BOOT_STRING_ADDR
comma
id|ZX4500_BOOT_STRING_LEN
)paren
suffix:semicolon
id|boot_string
(braket
id|ZX4500_BOOT_STRING_LEN
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Can be delimited by 0xff */
id|boot_arg
op_assign
id|strchr
c_func
(paren
id|boot_string
comma
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|boot_arg
op_ne
l_int|NULL
)paren
(brace
op_star
id|boot_arg
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/* First 3 chars must be &squot;dev&squot;.  If not, ignore. */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|boot_string
comma
l_string|&quot;dev&quot;
comma
l_int|3
)paren
)paren
(brace
multiline_comment|/* skip &squot;dev?&squot; and any blanks after it */
id|boot_arg
op_assign
id|strchr
c_func
(paren
id|boot_string
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|boot_arg
op_ne
l_int|NULL
)paren
(brace
r_while
c_loop
(paren
op_star
id|boot_arg
op_eq
l_char|&squot; &squot;
)paren
id|boot_arg
op_increment
suffix:semicolon
id|strcat
c_func
(paren
id|cmd_line
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|cmd_line
comma
id|boot_arg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* nothing but serial consoles... */
id|printk
c_func
(paren
l_string|&quot;Znyx ZX4500 Series High Performance Switch&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ZX4500 port (C) 2000, 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Lookup PCI host bridge */
id|zx4500_find_bridges
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ZX4500 Board ID: 0x%x, Revision #: 0x%x&bslash;n&quot;
comma
id|in_8
c_func
(paren
(paren
r_volatile
id|u_char
op_star
)paren
id|ZX4500_CPLD_BOARD_ID
)paren
comma
id|in_8
c_func
(paren
(paren
r_volatile
id|u_char
op_star
)paren
id|ZX4500_CPLD_REV
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
id|ulong
id|__init
DECL|function|zx4500_find_end_of_memory
id|zx4500_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
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
DECL|function|zx4500_map_io
id|zx4500_map_io
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
multiline_comment|/*&n; * Enable interrupts routed thru CPLD to reach the 8240&squot;s EPIC.&n; * Need to enable all 4 PMC intrs, BCM INTA, and 21554 SINTA to 8240.&n; * UART intrs routed directly to 8240 (not thru CPLD).&n; */
r_static
r_void
id|__init
DECL|function|zx4500_enable_cpld_intrs
id|zx4500_enable_cpld_intrs
c_func
(paren
r_void
)paren
(brace
id|u_char
id|sysctl
suffix:semicolon
id|sysctl
op_assign
id|in_8
c_func
(paren
(paren
r_volatile
id|u_char
op_star
)paren
id|ZX4500_CPLD_SYSCTL
)paren
suffix:semicolon
id|sysctl
op_or_assign
(paren
id|ZX4500_CPLD_SYSCTL_PMC
op_or
id|ZX4500_CPLD_SYSCTL_BCM
op_or
id|ZX4500_CPLD_SYSCTL_SINTA
)paren
suffix:semicolon
id|out_8
c_func
(paren
(paren
r_volatile
id|u_char
op_star
)paren
id|ZX4500_CPLD_SYSCTL
comma
id|sysctl
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|zx4500_init_IRQ
id|zx4500_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|OpenPIC_InitSenses
op_assign
id|zx4500_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|zx4500_openpic_initsenses
)paren
suffix:semicolon
id|openpic_init
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|zx4500_enable_cpld_intrs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Allow CPLD to route intrs to 8240 */
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|zx4500_restart
id|zx4500_restart
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
id|out_8
c_func
(paren
(paren
r_volatile
id|u_char
op_star
)paren
id|ZX4500_CPLD_RESET
comma
id|ZX4500_CPLD_RESET_XBUS
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Restart failed.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_static
r_void
DECL|function|zx4500_power_off
id|zx4500_power_off
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* No way to shut power off with software */
multiline_comment|/* NOTREACHED */
)brace
r_static
r_void
DECL|function|zx4500_halt
id|zx4500_halt
c_func
(paren
r_void
)paren
(brace
id|zx4500_power_off
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_static
r_int
DECL|function|zx4500_get_bus_speed
id|zx4500_get_bus_speed
c_func
(paren
r_void
)paren
(brace
r_int
id|bus_speed
suffix:semicolon
id|bus_speed
op_assign
l_int|100000000
suffix:semicolon
r_return
id|bus_speed
suffix:semicolon
)brace
r_static
r_int
DECL|function|zx4500_show_cpuinfo
id|zx4500_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|uint
id|pvid
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Znyx&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: ZX4500&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: PVID: 0x%x, vendor: %s&bslash;n&quot;
comma
id|pvid
comma
(paren
id|pvid
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
ques
c_cond
l_string|&quot;IBM&quot;
suffix:colon
l_string|&quot;Motorola&quot;
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bus speed&bslash;t: %dMhz&bslash;n&quot;
comma
id|zx4500_get_bus_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|zx4500_calibrate_decr
id|zx4500_calibrate_decr
c_func
(paren
r_void
)paren
(brace
id|ulong
id|freq
suffix:semicolon
id|freq
op_assign
id|zx4500_get_bus_speed
c_func
(paren
)paren
op_div
l_int|4
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;time_init: decrementer frequency = %lu.%.6lu MHz&bslash;n&quot;
comma
id|freq
op_div
l_int|1000000
comma
id|freq
op_mod
l_int|1000000
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
comma
l_int|1000000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space 1-1.&n; */
r_static
id|__inline__
r_void
DECL|function|zx4500_set_bat
id|zx4500_set_bat
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
l_string|&quot; lis %0,0xf800&bslash;n &bslash;&n;&t;&t;  ori %1,%0,0x002a&bslash;n &bslash;&n;&t;&t;  ori %0,%0,0x0ffe&bslash;n &bslash;&n;&t;&t;  mtspr 0x21e,%0&bslash;n &bslash;&n;&t;&t;  mtspr 0x21f,%1&bslash;n &bslash;&n;&t;&t;  isync&bslash;n &bslash;&n;&t;&t;  sync &quot;
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
macro_line|#ifdef&t;CONFIG_SERIAL_TEXT_DEBUG
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
DECL|function|zx4500_progress
id|zx4500_progress
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
r_int
id|com_port
suffix:semicolon
id|u16
id|shift
suffix:semicolon
id|com_port
op_assign
id|rs_table
(braket
l_int|0
)braket
dot
id|port
suffix:semicolon
id|shift
op_assign
id|rs_table
(braket
l_int|0
)braket
dot
id|iomem_reg_shift
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
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
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
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
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
multiline_comment|/* Map in board registers, etc. */
id|zx4500_set_bat
c_func
(paren
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
id|zx4500_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|zx4500_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_cannonicalize
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|zx4500_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.restart
op_assign
id|zx4500_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|zx4500_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|zx4500_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|zx4500_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|zx4500_map_io
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|zx4500_calibrate_decr
suffix:semicolon
id|ppc_md.heartbeat
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.heartbeat_reset
op_assign
l_int|0
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef&t;CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|zx4500_progress
suffix:semicolon
macro_line|#else&t;/* !CONFIG_SERIAL_TEXT_DEBUG */
id|ppc_md.progress
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
r_return
suffix:semicolon
)brace
eof
