macro_line|#ifndef _ASM_PPC64_MODULE_H
DECL|macro|_ASM_PPC64_MODULE_H
mdefine_line|#define _ASM_PPC64_MODULE_H
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/* Index of stubs section within module. */
DECL|member|stubs_section
r_int
r_int
id|stubs_section
suffix:semicolon
multiline_comment|/* What section is the TOC? */
DECL|member|toc_section
r_int
r_int
id|toc_section
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf64_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf64_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf64_Ehdr
multiline_comment|/* Make empty section for module_frob_arch_sections to expand. */
macro_line|#ifdef MODULE
id|asm
c_func
(paren
l_string|&quot;.section .stubs,&bslash;&quot;ax&bslash;&quot;,@nobits; .align 3; .previous&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_PPC64_MODULE_H */
eof
