multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998, 1999, 2000, 2001 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 1999, 2001 MIPS Technologies, Inc.&n; */
macro_line|#ifndef _ASM_SOFTIRQ_H
DECL|macro|_ASM_SOFTIRQ_H
mdefine_line|#define _ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|function|cpu_bh_disable
r_extern
r_inline
r_void
id|cpu_bh_disable
c_func
(paren
r_int
id|cpu
)paren
(brace
id|local_bh_count
c_func
(paren
id|cpu
)paren
op_increment
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__cpu_bh_enable
r_extern
r_inline
r_void
id|__cpu_bh_enable
c_func
(paren
r_int
id|cpu
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|local_bh_count
c_func
(paren
id|cpu
)paren
op_decrement
suffix:semicolon
)brace
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable(smp_processor_id())
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;__cpu_bh_enable(smp_processor_id())
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int cpu;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cpu = smp_processor_id();&t;&t;&t;&t;&bslash;&n;&t;if (!--local_bh_count(cpu) &amp;&amp; softirq_pending(cpu))&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
DECL|macro|__cpu_raise_softirq
mdefine_line|#define __cpu_raise_softirq(cpu, nr)&t;set_bit(nr, &amp;softirq_pending(cpu))
macro_line|#endif /* _ASM_SOFTIRQ_H */
eof
