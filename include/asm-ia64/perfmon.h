multiline_comment|/*&n; * Copyright (C) 2001-2002 Hewlett-Packard Co&n; *               Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
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
mdefine_line|#define PFM_ENABLE&t;&t;0x06
DECL|macro|PFM_DISABLE
mdefine_line|#define PFM_DISABLE&t;&t;0x07
DECL|macro|PFM_CREATE_CONTEXT
mdefine_line|#define PFM_CREATE_CONTEXT&t;0x08
DECL|macro|PFM_DESTROY_CONTEXT
mdefine_line|#define PFM_DESTROY_CONTEXT&t;0x09
DECL|macro|PFM_RESTART
mdefine_line|#define PFM_RESTART&t;&t;0x0a
DECL|macro|PFM_PROTECT_CONTEXT
mdefine_line|#define PFM_PROTECT_CONTEXT&t;0x0b
DECL|macro|PFM_GET_FEATURES
mdefine_line|#define PFM_GET_FEATURES&t;0x0c
DECL|macro|PFM_DEBUG
mdefine_line|#define PFM_DEBUG&t;&t;0x0d
DECL|macro|PFM_UNPROTECT_CONTEXT
mdefine_line|#define PFM_UNPROTECT_CONTEXT&t;0x0e
multiline_comment|/*&n; * CPU model specific commands (may not be supported on all models)&n; */
DECL|macro|PFM_WRITE_IBRS
mdefine_line|#define PFM_WRITE_IBRS&t;&t;0x20
DECL|macro|PFM_WRITE_DBRS
mdefine_line|#define PFM_WRITE_DBRS&t;&t;0x21
multiline_comment|/*&n; * context flags&n; */
DECL|macro|PFM_FL_INHERIT_NONE
mdefine_line|#define PFM_FL_INHERIT_NONE&t; 0x00&t;/* never inherit a context across fork (default) */
DECL|macro|PFM_FL_INHERIT_ONCE
mdefine_line|#define PFM_FL_INHERIT_ONCE&t; 0x01&t;/* clone pfm_context only once across fork() */
DECL|macro|PFM_FL_INHERIT_ALL
mdefine_line|#define PFM_FL_INHERIT_ALL&t; 0x02&t;/* always clone pfm_context across fork() */
DECL|macro|PFM_FL_NOTIFY_BLOCK
mdefine_line|#define PFM_FL_NOTIFY_BLOCK    &t; 0x04&t;/* block task on user level notifications */
DECL|macro|PFM_FL_SYSTEM_WIDE
mdefine_line|#define PFM_FL_SYSTEM_WIDE&t; 0x08&t;/* create a system wide context */
multiline_comment|/*&n; * PMC flags&n; */
DECL|macro|PFM_REGFL_OVFL_NOTIFY
mdefine_line|#define PFM_REGFL_OVFL_NOTIFY&t;0x1&t;/* send notification on overflow */
multiline_comment|/*&n; * PMD/PMC/IBR/DBR return flags (ignored on input)&n; *&n; * Those flags are used on output and must be checked in case EAGAIN is returned&n; * by any of the calls using a pfarg_reg_t or pfarg_dbreg_t structure.&n; */
DECL|macro|PFM_REG_RETFL_NOTAVAIL
mdefine_line|#define PFM_REG_RETFL_NOTAVAIL&t;(1U&lt;&lt;31) /* set if register is implemented but not available */
DECL|macro|PFM_REG_RETFL_EINVAL
mdefine_line|#define PFM_REG_RETFL_EINVAL&t;(1U&lt;&lt;30) /* set if register entry is invalid */
DECL|macro|PFM_REG_RETFL_MASK
mdefine_line|#define PFM_REG_RETFL_MASK&t;(PFM_REG_RETFL_NOTAVAIL|PFM_REG_RETFL_EINVAL)
DECL|macro|PFM_REG_HAS_ERROR
mdefine_line|#define PFM_REG_HAS_ERROR(flag)&t;(((flag) &amp; PFM_REG_RETFL_MASK) != 0)
multiline_comment|/*&n; * Request structure used to define a context&n; */
r_typedef
r_struct
(brace
DECL|member|ctx_smpl_entries
r_int
r_int
id|ctx_smpl_entries
suffix:semicolon
multiline_comment|/* how many entries in sampling buffer */
DECL|member|ctx_smpl_regs
r_int
r_int
id|ctx_smpl_regs
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which pmds to record on overflow */
DECL|member|ctx_notify_pid
id|pid_t
id|ctx_notify_pid
suffix:semicolon
multiline_comment|/* which process to notify on overflow */
DECL|member|ctx_flags
r_int
id|ctx_flags
suffix:semicolon
multiline_comment|/* noblock/block, inherit flags */
DECL|member|ctx_smpl_vaddr
r_void
op_star
id|ctx_smpl_vaddr
suffix:semicolon
multiline_comment|/* returns address of BTB buffer */
DECL|member|ctx_cpu_mask
r_int
r_int
id|ctx_cpu_mask
suffix:semicolon
multiline_comment|/* on which CPU to enable perfmon (systemwide) */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|8
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
multiline_comment|/* which register */
DECL|member|reg_flags
r_int
r_int
id|reg_flags
suffix:semicolon
multiline_comment|/* PMC: notify/don&squot;t notify. PMD/PMC: return flags */
DECL|member|reg_value
r_int
r_int
id|reg_value
suffix:semicolon
multiline_comment|/* configuration (PMC) or initial value (PMD) */
DECL|member|reg_long_reset
r_int
r_int
id|reg_long_reset
suffix:semicolon
multiline_comment|/* reset after sampling buffer overflow (large) */
DECL|member|reg_short_reset
r_int
r_int
id|reg_short_reset
suffix:semicolon
multiline_comment|/* reset after counter overflow (small) */
DECL|member|reg_reset_pmds
r_int
r_int
id|reg_reset_pmds
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which other counters to reset on overflow */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for future use */
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
multiline_comment|/* which register */
DECL|member|dbreg_flags
r_int
r_int
id|dbreg_flags
suffix:semicolon
multiline_comment|/* dbregs return flags */
DECL|member|dbreg_value
r_int
r_int
id|dbreg_value
suffix:semicolon
multiline_comment|/* configuration (PMC) or initial value (PMD) */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
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
DECL|member|ft_smpl_version
r_int
r_int
id|ft_smpl_version
suffix:semicolon
multiline_comment|/* sampling format: major [16-31], minor [0-15] */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* for future use */
DECL|typedef|pfarg_features_t
)brace
id|pfarg_features_t
suffix:semicolon
multiline_comment|/*&n; * This header is at the beginning of the sampling buffer returned to the user.&n; * It is exported as Read-Only at this point. It is directly followed by the&n; * first record.&n; */
r_typedef
r_struct
(brace
DECL|member|hdr_version
r_int
r_int
id|hdr_version
suffix:semicolon
multiline_comment|/* contains perfmon version (smpl format diffs) */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
DECL|member|hdr_entry_size
r_int
r_int
id|hdr_entry_size
suffix:semicolon
multiline_comment|/* size of one entry in bytes */
DECL|member|hdr_count
r_int
r_int
id|hdr_count
suffix:semicolon
multiline_comment|/* how many valid entries */
DECL|member|hdr_pmds
r_int
r_int
id|hdr_pmds
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which pmds are recorded */
DECL|typedef|perfmon_smpl_hdr_t
)brace
id|perfmon_smpl_hdr_t
suffix:semicolon
multiline_comment|/*&n; * Define the version numbers for both perfmon as a whole and the sampling buffer format.&n; */
DECL|macro|PFM_VERSION_MAJ
mdefine_line|#define PFM_VERSION_MAJ&t;&t;1U
DECL|macro|PFM_VERSION_MIN
mdefine_line|#define PFM_VERSION_MIN&t;&t;0U
DECL|macro|PFM_VERSION
mdefine_line|#define PFM_VERSION&t;&t;(((PFM_VERSION_MAJ&amp;0xffff)&lt;&lt;16)|(PFM_VERSION_MIN &amp; 0xffff))
DECL|macro|PFM_SMPL_VERSION_MAJ
mdefine_line|#define PFM_SMPL_VERSION_MAJ&t;1U
DECL|macro|PFM_SMPL_VERSION_MIN
mdefine_line|#define PFM_SMPL_VERSION_MIN&t;0U
DECL|macro|PFM_SMPL_VERSION
mdefine_line|#define PFM_SMPL_VERSION&t;(((PFM_SMPL_VERSION_MAJ&amp;0xffff)&lt;&lt;16)|(PFM_SMPL_VERSION_MIN &amp; 0xffff))
DECL|macro|PFM_VERSION_MAJOR
mdefine_line|#define PFM_VERSION_MAJOR(x)&t;(((x)&gt;&gt;16) &amp; 0xffff)
DECL|macro|PFM_VERSION_MINOR
mdefine_line|#define PFM_VERSION_MINOR(x)&t;((x) &amp; 0xffff)
multiline_comment|/*&n; * Entry header in the sampling buffer.&n; * The header is directly followed with the PMDS saved in increasing index &n; * order: PMD4, PMD5, .... How many PMDs are present is determined by the &n; * user program during context creation.&n; *&n; * XXX: in this version of the entry, only up to 64 registers can be recorded&n; * This should be enough for quite some time. Always check sampling format&n; * before parsing entries!&n; *&n; * Inn the case where multiple counters have overflowed at the same time, the &n; * rate field indicate the initial value of the first PMD, based on the index.&n; * For instance, if PMD2 and PMD5 have ovewrflowed for this entry, the rate field&n; * will show the initial value of PMD2.&n; */
r_typedef
r_struct
(brace
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* identification of process */
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
multiline_comment|/* which cpu was used */
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
multiline_comment|/* initial value of overflowed counter */
DECL|member|stamp
r_int
r_int
id|stamp
suffix:semicolon
multiline_comment|/* timestamp */
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* where did the overflow interrupt happened */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* bitmask of which registers overflowed */
DECL|member|period
r_int
r_int
id|period
suffix:semicolon
multiline_comment|/* sampling period used by overflowed counter (smallest pmd index) */
DECL|typedef|perfmon_smpl_entry_t
)brace
id|perfmon_smpl_entry_t
suffix:semicolon
r_extern
r_int
id|perfmonctl
c_func
(paren
id|pid_t
id|pid
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
macro_line|#ifdef __KERNEL__
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
comma
r_struct
id|pt_regs
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
r_extern
r_void
id|pfm_cleanup_notifiers
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pfm_cleanup_owners
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
r_int
id|pfm_cleanup_smpl_buf
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
)paren
suffix:semicolon
r_extern
r_void
id|pfm_ovfl_block_reset
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_PERFMON_H */
eof
