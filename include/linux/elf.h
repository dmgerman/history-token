macro_line|#ifndef _LINUX_ELF_H
DECL|macro|_LINUX_ELF_H
mdefine_line|#define _LINUX_ELF_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
multiline_comment|/* 32-bit ELF base types. */
DECL|typedef|Elf32_Addr
r_typedef
id|__u32
id|Elf32_Addr
suffix:semicolon
DECL|typedef|Elf32_Half
r_typedef
id|__u16
id|Elf32_Half
suffix:semicolon
DECL|typedef|Elf32_Off
r_typedef
id|__u32
id|Elf32_Off
suffix:semicolon
DECL|typedef|Elf32_Sword
r_typedef
id|__s32
id|Elf32_Sword
suffix:semicolon
DECL|typedef|Elf32_Word
r_typedef
id|__u32
id|Elf32_Word
suffix:semicolon
multiline_comment|/* 64-bit ELF base types. */
DECL|typedef|Elf64_Addr
r_typedef
id|__u64
id|Elf64_Addr
suffix:semicolon
DECL|typedef|Elf64_Half
r_typedef
id|__u16
id|Elf64_Half
suffix:semicolon
DECL|typedef|Elf64_SHalf
r_typedef
id|__s16
id|Elf64_SHalf
suffix:semicolon
DECL|typedef|Elf64_Off
r_typedef
id|__u64
id|Elf64_Off
suffix:semicolon
DECL|typedef|Elf64_Sword
r_typedef
id|__s32
id|Elf64_Sword
suffix:semicolon
DECL|typedef|Elf64_Word
r_typedef
id|__u32
id|Elf64_Word
suffix:semicolon
DECL|typedef|Elf64_Xword
r_typedef
id|__u64
id|Elf64_Xword
suffix:semicolon
DECL|typedef|Elf64_Sxword
r_typedef
id|__s64
id|Elf64_Sxword
suffix:semicolon
multiline_comment|/* These constants are for the segment types stored in the image headers */
DECL|macro|PT_NULL
mdefine_line|#define PT_NULL    0
DECL|macro|PT_LOAD
mdefine_line|#define PT_LOAD    1
DECL|macro|PT_DYNAMIC
mdefine_line|#define PT_DYNAMIC 2
DECL|macro|PT_INTERP
mdefine_line|#define PT_INTERP  3
DECL|macro|PT_NOTE
mdefine_line|#define PT_NOTE    4
DECL|macro|PT_SHLIB
mdefine_line|#define PT_SHLIB   5
DECL|macro|PT_PHDR
mdefine_line|#define PT_PHDR    6
DECL|macro|PT_LOPROC
mdefine_line|#define PT_LOPROC  0x70000000
DECL|macro|PT_HIPROC
mdefine_line|#define PT_HIPROC  0x7fffffff
DECL|macro|PT_MIPS_REGINFO
mdefine_line|#define PT_MIPS_REGINFO&t;&t;0x70000000
multiline_comment|/* Flags in the e_flags field of the header */
DECL|macro|EF_MIPS_NOREORDER
mdefine_line|#define EF_MIPS_NOREORDER 0x00000001
DECL|macro|EF_MIPS_PIC
mdefine_line|#define EF_MIPS_PIC       0x00000002
DECL|macro|EF_MIPS_CPIC
mdefine_line|#define EF_MIPS_CPIC      0x00000004
DECL|macro|EF_MIPS_ARCH
mdefine_line|#define EF_MIPS_ARCH      0xf0000000
multiline_comment|/* These constants define the different elf file types */
DECL|macro|ET_NONE
mdefine_line|#define ET_NONE   0
DECL|macro|ET_REL
mdefine_line|#define ET_REL    1
DECL|macro|ET_EXEC
mdefine_line|#define ET_EXEC   2
DECL|macro|ET_DYN
mdefine_line|#define ET_DYN    3
DECL|macro|ET_CORE
mdefine_line|#define ET_CORE   4
DECL|macro|ET_LOPROC
mdefine_line|#define ET_LOPROC 0xff00
DECL|macro|ET_HIPROC
mdefine_line|#define ET_HIPROC 0xffff
multiline_comment|/* These constants define the various ELF target machines */
DECL|macro|EM_NONE
mdefine_line|#define EM_NONE  0
DECL|macro|EM_M32
mdefine_line|#define EM_M32   1
DECL|macro|EM_SPARC
mdefine_line|#define EM_SPARC 2
DECL|macro|EM_386
mdefine_line|#define EM_386   3
DECL|macro|EM_68K
mdefine_line|#define EM_68K   4
DECL|macro|EM_88K
mdefine_line|#define EM_88K   5
DECL|macro|EM_486
mdefine_line|#define EM_486   6   /* Perhaps disused */
DECL|macro|EM_860
mdefine_line|#define EM_860   7
DECL|macro|EM_MIPS
mdefine_line|#define EM_MIPS&t;&t;8&t;/* MIPS R3000 (officially, big-endian only) */
DECL|macro|EM_MIPS_RS4_BE
mdefine_line|#define EM_MIPS_RS4_BE 10&t;/* MIPS R4000 big-endian */
DECL|macro|EM_PARISC
mdefine_line|#define EM_PARISC      15&t;/* HPPA */
DECL|macro|EM_SPARC32PLUS
mdefine_line|#define EM_SPARC32PLUS 18&t;/* Sun&squot;s &quot;v8plus&quot; */
DECL|macro|EM_PPC
mdefine_line|#define EM_PPC&t;       20&t;/* PowerPC */
DECL|macro|EM_PPC64
mdefine_line|#define EM_PPC64       21       /* PowerPC64 */
DECL|macro|EM_SH
mdefine_line|#define EM_SH&t;       42&t;/* SuperH */
DECL|macro|EM_SPARCV9
mdefine_line|#define EM_SPARCV9     43&t;/* SPARC v9 64-bit */
DECL|macro|EM_IA_64
mdefine_line|#define EM_IA_64&t;50&t;/* HP/Intel IA-64 */
DECL|macro|EM_X86_64
mdefine_line|#define EM_X86_64&t;62&t;/* AMD x86-64 */
DECL|macro|EM_S390
mdefine_line|#define EM_S390&t;&t;22&t;/* IBM S/390 */
DECL|macro|EM_CRIS
mdefine_line|#define EM_CRIS         76      /* Axis Communications 32-bit embedded processor */
DECL|macro|EM_V850
mdefine_line|#define EM_V850&t;&t;87&t;/* NEC v850 */
DECL|macro|EM_H8_300H
mdefine_line|#define EM_H8_300H      47      /* Hitachi H8/300H */
DECL|macro|EM_H8S
mdefine_line|#define EM_H8S          48      /* Hitachi H8S     */
multiline_comment|/*&n; * This is an interim value that we will use until the committee comes&n; * up with a final number.&n; */
DECL|macro|EM_ALPHA
mdefine_line|#define EM_ALPHA&t;0x9026
multiline_comment|/* Bogus old v850 magic number, used by old tools.  */
DECL|macro|EM_CYGNUS_V850
mdefine_line|#define EM_CYGNUS_V850&t;0x9080
multiline_comment|/*&n; * This is the old interim value for S/390 architecture&n; */
DECL|macro|EM_S390_OLD
mdefine_line|#define EM_S390_OLD     0xA390
multiline_comment|/* This is the info that is needed to parse the dynamic section of the file */
DECL|macro|DT_NULL
mdefine_line|#define DT_NULL&t;&t;0
DECL|macro|DT_NEEDED
mdefine_line|#define DT_NEEDED&t;1
DECL|macro|DT_PLTRELSZ
mdefine_line|#define DT_PLTRELSZ&t;2
DECL|macro|DT_PLTGOT
mdefine_line|#define DT_PLTGOT&t;3
DECL|macro|DT_HASH
mdefine_line|#define DT_HASH&t;&t;4
DECL|macro|DT_STRTAB
mdefine_line|#define DT_STRTAB&t;5
DECL|macro|DT_SYMTAB
mdefine_line|#define DT_SYMTAB&t;6
DECL|macro|DT_RELA
mdefine_line|#define DT_RELA&t;&t;7
DECL|macro|DT_RELASZ
mdefine_line|#define DT_RELASZ&t;8
DECL|macro|DT_RELAENT
mdefine_line|#define DT_RELAENT&t;9
DECL|macro|DT_STRSZ
mdefine_line|#define DT_STRSZ&t;10
DECL|macro|DT_SYMENT
mdefine_line|#define DT_SYMENT&t;11
DECL|macro|DT_INIT
mdefine_line|#define DT_INIT&t;&t;12
DECL|macro|DT_FINI
mdefine_line|#define DT_FINI&t;&t;13
DECL|macro|DT_SONAME
mdefine_line|#define DT_SONAME&t;14
DECL|macro|DT_RPATH
mdefine_line|#define DT_RPATH &t;15
DECL|macro|DT_SYMBOLIC
mdefine_line|#define DT_SYMBOLIC&t;16
DECL|macro|DT_REL
mdefine_line|#define DT_REL&t;        17
DECL|macro|DT_RELSZ
mdefine_line|#define DT_RELSZ&t;18
DECL|macro|DT_RELENT
mdefine_line|#define DT_RELENT&t;19
DECL|macro|DT_PLTREL
mdefine_line|#define DT_PLTREL&t;20
DECL|macro|DT_DEBUG
mdefine_line|#define DT_DEBUG&t;21
DECL|macro|DT_TEXTREL
mdefine_line|#define DT_TEXTREL&t;22
DECL|macro|DT_JMPREL
mdefine_line|#define DT_JMPREL&t;23
DECL|macro|DT_LOPROC
mdefine_line|#define DT_LOPROC&t;0x70000000
DECL|macro|DT_HIPROC
mdefine_line|#define DT_HIPROC&t;0x7fffffff
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
mdefine_line|#define RHF_NONE&t;&t;  0
DECL|macro|RHF_HARDWAY
mdefine_line|#define RHF_HARDWAY&t;&t;  1
DECL|macro|RHF_NOTPOT
mdefine_line|#define RHF_NOTPOT&t;&t;  2
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
multiline_comment|/* This info is needed when parsing the symbol table */
DECL|macro|STB_LOCAL
mdefine_line|#define STB_LOCAL  0
DECL|macro|STB_GLOBAL
mdefine_line|#define STB_GLOBAL 1
DECL|macro|STB_WEAK
mdefine_line|#define STB_WEAK   2
DECL|macro|STT_NOTYPE
mdefine_line|#define STT_NOTYPE  0
DECL|macro|STT_OBJECT
mdefine_line|#define STT_OBJECT  1
DECL|macro|STT_FUNC
mdefine_line|#define STT_FUNC    2
DECL|macro|STT_SECTION
mdefine_line|#define STT_SECTION 3
DECL|macro|STT_FILE
mdefine_line|#define STT_FILE    4
DECL|macro|ELF_ST_BIND
mdefine_line|#define ELF_ST_BIND(x)&t;&t;((x) &gt;&gt; 4)
DECL|macro|ELF_ST_TYPE
mdefine_line|#define ELF_ST_TYPE(x)&t;&t;(((unsigned int) x) &amp; 0xf)
DECL|macro|ELF32_ST_BIND
mdefine_line|#define ELF32_ST_BIND(x)&t;ELF_ST_BIND(x)
DECL|macro|ELF32_ST_TYPE
mdefine_line|#define ELF32_ST_TYPE(x)&t;ELF_ST_TYPE(x)
DECL|macro|ELF64_ST_BIND
mdefine_line|#define ELF64_ST_BIND(x)&t;ELF_ST_BIND(x)
DECL|macro|ELF64_ST_TYPE
mdefine_line|#define ELF64_ST_TYPE(x)&t;ELF_ST_TYPE(x)
multiline_comment|/* Symbolic values for the entries in the auxiliary table&n;   put on the initial stack */
DECL|macro|AT_NULL
mdefine_line|#define AT_NULL   0&t;/* end of vector */
DECL|macro|AT_IGNORE
mdefine_line|#define AT_IGNORE 1&t;/* entry should be ignored */
DECL|macro|AT_EXECFD
mdefine_line|#define AT_EXECFD 2&t;/* file descriptor of program */
DECL|macro|AT_PHDR
mdefine_line|#define AT_PHDR   3&t;/* program headers for program */
DECL|macro|AT_PHENT
mdefine_line|#define AT_PHENT  4&t;/* size of program header entry */
DECL|macro|AT_PHNUM
mdefine_line|#define AT_PHNUM  5&t;/* number of program headers */
DECL|macro|AT_PAGESZ
mdefine_line|#define AT_PAGESZ 6&t;/* system page size */
DECL|macro|AT_BASE
mdefine_line|#define AT_BASE   7&t;/* base address of interpreter */
DECL|macro|AT_FLAGS
mdefine_line|#define AT_FLAGS  8&t;/* flags */
DECL|macro|AT_ENTRY
mdefine_line|#define AT_ENTRY  9&t;/* entry point of program */
DECL|macro|AT_NOTELF
mdefine_line|#define AT_NOTELF 10&t;/* program is not ELF */
DECL|macro|AT_UID
mdefine_line|#define AT_UID    11&t;/* real uid */
DECL|macro|AT_EUID
mdefine_line|#define AT_EUID   12&t;/* effective uid */
DECL|macro|AT_GID
mdefine_line|#define AT_GID    13&t;/* real gid */
DECL|macro|AT_EGID
mdefine_line|#define AT_EGID   14&t;/* effective gid */
DECL|macro|AT_PLATFORM
mdefine_line|#define AT_PLATFORM 15  /* string identifying CPU for optimizations */
DECL|macro|AT_HWCAP
mdefine_line|#define AT_HWCAP  16    /* arch dependent hints at CPU capabilities */
DECL|macro|AT_CLKTCK
mdefine_line|#define AT_CLKTCK 17&t;/* frequency at which times() increments */
DECL|struct|dynamic
r_typedef
r_struct
id|dynamic
(brace
DECL|member|d_tag
id|Elf32_Sword
id|d_tag
suffix:semicolon
(def_block
r_union
(brace
DECL|member|d_val
id|Elf32_Sword
id|d_val
suffix:semicolon
DECL|member|d_ptr
id|Elf32_Addr
id|d_ptr
suffix:semicolon
DECL|member|d_un
)brace
)def_block
id|d_un
suffix:semicolon
DECL|typedef|Elf32_Dyn
)brace
id|Elf32_Dyn
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|d_tag
id|Elf64_Sxword
id|d_tag
suffix:semicolon
multiline_comment|/* entry tag value */
r_union
(brace
DECL|member|d_val
id|Elf64_Xword
id|d_val
suffix:semicolon
DECL|member|d_ptr
id|Elf64_Addr
id|d_ptr
suffix:semicolon
DECL|member|d_un
)brace
id|d_un
suffix:semicolon
DECL|typedef|Elf64_Dyn
)brace
id|Elf64_Dyn
suffix:semicolon
multiline_comment|/* The following are used with relocations */
DECL|macro|ELF32_R_SYM
mdefine_line|#define ELF32_R_SYM(x) ((x) &gt;&gt; 8)
DECL|macro|ELF32_R_TYPE
mdefine_line|#define ELF32_R_TYPE(x) ((x) &amp; 0xff)
DECL|macro|ELF64_R_SYM
mdefine_line|#define ELF64_R_SYM(i)&t;&t;&t;((i) &gt;&gt; 32)
DECL|macro|ELF64_R_TYPE
mdefine_line|#define ELF64_R_TYPE(i)&t;&t;&t;((i) &amp; 0xffffffff)
DECL|macro|R_ARM_NONE
mdefine_line|#define R_ARM_NONE&t;0
DECL|macro|R_ARM_PC24
mdefine_line|#define R_ARM_PC24&t;1
DECL|macro|R_ARM_ABS32
mdefine_line|#define R_ARM_ABS32&t;2
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
multiline_comment|/*&n; * Sparc ELF relocation types&n; */
DECL|macro|R_SPARC_NONE
mdefine_line|#define&t;R_SPARC_NONE&t;&t;0
DECL|macro|R_SPARC_8
mdefine_line|#define&t;R_SPARC_8&t;&t;1
DECL|macro|R_SPARC_16
mdefine_line|#define&t;R_SPARC_16&t;&t;2
DECL|macro|R_SPARC_32
mdefine_line|#define&t;R_SPARC_32&t;&t;3
DECL|macro|R_SPARC_DISP8
mdefine_line|#define&t;R_SPARC_DISP8&t;&t;4
DECL|macro|R_SPARC_DISP16
mdefine_line|#define&t;R_SPARC_DISP16&t;&t;5
DECL|macro|R_SPARC_DISP32
mdefine_line|#define&t;R_SPARC_DISP32&t;&t;6
DECL|macro|R_SPARC_WDISP30
mdefine_line|#define&t;R_SPARC_WDISP30&t;&t;7
DECL|macro|R_SPARC_WDISP22
mdefine_line|#define&t;R_SPARC_WDISP22&t;&t;8
DECL|macro|R_SPARC_HI22
mdefine_line|#define&t;R_SPARC_HI22&t;&t;9
DECL|macro|R_SPARC_22
mdefine_line|#define&t;R_SPARC_22&t;&t;10
DECL|macro|R_SPARC_13
mdefine_line|#define&t;R_SPARC_13&t;&t;11
DECL|macro|R_SPARC_LO10
mdefine_line|#define&t;R_SPARC_LO10&t;&t;12
DECL|macro|R_SPARC_GOT10
mdefine_line|#define&t;R_SPARC_GOT10&t;&t;13
DECL|macro|R_SPARC_GOT13
mdefine_line|#define&t;R_SPARC_GOT13&t;&t;14
DECL|macro|R_SPARC_GOT22
mdefine_line|#define&t;R_SPARC_GOT22&t;&t;15
DECL|macro|R_SPARC_PC10
mdefine_line|#define&t;R_SPARC_PC10&t;&t;16
DECL|macro|R_SPARC_PC22
mdefine_line|#define&t;R_SPARC_PC22&t;&t;17
DECL|macro|R_SPARC_WPLT30
mdefine_line|#define&t;R_SPARC_WPLT30&t;&t;18
DECL|macro|R_SPARC_COPY
mdefine_line|#define&t;R_SPARC_COPY&t;&t;19
DECL|macro|R_SPARC_GLOB_DAT
mdefine_line|#define&t;R_SPARC_GLOB_DAT&t;20
DECL|macro|R_SPARC_JMP_SLOT
mdefine_line|#define&t;R_SPARC_JMP_SLOT&t;21
DECL|macro|R_SPARC_RELATIVE
mdefine_line|#define&t;R_SPARC_RELATIVE&t;22
DECL|macro|R_SPARC_UA32
mdefine_line|#define&t;R_SPARC_UA32&t;&t;23
DECL|macro|R_SPARC_PLT32
mdefine_line|#define R_SPARC_PLT32&t;&t;24
DECL|macro|R_SPARC_HIPLT22
mdefine_line|#define R_SPARC_HIPLT22&t;&t;25
DECL|macro|R_SPARC_LOPLT10
mdefine_line|#define R_SPARC_LOPLT10&t;&t;26
DECL|macro|R_SPARC_PCPLT32
mdefine_line|#define R_SPARC_PCPLT32&t;&t;27
DECL|macro|R_SPARC_PCPLT22
mdefine_line|#define R_SPARC_PCPLT22&t;&t;28
DECL|macro|R_SPARC_PCPLT10
mdefine_line|#define R_SPARC_PCPLT10&t;&t;29
DECL|macro|R_SPARC_10
mdefine_line|#define R_SPARC_10&t;&t;30
DECL|macro|R_SPARC_11
mdefine_line|#define R_SPARC_11&t;&t;31
DECL|macro|R_SPARC_64
mdefine_line|#define R_SPARC_64&t;&t;32
DECL|macro|R_SPARC_WDISP16
mdefine_line|#define R_SPARC_WDISP16&t;&t;40
DECL|macro|R_SPARC_WDISP19
mdefine_line|#define R_SPARC_WDISP19&t;&t;41
DECL|macro|R_SPARC_7
mdefine_line|#define R_SPARC_7&t;&t;43
DECL|macro|R_SPARC_5
mdefine_line|#define R_SPARC_5&t;&t;44
DECL|macro|R_SPARC_6
mdefine_line|#define R_SPARC_6&t;&t;45
multiline_comment|/* Bits present in AT_HWCAP, primarily for Sparc32.  */
DECL|macro|HWCAP_SPARC_FLUSH
mdefine_line|#define HWCAP_SPARC_FLUSH       1    /* CPU supports flush instruction. */
DECL|macro|HWCAP_SPARC_STBAR
mdefine_line|#define HWCAP_SPARC_STBAR       2
DECL|macro|HWCAP_SPARC_SWAP
mdefine_line|#define HWCAP_SPARC_SWAP        4
DECL|macro|HWCAP_SPARC_MULDIV
mdefine_line|#define HWCAP_SPARC_MULDIV      8
DECL|macro|HWCAP_SPARC_V9
mdefine_line|#define HWCAP_SPARC_V9&t;&t;16
DECL|macro|HWCAP_SPARC_ULTRA3
mdefine_line|#define HWCAP_SPARC_ULTRA3&t;32
multiline_comment|/*&n; * 68k ELF relocation types&n; */
DECL|macro|R_68K_NONE
mdefine_line|#define R_68K_NONE&t;0
DECL|macro|R_68K_32
mdefine_line|#define R_68K_32&t;1
DECL|macro|R_68K_16
mdefine_line|#define R_68K_16&t;2
DECL|macro|R_68K_8
mdefine_line|#define R_68K_8&t;&t;3
DECL|macro|R_68K_PC32
mdefine_line|#define R_68K_PC32&t;4
DECL|macro|R_68K_PC16
mdefine_line|#define R_68K_PC16&t;5
DECL|macro|R_68K_PC8
mdefine_line|#define R_68K_PC8&t;6
DECL|macro|R_68K_GOT32
mdefine_line|#define R_68K_GOT32&t;7
DECL|macro|R_68K_GOT16
mdefine_line|#define R_68K_GOT16&t;8
DECL|macro|R_68K_GOT8
mdefine_line|#define R_68K_GOT8&t;9
DECL|macro|R_68K_GOT32O
mdefine_line|#define R_68K_GOT32O&t;10
DECL|macro|R_68K_GOT16O
mdefine_line|#define R_68K_GOT16O&t;11
DECL|macro|R_68K_GOT8O
mdefine_line|#define R_68K_GOT8O&t;12
DECL|macro|R_68K_PLT32
mdefine_line|#define R_68K_PLT32&t;13
DECL|macro|R_68K_PLT16
mdefine_line|#define R_68K_PLT16&t;14
DECL|macro|R_68K_PLT8
mdefine_line|#define R_68K_PLT8&t;15
DECL|macro|R_68K_PLT32O
mdefine_line|#define R_68K_PLT32O&t;16
DECL|macro|R_68K_PLT16O
mdefine_line|#define R_68K_PLT16O&t;17
DECL|macro|R_68K_PLT8O
mdefine_line|#define R_68K_PLT8O&t;18
DECL|macro|R_68K_COPY
mdefine_line|#define R_68K_COPY&t;19
DECL|macro|R_68K_GLOB_DAT
mdefine_line|#define R_68K_GLOB_DAT&t;20
DECL|macro|R_68K_JMP_SLOT
mdefine_line|#define R_68K_JMP_SLOT&t;21
DECL|macro|R_68K_RELATIVE
mdefine_line|#define R_68K_RELATIVE&t;22
multiline_comment|/*&n; * Alpha ELF relocation types&n; */
DECL|macro|R_ALPHA_NONE
mdefine_line|#define R_ALPHA_NONE            0       /* No reloc */
DECL|macro|R_ALPHA_REFLONG
mdefine_line|#define R_ALPHA_REFLONG         1       /* Direct 32 bit */
DECL|macro|R_ALPHA_REFQUAD
mdefine_line|#define R_ALPHA_REFQUAD         2       /* Direct 64 bit */
DECL|macro|R_ALPHA_GPREL32
mdefine_line|#define R_ALPHA_GPREL32         3       /* GP relative 32 bit */
DECL|macro|R_ALPHA_LITERAL
mdefine_line|#define R_ALPHA_LITERAL         4       /* GP relative 16 bit w/optimization */
DECL|macro|R_ALPHA_LITUSE
mdefine_line|#define R_ALPHA_LITUSE          5       /* Optimization hint for LITERAL */
DECL|macro|R_ALPHA_GPDISP
mdefine_line|#define R_ALPHA_GPDISP          6       /* Add displacement to GP */
DECL|macro|R_ALPHA_BRADDR
mdefine_line|#define R_ALPHA_BRADDR          7       /* PC+4 relative 23 bit shifted */
DECL|macro|R_ALPHA_HINT
mdefine_line|#define R_ALPHA_HINT            8       /* PC+4 relative 16 bit shifted */
DECL|macro|R_ALPHA_SREL16
mdefine_line|#define R_ALPHA_SREL16          9       /* PC relative 16 bit */
DECL|macro|R_ALPHA_SREL32
mdefine_line|#define R_ALPHA_SREL32          10      /* PC relative 32 bit */
DECL|macro|R_ALPHA_SREL64
mdefine_line|#define R_ALPHA_SREL64          11      /* PC relative 64 bit */
DECL|macro|R_ALPHA_GPRELHIGH
mdefine_line|#define R_ALPHA_GPRELHIGH       17      /* GP relative 32 bit, high 16 bits */
DECL|macro|R_ALPHA_GPRELLOW
mdefine_line|#define R_ALPHA_GPRELLOW        18      /* GP relative 32 bit, low 16 bits */
DECL|macro|R_ALPHA_GPREL16
mdefine_line|#define R_ALPHA_GPREL16         19      /* GP relative 16 bit */
DECL|macro|R_ALPHA_COPY
mdefine_line|#define R_ALPHA_COPY            24      /* Copy symbol at runtime */
DECL|macro|R_ALPHA_GLOB_DAT
mdefine_line|#define R_ALPHA_GLOB_DAT        25      /* Create GOT entry */
DECL|macro|R_ALPHA_JMP_SLOT
mdefine_line|#define R_ALPHA_JMP_SLOT        26      /* Create PLT entry */
DECL|macro|R_ALPHA_RELATIVE
mdefine_line|#define R_ALPHA_RELATIVE        27      /* Adjust by program base */
DECL|macro|R_ALPHA_BRSGP
mdefine_line|#define R_ALPHA_BRSGP&t;&t;28
DECL|macro|R_ALPHA_TLSGD
mdefine_line|#define R_ALPHA_TLSGD           29
DECL|macro|R_ALPHA_TLS_LDM
mdefine_line|#define R_ALPHA_TLS_LDM         30
DECL|macro|R_ALPHA_DTPMOD64
mdefine_line|#define R_ALPHA_DTPMOD64        31
DECL|macro|R_ALPHA_GOTDTPREL
mdefine_line|#define R_ALPHA_GOTDTPREL       32
DECL|macro|R_ALPHA_DTPREL64
mdefine_line|#define R_ALPHA_DTPREL64        33
DECL|macro|R_ALPHA_DTPRELHI
mdefine_line|#define R_ALPHA_DTPRELHI        34
DECL|macro|R_ALPHA_DTPRELLO
mdefine_line|#define R_ALPHA_DTPRELLO        35
DECL|macro|R_ALPHA_DTPREL16
mdefine_line|#define R_ALPHA_DTPREL16        36
DECL|macro|R_ALPHA_GOTTPREL
mdefine_line|#define R_ALPHA_GOTTPREL        37
DECL|macro|R_ALPHA_TPREL64
mdefine_line|#define R_ALPHA_TPREL64         38
DECL|macro|R_ALPHA_TPRELHI
mdefine_line|#define R_ALPHA_TPRELHI         39
DECL|macro|R_ALPHA_TPRELLO
mdefine_line|#define R_ALPHA_TPRELLO         40
DECL|macro|R_ALPHA_TPREL16
mdefine_line|#define R_ALPHA_TPREL16         41
DECL|macro|SHF_ALPHA_GPREL
mdefine_line|#define SHF_ALPHA_GPREL&t;&t;0x10000000
multiline_comment|/* PowerPC relocations defined by the ABIs */
DECL|macro|R_PPC_NONE
mdefine_line|#define R_PPC_NONE&t;&t;0
DECL|macro|R_PPC_ADDR32
mdefine_line|#define R_PPC_ADDR32&t;&t;1&t;/* 32bit absolute address */
DECL|macro|R_PPC_ADDR24
mdefine_line|#define R_PPC_ADDR24&t;&t;2&t;/* 26bit address, 2 bits ignored.  */
DECL|macro|R_PPC_ADDR16
mdefine_line|#define R_PPC_ADDR16&t;&t;3&t;/* 16bit absolute address */
DECL|macro|R_PPC_ADDR16_LO
mdefine_line|#define R_PPC_ADDR16_LO&t;&t;4&t;/* lower 16bit of absolute address */
DECL|macro|R_PPC_ADDR16_HI
mdefine_line|#define R_PPC_ADDR16_HI&t;&t;5&t;/* high 16bit of absolute address */
DECL|macro|R_PPC_ADDR16_HA
mdefine_line|#define R_PPC_ADDR16_HA&t;&t;6&t;/* adjusted high 16bit */
DECL|macro|R_PPC_ADDR14
mdefine_line|#define R_PPC_ADDR14&t;&t;7&t;/* 16bit address, 2 bits ignored */
DECL|macro|R_PPC_ADDR14_BRTAKEN
mdefine_line|#define R_PPC_ADDR14_BRTAKEN&t;8
DECL|macro|R_PPC_ADDR14_BRNTAKEN
mdefine_line|#define R_PPC_ADDR14_BRNTAKEN&t;9
DECL|macro|R_PPC_REL24
mdefine_line|#define R_PPC_REL24&t;&t;10&t;/* PC relative 26 bit */
DECL|macro|R_PPC_REL14
mdefine_line|#define R_PPC_REL14&t;&t;11&t;/* PC relative 16 bit */
DECL|macro|R_PPC_REL14_BRTAKEN
mdefine_line|#define R_PPC_REL14_BRTAKEN&t;12
DECL|macro|R_PPC_REL14_BRNTAKEN
mdefine_line|#define R_PPC_REL14_BRNTAKEN&t;13
DECL|macro|R_PPC_GOT16
mdefine_line|#define R_PPC_GOT16&t;&t;14
DECL|macro|R_PPC_GOT16_LO
mdefine_line|#define R_PPC_GOT16_LO&t;&t;15
DECL|macro|R_PPC_GOT16_HI
mdefine_line|#define R_PPC_GOT16_HI&t;&t;16
DECL|macro|R_PPC_GOT16_HA
mdefine_line|#define R_PPC_GOT16_HA&t;&t;17
DECL|macro|R_PPC_PLTREL24
mdefine_line|#define R_PPC_PLTREL24&t;&t;18
DECL|macro|R_PPC_COPY
mdefine_line|#define R_PPC_COPY&t;&t;19
DECL|macro|R_PPC_GLOB_DAT
mdefine_line|#define R_PPC_GLOB_DAT&t;&t;20
DECL|macro|R_PPC_JMP_SLOT
mdefine_line|#define R_PPC_JMP_SLOT&t;&t;21
DECL|macro|R_PPC_RELATIVE
mdefine_line|#define R_PPC_RELATIVE&t;&t;22
DECL|macro|R_PPC_LOCAL24PC
mdefine_line|#define R_PPC_LOCAL24PC&t;&t;23
DECL|macro|R_PPC_UADDR32
mdefine_line|#define R_PPC_UADDR32&t;&t;24
DECL|macro|R_PPC_UADDR16
mdefine_line|#define R_PPC_UADDR16&t;&t;25
DECL|macro|R_PPC_REL32
mdefine_line|#define R_PPC_REL32&t;&t;26
DECL|macro|R_PPC_PLT32
mdefine_line|#define R_PPC_PLT32&t;&t;27
DECL|macro|R_PPC_PLTREL32
mdefine_line|#define R_PPC_PLTREL32&t;&t;28
DECL|macro|R_PPC_PLT16_LO
mdefine_line|#define R_PPC_PLT16_LO&t;&t;29
DECL|macro|R_PPC_PLT16_HI
mdefine_line|#define R_PPC_PLT16_HI&t;&t;30
DECL|macro|R_PPC_PLT16_HA
mdefine_line|#define R_PPC_PLT16_HA&t;&t;31
DECL|macro|R_PPC_SDAREL16
mdefine_line|#define R_PPC_SDAREL16&t;&t;32
DECL|macro|R_PPC_SECTOFF
mdefine_line|#define R_PPC_SECTOFF&t;&t;33
DECL|macro|R_PPC_SECTOFF_LO
mdefine_line|#define R_PPC_SECTOFF_LO&t;34
DECL|macro|R_PPC_SECTOFF_HI
mdefine_line|#define R_PPC_SECTOFF_HI&t;35
DECL|macro|R_PPC_SECTOFF_HA
mdefine_line|#define R_PPC_SECTOFF_HA&t;36
multiline_comment|/* Keep this the last entry.  */
DECL|macro|R_PPC_NUM
mdefine_line|#define R_PPC_NUM&t;&t;37
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
multiline_comment|/* Keep this the last entry.  */
DECL|macro|R_390_NUM
mdefine_line|#define R_390_NUM&t;57
multiline_comment|/* x86-64 relocation types */
DECL|macro|R_X86_64_NONE
mdefine_line|#define R_X86_64_NONE&t;&t;0&t;/* No reloc */
DECL|macro|R_X86_64_64
mdefine_line|#define R_X86_64_64&t;&t;1&t;/* Direct 64 bit  */
DECL|macro|R_X86_64_PC32
mdefine_line|#define R_X86_64_PC32&t;&t;2&t;/* PC relative 32 bit signed */
DECL|macro|R_X86_64_GOT32
mdefine_line|#define R_X86_64_GOT32&t;&t;3&t;/* 32 bit GOT entry */
DECL|macro|R_X86_64_PLT32
mdefine_line|#define R_X86_64_PLT32&t;&t;4&t;/* 32 bit PLT address */
DECL|macro|R_X86_64_COPY
mdefine_line|#define R_X86_64_COPY&t;&t;5&t;/* Copy symbol at runtime */
DECL|macro|R_X86_64_GLOB_DAT
mdefine_line|#define R_X86_64_GLOB_DAT&t;6&t;/* Create GOT entry */
DECL|macro|R_X86_64_JUMP_SLOT
mdefine_line|#define R_X86_64_JUMP_SLOT&t;7&t;/* Create PLT entry */
DECL|macro|R_X86_64_RELATIVE
mdefine_line|#define R_X86_64_RELATIVE&t;8&t;/* Adjust by program base */
DECL|macro|R_X86_64_GOTPCREL
mdefine_line|#define R_X86_64_GOTPCREL&t;9&t;/* 32 bit signed pc relative&n;&t;&t;&t;&t;&t;   offset to GOT */
DECL|macro|R_X86_64_32
mdefine_line|#define R_X86_64_32&t;&t;10&t;/* Direct 32 bit zero extended */
DECL|macro|R_X86_64_32S
mdefine_line|#define R_X86_64_32S&t;&t;11&t;/* Direct 32 bit sign extended */
DECL|macro|R_X86_64_16
mdefine_line|#define R_X86_64_16&t;&t;12&t;/* Direct 16 bit zero extended */
DECL|macro|R_X86_64_PC16
mdefine_line|#define R_X86_64_PC16&t;&t;13&t;/* 16 bit sign extended pc relative */
DECL|macro|R_X86_64_8
mdefine_line|#define R_X86_64_8&t;&t;14&t;/* Direct 8 bit sign extended  */
DECL|macro|R_X86_64_PC8
mdefine_line|#define R_X86_64_PC8&t;&t;15&t;/* 8 bit sign extended pc relative */
DECL|macro|R_X86_64_NUM
mdefine_line|#define R_X86_64_NUM&t;&t;16
multiline_comment|/* Legal values for e_flags field of Elf64_Ehdr.  */
DECL|macro|EF_ALPHA_32BIT
mdefine_line|#define EF_ALPHA_32BIT&t;&t;1&t;/* All addresses are below 2GB */
multiline_comment|/* HPPA specific definitions.  */
multiline_comment|/* Legal values for e_flags field of Elf32_Ehdr.  */
DECL|macro|EF_PARISC_TRAPNIL
mdefine_line|#define EF_PARISC_TRAPNIL&t;0x00010000 /* Trap nil pointer dereference.  */
DECL|macro|EF_PARISC_EXT
mdefine_line|#define EF_PARISC_EXT&t;&t;0x00020000 /* Program uses arch. extensions. */
DECL|macro|EF_PARISC_LSB
mdefine_line|#define EF_PARISC_LSB&t;&t;0x00040000 /* Program expects little endian. */
DECL|macro|EF_PARISC_WIDE
mdefine_line|#define EF_PARISC_WIDE&t;&t;0x00080000 /* Program expects wide mode.  */
DECL|macro|EF_PARISC_NO_KABP
mdefine_line|#define EF_PARISC_NO_KABP&t;0x00100000 /* No kernel assisted branch&n;&t;&t;&t;&t;&t;      prediction.  */
DECL|macro|EF_PARISC_LAZYSWAP
mdefine_line|#define EF_PARISC_LAZYSWAP&t;0x00400000 /* Allow lazy swapping.  */
DECL|macro|EF_PARISC_ARCH
mdefine_line|#define EF_PARISC_ARCH&t;&t;0x0000ffff /* Architecture version.  */
multiline_comment|/* Defined values for `e_flags &amp; EF_PARISC_ARCH&squot; are:  */
DECL|macro|EFA_PARISC_1_0
mdefine_line|#define EFA_PARISC_1_0&t;&t;    0x020b /* PA-RISC 1.0 big-endian.  */
DECL|macro|EFA_PARISC_1_1
mdefine_line|#define EFA_PARISC_1_1&t;&t;    0x0210 /* PA-RISC 1.1 big-endian.  */
DECL|macro|EFA_PARISC_2_0
mdefine_line|#define EFA_PARISC_2_0&t;&t;    0x0214 /* PA-RISC 2.0 big-endian.  */
multiline_comment|/* Additional section indeces.  */
DECL|macro|SHN_PARISC_ANSI_COMMON
mdefine_line|#define SHN_PARISC_ANSI_COMMON&t;0xff00&t;   /* Section for tenatively declared&n;&t;&t;&t;&t;&t;      symbols in ANSI C.  */
DECL|macro|SHN_PARISC_HUGE_COMMON
mdefine_line|#define SHN_PARISC_HUGE_COMMON&t;0xff01&t;   /* Common blocks in huge model.  */
multiline_comment|/* Legal values for sh_type field of Elf32_Shdr.  */
DECL|macro|SHT_PARISC_EXT
mdefine_line|#define SHT_PARISC_EXT&t;&t;0x70000000 /* Contains product specific ext. */
DECL|macro|SHT_PARISC_UNWIND
mdefine_line|#define SHT_PARISC_UNWIND&t;0x70000001 /* Unwind information.  */
DECL|macro|SHT_PARISC_DOC
mdefine_line|#define SHT_PARISC_DOC&t;&t;0x70000002 /* Debug info for optimized code. */
multiline_comment|/* Legal values for sh_flags field of Elf32_Shdr.  */
DECL|macro|SHF_PARISC_SHORT
mdefine_line|#define SHF_PARISC_SHORT&t;0x20000000 /* Section with short addressing. */
DECL|macro|SHF_PARISC_HUGE
mdefine_line|#define SHF_PARISC_HUGE&t;&t;0x40000000 /* Section far from gp.  */
DECL|macro|SHF_PARISC_SBP
mdefine_line|#define SHF_PARISC_SBP&t;&t;0x80000000 /* Static branch prediction code. */
multiline_comment|/* Legal values for ST_TYPE subfield of st_info (symbol type).  */
DECL|macro|STT_PARISC_MILLICODE
mdefine_line|#define STT_PARISC_MILLICODE&t;13&t;/* Millicode function entry point.  */
DECL|macro|STT_HP_OPAQUE
mdefine_line|#define STT_HP_OPAQUE&t;&t;(STT_LOOS + 0x1)
DECL|macro|STT_HP_STUB
mdefine_line|#define STT_HP_STUB&t;&t;(STT_LOOS + 0x2)
multiline_comment|/* HPPA relocs.  */
DECL|macro|R_PARISC_NONE
mdefine_line|#define R_PARISC_NONE&t;&t;0&t;/* No reloc.  */
DECL|macro|R_PARISC_DIR32
mdefine_line|#define R_PARISC_DIR32&t;&t;1&t;/* Direct 32-bit reference.  */
DECL|macro|R_PARISC_DIR21L
mdefine_line|#define R_PARISC_DIR21L&t;&t;2&t;/* Left 21 bits of eff. address.  */
DECL|macro|R_PARISC_DIR17R
mdefine_line|#define R_PARISC_DIR17R&t;&t;3&t;/* Right 17 bits of eff. address.  */
DECL|macro|R_PARISC_DIR17F
mdefine_line|#define R_PARISC_DIR17F&t;&t;4&t;/* 17 bits of eff. address.  */
DECL|macro|R_PARISC_DIR14R
mdefine_line|#define R_PARISC_DIR14R&t;&t;6&t;/* Right 14 bits of eff. address.  */
DECL|macro|R_PARISC_PCREL32
mdefine_line|#define R_PARISC_PCREL32&t;9&t;/* 32-bit rel. address.  */
DECL|macro|R_PARISC_PCREL21L
mdefine_line|#define R_PARISC_PCREL21L&t;10&t;/* Left 21 bits of rel. address.  */
DECL|macro|R_PARISC_PCREL17R
mdefine_line|#define R_PARISC_PCREL17R&t;11&t;/* Right 17 bits of rel. address.  */
DECL|macro|R_PARISC_PCREL17F
mdefine_line|#define R_PARISC_PCREL17F&t;12&t;/* 17 bits of rel. address.  */
DECL|macro|R_PARISC_PCREL14R
mdefine_line|#define R_PARISC_PCREL14R&t;14&t;/* Right 14 bits of rel. address.  */
DECL|macro|R_PARISC_DPREL21L
mdefine_line|#define R_PARISC_DPREL21L&t;18&t;/* Left 21 bits of rel. address.  */
DECL|macro|R_PARISC_DPREL14R
mdefine_line|#define R_PARISC_DPREL14R&t;22&t;/* Right 14 bits of rel. address.  */
DECL|macro|R_PARISC_GPREL21L
mdefine_line|#define R_PARISC_GPREL21L&t;26&t;/* GP-relative, left 21 bits.  */
DECL|macro|R_PARISC_GPREL14R
mdefine_line|#define R_PARISC_GPREL14R&t;30&t;/* GP-relative, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF21L
mdefine_line|#define R_PARISC_LTOFF21L&t;34&t;/* LT-relative, left 21 bits.  */
DECL|macro|R_PARISC_LTOFF14R
mdefine_line|#define R_PARISC_LTOFF14R&t;38&t;/* LT-relative, right 14 bits.  */
DECL|macro|R_PARISC_SECREL32
mdefine_line|#define R_PARISC_SECREL32&t;41&t;/* 32 bits section rel. address.  */
DECL|macro|R_PARISC_SEGBASE
mdefine_line|#define R_PARISC_SEGBASE&t;48&t;/* No relocation, set segment base.  */
DECL|macro|R_PARISC_SEGREL32
mdefine_line|#define R_PARISC_SEGREL32&t;49&t;/* 32 bits segment rel. address.  */
DECL|macro|R_PARISC_PLTOFF21L
mdefine_line|#define R_PARISC_PLTOFF21L&t;50&t;/* PLT rel. address, left 21 bits.  */
DECL|macro|R_PARISC_PLTOFF14R
mdefine_line|#define R_PARISC_PLTOFF14R&t;54&t;/* PLT rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF_FPTR32
mdefine_line|#define R_PARISC_LTOFF_FPTR32&t;57&t;/* 32 bits LT-rel. function pointer. */
DECL|macro|R_PARISC_LTOFF_FPTR21L
mdefine_line|#define R_PARISC_LTOFF_FPTR21L&t;58&t;/* LT-rel. fct ptr, left 21 bits. */
DECL|macro|R_PARISC_LTOFF_FPTR14R
mdefine_line|#define R_PARISC_LTOFF_FPTR14R&t;62&t;/* LT-rel. fct ptr, right 14 bits. */
DECL|macro|R_PARISC_FPTR64
mdefine_line|#define R_PARISC_FPTR64&t;&t;64&t;/* 64 bits function address.  */
DECL|macro|R_PARISC_PLABEL32
mdefine_line|#define R_PARISC_PLABEL32&t;65&t;/* 32 bits function address.  */
DECL|macro|R_PARISC_PCREL64
mdefine_line|#define R_PARISC_PCREL64&t;72&t;/* 64 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL22F
mdefine_line|#define R_PARISC_PCREL22F&t;74&t;/* 22 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL14WR
mdefine_line|#define R_PARISC_PCREL14WR&t;75&t;/* PC-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PCREL14DR
mdefine_line|#define R_PARISC_PCREL14DR&t;76&t;/* PC rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PCREL16F
mdefine_line|#define R_PARISC_PCREL16F&t;77&t;/* 16 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL16WF
mdefine_line|#define R_PARISC_PCREL16WF&t;78&t;/* 16 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL16DF
mdefine_line|#define R_PARISC_PCREL16DF&t;79&t;/* 16 bits PC-rel. address.  */
DECL|macro|R_PARISC_DIR64
mdefine_line|#define R_PARISC_DIR64&t;&t;80&t;/* 64 bits of eff. address.  */
DECL|macro|R_PARISC_DIR14WR
mdefine_line|#define R_PARISC_DIR14WR&t;83&t;/* 14 bits of eff. address.  */
DECL|macro|R_PARISC_DIR14DR
mdefine_line|#define R_PARISC_DIR14DR&t;84&t;/* 14 bits of eff. address.  */
DECL|macro|R_PARISC_DIR16F
mdefine_line|#define R_PARISC_DIR16F&t;&t;85&t;/* 16 bits of eff. address.  */
DECL|macro|R_PARISC_DIR16WF
mdefine_line|#define R_PARISC_DIR16WF&t;86&t;/* 16 bits of eff. address.  */
DECL|macro|R_PARISC_DIR16DF
mdefine_line|#define R_PARISC_DIR16DF&t;87&t;/* 16 bits of eff. address.  */
DECL|macro|R_PARISC_GPREL64
mdefine_line|#define R_PARISC_GPREL64&t;88&t;/* 64 bits of GP-rel. address.  */
DECL|macro|R_PARISC_GPREL14WR
mdefine_line|#define R_PARISC_GPREL14WR&t;91&t;/* GP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_GPREL14DR
mdefine_line|#define R_PARISC_GPREL14DR&t;92&t;/* GP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_GPREL16F
mdefine_line|#define R_PARISC_GPREL16F&t;93&t;/* 16 bits GP-rel. address.  */
DECL|macro|R_PARISC_GPREL16WF
mdefine_line|#define R_PARISC_GPREL16WF&t;94&t;/* 16 bits GP-rel. address.  */
DECL|macro|R_PARISC_GPREL16DF
mdefine_line|#define R_PARISC_GPREL16DF&t;95&t;/* 16 bits GP-rel. address.  */
DECL|macro|R_PARISC_LTOFF64
mdefine_line|#define R_PARISC_LTOFF64&t;96&t;/* 64 bits LT-rel. address.  */
DECL|macro|R_PARISC_LTOFF14WR
mdefine_line|#define R_PARISC_LTOFF14WR&t;99&t;/* LT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF14DR
mdefine_line|#define R_PARISC_LTOFF14DR&t;100&t;/* LT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF16F
mdefine_line|#define R_PARISC_LTOFF16F&t;101&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_LTOFF16WF
mdefine_line|#define R_PARISC_LTOFF16WF&t;102&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_LTOFF16DF
mdefine_line|#define R_PARISC_LTOFF16DF&t;103&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_SECREL64
mdefine_line|#define R_PARISC_SECREL64&t;104&t;/* 64 bits section rel. address.  */
DECL|macro|R_PARISC_SEGREL64
mdefine_line|#define R_PARISC_SEGREL64&t;112&t;/* 64 bits segment rel. address.  */
DECL|macro|R_PARISC_PLTOFF14WR
mdefine_line|#define R_PARISC_PLTOFF14WR&t;115&t;/* PLT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PLTOFF14DR
mdefine_line|#define R_PARISC_PLTOFF14DR&t;116&t;/* PLT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PLTOFF16F
mdefine_line|#define R_PARISC_PLTOFF16F&t;117&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_PLTOFF16WF
mdefine_line|#define R_PARISC_PLTOFF16WF&t;118&t;/* 16 bits PLT-rel. address.  */
DECL|macro|R_PARISC_PLTOFF16DF
mdefine_line|#define R_PARISC_PLTOFF16DF&t;119&t;/* 16 bits PLT-rel. address.  */
DECL|macro|R_PARISC_LTOFF_FPTR64
mdefine_line|#define R_PARISC_LTOFF_FPTR64&t;120&t;/* 64 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LTOFF_FPTR14WR
mdefine_line|#define R_PARISC_LTOFF_FPTR14WR&t;123&t;/* LT-rel. fct. ptr., right 14 bits. */
DECL|macro|R_PARISC_LTOFF_FPTR14DR
mdefine_line|#define R_PARISC_LTOFF_FPTR14DR&t;124&t;/* LT-rel. fct. ptr., right 14 bits. */
DECL|macro|R_PARISC_LTOFF_FPTR16F
mdefine_line|#define R_PARISC_LTOFF_FPTR16F&t;125&t;/* 16 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LTOFF_FPTR16WF
mdefine_line|#define R_PARISC_LTOFF_FPTR16WF&t;126&t;/* 16 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LTOFF_FPTR16DF
mdefine_line|#define R_PARISC_LTOFF_FPTR16DF&t;127&t;/* 16 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LORESERVE
mdefine_line|#define R_PARISC_LORESERVE&t;128
DECL|macro|R_PARISC_COPY
mdefine_line|#define R_PARISC_COPY&t;&t;128&t;/* Copy relocation.  */
DECL|macro|R_PARISC_IPLT
mdefine_line|#define R_PARISC_IPLT&t;&t;129&t;/* Dynamic reloc, imported PLT */
DECL|macro|R_PARISC_EPLT
mdefine_line|#define R_PARISC_EPLT&t;&t;130&t;/* Dynamic reloc, exported PLT */
DECL|macro|R_PARISC_TPREL32
mdefine_line|#define R_PARISC_TPREL32&t;153&t;/* 32 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL21L
mdefine_line|#define R_PARISC_TPREL21L&t;154&t;/* TP-rel. address, left 21 bits.  */
DECL|macro|R_PARISC_TPREL14R
mdefine_line|#define R_PARISC_TPREL14R&t;158&t;/* TP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF_TP21L
mdefine_line|#define R_PARISC_LTOFF_TP21L&t;162&t;/* LT-TP-rel. address, left 21 bits. */
DECL|macro|R_PARISC_LTOFF_TP14R
mdefine_line|#define R_PARISC_LTOFF_TP14R&t;166&t;/* LT-TP-rel. address, right 14 bits.*/
DECL|macro|R_PARISC_LTOFF_TP14F
mdefine_line|#define R_PARISC_LTOFF_TP14F&t;167&t;/* 14 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_TPREL64
mdefine_line|#define R_PARISC_TPREL64&t;216&t;/* 64 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL14WR
mdefine_line|#define R_PARISC_TPREL14WR&t;219&t;/* TP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_TPREL14DR
mdefine_line|#define R_PARISC_TPREL14DR&t;220&t;/* TP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_TPREL16F
mdefine_line|#define R_PARISC_TPREL16F&t;221&t;/* 16 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL16WF
mdefine_line|#define R_PARISC_TPREL16WF&t;222&t;/* 16 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL16DF
mdefine_line|#define R_PARISC_TPREL16DF&t;223&t;/* 16 bits TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP64
mdefine_line|#define R_PARISC_LTOFF_TP64&t;224&t;/* 64 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP14WR
mdefine_line|#define R_PARISC_LTOFF_TP14WR&t;227&t;/* LT-TP-rel. address, right 14 bits.*/
DECL|macro|R_PARISC_LTOFF_TP14DR
mdefine_line|#define R_PARISC_LTOFF_TP14DR&t;228&t;/* LT-TP-rel. address, right 14 bits.*/
DECL|macro|R_PARISC_LTOFF_TP16F
mdefine_line|#define R_PARISC_LTOFF_TP16F&t;229&t;/* 16 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP16WF
mdefine_line|#define R_PARISC_LTOFF_TP16WF&t;230&t;/* 16 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP16DF
mdefine_line|#define R_PARISC_LTOFF_TP16DF&t;231&t;/* 16 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_HIRESERVE
mdefine_line|#define R_PARISC_HIRESERVE&t;255
multiline_comment|/* Legal values for p_type field of Elf32_Phdr/Elf64_Phdr.  */
DECL|macro|PT_HP_TLS
mdefine_line|#define PT_HP_TLS&t;&t;(PT_LOOS + 0x0)
DECL|macro|PT_HP_CORE_NONE
mdefine_line|#define PT_HP_CORE_NONE&t;&t;(PT_LOOS + 0x1)
DECL|macro|PT_HP_CORE_VERSION
mdefine_line|#define PT_HP_CORE_VERSION&t;(PT_LOOS + 0x2)
DECL|macro|PT_HP_CORE_KERNEL
mdefine_line|#define PT_HP_CORE_KERNEL&t;(PT_LOOS + 0x3)
DECL|macro|PT_HP_CORE_COMM
mdefine_line|#define PT_HP_CORE_COMM&t;&t;(PT_LOOS + 0x4)
DECL|macro|PT_HP_CORE_PROC
mdefine_line|#define PT_HP_CORE_PROC&t;&t;(PT_LOOS + 0x5)
DECL|macro|PT_HP_CORE_LOADABLE
mdefine_line|#define PT_HP_CORE_LOADABLE&t;(PT_LOOS + 0x6)
DECL|macro|PT_HP_CORE_STACK
mdefine_line|#define PT_HP_CORE_STACK&t;(PT_LOOS + 0x7)
DECL|macro|PT_HP_CORE_SHM
mdefine_line|#define PT_HP_CORE_SHM&t;&t;(PT_LOOS + 0x8)
DECL|macro|PT_HP_CORE_MMF
mdefine_line|#define PT_HP_CORE_MMF&t;&t;(PT_LOOS + 0x9)
DECL|macro|PT_HP_PARALLEL
mdefine_line|#define PT_HP_PARALLEL&t;&t;(PT_LOOS + 0x10)
DECL|macro|PT_HP_FASTBIND
mdefine_line|#define PT_HP_FASTBIND&t;&t;(PT_LOOS + 0x11)
DECL|macro|PT_HP_OPT_ANNOT
mdefine_line|#define PT_HP_OPT_ANNOT&t;&t;(PT_LOOS + 0x12)
DECL|macro|PT_HP_HSL_ANNOT
mdefine_line|#define PT_HP_HSL_ANNOT&t;&t;(PT_LOOS + 0x13)
DECL|macro|PT_HP_STACK
mdefine_line|#define PT_HP_STACK&t;&t;(PT_LOOS + 0x14)
DECL|macro|PT_PARISC_ARCHEXT
mdefine_line|#define PT_PARISC_ARCHEXT&t;0x70000000
DECL|macro|PT_PARISC_UNWIND
mdefine_line|#define PT_PARISC_UNWIND&t;0x70000001
multiline_comment|/* Legal values for p_flags field of Elf32_Phdr/Elf64_Phdr.  */
DECL|macro|PF_PARISC_SBP
mdefine_line|#define PF_PARISC_SBP&t;&t;0x08000000
DECL|macro|PF_HP_PAGE_SIZE
mdefine_line|#define PF_HP_PAGE_SIZE&t;&t;0x00100000
DECL|macro|PF_HP_FAR_SHARED
mdefine_line|#define PF_HP_FAR_SHARED&t;0x00200000
DECL|macro|PF_HP_NEAR_SHARED
mdefine_line|#define PF_HP_NEAR_SHARED&t;0x00400000
DECL|macro|PF_HP_CODE
mdefine_line|#define PF_HP_CODE&t;&t;0x01000000
DECL|macro|PF_HP_MODIFY
mdefine_line|#define PF_HP_MODIFY&t;&t;0x02000000
DECL|macro|PF_HP_LAZYSWAP
mdefine_line|#define PF_HP_LAZYSWAP&t;&t;0x04000000
DECL|macro|PF_HP_SBP
mdefine_line|#define PF_HP_SBP&t;&t;0x08000000
DECL|struct|elf32_rel
r_typedef
r_struct
id|elf32_rel
(brace
DECL|member|r_offset
id|Elf32_Addr
id|r_offset
suffix:semicolon
DECL|member|r_info
id|Elf32_Word
id|r_info
suffix:semicolon
DECL|typedef|Elf32_Rel
)brace
id|Elf32_Rel
suffix:semicolon
DECL|struct|elf64_rel
r_typedef
r_struct
id|elf64_rel
(brace
DECL|member|r_offset
id|Elf64_Addr
id|r_offset
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
id|Elf64_Xword
id|r_info
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|typedef|Elf64_Rel
)brace
id|Elf64_Rel
suffix:semicolon
DECL|struct|elf32_rela
r_typedef
r_struct
id|elf32_rela
(brace
DECL|member|r_offset
id|Elf32_Addr
id|r_offset
suffix:semicolon
DECL|member|r_info
id|Elf32_Word
id|r_info
suffix:semicolon
DECL|member|r_addend
id|Elf32_Sword
id|r_addend
suffix:semicolon
DECL|typedef|Elf32_Rela
)brace
id|Elf32_Rela
suffix:semicolon
DECL|struct|elf64_rela
r_typedef
r_struct
id|elf64_rela
(brace
DECL|member|r_offset
id|Elf64_Addr
id|r_offset
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
id|Elf64_Xword
id|r_info
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|member|r_addend
id|Elf64_Sxword
id|r_addend
suffix:semicolon
multiline_comment|/* Constant addend used to compute value */
DECL|typedef|Elf64_Rela
)brace
id|Elf64_Rela
suffix:semicolon
DECL|struct|elf32_sym
r_typedef
r_struct
id|elf32_sym
(brace
DECL|member|st_name
id|Elf32_Word
id|st_name
suffix:semicolon
DECL|member|st_value
id|Elf32_Addr
id|st_value
suffix:semicolon
DECL|member|st_size
id|Elf32_Word
id|st_size
suffix:semicolon
DECL|member|st_info
r_int
r_char
id|st_info
suffix:semicolon
DECL|member|st_other
r_int
r_char
id|st_other
suffix:semicolon
DECL|member|st_shndx
id|Elf32_Half
id|st_shndx
suffix:semicolon
DECL|typedef|Elf32_Sym
)brace
id|Elf32_Sym
suffix:semicolon
DECL|struct|elf64_sym
r_typedef
r_struct
id|elf64_sym
(brace
DECL|member|st_name
id|Elf64_Word
id|st_name
suffix:semicolon
multiline_comment|/* Symbol name, index in string tbl */
DECL|member|st_info
r_int
r_char
id|st_info
suffix:semicolon
multiline_comment|/* Type and binding attributes */
DECL|member|st_other
r_int
r_char
id|st_other
suffix:semicolon
multiline_comment|/* No defined meaning, 0 */
DECL|member|st_shndx
id|Elf64_Half
id|st_shndx
suffix:semicolon
multiline_comment|/* Associated section index */
DECL|member|st_value
id|Elf64_Addr
id|st_value
suffix:semicolon
multiline_comment|/* Value of the symbol */
DECL|member|st_size
id|Elf64_Xword
id|st_size
suffix:semicolon
multiline_comment|/* Associated symbol size */
DECL|typedef|Elf64_Sym
)brace
id|Elf64_Sym
suffix:semicolon
DECL|macro|EI_NIDENT
mdefine_line|#define EI_NIDENT&t;16
DECL|struct|elf32_hdr
r_typedef
r_struct
id|elf32_hdr
(brace
DECL|member|e_ident
r_int
r_char
id|e_ident
(braket
id|EI_NIDENT
)braket
suffix:semicolon
DECL|member|e_type
id|Elf32_Half
id|e_type
suffix:semicolon
DECL|member|e_machine
id|Elf32_Half
id|e_machine
suffix:semicolon
DECL|member|e_version
id|Elf32_Word
id|e_version
suffix:semicolon
DECL|member|e_entry
id|Elf32_Addr
id|e_entry
suffix:semicolon
multiline_comment|/* Entry point */
DECL|member|e_phoff
id|Elf32_Off
id|e_phoff
suffix:semicolon
DECL|member|e_shoff
id|Elf32_Off
id|e_shoff
suffix:semicolon
DECL|member|e_flags
id|Elf32_Word
id|e_flags
suffix:semicolon
DECL|member|e_ehsize
id|Elf32_Half
id|e_ehsize
suffix:semicolon
DECL|member|e_phentsize
id|Elf32_Half
id|e_phentsize
suffix:semicolon
DECL|member|e_phnum
id|Elf32_Half
id|e_phnum
suffix:semicolon
DECL|member|e_shentsize
id|Elf32_Half
id|e_shentsize
suffix:semicolon
DECL|member|e_shnum
id|Elf32_Half
id|e_shnum
suffix:semicolon
DECL|member|e_shstrndx
id|Elf32_Half
id|e_shstrndx
suffix:semicolon
DECL|typedef|Elf32_Ehdr
)brace
id|Elf32_Ehdr
suffix:semicolon
DECL|struct|elf64_hdr
r_typedef
r_struct
id|elf64_hdr
(brace
DECL|member|e_ident
r_int
r_char
id|e_ident
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* ELF &quot;magic number&quot; */
DECL|member|e_type
id|Elf64_Half
id|e_type
suffix:semicolon
DECL|member|e_machine
id|Elf64_Half
id|e_machine
suffix:semicolon
DECL|member|e_version
id|Elf64_Word
id|e_version
suffix:semicolon
DECL|member|e_entry
id|Elf64_Addr
id|e_entry
suffix:semicolon
multiline_comment|/* Entry point virtual address */
DECL|member|e_phoff
id|Elf64_Off
id|e_phoff
suffix:semicolon
multiline_comment|/* Program header table file offset */
DECL|member|e_shoff
id|Elf64_Off
id|e_shoff
suffix:semicolon
multiline_comment|/* Section header table file offset */
DECL|member|e_flags
id|Elf64_Word
id|e_flags
suffix:semicolon
DECL|member|e_ehsize
id|Elf64_Half
id|e_ehsize
suffix:semicolon
DECL|member|e_phentsize
id|Elf64_Half
id|e_phentsize
suffix:semicolon
DECL|member|e_phnum
id|Elf64_Half
id|e_phnum
suffix:semicolon
DECL|member|e_shentsize
id|Elf64_Half
id|e_shentsize
suffix:semicolon
DECL|member|e_shnum
id|Elf64_Half
id|e_shnum
suffix:semicolon
DECL|member|e_shstrndx
id|Elf64_Half
id|e_shstrndx
suffix:semicolon
DECL|typedef|Elf64_Ehdr
)brace
id|Elf64_Ehdr
suffix:semicolon
multiline_comment|/* These constants define the permissions on sections in the program&n;   header, p_flags. */
DECL|macro|PF_R
mdefine_line|#define PF_R&t;&t;0x4
DECL|macro|PF_W
mdefine_line|#define PF_W&t;&t;0x2
DECL|macro|PF_X
mdefine_line|#define PF_X&t;&t;0x1
DECL|struct|elf32_phdr
r_typedef
r_struct
id|elf32_phdr
(brace
DECL|member|p_type
id|Elf32_Word
id|p_type
suffix:semicolon
DECL|member|p_offset
id|Elf32_Off
id|p_offset
suffix:semicolon
DECL|member|p_vaddr
id|Elf32_Addr
id|p_vaddr
suffix:semicolon
DECL|member|p_paddr
id|Elf32_Addr
id|p_paddr
suffix:semicolon
DECL|member|p_filesz
id|Elf32_Word
id|p_filesz
suffix:semicolon
DECL|member|p_memsz
id|Elf32_Word
id|p_memsz
suffix:semicolon
DECL|member|p_flags
id|Elf32_Word
id|p_flags
suffix:semicolon
DECL|member|p_align
id|Elf32_Word
id|p_align
suffix:semicolon
DECL|typedef|Elf32_Phdr
)brace
id|Elf32_Phdr
suffix:semicolon
DECL|struct|elf64_phdr
r_typedef
r_struct
id|elf64_phdr
(brace
DECL|member|p_type
id|Elf64_Word
id|p_type
suffix:semicolon
DECL|member|p_flags
id|Elf64_Word
id|p_flags
suffix:semicolon
DECL|member|p_offset
id|Elf64_Off
id|p_offset
suffix:semicolon
multiline_comment|/* Segment file offset */
DECL|member|p_vaddr
id|Elf64_Addr
id|p_vaddr
suffix:semicolon
multiline_comment|/* Segment virtual address */
DECL|member|p_paddr
id|Elf64_Addr
id|p_paddr
suffix:semicolon
multiline_comment|/* Segment physical address */
DECL|member|p_filesz
id|Elf64_Xword
id|p_filesz
suffix:semicolon
multiline_comment|/* Segment size in file */
DECL|member|p_memsz
id|Elf64_Xword
id|p_memsz
suffix:semicolon
multiline_comment|/* Segment size in memory */
DECL|member|p_align
id|Elf64_Xword
id|p_align
suffix:semicolon
multiline_comment|/* Segment alignment, file &amp; memory */
DECL|typedef|Elf64_Phdr
)brace
id|Elf64_Phdr
suffix:semicolon
multiline_comment|/* sh_type */
DECL|macro|SHT_NULL
mdefine_line|#define SHT_NULL&t;0
DECL|macro|SHT_PROGBITS
mdefine_line|#define SHT_PROGBITS&t;1
DECL|macro|SHT_SYMTAB
mdefine_line|#define SHT_SYMTAB&t;2
DECL|macro|SHT_STRTAB
mdefine_line|#define SHT_STRTAB&t;3
DECL|macro|SHT_RELA
mdefine_line|#define SHT_RELA&t;4
DECL|macro|SHT_HASH
mdefine_line|#define SHT_HASH&t;5
DECL|macro|SHT_DYNAMIC
mdefine_line|#define SHT_DYNAMIC&t;6
DECL|macro|SHT_NOTE
mdefine_line|#define SHT_NOTE&t;7
DECL|macro|SHT_NOBITS
mdefine_line|#define SHT_NOBITS&t;8
DECL|macro|SHT_REL
mdefine_line|#define SHT_REL&t;&t;9
DECL|macro|SHT_SHLIB
mdefine_line|#define SHT_SHLIB&t;10
DECL|macro|SHT_DYNSYM
mdefine_line|#define SHT_DYNSYM&t;11
DECL|macro|SHT_NUM
mdefine_line|#define SHT_NUM&t;&t;12
DECL|macro|SHT_LOPROC
mdefine_line|#define SHT_LOPROC&t;0x70000000
DECL|macro|SHT_HIPROC
mdefine_line|#define SHT_HIPROC&t;0x7fffffff
DECL|macro|SHT_LOUSER
mdefine_line|#define SHT_LOUSER&t;0x80000000
DECL|macro|SHT_HIUSER
mdefine_line|#define SHT_HIUSER&t;0xffffffff
DECL|macro|SHT_MIPS_LIST
mdefine_line|#define SHT_MIPS_LIST&t;&t;0x70000000
DECL|macro|SHT_MIPS_CONFLICT
mdefine_line|#define SHT_MIPS_CONFLICT&t;0x70000002
DECL|macro|SHT_MIPS_GPTAB
mdefine_line|#define SHT_MIPS_GPTAB&t;&t;0x70000003
DECL|macro|SHT_MIPS_UCODE
mdefine_line|#define SHT_MIPS_UCODE&t;&t;0x70000004
multiline_comment|/* sh_flags */
DECL|macro|SHF_WRITE
mdefine_line|#define SHF_WRITE&t;0x1
DECL|macro|SHF_ALLOC
mdefine_line|#define SHF_ALLOC&t;0x2
DECL|macro|SHF_EXECINSTR
mdefine_line|#define SHF_EXECINSTR&t;0x4
DECL|macro|SHF_MASKPROC
mdefine_line|#define SHF_MASKPROC&t;0xf0000000
DECL|macro|SHF_MIPS_GPREL
mdefine_line|#define SHF_MIPS_GPREL&t;0x10000000
multiline_comment|/* special section indexes */
DECL|macro|SHN_UNDEF
mdefine_line|#define SHN_UNDEF&t;0
DECL|macro|SHN_LORESERVE
mdefine_line|#define SHN_LORESERVE&t;0xff00
DECL|macro|SHN_LOPROC
mdefine_line|#define SHN_LOPROC&t;0xff00
DECL|macro|SHN_HIPROC
mdefine_line|#define SHN_HIPROC&t;0xff1f
DECL|macro|SHN_ABS
mdefine_line|#define SHN_ABS&t;&t;0xfff1
DECL|macro|SHN_COMMON
mdefine_line|#define SHN_COMMON&t;0xfff2
DECL|macro|SHN_HIRESERVE
mdefine_line|#define SHN_HIRESERVE&t;0xffff
DECL|macro|SHN_MIPS_ACCOMON
mdefine_line|#define SHN_MIPS_ACCOMON&t;0xff00
r_typedef
r_struct
(brace
DECL|member|sh_name
id|Elf32_Word
id|sh_name
suffix:semicolon
DECL|member|sh_type
id|Elf32_Word
id|sh_type
suffix:semicolon
DECL|member|sh_flags
id|Elf32_Word
id|sh_flags
suffix:semicolon
DECL|member|sh_addr
id|Elf32_Addr
id|sh_addr
suffix:semicolon
DECL|member|sh_offset
id|Elf32_Off
id|sh_offset
suffix:semicolon
DECL|member|sh_size
id|Elf32_Word
id|sh_size
suffix:semicolon
DECL|member|sh_link
id|Elf32_Word
id|sh_link
suffix:semicolon
DECL|member|sh_info
id|Elf32_Word
id|sh_info
suffix:semicolon
DECL|member|sh_addralign
id|Elf32_Word
id|sh_addralign
suffix:semicolon
DECL|member|sh_entsize
id|Elf32_Word
id|sh_entsize
suffix:semicolon
DECL|typedef|Elf32_Shdr
)brace
id|Elf32_Shdr
suffix:semicolon
DECL|struct|elf64_shdr
r_typedef
r_struct
id|elf64_shdr
(brace
DECL|member|sh_name
id|Elf64_Word
id|sh_name
suffix:semicolon
multiline_comment|/* Section name, index in string tbl */
DECL|member|sh_type
id|Elf64_Word
id|sh_type
suffix:semicolon
multiline_comment|/* Type of section */
DECL|member|sh_flags
id|Elf64_Xword
id|sh_flags
suffix:semicolon
multiline_comment|/* Miscellaneous section attributes */
DECL|member|sh_addr
id|Elf64_Addr
id|sh_addr
suffix:semicolon
multiline_comment|/* Section virtual addr at execution */
DECL|member|sh_offset
id|Elf64_Off
id|sh_offset
suffix:semicolon
multiline_comment|/* Section file offset */
DECL|member|sh_size
id|Elf64_Xword
id|sh_size
suffix:semicolon
multiline_comment|/* Size of section in bytes */
DECL|member|sh_link
id|Elf64_Word
id|sh_link
suffix:semicolon
multiline_comment|/* Index of another section */
DECL|member|sh_info
id|Elf64_Word
id|sh_info
suffix:semicolon
multiline_comment|/* Additional section information */
DECL|member|sh_addralign
id|Elf64_Xword
id|sh_addralign
suffix:semicolon
multiline_comment|/* Section alignment */
DECL|member|sh_entsize
id|Elf64_Xword
id|sh_entsize
suffix:semicolon
multiline_comment|/* Entry size if section holds table */
DECL|typedef|Elf64_Shdr
)brace
id|Elf64_Shdr
suffix:semicolon
DECL|macro|EI_MAG0
mdefine_line|#define&t;EI_MAG0&t;&t;0&t;&t;/* e_ident[] indexes */
DECL|macro|EI_MAG1
mdefine_line|#define&t;EI_MAG1&t;&t;1
DECL|macro|EI_MAG2
mdefine_line|#define&t;EI_MAG2&t;&t;2
DECL|macro|EI_MAG3
mdefine_line|#define&t;EI_MAG3&t;&t;3
DECL|macro|EI_CLASS
mdefine_line|#define&t;EI_CLASS&t;4
DECL|macro|EI_DATA
mdefine_line|#define&t;EI_DATA&t;&t;5
DECL|macro|EI_VERSION
mdefine_line|#define&t;EI_VERSION&t;6
DECL|macro|EI_PAD
mdefine_line|#define&t;EI_PAD&t;&t;7
DECL|macro|ELFMAG0
mdefine_line|#define&t;ELFMAG0&t;&t;0x7f&t;&t;/* EI_MAG */
DECL|macro|ELFMAG1
mdefine_line|#define&t;ELFMAG1&t;&t;&squot;E&squot;
DECL|macro|ELFMAG2
mdefine_line|#define&t;ELFMAG2&t;&t;&squot;L&squot;
DECL|macro|ELFMAG3
mdefine_line|#define&t;ELFMAG3&t;&t;&squot;F&squot;
DECL|macro|ELFMAG
mdefine_line|#define&t;ELFMAG&t;&t;&quot;&bslash;177ELF&quot;
DECL|macro|SELFMAG
mdefine_line|#define&t;SELFMAG&t;&t;4
DECL|macro|ELFCLASSNONE
mdefine_line|#define&t;ELFCLASSNONE&t;0&t;&t;/* EI_CLASS */
DECL|macro|ELFCLASS32
mdefine_line|#define&t;ELFCLASS32&t;1
DECL|macro|ELFCLASS64
mdefine_line|#define&t;ELFCLASS64&t;2
DECL|macro|ELFCLASSNUM
mdefine_line|#define&t;ELFCLASSNUM&t;3
DECL|macro|ELFDATANONE
mdefine_line|#define ELFDATANONE&t;0&t;&t;/* e_ident[EI_DATA] */
DECL|macro|ELFDATA2LSB
mdefine_line|#define ELFDATA2LSB&t;1
DECL|macro|ELFDATA2MSB
mdefine_line|#define ELFDATA2MSB&t;2
DECL|macro|EV_NONE
mdefine_line|#define EV_NONE&t;&t;0&t;&t;/* e_version, EI_VERSION */
DECL|macro|EV_CURRENT
mdefine_line|#define EV_CURRENT&t;1
DECL|macro|EV_NUM
mdefine_line|#define EV_NUM&t;&t;2
multiline_comment|/* Notes used in ET_CORE */
DECL|macro|NT_PRSTATUS
mdefine_line|#define NT_PRSTATUS&t;1
DECL|macro|NT_PRFPREG
mdefine_line|#define NT_PRFPREG&t;2
DECL|macro|NT_PRPSINFO
mdefine_line|#define NT_PRPSINFO&t;3
DECL|macro|NT_TASKSTRUCT
mdefine_line|#define NT_TASKSTRUCT&t;4
DECL|macro|NT_PRXFPREG
mdefine_line|#define NT_PRXFPREG     0x46e62b7f      /* copied from gdb5.1/include/elf/common.h */
multiline_comment|/* Note header in a PT_NOTE section */
DECL|struct|elf32_note
r_typedef
r_struct
id|elf32_note
(brace
DECL|member|n_namesz
id|Elf32_Word
id|n_namesz
suffix:semicolon
multiline_comment|/* Name size */
DECL|member|n_descsz
id|Elf32_Word
id|n_descsz
suffix:semicolon
multiline_comment|/* Content size */
DECL|member|n_type
id|Elf32_Word
id|n_type
suffix:semicolon
multiline_comment|/* Content type */
DECL|typedef|Elf32_Nhdr
)brace
id|Elf32_Nhdr
suffix:semicolon
multiline_comment|/* Note header in a PT_NOTE section */
DECL|struct|elf64_note
r_typedef
r_struct
id|elf64_note
(brace
DECL|member|n_namesz
id|Elf64_Word
id|n_namesz
suffix:semicolon
multiline_comment|/* Name size */
DECL|member|n_descsz
id|Elf64_Word
id|n_descsz
suffix:semicolon
multiline_comment|/* Content size */
DECL|member|n_type
id|Elf64_Word
id|n_type
suffix:semicolon
multiline_comment|/* Content type */
DECL|typedef|Elf64_Nhdr
)brace
id|Elf64_Nhdr
suffix:semicolon
macro_line|#if ELF_CLASS == ELFCLASS32
r_extern
id|Elf32_Dyn
id|_DYNAMIC
(braket
)braket
suffix:semicolon
DECL|macro|elfhdr
mdefine_line|#define elfhdr&t;&t;elf32_hdr
DECL|macro|elf_phdr
mdefine_line|#define elf_phdr&t;elf32_phdr
DECL|macro|elf_note
mdefine_line|#define elf_note&t;elf32_note
macro_line|#else
r_extern
id|Elf64_Dyn
id|_DYNAMIC
(braket
)braket
suffix:semicolon
DECL|macro|elfhdr
mdefine_line|#define elfhdr&t;&t;elf64_hdr
DECL|macro|elf_phdr
mdefine_line|#define elf_phdr&t;elf64_phdr
DECL|macro|elf_note
mdefine_line|#define elf_note&t;elf64_note
macro_line|#endif
macro_line|#endif /* _LINUX_ELF_H */
eof
