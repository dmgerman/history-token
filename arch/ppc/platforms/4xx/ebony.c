multiline_comment|/*&n; * arch/ppc/platforms/4xx/ebony.c&n; *&n; * Ebony board specific routines&n; *&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; * Copyright 2002-2004 MontaVista Software Inc.&n; *&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; * Copyright (c) 2003, 2004 Zultys Technologies&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ppc4xx_pic.h&gt;
macro_line|#include &lt;syslib/gen550.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|ibm44x_clocks
id|clocks
id|__initdata
suffix:semicolon
multiline_comment|/*&n; * Ebony external IRQ triggering/polarity settings&n; */
DECL|variable|__initdata
r_int
r_char
id|ppc4xx_uic_ext_irq_cfg
(braket
)braket
id|__initdata
op_assign
(brace
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ0: PCI slot 0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ1: PCI slot 1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ2: PCI slot 2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ3: PCI slot 3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ4: IRDA */
(paren
id|IRQ_SENSE_EDGE
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ5: SMI pushbutton */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ6: PHYs */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ7: AUX */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ8: EXT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ9: EXT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ10: EXT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* IRQ11: EXT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* IRQ12: EXT */
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|ebony_calibrate_decr
id|ebony_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/*&n;&t; * Determine system clock speed&n;&t; *&n;&t; * If we are on Rev. B silicon, then use&n;&t; * default external system clock.  If we are&n;&t; * on Rev. C silicon then errata forces us to&n;&t; * use the internal clock.&n;&t; */
r_switch
c_cond
(paren
id|PVR_REV
c_func
(paren
id|mfspr
c_func
(paren
id|PVR
)paren
)paren
)paren
(brace
r_case
id|PVR_REV
c_func
(paren
id|PVR_440GP_RB
)paren
suffix:colon
id|freq
op_assign
id|EBONY_440GP_RB_SYSCLK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PVR_REV
c_func
(paren
id|PVR_440GP_RC1
)paren
suffix:colon
r_default
suffix:colon
id|freq
op_assign
id|EBONY_440GP_RC_SYSCLK
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ibm44x_calibrate_decr
c_func
(paren
id|freq
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ebony_show_cpuinfo
id|ebony_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: Ebony&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ebony_map_irq
id|ebony_map_irq
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
DECL|macro|PCIX_WRITEL
mdefine_line|#define PCIX_WRITEL(value, offset) &bslash;&n;&t;(writel(value, (u32)pcix_reg_base+offset))
multiline_comment|/*&n; * FIXME: This is only here to &quot;make it work&quot;.  This will move&n; * to a ibm_pcix.c which will contain a generic IBM PCIX bridge&n; * configuration library. -Matt&n; */
r_static
r_void
id|__init
DECL|function|ebony_setup_pcix
id|ebony_setup_pcix
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
l_int|0x80000007
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
DECL|function|ebony_setup_hose
id|ebony_setup_hose
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
id|ebony_setup_pcix
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
id|EBONY_PCI_MEM_OFFSET
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
id|EBONY_PCI_LOWER_IO
comma
id|EBONY_PCI_UPPER_IO
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
id|EBONY_PCI_LOWER_MEM
comma
id|EBONY_PCI_UPPER_MEM
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|hose-&gt;io_space.start
op_assign
id|EBONY_PCI_LOWER_IO
suffix:semicolon
id|hose-&gt;io_space.end
op_assign
id|EBONY_PCI_UPPER_IO
suffix:semicolon
id|hose-&gt;mem_space.start
op_assign
id|EBONY_PCI_LOWER_MEM
suffix:semicolon
id|hose-&gt;mem_space.end
op_assign
id|EBONY_PCI_UPPER_MEM
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
id|EBONY_PCI_IO_BASE
comma
id|EBONY_PCI_IO_SIZE
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
id|EBONY_PCI_CFGA_PLB32
comma
id|EBONY_PCI_CFGD_PLB32
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
id|ebony_map_irq
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
DECL|function|ebony_early_serial_map
id|ebony_early_serial_map
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
id|PPC440GP_UART0_ADDR
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
id|clocks.uart0
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
macro_line|#if defined(CONFIG_SERIAL_TEXT_DEBUG) || defined(CONFIG_KGDB)
multiline_comment|/* Configure debug serial access */
id|gen550_init
c_func
(paren
l_int|0
comma
op_amp
id|port
)paren
suffix:semicolon
macro_line|#endif
id|port.membase
op_assign
id|ioremap64
c_func
(paren
id|PPC440GP_UART1_ADDR
comma
l_int|8
)paren
suffix:semicolon
id|port.irq
op_assign
l_int|1
suffix:semicolon
id|port.uartclk
op_assign
id|clocks.uart1
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
macro_line|#if defined(CONFIG_SERIAL_TEXT_DEBUG) || defined(CONFIG_KGDB)
multiline_comment|/* Configure debug serial access */
id|gen550_init
c_func
(paren
l_int|1
comma
op_amp
id|port
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
id|__init
DECL|function|ebony_setup_arch
id|ebony_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_char
op_star
id|vpd_base
suffix:semicolon
r_struct
id|ocp_def
op_star
id|def
suffix:semicolon
r_struct
id|ocp_func_emac_data
op_star
id|emacdata
suffix:semicolon
multiline_comment|/* Set mac_addr for each EMAC */
id|vpd_base
op_assign
id|ioremap64
c_func
(paren
id|EBONY_VPD_BASE
comma
id|EBONY_VPD_SIZE
)paren
suffix:semicolon
id|def
op_assign
id|ocp_get_one_device
c_func
(paren
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_EMAC
comma
l_int|0
)paren
suffix:semicolon
id|emacdata
op_assign
id|def-&gt;additions
suffix:semicolon
id|memcpy
c_func
(paren
id|emacdata-&gt;mac_addr
comma
id|EBONY_NA0_ADDR
c_func
(paren
id|vpd_base
)paren
comma
l_int|6
)paren
suffix:semicolon
id|def
op_assign
id|ocp_get_one_device
c_func
(paren
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_EMAC
comma
l_int|1
)paren
suffix:semicolon
id|emacdata
op_assign
id|def-&gt;additions
suffix:semicolon
id|memcpy
c_func
(paren
id|emacdata-&gt;mac_addr
comma
id|EBONY_NA1_ADDR
c_func
(paren
id|vpd_base
)paren
comma
l_int|6
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|vpd_base
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Determine various clocks.&n;&t; * To be completely correct we should get SysClk&n;&t; * from FPGA, because it can be changed by on-board switches&n;&t; * --ebs&n;&t; */
id|ibm440gp_get_clocks
c_func
(paren
op_amp
id|clocks
comma
l_int|33333333
comma
l_int|6
op_star
l_int|1843200
)paren
suffix:semicolon
id|ocp_sys_info.opb_bus_freq
op_assign
id|clocks.opb
suffix:semicolon
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
id|EBONY_RTC_ADDR
comma
id|EBONY_RTC_SIZE
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
id|ebony_setup_hose
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
id|ebony_early_serial_map
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
l_string|&quot;IBM Ebony port (MontaVista Software, Inc. (source@mvista.com))&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
id|ibm44x_platform_init
c_func
(paren
)paren
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|ebony_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|ebony_show_cpuinfo
suffix:semicolon
id|ppc_md.get_irq
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Set in ppc4xx_pic_init() */
id|ppc_md.calibrate_decr
op_assign
id|ebony_calibrate_decr
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
macro_line|#ifdef CONFIG_KGDB
id|ppc_md.early_serial_map
op_assign
id|ebony_early_serial_map
suffix:semicolon
macro_line|#endif
)brace
eof
