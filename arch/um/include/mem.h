multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __MEM_H__
DECL|macro|__MEM_H__
mdefine_line|#define __MEM_H__
DECL|struct|vm_reserved
r_struct
id|vm_reserved
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|set_usable_vm
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
