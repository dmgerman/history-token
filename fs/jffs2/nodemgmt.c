multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * The original JFFS, from which the design for JFFS2 was derived,&n; * was designed and implemented by Axis Communications AB.&n; *&n; * The contents of this file are subject to the Red Hat eCos Public&n; * License Version 1.1 (the &quot;Licence&quot;); you may not use this file&n; * except in compliance with the Licence.  You may obtain a copy of&n; * the Licence at http://www.redhat.com/&n; *&n; * Software distributed under the Licence is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.&n; * See the Licence for the specific language governing rights and&n; * limitations under the Licence.&n; *&n; * The Original Code is JFFS2 - Journalling Flash File System, version 2&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the RHEPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the RHEPL or the GPL.&n; *&n; * $Id: nodemgmt.c,v 1.45.2.1 2002/02/23 14:13:34 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/jffs2.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;nodelist.h&quot;
multiline_comment|/**&n; *&t;jffs2_reserve_space - request physical space to write nodes to flash&n; *&t;@c: superblock info&n; *&t;@minsize: Minimum acceptable size of allocation&n; *&t;@ofs: Returned value of node offset&n; *&t;@len: Returned value of allocation length&n; *&t;@prio: Allocation type - ALLOC_{NORMAL,DELETION}&n; *&n; *&t;Requests a block of physical space on the flash. Returns zero for success&n; *&t;and puts &squot;ofs&squot; and &squot;len&squot; into the appriopriate place, or returns -ENOSPC&n; *&t;or other error if appropriate.&n; *&n; *&t;If it returns zero, jffs2_reserve_space() also downs the per-filesystem&n; *&t;allocation semaphore, to prevent more than one allocation from being&n; *&t;active at any time. The semaphore is later released by jffs2_commit_allocation()&n; *&n; *&t;jffs2_reserve_space() may trigger garbage collection in order to make room&n; *&t;for the requested allocation.&n; */
r_static
r_int
id|jffs2_do_reserve_space
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|__u32
id|minsize
comma
id|__u32
op_star
id|ofs
comma
id|__u32
op_star
id|len
)paren
suffix:semicolon
DECL|function|jffs2_reserve_space
r_int
id|jffs2_reserve_space
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|__u32
id|minsize
comma
id|__u32
op_star
id|ofs
comma
id|__u32
op_star
id|len
comma
r_int
id|prio
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_int
id|blocksneeded
op_assign
id|JFFS2_RESERVED_BLOCKS_WRITE
suffix:semicolon
multiline_comment|/* align it */
id|minsize
op_assign
id|PAD
c_func
(paren
id|minsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prio
op_eq
id|ALLOC_DELETION
)paren
id|blocksneeded
op_assign
id|JFFS2_RESERVED_BLOCKS_DELETION
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space(): Requested 0x%x bytes&bslash;n&quot;
comma
id|minsize
)paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space(): alloc sem got&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
multiline_comment|/* this needs a little more thought */
r_while
c_loop
(paren
id|ret
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_while
c_loop
(paren
id|c-&gt;nr_free_blocks
op_plus
id|c-&gt;nr_erasing_blocks
OL
id|blocksneeded
)paren
(brace
r_int
id|ret
suffix:semicolon
id|up
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;dirty_size
OL
id|c-&gt;sector_size
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Short on space, but total dirty size 0x%08x &lt; sector size 0x%08x, so -ENOSPC&bslash;n&quot;
comma
id|c-&gt;dirty_size
comma
id|c-&gt;sector_size
)paren
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Triggering GC pass. nr_free_blocks %d, nr_erasing_blocks %d, free_size 0x%08x, dirty_size 0x%08x, used_size 0x%08x, erasing_size 0x%08x, bad_size 0x%08x (total 0x%08x of 0x%08x)&bslash;n&quot;
comma
id|c-&gt;nr_free_blocks
comma
id|c-&gt;nr_erasing_blocks
comma
id|c-&gt;free_size
comma
id|c-&gt;dirty_size
comma
id|c-&gt;used_size
comma
id|c-&gt;erasing_size
comma
id|c-&gt;bad_size
comma
id|c-&gt;free_size
op_plus
id|c-&gt;dirty_size
op_plus
id|c-&gt;used_size
op_plus
id|c-&gt;erasing_size
op_plus
id|c-&gt;bad_size
comma
id|c-&gt;flash_size
)paren
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_garbage_collect_pass
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
id|down
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|jffs2_do_reserve_space
c_func
(paren
id|c
comma
id|minsize
comma
id|ofs
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space: ret is %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|up
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_reserve_space_gc
r_int
id|jffs2_reserve_space_gc
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|__u32
id|minsize
comma
id|__u32
op_star
id|ofs
comma
id|__u32
op_star
id|len
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|minsize
op_assign
id|PAD
c_func
(paren
id|minsize
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space_gc(): Requested 0x%x bytes&bslash;n&quot;
comma
id|minsize
)paren
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_eq
op_minus
id|EAGAIN
)paren
(brace
id|ret
op_assign
id|jffs2_do_reserve_space
c_func
(paren
id|c
comma
id|minsize
comma
id|ofs
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space_gc: looping, ret is %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Called with alloc sem _and_ erase_completion_lock */
DECL|function|jffs2_do_reserve_space
r_static
r_int
id|jffs2_do_reserve_space
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|__u32
id|minsize
comma
id|__u32
op_star
id|ofs
comma
id|__u32
op_star
id|len
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|c-&gt;nextblock
suffix:semicolon
id|restart
suffix:colon
r_if
c_cond
(paren
id|jeb
op_logical_and
id|minsize
OG
id|jeb-&gt;free_size
)paren
(brace
multiline_comment|/* Skip the end of this block and file it as having some dirty space */
id|c-&gt;dirty_size
op_add_assign
id|jeb-&gt;free_size
suffix:semicolon
id|c-&gt;free_size
op_sub_assign
id|jeb-&gt;free_size
suffix:semicolon
id|jeb-&gt;dirty_size
op_add_assign
id|jeb-&gt;free_size
suffix:semicolon
id|jeb-&gt;free_size
op_assign
l_int|0
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Adding full erase block at 0x%08x to dirty_list (free 0x%08x, dirty 0x%08x, used 0x%08x&bslash;n&quot;
comma
id|jeb-&gt;offset
comma
id|jeb-&gt;free_size
comma
id|jeb-&gt;dirty_size
comma
id|jeb-&gt;used_size
)paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|jeb-&gt;list
comma
op_amp
id|c-&gt;dirty_list
)paren
suffix:semicolon
id|c-&gt;nextblock
op_assign
id|jeb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|jeb
)paren
(brace
r_struct
id|list_head
op_star
id|next
suffix:semicolon
multiline_comment|/* Take the next block off the &squot;free&squot; list */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;free_list
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;nr_erasing_blocks
)paren
(brace
singleline_comment|//&t;&t;&t;if (list_empty(&amp;c-&gt;erasing_list) &amp;&amp; list_empty(&amp;c-&gt;erase_pending_list) &amp;&amp; list_empty(c-&gt;erase_complete_list)) {
multiline_comment|/* Ouch. We&squot;re in GC, or we wouldn&squot;t have got here.&n;&t;&t;&t;&t;   And there&squot;s no space left. At all. */
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Argh. No free space left for GC. nr_erasing_blocks is %d. nr_free_blocks is %d. (erasingempty: %s, erasependingempty: %s)&bslash;n&quot;
comma
id|c-&gt;nr_erasing_blocks
comma
id|c-&gt;nr_free_blocks
comma
id|list_empty
c_func
(paren
op_amp
id|c-&gt;erasing_list
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|list_empty
c_func
(paren
op_amp
id|c-&gt;erase_pending_list
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/* Make sure this can&squot;t deadlock. Someone has to start the erases&n;&t;&t;&t;   of erase_pending blocks */
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|c-&gt;erase_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Waiting for erases to complete. erasing_blocks is %d. (erasingempty: %s, erasependingempty: %s)&bslash;n&quot;
comma
id|c-&gt;nr_erasing_blocks
comma
id|list_empty
c_func
(paren
op_amp
id|c-&gt;erasing_list
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|list_empty
c_func
(paren
op_amp
id|c-&gt;erase_pending_list
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
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
id|c-&gt;erase_pending_list
)paren
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Triggering pending erases&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|jffs2_erase_pending_trigger
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|c-&gt;erase_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
multiline_comment|/* An erase may have failed, decreasing the&n;&t;&t;&t;   amount of free space available. So we must&n;&t;&t;&t;   restart from the beginning */
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|next
op_assign
id|c-&gt;free_list.next
suffix:semicolon
id|list_del
c_func
(paren
id|next
)paren
suffix:semicolon
id|c-&gt;nextblock
op_assign
id|jeb
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|c-&gt;nr_free_blocks
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|jeb-&gt;free_size
op_ne
id|c-&gt;sector_size
op_minus
r_sizeof
(paren
r_struct
id|jffs2_unknown_node
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Eep. Block 0x%08x taken from free_list had free_size of 0x%08x!!&bslash;n&quot;
comma
id|jeb-&gt;offset
comma
id|jeb-&gt;free_size
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
)brace
multiline_comment|/* OK, jeb (==c-&gt;nextblock) is now pointing at a block which definitely has&n;&t;   enough space */
op_star
id|ofs
op_assign
id|jeb-&gt;offset
op_plus
(paren
id|c-&gt;sector_size
op_minus
id|jeb-&gt;free_size
)paren
suffix:semicolon
op_star
id|len
op_assign
id|jeb-&gt;free_size
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_reserve_space(): Giving 0x%x bytes at 0x%x&bslash;n&quot;
comma
op_star
id|len
comma
op_star
id|ofs
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;jffs2_add_physical_node_ref - add a physical node reference to the list&n; *&t;@c: superblock info&n; *&t;@ofs: physical location of this physical node&n; *&t;@len: length of this physical node&n; *&t;@ino: inode number with which this physical node is associated&n; *&n; *&t;Should only be used to report nodes for which space has been allocated &n; *&t;by jffs2_reserve_space.&n; *&n; *&t;Must be called with the alloc_sem held.&n; */
DECL|function|jffs2_add_physical_node_ref
r_int
id|jffs2_add_physical_node_ref
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_raw_node_ref
op_star
r_new
comma
id|__u32
id|len
comma
r_int
id|dirty
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
suffix:semicolon
id|len
op_assign
id|PAD
c_func
(paren
id|len
)paren
suffix:semicolon
id|jeb
op_assign
op_amp
id|c-&gt;blocks
(braket
(paren
r_new
op_member_access_from_pointer
id|flash_offset
op_amp
op_complement
l_int|3
)paren
op_div
id|c-&gt;sector_size
)braket
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_add_physical_node_ref(): Node at 0x%x, size 0x%x&bslash;n&quot;
comma
r_new
op_member_access_from_pointer
id|flash_offset
op_amp
op_complement
l_int|3
comma
id|len
)paren
)paren
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|jeb
op_ne
id|c-&gt;nextblock
op_logical_or
(paren
r_new
op_member_access_from_pointer
id|flash_offset
op_amp
op_complement
l_int|3
)paren
op_ne
id|jeb-&gt;offset
op_plus
(paren
id|c-&gt;sector_size
op_minus
id|jeb-&gt;free_size
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;argh. node added in wrong place&bslash;n&quot;
)paren
suffix:semicolon
id|jffs2_free_raw_node_ref
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|jeb-&gt;first_node
)paren
id|jeb-&gt;first_node
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
id|jeb-&gt;last_node
)paren
id|jeb-&gt;last_node-&gt;next_phys
op_assign
r_new
suffix:semicolon
id|jeb-&gt;last_node
op_assign
r_new
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|jeb-&gt;free_size
op_sub_assign
id|len
suffix:semicolon
id|c-&gt;free_size
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|dirty
)paren
(brace
r_new
op_member_access_from_pointer
id|flash_offset
op_or_assign
l_int|1
suffix:semicolon
id|jeb-&gt;dirty_size
op_add_assign
id|len
suffix:semicolon
id|c-&gt;dirty_size
op_add_assign
id|len
suffix:semicolon
)brace
r_else
(brace
id|jeb-&gt;used_size
op_add_assign
id|len
suffix:semicolon
id|c-&gt;used_size
op_add_assign
id|len
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|jeb-&gt;free_size
op_logical_and
op_logical_neg
id|jeb-&gt;dirty_size
)paren
(brace
multiline_comment|/* If it lives on the dirty_list, jffs2_reserve_space will put it there */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Adding full erase block at 0x%08x to clean_list (free 0x%08x, dirty 0x%08x, used 0x%08x&bslash;n&quot;
comma
id|jeb-&gt;offset
comma
id|jeb-&gt;free_size
comma
id|jeb-&gt;dirty_size
comma
id|jeb-&gt;used_size
)paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|jeb-&gt;list
comma
op_amp
id|c-&gt;clean_list
)paren
suffix:semicolon
id|c-&gt;nextblock
op_assign
l_int|NULL
suffix:semicolon
)brace
id|ACCT_SANITY_CHECK
c_func
(paren
id|c
comma
id|jeb
)paren
suffix:semicolon
id|ACCT_PARANOIA_CHECK
c_func
(paren
id|jeb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_complete_reservation
r_void
id|jffs2_complete_reservation
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_complete_reservation()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|jffs2_garbage_collect_trigger
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
)brace
DECL|function|jffs2_mark_node_obsolete
r_void
id|jffs2_mark_node_obsolete
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_raw_node_ref
op_star
id|ref
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
suffix:semicolon
r_int
id|blocknr
suffix:semicolon
r_struct
id|jffs2_unknown_node
id|n
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ssize_t
id|retlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;EEEEEK. jffs2_mark_node_obsolete called with NULL node&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ref-&gt;flash_offset
op_amp
l_int|1
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_mark_node_obsolete called with already obsolete node at 0x%08x&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|blocknr
op_assign
id|ref-&gt;flash_offset
op_div
id|c-&gt;sector_size
suffix:semicolon
r_if
c_cond
(paren
id|blocknr
op_ge
id|c-&gt;nr_blocks
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;raw node at 0x%08x is off the end of device!&bslash;n&quot;
comma
id|ref-&gt;flash_offset
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|jeb
op_assign
op_amp
id|c-&gt;blocks
(braket
id|blocknr
)braket
suffix:semicolon
r_if
c_cond
(paren
id|jeb-&gt;used_size
OL
id|ref-&gt;totlen
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;raw node of size 0x%08x freed from erase block %d at 0x%08x, but used_size was already 0x%08x&bslash;n&quot;
comma
id|ref-&gt;totlen
comma
id|blocknr
comma
id|ref-&gt;flash_offset
comma
id|jeb-&gt;used_size
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|jeb-&gt;used_size
op_sub_assign
id|ref-&gt;totlen
suffix:semicolon
id|jeb-&gt;dirty_size
op_add_assign
id|ref-&gt;totlen
suffix:semicolon
id|c-&gt;used_size
op_sub_assign
id|ref-&gt;totlen
suffix:semicolon
id|c-&gt;dirty_size
op_add_assign
id|ref-&gt;totlen
suffix:semicolon
id|ref-&gt;flash_offset
op_or_assign
l_int|1
suffix:semicolon
id|ACCT_SANITY_CHECK
c_func
(paren
id|c
comma
id|jeb
)paren
suffix:semicolon
id|ACCT_PARANOIA_CHECK
c_func
(paren
id|jeb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;flags
op_amp
id|JFFS2_SB_FLAG_MOUNTING
)paren
(brace
multiline_comment|/* Mount in progress. Don&squot;t muck about with the block&n;&t;&t;   lists because they&squot;re not ready yet, and don&squot;t actually&n;&t;&t;   obliterate nodes that look obsolete. If they weren&squot;t &n;&t;&t;   marked obsolete on the flash at the time they _became_&n;&t;&t;   obsolete, there was probably a reason for that. */
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|jeb
op_eq
id|c-&gt;nextblock
)paren
(brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Not moving nextblock 0x%08x to dirty/erase_pending list&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|jeb
op_eq
id|c-&gt;gcblock
)paren
(brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Not moving gcblock 0x%08x to dirty/erase_pending list&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
)paren
suffix:semicolon
macro_line|#if 0 /* We no longer do this here. It can screw the wear levelling. If you have a lot of static&n;&t; data and a few blocks free, and you just create new files and keep deleting/overwriting&n;&t; them, then you&squot;d keep erasing and reusing those blocks without ever moving stuff around.&n;&t; So we leave completely obsoleted blocks on the dirty_list and let the GC delete them &n;&t; when it finds them there. That way, we still get the &squot;once in a while, take a clean block&squot;&n;&t; to spread out the flash usage */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|jeb-&gt;used_size
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Eraseblock at 0x%08x completely dirtied. Removing from (dirty?) list...&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|jeb-&gt;list
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;...and adding to erase_pending_list&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|jeb-&gt;list
comma
op_amp
id|c-&gt;erase_pending_list
)paren
suffix:semicolon
id|c-&gt;nr_erasing_blocks
op_increment
suffix:semicolon
id|jffs2_erase_pending_trigger
c_func
(paren
id|c
)paren
suffix:semicolon
singleline_comment|//&t;&t;OFNI_BS_2SFFJ(c)-&gt;s_dirt = 1;
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Done OK&bslash;n&quot;
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|jeb-&gt;dirty_size
op_eq
id|ref-&gt;totlen
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Eraseblock at 0x%08x is freshly dirtied. Removing from clean list...&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|jeb-&gt;list
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;...and adding to dirty_list&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|jeb-&gt;list
comma
op_amp
id|c-&gt;dirty_list
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;type
op_ne
id|MTD_NORFLASH
op_logical_and
id|c-&gt;mtd-&gt;type
op_ne
id|MTD_RAM
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|OFNI_BS_2SFFJ
c_func
(paren
id|c
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|MS_RDONLY
)paren
r_return
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;obliterating obsoleted node at 0x%08x&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|c-&gt;mtd
op_member_access_from_pointer
id|read
c_func
(paren
id|c-&gt;mtd
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
r_sizeof
(paren
id|n
)paren
comma
op_amp
id|retlen
comma
(paren
r_char
op_star
)paren
op_amp
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Read error reading from obsoleted node at 0x%08x: %d&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
id|ret
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retlen
op_ne
r_sizeof
(paren
id|n
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Short read from obsoleted node at 0x%08x: %d&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
id|retlen
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PAD
c_func
(paren
id|n.totlen
)paren
op_ne
id|PAD
c_func
(paren
id|ref-&gt;totlen
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Node totlen on flash (0x%08x) != totlen in node ref (0x%08x)&bslash;n&quot;
comma
id|n.totlen
comma
id|ref-&gt;totlen
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|n.nodetype
op_amp
id|JFFS2_NODE_ACCURATE
)paren
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Node at 0x%08x was already marked obsolete (nodetype 0x%04x&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
id|n.nodetype
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n.nodetype
op_and_assign
op_complement
id|JFFS2_NODE_ACCURATE
suffix:semicolon
id|ret
op_assign
id|c-&gt;mtd
op_member_access_from_pointer
id|write
c_func
(paren
id|c-&gt;mtd
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
r_sizeof
(paren
id|n
)paren
comma
op_amp
id|retlen
comma
(paren
r_char
op_star
)paren
op_amp
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Write error in obliterating obsoleted node at 0x%08x: %d&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
id|ret
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retlen
op_ne
r_sizeof
(paren
id|n
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Short write in obliterating obsoleted node at 0x%08x: %d&bslash;n&quot;
comma
id|ref-&gt;flash_offset
op_amp
op_complement
l_int|3
comma
id|retlen
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
