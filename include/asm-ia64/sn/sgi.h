multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SGI_H
DECL|macro|_ASM_IA64_SN_SGI_H
mdefine_line|#define _ASM_IA64_SN_SGI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/hwgfs.h&gt;
DECL|typedef|vertex_hdl_t
r_typedef
id|hwgfs_handle_t
id|vertex_hdl_t
suffix:semicolon
multiline_comment|/* Nice general name length that lots of people like to use */
macro_line|#ifndef MAXDEVNAME
DECL|macro|MAXDEVNAME
mdefine_line|#define MAXDEVNAME 256
macro_line|#endif
multiline_comment|/*&n; * Possible return values from graph routines.&n; */
DECL|enum|graph_error_e
r_typedef
r_enum
id|graph_error_e
(brace
DECL|enumerator|GRAPH_SUCCESS
id|GRAPH_SUCCESS
comma
multiline_comment|/* 0 */
DECL|enumerator|GRAPH_DUP
id|GRAPH_DUP
comma
multiline_comment|/* 1 */
DECL|enumerator|GRAPH_NOT_FOUND
id|GRAPH_NOT_FOUND
comma
multiline_comment|/* 2 */
DECL|enumerator|GRAPH_BAD_PARAM
id|GRAPH_BAD_PARAM
comma
multiline_comment|/* 3 */
DECL|enumerator|GRAPH_HIT_LIMIT
id|GRAPH_HIT_LIMIT
comma
multiline_comment|/* 4 */
DECL|enumerator|GRAPH_CANNOT_ALLOC
id|GRAPH_CANNOT_ALLOC
comma
multiline_comment|/* 5 */
DECL|enumerator|GRAPH_ILLEGAL_REQUEST
id|GRAPH_ILLEGAL_REQUEST
comma
multiline_comment|/* 6 */
DECL|enumerator|GRAPH_IN_USE
id|GRAPH_IN_USE
multiline_comment|/* 7 */
DECL|typedef|graph_error_t
)brace
id|graph_error_t
suffix:semicolon
DECL|macro|CNODEID_NONE
mdefine_line|#define CNODEID_NONE ((cnodeid_t)-1)
DECL|macro|CPU_NONE
mdefine_line|#define CPU_NONE&t;&t;(-1)
DECL|macro|GRAPH_VERTEX_NONE
mdefine_line|#define GRAPH_VERTEX_NONE ((vertex_hdl_t)-1)
multiline_comment|/*&n; * Defines for individual WARs. Each is a bitmask of applicable&n; * part revision numbers. (1 &lt;&lt; 1) == rev A, (1 &lt;&lt; 2) == rev B,&n; * (3 &lt;&lt; 1) == (rev A or rev B), etc&n; */
DECL|macro|PV854697
mdefine_line|#define PV854697 (~0)     /* PIC: write 64bit regs as 64bits. permanent */
DECL|macro|PV854827
mdefine_line|#define PV854827 (~0UL)   /* PIC: fake widget 0xf presence bit. permanent */
DECL|macro|PV855271
mdefine_line|#define PV855271 (1 &lt;&lt; 1) /* PIC: use virt chan iff 64-bit device. */
DECL|macro|PV878674
mdefine_line|#define PV878674 (~0)     /* PIC: Dont allow 64bit PIOs.  permanent */
DECL|macro|PV855272
mdefine_line|#define PV855272 (1 &lt;&lt; 1) /* PIC: runaway interrupt WAR */
DECL|macro|PV856155
mdefine_line|#define PV856155 (1 &lt;&lt; 1) /* PIC: arbitration WAR */
DECL|macro|PV856864
mdefine_line|#define PV856864 (1 &lt;&lt; 1) /* PIC: lower timeout to free TNUMs quicker */
DECL|macro|PV856866
mdefine_line|#define PV856866 (1 &lt;&lt; 1) /* PIC: avoid rrb&squot;s 0/1/8/9. */
DECL|macro|PV862253
mdefine_line|#define PV862253 (1 &lt;&lt; 1) /* PIC: don&squot;t enable write req RAM parity checking */
DECL|macro|PV867308
mdefine_line|#define PV867308 (3 &lt;&lt; 1) /* PIC: make LLP error interrupts FATAL for PIC */
multiline_comment|/*&n; * No code is complete without an Assertion macro&n; */
macro_line|#if defined(DISABLE_ASSERT)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr)
DECL|macro|ASSERT_ALWAYS
mdefine_line|#define ASSERT_ALWAYS(expr)
macro_line|#else
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr)  do {&t;&bslash;&n;        if(!(expr)) { &bslash;&n;&t;&t;printk( &quot;Assertion [%s] failed! %s:%s(line=%d)&bslash;n&quot;,&bslash;&n;&t;&t;&t;#expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;&t;&t;panic(&quot;Assertion panic&bslash;n&quot;); &t;&bslash;&n;        } } while(0)
DECL|macro|ASSERT_ALWAYS
mdefine_line|#define ASSERT_ALWAYS(expr)&t;do {&bslash;&n;        if(!(expr)) { &bslash;&n;&t;&t;printk( &quot;Assertion [%s] failed! %s:%s(line=%d)&bslash;n&quot;,&bslash;&n;&t;&t;&t;#expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;&t;&t;panic(&quot;Assertion always panic&bslash;n&quot;); &t;&bslash;&n;        } } while(0)
macro_line|#endif&t;/* DISABLE_ASSERT */
macro_line|#endif /* _ASM_IA64_SN_SGI_H */
eof
