macro_line|#ifndef _ASM_IA64_SOFTIRQ_H
DECL|macro|_ASM_IA64_SOFTIRQ_H
mdefine_line|#define _ASM_IA64_SOFTIRQ_H
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;do { barrier(); really_local_bh_count()--; } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;do { really_local_bh_count()++; barrier(); } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__local_bh_enable();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(local_softirq_pending()) &amp;&amp; really_local_bh_count() == 0)&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq()&t;&t;(really_local_bh_count() != 0)
macro_line|#endif /* _ASM_IA64_SOFTIRQ_H */
eof
