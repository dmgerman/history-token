multiline_comment|/*&n; *  linux/arch/ppc/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  Modified by PPC64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/pci_dma.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &quot;i8259.h&quot;
macro_line|#include &quot;open_pic.h&quot;
macro_line|#include &lt;asm/xics.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
r_extern
r_volatile
r_int
r_char
op_star
id|chrp_int_ack_special
suffix:semicolon
r_void
id|chrp_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|openpic_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_ras_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|find_and_init_phbs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pSeries_get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_time
)paren
suffix:semicolon
r_extern
r_int
id|pSeries_set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_time
)paren
suffix:semicolon
r_void
id|pSeries_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|fwnmi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|SystemReset_FWNMI
c_func
(paren
r_void
)paren
comma
id|MachineCheck_FWNMI
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* from head.S */
DECL|variable|fwnmi_active
r_int
id|fwnmi_active
suffix:semicolon
multiline_comment|/* TRUE if an FWNMI handler is present */
DECL|variable|boot_dev
id|kdev_t
id|boot_dev
suffix:semicolon
DECL|variable|virtPython0Facilities
r_int
r_int
id|virtPython0Facilities
op_assign
l_int|0
suffix:semicolon
singleline_comment|// python0 facility area (memory mapped io) (64-bit format) VIRTUAL address.
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
r_extern
r_int
r_int
id|ppc_proc_freq
suffix:semicolon
r_extern
r_int
r_int
id|ppc_tb_freq
suffix:semicolon
r_void
DECL|function|chrp_get_cpuinfo
id|chrp_get_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_const
r_char
op_star
id|model
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;timebase&bslash;t: %lu&bslash;n&quot;
comma
id|ppc_tb_freq
)paren
suffix:semicolon
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: CHRP %s&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
)brace
DECL|function|chrp_request_regions
r_void
id|__init
id|chrp_request_regions
c_func
(paren
r_void
)paren
(brace
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
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|chrp_setup_arch
id|chrp_setup_arch
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_int
r_int
op_star
id|opprop
suffix:semicolon
multiline_comment|/* openpic global configuration register (64-bit format). */
multiline_comment|/* openpic Interrupt Source Unit pointer (64-bit format). */
multiline_comment|/* python0 facility area (mmio) (64-bit format) REAL address. */
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* this is fine for chrp */
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
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
id|ROOT_DEV
op_assign
id|Root_SDA2
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Boot arguments: %s&bslash;n&quot;
comma
id|cmd_line
)paren
suffix:semicolon
id|fwnmi_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PPC_ISERIES
multiline_comment|/* Find and initialize PCI host bridges */
multiline_comment|/* iSeries needs to be done much later. */
id|eeh_init
c_func
(paren
)paren
suffix:semicolon
id|find_and_init_phbs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Find the Open PIC if present */
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
id|opprop
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;platform-open-pic&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opprop
op_ne
l_int|0
)paren
(brace
r_int
id|n
op_assign
id|prom_n_addr_cells
c_func
(paren
id|root
)paren
suffix:semicolon
r_int
r_int
id|openpic
suffix:semicolon
r_for
c_loop
(paren
id|openpic
op_assign
l_int|0
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
op_decrement
id|n
)paren
id|openpic
op_assign
(paren
id|openpic
op_lshift
l_int|32
)paren
op_plus
op_star
id|opprop
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;OpenPIC addr: %lx&bslash;n&quot;
comma
id|openpic
)paren
suffix:semicolon
id|OpenPIC_Addr
op_assign
id|__ioremap
c_func
(paren
id|openpic
comma
l_int|0x40000
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
)brace
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
DECL|function|chrp_init2
id|chrp_init2
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Manually leave the kernel version on the panel. */
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Linux ppc64&bslash;n&quot;
comma
l_int|0
)paren
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
id|UTS_RELEASE
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize firmware assisted non-maskable interrupts if&n; * the firmware supports this feature.&n; *&n; */
DECL|function|fwnmi_init
r_void
id|__init
id|fwnmi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|ibm_nmi_register
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,nmi-register&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ibm_nmi_register
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
suffix:semicolon
id|ret
op_assign
id|rtas_call
c_func
(paren
id|ibm_nmi_register
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|SystemReset_FWNMI
)paren
comma
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|MachineCheck_FWNMI
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|fwnmi_active
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Early initialization.  Relocation is on but do not reference unbolted pages */
DECL|function|pSeries_init_early
r_void
id|__init
id|pSeries_init_early
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PPC_PSERIES&t;/* This ifdef should go away */
r_void
op_star
id|comport
suffix:semicolon
id|hpte_init_pSeries
c_func
(paren
)paren
suffix:semicolon
id|tce_init_pSeries
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_init_pSeries
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Map the uart for udbg. */
id|comport
op_assign
(paren
r_void
op_star
)paren
id|__ioremap
c_func
(paren
id|naca-&gt;serialPortAddr
comma
l_int|16
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
id|udbg_init_uart
c_func
(paren
id|comport
)paren
suffix:semicolon
id|ppc_md.udbg_putc
op_assign
id|udbg_putc
suffix:semicolon
id|ppc_md.udbg_getc
op_assign
id|udbg_getc
suffix:semicolon
id|ppc_md.udbg_getc_poll
op_assign
id|udbg_getc_poll
suffix:semicolon
macro_line|#endif
)brace
r_void
id|__init
DECL|function|chrp_init
id|chrp_init
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
macro_line|#if 0 /* PPPBBB remove this later... -Peter */
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* take care of initrd if we have one */
r_if
c_cond
(paren
id|r6
)paren
(brace
id|initrd_start
op_assign
id|__va
c_func
(paren
id|r6
)paren
suffix:semicolon
id|initrd_end
op_assign
id|__va
c_func
(paren
id|r6
op_plus
id|r7
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
macro_line|#endif
id|ppc_md.setup_arch
op_assign
id|chrp_setup_arch
suffix:semicolon
id|ppc_md.setup_residual
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_cpuinfo
op_assign
id|chrp_get_cpuinfo
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;interrupt_controller
op_eq
id|IC_OPEN_PIC
)paren
(brace
id|ppc_md.init_IRQ
op_assign
id|openpic_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
)brace
r_else
(brace
id|ppc_md.init_IRQ
op_assign
id|xics_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|xics_get_irq
suffix:semicolon
)brace
id|ppc_md.init_ras_IRQ
op_assign
id|init_ras_IRQ
suffix:semicolon
id|ppc_md.init
op_assign
id|chrp_init2
suffix:semicolon
id|ppc_md.restart
op_assign
id|rtas_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|rtas_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|rtas_halt
suffix:semicolon
id|ppc_md.get_boot_time
op_assign
id|pSeries_get_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|pSeries_get_rtc_time
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|pSeries_set_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|pSeries_calibrate_decr
suffix:semicolon
id|ppc_md.progress
op_assign
id|chrp_progress
suffix:semicolon
)brace
r_void
DECL|function|chrp_progress
id|chrp_progress
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
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_int
id|width
comma
op_star
id|p
suffix:semicolon
r_char
op_star
id|os
suffix:semicolon
r_static
r_int
id|display_character
comma
id|set_indicator
suffix:semicolon
r_static
r_int
id|max_width
suffix:semicolon
r_static
id|spinlock_t
id|progress_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rtas.base
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|max_width
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
)paren
op_logical_and
(paren
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;ibm,display-line-length&quot;
comma
l_int|NULL
)paren
)paren
)paren
id|max_width
op_assign
op_star
id|p
suffix:semicolon
r_else
id|max_width
op_assign
l_int|0x10
suffix:semicolon
id|display_character
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;display-character&quot;
)paren
suffix:semicolon
id|set_indicator
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;set-indicator&quot;
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|progress_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|display_character
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
multiline_comment|/* use hex display */
r_if
c_cond
(paren
id|set_indicator
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_goto
id|chrp_progress_exit
suffix:semicolon
id|rtas_call
c_func
(paren
id|set_indicator
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
l_int|6
comma
l_int|0
comma
id|hex
)paren
suffix:semicolon
r_goto
id|chrp_progress_exit
suffix:semicolon
)brace
id|rtas_call
c_func
(paren
id|display_character
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|width
op_assign
id|max_width
suffix:semicolon
id|os
op_assign
id|s
suffix:semicolon
r_while
c_loop
(paren
op_star
id|os
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_logical_or
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|width
op_assign
id|max_width
suffix:semicolon
r_else
id|width
op_decrement
suffix:semicolon
id|rtas_call
c_func
(paren
id|display_character
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
op_star
id|os
op_increment
)paren
suffix:semicolon
multiline_comment|/* if we overwrite the screen length */
r_if
c_cond
(paren
id|width
op_eq
l_int|0
)paren
r_while
c_loop
(paren
(paren
op_star
id|os
op_ne
l_int|0
)paren
op_logical_and
(paren
op_star
id|os
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
op_star
id|os
op_ne
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|os
op_increment
suffix:semicolon
)brace
multiline_comment|/* Blank to end of line. */
r_while
c_loop
(paren
id|width
op_decrement
OG
l_int|0
)paren
id|rtas_call
c_func
(paren
id|display_character
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|chrp_progress_exit
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|progress_lock
)paren
suffix:semicolon
)brace
r_extern
r_void
id|setup_default_decr
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|pSeries_calibrate_decr
r_void
id|__init
id|pSeries_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|cpu
suffix:semicolon
r_struct
id|div_result
id|divres
suffix:semicolon
r_int
op_star
id|fp
suffix:semicolon
r_int
r_int
id|freq
comma
id|processor_freq
suffix:semicolon
multiline_comment|/*&n;&t; * The cpu node should have a timebase-frequency property&n;&t; * to tell us the rate at which the decrementer counts. &n;&t; */
id|freq
op_assign
l_int|16666000
suffix:semicolon
multiline_comment|/* hardcoded default */
id|cpu
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_ne
l_int|0
)paren
(brace
id|fp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;timebase-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_ne
l_int|0
)paren
id|freq
op_assign
op_star
id|fp
suffix:semicolon
)brace
id|ppc_tb_freq
op_assign
id|freq
suffix:semicolon
id|processor_freq
op_assign
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_ne
l_int|0
)paren
(brace
id|fp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_ne
l_int|0
)paren
id|processor_freq
op_assign
op_star
id|fp
suffix:semicolon
)brace
id|ppc_proc_freq
op_assign
id|processor_freq
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
id|printk
c_func
(paren
l_string|&quot;time_init: processor frequency   = %lu.%.6lu MHz&bslash;n&quot;
comma
id|processor_freq
op_div
l_int|1000000
comma
id|processor_freq
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
id|tb_ticks_per_sec
op_assign
id|tb_ticks_per_jiffy
op_star
id|HZ
suffix:semicolon
id|tb_ticks_per_usec
op_assign
id|freq
op_div
l_int|1000000
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
id|div128_by_32
c_func
(paren
l_int|1024
op_star
l_int|1024
comma
l_int|0
comma
id|tb_ticks_per_sec
comma
op_amp
id|divres
)paren
suffix:semicolon
id|tb_to_xs
op_assign
id|divres.result_low
suffix:semicolon
id|setup_default_decr
c_func
(paren
)paren
suffix:semicolon
)brace
eof
