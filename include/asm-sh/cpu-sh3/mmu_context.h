multiline_comment|/*&n; * include/asm-sh/cpu-sh3/mmu_context.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH3_MMU_CONTEXT_H
DECL|macro|__ASM_CPU_SH3_MMU_CONTEXT_H
mdefine_line|#define __ASM_CPU_SH3_MMU_CONTEXT_H
DECL|macro|MMU_PTEH
mdefine_line|#define MMU_PTEH&t;0xFFFFFFF0&t;/* Page table entry register HIGH */
DECL|macro|MMU_PTEL
mdefine_line|#define MMU_PTEL&t;0xFFFFFFF4&t;/* Page table entry register LOW */
DECL|macro|MMU_TTB
mdefine_line|#define MMU_TTB&t;&t;0xFFFFFFF8&t;/* Translation table base register */
DECL|macro|MMU_TEA
mdefine_line|#define MMU_TEA&t;&t;0xFFFFFFFC&t;/* TLB Exception Address */
DECL|macro|MMUCR
mdefine_line|#define MMUCR&t;&t;0xFFFFFFE0&t;/* MMU Control Register */
DECL|macro|MMU_TLB_ADDRESS_ARRAY
mdefine_line|#define MMU_TLB_ADDRESS_ARRAY&t;0xF2000000
DECL|macro|MMU_PAGE_ASSOC_BIT
mdefine_line|#define MMU_PAGE_ASSOC_BIT&t;0x80
DECL|macro|MMU_NTLB_ENTRIES
mdefine_line|#define MMU_NTLB_ENTRIES&t;128&t;/* for 7708 */
DECL|macro|MMU_CONTROL_INIT
mdefine_line|#define MMU_CONTROL_INIT&t;0x007&t;/* SV=0, TF=1, IX=1, AT=1 */
macro_line|#endif /* __ASM_CPU_SH3_MMU_CONTEXT_H */
eof
