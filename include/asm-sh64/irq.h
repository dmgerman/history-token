macro_line|#ifndef __ASM_SH64_IRQ_H
DECL|macro|__ASM_SH64_IRQ_H
mdefine_line|#define __ASM_SH64_IRQ_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/irq.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Encoded IRQs are not considered worth to be supported.&n; * Main reason is that there&squot;s no per-encoded-interrupt&n; * enable/disable mechanism (as there was in SH3/4).&n; * An all enabled/all disabled is worth only if there&squot;s&n; * a cascaded IC to disable/enable/ack on. Until such&n; * IC is available there&squot;s no such support.&n; *&n; * Presumably Encoded IRQs may use extra IRQs beyond 64,&n; * below. Some logic must be added to cope with IRQ_IRL?&n; * in an exclusive way.&n; *&n; * Priorities are set at Platform level, when IRQ_IRL0-3&n; * are set to 0 Encoding is allowed. Otherwise it&squot;s not&n; * allowed.&n; */
multiline_comment|/* Independent IRQs */
DECL|macro|IRQ_IRL0
mdefine_line|#define IRQ_IRL0&t;0
DECL|macro|IRQ_IRL1
mdefine_line|#define IRQ_IRL1&t;1
DECL|macro|IRQ_IRL2
mdefine_line|#define IRQ_IRL2&t;2
DECL|macro|IRQ_IRL3
mdefine_line|#define IRQ_IRL3&t;3
DECL|macro|IRQ_INTA
mdefine_line|#define IRQ_INTA&t;4
DECL|macro|IRQ_INTB
mdefine_line|#define IRQ_INTB&t;5
DECL|macro|IRQ_INTC
mdefine_line|#define IRQ_INTC&t;6
DECL|macro|IRQ_INTD
mdefine_line|#define IRQ_INTD&t;7
DECL|macro|IRQ_SERR
mdefine_line|#define IRQ_SERR&t;12
DECL|macro|IRQ_ERR
mdefine_line|#define IRQ_ERR&t;&t;13
DECL|macro|IRQ_PWR3
mdefine_line|#define IRQ_PWR3&t;14
DECL|macro|IRQ_PWR2
mdefine_line|#define IRQ_PWR2&t;15
DECL|macro|IRQ_PWR1
mdefine_line|#define IRQ_PWR1&t;16
DECL|macro|IRQ_PWR0
mdefine_line|#define IRQ_PWR0&t;17
DECL|macro|IRQ_DMTE0
mdefine_line|#define IRQ_DMTE0&t;18
DECL|macro|IRQ_DMTE1
mdefine_line|#define IRQ_DMTE1&t;19
DECL|macro|IRQ_DMTE2
mdefine_line|#define IRQ_DMTE2&t;20
DECL|macro|IRQ_DMTE3
mdefine_line|#define IRQ_DMTE3&t;21
DECL|macro|IRQ_DAERR
mdefine_line|#define IRQ_DAERR&t;22
DECL|macro|IRQ_TUNI0
mdefine_line|#define IRQ_TUNI0&t;32
DECL|macro|IRQ_TUNI1
mdefine_line|#define IRQ_TUNI1&t;33
DECL|macro|IRQ_TUNI2
mdefine_line|#define IRQ_TUNI2&t;34
DECL|macro|IRQ_TICPI2
mdefine_line|#define IRQ_TICPI2&t;35
DECL|macro|IRQ_ATI
mdefine_line|#define IRQ_ATI&t;&t;36
DECL|macro|IRQ_PRI
mdefine_line|#define IRQ_PRI&t;&t;37
DECL|macro|IRQ_CUI
mdefine_line|#define IRQ_CUI&t;&t;38
DECL|macro|IRQ_ERI
mdefine_line|#define IRQ_ERI&t;&t;39
DECL|macro|IRQ_RXI
mdefine_line|#define IRQ_RXI&t;&t;40
DECL|macro|IRQ_BRI
mdefine_line|#define IRQ_BRI&t;&t;41
DECL|macro|IRQ_TXI
mdefine_line|#define IRQ_TXI&t;&t;42
DECL|macro|IRQ_ITI
mdefine_line|#define IRQ_ITI&t;&t;63
DECL|macro|NR_INTC_IRQS
mdefine_line|#define NR_INTC_IRQS&t;64
macro_line|#ifdef CONFIG_SH_CAYMAN
DECL|macro|NR_EXT_IRQS
mdefine_line|#define NR_EXT_IRQS     32
DECL|macro|START_EXT_IRQS
mdefine_line|#define START_EXT_IRQS  64
multiline_comment|/* PCI bus 2 uses encoded external interrupts on the Cayman board */
DECL|macro|IRQ_P2INTA
mdefine_line|#define IRQ_P2INTA      (START_EXT_IRQS + (3*8) + 0)
DECL|macro|IRQ_P2INTB
mdefine_line|#define IRQ_P2INTB      (START_EXT_IRQS + (3*8) + 1)
DECL|macro|IRQ_P2INTC
mdefine_line|#define IRQ_P2INTC      (START_EXT_IRQS + (3*8) + 2)
DECL|macro|IRQ_P2INTD
mdefine_line|#define IRQ_P2INTD      (START_EXT_IRQS + (3*8) + 3)
DECL|macro|I8042_KBD_IRQ
mdefine_line|#define I8042_KBD_IRQ&t;(START_EXT_IRQS + 2)
DECL|macro|I8042_AUX_IRQ
mdefine_line|#define I8042_AUX_IRQ&t;(START_EXT_IRQS + 6)
DECL|macro|IRQ_CFCARD
mdefine_line|#define IRQ_CFCARD&t;(START_EXT_IRQS + 7)
DECL|macro|IRQ_PCMCIA
mdefine_line|#define IRQ_PCMCIA&t;(0)
macro_line|#else
DECL|macro|NR_EXT_IRQS
mdefine_line|#define NR_EXT_IRQS&t;0
macro_line|#endif
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(NR_INTC_IRQS+NR_EXT_IRQS)
multiline_comment|/* Default IRQs, fixed */
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;IRQ_TUNI0
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;IRQ_CUI
multiline_comment|/* Default Priorities, Platform may choose differently */
DECL|macro|NO_PRIORITY
mdefine_line|#define&t;NO_PRIORITY&t;0&t;/* Disabled */
DECL|macro|TIMER_PRIORITY
mdefine_line|#define TIMER_PRIORITY&t;2
DECL|macro|RTC_PRIORITY
mdefine_line|#define RTC_PRIORITY&t;TIMER_PRIORITY
DECL|macro|SCIF_PRIORITY
mdefine_line|#define SCIF_PRIORITY&t;3
DECL|macro|INTD_PRIORITY
mdefine_line|#define INTD_PRIORITY&t;3
DECL|macro|IRL3_PRIORITY
mdefine_line|#define&t;IRL3_PRIORITY&t;4
DECL|macro|INTC_PRIORITY
mdefine_line|#define INTC_PRIORITY&t;6
DECL|macro|IRL2_PRIORITY
mdefine_line|#define&t;IRL2_PRIORITY&t;7
DECL|macro|INTB_PRIORITY
mdefine_line|#define INTB_PRIORITY&t;9
DECL|macro|IRL1_PRIORITY
mdefine_line|#define&t;IRL1_PRIORITY&t;10
DECL|macro|INTA_PRIORITY
mdefine_line|#define INTA_PRIORITY&t;12
DECL|macro|IRL0_PRIORITY
mdefine_line|#define&t;IRL0_PRIORITY&t;13
DECL|macro|TOP_PRIORITY
mdefine_line|#define TOP_PRIORITY&t;15
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
id|disable_irq_nosync
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
r_extern
r_int
id|intc_evt_to_irq
(braket
(paren
l_int|0xE20
op_div
l_int|0x20
)paren
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|intc_irq_describe
c_func
(paren
r_char
op_star
id|p
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|irq_canonicalize
mdefine_line|#define irq_canonicalize(irq)&t;(irq)
macro_line|#ifdef CONFIG_SH_CAYMAN
r_int
id|cayman_irq_demux
c_func
(paren
r_int
id|evt
)paren
suffix:semicolon
r_int
id|cayman_irq_describe
c_func
(paren
r_char
op_star
id|p
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|irq_demux
mdefine_line|#define irq_demux(x) cayman_irq_demux(x)
DECL|macro|irq_describe
mdefine_line|#define irq_describe(p, x) cayman_irq_describe(p, x)
macro_line|#else
DECL|macro|irq_demux
mdefine_line|#define irq_demux(x) (intc_evt_to_irq[x])
DECL|macro|irq_describe
mdefine_line|#define irq_describe(p, x) intc_irq_describe(p, x)
macro_line|#endif
multiline_comment|/*&n; * Function for &quot;on chip support modules&quot;.&n; */
multiline_comment|/*&n; * SH-5 supports Priority based interrupts only.&n; * Interrupt priorities are defined at platform level.&n; */
DECL|macro|set_ipr_data
mdefine_line|#define set_ipr_data(a, b, c, d)
DECL|macro|make_ipr_irq
mdefine_line|#define make_ipr_irq(a)
DECL|macro|make_imask_irq
mdefine_line|#define make_imask_irq(a)
macro_line|#endif /* __ASM_SH64_IRQ_H */
eof
