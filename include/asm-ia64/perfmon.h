multiline_comment|/*&n; * Copyright (C) 2001 Hewlett-Packard Co&n; * Copyright (C) 2001 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_PERFMON_H
DECL|macro|_ASM_IA64_PERFMON_H
mdefine_line|#define _ASM_IA64_PERFMON_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Structure used to define a context&n; */
r_typedef
r_struct
(brace
DECL|member|smpl_entries
r_int
r_int
id|smpl_entries
suffix:semicolon
multiline_comment|/* how many entries in sampling buffer */
DECL|member|smpl_regs
r_int
r_int
id|smpl_regs
suffix:semicolon
multiline_comment|/* which pmds to record on overflow */
DECL|member|smpl_vaddr
r_void
op_star
id|smpl_vaddr
suffix:semicolon
multiline_comment|/* returns address of BTB buffer */
DECL|member|notify_pid
id|pid_t
id|notify_pid
suffix:semicolon
multiline_comment|/* which process to notify on overflow */
DECL|member|notify_sig
r_int
id|notify_sig
suffix:semicolon
multiline_comment|/* XXX: not used anymore */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* NOBLOCK/BLOCK/ INHERIT flags (will replace API flags) */
DECL|typedef|pfreq_context_t
)brace
id|pfreq_context_t
suffix:semicolon
multiline_comment|/*&n; * Structure used to configure a PMC or PMD&n; */
r_typedef
r_struct
(brace
DECL|member|reg_num
r_int
r_int
id|reg_num
suffix:semicolon
multiline_comment|/* which register */
DECL|member|reg_value
r_int
r_int
id|reg_value
suffix:semicolon
multiline_comment|/* configuration (PMC) or initial value (PMD) */
DECL|member|reg_smpl_reset
r_int
r_int
id|reg_smpl_reset
suffix:semicolon
multiline_comment|/* reset of sampling buffer overflow (large) */
DECL|member|reg_ovfl_reset
r_int
r_int
id|reg_ovfl_reset
suffix:semicolon
multiline_comment|/* reset on counter overflow (small) */
DECL|member|reg_flags
r_int
id|reg_flags
suffix:semicolon
multiline_comment|/* (PMD): notify/don&squot;t notify */
DECL|typedef|pfreq_reg_t
)brace
id|pfreq_reg_t
suffix:semicolon
multiline_comment|/*&n; * main request structure passed by user&n; */
r_typedef
r_union
(brace
DECL|member|pfr_ctx
id|pfreq_context_t
id|pfr_ctx
suffix:semicolon
multiline_comment|/* request to configure a context */
DECL|member|pfr_reg
id|pfreq_reg_t
id|pfr_reg
suffix:semicolon
multiline_comment|/* request to configure a PMD/PMC */
DECL|typedef|perfmon_req_t
)brace
id|perfmon_req_t
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
r_int
id|pfm_inherit
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pfm_context_exit
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pfm_flush_regs
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_PERFMON_H */
eof
