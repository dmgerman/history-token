multiline_comment|/*&n; * File ported from IRIX to Linux by Kanoj Sarcar, 06/08/00.&n; * Copyright 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_SN_KLKERNVARS_H
DECL|macro|__ASM_SN_KLKERNVARS_H
mdefine_line|#define __ASM_SN_KLKERNVARS_H
DECL|macro|KV_MAGIC_OFFSET
mdefine_line|#define KV_MAGIC_OFFSET&t;&t;0x0
DECL|macro|KV_RO_NASID_OFFSET
mdefine_line|#define KV_RO_NASID_OFFSET&t;0x4
DECL|macro|KV_RW_NASID_OFFSET
mdefine_line|#define KV_RW_NASID_OFFSET&t;0x6
DECL|macro|KV_MAGIC
mdefine_line|#define KV_MAGIC&t;&t;0x5f4b565f
macro_line|#if _LANGUAGE_C
macro_line|#include &lt;asm/sn/types.h&gt;
DECL|struct|kern_vars_s
r_typedef
r_struct
id|kern_vars_s
(brace
DECL|member|kv_magic
r_int
id|kv_magic
suffix:semicolon
DECL|member|kv_ro_nasid
id|nasid_t
id|kv_ro_nasid
suffix:semicolon
DECL|member|kv_rw_nasid
id|nasid_t
id|kv_rw_nasid
suffix:semicolon
DECL|member|kv_ro_baseaddr
r_int
r_int
id|kv_ro_baseaddr
suffix:semicolon
DECL|member|kv_rw_baseaddr
r_int
r_int
id|kv_rw_baseaddr
suffix:semicolon
DECL|typedef|kern_vars_t
)brace
id|kern_vars_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* __ASM_SN_KLKERNVARS_H */
eof
