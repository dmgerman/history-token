multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_emu.h                                                                |&n; |                                                                           |&n; | Copyright (C) 1992,1993,1994,1997                                         |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@suburbia.net             |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_EMU_H_
DECL|macro|_FPU_EMU_H_
mdefine_line|#define _FPU_EMU_H_
multiline_comment|/*&n; * Define PECULIAR_486 to get a closer approximation to 80486 behaviour,&n; * rather than behaviour which appears to be cleaner.&n; * This is a matter of opinion: for all I know, the 80486 may simply&n; * be complying with the IEEE spec. Maybe one day I&squot;ll get to see the&n; * spec...&n; */
DECL|macro|PECULIAR_486
mdefine_line|#define PECULIAR_486
macro_line|#ifdef __ASSEMBLY__
macro_line|#include &quot;fpu_asm.h&quot;
DECL|macro|Const
mdefine_line|#define&t;Const(x)&t;$##x
macro_line|#else
DECL|macro|Const
mdefine_line|#define&t;Const(x)&t;x
macro_line|#endif
DECL|macro|EXP_BIAS
mdefine_line|#define EXP_BIAS&t;Const(0)
DECL|macro|EXP_OVER
mdefine_line|#define EXP_OVER&t;Const(0x4000)    /* smallest invalid large exponent */
DECL|macro|EXP_UNDER
mdefine_line|#define&t;EXP_UNDER&t;Const(-0x3fff)   /* largest invalid small exponent */
DECL|macro|EXP_WAY_UNDER
mdefine_line|#define EXP_WAY_UNDER   Const(-0x6000)   /* Below the smallest denormal, but&n;&t;&t;&t;&t;&t;    still a 16 bit nr. */
DECL|macro|EXP_Infinity
mdefine_line|#define EXP_Infinity    EXP_OVER
DECL|macro|EXP_NaN
mdefine_line|#define EXP_NaN         EXP_OVER
DECL|macro|EXTENDED_Ebias
mdefine_line|#define EXTENDED_Ebias Const(0x3fff)
DECL|macro|EXTENDED_Emin
mdefine_line|#define EXTENDED_Emin (-0x3ffe)  /* smallest valid exponent */
DECL|macro|SIGN_POS
mdefine_line|#define SIGN_POS&t;Const(0)
DECL|macro|SIGN_NEG
mdefine_line|#define SIGN_NEG&t;Const(0x80)
DECL|macro|SIGN_Positive
mdefine_line|#define SIGN_Positive&t;Const(0)
DECL|macro|SIGN_Negative
mdefine_line|#define SIGN_Negative&t;Const(0x8000)
multiline_comment|/* Keep the order TAG_Valid, TAG_Zero, TW_Denormal */
multiline_comment|/* The following fold to 2 (Special) in the Tag Word */
DECL|macro|TW_Denormal
mdefine_line|#define TW_Denormal     Const(4)        /* De-normal */
DECL|macro|TW_Infinity
mdefine_line|#define TW_Infinity&t;Const(5)&t;/* + or - infinity */
DECL|macro|TW_NaN
mdefine_line|#define&t;TW_NaN&t;&t;Const(6)&t;/* Not a Number */
DECL|macro|TW_Unsupported
mdefine_line|#define&t;TW_Unsupported&t;Const(7)&t;/* Not supported by an 80486 */
DECL|macro|TAG_Valid
mdefine_line|#define TAG_Valid&t;Const(0)&t;/* valid */
DECL|macro|TAG_Zero
mdefine_line|#define TAG_Zero&t;Const(1)&t;/* zero */
DECL|macro|TAG_Special
mdefine_line|#define TAG_Special&t;Const(2)&t;/* De-normal, + or - infinity,&n;&t;&t;&t;&t;&t;   or Not a Number */
DECL|macro|TAG_Empty
mdefine_line|#define TAG_Empty&t;Const(3)&t;/* empty */
DECL|macro|LOADED_DATA
mdefine_line|#define LOADED_DATA&t;Const(10101)&t;/* Special st() number to identify&n;&t;&t;&t;&t;&t;   loaded data (not on stack). */
multiline_comment|/* A few flags (must be &gt;= 0x10). */
DECL|macro|REV
mdefine_line|#define REV             0x10
DECL|macro|DEST_RM
mdefine_line|#define DEST_RM         0x20
DECL|macro|LOADED
mdefine_line|#define LOADED          0x40
DECL|macro|FPU_Exception
mdefine_line|#define FPU_Exception   Const(0x80000000)   /* Added to tag returns. */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &lt;asm/sigcontext.h&gt;   /* for struct _fpstate */
macro_line|#include &lt;asm/math_emu.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n;#define RE_ENTRANT_CHECKING&n; */
macro_line|#ifdef RE_ENTRANT_CHECKING
r_extern
id|u_char
id|emulating
suffix:semicolon
DECL|macro|RE_ENTRANT_CHECK_OFF
macro_line|#  define RE_ENTRANT_CHECK_OFF emulating = 0
DECL|macro|RE_ENTRANT_CHECK_ON
macro_line|#  define RE_ENTRANT_CHECK_ON emulating = 1
macro_line|#else
DECL|macro|RE_ENTRANT_CHECK_OFF
macro_line|#  define RE_ENTRANT_CHECK_OFF
DECL|macro|RE_ENTRANT_CHECK_ON
macro_line|#  define RE_ENTRANT_CHECK_ON
macro_line|#endif RE_ENTRANT_CHECKING
DECL|macro|FWAIT_OPCODE
mdefine_line|#define FWAIT_OPCODE 0x9b
DECL|macro|OP_SIZE_PREFIX
mdefine_line|#define OP_SIZE_PREFIX 0x66
DECL|macro|ADDR_SIZE_PREFIX
mdefine_line|#define ADDR_SIZE_PREFIX 0x67
DECL|macro|PREFIX_CS
mdefine_line|#define PREFIX_CS 0x2e
DECL|macro|PREFIX_DS
mdefine_line|#define PREFIX_DS 0x3e
DECL|macro|PREFIX_ES
mdefine_line|#define PREFIX_ES 0x26
DECL|macro|PREFIX_SS
mdefine_line|#define PREFIX_SS 0x36
DECL|macro|PREFIX_FS
mdefine_line|#define PREFIX_FS 0x64
DECL|macro|PREFIX_GS
mdefine_line|#define PREFIX_GS 0x65
DECL|macro|PREFIX_REPE
mdefine_line|#define PREFIX_REPE 0xf3
DECL|macro|PREFIX_REPNE
mdefine_line|#define PREFIX_REPNE 0xf2
DECL|macro|PREFIX_LOCK
mdefine_line|#define PREFIX_LOCK 0xf0
DECL|macro|PREFIX_CS_
mdefine_line|#define PREFIX_CS_ 1
DECL|macro|PREFIX_DS_
mdefine_line|#define PREFIX_DS_ 2
DECL|macro|PREFIX_ES_
mdefine_line|#define PREFIX_ES_ 3
DECL|macro|PREFIX_FS_
mdefine_line|#define PREFIX_FS_ 4
DECL|macro|PREFIX_GS_
mdefine_line|#define PREFIX_GS_ 5
DECL|macro|PREFIX_SS_
mdefine_line|#define PREFIX_SS_ 6
DECL|macro|PREFIX_DEFAULT
mdefine_line|#define PREFIX_DEFAULT 7
DECL|struct|address
r_struct
id|address
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|selector
r_int
r_int
id|selector
suffix:colon
l_int|16
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|11
suffix:semicolon
DECL|member|empty
r_int
r_int
id|empty
suffix:colon
l_int|5
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fpu__reg
r_struct
id|fpu__reg
(brace
DECL|member|sigl
r_int
id|sigl
suffix:semicolon
DECL|member|sigh
r_int
id|sigh
suffix:semicolon
DECL|member|exp
r_int
id|exp
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|FUNC
r_typedef
r_void
(paren
op_star
id|FUNC
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|FPU_REG
r_typedef
r_struct
id|fpu__reg
id|FPU_REG
suffix:semicolon
DECL|typedef|FUNC_ST0
r_typedef
r_void
(paren
op_star
id|FUNC_ST0
)paren
(paren
id|FPU_REG
op_star
id|st0_ptr
comma
id|u_char
id|st0_tag
)paren
suffix:semicolon
DECL|member|address_size
DECL|member|operand_size
DECL|member|segment
r_typedef
r_struct
(brace
id|u_char
id|address_size
comma
id|operand_size
comma
id|segment
suffix:semicolon
)brace
DECL|typedef|overrides
id|overrides
suffix:semicolon
multiline_comment|/* This structure is 32 bits: */
DECL|member|override
r_typedef
r_struct
(brace
id|overrides
id|override
suffix:semicolon
DECL|member|default_mode
DECL|typedef|fpu_addr_modes
id|u_char
id|default_mode
suffix:semicolon
)brace
id|fpu_addr_modes
suffix:semicolon
multiline_comment|/* PROTECTED has a restricted meaning in the emulator; it is used&n;   to signal that the emulator needs to do special things to ensure&n;   that protection is respected in a segmented model. */
DECL|macro|PROTECTED
mdefine_line|#define PROTECTED 4
DECL|macro|SIXTEEN
mdefine_line|#define SIXTEEN   1         /* We rely upon this being 1 (true) */
DECL|macro|VM86
mdefine_line|#define VM86      SIXTEEN
DECL|macro|PM16
mdefine_line|#define PM16      (SIXTEEN | PROTECTED)
DECL|macro|SEG32
mdefine_line|#define SEG32     PROTECTED
r_extern
id|u_char
r_const
id|data_sizes_16
(braket
l_int|32
)braket
suffix:semicolon
DECL|macro|register_base
mdefine_line|#define register_base ((u_char *) registers )
DECL|macro|fpu_register
mdefine_line|#define fpu_register(x)  ( * ((FPU_REG *)( register_base + 10 * (x &amp; 7) )) )
DECL|macro|st
mdefine_line|#define&t;st(x)      ( * ((FPU_REG *)( register_base + 10 * ((top+x) &amp; 7) )) )
DECL|macro|STACK_OVERFLOW
mdefine_line|#define&t;STACK_OVERFLOW&t;(FPU_stackoverflow(&amp;st_new_ptr))
DECL|macro|NOT_EMPTY
mdefine_line|#define&t;NOT_EMPTY(i)&t;(!FPU_empty_i(i))
DECL|macro|NOT_EMPTY_ST0
mdefine_line|#define&t;NOT_EMPTY_ST0&t;(st0_tag ^ TAG_Empty)
DECL|macro|poppop
mdefine_line|#define poppop() { FPU_pop(); FPU_pop(); }
multiline_comment|/* push() does not affect the tags */
DECL|macro|push
mdefine_line|#define push()&t;{ top--; }
DECL|macro|signbyte
mdefine_line|#define signbyte(a) (((u_char *)(a))[9])
DECL|macro|getsign
mdefine_line|#define getsign(a) (signbyte(a) &amp; 0x80)
DECL|macro|setsign
mdefine_line|#define setsign(a,b) { if (b) signbyte(a) |= 0x80; else signbyte(a) &amp;= 0x7f; }
DECL|macro|copysign
mdefine_line|#define copysign(a,b) { if (getsign(a)) signbyte(b) |= 0x80; &bslash;&n;                        else signbyte(b) &amp;= 0x7f; }
DECL|macro|changesign
mdefine_line|#define changesign(a) { signbyte(a) ^= 0x80; }
DECL|macro|setpositive
mdefine_line|#define setpositive(a) { signbyte(a) &amp;= 0x7f; }
DECL|macro|setnegative
mdefine_line|#define setnegative(a) { signbyte(a) |= 0x80; }
DECL|macro|signpositive
mdefine_line|#define signpositive(a) ( (signbyte(a) &amp; 0x80) == 0 )
DECL|macro|signnegative
mdefine_line|#define signnegative(a) (signbyte(a) &amp; 0x80)
DECL|function|reg_copy
r_static
r_inline
r_void
id|reg_copy
c_func
(paren
id|FPU_REG
r_const
op_star
id|x
comma
id|FPU_REG
op_star
id|y
)paren
(brace
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|y-&gt;exp
)paren
op_assign
op_star
(paren
r_const
r_int
op_star
)paren
op_amp
(paren
id|x-&gt;exp
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|y-&gt;sigl
)paren
op_assign
op_star
(paren
r_const
r_int
r_int
op_star
)paren
op_amp
(paren
id|x-&gt;sigl
)paren
suffix:semicolon
)brace
DECL|macro|exponent
mdefine_line|#define exponent(x)  (((*(short *)&amp;((x)-&gt;exp)) &amp; 0x7fff) - EXTENDED_Ebias)
DECL|macro|setexponentpos
mdefine_line|#define setexponentpos(x,y) { (*(short *)&amp;((x)-&gt;exp)) = &bslash;&n;  ((y) + EXTENDED_Ebias) &amp; 0x7fff; }
DECL|macro|exponent16
mdefine_line|#define exponent16(x)         (*(short *)&amp;((x)-&gt;exp))
DECL|macro|setexponent16
mdefine_line|#define setexponent16(x,y)  { (*(short *)&amp;((x)-&gt;exp)) = (y); }
DECL|macro|addexponent
mdefine_line|#define addexponent(x,y)    { (*(short *)&amp;((x)-&gt;exp)) += (y); }
DECL|macro|stdexp
mdefine_line|#define stdexp(x)           { (*(short *)&amp;((x)-&gt;exp)) += EXTENDED_Ebias; }
DECL|macro|isdenormal
mdefine_line|#define isdenormal(ptr)   (exponent(ptr) == EXP_BIAS+EXP_UNDER)
DECL|macro|significand
mdefine_line|#define significand(x) ( ((unsigned long long *)&amp;((x)-&gt;sigl))[0] )
multiline_comment|/*----- Prototypes for functions written in assembler -----*/
multiline_comment|/* extern void reg_move(FPU_REG *a, FPU_REG *b); */
id|asmlinkage
r_int
id|FPU_normalize
c_func
(paren
id|FPU_REG
op_star
id|x
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_normalize_nuo
c_func
(paren
id|FPU_REG
op_star
id|x
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_u_sub
c_func
(paren
id|FPU_REG
r_const
op_star
id|arg1
comma
id|FPU_REG
r_const
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
comma
id|u_char
id|sign
comma
r_int
id|expa
comma
r_int
id|expb
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_u_mul
c_func
(paren
id|FPU_REG
r_const
op_star
id|arg1
comma
id|FPU_REG
r_const
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
comma
id|u_char
id|sign
comma
r_int
id|expon
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_u_div
c_func
(paren
id|FPU_REG
r_const
op_star
id|arg1
comma
id|FPU_REG
r_const
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
comma
id|u_char
id|sign
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_u_add
c_func
(paren
id|FPU_REG
r_const
op_star
id|arg1
comma
id|FPU_REG
r_const
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
comma
id|u_char
id|sign
comma
r_int
id|expa
comma
r_int
id|expb
)paren
suffix:semicolon
id|asmlinkage
r_int
id|wm_sqrt
c_func
(paren
id|FPU_REG
op_star
id|n
comma
r_int
id|dummy1
comma
r_int
id|dummy2
comma
r_int
r_int
id|control_w
comma
id|u_char
id|sign
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_shrx
c_func
(paren
r_void
op_star
id|l
comma
r_int
id|x
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_shrxs
c_func
(paren
r_void
op_star
id|v
comma
r_int
id|x
)paren
suffix:semicolon
id|asmlinkage
r_int
r_int
id|FPU_div_small
c_func
(paren
r_int
r_int
r_int
op_star
id|x
comma
r_int
r_int
id|y
)paren
suffix:semicolon
id|asmlinkage
r_int
id|FPU_round
c_func
(paren
id|FPU_REG
op_star
id|arg
comma
r_int
r_int
id|extent
comma
r_int
id|dummy
comma
r_int
r_int
id|control_w
comma
id|u_char
id|sign
)paren
suffix:semicolon
macro_line|#ifndef MAKING_PROTO
macro_line|#include &quot;fpu_proto.h&quot;
macro_line|#endif
macro_line|#endif __ASSEMBLY__
macro_line|#endif _FPU_EMU_H_
eof
