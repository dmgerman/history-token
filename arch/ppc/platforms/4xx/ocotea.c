multiline_comment|/*&n; * arch/ppc/platforms/ocotea.c&n; *&n; * Ocotea board specific routines&n; *&n; * Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2003 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ppc4xx_pic.h&gt;
r_extern
r_void
m_abort
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Global Variables */
DECL|variable|__res
id|bd_t
id|__res
suffix:semicolon
r_static
r_void
id|__init
DECL|function|ocotea_calibrate_decr
id|ocotea_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
id|freq
op_assign
id|OCOTEA_SYSCLK
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
multiline_comment|/* Set the time base to zero */
id|mtspr
c_func
(paren
id|SPRN_TBWL
comma
l_int|0
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_TBWU
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear any pending timer interrupts */
id|mtspr
c_func
(paren
id|SPRN_TSR
comma
id|TSR_ENW
op_or
id|TSR_WIS
op_or
id|TSR_DIS
op_or
id|TSR_FIS
)paren
suffix:semicolon
multiline_comment|/* Enable decrementer interrupt */
id|mtspr
c_func
(paren
id|SPRN_TCR
comma
id|TCR_DIE
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ocotea_show_cpuinfo
id|ocotea_show_cpuinfo
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
l_string|&quot;vendor&bslash;t&bslash;t: IBM&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: PPC440GX EVB (Ocotea)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ocotea_map_irq
id|ocotea_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; * &t;   A   B   C   D&n;&t; */
(brace
(brace
l_int|23
comma
l_int|23
comma
l_int|23
comma
l_int|23
)brace
comma
multiline_comment|/* IDSEL 1 - PCI Slot 0 */
(brace
l_int|24
comma
l_int|24
comma
l_int|24
comma
l_int|24
)brace
comma
multiline_comment|/* IDSEL 2 - PCI Slot 1 */
(brace
l_int|25
comma
l_int|25
comma
l_int|25
comma
l_int|25
)brace
comma
multiline_comment|/* IDSEL 3 - PCI Slot 2 */
(brace
l_int|26
comma
l_int|26
comma
l_int|26
comma
l_int|26
)brace
comma
multiline_comment|/* IDSEL 4 - PCI Slot 3 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|1
comma
id|max_idsel
op_assign
l_int|4
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
DECL|macro|PCIX_READW
mdefine_line|#define PCIX_READW(offset) &bslash;&n;&t;(readw((u32)pcix_reg_base+offset))
DECL|macro|PCIX_WRITEW
mdefine_line|#define PCIX_WRITEW(value, offset) &bslash;&n;&t;(writew(value, (u32)pcix_reg_base+offset))
DECL|macro|PCIX_WRITEL
mdefine_line|#define PCIX_WRITEL(value, offset) &bslash;&n;&t;(writel(value, (u32)pcix_reg_base+offset))
multiline_comment|/*&n; * FIXME: This is only here to &quot;make it work&quot;.  This will move&n; * to a ibm_pcix.c which will contain a generic IBM PCIX bridge&n; * configuration library. -Matt&n; */
r_static
r_void
id|__init
DECL|function|ocotea_setup_pcix
id|ocotea_setup_pcix
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|pcix_reg_base
suffix:semicolon
id|pcix_reg_base
op_assign
id|ioremap64
c_func
(paren
id|PCIX0_REG_BASE
comma
id|PCIX0_REG_SIZE
)paren
suffix:semicolon
multiline_comment|/* Enable PCIX0 I/O, Mem, and Busmaster cycles */
id|PCIX_WRITEW
c_func
(paren
id|PCIX_READW
c_func
(paren
id|PCIX0_COMMAND
)paren
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
comma
id|PCIX0_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Disable all windows */
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_POM0SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_POM1SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_POM2SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM0SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM0SAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM1SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM2SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM2SAH
)paren
suffix:semicolon
multiline_comment|/* Setup 2GB PLB-&gt;PCI outbound mem window (3_8000_0000-&gt;0_8000_0000) */
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000003
comma
id|PCIX0_POM0LAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x80000000
comma
id|PCIX0_POM0LAL
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000000
comma
id|PCIX0_POM0PCIAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x80000000
comma
id|PCIX0_POM0PCIAL
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x80000001
comma
id|PCIX0_POM0SA
)paren
suffix:semicolon
multiline_comment|/* Setup 2GB PCI-&gt;PLB inbound memory window at 0, enable MSIs */
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000000
comma
id|PCIX0_PIM0LAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000000
comma
id|PCIX0_PIM0LAL
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0xe0000007
comma
id|PCIX0_PIM0SA
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ocotea_setup_hose
id|ocotea_setup_hose
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
multiline_comment|/* Configure windows on the PCI-X host bridge */
id|ocotea_setup_pcix
c_func
(paren
)paren
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
suffix:semicolon
id|hose-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|hose-&gt;pci_mem_offset
op_assign
id|OCOTEA_PCI_MEM_OFFSET
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
id|OCOTEA_PCI_LOWER_IO
comma
id|OCOTEA_PCI_UPPER_IO
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
comma
id|OCOTEA_PCI_LOWER_MEM
comma
id|OCOTEA_PCI_UPPER_MEM
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|hose-&gt;io_space.start
op_assign
id|OCOTEA_PCI_LOWER_IO
suffix:semicolon
id|hose-&gt;io_space.end
op_assign
id|OCOTEA_PCI_UPPER_IO
suffix:semicolon
id|hose-&gt;mem_space.start
op_assign
id|OCOTEA_PCI_LOWER_MEM
suffix:semicolon
id|hose-&gt;mem_space.end
op_assign
id|OCOTEA_PCI_UPPER_MEM
suffix:semicolon
id|isa_io_base
op_assign
(paren
r_int
r_int
)paren
id|ioremap64
c_func
(paren
id|OCOTEA_PCI_IO_BASE
comma
id|OCOTEA_PCI_IO_SIZE
)paren
suffix:semicolon
id|hose-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|isa_io_base
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|OCOTEA_PCI_CFGA_PLB32
comma
id|OCOTEA_PCI_CFGD_PLB32
)paren
suffix:semicolon
id|hose-&gt;set_cfg_type
op_assign
l_int|1
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
)paren
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|ocotea_map_irq
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
DECL|function|ocotea_early_serial_map
id|ocotea_early_serial_map
c_func
(paren
r_void
)paren
(brace
r_struct
id|uart_port
id|port
suffix:semicolon
multiline_comment|/* Setup ioremapped serial port access */
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.membase
op_assign
id|ioremap64
c_func
(paren
id|PPC440GX_UART0_ADDR
comma
l_int|8
)paren
suffix:semicolon
id|port.irq
op_assign
l_int|0
suffix:semicolon
id|port.uartclk
op_assign
id|BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|port.regshift
op_assign
l_int|0
suffix:semicolon
id|port.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|port.flags
op_assign
id|ASYNC_BOOT_AUTOCONF
op_or
id|ASYNC_SKIP_TEST
suffix:semicolon
id|port.line
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 0 failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|port.membase
op_assign
id|ioremap64
c_func
(paren
id|PPC440GX_UART1_ADDR
comma
l_int|8
)paren
suffix:semicolon
id|port.irq
op_assign
l_int|1
suffix:semicolon
id|port.line
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 1 failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|ocotea_setup_arch
id|ocotea_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_char
op_star
id|addr
suffix:semicolon
r_int
r_int
r_int
id|mac64
suffix:semicolon
multiline_comment|/* Retrieve MAC addresses from flash */
id|addr
op_assign
id|ioremap64
c_func
(paren
id|OCOTEA_MAC_BASE
comma
id|OCOTEA_MAC_SIZE
)paren
suffix:semicolon
id|mac64
op_assign
id|simple_strtoull
c_func
(paren
id|addr
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|__res.bi_enetaddr
(braket
l_int|0
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|mac64
op_plus
l_int|2
comma
l_int|6
)paren
suffix:semicolon
id|mac64
op_assign
id|simple_strtoull
c_func
(paren
id|addr
op_plus
id|OCOTEA_MAC1_OFFSET
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|__res.bi_enetaddr
(braket
l_int|1
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|mac64
op_plus
l_int|2
comma
l_int|6
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_BDI_SWITCH)
multiline_comment|/*&n;&t; * The Abatron BDI JTAG debugger does not tolerate others&n;&t; * mucking with the debug registers.&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_DBCR0
comma
(paren
id|DBCR0_TDE
op_or
id|DBCR0_IDM
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Setup TODC access */
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_DS1743
comma
l_int|0
comma
l_int|0
comma
id|ioremap64
c_func
(paren
id|OCOTEA_RTC_ADDR
comma
id|OCOTEA_RTC_SIZE
)paren
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* Setup PCI host bridge */
id|ocotea_setup_hose
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
id|Root_HDA1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|ocotea_early_serial_map
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
l_string|&quot;IBM Ocotea port (MontaVista Software, Inc. &lt;source@mvista.com&gt;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ocotea_restart
id|ocotea_restart
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
m_abort
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ocotea_power_off
id|ocotea_power_off
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
)brace
r_static
r_void
DECL|function|ocotea_halt
id|ocotea_halt
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
)brace
multiline_comment|/*&n; * Read the 440GX memory controller to get size of system memory.&n; */
r_static
r_int
r_int
id|__init
DECL|function|ocotea_find_end_of_memory
id|ocotea_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|u32
id|i
comma
id|bank_config
suffix:semicolon
id|u32
id|mem_size
op_assign
l_int|0
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|mtdcr
c_func
(paren
id|DCRN_SDRAM0_CFGADDR
comma
id|SDRAM0_B0CR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|mtdcr
c_func
(paren
id|DCRN_SDRAM0_CFGADDR
comma
id|SDRAM0_B1CR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|mtdcr
c_func
(paren
id|DCRN_SDRAM0_CFGADDR
comma
id|SDRAM0_B2CR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|mtdcr
c_func
(paren
id|DCRN_SDRAM0_CFGADDR
comma
id|SDRAM0_B3CR
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|bank_config
op_assign
id|mfdcr
c_func
(paren
id|DCRN_SDRAM0_CFGDATA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bank_config
op_amp
id|SDRAM_CONFIG_BANK_ENABLE
)paren
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|SDRAM_CONFIG_BANK_SIZE
c_func
(paren
id|bank_config
)paren
)paren
(brace
r_case
id|SDRAM_CONFIG_SIZE_8M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_8M
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SDRAM_CONFIG_SIZE_16M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_16M
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SDRAM_CONFIG_SIZE_32M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_32M
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SDRAM_CONFIG_SIZE_64M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_64M
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SDRAM_CONFIG_SIZE_128M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_128M
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SDRAM_CONFIG_SIZE_256M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_256M
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SDRAM_CONFIG_SIZE_512M
suffix:colon
id|mem_size
op_add_assign
id|PPC44x_MEM_SIZE_512M
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|mem_size
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ocotea_init_irq
id|ocotea_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Enable PPC440GP interrupt compatibility mode */
id|SDR_WRITE
c_func
(paren
id|DCRN_SDR_MFR
comma
id|SDR_READ
c_func
(paren
id|DCRN_SDR_MFR
)paren
op_or
id|DCRN_SDR_MFR_PCM
)paren
suffix:semicolon
id|ppc4xx_pic_init
c_func
(paren
)paren
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
id|NR_IRQS
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
id|ppc4xx_pic
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|variable|rs_table
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
r_static
r_void
DECL|function|ocotea_progress
id|ocotea_progress
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
(paren
r_int
r_int
)paren
id|rs_table
(braket
l_int|0
)braket
dot
id|iomem_base
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
)brace
multiline_comment|/* Send LF/CR to pretty up output */
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
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SERIAL_TEXT_DEBUG */
macro_line|#if 0
r_static
r_void
id|__init
id|ocotea_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0xe0000000
comma
l_int|0x0000000140000000
comma
l_int|0x00001000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|platform_init
r_void
id|__init
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
(paren
r_struct
id|bi_record
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|ocotea_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|ocotea_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|ocotea_init_irq
suffix:semicolon
id|ppc_md.get_irq
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Set in ppc4xx_pic_init() */
id|ppc_md.find_end_of_memory
op_assign
id|ocotea_find_end_of_memory
suffix:semicolon
id|ppc_md.restart
op_assign
id|ocotea_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|ocotea_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|ocotea_halt
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|ocotea_calibrate_decr
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
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|ocotea_progress
suffix:semicolon
macro_line|#endif /* CONFIG_SERIAL_TEXT_DEBUG */
macro_line|#ifdef CONFIG_KGDB
id|ppc_md.early_serial_map
op_assign
id|ocotea_early_serial_map
suffix:semicolon
macro_line|#endif
)brace
eof
