multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; * Copyright (C) 2000, 2002  Maciej W. Rozycki&n; *&n; * Definitions for the address spaces of the MIPS CPUs.&n; */
macro_line|#ifndef __ASM_ADDRSPACE_H
DECL|macro|__ASM_ADDRSPACE_H
mdefine_line|#define __ASM_ADDRSPACE_H
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
mdefine_line|#define KUSEG&t;&t;&t;0x00000000
DECL|macro|KSEG0
mdefine_line|#define KSEG0&t;&t;&t;0x80000000
DECL|macro|KSEG1
mdefine_line|#define KSEG1&t;&t;&t;0xa0000000
DECL|macro|KSEG2
mdefine_line|#define KSEG2&t;&t;&t;0xc0000000
DECL|macro|KSEG3
mdefine_line|#define KSEG3&t;&t;&t;0xe0000000
DECL|macro|K0BASE
mdefine_line|#define K0BASE&t;&t;&t;KSEG0
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)&t;&t;((_ACAST32_ (a)) &amp; 0xe0000000)
multiline_comment|/*&n; * Returns the physical address of a KSEG0/KSEG1 address&n; */
DECL|macro|CPHYSADDR
mdefine_line|#define CPHYSADDR(a)&t;&t;((_ACAST32_ (a)) &amp; 0x1fffffff)
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;&t;CPHYSADDR(a)
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
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;&t;&t;0xfffffffffULL&t;&t;/* 36 bit */
multiline_comment|/*&n; * 64-bit address conversions&n; */
DECL|macro|PHYS_TO_XKSEG_UNCACHED
mdefine_line|#define PHYS_TO_XKSEG_UNCACHED(p)&t;PHYS_TO_XKPHYS(K_CALG_UNCACHED,(p))
DECL|macro|PHYS_TO_XKSEG_CACHED
mdefine_line|#define PHYS_TO_XKSEG_CACHED(p)&t;&t;PHYS_TO_XKPHYS(K_CALG_COH_SHAREABLE,(p))
DECL|macro|XKPHYS_TO_PHYS
mdefine_line|#define XKPHYS_TO_PHYS(p)&t;&t;((p) &amp; TO_PHYS_MASK)
DECL|macro|PHYS_TO_XKPHYS
mdefine_line|#define PHYS_TO_XKPHYS(cm,a)&t;&t;(0x8000000000000000 | ((cm)&lt;&lt;59) | (a))
macro_line|#endif /* __ASM_ADDRSPACE_H */
eof
