multiline_comment|/*&n; * include/asm-x86_64/xor.h&n; *&n; * Optimized RAID-5 checksumming functions for MMX and SSE.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * Cache avoiding checksumming functions utilizing KNI instructions&n; * Copyright (C) 1999 Zach Brown (with obvious credit due Ingo)&n; */
multiline_comment|/*&n; * Based on&n; * High-speed RAID5 checksumming functions utilizing SSE instructions.&n; * Copyright (C) 1998 Ingo Molnar.&n; */
multiline_comment|/*&n; * x86-64 changes / gcc fixes from Andi Kleen. &n; * Copyright 2002 Andi Kleen, SuSE Labs.&n; *&n; * This hasn&squot;t been optimized for the hammer yet, but there are likely&n; * no advantages to be gotten from x86-64 here anyways.&n; */
DECL|member|a
DECL|member|b
DECL|typedef|xmm_store_t
r_typedef
r_struct
(brace
r_int
r_int
id|a
comma
id|b
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
id|xmm_store_t
suffix:semicolon
multiline_comment|/* Doesn&squot;t use gcc to save the XMM registers, because there is no easy way to &n;   tell it to do a clts before the register saving. */
DECL|macro|XMMS_SAVE
mdefine_line|#define XMMS_SAVE&t;&t;&t;&t;&bslash;&n;&t;asm volatile ( &t;&t;&t;&bslash;&n;&t;&t;&quot;movq %%cr0,%0&t;&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;clts&t;&t;&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm0,(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm1,0x10(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm2,0x20(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm3,0x30(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (cr0)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (xmm_save) &t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|XMMS_RESTORE
mdefine_line|#define XMMS_RESTORE&t;&t;&t;&t;&bslash;&n;&t;asm volatile ( &t;&t;&t;&bslash;&n;&t;&t;&quot;sfence&t;&t;&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups (%1),%%xmm0&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups 0x10(%1),%%xmm1&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups 0x20(%1),%%xmm2&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups 0x30(%1),%%xmm3&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movq &t;%0,%%cr0&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (cr0), &quot;r&quot; (xmm_save)&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|OFFS
mdefine_line|#define OFFS(x)&t;&t;&quot;16*(&quot;#x&quot;)&quot;
DECL|macro|PF_OFFS
mdefine_line|#define PF_OFFS(x)&t;&quot;256+16*(&quot;#x&quot;)&quot;
DECL|macro|PF0
mdefine_line|#define&t;PF0(x)&t;&t;&quot;&t;prefetchnta &quot;PF_OFFS(x)&quot;(%[p1])&t;&t;;&bslash;n&quot;
DECL|macro|LD
mdefine_line|#define LD(x,y)&t;&t;&quot;       movaps   &quot;OFFS(x)&quot;(%[p1]), %%xmm&quot;#y&quot;&t;;&bslash;n&quot;
DECL|macro|ST
mdefine_line|#define ST(x,y)&t;&t;&quot;       movaps %%xmm&quot;#y&quot;,   &quot;OFFS(x)&quot;(%[p1])&t;;&bslash;n&quot;
DECL|macro|PF1
mdefine_line|#define PF1(x)&t;&t;&quot;&t;prefetchnta &quot;PF_OFFS(x)&quot;(%[p2])&t;&t;;&bslash;n&quot;
DECL|macro|PF2
mdefine_line|#define PF2(x)&t;&t;&quot;&t;prefetchnta &quot;PF_OFFS(x)&quot;(%[p3])&t;&t;;&bslash;n&quot;
DECL|macro|PF3
mdefine_line|#define PF3(x)&t;&t;&quot;&t;prefetchnta &quot;PF_OFFS(x)&quot;(%[p4])&t;&t;;&bslash;n&quot;
DECL|macro|PF4
mdefine_line|#define PF4(x)&t;&t;&quot;&t;prefetchnta &quot;PF_OFFS(x)&quot;(%[p5])&t;&t;;&bslash;n&quot;
DECL|macro|PF5
mdefine_line|#define PF5(x)&t;&t;&quot;&t;prefetchnta &quot;PF_OFFS(x)&quot;(%[p6])&t;&t;;&bslash;n&quot;
DECL|macro|XO1
mdefine_line|#define XO1(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%[p2]), %%xmm&quot;#y&quot;&t;;&bslash;n&quot;
DECL|macro|XO2
mdefine_line|#define XO2(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%[p3]), %%xmm&quot;#y&quot;&t;;&bslash;n&quot;
DECL|macro|XO3
mdefine_line|#define XO3(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%[p4]), %%xmm&quot;#y&quot;&t;;&bslash;n&quot;
DECL|macro|XO4
mdefine_line|#define XO4(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%[p5]), %%xmm&quot;#y&quot;&t;;&bslash;n&quot;
DECL|macro|XO5
mdefine_line|#define XO5(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%[p6]), %%xmm&quot;#y&quot;&t;;&bslash;n&quot;
r_static
r_void
DECL|function|xor_sse_2
id|xor_sse_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
r_int
r_int
id|cr0
suffix:semicolon
id|xmm_store_t
id|xmm_save
(braket
l_int|4
)braket
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|asm
r_volatile
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addq %[inc], %[p1]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p2]           ;&bslash;n&quot;
l_string|&quot;&t;&t;decl %[cnt] ; jnz 1b&quot;
suffix:colon
(braket
id|p1
)braket
l_string|&quot;+r&quot;
(paren
id|p1
)paren
comma
(braket
id|p2
)braket
l_string|&quot;+r&quot;
(paren
id|p2
)paren
comma
(braket
id|cnt
)braket
l_string|&quot;+r&quot;
(paren
id|lines
)paren
suffix:colon
(braket
id|inc
)braket
l_string|&quot;r&quot;
(paren
l_int|256UL
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_sse_3
id|xor_sse_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
id|xmm_store_t
id|xmm_save
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF2(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF2(i+2)&t;&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addq %[inc], %[p1]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p2]          ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p3]           ;&bslash;n&quot;
l_string|&quot;&t;&t;decl %[cnt] ; jnz 1b&quot;
suffix:colon
(braket
id|cnt
)braket
l_string|&quot;+r&quot;
(paren
id|lines
)paren
comma
(braket
id|p1
)braket
l_string|&quot;+r&quot;
(paren
id|p1
)paren
comma
(braket
id|p2
)braket
l_string|&quot;+r&quot;
(paren
id|p2
)paren
comma
(braket
id|p3
)braket
l_string|&quot;+r&quot;
(paren
id|p3
)paren
suffix:colon
(braket
id|inc
)braket
l_string|&quot;r&quot;
(paren
l_int|256UL
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_sse_4
id|xor_sse_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
id|xmm_store_t
id|xmm_save
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF2(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF2(i+2)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;PF3(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF3(i+2)&t;&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;XO3(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO3(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO3(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO3(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addq %[inc], %[p1]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p2]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p3]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p4]           ;&bslash;n&quot;
l_string|&quot;&t;decl %[cnt] ; jnz 1b&quot;
suffix:colon
(braket
id|cnt
)braket
l_string|&quot;+c&quot;
(paren
id|lines
)paren
comma
(braket
id|p1
)braket
l_string|&quot;+r&quot;
(paren
id|p1
)paren
comma
(braket
id|p2
)braket
l_string|&quot;+r&quot;
(paren
id|p2
)paren
comma
(braket
id|p3
)braket
l_string|&quot;+r&quot;
(paren
id|p3
)paren
comma
(braket
id|p4
)braket
l_string|&quot;+r&quot;
(paren
id|p4
)paren
suffix:colon
(braket
id|inc
)braket
l_string|&quot;r&quot;
(paren
l_int|256UL
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_sse_5
id|xor_sse_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
id|xmm_store_t
id|xmm_save
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF2(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF2(i+2)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;PF3(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF3(i+2)&t;&t;&bslash;&n;&t;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;PF4(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF4(i+2)&t;&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO3(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO3(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO3(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO3(i+3,3)&t;&bslash;&n;&t;&t;XO4(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO4(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO4(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO4(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addq %[inc], %[p1]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p2]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p3]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p4]           ;&bslash;n&quot;
l_string|&quot;       addq %[inc], %[p5]           ;&bslash;n&quot;
l_string|&quot;&t;decl %[cnt] ; jnz 1b&quot;
suffix:colon
(braket
id|cnt
)braket
l_string|&quot;+c&quot;
(paren
id|lines
)paren
comma
(braket
id|p1
)braket
l_string|&quot;+r&quot;
(paren
id|p1
)paren
comma
(braket
id|p2
)braket
l_string|&quot;+r&quot;
(paren
id|p2
)paren
comma
(braket
id|p3
)braket
l_string|&quot;+r&quot;
(paren
id|p3
)paren
comma
(braket
id|p4
)braket
l_string|&quot;+r&quot;
(paren
id|p4
)paren
comma
(braket
id|p5
)braket
l_string|&quot;+r&quot;
(paren
id|p5
)paren
suffix:colon
(braket
id|inc
)braket
l_string|&quot;r&quot;
(paren
l_int|256UL
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
DECL|variable|xor_block_sse
r_static
r_struct
id|xor_block_template
id|xor_block_sse
op_assign
(brace
id|name
suffix:colon
l_string|&quot;generic_sse&quot;
comma
id|do_2
suffix:colon
id|xor_sse_2
comma
id|do_3
suffix:colon
id|xor_sse_3
comma
id|do_4
suffix:colon
id|xor_sse_4
comma
id|do_5
suffix:colon
id|xor_sse_5
comma
)brace
suffix:semicolon
DECL|macro|XOR_TRY_TEMPLATES
macro_line|#undef XOR_TRY_TEMPLATES
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_sse);&t;&bslash;&n;&t;} while (0)
multiline_comment|/* We force the use of the SSE xor block because it can write around L2.&n;   We may also be able to load into the L1 only depending on how the cpu&n;   deals with a load to a line that is being prefetched.  */
DECL|macro|XOR_SELECT_TEMPLATE
mdefine_line|#define XOR_SELECT_TEMPLATE(FASTEST) (&amp;xor_block_sse)
eof
