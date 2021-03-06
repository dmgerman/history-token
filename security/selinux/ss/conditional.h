multiline_comment|/* Authors: Karl MacMillan &lt;kmacmillan@tresys.com&gt;&n; *          Frank Mayer &lt;mayerf@tresys.com&gt;&n; *&n; * Copyright (C) 2003 - 2004 Tresys Technology, LLC&n; *&t;This program is free software; you can redistribute it and/or modify&n; *  &t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation, version 2.&n; */
macro_line|#ifndef _CONDITIONAL_H_
DECL|macro|_CONDITIONAL_H_
mdefine_line|#define _CONDITIONAL_H_
macro_line|#include &quot;avtab.h&quot;
macro_line|#include &quot;symtab.h&quot;
macro_line|#include &quot;policydb.h&quot;
DECL|macro|COND_EXPR_MAXDEPTH
mdefine_line|#define COND_EXPR_MAXDEPTH 10
multiline_comment|/*&n; * A conditional expression is a list of operators and operands&n; * in reverse polish notation.&n; */
DECL|struct|cond_expr
r_struct
id|cond_expr
(brace
DECL|macro|COND_BOOL
mdefine_line|#define COND_BOOL&t;1 /* plain bool */
DECL|macro|COND_NOT
mdefine_line|#define COND_NOT&t;2 /* !bool */
DECL|macro|COND_OR
mdefine_line|#define COND_OR&t;&t;3 /* bool || bool */
DECL|macro|COND_AND
mdefine_line|#define COND_AND&t;4 /* bool &amp;&amp; bool */
DECL|macro|COND_XOR
mdefine_line|#define COND_XOR&t;5 /* bool ^ bool */
DECL|macro|COND_EQ
mdefine_line|#define COND_EQ&t;&t;6 /* bool == bool */
DECL|macro|COND_NEQ
mdefine_line|#define COND_NEQ&t;7 /* bool != bool */
DECL|macro|COND_LAST
mdefine_line|#define COND_LAST&t;8
DECL|member|expr_type
id|__u32
id|expr_type
suffix:semicolon
DECL|member|bool
id|__u32
r_bool
suffix:semicolon
DECL|member|next
r_struct
id|cond_expr
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Each cond_node contains a list of rules to be enabled/disabled&n; * depending on the current value of the conditional expression. This&n; * struct is for that list.&n; */
DECL|struct|cond_av_list
r_struct
id|cond_av_list
(brace
DECL|member|node
r_struct
id|avtab_node
op_star
id|node
suffix:semicolon
DECL|member|next
r_struct
id|cond_av_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A cond node represents a conditional block in a policy. It&n; * contains a conditional expression, the current state of the expression,&n; * two lists of rules to enable/disable depending on the value of the&n; * expression (the true list corresponds to if and the false list corresponds&n; * to else)..&n; */
DECL|struct|cond_node
r_struct
id|cond_node
(brace
DECL|member|cur_state
r_int
id|cur_state
suffix:semicolon
DECL|member|expr
r_struct
id|cond_expr
op_star
id|expr
suffix:semicolon
DECL|member|true_list
r_struct
id|cond_av_list
op_star
id|true_list
suffix:semicolon
DECL|member|false_list
r_struct
id|cond_av_list
op_star
id|false_list
suffix:semicolon
DECL|member|next
r_struct
id|cond_node
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_int
id|cond_policydb_init
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_void
id|cond_policydb_destroy
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_int
id|cond_init_bool_indexes
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_int
id|cond_destroy_bool
c_func
(paren
r_void
op_star
id|key
comma
r_void
op_star
id|datum
comma
r_void
op_star
id|p
)paren
suffix:semicolon
r_int
id|cond_index_bool
c_func
(paren
r_void
op_star
id|key
comma
r_void
op_star
id|datum
comma
r_void
op_star
id|datap
)paren
suffix:semicolon
r_int
id|cond_read_bool
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_struct
id|hashtab
op_star
id|h
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|cond_read_list
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_void
id|cond_compute_av
c_func
(paren
r_struct
id|avtab
op_star
id|ctab
comma
r_struct
id|avtab_key
op_star
id|key
comma
r_struct
id|av_decision
op_star
id|avd
)paren
suffix:semicolon
r_int
id|evaluate_cond_node
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_struct
id|cond_node
op_star
id|node
)paren
suffix:semicolon
macro_line|#endif /* _CONDITIONAL_H_ */
eof
