macro_line|#ifndef __ASMH8300_ELF_H
DECL|macro|__ASMH8300_ELF_H
mdefine_line|#define __ASMH8300_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof(struct user_regs_struct) / sizeof(elf_greg_t))
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
r_int
r_int
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_H8_300)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_H8_300
macro_line|#if defined(__H8300H__)
DECL|macro|ELF_FLAGS
mdefine_line|#define ELF_FLAGS       0x810000
macro_line|#endif
macro_line|#if defined(__H8300S__)
DECL|macro|ELF_FLAGS
mdefine_line|#define ELF_FLAGS       0x820000
macro_line|#endif
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;_r-&gt;er1 = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         0xD0000000UL
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality(PER_LINUX)
macro_line|#endif
DECL|macro|R_H8_NONE
mdefine_line|#define R_H8_NONE       0
DECL|macro|R_H8_DIR32
mdefine_line|#define R_H8_DIR32      1
DECL|macro|R_H8_DIR32_28
mdefine_line|#define R_H8_DIR32_28   2
DECL|macro|R_H8_DIR32_24
mdefine_line|#define R_H8_DIR32_24   3
DECL|macro|R_H8_DIR32_16
mdefine_line|#define R_H8_DIR32_16   4
DECL|macro|R_H8_DIR32U
mdefine_line|#define R_H8_DIR32U     6
DECL|macro|R_H8_DIR32U_28
mdefine_line|#define R_H8_DIR32U_28  7
DECL|macro|R_H8_DIR32U_24
mdefine_line|#define R_H8_DIR32U_24  8
DECL|macro|R_H8_DIR32U_20
mdefine_line|#define R_H8_DIR32U_20  9
DECL|macro|R_H8_DIR32U_16
mdefine_line|#define R_H8_DIR32U_16 10
DECL|macro|R_H8_DIR24
mdefine_line|#define R_H8_DIR24     11
DECL|macro|R_H8_DIR24_20
mdefine_line|#define R_H8_DIR24_20  12
DECL|macro|R_H8_DIR24_16
mdefine_line|#define R_H8_DIR24_16  13
DECL|macro|R_H8_DIR24U
mdefine_line|#define R_H8_DIR24U    14
DECL|macro|R_H8_DIR24U_20
mdefine_line|#define R_H8_DIR24U_20 15
DECL|macro|R_H8_DIR24U_16
mdefine_line|#define R_H8_DIR24U_16 16
DECL|macro|R_H8_DIR16
mdefine_line|#define R_H8_DIR16     17
DECL|macro|R_H8_DIR16U
mdefine_line|#define R_H8_DIR16U    18
DECL|macro|R_H8_DIR16S_32
mdefine_line|#define R_H8_DIR16S_32 19
DECL|macro|R_H8_DIR16S_28
mdefine_line|#define R_H8_DIR16S_28 20
DECL|macro|R_H8_DIR16S_24
mdefine_line|#define R_H8_DIR16S_24 21
DECL|macro|R_H8_DIR16S_20
mdefine_line|#define R_H8_DIR16S_20 22
DECL|macro|R_H8_DIR16S
mdefine_line|#define R_H8_DIR16S    23
DECL|macro|R_H8_DIR8
mdefine_line|#define R_H8_DIR8      24
DECL|macro|R_H8_DIR8U
mdefine_line|#define R_H8_DIR8U     25
DECL|macro|R_H8_DIR8Z_32
mdefine_line|#define R_H8_DIR8Z_32  26
DECL|macro|R_H8_DIR8Z_28
mdefine_line|#define R_H8_DIR8Z_28  27
DECL|macro|R_H8_DIR8Z_24
mdefine_line|#define R_H8_DIR8Z_24  28
DECL|macro|R_H8_DIR8Z_20
mdefine_line|#define R_H8_DIR8Z_20  29
DECL|macro|R_H8_DIR8Z_16
mdefine_line|#define R_H8_DIR8Z_16  30
DECL|macro|R_H8_PCREL16
mdefine_line|#define R_H8_PCREL16   31
DECL|macro|R_H8_PCREL8
mdefine_line|#define R_H8_PCREL8    32
DECL|macro|R_H8_BPOS
mdefine_line|#define R_H8_BPOS      33
DECL|macro|R_H8_PCREL32
mdefine_line|#define R_H8_PCREL32   34
DECL|macro|R_H8_GOT32O
mdefine_line|#define R_H8_GOT32O    35
DECL|macro|R_H8_GOT16O
mdefine_line|#define R_H8_GOT16O    36
DECL|macro|R_H8_DIR16A8
mdefine_line|#define R_H8_DIR16A8   59
DECL|macro|R_H8_DIR16R8
mdefine_line|#define R_H8_DIR16R8   60
DECL|macro|R_H8_DIR24A8
mdefine_line|#define R_H8_DIR24A8   61
DECL|macro|R_H8_DIR24R8
mdefine_line|#define R_H8_DIR24R8   62
DECL|macro|R_H8_DIR32A16
mdefine_line|#define R_H8_DIR32A16  63
DECL|macro|R_H8_ABS32
mdefine_line|#define R_H8_ABS32     65
DECL|macro|R_H8_ABS32A16
mdefine_line|#define R_H8_ABS32A16 127
macro_line|#endif
eof
