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
macro_line|#include &lt;linux/initrd.h&gt;
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
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &quot;i8259.h&quot;
macro_line|#include &quot;open_pic.h&quot;
macro_line|#include &lt;asm/xics.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
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
id|pSeries_init_openpic
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
id|pSeries_final_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pSeries_get_boot_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_time
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
id|dev_t
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
DECL|function|chrp_get_cpuinfo
r_void
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
id|root
op_assign
id|of_find_node_by_path
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
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
)brace
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG 0x60
DECL|function|chrp_request_regions
r_void
id|__init
id|chrp_request_regions
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|i8042
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
multiline_comment|/*&n;&t; * Some machines have an unterminated i8042 so check the device&n;&t; * tree and reserve the region if it does not appear. Later on&n;&t; * the i8042 code will try and reserve this region and fail.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|i8042
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;8042&quot;
)paren
)paren
)paren
id|request_region
c_func
(paren
id|I8042_DATA_REG
comma
l_int|16
comma
l_string|&quot;reserved (no i8042)&quot;
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|i8042
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
id|of_find_node_by_path
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
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PPC_PSERIES
id|pSeries_nvram_init
c_func
(paren
)paren
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
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
r_char
op_star
id|hypertas
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
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
id|pSeries_init_openpic
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
id|ppc_md.init
op_assign
id|chrp_init2
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
id|pSeries_final_fixup
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
id|pSeries_get_boot_time
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
multiline_comment|/* Build up the firmware_features bitmask field&n;         * using contents of device-tree/ibm,hypertas-functions.&n;         * Ultimately this functionality may be moved into prom.c prom_init().&n;         */
id|dn
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
suffix:semicolon
id|cur_cpu_spec-&gt;firmware_features
op_assign
l_int|0
suffix:semicolon
id|hypertas
op_assign
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,hypertas-functions&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hypertas
)paren
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|i
comma
id|hypertas_len
suffix:semicolon
multiline_comment|/* check value against table of strings */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FIRMWARE_MAX_FEATURES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|firmware_features_table
(braket
id|i
)braket
dot
id|name
)paren
op_logical_and
(paren
id|strcmp
c_func
(paren
id|firmware_features_table
(braket
id|i
)braket
dot
id|name
comma
id|hypertas
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* we have a match */
id|cur_cpu_spec-&gt;firmware_features
op_or_assign
(paren
id|firmware_features_table
(braket
id|i
)braket
dot
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|hypertas_len
op_assign
id|strlen
c_func
(paren
id|hypertas
)paren
suffix:semicolon
id|len
op_sub_assign
id|hypertas_len
op_plus
l_int|1
suffix:semicolon
id|hypertas
op_add_assign
id|hypertas_len
op_plus
l_int|1
suffix:semicolon
)brace
)brace
id|of_node_put
c_func
(paren
id|dn
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;firmware_features = 0x%lx&bslash;n&quot;
comma
id|cur_cpu_spec-&gt;firmware_features
)paren
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
r_static
r_int
id|pending_newline
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* did last write end with unprinted newline? */
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
r_return
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
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|display_character
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
multiline_comment|/* use hex display if available */
r_if
c_cond
(paren
id|set_indicator
op_ne
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
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
)brace
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|progress_lock
)paren
suffix:semicolon
multiline_comment|/* Last write ended with newline, but we didn&squot;t print it since&n;&t; * it would just clear the bottom line of output. Print it now&n;&t; * instead.&n;&t; *&n;&t; * If no newline is pending, print a CR to start output at the&n;&t; * beginning of the line.&n;&t; */
r_if
c_cond
(paren
id|pending_newline
)paren
(brace
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
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pending_newline
op_assign
l_int|0
suffix:semicolon
)brace
r_else
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
op_star
id|os
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
op_star
id|os
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
multiline_comment|/* Blank to end of line. */
r_while
c_loop
(paren
id|width
op_decrement
OG
l_int|0
)paren
(brace
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
)brace
multiline_comment|/* If newline is the last character, save it&n;&t;&t;&t; * until next call to avoid bumping up the&n;&t;&t;&t; * display output.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|os
(braket
l_int|1
)braket
)paren
(brace
id|pending_newline
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|progress_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* RTAS wants CR-LF, not just LF */
r_if
c_cond
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
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
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* CR might be used to re-draw a line, so we&squot;ll&n;&t;&t;&t;&t; * leave it alone and not add LF.&n;&t;&t;&t;&t; */
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
)paren
suffix:semicolon
)brace
id|width
op_assign
id|max_width
suffix:semicolon
)brace
r_else
(brace
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
)paren
suffix:semicolon
)brace
id|os
op_increment
suffix:semicolon
multiline_comment|/* if we overwrite the screen length */
r_if
c_cond
(paren
id|width
op_le
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
multiline_comment|/* Some sane defaults: 125 MHz timebase, 1GHz processor */
DECL|macro|DEFAULT_TB_FREQ
mdefine_line|#define DEFAULT_TB_FREQ&t;&t;125000000UL
DECL|macro|DEFAULT_PROC_FREQ
mdefine_line|#define DEFAULT_PROC_FREQ&t;(DEFAULT_TB_FREQ * 8)
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
r_int
op_star
id|fp
suffix:semicolon
r_int
id|node_found
suffix:semicolon
multiline_comment|/*&n;&t; * The cpu node should have a timebase-frequency property&n;&t; * to tell us the rate at which the decrementer counts.&n;&t; */
id|cpu
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
id|ppc_tb_freq
op_assign
id|DEFAULT_TB_FREQ
suffix:semicolon
multiline_comment|/* hardcoded default */
id|node_found
op_assign
l_int|0
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
(brace
id|node_found
op_assign
l_int|1
suffix:semicolon
id|ppc_tb_freq
op_assign
op_star
id|fp
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|node_found
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: Estimating decrementer frequency &quot;
l_string|&quot;(not found)&bslash;n&quot;
)paren
suffix:semicolon
id|ppc_proc_freq
op_assign
id|DEFAULT_PROC_FREQ
suffix:semicolon
id|node_found
op_assign
l_int|0
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
(brace
id|node_found
op_assign
l_int|1
suffix:semicolon
id|ppc_proc_freq
op_assign
op_star
id|fp
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|node_found
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: Estimating processor frequency &quot;
l_string|&quot;(not found)&bslash;n&quot;
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time_init: decrementer frequency = %lu.%.6lu MHz&bslash;n&quot;
comma
id|ppc_tb_freq
op_div
l_int|1000000
comma
id|ppc_tb_freq
op_mod
l_int|1000000
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time_init: processor frequency   = %lu.%.6lu MHz&bslash;n&quot;
comma
id|ppc_proc_freq
op_div
l_int|1000000
comma
id|ppc_proc_freq
op_mod
l_int|1000000
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|ppc_tb_freq
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
id|ppc_tb_freq
op_div
l_int|1000000
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|ppc_tb_freq
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
