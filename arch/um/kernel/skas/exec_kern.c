multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/signal.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/mmu_context.h&quot;
macro_line|#include &quot;tlb.h&quot;
macro_line|#include &quot;skas.h&quot;
macro_line|#include &quot;um_mmu.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|flush_thread_skas
r_void
id|flush_thread_skas
c_func
(paren
r_void
)paren
(brace
id|force_flush_all
c_func
(paren
)paren
suffix:semicolon
id|switch_mm_skas
c_func
(paren
id|current-&gt;mm-&gt;context.skas.mm_fd
)paren
suffix:semicolon
)brace
DECL|function|start_thread_skas
r_void
id|start_thread_skas
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|eip
comma
r_int
r_int
id|esp
)paren
(brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|PT_REGS_IP
c_func
(paren
id|regs
)paren
op_assign
id|eip
suffix:semicolon
id|PT_REGS_SP
c_func
(paren
id|regs
)paren
op_assign
id|esp
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
