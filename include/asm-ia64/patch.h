macro_line|#ifndef _ASM_IA64_PATCH_H
DECL|macro|_ASM_IA64_PATCH_H
mdefine_line|#define _ASM_IA64_PATCH_H
multiline_comment|/*&n; * Copyright (C) 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * There are a number of reasons for patching instructions.  Rather than duplicating code&n; * all over the place, we put the common stuff here.  Reasons for patching: in-kernel&n; * module-loader, virtual-to-physical patch-list, McKinley Errata 9 workaround, and gate&n; * shared library.  Undoubtedly, some of these reasons will disappear and others will&n; * be added over time.&n; */
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/types.h&gt;
r_extern
r_void
id|ia64_patch
(paren
id|u64
id|insn_addr
comma
id|u64
id|mask
comma
id|u64
id|val
)paren
suffix:semicolon
multiline_comment|/* patch any insn slot */
r_extern
r_void
id|ia64_patch_imm64
(paren
id|u64
id|insn_addr
comma
id|u64
id|val
)paren
suffix:semicolon
multiline_comment|/* patch &quot;movl&quot; w/abs. value*/
r_extern
r_void
id|ia64_patch_imm60
(paren
id|u64
id|insn_addr
comma
id|u64
id|val
)paren
suffix:semicolon
multiline_comment|/* patch &quot;brl&quot; w/ip-rel value */
r_extern
r_void
id|ia64_patch_mckinley_e9
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|ia64_patch_vtop
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|ia64_patch_gate
(paren
id|Elf64_Ehdr
op_star
id|ehdr
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_PATCH_H */
eof
