multiline_comment|/*&n; *  arch/ppc/syslib/m8260_setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  Modified for MBX using prep/chrp/pmac functions by Dan (dmalek@jlc.net)&n; *  Further modified for generic 8xx and 8260 by Dan.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/immap_cpm2.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &quot;cpm2_pic.h&quot;
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
r_extern
r_void
id|cpm2_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|m8260_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|idma_pci9_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|m8260_setup_arch
id|m8260_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Print out Vendor and Machine info. */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s %s port&bslash;n&quot;
comma
id|CPUINFO_VENDOR
comma
id|CPUINFO_MACHINE
)paren
suffix:semicolon
multiline_comment|/* Reset the Communication Processor Module. */
id|cpm2_reset
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_8260_PCI9
multiline_comment|/* Initialise IDMA for PCI erratum workaround */
id|idma_pci9_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI_8260
id|m8260_find_bridges
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#endif
)brace
multiline_comment|/* The decrementer counts at the system (internal) clock frequency&n; * divided by four.&n; */
r_static
r_void
id|__init
DECL|function|m8260_calibrate_decr
id|m8260_calibrate_decr
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
id|freq
comma
id|divisor
suffix:semicolon
id|freq
op_assign
id|binfo-&gt;bi_busfreq
suffix:semicolon
id|divisor
op_assign
l_int|4
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
op_div
id|divisor
comma
l_int|1000000
)paren
suffix:semicolon
)brace
multiline_comment|/* The 8260 has an internal 1-second timer update register that&n; * we should use for this purpose.&n; */
DECL|variable|rtc_time
r_static
id|uint
id|rtc_time
suffix:semicolon
r_static
r_int
DECL|function|m8260_set_rtc_time
id|m8260_set_rtc_time
c_func
(paren
r_int
r_int
id|time
)paren
(brace
id|rtc_time
op_assign
id|time
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|m8260_get_rtc_time
id|m8260_get_rtc_time
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Get time from the RTC.&n;&t;*/
r_return
(paren
r_int
r_int
)paren
id|rtc_time
suffix:semicolon
)brace
macro_line|#ifndef BOOTROM_RESTART_ADDR
macro_line|#warning &quot;Using default BOOTROM_RESTART_ADDR!&quot;
DECL|macro|BOOTROM_RESTART_ADDR
mdefine_line|#define BOOTROM_RESTART_ADDR&t;0xff000104
macro_line|#endif
r_static
r_void
DECL|function|m8260_restart
id|m8260_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_extern
r_void
id|m8260_gorom
c_func
(paren
id|bd_t
op_star
id|bi
comma
id|uint
id|addr
)paren
suffix:semicolon
id|uint
id|startaddr
suffix:semicolon
multiline_comment|/* Most boot roms have a warmstart as the second instruction&n;&t; * of the reset vector.  If that doesn&squot;t work for you, change this&n;&t; * or the reboot program to send a proper address.&n;&t; */
id|startaddr
op_assign
id|BOOTROM_RESTART_ADDR
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;startaddr=&quot;
comma
l_int|10
)paren
)paren
id|startaddr
op_assign
id|simple_strtoul
c_func
(paren
op_amp
id|cmd
(braket
l_int|10
)braket
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
id|m8260_gorom
c_func
(paren
(paren
r_void
op_star
)paren
id|__pa
c_func
(paren
id|__res
)paren
comma
id|startaddr
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|m8260_halt
id|m8260_halt
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
DECL|function|m8260_power_off
id|m8260_power_off
c_func
(paren
r_void
)paren
(brace
id|m8260_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|m8260_show_cpuinfo
id|m8260_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|bd_t
op_star
id|bp
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;machine&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;mem size&bslash;t&bslash;t: 0x%08x&bslash;n&quot;
l_string|&quot;console baud&bslash;t&bslash;t: %d&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;core clock&bslash;t: %u MHz&bslash;n&quot;
l_string|&quot;CPM  clock&bslash;t: %u MHz&bslash;n&quot;
l_string|&quot;bus  clock&bslash;t: %u MHz&bslash;n&quot;
comma
id|CPUINFO_VENDOR
comma
id|CPUINFO_MACHINE
comma
id|bp-&gt;bi_memsize
comma
id|bp-&gt;bi_baudrate
comma
id|bp-&gt;bi_intfreq
op_div
l_int|1000000
comma
id|bp-&gt;bi_cpmfreq
op_div
l_int|1000000
comma
id|bp-&gt;bi_busfreq
op_div
l_int|1000000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize the internal interrupt controller.  The number of&n; * interrupts supported can vary with the processor type, and the&n; * 8260 family can have up to 64.&n; * External interrupts can be either edge or level triggered, and&n; * need to be initialized by the appropriate driver.&n; */
r_static
r_void
id|__init
DECL|function|m8260_init_IRQ
id|m8260_init_IRQ
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
id|NR_SIU_INTS
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
id|cpm2_immr-&gt;im_intctl.ic_sicr
op_assign
l_int|0
suffix:semicolon
id|cpm2_immr-&gt;im_intctl.ic_siprr
op_assign
l_int|0x05309770
suffix:semicolon
id|cpm2_immr-&gt;im_intctl.ic_scprrh
op_assign
l_int|0x05309770
suffix:semicolon
id|cpm2_immr-&gt;im_intctl.ic_scprrl
op_assign
l_int|0x05309770
suffix:semicolon
)brace
multiline_comment|/*&n; * Same hack as 8xx&n; */
r_static
r_int
r_int
id|__init
DECL|function|m8260_find_end_of_memory
id|m8260_find_end_of_memory
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
r_return
id|binfo-&gt;bi_memsize
suffix:semicolon
)brace
multiline_comment|/* Map the IMMR, plus anything else we can cover&n; * in that upper space according to the memory controller&n; * chip select mapping.  Grab another bunch of space&n; * below that for stuff we can&squot;t cover in the upper.&n; */
r_static
r_void
id|__init
DECL|function|m8260_map_io
id|m8260_map_io
c_func
(paren
r_void
)paren
(brace
id|uint
id|addr
suffix:semicolon
multiline_comment|/* Map IMMR region to a 256MB BAT */
id|addr
op_assign
(paren
id|cpm2_immr
op_ne
l_int|NULL
)paren
ques
c_cond
(paren
id|uint
)paren
id|cpm2_immr
suffix:colon
id|CPM_MAP_ADDR
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|addr
comma
id|addr
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
multiline_comment|/* Map I/O region to a 256MB BAT */
id|io_block_mapping
c_func
(paren
id|IO_VIRT_ADDR
comma
id|IO_PHYS_ADDR
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
multiline_comment|/* Place-holder for board-specific init */
r_void
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
id|__init
DECL|function|m82xx_board_init
id|m82xx_board_init
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Inputs:&n; *   r3 - Optional pointer to a board information structure.&n; *   r4 - Optional pointer to the physical starting address of the init RAM&n; *        disk.&n; *   r5 - Optional pointer to the physical ending address of the init RAM&n; *        disk.&n; *   r6 - Optional pointer to the physical starting address of any kernel&n; *        command-line parameters.&n; *   r7 - Optional pointer to the physical ending address of any kernel&n; *        command-line parameters.&n; */
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
multiline_comment|/* take care of initrd if we have one */
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
multiline_comment|/* take care of cmd line */
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
id|ppc_md.setup_arch
op_assign
id|m8260_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|m8260_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|m8260_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|cpm2_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|m8260_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|m8260_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|m8260_halt
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|m8260_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|m8260_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|m8260_calibrate_decr
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|m8260_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|m8260_map_io
suffix:semicolon
multiline_comment|/* Call back for board-specific settings and overrides. */
id|m82xx_board_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
