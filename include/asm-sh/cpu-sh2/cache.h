multiline_comment|/*&n; * include/asm-sh/cpu-sh2/cache.h&n; *&n; * Copyright (C) 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH2_CACHE_H
DECL|macro|__ASM_CPU_SH2_CACHE_H
mdefine_line|#define __ASM_CPU_SH2_CACHE_H
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define&t;L1_CACHE_BYTES&t;16
DECL|macro|CCR
mdefine_line|#define CCR&t;&t;0xfffffe92&t;/* Address of Cache Control Register */
DECL|macro|CCR_CACHE_CE
mdefine_line|#define CCR_CACHE_CE&t;0x01&t;/* Cache enable */
DECL|macro|CCR_CACHE_ID
mdefine_line|#define CCR_CACHE_ID&t;0x02&t;/* Instruction Replacement disable */
DECL|macro|CCR_CACHE_OD
mdefine_line|#define CCR_CACHE_OD&t;0x04&t;/* Data Replacement disable */
DECL|macro|CCR_CACHE_TW
mdefine_line|#define CCR_CACHE_TW&t;0x08&t;/* Two-way mode */
DECL|macro|CCR_CACHE_CP
mdefine_line|#define CCR_CACHE_CP&t;0x10&t;/* Cache purge */
DECL|macro|CACHE_OC_ADDRESS_ARRAY
mdefine_line|#define CACHE_OC_ADDRESS_ARRAY&t;0x60000000
DECL|macro|CCR_CACHE_ENABLE
mdefine_line|#define CCR_CACHE_ENABLE&t;CCR_CACHE_CE
DECL|macro|CCR_CACHE_INVALIDATE
mdefine_line|#define CCR_CACHE_INVALIDATE&t;CCR_CACHE_CP
DECL|macro|CCR_CACHE_ORA
mdefine_line|#define CCR_CACHE_ORA&t;&t;CCR_CACHE_TW
DECL|macro|CCR_CACHE_WT
mdefine_line|#define CCR_CACHE_WT&t;&t;0x00&t;/* SH-2 is _always_ write-through */
macro_line|#endif /* __ASM_CPU_SH2_CACHE_H */
eof
