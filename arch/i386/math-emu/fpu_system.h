multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_system.h                                                             |&n; |                                                                           |&n; | Copyright (C) 1992,1994,1997                                              |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@suburbia.net             |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_SYSTEM_H
DECL|macro|_FPU_SYSTEM_H
mdefine_line|#define _FPU_SYSTEM_H
multiline_comment|/* system dependent definitions */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* This sets the pointer FPU_info to point to the argument part&n;   of the stack frame of math_emulate() */
DECL|macro|SETUP_DATA_AREA
mdefine_line|#define SETUP_DATA_AREA(arg)&t;FPU_info = (struct info *) &amp;arg
DECL|macro|LDT_DESCRIPTOR
mdefine_line|#define LDT_DESCRIPTOR(s)&t;(((struct desc_struct *)current-&gt;mm-&gt;context.segments)[(s) &gt;&gt; 3])
DECL|macro|SEG_D_SIZE
mdefine_line|#define SEG_D_SIZE(x)&t;&t;((x).b &amp; (3 &lt;&lt; 21))
DECL|macro|SEG_G_BIT
mdefine_line|#define SEG_G_BIT(x)&t;&t;((x).b &amp; (1 &lt;&lt; 23))
DECL|macro|SEG_GRANULARITY
mdefine_line|#define SEG_GRANULARITY(x)&t;(((x).b &amp; (1 &lt;&lt; 23)) ? 4096 : 1)
DECL|macro|SEG_286_MODE
mdefine_line|#define SEG_286_MODE(x)&t;&t;((x).b &amp; ( 0xff000000 | 0xf0000 | (1 &lt;&lt; 23)))
DECL|macro|SEG_BASE_ADDR
mdefine_line|#define SEG_BASE_ADDR(s)&t;(((s).b &amp; 0xff000000) &bslash;&n;&t;&t;&t;&t; | (((s).b &amp; 0xff) &lt;&lt; 16) | ((s).a &gt;&gt; 16))
DECL|macro|SEG_LIMIT
mdefine_line|#define SEG_LIMIT(s)&t;&t;(((s).b &amp; 0xff0000) | ((s).a &amp; 0xffff))
DECL|macro|SEG_EXECUTE_ONLY
mdefine_line|#define SEG_EXECUTE_ONLY(s)&t;(((s).b &amp; ((1 &lt;&lt; 11) | (1 &lt;&lt; 9))) == (1 &lt;&lt; 11))
DECL|macro|SEG_WRITE_PERM
mdefine_line|#define SEG_WRITE_PERM(s)&t;(((s).b &amp; ((1 &lt;&lt; 11) | (1 &lt;&lt; 9))) == (1 &lt;&lt; 9))
DECL|macro|SEG_EXPAND_DOWN
mdefine_line|#define SEG_EXPAND_DOWN(s)&t;(((s).b &amp; ((1 &lt;&lt; 11) | (1 &lt;&lt; 10))) &bslash;&n;&t;&t;&t;&t; == (1 &lt;&lt; 10))
DECL|macro|I387
mdefine_line|#define I387&t;&t;&t;(current-&gt;thread.i387)
DECL|macro|FPU_info
mdefine_line|#define FPU_info&t;&t;(I387.soft.info)
DECL|macro|FPU_CS
mdefine_line|#define FPU_CS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___cs))
DECL|macro|FPU_SS
mdefine_line|#define FPU_SS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___ss))
DECL|macro|FPU_DS
mdefine_line|#define FPU_DS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___ds))
DECL|macro|FPU_EAX
mdefine_line|#define FPU_EAX&t;&t;&t;(FPU_info-&gt;___eax)
DECL|macro|FPU_EFLAGS
mdefine_line|#define FPU_EFLAGS&t;&t;(FPU_info-&gt;___eflags)
DECL|macro|FPU_EIP
mdefine_line|#define FPU_EIP&t;&t;&t;(FPU_info-&gt;___eip)
DECL|macro|FPU_ORIG_EIP
mdefine_line|#define FPU_ORIG_EIP&t;&t;(FPU_info-&gt;___orig_eip)
DECL|macro|FPU_lookahead
mdefine_line|#define FPU_lookahead           (I387.soft.lookahead)
multiline_comment|/* nz if ip_offset and cs_selector are not to be set for the current&n;   instruction. */
DECL|macro|no_ip_update
mdefine_line|#define no_ip_update&t;&t;(*(u_char *)&amp;(I387.soft.no_update))
DECL|macro|FPU_rm
mdefine_line|#define FPU_rm&t;&t;&t;(*(u_char *)&amp;(I387.soft.rm))
multiline_comment|/* Number of bytes of data which can be legally accessed by the current&n;   instruction. This only needs to hold a number &lt;= 108, so a byte will do. */
DECL|macro|access_limit
mdefine_line|#define access_limit&t;&t;(*(u_char *)&amp;(I387.soft.alimit))
DECL|macro|partial_status
mdefine_line|#define partial_status&t;&t;(I387.soft.swd)
DECL|macro|control_word
mdefine_line|#define control_word&t;&t;(I387.soft.cwd)
DECL|macro|fpu_tag_word
mdefine_line|#define fpu_tag_word&t;&t;(I387.soft.twd)
DECL|macro|registers
mdefine_line|#define registers&t;&t;(I387.soft.st_space)
DECL|macro|top
mdefine_line|#define top&t;&t;&t;(I387.soft.ftop)
DECL|macro|instruction_address
mdefine_line|#define instruction_address&t;(*(struct address *)&amp;I387.soft.fip)
DECL|macro|operand_address
mdefine_line|#define operand_address&t;&t;(*(struct address *)&amp;I387.soft.foo)
DECL|macro|FPU_verify_area
mdefine_line|#define FPU_verify_area(x,y,z)&t;if ( verify_area(x,y,z) ) &bslash;&n;&t;&t;&t;&t;math_abort(FPU_info,SIGSEGV)
DECL|macro|FPU_IGNORE_CODE_SEGV
macro_line|#undef FPU_IGNORE_CODE_SEGV
macro_line|#ifdef FPU_IGNORE_CODE_SEGV
multiline_comment|/* verify_area() is very expensive, and causes the emulator to run&n;   about 20% slower if applied to the code. Anyway, errors due to bad&n;   code addresses should be much rarer than errors due to bad data&n;   addresses. */
DECL|macro|FPU_code_verify_area
mdefine_line|#define&t;FPU_code_verify_area(z)
macro_line|#else
multiline_comment|/* A simpler test than verify_area() can probably be done for&n;   FPU_code_verify_area() because the only possible error is to step&n;   past the upper boundary of a legal code area. */
DECL|macro|FPU_code_verify_area
mdefine_line|#define&t;FPU_code_verify_area(z) FPU_verify_area(VERIFY_READ,(void *)FPU_EIP,z)
macro_line|#endif
DECL|macro|FPU_get_user
mdefine_line|#define FPU_get_user(x,y)       get_user((x),(y))
DECL|macro|FPU_put_user
mdefine_line|#define FPU_put_user(x,y)       put_user((x),(y))
macro_line|#endif
eof
