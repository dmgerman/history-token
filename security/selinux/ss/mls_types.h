multiline_comment|/*&n; * Type definitions for the multi-level security (MLS) policy.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
multiline_comment|/*&n; * Updated: Trusted Computer Solutions, Inc. &lt;dgoeddel@trustedcs.com&gt;&n; *&n; *&t;Support for enhanced MLS infrastructure.&n; *&n; * Copyright (C) 2004-2005 Trusted Computer Solutions, Inc.&n; */
macro_line|#ifndef _SS_MLS_TYPES_H_
DECL|macro|_SS_MLS_TYPES_H_
mdefine_line|#define _SS_MLS_TYPES_H_
macro_line|#include &quot;security.h&quot;
DECL|struct|mls_level
r_struct
id|mls_level
(brace
DECL|member|sens
id|u32
id|sens
suffix:semicolon
multiline_comment|/* sensitivity */
DECL|member|cat
r_struct
id|ebitmap
id|cat
suffix:semicolon
multiline_comment|/* category set */
)brace
suffix:semicolon
DECL|struct|mls_range
r_struct
id|mls_range
(brace
DECL|member|level
r_struct
id|mls_level
id|level
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* low == level[0], high == level[1] */
)brace
suffix:semicolon
DECL|function|mls_level_eq
r_static
r_inline
r_int
id|mls_level_eq
c_func
(paren
r_struct
id|mls_level
op_star
id|l1
comma
r_struct
id|mls_level
op_star
id|l2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|selinux_mls_enabled
)paren
r_return
l_int|1
suffix:semicolon
r_return
(paren
(paren
id|l1-&gt;sens
op_eq
id|l2-&gt;sens
)paren
op_logical_and
id|ebitmap_cmp
c_func
(paren
op_amp
id|l1-&gt;cat
comma
op_amp
id|l2-&gt;cat
)paren
)paren
suffix:semicolon
)brace
DECL|function|mls_level_dom
r_static
r_inline
r_int
id|mls_level_dom
c_func
(paren
r_struct
id|mls_level
op_star
id|l1
comma
r_struct
id|mls_level
op_star
id|l2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|selinux_mls_enabled
)paren
r_return
l_int|1
suffix:semicolon
r_return
(paren
(paren
id|l1-&gt;sens
op_ge
id|l2-&gt;sens
)paren
op_logical_and
id|ebitmap_contains
c_func
(paren
op_amp
id|l1-&gt;cat
comma
op_amp
id|l2-&gt;cat
)paren
)paren
suffix:semicolon
)brace
DECL|macro|mls_level_incomp
mdefine_line|#define mls_level_incomp(l1, l2) &bslash;&n;(!mls_level_dom((l1), (l2)) &amp;&amp; !mls_level_dom((l2), (l1)))
DECL|macro|mls_level_between
mdefine_line|#define mls_level_between(l1, l2, l3) &bslash;&n;(mls_level_dom((l1), (l2)) &amp;&amp; mls_level_dom((l3), (l1)))
DECL|macro|mls_range_contains
mdefine_line|#define mls_range_contains(r1, r2) &bslash;&n;(mls_level_dom(&amp;(r2).level[0], &amp;(r1).level[0]) &amp;&amp; &bslash;&n; mls_level_dom(&amp;(r1).level[1], &amp;(r2).level[1]))
macro_line|#endif&t;/* _SS_MLS_TYPES_H_ */
eof
