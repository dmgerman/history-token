macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
DECL|macro|__cpu_bh_enable
mdefine_line|#define __cpu_bh_enable() do { &bslash;&n;&t;barrier(); sub_pda(__local_bh_count,1); preempt_enable(); } while (0)
DECL|macro|cpu_bh_disable
mdefine_line|#define cpu_bh_disable() do { &bslash;&n;&t;preempt_disable(); add_pda(__local_bh_count,1); barrier(); } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable()
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;__cpu_bh_enable()
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (read_pda(__local_bh_count) != 0)
DECL|macro|_local_bh_enable
mdefine_line|#define _local_bh_enable() do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;decl %%gs:%c1;&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;jnz 1f;&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmpl $0,%%gs:%c0;&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;jnz 2f;&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:;&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;;&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2: call do_softirq_thunk;&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;jmp 1b;&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot; &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:: &quot;i&quot; (pda___softirq_pending), &quot;i&quot; (pda___local_bh_count) : &bslash;&n;&t;&t;&quot;memory&quot;);&t;&bslash;&n;} while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable() do { _local_bh_enable(); preempt_enable(); } while(0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
