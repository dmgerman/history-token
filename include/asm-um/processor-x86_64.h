multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PROCESSOR_X86_64_H
DECL|macro|__UM_PROCESSOR_X86_64_H
mdefine_line|#define __UM_PROCESSOR_X86_64_H
macro_line|#include &quot;asm/arch/user.h&quot;
DECL|struct|arch_thread
r_struct
id|arch_thread
(brace
)brace
suffix:semicolon
DECL|macro|INIT_ARCH_THREAD
mdefine_line|#define INIT_ARCH_THREAD { }
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() &bslash;&n;&t;({ void *pc; __asm__(&quot;movq $1f,%0&bslash;n1:&quot;:&quot;=g&quot; (pc)); pc; })
DECL|macro|ARCH_IS_STACKGROW
mdefine_line|#define ARCH_IS_STACKGROW(address) &bslash;&n;        (address + 128 &gt;= UPT_SP(&amp;current-&gt;thread.regs.regs))
macro_line|#include &quot;asm/processor-generic.h&quot;
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
