macro_line|#ifndef __ASMi386_ELF_H
DECL|macro|__ASMi386_ELF_H
mdefine_line|#define __ASMi386_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for savesegment */
macro_line|#include &lt;linux/utsname.h&gt;
DECL|macro|R_386_NONE
mdefine_line|#define R_386_NONE&t;0
DECL|macro|R_386_32
mdefine_line|#define R_386_32&t;1
DECL|macro|R_386_PC32
mdefine_line|#define R_386_PC32&t;2
DECL|macro|R_386_GOT32
mdefine_line|#define R_386_GOT32&t;3
DECL|macro|R_386_PLT32
mdefine_line|#define R_386_PLT32&t;4
DECL|macro|R_386_COPY
mdefine_line|#define R_386_COPY&t;5
DECL|macro|R_386_GLOB_DAT
mdefine_line|#define R_386_GLOB_DAT&t;6
DECL|macro|R_386_JMP_SLOT
mdefine_line|#define R_386_JMP_SLOT&t;7
DECL|macro|R_386_RELATIVE
mdefine_line|#define R_386_RELATIVE&t;8
DECL|macro|R_386_GOTOFF
mdefine_line|#define R_386_GOTOFF&t;9
DECL|macro|R_386_GOTPC
mdefine_line|#define R_386_GOTPC&t;10
DECL|macro|R_386_NUM
mdefine_line|#define R_386_NUM&t;11
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct user_regs_struct) / sizeof(elf_greg_t))
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
id|user_i387_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_fpxregset_t
r_typedef
r_struct
id|user_fxsr_struct
id|elf_fpxregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;(((x)-&gt;e_machine == EM_386) || ((x)-&gt;e_machine == EM_486))
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_386
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program starts %edx&n;   contains a pointer to a function which might be registered using `atexit&squot;.&n;   This provides a mean for the dynamic linker to call DT_FINI functions for&n;   shared libraries that have been loaded before the code runs.&n;&n;   A value of 0 tells we have no such handler. &n;&n;   We might as well make sure everything else is cleared too (except for %esp),&n;   just to make things more deterministic.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;do { &bslash;&n;&t;_r-&gt;ebx = 0; _r-&gt;ecx = 0; _r-&gt;edx = 0; &bslash;&n;&t;_r-&gt;esi = 0; _r-&gt;edi = 0; _r-&gt;ebp = 0; &bslash;&n;&t;_r-&gt;eax = 0; &bslash;&n;} while (0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)&t;&t;&bslash;&n;&t;pr_reg[0] = regs-&gt;ebx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[1] = regs-&gt;ecx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[2] = regs-&gt;edx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[3] = regs-&gt;esi;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[4] = regs-&gt;edi;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[5] = regs-&gt;ebp;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[6] = regs-&gt;eax;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[7] = regs-&gt;xds;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[8] = regs-&gt;xes;&t;&t;&t;&t;&bslash;&n;&t;savesegment(fs,pr_reg[9]);&t;&t;&t;&bslash;&n;&t;savesegment(gs,pr_reg[10]);&t;&t;&t;&bslash;&n;&t;pr_reg[11] = regs-&gt;orig_eax;&t;&t;&t;&bslash;&n;&t;pr_reg[12] = regs-&gt;eip;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[13] = regs-&gt;xcs;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[14] = regs-&gt;eflags;&t;&t;&t;&bslash;&n;&t;pr_reg[15] = regs-&gt;esp;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[16] = regs-&gt;xss;
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(boot_cpu_data.x86_capability[0])
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (system_utsname.machine)
multiline_comment|/*&n; * Architecture-neutral AT_ values in 0-17, leave some room&n; * for more of them, start the x86-specific ones at 32.&n; */
DECL|macro|AT_SYSINFO
mdefine_line|#define AT_SYSINFO&t;&t;32
DECL|macro|AT_SYSINFO_EHDR
mdefine_line|#define AT_SYSINFO_EHDR&t;&t;33
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) do { } while (0)
multiline_comment|/*&n; * An executable for which elf_read_implies_exec() returns TRUE will&n; * have the READ_IMPLIES_EXEC personality flag set automatically.&n; */
DECL|macro|elf_read_implies_exec
mdefine_line|#define elf_read_implies_exec(ex, executable_stack)&t;(executable_stack != EXSTACK_DISABLE_X)
r_extern
r_int
id|dump_task_regs
(paren
r_struct
id|task_struct
op_star
comma
id|elf_gregset_t
op_star
)paren
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
r_extern
r_int
id|dump_task_extended_fpu
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|user_fxsr_struct
op_star
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(tsk, elf_regs) dump_task_regs(tsk, elf_regs)
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, elf_fpregs) dump_task_fpu(tsk, elf_fpregs)
DECL|macro|ELF_CORE_COPY_XFPREGS
mdefine_line|#define ELF_CORE_COPY_XFPREGS(tsk, elf_xfpregs) dump_task_extended_fpu(tsk, elf_xfpregs)
DECL|macro|VSYSCALL_BASE
mdefine_line|#define VSYSCALL_BASE&t;(__fix_to_virt(FIX_VSYSCALL))
DECL|macro|VSYSCALL_EHDR
mdefine_line|#define VSYSCALL_EHDR&t;((const struct elfhdr *) VSYSCALL_BASE)
DECL|macro|VSYSCALL_ENTRY
mdefine_line|#define VSYSCALL_ENTRY&t;((unsigned long) &amp;__kernel_vsyscall)
r_extern
r_void
id|__kernel_vsyscall
suffix:semicolon
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;NEW_AUX_ENT(AT_SYSINFO,&t;VSYSCALL_ENTRY);&t;&bslash;&n;&t;&t;NEW_AUX_ENT(AT_SYSINFO_EHDR, VSYSCALL_BASE);&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * These macros parameterize elf_core_dump in fs/binfmt_elf.c to write out&n; * extra segments containing the vsyscall DSO contents.  Dumping its&n; * contents makes post-mortem fully interpretable later without matching up&n; * the same kernel and hardware config to see what PC values meant.&n; * Dumping its extra ELF program headers includes all the other information&n; * a debugger needs to easily find how the vsyscall DSO was being used.&n; */
DECL|macro|ELF_CORE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_EXTRA_PHDRS&t;&t;(VSYSCALL_EHDR-&gt;e_phnum)
DECL|macro|ELF_CORE_WRITE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_WRITE_EXTRA_PHDRS&t;&t;&t;&t;&t;      &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const struct elf_phdr *const vsyscall_phdrs =&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf_phdr *) (VSYSCALL_BASE&t;&t;      &bslash;&n;&t;&t;&t;&t;&t;   + VSYSCALL_EHDR-&gt;e_phoff);&t;      &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;Elf32_Off ofs = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; VSYSCALL_EHDR-&gt;e_phnum; ++i) {&t;&t;&t;      &bslash;&n;&t;&t;struct elf_phdr phdr = vsyscall_phdrs[i];&t;&t;      &bslash;&n;&t;&t;if (phdr.p_type == PT_LOAD) {&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;BUG_ON(ofs != 0);&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;ofs = phdr.p_offset = offset;&t;&t;&t;      &bslash;&n;&t;&t;&t;phdr.p_memsz = PAGE_ALIGN(phdr.p_memsz);&t;      &bslash;&n;&t;&t;&t;phdr.p_filesz = phdr.p_memsz;&t;&t;&t;      &bslash;&n;&t;&t;&t;offset += phdr.p_filesz;&t;&t;&t;      &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;phdr.p_offset += ofs;&t;&t;&t;&t;      &bslash;&n;&t;&t;phdr.p_paddr = 0; /* match other core phdrs */&t;&t;      &bslash;&n;&t;&t;DUMP_WRITE(&amp;phdr, sizeof(phdr));&t;&t;&t;      &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;} while (0)
DECL|macro|ELF_CORE_WRITE_EXTRA_DATA
mdefine_line|#define ELF_CORE_WRITE_EXTRA_DATA&t;&t;&t;&t;&t;      &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const struct elf_phdr *const vsyscall_phdrs =&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf_phdr *) (VSYSCALL_BASE&t;&t;      &bslash;&n;&t;&t;&t;&t;&t;   + VSYSCALL_EHDR-&gt;e_phoff);&t;      &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; VSYSCALL_EHDR-&gt;e_phnum; ++i) {&t;&t;&t;      &bslash;&n;&t;&t;if (vsyscall_phdrs[i].p_type == PT_LOAD)&t;&t;      &bslash;&n;&t;&t;&t;DUMP_WRITE((void *) vsyscall_phdrs[i].p_vaddr,&t;      &bslash;&n;&t;&t;&t;&t;   PAGE_ALIGN(vsyscall_phdrs[i].p_memsz));    &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif
eof
