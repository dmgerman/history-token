multiline_comment|/*&n; * include/asm-v850/module.h -- Architecture-specific module hooks&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 2001  Rusty Russell&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * Derived in part from include/asm-ppc/module.h&n; */
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
multiline_comment|/* How much of the core is actually taken up with core (then&n;           we know the rest is for the PLT).  */
DECL|member|core_plt_offset
r_int
r_int
id|core_plt_offset
suffix:semicolon
multiline_comment|/* Same for init.  */
DECL|member|init_plt_offset
r_int
r_int
id|init_plt_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr
macro_line|#endif /* __V850_MODULE_H__ */
eof
