multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Kaz Kojima&n; *&n; * Defitions for the address spaces of the SH-4 CPUs.&n; */
macro_line|#ifndef __ASM_CPU_SH4_ADDRSPACE_H
DECL|macro|__ASM_CPU_SH4_ADDRSPACE_H
mdefine_line|#define __ASM_CPU_SH4_ADDRSPACE_H
multiline_comment|/* Detailed P4SEG  */
DECL|macro|P4SEG_STORE_QUE
mdefine_line|#define P4SEG_STORE_QUE&t;(P4SEG)
DECL|macro|P4SEG_IC_ADDR
mdefine_line|#define P4SEG_IC_ADDR&t;0xf0000000
DECL|macro|P4SEG_IC_DATA
mdefine_line|#define P4SEG_IC_DATA&t;0xf1000000
DECL|macro|P4SEG_ITLB_ADDR
mdefine_line|#define P4SEG_ITLB_ADDR&t;0xf2000000
DECL|macro|P4SEG_ITLB_DATA
mdefine_line|#define P4SEG_ITLB_DATA&t;0xf3000000
DECL|macro|P4SEG_OC_ADDR
mdefine_line|#define P4SEG_OC_ADDR&t;0xf4000000
DECL|macro|P4SEG_OC_DATA
mdefine_line|#define P4SEG_OC_DATA&t;0xf5000000
DECL|macro|P4SEG_TLB_ADDR
mdefine_line|#define P4SEG_TLB_ADDR&t;0xf6000000
DECL|macro|P4SEG_TLB_DATA
mdefine_line|#define P4SEG_TLB_DATA&t;0xf7000000
DECL|macro|P4SEG_REG_BASE
mdefine_line|#define P4SEG_REG_BASE&t;0xff000000
macro_line|#endif /* __ASM_CPU_SH4_ADDRSPACE_H */
eof
