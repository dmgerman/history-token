multiline_comment|/*&n; *  linux/arch/ppc/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  Modified by PPC64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
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
macro_line|#include &lt;asm/xics.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &quot;mpic.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) udbg_printf(fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
macro_line|#endif
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
r_extern
r_void
id|find_udbg_vterm
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
DECL|variable|fwnmi_active
r_int
id|fwnmi_active
suffix:semicolon
multiline_comment|/* TRUE if an FWNMI handler is present */
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
DECL|variable|chrp_int_ack_special
r_static
r_volatile
r_void
id|__iomem
op_star
id|chrp_int_ack_special
suffix:semicolon
DECL|variable|pSeries_mpic
r_struct
id|mpic
op_star
id|pSeries_mpic
suffix:semicolon
DECL|function|pSeries_get_cpuinfo
r_void
id|pSeries_get_cpuinfo
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
multiline_comment|/* Initialize firmware assisted non-maskable interrupts if&n; * the firmware supports this feature.&n; *&n; */
DECL|function|fwnmi_init
r_static
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
DECL|function|pSeries_irq_cascade
r_static
r_int
id|pSeries_irq_cascade
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
r_if
c_cond
(paren
id|chrp_int_ack_special
)paren
r_return
id|readb
c_func
(paren
id|chrp_int_ack_special
)paren
suffix:semicolon
r_else
r_return
id|i8259_irq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|pSeries_init_mpic
r_static
r_void
id|__init
id|pSeries_init_mpic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|addrp
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* All ISUs are setup, complete initialization */
id|mpic_init
c_func
(paren
id|pSeries_mpic
)paren
suffix:semicolon
multiline_comment|/* Check what kind of cascade ACK we have */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;pci&quot;
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|addrp
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;8259-interrupt-acknowledge&quot;
comma
l_int|NULL
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Cannot find pci to get ack address&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|chrp_int_ack_special
op_assign
id|ioremap
c_func
(paren
id|addrp
(braket
id|prom_n_addr_cells
c_func
(paren
id|np
)paren
op_minus
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
multiline_comment|/* Setup the legacy interrupts &amp; controller */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ISA_INTERRUPTS
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
id|i8259_pic
suffix:semicolon
id|i8259_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Hook cascade to mpic */
id|mpic_setup_cascade
c_func
(paren
id|NUM_ISA_INTERRUPTS
comma
id|pSeries_irq_cascade
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pSeries_setup_mpic
r_static
r_void
id|__init
id|pSeries_setup_mpic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|opprop
suffix:semicolon
r_int
r_int
id|openpic_addr
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|senses
(braket
id|NR_IRQS
op_minus
id|NUM_ISA_INTERRUPTS
)braket
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_int
id|irq_count
suffix:semicolon
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
r_for
c_loop
(paren
id|openpic_addr
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
id|openpic_addr
op_assign
(paren
id|openpic_addr
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
id|openpic_addr
)paren
suffix:semicolon
)brace
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|openpic_addr
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Get the sense values from OF */
id|prom_get_irq_senses
c_func
(paren
id|senses
comma
id|NUM_ISA_INTERRUPTS
comma
id|NR_IRQS
)paren
suffix:semicolon
multiline_comment|/* Setup the openpic driver */
id|irq_count
op_assign
id|NR_IRQS
op_minus
id|NUM_ISA_INTERRUPTS
op_minus
l_int|4
suffix:semicolon
multiline_comment|/* leave room for IPIs */
id|pSeries_mpic
op_assign
id|mpic_alloc
c_func
(paren
id|openpic_addr
comma
id|MPIC_PRIMARY
comma
l_int|16
comma
l_int|16
comma
id|irq_count
comma
multiline_comment|/* isu size, irq offset, irq count */
id|NR_IRQS
op_minus
l_int|4
comma
multiline_comment|/* ipi offset */
id|senses
comma
id|irq_count
comma
multiline_comment|/* sense &amp; sense size */
l_string|&quot; MPIC     &quot;
)paren
suffix:semicolon
)brace
DECL|function|pSeries_setup_arch
r_static
r_void
id|__init
id|pSeries_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Fixup ppc_md depending on the type of interrupt controller */
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
id|pSeries_init_mpic
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|mpic_get_irq
suffix:semicolon
multiline_comment|/* Allocate the mpic now, so that find_and_init_phbs() can&n;&t;&t; * fill the ISUs */
id|pSeries_setup_mpic
c_func
(paren
)paren
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
macro_line|#ifdef CONFIG_SMP
id|smp_init_pSeries
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* openpic global configuration register (64-bit format). */
multiline_comment|/* openpic Interrupt Source Unit pointer (64-bit format). */
multiline_comment|/* python0 facility area (mmio) (64-bit format) REAL address. */
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
suffix:semicolon
r_if
c_cond
(paren
id|ROOT_DEV
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No ramdisk, default root is /dev/sda2&bslash;n&quot;
)paren
suffix:semicolon
id|ROOT_DEV
op_assign
id|Root_SDA2
suffix:semicolon
)brace
id|fwnmi_init
c_func
(paren
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|pSeries_nvram_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pSeries_init_panel
r_static
r_int
id|__init
id|pSeries_init_panel
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pSeries_init_panel
id|arch_initcall
c_func
(paren
id|pSeries_init_panel
)paren
suffix:semicolon
multiline_comment|/* Build up the firmware_features bitmask field&n; * using contents of device-tree/ibm,hypertas-functions.&n; * Ultimately this functionality may be moved into prom.c prom_init().&n; */
DECL|function|fw_feature_init
r_void
id|__init
id|fw_feature_init
c_func
(paren
r_void
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
id|DBG
c_func
(paren
l_string|&quot; -&gt; fw_feature_init()&bslash;n&quot;
)paren
suffix:semicolon
id|cur_cpu_spec-&gt;firmware_features
op_assign
l_int|0
suffix:semicolon
id|dn
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING ! Cannot find RTAS in device-tree !&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|no_rtas
suffix:semicolon
)brace
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
id|no_rtas
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;firmware_features = 0x%lx&bslash;n&quot;
comma
id|cur_cpu_spec-&gt;firmware_features
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; &lt;- fw_feature_init()&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pSeries_discover_pic
r_static
r_void
id|__init
id|pSeries_discover_pic
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
r_char
op_star
id|typep
suffix:semicolon
multiline_comment|/*&n;&t; * Setup interrupt mapping options that are needed for finish_device_tree&n;&t; * to properly parse the OF interrupt tree &amp; do the virtual irq mapping&n;&t; */
id|__irq_offset_value
op_assign
id|NUM_ISA_INTERRUPTS
suffix:semicolon
id|naca-&gt;interrupt_controller
op_assign
id|IC_INVALID
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
id|of_find_node_by_name
c_func
(paren
id|np
comma
l_string|&quot;interrupt-controller&quot;
)paren
)paren
suffix:semicolon
)paren
(brace
id|typep
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
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|typep
comma
l_string|&quot;open-pic&quot;
)paren
)paren
id|naca-&gt;interrupt_controller
op_assign
id|IC_OPEN_PIC
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|typep
comma
l_string|&quot;ppc-xicp&quot;
)paren
)paren
id|naca-&gt;interrupt_controller
op_assign
id|IC_PPC_XIC
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;initialize_naca: failed to recognize&quot;
l_string|&quot; interrupt-controller&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|pSeries_cpu_die
r_static
r_void
id|pSeries_cpu_die
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
multiline_comment|/* Some hardware requires clearing the CPPR, while other hardware does not&n;&t; * it is safe either way&n;&t; */
id|pSeriesLP_cppr_info
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|rtas_stop_self
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Should never get here... */
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Early initialization.  Relocation is on but do not reference unbolted pages&n; */
DECL|function|pSeries_init_early
r_static
r_void
id|__init
id|pSeries_init_early
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|comport
suffix:semicolon
r_int
id|iommu_off
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|default_speed
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; -&gt; pSeries_init_early()&bslash;n&quot;
)paren
suffix:semicolon
id|fw_feature_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_LPAR
)paren
id|hpte_init_lpar
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|hpte_init_native
c_func
(paren
)paren
suffix:semicolon
id|iommu_off
op_assign
(paren
id|of_chosen
op_logical_and
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,iommu-off&quot;
comma
l_int|NULL
)paren
)paren
suffix:semicolon
)brace
id|generic_find_legacy_serial_ports
c_func
(paren
op_amp
id|default_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_LPAR
)paren
id|find_udbg_vterm
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|naca-&gt;serialPortAddr
)paren
(brace
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
r_if
c_cond
(paren
id|iommu_off
)paren
id|pci_dma_init_direct
c_func
(paren
)paren
suffix:semicolon
r_else
id|tce_init_pSeries
c_func
(paren
)paren
suffix:semicolon
id|pSeries_discover_pic
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; &lt;- pSeries_init_early()&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pSeries_progress
r_static
r_void
id|pSeries_progress
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
multiline_comment|/* use hex display if available */
r_if
c_cond
(paren
id|set_indicator
op_ne
id|RTAS_UNKNOWN_SERVICE
)paren
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
id|spin_lock
c_func
(paren
op_amp
id|progress_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Last write ended with newline, but we didn&squot;t print it since&n;&t; * it would just clear the bottom line of output. Print it now&n;&t; * instead.&n;&t; *&n;&t; * If no newline is pending, print a CR to start output at the&n;&t; * beginning of the line.&n;&t; */
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
)brace
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
r_static
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
DECL|function|pSeries_check_legacy_ioport
r_static
r_int
id|pSeries_check_legacy_ioport
c_func
(paren
r_int
r_int
id|baseport
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG&t;0x60
DECL|macro|FDC_BASE
mdefine_line|#define FDC_BASE&t;0x3f0
r_switch
c_cond
(paren
id|baseport
)paren
(brace
r_case
id|I8042_DATA_REG
suffix:colon
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;8042&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FDC_BASE
suffix:colon
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;fdc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called very early, MMU is off, device-tree isn&squot;t unflattened&n; */
r_extern
r_struct
id|machdep_calls
id|pSeries_md
suffix:semicolon
DECL|function|pSeries_probe
r_static
r_int
id|__init
id|pSeries_probe
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
id|PLATFORM_PSERIES
op_logical_and
id|platform
op_ne
id|PLATFORM_PSERIES_LPAR
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* if we have some ppc_md fixups for LPAR to do, do&n;&t; * it here ...&n;&t; */
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pSeries_md
r_struct
id|machdep_calls
id|__initdata
id|pSeries_md
op_assign
(brace
dot
id|probe
op_assign
id|pSeries_probe
comma
dot
id|setup_arch
op_assign
id|pSeries_setup_arch
comma
dot
id|init_early
op_assign
id|pSeries_init_early
comma
dot
id|get_cpuinfo
op_assign
id|pSeries_get_cpuinfo
comma
dot
id|log_error
op_assign
id|pSeries_log_error
comma
dot
id|pcibios_fixup
op_assign
id|pSeries_final_fixup
comma
dot
id|restart
op_assign
id|rtas_restart
comma
dot
id|power_off
op_assign
id|rtas_power_off
comma
dot
id|halt
op_assign
id|rtas_halt
comma
dot
id|panic
op_assign
id|rtas_os_term
comma
dot
id|cpu_die
op_assign
id|pSeries_cpu_die
comma
dot
id|get_boot_time
op_assign
id|pSeries_get_boot_time
comma
dot
id|get_rtc_time
op_assign
id|pSeries_get_rtc_time
comma
dot
id|set_rtc_time
op_assign
id|pSeries_set_rtc_time
comma
dot
id|calibrate_decr
op_assign
id|pSeries_calibrate_decr
comma
dot
id|progress
op_assign
id|pSeries_progress
comma
dot
id|check_legacy_ioport
op_assign
id|pSeries_check_legacy_ioport
comma
)brace
suffix:semicolon
eof
