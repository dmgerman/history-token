macro_line|#ifndef __ASMARM_ELF_H
DECL|macro|__ASMARM_ELF_H
mdefine_line|#define __ASMARM_ELF_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/procinfo.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_freg_t
r_typedef
r_int
r_int
id|elf_freg_t
(braket
l_int|3
)braket
suffix:semicolon
DECL|macro|EM_ARM
mdefine_line|#define EM_ARM&t;40
DECL|macro|EF_ARM_APCS26
mdefine_line|#define EF_ARM_APCS26 0x08
DECL|macro|EF_ARM_SOFT_FLOAT
mdefine_line|#define EF_ARM_SOFT_FLOAT 0x200
DECL|macro|EF_ARM_EABI_MASK
mdefine_line|#define EF_ARM_EABI_MASK 0xFF000000
DECL|macro|R_ARM_NONE
mdefine_line|#define R_ARM_NONE&t;0
DECL|macro|R_ARM_PC24
mdefine_line|#define R_ARM_PC24&t;1
DECL|macro|R_ARM_ABS32
mdefine_line|#define R_ARM_ABS32&t;2
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
id|user_fp
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ( ((x)-&gt;e_machine == EM_ARM) &amp;&amp; (ELF_PROC_OK((x))) )
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#ifdef __ARMEB__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB;
macro_line|#else
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB;
macro_line|#endif
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_ARM
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;(2 * TASK_SIZE / 3)
multiline_comment|/* When the program starts, a1 contains a pointer to a function to be &n;   registered with atexit, as per the SVR4 ABI.  A value of 0 means we &n;   have no such handler.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;(_r)-&gt;ARM_r0 = 0
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports. */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(elf_hwcap)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo. */
multiline_comment|/* For now we just provide a fairly general string that describes the&n;   processor family.  This could be made more specific later if someone&n;   implemented optimisations that require it.  26-bit CPUs give you&n;   &quot;v1l&quot; for ARM2 (no SWP) and &quot;v2l&quot; for anything else (ARM1 isn&squot;t&n;   supported).  32-bit CPUs give you &quot;v3[lb]&quot; for anything based on an&n;   ARM6 or ARM7 core and &quot;armv4[lb]&quot; for anything based on a StrongARM-1&n;   core.  */
DECL|macro|ELF_PLATFORM_SIZE
mdefine_line|#define ELF_PLATFORM_SIZE 8
r_extern
r_char
id|elf_platform
(braket
)braket
suffix:semicolon
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(elf_platform)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * 32-bit code is always OK.  Some cpus can do 26-bit, some can&squot;t.&n; */
DECL|macro|ELF_PROC_OK
mdefine_line|#define ELF_PROC_OK(x)&t;(ELF_THUMB_OK(x) &amp;&amp; ELF_26BIT_OK(x))
DECL|macro|ELF_THUMB_OK
mdefine_line|#define ELF_THUMB_OK(x) &bslash;&n;&t;(( (elf_hwcap &amp; HWCAP_THUMB) &amp;&amp; ((x)-&gt;e_entry &amp; 1) == 1) || &bslash;&n;&t; ((x)-&gt;e_entry &amp; 3) == 0)
DECL|macro|ELF_26BIT_OK
mdefine_line|#define ELF_26BIT_OK(x) &bslash;&n;&t;(( (elf_hwcap &amp; HWCAP_26BIT) &amp;&amp; (x)-&gt;e_flags &amp; EF_ARM_APCS26) || &bslash;&n;&t;  ((x)-&gt;e_flags &amp; EF_ARM_APCS26) == 0)
macro_line|#ifndef CONFIG_IWMMXT
multiline_comment|/* Old NetWinder binaries were compiled in such a way that the iBCS&n;   heuristic always trips on them.  Until these binaries become uncommon&n;   enough not to care, don&squot;t trust the `ibcs&squot; flag here.  In any case&n;   there is no other ELF system currently supported by iBCS.&n;   @@ Could print a warning message to encourage users to upgrade.  */
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex,ibcs2) &bslash;&n;&t;set_personality(((ex).e_flags&amp;EF_ARM_APCS26 ?PER_LINUX :PER_LINUX_32BIT))
macro_line|#else
multiline_comment|/*&n; * All iWMMXt capable CPUs don&squot;t support 26-bit mode.  Yet they can run&n; * legacy binaries which used to contain FPA11 floating point instructions&n; * that have always been emulated by the kernel.  PFA11 and iWMMXt overlap&n; * on coprocessor 1 space though.  We therefore must decide if given task&n; * is allowed to use CP 0 and 1 for iWMMXt, or if they should be blocked&n; * at all times for the prefetch exception handler to catch FPA11 opcodes&n; * and emulate them.  The best indication to discriminate those two cases&n; * is the SOFT_FLOAT flag in the ELF header.&n; */
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex,ibcs2) &bslash;&n;do { &bslash;&n;&t;set_personality(PER_LINUX_32BIT); &bslash;&n;&t;if (((ex).e_flags &amp; EF_ARM_EABI_MASK) || &bslash;&n;&t;    ((ex).e_flags &amp; EF_ARM_SOFT_FLOAT)) &bslash;&n;&t;&t;set_thread_flag(TIF_USING_IWMMXT); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
