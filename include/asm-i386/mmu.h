macro_line|#ifndef __i386_MMU_H
DECL|macro|__i386_MMU_H
mdefine_line|#define __i386_MMU_H
multiline_comment|/*&n; * The i386 doesn&squot;t have a mmu context, but&n; * we put the segment information here.&n; */
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
