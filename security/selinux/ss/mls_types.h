multiline_comment|/*&n; * Type definitions for the multi-level security (MLS) policy.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SS_MLS_TYPES_H_
DECL|macro|_SS_MLS_TYPES_H_
mdefine_line|#define _SS_MLS_TYPES_H_
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
DECL|struct|mls_range_list
r_struct
id|mls_range_list
(brace
DECL|member|range
r_struct
id|mls_range
id|range
suffix:semicolon
DECL|member|next
r_struct
id|mls_range_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MLS_RELATION_DOM
mdefine_line|#define MLS_RELATION_DOM&t;1 /* source dominates */
DECL|macro|MLS_RELATION_DOMBY
mdefine_line|#define MLS_RELATION_DOMBY&t;2 /* target dominates */
DECL|macro|MLS_RELATION_EQ
mdefine_line|#define MLS_RELATION_EQ&t;&t;4 /* source and target are equivalent */
DECL|macro|MLS_RELATION_INCOMP
mdefine_line|#define MLS_RELATION_INCOMP&t;8 /* source and target are incomparable */
DECL|macro|mls_level_eq
mdefine_line|#define mls_level_eq(l1,l2) &bslash;&n;(((l1).sens == (l2).sens) &amp;&amp; ebitmap_cmp(&amp;(l1).cat,&amp;(l2).cat))
DECL|macro|mls_level_relation
mdefine_line|#define mls_level_relation(l1,l2) ( &bslash;&n;(((l1).sens == (l2).sens) &amp;&amp; ebitmap_cmp(&amp;(l1).cat,&amp;(l2).cat)) ? &bslash;&n;&t;&t;&t;&t;    MLS_RELATION_EQ : &bslash;&n;(((l1).sens &gt;= (l2).sens) &amp;&amp; ebitmap_contains(&amp;(l1).cat, &amp;(l2).cat)) ? &bslash;&n;&t;&t;&t;&t;    MLS_RELATION_DOM : &bslash;&n;(((l2).sens &gt;= (l1).sens) &amp;&amp; ebitmap_contains(&amp;(l2).cat, &amp;(l1).cat)) ? &bslash;&n;&t;&t;&t;&t;    MLS_RELATION_DOMBY : &bslash;&n;&t;&t;&t;&t;    MLS_RELATION_INCOMP )
DECL|macro|mls_range_contains
mdefine_line|#define mls_range_contains(r1,r2) &bslash;&n;((mls_level_relation((r1).level[0], (r2).level[0]) &amp; &bslash;&n;&t;  (MLS_RELATION_EQ | MLS_RELATION_DOMBY)) &amp;&amp; &bslash;&n;&t; (mls_level_relation((r1).level[1], (r2).level[1]) &amp; &bslash;&n;&t;  (MLS_RELATION_EQ | MLS_RELATION_DOM)))
multiline_comment|/*&n; * Every access vector permission is mapped to a set of MLS base&n; * permissions, based on the flow properties of the corresponding&n; * operation.&n; */
DECL|struct|mls_perms
r_struct
id|mls_perms
(brace
DECL|member|read
id|u32
id|read
suffix:semicolon
multiline_comment|/* permissions that map to `read&squot; */
DECL|member|readby
id|u32
id|readby
suffix:semicolon
multiline_comment|/* permissions that map to `readby&squot; */
DECL|member|write
id|u32
id|write
suffix:semicolon
multiline_comment|/* permissions that map to `write&squot; */
DECL|member|writeby
id|u32
id|writeby
suffix:semicolon
multiline_comment|/* permissions that map to `writeby&squot; */
)brace
suffix:semicolon
macro_line|#endif&t;/* _SS_MLS_TYPES_H_ */
eof
