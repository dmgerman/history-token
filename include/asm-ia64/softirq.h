macro_line|#ifndef _ASM_IA64_SOFTIRQ_H
DECL|macro|_ASM_IA64_SOFTIRQ_H
mdefine_line|#define _ASM_IA64_SOFTIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; * Copyright (C) 1998-2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;do { local_bh_count()++; barrier(); } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;do { barrier(); local_bh_count()--; } while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq()&t;&t;(local_bh_count() != 0)
macro_line|#endif /* _ASM_IA64_SOFTIRQ_H */
eof
