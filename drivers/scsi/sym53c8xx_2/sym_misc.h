multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM_MISC_H
DECL|macro|SYM_MISC_H
mdefine_line|#define SYM_MISC_H
multiline_comment|/*&n; *  A &squot;read barrier&squot; flushes any data that have been prefetched &n; *  by the processor due to out of order execution. Such a barrier &n; *  must notably be inserted prior to looking at data that have &n; *  been DMAed, assuming that program does memory READs in proper &n; *  order and that the device ensured proper ordering of WRITEs.&n; *&n; *  A &squot;write barrier&squot; prevents any previous WRITEs to pass further &n; *  WRITEs. Such barriers must be inserted each time another agent &n; *  relies on ordering of WRITEs.&n; *&n; *  Note that, due to posting of PCI memory writes, we also must &n; *  insert dummy PCI read transactions when some ordering involving &n; *  both directions over the PCI does matter. PCI transactions are &n; *  fully ordered in each direction.&n; *&n; *  IA32 processors insert implicit barriers when the processor &n; *  accesses unchacheable either for reading or writing, and &n; *  donnot reorder WRITEs. As a result, some &squot;read barriers&squot; can &n; *  be avoided (following access to uncacheable), and &squot;write &n; *  barriers&squot; should be useless (preventing compiler optimizations &n; *  should be enough).&n; */
macro_line|#if&t;defined&t;__i386__
DECL|macro|__READ_BARRIER
mdefine_line|#define __READ_BARRIER()&t;&bslash;&n;&t;&t;__asm__ volatile(&quot;lock; addl $0,0(%%esp)&quot;: : :&quot;memory&quot;)
DECL|macro|__WRITE_BARRIER
mdefine_line|#define __WRITE_BARRIER()&t;__asm__ volatile (&quot;&quot;: : :&quot;memory&quot;)
macro_line|#elif&t;defined&t;__powerpc__
DECL|macro|__READ_BARRIER
mdefine_line|#define __READ_BARRIER()&t;__asm__ volatile(&quot;eieio; sync&quot; : : : &quot;memory&quot;)
DECL|macro|__WRITE_BARRIER
mdefine_line|#define __WRITE_BARRIER()&t;__asm__ volatile(&quot;eieio; sync&quot; : : : &quot;memory&quot;)
macro_line|#elif&t;defined&t;__ia64__
DECL|macro|__READ_BARRIER
mdefine_line|#define __READ_BARRIER()&t;__asm__ volatile(&quot;mf.a; mf&quot; : : : &quot;memory&quot;)
DECL|macro|__WRITE_BARRIER
mdefine_line|#define __WRITE_BARRIER()&t;__asm__ volatile(&quot;mf.a; mf&quot; : : : &quot;memory&quot;)
macro_line|#elif&t;defined&t;__alpha__
DECL|macro|__READ_BARRIER
mdefine_line|#define __READ_BARRIER()&t;__asm__ volatile(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|__WRITE_BARRIER
mdefine_line|#define __WRITE_BARRIER()&t;__asm__ volatile(&quot;mb&quot;: : :&quot;memory&quot;)
macro_line|#else
DECL|macro|__READ_BARRIER
mdefine_line|#define __READ_BARRIER()&t;mb()
DECL|macro|__WRITE_BARRIER
mdefine_line|#define __WRITE_BARRIER()&t;mb()
macro_line|#endif
macro_line|#ifndef MEMORY_READ_BARRIER
DECL|macro|MEMORY_READ_BARRIER
mdefine_line|#define MEMORY_READ_BARRIER()&t;__READ_BARRIER()
macro_line|#endif
macro_line|#ifndef MEMORY_WRITE_BARRIER
DECL|macro|MEMORY_WRITE_BARRIER
mdefine_line|#define MEMORY_WRITE_BARRIER()&t;__WRITE_BARRIER()
macro_line|#endif
multiline_comment|/*&n; *  A la VMS/CAM-3 queue management.&n; */
DECL|struct|sym_quehead
r_typedef
r_struct
id|sym_quehead
(brace
DECL|member|flink
r_struct
id|sym_quehead
op_star
id|flink
suffix:semicolon
multiline_comment|/* Forward  pointer */
DECL|member|blink
r_struct
id|sym_quehead
op_star
id|blink
suffix:semicolon
multiline_comment|/* Backward pointer */
DECL|typedef|SYM_QUEHEAD
)brace
id|SYM_QUEHEAD
suffix:semicolon
DECL|macro|sym_que_init
mdefine_line|#define sym_que_init(ptr) do { &bslash;&n;&t;(ptr)-&gt;flink = (ptr); (ptr)-&gt;blink = (ptr); &bslash;&n;} while (0)
DECL|function|sym_que_first
r_static
id|__inline
r_struct
id|sym_quehead
op_star
id|sym_que_first
c_func
(paren
r_struct
id|sym_quehead
op_star
id|head
)paren
(brace
r_return
(paren
id|head-&gt;flink
op_eq
id|head
)paren
ques
c_cond
l_int|0
suffix:colon
id|head-&gt;flink
suffix:semicolon
)brace
DECL|function|sym_que_last
r_static
id|__inline
r_struct
id|sym_quehead
op_star
id|sym_que_last
c_func
(paren
r_struct
id|sym_quehead
op_star
id|head
)paren
(brace
r_return
(paren
id|head-&gt;blink
op_eq
id|head
)paren
ques
c_cond
l_int|0
suffix:colon
id|head-&gt;blink
suffix:semicolon
)brace
DECL|function|__sym_que_add
r_static
id|__inline
r_void
id|__sym_que_add
c_func
(paren
r_struct
id|sym_quehead
op_star
r_new
comma
r_struct
id|sym_quehead
op_star
id|blink
comma
r_struct
id|sym_quehead
op_star
id|flink
)paren
(brace
id|flink-&gt;blink
op_assign
r_new
suffix:semicolon
r_new
op_member_access_from_pointer
id|flink
op_assign
id|flink
suffix:semicolon
r_new
op_member_access_from_pointer
id|blink
op_assign
id|blink
suffix:semicolon
id|blink-&gt;flink
op_assign
r_new
suffix:semicolon
)brace
DECL|function|__sym_que_del
r_static
id|__inline
r_void
id|__sym_que_del
c_func
(paren
r_struct
id|sym_quehead
op_star
id|blink
comma
r_struct
id|sym_quehead
op_star
id|flink
)paren
(brace
id|flink-&gt;blink
op_assign
id|blink
suffix:semicolon
id|blink-&gt;flink
op_assign
id|flink
suffix:semicolon
)brace
DECL|function|sym_que_empty
r_static
id|__inline
r_int
id|sym_que_empty
c_func
(paren
r_struct
id|sym_quehead
op_star
id|head
)paren
(brace
r_return
id|head-&gt;flink
op_eq
id|head
suffix:semicolon
)brace
DECL|function|sym_que_splice
r_static
id|__inline
r_void
id|sym_que_splice
c_func
(paren
r_struct
id|sym_quehead
op_star
id|list
comma
r_struct
id|sym_quehead
op_star
id|head
)paren
(brace
r_struct
id|sym_quehead
op_star
id|first
op_assign
id|list-&gt;flink
suffix:semicolon
r_if
c_cond
(paren
id|first
op_ne
id|list
)paren
(brace
r_struct
id|sym_quehead
op_star
id|last
op_assign
id|list-&gt;blink
suffix:semicolon
r_struct
id|sym_quehead
op_star
id|at
op_assign
id|head-&gt;flink
suffix:semicolon
id|first-&gt;blink
op_assign
id|head
suffix:semicolon
id|head-&gt;flink
op_assign
id|first
suffix:semicolon
id|last-&gt;flink
op_assign
id|at
suffix:semicolon
id|at-&gt;blink
op_assign
id|last
suffix:semicolon
)brace
)brace
DECL|function|sym_que_move
r_static
id|__inline
r_void
id|sym_que_move
c_func
(paren
r_struct
id|sym_quehead
op_star
id|orig
comma
r_struct
id|sym_quehead
op_star
id|dest
)paren
(brace
r_struct
id|sym_quehead
op_star
id|first
comma
op_star
id|last
suffix:semicolon
id|first
op_assign
id|orig-&gt;flink
suffix:semicolon
r_if
c_cond
(paren
id|first
op_ne
id|orig
)paren
(brace
id|first-&gt;blink
op_assign
id|dest
suffix:semicolon
id|dest-&gt;flink
op_assign
id|first
suffix:semicolon
id|last
op_assign
id|orig-&gt;blink
suffix:semicolon
id|last-&gt;flink
op_assign
id|dest
suffix:semicolon
id|dest-&gt;blink
op_assign
id|last
suffix:semicolon
id|orig-&gt;flink
op_assign
id|orig
suffix:semicolon
id|orig-&gt;blink
op_assign
id|orig
suffix:semicolon
)brace
r_else
(brace
id|dest-&gt;flink
op_assign
id|dest
suffix:semicolon
id|dest-&gt;blink
op_assign
id|dest
suffix:semicolon
)brace
)brace
DECL|macro|sym_que_entry
mdefine_line|#define sym_que_entry(ptr, type, member) &bslash;&n;&t;((type *)((char *)(ptr)-(unsigned int)(&amp;((type *)0)-&gt;member)))
DECL|macro|sym_insque
mdefine_line|#define sym_insque(new, pos)&t;&t;__sym_que_add(new, pos, (pos)-&gt;flink)
DECL|macro|sym_remque
mdefine_line|#define sym_remque(el)&t;&t;&t;__sym_que_del((el)-&gt;blink, (el)-&gt;flink)
DECL|macro|sym_insque_head
mdefine_line|#define sym_insque_head(new, head)&t;__sym_que_add(new, head, (head)-&gt;flink)
DECL|function|sym_remque_head
r_static
id|__inline
r_struct
id|sym_quehead
op_star
id|sym_remque_head
c_func
(paren
r_struct
id|sym_quehead
op_star
id|head
)paren
(brace
r_struct
id|sym_quehead
op_star
id|elem
op_assign
id|head-&gt;flink
suffix:semicolon
r_if
c_cond
(paren
id|elem
op_ne
id|head
)paren
id|__sym_que_del
c_func
(paren
id|head
comma
id|elem-&gt;flink
)paren
suffix:semicolon
r_else
id|elem
op_assign
l_int|0
suffix:semicolon
r_return
id|elem
suffix:semicolon
)brace
DECL|macro|sym_insque_tail
mdefine_line|#define sym_insque_tail(new, head)&t;__sym_que_add(new, (head)-&gt;blink, head)
DECL|function|sym_remque_tail
r_static
id|__inline
r_struct
id|sym_quehead
op_star
id|sym_remque_tail
c_func
(paren
r_struct
id|sym_quehead
op_star
id|head
)paren
(brace
r_struct
id|sym_quehead
op_star
id|elem
op_assign
id|head-&gt;blink
suffix:semicolon
r_if
c_cond
(paren
id|elem
op_ne
id|head
)paren
id|__sym_que_del
c_func
(paren
id|elem-&gt;blink
comma
id|head
)paren
suffix:semicolon
r_else
id|elem
op_assign
l_int|0
suffix:semicolon
r_return
id|elem
suffix:semicolon
)brace
multiline_comment|/*&n; *  This one may be useful.&n; */
DECL|macro|FOR_EACH_QUEUED_ELEMENT
mdefine_line|#define FOR_EACH_QUEUED_ELEMENT(head, qp) &bslash;&n;&t;for (qp = (head)-&gt;flink; qp != (head); qp = qp-&gt;flink)
multiline_comment|/*&n; *  FreeBSD does not offer our kind of queue in the CAM CCB.&n; *  So, we have to cast.&n; */
DECL|macro|sym_qptr
mdefine_line|#define sym_qptr(p)&t;((struct sym_quehead *) (p))
multiline_comment|/*&n; *  Simple bitmap operations.&n; */
DECL|macro|sym_set_bit
mdefine_line|#define sym_set_bit(p, n)&t;(((u32 *)(p))[(n)&gt;&gt;5] |=  (1&lt;&lt;((n)&amp;0x1f)))
DECL|macro|sym_clr_bit
mdefine_line|#define sym_clr_bit(p, n)&t;(((u32 *)(p))[(n)&gt;&gt;5] &amp;= ~(1&lt;&lt;((n)&amp;0x1f)))
DECL|macro|sym_is_bit
mdefine_line|#define sym_is_bit(p, n)&t;(((u32 *)(p))[(n)&gt;&gt;5] &amp;   (1&lt;&lt;((n)&amp;0x1f)))
multiline_comment|/*&n; *  Portable but silly implemented byte order primitives.&n; */
macro_line|#if&t;BYTE_ORDER == BIG_ENDIAN
DECL|macro|__revb16
mdefine_line|#define __revb16(x) (&t;(((u16)(x) &amp; (u16)0x00ffU) &lt;&lt; 8) | &bslash;&n;&t;&t;&t;(((u16)(x) &amp; (u16)0xff00U) &gt;&gt; 8) &t;)
DECL|macro|__revb32
mdefine_line|#define __revb32(x) (&t;(((u32)(x) &amp; 0x000000ffU) &lt;&lt; 24) | &bslash;&n;&t;&t;&t;(((u32)(x) &amp; 0x0000ff00U) &lt;&lt;  8) | &bslash;&n;&t;&t;&t;(((u32)(x) &amp; 0x00ff0000U) &gt;&gt;  8) | &bslash;&n;&t;&t;&t;(((u32)(x) &amp; 0xff000000U) &gt;&gt; 24)&t;)
DECL|macro|__htole16
mdefine_line|#define __htole16(v)&t;__revb16(v)
DECL|macro|__htole32
mdefine_line|#define __htole32(v)&t;__revb32(v)
DECL|macro|__le16toh
mdefine_line|#define __le16toh(v)&t;__htole16(v)
DECL|macro|__le32toh
mdefine_line|#define __le32toh(v)&t;__htole32(v)
DECL|function|_htole16
r_static
id|__inline
id|u16
id|_htole16
c_func
(paren
id|u16
id|v
)paren
(brace
r_return
id|__htole16
c_func
(paren
id|v
)paren
suffix:semicolon
)brace
DECL|function|_htole32
r_static
id|__inline
id|u32
id|_htole32
c_func
(paren
id|u32
id|v
)paren
(brace
r_return
id|__htole32
c_func
(paren
id|v
)paren
suffix:semicolon
)brace
DECL|macro|_le16toh
mdefine_line|#define _le16toh&t;_htole16
DECL|macro|_le32toh
mdefine_line|#define _le32toh&t;_htole32
macro_line|#else&t;/* LITTLE ENDIAN */
DECL|macro|__htole16
mdefine_line|#define __htole16(v)&t;(v)
DECL|macro|__htole32
mdefine_line|#define __htole32(v)&t;(v)
DECL|macro|__le16toh
mdefine_line|#define __le16toh(v)&t;(v)
DECL|macro|__le32toh
mdefine_line|#define __le32toh(v)&t;(v)
DECL|macro|_htole16
mdefine_line|#define _htole16(v)&t;(v)
DECL|macro|_htole32
mdefine_line|#define _htole32(v)&t;(v)
DECL|macro|_le16toh
mdefine_line|#define _le16toh(v)&t;(v)
DECL|macro|_le32toh
mdefine_line|#define _le32toh(v)&t;(v)
macro_line|#endif&t;/* BYTE_ORDER */
multiline_comment|/*&n; * The below round up/down macros are to be used with a constant &n; * as argument (sizeof(...) for example), for the compiler to &n; * optimize the whole thing.&n; */
DECL|macro|_U_
mdefine_line|#define _U_(a,m)&t;(a)&lt;=(1&lt;&lt;m)?m:
DECL|macro|_D_
mdefine_line|#define _D_(a,m)&t;(a)&lt;(1&lt;&lt;(m+1))?m:
multiline_comment|/*&n; * Round up logarithm to base 2 of a 16 bit constant.&n; */
DECL|macro|_LGRU16_
mdefine_line|#define _LGRU16_(a) &bslash;&n;( &bslash;&n; _U_(a, 0)_U_(a, 1)_U_(a, 2)_U_(a, 3)_U_(a, 4)_U_(a, 5)_U_(a, 6)_U_(a, 7) &bslash;&n; _U_(a, 8)_U_(a, 9)_U_(a,10)_U_(a,11)_U_(a,12)_U_(a,13)_U_(a,14)_U_(a,15) &bslash;&n; 16)
multiline_comment|/*&n; * Round down logarithm to base 2 of a 16 bit constant.&n; */
DECL|macro|_LGRD16_
mdefine_line|#define _LGRD16_(a) &bslash;&n;( &bslash;&n; _D_(a, 0)_D_(a, 1)_D_(a, 2)_D_(a, 3)_D_(a, 4)_D_(a, 5)_D_(a, 6)_D_(a, 7) &bslash;&n; _D_(a, 8)_D_(a, 9)_D_(a,10)_D_(a,11)_D_(a,12)_D_(a,13)_D_(a,14)_D_(a,15) &bslash;&n; 16)
multiline_comment|/*&n; * Round up a 16 bit constant to the nearest power of 2.&n; */
DECL|macro|_SZRU16_
mdefine_line|#define _SZRU16_(a) ((a)==0?0:(1&lt;&lt;_LGRU16_(a)))
multiline_comment|/*&n; * Round down a 16 bit constant to the nearest power of 2.&n; */
DECL|macro|_SZRD16_
mdefine_line|#define _SZRD16_(a) ((a)==0?0:(1&lt;&lt;_LGRD16_(a)))
macro_line|#endif /* SYM_MISC_H */
eof
