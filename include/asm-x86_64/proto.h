macro_line|#ifndef _ASM_X8664_PROTO_H
DECL|macro|_ASM_X8664_PROTO_H
mdefine_line|#define _ASM_X8664_PROTO_H 1
macro_line|#include &lt;asm/ldt.h&gt;
multiline_comment|/* misc architecture specific prototypes */
r_struct
id|cpuinfo_x86
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|get_cpu_vendor
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
)paren
suffix:semicolon
r_extern
r_void
id|start_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pda_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|early_idt_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|init_memory_mapping
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|kernel_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|syscall_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_cstar_target
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_sysenter_target
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_acpi_tables
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iommu_hole_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|time_init_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_softirq_thunk
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|numa_setup
c_func
(paren
r_char
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_int
id|setup_early_printk
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|early_printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|early_identify_cpu
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
r_extern
r_int
id|k8_scan_nodes
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|numa_initmem_init
c_func
(paren
r_int
r_int
id|start_pfn
comma
r_int
r_int
id|end_pfn
)paren
suffix:semicolon
r_extern
r_int
r_int
id|numa_free_all_bootmem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reserve_bootmem_generic
c_func
(paren
r_int
r_int
id|phys
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|free_bootmem_generic
c_func
(paren
r_int
r_int
id|phys
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|load_gs_index
c_func
(paren
r_int
id|gs
)paren
suffix:semicolon
r_extern
r_int
r_int
id|end_pfn_map
suffix:semicolon
r_extern
r_int
r_int
id|cpu_initialized
suffix:semicolon
r_extern
r_void
id|show_trace
c_func
(paren
r_int
r_int
op_star
id|rsp
)paren
suffix:semicolon
r_extern
r_void
id|show_registers
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|exception_table_check
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|acpi_reserve_bootmem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|swap_low_mappings
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|oops_begin
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|die
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__die
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
suffix:semicolon
r_extern
r_void
id|__show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|map_syscall32
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_int
id|__map_syscall32
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_char
op_star
id|syscall32_page
suffix:semicolon
r_extern
r_void
id|syscall32_cpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_node_bootmem
c_func
(paren
r_int
id|nodeid
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|check_ioapic
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|check_efer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|unhandled_signal
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_void
id|select_idle_routine
c_func
(paren
r_const
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|swiotlb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|max_mapnr
suffix:semicolon
r_extern
r_int
r_int
id|end_pfn
suffix:semicolon
r_extern
r_int
r_int
id|table_start
comma
id|table_end
suffix:semicolon
r_extern
r_int
id|exception_trace
suffix:semicolon
r_extern
r_int
id|force_iommu
comma
id|no_iommu
suffix:semicolon
r_extern
r_int
id|using_apic_timer
suffix:semicolon
r_extern
r_int
id|disable_apic
suffix:semicolon
r_extern
r_int
id|cpu_khz
suffix:semicolon
r_extern
r_int
id|ioapic_force
suffix:semicolon
r_extern
r_int
id|skip_ioapic_setup
suffix:semicolon
r_extern
r_int
id|acpi_ht
suffix:semicolon
r_extern
r_int
id|acpi_disabled
suffix:semicolon
r_extern
r_int
id|fallback_aper_order
suffix:semicolon
r_extern
r_int
id|fallback_aper_force
suffix:semicolon
r_extern
r_int
id|iommu_aperture
suffix:semicolon
r_extern
r_int
id|iommu_aperture_disabled
suffix:semicolon
r_extern
r_int
id|iommu_aperture_allowed
suffix:semicolon
r_extern
r_int
id|fix_aperture
suffix:semicolon
r_extern
r_int
id|force_iommu
suffix:semicolon
r_extern
r_int
id|reboot_force
suffix:semicolon
r_extern
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|do_arch_prctl
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|code
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|round_up
mdefine_line|#define round_up(x,y) (((x) + (y) - 1) &amp; ~((y)-1))
DECL|macro|round_down
mdefine_line|#define round_down(x,y) ((x) &amp; ~((y)-1))
macro_line|#endif
eof
