multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 2004 Ralf Baechle&n; */
macro_line|#ifndef _ASM_HAZARDS_H
DECL|macro|_ASM_HAZARDS_H
mdefine_line|#define _ASM_HAZARDS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __ASSEMBLY__
dot
id|macro
id|_ssnop
DECL|variable|$0
id|sll
"$"
l_int|0
comma
"$"
l_int|0
comma
l_int|1
dot
id|endm
dot
id|macro
id|_ehb
DECL|variable|$0
id|sll
"$"
l_int|0
comma
"$"
l_int|0
comma
l_int|3
dot
id|endm
multiline_comment|/*&n; * RM9000 hazards.  When the JTLB is updated by tlbwi or tlbwr, a subsequent&n; * use of the JTLB for instructions should not occur for 4 cpu cycles and use&n; * for data translations should not occur for 3 cpu cycles.&n; */
macro_line|#ifdef CONFIG_CPU_RM9000
dot
id|macro
id|mtc0_tlbw_hazard
dot
id|set
id|push
dot
id|set
id|mips32
id|_ssnop
suffix:semicolon
id|_ssnop
suffix:semicolon
id|_ssnop
suffix:semicolon
id|_ssnop
dot
id|set
id|pop
dot
id|endm
dot
id|macro
id|tlbw_eret_hazard
dot
id|set
id|push
dot
id|set
id|mips32
id|_ssnop
suffix:semicolon
id|_ssnop
suffix:semicolon
id|_ssnop
suffix:semicolon
id|_ssnop
dot
id|set
id|pop
dot
id|endm
macro_line|#else
multiline_comment|/*&n; * The taken branch will result in a two cycle penalty for the two killed&n; * instructions on R4000 / R4400.  Other processors only have a single cycle&n; * hazard so this is nice trick to have an optimal code for a range of&n; * processors.&n; */
dot
id|macro
id|mtc0_tlbw_hazard
id|b
dot
op_plus
l_int|8
dot
id|endm
dot
id|macro
id|tlbw_eret_hazard
dot
id|endm
macro_line|#endif
multiline_comment|/*&n; * mtc0-&gt;mfc0 hazard&n; * The 24K has a 2 cycle mtc0/mfc0 execution hazard.&n; * It is a MIPS32R2 processor so ehb will clear the hazard.&n; */
macro_line|#ifdef CONFIG_CPU_MIPSR2
multiline_comment|/*&n; * Use a macro for ehb unless explicit support for MIPSR2 is enabled&n; */
DECL|macro|irq_enable_hazard
mdefine_line|#define irq_enable_hazard
id|_ehb
DECL|macro|irq_disable_hazard
mdefine_line|#define irq_disable_hazard
id|_ehb
macro_line|#elif defined(CONFIG_CPU_R10000) || defined(CONFIG_CPU_RM9000)
multiline_comment|/*&n; * R10000 rocks - all hazards handled in hardware, so this becomes a nobrainer.&n; */
mdefine_line|#define irq_enable_hazard
mdefine_line|#define irq_disable_hazard
macro_line|#else
multiline_comment|/*&n; * Classic MIPS needs 1 - 3 nops or ssnops&n; */
mdefine_line|#define irq_enable_hazard
mdefine_line|#define irq_disable_hazard&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_ssnop; _ssnop; _ssnop
macro_line|#endif
macro_line|#else /* __ASSEMBLY__ */
id|__asm__
c_func
(paren
l_string|&quot;&t;.macro&t;_ssnop&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;sll&t;$0, $2, 1&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.macro&t;_ehb&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;sll&t;$0, $0, 3&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_RM9000
multiline_comment|/*&n; * RM9000 hazards.  When the JTLB is updated by tlbwi or tlbwr, a subsequent&n; * use of the JTLB for instructions should not occur for 4 cpu cycles and use&n; * for data translations should not occur for 3 cpu cycles.&n; */
mdefine_line|#define mtc0_tlbw_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;_ssnop; _ssnop; _ssnop; _ssnop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips0&quot;)
mdefine_line|#define tlbw_use_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;_ssnop; _ssnop; _ssnop; _ssnop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tmips0&quot;)
macro_line|#else
multiline_comment|/*&n; * Overkill warning ...&n; */
mdefine_line|#define mtc0_tlbw_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set noreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop; nop; nop; nop; nop; nop;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set reorder&bslash;n&bslash;t&quot;)
mdefine_line|#define tlbw_use_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set noreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop; nop; nop; nop; nop; nop;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set reorder&bslash;n&bslash;t&quot;)
macro_line|#endif
multiline_comment|/*&n; * mtc0-&gt;mfc0 hazard&n; * The 24K has a 2 cycle mtc0/mfc0 execution hazard.&n; * It is a MIPS32R2 processor so ehb will clear the hazard.&n; */
macro_line|#ifdef CONFIG_CPU_MIPSR2
multiline_comment|/*&n; * Use a macro for ehb unless explicit support for MIPSR2 is enabled&n; */
id|__asm__
c_func
(paren
l_string|&quot;&t;.macro&bslash;tirq_enable_hazard&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;_ehb&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.macro&bslash;tirq_disable_hazard&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;_ehb&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&quot;
)paren
suffix:semicolon
mdefine_line|#define irq_enable_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;_ehb&bslash;t&bslash;t&bslash;t&bslash;t# irq_enable_hazard&quot;)
mdefine_line|#define irq_disable_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;_ehb&bslash;t&bslash;t&bslash;t&bslash;t# irq_disable_hazard&quot;)
macro_line|#elif defined(CONFIG_CPU_R10000) || defined(CONFIG_CPU_RM9000)
multiline_comment|/*&n; * R10000 rocks - all hazards handled in hardware, so this becomes a nobrainer.&n; */
id|__asm__
c_func
(paren
l_string|&quot;&t;.macro&bslash;tirq_enable_hazard&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.macro&bslash;tirq_disable_hazard&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&quot;
)paren
suffix:semicolon
mdefine_line|#define irq_enable_hazard()&t;do { } while (0)
mdefine_line|#define irq_disable_hazard()&t;do { } while (0)
macro_line|#else
multiline_comment|/*&n; * Default for classic MIPS processors.  Assume worst case hazards but don&squot;t&n; * care about the irq_enable_hazard - sooner or later the hardware will&n; * enable it and we don&squot;t care when exactly.&n; */
id|__asm__
c_func
(paren
l_string|&quot;&t;#&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;# There is a hazard but we do not care&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;#&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.macro&bslash;tirq_enable_hazard&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.macro&bslash;tirq_disable_hazard&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;_ssnop; _ssnop; _ssnop&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.endm&quot;
)paren
suffix:semicolon
mdefine_line|#define irq_enable_hazard()&t;do { } while (0)
mdefine_line|#define irq_disable_hazard()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;_ssnop; _ssnop; _ssnop;&bslash;t&bslash;t# irq_disable_hazard&quot;)
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_HAZARDS_H */
eof
