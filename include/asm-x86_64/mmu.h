macro_line|#ifndef __x86_64_MMU_H
DECL|macro|__x86_64_MMU_H
mdefine_line|#define __x86_64_MMU_H
multiline_comment|/*&n; * The x86_64 doesn&squot;t have a mmu context, but&n; * we put the segment information here.&n; */
r_typedef
r_struct
(brace
DECL|member|segments
r_void
op_star
id|segments
suffix:semicolon
DECL|member|cpuvalid
r_int
r_int
id|cpuvalid
suffix:semicolon
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#endif
eof
