macro_line|#ifndef _ASM_PPC64_MODULE_H
DECL|macro|_ASM_PPC64_MODULE_H
mdefine_line|#define _ASM_PPC64_MODULE_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
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
multiline_comment|/* List of BUG addresses, source line numbers and filenames */
DECL|member|bug_list
r_struct
id|list_head
id|bug_list
suffix:semicolon
DECL|member|bug_table
r_struct
id|bug_entry
op_star
id|bug_table
suffix:semicolon
DECL|member|num_bugs
r_int
r_int
id|num_bugs
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|bug_entry
op_star
id|module_find_bug
c_func
(paren
r_int
r_int
id|bugaddr
)paren
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
r_struct
id|exception_table_entry
suffix:semicolon
r_void
id|sort_ex_table
c_func
(paren
r_struct
id|exception_table_entry
op_star
id|start
comma
r_struct
id|exception_table_entry
op_star
id|finish
)paren
suffix:semicolon
macro_line|#endif /* _ASM_PPC64_MODULE_H */
eof
