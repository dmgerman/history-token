multiline_comment|/*&n; *  arch/ppc/platforms/setup.c&n; *&n; *  PowerPC version&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Adapted for Power Macintosh by Paul Mackerras&n; *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)&n; *&n; *  Derived from &quot;arch/alpha/kernel/setup.c&quot;&n; *    Copyright (C) 1995 Linus Torvalds&n; *&n; *  Maintained by Benjamin Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
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
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/of_device.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &quot;pmac.h&quot;
macro_line|#include &quot;mpic.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) udbg_printf(fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
macro_line|#endif
DECL|variable|current_root_goodness
r_static
r_int
id|current_root_goodness
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|DEFAULT_ROOT_DEVICE
mdefine_line|#define DEFAULT_ROOT_DEVICE Root_SDA1&t;/* sda1 - slightly silly choice */
r_extern
r_int
id|powersave_nap
suffix:semicolon
DECL|variable|sccdbg
r_int
id|sccdbg
suffix:semicolon
r_extern
r_void
id|udbg_init_scc
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
suffix:semicolon
DECL|function|pmac_show_cpuinfo
r_void
id|__pmac
id|pmac_show_cpuinfo
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
id|np
suffix:semicolon
r_char
op_star
id|pp
suffix:semicolon
r_int
id|plen
suffix:semicolon
r_char
op_star
id|mbname
suffix:semicolon
r_int
id|mbmodel
op_assign
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_GET_MB_INFO
comma
l_int|NULL
comma
id|PMAC_MB_INFO_MODEL
comma
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|mbflags
op_assign
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_GET_MB_INFO
comma
l_int|NULL
comma
id|PMAC_MB_INFO_FLAGS
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_GET_MB_INFO
comma
l_int|NULL
comma
id|PMAC_MB_INFO_NAME
comma
(paren
r_int
)paren
op_amp
id|mbname
)paren
op_ne
l_int|0
)paren
id|mbname
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
multiline_comment|/* find motherboard type */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: &quot;
)paren
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;device-tree&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
id|pp
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
op_ne
l_int|NULL
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|pp
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PowerMac&bslash;n&quot;
)paren
suffix:semicolon
id|pp
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;compatible&quot;
comma
op_amp
id|plen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
op_ne
l_int|NULL
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;motherboard&bslash;t:&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|plen
OG
l_int|0
)paren
(brace
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|pp
)paren
op_plus
l_int|1
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %s&quot;
comma
id|pp
)paren
suffix:semicolon
id|plen
op_sub_assign
id|l
suffix:semicolon
id|pp
op_add_assign
id|l
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PowerMac&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* print parsed model */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;detected as&bslash;t: %d (%s)&bslash;n&quot;
comma
id|mbmodel
comma
id|mbname
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pmac flags&bslash;t: %08x&bslash;n&quot;
comma
id|mbflags
)paren
suffix:semicolon
multiline_comment|/* Indicate newworld */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pmac-generation&bslash;t: NewWorld&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pmac_setup_arch
r_void
id|__init
id|pmac_setup_arch
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
multiline_comment|/* Probe motherboard chipset */
id|pmac_feature_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Lock-enable the SCC channel used for debug */
r_if
c_cond
(paren
id|sccdbg
)paren
(brace
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;escc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
)paren
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_SCC_ENABLE
comma
id|np
comma
id|PMAC_SCC_ASYNC
op_or
id|PMAC_SCC_FLAG_XMON
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* We can NAP */
id|powersave_nap
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Initialize the PMU */
id|find_via_pmu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init NVRAM access */
id|pmac_nvram_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Setup SMP callback */
macro_line|#ifdef CONFIG_SMP
id|pmac_setup_smp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Setup the PCI DMA to &quot;direct&quot; by default. May be overriden&n;&t; * by iommu later on&n;&t; */
id|pci_dma_init_direct
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Lookup PCI hosts */
id|pmac_pci_init
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
macro_line|#ifdef CONFIG_SCSI
DECL|function|note_scsi_host
r_void
id|note_scsi_host
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_void
op_star
id|host
)paren
(brace
multiline_comment|/* Obsolete */
)brace
macro_line|#endif
DECL|variable|initializing
r_static
r_int
id|initializing
op_assign
l_int|1
suffix:semicolon
DECL|function|pmac_late_init
r_static
r_int
id|pmac_late_init
c_func
(paren
r_void
)paren
(brace
id|initializing
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pmac_late_init
id|late_initcall
c_func
(paren
id|pmac_late_init
)paren
suffix:semicolon
multiline_comment|/* can&squot;t be __init - can be called whenever a disk is first accessed */
DECL|function|note_bootable_part
r_void
id|__pmac
id|note_bootable_part
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|part
comma
r_int
id|goodness
)paren
(brace
r_extern
id|dev_t
id|boot_dev
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initializing
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|goodness
op_le
id|current_root_goodness
)paren
op_logical_and
id|ROOT_DEV
op_ne
id|DEFAULT_ROOT_DEVICE
)paren
r_return
suffix:semicolon
id|p
op_assign
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;root=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
op_logical_and
(paren
id|p
op_eq
id|saved_command_line
op_logical_or
id|p
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot_dev
op_logical_or
id|dev
op_eq
id|boot_dev
)paren
(brace
id|ROOT_DEV
op_assign
id|dev
op_plus
id|part
suffix:semicolon
id|boot_dev
op_assign
l_int|0
suffix:semicolon
id|current_root_goodness
op_assign
id|goodness
suffix:semicolon
)brace
)brace
DECL|function|pmac_restart
r_void
id|__pmac
id|pmac_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|pmu_restart
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pmac_power_off
r_void
id|__pmac
id|pmac_power_off
c_func
(paren
r_void
)paren
(brace
id|pmu_shutdown
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pmac_halt
r_void
id|__pmac
id|pmac_halt
c_func
(paren
r_void
)paren
(brace
id|pmac_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
DECL|function|dummy_getc_poll
r_static
r_int
id|dummy_getc_poll
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|dummy_getc
r_static
r_int
r_char
id|dummy_getc
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|btext_putc
r_static
r_void
id|btext_putc
c_func
(paren
r_int
r_char
id|c
)paren
(brace
id|btext_drawchar
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BOOTX_TEXT */
DECL|function|init_boot_display
r_static
r_void
id|__init
id|init_boot_display
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_struct
id|device_node
op_star
id|np
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;trying to initialize btext ...&bslash;n&quot;
)paren
suffix:semicolon
id|name
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,stdout-path&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
op_ne
l_int|NULL
)paren
(brace
id|np
op_assign
id|of_find_node_by_path
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|np-&gt;type
comma
l_string|&quot;display&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;boot stdout isn&squot;t a display !&bslash;n&quot;
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
id|np
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|np
)paren
id|rc
op_assign
id|btext_initialize
c_func
(paren
id|np
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
l_int|NULL
suffix:semicolon
(paren
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;display&quot;
)paren
)paren
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;linux,opened&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;trying %s ...&bslash;n&quot;
comma
id|np-&gt;full_name
)paren
suffix:semicolon
id|rc
op_assign
id|btext_initialize
c_func
(paren
id|np
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;result: %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Early initialization.&n; */
DECL|function|pmac_init_early
r_void
id|__init
id|pmac_init_early
c_func
(paren
r_void
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; pmac_init_early&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Initialize hash table, from now on, we can take hash faults&n;&t; * and call ioremap&n;&t; */
id|hpte_init_native
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init SCC */
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;sccdbg&quot;
)paren
)paren
(brace
id|sccdbg
op_assign
l_int|1
suffix:semicolon
id|udbg_init_scc
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
id|init_boot_display
c_func
(paren
)paren
suffix:semicolon
id|ppc_md.udbg_putc
op_assign
id|btext_putc
suffix:semicolon
id|ppc_md.udbg_getc
op_assign
id|dummy_getc
suffix:semicolon
id|ppc_md.udbg_getc_poll
op_assign
id|dummy_getc_poll
suffix:semicolon
macro_line|#endif /* CONFIG_BOOTX_TEXT */
)brace
multiline_comment|/* Setup interrupt mapping options */
id|naca-&gt;interrupt_controller
op_assign
id|IC_OPEN_PIC
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; &lt;- pmac_init_early&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pmac_u3_cascade
r_static
r_int
id|pmac_u3_cascade
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|mpic_get_one_irq
c_func
(paren
(paren
r_struct
id|mpic
op_star
)paren
id|data
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|pmac_init_IRQ
r_static
id|__init
r_void
id|pmac_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|irqctrler
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|irqctrler2
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|np
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|mpic
op_star
id|mpic1
comma
op_star
id|mpic2
suffix:semicolon
multiline_comment|/* We first try to detect Apple&squot;s new Core99 chipset, since mac-io&n;&t; * is quite different on those machines and contains an IBM MPIC2.&n;&t; */
r_while
c_loop
(paren
(paren
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;open-pic&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|device_node
op_star
id|parent
op_assign
id|of_get_parent
c_func
(paren
id|np
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|parent-&gt;name
comma
l_string|&quot;u3&quot;
)paren
)paren
id|irqctrler2
op_assign
id|of_node_get
c_func
(paren
id|np
)paren
suffix:semicolon
r_else
id|irqctrler
op_assign
id|of_node_get
c_func
(paren
id|np
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqctrler
op_ne
l_int|NULL
op_logical_and
id|irqctrler-&gt;n_addrs
OG
l_int|0
)paren
(brace
r_int
r_char
id|senses
(braket
l_int|128
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PowerMac using OpenPIC irq controller at 0x%08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
)paren
suffix:semicolon
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
id|mpic1
op_assign
id|mpic_alloc
c_func
(paren
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|MPIC_PRIMARY
op_or
id|MPIC_WANTS_RESET
comma
l_int|0
comma
l_int|0
comma
l_int|128
comma
l_int|256
comma
id|senses
comma
l_int|128
comma
l_string|&quot; K2-MPIC  &quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mpic1
op_eq
l_int|NULL
)paren
suffix:semicolon
id|mpic_init
c_func
(paren
id|mpic1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler2
op_ne
l_int|NULL
op_logical_and
id|irqctrler2-&gt;n_intrs
OG
l_int|0
op_logical_and
id|irqctrler2-&gt;n_addrs
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Slave OpenPIC at 0x%08x hooked on IRQ %d&bslash;n&quot;
comma
(paren
id|u32
)paren
id|irqctrler2-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|irqctrler2-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
)paren
suffix:semicolon
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_ENABLE_MPIC
comma
id|irqctrler2
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|prom_get_irq_senses
c_func
(paren
id|senses
comma
l_int|128
comma
l_int|128
op_plus
l_int|128
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t need to set MPIC_BROKEN_U3 here since we don&squot;t have&n;&t;&t;&t; * hypertransport interrupts routed to it&n;&t;&t;&t; */
id|mpic2
op_assign
id|mpic_alloc
c_func
(paren
id|irqctrler2-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|MPIC_BIG_ENDIAN
op_or
id|MPIC_WANTS_RESET
comma
l_int|0
comma
l_int|128
comma
l_int|128
comma
l_int|0
comma
id|senses
comma
l_int|128
comma
l_string|&quot; U3-MPIC  &quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mpic2
op_eq
l_int|NULL
)paren
suffix:semicolon
id|mpic_init
c_func
(paren
id|mpic2
)paren
suffix:semicolon
id|mpic_setup_cascade
c_func
(paren
id|irqctrler2-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
comma
id|pmac_u3_cascade
comma
id|mpic2
)paren
suffix:semicolon
)brace
)brace
id|of_node_put
c_func
(paren
id|irqctrler
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|irqctrler2
)paren
suffix:semicolon
)brace
DECL|function|pmac_progress
r_static
r_void
id|__init
id|pmac_progress
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
r_if
c_cond
(paren
id|sccdbg
)paren
(brace
id|udbg_puts
c_func
(paren
id|s
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_else
r_if
c_cond
(paren
id|boot_text_mapped
)paren
(brace
id|btext_drawstring
c_func
(paren
id|s
)paren
suffix:semicolon
id|btext_drawstring
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BOOTX_TEXT */
)brace
DECL|function|pmac_declare_of_platform_devices
r_static
r_int
id|__init
id|pmac_declare_of_platform_devices
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;u3&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
)paren
(brace
r_for
c_loop
(paren
id|np
op_assign
id|np-&gt;child
suffix:semicolon
id|np
op_ne
l_int|NULL
suffix:semicolon
id|np
op_assign
id|np-&gt;sibling
)paren
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|np-&gt;name
comma
l_string|&quot;i2c&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
id|of_platform_device_create
c_func
(paren
id|np
comma
l_string|&quot;u3-i2c&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pmac_declare_of_platform_devices
id|device_initcall
c_func
(paren
id|pmac_declare_of_platform_devices
)paren
suffix:semicolon
multiline_comment|/*&n; * Called very early, MMU is off, device-tree isn&squot;t unflattened&n; */
DECL|function|pmac_probe
r_static
r_int
id|__init
id|pmac_probe
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
id|PLATFORM_POWERMAC
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
DECL|variable|pmac_md
r_struct
id|machdep_calls
id|__initdata
id|pmac_md
op_assign
(brace
dot
id|probe
op_assign
id|pmac_probe
comma
dot
id|setup_arch
op_assign
id|pmac_setup_arch
comma
dot
id|init_early
op_assign
id|pmac_init_early
comma
dot
id|get_cpuinfo
op_assign
id|pmac_show_cpuinfo
comma
dot
id|init_IRQ
op_assign
id|pmac_init_IRQ
comma
dot
id|get_irq
op_assign
id|mpic_get_irq
comma
dot
id|pcibios_fixup
op_assign
id|pmac_pcibios_fixup
comma
dot
id|restart
op_assign
id|pmac_restart
comma
dot
id|power_off
op_assign
id|pmac_power_off
comma
dot
id|halt
op_assign
id|pmac_halt
comma
dot
id|get_boot_time
op_assign
id|pmac_get_boot_time
comma
dot
id|set_rtc_time
op_assign
id|pmac_set_rtc_time
comma
dot
id|get_rtc_time
op_assign
id|pmac_get_rtc_time
comma
dot
id|calibrate_decr
op_assign
id|pmac_calibrate_decr
comma
dot
id|feature_call
op_assign
id|pmac_do_feature_call
comma
dot
id|progress
op_assign
id|pmac_progress
comma
)brace
suffix:semicolon
eof
