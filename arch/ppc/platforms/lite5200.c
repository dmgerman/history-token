multiline_comment|/*&n; * arch/ppc/platforms/lite5200.c&n; *&n; * Platform support file for the Freescale LITE5200 based on MPC52xx.&n; * A maximum of this file should be moved to syslib/mpc52xx_?????&n; * so that new platform based on MPC52xx need a minimal platform file&n; * ( avoid code duplication )&n; *&n; * &n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Based on the 2.4 code written by Kent Borg,&n; * Dale Farnsworth &lt;dale.farnsworth@mvista.com&gt; and&n; * Wolfgang Denk &lt;wd@denx.de&gt;&n; * &n; * Copyright 2004 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; * Copyright 2003 Motorola Inc.&n; * Copyright 2003 MontaVista Software Inc.&n; * Copyright 2003 DENX Software Engineering (wd@denx.de)&n; *&n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/mpc52xx.h&gt;
macro_line|#include &lt;syslib/mpc52xx_pci.h&gt;
r_extern
r_int
id|powersave_nap
suffix:semicolon
multiline_comment|/* Board data given by U-Boot */
DECL|variable|__res
id|bd_t
id|__res
suffix:semicolon
DECL|variable|__res
id|EXPORT_SYMBOL
c_func
(paren
id|__res
)paren
suffix:semicolon
multiline_comment|/* For modules */
multiline_comment|/* ======================================================================== */
multiline_comment|/* OCP device definition                                                    */
multiline_comment|/* For board/shared resources like PSCs                                     */
multiline_comment|/* ======================================================================== */
multiline_comment|/* Be sure not to load conficting devices : e.g. loading the UART drivers for&n; * PSC1 and then also loading a AC97 for this same PSC.&n; * For details about how to create an entry, look in the doc of the concerned&n; * driver ( eg drivers/serial/mpc52xx_uart.c for the PSC in uart mode )&n; */
DECL|variable|board_ocp
r_struct
id|ocp_def
id|board_ocp
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_PSC_UART
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|MPC52xx_PSC1
comma
dot
id|irq
op_assign
id|MPC52xx_PSC1_IRQ
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
)brace
comma
(brace
multiline_comment|/* Terminating entry */
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
multiline_comment|/* ======================================================================== */
multiline_comment|/* Platform specific code                                                   */
multiline_comment|/* ======================================================================== */
r_static
r_int
DECL|function|lite5200_show_cpuinfo
id|lite5200_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: Freescale LITE5200&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
r_static
r_int
DECL|function|lite5200_map_irq
id|lite5200_map_irq
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
r_return
(paren
id|pin
op_eq
l_int|1
)paren
op_logical_and
(paren
id|idsel
op_eq
l_int|24
)paren
ques
c_cond
id|MPC52xx_IRQ0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_static
r_void
id|__init
DECL|function|lite5200_setup_cpu
id|lite5200_setup_cpu
c_func
(paren
r_void
)paren
(brace
r_struct
id|mpc52xx_xlb
id|__iomem
op_star
id|xlb
suffix:semicolon
r_struct
id|mpc52xx_intr
op_star
id|intr
suffix:semicolon
id|u32
id|intr_ctrl
suffix:semicolon
multiline_comment|/* Map zones */
id|xlb
op_assign
id|ioremap
c_func
(paren
id|MPC52xx_XLB
comma
r_sizeof
(paren
r_struct
id|mpc52xx_xlb
)paren
)paren
suffix:semicolon
id|intr
op_assign
(paren
r_struct
id|mpc52xx_intr
op_star
)paren
id|ioremap
c_func
(paren
id|MPC52xx_INTR
comma
r_sizeof
(paren
r_struct
id|mpc52xx_intr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xlb
op_logical_or
op_logical_neg
id|intr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lite5200.c: Error while mapping XLB/INTR during &quot;
l_string|&quot;lite5200_setup_cpu&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|unmap_regs
suffix:semicolon
)brace
multiline_comment|/* Configure the XLB Arbiter */
id|out_be32
c_func
(paren
op_amp
id|xlb-&gt;master_pri_enable
comma
l_int|0xff
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|xlb-&gt;master_priority
comma
l_int|0x11111111
)paren
suffix:semicolon
multiline_comment|/* Enable ram snooping for 1GB window */
id|out_be32
c_func
(paren
op_amp
id|xlb-&gt;config
comma
id|in_be32
c_func
(paren
op_amp
id|xlb-&gt;config
)paren
op_or
id|MPC52xx_XLB_CFG_SNOOP
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|xlb-&gt;snoop_window
comma
id|MPC52xx_PCI_TARGET_MEM
op_or
l_int|0x1d
)paren
suffix:semicolon
multiline_comment|/* IRQ[0-3] setup : IRQ0     - Level Active Low  */
multiline_comment|/*                  IRQ[1-3] - Level Active High */
id|intr_ctrl
op_assign
id|in_be32
c_func
(paren
op_amp
id|intr-&gt;ctrl
)paren
suffix:semicolon
id|intr_ctrl
op_and_assign
op_complement
l_int|0x00ff0000
suffix:semicolon
id|intr_ctrl
op_or_assign
l_int|0x00c00000
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|intr-&gt;ctrl
comma
id|intr_ctrl
)paren
suffix:semicolon
multiline_comment|/* Unmap reg zone */
id|unmap_regs
suffix:colon
r_if
c_cond
(paren
id|xlb
)paren
id|iounmap
c_func
(paren
id|xlb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr
)paren
id|iounmap
c_func
(paren
id|intr
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|lite5200_setup_arch
id|lite5200_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Add board OCP definitions */
id|mpc52xx_add_board_devices
c_func
(paren
id|board_ocp
)paren
suffix:semicolon
multiline_comment|/* CPU &amp; Port mux setup */
id|lite5200_setup_cpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* PCI Bridge setup */
id|mpc52xx_find_bridges
c_func
(paren
)paren
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
multiline_comment|/* Generic MPC52xx platform initialization */
multiline_comment|/* TODO Create one and move a max of stuff in it.&n;&t;   Put this init in the syslib */
r_struct
id|bi_record
op_star
id|bootinfo
op_assign
id|find_bootinfo
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bootinfo
)paren
id|parse_bootinfo
c_func
(paren
id|bootinfo
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Load the bd_t board info structure */
r_if
c_cond
(paren
id|r3
)paren
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
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
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* Load the initrd */
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
macro_line|#endif
multiline_comment|/* Load the command line */
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
)brace
multiline_comment|/* BAT setup */
id|mpc52xx_set_bat
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* No ISA bus by default */
id|isa_io_base
op_assign
l_int|0
suffix:semicolon
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Powersave */
id|powersave_nap
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We allow this platform to NAP */
multiline_comment|/* Setup the ppc_md struct */
id|ppc_md.setup_arch
op_assign
id|lite5200_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|lite5200_show_cpuinfo
suffix:semicolon
id|ppc_md.show_percpuinfo
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|mpc52xx_init_irq
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|mpc52xx_get_irq
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|ppc_md.pci_map_irq
op_assign
id|lite5200_map_irq
suffix:semicolon
macro_line|#endif
id|ppc_md.find_end_of_memory
op_assign
id|mpc52xx_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|mpc52xx_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|mpc52xx_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|mpc52xx_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|mpc52xx_halt
suffix:semicolon
multiline_comment|/* No time keeper on the LITE5200 */
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
id|mpc52xx_calibrate_decr
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|mpc52xx_progress
suffix:semicolon
macro_line|#endif
)brace
eof
