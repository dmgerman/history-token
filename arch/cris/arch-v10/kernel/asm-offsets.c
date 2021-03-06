macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
multiline_comment|/*&n; * Generate definitions needed by assembly language modules.&n; * This code generates raw asm output which is post-processed to extract&n; * and format the required data.&n; */
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
mdefine_line|#define ENTRY(entry) DEFINE(PT_ ## entry, offsetof(struct pt_regs, entry))
id|ENTRY
c_func
(paren
id|orig_r10
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|r13
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|r12
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|r11
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|r10
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|r9
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|mof
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|dccr
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|srp
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
mdefine_line|#define ENTRY(entry) DEFINE(TI_ ## entry, offsetof(struct thread_info, entry))
id|ENTRY
c_func
(paren
id|task
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
mdefine_line|#define ENTRY(entry) DEFINE(THREAD_ ## entry, offsetof(struct thread_struct, entry))
id|ENTRY
c_func
(paren
id|ksp
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|usp
)paren
suffix:semicolon
id|ENTRY
c_func
(paren
id|dccr
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
mdefine_line|#define ENTRY(entry) DEFINE(TASK_ ## entry, offsetof(struct task_struct, entry))
id|ENTRY
c_func
(paren
id|pid
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LCLONE_VM
comma
id|CLONE_VM
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|LCLONE_UNTRACED
comma
id|CLONE_UNTRACED
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
