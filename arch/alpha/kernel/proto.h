macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Prototypes of functions used across modules here in this directory.  */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char  *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vip
mdefine_line|#define vip&t;volatile int *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int   *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long  *
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|pci_controller
suffix:semicolon
multiline_comment|/* core_apecs.c */
r_extern
r_struct
id|pci_ops
id|apecs_pci_ops
suffix:semicolon
r_extern
r_void
id|apecs_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|apecs_pci_clr_err
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|apecs_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|apecs_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* core_cia.c */
r_extern
r_struct
id|pci_ops
id|cia_pci_ops
suffix:semicolon
r_extern
r_void
id|cia_init_pci
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cia_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pyxis_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cia_kill_arch
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|cia_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|cia_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* core_irongate.c */
r_extern
r_struct
id|pci_ops
id|irongate_pci_ops
suffix:semicolon
r_extern
r_int
id|irongate_pci_clr_err
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irongate_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irongate_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|irongate_pci_tbi
mdefine_line|#define irongate_pci_tbi ((void *)0)
multiline_comment|/* core_lca.c */
r_extern
r_struct
id|pci_ops
id|lca_pci_ops
suffix:semicolon
r_extern
r_void
id|lca_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lca_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|lca_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* core_marvel.c */
r_extern
r_struct
id|pci_ops
id|marvel_pci_ops
suffix:semicolon
r_extern
r_void
id|marvel_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|marvel_kill_arch
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|marvel_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|marvel_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
r_extern
r_int
id|marvel_pa_to_nid
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|marvel_cpuid_to_nid
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|marvel_node_mem_start
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|marvel_node_mem_size
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|_alpha_agp_info
op_star
id|marvel_agp_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|io7
op_star
id|marvel_find_io7
c_func
(paren
r_int
id|pe
)paren
suffix:semicolon
r_struct
id|io7
op_star
id|marvel_next_io7
c_func
(paren
r_struct
id|io7
op_star
id|prev
)paren
suffix:semicolon
r_void
id|io7_clear_errors
c_func
(paren
r_struct
id|io7
op_star
id|io7
)paren
suffix:semicolon
multiline_comment|/* core_mcpcia.c */
r_extern
r_struct
id|pci_ops
id|mcpcia_pci_ops
suffix:semicolon
r_extern
r_void
id|mcpcia_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mcpcia_init_hoses
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mcpcia_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mcpcia_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* core_polaris.c */
r_extern
r_struct
id|pci_ops
id|polaris_pci_ops
suffix:semicolon
r_extern
r_int
id|polaris_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|polaris_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|polaris_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|polaris_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|polaris_pci_tbi
mdefine_line|#define polaris_pci_tbi ((void *)0)
multiline_comment|/* core_t2.c */
r_extern
r_struct
id|pci_ops
id|t2_pci_ops
suffix:semicolon
r_extern
r_void
id|t2_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|t2_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|t2_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* core_titan.c */
r_extern
r_struct
id|pci_ops
id|titan_pci_ops
suffix:semicolon
r_extern
r_void
id|titan_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|titan_kill_arch
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|titan_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|titan_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
r_extern
r_struct
id|_alpha_agp_info
op_star
id|titan_agp_info
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* core_tsunami.c */
r_extern
r_struct
id|pci_ops
id|tsunami_pci_ops
suffix:semicolon
r_extern
r_void
id|tsunami_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tsunami_kill_arch
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tsunami_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tsunami_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* core_wildfire.c */
r_extern
r_struct
id|pci_ops
id|wildfire_pci_ops
suffix:semicolon
r_extern
r_void
id|wildfire_init_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wildfire_kill_arch
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wildfire_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|wildfire_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
id|dma_addr_t
)paren
suffix:semicolon
r_extern
r_int
id|wildfire_pa_to_nid
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|wildfire_cpuid_to_nid
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_node_mem_start
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|wildfire_node_mem_size
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* setup.c */
r_extern
r_int
r_int
id|srm_hae
suffix:semicolon
r_extern
r_int
id|boot_cpuid
suffix:semicolon
multiline_comment|/* srmcons.c */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM)
r_extern
r_void
id|register_srm_console
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unregister_srm_console
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|register_srm_console
mdefine_line|#define register_srm_console()
DECL|macro|unregister_srm_console
mdefine_line|#define unregister_srm_console()
macro_line|#endif
multiline_comment|/* smp.c */
r_extern
r_void
id|setup_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|handle_ipi
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|smp_percpu_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* bios32.c */
multiline_comment|/* extern void reset_for_srm(void); */
multiline_comment|/* time.c */
r_extern
r_void
id|timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|common_init_rtc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|est_cycle_freq
suffix:semicolon
multiline_comment|/* smc37c93x.c */
r_extern
r_void
id|SMC93x_Init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* smc37c669.c */
r_extern
r_void
id|SMC669_Init
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* es1888.c */
r_extern
r_void
id|es1888_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* ns87312.c */
r_extern
r_void
id|ns87312_enable_ide
c_func
(paren
r_int
id|ide_base
)paren
suffix:semicolon
multiline_comment|/* ../lib/fpreg.c */
r_extern
r_void
id|alpha_write_fp_reg
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
r_int
id|alpha_read_fp_reg
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
multiline_comment|/* head.S */
r_extern
r_void
id|wrmces
c_func
(paren
r_int
r_int
id|mces
)paren
suffix:semicolon
r_extern
r_void
id|cserve_ena
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|cserve_dis
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__smp_callin
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* entry.S */
r_extern
r_void
id|entArith
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|entIF
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|entInt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|entMM
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|entSys
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|entUna
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|entDbg
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* process.c */
r_extern
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
multiline_comment|/* ptrace.c */
r_extern
r_int
id|ptrace_set_bpt
(paren
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_cancel_bpt
(paren
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
multiline_comment|/* traps.c */
r_extern
r_void
id|dik_show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
op_star
id|r9_15
)paren
suffix:semicolon
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* sys_titan.c */
r_extern
r_void
id|titan_dispatch_irqs
c_func
(paren
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* ../mm/init.c */
r_extern
r_void
id|switch_to_system_map
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|srm_paging_stop
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* ../mm/remap.c */
r_extern
r_int
id|__alpha_remap_area_pages
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* irq.c */
macro_line|#ifdef CONFIG_SMP
DECL|macro|mcheck_expected
mdefine_line|#define mcheck_expected(cpu)&t;(cpu_data[cpu].mcheck_expected)
DECL|macro|mcheck_taken
mdefine_line|#define mcheck_taken(cpu)&t;(cpu_data[cpu].mcheck_taken)
DECL|macro|mcheck_extra
mdefine_line|#define mcheck_extra(cpu)&t;(cpu_data[cpu].mcheck_extra)
macro_line|#else
DECL|struct|mcheck_info
r_extern
r_struct
id|mcheck_info
(brace
DECL|member|expected
r_int
r_char
id|expected
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|member|taken
r_int
r_char
id|taken
suffix:semicolon
DECL|member|extra
r_int
r_char
id|extra
suffix:semicolon
)brace
id|__mcheck_info
suffix:semicolon
DECL|macro|mcheck_expected
mdefine_line|#define mcheck_expected(cpu)&t;((void)(cpu), __mcheck_info.expected)
DECL|macro|mcheck_taken
mdefine_line|#define mcheck_taken(cpu)&t;((void)(cpu), __mcheck_info.taken)
DECL|macro|mcheck_extra
mdefine_line|#define mcheck_extra(cpu)&t;((void)(cpu), __mcheck_info.extra)
macro_line|#endif
DECL|macro|DEBUG_MCHECK
mdefine_line|#define DEBUG_MCHECK 0          /* 0 = minimal, 1 = debug, 2 = debug+dump.  */
r_extern
r_void
id|process_mcheck_info
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_const
r_char
op_star
id|machine
comma
r_int
id|expected
)paren
suffix:semicolon
eof
