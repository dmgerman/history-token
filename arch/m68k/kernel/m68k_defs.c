multiline_comment|/*&n; * This program is used to generate definitions needed by&n; * assembly language modules.&n; *&n; * We use the technique used in the OSF Mach kernel code:&n; * generate asm statements containing #defines,&n; * compile this file to assembler, and then extract the&n; * #defines from the assembly-language output.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;linux/font.h&gt;
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;&t;asm volatile(&quot;&bslash;n#define &quot; #sym &quot; %c0&quot; : : &quot;i&quot; (val))
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
id|TASK_WORK
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.work
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_NEEDRESCHED
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.work.need_resched
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_SYSCALL_TRACE
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.work.syscall_trace
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_SIGPENDING
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.work.sigpending
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_NOTIFY_RESUME
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.work.notify_resume
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
id|THREAD_SR
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|sr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FS
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fs
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_CRP
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|crp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_ESP0
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|esp0
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FPREG
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FPCNTL
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fpcntl
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_FPSTATE
comma
m_offsetof
(paren
r_struct
id|thread_struct
comma
id|fpstate
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets into the pt_regs */
id|DEFINE
c_func
(paren
id|PT_D0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|d0
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_ORIG_D0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|orig_d0
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_D1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|d1
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_D2
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|d2
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_D3
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|d3
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_D4
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|d4
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_D5
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|d5
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_A0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|a0
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_A1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|a1
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_A2
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|a2
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_PC
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|pc
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
)paren
)paren
suffix:semicolon
multiline_comment|/* bitfields are a bit difficult */
id|DEFINE
c_func
(paren
id|PT_VECTOR
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|pc
)paren
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* offsets into the irq_handler struct */
id|DEFINE
c_func
(paren
id|IRQ_HANDLER
comma
m_offsetof
(paren
r_struct
id|irq_node
comma
id|handler
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|IRQ_DEVID
comma
m_offsetof
(paren
r_struct
id|irq_node
comma
id|dev_id
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|IRQ_NEXT
comma
m_offsetof
(paren
r_struct
id|irq_node
comma
id|next
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets into the kernel_stat struct */
id|DEFINE
c_func
(paren
id|STAT_IRQ
comma
m_offsetof
(paren
r_struct
id|kernel_stat
comma
id|irqs
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
id|DEFINE
c_func
(paren
id|CPUSTAT_SYSCALL_COUNT
comma
m_offsetof
(paren
id|irq_cpustat_t
comma
id|__syscall_count
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets into the bi_record struct */
id|DEFINE
c_func
(paren
id|BIR_TAG
comma
m_offsetof
(paren
r_struct
id|bi_record
comma
id|tag
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|BIR_SIZE
comma
m_offsetof
(paren
r_struct
id|bi_record
comma
id|size
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|BIR_DATA
comma
m_offsetof
(paren
r_struct
id|bi_record
comma
id|data
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets into font_desc (drivers/video/console/font.h) */
id|DEFINE
c_func
(paren
id|FONT_DESC_IDX
comma
m_offsetof
(paren
r_struct
id|font_desc
comma
id|idx
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|FONT_DESC_NAME
comma
m_offsetof
(paren
r_struct
id|font_desc
comma
id|name
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|FONT_DESC_WIDTH
comma
m_offsetof
(paren
r_struct
id|font_desc
comma
id|width
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|FONT_DESC_HEIGHT
comma
m_offsetof
(paren
r_struct
id|font_desc
comma
id|height
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|FONT_DESC_DATA
comma
m_offsetof
(paren
r_struct
id|font_desc
comma
id|data
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|FONT_DESC_PREF
comma
m_offsetof
(paren
r_struct
id|font_desc
comma
id|pref
)paren
)paren
suffix:semicolon
multiline_comment|/* signal defines */
id|DEFINE
c_func
(paren
id|SIGSEGV
comma
id|SIGSEGV
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|SEGV_MAPERR
comma
id|SEGV_MAPERR
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|SIGTRAP
comma
id|SIGTRAP
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TRAP_TRACE
comma
id|TRAP_TRACE
)paren
suffix:semicolon
multiline_comment|/* offsets into the custom struct */
id|DEFINE
c_func
(paren
id|CUSTOMBASE
comma
op_amp
id|custom
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_INTENAR
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|intenar
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_INTREQR
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|intreqr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_INTENA
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|intena
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_INTREQ
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|intreq
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_SERDATR
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|serdatr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_SERDAT
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|serdat
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_SERPER
comma
m_offsetof
(paren
r_struct
id|CUSTOM
comma
id|serper
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CIAABASE
comma
op_amp
id|ciaa
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|CIABBASE
comma
op_amp
id|ciab
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|C_PRA
comma
m_offsetof
(paren
r_struct
id|CIA
comma
id|pra
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ZTWOBASE
comma
id|zTwoBase
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
