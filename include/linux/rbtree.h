multiline_comment|/*&n;  Red Black Trees&n;  (C) 1999  Andrea Arcangeli &lt;andrea@suse.de&gt;&n;  &n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2 of the License, or&n;  (at your option) any later version.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;  linux/include/linux/rbtree.h&n;&n;  To use rbtrees you&squot;ll have to implement your own insert and search cores.&n;  This will avoid us to use callbacks and to drop drammatically performances.&n;  I know it&squot;s not the cleaner way,  but in C (not in C++) to get&n;  performances and genericity...&n;&n;  Some example of insert and search follows here. The search is a plain&n;  normal search over an ordered tree. The insert instead must be implemented&n;  int two steps: as first thing the code must insert the element in&n;  order as a red leaf in the tree, then the support library function&n;  rb_insert_color() must be called. Such function will do the&n;  not trivial work to rebalance the rbtree if necessary.&n;&n;-----------------------------------------------------------------------&n;static inline struct page * rb_search_page_cache(struct inode * inode,&n;&t;&t;&t;&t;&t;&t; unsigned long offset)&n;{&n;&t;struct rb_node * n = inode-&gt;i_rb_page_cache.rb_node;&n;&t;struct page * page;&n;&n;&t;while (n)&n;&t;{&n;&t;&t;page = rb_entry(n, struct page, rb_page_cache);&n;&n;&t;&t;if (offset &lt; page-&gt;offset)&n;&t;&t;&t;n = n-&gt;rb_left;&n;&t;&t;else if (offset &gt; page-&gt;offset)&n;&t;&t;&t;n = n-&gt;rb_right;&n;&t;&t;else&n;&t;&t;&t;return page;&n;&t;}&n;&t;return NULL;&n;}&n;&n;static inline struct page * __rb_insert_page_cache(struct inode * inode,&n;&t;&t;&t;&t;&t;&t;   unsigned long offset,&n;&t;&t;&t;&t;&t;&t;   struct rb_node * node)&n;{&n;&t;struct rb_node ** p = &amp;inode-&gt;i_rb_page_cache.rb_node;&n;&t;struct rb_node * parent = NULL;&n;&t;struct page * page;&n;&n;&t;while (*p)&n;&t;{&n;&t;&t;parent = *p;&n;&t;&t;page = rb_entry(parent, struct page, rb_page_cache);&n;&n;&t;&t;if (offset &lt; page-&gt;offset)&n;&t;&t;&t;p = &amp;(*p)-&gt;rb_left;&n;&t;&t;else if (offset &gt; page-&gt;offset)&n;&t;&t;&t;p = &amp;(*p)-&gt;rb_right;&n;&t;&t;else&n;&t;&t;&t;return page;&n;&t;}&n;&n;&t;rb_link_node(node, parent, p);&n;&n;&t;return NULL;&n;}&n;&n;static inline struct page * rb_insert_page_cache(struct inode * inode,&n;&t;&t;&t;&t;&t;&t; unsigned long offset,&n;&t;&t;&t;&t;&t;&t; struct rb_node * node)&n;{&n;&t;struct page * ret;&n;&t;if ((ret = __rb_insert_page_cache(inode, offset, node)))&n;&t;&t;goto out;&n;&t;rb_insert_color(node, &amp;inode-&gt;i_rb_page_cache);&n; out:&n;&t;return ret;&n;}&n;-----------------------------------------------------------------------&n;*/
macro_line|#ifndef&t;_LINUX_RBTREE_H
DECL|macro|_LINUX_RBTREE_H
mdefine_line|#define&t;_LINUX_RBTREE_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
DECL|struct|rb_node
r_struct
id|rb_node
(brace
DECL|member|rb_parent
r_struct
id|rb_node
op_star
id|rb_parent
suffix:semicolon
DECL|member|rb_color
r_int
id|rb_color
suffix:semicolon
DECL|macro|RB_RED
mdefine_line|#define&t;RB_RED&t;&t;0
DECL|macro|RB_BLACK
mdefine_line|#define&t;RB_BLACK&t;1
DECL|member|rb_right
r_struct
id|rb_node
op_star
id|rb_right
suffix:semicolon
DECL|member|rb_left
r_struct
id|rb_node
op_star
id|rb_left
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rb_root
r_struct
id|rb_root
(brace
DECL|member|rb_node
r_struct
id|rb_node
op_star
id|rb_node
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RB_ROOT
mdefine_line|#define RB_ROOT&t;(struct rb_root) { NULL, }
DECL|macro|rb_entry
mdefine_line|#define&t;rb_entry(ptr, type, member)&t;&t;&t;&t;&t;&bslash;&n;&t;((type *)((char *)(ptr)-(unsigned long)(&amp;((type *)0)-&gt;member)))
r_extern
r_void
id|rb_insert_color
c_func
(paren
r_struct
id|rb_node
op_star
comma
r_struct
id|rb_root
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rb_erase
c_func
(paren
r_struct
id|rb_node
op_star
comma
r_struct
id|rb_root
op_star
)paren
suffix:semicolon
multiline_comment|/* Find logical next and previous nodes in a tree */
r_extern
r_struct
id|rb_node
op_star
id|rb_next
c_func
(paren
r_struct
id|rb_node
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rb_node
op_star
id|rb_prev
c_func
(paren
r_struct
id|rb_node
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rb_node
op_star
id|rb_first
c_func
(paren
r_struct
id|rb_root
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rb_node
op_star
id|rb_last
c_func
(paren
r_struct
id|rb_root
op_star
)paren
suffix:semicolon
multiline_comment|/* Fast replacement of a single node without remove/rebalance/add/rebalance */
r_extern
r_void
id|rb_replace_node
c_func
(paren
r_struct
id|rb_node
op_star
id|victim
comma
r_struct
id|rb_node
op_star
r_new
comma
r_struct
id|rb_root
op_star
id|root
)paren
suffix:semicolon
DECL|function|rb_link_node
r_static
r_inline
r_void
id|rb_link_node
c_func
(paren
r_struct
id|rb_node
op_star
id|node
comma
r_struct
id|rb_node
op_star
id|parent
comma
r_struct
id|rb_node
op_star
op_star
id|rb_link
)paren
(brace
id|node-&gt;rb_parent
op_assign
id|parent
suffix:semicolon
id|node-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|node-&gt;rb_left
op_assign
id|node-&gt;rb_right
op_assign
l_int|NULL
suffix:semicolon
op_star
id|rb_link
op_assign
id|node
suffix:semicolon
)brace
macro_line|#endif&t;/* _LINUX_RBTREE_H */
eof
