multiline_comment|/*&n; * File:&t;mca.h&n; * Purpose:&t;Machine check handling specific defines&n; *&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) Vijay Chander (vijay@engr.sgi.com)&n; * Copyright (C) Srinivasa Thirumalachar (sprasad@engr.sgi.com)&n; */
macro_line|#ifndef _ASM_IA64_MCA_H
DECL|macro|_ASM_IA64_MCA_H
mdefine_line|#define _ASM_IA64_MCA_H
macro_line|#if !defined(__ASSEMBLY__)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* These are the return codes from all the IA64_MCA specific interfaces */
DECL|typedef|ia64_mca_return_code_t
r_typedef
r_int
id|ia64_mca_return_code_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|IA64_MCA_SUCCESS
id|IA64_MCA_SUCCESS
op_assign
l_int|0
comma
DECL|enumerator|IA64_MCA_FAILURE
id|IA64_MCA_FAILURE
op_assign
l_int|1
)brace
suffix:semicolon
DECL|macro|IA64_MCA_RENDEZ_TIMEOUT
mdefine_line|#define IA64_MCA_RENDEZ_TIMEOUT&t;&t;(100 * HZ)&t;/* 1000 milliseconds */
DECL|macro|IA64_CMC_INT_DISABLE
mdefine_line|#define IA64_CMC_INT_DISABLE&t;&t;0
DECL|macro|IA64_CMC_INT_ENABLE
mdefine_line|#define IA64_CMC_INT_ENABLE&t;&t;1
DECL|typedef|int_vector_t
r_typedef
id|u32
id|int_vector_t
suffix:semicolon
DECL|typedef|millisec_t
r_typedef
id|u64
id|millisec_t
suffix:semicolon
DECL|union|cmcv_reg_u
r_typedef
r_union
id|cmcv_reg_u
(brace
DECL|member|cmcv_regval
id|u64
id|cmcv_regval
suffix:semicolon
r_struct
(brace
DECL|member|cmcr_vector
id|u64
id|cmcr_vector
suffix:colon
l_int|8
suffix:semicolon
DECL|member|cmcr_reserved1
id|u64
id|cmcr_reserved1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cmcr_ignored1
id|u64
id|cmcr_ignored1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cmcr_reserved2
id|u64
id|cmcr_reserved2
suffix:colon
l_int|3
suffix:semicolon
DECL|member|cmcr_mask
id|u64
id|cmcr_mask
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cmcr_ignored2
id|u64
id|cmcr_ignored2
suffix:colon
l_int|47
suffix:semicolon
DECL|member|cmcv_reg_s
)brace
id|cmcv_reg_s
suffix:semicolon
DECL|typedef|cmcv_reg_t
)brace
id|cmcv_reg_t
suffix:semicolon
DECL|macro|cmcv_mask
mdefine_line|#define cmcv_mask&t;&t;cmcv_reg_s.cmcr_mask
DECL|macro|cmcv_vector
mdefine_line|#define cmcv_vector&t;&t;cmcv_reg_s.cmcr_vector
DECL|macro|IA64_MCA_UCMC_HANDLER_SIZE
mdefine_line|#define IA64_MCA_UCMC_HANDLER_SIZE&t;0x10
DECL|macro|IA64_INIT_HANDLER_SIZE
mdefine_line|#define IA64_INIT_HANDLER_SIZE&t;&t;0x10
r_enum
(brace
DECL|enumerator|IA64_MCA_RENDEZ_CHECKIN_NOTDONE
id|IA64_MCA_RENDEZ_CHECKIN_NOTDONE
op_assign
l_int|0x0
comma
DECL|enumerator|IA64_MCA_RENDEZ_CHECKIN_DONE
id|IA64_MCA_RENDEZ_CHECKIN_DONE
op_assign
l_int|0x1
)brace
suffix:semicolon
multiline_comment|/* Information maintained by the MC infrastructure */
DECL|struct|ia64_mc_info_s
r_typedef
r_struct
id|ia64_mc_info_s
(brace
DECL|member|imi_mca_handler
id|u64
id|imi_mca_handler
suffix:semicolon
DECL|member|imi_mca_handler_size
r_int
id|imi_mca_handler_size
suffix:semicolon
DECL|member|imi_monarch_init_handler
id|u64
id|imi_monarch_init_handler
suffix:semicolon
DECL|member|imi_monarch_init_handler_size
r_int
id|imi_monarch_init_handler_size
suffix:semicolon
DECL|member|imi_slave_init_handler
id|u64
id|imi_slave_init_handler
suffix:semicolon
DECL|member|imi_slave_init_handler_size
r_int
id|imi_slave_init_handler_size
suffix:semicolon
DECL|member|imi_rendez_checkin
id|u8
id|imi_rendez_checkin
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|typedef|ia64_mc_info_t
)brace
id|ia64_mc_info_t
suffix:semicolon
multiline_comment|/* Possible rendez states passed from SAL to OS during MCA&n; * handoff&n; */
r_enum
(brace
DECL|enumerator|IA64_MCA_RENDEZ_NOT_RQD
id|IA64_MCA_RENDEZ_NOT_RQD
op_assign
l_int|0x0
comma
DECL|enumerator|IA64_MCA_RENDEZ_DONE_WITHOUT_INIT
id|IA64_MCA_RENDEZ_DONE_WITHOUT_INIT
op_assign
l_int|0x1
comma
DECL|enumerator|IA64_MCA_RENDEZ_DONE_WITH_INIT
id|IA64_MCA_RENDEZ_DONE_WITH_INIT
op_assign
l_int|0x2
comma
DECL|enumerator|IA64_MCA_RENDEZ_FAILURE
id|IA64_MCA_RENDEZ_FAILURE
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
DECL|struct|ia64_mca_sal_to_os_state_s
r_typedef
r_struct
id|ia64_mca_sal_to_os_state_s
(brace
DECL|member|imsto_os_gp
id|u64
id|imsto_os_gp
suffix:semicolon
multiline_comment|/* GP of the os registered with the SAL */
DECL|member|imsto_pal_proc
id|u64
id|imsto_pal_proc
suffix:semicolon
multiline_comment|/* PAL_PROC entry point - physical addr */
DECL|member|imsto_sal_proc
id|u64
id|imsto_sal_proc
suffix:semicolon
multiline_comment|/* SAL_PROC entry point - physical addr */
DECL|member|imsto_sal_gp
id|u64
id|imsto_sal_gp
suffix:semicolon
multiline_comment|/* GP of the SAL - physical */
DECL|member|imsto_rendez_state
id|u64
id|imsto_rendez_state
suffix:semicolon
multiline_comment|/* Rendez state information */
DECL|member|imsto_sal_check_ra
id|u64
id|imsto_sal_check_ra
suffix:semicolon
multiline_comment|/* Return address in SAL_CHECK while going&n;&t;&t;&t;&t;&t;&t; * back to SAL from OS after MCA handling.&n;&t;&t;&t;&t;&t;&t; */
DECL|typedef|ia64_mca_sal_to_os_state_t
)brace
id|ia64_mca_sal_to_os_state_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|IA64_MCA_CORRECTED
id|IA64_MCA_CORRECTED
op_assign
l_int|0x0
comma
multiline_comment|/* Error has been corrected by OS_MCA */
DECL|enumerator|IA64_MCA_WARM_BOOT
id|IA64_MCA_WARM_BOOT
op_assign
op_minus
l_int|1
comma
multiline_comment|/* Warm boot of the system need from SAL */
DECL|enumerator|IA64_MCA_COLD_BOOT
id|IA64_MCA_COLD_BOOT
op_assign
op_minus
l_int|2
comma
multiline_comment|/* Cold boot of the system need from SAL */
DECL|enumerator|IA64_MCA_HALT
id|IA64_MCA_HALT
op_assign
op_minus
l_int|3
multiline_comment|/* System to be halted by SAL */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IA64_MCA_SAME_CONTEXT
id|IA64_MCA_SAME_CONTEXT
op_assign
l_int|0x0
comma
multiline_comment|/* SAL to return to same context */
DECL|enumerator|IA64_MCA_NEW_CONTEXT
id|IA64_MCA_NEW_CONTEXT
op_assign
op_minus
l_int|1
multiline_comment|/* SAL to return to new context */
)brace
suffix:semicolon
DECL|macro|MIN_STATE_AREA_SIZE
mdefine_line|#define MIN_STATE_AREA_SIZE     57
DECL|struct|ia64_mca_os_to_sal_state_s
r_typedef
r_struct
id|ia64_mca_os_to_sal_state_s
(brace
DECL|member|imots_os_status
id|u64
id|imots_os_status
suffix:semicolon
multiline_comment|/*   OS status to SAL as to what happened&n;&t;&t;&t;&t;&t;&t; *   with the MCA handling.&n;&t;&t;&t;&t;&t;&t; */
DECL|member|imots_sal_gp
id|u64
id|imots_sal_gp
suffix:semicolon
multiline_comment|/* GP of the SAL - physical */
DECL|member|imots_context
id|u64
id|imots_context
suffix:semicolon
multiline_comment|/* 0 if return to same context&n;&t;&t;&t;&t;&t;&t;   1 if return to new context */
DECL|member|imots_new_min_state
id|u64
op_star
id|imots_new_min_state
suffix:semicolon
multiline_comment|/* Pointer to structure containing&n;&t;&t;&t;&t;&t;&t; * new values of registers in the min state&n;&t;&t;&t;&t;&t;&t; * save area.&n;&t;&t;&t;&t;&t;&t; */
DECL|member|imots_sal_check_ra
id|u64
id|imots_sal_check_ra
suffix:semicolon
multiline_comment|/* Return address in SAL_CHECK while going&n;&t;&t;&t;&t;&t;&t; * back to SAL from OS after MCA handling.&n;&t;&t;&t;&t;&t;&t; */
DECL|typedef|ia64_mca_os_to_sal_state_t
)brace
id|ia64_mca_os_to_sal_state_t
suffix:semicolon
DECL|typedef|prfunc_t
r_typedef
r_int
(paren
op_star
id|prfunc_t
)paren
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
suffix:semicolon
r_extern
r_void
id|ia64_mca_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_os_mca_dispatch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_os_mca_dispatch_end
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_mca_ucmc_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_monarch_init_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_slave_init_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_mca_rendez_int_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ia64_mca_wakeup_int_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ia64_mca_cmc_int_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ia64_mca_cpe_int_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ia64_log_print
c_func
(paren
r_int
comma
id|prfunc_t
)paren
suffix:semicolon
r_extern
r_void
id|ia64_mca_cmc_vector_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ia64_mca_check_errors
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u64
id|ia64_log_get
c_func
(paren
r_int
comma
id|prfunc_t
)paren
suffix:semicolon
DECL|macro|PLATFORM_CALL
mdefine_line|#define PLATFORM_CALL(fn, args)&t;printk(&quot;Platform call TBD&bslash;n&quot;)
DECL|macro|platform_mem_dev_err_print
mdefine_line|#define platform_mem_dev_err_print ia64_log_prt_oem_data
DECL|macro|platform_pci_bus_err_print
mdefine_line|#define platform_pci_bus_err_print ia64_log_prt_oem_data
DECL|macro|platform_pci_comp_err_print
mdefine_line|#define platform_pci_comp_err_print ia64_log_prt_oem_data
DECL|macro|platform_plat_specific_err_print
mdefine_line|#define platform_plat_specific_err_print ia64_log_prt_oem_data
DECL|macro|platform_host_ctlr_err_print
mdefine_line|#define platform_host_ctlr_err_print ia64_log_prt_oem_data
DECL|macro|platform_plat_bus_err_print
mdefine_line|#define platform_plat_bus_err_print ia64_log_prt_oem_data
DECL|macro|MCA_TEST
macro_line|#undef&t;MCA_TEST
DECL|macro|IA64_MCA_DEBUG_INFO
macro_line|#undef IA64_MCA_DEBUG_INFO
macro_line|#if defined(IA64_MCA_DEBUG_INFO)
DECL|macro|IA64_MCA_DEBUG
macro_line|# define IA64_MCA_DEBUG(fmt...)&t;printk(fmt)
macro_line|#else
DECL|macro|IA64_MCA_DEBUG
macro_line|# define IA64_MCA_DEBUG(fmt...)
macro_line|#endif
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_MCA_H */
eof
