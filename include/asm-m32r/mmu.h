macro_line|#ifndef _ASM_M32R_MMU_H
DECL|macro|_ASM_M32R_MMU_H
mdefine_line|#define _ASM_M32R_MMU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if !defined(CONFIG_MMU)
r_typedef
r_struct
(brace
DECL|member|vmlist
r_struct
id|vm_list_struct
op_star
id|vmlist
suffix:semicolon
DECL|member|end_brk
r_int
r_int
id|end_brk
suffix:semicolon
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#else
multiline_comment|/* Default &quot;unsigned long&quot; context */
macro_line|#ifndef CONFIG_SMP
DECL|typedef|mm_context_t
r_typedef
r_int
r_int
id|mm_context_t
suffix:semicolon
macro_line|#else
DECL|typedef|mm_context_t
r_typedef
r_int
r_int
id|mm_context_t
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
macro_line|#endif  /* CONFIG_MMU */
macro_line|#endif  /* _ASM_M32R_MMU_H */
eof
