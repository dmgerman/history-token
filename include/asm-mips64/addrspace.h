multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1999 by Ralf Baechle&n; * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_ADDRSPACE_H
DECL|macro|_ASM_ADDRSPACE_H
mdefine_line|#define _ASM_ADDRSPACE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Memory segments (32bit kernel mode addresses)&n; */
DECL|macro|KUSEG
mdefine_line|#define KUSEG                   0x0000000000000000
DECL|macro|KSEG0
mdefine_line|#define KSEG0                   0xffffffff80000000
DECL|macro|KSEG1
mdefine_line|#define KSEG1                   0xffffffffa0000000
DECL|macro|KSEG2
mdefine_line|#define KSEG2                   0xffffffffc0000000
DECL|macro|KSEG3
mdefine_line|#define KSEG3                   0xffffffffe0000000
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)                (((unsigned long)(a)) &amp; 0xe0000000)
multiline_comment|/*&n; * Returns the physical address of a KSEG0/KSEG1 address&n; */
DECL|macro|CPHYSADDR
mdefine_line|#define CPHYSADDR(a)&t;&t;(((unsigned long)(a)) &amp; 0x000000001fffffffUL)
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;&t;(((unsigned long)(a)) &amp; 0x000000ffffffffffUL)
multiline_comment|/*&n; * Map an address to a certain kernel segment&n; */
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x000000ffffffffffUL) | KSEG0))
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x000000ffffffffffUL) | KSEG1))
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x000000ffffffffffUL) | KSEG2))
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;((__typeof__(a))(((unsigned long)(a) &amp; 0x000000ffffffffffUL) | KSEG3))
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
macro_line|#if defined (CONFIG_CPU_R4300)&t;&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_R4X00)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_R5000)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_NEVADA)
DECL|macro|KUSIZE
mdefine_line|#define&t;KUSIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|KUSIZE_64
mdefine_line|#define&t;KUSIZE_64&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K0SIZE
mdefine_line|#define&t;K0SIZE&t;&t;0x0000001000000000&t;&t;/* 2^^36 */
DECL|macro|K1SIZE
mdefine_line|#define&t;K1SIZE&t;&t;0x0000001000000000&t;&t;/* 2^^36 */
DECL|macro|K2SIZE
mdefine_line|#define&t;K2SIZE&t;&t;0x000000ff80000000
DECL|macro|KSEGSIZE
mdefine_line|#define&t;KSEGSIZE&t;0x000000ff80000000&t;&t;/* max syssegsz */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;0x0000000fffffffff&t;&t;/* 2^^36 - 1 */
macro_line|#endif
macro_line|#if defined (CONFIG_CPU_R8000)
multiline_comment|/* We keep KUSIZE consistent with R4000 for now (2^^40) instead of (2^^48) */
DECL|macro|KUSIZE
mdefine_line|#define&t;KUSIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|KUSIZE_64
mdefine_line|#define&t;KUSIZE_64&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K0SIZE
mdefine_line|#define&t;K0SIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K1SIZE
mdefine_line|#define&t;K1SIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K2SIZE
mdefine_line|#define&t;K2SIZE&t;&t;0x0001000000000000
DECL|macro|KSEGSIZE
mdefine_line|#define&t;KSEGSIZE&t;0x0000010000000000&t;&t;/* max syssegsz */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;0x000000ffffffffff&t;&t;/* 2^^40 - 1 */
macro_line|#endif
macro_line|#if defined (CONFIG_CPU_R10000)
DECL|macro|KUSIZE
mdefine_line|#define&t;KUSIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|KUSIZE_64
mdefine_line|#define&t;KUSIZE_64&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K0SIZE
mdefine_line|#define&t;K0SIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K1SIZE
mdefine_line|#define&t;K1SIZE&t;&t;0x0000010000000000&t;&t;/* 2^^40 */
DECL|macro|K2SIZE
mdefine_line|#define&t;K2SIZE&t;&t;0x00000fff80000000
DECL|macro|KSEGSIZE
mdefine_line|#define&t;KSEGSIZE&t;0x00000fff80000000&t;&t;/* max syssegsz */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;0x000000ffffffffff&t;&t;/* 2^^40 - 1 */
macro_line|#endif
multiline_comment|/*&n; * Further names for SGI source compatibility.  These are stolen from&n; * IRIX&squot;s &lt;sys/mips_addrspace.h&gt;.&n; */
DECL|macro|KUBASE
mdefine_line|#define KUBASE&t;&t;0
DECL|macro|KUSIZE_32
mdefine_line|#define KUSIZE_32&t;0x0000000080000000&t;/* KUSIZE for a 32 bit proc */
DECL|macro|K0BASE
mdefine_line|#define K0BASE&t;&t;0xa800000000000000
DECL|macro|K0BASE_EXL_WR
mdefine_line|#define K0BASE_EXL_WR&t;K0BASE&t;&t;&t;/* exclusive on write */
DECL|macro|K0BASE_NONCOH
mdefine_line|#define K0BASE_NONCOH&t;0x9800000000000000&t;/* noncoherent */
DECL|macro|K0BASE_EXL
mdefine_line|#define K0BASE_EXL&t;0xa000000000000000&t;/* exclusive */
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|K1BASE
mdefine_line|#define K1BASE&t;&t;0x9600000000000000&t;/* Uncached attr 3, uncac */
macro_line|#else
DECL|macro|K1BASE
mdefine_line|#define K1BASE&t;&t;0x9000000000000000
macro_line|#endif
DECL|macro|K2BASE
mdefine_line|#define K2BASE&t;&t;0xc000000000000000
macro_line|#if !defined (CONFIG_CPU_R8000)
DECL|macro|COMPAT_K1BASE32
mdefine_line|#define COMPAT_K1BASE32&t;&t;0xffffffffa0000000
DECL|macro|PHYS_TO_COMPATK1
mdefine_line|#define PHYS_TO_COMPATK1(x)&t;((x) | COMPAT_K1BASE32) /* 32-bit compat k1 */
macro_line|#endif
DECL|macro|KDM_TO_PHYS
mdefine_line|#define KDM_TO_PHYS(x)&t;((unsigned long)(x) &amp; TO_PHYS_MASK)
DECL|macro|PHYS_TO_K0
mdefine_line|#define PHYS_TO_K0(x)&t;((unsigned long)(x) | K0BASE)
macro_line|#endif /* _ASM_ADDRSPACE_H */
eof
