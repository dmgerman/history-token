macro_line|#ifndef __ASM_ARM_IRQ_H
DECL|macro|__ASM_ARM_IRQ_H
mdefine_line|#define __ASM_ARM_IRQ_H
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#ifndef irq_cannonicalize
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
macro_line|#endif
macro_line|#ifndef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;128
macro_line|#endif
multiline_comment|/*&n; * Use this value to indicate lack of interrupt&n; * capability&n; */
macro_line|#ifndef NO_IRQ
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;((unsigned int)(-1))
macro_line|#endif
r_struct
id|irqaction
suffix:semicolon
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync(i) disable_irq(i)
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__IRQT_FALEDGE
mdefine_line|#define __IRQT_FALEDGE&t;(1 &lt;&lt; 0)
DECL|macro|__IRQT_RISEDGE
mdefine_line|#define __IRQT_RISEDGE&t;(1 &lt;&lt; 1)
DECL|macro|__IRQT_LOWLVL
mdefine_line|#define __IRQT_LOWLVL&t;(1 &lt;&lt; 2)
DECL|macro|__IRQT_HIGHLVL
mdefine_line|#define __IRQT_HIGHLVL&t;(1 &lt;&lt; 3)
DECL|macro|IRQT_NOEDGE
mdefine_line|#define IRQT_NOEDGE&t;(0)
DECL|macro|IRQT_RISING
mdefine_line|#define IRQT_RISING&t;(__IRQT_RISEDGE)
DECL|macro|IRQT_FALLING
mdefine_line|#define IRQT_FALLING&t;(__IRQT_FALEDGE)
DECL|macro|IRQT_BOTHEDGE
mdefine_line|#define IRQT_BOTHEDGE&t;(__IRQT_RISEDGE|__IRQT_FALEDGE)
DECL|macro|IRQT_LOW
mdefine_line|#define IRQT_LOW&t;(__IRQT_LOWLVL)
DECL|macro|IRQT_HIGH
mdefine_line|#define IRQT_HIGH&t;(__IRQT_HIGHLVL)
DECL|macro|IRQT_PROBE
mdefine_line|#define IRQT_PROBE&t;(1 &lt;&lt; 4)
r_int
id|set_irq_type
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|type
)paren
suffix:semicolon
r_int
id|setup_irq
c_func
(paren
r_int
r_int
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
