multiline_comment|/* $Id$ */
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001 by Hiroyuki Kondo&n; *&n; * Defitions for the address spaces of the M32R CPUs.&n; */
macro_line|#ifndef __ASM_M32R_ADDRSPACE_H
DECL|macro|__ASM_M32R_ADDRSPACE_H
mdefine_line|#define __ASM_M32R_ADDRSPACE_H
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
DECL|macro|K0BASE
mdefine_line|#define K0BASE  KSEG0
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)                (((unsigned long)(a)) &amp; 0xe0000000)
macro_line|#else
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)                ((a) &amp; 0xe0000000)
macro_line|#endif
multiline_comment|/*&n; * Returns the physical address of a KSEG0/KSEG1 address&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;&t;(((unsigned long)(a)) &amp; 0x1fffffff)
macro_line|#else
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;&t;((a) &amp; 0x1fffffff)
macro_line|#endif
multiline_comment|/*&n; * Map an address to a certain kernel segment&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG0))
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG1))
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG2))
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x1fffffff) | KSEG3))
macro_line|#else
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;(((a) &amp; 0x1fffffff) | KSEG0)
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;(((a) &amp; 0x1fffffff) | KSEG1)
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;(((a) &amp; 0x1fffffff) | KSEG2)
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;(((a) &amp; 0x1fffffff) | KSEG3)
macro_line|#endif
macro_line|#endif /* __ASM_M32R_ADDRSPACE_H */
eof
