multiline_comment|/* hardirq.h: PA-RISC hard IRQ support.&n; *&n; * Copyright (C) 2001 Matthew Wilcox &lt;matthew@wil.cx&gt;&n; *&n; * The locking is really quite interesting.  There&squot;s a cpu-local&n; * count of how many interrupts are being handled, and a global&n; * lock.  An interrupt can only be serviced if the global lock&n; * is free.  You can&squot;t be sure no more interrupts are being&n; * serviced until you&squot;ve acquired the lock and then checked&n; * all the per-cpu interrupt counts are all zero.  It&squot;s a specialised&n; * br_lock, and that&squot;s exactly how Sparc does it.  We don&squot;t because&n; * it&squot;s more locking for us.  This way is lock-free in the interrupt path.&n; */
macro_line|#ifndef _PARISC_HARDIRQ_H
DECL|macro|_PARISC_HARDIRQ_H
mdefine_line|#define _PARISC_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
multiline_comment|/* set_bit is used on this */
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;16
multiline_comment|/*&n; * The hardirq mask has to be large enough to have space for potentially all IRQ sources&n; * in the system nesting on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
macro_line|#endif /* _PARISC_HARDIRQ_H */
eof
