multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_SIGNAL_H
DECL|macro|__UM_SIGNAL_H
mdefine_line|#define __UM_SIGNAL_H
multiline_comment|/* Need to kill the do_signal() declaration in the i386 signal.h */
DECL|macro|do_signal
mdefine_line|#define do_signal do_signal_renamed
macro_line|#include &quot;asm/arch/signal.h&quot;
DECL|macro|do_signal
macro_line|#undef do_signal
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
