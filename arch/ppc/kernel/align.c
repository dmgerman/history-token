multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * align.c - handle alignment exceptions for the Power PC.&n; *&n; * Copyright (c) 1996 Paul Mackerras &lt;paulus@cs.anu.edu.au&gt;&n; * Copyright (c) 1998-1999 TiVo, Inc.&n; *   PowerPC 403GCX modifications.&n; * Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *   PowerPC 403GCX/405GP modifications.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
DECL|struct|aligninfo
r_struct
id|aligninfo
(brace
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_4xx)
DECL|macro|OPCD
mdefine_line|#define&t;OPCD(inst)&t;(((inst) &amp; 0xFC000000) &gt;&gt; 26)
DECL|macro|RS
mdefine_line|#define&t;RS(inst)&t;(((inst) &amp; 0x03E00000) &gt;&gt; 21)
DECL|macro|RA
mdefine_line|#define&t;RA(inst)&t;(((inst) &amp; 0x001F0000) &gt;&gt; 16)
DECL|macro|IS_DFORM
mdefine_line|#define&t;IS_DFORM(code)&t;((code) &gt;= 32 &amp;&amp; (code) &lt;= 55)
macro_line|#endif
DECL|macro|INVALID
mdefine_line|#define INVALID&t;{ 0, 0 }
DECL|macro|LD
mdefine_line|#define LD&t;1&t;/* load */
DECL|macro|ST
mdefine_line|#define ST&t;2&t;/* store */
DECL|macro|SE
mdefine_line|#define&t;SE&t;4&t;/* sign-extend value */
DECL|macro|F
mdefine_line|#define F&t;8&t;/* to/from fp regs */
DECL|macro|U
mdefine_line|#define U&t;0x10&t;/* update index register */
DECL|macro|M
mdefine_line|#define M&t;0x20&t;/* multiple load/store */
DECL|macro|S
mdefine_line|#define S&t;0x40&t;/* single-precision fp, or byte-swap value */
DECL|macro|HARD
mdefine_line|#define HARD&t;0x80&t;/* string, stwcx. */
DECL|macro|DCBZ
mdefine_line|#define DCBZ&t;0x5f&t;/* 8xx/82xx dcbz faults when cache not enabled */
multiline_comment|/*&n; * The PowerPC stores certain bits of the instruction that caused the&n; * alignment exception in the DSISR register.  This array maps those&n; * bits to information about the operand length and what the&n; * instruction would do.&n; */
DECL|variable|aligninfo
r_static
r_struct
id|aligninfo
id|aligninfo
(braket
l_int|128
)braket
op_assign
(brace
(brace
l_int|4
comma
id|LD
)brace
comma
multiline_comment|/* 00 0 0000: lwz / lwarx */
id|INVALID
comma
multiline_comment|/* 00 0 0001 */
(brace
l_int|4
comma
id|ST
)brace
comma
multiline_comment|/* 00 0 0010: stw */
id|INVALID
comma
multiline_comment|/* 00 0 0011 */
(brace
l_int|2
comma
id|LD
)brace
comma
multiline_comment|/* 00 0 0100: lhz */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
)brace
comma
multiline_comment|/* 00 0 0101: lha */
(brace
l_int|2
comma
id|ST
)brace
comma
multiline_comment|/* 00 0 0110: sth */
(brace
l_int|4
comma
id|LD
op_plus
id|M
)brace
comma
multiline_comment|/* 00 0 0111: lmw */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 00 0 1000: lfs */
(brace
l_int|8
comma
id|LD
op_plus
id|F
)brace
comma
multiline_comment|/* 00 0 1001: lfd */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 00 0 1010: stfs */
(brace
l_int|8
comma
id|ST
op_plus
id|F
)brace
comma
multiline_comment|/* 00 0 1011: stfd */
id|INVALID
comma
multiline_comment|/* 00 0 1100 */
id|INVALID
comma
multiline_comment|/* 00 0 1101 */
id|INVALID
comma
multiline_comment|/* 00 0 1110 */
id|INVALID
comma
multiline_comment|/* 00 0 1111 */
(brace
l_int|4
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0000: lwzu */
id|INVALID
comma
multiline_comment|/* 00 1 0001 */
(brace
l_int|4
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0010: stwu */
id|INVALID
comma
multiline_comment|/* 00 1 0011 */
(brace
l_int|2
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0100: lhzu */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0101: lhau */
(brace
l_int|2
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0110: sthu */
(brace
l_int|4
comma
id|ST
op_plus
id|M
)brace
comma
multiline_comment|/* 00 1 0111: stmw */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1000: lfsu */
(brace
l_int|8
comma
id|LD
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1001: lfdu */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1010: stfsu */
(brace
l_int|8
comma
id|ST
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1011: stfdu */
id|INVALID
comma
multiline_comment|/* 00 1 1100 */
id|INVALID
comma
multiline_comment|/* 00 1 1101 */
id|INVALID
comma
multiline_comment|/* 00 1 1110 */
id|INVALID
comma
multiline_comment|/* 00 1 1111 */
id|INVALID
comma
multiline_comment|/* 01 0 0000 */
id|INVALID
comma
multiline_comment|/* 01 0 0001 */
id|INVALID
comma
multiline_comment|/* 01 0 0010 */
id|INVALID
comma
multiline_comment|/* 01 0 0011 */
id|INVALID
comma
multiline_comment|/* 01 0 0100 */
id|INVALID
comma
multiline_comment|/* 01 0 0101: lwax?? */
id|INVALID
comma
multiline_comment|/* 01 0 0110 */
id|INVALID
comma
multiline_comment|/* 01 0 0111 */
(brace
l_int|0
comma
id|LD
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1000: lswx */
(brace
l_int|0
comma
id|LD
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1001: lswi */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1010: stswx */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1011: stswi */
id|INVALID
comma
multiline_comment|/* 01 0 1100 */
id|INVALID
comma
multiline_comment|/* 01 0 1101 */
id|INVALID
comma
multiline_comment|/* 01 0 1110 */
id|INVALID
comma
multiline_comment|/* 01 0 1111 */
id|INVALID
comma
multiline_comment|/* 01 1 0000 */
id|INVALID
comma
multiline_comment|/* 01 1 0001 */
id|INVALID
comma
multiline_comment|/* 01 1 0010 */
id|INVALID
comma
multiline_comment|/* 01 1 0011 */
id|INVALID
comma
multiline_comment|/* 01 1 0100 */
id|INVALID
comma
multiline_comment|/* 01 1 0101: lwaux?? */
id|INVALID
comma
multiline_comment|/* 01 1 0110 */
id|INVALID
comma
multiline_comment|/* 01 1 0111 */
id|INVALID
comma
multiline_comment|/* 01 1 1000 */
id|INVALID
comma
multiline_comment|/* 01 1 1001 */
id|INVALID
comma
multiline_comment|/* 01 1 1010 */
id|INVALID
comma
multiline_comment|/* 01 1 1011 */
id|INVALID
comma
multiline_comment|/* 01 1 1100 */
id|INVALID
comma
multiline_comment|/* 01 1 1101 */
id|INVALID
comma
multiline_comment|/* 01 1 1110 */
id|INVALID
comma
multiline_comment|/* 01 1 1111 */
id|INVALID
comma
multiline_comment|/* 10 0 0000 */
id|INVALID
comma
multiline_comment|/* 10 0 0001 */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 10 0 0010: stwcx. */
id|INVALID
comma
multiline_comment|/* 10 0 0011 */
id|INVALID
comma
multiline_comment|/* 10 0 0100 */
id|INVALID
comma
multiline_comment|/* 10 0 0101 */
id|INVALID
comma
multiline_comment|/* 10 0 0110 */
id|INVALID
comma
multiline_comment|/* 10 0 0111 */
(brace
l_int|4
comma
id|LD
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1000: lwbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1001 */
(brace
l_int|4
comma
id|ST
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1010: stwbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1011 */
(brace
l_int|2
comma
id|LD
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1100: lhbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1101 */
(brace
l_int|2
comma
id|ST
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1110: sthbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1111 */
id|INVALID
comma
multiline_comment|/* 10 1 0000 */
id|INVALID
comma
multiline_comment|/* 10 1 0001 */
id|INVALID
comma
multiline_comment|/* 10 1 0010 */
id|INVALID
comma
multiline_comment|/* 10 1 0011 */
id|INVALID
comma
multiline_comment|/* 10 1 0100 */
id|INVALID
comma
multiline_comment|/* 10 1 0101 */
id|INVALID
comma
multiline_comment|/* 10 1 0110 */
id|INVALID
comma
multiline_comment|/* 10 1 0111 */
id|INVALID
comma
multiline_comment|/* 10 1 1000 */
id|INVALID
comma
multiline_comment|/* 10 1 1001 */
id|INVALID
comma
multiline_comment|/* 10 1 1010 */
id|INVALID
comma
multiline_comment|/* 10 1 1011 */
id|INVALID
comma
multiline_comment|/* 10 1 1100 */
id|INVALID
comma
multiline_comment|/* 10 1 1101 */
id|INVALID
comma
multiline_comment|/* 10 1 1110 */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 10 1 1111: dcbz */
(brace
l_int|4
comma
id|LD
)brace
comma
multiline_comment|/* 11 0 0000: lwzx */
id|INVALID
comma
multiline_comment|/* 11 0 0001 */
(brace
l_int|4
comma
id|ST
)brace
comma
multiline_comment|/* 11 0 0010: stwx */
id|INVALID
comma
multiline_comment|/* 11 0 0011 */
(brace
l_int|2
comma
id|LD
)brace
comma
multiline_comment|/* 11 0 0100: lhzx */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
)brace
comma
multiline_comment|/* 11 0 0101: lhax */
(brace
l_int|2
comma
id|ST
)brace
comma
multiline_comment|/* 11 0 0110: sthx */
id|INVALID
comma
multiline_comment|/* 11 0 0111 */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 11 0 1000: lfsx */
(brace
l_int|8
comma
id|LD
op_plus
id|F
)brace
comma
multiline_comment|/* 11 0 1001: lfdx */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 11 0 1010: stfsx */
(brace
l_int|8
comma
id|ST
op_plus
id|F
)brace
comma
multiline_comment|/* 11 0 1011: stfdx */
id|INVALID
comma
multiline_comment|/* 11 0 1100 */
id|INVALID
comma
multiline_comment|/* 11 0 1101 */
id|INVALID
comma
multiline_comment|/* 11 0 1110 */
id|INVALID
comma
multiline_comment|/* 11 0 1111 */
(brace
l_int|4
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0000: lwzux */
id|INVALID
comma
multiline_comment|/* 11 1 0001 */
(brace
l_int|4
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0010: stwux */
id|INVALID
comma
multiline_comment|/* 11 1 0011 */
(brace
l_int|2
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0100: lhzux */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0101: lhaux */
(brace
l_int|2
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0110: sthux */
id|INVALID
comma
multiline_comment|/* 11 1 0111 */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1000: lfsux */
(brace
l_int|8
comma
id|LD
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1001: lfdux */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1010: stfsux */
(brace
l_int|8
comma
id|ST
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1011: stfdux */
id|INVALID
comma
multiline_comment|/* 11 1 1100 */
id|INVALID
comma
multiline_comment|/* 11 1 1101 */
id|INVALID
comma
multiline_comment|/* 11 1 1110 */
id|INVALID
comma
multiline_comment|/* 11 1 1111 */
)brace
suffix:semicolon
DECL|macro|SWAP
mdefine_line|#define SWAP(a, b)&t;(t = (a), (a) = (b), (b) = t)
r_int
DECL|function|fix_alignment
id|fix_alignment
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|instr
comma
id|nb
comma
id|flags
suffix:semicolon
macro_line|#if defined(CONFIG_4xx)
r_int
id|opcode
comma
id|f1
comma
id|f2
comma
id|f3
suffix:semicolon
macro_line|#endif
r_int
id|i
comma
id|t
suffix:semicolon
r_int
id|reg
comma
id|areg
suffix:semicolon
r_int
r_char
op_star
id|addr
suffix:semicolon
r_union
(brace
r_int
id|l
suffix:semicolon
r_float
id|f
suffix:semicolon
r_float
id|d
suffix:semicolon
r_int
r_char
id|v
(braket
l_int|8
)braket
suffix:semicolon
)brace
id|data
suffix:semicolon
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_4xx)
multiline_comment|/* The 4xx-family processors have no DSISR register,&n;&t; * so we emulate it.&n;&t; */
id|instr
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;nip
)paren
suffix:semicolon
id|opcode
op_assign
id|OPCD
c_func
(paren
id|instr
)paren
suffix:semicolon
id|reg
op_assign
id|RS
c_func
(paren
id|instr
)paren
suffix:semicolon
id|areg
op_assign
id|RA
c_func
(paren
id|instr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_DFORM
c_func
(paren
id|opcode
)paren
)paren
(brace
id|f1
op_assign
l_int|0
suffix:semicolon
id|f2
op_assign
(paren
id|instr
op_amp
l_int|0x04000000
)paren
op_rshift
l_int|26
suffix:semicolon
id|f3
op_assign
(paren
id|instr
op_amp
l_int|0x78000000
)paren
op_rshift
l_int|27
suffix:semicolon
)brace
r_else
(brace
id|f1
op_assign
(paren
id|instr
op_amp
l_int|0x00000006
)paren
op_rshift
l_int|1
suffix:semicolon
id|f2
op_assign
(paren
id|instr
op_amp
l_int|0x00000040
)paren
op_rshift
l_int|6
suffix:semicolon
id|f3
op_assign
(paren
id|instr
op_amp
l_int|0x00000780
)paren
op_rshift
l_int|7
suffix:semicolon
)brace
id|instr
op_assign
(paren
(paren
id|f1
op_lshift
l_int|5
)paren
op_or
(paren
id|f2
op_lshift
l_int|4
)paren
op_or
id|f3
)paren
suffix:semicolon
macro_line|#else
id|reg
op_assign
(paren
id|regs-&gt;dsisr
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* source/dest register */
id|areg
op_assign
id|regs-&gt;dsisr
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* register to update */
id|instr
op_assign
(paren
id|regs-&gt;dsisr
op_rshift
l_int|10
)paren
op_amp
l_int|0x7f
suffix:semicolon
macro_line|#endif
id|nb
op_assign
id|aligninfo
(braket
id|instr
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|nb
op_eq
l_int|0
)paren
(brace
r_int
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|instr
op_ne
id|DCBZ
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* too hard or invalid instruction */
multiline_comment|/*&n;&t;&t; * The dcbz (data cache block zero) instruction&n;&t;&t; * gives an alignment fault if used on non-cacheable&n;&t;&t; * memory.  We handle the fault mainly for the&n;&t;&t; * case when we are running with the cache disabled&n;&t;&t; * for debugging.&n;&t;&t; */
id|p
op_assign
(paren
r_int
op_star
)paren
(paren
id|regs-&gt;dar
op_amp
op_minus
id|L1_CACHE_BYTES
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|L1_CACHE_BYTES
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
op_increment
id|i
)paren
id|p
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|flags
op_assign
id|aligninfo
(braket
id|instr
)braket
dot
id|flags
suffix:semicolon
multiline_comment|/* For the 4xx-family processors, the &squot;dar&squot; field of the&n;&t; * pt_regs structure is overloaded and is really from the DEAR.&n;&t; */
id|addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|regs-&gt;dar
suffix:semicolon
multiline_comment|/* Verify the address of the operand */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
(paren
id|flags
op_amp
id|ST
ques
c_cond
id|VERIFY_WRITE
suffix:colon
id|VERIFY_READ
)paren
comma
id|addr
comma
id|nb
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* bad address */
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|F
)paren
op_logical_and
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
)paren
id|giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|M
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* too hard for now */
multiline_comment|/* If we read the operand, copy it in */
r_if
c_cond
(paren
id|flags
op_amp
id|LD
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
id|data.v
(braket
l_int|0
)braket
op_assign
id|data.v
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|addr
)paren
op_logical_or
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|3
)braket
comma
id|addr
op_plus
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|data.v
(braket
id|i
)braket
comma
id|addr
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|flags
op_amp
op_complement
id|U
)paren
(brace
r_case
id|LD
op_plus
id|SE
suffix:colon
r_if
c_cond
(paren
id|data.v
(braket
l_int|2
)braket
op_ge
l_int|0x80
)paren
id|data.v
(braket
l_int|0
)braket
op_assign
id|data.v
(braket
l_int|1
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|LD
suffix:colon
id|regs-&gt;gpr
(braket
id|reg
)braket
op_assign
id|data.l
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LD
op_plus
id|S
suffix:colon
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|0
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|1
)braket
comma
id|data.v
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
id|regs-&gt;gpr
(braket
id|reg
)braket
op_assign
id|data.l
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST
suffix:colon
id|data.l
op_assign
id|regs-&gt;gpr
(braket
id|reg
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST
op_plus
id|S
suffix:colon
id|data.l
op_assign
id|regs-&gt;gpr
(braket
id|reg
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|0
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|1
)braket
comma
id|data.v
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LD
op_plus
id|F
suffix:colon
id|current-&gt;thread.fpr
(braket
id|reg
)braket
op_assign
id|data.d
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST
op_plus
id|F
suffix:colon
id|data.d
op_assign
id|current-&gt;thread.fpr
(braket
id|reg
)braket
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* these require some floating point conversions... */
multiline_comment|/* we&squot;d like to use the assignment, but we have to compile&n;&t; * the kernel with -msoft-float so it doesn&squot;t use the&n;&t; * fp regs for copying 8-byte objects. */
r_case
id|LD
op_plus
id|F
op_plus
id|S
suffix:colon
id|enable_kernel_fp
c_func
(paren
)paren
suffix:semicolon
id|cvt_fd
c_func
(paren
op_amp
id|data.f
comma
op_amp
id|current-&gt;thread.fpr
(braket
id|reg
)braket
comma
op_amp
id|current-&gt;thread.fpscr
)paren
suffix:semicolon
multiline_comment|/* current-&gt;thread.fpr[reg] = data.f; */
r_break
suffix:semicolon
r_case
id|ST
op_plus
id|F
op_plus
id|S
suffix:colon
id|enable_kernel_fp
c_func
(paren
)paren
suffix:semicolon
id|cvt_df
c_func
(paren
op_amp
id|current-&gt;thread.fpr
(braket
id|reg
)braket
comma
op_amp
id|data.f
comma
op_amp
id|current-&gt;thread.fpscr
)paren
suffix:semicolon
multiline_comment|/* data.f = current-&gt;thread.fpr[reg]; */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;align: can&squot;t handle flags=%x&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|ST
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|addr
)paren
op_logical_or
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|3
)braket
comma
id|addr
op_plus
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|data.v
(braket
id|i
)braket
comma
id|addr
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|U
)paren
(brace
id|regs-&gt;gpr
(braket
id|areg
)braket
op_assign
id|regs-&gt;dar
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
