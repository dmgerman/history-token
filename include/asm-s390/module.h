macro_line|#ifndef _ASM_S390_MODULE_H
DECL|macro|_ASM_S390_MODULE_H
mdefine_line|#define _ASM_S390_MODULE_H
multiline_comment|/*&n; * This file contains the s390 architecture specific module code.&n; */
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
DECL|member|module_got
DECL|member|module_plt
r_void
op_star
id|module_got
comma
op_star
id|module_plt
suffix:semicolon
DECL|member|got_size
DECL|member|plt_size
r_int
r_int
id|got_size
comma
id|plt_size
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
mdefine_line|#define ELFW(x) ELF32_ ## x
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
