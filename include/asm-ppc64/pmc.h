multiline_comment|/*&n; * pmc.h&n; * Copyright (C) 2004  David Gibson, IBM Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _PPC64_PMC_H
DECL|macro|_PPC64_PMC_H
mdefine_line|#define _PPC64_PMC_H
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|typedef|perf_irq_t
r_typedef
r_void
(paren
op_star
id|perf_irq_t
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_int
id|reserve_pmc_hardware
c_func
(paren
id|perf_irq_t
id|new_perf_irq
)paren
suffix:semicolon
r_void
id|release_pmc_hardware
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_PMC_H */
eof
