multiline_comment|/*&n; * include/asm-v850/module.h -- Architecture-specific module hooks&n; *&n; *  Copyright (C) 2001,02,03  NEC Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 2001,03  Rusty Russell&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * Derived in part from include/asm-ppc/module.h&n; */
macro_line|#ifndef __V850_MODULE_H__
DECL|macro|__V850_MODULE_H__
mdefine_line|#define __V850_MODULE_H__
DECL|macro|MODULE_SYMBOL_PREFIX
mdefine_line|#define MODULE_SYMBOL_PREFIX &quot;_&quot;
DECL|struct|v850_plt_entry
r_struct
id|v850_plt_entry
(brace
multiline_comment|/* Indirect jump instruction sequence (6-byte mov + 2-byte jr).  */
DECL|member|tramp
r_int
r_int
id|tramp
(braket
l_int|2
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
l_string|&quot;.section .plt,&bslash;&quot;ax&bslash;&quot;,@nobits; .align 3; .previous&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.section .init.plt,&bslash;&quot;ax&bslash;&quot;,@nobits; .align 3; .previous&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* We don&squot;t do exception tables.  */
r_struct
id|exception_table_entry
suffix:semicolon
r_static
r_inline
r_const
r_struct
id|exception_table_entry
op_star
DECL|function|search_extable
id|search_extable
c_func
(paren
r_const
r_struct
id|exception_table_entry
op_star
id|first
comma
r_const
r_struct
id|exception_table_entry
op_star
id|last
comma
r_int
r_int
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __V850_MODULE_H__ */
eof
