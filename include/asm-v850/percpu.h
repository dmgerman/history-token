macro_line|#ifndef __V850_PERCPU_H__
DECL|macro|__V850_PERCPU_H__
mdefine_line|#define __V850_PERCPU_H__
macro_line|#include &lt;asm-generic/percpu.h&gt;
multiline_comment|/* This is a stupid hack to satisfy some grotty implicit include-file&n;   dependency; basically, &lt;linux/smp.h&gt; uses BUG_ON, which calls BUG, but&n;   doesn&squot;t include the necessary headers to define it.  In the twisted&n;   festering mess of includes this must all be resolved somehow on other&n;   platforms, but I haven&squot;t the faintest idea how, and don&squot;t care; here will&n;   do, even though doesn&squot;t actually make any sense.  */
macro_line|#include &lt;asm/page.h&gt;
macro_line|#endif /* __V850_PERCPU_H__ */
eof
