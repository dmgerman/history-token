multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1999 by Ralf Baechle&n; * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.&n; * Copyright (C) 2002  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_ADDRSPACE_H
DECL|macro|__ASM_ADDRSPACE_H
mdefine_line|#define __ASM_ADDRSPACE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *  Configure language&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_ATYPE_
mdefine_line|#define _ATYPE_
DECL|macro|_ATYPE32_
mdefine_line|#define _ATYPE32_
DECL|macro|_ATYPE64_
mdefine_line|#define _ATYPE64_
macro_line|#else
DECL|macro|_ATYPE_
mdefine_line|#define _ATYPE_&t;&t;__PTRDIFF_TYPE__
DECL|macro|_ATYPE32_
mdefine_line|#define _ATYPE32_&t;int
DECL|macro|_ATYPE64_
mdefine_line|#define _ATYPE64_&t;long long
macro_line|#endif
multiline_comment|/*&n; *  32-bit MIPS address spaces&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_ACAST32_
mdefine_line|#define _ACAST32_
DECL|macro|_ACAST64_
mdefine_line|#define _ACAST64_
macro_line|#else
DECL|macro|_ACAST32_
mdefine_line|#define _ACAST32_&t;&t;(_ATYPE_)(_ATYPE32_)&t;/* widen if necessary */
DECL|macro|_ACAST64_
mdefine_line|#define _ACAST64_&t;&t;(_ATYPE64_)&t;&t;/* do _not_ narrow */
macro_line|#endif
multiline_comment|/*&n; * Memory segments (32bit kernel mode addresses)&n; */
DECL|macro|KUSEG
mdefine_line|#define KUSEG&t;&t;&t;0x0000000000000000
DECL|macro|KSEG0
mdefine_line|#define KSEG0&t;&t;&t;0xffffffff80000000
DECL|macro|KSEG1
mdefine_line|#define KSEG1&t;&t;&t;0xffffffffa0000000
DECL|macro|KSEG2
mdefine_line|#define KSEG2&t;&t;&t;0xffffffffc0000000
DECL|macro|KSEG3
mdefine_line|#define KSEG3&t;&t;&t;0xffffffffe0000000
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)&t;&t;((_ACAST64_ (a)) &amp; 0xffffffffe0000000)
multiline_comment|/*&n; * Returns the physical address of a KSEG0/KSEG1 address&n; */
DECL|macro|XPHYSADDR
mdefine_line|#define XPHYSADDR(a)&t;&t;((_ACAST64_ (a)) &amp; 0x000000ffffffffff)
DECL|macro|CPHYSADDR
mdefine_line|#define CPHYSADDR(a)&t;&t;((_ACAST64_ (a)) &amp; 0x000000001fffffff)
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a) ({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const _ATYPE64_ _a = _ACAST64_ (a);&t;&t;&t;&bslash;&n;&t;_a == _ACAST32_ _a ? CPHYSADDR(_a) : XPHYSADDR(_a); })
multiline_comment|/*&n; * Map an address to a certain kernel segment&n; */
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG0)
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG1)
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG2)
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG3)
multiline_comment|/*&n; * Memory segments (64bit kernel mode addresses)&n; */
DECL|macro|XKUSEG
mdefine_line|#define XKUSEG&t;&t;&t;0x0000000000000000
DECL|macro|XKSSEG
mdefine_line|#define XKSSEG&t;&t;&t;0x4000000000000000
DECL|macro|XKPHYS
mdefine_line|#define XKPHYS&t;&t;&t;0x8000000000000000
DECL|macro|XKSEG
mdefine_line|#define XKSEG&t;&t;&t;0xc000000000000000
DECL|macro|CKSEG0
mdefine_line|#define CKSEG0&t;&t;&t;0xffffffff80000000
DECL|macro|CKSEG1
mdefine_line|#define CKSEG1&t;&t;&t;0xffffffffa0000000
DECL|macro|CKSSEG
mdefine_line|#define CKSSEG&t;&t;&t;0xffffffffc0000000
DECL|macro|CKSEG3
mdefine_line|#define CKSEG3&t;&t;&t;0xffffffffe0000000
macro_line|#if defined (CONFIG_CPU_R4300)&t;&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_R4X00)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_R5000)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_NEVADA)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_MIPS64)
DECL|macro|KUSIZE
mdefine_line|#define&t;KUSIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|KUSIZE_64
mdefine_line|#define&t;KUSIZE_64&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K0SIZE
mdefine_line|#define&t;K0SIZE&t;&t;&t;0x0000001000000000&t;/* 2^^36 */
DECL|macro|K1SIZE
mdefine_line|#define&t;K1SIZE&t;&t;&t;0x0000001000000000&t;/* 2^^36 */
DECL|macro|K2SIZE
mdefine_line|#define&t;K2SIZE&t;&t;&t;0x000000ff80000000
DECL|macro|KSEGSIZE
mdefine_line|#define&t;KSEGSIZE&t;&t;0x000000ff80000000&t;/* max syssegsz */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;&t;0x0000000fffffffff&t;/* 2^^36 - 1 */
macro_line|#endif
macro_line|#if defined (CONFIG_CPU_R8000)
multiline_comment|/* We keep KUSIZE consistent with R4000 for now (2^^40) instead of (2^^48) */
DECL|macro|KUSIZE
mdefine_line|#define&t;KUSIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|KUSIZE_64
mdefine_line|#define&t;KUSIZE_64&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K0SIZE
mdefine_line|#define&t;K0SIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K1SIZE
mdefine_line|#define&t;K1SIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K2SIZE
mdefine_line|#define&t;K2SIZE&t;&t;&t;0x0001000000000000
DECL|macro|KSEGSIZE
mdefine_line|#define&t;KSEGSIZE&t;&t;0x0000010000000000&t;/* max syssegsz */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;&t;0x000000ffffffffff&t;/* 2^^40 - 1 */
macro_line|#endif
macro_line|#if defined (CONFIG_CPU_R10000)
DECL|macro|KUSIZE
mdefine_line|#define&t;KUSIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|KUSIZE_64
mdefine_line|#define&t;KUSIZE_64&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K0SIZE
mdefine_line|#define&t;K0SIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K1SIZE
mdefine_line|#define&t;K1SIZE&t;&t;&t;0x0000010000000000&t;/* 2^^40 */
DECL|macro|K2SIZE
mdefine_line|#define&t;K2SIZE&t;&t;&t;0x00000fff80000000
DECL|macro|KSEGSIZE
mdefine_line|#define&t;KSEGSIZE&t;&t;0x00000fff80000000&t;/* max syssegsz */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;&t;0x000000ffffffffff&t;/* 2^^40 - 1 */
macro_line|#endif
multiline_comment|/*&n; * Further names for SGI source compatibility.  These are stolen from&n; * IRIX&squot;s &lt;sys/mips_addrspace.h&gt;.&n; */
DECL|macro|KUBASE
mdefine_line|#define KUBASE&t;&t;&t;0
DECL|macro|KUSIZE_32
mdefine_line|#define KUSIZE_32&t;&t;0x0000000080000000&t;/* KUSIZE&n;&t;&t;&t;&t;&t;&t;&t;   for a 32 bit proc */
DECL|macro|K0BASE
mdefine_line|#define K0BASE&t;&t;&t;0xa800000000000000
DECL|macro|K0BASE_EXL_WR
mdefine_line|#define K0BASE_EXL_WR&t;&t;K0BASE&t;&t;&t;/* exclusive on write */
DECL|macro|K0BASE_NONCOH
mdefine_line|#define K0BASE_NONCOH&t;&t;0x9800000000000000&t;/* noncoherent */
DECL|macro|K0BASE_EXL
mdefine_line|#define K0BASE_EXL&t;&t;0xa000000000000000&t;/* exclusive */
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|K1BASE
mdefine_line|#define K1BASE&t;&t;&t;0x9600000000000000&t;/* uncached attr 3,&n;&t;&t;&t;&t;&t;&t;&t;   uncac */
macro_line|#else
DECL|macro|K1BASE
mdefine_line|#define K1BASE&t;&t;&t;0x9000000000000000
macro_line|#endif
DECL|macro|K2BASE
mdefine_line|#define K2BASE&t;&t;&t;0xc000000000000000
macro_line|#if !defined (CONFIG_CPU_R8000)
DECL|macro|COMPAT_K1BASE32
mdefine_line|#define COMPAT_K1BASE32&t;&t;0xffffffffa0000000
DECL|macro|PHYS_TO_COMPATK1
mdefine_line|#define PHYS_TO_COMPATK1(x)&t;((x) | COMPAT_K1BASE32) /* 32-bit compat k1 */
macro_line|#endif
DECL|macro|KDM_TO_PHYS
mdefine_line|#define KDM_TO_PHYS(x)&t;&t;(_ACAST64_ (x) &amp; TO_PHYS_MASK)
DECL|macro|PHYS_TO_K0
mdefine_line|#define PHYS_TO_K0(x)&t;&t;(_ACAST64_ (x) | K0BASE)
macro_line|#endif /* __ASM_ADDRSPACE_H */
eof
