macro_line|#ifndef _LINUX_PRIO_TREE_H
DECL|macro|_LINUX_PRIO_TREE_H
mdefine_line|#define _LINUX_PRIO_TREE_H
multiline_comment|/*&n; * Dummy version of include/linux/prio_tree.h, just for this patch:&n; * no radix priority search tree whatsoever, just implement interfaces&n; * using the old lists.&n; */
DECL|struct|prio_tree_root
r_struct
id|prio_tree_root
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|prio_tree_iter
r_struct
id|prio_tree_iter
(brace
DECL|member|not_used_yet
r_int
id|not_used_yet
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_PRIO_TREE_ROOT
mdefine_line|#define INIT_PRIO_TREE_ROOT(ptr)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&bslash;&n;&t;INIT_LIST_HEAD(&amp;(ptr)-&gt;list);&t;&bslash;&n;} while (0)&t;&t;&t;&t;&bslash;&n;
DECL|function|prio_tree_empty
r_static
r_inline
r_int
id|prio_tree_empty
c_func
(paren
r_const
r_struct
id|prio_tree_root
op_star
id|root
)paren
(brace
r_return
id|list_empty
c_func
(paren
op_amp
id|root-&gt;list
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_PRIO_TREE_H */
eof
