macro_line|#ifndef _ASM_IA64_SOFTIRQ_H
DECL|macro|_ASM_IA64_SOFTIRQ_H
mdefine_line|#define _ASM_IA64_SOFTIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|cpu_bh_disable
mdefine_line|#define cpu_bh_disable(cpu)&t;do { local_bh_count(cpu)++; barrier(); } while (0)
DECL|macro|cpu_bh_enable
mdefine_line|#define cpu_bh_enable(cpu)&t;do { barrier(); local_bh_count(cpu)--; } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable(smp_processor_id())
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;cpu_bh_enable(smp_processor_id())
DECL|macro|in_softirq
mdefine_line|#define in_softirq()&t;&t;(local_bh_count(smp_processor_id()) != 0)
macro_line|#endif /* _ASM_IA64_SOFTIRQ_H */
eof
