macro_line|#ifndef _ALPHA_MODULE_H
DECL|macro|_ALPHA_MODULE_H
mdefine_line|#define _ALPHA_MODULE_H
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
DECL|member|gotsecindex
r_int
r_int
id|gotsecindex
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf64_Sym
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf64_Shdr
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf64_Ehdr
DECL|macro|Elf_Phdr
mdefine_line|#define Elf_Phdr Elf64_Phdr
DECL|macro|Elf_Dyn
mdefine_line|#define Elf_Dyn Elf64_Dyn
DECL|macro|Elf_Rel
mdefine_line|#define Elf_Rel Elf64_Rel
DECL|macro|Elf_Rela
mdefine_line|#define Elf_Rela Elf64_Rela
DECL|macro|ARCH_SHF_SMALL
mdefine_line|#define ARCH_SHF_SMALL SHF_ALPHA_GPREL
macro_line|#ifdef MODULE
id|asm
c_func
(paren
l_string|&quot;.section .got,&bslash;&quot;aws&bslash;&quot;,@nobits; .align 3; .previous&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /*_ALPHA_MODULE_H*/
eof
