multiline_comment|/* $Id: softirq.h,v 1.3 2000/02/23 00:41:38 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SOFTIRQ_H
DECL|macro|_ASM_SOFTIRQ_H
mdefine_line|#define _ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|cpu_bh_disable
mdefine_line|#define cpu_bh_disable(cpu)&t;do { local_bh_count(cpu)++; barrier(); } while (0)
DECL|macro|cpu_bh_enable
mdefine_line|#define cpu_bh_enable(cpu)&t;do { barrier(); local_bh_count(cpu)--; } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable(smp_processor_id())
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;cpu_bh_enable(smp_processor_id())
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif /* _ASM_SOFTIRQ_H */
eof
