multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 98, 99, 2000, 01, 05 Ralf Baechle (ralf@linux-mips.org)&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#ifndef _ASM_HARDIRQ_H
DECL|macro|_ASM_HARDIRQ_H
mdefine_line|#define _ASM_HARDIRQ_H
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
r_extern
r_void
id|ack_bad_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif /* _ASM_HARDIRQ_H */
eof
