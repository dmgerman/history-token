multiline_comment|/*&n;  Red Black Trees&n;  (C) 1999  Andrea Arcangeli &lt;andrea@suse.de&gt;&n;  (C) 2002  David Woodhouse &lt;dwmw2@infradead.org&gt;&n;  &n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2 of the License, or&n;  (at your option) any later version.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;  linux/lib/rbtree.c&n;*/
macro_line|#include &lt;linux/rbtree.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|__rb_rotate_left
r_static
r_void
id|__rb_rotate_left
c_func
(paren
r_struct
id|rb_node
op_star
id|node
comma
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|right
op_assign
id|node-&gt;rb_right
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node-&gt;rb_right
op_assign
id|right-&gt;rb_left
)paren
)paren
id|right-&gt;rb_left-&gt;rb_parent
op_assign
id|node
suffix:semicolon
id|right-&gt;rb_left
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
(paren
id|right-&gt;rb_parent
op_assign
id|node-&gt;rb_parent
)paren
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
id|node-&gt;rb_parent-&gt;rb_left
)paren
id|node-&gt;rb_parent-&gt;rb_left
op_assign
id|right
suffix:semicolon
r_else
id|node-&gt;rb_parent-&gt;rb_right
op_assign
id|right
suffix:semicolon
)brace
r_else
id|root-&gt;rb_node
op_assign
id|right
suffix:semicolon
id|node-&gt;rb_parent
op_assign
id|right
suffix:semicolon
)brace
DECL|function|__rb_rotate_right
r_static
r_void
id|__rb_rotate_right
c_func
(paren
r_struct
id|rb_node
op_star
id|node
comma
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|left
op_assign
id|node-&gt;rb_left
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node-&gt;rb_left
op_assign
id|left-&gt;rb_right
)paren
)paren
id|left-&gt;rb_right-&gt;rb_parent
op_assign
id|node
suffix:semicolon
id|left-&gt;rb_right
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
(paren
id|left-&gt;rb_parent
op_assign
id|node-&gt;rb_parent
)paren
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
id|node-&gt;rb_parent-&gt;rb_right
)paren
id|node-&gt;rb_parent-&gt;rb_right
op_assign
id|left
suffix:semicolon
r_else
id|node-&gt;rb_parent-&gt;rb_left
op_assign
id|left
suffix:semicolon
)brace
r_else
id|root-&gt;rb_node
op_assign
id|left
suffix:semicolon
id|node-&gt;rb_parent
op_assign
id|left
suffix:semicolon
)brace
DECL|function|rb_insert_color
r_void
id|rb_insert_color
c_func
(paren
r_struct
id|rb_node
op_star
id|node
comma
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|parent
comma
op_star
id|gparent
suffix:semicolon
r_while
c_loop
(paren
(paren
id|parent
op_assign
id|node-&gt;rb_parent
)paren
op_logical_and
id|parent-&gt;rb_color
op_eq
id|RB_RED
)paren
(brace
id|gparent
op_assign
id|parent-&gt;rb_parent
suffix:semicolon
r_if
c_cond
(paren
id|parent
op_eq
id|gparent-&gt;rb_left
)paren
(brace
(brace
r_register
r_struct
id|rb_node
op_star
id|uncle
op_assign
id|gparent-&gt;rb_right
suffix:semicolon
r_if
c_cond
(paren
id|uncle
op_logical_and
id|uncle-&gt;rb_color
op_eq
id|RB_RED
)paren
(brace
id|uncle-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|parent-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|gparent-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|node
op_assign
id|gparent
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|parent-&gt;rb_right
op_eq
id|node
)paren
(brace
r_register
r_struct
id|rb_node
op_star
id|tmp
suffix:semicolon
id|__rb_rotate_left
c_func
(paren
id|parent
comma
id|root
)paren
suffix:semicolon
id|tmp
op_assign
id|parent
suffix:semicolon
id|parent
op_assign
id|node
suffix:semicolon
id|node
op_assign
id|tmp
suffix:semicolon
)brace
id|parent-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|gparent-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|__rb_rotate_right
c_func
(paren
id|gparent
comma
id|root
)paren
suffix:semicolon
)brace
r_else
(brace
(brace
r_register
r_struct
id|rb_node
op_star
id|uncle
op_assign
id|gparent-&gt;rb_left
suffix:semicolon
r_if
c_cond
(paren
id|uncle
op_logical_and
id|uncle-&gt;rb_color
op_eq
id|RB_RED
)paren
(brace
id|uncle-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|parent-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|gparent-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|node
op_assign
id|gparent
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|parent-&gt;rb_left
op_eq
id|node
)paren
(brace
r_register
r_struct
id|rb_node
op_star
id|tmp
suffix:semicolon
id|__rb_rotate_right
c_func
(paren
id|parent
comma
id|root
)paren
suffix:semicolon
id|tmp
op_assign
id|parent
suffix:semicolon
id|parent
op_assign
id|node
suffix:semicolon
id|node
op_assign
id|tmp
suffix:semicolon
)brace
id|parent-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|gparent-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|__rb_rotate_left
c_func
(paren
id|gparent
comma
id|root
)paren
suffix:semicolon
)brace
)brace
id|root-&gt;rb_node-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
)brace
DECL|variable|rb_insert_color
id|EXPORT_SYMBOL
c_func
(paren
id|rb_insert_color
)paren
suffix:semicolon
DECL|function|__rb_erase_color
r_static
r_void
id|__rb_erase_color
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
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|other
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
id|node
op_logical_or
id|node-&gt;rb_color
op_eq
id|RB_BLACK
)paren
op_logical_and
id|node
op_ne
id|root-&gt;rb_node
)paren
(brace
r_if
c_cond
(paren
id|parent-&gt;rb_left
op_eq
id|node
)paren
(brace
id|other
op_assign
id|parent-&gt;rb_right
suffix:semicolon
r_if
c_cond
(paren
id|other-&gt;rb_color
op_eq
id|RB_RED
)paren
(brace
id|other-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|parent-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|__rb_rotate_left
c_func
(paren
id|parent
comma
id|root
)paren
suffix:semicolon
id|other
op_assign
id|parent-&gt;rb_right
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|other-&gt;rb_left
op_logical_or
id|other-&gt;rb_left-&gt;rb_color
op_eq
id|RB_BLACK
)paren
op_logical_and
(paren
op_logical_neg
id|other-&gt;rb_right
op_logical_or
id|other-&gt;rb_right-&gt;rb_color
op_eq
id|RB_BLACK
)paren
)paren
(brace
id|other-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|node
op_assign
id|parent
suffix:semicolon
id|parent
op_assign
id|node-&gt;rb_parent
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|other-&gt;rb_right
op_logical_or
id|other-&gt;rb_right-&gt;rb_color
op_eq
id|RB_BLACK
)paren
(brace
r_register
r_struct
id|rb_node
op_star
id|o_left
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o_left
op_assign
id|other-&gt;rb_left
)paren
)paren
id|o_left-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|other-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|__rb_rotate_right
c_func
(paren
id|other
comma
id|root
)paren
suffix:semicolon
id|other
op_assign
id|parent-&gt;rb_right
suffix:semicolon
)brace
id|other-&gt;rb_color
op_assign
id|parent-&gt;rb_color
suffix:semicolon
id|parent-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
r_if
c_cond
(paren
id|other-&gt;rb_right
)paren
id|other-&gt;rb_right-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|__rb_rotate_left
c_func
(paren
id|parent
comma
id|root
)paren
suffix:semicolon
id|node
op_assign
id|root-&gt;rb_node
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|other
op_assign
id|parent-&gt;rb_left
suffix:semicolon
r_if
c_cond
(paren
id|other-&gt;rb_color
op_eq
id|RB_RED
)paren
(brace
id|other-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|parent-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|__rb_rotate_right
c_func
(paren
id|parent
comma
id|root
)paren
suffix:semicolon
id|other
op_assign
id|parent-&gt;rb_left
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|other-&gt;rb_left
op_logical_or
id|other-&gt;rb_left-&gt;rb_color
op_eq
id|RB_BLACK
)paren
op_logical_and
(paren
op_logical_neg
id|other-&gt;rb_right
op_logical_or
id|other-&gt;rb_right-&gt;rb_color
op_eq
id|RB_BLACK
)paren
)paren
(brace
id|other-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|node
op_assign
id|parent
suffix:semicolon
id|parent
op_assign
id|node-&gt;rb_parent
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|other-&gt;rb_left
op_logical_or
id|other-&gt;rb_left-&gt;rb_color
op_eq
id|RB_BLACK
)paren
(brace
r_register
r_struct
id|rb_node
op_star
id|o_right
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o_right
op_assign
id|other-&gt;rb_right
)paren
)paren
id|o_right-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|other-&gt;rb_color
op_assign
id|RB_RED
suffix:semicolon
id|__rb_rotate_left
c_func
(paren
id|other
comma
id|root
)paren
suffix:semicolon
id|other
op_assign
id|parent-&gt;rb_left
suffix:semicolon
)brace
id|other-&gt;rb_color
op_assign
id|parent-&gt;rb_color
suffix:semicolon
id|parent-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
r_if
c_cond
(paren
id|other-&gt;rb_left
)paren
id|other-&gt;rb_left-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
id|__rb_rotate_right
c_func
(paren
id|parent
comma
id|root
)paren
suffix:semicolon
id|node
op_assign
id|root-&gt;rb_node
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|node
)paren
id|node-&gt;rb_color
op_assign
id|RB_BLACK
suffix:semicolon
)brace
DECL|function|rb_erase
r_void
id|rb_erase
c_func
(paren
r_struct
id|rb_node
op_star
id|node
comma
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|child
comma
op_star
id|parent
suffix:semicolon
r_int
id|color
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;rb_left
)paren
id|child
op_assign
id|node-&gt;rb_right
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;rb_right
)paren
id|child
op_assign
id|node-&gt;rb_left
suffix:semicolon
r_else
(brace
r_struct
id|rb_node
op_star
id|old
op_assign
id|node
comma
op_star
id|left
suffix:semicolon
id|node
op_assign
id|node-&gt;rb_right
suffix:semicolon
r_while
c_loop
(paren
(paren
id|left
op_assign
id|node-&gt;rb_left
)paren
op_ne
l_int|NULL
)paren
id|node
op_assign
id|left
suffix:semicolon
id|child
op_assign
id|node-&gt;rb_right
suffix:semicolon
id|parent
op_assign
id|node-&gt;rb_parent
suffix:semicolon
id|color
op_assign
id|node-&gt;rb_color
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|child-&gt;rb_parent
op_assign
id|parent
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
(brace
r_if
c_cond
(paren
id|parent-&gt;rb_left
op_eq
id|node
)paren
id|parent-&gt;rb_left
op_assign
id|child
suffix:semicolon
r_else
id|parent-&gt;rb_right
op_assign
id|child
suffix:semicolon
)brace
r_else
id|root-&gt;rb_node
op_assign
id|child
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;rb_parent
op_eq
id|old
)paren
id|parent
op_assign
id|node
suffix:semicolon
id|node-&gt;rb_parent
op_assign
id|old-&gt;rb_parent
suffix:semicolon
id|node-&gt;rb_color
op_assign
id|old-&gt;rb_color
suffix:semicolon
id|node-&gt;rb_right
op_assign
id|old-&gt;rb_right
suffix:semicolon
id|node-&gt;rb_left
op_assign
id|old-&gt;rb_left
suffix:semicolon
r_if
c_cond
(paren
id|old-&gt;rb_parent
)paren
(brace
r_if
c_cond
(paren
id|old-&gt;rb_parent-&gt;rb_left
op_eq
id|old
)paren
id|old-&gt;rb_parent-&gt;rb_left
op_assign
id|node
suffix:semicolon
r_else
id|old-&gt;rb_parent-&gt;rb_right
op_assign
id|node
suffix:semicolon
)brace
r_else
id|root-&gt;rb_node
op_assign
id|node
suffix:semicolon
id|old-&gt;rb_left-&gt;rb_parent
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
id|old-&gt;rb_right
)paren
id|old-&gt;rb_right-&gt;rb_parent
op_assign
id|node
suffix:semicolon
r_goto
id|color
suffix:semicolon
)brace
id|parent
op_assign
id|node-&gt;rb_parent
suffix:semicolon
id|color
op_assign
id|node-&gt;rb_color
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|child-&gt;rb_parent
op_assign
id|parent
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
(brace
r_if
c_cond
(paren
id|parent-&gt;rb_left
op_eq
id|node
)paren
id|parent-&gt;rb_left
op_assign
id|child
suffix:semicolon
r_else
id|parent-&gt;rb_right
op_assign
id|child
suffix:semicolon
)brace
r_else
id|root-&gt;rb_node
op_assign
id|child
suffix:semicolon
id|color
suffix:colon
r_if
c_cond
(paren
id|color
op_eq
id|RB_BLACK
)paren
id|__rb_erase_color
c_func
(paren
id|child
comma
id|parent
comma
id|root
)paren
suffix:semicolon
)brace
DECL|variable|rb_erase
id|EXPORT_SYMBOL
c_func
(paren
id|rb_erase
)paren
suffix:semicolon
multiline_comment|/*&n; * This function returns the first node (in sort order) of the tree.&n; */
DECL|function|rb_first
r_struct
id|rb_node
op_star
id|rb_first
c_func
(paren
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|n
suffix:semicolon
id|n
op_assign
id|root-&gt;rb_node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|n-&gt;rb_left
)paren
id|n
op_assign
id|n-&gt;rb_left
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|variable|rb_first
id|EXPORT_SYMBOL
c_func
(paren
id|rb_first
)paren
suffix:semicolon
DECL|function|rb_last
r_struct
id|rb_node
op_star
id|rb_last
c_func
(paren
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|n
suffix:semicolon
id|n
op_assign
id|root-&gt;rb_node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|n-&gt;rb_right
)paren
id|n
op_assign
id|n-&gt;rb_right
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|variable|rb_last
id|EXPORT_SYMBOL
c_func
(paren
id|rb_last
)paren
suffix:semicolon
DECL|function|rb_next
r_struct
id|rb_node
op_star
id|rb_next
c_func
(paren
r_struct
id|rb_node
op_star
id|node
)paren
(brace
multiline_comment|/* If we have a right-hand child, go down and then left as far&n;&t;   as we can. */
r_if
c_cond
(paren
id|node-&gt;rb_right
)paren
(brace
id|node
op_assign
id|node-&gt;rb_right
suffix:semicolon
r_while
c_loop
(paren
id|node-&gt;rb_left
)paren
id|node
op_assign
id|node-&gt;rb_left
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
multiline_comment|/* No right-hand children.  Everything down and left is&n;&t;   smaller than us, so any &squot;next&squot; node must be in the general&n;&t;   direction of our parent. Go up the tree; any time the&n;&t;   ancestor is a right-hand child of its parent, keep going&n;&t;   up. First time it&squot;s a left-hand child of its parent, said&n;&t;   parent is our &squot;next&squot; node. */
r_while
c_loop
(paren
id|node-&gt;rb_parent
op_logical_and
id|node
op_eq
id|node-&gt;rb_parent-&gt;rb_right
)paren
id|node
op_assign
id|node-&gt;rb_parent
suffix:semicolon
r_return
id|node-&gt;rb_parent
suffix:semicolon
)brace
DECL|variable|rb_next
id|EXPORT_SYMBOL
c_func
(paren
id|rb_next
)paren
suffix:semicolon
DECL|function|rb_prev
r_struct
id|rb_node
op_star
id|rb_prev
c_func
(paren
r_struct
id|rb_node
op_star
id|node
)paren
(brace
multiline_comment|/* If we have a left-hand child, go down and then right as far&n;&t;   as we can. */
r_if
c_cond
(paren
id|node-&gt;rb_left
)paren
(brace
id|node
op_assign
id|node-&gt;rb_left
suffix:semicolon
r_while
c_loop
(paren
id|node-&gt;rb_right
)paren
id|node
op_assign
id|node-&gt;rb_right
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
multiline_comment|/* No left-hand children. Go up till we find an ancestor which&n;&t;   is a right-hand child of its parent */
r_while
c_loop
(paren
id|node-&gt;rb_parent
op_logical_and
id|node
op_eq
id|node-&gt;rb_parent-&gt;rb_left
)paren
id|node
op_assign
id|node-&gt;rb_parent
suffix:semicolon
r_return
id|node-&gt;rb_parent
suffix:semicolon
)brace
DECL|variable|rb_prev
id|EXPORT_SYMBOL
c_func
(paren
id|rb_prev
)paren
suffix:semicolon
DECL|function|rb_replace_node
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
(brace
r_struct
id|rb_node
op_star
id|parent
op_assign
id|victim-&gt;rb_parent
suffix:semicolon
multiline_comment|/* Set the surrounding nodes to point to the replacement */
r_if
c_cond
(paren
id|parent
)paren
(brace
r_if
c_cond
(paren
id|victim
op_eq
id|parent-&gt;rb_left
)paren
id|parent-&gt;rb_left
op_assign
r_new
suffix:semicolon
r_else
id|parent-&gt;rb_right
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
id|root-&gt;rb_node
op_assign
r_new
suffix:semicolon
)brace
r_if
c_cond
(paren
id|victim-&gt;rb_left
)paren
id|victim-&gt;rb_left-&gt;rb_parent
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
id|victim-&gt;rb_right
)paren
id|victim-&gt;rb_right-&gt;rb_parent
op_assign
r_new
suffix:semicolon
multiline_comment|/* Copy the pointers/colour from the victim to the replacement */
op_star
r_new
op_assign
op_star
id|victim
suffix:semicolon
)brace
DECL|variable|rb_replace_node
id|EXPORT_SYMBOL
c_func
(paren
id|rb_replace_node
)paren
suffix:semicolon
eof
