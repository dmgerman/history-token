multiline_comment|/* irc-regs.h: on-chip interrupt controller registers&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IRC_REGS
DECL|macro|_ASM_IRC_REGS
mdefine_line|#define _ASM_IRC_REGS
DECL|macro|__reg
mdefine_line|#define __reg(ADDR) (*(volatile unsigned long *)(ADDR))
DECL|macro|__get_TM0
mdefine_line|#define __get_TM0()&t;({ __reg(0xfeff9800); })
DECL|macro|__get_TM1
mdefine_line|#define __get_TM1()&t;({ __reg(0xfeff9808); })
DECL|macro|__set_TM1
mdefine_line|#define __set_TM1(V)&t;do { __reg(0xfeff9808) = (V); mb(); } while(0)
DECL|macro|__set_TM1x
mdefine_line|#define __set_TM1x(XI,V)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int shift = (XI) * 2 + 16;&t;&t;&bslash;&n;&t;unsigned long tm1 = __reg(0xfeff9808);&t;&bslash;&n;&t;tm1 &amp;= ~(0x3 &lt;&lt; shift);&t;&t;&t;&bslash;&n;&t;tm1 |= (V) &lt;&lt; shift;&t;&t;&t;&bslash;&n;&t;__reg(0xfeff9808) = tm1;&t;&t;&bslash;&n;&t;mb();&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|__get_RS
mdefine_line|#define __get_RS(C)&t;({ (__reg(0xfeff9810) &gt;&gt; ((C)+16)) &amp; 1; })
DECL|macro|__clr_RC
mdefine_line|#define __clr_RC(C)&t;do { __reg(0xfeff9818) = 1 &lt;&lt; ((C)+16); mb(); } while(0)
DECL|macro|__get_MASK
mdefine_line|#define __get_MASK(C)&t;({ (__reg(0xfeff9820) &gt;&gt; ((C)+16)) &amp; 1; })
DECL|macro|__set_MASK
mdefine_line|#define __set_MASK(C)&t;do { __reg(0xfeff9820) |=  1 &lt;&lt; ((C)+16); mb(); } while(0)
DECL|macro|__clr_MASK
mdefine_line|#define __clr_MASK(C)&t;do { __reg(0xfeff9820) &amp;=  ~(1 &lt;&lt; ((C)+16)); mb(); } while(0)
DECL|macro|__get_MASK_all
mdefine_line|#define __get_MASK_all() __get_MASK(0)
DECL|macro|__set_MASK_all
mdefine_line|#define __set_MASK_all() __set_MASK(0)
DECL|macro|__clr_MASK_all
mdefine_line|#define __clr_MASK_all() __clr_MASK(0)
DECL|macro|__get_IRL
mdefine_line|#define __get_IRL()&t;({ (__reg(0xfeff9828) &gt;&gt; 16) &amp; 0xf; })
DECL|macro|__clr_IRL
mdefine_line|#define __clr_IRL()&t;do { __reg(0xfeff9828) = 0x100000; mb(); } while(0)
DECL|macro|__get_IRR
mdefine_line|#define __get_IRR(N)&t;({ __reg(0xfeff9840 + (N) * 8); })
DECL|macro|__set_IRR
mdefine_line|#define __set_IRR(N,V)&t;do { __reg(0xfeff9840 + (N) * 8) = (V); } while(0)
DECL|macro|__get_IITMR
mdefine_line|#define __get_IITMR(N)&t;({ __reg(0xfeff9880 + (N) * 8); })
DECL|macro|__set_IITMR
mdefine_line|#define __set_IITMR(N,V) do { __reg(0xfeff9880 + (N) * 8) = (V); } while(0)
macro_line|#endif /* _ASM_IRC_REGS */
eof
