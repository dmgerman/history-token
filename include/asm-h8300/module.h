macro_line|#ifndef _ASM_H8300_MODULE_H
DECL|macro|_ASM_H8300_MODULE_H
mdefine_line|#define _ASM_H8300_MODULE_H
multiline_comment|/*&n; * This file contains the H8/300 architecture specific module code.&n; */
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr
DECL|macro|MODULE_SYMBOL_PREFIX
mdefine_line|#define MODULE_SYMBOL_PREFIX &quot;_&quot;
macro_line|#endif /* _ASM_H8/300_MODULE_H */
eof
