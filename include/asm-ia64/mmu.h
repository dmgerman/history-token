macro_line|#ifndef __MMU_H
DECL|macro|__MMU_H
mdefine_line|#define __MMU_H
multiline_comment|/*&n; * Type for a context number.  We declare it volatile to ensure proper ordering when it&squot;s&n; * accessed outside of spinlock&squot;d critical sections (e.g., as done in activate_mm() and&n; * init_new_context()).&n; */
DECL|typedef|mm_context_t
r_typedef
r_volatile
r_int
r_int
id|mm_context_t
suffix:semicolon
macro_line|#endif
eof
