multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_CURRENT_H
DECL|macro|__UM_CURRENT_H
mdefine_line|#define __UM_CURRENT_H
macro_line|#ifndef __ASSEMBLY__
r_struct
id|thread_info
suffix:semicolon
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;asm/page.h&quot;
DECL|macro|CURRENT_THREAD
mdefine_line|#define CURRENT_THREAD(dummy) (((unsigned long) &amp;dummy) &amp; &bslash;&n;&t;&t;&t;        (PAGE_MASK &lt;&lt; CONFIG_KERNEL_SACK_ORDER))
DECL|macro|current
mdefine_line|#define current ({ int dummy; &bslash;&n;                   ((struct thread_info *) CURRENT_THREAD(dummy))-&gt;task; })
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
