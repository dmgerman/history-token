multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; *&n; * Defitions for the address spaces of the MIPS CPUs.&n; */
macro_line|#ifndef __ASM_MIPS_ADDRSPACE_H
DECL|macro|__ASM_MIPS_ADDRSPACE_H
mdefine_line|#define __ASM_MIPS_ADDRSPACE_H
multiline_comment|/*&n; * Memory segments (32bit kernel mode addresses)&n; */
DECL|macro|KUSEG
mdefine_line|#define KUSEG                   0x00000000
DECL|macro|KSEG0
mdefine_line|#define KSEG0                   0x80000000
DECL|macro|KSEG1
mdefine_line|#define KSEG1                   0xa0000000
DECL|macro|KSEG2
mdefine_line|#define KSEG2                   0xc0000000
DECL|macro|KSEG3
mdefine_line|#define KSEG3                   0xe0000000
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)                (((unsigned long)(a)) &amp; 0xe0000000)
multiline_comment|/*&n; * Returns the physical address of a KSEG0/KSEG1 address&n; */
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;&t;(((unsigned long)(a)) &amp; 0x1fffffff)
multiline_comment|/*&n; * Map an address to a certain kernel segment&n; */
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG0))
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG1))
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG2))
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG3))
multiline_comment|/*&n; * Memory segments (64bit kernel mode addresses)&n; */
DECL|macro|XKUSEG
mdefine_line|#define XKUSEG                  0x0000000000000000
DECL|macro|XKSSEG
mdefine_line|#define XKSSEG                  0x4000000000000000
DECL|macro|XKPHYS
mdefine_line|#define XKPHYS                  0x8000000000000000
DECL|macro|XKSEG
mdefine_line|#define XKSEG                   0xc000000000000000
DECL|macro|CKSEG0
mdefine_line|#define CKSEG0                  0xffffffff80000000
DECL|macro|CKSEG1
mdefine_line|#define CKSEG1                  0xffffffffa0000000
DECL|macro|CKSSEG
mdefine_line|#define CKSSEG                  0xffffffffc0000000
DECL|macro|CKSEG3
mdefine_line|#define CKSEG3                  0xffffffffe0000000
macro_line|#endif /* __ASM_MIPS_ADDRSPACE_H */
eof
