multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_CURRENT_H
DECL|macro|__UM_CURRENT_H
mdefine_line|#define __UM_CURRENT_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;linux/thread_info.h&quot;
DECL|macro|current
mdefine_line|#define current (current_thread_info()-&gt;task)
multiline_comment|/*Backward compatibility - it&squot;s used inside arch/um.*/
DECL|macro|current_thread
mdefine_line|#define current_thread current_thread_info()
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
