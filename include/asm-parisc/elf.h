macro_line|#ifndef __ASMPARISC_ELF_H
DECL|macro|__ASMPARISC_ELF_H
mdefine_line|#define __ASMPARISC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|EM_PARISC
mdefine_line|#define EM_PARISC 15
multiline_comment|/*&n; * The following definitions are those for 32-bit ELF binaries on a 32-bit kernel&n; * and for 64-bit binaries on a 64-bit kernel.  To run 32-bit binaries on a 64-bit&n; * kernel, arch/parisc64/kernel/binfmt_elf32.c defines these macros appropriately&n; * and then #includes binfmt_elf.c, which then includes this file.&n; */
macro_line|#ifndef ELF_CLASS
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; *&n; * Note that this header file is used by default in fs/binfmt_elf.c. So&n; * the following macros are for the default case. However, for the 64&n; * bit kernel we also support 32 bit parisc binaries. To do that&n; * arch/parisc64/kernel/binfmt_elf32.c defines its own set of these&n; * macros, and then it includes fs/binfmt_elf.c to provide an alternate&n; * elf binary handler for 32 bit binaries (on the 64 bit kernel).&n; */
macro_line|#ifdef __LP64__
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS       ELFCLASS64
macro_line|#else
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#endif
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (&quot;PARISC&bslash;0&quot; /*+((boot_cpu_data.x86-3)*5) */)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) &bslash;&n;&t;current-&gt;personality = PER_LINUX
macro_line|#endif
multiline_comment|/*&n; * Fill in general registers in a core dump.  This saves pretty&n; * much the same registers as hp-ux, although in a different order.&n; * Registers marked # below are not currently saved in pt_regs, so&n; * we use their current values here.&n; *&n; * &t;gr0..gr31&n; * &t;sr0..sr7&n; * &t;iaoq0..iaoq1&n; * &t;iasq0..iasq1&n; * &t;cr11 (sar)&n; * &t;cr19 (iir)&n; * &t;cr20 (isr)&n; * &t;cr21 (ior)&n; *  #&t;cr22 (ipsw)&n; *  #&t;cr0 (recovery counter)&n; *  #&t;cr24..cr31 (temporary registers)&n; *  #&t;cr8,9,12,13 (protection IDs)&n; *  #&t;cr10 (scr/ccr)&n; *  #&t;cr15 (ext int enable mask)&n; *&n; */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(dst, pt)&t;&bslash;&n;&t;memset(dst, 0, sizeof(dst));&t;/* don&squot;t leak any &quot;random&quot; bits */ &bslash;&n;&t;memcpy(dst + 0, pt-&gt;gr, 32 * sizeof(elf_greg_t)); &bslash;&n;&t;memcpy(dst + 32, pt-&gt;sr, 8 * sizeof(elf_greg_t)); &bslash;&n;&t;memcpy(dst + 40, pt-&gt;iaoq, 2 * sizeof(elf_greg_t)); &bslash;&n;&t;memcpy(dst + 42, pt-&gt;iasq, 2 * sizeof(elf_greg_t)); &bslash;&n;&t;dst[44] = pt-&gt;sar;   dst[45] = pt-&gt;iir; &bslash;&n;&t;dst[46] = pt-&gt;isr;   dst[47] = pt-&gt;ior; &bslash;&n;&t;dst[48] = mfctl(22); dst[49] = mfctl(0); &bslash;&n;&t;dst[50] = mfctl(24); dst[51] = mfctl(25); &bslash;&n;&t;dst[52] = mfctl(26); dst[53] = mfctl(27); &bslash;&n;&t;dst[54] = mfctl(28); dst[55] = mfctl(29); &bslash;&n;&t;dst[56] = mfctl(30); dst[57] = mfctl(31); &bslash;&n;&t;dst[58] = mfctl( 8); dst[59] = mfctl( 9); &bslash;&n;&t;dst[60] = mfctl(12); dst[61] = mfctl(13); &bslash;&n;&t;dst[62] = mfctl(10); dst[63] = mfctl(15);
macro_line|#endif /* ! ELF_CLASS */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG 80&t;/* We only need 64 at present, but leave space&n;&t;&t;&t;   for expansion. */
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG 32
DECL|typedef|elf_fpreg_t
r_typedef
r_float
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
r_extern
r_int
id|dump_task_fpu
(paren
r_struct
id|task_struct
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, elf_fpregs) dump_task_fpu(tsk, elf_fpregs)
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/* forward declaration... */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_PARISC &amp;&amp; (x)-&gt;e_ident[EI_CLASS] == ELF_CLASS)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_PARISC
multiline_comment|/* %r23 is set by ld.so to a pointer to a function which might be &n;   registered using atexit.  This provides a mean for the dynamic&n;   linker to call DT_FINI functions for shared libraries that have&n;   been loaded before the code runs.&n;&n;   So that we can use the same startup file with static executables,&n;   we start programs with a value of 0 to indicate that there is no&n;   such function.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)       _r-&gt;gr[23] = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.&n;&n;   (2 * TASK_SIZE / 3) turns into something undefined when run through a&n;   32 bit preprocessor and in some cases results in the kernel trying to map&n;   ld.so to the kernel virtual base. Use a sane value instead. /Jes &n;  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE + 0x01000000)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;0
multiline_comment|/* (boot_cpu_data.x86_capability) */
macro_line|#endif
eof
