multiline_comment|/*&n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __MCONSOLE_KERN_H__
DECL|macro|__MCONSOLE_KERN_H__
mdefine_line|#define __MCONSOLE_KERN_H__
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;mconsole.h&quot;
DECL|struct|mconsole_entry
r_struct
id|mconsole_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|request
r_struct
id|mc_request
id|request
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mc_device
r_struct
id|mc_device
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|config
r_int
(paren
op_star
id|config
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MCONSOLE
r_extern
r_void
id|mconsole_register_dev
c_func
(paren
r_struct
id|mc_device
op_star
r_new
)paren
suffix:semicolon
macro_line|#else
DECL|function|mconsole_register_dev
r_static
r_inline
r_void
id|mconsole_register_dev
c_func
(paren
r_struct
id|mc_device
op_star
r_new
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof