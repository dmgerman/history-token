multiline_comment|/*&n; * Copyright (C) 1999 Hewlett-Packard (Frank Rowand)&n; * Copyright (C) 1999 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; * Copyright (C) 1999 SuSE GmbH&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _PARISC_ASSEMBLY_H
DECL|macro|_PARISC_ASSEMBLY_H
mdefine_line|#define _PARISC_ASSEMBLY_H
macro_line|#if defined(__LP64__) &amp;&amp; defined(__ASSEMBLY__)
multiline_comment|/* the 64-bit pa gnu assembler unfortunately defaults to .level 1.1 or 2.0 so&n; * work around that for now... */
dot
id|level
l_float|2.0
id|w
macro_line|#endif
macro_line|#include &lt;asm/offsets.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/asmregs.h&gt;
id|sp
op_assign
l_int|30
id|gp
op_assign
l_int|27
id|ipsw
op_assign
l_int|22
multiline_comment|/*&n;&t; * We provide two versions of each macro to convert from physical&n;&t; * to virtual and vice versa. The &quot;_r1&quot; versions take one argument&n;&t; * register, but trashes r1 to do the conversion. The other&n;&t; * version takes two arguments: a src and destination register.&n;&t; * However, the source and destination registers can not be&n;&t; * the same register.&n;&t; */
dot
id|macro
id|tophys
id|grvirt
comma
id|grphys
id|ldil
id|L
op_mod
(paren
id|__PAGE_OFFSET
)paren
comma
"&bslash;"
id|grphys
DECL|variable|grvirt
DECL|variable|grphys
id|sub
"&bslash;"
id|grvirt
comma
"&bslash;"
id|grphys
comma
"&bslash;"
id|grphys
dot
id|endm
dot
id|macro
id|tovirt
id|grphys
comma
id|grvirt
id|ldil
id|L
op_mod
(paren
id|__PAGE_OFFSET
)paren
comma
"&bslash;"
id|grvirt
DECL|variable|grphys
DECL|variable|grvirt
id|add
"&bslash;"
id|grphys
comma
"&bslash;"
id|grvirt
comma
"&bslash;"
id|grvirt
dot
id|endm
dot
id|macro
id|tophys_r1
id|gr
id|ldil
id|L
op_mod
(paren
id|__PAGE_OFFSET
)paren
comma
op_mod
id|r1
DECL|variable|gr
DECL|variable|r1
id|sub
"&bslash;"
id|gr
comma
op_mod
id|r1
comma
"&bslash;"
id|gr
dot
id|endm
dot
id|macro
id|tovirt_r1
id|gr
id|ldil
id|L
op_mod
(paren
id|__PAGE_OFFSET
)paren
comma
op_mod
id|r1
DECL|variable|gr
DECL|variable|r1
id|add
"&bslash;"
id|gr
comma
op_mod
id|r1
comma
"&bslash;"
id|gr
dot
id|endm
dot
id|macro
id|delay
id|value
id|ldil
id|L
op_mod
"&bslash;"
id|value
comma
l_int|1
id|ldo
id|R
op_mod
"&bslash;"
id|value
c_func
(paren
l_int|1
)paren
comma
l_int|1
id|addib
comma
id|UV
comma
id|n
op_minus
l_int|1
comma
l_int|1
comma
dot
id|addib
comma
id|NUV
comma
id|n
op_minus
l_int|1
comma
l_int|1
comma
dot
op_plus
l_int|8
id|nop
dot
id|endm
dot
id|macro
id|debug
id|value
dot
id|endm
multiline_comment|/* Shift Left - note the r and t can NOT be the same! */
DECL|variable|sa
dot
id|macro
id|shl
id|r
comma
id|sa
comma
id|t
DECL|variable|dep
DECL|variable|r
id|dep
comma
id|z
"&bslash;"
id|r
comma
l_int|31
op_minus
"&bslash;"
id|sa
comma
l_int|32
op_minus
"&bslash;"
id|sa
comma
"&bslash;"
id|t
dot
id|endm
multiline_comment|/* The PA 2.0 shift left */
DECL|variable|sa
dot
id|macro
id|shlw
id|r
comma
id|sa
comma
id|t
DECL|variable|depw
DECL|variable|r
id|depw
comma
id|z
"&bslash;"
id|r
comma
l_int|31
op_minus
"&bslash;"
id|sa
comma
l_int|32
op_minus
"&bslash;"
id|sa
comma
"&bslash;"
id|t
dot
id|endm
multiline_comment|/* And the PA 2.0W shift left */
DECL|variable|sa
dot
id|macro
id|shld
id|r
comma
id|sa
comma
id|t
DECL|variable|depd
DECL|variable|r
id|depd
comma
id|z
"&bslash;"
id|r
comma
l_int|63
op_minus
"&bslash;"
id|sa
comma
l_int|64
op_minus
"&bslash;"
id|sa
comma
"&bslash;"
id|t
dot
id|endm
multiline_comment|/* load 32-bit &squot;value&squot; into &squot;reg&squot; compensating for the ldil&n;&t; * sign-extension when running in wide mode.&n;&t; * WARNING!! neither &squot;value&squot; nor &squot;reg&squot; can be expressions&n;&t; * containing &squot;.&squot;!!!! */
dot
id|macro
id|load32
id|value
comma
id|reg
DECL|variable|value
id|ldil
id|L
op_mod
"&bslash;"
id|value
comma
"&bslash;"
id|reg
id|ldo
id|R
op_mod
"&bslash;"
id|value
c_func
(paren
"&bslash;"
id|reg
)paren
comma
"&bslash;"
id|reg
dot
id|endm
macro_line|#ifdef __LP64__
DECL|macro|LDREG
mdefine_line|#define LDREG   ldd
DECL|macro|STREG
mdefine_line|#define STREG   std
DECL|macro|RP_OFFSET
mdefine_line|#define RP_OFFSET&t;16
macro_line|#else
mdefine_line|#define LDREG   ldw
mdefine_line|#define STREG   stw
mdefine_line|#define RP_OFFSET&t;20
macro_line|#endif
dot
id|macro
id|loadgp
macro_line|#ifdef __LP64__
id|ldil
id|L
op_mod
id|__gp
comma
op_mod
id|r27
id|ldo
id|R
op_mod
id|__gp
c_func
(paren
op_mod
id|r27
)paren
comma
op_mod
id|r27
macro_line|#else
id|ldil
id|L
op_mod
"$"
id|global
"$"
comma
op_mod
id|r27
id|ldo
id|R
op_mod
"$"
id|global
"$"
(paren
op_mod
id|r27
)paren
comma
op_mod
id|r27
macro_line|#endif
dot
id|endm
DECL|macro|SAVE_SP
mdefine_line|#define SAVE_SP(r, where) mfsp r, %r1 ! STREG %r1, where
DECL|macro|REST_SP
mdefine_line|#define REST_SP(r, where) LDREG where, %r1 ! mtsp %r1, r
DECL|macro|SAVE_CR
mdefine_line|#define SAVE_CR(r, where) mfctl r, %r1 ! STREG %r1, where
DECL|macro|REST_CR
mdefine_line|#define REST_CR(r, where) LDREG where, %r1 ! mtctl %r1, r
dot
id|macro
id|save_general
id|regs
id|STREG
op_mod
id|r1
comma
id|PT_GR1
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r2
id|STREG
op_mod
id|r2
comma
id|PT_GR2
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r3
id|STREG
op_mod
id|r3
comma
id|PT_GR3
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r4
id|STREG
op_mod
id|r4
comma
id|PT_GR4
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r5
id|STREG
op_mod
id|r5
comma
id|PT_GR5
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r6
id|STREG
op_mod
id|r6
comma
id|PT_GR6
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r7
id|STREG
op_mod
id|r7
comma
id|PT_GR7
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r8
id|STREG
op_mod
id|r8
comma
id|PT_GR8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r9
id|STREG
op_mod
id|r9
comma
id|PT_GR9
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r10
id|STREG
op_mod
id|r10
comma
id|PT_GR10
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r11
id|STREG
op_mod
id|r11
comma
id|PT_GR11
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r12
id|STREG
op_mod
id|r12
comma
id|PT_GR12
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r13
id|STREG
op_mod
id|r13
comma
id|PT_GR13
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r14
id|STREG
op_mod
id|r14
comma
id|PT_GR14
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r15
id|STREG
op_mod
id|r15
comma
id|PT_GR15
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r16
id|STREG
op_mod
id|r16
comma
id|PT_GR16
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r17
id|STREG
op_mod
id|r17
comma
id|PT_GR17
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r18
id|STREG
op_mod
id|r18
comma
id|PT_GR18
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r19
id|STREG
op_mod
id|r19
comma
id|PT_GR19
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r20
id|STREG
op_mod
id|r20
comma
id|PT_GR20
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r21
id|STREG
op_mod
id|r21
comma
id|PT_GR21
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r22
id|STREG
op_mod
id|r22
comma
id|PT_GR22
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r23
id|STREG
op_mod
id|r23
comma
id|PT_GR23
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r24
id|STREG
op_mod
id|r24
comma
id|PT_GR24
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r25
id|STREG
op_mod
id|r25
comma
id|PT_GR25
c_func
(paren
"&bslash;"
id|regs
)paren
multiline_comment|/* r26 is saved in get_stack and used to preserve a value across virt_map */
DECL|variable|r27
id|STREG
op_mod
id|r27
comma
id|PT_GR27
c_func
(paren
"&bslash;"
id|regs
)paren
DECL|variable|r28
id|STREG
op_mod
id|r28
comma
id|PT_GR28
c_func
(paren
"&bslash;"
id|regs
)paren
multiline_comment|/* r29 is saved in get_stack and used to point to saved registers */
multiline_comment|/* r30 stack pointer saved in get_stack */
DECL|variable|r31
id|STREG
op_mod
id|r31
comma
id|PT_GR31
c_func
(paren
"&bslash;"
id|regs
)paren
dot
id|endm
dot
id|macro
id|rest_general
id|regs
multiline_comment|/* r1 used as a temp in rest_stack and is restored there */
id|LDREG
id|PT_GR2
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r2
id|LDREG
id|PT_GR3
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r3
id|LDREG
id|PT_GR4
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r4
id|LDREG
id|PT_GR5
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r5
id|LDREG
id|PT_GR6
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r6
id|LDREG
id|PT_GR7
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r7
id|LDREG
id|PT_GR8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r8
id|LDREG
id|PT_GR9
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r9
id|LDREG
id|PT_GR10
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r10
id|LDREG
id|PT_GR11
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r11
id|LDREG
id|PT_GR12
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r12
id|LDREG
id|PT_GR13
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r13
id|LDREG
id|PT_GR14
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r14
id|LDREG
id|PT_GR15
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r15
id|LDREG
id|PT_GR16
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r16
id|LDREG
id|PT_GR17
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r17
id|LDREG
id|PT_GR18
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r18
id|LDREG
id|PT_GR19
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r19
id|LDREG
id|PT_GR20
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r20
id|LDREG
id|PT_GR21
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r21
id|LDREG
id|PT_GR22
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r22
id|LDREG
id|PT_GR23
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r23
id|LDREG
id|PT_GR24
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r24
id|LDREG
id|PT_GR25
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r25
id|LDREG
id|PT_GR26
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r26
id|LDREG
id|PT_GR27
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r27
id|LDREG
id|PT_GR28
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r28
multiline_comment|/* r29 points to register save area, and is restored in rest_stack */
multiline_comment|/* r30 stack pointer restored in rest_stack */
id|LDREG
id|PT_GR31
c_func
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|r31
dot
id|endm
dot
id|macro
id|save_fp
id|regs
DECL|variable|fr0
id|fstd
comma
id|ma
op_mod
id|fr0
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr1
id|fstd
comma
id|ma
op_mod
id|fr1
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr2
id|fstd
comma
id|ma
op_mod
id|fr2
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr3
id|fstd
comma
id|ma
op_mod
id|fr3
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr4
id|fstd
comma
id|ma
op_mod
id|fr4
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr5
id|fstd
comma
id|ma
op_mod
id|fr5
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr6
id|fstd
comma
id|ma
op_mod
id|fr6
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr7
id|fstd
comma
id|ma
op_mod
id|fr7
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr8
id|fstd
comma
id|ma
op_mod
id|fr8
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr9
id|fstd
comma
id|ma
op_mod
id|fr9
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr10
id|fstd
comma
id|ma
op_mod
id|fr10
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr11
id|fstd
comma
id|ma
op_mod
id|fr11
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr12
id|fstd
comma
id|ma
op_mod
id|fr12
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr13
id|fstd
comma
id|ma
op_mod
id|fr13
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr14
id|fstd
comma
id|ma
op_mod
id|fr14
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr15
id|fstd
comma
id|ma
op_mod
id|fr15
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr16
id|fstd
comma
id|ma
op_mod
id|fr16
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr17
id|fstd
comma
id|ma
op_mod
id|fr17
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr18
id|fstd
comma
id|ma
op_mod
id|fr18
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr19
id|fstd
comma
id|ma
op_mod
id|fr19
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr20
id|fstd
comma
id|ma
op_mod
id|fr20
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr21
id|fstd
comma
id|ma
op_mod
id|fr21
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr22
id|fstd
comma
id|ma
op_mod
id|fr22
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr23
id|fstd
comma
id|ma
op_mod
id|fr23
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr24
id|fstd
comma
id|ma
op_mod
id|fr24
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr25
id|fstd
comma
id|ma
op_mod
id|fr25
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr26
id|fstd
comma
id|ma
op_mod
id|fr26
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr27
id|fstd
comma
id|ma
op_mod
id|fr27
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr28
id|fstd
comma
id|ma
op_mod
id|fr28
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr29
id|fstd
comma
id|ma
op_mod
id|fr29
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fstd
DECL|variable|fr30
id|fstd
comma
id|ma
op_mod
id|fr30
comma
l_int|8
(paren
"&bslash;"
id|regs
)paren
DECL|variable|fr31
id|fstd
op_mod
id|fr31
comma
l_int|0
(paren
"&bslash;"
id|regs
)paren
dot
id|endm
dot
id|macro
id|rest_fp
id|regs
id|fldd
l_int|0
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr31
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr30
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr29
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr28
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr27
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr26
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr25
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr24
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr23
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr22
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr21
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr20
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr19
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr18
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr17
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr16
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr15
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr14
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr13
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr12
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr11
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr10
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr9
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr8
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr7
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr6
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr5
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr4
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr3
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr2
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr1
DECL|variable|fldd
id|fldd
comma
id|mb
op_minus
l_int|8
(paren
"&bslash;"
id|regs
)paren
comma
op_mod
id|fr0
dot
id|endm
macro_line|#ifdef __LP64__
dot
id|macro
id|callee_save
DECL|variable|r3
id|std
comma
id|ma
op_mod
id|r3
comma
l_int|144
(paren
op_mod
id|r30
)paren
DECL|variable|cr27
id|mfctl
op_mod
id|cr27
comma
op_mod
id|r3
DECL|variable|r4
id|std
op_mod
id|r4
comma
op_minus
l_int|136
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r5
comma
op_minus
l_int|128
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r6
comma
op_minus
l_int|120
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r7
comma
op_minus
l_int|112
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r8
comma
op_minus
l_int|104
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r9
comma
op_minus
l_int|96
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r10
comma
op_minus
l_int|88
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r11
comma
op_minus
l_int|80
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r12
comma
op_minus
l_int|72
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r13
comma
op_minus
l_int|64
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r14
comma
op_minus
l_int|56
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r15
comma
op_minus
l_int|48
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r16
comma
op_minus
l_int|40
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r17
comma
op_minus
l_int|32
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r18
comma
op_minus
l_int|24
(paren
op_mod
id|r30
)paren
id|std
op_mod
id|r3
comma
op_minus
l_int|16
(paren
op_mod
id|r30
)paren
dot
id|endm
dot
id|macro
id|callee_rest
id|ldd
op_minus
l_int|16
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r3
id|ldd
op_minus
l_int|24
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r18
id|ldd
op_minus
l_int|32
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r17
id|ldd
op_minus
l_int|40
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r16
id|ldd
op_minus
l_int|48
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r15
id|ldd
op_minus
l_int|56
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r14
id|ldd
op_minus
l_int|64
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r13
id|ldd
op_minus
l_int|72
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r12
id|ldd
op_minus
l_int|80
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r11
id|ldd
op_minus
l_int|88
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r10
id|ldd
op_minus
l_int|96
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r9
id|ldd
op_minus
l_int|104
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r8
id|ldd
op_minus
l_int|112
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r7
id|ldd
op_minus
l_int|120
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r6
id|ldd
op_minus
l_int|128
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r5
id|ldd
op_minus
l_int|136
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r4
DECL|variable|r3
id|mtctl
op_mod
id|r3
comma
op_mod
id|cr27
DECL|variable|ldd
id|ldd
comma
id|mb
op_minus
l_int|144
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r3
dot
id|endm
macro_line|#else /* ! __LP64__ */
dot
id|macro
id|callee_save
id|stw
comma
id|ma
op_mod
id|r3
comma
l_int|128
(paren
op_mod
id|r30
)paren
id|mfctl
op_mod
id|cr27
comma
op_mod
id|r3
id|stw
op_mod
id|r4
comma
op_minus
l_int|124
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r5
comma
op_minus
l_int|120
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r6
comma
op_minus
l_int|116
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r7
comma
op_minus
l_int|112
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r8
comma
op_minus
l_int|108
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r9
comma
op_minus
l_int|104
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r10
comma
op_minus
l_int|100
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r11
comma
op_minus
l_int|96
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r12
comma
op_minus
l_int|92
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r13
comma
op_minus
l_int|88
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r14
comma
op_minus
l_int|84
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r15
comma
op_minus
l_int|80
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r16
comma
op_minus
l_int|76
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r17
comma
op_minus
l_int|72
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r18
comma
op_minus
l_int|68
(paren
op_mod
id|r30
)paren
id|stw
op_mod
id|r3
comma
op_minus
l_int|64
(paren
op_mod
id|r30
)paren
dot
id|endm
dot
id|macro
id|callee_rest
id|ldw
op_minus
l_int|64
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r3
id|ldw
op_minus
l_int|68
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r18
id|ldw
op_minus
l_int|72
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r17
id|ldw
op_minus
l_int|76
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r16
id|ldw
op_minus
l_int|80
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r15
id|ldw
op_minus
l_int|84
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r14
id|ldw
op_minus
l_int|88
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r13
id|ldw
op_minus
l_int|92
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r12
id|ldw
op_minus
l_int|96
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r11
id|ldw
op_minus
l_int|100
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r10
id|ldw
op_minus
l_int|104
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r9
id|ldw
op_minus
l_int|108
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r8
id|ldw
op_minus
l_int|112
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r7
id|ldw
op_minus
l_int|116
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r6
id|ldw
op_minus
l_int|120
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r5
id|ldw
op_minus
l_int|124
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r4
id|mtctl
op_mod
id|r3
comma
op_mod
id|cr27
id|ldw
comma
id|mb
op_minus
l_int|128
(paren
op_mod
id|r30
)paren
comma
op_mod
id|r3
dot
id|endm
macro_line|#endif /* ! __LP64__ */
dot
id|macro
id|save_specials
id|regs
id|SAVE_SP
(paren
op_mod
id|sr0
comma
id|PT_SR0
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr1
comma
id|PT_SR1
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr2
comma
id|PT_SR2
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr3
comma
id|PT_SR3
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr4
comma
id|PT_SR4
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr5
comma
id|PT_SR5
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr6
comma
id|PT_SR6
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_SP
(paren
op_mod
id|sr7
comma
id|PT_SR7
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_CR
(paren
op_mod
id|cr17
comma
id|PT_IASQ0
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
DECL|variable|r0
id|mtctl
op_mod
id|r0
comma
op_mod
id|cr17
id|SAVE_CR
(paren
op_mod
id|cr17
comma
id|PT_IASQ1
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
id|SAVE_CR
(paren
op_mod
id|cr18
comma
id|PT_IAOQ0
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
DECL|variable|r0
id|mtctl
op_mod
id|r0
comma
op_mod
id|cr18
id|SAVE_CR
(paren
op_mod
id|cr18
comma
id|PT_IAOQ1
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
macro_line|#ifdef __LP64__
multiline_comment|/* cr11 (sar) is a funny one.  5 bits on PA1.1 and 6 bit on PA2.0&n;&t; * For PA2.0 mtsar or mtctl always write 6 bits, but mfctl only&n;&t; * reads 5 bits.  Use mfctl,w to read all six bits.  Otherwise&n;&t; * we loose the 6th bit on a save/restore over interrupt.&n;&t; */
DECL|variable|cr11
id|mfctl
comma
id|w
op_mod
id|cr11
comma
op_mod
id|r1
DECL|variable|r1
id|STREG
op_mod
id|r1
comma
id|PT_SAR
(paren
"&bslash;"
id|regs
)paren
macro_line|#else
id|SAVE_CR
(paren
op_mod
id|cr11
comma
id|PT_SAR
(paren
"&bslash;"
id|regs
)paren
)paren
macro_line|#endif
id|SAVE_CR
(paren
op_mod
id|cr19
comma
id|PT_IIR
(paren
"&bslash;"
id|regs
)paren
)paren
multiline_comment|/*&n;&t; * Code immediately following this macro (in intr_save) relies&n;&t; * on r8 containing ipsw.&n;&t; */
DECL|variable|cr22
id|mfctl
op_mod
id|cr22
comma
op_mod
id|r8
DECL|variable|r8
id|STREG
op_mod
id|r8
comma
id|PT_PSW
c_func
(paren
"&bslash;"
id|regs
)paren
dot
id|endm
dot
id|macro
id|rest_specials
id|regs
id|REST_SP
(paren
op_mod
id|sr0
comma
id|PT_SR0
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr1
comma
id|PT_SR1
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr2
comma
id|PT_SR2
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr3
comma
id|PT_SR3
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr4
comma
id|PT_SR4
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr5
comma
id|PT_SR5
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr6
comma
id|PT_SR6
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_SP
(paren
op_mod
id|sr7
comma
id|PT_SR7
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_CR
(paren
op_mod
id|cr17
comma
id|PT_IASQ0
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_CR
(paren
op_mod
id|cr17
comma
id|PT_IASQ1
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_CR
(paren
op_mod
id|cr18
comma
id|PT_IAOQ0
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_CR
(paren
op_mod
id|cr18
comma
id|PT_IAOQ1
c_func
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_CR
(paren
op_mod
id|cr11
comma
id|PT_SAR
(paren
"&bslash;"
id|regs
)paren
)paren
id|REST_CR
(paren
op_mod
id|cr22
comma
id|PT_PSW
(paren
"&bslash;"
id|regs
)paren
)paren
dot
id|endm
macro_line|#endif
eof
