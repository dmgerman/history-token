macro_line|#ifndef _LISTHELP_H
DECL|macro|_LISTHELP_H
mdefine_line|#define _LISTHELP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
multiline_comment|/* Header to do more comprehensive job than linux/list.h; assume list&n;   is first entry in structure. */
multiline_comment|/* Return pointer to first true entry, if any, or NULL.  A macro&n;   required to allow inlining of cmpfn. */
DECL|macro|LIST_FIND
mdefine_line|#define LIST_FIND(head, cmpfn, type, args...)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const struct list_head *__i, *__j = NULL;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT_READ_LOCK(head);&t;&t;&t;&t;&bslash;&n;&t;list_for_each(__i, (head))&t;&t;&t;&bslash;&n;&t;&t;if (cmpfn((const type)__i , ## args)) {&t;&bslash;&n;&t;&t;&t;__j = __i;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;(type)__j;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|LIST_FIND_W
mdefine_line|#define LIST_FIND_W(head, cmpfn, type, args...)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const struct list_head *__i, *__j = NULL;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT_WRITE_LOCK(head);&t;&t;&t;&bslash;&n;&t;list_for_each(__i, (head))&t;&t;&t;&bslash;&n;&t;&t;if (cmpfn((type)__i , ## args)) {&t;&bslash;&n;&t;&t;&t;__j = __i;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;(type)__j;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Just like LIST_FIND but we search backwards */
DECL|macro|LIST_FIND_B
mdefine_line|#define LIST_FIND_B(head, cmpfn, type, args...)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const struct list_head *__i, *__j = NULL;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT_READ_LOCK(head);&t;&t;&t;&t;&bslash;&n;&t;list_for_each_prev(__i, (head))&t;&t;&t;&bslash;&n;&t;&t;if (cmpfn((const type)__i , ## args)) {&t;&bslash;&n;&t;&t;&t;__j = __i;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;(type)__j;&t;&t;&t;&t;&t;&bslash;&n;})
r_static
r_inline
r_int
DECL|function|__list_cmp_same
id|__list_cmp_same
c_func
(paren
r_const
r_void
op_star
id|p1
comma
r_const
r_void
op_star
id|p2
)paren
(brace
r_return
id|p1
op_eq
id|p2
suffix:semicolon
)brace
multiline_comment|/* Is this entry in the list? */
r_static
r_inline
r_int
DECL|function|list_inlist
id|list_inlist
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_const
r_void
op_star
id|entry
)paren
(brace
r_return
id|LIST_FIND
c_func
(paren
id|head
comma
id|__list_cmp_same
comma
r_void
op_star
comma
id|entry
)paren
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Delete from list. */
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|macro|LIST_DELETE
mdefine_line|#define LIST_DELETE(head, oldentry)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT_WRITE_LOCK(head);&t;&t;&t;&t;&t;&bslash;&n;&t;if (!list_inlist(head, oldentry))&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;LIST_DELETE: %s:%u `%s&squot;(%p) not in %s.&bslash;n&quot;,&t;&bslash;&n;&t;&t;       __FILE__, __LINE__, #oldentry, oldentry, #head);&t;&bslash;&n;        else list_del((struct list_head *)oldentry);&t;&t;&t;&bslash;&n;} while(0)
macro_line|#else
DECL|macro|LIST_DELETE
mdefine_line|#define LIST_DELETE(head, oldentry) list_del((struct list_head *)oldentry)
macro_line|#endif
multiline_comment|/* Append. */
r_static
r_inline
r_void
DECL|function|list_append
id|list_append
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_void
op_star
r_new
)paren
(brace
id|ASSERT_WRITE_LOCK
c_func
(paren
id|head
)paren
suffix:semicolon
id|list_add
c_func
(paren
(paren
r_new
)paren
comma
(paren
id|head
)paren
op_member_access_from_pointer
id|prev
)paren
suffix:semicolon
)brace
multiline_comment|/* Prepend. */
r_static
r_inline
r_void
DECL|function|list_prepend
id|list_prepend
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_void
op_star
r_new
)paren
(brace
id|ASSERT_WRITE_LOCK
c_func
(paren
id|head
)paren
suffix:semicolon
id|list_add
c_func
(paren
r_new
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/* Insert according to ordering function; insert before first true. */
DECL|macro|LIST_INSERT
mdefine_line|#define LIST_INSERT(head, new, cmpfn)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct list_head *__i;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT_WRITE_LOCK(head);&t;&t;&t;&t;&bslash;&n;&t;list_for_each(__i, (head))&t;&t;&t;&t;&bslash;&n;&t;&t;if ((new), (typeof (new))__i)&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;list_add((struct list_head *)(new), __i-&gt;prev);&t;&t;&bslash;&n;} while(0)
multiline_comment|/* If the field after the list_head is a nul-terminated string, you&n;   can use these functions. */
DECL|function|__list_cmp_name
r_static
r_inline
r_int
id|__list_cmp_name
c_func
(paren
r_const
r_void
op_star
id|i
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|strcmp
c_func
(paren
id|name
comma
id|i
op_plus
r_sizeof
(paren
r_struct
id|list_head
)paren
)paren
op_eq
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns false if same name already in list, otherwise does insert. */
r_static
r_inline
r_int
DECL|function|list_named_insert
id|list_named_insert
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_void
op_star
r_new
)paren
(brace
r_if
c_cond
(paren
id|LIST_FIND
c_func
(paren
id|head
comma
id|__list_cmp_name
comma
r_void
op_star
comma
r_new
op_plus
r_sizeof
(paren
r_struct
id|list_head
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|list_prepend
c_func
(paren
id|head
comma
r_new
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Find this named element in the list. */
DECL|macro|list_named_find
mdefine_line|#define list_named_find(head, name)&t;&t;&t;&bslash;&n;LIST_FIND(head, __list_cmp_name, void *, name)
macro_line|#endif /*_LISTHELP_H*/
eof
