multiline_comment|/*&n; * &t;w1_family.c&n; *&n; * Copyright (c) 2004 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; * &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;w1_family.h&quot;
DECL|variable|w1_flock
id|spinlock_t
id|w1_flock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|w1_families
)paren
suffix:semicolon
DECL|function|w1_check_family
r_static
r_int
id|w1_check_family
c_func
(paren
r_struct
id|w1_family
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;fops-&gt;rname
op_logical_or
op_logical_neg
id|f-&gt;fops-&gt;rbin
op_logical_or
op_logical_neg
id|f-&gt;fops-&gt;rval
op_logical_or
op_logical_neg
id|f-&gt;fops-&gt;rvalname
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|w1_register_family
r_int
id|w1_register_family
c_func
(paren
r_struct
id|w1_family
op_star
id|newf
)paren
(brace
r_struct
id|list_head
op_star
id|ent
comma
op_star
id|n
suffix:semicolon
r_struct
id|w1_family
op_star
id|f
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|w1_check_family
c_func
(paren
id|newf
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|ent
comma
id|n
comma
op_amp
id|w1_families
)paren
(brace
id|f
op_assign
id|list_entry
c_func
(paren
id|ent
comma
r_struct
id|w1_family
comma
id|family_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;fid
op_eq
id|newf-&gt;fid
)paren
(brace
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|newf-&gt;refcnt
comma
l_int|0
)paren
suffix:semicolon
id|newf-&gt;need_exit
op_assign
l_int|0
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|newf-&gt;family_entry
comma
op_amp
id|w1_families
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|w1_unregister_family
r_void
id|w1_unregister_family
c_func
(paren
r_struct
id|w1_family
op_star
id|fent
)paren
(brace
r_struct
id|list_head
op_star
id|ent
comma
op_star
id|n
suffix:semicolon
r_struct
id|w1_family
op_star
id|f
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|ent
comma
id|n
comma
op_amp
id|w1_families
)paren
(brace
id|f
op_assign
id|list_entry
c_func
(paren
id|ent
comma
r_struct
id|w1_family
comma
id|family_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;fid
op_eq
id|fent-&gt;fid
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|fent-&gt;family_entry
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fent-&gt;need_exit
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|fent-&gt;refcnt
)paren
)paren
id|schedule_timeout
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Should be called under w1_flock held.&n; */
DECL|function|w1_family_registered
r_struct
id|w1_family
op_star
id|w1_family_registered
c_func
(paren
id|u8
id|fid
)paren
(brace
r_struct
id|list_head
op_star
id|ent
comma
op_star
id|n
suffix:semicolon
r_struct
id|w1_family
op_star
id|f
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|ent
comma
id|n
comma
op_amp
id|w1_families
)paren
(brace
id|f
op_assign
id|list_entry
c_func
(paren
id|ent
comma
r_struct
id|w1_family
comma
id|family_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;fid
op_eq
id|fid
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
(paren
id|ret
)paren
ques
c_cond
id|f
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|w1_family_put
r_void
id|w1_family_put
c_func
(paren
r_struct
id|w1_family
op_star
id|f
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
id|__w1_family_put
c_func
(paren
id|f
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
)brace
DECL|function|__w1_family_put
r_void
id|__w1_family_put
c_func
(paren
r_struct
id|w1_family
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|f-&gt;refcnt
)paren
)paren
id|f-&gt;need_exit
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|w1_family_get
r_void
id|w1_family_get
c_func
(paren
r_struct
id|w1_family
op_star
id|f
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
id|__w1_family_get
c_func
(paren
id|f
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|w1_flock
)paren
suffix:semicolon
)brace
DECL|function|__w1_family_get
r_void
id|__w1_family_get
c_func
(paren
r_struct
id|w1_family
op_star
id|f
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|f-&gt;refcnt
)paren
suffix:semicolon
)brace
DECL|variable|w1_family_get
id|EXPORT_SYMBOL
c_func
(paren
id|w1_family_get
)paren
suffix:semicolon
DECL|variable|w1_family_put
id|EXPORT_SYMBOL
c_func
(paren
id|w1_family_put
)paren
suffix:semicolon
DECL|variable|__w1_family_get
id|EXPORT_SYMBOL
c_func
(paren
id|__w1_family_get
)paren
suffix:semicolon
DECL|variable|__w1_family_put
id|EXPORT_SYMBOL
c_func
(paren
id|__w1_family_put
)paren
suffix:semicolon
DECL|variable|w1_family_registered
id|EXPORT_SYMBOL
c_func
(paren
id|w1_family_registered
)paren
suffix:semicolon
DECL|variable|w1_unregister_family
id|EXPORT_SYMBOL
c_func
(paren
id|w1_unregister_family
)paren
suffix:semicolon
DECL|variable|w1_register_family
id|EXPORT_SYMBOL
c_func
(paren
id|w1_register_family
)paren
suffix:semicolon
eof
