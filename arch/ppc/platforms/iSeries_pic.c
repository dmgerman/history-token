multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; *  arch/ppc/platforms/iSeries_pic.c&n; *&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
r_extern
r_void
id|iSeries_smp_message_recv
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|is_soft_enabled
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__no_lpq_restore_flags
c_func
(paren
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_smp_message_recv
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|lpEvent_count
r_int
id|lpEvent_count
op_assign
l_int|0
suffix:semicolon
DECL|function|do_IRQ
r_int
id|do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|Paca
op_star
id|paca
suffix:semicolon
r_struct
id|ItLpQueue
op_star
id|lpq
suffix:semicolon
r_if
c_cond
(paren
id|is_soft_enabled
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|hardirq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|paca
op_assign
(paren
r_struct
id|Paca
op_star
)paren
id|mfspr
c_func
(paren
id|SPRG1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|paca-&gt;xLpPacaPtr-&gt;xIpiCnt
)paren
(brace
id|paca-&gt;xLpPacaPtr-&gt;xIpiCnt
op_assign
l_int|0
suffix:semicolon
id|iSeries_smp_message_recv
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
id|lpq
op_assign
id|paca-&gt;lpQueuePtr
suffix:semicolon
r_if
c_cond
(paren
id|lpq
)paren
(brace
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|lpEvent_count
op_add_assign
id|ItLpQueue_process
c_func
(paren
id|lpq
comma
id|regs
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
id|hardirq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|paca-&gt;xLpPacaPtr-&gt;xDecrInt
)paren
(brace
id|paca-&gt;xLpPacaPtr-&gt;xDecrInt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Signal a fake decrementer interrupt */
id|timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* lets ret_from_int know we can do checks */
)brace
eof
