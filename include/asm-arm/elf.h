macro_line|#ifndef __ASMARM_ELF_H
DECL|macro|__ASMARM_ELF_H
mdefine_line|#define __ASMARM_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/proc/elf.h&gt;
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
DECL|member|null
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
(brace
r_void
op_star
id|null
suffix:semicolon
)brace
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
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;(2 * TASK_SIZE / 3)
multiline_comment|/* When the program starts, a1 contains a pointer to a function to be &n;   registered with atexit, as per the SVR4 ABI.  A value of 0 means we &n;   have no such handler.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;(_r)-&gt;ARM_r0 = 0
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports. */
r_extern
r_int
r_int
id|elf_hwcap
suffix:semicolon
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
macro_line|#endif
eof
