multiline_comment|/* $Id: head.h,v 1.30 1997/08/08 08:34:33 jj Exp $ */
macro_line|#ifndef _SPARC64_HEAD_H
DECL|macro|_SPARC64_HEAD_H
mdefine_line|#define _SPARC64_HEAD_H
macro_line|#include &lt;asm/pstate.h&gt;
DECL|macro|KERNBASE
mdefine_line|#define KERNBASE&t;0x400000
DECL|macro|PTREGS_OFF
mdefine_line|#define&t;PTREGS_OFF&t;(STACK_BIAS + STACKFRAME_SZ)
DECL|macro|__CHEETAH_ID
mdefine_line|#define __CHEETAH_ID&t;0x003e0014
DECL|macro|__JALAPENO_ID
mdefine_line|#define __JALAPENO_ID&t;0x003e0016
DECL|macro|CHEETAH_MANUF
mdefine_line|#define CHEETAH_MANUF&t;&t;0x003e
DECL|macro|CHEETAH_IMPL
mdefine_line|#define CHEETAH_IMPL&t;&t;0x0014
DECL|macro|CHEETAH_PLUS_IMPL
mdefine_line|#define CHEETAH_PLUS_IMPL&t;0x0015
DECL|macro|JALAPENO_IMPL
mdefine_line|#define JALAPENO_IMPL&t;&t;0x0016
DECL|macro|BRANCH_IF_CHEETAH_BASE
mdefine_line|#define BRANCH_IF_CHEETAH_BASE(tmp1,tmp2,label)&t;&bslash;&n;&t;rdpr&t;%ver, %tmp1;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(__CHEETAH_ID), %tmp2;&t;&bslash;&n;&t;srlx&t;%tmp1, 32, %tmp1;&t;&t;&bslash;&n;&t;or&t;%tmp2, %lo(__CHEETAH_ID), %tmp2;&bslash;&n;&t;cmp&t;%tmp1, %tmp2;&t;&t;&t;&bslash;&n;&t;be,pn&t;%icc, label;&t;&t;&t;&bslash;&n;&t; nop;
DECL|macro|BRANCH_IF_JALAPENO
mdefine_line|#define BRANCH_IF_JALAPENO(tmp1,tmp2,label)&t;&bslash;&n;&t;rdpr&t;%ver, %tmp1;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(__JALAPENO_ID), %tmp2;&t;&bslash;&n;&t;srlx&t;%tmp1, 32, %tmp1;&t;&t;&bslash;&n;&t;or&t;%tmp2, %lo(__JALAPENO_ID), %tmp2;&bslash;&n;&t;cmp&t;%tmp1, %tmp2;&t;&t;&t;&bslash;&n;&t;be,pn&t;%icc, label;&t;&t;&t;&bslash;&n;&t; nop;
DECL|macro|BRANCH_IF_CHEETAH_PLUS_OR_FOLLOWON
mdefine_line|#define BRANCH_IF_CHEETAH_PLUS_OR_FOLLOWON(tmp1,tmp2,label)&t;&bslash;&n;&t;rdpr&t;%ver, %tmp1;&t;&t;&t;&bslash;&n;&t;srlx&t;%tmp1, (32 + 16), %tmp2;&t;&bslash;&n;&t;cmp&t;%tmp2, CHEETAH_MANUF;&t;&t;&bslash;&n;&t;bne,pt&t;%xcc, 99f;&t;&t;&t;&bslash;&n;&t; sllx&t;%tmp1, 16, %tmp1;&t;&t;&bslash;&n;&t;srlx&t;%tmp1, (32 + 16), %tmp2;&t;&bslash;&n;&t;cmp&t;%tmp2, CHEETAH_PLUS_IMPL;&t;&bslash;&n;&t;bgeu,pt&t;%xcc, label;&t;&t;&t;&bslash;&n;99:&t; nop;
DECL|macro|BRANCH_IF_ANY_CHEETAH
mdefine_line|#define BRANCH_IF_ANY_CHEETAH(tmp1,tmp2,label)&t;&bslash;&n;&t;rdpr&t;%ver, %tmp1;&t;&t;&t;&bslash;&n;&t;srlx&t;%tmp1, (32 + 16), %tmp2;&t;&bslash;&n;&t;cmp&t;%tmp2, CHEETAH_MANUF;&t;&t;&bslash;&n;&t;bne,pt&t;%xcc, 99f;&t;&t;&t;&bslash;&n;&t; sllx&t;%tmp1, 16, %tmp1;&t;&t;&bslash;&n;&t;srlx&t;%tmp1, (32 + 16), %tmp2;&t;&bslash;&n;&t;cmp&t;%tmp2, CHEETAH_IMPL;&t;&t;&bslash;&n;&t;bgeu,pt&t;%xcc, label;&t;&t;&t;&bslash;&n;99:&t; nop;
macro_line|#endif /* !(_SPARC64_HEAD_H) */
eof
