macro_line|#ifndef _ASM_MODULE_H
DECL|macro|_ASM_MODULE_H
mdefine_line|#define _ASM_MODULE_H
macro_line|#include &lt;linux/config.h&gt;
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
DECL|typedef|Elf64_Byte
r_typedef
r_uint8
id|Elf64_Byte
suffix:semicolon
multiline_comment|/* Type for a 8-bit quantity.  */
r_typedef
r_struct
(brace
DECL|member|r_offset
id|Elf64_Addr
id|r_offset
suffix:semicolon
multiline_comment|/* Address of relocation.  */
DECL|member|r_sym
id|Elf64_Word
id|r_sym
suffix:semicolon
multiline_comment|/* Symbol index.  */
DECL|member|r_ssym
id|Elf64_Byte
id|r_ssym
suffix:semicolon
multiline_comment|/* Special symbol.  */
DECL|member|r_type3
id|Elf64_Byte
id|r_type3
suffix:semicolon
multiline_comment|/* Third relocation.  */
DECL|member|r_type2
id|Elf64_Byte
id|r_type2
suffix:semicolon
multiline_comment|/* Second relocation.  */
DECL|member|r_type
id|Elf64_Byte
id|r_type
suffix:semicolon
multiline_comment|/* First relocation.  */
DECL|member|r_addend
id|Elf64_Sxword
id|r_addend
suffix:semicolon
multiline_comment|/* Addend.  */
DECL|typedef|Elf64_Mips_Rela
)brace
id|Elf64_Mips_Rela
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr&t;Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym&t;&t;Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr&t;Elf32_Ehdr
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr&t;Elf64_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym&t;&t;Elf64_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr&t;Elf64_Ehdr
macro_line|#endif
macro_line|#endif /* _ASM_MODULE_H */
eof
