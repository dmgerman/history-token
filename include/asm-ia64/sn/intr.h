multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_INTR_H
DECL|macro|_ASM_IA64_SN_INTR_H
mdefine_line|#define _ASM_IA64_SN_INTR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/sn2/intr.h&gt;
r_extern
r_void
id|sn_send_IPI_phys
c_func
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|CPU_VECTOR_TO_IRQ
mdefine_line|#define CPU_VECTOR_TO_IRQ(cpuid,vector) (vector)
DECL|macro|SN_CPU_FROM_IRQ
mdefine_line|#define SN_CPU_FROM_IRQ(irq)&t;(0)
DECL|macro|SN_IVEC_FROM_IRQ
mdefine_line|#define SN_IVEC_FROM_IRQ(irq)&t;(irq)
macro_line|#endif /* _ASM_IA64_SN_INTR_H */
eof
