multiline_comment|/*&n; *  include/asm-s390/elf.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/elf.h&quot;&n; */
macro_line|#ifndef __ASMS390_ELF_H
DECL|macro|__ASMS390_ELF_H
mdefine_line|#define __ASMS390_ELF_H
multiline_comment|/* s390 relocations defined by the ABIs */
DECL|macro|R_390_NONE
mdefine_line|#define R_390_NONE&t;&t;0&t;/* No reloc.  */
DECL|macro|R_390_8
mdefine_line|#define R_390_8&t;&t;&t;1&t;/* Direct 8 bit.  */
DECL|macro|R_390_12
mdefine_line|#define R_390_12&t;&t;2&t;/* Direct 12 bit.  */
DECL|macro|R_390_16
mdefine_line|#define R_390_16&t;&t;3&t;/* Direct 16 bit.  */
DECL|macro|R_390_32
mdefine_line|#define R_390_32&t;&t;4&t;/* Direct 32 bit.  */
DECL|macro|R_390_PC32
mdefine_line|#define R_390_PC32&t;&t;5&t;/* PC relative 32 bit.&t;*/
DECL|macro|R_390_GOT12
mdefine_line|#define R_390_GOT12&t;&t;6&t;/* 12 bit GOT offset.  */
DECL|macro|R_390_GOT32
mdefine_line|#define R_390_GOT32&t;&t;7&t;/* 32 bit GOT offset.  */
DECL|macro|R_390_PLT32
mdefine_line|#define R_390_PLT32&t;&t;8&t;/* 32 bit PC relative PLT address.  */
DECL|macro|R_390_COPY
mdefine_line|#define R_390_COPY&t;&t;9&t;/* Copy symbol at runtime.  */
DECL|macro|R_390_GLOB_DAT
mdefine_line|#define R_390_GLOB_DAT&t;&t;10&t;/* Create GOT entry.  */
DECL|macro|R_390_JMP_SLOT
mdefine_line|#define R_390_JMP_SLOT&t;&t;11&t;/* Create PLT entry.  */
DECL|macro|R_390_RELATIVE
mdefine_line|#define R_390_RELATIVE&t;&t;12&t;/* Adjust by program base.  */
DECL|macro|R_390_GOTOFF32
mdefine_line|#define R_390_GOTOFF32&t;&t;13&t;/* 32 bit offset to GOT.&t; */
DECL|macro|R_390_GOTPC
mdefine_line|#define R_390_GOTPC&t;&t;14&t;/* 32 bit PC rel. offset to GOT.  */
DECL|macro|R_390_GOT16
mdefine_line|#define R_390_GOT16&t;&t;15&t;/* 16 bit GOT offset.  */
DECL|macro|R_390_PC16
mdefine_line|#define R_390_PC16&t;&t;16&t;/* PC relative 16 bit.&t;*/
DECL|macro|R_390_PC16DBL
mdefine_line|#define R_390_PC16DBL&t;&t;17&t;/* PC relative 16 bit shifted by 1.  */
DECL|macro|R_390_PLT16DBL
mdefine_line|#define R_390_PLT16DBL&t;&t;18&t;/* 16 bit PC rel. PLT shifted by 1.  */
DECL|macro|R_390_PC32DBL
mdefine_line|#define R_390_PC32DBL&t;&t;19&t;/* PC relative 32 bit shifted by 1.  */
DECL|macro|R_390_PLT32DBL
mdefine_line|#define R_390_PLT32DBL&t;&t;20&t;/* 32 bit PC rel. PLT shifted by 1.  */
DECL|macro|R_390_GOTPCDBL
mdefine_line|#define R_390_GOTPCDBL&t;&t;21&t;/* 32 bit PC rel. GOT shifted by 1.  */
DECL|macro|R_390_64
mdefine_line|#define R_390_64&t;&t;22&t;/* Direct 64 bit.  */
DECL|macro|R_390_PC64
mdefine_line|#define R_390_PC64&t;&t;23&t;/* PC relative 64 bit.&t;*/
DECL|macro|R_390_GOT64
mdefine_line|#define R_390_GOT64&t;&t;24&t;/* 64 bit GOT offset.  */
DECL|macro|R_390_PLT64
mdefine_line|#define R_390_PLT64&t;&t;25&t;/* 64 bit PC relative PLT address.  */
DECL|macro|R_390_GOTENT
mdefine_line|#define R_390_GOTENT&t;&t;26&t;/* 32 bit PC rel. to GOT entry &gt;&gt; 1. */
DECL|macro|R_390_GOTOFF16
mdefine_line|#define R_390_GOTOFF16&t;&t;27&t;/* 16 bit offset to GOT. */
DECL|macro|R_390_GOTOFF64
mdefine_line|#define R_390_GOTOFF64&t;&t;28&t;/* 64 bit offset to GOT. */
DECL|macro|R_390_GOTPLT12
mdefine_line|#define R_390_GOTPLT12&t;&t;29&t;/* 12 bit offset to jump slot.&t;*/
DECL|macro|R_390_GOTPLT16
mdefine_line|#define R_390_GOTPLT16&t;&t;30&t;/* 16 bit offset to jump slot.&t;*/
DECL|macro|R_390_GOTPLT32
mdefine_line|#define R_390_GOTPLT32&t;&t;31&t;/* 32 bit offset to jump slot.&t;*/
DECL|macro|R_390_GOTPLT64
mdefine_line|#define R_390_GOTPLT64&t;&t;32&t;/* 64 bit offset to jump slot.&t;*/
DECL|macro|R_390_GOTPLTENT
mdefine_line|#define R_390_GOTPLTENT&t;&t;33&t;/* 32 bit rel. offset to jump slot.  */
DECL|macro|R_390_PLTOFF16
mdefine_line|#define R_390_PLTOFF16&t;&t;34&t;/* 16 bit offset from GOT to PLT. */
DECL|macro|R_390_PLTOFF32
mdefine_line|#define R_390_PLTOFF32&t;&t;35&t;/* 32 bit offset from GOT to PLT. */
DECL|macro|R_390_PLTOFF64
mdefine_line|#define R_390_PLTOFF64&t;&t;36&t;/* 16 bit offset from GOT to PLT. */
DECL|macro|R_390_TLS_LOAD
mdefine_line|#define R_390_TLS_LOAD&t;&t;37&t;/* Tag for load insn in TLS code. */
DECL|macro|R_390_TLS_GDCALL
mdefine_line|#define R_390_TLS_GDCALL&t;38&t;/* Tag for function call in general&n;                                           dynamic TLS code.  */
DECL|macro|R_390_TLS_LDCALL
mdefine_line|#define R_390_TLS_LDCALL&t;39&t;/* Tag for function call in local&n;                                           dynamic TLS code.  */
DECL|macro|R_390_TLS_GD32
mdefine_line|#define R_390_TLS_GD32&t;&t;40&t;/* Direct 32 bit for general dynamic&n;                                           thread local data.  */
DECL|macro|R_390_TLS_GD64
mdefine_line|#define R_390_TLS_GD64&t;&t;41&t;/* Direct 64 bit for general dynamic&n;                                           thread local data.  */
DECL|macro|R_390_TLS_GOTIE12
mdefine_line|#define R_390_TLS_GOTIE12&t;42&t;/* 12 bit GOT offset for static TLS&n;                                           block offset.  */
DECL|macro|R_390_TLS_GOTIE32
mdefine_line|#define R_390_TLS_GOTIE32&t;43&t;/* 32 bit GOT offset for static TLS&n;                                           block offset.  */
DECL|macro|R_390_TLS_GOTIE64
mdefine_line|#define R_390_TLS_GOTIE64&t;44&t;/* 64 bit GOT offset for static TLS&n;                                           block offset.  */
DECL|macro|R_390_TLS_LDM32
mdefine_line|#define R_390_TLS_LDM32&t;&t;45&t;/* Direct 32 bit for local dynamic&n;                                           thread local data in LD code.  */
DECL|macro|R_390_TLS_LDM64
mdefine_line|#define R_390_TLS_LDM64&t;&t;46&t;/* Direct 64 bit for local dynamic&n;                                           thread local data in LD code.  */
DECL|macro|R_390_TLS_IE32
mdefine_line|#define R_390_TLS_IE32&t;&t;47&t;/* 32 bit address of GOT entry for&n;                                           negated static TLS block offset.  */
DECL|macro|R_390_TLS_IE64
mdefine_line|#define R_390_TLS_IE64&t;&t;48&t;/* 64 bit address of GOT entry for&n;                                           negated static TLS block offset.  */
DECL|macro|R_390_TLS_IEENT
mdefine_line|#define R_390_TLS_IEENT&t;&t;49&t;/* 32 bit rel. offset to GOT entry for&n;                                           negated static TLS block offset.  */
DECL|macro|R_390_TLS_LE32
mdefine_line|#define R_390_TLS_LE32&t;&t;50&t;/* 32 bit negated offset relative to&n;                                           static TLS block.  */
DECL|macro|R_390_TLS_LE64
mdefine_line|#define R_390_TLS_LE64&t;&t;51&t;/* 64 bit negated offset relative to&n;                                           static TLS block.  */
DECL|macro|R_390_TLS_LDO32
mdefine_line|#define R_390_TLS_LDO32&t;&t;52&t;/* 32 bit offset relative to TLS&n;                                           block.  */
DECL|macro|R_390_TLS_LDO64
mdefine_line|#define R_390_TLS_LDO64&t;&t;53&t;/* 64 bit offset relative to TLS&n;                                           block.  */
DECL|macro|R_390_TLS_DTPMOD
mdefine_line|#define R_390_TLS_DTPMOD&t;54&t;/* ID of module containing symbol.  */
DECL|macro|R_390_TLS_DTPOFF
mdefine_line|#define R_390_TLS_DTPOFF&t;55&t;/* Offset in TLS block.  */
DECL|macro|R_390_TLS_TPOFF
mdefine_line|#define R_390_TLS_TPOFF&t;&t;56&t;/* Negate offset in static TLS&n;                                           block.  */
DECL|macro|R_390_20
mdefine_line|#define R_390_20&t;&t;57&t;/* Direct 20 bit.  */
DECL|macro|R_390_GOT20
mdefine_line|#define R_390_GOT20&t;&t;58&t;/* 20 bit GOT offset.  */
DECL|macro|R_390_GOTPLT20
mdefine_line|#define R_390_GOTPLT20&t;&t;59&t;/* 20 bit offset to jump slot.  */
DECL|macro|R_390_TLS_GOTIE20
mdefine_line|#define R_390_TLS_GOTIE20&t;60&t;/* 20 bit GOT offset for static TLS&n;&t;&t;&t;&t;&t;   block offset.  */
multiline_comment|/* Keep this the last entry.  */
DECL|macro|R_390_NUM
mdefine_line|#define R_390_NUM&t;61
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for save_access_regs */
DECL|typedef|elf_fpregset_t
r_typedef
id|s390_fp_regs
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|s390_regs
id|elf_gregset_t
suffix:semicolon
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
macro_line|#ifndef __s390x__
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#else /* __s390x__ */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
macro_line|#endif /* __s390x__ */
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_S390
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;(((x)-&gt;e_machine == EM_S390 || (x)-&gt;e_machine == EM_S390_OLD) &bslash;&n;         &amp;&amp; (x)-&gt;e_ident[EI_CLASS] == ELF_CLASS) 
multiline_comment|/* For SVR4/S390 the function pointer to be registered with `atexit` is&n;   passed in R14. */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr) &bslash;&n;&t;do { &bslash;&n;&t;&t;_r-&gt;gprs[14] = 0; &bslash;&n;&t;} while (0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
macro_line|#ifndef __s390x__
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         ((TASK_SIZE &amp; 0x80000000) &bslash;&n;                                ? TASK_SIZE / 3 * 2 &bslash;&n;                                : 2 * TASK_SIZE / 3)
macro_line|#else /* __s390x__ */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
macro_line|#endif /* __s390x__ */
multiline_comment|/* Wow, the &quot;main&quot; arch needs arch dependent functions too.. :) */
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|function|dump_regs
r_static
r_inline
r_int
id|dump_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|ptregs
comma
id|elf_gregset_t
op_star
id|regs
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;psw
comma
op_amp
id|ptregs-&gt;psw
comma
r_sizeof
(paren
id|regs-&gt;psw
)paren
op_plus
r_sizeof
(paren
id|regs-&gt;gprs
)paren
)paren
suffix:semicolon
id|save_access_regs
c_func
(paren
id|regs-&gt;acrs
)paren
suffix:semicolon
id|regs-&gt;orig_gpr2
op_assign
id|ptregs-&gt;orig_gpr2
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs) dump_regs(regs, &amp;pr_reg);
DECL|function|dump_task_regs
r_static
r_inline
r_int
id|dump_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_gregset_t
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|ptregs
op_assign
id|__KSTK_PTREGS
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;psw
comma
op_amp
id|ptregs-&gt;psw
comma
r_sizeof
(paren
id|regs-&gt;psw
)paren
op_plus
r_sizeof
(paren
id|regs-&gt;gprs
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|regs-&gt;acrs
comma
id|tsk-&gt;thread.acrs
comma
r_sizeof
(paren
id|regs-&gt;acrs
)paren
)paren
suffix:semicolon
id|regs-&gt;orig_gpr2
op_assign
id|ptregs-&gt;orig_gpr2
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(tsk, regs) dump_task_regs(tsk, regs)
DECL|function|dump_task_fpu
r_static
r_inline
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
(brace
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|save_fp_regs
c_func
(paren
id|fpregs
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|fpregs
comma
op_amp
id|tsk-&gt;thread.fp_regs
comma
r_sizeof
(paren
id|elf_fpregset_t
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, fpregs) dump_task_fpu(tsk, fpregs)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports. */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM (NULL)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __s390x__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#else /* __s390x__ */
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)&t;&bslash;&n;&t;&t;set_personality(PER_LINUX);&t;&t;&bslash;&n;&t;clear_thread_flag(TIF_31BIT);&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __s390x__ */
macro_line|#endif
macro_line|#endif
eof
