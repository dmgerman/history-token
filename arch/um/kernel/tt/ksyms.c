multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;mode.h&quot;
DECL|variable|__do_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__do_copy_from_user
)paren
suffix:semicolon
DECL|variable|__do_copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|__do_copy_to_user
)paren
suffix:semicolon
DECL|variable|__do_strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__do_strncpy_from_user
)paren
suffix:semicolon
DECL|variable|__do_strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__do_strnlen_user
)paren
suffix:semicolon
DECL|variable|__do_clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__do_clear_user
)paren
suffix:semicolon
DECL|variable|tracing_pid
id|EXPORT_SYMBOL
c_func
(paren
id|tracing_pid
)paren
suffix:semicolon
DECL|variable|honeypot
id|EXPORT_SYMBOL
c_func
(paren
id|honeypot
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
