multiline_comment|/*&n; *  linux/mm/vcache.c&n; *&n; *  virtual =&gt; physical page mapping cache. Users of this mechanism&n; *  register callbacks for a given (virt,mm,phys) page mapping, and&n; *  the kernel guarantees to call back when this mapping is invalidated.&n; *  (ie. upon COW or unmap.)&n; *&n; *  Started by Ingo Molnar, Copyright (C) 2002&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
macro_line|#include &lt;linux/vcache.h&gt;
DECL|macro|VCACHE_HASHBITS
mdefine_line|#define VCACHE_HASHBITS 8
DECL|macro|VCACHE_HASHSIZE
mdefine_line|#define VCACHE_HASHSIZE (1 &lt;&lt; VCACHE_HASHBITS)
DECL|variable|vcache_lock
id|spinlock_t
id|vcache_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|hash
r_static
r_struct
id|list_head
id|hash
(braket
id|VCACHE_HASHSIZE
)braket
suffix:semicolon
DECL|function|hash_vcache
r_static
r_struct
id|list_head
op_star
id|hash_vcache
c_func
(paren
r_int
r_int
id|address
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_return
op_amp
id|hash
(braket
id|hash_long
c_func
(paren
id|address
op_plus
(paren
r_int
r_int
)paren
id|mm
comma
id|VCACHE_HASHBITS
)paren
)braket
suffix:semicolon
)brace
DECL|function|__attach_vcache
r_void
id|__attach_vcache
c_func
(paren
id|vcache_t
op_star
id|vcache
comma
r_int
r_int
id|address
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|vcache_s
op_star
id|data
comma
r_struct
id|page
op_star
r_new
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|hash_head
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|vcache-&gt;address
op_assign
id|address
suffix:semicolon
id|vcache-&gt;mm
op_assign
id|mm
suffix:semicolon
id|vcache-&gt;callback
op_assign
id|callback
suffix:semicolon
id|hash_head
op_assign
id|hash_vcache
c_func
(paren
id|address
comma
id|mm
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|vcache-&gt;hash_entry
comma
id|hash_head
)paren
suffix:semicolon
)brace
DECL|function|__detach_vcache
r_void
id|__detach_vcache
c_func
(paren
id|vcache_t
op_star
id|vcache
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|vcache-&gt;hash_entry
)paren
suffix:semicolon
)brace
DECL|function|invalidate_vcache
r_void
id|invalidate_vcache
c_func
(paren
r_int
r_int
id|address
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|page
op_star
id|new_page
)paren
(brace
r_struct
id|list_head
op_star
id|l
comma
op_star
id|hash_head
suffix:semicolon
id|vcache_t
op_star
id|vcache
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|hash_head
op_assign
id|hash_vcache
c_func
(paren
id|address
comma
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is safe, because this path is called with the pagetable&n;&t; * lock held. So while other mm&squot;s might add new entries in&n;&t; * parallel, *this* mm is locked out, so if the list is empty&n;&t; * now then we do not have to take the vcache lock to see it&squot;s&n;&t; * really empty.&n;&t; */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|list_empty
c_func
(paren
id|hash_head
)paren
)paren
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vcache_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
id|hash_head
)paren
(brace
id|vcache
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|vcache_t
comma
id|hash_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vcache-&gt;address
op_ne
id|address
op_logical_or
id|vcache-&gt;mm
op_ne
id|mm
)paren
r_continue
suffix:semicolon
id|vcache
op_member_access_from_pointer
id|callback
c_func
(paren
id|vcache
comma
id|new_page
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|vcache_lock
)paren
suffix:semicolon
)brace
DECL|function|vcache_init
r_static
r_int
id|__init
id|vcache_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VCACHE_HASHSIZE
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
id|hash
op_plus
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vcache_init
id|__initcall
c_func
(paren
id|vcache_init
)paren
suffix:semicolon
eof
