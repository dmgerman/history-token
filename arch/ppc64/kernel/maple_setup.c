multiline_comment|/*&n; *  arch/ppc64/kernel/maple_setup.c&n; *&n; *  (c) Copyright 2004 Benjamin Herrenschmidt (benh@kernel.crashing.org),&n; *                     IBM Corp. &n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/of_device.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &quot;mpic.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) udbg_printf(fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
macro_line|#endif
r_extern
r_int
id|maple_set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
r_extern
r_void
id|maple_get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
r_extern
r_void
id|maple_get_boot_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
r_extern
r_void
id|maple_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|maple_pci_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|maple_pcibios_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|maple_pci_get_legacy_ide_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|channel
)paren
suffix:semicolon
r_extern
r_void
id|generic_find_legacy_serial_ports
c_func
(paren
r_int
r_int
op_star
id|default_speed
)paren
suffix:semicolon
DECL|function|maple_restart
r_static
r_void
id|maple_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
)brace
DECL|function|maple_power_off
r_static
r_void
id|maple_power_off
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|maple_halt
r_static
r_void
id|maple_halt
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#ifdef CONFIG_SMP
DECL|variable|maple_smp_ops
r_struct
id|smp_ops_t
id|maple_smp_ops
op_assign
(brace
dot
id|probe
op_assign
id|smp_mpic_probe
comma
dot
id|message_pass
op_assign
id|smp_mpic_message_pass
comma
dot
id|kick_cpu
op_assign
id|smp_generic_kick_cpu
comma
dot
id|setup_cpu
op_assign
id|smp_mpic_setup_cpu
comma
dot
id|give_timebase
op_assign
id|smp_generic_give_timebase
comma
dot
id|take_timebase
op_assign
id|smp_generic_take_timebase
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|function|maple_setup_arch
r_void
id|__init
id|maple_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
suffix:semicolon
multiline_comment|/* Setup SMP callback */
macro_line|#ifdef CONFIG_SMP
id|smp_ops
op_assign
op_amp
id|maple_smp_ops
suffix:semicolon
macro_line|#endif
multiline_comment|/* Setup the PCI DMA to &quot;direct&quot; by default. May be overriden&n;&t; * by iommu later on&n;&t; */
id|pci_dma_init_direct
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Lookup PCI hosts */
id|maple_pci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* &n; * Early initialization.&n; */
DECL|function|maple_init_early
r_static
r_void
id|__init
id|maple_init_early
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|default_speed
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; -&gt; maple_init_early&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Initialize hash table, from now on, we can take hash faults&n;&t; * and call ioremap&n;&t; */
id|hpte_init_native
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Find the serial port */
id|generic_find_legacy_serial_ports
c_func
(paren
op_amp
id|default_speed
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;naca-&gt;serialPortAddr: %lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|naca-&gt;serialPortAddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;serialPortAddr
)paren
(brace
r_void
op_star
id|comport
suffix:semicolon
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
comma
id|default_speed
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
id|DBG
c_func
(paren
l_string|&quot;Hello World !&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup interrupt mapping options */
id|naca-&gt;interrupt_controller
op_assign
id|IC_OPEN_PIC
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; &lt;- maple_init_early&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|maple_init_IRQ
r_static
id|__init
r_void
id|maple_init_IRQ
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
r_int
r_int
id|opic_addr
suffix:semicolon
r_struct
id|mpic
op_star
id|mpic
suffix:semicolon
r_int
r_char
id|senses
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|n
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; -&gt; maple_init_IRQ&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX: Non standard, replace that with a proper openpic/mpic node&n;&t; * in the device-tree. Find the Open PIC if present */
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
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;OpenPIC not found !&bslash;n&quot;
)paren
suffix:semicolon
id|n
op_assign
id|prom_n_addr_cells
c_func
(paren
id|root
)paren
suffix:semicolon
r_for
c_loop
(paren
id|opic_addr
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
id|opic_addr
op_assign
(paren
id|opic_addr
op_lshift
l_int|32
)paren
op_plus
op_star
id|opprop
op_increment
suffix:semicolon
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
multiline_comment|/* Obtain sense values from device-tree */
id|prom_get_irq_senses
c_func
(paren
id|senses
comma
l_int|0
comma
l_int|128
)paren
suffix:semicolon
id|mpic
op_assign
id|mpic_alloc
c_func
(paren
id|opic_addr
comma
id|MPIC_PRIMARY
op_or
id|MPIC_BIG_ENDIAN
op_or
id|MPIC_BROKEN_U3
op_or
id|MPIC_WANTS_RESET
comma
l_int|0
comma
l_int|0
comma
l_int|128
comma
l_int|128
comma
id|senses
comma
l_int|128
comma
l_string|&quot;U3-MPIC&quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mpic
op_eq
l_int|NULL
)paren
suffix:semicolon
id|mpic_init
c_func
(paren
id|mpic
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; &lt;- maple_init_IRQ&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|maple_progress
r_static
r_void
id|__init
id|maple_progress
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
l_string|&quot;*** %04x : %s&bslash;n&quot;
comma
id|hex
comma
id|s
ques
c_cond
id|s
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called very early, MMU is off, device-tree isn&squot;t unflattened&n; */
DECL|function|maple_probe
r_static
r_int
id|__init
id|maple_probe
c_func
(paren
r_int
id|platform
)paren
(brace
r_if
c_cond
(paren
id|platform
op_ne
id|PLATFORM_MAPLE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * On U3, the DART (iommu) must be allocated now since it&n;&t; * has an impact on htab_initialize (due to the large page it&n;&t; * occupies having to be broken up so the DART itself is not&n;&t; * part of the cacheable linar mapping&n;&t; */
id|alloc_u3_dart_table
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|maple_md
r_struct
id|machdep_calls
id|__initdata
id|maple_md
op_assign
(brace
dot
id|probe
op_assign
id|maple_probe
comma
dot
id|setup_arch
op_assign
id|maple_setup_arch
comma
dot
id|init_early
op_assign
id|maple_init_early
comma
dot
id|init_IRQ
op_assign
id|maple_init_IRQ
comma
dot
id|get_irq
op_assign
id|mpic_get_irq
comma
dot
id|pcibios_fixup
op_assign
id|maple_pcibios_fixup
comma
macro_line|#if 0
dot
id|pci_get_legacy_ide_irq
op_assign
id|maple_pci_get_legacy_ide_irq
comma
macro_line|#endif
dot
id|restart
op_assign
id|maple_restart
comma
dot
id|power_off
op_assign
id|maple_power_off
comma
dot
id|halt
op_assign
id|maple_halt
comma
dot
id|get_boot_time
op_assign
id|maple_get_boot_time
comma
dot
id|set_rtc_time
op_assign
id|maple_set_rtc_time
comma
dot
id|get_rtc_time
op_assign
id|maple_get_rtc_time
comma
dot
id|calibrate_decr
op_assign
id|maple_calibrate_decr
comma
dot
id|progress
op_assign
id|maple_progress
comma
)brace
suffix:semicolon
eof
