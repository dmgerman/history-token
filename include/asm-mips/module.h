macro_line|#ifndef _ASM_MODULE_H
DECL|macro|_ASM_MODULE_H
mdefine_line|#define _ASM_MODULE_H
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/* Data Bus Error exception tables */
DECL|member|dbe_table_start
r_const
r_struct
id|exception_table_entry
op_star
id|dbe_table_start
suffix:semicolon
DECL|member|dbe_table_end
r_const
r_struct
id|exception_table_entry
op_star
id|dbe_table_end
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr
macro_line|#endif /* _ASM_MODULE_H */
eof
