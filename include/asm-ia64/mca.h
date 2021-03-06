multiline_comment|/*&n; * File:&t;mca.h&n; * Purpose:&t;Machine check handling specific defines&n; *&n; * Copyright (C) 1999, 2004 Silicon Graphics, Inc.&n; * Copyright (C) Vijay Chander (vijay@engr.sgi.com)&n; * Copyright (C) Srinivasa Thirumalachar (sprasad@engr.sgi.com)&n; * Copyright (C) Russ Anderson (rja@sgi.com)&n; */
macro_line|#ifndef _ASM_IA64_MCA_H
DECL|macro|_ASM_IA64_MCA_H
mdefine_line|#define _ASM_IA64_MCA_H
DECL|macro|IA64_MCA_STACK_SIZE
mdefine_line|#define IA64_MCA_STACK_SIZE&t;8192
macro_line|#if !defined(__ASSEMBLY__)
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mca_asm.h&gt;
DECL|macro|IA64_MCA_RENDEZ_TIMEOUT
mdefine_line|#define IA64_MCA_RENDEZ_TIMEOUT&t;&t;(20 * 1000)&t;/* value in milliseconds - 20 seconds */
DECL|struct|ia64_fptr
r_typedef
r_struct
id|ia64_fptr
(brace
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
DECL|typedef|ia64_fptr_t
)brace
id|ia64_fptr_t
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
DECL|member|pal_min_state
id|u64
id|pal_min_state
suffix:semicolon
multiline_comment|/* from PAL in r17 */
DECL|member|proc_state_param
id|u64
id|proc_state_param
suffix:semicolon
multiline_comment|/* from PAL in r18. See SDV 2:268 11.3.2.1 */
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
multiline_comment|/* Per-CPU MCA state that is too big for normal per-CPU variables.  */
DECL|struct|ia64_mca_cpu
r_struct
id|ia64_mca_cpu
(brace
DECL|member|stack
id|u64
id|stack
(braket
id|IA64_MCA_STACK_SIZE
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* MCA memory-stack */
DECL|member|proc_state_dump
id|u64
id|proc_state_dump
(braket
l_int|512
)braket
suffix:semicolon
DECL|member|stackframe
id|u64
id|stackframe
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rbstore
id|u64
id|rbstore
(braket
id|IA64_MCA_STACK_SIZE
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* MCA reg.-backing store */
DECL|member|init_stack
id|u64
id|init_stack
(braket
id|KERNEL_STACK_SIZE
op_div
l_int|8
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Array of physical addresses of each CPU&squot;s MCA area.  */
r_extern
r_int
r_int
id|__per_cpu_mca
(braket
id|NR_CPUS
)braket
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
id|ia64_mca_cpu_init
c_func
(paren
r_void
op_star
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
id|ia64_mca_cmc_vector_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ia64_reg_MCA_extension
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ia64_unreg_MCA_extension
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_MCA_H */
eof
