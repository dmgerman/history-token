multiline_comment|/* align.c - handle alignment exceptions for the Power PC.&n; *&n; * Copyright (c) 1996 Paul Mackerras &lt;paulus@cs.anu.edu.au&gt;&n; * Copyright (c) 1998-1999 TiVo, Inc.&n; *   PowerPC 403GCX modifications.&n; * Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *   PowerPC 403GCX/405GP modifications.&n; * Copyright (c) 2001-2002 PPC64 team, IBM Corp&n; *   64-bit and Power4 support&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
DECL|macro|IS_XFORM
mdefine_line|#define IS_XFORM(inst)&t;(((inst) &gt;&gt; 26) == 31)
DECL|macro|IS_DSFORM
mdefine_line|#define IS_DSFORM(inst)&t;(((inst) &gt;&gt; 26) &gt;= 56)
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
DECL|macro|SW
mdefine_line|#define SW&t;0x40&t;/* byte swap */
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
(brace
l_int|8
comma
id|LD
)brace
comma
multiline_comment|/* 00 0 1101: ld */
id|INVALID
comma
multiline_comment|/* 00 0 1110 */
(brace
l_int|8
comma
id|ST
)brace
comma
multiline_comment|/* 00 0 1111: std */
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
(brace
l_int|8
comma
id|LD
)brace
comma
multiline_comment|/* 01 0 0000: ldx */
id|INVALID
comma
multiline_comment|/* 01 0 0001 */
(brace
l_int|8
comma
id|ST
)brace
comma
multiline_comment|/* 01 0 0010: stdx */
id|INVALID
comma
multiline_comment|/* 01 0 0011 */
id|INVALID
comma
multiline_comment|/* 01 0 0100 */
(brace
l_int|4
comma
id|LD
op_plus
id|SE
)brace
comma
multiline_comment|/* 01 0 0101: lwax */
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
)brace
comma
multiline_comment|/* 01 0 1000: lswx */
(brace
l_int|0
comma
id|LD
)brace
comma
multiline_comment|/* 01 0 1001: lswi */
(brace
l_int|0
comma
id|ST
)brace
comma
multiline_comment|/* 01 0 1010: stswx */
(brace
l_int|0
comma
id|ST
)brace
comma
multiline_comment|/* 01 0 1011: stswi */
id|INVALID
comma
multiline_comment|/* 01 0 1100 */
(brace
l_int|8
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 01 0 1101: ldu */
id|INVALID
comma
multiline_comment|/* 01 0 1110 */
(brace
l_int|8
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 01 0 1111: stdu */
(brace
l_int|8
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 01 1 0000: ldux */
id|INVALID
comma
multiline_comment|/* 01 1 0001 */
(brace
l_int|8
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 01 1 0010: stdux */
id|INVALID
comma
multiline_comment|/* 01 1 0011 */
id|INVALID
comma
multiline_comment|/* 01 1 0100 */
(brace
l_int|4
comma
id|LD
op_plus
id|SE
op_plus
id|U
)brace
comma
multiline_comment|/* 01 1 0101: lwaux */
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
id|SW
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
id|SW
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
id|SW
)brace
comma
multiline_comment|/* 10 0 1100: lhbrx */
(brace
l_int|4
comma
id|LD
op_plus
id|SE
)brace
comma
multiline_comment|/* 10 0 1101  lwa */
(brace
l_int|2
comma
id|ST
op_plus
id|SW
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
id|L1_CACHE_BYTES
comma
id|ST
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
(brace
l_int|8
comma
id|LD
op_plus
id|M
)brace
comma
multiline_comment|/* 11 0 1101: lmd */
id|INVALID
comma
multiline_comment|/* 11 0 1110 */
(brace
l_int|8
comma
id|ST
op_plus
id|M
)brace
comma
multiline_comment|/* 11 0 1111: stmd */
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
DECL|function|make_dsisr
r_int
r_static
r_inline
id|make_dsisr
c_func
(paren
r_int
id|instr
)paren
(brace
r_int
id|dsisr
suffix:semicolon
multiline_comment|/* create a DSISR value from the instruction */
id|dsisr
op_assign
(paren
id|instr
op_amp
l_int|0x03ff0000
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* bits  6:15 --&gt; 22:31 */
r_if
c_cond
(paren
id|IS_XFORM
c_func
(paren
id|instr
)paren
)paren
(brace
id|dsisr
op_or_assign
(paren
id|instr
op_amp
l_int|0x00000006
)paren
op_lshift
l_int|14
suffix:semicolon
multiline_comment|/* bits 29:30 --&gt; 15:16 */
id|dsisr
op_or_assign
(paren
id|instr
op_amp
l_int|0x00000040
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* bit     25 --&gt;    17 */
id|dsisr
op_or_assign
(paren
id|instr
op_amp
l_int|0x00000780
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* bits 21:24 --&gt; 18:21 */
)brace
r_else
(brace
id|dsisr
op_or_assign
(paren
id|instr
op_amp
l_int|0x04000000
)paren
op_rshift
l_int|12
suffix:semicolon
multiline_comment|/* bit      5 --&gt;    17 */
id|dsisr
op_or_assign
(paren
id|instr
op_amp
l_int|0x78000000
)paren
op_rshift
l_int|17
suffix:semicolon
multiline_comment|/* bits  1: 4 --&gt; 18:21 */
r_if
c_cond
(paren
id|IS_DSFORM
c_func
(paren
id|instr
)paren
)paren
(brace
id|dsisr
op_or_assign
(paren
id|instr
op_amp
l_int|0x00000003
)paren
op_lshift
l_int|18
suffix:semicolon
multiline_comment|/* bits 30:31 --&gt; 12:13 */
)brace
)brace
r_return
id|dsisr
suffix:semicolon
)brace
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
r_int
id|instr
comma
id|nb
comma
id|flags
suffix:semicolon
r_int
id|t
suffix:semicolon
r_int
r_int
id|reg
comma
id|areg
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|dsisr
suffix:semicolon
r_int
r_char
op_star
id|addr
comma
op_star
id|p
suffix:semicolon
r_int
r_int
op_star
id|lp
suffix:semicolon
r_union
(brace
r_int
id|ll
suffix:semicolon
r_float
id|dd
suffix:semicolon
r_int
r_char
id|v
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
r_int
id|hi32
suffix:semicolon
r_int
id|low32
suffix:semicolon
)brace
id|x32
suffix:semicolon
r_struct
(brace
r_int
r_char
id|hi48
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|low16
suffix:semicolon
)brace
id|x16
suffix:semicolon
)brace
id|data
suffix:semicolon
multiline_comment|/*&n;&t; * Return 1 on success&n;&t; * Return 0 if unable to handle the interrupt&n;&t; * Return -EFAULT if data address is bad&n;&t; */
id|dsisr
op_assign
id|regs-&gt;dsisr
suffix:semicolon
multiline_comment|/* Power4 doesn&squot;t set DSISR for an alignment interrupt */
r_if
c_cond
(paren
id|__is_processor
c_func
(paren
id|PV_POWER4
)paren
)paren
id|dsisr
op_assign
id|make_dsisr
c_func
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|regs-&gt;nip
)paren
)paren
suffix:semicolon
multiline_comment|/* extract the operation and registers from the dsisr */
id|reg
op_assign
(paren
id|dsisr
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* source/dest register */
id|areg
op_assign
id|dsisr
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* register to update */
id|instr
op_assign
(paren
id|dsisr
op_rshift
l_int|10
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|instr
op_or_assign
(paren
id|dsisr
op_rshift
l_int|13
)paren
op_amp
l_int|0x60
suffix:semicolon
multiline_comment|/* Lookup the operation in our table */
id|nb
op_assign
id|aligninfo
(braket
id|instr
)braket
dot
id|len
suffix:semicolon
id|flags
op_assign
id|aligninfo
(braket
id|instr
)braket
dot
id|flags
suffix:semicolon
multiline_comment|/* DAR has the operand effective address */
id|addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|regs-&gt;dar
suffix:semicolon
multiline_comment|/* A size of 0 indicates an instruction we don&squot;t support */
multiline_comment|/* we also don&squot;t support the multiples (lmw, stmw, lmd, stmd) */
r_if
c_cond
(paren
(paren
id|nb
op_eq
l_int|0
)paren
op_logical_or
(paren
id|flags
op_amp
id|M
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* too hard or invalid instruction */
multiline_comment|/*&n;&t; * Special handling for dcbz&n;&t; * dcbz may give an alignment exception for accesses to caching inhibited&n;&t; * storage&n;&t; */
r_if
c_cond
(paren
id|instr
op_eq
id|DCBZ
)paren
id|addr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|addr
op_amp
op_minus
id|L1_CACHE_BYTES
)paren
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
multiline_comment|/* Force the fprs into the save area so we can reference them */
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
multiline_comment|/* If we are loading, get the data from user space */
r_if
c_cond
(paren
id|flags
op_amp
id|LD
)paren
(brace
id|data.ll
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|addr
suffix:semicolon
r_switch
c_cond
(paren
id|nb
)paren
(brace
r_case
l_int|8
suffix:colon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|0
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|1
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|3
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|4
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|5
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|6
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|7
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
multiline_comment|/* If we are storing, get the data from the saved gpr or fpr */
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
id|flags
op_amp
id|F
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Doing stfs, have to convert to single */
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
(paren
r_float
op_star
)paren
op_amp
id|data.v
(braket
l_int|4
)braket
comma
op_amp
id|current-&gt;thread.fpscr
)paren
suffix:semicolon
)brace
r_else
id|data.dd
op_assign
id|current-&gt;thread.fpr
(braket
id|reg
)braket
suffix:semicolon
)brace
r_else
id|data.ll
op_assign
id|regs-&gt;gpr
(braket
id|reg
)braket
suffix:semicolon
)brace
multiline_comment|/* Swap bytes as needed */
r_if
c_cond
(paren
id|flags
op_amp
id|SW
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|6
)braket
comma
id|data.v
(braket
l_int|7
)braket
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* nb must be 4 */
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|4
)braket
comma
id|data.v
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|5
)braket
comma
id|data.v
(braket
l_int|6
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Sign extend as needed */
r_if
c_cond
(paren
id|flags
op_amp
id|SE
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
id|data.ll
op_assign
id|data.x16.low16
suffix:semicolon
r_else
multiline_comment|/* nb must be 4 */
id|data.ll
op_assign
id|data.x32.low32
suffix:semicolon
)brace
multiline_comment|/* If we are loading, move the data to the gpr or fpr */
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
id|flags
op_amp
id|F
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Doing lfs, have to convert to double */
id|enable_kernel_fp
c_func
(paren
)paren
suffix:semicolon
id|cvt_fd
c_func
(paren
(paren
r_float
op_star
)paren
op_amp
id|data.v
(braket
l_int|4
)braket
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
)brace
r_else
id|current-&gt;thread.fpr
(braket
id|reg
)braket
op_assign
id|data.dd
suffix:semicolon
)brace
r_else
id|regs-&gt;gpr
(braket
id|reg
)braket
op_assign
id|data.ll
suffix:semicolon
)brace
multiline_comment|/* If we are storing, copy the data to the user */
r_if
c_cond
(paren
id|flags
op_amp
id|ST
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|addr
suffix:semicolon
r_switch
c_cond
(paren
id|nb
)paren
(brace
r_case
l_int|128
suffix:colon
multiline_comment|/* Special case - must be dcbz */
id|lp
op_assign
(paren
r_int
r_int
op_star
)paren
id|p
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
id|ret
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|lp
op_increment
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|0
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|1
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|3
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|4
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|5
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|6
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|7
)braket
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* Update RA as needed */
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
