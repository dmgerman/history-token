multiline_comment|/*&n; * This program is used to generate definitions needed by&n; * assembly language modules.&n; *&n; * We use the technique used in the OSF Mach kernel code:&n; * generate asm statements containing #defines,&n; * compile this file to assembler, and then extract the&n; * #defines from the assembly-language output.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
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
multiline_comment|/* offsets into the task struct */
id|DEFINE
c_func
(paren
id|TASK_STATE
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|state
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_FLAGS
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|flags
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PTRACE
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|ptrace
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_BLOCKED
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|blocked
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_THREAD
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
id|DEFINE
c_func
(paren
id|TASK_THREAD_INFO
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread_info
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_MM
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|mm
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_ACTIVE_MM
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|active_mm
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets into the irq_cpustat_t struct */
id|DEFINE
c_func
(paren
id|CPUSTAT_SOFTIRQ_PENDING
comma
m_offsetof
(paren
id|irq_cpustat_t
comma
id|__softirq_pending
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets into the thread struct */
id|DEFINE
c_func
(paren
id|THREAD_KSP
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|ksp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_USP
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|usp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_CCR
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|ccr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_VFORK
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|vfork_ret
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_PTRACED
comma
id|PT_PTRACED
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_DTRACE
comma
id|PT_DTRACE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
