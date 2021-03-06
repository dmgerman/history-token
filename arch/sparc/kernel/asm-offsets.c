multiline_comment|/*&n; * This program is used to generate definitions needed by&n; * assembly language modules.&n; *&n; * We use the technique used in the OSF Mach kernel code:&n; * generate asm statements containing #defines,&n; * compile this file to assembler, and then extract the&n; * #defines from the assembly-language output.&n; *&n; * On sparc, thread_info data is static and TI_XXX offsets are computed by hand.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
singleline_comment|// #include &lt;linux/mm.h&gt;
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;&t;asm volatile(&quot;&bslash;n-&gt;&quot; #sym &quot; %0 &quot; #val : : &quot;i&quot; (val))
DECL|macro|BLANK
mdefine_line|#define BLANK() asm volatile(&quot;&bslash;n-&gt;&quot; : : )
DECL|function|foo
r_int
id|foo
c_func
(paren
r_void
)paren
(brace
id|DEFINE
c_func
(paren
id|AOFF_task_thread
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX This is the stuff for sclow.S, kill it. */
id|DEFINE
c_func
(paren
id|AOFF_task_pid
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|pid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|AOFF_task_uid
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|uid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|AOFF_task_gid
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|gid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|AOFF_task_euid
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|euid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|AOFF_task_egid
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|egid
)paren
)paren
suffix:semicolon
multiline_comment|/* DEFINE(THREAD_INFO, offsetof(struct task_struct, thread_info)); */
id|DEFINE
c_func
(paren
id|ASIZ_task_uid
comma
r_sizeof
(paren
id|current-&gt;uid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASIZ_task_gid
comma
r_sizeof
(paren
id|current-&gt;gid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASIZ_task_euid
comma
r_sizeof
(paren
id|current-&gt;euid
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASIZ_task_egid
comma
r_sizeof
(paren
id|current-&gt;egid
)paren
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
id|AOFF_thread_fork_kpsr
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fork_kpsr
)paren
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
id|AOFF_mm_context
comma
m_offsetof
(paren
r_struct
id|mm_struct
comma
id|context
)paren
)paren
suffix:semicolon
multiline_comment|/* DEFINE(NUM_USER_SEGMENTS, TASK_SIZE&gt;&gt;28); */
r_return
l_int|0
suffix:semicolon
)brace
eof
