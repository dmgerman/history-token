multiline_comment|/*&n; *  arch/s390x/kernel/delay.c&n; *    Precise Delay Loops for S390&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *&n; *  Derived from &quot;arch/i386/lib/delay.c&quot;&n; *    Copyright (C) 1993 Linus Torvalds&n; *    Copyright (C) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif
DECL|function|__delay
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
multiline_comment|/*&n;         * To end the bloody studid and useless discussion about the&n;         * BogoMips number I took the liberty to define the __delay&n;         * function in a way that that resulting BogoMips number will&n;         * yield the megahertz number of the cpu. The important function&n;         * is udelay and that is done using the tod clock. -- martin.&n;         */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;0: brct %0,0b&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|loops
op_div
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Waits for &squot;usecs&squot; microseconds using the tod clock&n; */
DECL|function|__udelay
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
r_uint64
id|start_cc
comma
id|end_cc
suffix:semicolon
r_if
c_cond
(paren
id|usecs
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;STCK %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|start_cc
)paren
)paren
suffix:semicolon
r_do
(brace
id|asm
r_volatile
(paren
l_string|&quot;STCK %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|end_cc
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|end_cc
op_minus
id|start_cc
)paren
op_div
l_int|4096
)paren
OL
id|usecs
)paren
suffix:semicolon
)brace
eof
