multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 2004 Ralf Baechle&n; */
macro_line|#ifndef _ASM_HAZARDS_H
DECL|macro|_ASM_HAZARDS_H
mdefine_line|#define _ASM_HAZARDS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/*&n; * RM9000 hazards.  When the JTLB is updated by tlbwi or tlbwr, a subsequent&n; * use of the JTLB for instructions should not occur for 4 cpu cycles and use&n; * for data translations should not occur for 3 cpu cycles.&n; */
macro_line|#ifdef CONFIG_CPU_RM9000
DECL|macro|mtc0_tlbw_hazard
mdefine_line|#define mtc0_tlbw_hazard&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;push;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;mips32;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ssnop; ssnop; ssnop; ssnop;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;pop
DECL|macro|tlbw_eret_hazard
mdefine_line|#define tlbw_eret_hazard&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;push;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;mips32;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ssnop; ssnop; ssnop; ssnop;&t;&t;&t;&t;&t;&bslash;&n;&t;.set&t;pop
macro_line|#else
multiline_comment|/*&n; * The taken branch will result in a two cycle penalty for the two killed&n; * instructions on R4000 / R4400.  Other processors only have a single cycle&n; * hazard so this is nice trick to have an optimal code for a range of&n; * processors.&n; */
DECL|macro|mtc0_tlbw_hazard
mdefine_line|#define mtc0_tlbw_hazard&t;&t;&t;&t;&t;&t;&bslash;&n;&t;b&t;. + 8
DECL|macro|tlbw_eret_hazard
mdefine_line|#define tlbw_eret_hazard
macro_line|#endif
macro_line|#else /* __ASSEMBLY__ */
multiline_comment|/*&n; * RM9000 hazards.  When the JTLB is updated by tlbwi or tlbwr, a subsequent&n; * use of the JTLB for instructions should not occur for 4 cpu cycles and use&n; * for data translations should not occur for 3 cpu cycles.&n; */
macro_line|#ifdef CONFIG_CPU_RM9000
DECL|macro|mtc0_tlbw_hazard
mdefine_line|#define mtc0_tlbw_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ssnop; ssnop; ssnop; ssnop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips0&quot;)
DECL|macro|tlbw_use_hazard
mdefine_line|#define tlbw_use_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ssnop; ssnop; ssnop; ssnop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips0&quot;)
macro_line|#else
multiline_comment|/*&n; * Overkill warning ...&n; */
DECL|macro|mtc0_tlbw_hazard
mdefine_line|#define mtc0_tlbw_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set noreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop; nop; nop; nop; nop; nop;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set reorder&bslash;n&bslash;t&quot;)
DECL|macro|tlbw_use_hazard
mdefine_line|#define tlbw_use_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set noreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop; nop; nop; nop; nop; nop;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set reorder&bslash;n&bslash;t&quot;)
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_HAZARDS_H */
eof
