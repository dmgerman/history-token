multiline_comment|/*&n; *&n; *    Copyright (c) 1999-2000 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Copyright 2000-2001 MontaVista Software Inc.&n; *      Completed implementation.&n; *      Author: MontaVista Software, Inc.  &lt;source@mvista.com&gt;&n; *              Frank Rowand &lt;frank_rowand@mvista.com&gt;&n; *              Debbie Chu   &lt;debbie_chu@mvista.com&gt;&n; *&n; *    Module name: ppc4xx_setup.c&n; *&n; *    Description:&n; *      Architecture- / platform-specific boot-time initialization code for&n; *      IBM PowerPC 4xx based boards. Adapted from original&n; *      code by Gary Thomas, Cort Dougan &lt;cort@fsmlabs.com&gt;, and Dan Malek&n; *      &lt;dan@net4x.com&gt;.&n; *&n; * &t;History: 11/09/2001 - armin&n; *&t;rename board_setup_nvram_access to board_init. board_init is&n; *&t;used for all other board specific instructions needed during&n; *&t;platform_init.&n; *&t;moved RTC to board.c files&n; *&t;moved VT/FB to board.c files&n; *&t;moved r/w4 ide to redwood.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/ppc4xx_pic.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
multiline_comment|/* Function Prototypes */
r_extern
r_void
m_abort
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_wdt_heartbeat
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|wdt_enable
suffix:semicolon
r_extern
r_int
r_int
id|wdt_period
suffix:semicolon
multiline_comment|/* Board specific functions */
r_extern
r_void
id|board_setup_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|board_io_mapping
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|board_setup_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|board_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Global Variables */
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
r_static
r_void
id|__init
DECL|function|ppc4xx_setup_arch
id|ppc4xx_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Setup PCI host bridges */
macro_line|#ifdef CONFIG_PCI
id|ppc4xx_find_bridges
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_FB)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|board_setup_arch
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *   This routine pretty-prints the platform&squot;s internal CPU clock&n; *   frequencies into the buffer for usage in /proc/cpuinfo.&n; */
r_static
r_int
DECL|function|ppc4xx_show_percpuinfo
id|ppc4xx_show_percpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_int
id|i
)paren
(brace
id|bd_t
op_star
id|bip
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
l_string|&quot;clock&bslash;t&bslash;t: %ldMHz&bslash;n&quot;
comma
(paren
r_int
)paren
id|bip-&gt;bi_intfreq
op_div
l_int|1000000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *   This routine pretty-prints the platform&squot;s internal bus clock&n; *   frequencies into the buffer for usage in /proc/cpuinfo.&n; */
r_static
r_int
DECL|function|ppc4xx_show_cpuinfo
id|ppc4xx_show_cpuinfo
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
id|bip
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
l_string|&quot;machine&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|PPC4xx_MACHINE_NAME
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;plb bus clock&bslash;t: %ldMHz&bslash;n&quot;
comma
(paren
r_int
)paren
id|bip-&gt;bi_busfreq
op_div
l_int|1000000
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pci bus clock&bslash;t: %dMHz&bslash;n&quot;
comma
id|bip-&gt;bi_pci_busfreq
op_div
l_int|1000000
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the virtual address representing the top of physical RAM.&n; */
r_static
r_int
r_int
id|__init
DECL|function|ppc4xx_find_end_of_memory
id|ppc4xx_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|bip
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
id|bip-&gt;bi_memsize
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|m4xx_map_io
id|m4xx_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|PPC4xx_ONB_IO_VADDR
comma
id|PPC4xx_ONB_IO_PADDR
comma
id|PPC4xx_ONB_IO_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|io_block_mapping
c_func
(paren
id|PPC4xx_PCI_IO_VADDR
comma
id|PPC4xx_PCI_IO_PADDR
comma
id|PPC4xx_PCI_IO_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|PPC4xx_PCI_CFG_VADDR
comma
id|PPC4xx_PCI_CFG_PADDR
comma
id|PPC4xx_PCI_CFG_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|PPC4xx_PCI_LCFG_VADDR
comma
id|PPC4xx_PCI_LCFG_PADDR
comma
id|PPC4xx_PCI_LCFG_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
id|board_io_mapping
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ppc4xx_init_IRQ
id|ppc4xx_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
multiline_comment|/* give board specific code a chance to setup things */
id|board_setup_irq
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|ppc4xx_restart
id|ppc4xx_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ppc4xx_power_off
id|ppc4xx_power_off
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;System Halted&bslash;n&quot;
)paren
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
suffix:semicolon
)brace
r_static
r_void
DECL|function|ppc4xx_halt
id|ppc4xx_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;System Halted&bslash;n&quot;
)paren
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
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine retrieves the internal processor frequency from the board&n; * information structure, sets up the kernel timer decrementer based on&n; * that value, enables the 4xx programmable interval timer (PIT) and sets&n; * it up for auto-reload.&n; */
r_static
r_void
id|__init
DECL|function|ppc4xx_calibrate_decr
id|ppc4xx_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
id|bd_t
op_star
id|bip
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
macro_line|#if defined(CONFIG_WALNUT) || defined(CONFIG_CEDER)
multiline_comment|/* Walnut boot rom sets DCR CHCR1 (aka CPC0_CR1) bit CETE to 1 */
id|mtdcr
c_func
(paren
id|DCRN_CHCR1
comma
id|mfdcr
c_func
(paren
id|DCRN_CHCR1
)paren
op_amp
op_complement
id|CHR1_CETE
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_REDWOOD_5
id|freq
op_assign
id|bip-&gt;bi_tbfreq
suffix:semicolon
macro_line|#else
id|freq
op_assign
id|bip-&gt;bi_intfreq
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Set the time base to zero.&n;&t;   ** At 200 Mhz, time base will rollover in ~2925 years.&n;&t; */
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
id|TSR_PIS
op_or
id|TSR_FIS
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_TCR
comma
id|TCR_PIE
op_or
id|TCR_ARE
)paren
suffix:semicolon
multiline_comment|/* Set the PIT reload value and just let it run. */
id|mtspr
c_func
(paren
id|SPRN_PIT
comma
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_TEXT
r_static
r_void
DECL|function|ppc4xx_progress
id|ppc4xx_progress
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
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&bslash;r&quot;
comma
id|s
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * IDE stuff.&n; * should be generic for every IDE PCI chipset&n; */
macro_line|#ifdef  CONFIG_PCI
r_static
r_void
DECL|function|ppc4xx_ide_init_hwif_ports
id|ppc4xx_ide_init_hwif_ports
c_func
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
op_increment
id|i
)paren
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|data_port
op_plus
id|i
op_minus
id|IDE_DATA_OFFSET
suffix:semicolon
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
)brace
macro_line|#endif
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Input(s):&n; *   r3 - Optional pointer to a board information structure.&n; *   r4 - Optional pointer to the physical starting address of the init RAM&n; *        disk.&n; *   r5 - Optional pointer to the physical ending address of the init RAM&n; *        disk.&n; *   r6 - Optional pointer to the physical starting address of any kernel&n; *        command-line parameters.&n; *   r7 - Optional pointer to the physical ending address of any kernel&n; *        command-line parameters.&n; */
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
macro_line|#if defined(CONFIG_PPC405_WDT)
multiline_comment|/* Look for wdt= option on command line */
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;wdt=&quot;
)paren
)paren
(brace
r_int
id|valid_wdt
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|cmd_line
suffix:semicolon
(paren
id|p
op_assign
id|strstr
c_func
(paren
id|q
comma
l_string|&quot;wdt=&quot;
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)paren
(brace
id|q
op_assign
id|p
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p
OG
id|cmd_line
op_logical_and
id|p
(braket
op_minus
l_int|1
)braket
op_ne
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
id|wdt_period
op_assign
id|simple_strtoul
c_func
(paren
id|q
comma
op_amp
id|q
comma
l_int|0
)paren
suffix:semicolon
id|valid_wdt
op_assign
l_int|1
suffix:semicolon
op_increment
id|q
suffix:semicolon
)brace
id|wdt_enable
op_assign
id|valid_wdt
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Initialize machine-dependency vectors */
id|ppc_md.setup_arch
op_assign
id|ppc4xx_setup_arch
suffix:semicolon
id|ppc_md.show_percpuinfo
op_assign
id|ppc4xx_show_percpuinfo
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|ppc4xx_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|ppc4xx_init_IRQ
suffix:semicolon
id|ppc_md.restart
op_assign
id|ppc4xx_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|ppc4xx_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|ppc4xx_halt
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|ppc4xx_calibrate_decr
suffix:semicolon
macro_line|#ifdef CONFIG_PPC405_WDT
id|ppc_md.heartbeat
op_assign
id|ppc4xx_wdt_heartbeat
suffix:semicolon
macro_line|#endif
id|ppc_md.heartbeat_count
op_assign
l_int|0
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|ppc4xx_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|m4xx_map_io
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_TEXT
id|ppc_md.progress
op_assign
id|ppc4xx_progress
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_PC_KEYBOARD)
macro_line|#if defined(CONFIG_REDWOOD_4) &amp;&amp; defined(CONFIG_STB_KB)
id|redwood_irkb_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;**   m8xx_setup.c, prep_setup.c use&n;**     defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)&n;*/
macro_line|#ifdef CONFIG_IDE
macro_line|# ifdef CONFIG_PCI
id|ppc_ide_md.ide_init_hwif
op_assign
id|ppc4xx_ide_init_hwif_ports
suffix:semicolon
macro_line|# endif
macro_line|#endif
id|board_init
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
