multiline_comment|/*&n; * Generate definitions needed by assembly language modules.&n; * This code generates raw asm output which is post-processed to extract&n; * and format the required data.&n; */
macro_line|#include &lt;linux/sched.h&gt; 
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/errno.h&gt; 
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;        asm volatile(&quot;&bslash;n-&gt;&quot; #sym &quot; %0 &quot; #val : : &quot;i&quot; (val))
DECL|macro|BLANK
mdefine_line|#define BLANK() asm volatile(&quot;&bslash;n-&gt;&quot; : : )
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
DECL|macro|ENTRY
mdefine_line|#define ENTRY(entry) DEFINE(tsk_ ## entry, offsetof(struct task_struct, entry))
id|ENTRY
c_func
(paren
id|state
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|thread
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
DECL|macro|ENTRY
macro_line|#undef ENTRY
DECL|macro|ENTRY
mdefine_line|#define ENTRY(entry) DEFINE(threadinfo__ ## entry, offsetof(struct thread_info, entry))
id|ENTRY
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|addr_limit
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|preempt_count
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
DECL|macro|ENTRY
macro_line|#undef ENTRY
DECL|macro|ENTRY
mdefine_line|#define ENTRY(entry) DEFINE(pda__ ## entry, offsetof(struct x8664_pda, entry))
id|ENTRY
c_func
(paren
id|kernelstack
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|oldrsp
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|pcurrent
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|irqrsp
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|irqcount
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|cpunumber
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|irqstackptr
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
DECL|macro|ENTRY
macro_line|#undef ENTRY
r_return
l_int|0
suffix:semicolon
)brace
eof
