multiline_comment|/* -*- c -*- --------------------------------------------------------------- *&n; *&n; * linux/fs/autofs/expire.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *  Copyright 1999-2000 Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&n; *  Copyright 2001-2003 Ian Kent &lt;raven@themaw.net&gt;&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &quot;autofs_i.h&quot;
DECL|variable|now
r_static
r_int
r_int
id|now
suffix:semicolon
multiline_comment|/* Check if a dentry can be expired return 1 if it can else return 0 */
DECL|function|autofs4_can_expire
r_static
r_inline
r_int
id|autofs4_can_expire
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
r_int
id|timeout
comma
r_int
id|do_now
)paren
(brace
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* dentry in the process of being deleted */
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No point expiring a pending mount */
r_if
c_cond
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_AUTOFS_PENDING
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|do_now
)paren
(brace
multiline_comment|/* Too young to die */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|ino-&gt;last_used
op_plus
id|timeout
comma
id|now
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* update last_used here :-&n;&t;&t;   - obviously makes sense if it is in use now&n;&t;&t;   - less obviously, prevents rapid-fire expire&n;&t;&t;     attempts if expire fails the first time */
id|ino-&gt;last_used
op_assign
id|now
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Check a mount point for busyness return 1 if not busy, otherwise */
DECL|function|autofs4_check_mount
r_static
r_int
id|autofs4_check_mount
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dentry %p %.*s&quot;
comma
id|dentry
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|mntget
c_func
(paren
id|mnt
)paren
suffix:semicolon
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|follow_down
c_func
(paren
op_amp
id|mnt
comma
op_amp
id|dentry
)paren
)paren
r_goto
id|done
suffix:semicolon
r_while
c_loop
(paren
id|d_mountpoint
c_func
(paren
id|dentry
)paren
op_logical_and
id|follow_down
c_func
(paren
op_amp
id|mnt
comma
op_amp
id|dentry
)paren
)paren
suffix:semicolon
multiline_comment|/* This is an autofs submount, we can&squot;t expire it */
r_if
c_cond
(paren
id|is_autofs4_dentry
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* The big question */
r_if
c_cond
(paren
id|may_umount_tree
c_func
(paren
id|mnt
)paren
op_eq
l_int|0
)paren
id|status
op_assign
l_int|1
suffix:semicolon
id|done
suffix:colon
id|DPRINTK
c_func
(paren
l_string|&quot;returning = %d&quot;
comma
id|status
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/* Check a directory tree of mount points for busyness&n; * The tree is not busy iff no mountpoints are busy&n; * Return 1 if the tree is busy or 0 otherwise&n; */
DECL|function|autofs4_check_tree
r_static
r_int
id|autofs4_check_tree
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|top
comma
r_int
r_int
id|timeout
comma
r_int
id|do_now
)paren
(brace
r_struct
id|dentry
op_star
id|this_parent
op_assign
id|top
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;parent %p %.*s&quot;
comma
id|top
comma
(paren
r_int
)paren
id|top-&gt;d_name.len
comma
id|top-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* Negative dentry - give up */
r_if
c_cond
(paren
op_logical_neg
id|simple_positive
c_func
(paren
id|top
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Timeout of a tree mount is determined by its top dentry */
r_if
c_cond
(paren
op_logical_neg
id|autofs4_can_expire
c_func
(paren
id|top
comma
id|timeout
comma
id|do_now
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|repeat
suffix:colon
id|next
op_assign
id|this_parent-&gt;d_subdirs.next
suffix:semicolon
id|resume
suffix:colon
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|this_parent-&gt;d_subdirs
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
multiline_comment|/* Negative dentry - give up */
r_if
c_cond
(paren
op_logical_neg
id|simple_positive
c_func
(paren
id|dentry
)paren
)paren
(brace
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;dentry %p %.*s&quot;
comma
id|dentry
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|simple_empty_nolock
c_func
(paren
id|dentry
)paren
)paren
(brace
id|this_parent
op_assign
id|dentry
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d_mountpoint
c_func
(paren
id|dentry
)paren
)paren
(brace
multiline_comment|/* First busy =&gt; tree busy */
r_if
c_cond
(paren
op_logical_neg
id|autofs4_check_mount
c_func
(paren
id|mnt
comma
id|dentry
)paren
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_parent
op_ne
id|top
)paren
(brace
id|next
op_assign
id|this_parent-&gt;d_child.next
suffix:semicolon
id|this_parent
op_assign
id|this_parent-&gt;d_parent
suffix:semicolon
r_goto
id|resume
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|autofs4_check_leaves
r_struct
id|dentry
op_star
id|autofs4_check_leaves
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|parent
comma
r_int
r_int
id|timeout
comma
r_int
id|do_now
)paren
(brace
r_struct
id|dentry
op_star
id|this_parent
op_assign
id|parent
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;parent %p %.*s&quot;
comma
id|parent
comma
(paren
r_int
)paren
id|parent-&gt;d_name.len
comma
id|parent-&gt;d_name.name
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|repeat
suffix:colon
id|next
op_assign
id|this_parent-&gt;d_subdirs.next
suffix:semicolon
id|resume
suffix:colon
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|this_parent-&gt;d_subdirs
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
multiline_comment|/* Negative dentry - give up */
r_if
c_cond
(paren
op_logical_neg
id|simple_positive
c_func
(paren
id|dentry
)paren
)paren
(brace
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;dentry %p %.*s&quot;
comma
id|dentry
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
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
id|dentry-&gt;d_subdirs
)paren
)paren
(brace
id|this_parent
op_assign
id|dentry
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d_mountpoint
c_func
(paren
id|dentry
)paren
)paren
(brace
multiline_comment|/* Can we expire this guy */
r_if
c_cond
(paren
op_logical_neg
id|autofs4_can_expire
c_func
(paren
id|dentry
comma
id|timeout
comma
id|do_now
)paren
)paren
r_goto
id|cont
suffix:semicolon
multiline_comment|/* Can we umount this guy */
r_if
c_cond
(paren
id|autofs4_check_mount
c_func
(paren
id|mnt
comma
id|dentry
)paren
)paren
r_return
id|dentry
suffix:semicolon
)brace
id|cont
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_parent
op_ne
id|parent
)paren
(brace
id|next
op_assign
id|this_parent-&gt;d_child.next
suffix:semicolon
id|this_parent
op_assign
id|this_parent-&gt;d_parent
suffix:semicolon
r_goto
id|resume
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Find an eligible tree to time-out&n; * A tree is eligible if :-&n; *  - it is unused by any user process&n; *  - it has been unused for exp_timeout time&n; */
DECL|function|autofs4_expire
r_static
r_struct
id|dentry
op_star
id|autofs4_expire
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
id|how
)paren
(brace
r_int
r_int
id|timeout
suffix:semicolon
r_struct
id|dentry
op_star
id|root
op_assign
id|sb-&gt;s_root
suffix:semicolon
r_struct
id|dentry
op_star
id|expired
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_int
id|do_now
op_assign
id|how
op_amp
id|AUTOFS_EXP_IMMEDIATE
suffix:semicolon
r_int
id|exp_leaves
op_assign
id|how
op_amp
id|AUTOFS_EXP_LEAVES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;exp_timeout
op_logical_or
op_logical_neg
id|root
)paren
r_return
l_int|NULL
suffix:semicolon
id|now
op_assign
id|jiffies
suffix:semicolon
id|timeout
op_assign
id|sbi-&gt;exp_timeout
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|next
op_assign
id|root-&gt;d_subdirs.next
suffix:semicolon
multiline_comment|/* On exit from the loop expire is set to a dgot dentry&n;&t; * to expire or it&squot;s NULL */
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|root-&gt;d_subdirs
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
multiline_comment|/* Negative dentry - give up */
r_if
c_cond
(paren
op_logical_neg
id|simple_positive
c_func
(paren
id|dentry
)paren
)paren
(brace
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
multiline_comment|/* Case 1: indirect mount or top level direct mount */
r_if
c_cond
(paren
id|d_mountpoint
c_func
(paren
id|dentry
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;checking mountpoint %p %.*s&quot;
comma
id|dentry
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* Can we expire this guy */
r_if
c_cond
(paren
op_logical_neg
id|autofs4_can_expire
c_func
(paren
id|dentry
comma
id|timeout
comma
id|do_now
)paren
)paren
r_goto
id|next
suffix:semicolon
multiline_comment|/* Can we umount this guy */
r_if
c_cond
(paren
id|autofs4_check_mount
c_func
(paren
id|mnt
comma
id|dentry
)paren
)paren
(brace
id|expired
op_assign
id|dentry
suffix:semicolon
r_break
suffix:semicolon
)brace
r_goto
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|simple_empty
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|next
suffix:semicolon
multiline_comment|/* Case 2: tree mount, expire iff entire tree is not busy */
r_if
c_cond
(paren
op_logical_neg
id|exp_leaves
)paren
(brace
r_if
c_cond
(paren
id|autofs4_check_tree
c_func
(paren
id|mnt
comma
id|dentry
comma
id|timeout
comma
id|do_now
)paren
)paren
(brace
id|expired
op_assign
id|dentry
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Case 3: direct mount, expire individual leaves */
)brace
r_else
(brace
id|expired
op_assign
id|autofs4_check_leaves
c_func
(paren
id|mnt
comma
id|dentry
comma
id|timeout
comma
id|do_now
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expired
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|next
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|expired
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;returning %p %.*s&quot;
comma
id|expired
comma
(paren
r_int
)paren
id|expired-&gt;d_name.len
comma
id|expired-&gt;d_name.name
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|expired-&gt;d_parent-&gt;d_subdirs
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|expired-&gt;d_parent-&gt;d_subdirs
comma
op_amp
id|expired-&gt;d_child
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
id|expired
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Perform an expiry operation */
DECL|function|autofs4_expire_run
r_int
id|autofs4_expire_run
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|autofs_packet_expire
id|__user
op_star
id|pkt_p
)paren
(brace
r_struct
id|autofs_packet_expire
id|pkt
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pkt
comma
l_int|0
comma
r_sizeof
id|pkt
)paren
suffix:semicolon
id|pkt.hdr.proto_version
op_assign
id|sbi-&gt;version
suffix:semicolon
id|pkt.hdr.type
op_assign
id|autofs_ptype_expire
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dentry
op_assign
id|autofs4_expire
c_func
(paren
id|sb
comma
id|mnt
comma
id|sbi
comma
l_int|0
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|pkt.len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|memcpy
c_func
(paren
id|pkt.name
comma
id|dentry-&gt;d_name.name
comma
id|pkt.len
)paren
suffix:semicolon
id|pkt.name
(braket
id|pkt.len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|pkt_p
comma
op_amp
id|pkt
comma
r_sizeof
(paren
r_struct
id|autofs_packet_expire
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Call repeatedly until it returns -EAGAIN, meaning there&squot;s nothing&n;   more to be done */
DECL|function|autofs4_expire_multi
r_int
id|autofs4_expire_multi
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_int
id|do_now
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_logical_and
id|get_user
c_func
(paren
id|do_now
comma
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dentry
op_assign
id|autofs4_expire
c_func
(paren
id|sb
comma
id|mnt
comma
id|sbi
comma
id|do_now
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|autofs_info
op_star
id|de_info
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* This is synchronous because it makes the daemon a&n;                   little easier */
id|de_info-&gt;flags
op_or_assign
id|AUTOFS_INF_EXPIRING
suffix:semicolon
id|ret
op_assign
id|autofs4_wait
c_func
(paren
id|sbi
comma
id|dentry
comma
id|NFY_EXPIRE
)paren
suffix:semicolon
id|de_info-&gt;flags
op_and_assign
op_complement
id|AUTOFS_INF_EXPIRING
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
