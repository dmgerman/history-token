multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Kaz Kojima&n; *&n; * Defitions for the address spaces of the SH CPUs.&n; */
macro_line|#ifndef __ASM_SH_ADDRSPACE_H
DECL|macro|__ASM_SH_ADDRSPACE_H
mdefine_line|#define __ASM_SH_ADDRSPACE_H
multiline_comment|/* Memory segments (32bit Priviledged mode addresses)  */
DECL|macro|P0SEG
mdefine_line|#define P0SEG&t;&t;0x00000000
DECL|macro|P1SEG
mdefine_line|#define P1SEG&t;&t;0x80000000
DECL|macro|P2SEG
mdefine_line|#define P2SEG&t;&t;0xa0000000
DECL|macro|P3SEG
mdefine_line|#define P3SEG&t;&t;0xc0000000
DECL|macro|P4SEG
mdefine_line|#define P4SEG&t;&t;0xe0000000
macro_line|#if defined(__sh3__)
multiline_comment|/* Should fill here */
macro_line|#elif defined(__SH4__)
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
macro_line|#endif
multiline_comment|/* Returns the privileged segment base of a given address  */
DECL|macro|PXSEG
mdefine_line|#define PXSEG(a)&t;(((unsigned long)(a)) &amp; 0xe0000000)
multiline_comment|/* Returns the physical address of a PnSEG (n=1,2) address   */
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;(((unsigned long)(a)) &amp; 0x1fffffff)
multiline_comment|/*&n; * Map an address to a certain privileged segment&n; */
DECL|macro|P1SEGADDR
mdefine_line|#define P1SEGADDR(a)&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | P1SEG))
DECL|macro|P2SEGADDR
mdefine_line|#define P2SEGADDR(a)&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | P2SEG))
DECL|macro|P3SEGADDR
mdefine_line|#define P3SEGADDR(a)&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | P3SEG))
DECL|macro|P4SEGADDR
mdefine_line|#define P4SEGADDR(a)&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | P4SEG))
macro_line|#endif /* __ASM_SH_ADDRSPACE_H */
eof
