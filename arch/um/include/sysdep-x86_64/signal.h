multiline_comment|/*&n; * Copyright (C) 2004 PathScale, Inc&n; * Licensed under the GPL&n; */
macro_line|#ifndef __X86_64_SIGNAL_H_
DECL|macro|__X86_64_SIGNAL_H_
mdefine_line|#define __X86_64_SIGNAL_H_
DECL|macro|ARCH_GET_SIGCONTEXT
mdefine_line|#define ARCH_GET_SIGCONTEXT(sc, sig_addr) &bslash;&n;&t;do { &bslash;&n;&t;&t;struct ucontext *__uc; &bslash;&n;&t;&t;asm(&quot;movq %%rdx, %0&quot; : &quot;=r&quot; (__uc)); &bslash;&n;&t;&t;sc = (struct sigcontext *) &amp;__uc-&gt;uc_mcontext; &bslash;&n;&t;} while(0)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
