multiline_comment|/*&n; *  include/asm-s390/delay.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/delay.h&quot;&n; *    Copyright (C) 1993 Linus Torvalds&n; *&n; *  Delay routines calling functions in arch/i386/lib/delay.c&n; */
macro_line|#ifndef _S390_DELAY_H
DECL|macro|_S390_DELAY_H
mdefine_line|#define _S390_DELAY_H
r_extern
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
suffix:semicolon
DECL|macro|udelay
mdefine_line|#define udelay(n) __udelay(n)
macro_line|#endif /* defined(_S390_DELAY_H) */
eof
