macro_line|#ifndef __V850_ELF_H__
DECL|macro|__V850_ELF_H__
mdefine_line|#define __V850_ELF_H__
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))
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
id|user_fpu_struct
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ( (x)-&gt;e_machine == EM_CYGNUS_V850 )
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#ifdef __LITTLE_ENDIAN__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
macro_line|#else
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
macro_line|#endif
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_V850
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(_dest,_regs)&t;&t;&t;&t;&bslash;&n;&t;memcpy((char *) &amp;_dest, (char *) _regs,&t;&t;&t;&bslash;&n;&t;       sizeof(struct pt_regs));
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;&t;&t;&t;&t;&t;      &bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t; _r-&gt;gpr[0] =  _r-&gt;gpr[1] =  _r-&gt;gpr[2] =  _r-&gt;gpr[3] =&t;&t;      &bslash;&n;&t; _r-&gt;gpr[4] =  _r-&gt;gpr[5] =  _r-&gt;gpr[6] =  _r-&gt;gpr[7] =&t;&t;      &bslash;&n;&t; _r-&gt;gpr[8] =  _r-&gt;gpr[9] = _r-&gt;gpr[10] = _r-&gt;gpr[11] =&t;&t;      &bslash;&n;&t;_r-&gt;gpr[12] = _r-&gt;gpr[13] = _r-&gt;gpr[14] = _r-&gt;gpr[15] =&t;&t;      &bslash;&n;&t;_r-&gt;gpr[16] = _r-&gt;gpr[17] = _r-&gt;gpr[18] = _r-&gt;gpr[19] =&t;&t;      &bslash;&n;&t;_r-&gt;gpr[20] = _r-&gt;gpr[21] = _r-&gt;gpr[22] = _r-&gt;gpr[23] =&t;&t;      &bslash;&n;&t;_r-&gt;gpr[24] = _r-&gt;gpr[25] = _r-&gt;gpr[26] = _r-&gt;gpr[27] =&t;&t;      &bslash;&n;&t;_r-&gt;gpr[28] = _r-&gt;gpr[29] = _r-&gt;gpr[30] = _r-&gt;gpr[31] =&t;&t;      &bslash;&n;&t;0;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  } while (0)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality(PER_LINUX_32BIT)
macro_line|#endif
macro_line|#endif /* __V850_ELF_H__ */
eof
