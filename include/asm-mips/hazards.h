multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Ralf Baechle&n; */
macro_line|#ifndef _ASM_HAZARDS_H
DECL|macro|_ASM_HAZARDS_H
mdefine_line|#define _ASM_HAZARDS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/*&n; * RM9000 hazards.  When the JTLB is updated by tlbwi or tlbwr, a subsequent&n; * use of the JTLB for instructions should not occur for 4 cpu cycles and use&n; * for data translations should not occur for 3 cpu cycles.&n; */
macro_line|#ifdef CONFIG_CPU_RM9000
DECL|macro|rm9000_tlb_hazard
mdefine_line|#define rm9000_tlb_hazard&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;push;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;mips32;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ssnop; ssnop; ssnop; ssnop;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;pop
macro_line|#else
DECL|macro|rm9000_tlb_hazard
mdefine_line|#define rm9000_tlb_hazard
macro_line|#endif
macro_line|#else
multiline_comment|/*&n; * RM9000 hazards.  When the JTLB is updated by tlbwi or tlbwr, a subsequent&n; * use of the JTLB for instructions should not occur for 4 cpu cycles and use&n; * for data translations should not occur for 3 cpu cycles.&n; */
macro_line|#ifdef CONFIG_CPU_RM9000
DECL|macro|rm9000_tlb_hazard
mdefine_line|#define rm9000_tlb_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ssnop; ssnop; ssnop; ssnop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips0&quot;)
macro_line|#else
DECL|macro|rm9000_tlb_hazard
mdefine_line|#define rm9000_tlb_hazard() do { } while (0)
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _ASM_HAZARDS_H */
eof
