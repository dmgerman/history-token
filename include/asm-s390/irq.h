macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/*&n; * the definition of irqs has changed in 2.5.46:&n; * NR_IRQS is no longer the number of i/o&n; * interrupts (65536), but rather the number&n; * of interrupt classes (2).&n; * Only external and i/o interrupts make much sense here (CH).&n; */
DECL|enum|interruption_class
r_enum
id|interruption_class
(brace
DECL|enumerator|EXTERNAL_INTERRUPT
id|EXTERNAL_INTERRUPT
comma
DECL|enumerator|IO_INTERRUPT
id|IO_INTERRUPT
comma
DECL|enumerator|NR_IRQS
id|NR_IRQS
comma
)brace
suffix:semicolon
DECL|macro|touch_nmi_watchdog
mdefine_line|#define touch_nmi_watchdog() do { } while(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
