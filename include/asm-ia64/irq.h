macro_line|#ifndef _ASM_IA64_IRQ_H
DECL|macro|_ASM_IA64_IRQ_H
mdefine_line|#define _ASM_IA64_IRQ_H
multiline_comment|/*&n; * Copyright (C) 1999-2000, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * 11/24/98&t;S.Eranian &t;updated TIMER_IRQ and irq_canonicalize&n; * 01/20/99&t;S.Eranian&t;added keyboard interrupt&n; * 02/29/00     D.Mosberger&t;moved most things into hw_irq.h&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;256
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS&t;NR_IRQS
r_static
id|__inline__
r_int
DECL|function|irq_canonicalize
id|irq_canonicalize
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; * We do the legacy thing here of pretending that irqs &lt; 16&n;&t; * are 8259 irqs.  This really shouldn&squot;t be necessary at all,&n;&t; * but we keep it here as serial.c still uses it...&n;&t; */
r_return
(paren
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
)paren
suffix:semicolon
)brace
r_extern
r_void
id|disable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq_nosync
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|set_irq_affinity_info
(paren
r_int
r_int
id|irq
comma
r_int
id|dest
comma
r_int
id|redir
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_IRQ_H */
eof
