macro_line|#ifndef _ASM_S390_MODULE_H
DECL|macro|_ASM_S390_MODULE_H
mdefine_line|#define _ASM_S390_MODULE_H
multiline_comment|/*&n; * This file contains the s390 architecture specific module code.&n; */
DECL|struct|mod_arch_syminfo
r_struct
id|mod_arch_syminfo
(brace
DECL|member|got_offset
r_int
r_int
id|got_offset
suffix:semicolon
DECL|member|plt_offset
r_int
r_int
id|plt_offset
suffix:semicolon
DECL|member|got_initialized
r_int
id|got_initialized
suffix:semicolon
DECL|member|plt_initialized
r_int
id|plt_initialized
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/* Starting offset of got in the module core memory. */
DECL|member|got_offset
r_int
r_int
id|got_offset
suffix:semicolon
multiline_comment|/* Starting offset of plt in the module core memory. */
DECL|member|plt_offset
r_int
r_int
id|plt_offset
suffix:semicolon
multiline_comment|/* Size of the got. */
DECL|member|got_size
r_int
r_int
id|got_size
suffix:semicolon
multiline_comment|/* Size of the plt. */
DECL|member|plt_size
r_int
r_int
id|plt_size
suffix:semicolon
multiline_comment|/* Number of symbols in syminfo. */
DECL|member|nsyms
r_int
id|nsyms
suffix:semicolon
multiline_comment|/* Additional symbol information (got and plt offsets). */
DECL|member|syminfo
r_struct
id|mod_arch_syminfo
op_star
id|syminfo
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_S390X
DECL|macro|ElfW
mdefine_line|#define ElfW(x) Elf64_ ## x
DECL|macro|ELFW
mdefine_line|#define ELFW(x) ELF64_ ## x
macro_line|#else
DECL|macro|ElfW
mdefine_line|#define ElfW(x) Elf32_ ## x
DECL|macro|ELFW
mdefine_line|#define ELFW(x) ELF64_ ## x
macro_line|#endif
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr ElfW(Shdr)
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym ElfW(Sym)
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr ElfW(Ehdr)
DECL|macro|ELF_R_TYPE
mdefine_line|#define ELF_R_TYPE ELFW(R_TYPE)
macro_line|#endif /* _ASM_S390_MODULE_H */
eof
