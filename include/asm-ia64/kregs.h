macro_line|#ifndef _ASM_IA64_KREGS_H
DECL|macro|_ASM_IA64_KREGS_H
mdefine_line|#define _ASM_IA64_KREGS_H
multiline_comment|/*&n; * Copyright (C) 2001 Hewlett-Packard Co&n; * Copyright (C) 2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * This file defines the kernel register usage convention used by Linux/ia64.&n; */
multiline_comment|/*&n; * Kernel registers:&n; */
DECL|macro|IA64_KR_IO_BASE
mdefine_line|#define IA64_KR_IO_BASE&t;&t;0&t;/* ar.k0: legacy I/O base address */
DECL|macro|IA64_KR_TSSD
mdefine_line|#define IA64_KR_TSSD&t;&t;1&t;/* ar.k1: IVE uses this as the TSSD */
DECL|macro|IA64_KR_CURRENT_STACK
mdefine_line|#define IA64_KR_CURRENT_STACK&t;4&t;/* ar.k4: what&squot;s mapped in IA64_TR_CURRENT_STACK */
DECL|macro|IA64_KR_FPU_OWNER
mdefine_line|#define IA64_KR_FPU_OWNER&t;5&t;/* ar.k5: fpu-owner (UP only, at the moment) */
DECL|macro|IA64_KR_CURRENT
mdefine_line|#define IA64_KR_CURRENT&t;&t;6&t;/* ar.k6: &quot;current&quot; task pointer */
DECL|macro|IA64_KR_PT_BASE
mdefine_line|#define IA64_KR_PT_BASE&t;&t;7&t;/* ar.k7: page table base address (physical) */
DECL|macro|_IA64_KR_PASTE
mdefine_line|#define _IA64_KR_PASTE(x,y)&t;x##y
DECL|macro|_IA64_KR_PREFIX
mdefine_line|#define _IA64_KR_PREFIX(n)&t;_IA64_KR_PASTE(ar.k, n)
DECL|macro|IA64_KR
mdefine_line|#define IA64_KR(n)&t;&t;_IA64_KR_PREFIX(IA64_KR_##n)
multiline_comment|/*&n; * Translation registers:&n; */
DECL|macro|IA64_TR_KERNEL
mdefine_line|#define IA64_TR_KERNEL&t;&t;0&t;/* itr0, dtr0: maps kernel image (code &amp; data) */
DECL|macro|IA64_TR_PALCODE
mdefine_line|#define IA64_TR_PALCODE&t;&t;1&t;/* itr1: maps PALcode as required by EFI */
DECL|macro|IA64_TR_PERCPU_DATA
mdefine_line|#define IA64_TR_PERCPU_DATA&t;1&t;/* dtr1: percpu data */
DECL|macro|IA64_TR_CURRENT_STACK
mdefine_line|#define IA64_TR_CURRENT_STACK&t;2&t;/* dtr2: maps kernel&squot;s memory- &amp; register-stacks */
macro_line|#endif /* _ASM_IA64_kREGS_H */
eof
