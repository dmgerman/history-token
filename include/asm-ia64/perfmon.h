multiline_comment|/*&n; * Copyright (C) 2001-2003 Hewlett-Packard Co&n; *               Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_PERFMON_H
DECL|macro|_ASM_IA64_PERFMON_H
mdefine_line|#define _ASM_IA64_PERFMON_H
multiline_comment|/*&n; * perfmon comamnds supported on all CPU models&n; */
DECL|macro|PFM_WRITE_PMCS
mdefine_line|#define PFM_WRITE_PMCS&t;&t;0x01
DECL|macro|PFM_WRITE_PMDS
mdefine_line|#define PFM_WRITE_PMDS&t;&t;0x02
DECL|macro|PFM_READ_PMDS
mdefine_line|#define PFM_READ_PMDS&t;&t;0x03
DECL|macro|PFM_STOP
mdefine_line|#define PFM_STOP&t;&t;0x04
DECL|macro|PFM_START
mdefine_line|#define PFM_START&t;&t;0x05
DECL|macro|PFM_ENABLE
mdefine_line|#define PFM_ENABLE&t;&t;0x06 /* obsolete */
DECL|macro|PFM_DISABLE
mdefine_line|#define PFM_DISABLE&t;&t;0x07 /* obsolete */
DECL|macro|PFM_CREATE_CONTEXT
mdefine_line|#define PFM_CREATE_CONTEXT&t;0x08
DECL|macro|PFM_DESTROY_CONTEXT
mdefine_line|#define PFM_DESTROY_CONTEXT&t;0x09 /* obsolete use close() */
DECL|macro|PFM_RESTART
mdefine_line|#define PFM_RESTART&t;&t;0x0a
DECL|macro|PFM_PROTECT_CONTEXT
mdefine_line|#define PFM_PROTECT_CONTEXT&t;0x0b /* obsolete */
DECL|macro|PFM_GET_FEATURES
mdefine_line|#define PFM_GET_FEATURES&t;0x0c
DECL|macro|PFM_DEBUG
mdefine_line|#define PFM_DEBUG&t;&t;0x0d
DECL|macro|PFM_UNPROTECT_CONTEXT
mdefine_line|#define PFM_UNPROTECT_CONTEXT&t;0x0e /* obsolete */
DECL|macro|PFM_GET_PMC_RESET_VAL
mdefine_line|#define PFM_GET_PMC_RESET_VAL&t;0x0f
DECL|macro|PFM_LOAD_CONTEXT
mdefine_line|#define PFM_LOAD_CONTEXT&t;0x10
DECL|macro|PFM_UNLOAD_CONTEXT
mdefine_line|#define PFM_UNLOAD_CONTEXT&t;0x11
multiline_comment|/*&n; * PMU model specific commands (may not be supported on all PMU models)&n; */
DECL|macro|PFM_WRITE_IBRS
mdefine_line|#define PFM_WRITE_IBRS&t;&t;0x20
DECL|macro|PFM_WRITE_DBRS
mdefine_line|#define PFM_WRITE_DBRS&t;&t;0x21
multiline_comment|/*&n; * context flags&n; */
DECL|macro|PFM_FL_NOTIFY_BLOCK
mdefine_line|#define PFM_FL_NOTIFY_BLOCK    &t; 0x01&t;/* block task on user level notifications */
DECL|macro|PFM_FL_SYSTEM_WIDE
mdefine_line|#define PFM_FL_SYSTEM_WIDE&t; 0x02&t;/* create a system wide context */
DECL|macro|PFM_FL_UNSECURE
mdefine_line|#define PFM_FL_UNSECURE&t;&t; 0x04   /* allow unsecure monitoring for non self-monitoring task */
DECL|macro|PFM_FL_OVFL_NO_MSG
mdefine_line|#define PFM_FL_OVFL_NO_MSG&t; 0x80   /* do not post overflow/end messages for notification */
multiline_comment|/*&n; * event set flags&n; */
DECL|macro|PFM_SETFL_EXCL_IDLE
mdefine_line|#define PFM_SETFL_EXCL_IDLE      0x01   /* exclude idle task (syswide only) XXX: DO NOT USE YET */
multiline_comment|/*&n; * PMC flags&n; */
DECL|macro|PFM_REGFL_OVFL_NOTIFY
mdefine_line|#define PFM_REGFL_OVFL_NOTIFY&t;0x1&t;/* send notification on overflow */
DECL|macro|PFM_REGFL_RANDOM
mdefine_line|#define PFM_REGFL_RANDOM&t;0x2&t;/* randomize sampling interval   */
multiline_comment|/*&n; * PMD/PMC/IBR/DBR return flags (ignored on input)&n; *&n; * Those flags are used on output and must be checked in case EAGAIN is returned&n; * by any of the calls using a pfarg_reg_t or pfarg_dbreg_t structure.&n; */
DECL|macro|PFM_REG_RETFL_NOTAVAIL
mdefine_line|#define PFM_REG_RETFL_NOTAVAIL&t;(1UL&lt;&lt;31) /* set if register is implemented but not available */
DECL|macro|PFM_REG_RETFL_EINVAL
mdefine_line|#define PFM_REG_RETFL_EINVAL&t;(1UL&lt;&lt;30) /* set if register entry is invalid */
DECL|macro|PFM_REG_RETFL_MASK
mdefine_line|#define PFM_REG_RETFL_MASK&t;(PFM_REG_RETFL_NOTAVAIL|PFM_REG_RETFL_EINVAL)
DECL|macro|PFM_REG_HAS_ERROR
mdefine_line|#define PFM_REG_HAS_ERROR(flag)&t;(((flag) &amp; PFM_REG_RETFL_MASK) != 0)
DECL|typedef|pfm_uuid_t
r_typedef
r_int
r_char
id|pfm_uuid_t
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* custom sampling buffer identifier type */
multiline_comment|/*&n; * Request structure used to define a context&n; */
r_typedef
r_struct
(brace
DECL|member|ctx_smpl_buf_id
id|pfm_uuid_t
id|ctx_smpl_buf_id
suffix:semicolon
multiline_comment|/* which buffer format to use (if needed) */
DECL|member|ctx_flags
r_int
r_int
id|ctx_flags
suffix:semicolon
multiline_comment|/* noblock/block */
DECL|member|ctx_nextra_sets
r_int
r_int
id|ctx_nextra_sets
suffix:semicolon
multiline_comment|/* number of extra event sets (you always get 1) */
DECL|member|ctx_fd
r_int
id|ctx_fd
suffix:semicolon
multiline_comment|/* return arg: unique identification for context */
DECL|member|ctx_smpl_vaddr
r_void
op_star
id|ctx_smpl_vaddr
suffix:semicolon
multiline_comment|/* return arg: virtual address of sampling buffer, is used */
DECL|member|ctx_reserved
r_int
r_int
id|ctx_reserved
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* for future use */
DECL|typedef|pfarg_context_t
)brace
id|pfarg_context_t
suffix:semicolon
multiline_comment|/*&n; * Request structure used to write/read a PMC or PMD&n; */
r_typedef
r_struct
(brace
DECL|member|reg_num
r_int
r_int
id|reg_num
suffix:semicolon
multiline_comment|/* which register                             */
DECL|member|reg_set
r_int
r_int
id|reg_set
suffix:semicolon
multiline_comment|/* event set for this register                */
DECL|member|reg_value
r_int
r_int
id|reg_value
suffix:semicolon
multiline_comment|/* initial pmc/pmd value                      */
DECL|member|reg_flags
r_int
r_int
id|reg_flags
suffix:semicolon
multiline_comment|/* input: pmc/pmd flags, return: reg error    */
DECL|member|reg_long_reset
r_int
r_int
id|reg_long_reset
suffix:semicolon
multiline_comment|/* reset after buffer overflow notification   */
DECL|member|reg_short_reset
r_int
r_int
id|reg_short_reset
suffix:semicolon
multiline_comment|/* reset after counter overflow               */
DECL|member|reg_reset_pmds
r_int
r_int
id|reg_reset_pmds
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which other counters to reset on overflow  */
DECL|member|reg_random_seed
r_int
r_int
id|reg_random_seed
suffix:semicolon
multiline_comment|/* seed value when randomization is used      */
DECL|member|reg_random_mask
r_int
r_int
id|reg_random_mask
suffix:semicolon
multiline_comment|/* bitmask used to limit random value         */
DECL|member|reg_last_reset_val
r_int
r_int
id|reg_last_reset_val
suffix:semicolon
multiline_comment|/* return: PMD last reset value               */
DECL|member|reg_smpl_pmds
r_int
r_int
id|reg_smpl_pmds
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which pmds are accessed when PMC overflows */
DECL|member|reg_smpl_eventid
r_int
r_int
id|reg_smpl_eventid
suffix:semicolon
multiline_comment|/* opaque sampling event identifier           */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* for future use                             */
DECL|typedef|pfarg_reg_t
)brace
id|pfarg_reg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dbreg_num
r_int
r_int
id|dbreg_num
suffix:semicolon
multiline_comment|/* which debug register        */
DECL|member|dbreg_set
r_int
r_int
id|dbreg_set
suffix:semicolon
multiline_comment|/* event set for this register */
DECL|member|dbreg_value
r_int
r_int
id|dbreg_value
suffix:semicolon
multiline_comment|/* value for debug register    */
DECL|member|dbreg_flags
r_int
r_int
id|dbreg_flags
suffix:semicolon
multiline_comment|/* return: dbreg error         */
DECL|member|dbreg_reserved
r_int
r_int
id|dbreg_reserved
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* for future use              */
DECL|typedef|pfarg_dbreg_t
)brace
id|pfarg_dbreg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ft_version
r_int
r_int
id|ft_version
suffix:semicolon
multiline_comment|/* perfmon: major [16-31], minor [0-15] */
DECL|member|ft_reserved
r_int
r_int
id|ft_reserved
suffix:semicolon
multiline_comment|/* reserved for future use              */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* for future use                       */
DECL|typedef|pfarg_features_t
)brace
id|pfarg_features_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|load_pid
id|pid_t
id|load_pid
suffix:semicolon
multiline_comment|/* process to load the context into */
DECL|member|load_set
r_int
r_int
id|load_set
suffix:semicolon
multiline_comment|/* first event set to load          */
DECL|member|load_reserved
r_int
r_int
id|load_reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* for future use                   */
DECL|typedef|pfarg_load_t
)brace
id|pfarg_load_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|msg_type
r_int
id|msg_type
suffix:semicolon
multiline_comment|/* generic message header */
DECL|member|msg_ctx_fd
r_int
id|msg_ctx_fd
suffix:semicolon
multiline_comment|/* generic message header */
DECL|member|msg_tstamp
r_int
r_int
id|msg_tstamp
suffix:semicolon
multiline_comment|/* for perf tuning */
DECL|member|msg_active_set
r_int
r_int
id|msg_active_set
suffix:semicolon
multiline_comment|/* active set at the time of overflow */
DECL|member|msg_ovfl_pmds
r_int
r_int
id|msg_ovfl_pmds
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which PMDs overflowed */
DECL|typedef|pfm_ovfl_msg_t
)brace
id|pfm_ovfl_msg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|msg_type
r_int
id|msg_type
suffix:semicolon
multiline_comment|/* generic message header */
DECL|member|msg_ctx_fd
r_int
id|msg_ctx_fd
suffix:semicolon
multiline_comment|/* generic message header */
DECL|member|msg_tstamp
r_int
r_int
id|msg_tstamp
suffix:semicolon
multiline_comment|/* for perf tuning */
DECL|typedef|pfm_end_msg_t
)brace
id|pfm_end_msg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|msg_type
r_int
id|msg_type
suffix:semicolon
multiline_comment|/* type of the message */
DECL|member|msg_ctx_fd
r_int
id|msg_ctx_fd
suffix:semicolon
multiline_comment|/* unique identifier for the context */
DECL|member|msg_tstamp
r_int
r_int
id|msg_tstamp
suffix:semicolon
multiline_comment|/* for perf tuning */
DECL|typedef|pfm_gen_msg_t
)brace
id|pfm_gen_msg_t
suffix:semicolon
DECL|macro|PFM_MSG_OVFL
mdefine_line|#define PFM_MSG_OVFL&t;1&t;/* an overflow happened */
DECL|macro|PFM_MSG_END
mdefine_line|#define PFM_MSG_END&t;2&t;/* task to which context was attached ended */
r_typedef
r_union
(brace
DECL|member|pfm_ovfl_msg
id|pfm_ovfl_msg_t
id|pfm_ovfl_msg
suffix:semicolon
DECL|member|pfm_end_msg
id|pfm_end_msg_t
id|pfm_end_msg
suffix:semicolon
DECL|member|pfm_gen_msg
id|pfm_gen_msg_t
id|pfm_gen_msg
suffix:semicolon
DECL|typedef|pfm_msg_t
)brace
id|pfm_msg_t
suffix:semicolon
multiline_comment|/*&n; * Define the version numbers for both perfmon as a whole and the sampling buffer format.&n; */
DECL|macro|PFM_VERSION_MAJ
mdefine_line|#define PFM_VERSION_MAJ&t;&t; 2U
DECL|macro|PFM_VERSION_MIN
mdefine_line|#define PFM_VERSION_MIN&t;&t; 0U
DECL|macro|PFM_SMPL_HDR_VERSION_MAJ
mdefine_line|#define PFM_SMPL_HDR_VERSION_MAJ 2U
DECL|macro|PFM_SMPL_HDR_VERSION_MIN
mdefine_line|#define PFM_SMPL_HDR_VERSION_MIN 0U
DECL|macro|PFM_VERSION
mdefine_line|#define PFM_VERSION&t;&t; (((PFM_VERSION_MAJ&amp;0xffff)&lt;&lt;16)|(PFM_VERSION_MIN &amp; 0xffff))
DECL|macro|PFM_VERSION_MAJOR
mdefine_line|#define PFM_VERSION_MAJOR(x)&t; (((x)&gt;&gt;16) &amp; 0xffff)
DECL|macro|PFM_VERSION_MINOR
mdefine_line|#define PFM_VERSION_MINOR(x)&t; ((x) &amp; 0xffff)
multiline_comment|/*&n; * miscellaneous architected definitions&n; */
DECL|macro|PMU_FIRST_COUNTER
mdefine_line|#define PMU_FIRST_COUNTER&t;4&t;/* first counting monitor (PMC/PMD) */
DECL|macro|PMU_MAX_PMCS
mdefine_line|#define PMU_MAX_PMCS&t;&t;256&t;/* maximum architected number of PMC registers */
DECL|macro|PMU_MAX_PMDS
mdefine_line|#define PMU_MAX_PMDS&t;&t;256&t;/* maximum architected number of PMD registers */
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|perfmonctl
c_func
(paren
r_int
id|fd
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
comma
r_int
id|narg
)paren
suffix:semicolon
r_extern
r_void
id|pfm_save_regs
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pfm_load_regs
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pfm_exit_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pfm_use_debug_registers
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pfm_release_debug_registers
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pfm_syst_wide_update_task
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
r_int
id|info
comma
r_int
id|is_ctxswin
)paren
suffix:semicolon
r_extern
r_void
id|pfm_inherit
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|pfm_init_percpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pfm_handle_work
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Reset PMD register flags&n; */
DECL|macro|PFM_PMD_NO_RESET
mdefine_line|#define PFM_PMD_NO_RESET&t;0
DECL|macro|PFM_PMD_LONG_RESET
mdefine_line|#define PFM_PMD_LONG_RESET&t;1
DECL|macro|PFM_PMD_SHORT_RESET
mdefine_line|#define PFM_PMD_SHORT_RESET&t;2
r_typedef
r_struct
(brace
DECL|member|notify_user
r_int
r_int
id|notify_user
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* notify user program of overflow                           */
DECL|member|reset_pmds
r_int
r_int
id|reset_pmds
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* PFM_PMD_NO_RESET, PFM_PMD_LONG_RESET, PFM_PMD_SHORT_RESET */
DECL|member|block
r_int
r_int
id|block
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* block monitored task on kernel exit                       */
DECL|member|stop_monitoring
r_int
r_int
id|stop_monitoring
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* will mask monitoring via PMCx.plm                         */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:colon
l_int|26
suffix:semicolon
multiline_comment|/* for future use                                            */
DECL|typedef|pfm_ovfl_ctrl_t
)brace
id|pfm_ovfl_ctrl_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ovfl_pmds
r_int
r_int
id|ovfl_pmds
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* bitmask of overflowed pmds                            */
DECL|member|ovfl_notify
r_int
r_int
id|ovfl_notify
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* bitmask of overflow pmds which asked for notification */
DECL|member|pmd_value
r_int
r_int
id|pmd_value
suffix:semicolon
multiline_comment|/* current 64-bit value of 1st pmd which overflowed      */
DECL|member|pmd_last_reset
r_int
r_int
id|pmd_last_reset
suffix:semicolon
multiline_comment|/* last reset value of 1st pmd which overflowed          */
DECL|member|pmd_eventid
r_int
r_int
id|pmd_eventid
suffix:semicolon
multiline_comment|/* eventid associated with 1st pmd which overflowed      */
DECL|member|active_set
r_int
r_int
id|active_set
suffix:semicolon
multiline_comment|/* event set active at the time of the overflow          */
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:semicolon
DECL|member|smpl_pmds
r_int
r_int
id|smpl_pmds
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|smpl_pmds_values
r_int
r_int
id|smpl_pmds_values
(braket
id|PMU_MAX_PMDS
)braket
suffix:semicolon
DECL|member|ovfl_ctrl
id|pfm_ovfl_ctrl_t
id|ovfl_ctrl
suffix:semicolon
multiline_comment|/* return: perfmon controls to set by handler            */
DECL|typedef|pfm_ovfl_arg_t
)brace
id|pfm_ovfl_arg_t
suffix:semicolon
DECL|struct|_pfm_buffer_fmt_t
r_typedef
r_struct
id|_pfm_buffer_fmt_t
(brace
DECL|member|fmt_name
r_char
op_star
id|fmt_name
suffix:semicolon
DECL|member|fmt_uuid
id|pfm_uuid_t
id|fmt_uuid
suffix:semicolon
DECL|member|fmt_arg_size
r_int
id|fmt_arg_size
suffix:semicolon
DECL|member|fmt_flags
r_int
r_int
id|fmt_flags
suffix:semicolon
DECL|member|fmt_validate
r_int
(paren
op_star
id|fmt_validate
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|flags
comma
r_int
id|cpu
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|fmt_getsize
r_int
(paren
op_star
id|fmt_getsize
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|flags
comma
r_int
id|cpu
comma
r_void
op_star
id|arg
comma
r_int
r_int
op_star
id|size
)paren
suffix:semicolon
DECL|member|fmt_init
r_int
(paren
op_star
id|fmt_init
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|flags
comma
r_int
id|cpu
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|fmt_handler
r_int
(paren
op_star
id|fmt_handler
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_void
op_star
id|buf
comma
id|pfm_ovfl_arg_t
op_star
id|arg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|fmt_restart
r_int
(paren
op_star
id|fmt_restart
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
id|pfm_ovfl_ctrl_t
op_star
id|ctrl
comma
r_void
op_star
id|buf
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|fmt_restart_active
r_int
(paren
op_star
id|fmt_restart_active
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
id|pfm_ovfl_ctrl_t
op_star
id|ctrl
comma
r_void
op_star
id|buf
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|fmt_exit
r_int
(paren
op_star
id|fmt_exit
)paren
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_void
op_star
id|buf
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|fmt_next
r_struct
id|_pfm_buffer_fmt_t
op_star
id|fmt_next
suffix:semicolon
DECL|member|fmt_prev
r_struct
id|_pfm_buffer_fmt_t
op_star
id|fmt_prev
suffix:semicolon
DECL|typedef|pfm_buffer_fmt_t
)brace
id|pfm_buffer_fmt_t
suffix:semicolon
r_extern
r_int
id|pfm_register_buffer_fmt
c_func
(paren
id|pfm_buffer_fmt_t
op_star
id|fmt
)paren
suffix:semicolon
r_extern
r_int
id|pfm_unregister_buffer_fmt
c_func
(paren
id|pfm_uuid_t
id|uuid
)paren
suffix:semicolon
multiline_comment|/*&n; * perfmon interface exported to modules&n; */
r_extern
r_int
id|pfm_mod_fast_read_pmds
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
r_int
id|mask
(braket
l_int|4
)braket
comma
r_int
r_int
op_star
id|addr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|pfm_mod_read_pmds
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|pfarg_reg_t
op_star
id|req
comma
r_int
r_int
id|nreq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|pfm_mod_write_pmcs
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|pfarg_reg_t
op_star
id|req
comma
r_int
r_int
id|nreq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * describe the content of the local_cpu_date-&gt;pfm_syst_info field&n; */
DECL|macro|PFM_CPUINFO_SYST_WIDE
mdefine_line|#define PFM_CPUINFO_SYST_WIDE&t;0x1&t;/* if set a system wide session exists */
DECL|macro|PFM_CPUINFO_DCR_PP
mdefine_line|#define PFM_CPUINFO_DCR_PP&t;0x2&t;/* if set the system wide session has started */
DECL|macro|PFM_CPUINFO_EXCL_IDLE
mdefine_line|#define PFM_CPUINFO_EXCL_IDLE&t;0x4&t;/* the system wide session excludes the idle task */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_PERFMON_H */
eof
