macro_line|#ifndef __ASM_SH_ELF_H
DECL|macro|__ASM_SH_ELF_H
mdefine_line|#define __ASM_SH_ELF_H
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
mdefine_line|#define elf_check_arch(x) ( (x)-&gt;e_machine == EM_SH )
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
mdefine_line|#define ELF_ARCH&t;EM_SH
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(_dest,_regs)&t;&t;&t;&t;&bslash;&n;&t;memcpy((char *) &amp;_dest, (char *) _regs,&t;&t;&t;&bslash;&n;&t;       sizeof(struct pt_regs));
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r) &bslash;&n;  do { _r-&gt;regs[0]=0; _r-&gt;regs[1]=0; _r-&gt;regs[2]=0; _r-&gt;regs[3]=0; &bslash;&n;       _r-&gt;regs[4]=0; _r-&gt;regs[5]=0; _r-&gt;regs[6]=0; _r-&gt;regs[7]=0; &bslash;&n;       _r-&gt;regs[8]=0; _r-&gt;regs[9]=0; _r-&gt;regs[10]=0; _r-&gt;regs[11]=0; &bslash;&n;       _r-&gt;regs[12]=0; _r-&gt;regs[13]=0; _r-&gt;regs[14]=0; &bslash;&n;       _r-&gt;sr = SR_FD; } while (0)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality(PER_LINUX_32BIT)
macro_line|#endif
macro_line|#endif /* __ASM_SH_ELF_H */
eof
