macro_line|#ifndef _ASM_IA64_ELF_H
DECL|macro|_ASM_IA64_ELF_H
mdefine_line|#define _ASM_IA64_ELF_H
multiline_comment|/*&n; * ELF archtecture specific definitions.&n; *&n; * Copyright (C) 1998, 1999, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_IA_64)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_IA_64
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
multiline_comment|/* Least-significant four bits of ELF header&squot;s e_flags are OS-specific.  The bits are&n;   interpreted as follows by Linux: */
DECL|macro|EF_IA_64_LINUX_EXECUTABLE_STACK
mdefine_line|#define EF_IA_64_LINUX_EXECUTABLE_STACK&t;0x1&t;/* is stack (&amp; heap) executable by default? */
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;PAGE_SIZE
multiline_comment|/*&n; * This is the location that an ET_DYN program is loaded if exec&squot;ed.&n; * Typical use of this is to invoke &quot;./ld.so someprog&quot; to test out a&n; * new version of the loader.  We need to make sure that it is out of&n; * the way of the program that it will &quot;exec&quot;, and that there is&n; * sufficient room for the brk.&n; */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(TASK_UNMAPPED_BASE + 0x1000000)
multiline_comment|/*&n; * We use (abuse?) this macro to insert the (empty) vm_area that is&n; * used to map the register backing store.  I don&squot;t see any better&n; * place to do this, but we should discuss this with Linus once we can&n; * talk to him...&n; */
r_extern
r_void
id|ia64_init_addr_space
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;ia64_init_addr_space()
multiline_comment|/* ELF register definitions.  This is needed for core dump support.  */
multiline_comment|/*&n; * elf_gregset_t contains the application-level state in the following order:&n; *&t;r0-r31&n; *&t;NaT bits (for r0-r31; bit N == 1 iff rN is a NaT)&n; *&t;predicate registers (p0-p63)&n; *&t;b0-b7&n; *&t;ip cfm psr&n; *&t;ar.rsc ar.bsp ar.bspstore ar.rnat&n; *&t;ar.ccv ar.unat ar.fpsr ar.pfs ar.lc ar.ec&n; */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;128&t;/* we really need just 72 but let&squot;s leave some headroom... */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;128&t;/* f0 and f1 could be omitted, but so what... */
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_fpreg_t
r_typedef
r_struct
id|ia64_fpreg
id|elf_fpreg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
id|elf_fpreg_t
id|elf_fpregset_t
(braket
id|ELF_NFPREG
)braket
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/* forward declaration... */
r_extern
r_void
id|ia64_elf_core_copy_regs
(paren
r_struct
id|pt_regs
op_star
id|src
comma
id|elf_gregset_t
id|dst
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(_dest,_regs)&t;ia64_elf_core_copy_regs(_regs, _dest);
multiline_comment|/* This macro yields a bitmask that programs can use to figure out&n;   what instruction set this CPU supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP &t;0
multiline_comment|/* This macro yields a string that ld.so will use to load&n;   implementation specific libraries for optimization.  Not terribly&n;   relevant until we have real hardware to play with... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;0
macro_line|#ifdef __KERNEL__
r_struct
id|elf64_hdr
suffix:semicolon
r_extern
r_void
id|ia64_set_personality
(paren
r_struct
id|elf64_hdr
op_star
id|elf_ex
comma
r_int
id|ibcs2_interpreter
)paren
suffix:semicolon
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;ia64_set_personality(&amp;(ex), ibcs2)
macro_line|#endif
macro_line|#endif /* _ASM_IA64_ELF_H */
eof
