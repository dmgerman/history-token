multiline_comment|/* $Id: btfixup.h,v 1.4 1998/03/09 14:04:43 jj Exp $&n; *  asm-sparc/btfixup.h:    Macros for boot time linking.&n; *&n; *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _SPARC_BTFIXUP_H
DECL|macro|_SPARC_BTFIXUP_H
mdefine_line|#define _SPARC_BTFIXUP_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef MODULE
r_extern
r_int
r_int
id|___illegal_use_of_BTFIXUP_SIMM13_in_module
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|___illegal_use_of_BTFIXUP_SETHI_in_module
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|___illegal_use_of_BTFIXUP_HALF_in_module
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|___illegal_use_of_BTFIXUP_INT_in_module
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BTFIXUP_SIMM13
mdefine_line|#define BTFIXUP_SIMM13(__name) ___illegal_use_of_BTFIXUP_SIMM13_in_module()
DECL|macro|BTFIXUP_HALF
mdefine_line|#define BTFIXUP_HALF(__name) ___illegal_use_of_BTFIXUP_HALF_in_module()
DECL|macro|BTFIXUP_SETHI
mdefine_line|#define BTFIXUP_SETHI(__name) ___illegal_use_of_BTFIXUP_SETHI_in_module()
DECL|macro|BTFIXUP_INT
mdefine_line|#define BTFIXUP_INT(__name) ___illegal_use_of_BTFIXUP_INT_in_module()
DECL|macro|BTFIXUP_BLACKBOX
mdefine_line|#define BTFIXUP_BLACKBOX(__name) ___illegal_use_of_BTFIXUP_BLACKBOX_in_module
macro_line|#else
DECL|macro|BTFIXUP_SIMM13
mdefine_line|#define BTFIXUP_SIMM13(__name) ___sf_##__name()
DECL|macro|BTFIXUP_HALF
mdefine_line|#define BTFIXUP_HALF(__name) ___af_##__name()
DECL|macro|BTFIXUP_SETHI
mdefine_line|#define BTFIXUP_SETHI(__name) ___hf_##__name()
DECL|macro|BTFIXUP_INT
mdefine_line|#define BTFIXUP_INT(__name) ((unsigned int)&amp;___i_##__name)
multiline_comment|/* This must be written in assembly and present in a sethi */
DECL|macro|BTFIXUP_BLACKBOX
mdefine_line|#define BTFIXUP_BLACKBOX(__name) ___b_##__name
macro_line|#endif /* MODULE */
multiline_comment|/* Fixup call xx */
DECL|macro|BTFIXUPDEF_CALL
mdefine_line|#define BTFIXUPDEF_CALL(__type, __name, __args...) &t;&t;&t;&t;&t;&bslash;&n;&t;extern __type ___f_##__name(__args);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned ___fs_##__name[3];
DECL|macro|BTFIXUPDEF_CALL_CONST
mdefine_line|#define BTFIXUPDEF_CALL_CONST(__type, __name, __args...) &t;&t;&t;&t;&bslash;&n;&t;extern __type ___f_##__name(__args) __attribute__((const));&t;&t;&t;&bslash;&n;&t;extern unsigned ___fs_##__name[3];
DECL|macro|BTFIXUP_CALL
mdefine_line|#define BTFIXUP_CALL(__name) ___f_##__name
DECL|macro|BTFIXUPDEF_BLACKBOX
mdefine_line|#define BTFIXUPDEF_BLACKBOX(__name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned ___bs_##__name[2];
multiline_comment|/* Put bottom 13bits into some register variable */
DECL|macro|BTFIXUPDEF_SIMM13
mdefine_line|#define BTFIXUPDEF_SIMM13(__name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned int ___sf_##__name(void) __attribute__((const));&t;&t;&bslash;&n;&t;extern unsigned ___ss_##__name[2];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern __inline__ unsigned int ___sf_##__name(void) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;or %%g0, ___s_&quot; #__name &quot;, %0&quot; : &quot;=r&quot;(ret));&t;&t;&t;&bslash;&n;&t;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|BTFIXUPDEF_SIMM13_INIT
mdefine_line|#define BTFIXUPDEF_SIMM13_INIT(__name,__val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned int ___sf_##__name(void) __attribute__((const));&t;&t;&bslash;&n;&t;extern unsigned ___ss_##__name[2];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern __inline__ unsigned int ___sf_##__name(void) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;or %%g0, ___s_&quot; #__name &quot;__btset_&quot; #__val &quot;, %0&quot; : &quot;=r&quot;(ret));&bslash;&n;&t;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* Put either bottom 13 bits, or upper 22 bits into some register variable&n; * (depending on the value, this will lead into sethi FIX, reg; or&n; * mov FIX, reg; )&n; */
DECL|macro|BTFIXUPDEF_HALF
mdefine_line|#define BTFIXUPDEF_HALF(__name)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned int ___af_##__name(void) __attribute__((const));&t;&t;&bslash;&n;&t;extern unsigned ___as_##__name[2];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern __inline__ unsigned int ___af_##__name(void) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;or %%g0, ___a_&quot; #__name &quot;, %0&quot; : &quot;=r&quot;(ret));&t;&t;&t;&bslash;&n;&t;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|BTFIXUPDEF_HALF_INIT
mdefine_line|#define BTFIXUPDEF_HALF_INIT(__name,__val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned int ___af_##__name(void) __attribute__((const));&t;&t;&bslash;&n;&t;extern unsigned ___as_##__name[2];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern __inline__ unsigned int ___af_##__name(void) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;or %%g0, ___a_&quot; #__name &quot;__btset_&quot; #__val &quot;, %0&quot; : &quot;=r&quot;(ret));&bslash;&n;&t;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* Put upper 22 bits into some register variable */
DECL|macro|BTFIXUPDEF_SETHI
mdefine_line|#define BTFIXUPDEF_SETHI(__name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned int ___hf_##__name(void) __attribute__((const));&t;&t;&bslash;&n;&t;extern unsigned ___hs_##__name[2];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern __inline__ unsigned int ___hf_##__name(void) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;sethi %%hi(___h_&quot; #__name &quot;), %0&quot; : &quot;=r&quot;(ret));&t;&t;&bslash;&n;&t;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|BTFIXUPDEF_SETHI_INIT
mdefine_line|#define BTFIXUPDEF_SETHI_INIT(__name,__val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned int ___hf_##__name(void) __attribute__((const));&t;&t;&bslash;&n;&t;extern unsigned ___hs_##__name[2];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern __inline__ unsigned int ___hf_##__name(void) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;sethi %%hi(___h_&quot; #__name &quot;__btset_&quot; #__val &quot;), %0&quot; : &t;&bslash;&n;&t;&t;&t; &quot;=r&quot;(ret));&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* Put a full 32bit integer into some register variable */
DECL|macro|BTFIXUPDEF_INT
mdefine_line|#define BTFIXUPDEF_INT(__name)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned char ___i_##__name;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern unsigned ___is_##__name[2];
DECL|macro|BTFIXUPCALL_NORM
mdefine_line|#define BTFIXUPCALL_NORM&t;0x00000000&t;&t;&t;/* Always call */
DECL|macro|BTFIXUPCALL_NOP
mdefine_line|#define BTFIXUPCALL_NOP&t;&t;0x01000000&t;&t;&t;/* Possibly optimize to nop */
DECL|macro|BTFIXUPCALL_RETINT
mdefine_line|#define BTFIXUPCALL_RETINT(i)&t;(0x90102000|((i) &amp; 0x1fff))&t;/* Possibly optimize to mov i, %o0 */
DECL|macro|BTFIXUPCALL_ORINT
mdefine_line|#define BTFIXUPCALL_ORINT(i)&t;(0x90122000|((i) &amp; 0x1fff))&t;/* Possibly optimize to or %o0, i, %o0 */
DECL|macro|BTFIXUPCALL_RETO0
mdefine_line|#define BTFIXUPCALL_RETO0&t;0x01000000&t;&t;&t;/* Return first parameter, actually a nop */
DECL|macro|BTFIXUPCALL_ANDNINT
mdefine_line|#define BTFIXUPCALL_ANDNINT(i)&t;(0x902a2000|((i) &amp; 0x1fff))&t;/* Possibly optimize to andn %o0, i, %o0 */
DECL|macro|BTFIXUPCALL_SWAPO0O1
mdefine_line|#define BTFIXUPCALL_SWAPO0O1&t;0xd27a0000&t;&t;&t;/* Possibly optimize to swap [%o0],%o1 */
DECL|macro|BTFIXUPCALL_SWAPO0G0
mdefine_line|#define BTFIXUPCALL_SWAPO0G0&t;0xc07a0000&t;&t;&t;/* Possibly optimize to swap [%o0],%g0 */
DECL|macro|BTFIXUPCALL_SWAPG1G2
mdefine_line|#define BTFIXUPCALL_SWAPG1G2&t;0xc4784000&t;&t;&t;/* Possibly optimize to swap [%g1],%g2 */
DECL|macro|BTFIXUPCALL_STG0O0
mdefine_line|#define BTFIXUPCALL_STG0O0&t;0xc0220000&t;&t;&t;/* Possibly optimize to st %g0,[%o0] */
DECL|macro|BTFIXUPCALL_STO1O0
mdefine_line|#define BTFIXUPCALL_STO1O0&t;0xd2220000&t;&t;&t;/* Possibly optimize to st %o1,[%o0] */
DECL|macro|BTFIXUPSET_CALL
mdefine_line|#define BTFIXUPSET_CALL(__name, __addr, __insn)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___fs_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___fs_##__name[1] = (unsigned long)__addr;&t;&t;&t;&t;&bslash;&n;&t;&t;___fs_##__name[2] = __insn;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPSET_BLACKBOX
mdefine_line|#define BTFIXUPSET_BLACKBOX(__name, __func)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___bs_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___bs_##__name[1] = (unsigned long)__func;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPCOPY_CALL
mdefine_line|#define BTFIXUPCOPY_CALL(__name, __from)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___fs_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___fs_##__name[1] = ___fs_##__from[1];&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___fs_##__name[2] = ___fs_##__from[2];&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPSET_SIMM13
mdefine_line|#define BTFIXUPSET_SIMM13(__name, __val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___ss_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___ss_##__name[1] = (unsigned)__val;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPCOPY_SIMM13
mdefine_line|#define BTFIXUPCOPY_SIMM13(__name, __from)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___ss_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___ss_##__name[1] = ___ss_##__from[1];&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPSET_HALF
mdefine_line|#define BTFIXUPSET_HALF(__name, __val)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___as_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___as_##__name[1] = (unsigned)__val;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPCOPY_HALF
mdefine_line|#define BTFIXUPCOPY_HALF(__name, __from)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___as_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___as_##__name[1] = ___as_##__from[1];&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPSET_SETHI
mdefine_line|#define BTFIXUPSET_SETHI(__name, __val)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___hs_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___hs_##__name[1] = (unsigned)__val;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPCOPY_SETHI
mdefine_line|#define BTFIXUPCOPY_SETHI(__name, __from)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___hs_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___hs_##__name[1] = ___hs_##__from[1];&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPSET_INT
mdefine_line|#define BTFIXUPSET_INT(__name, __val)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___is_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___is_##__name[1] = (unsigned)__val;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPCOPY_INT
mdefine_line|#define BTFIXUPCOPY_INT(__name, __from)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___is_##__name[0] |= 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___is_##__name[1] = ___is_##__from[1];&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|BTFIXUPVAL_CALL
mdefine_line|#define BTFIXUPVAL_CALL(__name)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((unsigned long)___fs_##__name[1])
r_extern
r_void
id|btfixup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* __ASSEMBLY__ */
DECL|macro|BTFIXUP_SETHI
mdefine_line|#define BTFIXUP_SETHI(__name)&t;&t;&t;%hi(___h_ ## __name)
DECL|macro|BTFIXUP_SETHI_INIT
mdefine_line|#define BTFIXUP_SETHI_INIT(__name,__val)&t;%hi(___h_ ## __name ## __btset_ ## __val)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* !(_SPARC_BTFIXUP_H) */
eof
