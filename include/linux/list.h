macro_line|#ifndef _LINUX_LIST_H
DECL|macro|_LINUX_LIST_H
mdefine_line|#define _LINUX_LIST_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/prefetch.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Simple doubly linked list implementation.&n; *&n; * Some of the internal functions (&quot;__xxx&quot;) are useful when&n; * manipulating whole lists rather than single entries, as&n; * sometimes we already know the next/prev entries and we can&n; * generate better code by using them directly rather than&n; * using the generic single-entry routines.&n; */
DECL|struct|list_head
r_struct
id|list_head
(brace
DECL|member|next
DECL|member|prev
r_struct
id|list_head
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LIST_HEAD_INIT
mdefine_line|#define LIST_HEAD_INIT(name) { &amp;(name), &amp;(name) }
DECL|macro|LIST_HEAD
mdefine_line|#define LIST_HEAD(name) &bslash;&n;&t;struct list_head name = LIST_HEAD_INIT(name)
DECL|macro|INIT_LIST_HEAD
mdefine_line|#define INIT_LIST_HEAD(ptr) do { &bslash;&n;&t;(ptr)-&gt;next = (ptr); (ptr)-&gt;prev = (ptr); &bslash;&n;} while (0)
multiline_comment|/*&n; * Insert a new entry between two known consecutive entries. &n; *&n; * This is only for internal list manipulation where we know&n; * the prev/next entries already!&n; */
DECL|function|__list_add
r_static
r_inline
r_void
id|__list_add
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|prev
comma
r_struct
id|list_head
op_star
id|next
)paren
(brace
id|next-&gt;prev
op_assign
r_new
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
id|next
suffix:semicolon
r_new
op_member_access_from_pointer
id|prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
r_new
suffix:semicolon
)brace
multiline_comment|/**&n; * list_add - add a new entry&n; * @new: new entry to be added&n; * @head: list head to add it after&n; *&n; * Insert a new entry after the specified head.&n; * This is good for implementing stacks.&n; */
DECL|function|list_add
r_static
r_inline
r_void
id|list_add
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add
c_func
(paren
r_new
comma
id|head
comma
id|head-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_add_tail - add a new entry&n; * @new: new entry to be added&n; * @head: list head to add it before&n; *&n; * Insert a new entry before the specified head.&n; * This is useful for implementing queues.&n; */
DECL|function|list_add_tail
r_static
r_inline
r_void
id|list_add_tail
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add
c_func
(paren
r_new
comma
id|head-&gt;prev
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert a new entry between two known consecutive entries. &n; *&n; * This is only for internal list manipulation where we know&n; * the prev/next entries already!&n; */
DECL|function|__list_add_rcu
r_static
id|__inline__
r_void
id|__list_add_rcu
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|prev
comma
r_struct
id|list_head
op_star
id|next
)paren
(brace
r_new
op_member_access_from_pointer
id|next
op_assign
id|next
suffix:semicolon
r_new
op_member_access_from_pointer
id|prev
op_assign
id|prev
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
id|next-&gt;prev
op_assign
r_new
suffix:semicolon
id|prev-&gt;next
op_assign
r_new
suffix:semicolon
)brace
multiline_comment|/**&n; * list_add_rcu - add a new entry to rcu-protected list&n; * @new: new entry to be added&n; * @head: list head to add it after&n; *&n; * Insert a new entry after the specified head.&n; * This is good for implementing stacks.&n; */
DECL|function|list_add_rcu
r_static
id|__inline__
r_void
id|list_add_rcu
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add_rcu
c_func
(paren
r_new
comma
id|head
comma
id|head-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_add_tail_rcu - add a new entry to rcu-protected list&n; * @new: new entry to be added&n; * @head: list head to add it before&n; *&n; * Insert a new entry before the specified head.&n; * This is useful for implementing queues.&n; */
DECL|function|list_add_tail_rcu
r_static
id|__inline__
r_void
id|list_add_tail_rcu
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add_rcu
c_func
(paren
r_new
comma
id|head-&gt;prev
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a list entry by making the prev/next entries&n; * point to each other.&n; *&n; * This is only for internal list manipulation where we know&n; * the prev/next entries already!&n; */
DECL|function|__list_del
r_static
r_inline
r_void
id|__list_del
c_func
(paren
r_struct
id|list_head
op_star
id|prev
comma
r_struct
id|list_head
op_star
id|next
)paren
(brace
id|next-&gt;prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
id|next
suffix:semicolon
)brace
multiline_comment|/**&n; * list_del - deletes entry from list.&n; * @entry: the element to delete from the list.&n; * Note: list_empty on entry does not return true after this, the entry is&n; * in an undefined state.&n; */
DECL|function|list_del
r_static
r_inline
r_void
id|list_del
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
id|__list_del
c_func
(paren
id|entry-&gt;prev
comma
id|entry-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_del_rcu - deletes entry from list without re-initialization&n; * @entry: the element to delete from the list.&n; * Note: list_empty on entry does not return true after this, &n; * the entry is in an undefined state. It is useful for RCU based&n; * lockfree traversal.&n; */
DECL|function|list_del_rcu
r_static
r_inline
r_void
id|list_del_rcu
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
id|__list_del
c_func
(paren
id|entry-&gt;prev
comma
id|entry-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_del_init - deletes entry from list and reinitialize it.&n; * @entry: the element to delete from the list.&n; */
DECL|function|list_del_init
r_static
r_inline
r_void
id|list_del_init
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
id|__list_del
c_func
(paren
id|entry-&gt;prev
comma
id|entry-&gt;next
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_move - delete from one list and add as another&squot;s head&n; * @list: the entry to move&n; * @head: the head that will precede our entry&n; */
DECL|function|list_move
r_static
r_inline
r_void
id|list_move
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_del
c_func
(paren
id|list-&gt;prev
comma
id|list-&gt;next
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|list
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_move_tail - delete from one list and add as another&squot;s tail&n; * @list: the entry to move&n; * @head: the head that will follow our entry&n; */
DECL|function|list_move_tail
r_static
r_inline
r_void
id|list_move_tail
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_del
c_func
(paren
id|list-&gt;prev
comma
id|list-&gt;next
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
id|list
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_empty - tests whether a list is empty&n; * @head: the list to test.&n; */
DECL|function|list_empty
r_static
r_inline
r_int
id|list_empty
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_return
id|head-&gt;next
op_eq
id|head
suffix:semicolon
)brace
DECL|function|__list_splice
r_static
r_inline
r_void
id|__list_splice
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|first
op_assign
id|list-&gt;next
suffix:semicolon
r_struct
id|list_head
op_star
id|last
op_assign
id|list-&gt;prev
suffix:semicolon
r_struct
id|list_head
op_star
id|at
op_assign
id|head-&gt;next
suffix:semicolon
id|first-&gt;prev
op_assign
id|head
suffix:semicolon
id|head-&gt;next
op_assign
id|first
suffix:semicolon
id|last-&gt;next
op_assign
id|at
suffix:semicolon
id|at-&gt;prev
op_assign
id|last
suffix:semicolon
)brace
multiline_comment|/**&n; * list_splice - join two lists&n; * @list: the new list to add.&n; * @head: the place to add it in the first list.&n; */
DECL|function|list_splice
r_static
r_inline
r_void
id|list_splice
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|list
)paren
)paren
id|__list_splice
c_func
(paren
id|list
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_splice_init - join two lists and reinitialise the emptied list.&n; * @list: the new list to add.&n; * @head: the place to add it in the first list.&n; *&n; * The list at @list is reinitialised&n; */
DECL|function|list_splice_init
r_static
r_inline
r_void
id|list_splice_init
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|list
)paren
)paren
(brace
id|__list_splice
c_func
(paren
id|list
comma
id|head
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * list_entry - get the struct for this entry&n; * @ptr:&t;the &amp;struct list_head pointer.&n; * @type:&t;the type of the struct this is embedded in.&n; * @member:&t;the name of the list_struct within the struct.&n; */
DECL|macro|list_entry
mdefine_line|#define list_entry(ptr, type, member) &bslash;&n;&t;container_of(ptr, type, member)
multiline_comment|/**&n; * list_for_each&t;-&t;iterate over a list&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each
mdefine_line|#define list_for_each(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;next, prefetch(pos-&gt;next); pos != (head); &bslash;&n;        &t;pos = pos-&gt;next, prefetch(pos-&gt;next))
multiline_comment|/**&n; * __list_for_each&t;-&t;iterate over a list&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @head:&t;the head for your list.&n; *&n; * This variant differs from list_for_each() in that it&squot;s the&n; * simplest possible list iteration code, no prefetching is done.&n; * Use this for code that knows the list to be very short (empty&n; * or 1 entry) most of the time.&n; */
DECL|macro|__list_for_each
mdefine_line|#define __list_for_each(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;next; pos != (head); pos = pos-&gt;next)
multiline_comment|/**&n; * list_for_each_prev&t;-&t;iterate over a list backwards&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each_prev
mdefine_line|#define list_for_each_prev(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;prev, prefetch(pos-&gt;prev); pos != (head); &bslash;&n;        &t;pos = pos-&gt;prev, prefetch(pos-&gt;prev))
multiline_comment|/**&n; * list_for_each_safe&t;-&t;iterate over a list safe against removal of list entry&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @n:&t;&t;another &amp;struct list_head to use as temporary storage&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each_safe
mdefine_line|#define list_for_each_safe(pos, n, head) &bslash;&n;&t;for (pos = (head)-&gt;next, n = pos-&gt;next; pos != (head); &bslash;&n;&t;&t;pos = n, n = pos-&gt;next)
multiline_comment|/**&n; * list_for_each_entry&t;-&t;iterate over list of given type&n; * @pos:&t;the type * to use as a loop counter.&n; * @head:&t;the head for your list.&n; * @member:&t;the name of the list_struct within the struct.&n; */
DECL|macro|list_for_each_entry
mdefine_line|#define list_for_each_entry(pos, head, member)&t;&t;&t;&t;&bslash;&n;&t;for (pos = list_entry((head)-&gt;next, typeof(*pos), member),&t;&bslash;&n;&t;&t;     prefetch(pos-&gt;member.next);&t;&t;&t;&bslash;&n;&t;     &amp;pos-&gt;member != (head); &t;&t;&t;&t;&t;&bslash;&n;&t;     pos = list_entry(pos-&gt;member.next, typeof(*pos), member),&t;&bslash;&n;&t;&t;     prefetch(pos-&gt;member.next))
multiline_comment|/**&n; * list_for_each_entry_reverse - iterate backwards over list of given type.&n; * @pos:&t;the type * to use as a loop counter.&n; * @head:&t;the head for your list.&n; * @member:&t;the name of the list_struct within the struct.&n; */
DECL|macro|list_for_each_entry_reverse
mdefine_line|#define list_for_each_entry_reverse(pos, head, member)&t;&t;&t;&bslash;&n;&t;for (pos = list_entry((head)-&gt;prev, typeof(*pos), member),&t;&bslash;&n;&t;&t;     prefetch(pos-&gt;member.prev);&t;&t;&t;&bslash;&n;&t;     &amp;pos-&gt;member != (head); &t;&t;&t;&t;&t;&bslash;&n;&t;     pos = list_entry(pos-&gt;member.prev, typeof(*pos), member),&t;&bslash;&n;&t;&t;     prefetch(pos-&gt;member.prev))
multiline_comment|/**&n; * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry&n; * @pos:&t;the type * to use as a loop counter.&n; * @n:&t;&t;another type * to use as temporary storage&n; * @head:&t;the head for your list.&n; * @member:&t;the name of the list_struct within the struct.&n; */
DECL|macro|list_for_each_entry_safe
mdefine_line|#define list_for_each_entry_safe(pos, n, head, member)&t;&t;&t;&bslash;&n;&t;for (pos = list_entry((head)-&gt;next, typeof(*pos), member),&t;&bslash;&n;&t;&t;n = list_entry(pos-&gt;member.next, typeof(*pos), member);&t;&bslash;&n;&t;     &amp;pos-&gt;member != (head); &t;&t;&t;&t;&t;&bslash;&n;&t;     pos = n, n = list_entry(n-&gt;member.next, typeof(*n), member))
multiline_comment|/**&n; * list_for_each_rcu&t;-&t;iterate over an rcu-protected list&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each_rcu
mdefine_line|#define list_for_each_rcu(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;next, prefetch(pos-&gt;next); pos != (head); &bslash;&n;        &t;pos = pos-&gt;next, ({ smp_read_barrier_depends(); 0;}), prefetch(pos-&gt;next))
DECL|macro|__list_for_each_rcu
mdefine_line|#define __list_for_each_rcu(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;next; pos != (head); &bslash;&n;        &t;pos = pos-&gt;next, ({ smp_read_barrier_depends(); 0;}))
multiline_comment|/**&n; * list_for_each_safe_rcu&t;-&t;iterate over an rcu-protected list safe&n; *&t;&t;&t;&t;&t;against removal of list entry&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @n:&t;&t;another &amp;struct list_head to use as temporary storage&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each_safe_rcu
mdefine_line|#define list_for_each_safe_rcu(pos, n, head) &bslash;&n;&t;for (pos = (head)-&gt;next, n = pos-&gt;next; pos != (head); &bslash;&n;&t;&t;pos = n, ({ smp_read_barrier_depends(); 0;}), n = pos-&gt;next)
multiline_comment|/**&n; * list_for_each_entry_rcu&t;-&t;iterate over rcu list of given type&n; * @pos:&t;the type * to use as a loop counter.&n; * @head:&t;the head for your list.&n; * @member:&t;the name of the list_struct within the struct.&n; */
DECL|macro|list_for_each_entry_rcu
mdefine_line|#define list_for_each_entry_rcu(pos, head, member)&t;&t;&t;&bslash;&n;&t;for (pos = list_entry((head)-&gt;next, typeof(*pos), member),&t;&bslash;&n;&t;&t;     prefetch(pos-&gt;member.next);&t;&t;&t;&bslash;&n;&t;     &amp;pos-&gt;member != (head); &t;&t;&t;&t;&t;&bslash;&n;&t;     pos = list_entry(pos-&gt;member.next, typeof(*pos), member),&t;&bslash;&n;&t;&t;     ({ smp_read_barrier_depends(); 0;}),&t;&t;&bslash;&n;&t;&t;     prefetch(pos-&gt;member.next))
multiline_comment|/**&n; * list_for_each_continue_rcu&t;-&t;iterate over an rcu-protected list &n; *&t;&t;&t;continuing from existing point.&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each_continue_rcu
mdefine_line|#define list_for_each_continue_rcu(pos, head) &bslash;&n;&t;for ((pos) = (pos)-&gt;next, prefetch((pos)-&gt;next); (pos) != (head); &bslash;&n;        &t;(pos) = (pos)-&gt;next, ({ smp_read_barrier_depends(); 0;}), prefetch((pos)-&gt;next))
multiline_comment|/* &n; * Double linked lists with a single pointer list head. &n; * Mostly useful for hash tables where the two pointer list head is &n; * too wasteful.&n; * You lose the ability to access the tail in O(1).&n; */
DECL|struct|hlist_head
r_struct
id|hlist_head
(brace
DECL|member|first
r_struct
id|hlist_node
op_star
id|first
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hlist_node
r_struct
id|hlist_node
(brace
DECL|member|next
DECL|member|pprev
r_struct
id|hlist_node
op_star
id|next
comma
op_star
op_star
id|pprev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HLIST_HEAD_INIT
mdefine_line|#define HLIST_HEAD_INIT { .first = NULL } 
DECL|macro|HLIST_HEAD
mdefine_line|#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }
DECL|macro|INIT_HLIST_HEAD
mdefine_line|#define INIT_HLIST_HEAD(ptr) ((ptr)-&gt;first = NULL) 
DECL|macro|INIT_HLIST_NODE
mdefine_line|#define INIT_HLIST_NODE(ptr) ((ptr)-&gt;next = NULL, (ptr)-&gt;pprev = NULL)
DECL|function|hlist_unhashed
r_static
id|__inline__
r_int
id|hlist_unhashed
c_func
(paren
r_struct
id|hlist_node
op_star
id|h
)paren
(brace
r_return
op_logical_neg
id|h-&gt;pprev
suffix:semicolon
)brace
DECL|function|hlist_empty
r_static
id|__inline__
r_int
id|hlist_empty
c_func
(paren
r_struct
id|hlist_head
op_star
id|h
)paren
(brace
r_return
op_logical_neg
id|h-&gt;first
suffix:semicolon
)brace
DECL|function|__hlist_del
r_static
id|__inline__
r_void
id|__hlist_del
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
)paren
(brace
r_struct
id|hlist_node
op_star
id|next
op_assign
id|n-&gt;next
suffix:semicolon
r_struct
id|hlist_node
op_star
op_star
id|pprev
op_assign
id|n-&gt;pprev
suffix:semicolon
op_star
id|pprev
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
id|next-&gt;pprev
op_assign
id|pprev
suffix:semicolon
)brace
DECL|function|hlist_del
r_static
id|__inline__
r_void
id|hlist_del
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;pprev
)paren
id|__hlist_del
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|macro|hlist_del_rcu
mdefine_line|#define hlist_del_rcu hlist_del  /* list_del_rcu is identical too? */
DECL|function|hlist_del_init
r_static
id|__inline__
r_void
id|hlist_del_init
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;pprev
)paren
(brace
id|__hlist_del
c_func
(paren
id|n
)paren
suffix:semicolon
id|INIT_HLIST_NODE
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
)brace
DECL|function|hlist_add_head
r_static
id|__inline__
r_void
id|hlist_add_head
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
comma
r_struct
id|hlist_head
op_star
id|h
)paren
(brace
r_struct
id|hlist_node
op_star
id|first
op_assign
id|h-&gt;first
suffix:semicolon
id|n-&gt;next
op_assign
id|first
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
id|first-&gt;pprev
op_assign
op_amp
id|n-&gt;next
suffix:semicolon
id|h-&gt;first
op_assign
id|n
suffix:semicolon
id|n-&gt;pprev
op_assign
op_amp
id|h-&gt;first
suffix:semicolon
)brace
DECL|function|hlist_add_head_rcu
r_static
id|__inline__
r_void
id|hlist_add_head_rcu
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
comma
r_struct
id|hlist_head
op_star
id|h
)paren
(brace
r_struct
id|hlist_node
op_star
id|first
op_assign
id|h-&gt;first
suffix:semicolon
id|n-&gt;next
op_assign
id|first
suffix:semicolon
id|n-&gt;pprev
op_assign
op_amp
id|h-&gt;first
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
id|first-&gt;pprev
op_assign
op_amp
id|n-&gt;next
suffix:semicolon
id|h-&gt;first
op_assign
id|n
suffix:semicolon
)brace
multiline_comment|/* next must be != NULL */
DECL|function|hlist_add_before
r_static
id|__inline__
r_void
id|hlist_add_before
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
comma
r_struct
id|hlist_node
op_star
id|next
)paren
(brace
id|n-&gt;pprev
op_assign
id|next-&gt;pprev
suffix:semicolon
id|n-&gt;next
op_assign
id|next
suffix:semicolon
id|next-&gt;pprev
op_assign
op_amp
id|n-&gt;next
suffix:semicolon
op_star
(paren
id|n-&gt;pprev
)paren
op_assign
id|n
suffix:semicolon
)brace
DECL|function|hlist_add_after
r_static
id|__inline__
r_void
id|hlist_add_after
c_func
(paren
r_struct
id|hlist_node
op_star
id|n
comma
r_struct
id|hlist_node
op_star
id|next
)paren
(brace
id|next-&gt;next
op_assign
id|n-&gt;next
suffix:semicolon
op_star
(paren
id|next-&gt;pprev
)paren
op_assign
id|n
suffix:semicolon
id|n-&gt;next
op_assign
id|next
suffix:semicolon
)brace
DECL|macro|hlist_entry
mdefine_line|#define hlist_entry(ptr, type, member) container_of(ptr,type,member)
multiline_comment|/* Cannot easily do prefetch unfortunately */
DECL|macro|hlist_for_each
mdefine_line|#define hlist_for_each(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;first; pos &amp;&amp; ({ prefetch(pos-&gt;next); 1; }); &bslash;&n;&t;     pos = pos-&gt;next) 
DECL|macro|hlist_for_each_safe
mdefine_line|#define hlist_for_each_safe(pos, n, head) &bslash;&n;&t;for (pos = (head)-&gt;first; n = pos ? pos-&gt;next : 0, pos; &bslash;&n;&t;     pos = n)
multiline_comment|/**&n; * hlist_for_each_entry&t;- iterate over list of given type&n; * @tpos:&t;the type * to use as a loop counter.&n; * @pos:&t;the &amp;struct hlist_node to use as a loop counter.&n; * @head:&t;the head for your list.&n; * @member:&t;the name of the hlist_node within the struct.&n; */
DECL|macro|hlist_for_each_entry
mdefine_line|#define hlist_for_each_entry(tpos, pos, head, member)&t;&t;&t; &bslash;&n;&t;for (pos = (head)-&gt;first;&t;&t;&t;&t;&t; &bslash;&n;&t;     pos &amp;&amp; ({ prefetch(pos-&gt;next); 1;}) &amp;&amp;&t;&t;&t; &bslash;&n;&t;&t;({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); &bslash;&n;&t;     pos = pos-&gt;next)
multiline_comment|/**&n; * hlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry&n; * @tpos:&t;the type * to use as a loop counter.&n; * @pos:&t;the &amp;struct hlist_node to use as a loop counter.&n; * @n:&t;&t;another &amp;struct hlist_node to use as temporary storage&n; * @head:&t;the head for your list.&n; * @member:&t;the name of the hlist_node within the struct.&n; */
DECL|macro|hlist_for_each_entry_safe
mdefine_line|#define hlist_for_each_entry_safe(tpos, pos, n, head, member) &t;&t; &bslash;&n;&t;for (pos = (head)-&gt;first;&t;&t;&t;&t;&t; &bslash;&n;&t;     pos &amp;&amp; ({ n = pos-&gt;next; 1; }) &amp;&amp; &t;&t;&t;&t; &bslash;&n;&t;&t;({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); &bslash;&n;&t;     pos = n)
macro_line|#else
macro_line|#warning &quot;don&squot;t include kernel headers in userspace&quot;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
