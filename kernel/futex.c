multiline_comment|/*&n; *  Fast Userspace Mutexes (which I call &quot;Futexes!&quot;).&n; *  (C) Rusty Russell, IBM 2002&n; *&n; *  Generalized futexes, futex requeueing, misc fixes by Ingo Molnar&n; *  (C) Copyright 2003 Red Hat Inc, All Rights Reserved&n; *&n; *  Removed page pinning, fix privately mapped COW pages and other cleanups&n; *  (C) Copyright 2003 Jamie Lokier&n; *&n; *  Thanks to Ben LaHaise for yelling &quot;hashed waitqueues&quot; loudly&n; *  enough at me, Linus for the original (flawed) idea, Matthew&n; *  Kirkwood for proof-of-concept implementation.&n; *&n; *  &quot;The futexes are also cursed.&quot;&n; *  &quot;But they come in a choice of three flavours!&quot;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/jhash.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/futex.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
DECL|macro|FUTEX_HASHBITS
mdefine_line|#define FUTEX_HASHBITS 8
multiline_comment|/*&n; * Futexes are matched on equal values of this key.&n; * The key type depends on whether it&squot;s a shared or private mapping.&n; * Don&squot;t rearrange members without looking at hash_futex().&n; */
DECL|union|futex_key
r_union
id|futex_key
(brace
r_struct
(brace
DECL|member|pgoff
r_int
r_int
id|pgoff
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|shared
)brace
id|shared
suffix:semicolon
r_struct
(brace
DECL|member|uaddr
r_int
r_int
id|uaddr
suffix:semicolon
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|private
)brace
r_private
suffix:semicolon
r_struct
(brace
DECL|member|word
r_int
r_int
id|word
suffix:semicolon
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|both
)brace
id|both
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * We use this hashed waitqueue instead of a normal wait_queue_t, so&n; * we can wake only the relevant ones (hashed queues may be shared):&n; */
DECL|struct|futex_q
r_struct
id|futex_q
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|waiters
id|wait_queue_head_t
id|waiters
suffix:semicolon
multiline_comment|/* Key which the futex is hashed on. */
DECL|member|key
r_union
id|futex_key
id|key
suffix:semicolon
multiline_comment|/* For fd, sigio sent using these. */
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Split the global futex_lock into every hash list lock.&n; */
DECL|struct|futex_hash_bucket
r_struct
id|futex_hash_bucket
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|chain
r_struct
id|list_head
id|chain
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|futex_queues
r_static
r_struct
id|futex_hash_bucket
id|futex_queues
(braket
l_int|1
op_lshift
id|FUTEX_HASHBITS
)braket
suffix:semicolon
multiline_comment|/* Futex-fs vfsmount entry: */
DECL|variable|futex_mnt
r_static
r_struct
id|vfsmount
op_star
id|futex_mnt
suffix:semicolon
multiline_comment|/*&n; * We hash on the keys returned from get_futex_key (see below).&n; */
DECL|function|hash_futex
r_static
r_struct
id|futex_hash_bucket
op_star
id|hash_futex
c_func
(paren
r_union
id|futex_key
op_star
id|key
)paren
(brace
id|u32
id|hash
op_assign
id|jhash2
c_func
(paren
(paren
id|u32
op_star
)paren
op_amp
id|key-&gt;both.word
comma
(paren
r_sizeof
(paren
id|key-&gt;both.word
)paren
op_plus
r_sizeof
(paren
id|key-&gt;both.ptr
)paren
)paren
op_div
l_int|4
comma
id|key-&gt;both.offset
)paren
suffix:semicolon
r_return
op_amp
id|futex_queues
(braket
id|hash
op_amp
(paren
(paren
l_int|1
op_lshift
id|FUTEX_HASHBITS
)paren
op_minus
l_int|1
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Return 1 if two futex_keys are equal, 0 otherwise.&n; */
DECL|function|match_futex
r_static
r_inline
r_int
id|match_futex
c_func
(paren
r_union
id|futex_key
op_star
id|key1
comma
r_union
id|futex_key
op_star
id|key2
)paren
(brace
r_return
(paren
id|key1-&gt;both.word
op_eq
id|key2-&gt;both.word
op_logical_and
id|key1-&gt;both.ptr
op_eq
id|key2-&gt;both.ptr
op_logical_and
id|key1-&gt;both.offset
op_eq
id|key2-&gt;both.offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get parameters which are the keys for a futex.&n; *&n; * For shared mappings, it&squot;s (page-&gt;index, vma-&gt;vm_file-&gt;f_dentry-&gt;d_inode,&n; * offset_within_page).  For private mappings, it&squot;s (uaddr, current-&gt;mm).&n; * We can usually work out the index without swapping in the page.&n; *&n; * Returns: 0, or negative error code.&n; * The key words are stored in *key on success.&n; *&n; * Should be called with &amp;current-&gt;mm-&gt;mmap_sem,&n; * but NOT &amp;futex_lock or &amp;current-&gt;mm-&gt;page_table_lock.&n; */
DECL|function|get_futex_key
r_static
r_int
id|get_futex_key
c_func
(paren
r_int
r_int
id|uaddr
comma
r_union
id|futex_key
op_star
id|key
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * The futex address must be &quot;naturally&quot; aligned.&n;&t; */
id|key-&gt;both.offset
op_assign
id|uaddr
op_mod
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|key-&gt;both.offset
op_mod
r_sizeof
(paren
id|u32
)paren
)paren
op_ne
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|uaddr
op_sub_assign
id|key-&gt;both.offset
suffix:semicolon
multiline_comment|/*&n;&t; * The futex is hashed differently depending on whether&n;&t; * it&squot;s in a shared or private mapping.  So check vma first.&n;&t; */
id|vma
op_assign
id|find_extend_vma
c_func
(paren
id|mm
comma
id|uaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|vma
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t; * Permissions.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_IO
op_or
id|VM_READ
)paren
)paren
op_ne
id|VM_READ
)paren
)paren
r_return
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_IO
)paren
ques
c_cond
op_minus
id|EPERM
suffix:colon
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/*&n;&t; * Private mappings are handled in a simple way.&n;&t; *&n;&t; * NOTE: When userspace waits on a MAP_SHARED mapping, even if&n;&t; * it&squot;s a read-only handle, it&squot;s expected that futexes attach to&n;&t; * the object not the particular process.  Therefore we use&n;&t; * VM_MAYSHARE here, not VM_SHARED which is restricted to shared&n;&t; * mappings of _writable_ handles.&n;&t; */
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_MAYSHARE
)paren
)paren
)paren
(brace
id|key
op_member_access_from_pointer
r_private
dot
id|mm
op_assign
id|mm
suffix:semicolon
id|key
op_member_access_from_pointer
r_private
dot
id|uaddr
op_assign
id|uaddr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Linear mappings are also simple.&n;&t; */
id|key-&gt;shared.inode
op_assign
id|vma-&gt;vm_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_NONLINEAR
)paren
)paren
)paren
(brace
id|key-&gt;shared.pgoff
op_assign
(paren
(paren
(paren
id|uaddr
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_plus
id|vma-&gt;vm_pgoff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We could walk the page table to read the non-linear&n;&t; * pte, and get the page index without fetching the page&n;&t; * from swap.  But that&squot;s a lot of code to duplicate here&n;&t; * for a rare case, so we simply fetch the page.&n;&t; */
multiline_comment|/*&n;&t; * Do a quick atomic lookup first - this is the fastpath.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
suffix:semicolon
id|page
op_assign
id|follow_page
c_func
(paren
id|mm
comma
id|uaddr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|page
op_ne
l_int|NULL
)paren
)paren
(brace
id|key-&gt;shared.pgoff
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do it the general way.&n;&t; */
id|err
op_assign
id|get_user_pages
c_func
(paren
id|current
comma
id|mm
comma
id|uaddr
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
op_amp
id|page
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
(brace
id|key-&gt;shared.pgoff
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Wake up all waiters hashed on the physical page that is mapped&n; * to this virtual address:&n; */
DECL|function|futex_wake
r_static
r_int
id|futex_wake
c_func
(paren
r_int
r_int
id|uaddr
comma
r_int
id|num
)paren
(brace
r_struct
id|list_head
op_star
id|i
comma
op_star
id|next
comma
op_star
id|head
suffix:semicolon
r_struct
id|futex_hash_bucket
op_star
id|bh
suffix:semicolon
r_union
id|futex_key
id|key
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|get_futex_key
c_func
(paren
id|uaddr
comma
op_amp
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
op_ne
l_int|0
)paren
)paren
r_goto
id|out
suffix:semicolon
id|bh
op_assign
id|hash_futex
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|bh-&gt;chain
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|i
comma
id|next
comma
id|head
)paren
(brace
r_struct
id|futex_q
op_star
id|this
op_assign
id|list_entry
c_func
(paren
id|i
comma
r_struct
id|futex_q
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_futex
(paren
op_amp
id|this-&gt;key
comma
op_amp
id|key
)paren
)paren
(brace
id|list_del_init
c_func
(paren
id|i
)paren
suffix:semicolon
id|wake_up_all
c_func
(paren
op_amp
id|this-&gt;waiters
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this-&gt;filp
)paren
id|send_sigio
c_func
(paren
op_amp
id|this-&gt;filp-&gt;f_owner
comma
id|this-&gt;fd
comma
id|POLL_IN
)paren
suffix:semicolon
id|ret
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
id|num
)paren
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
id|out
suffix:colon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Requeue all waiters hashed on one physical page to another&n; * physical page.&n; */
DECL|function|futex_requeue
r_static
r_int
id|futex_requeue
c_func
(paren
r_int
r_int
id|uaddr1
comma
r_int
r_int
id|uaddr2
comma
r_int
id|nr_wake
comma
r_int
id|nr_requeue
)paren
(brace
r_struct
id|list_head
op_star
id|i
comma
op_star
id|next
comma
op_star
id|head1
comma
op_star
id|head2
suffix:semicolon
r_struct
id|futex_hash_bucket
op_star
id|bh1
comma
op_star
id|bh2
suffix:semicolon
r_union
id|futex_key
id|key1
comma
id|key2
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|get_futex_key
c_func
(paren
id|uaddr1
comma
op_amp
id|key1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
op_ne
l_int|0
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|get_futex_key
c_func
(paren
id|uaddr2
comma
op_amp
id|key2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
op_ne
l_int|0
)paren
)paren
r_goto
id|out
suffix:semicolon
id|bh1
op_assign
id|hash_futex
c_func
(paren
op_amp
id|key1
)paren
suffix:semicolon
id|bh2
op_assign
id|hash_futex
c_func
(paren
op_amp
id|key2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh1
OL
id|bh2
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|bh1-&gt;lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bh2-&gt;lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock
c_func
(paren
op_amp
id|bh2-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh1
OG
id|bh2
)paren
id|spin_lock
c_func
(paren
op_amp
id|bh1-&gt;lock
)paren
suffix:semicolon
)brace
id|head1
op_assign
op_amp
id|bh1-&gt;chain
suffix:semicolon
id|head2
op_assign
op_amp
id|bh2-&gt;chain
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|i
comma
id|next
comma
id|head1
)paren
(brace
r_struct
id|futex_q
op_star
id|this
op_assign
id|list_entry
c_func
(paren
id|i
comma
r_struct
id|futex_q
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_futex
(paren
op_amp
id|this-&gt;key
comma
op_amp
id|key1
)paren
)paren
(brace
id|list_del_init
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|ret
op_le
id|nr_wake
)paren
(brace
id|wake_up_all
c_func
(paren
op_amp
id|this-&gt;waiters
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this-&gt;filp
)paren
id|send_sigio
c_func
(paren
op_amp
id|this-&gt;filp-&gt;f_owner
comma
id|this-&gt;fd
comma
id|POLL_IN
)paren
suffix:semicolon
)brace
r_else
(brace
id|list_add_tail
c_func
(paren
id|i
comma
id|head2
)paren
suffix:semicolon
id|this-&gt;key
op_assign
id|key2
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_minus
id|nr_wake
op_ge
id|nr_requeue
)paren
r_break
suffix:semicolon
multiline_comment|/* Make sure to stop if key1 == key2 */
r_if
c_cond
(paren
id|head1
op_eq
id|head2
op_logical_and
id|head1
op_ne
id|next
)paren
id|head1
op_assign
id|i
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|bh1
OL
id|bh2
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|bh2-&gt;lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bh1-&gt;lock
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|bh1
OG
id|bh2
)paren
id|spin_unlock
c_func
(paren
op_amp
id|bh1-&gt;lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bh2-&gt;lock
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|queue_me
r_static
r_inline
r_void
id|queue_me
c_func
(paren
r_struct
id|futex_q
op_star
id|q
comma
r_union
id|futex_key
op_star
id|key
comma
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|futex_hash_bucket
op_star
id|bh
op_assign
id|hash_futex
c_func
(paren
id|key
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
op_amp
id|bh-&gt;chain
suffix:semicolon
id|q-&gt;key
op_assign
op_star
id|key
suffix:semicolon
id|q-&gt;fd
op_assign
id|fd
suffix:semicolon
id|q-&gt;filp
op_assign
id|filp
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|q-&gt;list
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Return 1 if we were still queued (ie. 0 means we were woken) */
DECL|function|unqueue_me
r_static
r_inline
r_int
id|unqueue_me
c_func
(paren
r_struct
id|futex_q
op_star
id|q
)paren
(brace
r_struct
id|futex_hash_bucket
op_star
id|bh
op_assign
id|hash_futex
c_func
(paren
op_amp
id|q-&gt;key
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;list
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|q-&gt;list
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|futex_wait
r_static
r_int
id|futex_wait
c_func
(paren
r_int
r_int
id|uaddr
comma
r_int
id|val
comma
r_int
r_int
id|time
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|ret
comma
id|curval
suffix:semicolon
r_union
id|futex_key
id|key
suffix:semicolon
r_struct
id|futex_q
id|q
suffix:semicolon
r_struct
id|futex_hash_bucket
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q.waiters
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|get_futex_key
c_func
(paren
id|uaddr
comma
op_amp
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
op_ne
l_int|0
)paren
)paren
r_goto
id|out_release_sem
suffix:semicolon
id|queue_me
c_func
(paren
op_amp
id|q
comma
op_amp
id|key
comma
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Access the page after the futex is queued.&n;&t; * We hold the mmap semaphore, so the mapping cannot have changed&n;&t; * since we looked it up.&n;&t; */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|curval
comma
(paren
r_int
op_star
)paren
id|uaddr
)paren
op_ne
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out_unqueue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|curval
op_ne
id|val
)paren
(brace
id|ret
op_assign
op_minus
id|EWOULDBLOCK
suffix:semicolon
r_goto
id|out_unqueue
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now the futex is queued and we have checked the data, we&n;&t; * don&squot;t want to hold mmap_sem while we sleep.&n;&t; */
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There might have been scheduling since the queue_me(), as we&n;&t; * cannot hold a spinlock across the get_user() in case it&n;&t; * faults, and we cannot just set TASK_INTERRUPTIBLE state when&n;&t; * queueing ourselves into the futex hash.  This code thus has to&n;&t; * rely on the futex_wake() code removing us from hash when it&n;&t; * wakes us up.&n;&t; */
id|add_wait_queue
c_func
(paren
op_amp
id|q.waiters
comma
op_amp
id|wait
)paren
suffix:semicolon
id|bh
op_assign
id|hash_futex
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|list_empty
c_func
(paren
op_amp
id|q.list
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We were woken already.&n;&t;&t; */
id|spin_unlock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
id|time
op_assign
id|schedule_timeout
c_func
(paren
id|time
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE: we don&squot;t remove ourselves from the waitqueue because&n;&t; * we are the only user of it.&n;&t; */
multiline_comment|/* If we were woken (and unqueued), we succeeded, whatever. */
r_if
c_cond
(paren
op_logical_neg
id|unqueue_me
c_func
(paren
op_amp
id|q
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|time
op_eq
l_int|0
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
multiline_comment|/* A spurious wakeup should never happen. */
id|WARN_ON
c_func
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
id|out_unqueue
suffix:colon
multiline_comment|/* If we were woken (and unqueued), we succeeded, whatever. */
r_if
c_cond
(paren
op_logical_neg
id|unqueue_me
c_func
(paren
op_amp
id|q
)paren
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
id|out_release_sem
suffix:colon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|futex_close
r_static
r_int
id|futex_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|futex_q
op_star
id|q
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|unqueue_me
c_func
(paren
id|q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|filp-&gt;private_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This is one-shot: once it&squot;s gone off you need a new fd */
DECL|function|futex_poll
r_static
r_int
r_int
id|futex_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_struct
id|futex_q
op_star
id|q
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_struct
id|futex_hash_bucket
op_star
id|bh
op_assign
id|hash_futex
c_func
(paren
op_amp
id|q-&gt;key
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|poll_wait
c_func
(paren
id|filp
comma
op_amp
id|q-&gt;waiters
comma
id|wait
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|q-&gt;list
)paren
)paren
id|ret
op_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bh-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|futex_fops
r_static
r_struct
id|file_operations
id|futex_fops
op_assign
(brace
dot
id|release
op_assign
id|futex_close
comma
dot
id|poll
op_assign
id|futex_poll
comma
)brace
suffix:semicolon
multiline_comment|/* Signal allows caller to avoid the race which would occur if they&n;   set the sigio stuff up afterwards. */
DECL|function|futex_fd
r_static
r_int
id|futex_fd
c_func
(paren
r_int
r_int
id|uaddr
comma
r_int
id|signal
)paren
(brace
r_struct
id|futex_q
op_star
id|q
suffix:semicolon
r_union
id|futex_key
id|key
suffix:semicolon
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|ret
comma
id|err
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|signal
template_param
id|_NSIG
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|filp
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp
)paren
(brace
id|put_unused_fd
c_func
(paren
id|ret
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENFILE
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|filp-&gt;f_op
op_assign
op_amp
id|futex_fops
suffix:semicolon
id|filp-&gt;f_vfsmnt
op_assign
id|mntget
c_func
(paren
id|futex_mnt
)paren
suffix:semicolon
id|filp-&gt;f_dentry
op_assign
id|dget
c_func
(paren
id|futex_mnt-&gt;mnt_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|f_setown
c_func
(paren
id|filp
comma
id|current-&gt;tgid
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|put_unused_fd
c_func
(paren
id|ret
)paren
suffix:semicolon
id|put_filp
c_func
(paren
id|filp
)paren
suffix:semicolon
id|ret
op_assign
id|err
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|filp-&gt;f_owner.signum
op_assign
id|signal
suffix:semicolon
)brace
id|q
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|q
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
(brace
id|put_unused_fd
c_func
(paren
id|ret
)paren
suffix:semicolon
id|put_filp
c_func
(paren
id|filp
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|err
op_assign
id|get_futex_key
c_func
(paren
id|uaddr
comma
op_amp
id|key
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
op_ne
l_int|0
)paren
)paren
(brace
id|put_unused_fd
c_func
(paren
id|ret
)paren
suffix:semicolon
id|put_filp
c_func
(paren
id|filp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;waiters
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|q
suffix:semicolon
id|queue_me
c_func
(paren
id|q
comma
op_amp
id|key
comma
id|ret
comma
id|filp
)paren
suffix:semicolon
multiline_comment|/* Now we map fd to filp, so userspace can access it */
id|fd_install
c_func
(paren
id|ret
comma
id|filp
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_futex
r_int
id|do_futex
c_func
(paren
r_int
r_int
id|uaddr
comma
r_int
id|op
comma
r_int
id|val
comma
r_int
r_int
id|timeout
comma
r_int
r_int
id|uaddr2
comma
r_int
id|val2
)paren
(brace
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|FUTEX_WAIT
suffix:colon
id|ret
op_assign
id|futex_wait
c_func
(paren
id|uaddr
comma
id|val
comma
id|timeout
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FUTEX_WAKE
suffix:colon
id|ret
op_assign
id|futex_wake
c_func
(paren
id|uaddr
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FUTEX_FD
suffix:colon
multiline_comment|/* non-zero val means F_SETOWN(getpid()) &amp; F_SETSIG(val) */
id|ret
op_assign
id|futex_fd
c_func
(paren
id|uaddr
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FUTEX_REQUEUE
suffix:colon
id|ret
op_assign
id|futex_requeue
c_func
(paren
id|uaddr
comma
id|uaddr2
comma
id|val
comma
id|val2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_futex
id|asmlinkage
r_int
id|sys_futex
c_func
(paren
id|u32
id|__user
op_star
id|uaddr
comma
r_int
id|op
comma
r_int
id|val
comma
r_struct
id|timespec
id|__user
op_star
id|utime
comma
id|u32
id|__user
op_star
id|uaddr2
)paren
(brace
r_struct
id|timespec
id|t
suffix:semicolon
r_int
r_int
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
r_int
id|val2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|op
op_eq
id|FUTEX_WAIT
)paren
op_logical_and
id|utime
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|t
comma
id|utime
comma
r_sizeof
(paren
id|t
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|timeout
op_assign
id|timespec_to_jiffies
c_func
(paren
op_amp
id|t
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * requeue parameter in &squot;utime&squot; if op == FUTEX_REQUEUE.&n;&t; */
r_if
c_cond
(paren
id|op
op_eq
id|FUTEX_REQUEUE
)paren
id|val2
op_assign
(paren
r_int
)paren
(paren
r_int
)paren
id|utime
suffix:semicolon
r_return
id|do_futex
c_func
(paren
(paren
r_int
r_int
)paren
id|uaddr
comma
id|op
comma
id|val
comma
id|timeout
comma
(paren
r_int
r_int
)paren
id|uaddr2
comma
id|val2
)paren
suffix:semicolon
)brace
r_static
r_struct
id|super_block
op_star
DECL|function|futexfs_get_sb
id|futexfs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_pseudo
c_func
(paren
id|fs_type
comma
l_string|&quot;futex&quot;
comma
l_int|NULL
comma
l_int|0xBAD1DEA
)paren
suffix:semicolon
)brace
DECL|variable|futex_fs_type
r_static
r_struct
id|file_system_type
id|futex_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;futexfs&quot;
comma
dot
id|get_sb
op_assign
id|futexfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_anon_super
comma
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|register_filesystem
c_func
(paren
op_amp
id|futex_fs_type
)paren
suffix:semicolon
id|futex_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|futex_fs_type
)paren
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
id|ARRAY_SIZE
c_func
(paren
id|futex_queues
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|futex_queues
(braket
id|i
)braket
dot
id|chain
)paren
suffix:semicolon
id|futex_queues
(braket
id|i
)braket
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init
id|__initcall
c_func
(paren
id|init
)paren
suffix:semicolon
eof
