macro_line|#ifndef _ASM_PPC_MODULE_H
DECL|macro|_ASM_PPC_MODULE_H
mdefine_line|#define _ASM_PPC_MODULE_H
multiline_comment|/* Module stuff for PPC.  (C) 2001 Rusty Russell */
multiline_comment|/* Thanks to Paul M for explaining this.&n;&n;   PPC can only do rel jumps += 32MB, and often the kernel and other&n;   modules are furthur away than this.  So, we jump to a table of&n;   trampolines attached to the module (the Procedure Linkage Table)&n;   whenever that happens.&n;*/
DECL|struct|ppc_plt_entry
r_struct
id|ppc_plt_entry
(brace
multiline_comment|/* 16 byte jump instruction sequence (4 instructions) */
DECL|member|jump
r_int
r_int
id|jump
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/* Indices of PLT sections within module. */
DECL|member|core_plt_section
DECL|member|init_plt_section
r_int
r_int
id|core_plt_section
comma
id|init_plt_section
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr
multiline_comment|/* Make empty sections for module_frob_arch_sections to expand. */
macro_line|#ifdef MODULE
id|asm
c_func
(paren
l_string|&quot;.section .plt,&bslash;&quot;aws&bslash;&quot;,@nobits; .align 3; .previous&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.section .plt.init,&bslash;&quot;aws&bslash;&quot;,@nobits; .align 3; .previous&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_PPC_MODULE_H */
eof
