macro_line|#ifndef _ASM_X8664_PROTO_H
DECL|macro|_ASM_X8664_PROTO_H
mdefine_line|#define _ASM_X8664_PROTO_H 1
multiline_comment|/* misc architecture specific prototypes */
r_struct
id|cpuinfo_x86
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
r_void
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
r_void
id|ia32_cstar_target
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|calibrate_delay
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sys_ni_syscall
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
id|do_softirq_thunk
c_func
(paren
r_void
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
r_int
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
r_int
r_int
id|start_pfn
comma
id|end_pfn
suffix:semicolon
r_extern
r_void
id|show_stack
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
id|exception_table_check
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|acpi_boot_init
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_int
id|iommu_setup
c_func
(paren
r_char
op_star
id|opt
)paren
suffix:semicolon
DECL|macro|round_up
mdefine_line|#define round_up(x,y) (((x) + (y) - 1) &amp; ~((y)-1))
DECL|macro|round_down
mdefine_line|#define round_down(x,y) ((x) &amp; ~((y)-1))
macro_line|#endif
eof
