multiline_comment|/*&n; * Copyright (C) 2004 PathScale, Inc&n; * Licensed under the GPL&n; */
macro_line|#ifndef __I386_SIGNAL_H_
DECL|macro|__I386_SIGNAL_H_
mdefine_line|#define __I386_SIGNAL_H_
macro_line|#include &lt;signal.h&gt;
DECL|macro|ARCH_GET_SIGCONTEXT
mdefine_line|#define ARCH_GET_SIGCONTEXT(sc, sig) &bslash;&n;&t;do sc = (struct sigcontext *) (&amp;sig + 1); while(0)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
