multiline_comment|/*&n; * include/asm-sh/cpu-sh4/mmu_context.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH4_MMU_CONTEXT_H
DECL|macro|__ASM_CPU_SH4_MMU_CONTEXT_H
mdefine_line|#define __ASM_CPU_SH4_MMU_CONTEXT_H
DECL|macro|MMU_PTEH
mdefine_line|#define MMU_PTEH&t;0xFF000000&t;/* Page table entry register HIGH */
DECL|macro|MMU_PTEL
mdefine_line|#define MMU_PTEL&t;0xFF000004&t;/* Page table entry register LOW */
DECL|macro|MMU_TTB
mdefine_line|#define MMU_TTB&t;&t;0xFF000008&t;/* Translation table base register */
DECL|macro|MMU_TEA
mdefine_line|#define MMU_TEA&t;&t;0xFF00000C&t;/* TLB Exception Address */
DECL|macro|MMU_PTEA
mdefine_line|#define MMU_PTEA&t;0xFF000034&t;/* Page table entry assistance register */
DECL|macro|MMUCR
mdefine_line|#define MMUCR&t;&t;0xFF000010&t;/* MMU Control Register */
DECL|macro|MMU_ITLB_ADDRESS_ARRAY
mdefine_line|#define MMU_ITLB_ADDRESS_ARRAY&t;0xF2000000
DECL|macro|MMU_UTLB_ADDRESS_ARRAY
mdefine_line|#define MMU_UTLB_ADDRESS_ARRAY&t;0xF6000000
DECL|macro|MMU_PAGE_ASSOC_BIT
mdefine_line|#define MMU_PAGE_ASSOC_BIT&t;0x80
DECL|macro|MMU_NTLB_ENTRIES
mdefine_line|#define MMU_NTLB_ENTRIES&t;64&t;/* for 7750 */
DECL|macro|MMU_CONTROL_INIT
mdefine_line|#define MMU_CONTROL_INIT&t;0x205&t;/* SQMD=1, SV=0, TI=1, AT=1 */
DECL|macro|MMU_ITLB_DATA_ARRAY
mdefine_line|#define MMU_ITLB_DATA_ARRAY&t;0xF3000000
DECL|macro|MMU_UTLB_DATA_ARRAY
mdefine_line|#define MMU_UTLB_DATA_ARRAY&t;0xF7000000
DECL|macro|MMU_UTLB_ENTRIES
mdefine_line|#define MMU_UTLB_ENTRIES&t;   64
DECL|macro|MMU_U_ENTRY_SHIFT
mdefine_line|#define MMU_U_ENTRY_SHIFT&t;    8
DECL|macro|MMU_UTLB_VALID
mdefine_line|#define MMU_UTLB_VALID&t;&t;0x100
DECL|macro|MMU_ITLB_ENTRIES
mdefine_line|#define MMU_ITLB_ENTRIES&t;    4
DECL|macro|MMU_I_ENTRY_SHIFT
mdefine_line|#define MMU_I_ENTRY_SHIFT&t;    8
DECL|macro|MMU_ITLB_VALID
mdefine_line|#define MMU_ITLB_VALID&t;&t;0x100
macro_line|#endif /* __ASM_CPU_SH4_MMU_CONTEXT_H */
eof
