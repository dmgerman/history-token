multiline_comment|/*&n; * Generate definitions needed by assembly language modules.&n; * This code generates raw asm output which is post-processed to extract&n; * and format the required data.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* Use marker if you need to separate the values later */
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val, marker) &bslash;&n;&t;asm volatile(&quot;&bslash;n-&gt;&quot; #sym &quot; %0 &quot; #val &quot; &quot; #marker : : &quot;i&quot; (val))
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
id|DEFINE
c_func
(paren
id|__THREAD_info
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread_info
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__THREAD_ksp
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.ksp
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__THREAD_per
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.per_info
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__THREAD_mm_segment
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.mm_segment
)paren
comma
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
id|__PER_atmid
comma
m_offsetof
(paren
id|per_struct
comma
id|lowcore.words.perc_atmid
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PER_address
comma
m_offsetof
(paren
id|per_struct
comma
id|lowcore.words.address
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PER_access_id
comma
m_offsetof
(paren
id|per_struct
comma
id|lowcore.words.access_id
)paren
comma
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
id|__TI_task
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|task
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__TI_domain
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|exec_domain
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__TI_flags
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|flags
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__TI_cpu
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|cpu
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__TI_precount
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|preempt_count
)paren
comma
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
id|__PT_ARGS
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|args
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PT_PSW
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|psw
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PT_GPRS
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gprs
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PT_ORIG_GPR2
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|orig_gpr2
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PT_ILC
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|ilc
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PT_TRAP
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|trap
)paren
comma
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|__PT_SIZE
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
comma
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
