multiline_comment|/*&n; * arch/ppc/platforms/85xx/mpc8540_ads.c&n; *&n; * MPC8540ADS board specific routines&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/mpc85xx.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/immap_85xx.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;asm/ppc_sys.h&gt;
macro_line|#include &lt;mm/mmu_decl.h&gt;
macro_line|#include &lt;syslib/ppc85xx_setup.h&gt;
multiline_comment|/* ************************************************************************&n; *&n; * Setup the architecture&n; *&n; */
r_static
r_void
id|__init
DECL|function|mpc8540ads_setup_arch
id|mpc8540ads_setup_arch
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
l_string|&quot;mpc8540ads_setup_arch()&quot;
comma
l_int|0
)paren
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
id|mpc85xx_setup_hose
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_8250
id|mpc85xx_early_serial_map
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
multiline_comment|/* Invalidate the entry we stole earlier the serial ports&n;&t; * should be properly mapped */
id|invalidate_tlbcam_entry
c_func
(paren
id|NUM_TLBCAMS
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
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
id|MPC85xx_TSEC1
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC85xx_IRQ_EXT5
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
id|MPC85xx_TSEC2
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC85xx_IRQ_EXT5
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
id|MPC85xx_FEC
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC85xx_IRQ_EXT5
suffix:semicolon
id|pdata-&gt;phyid
op_assign
l_int|3
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
id|binfo-&gt;bi_enet2addr
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
multiline_comment|/* ************************************************************************ */
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
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
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
multiline_comment|/* Use the last TLB entry to map CCSRBAR to allow access to DUART regs */
id|settlbcam
c_func
(paren
id|NUM_TLBCAMS
op_minus
l_int|1
comma
id|binfo-&gt;bi_immr_base
comma
id|binfo-&gt;bi_immr_base
comma
id|MPC85xx_CCSRBAR_SIZE
comma
id|_PAGE_IO
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#endif&t;&t;&t;&t;/* CONFIG_BLK_DEV_INITRD */
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
id|identify_ppc_sys_by_id
c_func
(paren
id|mfspr
c_func
(paren
id|SVR
)paren
)paren
suffix:semicolon
multiline_comment|/* setup the PowerPC module struct */
id|ppc_md.setup_arch
op_assign
id|mpc8540ads_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|mpc85xx_ads_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|mpc85xx_ads_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|mpc85xx_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|mpc85xx_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|mpc85xx_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|mpc85xx_find_end_of_memory
suffix:semicolon
id|ppc_md.time_init
op_assign
l_int|NULL
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
id|mpc85xx_calibrate_decr
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
l_string|&quot;mpc8540ads_init(): exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
