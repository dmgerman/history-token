multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2003 by Ralf Baechle&n; * Copyright (C) 1996 by Paul M. Antoine&n; * Copyright (C) 1999 Silicon Graphics&n; * Copyright (C) 2000 MIPS Technologies, Inc.&n; */
macro_line|#ifndef _ASM_INTERRUPT_H
DECL|macro|_ASM_INTERRUPT_H
mdefine_line|#define _ASM_INTERRUPT_H
macro_line|#include &lt;asm/hazards.h&gt;
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_enable&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,0x1f&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,0x1e&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;irq_enable_hazard&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|function|local_irq_enable
r_static
r_inline
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;local_irq_enable&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * For cli() we have to insert nops to make sure that the new value&n; * has actually arrived in the status register before the end of this&n; * macro.&n; * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs&n; * no nops at all.&n; */
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_disable&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;irq_disable_hazard&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|function|local_irq_disable
r_static
r_inline
r_void
id|local_irq_disable
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;local_irq_disable&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_save_flags flags&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t&bslash;&bslash;flags, $12&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;local_save_flags %0&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x))
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_save result&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t&bslash;&bslash;result, $12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1, &bslash;&bslash;result, 1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1, 1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1, $12&bslash;n&bslash;t&quot;
l_string|&quot;irq_disable_hazard&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;local_irq_save&bslash;t%0&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no inputs */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;)
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_restore flags&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1, $12&bslash;n&bslash;t&quot;
l_string|&quot;andi&bslash;t&bslash;&bslash;flags, 1&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1, 1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1, 1&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t&bslash;&bslash;flags, $1&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t&bslash;&bslash;flags, $12&bslash;n&bslash;t&quot;
l_string|&quot;irq_disable_hazard&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __tmp1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;local_irq_restore&bslash;t%0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (__tmp1)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (flags)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;!(flags &amp; 1);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* _ASM_INTERRUPT_H */
eof
