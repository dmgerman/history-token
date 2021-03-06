multiline_comment|/* Copyright (C) 2002, David McCullough &lt;davidm@snapgear.com&gt; */
macro_line|#ifndef __V850_MMU_H__
DECL|macro|__V850_MMU_H__
mdefine_line|#define __V850_MMU_H__
DECL|struct|mm_rblock_struct
r_struct
id|mm_rblock_struct
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
DECL|member|kblock
r_void
op_star
id|kblock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mm_tblock_struct
r_struct
id|mm_tblock_struct
(brace
DECL|member|rblock
r_struct
id|mm_rblock_struct
op_star
id|rblock
suffix:semicolon
DECL|member|next
r_struct
id|mm_tblock_struct
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|tblock
r_struct
id|mm_tblock_struct
id|tblock
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
macro_line|#endif /* __V850_MMU_H__ */
eof
