multiline_comment|/*&n; * arch/ppc/platforms/83xx/mpc834x_sys.c&n; *&n; * MPC834x SYS board specific routines&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;&t;/* for linux/serial_core.h */
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fsl_devices.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ipic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/mpc83xx.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;asm/ppc_sys.h&gt;
macro_line|#include &lt;mm/mmu_decl.h&gt;
macro_line|#include &lt;syslib/ppc83xx_setup.h&gt;
macro_line|#ifndef CONFIG_PCI
DECL|variable|isa_io_base
r_int
r_int
id|isa_io_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|isa_mem_base
r_int
r_int
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|total_memory
suffix:semicolon
multiline_comment|/* in mm/init */
DECL|variable|__res
r_int
r_char
id|__res
(braket
r_sizeof
(paren
id|bd_t
)paren
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
macro_line|#error &quot;PCI is not supported&quot;
multiline_comment|/* NEED mpc83xx_map_irq &amp; mpc83xx_exclude_device&n;   see platforms/85xx/mpc85xx_ads_common.c */
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* ************************************************************************&n; *&n; * Setup the architecture&n; *&n; */
r_static
r_void
id|__init
DECL|function|mpc834x_sys_setup_arch
id|mpc834x_sys_setup_arch
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_int
r_int
id|freq
suffix:semicolon
r_struct
id|gianfar_platform_data
op_star
id|pdata
suffix:semicolon
multiline_comment|/* get the core frequency */
id|freq
op_assign
id|binfo-&gt;bi_intfreq
suffix:semicolon
multiline_comment|/* Set loops_per_jiffy to a half-way reasonable value,&n;&t;   for use until calibrate_delay gets called. */
id|loops_per_jiffy
op_assign
id|freq
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* setup PCI host bridges */
id|mpc83xx_sys_setup_hose
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|mpc83xx_early_serial_map
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup the board related information for the enet controllers */
id|pdata
op_assign
(paren
r_struct
id|gianfar_platform_data
op_star
)paren
id|ppc_sys_get_pdata
c_func
(paren
id|MPC83xx_TSEC1
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC83xx_IRQ_EXT1
suffix:semicolon
id|pdata-&gt;phyid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fixup phy address */
id|pdata-&gt;phy_reg_addr
op_add_assign
id|binfo-&gt;bi_immr_base
suffix:semicolon
id|memcpy
c_func
(paren
id|pdata-&gt;mac_addr
comma
id|binfo-&gt;bi_enetaddr
comma
l_int|6
)paren
suffix:semicolon
id|pdata
op_assign
(paren
r_struct
id|gianfar_platform_data
op_star
)paren
id|ppc_sys_get_pdata
c_func
(paren
id|MPC83xx_TSEC2
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC83xx_IRQ_EXT2
suffix:semicolon
id|pdata-&gt;phyid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fixup phy address */
id|pdata-&gt;phy_reg_addr
op_add_assign
id|binfo-&gt;bi_immr_base
suffix:semicolon
id|memcpy
c_func
(paren
id|pdata-&gt;mac_addr
comma
id|binfo-&gt;bi_enet1addr
comma
l_int|6
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
macro_line|#ifdef  CONFIG_ROOT_NFS
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
)brace
r_static
r_void
id|__init
DECL|function|mpc834x_sys_map_io
id|mpc834x_sys_map_io
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we steal the lowest ioremap addr for virt space */
id|io_block_mapping
c_func
(paren
id|VIRT_IMMRBAR
comma
id|immrbar
comma
l_int|1024
op_star
l_int|1024
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|BCSR_VIRT_ADDR
comma
id|BCSR_PHYS_ADDR
comma
id|BCSR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_int
DECL|function|mpc834x_sys_show_cpuinfo
id|mpc834x_sys_show_cpuinfo
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
comma
id|svid
comma
id|phid1
suffix:semicolon
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* get the core frequency */
id|freq
op_assign
id|binfo-&gt;bi_intfreq
suffix:semicolon
id|pvid
op_assign
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
suffix:semicolon
id|svid
op_assign
id|mfspr
c_func
(paren
id|SPRN_SVR
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;chip&bslash;t&bslash;t: MPC%s&bslash;n&quot;
comma
id|cur_ppc_sys_spec-&gt;ppc_sys_name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Vendor&bslash;t&bslash;t: Freescale Inc.&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: mpc%s sys&bslash;n&quot;
comma
id|cur_ppc_sys_spec-&gt;ppc_sys_name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;core clock&bslash;t: %d MHz&bslash;n&quot;
l_string|&quot;bus  clock&bslash;t: %d MHz&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|binfo-&gt;bi_intfreq
op_div
l_int|1000000
)paren
comma
(paren
r_int
)paren
(paren
id|binfo-&gt;bi_busfreq
op_div
l_int|1000000
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PVR&bslash;t&bslash;t: 0x%x&bslash;n&quot;
comma
id|pvid
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;SVR&bslash;t&bslash;t: 0x%x&bslash;n&quot;
comma
id|svid
)paren
suffix:semicolon
multiline_comment|/* Display cpu Pll setting */
id|phid1
op_assign
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PLL setting&bslash;t: 0x%x&bslash;n&quot;
comma
(paren
(paren
id|phid1
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
multiline_comment|/* Display the amount of memory */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Memory&bslash;t&bslash;t: %d MB&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|binfo-&gt;bi_memsize
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|mpc834x_sys_init_IRQ
id|mpc834x_sys_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
id|u8
id|senses
(braket
l_int|8
)braket
op_assign
(brace
l_int|0
comma
multiline_comment|/* EXT 0 */
id|IRQ_SENSE_LEVEL
comma
multiline_comment|/* EXT 1 */
id|IRQ_SENSE_LEVEL
comma
multiline_comment|/* EXT 2 */
l_int|0
comma
multiline_comment|/* EXT 3 */
l_int|0
comma
multiline_comment|/* EXT 4 */
l_int|0
comma
multiline_comment|/* EXT 5 */
l_int|0
comma
multiline_comment|/* EXT 6 */
l_int|0
comma
multiline_comment|/* EXT 7 */
)brace
suffix:semicolon
id|ipic_init
c_func
(paren
id|binfo-&gt;bi_immr_base
op_plus
l_int|0x00700
comma
l_int|0
comma
id|MPC83xx_IPIC_IRQ_OFFSET
comma
id|senses
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Initialize the default interrupt mapping priorities,&n;&t; * in case the boot rom changed something on us.&n;&t; */
id|ipic_set_default_priority
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|mpc834x_sys_set_bat
id|mpc834x_sys_set_bat
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we steal the lowest ioremap addr for virt space */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT1U
comma
id|VIRT_IMMRBAR
op_or
l_int|0x1e
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT1L
comma
id|immrbar
op_or
l_int|0x2a
)paren
suffix:semicolon
id|mb
c_func
(paren
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
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
multiline_comment|/* parse_bootinfo must always be called first */
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we were passed in a board information, copy it into the&n;&t; * residual data area.&n;&t; */
r_if
c_cond
(paren
id|r3
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|__res
comma
(paren
r_void
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
comma
r_sizeof
(paren
id|bd_t
)paren
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_BLK_DEV_INITRD)
multiline_comment|/*&n;&t; * If the init RAM disk has been configured in, and there&squot;s a valid&n;&t; * starting address for it, set it up.&n;&t; */
r_if
c_cond
(paren
id|r4
)paren
(brace
id|initrd_start
op_assign
id|r4
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r5
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
multiline_comment|/* Copy the kernel command line arguments to a safe place. */
r_if
c_cond
(paren
id|r6
)paren
(brace
op_star
(paren
r_char
op_star
)paren
(paren
id|r7
op_plus
id|KERNELBASE
)paren
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|cmd_line
comma
(paren
r_char
op_star
)paren
(paren
id|r6
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
)brace
id|immrbar
op_assign
id|binfo-&gt;bi_immr_base
suffix:semicolon
id|mpc834x_sys_set_bat
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_8250) &amp;&amp; defined(CONFIG_SERIAL_TEXT_DEBUG)
(brace
r_struct
id|uart_port
id|p
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|p
comma
l_int|0
comma
r_sizeof
(paren
id|p
)paren
)paren
suffix:semicolon
id|p.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|p.membase
op_assign
(paren
r_int
r_char
id|__iomem
op_star
)paren
id|immrbar
op_plus
l_int|0x4500
suffix:semicolon
id|p.uartclk
op_assign
id|binfo-&gt;bi_busfreq
suffix:semicolon
id|gen550_init
c_func
(paren
l_int|0
comma
op_amp
id|p
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|p
comma
l_int|0
comma
r_sizeof
(paren
id|p
)paren
)paren
suffix:semicolon
id|p.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|p.membase
op_assign
(paren
r_int
r_char
id|__iomem
op_star
)paren
id|immrbar
op_plus
l_int|0x4500
suffix:semicolon
id|p.uartclk
op_assign
id|binfo-&gt;bi_busfreq
suffix:semicolon
id|gen550_init
c_func
(paren
l_int|1
comma
op_amp
id|p
)paren
suffix:semicolon
)brace
macro_line|#endif
id|identify_ppc_sys_by_id
c_func
(paren
id|mfspr
c_func
(paren
id|SPRN_SVR
)paren
)paren
suffix:semicolon
multiline_comment|/* setup the PowerPC module struct */
id|ppc_md.setup_arch
op_assign
id|mpc834x_sys_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|mpc834x_sys_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|mpc834x_sys_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|ipic_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|mpc83xx_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|mpc83xx_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|mpc83xx_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|mpc83xx_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|mpc834x_sys_map_io
suffix:semicolon
id|ppc_md.time_init
op_assign
id|mpc83xx_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|mpc83xx_calibrate_decr
suffix:semicolon
id|ppc_md.early_serial_map
op_assign
id|mpc83xx_early_serial_map
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_8250) &amp;&amp; defined(CONFIG_SERIAL_TEXT_DEBUG)
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SERIAL_8250 &amp;&amp; CONFIG_SERIAL_TEXT_DEBUG */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc834x_sys_init(): exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
