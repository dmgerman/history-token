multiline_comment|/*&n; * include/asm-sh/cpu-sh3/cache.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH3_CACHE_H
DECL|macro|__ASM_CPU_SH3_CACHE_H
mdefine_line|#define __ASM_CPU_SH3_CACHE_H
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  16
DECL|macro|CCR
mdefine_line|#define CCR&t;&t;0xffffffec&t;/* Address of Cache Control Register */
DECL|macro|CCR_CACHE_CE
mdefine_line|#define CCR_CACHE_CE&t;0x01&t;/* Cache Enable */
DECL|macro|CCR_CACHE_WT
mdefine_line|#define CCR_CACHE_WT&t;0x02&t;/* Write-Through (for P0,U0,P3) (else writeback) */
DECL|macro|CCR_CACHE_CB
mdefine_line|#define CCR_CACHE_CB&t;0x04&t;/* Write-Back (for P1) (else writethrough) */
DECL|macro|CCR_CACHE_CF
mdefine_line|#define CCR_CACHE_CF&t;0x08&t;/* Cache Flush */
DECL|macro|CCR_CACHE_ORA
mdefine_line|#define CCR_CACHE_ORA&t;0x20&t;/* RAM mode */
DECL|macro|CACHE_OC_ADDRESS_ARRAY
mdefine_line|#define CACHE_OC_ADDRESS_ARRAY&t;0xf0000000
DECL|macro|CACHE_PHYSADDR_MASK
mdefine_line|#define CACHE_PHYSADDR_MASK&t;0x1ffffc00
DECL|macro|CCR_CACHE_ENABLE
mdefine_line|#define CCR_CACHE_ENABLE&t;CCR_CACHE_CE
DECL|macro|CCR_CACHE_INVALIDATE
mdefine_line|#define CCR_CACHE_INVALIDATE&t;CCR_CACHE_CF
macro_line|#endif /* __ASM_CPU_SH3_CACHE_H */
eof
