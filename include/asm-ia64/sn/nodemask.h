multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_NODEMASK_H
DECL|macro|_ASM_SN_NODEMASK_H
mdefine_line|#define _ASM_SN_NODEMASK_H
macro_line|#if defined(__KERNEL__) || defined(_KMEMUSER)
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if CONFIG_SGI_IP35 || CONFIG_IA64_SGI_SN1 || CONFIG_IA64_GENERIC
macro_line|#include &lt;asm/sn/sn1/arch.h&gt;    /* needed for MAX_COMPACT_NODES */
macro_line|#endif
DECL|macro|CNODEMASK_BOOTED_MASK
mdefine_line|#define CNODEMASK_BOOTED_MASK&t;&t;boot_cnodemask
DECL|macro|CNODEMASK_BIPW
mdefine_line|#define CNODEMASK_BIPW    64
macro_line|#if !defined(SN0XXL) &amp;&amp; !defined(CONFIG_SGI_IP35) &amp;&amp; !defined(CONFIG_IA64_SGI_SN1) &amp;&amp; !defined(CONFIG_IA64_GENERIC)
multiline_comment|/* MAXCPUS 128p (64 nodes) or less */
DECL|macro|CNODEMASK_SIZE
mdefine_line|#define CNODEMASK_SIZE    1
DECL|typedef|cnodemask_t
r_typedef
r_uint64
id|cnodemask_t
suffix:semicolon
DECL|macro|CNODEMASK_WORD
mdefine_line|#define CNODEMASK_WORD(p,w)     (p)
DECL|macro|CNODEMASK_SET_WORD
mdefine_line|#define CNODEMASK_SET_WORD(p,w,val)     (p) = val
DECL|macro|CNODEMASK_CLRALL
mdefine_line|#define CNODEMASK_CLRALL(p)     (p) = 0
DECL|macro|CNODEMASK_SETALL
mdefine_line|#define CNODEMASK_SETALL(p)     (p) = ~((cnodemask_t)0)
DECL|macro|CNODEMASK_IS_ZERO
mdefine_line|#define CNODEMASK_IS_ZERO(p)&t;((p) == 0)
DECL|macro|CNODEMASK_IS_NONZERO
mdefine_line|#define CNODEMASK_IS_NONZERO(p)&t;((p) != 0)
DECL|macro|CNODEMASK_NOTEQ
mdefine_line|#define CNODEMASK_NOTEQ(p, q)&t;((p) != (q))
DECL|macro|CNODEMASK_EQ
mdefine_line|#define CNODEMASK_EQ(p, q)      ((p) == (q))
DECL|macro|CNODEMASK_LSB_ISONE
mdefine_line|#define CNODEMASK_LSB_ISONE(p)  ((p) &amp; 0x1ULL)
DECL|macro|CNODEMASK_ZERO
mdefine_line|#define CNODEMASK_ZERO()        ((cnodemask_t)0)
DECL|macro|CNODEMASK_CVTB
mdefine_line|#define CNODEMASK_CVTB(bit)     (1ULL &lt;&lt; (bit))
DECL|macro|CNODEMASK_SETB
mdefine_line|#define CNODEMASK_SETB(p, bit)&t;((p) |= 1ULL &lt;&lt; (bit))
DECL|macro|CNODEMASK_CLRB
mdefine_line|#define CNODEMASK_CLRB(p, bit)&t;((p) &amp;= ~(1ULL &lt;&lt; (bit)))
DECL|macro|CNODEMASK_TSTB
mdefine_line|#define CNODEMASK_TSTB(p, bit)&t;((p) &amp; (1ULL &lt;&lt; (bit)))
DECL|macro|CNODEMASK_SETM
mdefine_line|#define CNODEMASK_SETM(p, q)&t;((p) |= (q))
DECL|macro|CNODEMASK_CLRM
mdefine_line|#define CNODEMASK_CLRM(p, q)&t;((p) &amp;= ~(q))
DECL|macro|CNODEMASK_ANDM
mdefine_line|#define CNODEMASK_ANDM(p, q)&t;((p) &amp;= (q))
DECL|macro|CNODEMASK_TSTM
mdefine_line|#define CNODEMASK_TSTM(p, q)&t;((p) &amp; (q))
DECL|macro|CNODEMASK_CPYNOTM
mdefine_line|#define CNODEMASK_CPYNOTM(p, q)&t;((p) = ~(q))
DECL|macro|CNODEMASK_CPY
mdefine_line|#define CNODEMASK_CPY(p, q)     ((p) = (q))
DECL|macro|CNODEMASK_ORNOTM
mdefine_line|#define CNODEMASK_ORNOTM(p, q)&t;((p) |= ~(q))
DECL|macro|CNODEMASK_SHIFTL
mdefine_line|#define CNODEMASK_SHIFTL(p)     ((p) &lt;&lt;= 1)
DECL|macro|CNODEMASK_SHIFTR
mdefine_line|#define CNODEMASK_SHIFTR(p)     ((p) &gt;&gt;= 1)
DECL|macro|CNODEMASK_SHIFTL_PTR
mdefine_line|#define CNODEMASK_SHIFTL_PTR(p)     (*(p) &lt;&lt;= 1)
DECL|macro|CNODEMASK_SHIFTR_PTR
mdefine_line|#define CNODEMASK_SHIFTR_PTR(p)     (*(p) &gt;&gt;= 1)
multiline_comment|/* Atomically set or clear a particular bit */
DECL|macro|CNODEMASK_ATOMSET_BIT
mdefine_line|#define CNODEMASK_ATOMSET_BIT(p, bit) atomicSetUlong((cnodemask_t *)&amp;(p), (1ULL&lt;&lt;(bit))) 
DECL|macro|CNODEMASK_ATOMCLR_BIT
mdefine_line|#define CNODEMASK_ATOMCLR_BIT(p, bit) atomicClearUlong((cnodemask_t *)&amp;(p), (1ULL&lt;&lt;(bit)))
multiline_comment|/* Atomically set or clear a collection of bits */
DECL|macro|CNODEMASK_ATOMSET
mdefine_line|#define CNODEMASK_ATOMSET(p, q)  atomicSetUlong((cnodemask_t *)&amp;(p), q)
DECL|macro|CNODEMASK_ATOMCLR
mdefine_line|#define CNODEMASK_ATOMCLR(p, q)  atomicClearUlong((cnodemask_t *)&amp;(p), q)
multiline_comment|/* Atomically set or clear a collection of bits, returning the old value */
DECL|macro|CNODEMASK_ATOMSET_MASK
mdefine_line|#define CNODEMASK_ATOMSET_MASK(__old, p, q)&t;{ &bslash;&n;&t;&t;(__old) = atomicSetUlong((cnodemask_t *)&amp;(p), q); &bslash;&n;}
DECL|macro|CNODEMASK_ATOMCLR_MASK
mdefine_line|#define CNODEMASK_ATOMCLR_MASK(__old, p, q)&t;{ &bslash;&n;&t;&t;(__old) = atomicClearUlong((cnodemask_t *)&amp;(p),q); &bslash;&n;}
DECL|macro|CNODEMASK_FROM_NUMNODES
mdefine_line|#define CNODEMASK_FROM_NUMNODES(n)&t;((~(cnodemask_t)0)&gt;&gt;(CNODEMASK_BIPW-(n)))
macro_line|#else  /* SN0XXL || SN1 - MAXCPUS &gt; 128 */
DECL|macro|CNODEMASK_SIZE
mdefine_line|#define CNODEMASK_SIZE    (MAX_COMPACT_NODES / CNODEMASK_BIPW)
r_typedef
r_struct
(brace
DECL|member|_bits
r_uint64
id|_bits
(braket
id|CNODEMASK_SIZE
)braket
suffix:semicolon
DECL|typedef|cnodemask_t
)brace
id|cnodemask_t
suffix:semicolon
DECL|macro|CNODEMASK_WORD
mdefine_line|#define CNODEMASK_WORD(p,w)  &bslash;&n;&t;((w &gt;= 0 &amp;&amp; w &lt; CNODEMASK_SIZE) ? (p)._bits[(w)] : 0)
DECL|macro|CNODEMASK_SET_WORD
mdefine_line|#define CNODEMASK_SET_WORD(p,w,val)  { &t;&t;&t;&t;&bslash;&n;&t;if (w &gt;= 0 &amp;&amp; w &lt; CNODEMASK_SIZE) &t;&t;&t;&bslash;&n;&t;&t;(p)._bits[(w)] = val;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|CNODEMASK_CLRALL
mdefine_line|#define CNODEMASK_CLRALL(p)       {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] = 0;                               &bslash;&n;}
DECL|macro|CNODEMASK_SETALL
mdefine_line|#define CNODEMASK_SETALL(p)       {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] = ~(0);                            &bslash;&n;}
DECL|macro|CNODEMASK_LSB_ISONE
mdefine_line|#define CNODEMASK_LSB_ISONE(p)  ((p)._bits[0] &amp; 0x1ULL)
DECL|macro|CNODEMASK_SETM
mdefine_line|#define CNODEMASK_SETM(p,q)       {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] |= ((q)._bits[i]);                 &bslash;&n;}
DECL|macro|CNODEMASK_CLRM
mdefine_line|#define CNODEMASK_CLRM(p,q)       {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] &amp;= ~((q)._bits[i]);                &bslash;&n;}
DECL|macro|CNODEMASK_ANDM
mdefine_line|#define CNODEMASK_ANDM(p,q)       {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] &amp;= ((q)._bits[i]);                 &bslash;&n;}
DECL|macro|CNODEMASK_CPY
mdefine_line|#define CNODEMASK_CPY(p, q)  {&t;&t;&t;&t;&t;&bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] = (q)._bits[i];&t;                &bslash;&n;}
DECL|macro|CNODEMASK_CPYNOTM
mdefine_line|#define CNODEMASK_CPYNOTM(p,q)    {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] = ~((q)._bits[i]);                 &bslash;&n;}
DECL|macro|CNODEMASK_ORNOTM
mdefine_line|#define CNODEMASK_ORNOTM(p,q)     {                             &bslash;&n;        int i;                                                  &bslash;&n;                                                                &bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++)                  &bslash;&n;                (p)._bits[i] |= ~((q)._bits[i]);                &bslash;&n;}
DECL|macro|CNODEMASK_INDEX
mdefine_line|#define CNODEMASK_INDEX(bit)      ((bit) &gt;&gt; 6)
DECL|macro|CNODEMASK_SHFT
mdefine_line|#define CNODEMASK_SHFT(bit)       ((bit) &amp; 0x3f)
DECL|macro|CNODEMASK_SETB
mdefine_line|#define CNODEMASK_SETB(p, bit)&t; &t;&t;&t;&t;&bslash;&n;&t;(p)._bits[CNODEMASK_INDEX(bit)] |= (1ULL &lt;&lt; CNODEMASK_SHFT(bit))
DECL|macro|CNODEMASK_CLRB
mdefine_line|#define CNODEMASK_CLRB(p, bit)&t;&t;&t;&t;&t;&bslash;&n;&t;(p)._bits[CNODEMASK_INDEX(bit)] &amp;= ~(1ULL &lt;&lt; CNODEMASK_SHFT(bit)) 
DECL|macro|CNODEMASK_TSTB
mdefine_line|#define CNODEMASK_TSTB(p, bit)&t;&t;&bslash;&n;&t;((p)._bits[CNODEMASK_INDEX(bit)] &amp; (1ULL &lt;&lt; CNODEMASK_SHFT(bit))) 
multiline_comment|/** Probably should add atomic update for entire cnodemask_t struct **/
multiline_comment|/* Atomically set or clear a particular bit */
DECL|macro|CNODEMASK_ATOMSET_BIT
mdefine_line|#define CNODEMASK_ATOMSET_BIT(p, bit) &bslash;&n;        (atomicSetUlong((unsigned long *)&amp;(p)._bits[CNODEMASK_INDEX(bit)], (1ULL &lt;&lt; CNODEMASK_SHFT(bit))));
DECL|macro|CNODEMASK_ATOMCLR_BIT
mdefine_line|#define CNODEMASK_ATOMCLR_BIT(__old, p, bit) &bslash;&n;        (atomicClearUlong((unsigned long *)&amp;(p)._bits[CNODEMASK_INDEX(bit)], (1ULL &lt;&lt; CNODEMASK_SHFT(bit))));
multiline_comment|/* Atomically set or clear a collection of bits */
DECL|macro|CNODEMASK_ATOMSET
mdefine_line|#define CNODEMASK_ATOMSET(p, q) { &bslash;&n;        int i;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++) { &bslash;&n;&t;      atomicSetUlong((unsigned long *)&amp;(p)._bits[i], (q)._bits[i]);  &bslash;&n;        }&t;&t;&t;&t;&bslash;&n;}
DECL|macro|CNODEMASK_ATOMCLR
mdefine_line|#define CNODEMASK_ATOMCLR(p, q) { &bslash;&n;        int i;&t;&t;&t;&t;&bslash;&n;                        &t;&t;&bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++) {&t;&bslash;&n;&t;      atomicClearUlong((unsigned long *)&amp;(p)._bits[i], (q)._bits[i]); &bslash;&n;        }&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/* Atomically set or clear a collection of bits, returning the old value */
DECL|macro|CNODEMASK_ATOMSET_MASK
mdefine_line|#define CNODEMASK_ATOMSET_MASK(__old, p, q)  { &bslash;&n;        int i;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++) { &bslash;&n;           (__old)._bits[i] =&t; &bslash;&n;&t;      atomicSetUlong((unsigned long *)&amp;(p)._bits[i], (q)._bits[i]);  &bslash;&n;        }&t;&t;&t;&t;&bslash;&n;}
DECL|macro|CNODEMASK_ATOMCLR_MASK
mdefine_line|#define CNODEMASK_ATOMCLR_MASK(__old, p, q) {&t;&t;&t;&t;&t;&bslash;&n;        int i;&t;&t;&t;&t;&bslash;&n;                        &t;&t;&bslash;&n;        for (i = 0 ; i &lt; CNODEMASK_SIZE ; i++) {&t;&bslash;&n;           (__old)._bits[i] =&t;&t;&t;&t;&bslash;&n;&t;      atomicClearUlong((unsigned long *)&amp;(p)._bits[i], (q)._bits[i]); &bslash;&n;        }&t;&t;&t;&t;&bslash;&n;}
DECL|function|CNODEMASK_CVTB
id|__inline
r_static
id|cnodemask_t
id|CNODEMASK_CVTB
c_func
(paren
r_int
id|bit
)paren
(brace
id|cnodemask_t
id|__tmp
suffix:semicolon
id|CNODEMASK_CLRALL
c_func
(paren
id|__tmp
)paren
suffix:semicolon
id|CNODEMASK_SETB
c_func
(paren
id|__tmp
comma
id|bit
)paren
suffix:semicolon
r_return
id|__tmp
suffix:semicolon
)brace
DECL|function|CNODEMASK_ZERO
id|__inline
r_static
id|cnodemask_t
id|CNODEMASK_ZERO
c_func
(paren
r_void
)paren
(brace
id|cnodemask_t
id|__tmp
suffix:semicolon
id|CNODEMASK_CLRALL
c_func
(paren
id|__tmp
)paren
suffix:semicolon
r_return
id|__tmp
suffix:semicolon
)brace
DECL|function|CNODEMASK_IS_ZERO
id|__inline
r_static
r_int
id|CNODEMASK_IS_ZERO
(paren
id|cnodemask_t
id|p
)paren
(brace
r_int
id|i
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
id|CNODEMASK_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|p._bits
(braket
id|i
)braket
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|CNODEMASK_IS_NONZERO
id|__inline
r_static
r_int
id|CNODEMASK_IS_NONZERO
(paren
id|cnodemask_t
id|p
)paren
(brace
r_int
id|i
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
id|CNODEMASK_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|p._bits
(braket
id|i
)braket
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|CNODEMASK_NOTEQ
id|__inline
r_static
r_int
id|CNODEMASK_NOTEQ
(paren
id|cnodemask_t
id|p
comma
id|cnodemask_t
id|q
)paren
(brace
r_int
id|i
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
id|CNODEMASK_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|p._bits
(braket
id|i
)braket
op_ne
id|q._bits
(braket
id|i
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|CNODEMASK_EQ
id|__inline
r_static
r_int
id|CNODEMASK_EQ
(paren
id|cnodemask_t
id|p
comma
id|cnodemask_t
id|q
)paren
(brace
r_int
id|i
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
id|CNODEMASK_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|p._bits
(braket
id|i
)braket
op_ne
id|q._bits
(braket
id|i
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|CNODEMASK_TSTM
id|__inline
r_static
r_int
id|CNODEMASK_TSTM
(paren
id|cnodemask_t
id|p
comma
id|cnodemask_t
id|q
)paren
(brace
r_int
id|i
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
id|CNODEMASK_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|p._bits
(braket
id|i
)braket
op_amp
id|q._bits
(braket
id|i
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|CNODEMASK_SHIFTL_PTR
id|__inline
r_static
r_void
id|CNODEMASK_SHIFTL_PTR
(paren
id|cnodemask_t
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_uint64
id|upper
suffix:semicolon
multiline_comment|/*&n;         * shift words starting with the last word&n;         * of the vector and work backward to the first&n;         * word updating the low order bits with the&n;         * high order bit of the prev word.&n;         */
r_for
c_loop
(paren
id|i
op_assign
(paren
id|CNODEMASK_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|upper
op_assign
(paren
id|p-&gt;_bits
(braket
id|i
op_minus
l_int|1
)braket
op_amp
(paren
l_int|1ULL
op_lshift
(paren
id|CNODEMASK_BIPW
op_minus
l_int|1
)paren
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|p-&gt;_bits
(braket
id|i
)braket
op_lshift_assign
l_int|1
suffix:semicolon
id|p-&gt;_bits
(braket
id|i
)braket
op_or_assign
id|upper
suffix:semicolon
)brace
id|p-&gt;_bits
(braket
id|i
)braket
op_lshift_assign
l_int|1
suffix:semicolon
)brace
DECL|function|CNODEMASK_SHIFTR_PTR
id|__inline
r_static
r_void
id|CNODEMASK_SHIFTR_PTR
(paren
id|cnodemask_t
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_uint64
id|lower
suffix:semicolon
multiline_comment|/*&n;         * shift words starting with the first word&n;         * of the vector and work forward to the last&n;         * word updating the high order bit with the&n;         * low order bit of the next word.&n;         */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|CNODEMASK_SIZE
op_minus
l_int|2
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
id|lower
op_assign
(paren
id|p-&gt;_bits
(braket
id|i
op_plus
l_int|1
)braket
op_amp
(paren
l_int|0x1
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|p-&gt;_bits
(braket
id|i
)braket
op_rshift_assign
l_int|1
suffix:semicolon
id|p-&gt;_bits
(braket
id|i
)braket
op_or_assign
(paren
id|lower
op_lshift
(paren
(paren
id|CNODEMASK_BIPW
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
id|p-&gt;_bits
(braket
id|i
)braket
op_rshift_assign
l_int|1
suffix:semicolon
)brace
DECL|function|CNODEMASK_FROM_NUMNODES
id|__inline
r_static
id|cnodemask_t
id|CNODEMASK_FROM_NUMNODES
c_func
(paren
r_int
id|n
)paren
(brace
id|cnodemask_t
id|__tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|CNODEMASK_CLRALL
c_func
(paren
id|__tmp
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|CNODEMASK_SETB
c_func
(paren
id|__tmp
comma
id|i
)paren
suffix:semicolon
)brace
r_return
id|__tmp
suffix:semicolon
)brace
macro_line|#endif /* SN0XXL || SN1 */
r_extern
id|cnodemask_t
id|boot_cnodemask
suffix:semicolon
macro_line|#endif /* __KERNEL__ || _KMEMUSER */
macro_line|#endif /* _ASM_SN_NODEMASK_H */
eof
