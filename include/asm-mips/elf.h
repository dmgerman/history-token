multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_ELF_H
DECL|macro|_ASM_ELF_H
mdefine_line|#define _ASM_ELF_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* ELF header e_flags defines. */
multiline_comment|/* MIPS architecture level. */
DECL|macro|EF_MIPS_ARCH_1
mdefine_line|#define EF_MIPS_ARCH_1&t;&t;0x00000000&t;/* -mips1 code.  */
DECL|macro|EF_MIPS_ARCH_2
mdefine_line|#define EF_MIPS_ARCH_2&t;&t;0x10000000&t;/* -mips2 code.  */
DECL|macro|EF_MIPS_ARCH_3
mdefine_line|#define EF_MIPS_ARCH_3&t;&t;0x20000000&t;/* -mips3 code.  */
DECL|macro|EF_MIPS_ARCH_4
mdefine_line|#define EF_MIPS_ARCH_4&t;&t;0x30000000&t;/* -mips4 code.  */
DECL|macro|EF_MIPS_ARCH_5
mdefine_line|#define EF_MIPS_ARCH_5&t;&t;0x40000000&t;/* -mips5 code.  */
DECL|macro|EF_MIPS_ARCH_32
mdefine_line|#define EF_MIPS_ARCH_32&t;&t;0x50000000&t;/* MIPS32 code.  */
DECL|macro|EF_MIPS_ARCH_64
mdefine_line|#define EF_MIPS_ARCH_64&t;&t;0x60000000&t;/* MIPS64 code.  */
multiline_comment|/* The ABI of a file. */
DECL|macro|EF_MIPS_ABI_O32
mdefine_line|#define EF_MIPS_ABI_O32&t;&t;0x00001000&t;/* O32 ABI.  */
DECL|macro|EF_MIPS_ABI_O64
mdefine_line|#define EF_MIPS_ABI_O64&t;&t;0x00002000&t;/* O32 extended for 64 bit.  */
DECL|macro|PT_MIPS_REGINFO
mdefine_line|#define PT_MIPS_REGINFO&t;&t;0x70000000
DECL|macro|PT_MIPS_RTPROC
mdefine_line|#define PT_MIPS_RTPROC&t;&t;0x70000001
DECL|macro|PT_MIPS_OPTIONS
mdefine_line|#define PT_MIPS_OPTIONS&t;&t;0x70000002
multiline_comment|/* Flags in the e_flags field of the header */
DECL|macro|EF_MIPS_NOREORDER
mdefine_line|#define EF_MIPS_NOREORDER&t;0x00000001
DECL|macro|EF_MIPS_PIC
mdefine_line|#define EF_MIPS_PIC&t;&t;0x00000002
DECL|macro|EF_MIPS_CPIC
mdefine_line|#define EF_MIPS_CPIC&t;&t;0x00000004
DECL|macro|EF_MIPS_ABI2
mdefine_line|#define EF_MIPS_ABI2&t;&t;0x00000020
DECL|macro|EF_MIPS_OPTIONS_FIRST
mdefine_line|#define EF_MIPS_OPTIONS_FIRST&t;0x00000080
DECL|macro|EF_MIPS_32BITMODE
mdefine_line|#define EF_MIPS_32BITMODE&t;0x00000100
DECL|macro|EF_MIPS_ABI
mdefine_line|#define EF_MIPS_ABI&t;&t;0x0000f000
DECL|macro|EF_MIPS_ARCH
mdefine_line|#define EF_MIPS_ARCH&t;&t;0xf0000000
DECL|macro|DT_MIPS_RLD_VERSION
mdefine_line|#define DT_MIPS_RLD_VERSION&t;0x70000001
DECL|macro|DT_MIPS_TIME_STAMP
mdefine_line|#define DT_MIPS_TIME_STAMP&t;0x70000002
DECL|macro|DT_MIPS_ICHECKSUM
mdefine_line|#define DT_MIPS_ICHECKSUM&t;0x70000003
DECL|macro|DT_MIPS_IVERSION
mdefine_line|#define DT_MIPS_IVERSION&t;0x70000004
DECL|macro|DT_MIPS_FLAGS
mdefine_line|#define DT_MIPS_FLAGS&t;&t;0x70000005
DECL|macro|RHF_NONE
mdefine_line|#define RHF_NONE&t;0x00000000
DECL|macro|RHF_HARDWAY
mdefine_line|#define RHF_HARDWAY&t;0x00000001
DECL|macro|RHF_NOTPOT
mdefine_line|#define RHF_NOTPOT&t;0x00000002
DECL|macro|RHF_SGI_ONLY
mdefine_line|#define RHF_SGI_ONLY&t;0x00000010
DECL|macro|DT_MIPS_BASE_ADDRESS
mdefine_line|#define DT_MIPS_BASE_ADDRESS&t;0x70000006
DECL|macro|DT_MIPS_CONFLICT
mdefine_line|#define DT_MIPS_CONFLICT&t;0x70000008
DECL|macro|DT_MIPS_LIBLIST
mdefine_line|#define DT_MIPS_LIBLIST&t;&t;0x70000009
DECL|macro|DT_MIPS_LOCAL_GOTNO
mdefine_line|#define DT_MIPS_LOCAL_GOTNO&t;0x7000000a
DECL|macro|DT_MIPS_CONFLICTNO
mdefine_line|#define DT_MIPS_CONFLICTNO&t;0x7000000b
DECL|macro|DT_MIPS_LIBLISTNO
mdefine_line|#define DT_MIPS_LIBLISTNO&t;0x70000010
DECL|macro|DT_MIPS_SYMTABNO
mdefine_line|#define DT_MIPS_SYMTABNO&t;0x70000011
DECL|macro|DT_MIPS_UNREFEXTNO
mdefine_line|#define DT_MIPS_UNREFEXTNO&t;0x70000012
DECL|macro|DT_MIPS_GOTSYM
mdefine_line|#define DT_MIPS_GOTSYM&t;&t;0x70000013
DECL|macro|DT_MIPS_HIPAGENO
mdefine_line|#define DT_MIPS_HIPAGENO&t;0x70000014
DECL|macro|DT_MIPS_RLD_MAP
mdefine_line|#define DT_MIPS_RLD_MAP&t;&t;0x70000016
DECL|macro|R_MIPS_NONE
mdefine_line|#define R_MIPS_NONE&t;&t;0
DECL|macro|R_MIPS_16
mdefine_line|#define R_MIPS_16&t;&t;1
DECL|macro|R_MIPS_32
mdefine_line|#define R_MIPS_32&t;&t;2
DECL|macro|R_MIPS_REL32
mdefine_line|#define R_MIPS_REL32&t;&t;3
DECL|macro|R_MIPS_26
mdefine_line|#define R_MIPS_26&t;&t;4
DECL|macro|R_MIPS_HI16
mdefine_line|#define R_MIPS_HI16&t;&t;5
DECL|macro|R_MIPS_LO16
mdefine_line|#define R_MIPS_LO16&t;&t;6
DECL|macro|R_MIPS_GPREL16
mdefine_line|#define R_MIPS_GPREL16&t;&t;7
DECL|macro|R_MIPS_LITERAL
mdefine_line|#define R_MIPS_LITERAL&t;&t;8
DECL|macro|R_MIPS_GOT16
mdefine_line|#define R_MIPS_GOT16&t;&t;9
DECL|macro|R_MIPS_PC16
mdefine_line|#define R_MIPS_PC16&t;&t;10
DECL|macro|R_MIPS_CALL16
mdefine_line|#define R_MIPS_CALL16&t;&t;11
DECL|macro|R_MIPS_GPREL32
mdefine_line|#define R_MIPS_GPREL32&t;&t;12
multiline_comment|/* The remaining relocs are defined on Irix, although they are not&n;   in the MIPS ELF ABI.  */
DECL|macro|R_MIPS_UNUSED1
mdefine_line|#define R_MIPS_UNUSED1&t;&t;13
DECL|macro|R_MIPS_UNUSED2
mdefine_line|#define R_MIPS_UNUSED2&t;&t;14
DECL|macro|R_MIPS_UNUSED3
mdefine_line|#define R_MIPS_UNUSED3&t;&t;15
DECL|macro|R_MIPS_SHIFT5
mdefine_line|#define R_MIPS_SHIFT5&t;&t;16
DECL|macro|R_MIPS_SHIFT6
mdefine_line|#define R_MIPS_SHIFT6&t;&t;17
DECL|macro|R_MIPS_64
mdefine_line|#define R_MIPS_64&t;&t;18
DECL|macro|R_MIPS_GOT_DISP
mdefine_line|#define R_MIPS_GOT_DISP&t;&t;19
DECL|macro|R_MIPS_GOT_PAGE
mdefine_line|#define R_MIPS_GOT_PAGE&t;&t;20
DECL|macro|R_MIPS_GOT_OFST
mdefine_line|#define R_MIPS_GOT_OFST&t;&t;21
multiline_comment|/*&n; * The following two relocation types are specified in the MIPS ABI&n; * conformance guide version 1.2 but not yet in the psABI.&n; */
DECL|macro|R_MIPS_GOTHI16
mdefine_line|#define R_MIPS_GOTHI16&t;&t;22
DECL|macro|R_MIPS_GOTLO16
mdefine_line|#define R_MIPS_GOTLO16&t;&t;23
DECL|macro|R_MIPS_SUB
mdefine_line|#define R_MIPS_SUB&t;&t;24
DECL|macro|R_MIPS_INSERT_A
mdefine_line|#define R_MIPS_INSERT_A&t;&t;25
DECL|macro|R_MIPS_INSERT_B
mdefine_line|#define R_MIPS_INSERT_B&t;&t;26
DECL|macro|R_MIPS_DELETE
mdefine_line|#define R_MIPS_DELETE&t;&t;27
DECL|macro|R_MIPS_HIGHER
mdefine_line|#define R_MIPS_HIGHER&t;&t;28
DECL|macro|R_MIPS_HIGHEST
mdefine_line|#define R_MIPS_HIGHEST&t;&t;29
multiline_comment|/*&n; * The following two relocation types are specified in the MIPS ABI&n; * conformance guide version 1.2 but not yet in the psABI.&n; */
DECL|macro|R_MIPS_CALLHI16
mdefine_line|#define R_MIPS_CALLHI16&t;&t;30
DECL|macro|R_MIPS_CALLLO16
mdefine_line|#define R_MIPS_CALLLO16&t;&t;31
multiline_comment|/*&n; * This range is reserved for vendor specific relocations.&n; */
DECL|macro|R_MIPS_LOVENDOR
mdefine_line|#define R_MIPS_LOVENDOR&t;&t;100
DECL|macro|R_MIPS_HIVENDOR
mdefine_line|#define R_MIPS_HIVENDOR&t;&t;127
DECL|macro|SHN_MIPS_ACCOMON
mdefine_line|#define SHN_MIPS_ACCOMON&t;0xff00
DECL|macro|SHT_MIPS_LIST
mdefine_line|#define SHT_MIPS_LIST&t;&t;0x70000000
DECL|macro|SHT_MIPS_CONFLICT
mdefine_line|#define SHT_MIPS_CONFLICT&t;0x70000002
DECL|macro|SHT_MIPS_GPTAB
mdefine_line|#define SHT_MIPS_GPTAB&t;&t;0x70000003
DECL|macro|SHT_MIPS_UCODE
mdefine_line|#define SHT_MIPS_UCODE&t;&t;0x70000004
DECL|macro|SHF_MIPS_GPREL
mdefine_line|#define SHF_MIPS_GPREL&t;0x10000000
macro_line|#ifndef ELF_ARCH
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
macro_line|#ifdef CONFIG_MIPS32
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(hdr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __res = 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct elfhdr *__h = (hdr);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_machine != EM_MIPS)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_ident[EI_CLASS] != ELFCLASS32)&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((__h-&gt;e_flags &amp; EF_MIPS_ABI2) != 0)&t;&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (((__h-&gt;e_flags &amp; EF_MIPS_ABI) != 0) &amp;&amp;&t;&t;&t;&bslash;&n;&t;    ((__h-&gt;e_flags &amp; EF_MIPS_ABI) != EF_MIPS_ABI_O32))&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#endif /* CONFIG_MIPS32 */
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(hdr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __res = 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct elfhdr *__h = (hdr);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_machine != EM_MIPS)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_ident[EI_CLASS] != ELFCLASS64) &t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
macro_line|#endif /* CONFIG_MIPS64 */
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
macro_line|#ifdef __MIPSEB__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
macro_line|#elif __MIPSEL__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
macro_line|#endif
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_MIPS
macro_line|#endif /* !defined(ELF_ARCH) */
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&bslash;&n;&t;set_personality(PER_LINUX);&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* CONFIG_MIPS32 */
macro_line|#ifdef CONFIG_MIPS64
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&t;&bslash;&n;do {&t;current-&gt;thread.mflags &amp;= ~MF_ABI_MASK;&t;&t;&t;&bslash;&n;&t;if ((ex).e_ident[EI_CLASS] == ELFCLASS32) {&t;&t;&bslash;&n;&t;&t;if ((((ex).e_flags &amp; EF_MIPS_ABI2) != 0) &amp;&amp;&t;&bslash;&n;&t;&t;     ((ex).e_flags &amp; EF_MIPS_ABI) == 0)&t;&t;&bslash;&n;&t;&t;&t;current-&gt;thread.mflags |= MF_N32;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;current-&gt;thread.mflags |= MF_O32;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;thread.mflags |= MF_N64;&t;&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&t;&bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)&t;&t;&bslash;&n;&t;&t;set_personality(PER_LINUX);&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* CONFIG_MIPS64 */
r_extern
r_void
id|dump_regs
c_func
(paren
id|elf_greg_t
op_star
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(elf_regs, regs)&t;&t;&t;&bslash;&n;&t;dump_regs((elf_greg_t *)&amp;(elf_regs), regs);
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, elf_fpregs)&t;&t;&t;&bslash;&n;&t;dump_task_fpu(tsk, elf_fpregs)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* This one accepts IRIX binaries.  */
DECL|macro|irix_elf_check_arch
mdefine_line|#define irix_elf_check_arch(hdr)&t;((hdr)-&gt;e_flags &amp; RHF_SGI_ONLY)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;PAGE_SIZE
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This could be done in userspace,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP       (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
multiline_comment|/*&n; * See comments in asm-alpha/elf.h, this is the same thing&n; * on the MIPS.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;do { &bslash;&n;&t;_r-&gt;regs[1] = _r-&gt;regs[2] = _r-&gt;regs[3] = _r-&gt;regs[4] = 0;&t;&bslash;&n;&t;_r-&gt;regs[5] = _r-&gt;regs[6] = _r-&gt;regs[7] = _r-&gt;regs[8] = 0;&t;&bslash;&n;&t;_r-&gt;regs[9] = _r-&gt;regs[10] = _r-&gt;regs[11] = _r-&gt;regs[12] = 0;&t;&bslash;&n;&t;_r-&gt;regs[13] = _r-&gt;regs[14] = _r-&gt;regs[15] = _r-&gt;regs[16] = 0;&t;&bslash;&n;&t;_r-&gt;regs[17] = _r-&gt;regs[18] = _r-&gt;regs[19] = _r-&gt;regs[20] = 0;&t;&bslash;&n;&t;_r-&gt;regs[21] = _r-&gt;regs[22] = _r-&gt;regs[23] = _r-&gt;regs[24] = 0;&t;&bslash;&n;&t;_r-&gt;regs[25] = _r-&gt;regs[26] = _r-&gt;regs[27] = _r-&gt;regs[28] = 0;&t;&bslash;&n;&t;_r-&gt;regs[30] = _r-&gt;regs[31] = 0;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
macro_line|#ifndef ELF_ET_DYN_BASE
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
macro_line|#endif
macro_line|#endif /* _ASM_ELF_H */
eof
