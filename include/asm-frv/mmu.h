multiline_comment|/* mmu.h: memory management context for FR-V with or without MMU support&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MMU_H
DECL|macro|_ASM_MMU_H
mdefine_line|#define _ASM_MMU_H
r_typedef
r_struct
(brace
macro_line|#ifdef CONFIG_MMU
DECL|member|id_link
r_struct
id|list_head
id|id_link
suffix:semicolon
multiline_comment|/* link in list of context ID owners */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* MMU context ID */
DECL|member|id_busy
r_int
r_int
id|id_busy
suffix:semicolon
multiline_comment|/* true if ID is in CXNR */
DECL|member|itlb_cached_pge
r_int
r_int
id|itlb_cached_pge
suffix:semicolon
multiline_comment|/* [SCR0] PGE cached for insn TLB handler */
DECL|member|itlb_ptd_mapping
r_int
r_int
id|itlb_ptd_mapping
suffix:semicolon
multiline_comment|/* [DAMR4] PTD mapping for itlb cached PGE */
DECL|member|dtlb_cached_pge
r_int
r_int
id|dtlb_cached_pge
suffix:semicolon
multiline_comment|/* [SCR1] PGE cached for data TLB handler */
DECL|member|dtlb_ptd_mapping
r_int
r_int
id|dtlb_ptd_mapping
suffix:semicolon
multiline_comment|/* [DAMR5] PTD mapping for dtlb cached PGE */
macro_line|#else
r_struct
id|vm_list_struct
op_star
id|vmlist
suffix:semicolon
r_int
r_int
id|end_brk
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_ELF_FDPIC
DECL|member|exec_fdpic_loadmap
r_int
r_int
id|exec_fdpic_loadmap
suffix:semicolon
DECL|member|interp_fdpic_loadmap
r_int
r_int
id|interp_fdpic_loadmap
suffix:semicolon
macro_line|#endif
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
r_extern
r_int
id|__nongpreldata
id|cxn_pinned
suffix:semicolon
r_extern
r_int
id|cxn_pin_by_pid
c_func
(paren
id|pid_t
id|pid
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_MMU_H */
eof
