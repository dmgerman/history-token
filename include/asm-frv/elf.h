multiline_comment|/* elf.h: FR-V ELF definitions&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; * - Derived from include/asm-m68knommu/elf.h&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_ELF_H
DECL|macro|__ASM_ELF_H
mdefine_line|#define __ASM_ELF_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
r_struct
id|elf32_hdr
suffix:semicolon
multiline_comment|/*&n; * ELF header e_flags defines.&n; */
DECL|macro|EF_FRV_GPR_MASK
mdefine_line|#define EF_FRV_GPR_MASK         0x00000003 /* mask for # of gprs */
DECL|macro|EF_FRV_GPR32
mdefine_line|#define EF_FRV_GPR32&t;&t;0x00000001 /* Only uses GR on 32-register */
DECL|macro|EF_FRV_GPR64
mdefine_line|#define EF_FRV_GPR64&t;&t;0x00000002 /* Only uses GR on 64-register */
DECL|macro|EF_FRV_FPR_MASK
mdefine_line|#define EF_FRV_FPR_MASK         0x0000000c /* mask for # of fprs */
DECL|macro|EF_FRV_FPR32
mdefine_line|#define EF_FRV_FPR32&t;&t;0x00000004 /* Only uses FR on 32-register */
DECL|macro|EF_FRV_FPR64
mdefine_line|#define EF_FRV_FPR64&t;&t;0x00000008 /* Only uses FR on 64-register */
DECL|macro|EF_FRV_FPR_NONE
mdefine_line|#define EF_FRV_FPR_NONE&t;&t;0x0000000C /* Uses software floating-point */
DECL|macro|EF_FRV_DWORD_MASK
mdefine_line|#define EF_FRV_DWORD_MASK       0x00000030 /* mask for dword support */
DECL|macro|EF_FRV_DWORD_YES
mdefine_line|#define EF_FRV_DWORD_YES&t;0x00000010 /* Assumes stack aligned to 8-byte boundaries. */
DECL|macro|EF_FRV_DWORD_NO
mdefine_line|#define EF_FRV_DWORD_NO&t;&t;0x00000020 /* Assumes stack aligned to 4-byte boundaries. */
DECL|macro|EF_FRV_DOUBLE
mdefine_line|#define EF_FRV_DOUBLE&t;&t;0x00000040 /* Uses double instructions. */
DECL|macro|EF_FRV_MEDIA
mdefine_line|#define EF_FRV_MEDIA&t;&t;0x00000080 /* Uses media instructions. */
DECL|macro|EF_FRV_PIC
mdefine_line|#define EF_FRV_PIC&t;&t;0x00000100 /* Uses position independent code. */
DECL|macro|EF_FRV_NON_PIC_RELOCS
mdefine_line|#define EF_FRV_NON_PIC_RELOCS&t;0x00000200 /* Does not use position Independent code. */
DECL|macro|EF_FRV_MULADD
mdefine_line|#define EF_FRV_MULADD           0x00000400 /* -mmuladd */
DECL|macro|EF_FRV_BIGPIC
mdefine_line|#define EF_FRV_BIGPIC           0x00000800 /* -fPIC */
DECL|macro|EF_FRV_LIBPIC
mdefine_line|#define EF_FRV_LIBPIC           0x00001000 /* -mlibrary-pic */
DECL|macro|EF_FRV_G0
mdefine_line|#define EF_FRV_G0               0x00002000 /* -G 0, no small data ptr */
DECL|macro|EF_FRV_NOPACK
mdefine_line|#define EF_FRV_NOPACK           0x00004000 /* -mnopack */
DECL|macro|EF_FRV_FDPIC
mdefine_line|#define EF_FRV_FDPIC            0x00008000 /* -mfdpic */
DECL|macro|EF_FRV_CPU_MASK
mdefine_line|#define EF_FRV_CPU_MASK         0xff000000 /* specific cpu bits */
DECL|macro|EF_FRV_CPU_GENERIC
mdefine_line|#define EF_FRV_CPU_GENERIC&t;0x00000000 /* Set CPU type is FR-V */
DECL|macro|EF_FRV_CPU_FR500
mdefine_line|#define EF_FRV_CPU_FR500&t;0x01000000 /* Set CPU type is FR500 */
DECL|macro|EF_FRV_CPU_FR300
mdefine_line|#define EF_FRV_CPU_FR300&t;0x02000000 /* Set CPU type is FR300 */
DECL|macro|EF_FRV_CPU_SIMPLE
mdefine_line|#define EF_FRV_CPU_SIMPLE       0x03000000 /* SIMPLE */
DECL|macro|EF_FRV_CPU_TOMCAT
mdefine_line|#define EF_FRV_CPU_TOMCAT       0x04000000 /* Tomcat, FR500 prototype */
DECL|macro|EF_FRV_CPU_FR400
mdefine_line|#define EF_FRV_CPU_FR400&t;0x05000000 /* Set CPU type is FR400 */
DECL|macro|EF_FRV_CPU_FR550
mdefine_line|#define EF_FRV_CPU_FR550        0x06000000 /* Set CPU type is FR550 */
DECL|macro|EF_FRV_CPU_FR405
mdefine_line|#define EF_FRV_CPU_FR405&t;0x07000000 /* Set CPU type is FR405 */
DECL|macro|EF_FRV_CPU_FR450
mdefine_line|#define EF_FRV_CPU_FR450&t;0x08000000 /* Set CPU type is FR450 */
multiline_comment|/*&n; * FR-V ELF relocation types&n; */
multiline_comment|/*&n; * ELF register definitions..&n; */
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof(struct pt_regs) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|fpmedia_struct
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
r_extern
r_int
id|elf_check_arch
c_func
(paren
r_const
r_struct
id|elf32_hdr
op_star
id|hdr
)paren
suffix:semicolon
DECL|macro|elf_check_fdpic
mdefine_line|#define elf_check_fdpic(x) ((x)-&gt;e_flags &amp; EF_FRV_FDPIC &amp;&amp; !((x)-&gt;e_flags &amp; EF_FRV_NON_PIC_RELOCS))
DECL|macro|elf_check_const_displacement
mdefine_line|#define elf_check_const_displacement(x) ((x)-&gt;e_flags &amp; EF_FRV_PIC)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_FRV
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr16&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr17&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr18&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr19&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr20&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr21&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr22&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr23&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr24&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr25&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr26&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr27&t;= 0;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr29&t;= 0;&t;&bslash;&n;} while(0)
DECL|macro|ELF_FDPIC_PLAT_INIT
mdefine_line|#define ELF_FDPIC_PLAT_INIT(_regs, _exec_map_addr, _interp_map_addr, _dynamic_addr)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr16&t;= _exec_map_addr;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr17&t;= _interp_map_addr;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr18&t;= _dynamic_addr;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr19&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr20&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr21&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr22&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr23&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr24&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr25&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr26&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr27&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_frame0_ptr-&gt;gr29&t;= 0;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;16384
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         0x08000000UL
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)&t;&t;&t;&t;&bslash;&n;&t;memcpy(&amp;pr_reg[0], &amp;regs-&gt;sp, 31 * sizeof(uint32_t));
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif
eof
