multiline_comment|/*&n; * Copyright (C) 2002-2003 Hewlett-Packard Co&n; *               Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * This file implements the default sampling buffer format&n; * for Linux/ia64 perfmon subsystem.&n; */
macro_line|#ifndef __PERFMON_DEFAULT_SMPL_H__
DECL|macro|__PERFMON_DEFAULT_SMPL_H__
mdefine_line|#define __PERFMON_DEFAULT_SMPL_H__ 1
DECL|macro|PFM_DEFAULT_SMPL_UUID
mdefine_line|#define PFM_DEFAULT_SMPL_UUID { &bslash;&n;&t;&t;0x4d, 0x72, 0xbe, 0xc0, 0x06, 0x64, 0x41, 0x43, 0x82, 0xb4, 0xd3, 0xfd, 0x27, 0x24, 0x3c, 0x97}
multiline_comment|/*&n; * format specific parameters (passed at context creation)&n; */
r_typedef
r_struct
(brace
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* size of the buffer in bytes */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* buffer specific flags */
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* for future use */
DECL|typedef|pfm_default_smpl_arg_t
)brace
id|pfm_default_smpl_arg_t
suffix:semicolon
multiline_comment|/*&n; * combined context+format specific structure. Can be passed&n; * to PFM_CONTEXT_CREATE&n; */
r_typedef
r_struct
(brace
DECL|member|ctx_arg
id|pfarg_context_t
id|ctx_arg
suffix:semicolon
DECL|member|buf_arg
id|pfm_default_smpl_arg_t
id|buf_arg
suffix:semicolon
DECL|typedef|pfm_default_smpl_ctx_arg_t
)brace
id|pfm_default_smpl_ctx_arg_t
suffix:semicolon
multiline_comment|/*&n; * This header is at the beginning of the sampling buffer returned to the user.&n; * It is directly followed by the first record.&n; */
r_typedef
r_struct
(brace
DECL|member|hdr_count
r_int
r_int
id|hdr_count
suffix:semicolon
multiline_comment|/* how many valid entries */
DECL|member|hdr_cur_pos
r_void
op_star
id|hdr_cur_pos
suffix:semicolon
multiline_comment|/* current position in the buffer */
DECL|member|hdr_last_pos
r_void
op_star
id|hdr_last_pos
suffix:semicolon
multiline_comment|/* first byte beyond buffer */
DECL|member|hdr_overflows
r_int
r_int
id|hdr_overflows
suffix:semicolon
multiline_comment|/* how many times the buffer overflowed */
DECL|member|hdr_buf_size
r_int
r_int
id|hdr_buf_size
suffix:semicolon
multiline_comment|/* how many bytes in the buffer */
DECL|member|hdr_version
r_int
r_int
id|hdr_version
suffix:semicolon
multiline_comment|/* contains perfmon version (smpl format diffs) */
DECL|member|hdr_reserved1
r_int
r_int
id|hdr_reserved1
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|hdr_reserved
r_int
r_int
id|hdr_reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* for future use */
DECL|typedef|pfm_default_smpl_hdr_t
)brace
id|pfm_default_smpl_hdr_t
suffix:semicolon
multiline_comment|/*&n; * Entry header in the sampling buffer.  The header is directly followed&n; * with the values of the PMD registers of interest saved in increasing &n; * index order: PMD4, PMD5, and so on. How many PMDs are present depends &n; * on how the session was programmed.&n; *&n; * In the case where multiple counters overflow at the same time, multiple&n; * entries are written consecutively.&n; *&n; * last_reset_value member indicates the initial value of the overflowed PMD. &n; */
r_typedef
r_struct
(brace
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* active process at PMU interrupt point */
DECL|member|reserved1
r_int
r_char
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|ovfl_pmd
r_int
r_char
id|ovfl_pmd
suffix:semicolon
multiline_comment|/* index of overflowed PMD */
DECL|member|last_reset_val
r_int
r_int
id|last_reset_val
suffix:semicolon
multiline_comment|/* initial value of overflowed PMD */
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* where did the overflow interrupt happened  */
DECL|member|tstamp
r_int
r_int
id|tstamp
suffix:semicolon
multiline_comment|/* ar.itc when entering perfmon intr. handler */
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu on which the overfow occured */
DECL|member|set
r_int
r_int
id|set
suffix:semicolon
multiline_comment|/* event set active when overflow ocurred   */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:semicolon
multiline_comment|/* for future use */
DECL|typedef|pfm_default_smpl_entry_t
)brace
id|pfm_default_smpl_entry_t
suffix:semicolon
DECL|macro|PFM_DEFAULT_MAX_PMDS
mdefine_line|#define PFM_DEFAULT_MAX_PMDS&t;&t;64 /* how many pmds supported by data structures (sizeof(unsigned long) */
DECL|macro|PFM_DEFAULT_MAX_ENTRY_SIZE
mdefine_line|#define PFM_DEFAULT_MAX_ENTRY_SIZE&t;(sizeof(pfm_default_smpl_entry_t)+(sizeof(unsigned long)*PFM_DEFAULT_MAX_PMDS))
DECL|macro|PFM_DEFAULT_SMPL_MIN_BUF_SIZE
mdefine_line|#define PFM_DEFAULT_SMPL_MIN_BUF_SIZE&t;(sizeof(pfm_default_smpl_hdr_t)+PFM_DEFAULT_MAX_ENTRY_SIZE)
DECL|macro|PFM_DEFAULT_SMPL_VERSION_MAJ
mdefine_line|#define PFM_DEFAULT_SMPL_VERSION_MAJ&t;2U
DECL|macro|PFM_DEFAULT_SMPL_VERSION_MIN
mdefine_line|#define PFM_DEFAULT_SMPL_VERSION_MIN&t;0U
DECL|macro|PFM_DEFAULT_SMPL_VERSION
mdefine_line|#define PFM_DEFAULT_SMPL_VERSION&t;(((PFM_DEFAULT_SMPL_VERSION_MAJ&amp;0xffff)&lt;&lt;16)|(PFM_DEFAULT_SMPL_VERSION_MIN &amp; 0xffff))
macro_line|#endif /* __PERFMON_DEFAULT_SMPL_H__ */
eof
