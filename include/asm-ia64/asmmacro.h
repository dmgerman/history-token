macro_line|#ifndef _ASM_IA64_ASMMACRO_H
DECL|macro|_ASM_IA64_ASMMACRO_H
mdefine_line|#define _ASM_IA64_ASMMACRO_H
multiline_comment|/*&n; * Copyright (C) 2000-2001 Hewlett-Packard Co&n; * Copyright (C) 2000-2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|ENTRY
mdefine_line|#define ENTRY(name)&t;&t;&t;&t;&bslash;&n;&t;.align 32;&t;&t;&t;&t;&bslash;&n;&t;.proc name;&t;&t;&t;&t;&bslash;&n;name:
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
macro_line|#if __GNUC__ &gt;= 3
DECL|macro|EX
macro_line|# define EX(y,x...)&t;&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;__ex_table&quot;, @gprel(99f), @gprel(y);&t;&bslash;&n;  [99:]&t;x
DECL|macro|EXCLR
macro_line|# define EXCLR(y,x...)&t;&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;__ex_table&quot;, @gprel(99f), @gprel(y)+4;&t;&bslash;&n;  [99:]&t;x
macro_line|#else
macro_line|# define EX(y,x...)&t;&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;__ex_table&quot;, @gprel(99f), @gprel(y);&t;&bslash;&n;  99:&t;x
macro_line|# define EXCLR(y,x...)&t;&t;&t;&t;&t;&bslash;&n;&t;.xdata4 &quot;__ex_table&quot;, @gprel(99f), @gprel(y)+4;&t;&bslash;&n;  99:&t;x
macro_line|#endif
macro_line|#endif /* _ASM_IA64_ASMMACRO_H */
eof
