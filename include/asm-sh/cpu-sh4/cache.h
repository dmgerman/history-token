multiline_comment|/*&n; * include/asm-sh/cpu-sh4/cache.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH4_CACHE_H
DECL|macro|__ASM_CPU_SH4_CACHE_H
mdefine_line|#define __ASM_CPU_SH4_CACHE_H
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32
DECL|macro|CCR
mdefine_line|#define CCR&t;&t;0xff00001c&t;/* Address of Cache Control Register */
DECL|macro|CCR_CACHE_OCE
mdefine_line|#define CCR_CACHE_OCE&t;0x0001&t;/* Operand Cache Enable */
DECL|macro|CCR_CACHE_WT
mdefine_line|#define CCR_CACHE_WT&t;0x0002&t;/* Write-Through (for P0,U0,P3) (else writeback)*/
DECL|macro|CCR_CACHE_CB
mdefine_line|#define CCR_CACHE_CB&t;0x0004&t;/* Copy-Back (for P1) (else writethrough) */
DECL|macro|CCR_CACHE_OCI
mdefine_line|#define CCR_CACHE_OCI&t;0x0008&t;/* OC Invalidate */
DECL|macro|CCR_CACHE_ORA
mdefine_line|#define CCR_CACHE_ORA&t;0x0020&t;/* OC RAM Mode */
DECL|macro|CCR_CACHE_OIX
mdefine_line|#define CCR_CACHE_OIX&t;0x0080&t;/* OC Index Enable */
DECL|macro|CCR_CACHE_ICE
mdefine_line|#define CCR_CACHE_ICE&t;0x0100&t;/* Instruction Cache Enable */
DECL|macro|CCR_CACHE_ICI
mdefine_line|#define CCR_CACHE_ICI&t;0x0800&t;/* IC Invalidate */
DECL|macro|CCR_CACHE_IIX
mdefine_line|#define CCR_CACHE_IIX&t;0x8000&t;/* IC Index Enable */
DECL|macro|CCR_CACHE_EMODE
mdefine_line|#define CCR_CACHE_EMODE&t;0x80000000&t;/* EMODE Enable */
multiline_comment|/* Default CCR setup: 8k+16k-byte cache,P1-wb,enable */
DECL|macro|CCR_CACHE_ENABLE
mdefine_line|#define CCR_CACHE_ENABLE&t;(CCR_CACHE_OCE|CCR_CACHE_ICE)
DECL|macro|CCR_CACHE_INVALIDATE
mdefine_line|#define CCR_CACHE_INVALIDATE&t;(CCR_CACHE_OCI|CCR_CACHE_ICI)
DECL|macro|CACHE_IC_ADDRESS_ARRAY
mdefine_line|#define CACHE_IC_ADDRESS_ARRAY&t;0xf0000000
DECL|macro|CACHE_OC_ADDRESS_ARRAY
mdefine_line|#define CACHE_OC_ADDRESS_ARRAY&t;0xf4000000
macro_line|#endif /* __ASM_CPU_SH4_CACHE_H */
eof
