macro_line|#ifndef _ASM_IA64_UNWIND_H
DECL|macro|_ASM_IA64_UNWIND_H
mdefine_line|#define _ASM_IA64_UNWIND_H
multiline_comment|/*&n; * Copyright (C) 1999-2000, 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * A simple API for unwinding kernel stacks.  This is used for&n; * debugging and error reporting purposes.  The kernel doesn&squot;t need&n; * full-blown stack unwinding with all the bells and whitles, so there&n; * is not much point in implementing the full IA-64 unwind API (though&n; * it would of course be possible to implement the kernel API on top&n; * of it).&n; */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* forward declaration */
r_struct
id|switch_stack
suffix:semicolon
multiline_comment|/* forward declaration */
DECL|enum|unw_application_register
r_enum
id|unw_application_register
(brace
DECL|enumerator|UNW_AR_BSP
id|UNW_AR_BSP
comma
DECL|enumerator|UNW_AR_BSPSTORE
id|UNW_AR_BSPSTORE
comma
DECL|enumerator|UNW_AR_PFS
id|UNW_AR_PFS
comma
DECL|enumerator|UNW_AR_RNAT
id|UNW_AR_RNAT
comma
DECL|enumerator|UNW_AR_UNAT
id|UNW_AR_UNAT
comma
DECL|enumerator|UNW_AR_LC
id|UNW_AR_LC
comma
DECL|enumerator|UNW_AR_EC
id|UNW_AR_EC
comma
DECL|enumerator|UNW_AR_FPSR
id|UNW_AR_FPSR
comma
DECL|enumerator|UNW_AR_RSC
id|UNW_AR_RSC
comma
DECL|enumerator|UNW_AR_CCV
id|UNW_AR_CCV
)brace
suffix:semicolon
multiline_comment|/*&n; * The following declarations are private to the unwind&n; * implementation:&n; */
DECL|struct|unw_stack
r_struct
id|unw_stack
(brace
DECL|member|limit
r_int
r_int
id|limit
suffix:semicolon
DECL|member|top
r_int
r_int
id|top
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UNW_FLAG_INTERRUPT_FRAME
mdefine_line|#define UNW_FLAG_INTERRUPT_FRAME&t;(1UL &lt;&lt; 0)
multiline_comment|/*&n; * No user of this module should every access this structure directly&n; * as it is subject to change.  It is declared here solely so we can&n; * use automatic variables.&n; */
DECL|struct|unw_frame_info
r_struct
id|unw_frame_info
(brace
DECL|member|regstk
r_struct
id|unw_stack
id|regstk
suffix:semicolon
DECL|member|memstk
r_struct
id|unw_stack
id|memstk
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|hint
r_int
id|hint
suffix:semicolon
DECL|member|prev_script
r_int
id|prev_script
suffix:semicolon
multiline_comment|/* current frame info: */
DECL|member|bsp
r_int
r_int
id|bsp
suffix:semicolon
multiline_comment|/* backing store pointer value */
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* stack pointer value */
DECL|member|psp
r_int
r_int
id|psp
suffix:semicolon
multiline_comment|/* previous sp value */
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* instruction pointer value */
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
multiline_comment|/* current predicate values */
DECL|member|cfm_loc
r_int
r_int
op_star
id|cfm_loc
suffix:semicolon
multiline_comment|/* cfm save location (or NULL) */
DECL|member|pt
r_int
r_int
id|pt
suffix:semicolon
multiline_comment|/* struct pt_regs location */
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|sw
r_struct
id|switch_stack
op_star
id|sw
suffix:semicolon
multiline_comment|/* preserved state: */
DECL|member|bsp_loc
r_int
r_int
op_star
id|bsp_loc
suffix:semicolon
multiline_comment|/* previous bsp save location */
DECL|member|bspstore_loc
r_int
r_int
op_star
id|bspstore_loc
suffix:semicolon
DECL|member|pfs_loc
r_int
r_int
op_star
id|pfs_loc
suffix:semicolon
DECL|member|rnat_loc
r_int
r_int
op_star
id|rnat_loc
suffix:semicolon
DECL|member|rp_loc
r_int
r_int
op_star
id|rp_loc
suffix:semicolon
DECL|member|pri_unat_loc
r_int
r_int
op_star
id|pri_unat_loc
suffix:semicolon
DECL|member|unat_loc
r_int
r_int
op_star
id|unat_loc
suffix:semicolon
DECL|member|pr_loc
r_int
r_int
op_star
id|pr_loc
suffix:semicolon
DECL|member|lc_loc
r_int
r_int
op_star
id|lc_loc
suffix:semicolon
DECL|member|fpsr_loc
r_int
r_int
op_star
id|fpsr_loc
suffix:semicolon
DECL|struct|unw_ireg
r_struct
id|unw_ireg
(brace
DECL|member|loc
r_int
r_int
op_star
id|loc
suffix:semicolon
DECL|struct|unw_ireg_nat
r_struct
id|unw_ireg_nat
(brace
DECL|member|type
r_int
id|type
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* enum unw_nat_type */
DECL|member|off
r_int
r_int
id|off
suffix:colon
l_int|61
suffix:semicolon
multiline_comment|/* NaT word is at loc+nat.off */
DECL|member|nat
)brace
id|nat
suffix:semicolon
DECL|member|r4
DECL|member|r5
DECL|member|r6
DECL|member|r7
)brace
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
suffix:semicolon
DECL|member|b1_loc
DECL|member|b2_loc
DECL|member|b3_loc
DECL|member|b4_loc
DECL|member|b5_loc
r_int
r_int
op_star
id|b1_loc
comma
op_star
id|b2_loc
comma
op_star
id|b3_loc
comma
op_star
id|b4_loc
comma
op_star
id|b5_loc
suffix:semicolon
DECL|member|f2_loc
DECL|member|f3_loc
DECL|member|f4_loc
DECL|member|f5_loc
DECL|member|fr_loc
r_struct
id|ia64_fpreg
op_star
id|f2_loc
comma
op_star
id|f3_loc
comma
op_star
id|f4_loc
comma
op_star
id|f5_loc
comma
op_star
id|fr_loc
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The official API follows below:&n; */
multiline_comment|/*&n; * Initialize unwind support.&n; */
r_extern
r_void
id|unw_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unw_create_gate_table
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|unw_add_unwind_table
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|segment_base
comma
r_int
r_int
id|gp
comma
r_const
r_void
op_star
id|table_start
comma
r_const
r_void
op_star
id|table_end
)paren
suffix:semicolon
r_extern
r_void
id|unw_remove_unwind_table
(paren
r_void
op_star
id|handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Prepare to unwind blocked task t.&n; */
r_extern
r_void
id|unw_init_from_blocked_task
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*&n; * Prepare to unwind from interruption.  The pt-regs and switch-stack structures must have&n; * be &quot;adjacent&quot; (no state modifications between pt-regs and switch-stack).&n; */
r_extern
r_void
id|unw_init_from_interruption
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|t
comma
r_struct
id|pt_regs
op_star
id|pt
comma
r_struct
id|switch_stack
op_star
id|sw
)paren
suffix:semicolon
r_extern
r_void
id|unw_init_frame_info
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|t
comma
r_struct
id|switch_stack
op_star
id|sw
)paren
suffix:semicolon
multiline_comment|/*&n; * Prepare to unwind the currently running thread.&n; */
r_extern
r_void
id|unw_init_running
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_void
op_star
id|arg
)paren
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; * Unwind to previous to frame.  Returns 0 if successful, negative&n; * number in case of an error.&n; */
r_extern
r_int
id|unw_unwind
(paren
r_struct
id|unw_frame_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; * Unwind until the return pointer is in user-land (or until an error&n; * occurs).  Returns 0 if successful, negative number in case of&n; * error.&n; */
r_extern
r_int
id|unw_unwind_to_user
(paren
r_struct
id|unw_frame_info
op_star
id|info
)paren
suffix:semicolon
DECL|macro|unw_is_intr_frame
mdefine_line|#define unw_is_intr_frame(info)&t;(((info)-&gt;flags &amp; UNW_FLAG_INTERRUPT_FRAME) != 0)
r_static
r_inline
r_int
DECL|function|unw_get_ip
id|unw_get_ip
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
(paren
id|info
)paren
op_member_access_from_pointer
id|ip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_get_sp
id|unw_get_sp
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
(paren
id|info
)paren
op_member_access_from_pointer
id|sp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_get_psp
id|unw_get_psp
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
(paren
id|info
)paren
op_member_access_from_pointer
id|psp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_get_bsp
id|unw_get_bsp
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
(paren
id|info
)paren
op_member_access_from_pointer
id|bsp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_get_cfm
id|unw_get_cfm
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
op_star
(paren
id|info
)paren
op_member_access_from_pointer
id|cfm_loc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_set_cfm
id|unw_set_cfm
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
id|val
)paren
(brace
op_star
(paren
id|info
)paren
op_member_access_from_pointer
id|cfm_loc
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_get_rp
id|unw_get_rp
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;rp_loc
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|val
op_assign
op_star
id|info-&gt;rp_loc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|unw_access_gr
(paren
r_struct
id|unw_frame_info
op_star
comma
r_int
comma
r_int
r_int
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|unw_access_br
(paren
r_struct
id|unw_frame_info
op_star
comma
r_int
comma
r_int
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|unw_access_fr
(paren
r_struct
id|unw_frame_info
op_star
comma
r_int
comma
r_struct
id|ia64_fpreg
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|unw_access_ar
(paren
r_struct
id|unw_frame_info
op_star
comma
r_int
comma
r_int
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|unw_access_pr
(paren
r_struct
id|unw_frame_info
op_star
comma
r_int
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|unw_set_gr
id|unw_set_gr
(paren
r_struct
id|unw_frame_info
op_star
id|i
comma
r_int
id|n
comma
r_int
r_int
id|v
comma
r_char
id|nat
)paren
(brace
r_return
id|unw_access_gr
c_func
(paren
id|i
comma
id|n
comma
op_amp
id|v
comma
op_amp
id|nat
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_set_br
id|unw_set_br
(paren
r_struct
id|unw_frame_info
op_star
id|i
comma
r_int
id|n
comma
r_int
r_int
id|v
)paren
(brace
r_return
id|unw_access_br
c_func
(paren
id|i
comma
id|n
comma
op_amp
id|v
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_set_fr
id|unw_set_fr
(paren
r_struct
id|unw_frame_info
op_star
id|i
comma
r_int
id|n
comma
r_struct
id|ia64_fpreg
id|v
)paren
(brace
r_return
id|unw_access_fr
c_func
(paren
id|i
comma
id|n
comma
op_amp
id|v
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_set_ar
id|unw_set_ar
(paren
r_struct
id|unw_frame_info
op_star
id|i
comma
r_int
id|n
comma
r_int
r_int
id|v
)paren
(brace
r_return
id|unw_access_ar
c_func
(paren
id|i
comma
id|n
comma
op_amp
id|v
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|unw_set_pr
id|unw_set_pr
(paren
r_struct
id|unw_frame_info
op_star
id|i
comma
r_int
r_int
id|v
)paren
(brace
r_return
id|unw_access_pr
c_func
(paren
id|i
comma
op_amp
id|v
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|unw_get_gr
mdefine_line|#define unw_get_gr(i,n,v,nat)&t;unw_access_gr(i,n,v,nat,0)
DECL|macro|unw_get_br
mdefine_line|#define unw_get_br(i,n,v)&t;unw_access_br(i,n,v,0)
DECL|macro|unw_get_fr
mdefine_line|#define unw_get_fr(i,n,v)&t;unw_access_fr(i,n,v,0)
DECL|macro|unw_get_ar
mdefine_line|#define unw_get_ar(i,n,v)&t;unw_access_ar(i,n,v,0)
DECL|macro|unw_get_pr
mdefine_line|#define unw_get_pr(i,v)&t;&t;unw_access_pr(i,v,0)
macro_line|#endif /* _ASM_UNWIND_H */
eof
