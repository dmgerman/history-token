multiline_comment|/*&n; * Copyright (C) 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __MEM_KERN_H__
DECL|macro|__MEM_KERN_H__
mdefine_line|#define __MEM_KERN_H__
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/types.h&quot;
DECL|struct|remapper
r_struct
id|remapper
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|proc
r_int
(paren
op_star
id|proc
)paren
(paren
r_int
comma
r_int
r_int
comma
r_int
comma
id|__u64
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|register_remapper
c_func
(paren
r_struct
id|remapper
op_star
id|info
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
