multiline_comment|/*&n; * arch/ppc/platforms/85xx/mpc8560_ads.c&n; *&n; * MPC8560ADS board specific routines&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;asm/cpm2.h&gt;
macro_line|#include &lt;mm/mmu_decl.h&gt;
macro_line|#include &lt;syslib/cpm2_pic.h&gt;
macro_line|#include &lt;syslib/ppc85xx_common.h&gt;
macro_line|#include &lt;syslib/ppc85xx_setup.h&gt;
r_extern
r_void
id|cpm2_reset
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* ************************************************************************&n; *&n; * Setup the architecture&n; *&n; */
r_static
r_void
id|__init
DECL|function|mpc8560ads_setup_arch
id|mpc8560ads_setup_arch
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
id|cpm2_reset
c_func
(paren
)paren
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
l_string|&quot;mpc8560ads_setup_arch()&quot;
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
DECL|function|cpm2_cascade
r_static
id|irqreturn_t
id|cpm2_cascade
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_while
c_loop
(paren
(paren
id|irq
op_assign
id|cpm2_get_irq
c_func
(paren
id|regs
)paren
)paren
op_ge
l_int|0
)paren
id|__do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|cpm2_irqaction
r_static
r_struct
id|irqaction
id|cpm2_irqaction
op_assign
(brace
dot
id|handler
op_assign
id|cpm2_cascade
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|mask
op_assign
id|CPU_MASK_NONE
comma
dot
id|name
op_assign
l_string|&quot;cpm2_cascade&quot;
comma
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|mpc8560_ads_init_IRQ
id|mpc8560_ads_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_volatile
id|cpm2_map_t
op_star
id|immap
op_assign
id|cpm2_immr
suffix:semicolon
multiline_comment|/* Setup OpenPIC */
id|mpc85xx_ads_init_IRQ
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* disable all CPM interupts */
id|immap-&gt;im_intctl.ic_simrh
op_assign
l_int|0x0
suffix:semicolon
id|immap-&gt;im_intctl.ic_simrl
op_assign
l_int|0x0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|CPM_IRQ_OFFSET
suffix:semicolon
id|i
OL
(paren
id|NR_CPM_INTS
op_plus
id|CPM_IRQ_OFFSET
)paren
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
id|cpm2_pic
suffix:semicolon
multiline_comment|/* Initialize the default interrupt mapping priorities,&n;&t; * in case the boot rom changed something on us.&n;&t; */
id|immap-&gt;im_intctl.ic_sicr
op_assign
l_int|0
suffix:semicolon
id|immap-&gt;im_intctl.ic_scprrh
op_assign
l_int|0x05309770
suffix:semicolon
id|immap-&gt;im_intctl.ic_scprrl
op_assign
l_int|0x05309770
suffix:semicolon
id|setup_irq
c_func
(paren
id|MPC85xx_IRQ_CPM
comma
op_amp
id|cpm2_irqaction
)paren
suffix:semicolon
r_return
suffix:semicolon
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
id|mpc8560ads_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|mpc85xx_ads_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|mpc8560_ads_init_IRQ
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
l_string|&quot;mpc8560ads_init(): exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
