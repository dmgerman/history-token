multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 99 Ralf Baechle&n; * Copyright (C) 2000, 2002  Maciej W. Rozycki&n; * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_ADDRSPACE_H
DECL|macro|_ASM_ADDRSPACE_H
mdefine_line|#define _ASM_ADDRSPACE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;spaces.h&gt;
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
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)&t;&t;((_ACAST32_ (a)) &amp; 0xe0000000)
multiline_comment|/*&n; * Returns the physical address of a CKSEGx / XKPHYS address&n; */
DECL|macro|CPHYSADDR
mdefine_line|#define CPHYSADDR(a)&t;&t;((_ACAST32_ (a)) &amp; 0x1fffffff)
DECL|macro|XPHYSADDR
mdefine_line|#define XPHYSADDR(a)            ((_ACAST64_ (a)) &amp; 0x000000ffffffffff)
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n; * Memory segments (64bit kernel mode addresses)&n; * The compatibility segments use the full 64-bit sign extended value.  Note&n; * the R8000 doesn&squot;t have them so don&squot;t reference these in generic MIPS code.&n; */
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
DECL|macro|CKSEG0ADDR
mdefine_line|#define CKSEG0ADDR(a)&t;&t;(CPHYSADDR(a) | CKSEG0)
DECL|macro|CKSEG1ADDR
mdefine_line|#define CKSEG1ADDR(a)&t;&t;(CPHYSADDR(a) | CKSEG1)
DECL|macro|CKSEG2ADDR
mdefine_line|#define CKSEG2ADDR(a)&t;&t;(CPHYSADDR(a) | CKSEG2)
DECL|macro|CKSEG3ADDR
mdefine_line|#define CKSEG3ADDR(a)&t;&t;(CPHYSADDR(a) | CKSEG3)
macro_line|#else
DECL|macro|CKSEG0ADDR
mdefine_line|#define CKSEG0ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG0)
DECL|macro|CKSEG1ADDR
mdefine_line|#define CKSEG1ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG1)
DECL|macro|CKSEG2ADDR
mdefine_line|#define CKSEG2ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG2)
DECL|macro|CKSEG3ADDR
mdefine_line|#define CKSEG3ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG3)
multiline_comment|/*&n; * Map an address to a certain kernel segment&n; */
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG0)
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG1)
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG2)
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;(CPHYSADDR(a) | KSEG3)
multiline_comment|/*&n; * Memory segments (32bit kernel mode addresses)&n; * These are the traditional names used in the 32-bit universe.&n; */
DECL|macro|KUSEG
mdefine_line|#define KUSEG&t;&t;&t;0x00000000
DECL|macro|KSEG0
mdefine_line|#define KSEG0&t;&t;&t;0x80000000
DECL|macro|KSEG1
mdefine_line|#define KSEG1&t;&t;&t;0xa0000000
DECL|macro|KSEG2
mdefine_line|#define KSEG2&t;&t;&t;0xc0000000
DECL|macro|KSEG3
mdefine_line|#define KSEG3&t;&t;&t;0xe0000000
DECL|macro|CKUSEG
mdefine_line|#define CKUSEG&t;&t;&t;0x00000000
DECL|macro|CKSEG0
mdefine_line|#define CKSEG0&t;&t;&t;0x80000000
DECL|macro|CKSEG1
mdefine_line|#define CKSEG1&t;&t;&t;0xa0000000
DECL|macro|CKSEG2
mdefine_line|#define CKSEG2&t;&t;&t;0xc0000000
DECL|macro|CKSEG3
mdefine_line|#define CKSEG3&t;&t;&t;0xe0000000
macro_line|#endif
multiline_comment|/*&n; * Cache modes for XKPHYS address conversion macros&n; */
DECL|macro|K_CALG_COH_EXCL1_NOL2
mdefine_line|#define K_CALG_COH_EXCL1_NOL2&t;0
DECL|macro|K_CALG_COH_SHRL1_NOL2
mdefine_line|#define K_CALG_COH_SHRL1_NOL2&t;1
DECL|macro|K_CALG_UNCACHED
mdefine_line|#define K_CALG_UNCACHED&t;&t;2
DECL|macro|K_CALG_NONCOHERENT
mdefine_line|#define K_CALG_NONCOHERENT&t;3
DECL|macro|K_CALG_COH_EXCL
mdefine_line|#define K_CALG_COH_EXCL&t;&t;4
DECL|macro|K_CALG_COH_SHAREABLE
mdefine_line|#define K_CALG_COH_SHAREABLE&t;5
DECL|macro|K_CALG_NOTUSED
mdefine_line|#define K_CALG_NOTUSED&t;&t;6
DECL|macro|K_CALG_UNCACHED_ACCEL
mdefine_line|#define K_CALG_UNCACHED_ACCEL&t;7
multiline_comment|/*&n; * 64-bit address conversions&n; */
DECL|macro|PHYS_TO_XKSEG_UNCACHED
mdefine_line|#define PHYS_TO_XKSEG_UNCACHED(p)&t;PHYS_TO_XKPHYS(K_CALG_UNCACHED,(p))
DECL|macro|PHYS_TO_XKSEG_CACHED
mdefine_line|#define PHYS_TO_XKSEG_CACHED(p)&t;&t;PHYS_TO_XKPHYS(K_CALG_COH_SHAREABLE,(p))
DECL|macro|XKPHYS_TO_PHYS
mdefine_line|#define XKPHYS_TO_PHYS(p)&t;&t;((p) &amp; TO_PHYS_MASK)
DECL|macro|PHYS_TO_XKPHYS
mdefine_line|#define PHYS_TO_XKPHYS(cm,a)&t;&t;(0x8000000000000000 | ((cm)&lt;&lt;59) | (a))
macro_line|#if defined (CONFIG_CPU_R4300)&t;&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_R4X00)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_R5000)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_NEVADA)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_TX49XX)&t;&t;&t;&t;&t;&bslash;&n;    || defined (CONFIG_CPU_MIPS64)
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
DECL|macro|K0BASE_EXL_WR
mdefine_line|#define K0BASE_EXL_WR&t;&t;0xa800000000000000&t;/* exclusive on write */
DECL|macro|K0BASE_NONCOH
mdefine_line|#define K0BASE_NONCOH&t;&t;0x9800000000000000&t;/* noncoherent */
DECL|macro|K0BASE_EXL
mdefine_line|#define K0BASE_EXL&t;&t;0xa000000000000000&t;/* exclusive */
macro_line|#ifndef CONFIG_CPU_R8000
multiline_comment|/*&n; * The R8000 doesn&squot;t have the 32-bit compat spaces so we don&squot;t define them&n; * in order to catch bugs in the source code.&n; */
DECL|macro|COMPAT_K1BASE32
mdefine_line|#define COMPAT_K1BASE32&t;&t;0xffffffffa0000000
DECL|macro|PHYS_TO_COMPATK1
mdefine_line|#define PHYS_TO_COMPATK1(x)&t;((x) | COMPAT_K1BASE32) /* 32-bit compat k1 */
macro_line|#endif
DECL|macro|KDM_TO_PHYS
mdefine_line|#define KDM_TO_PHYS(x)&t;&t;(_ACAST64_ (x) &amp; TO_PHYS_MASK)
DECL|macro|PHYS_TO_K0
mdefine_line|#define PHYS_TO_K0(x)&t;&t;(_ACAST64_ (x) | CAC_BASE)
macro_line|#endif /* _ASM_ADDRSPACE_H */
eof
