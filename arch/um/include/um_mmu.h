multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __ARCH_UM_MMU_H
DECL|macro|__ARCH_UM_MMU_H
mdefine_line|#define __ARCH_UM_MMU_H
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#ifdef CONFIG_MODE_TT
macro_line|#include &quot;mmu-tt.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_SKAS
macro_line|#include &quot;mmu-skas.h&quot;
macro_line|#endif
r_typedef
r_union
(brace
macro_line|#ifdef CONFIG_MODE_TT
DECL|member|tt
r_struct
id|mmu_context_tt
id|tt
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_SKAS
DECL|member|skas
r_struct
id|mmu_context_skas
id|skas
suffix:semicolon
macro_line|#endif
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
