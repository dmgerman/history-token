multiline_comment|/* irq.h: FRV IRQ definitions&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IRQ_H_
DECL|macro|_ASM_IRQ_H_
mdefine_line|#define _ASM_IRQ_H_
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * the system has an on-CPU PIC and another PIC on the FPGA and other PICs on other peripherals,&n; * so we do some routing in irq-routing.[ch] to reduce the number of false-positives seen by&n; * drivers&n; */
multiline_comment|/* this number is used when no interrupt has been assigned */
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;&t;&t;&t;(-1)
DECL|macro|NR_IRQ_LOG2_ACTIONS_PER_GROUP
mdefine_line|#define NR_IRQ_LOG2_ACTIONS_PER_GROUP&t;5
DECL|macro|NR_IRQ_ACTIONS_PER_GROUP
mdefine_line|#define NR_IRQ_ACTIONS_PER_GROUP&t;(1 &lt;&lt; NR_IRQ_LOG2_ACTIONS_PER_GROUP)
DECL|macro|NR_IRQ_GROUPS
mdefine_line|#define NR_IRQ_GROUPS&t;&t;&t;4
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;&t;(NR_IRQ_ACTIONS_PER_GROUP * NR_IRQ_GROUPS)
multiline_comment|/* probe returns a 32-bit IRQ mask:-/ */
DECL|macro|MIN_PROBE_IRQ
mdefine_line|#define MIN_PROBE_IRQ&t;(NR_IRQS - 32)
DECL|function|irq_canonicalize
r_static
r_inline
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
r_extern
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H_ */
eof
