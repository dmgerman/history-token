macro_line|#ifndef _ASM_IA64_ASMMACRO_H
DECL|macro|_ASM_IA64_ASMMACRO_H
mdefine_line|#define _ASM_IA64_ASMMACRO_H
multiline_comment|/*&n; * Copyright (C) 2000-2001, 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|ENTRY
mdefine_line|#define ENTRY(name)&t;&t;&t;&t;&bslash;&n;&t;.align 32;&t;&t;&t;&t;&bslash;&n;&t;.proc name;&t;&t;&t;&t;&bslash;&n;name:
DECL|macro|ENTRY_MIN_ALIGN
mdefine_line|#define ENTRY_MIN_ALIGN(name)&t;&t;&t;&bslash;&n;&t;.align 16;&t;&t;&t;&t;&bslash;&n;&t;.proc name;&t;&t;&t;&t;&bslash;&n;name:
DECL|macro|GLOBAL_ENTRY
mdefine_line|#define GLOBAL_ENTRY(name)&t;&t;&t;&bslash;&n;&t;.global name;&t;&t;&t;&t;&bslash;&n;&t;ENTRY(name)
DECL|macro|END
mdefine_line|#define END(name)&t;&t;&t;&t;&bslash;&n;&t;.endp name
multiline_comment|/*&n; * Helper macros to make unwind directives more readable:&n; */
multiline_comment|/* prologue_gr: */
DECL|macro|ASM_UNW_PRLG_RP
mdefine_line|#define ASM_UNW_PRLG_RP&t;&t;&t;0x8
DECL|macro|ASM_UNW_PRLG_PFS
mdefine_line|#define ASM_UNW_PRLG_PFS&t;&t;0x4
DECL|macro|ASM_UNW_PRLG_PSP
mdefine_line|#define ASM_UNW_PRLG_PSP&t;&t;0x2
DECL|macro|ASM_UNW_PRLG_PR
mdefine_line|#define ASM_UNW_PRLG_PR&t;&t;&t;0x1
DECL|macro|ASM_UNW_PRLG_GRSAVE
mdefine_line|#define ASM_UNW_PRLG_GRSAVE(ninputs)&t;(32+(ninputs))
multiline_comment|/*&n; * Helper macros for accessing user memory.&n; */
dot
id|section
l_string|&quot;__ex_table&quot;
comma
l_string|&quot;a&quot;
singleline_comment|// declare section &amp; section attributes
dot
id|previous
DECL|macro|EX
macro_line|# define EX(y,x...)&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;__ex_table&quot;, 99f-., y-.;&t;&bslash;&n;  [99:]&t;x
DECL|macro|EXCLR
macro_line|# define EXCLR(y,x...)&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;__ex_table&quot;, 99f-., y-.+4;&t;&bslash;&n;  [99:]&t;x
multiline_comment|/*&n; * Mark instructions that need a load of a virtual address patched to be&n; * a load of a physical address.  We use this either in critical performance&n; * path (ivt.S - TLB miss processing) or in places where it might not be&n; * safe to use a &quot;tpa&quot; instruction (mca_asm.S - error recovery).&n; */
dot
id|section
l_string|&quot;.data.patch.vtop&quot;
comma
l_string|&quot;a&quot;
singleline_comment|// declare section &amp; section attributes
dot
id|previous
DECL|macro|LOAD_PHYSICAL
mdefine_line|#define&t;LOAD_PHYSICAL(pr, reg, obj)&t;&t;&bslash;&n;[1:](pr)movl reg = obj;&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;.data.patch.vtop&quot;, 1b-.
multiline_comment|/*&n; * For now, we always put in the McKinley E9 workaround.  On CPUs that don&squot;t need it,&n; * we&squot;ll patch out the work-around bundles with NOPs, so their impact is minimal.&n; */
DECL|macro|DO_MCKINLEY_E9_WORKAROUND
mdefine_line|#define DO_MCKINLEY_E9_WORKAROUND
macro_line|#ifdef DO_MCKINLEY_E9_WORKAROUND
dot
id|section
l_string|&quot;.data.patch.mckinley_e9&quot;
comma
l_string|&quot;a&quot;
dot
id|previous
multiline_comment|/* workaround for Itanium 2 Errata 9: */
DECL|macro|MCKINLEY_E9_WORKAROUND
macro_line|# define MCKINLEY_E9_WORKAROUND&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;.data.patch.mckinley_e9&quot;, 1f-.;&bslash;&n;1:{ .mib;&t;&t;&t;&t;&t;&bslash;&n;&t;nop.m 0;&t;&t;&t;&t;&bslash;&n;&t;nop.i 0;&t;&t;&t;&t;&bslash;&n;&t;br.call.sptk.many b7=1f;;&t;&t;&bslash;&n;  };&t;&t;&t;&t;&t;&t;&bslash;&n;1:
macro_line|#else
macro_line|# define MCKINLEY_E9_WORKAROUND
macro_line|#endif
macro_line|#endif /* _ASM_IA64_ASMMACRO_H */
eof
