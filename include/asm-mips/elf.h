multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_ELF_H
DECL|macro|__ASM_ELF_H
mdefine_line|#define __ASM_ELF_H
multiline_comment|/* ELF register definitions */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;45
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;33
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
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture&n; * and also rejects IRIX binaries.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(hdr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __res = 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct elfhdr *__h = (hdr);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_machine != EM_MIPS)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_flags &amp; EF_MIPS_ARCH)&t;&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* This one accepts IRIX binaries.  */
DECL|macro|irix_elf_check_arch
mdefine_line|#define irix_elf_check_arch(hdr)&t;((hdr)-&gt;e_machine == EM_MIPS)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#ifdef __MIPSEB__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
macro_line|#elif __MIPSEL__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
macro_line|#endif
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_MIPS
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(_dest,_regs)&t;&t;&t;&t;&bslash;&n;&t;memcpy((char *) &amp;_dest, (char *) _regs,&t;&t;&t;&bslash;&n;&t;       sizeof(struct pt_regs));
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This could be done in userspace,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP       (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
multiline_comment|/*&n; * See comments in asm-alpha/elf.h, this is the same thing&n; * on the MIPS.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;do { &bslash;&n;&t;_r-&gt;regs[1] = _r-&gt;regs[2] = _r-&gt;regs[3] = _r-&gt;regs[4] = 0;&t;&bslash;&n;&t;_r-&gt;regs[5] = _r-&gt;regs[6] = _r-&gt;regs[7] = _r-&gt;regs[8] = 0;&t;&bslash;&n;&t;_r-&gt;regs[9] = _r-&gt;regs[10] = _r-&gt;regs[11] = _r-&gt;regs[12] = 0;&t;&bslash;&n;&t;_r-&gt;regs[13] = _r-&gt;regs[14] = _r-&gt;regs[15] = _r-&gt;regs[16] = 0;&t;&bslash;&n;&t;_r-&gt;regs[17] = _r-&gt;regs[18] = _r-&gt;regs[19] = _r-&gt;regs[20] = 0;&t;&bslash;&n;&t;_r-&gt;regs[21] = _r-&gt;regs[22] = _r-&gt;regs[23] = _r-&gt;regs[24] = 0;&t;&bslash;&n;&t;_r-&gt;regs[25] = _r-&gt;regs[26] = _r-&gt;regs[27] = _r-&gt;regs[28] = 0;&t;&bslash;&n;&t;_r-&gt;regs[30] = _r-&gt;regs[31] = 0;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif /* __ASM_ELF_H */
eof
