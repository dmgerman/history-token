macro_line|#ifndef _ASM_IA64_SOFTIRQ_H
DECL|macro|_ASM_IA64_SOFTIRQ_H
mdefine_line|#define _ASM_IA64_SOFTIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; * Copyright (C) 1998-2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;do { barrier(); local_bh_count()--; } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;do { local_bh_count()++; barrier(); } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__local_bh_enable();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__builtin_expect(local_softirq_pending(), 0) &amp;&amp; local_bh_count() == 0)&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__cpu_raise_softirq
mdefine_line|#define __cpu_raise_softirq(cpu,nr)&t;set_bit((nr), &amp;softirq_pending(cpu))
DECL|macro|in_softirq
mdefine_line|#define in_softirq()&t;&t;(local_bh_count() != 0)
macro_line|#endif /* _ASM_IA64_SOFTIRQ_H */
eof
