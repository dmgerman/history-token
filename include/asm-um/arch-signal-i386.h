multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_ARCH_SIGNAL_I386_H
DECL|macro|__UM_ARCH_SIGNAL_I386_H
mdefine_line|#define __UM_ARCH_SIGNAL_I386_H
DECL|struct|arch_signal_context
r_struct
id|arch_signal_context
(brace
DECL|member|extrasigs
r_int
r_int
id|extrasigs
(braket
id|_NSIG_WORDS
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
