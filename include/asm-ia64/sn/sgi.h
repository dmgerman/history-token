multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SGI_H
DECL|macro|_ASM_IA64_SN_SGI_H
mdefine_line|#define _ASM_IA64_SN_SGI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;&t;&t;/* for copy_??_user */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
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
DECL|enumerator|B_FALSE
DECL|enumerator|B_TRUE
DECL|typedef|boolean_t
r_typedef
r_enum
(brace
id|B_FALSE
comma
id|B_TRUE
)brace
id|boolean_t
suffix:semicolon
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
