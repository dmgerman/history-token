macro_line|#ifndef _ASM_IA64_ASMMACRO_H
DECL|macro|_ASM_IA64_ASMMACRO_H
mdefine_line|#define _ASM_IA64_ASMMACRO_H
multiline_comment|/*&n; * Copyright (C) 2000 Hewlett-Packard Co&n; * Copyright (C) 2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#if 1
multiline_comment|/*&n; * This is a hack that&squot;s necessary as long as we support old versions&n; * of gas, that have no unwind support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA64_NEW_UNWIND
DECL|macro|UNW
macro_line|# define UNW(args...)&t;args
macro_line|#else
DECL|macro|UNW
macro_line|# define UNW(args...)
macro_line|#endif
macro_line|#endif
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
macro_line|#endif /* _ASM_IA64_ASMMACRO_H */
eof
