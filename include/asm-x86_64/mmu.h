macro_line|#ifndef __x86_64_MMU_H
DECL|macro|__x86_64_MMU_H
mdefine_line|#define __x86_64_MMU_H
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/*&n; * The x86_64 doesn&squot;t have a mmu context, but&n; * we put the segment information here.&n; *&n; * cpu_vm_mask is used to optimize ldt flushing.&n; */
r_typedef
r_struct
(brace
DECL|member|ldt
r_void
op_star
id|ldt
suffix:semicolon
DECL|member|ldtlock
id|rwlock_t
id|ldtlock
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#endif
eof
