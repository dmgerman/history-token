macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_MACHDEP_H
DECL|macro|_PPC_MACHDEP_H
mdefine_line|#define _PPC_MACHDEP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_APUS
macro_line|#include &lt;asm-m68k/machdep.h&gt;
macro_line|#endif
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|pci_bus
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|seq_file
suffix:semicolon
multiline_comment|/* We export this macro for external modules like Alsa to know if&n; * ppc_md.feature_call is implemented or not&n; */
DECL|macro|CONFIG_PPC_HAS_FEATURE_CALLS
mdefine_line|#define CONFIG_PPC_HAS_FEATURE_CALLS
DECL|struct|machdep_calls
r_struct
id|machdep_calls
(brace
DECL|member|setup_arch
r_void
(paren
op_star
id|setup_arch
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|show_cpuinfo
r_int
(paren
op_star
id|show_cpuinfo
)paren
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
DECL|member|show_percpuinfo
r_int
(paren
op_star
id|show_percpuinfo
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_int
id|i
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|irq_cannonicalize
r_int
r_int
(paren
op_star
id|irq_cannonicalize
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|init_IRQ
r_void
(paren
op_star
id|init_IRQ
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|get_irq
r_int
(paren
op_star
id|get_irq
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* A general init function, called by ppc_init in init/main.c.&n;&t;   May be NULL. */
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|restart
r_void
(paren
op_star
id|restart
)paren
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
DECL|member|power_off
r_void
(paren
op_star
id|power_off
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|halt
r_void
(paren
op_star
id|halt
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|idle
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|power_save
r_void
(paren
op_star
id|power_save
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|time_init
r_int
(paren
op_star
id|time_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL */
DECL|member|set_rtc_time
r_int
(paren
op_star
id|set_rtc_time
)paren
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
DECL|member|get_rtc_time
r_int
r_int
(paren
op_star
id|get_rtc_time
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|calibrate_decr
r_void
(paren
op_star
id|calibrate_decr
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|heartbeat
r_void
(paren
op_star
id|heartbeat
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|heartbeat_reset
r_int
r_int
id|heartbeat_reset
suffix:semicolon
DECL|member|heartbeat_count
r_int
r_int
id|heartbeat_count
suffix:semicolon
DECL|member|find_end_of_memory
r_int
r_int
(paren
op_star
id|find_end_of_memory
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|setup_io_mappings
r_void
(paren
op_star
id|setup_io_mappings
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|progress
r_void
(paren
op_star
id|progress
)paren
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|nvram_read_val
r_int
r_char
(paren
op_star
id|nvram_read_val
)paren
(paren
r_int
id|addr
)paren
suffix:semicolon
DECL|member|nvram_write_val
r_void
(paren
op_star
id|nvram_write_val
)paren
(paren
r_int
id|addr
comma
r_int
r_char
id|val
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * optional PCI &quot;hooks&quot;&n;&t; */
multiline_comment|/* Called after scanning the bus, before allocating resources */
DECL|member|pcibios_fixup
r_void
(paren
op_star
id|pcibios_fixup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Called after PPC generic resource fixup to perform&n;&t;   machine specific fixups */
DECL|member|pcibios_fixup_resources
r_void
(paren
op_star
id|pcibios_fixup_resources
)paren
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* Called for each PCI bus in the system when it&squot;s probed */
DECL|member|pcibios_fixup_bus
r_void
(paren
op_star
id|pcibios_fixup_bus
)paren
(paren
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
multiline_comment|/* Called when pci_enable_device() is called (initial=0) or&n;&t; * when a device with no assigned resource is found (initial=1).&n;&t; * Returns 0 to allow assignment/enabling of the device. */
DECL|member|pcibios_enable_device_hook
r_int
(paren
op_star
id|pcibios_enable_device_hook
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|initial
)paren
suffix:semicolon
multiline_comment|/* For interrupt routing */
DECL|member|pci_swizzle
r_int
r_char
(paren
op_star
id|pci_swizzle
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|pci_map_irq
r_int
(paren
op_star
id|pci_map_irq
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
r_char
comma
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/* Called in indirect_* to avoid touching devices */
DECL|member|pci_exclude_device
r_int
(paren
op_star
id|pci_exclude_device
)paren
(paren
r_int
r_char
comma
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/* Called at then very end of pcibios_init() */
DECL|member|pcibios_after_init
r_void
(paren
op_star
id|pcibios_after_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* this is for modules, since _machine can be a define -- Cort */
DECL|member|ppc_machine
r_int
id|ppc_machine
suffix:semicolon
multiline_comment|/* Motherboard/chipset features. This is a kind of general purpose&n;&t; * hook used to control some machine specific features (like reset&n;&t; * lines, chip power control, etc...).&n;&t; */
DECL|member|feature_call
r_int
(paren
op_star
id|feature_call
)paren
(paren
r_int
r_int
id|feature
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* functions for dealing with other cpus */
DECL|member|smp_ops
r_struct
id|smp_ops_t
op_star
id|smp_ops
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
suffix:semicolon
r_extern
r_struct
id|machdep_calls
id|ppc_md
suffix:semicolon
r_extern
r_char
id|cmd_line
(braket
l_int|512
)braket
suffix:semicolon
r_extern
r_void
id|setup_pci_ptrs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Power macintoshes have either a CUDA or a PMU controlling&n; * system reset, power, NVRAM, RTC.&n; */
DECL|enum|sys_ctrler_kind
r_typedef
r_enum
id|sys_ctrler_kind
(brace
DECL|enumerator|SYS_CTRLER_UNKNOWN
id|SYS_CTRLER_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|SYS_CTRLER_CUDA
id|SYS_CTRLER_CUDA
op_assign
l_int|1
comma
DECL|enumerator|SYS_CTRLER_PMU
id|SYS_CTRLER_PMU
op_assign
l_int|2
comma
DECL|typedef|sys_ctrler_t
)brace
id|sys_ctrler_t
suffix:semicolon
r_extern
id|sys_ctrler_t
id|sys_ctrler
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|struct|smp_ops_t
r_struct
id|smp_ops_t
(brace
DECL|member|message_pass
r_void
(paren
op_star
id|message_pass
)paren
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|kick_cpu
r_void
(paren
op_star
id|kick_cpu
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|setup_cpu
r_void
(paren
op_star
id|setup_cpu
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|space_timers
r_void
(paren
op_star
id|space_timers
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|take_timebase
r_void
(paren
op_star
id|take_timebase
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|give_timebase
r_void
(paren
op_star
id|give_timebase
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Poor default implementations */
r_extern
r_void
id|__devinit
id|smp_generic_give_timebase
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__devinit
id|smp_generic_take_timebase
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* _PPC_MACHDEP_H */
macro_line|#endif /* __KERNEL__ */
eof
