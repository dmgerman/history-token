macro_line|#ifndef __UM_SOFTIRQ_H
DECL|macro|__UM_SOFTIRQ_H
mdefine_line|#define __UM_SOFTIRQ_H
macro_line|#include &quot;linux/smp.h&quot;
macro_line|#include &quot;asm/system.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
multiline_comment|/* A gratuitous name change */
DECL|macro|i386_bh_lock
mdefine_line|#define i386_bh_lock um_bh_lock
macro_line|#include &quot;asm/arch/softirq.h&quot;
DECL|macro|i386_bh_lock
macro_line|#undef i386_bh_lock
macro_line|#endif
eof
