multiline_comment|/*&n; * A constraint is a condition that must be satisfied in&n; * order for one or more permissions to be granted.&n; * Constraints are used to impose additional restrictions&n; * beyond the type-based rules in `te&squot; or the role-based&n; * transition rules in `rbac&squot;.  Constraints are typically&n; * used to prevent a process from transitioning to a new user&n; * identity or role unless it is in a privileged type.&n; * Constraints are likewise typically used to prevent a&n; * process from labeling an object with a different user&n; * identity.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SS_CONSTRAINT_H_
DECL|macro|_SS_CONSTRAINT_H_
mdefine_line|#define _SS_CONSTRAINT_H_
macro_line|#include &quot;ebitmap.h&quot;
DECL|macro|CEXPR_MAXDEPTH
mdefine_line|#define CEXPR_MAXDEPTH 5
DECL|struct|constraint_expr
r_struct
id|constraint_expr
(brace
DECL|macro|CEXPR_NOT
mdefine_line|#define CEXPR_NOT&t;&t;1 /* not expr */
DECL|macro|CEXPR_AND
mdefine_line|#define CEXPR_AND&t;&t;2 /* expr and expr */
DECL|macro|CEXPR_OR
mdefine_line|#define CEXPR_OR&t;&t;3 /* expr or expr */
DECL|macro|CEXPR_ATTR
mdefine_line|#define CEXPR_ATTR&t;&t;4 /* attr op attr */
DECL|macro|CEXPR_NAMES
mdefine_line|#define CEXPR_NAMES&t;&t;5 /* attr op names */
DECL|member|expr_type
id|u32
id|expr_type
suffix:semicolon
multiline_comment|/* expression type */
DECL|macro|CEXPR_USER
mdefine_line|#define CEXPR_USER 1&t;&t;/* user */
DECL|macro|CEXPR_ROLE
mdefine_line|#define CEXPR_ROLE 2&t;&t;/* role */
DECL|macro|CEXPR_TYPE
mdefine_line|#define CEXPR_TYPE 4&t;&t;/* type */
DECL|macro|CEXPR_TARGET
mdefine_line|#define CEXPR_TARGET 8&t;&t;/* target if set, source otherwise */
DECL|member|attr
id|u32
id|attr
suffix:semicolon
multiline_comment|/* attribute */
DECL|macro|CEXPR_EQ
mdefine_line|#define CEXPR_EQ     1&t;&t;/* == or eq */
DECL|macro|CEXPR_NEQ
mdefine_line|#define CEXPR_NEQ    2&t;&t;/* != */
DECL|macro|CEXPR_DOM
mdefine_line|#define CEXPR_DOM    3&t;&t;/* dom */
DECL|macro|CEXPR_DOMBY
mdefine_line|#define CEXPR_DOMBY  4&t;&t;/* domby  */
DECL|macro|CEXPR_INCOMP
mdefine_line|#define CEXPR_INCOMP 5&t;&t;/* incomp */
DECL|member|op
id|u32
id|op
suffix:semicolon
multiline_comment|/* operator */
DECL|member|names
r_struct
id|ebitmap
id|names
suffix:semicolon
multiline_comment|/* names */
DECL|member|next
r_struct
id|constraint_expr
op_star
id|next
suffix:semicolon
multiline_comment|/* next expression */
)brace
suffix:semicolon
DECL|struct|constraint_node
r_struct
id|constraint_node
(brace
DECL|member|permissions
id|u32
id|permissions
suffix:semicolon
multiline_comment|/* constrained permissions */
DECL|member|expr
r_struct
id|constraint_expr
op_star
id|expr
suffix:semicolon
multiline_comment|/* constraint on permissions */
DECL|member|next
r_struct
id|constraint_node
op_star
id|next
suffix:semicolon
multiline_comment|/* next constraint */
)brace
suffix:semicolon
macro_line|#endif&t;/* _SS_CONSTRAINT_H_ */
eof
