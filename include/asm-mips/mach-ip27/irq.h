multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000, 01, 02, 03 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2001 Kanoj Sarcar&n; */
macro_line|#ifndef __ASM_MACH_IP27_IRQ_H
DECL|macro|__ASM_MACH_IP27_IRQ_H
mdefine_line|#define __ASM_MACH_IP27_IRQ_H
macro_line|#include &lt;asm/sn/arch.h&gt;
multiline_comment|/*&n; * A hardwired interrupt number is completly stupid for this system - a&n; * large configuration might have thousands if not tenthousands of&n; * interrupts.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 256
macro_line|#endif /* __ASM_MACH_IP27_IRQ_H */
eof
