macro_line|#ifndef __i386_MMU_H
DECL|macro|__i386_MMU_H
mdefine_line|#define __i386_MMU_H
multiline_comment|/*&n; * The i386 doesn&squot;t have a mmu context, but&n; * we put the segment information here.&n; *&n; * cpu_vm_mask is used to optimize ldt flushing.&n; */
r_typedef
r_struct
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|ldt
r_void
op_star
id|ldt
suffix:semicolon
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#endif
eof
