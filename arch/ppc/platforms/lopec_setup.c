multiline_comment|/*&n; * arch/ppc/platforms/lopec_setup.c&n; * &n; * Setup routines for the Motorola LoPEC.&n; *&n; * Author: Dan Cox&n; *         danc@mvista.com&n; *&n; * Copyright 2001-2002 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
r_extern
r_void
id|lopec_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Define all of the IRQ senses and polarities.  Taken from the&n; * LoPEC Programmer&squot;s Reference Guide.&n; */
DECL|variable|__initdata
r_static
id|u_char
id|lopec_openpic_initsenses
(braket
l_int|16
)braket
id|__initdata
op_assign
(brace
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ 0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ 2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ 4 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ 5 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 6 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 7 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 8 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 9 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 10 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 11 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 12 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ 13 */
(paren
id|IRQ_SENSE_EDGE
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ 14 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
multiline_comment|/* IRQ 15 */
)brace
suffix:semicolon
r_static
r_int
DECL|function|lopec_show_cpuinfo
id|lopec_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: Motorola LoPEC&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|u32
DECL|function|lopec_irq_cannonicalize
id|lopec_irq_cannonicalize
c_func
(paren
id|u32
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
r_return
l_int|9
suffix:semicolon
r_else
r_return
id|irq
suffix:semicolon
)brace
r_static
r_void
DECL|function|lopec_restart
id|lopec_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
DECL|macro|LOPEC_SYSSTAT1
mdefine_line|#define LOPEC_SYSSTAT1 0xffe00000
multiline_comment|/* force a hard reset, if possible */
r_int
r_char
id|reg
op_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|LOPEC_SYSSTAT1
)paren
suffix:semicolon
id|reg
op_or_assign
l_int|0x80
suffix:semicolon
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|LOPEC_SYSSTAT1
)paren
op_assign
id|reg
suffix:semicolon
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
(brace
suffix:semicolon
)brace
DECL|macro|LOPEC_SYSSTAT1
macro_line|#undef LOPEC_SYSSTAT1
)brace
r_static
r_void
DECL|function|lopec_halt
id|lopec_halt
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
(brace
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|lopec_power_off
id|lopec_power_off
c_func
(paren
r_void
)paren
(brace
id|lopec_halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
DECL|variable|lopec_ide_ports_known
r_int
id|lopec_ide_ports_known
op_assign
l_int|0
suffix:semicolon
DECL|variable|lopec_ide_regbase
r_static
id|ide_ioreg_t
id|lopec_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|lopec_ide_ctl_regbase
r_static
id|ide_ioreg_t
id|lopec_ide_ctl_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|lopec_idedma_regbase
r_static
id|ide_ioreg_t
id|lopec_idedma_regbase
suffix:semicolon
r_static
r_void
DECL|function|lopec_ide_probe
id|lopec_ide_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
comma
l_int|NULL
)paren
suffix:semicolon
id|lopec_ide_ports_known
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|lopec_ide_regbase
(braket
l_int|0
)braket
op_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|lopec_ide_regbase
(braket
l_int|1
)braket
op_assign
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
suffix:semicolon
id|lopec_ide_ctl_regbase
(braket
l_int|0
)braket
op_assign
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|lopec_ide_ctl_regbase
(braket
l_int|1
)braket
op_assign
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|start
suffix:semicolon
id|lopec_idedma_regbase
op_assign
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|start
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|lopec_ide_default_irq
id|lopec_ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_if
c_cond
(paren
id|lopec_ide_ports_known
op_eq
l_int|0
)paren
id|lopec_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
id|lopec_ide_regbase
(braket
l_int|0
)braket
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
id|lopec_ide_regbase
(braket
l_int|1
)braket
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
DECL|function|lopec_ide_default_io_base
id|lopec_ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|lopec_ide_ports_known
op_eq
l_int|0
)paren
id|lopec_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|lopec_ide_regbase
(braket
id|index
)braket
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|lopec_ide_init_hwif_ports
id|lopec_ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data
comma
id|ide_ioreg_t
id|ctl
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
id|data
suffix:semicolon
id|uint
id|alt_status_base
suffix:semicolon
r_int
id|i
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
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
op_eq
id|lopec_ide_regbase
(braket
l_int|0
)braket
)paren
(brace
id|alt_status_base
op_assign
id|lopec_ide_ctl_regbase
(braket
l_int|0
)braket
op_plus
l_int|2
suffix:semicolon
id|hw-&gt;irq
op_assign
l_int|14
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data
op_eq
id|lopec_ide_regbase
(braket
l_int|1
)braket
)paren
(brace
id|alt_status_base
op_assign
id|lopec_ide_ctl_regbase
(braket
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
id|hw-&gt;irq
op_assign
l_int|15
suffix:semicolon
)brace
r_else
(brace
id|alt_status_base
op_assign
l_int|0
suffix:semicolon
id|hw-&gt;irq
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctl
)paren
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctl
suffix:semicolon
r_else
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|alt_status_base
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
id|hw-&gt;irq
suffix:semicolon
)brace
macro_line|#endif /* BLK_DEV_IDE */
r_static
r_void
id|__init
DECL|function|lopec_init_IRQ
id|lopec_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Provide the open_pic code with the correct table of interrupts.&n;&t; */
id|OpenPIC_InitSenses
op_assign
id|lopec_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|lopec_openpic_initsenses
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need to tell openpic_set_sources where things actually are.&n;&t; * mpc10x_common will setup OpenPIC_Addr at ioremap(EUMB phys base +&n;&t; * EPIC offset (0x40000));  The EPIC IRQ Register Address Map -&n;&t; * Interrupt Source Configuration Registers gives these numbers&n;&t; * as offsets starting at 0x50200, we need to adjust occordinly.&n;&t; */
multiline_comment|/* Map serial interrupts 0-15 */
id|openpic_set_sources
c_func
(paren
l_int|0
comma
l_int|16
comma
id|OpenPIC_Addr
op_plus
l_int|0x10200
)paren
suffix:semicolon
multiline_comment|/* Skip reserved space and map i2c and DMA Ch[01] */
id|openpic_set_sources
c_func
(paren
l_int|16
comma
l_int|3
comma
id|OpenPIC_Addr
op_plus
l_int|0x11020
)paren
suffix:semicolon
multiline_comment|/* Skip reserved space and map Message Unit Interrupt (I2O) */
id|openpic_set_sources
c_func
(paren
l_int|19
comma
l_int|1
comma
id|OpenPIC_Addr
op_plus
l_int|0x110C0
)paren
suffix:semicolon
id|openpic_init
c_func
(paren
l_int|1
comma
id|NUM_8259_INTERRUPTS
comma
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Map i8259 interrupts */
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
(brace
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
)brace
multiline_comment|/*&n;&t; * The EPIC allows for a read in the range of 0xFEF00000 -&gt;&n;&t; * 0xFEFFFFFF to generate a PCI interrupt-acknowledge transaction.&n;&t; */
id|i8259_init
c_func
(paren
l_int|0xfef00000
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|lopec_request_io
id|lopec_request_io
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x4d0
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc0
comma
l_int|0x4d1
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lopec_request_io
id|device_initcall
c_func
(paren
id|lopec_request_io
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|lopec_map_io
id|lopec_map_io
c_func
(paren
r_void
)paren
(brace
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
id|io_block_mapping
c_func
(paren
l_int|0xb0000000
comma
l_int|0xb0000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|lopec_set_bat
id|lopec_set_bat
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|batu
comma
id|batl
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lis %0,0xf800&bslash;n &bslash;&n;                 ori %1,%0,0x002a&bslash;n &bslash;&n;                 ori %0,%0,0x0ffe&bslash;n &bslash;&n;                 mtspr 0x21e,%0&bslash;n &bslash;&n;                 mtspr 0x21f,%1&bslash;n &bslash;&n;                 isync&bslash;n &bslash;&n;                 sync &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|batu
)paren
comma
l_string|&quot;=r&quot;
(paren
id|batl
)paren
)paren
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
DECL|variable|com_port
r_volatile
r_int
r_char
op_star
id|com_port
suffix:semicolon
DECL|variable|com_port_lsr
r_volatile
r_int
r_char
op_star
id|com_port_lsr
suffix:semicolon
r_static
r_void
DECL|function|serial_writechar
id|serial_writechar
c_func
(paren
r_char
id|c
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
)brace
r_void
DECL|function|lopec_progress
id|lopec_progress
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
id|serial_writechar
c_func
(paren
id|c
)paren
suffix:semicolon
multiline_comment|/* Most messages don&squot;t have a newline in them */
id|serial_writechar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|serial_writechar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
r_static
r_int
r_int
id|__init
DECL|function|lopec_find_end_of_memory
id|lopec_find_end_of_memory
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
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|lopec_setup_arch
id|lopec_setup_arch
c_func
(paren
r_void
)paren
(brace
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T37
comma
l_int|0
comma
l_int|0
comma
id|ioremap
c_func
(paren
l_int|0xffe80000
comma
l_int|0x8000
)paren
comma
l_int|8
)paren
suffix:semicolon
id|loops_per_jiffy
op_assign
l_int|100000000
op_div
id|HZ
suffix:semicolon
id|lopec_find_bridges
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
id|MKDEV
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
r_else
macro_line|#elif defined(CONFIG_ROOT_NFS)
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x00ff
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0301
)paren
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0801
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
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
id|lopec_set_bat
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
id|ISA_DMA_THRESHOLD
op_assign
l_int|0x00ffffff
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|0x44
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|0x48
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|lopec_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|lopec_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_cannonicalize
op_assign
id|lopec_irq_cannonicalize
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|lopec_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|lopec_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|lopec_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|lopec_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|lopec_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|lopec_map_io
suffix:semicolon
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|todc_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_ID_MODULE)
id|ppc_ide_md.default_irq
op_assign
id|lopec_ide_default_irq
suffix:semicolon
id|ppc_ide_md.default_io_base
op_assign
id|lopec_ide_default_io_base
suffix:semicolon
id|ppc_ide_md.ide_init_hwif
op_assign
id|lopec_ide_init_hwif_ports
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|lopec_progress
suffix:semicolon
macro_line|#endif
)brace
eof
