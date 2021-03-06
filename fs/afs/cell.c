multiline_comment|/* cell.c: AFS cell and server record management&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;server.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;vlclient.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &quot;super.h&quot;
macro_line|#include &quot;internal.h&quot;
DECL|variable|afs_proc_cells_sem
id|DECLARE_RWSEM
c_func
(paren
id|afs_proc_cells_sem
)paren
suffix:semicolon
DECL|variable|afs_proc_cells
id|LIST_HEAD
c_func
(paren
id|afs_proc_cells
)paren
suffix:semicolon
DECL|variable|afs_cells
r_static
r_struct
id|list_head
id|afs_cells
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|afs_cells
)paren
suffix:semicolon
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|afs_cells_lock
)paren
suffix:semicolon
r_static
id|DECLARE_RWSEM
c_func
(paren
id|afs_cells_sem
)paren
suffix:semicolon
multiline_comment|/* add/remove serialisation */
DECL|variable|afs_cell_root
r_static
r_struct
id|afs_cell
op_star
id|afs_cell_root
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
r_static
id|cachefs_match_val_t
id|afs_cell_cache_match
c_func
(paren
r_void
op_star
id|target
comma
r_const
r_void
op_star
id|entry
)paren
suffix:semicolon
r_static
r_void
id|afs_cell_cache_update
c_func
(paren
r_void
op_star
id|source
comma
r_void
op_star
id|entry
)paren
suffix:semicolon
DECL|variable|afs_cache_cell_index_def
r_struct
id|cachefs_index_def
id|afs_cache_cell_index_def
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cell_ix&quot;
comma
dot
id|data_size
op_assign
r_sizeof
(paren
r_struct
id|afs_cache_cell
)paren
comma
dot
id|keys
(braket
l_int|0
)braket
op_assign
(brace
id|CACHEFS_INDEX_KEYS_ASCIIZ
comma
l_int|64
)brace
comma
dot
id|match
op_assign
id|afs_cell_cache_match
comma
dot
id|update
op_assign
id|afs_cell_cache_update
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * create a cell record&n; * - &quot;name&quot; is the name of the cell&n; * - &quot;vllist&quot; is a colon separated list of IP addresses in &quot;a.b.c.d&quot; format&n; */
DECL|function|afs_cell_create
r_int
id|afs_cell_create
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_char
op_star
id|vllist
comma
r_struct
id|afs_cell
op_star
op_star
id|_cell
)paren
(brace
r_struct
id|afs_cell
op_star
id|cell
suffix:semicolon
r_char
op_star
id|next
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%s&quot;
comma
id|name
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|name
)paren
suffix:semicolon
multiline_comment|/* TODO: want to look up &quot;this cell&quot; in the cache */
multiline_comment|/* allocate and initialise a cell record */
id|cell
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|afs_cell
)paren
op_plus
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cell
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ENOMEM&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|afs_cells_sem
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cell
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|afs_cell
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|cell-&gt;usage
comma
l_int|0
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cell-&gt;link
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|cell-&gt;sv_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cell-&gt;sv_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cell-&gt;sv_graveyard
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|cell-&gt;vl_sem
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cell-&gt;vl_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cell-&gt;vl_graveyard
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|cell-&gt;vl_gylock
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|cell-&gt;name
comma
id|name
)paren
suffix:semicolon
multiline_comment|/* fill in the VL server list from the rest of the string */
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_do
(brace
r_int
id|a
comma
id|b
comma
id|c
comma
id|d
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|vllist
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
op_star
id|next
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|vllist
comma
l_string|&quot;%u.%u.%u.%u&quot;
comma
op_amp
id|a
comma
op_amp
id|b
comma
op_amp
id|c
comma
op_amp
id|d
)paren
op_ne
l_int|4
)paren
r_goto
id|badaddr
suffix:semicolon
r_if
c_cond
(paren
id|a
OG
l_int|255
op_logical_or
id|b
OG
l_int|255
op_logical_or
id|c
OG
l_int|255
op_logical_or
id|d
OG
l_int|255
)paren
r_goto
id|badaddr
suffix:semicolon
id|cell-&gt;vl_addrs
(braket
id|cell-&gt;vl_naddrs
op_increment
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
(paren
id|a
op_lshift
l_int|24
)paren
op_or
(paren
id|b
op_lshift
l_int|16
)paren
op_or
(paren
id|c
op_lshift
l_int|8
)paren
op_or
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cell-&gt;vl_naddrs
op_ge
id|AFS_CELL_MAX_ADDRS
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vllist
op_assign
id|next
comma
id|vllist
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* add a proc dir for this cell */
id|ret
op_assign
id|afs_proc_cell_setup
c_func
(paren
id|cell
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
id|error
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
multiline_comment|/* put it up for caching */
id|cachefs_acquire_cookie
c_func
(paren
id|afs_cache_netfs.primary_index
comma
op_amp
id|afs_vlocation_cache_index_def
comma
id|cell
comma
op_amp
id|cell-&gt;cache
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* add to the cell lists */
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|cell-&gt;link
comma
op_amp
id|afs_cells
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|afs_proc_cells_sem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|cell-&gt;proc_link
comma
op_amp
id|afs_proc_cells
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|afs_proc_cells_sem
)paren
suffix:semicolon
op_star
id|_cell
op_assign
id|cell
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|afs_cells_sem
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 (%p)&quot;
comma
id|cell
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|badaddr
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kAFS: bad VL server IP address: &squot;%s&squot;&bslash;n&quot;
comma
id|vllist
)paren
suffix:semicolon
id|error
suffix:colon
id|up_write
c_func
(paren
op_amp
id|afs_cells_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cell
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_create() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the cell database from module parameters&n; */
DECL|function|afs_cell_init
r_int
id|afs_cell_init
c_func
(paren
r_char
op_star
id|rootcell
)paren
(brace
r_struct
id|afs_cell
op_star
id|old_root
comma
op_star
id|new_root
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rootcell
)paren
(brace
multiline_comment|/* module is loaded with no parameters, or built statically.&n;&t;&t; * - in the future we might initialize cell DB here.&n;&t;&t; */
id|_leave
c_func
(paren
l_string|&quot; = 0 (but no root)&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cp
op_assign
id|strchr
c_func
(paren
id|rootcell
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kAFS: no VL server IP addresses specified&bslash;n&quot;
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d (no colon)&quot;
comma
op_minus
id|EINVAL
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* allocate a cell record for the root cell */
op_star
id|cp
op_increment
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|afs_cell_create
c_func
(paren
id|rootcell
comma
id|cp
comma
op_amp
id|new_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* as afs_put_cell() takes locks by itself, we have to do&n;&t; * a little gymnastics to be race-free.&n;&t; */
id|afs_get_cell
c_func
(paren
id|new_root
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|afs_cell_root
)paren
(brace
id|old_root
op_assign
id|afs_cell_root
suffix:semicolon
id|afs_cell_root
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|afs_put_cell
c_func
(paren
id|old_root
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
)brace
id|afs_cell_root
op_assign
id|new_root
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * lookup a cell record&n; */
DECL|function|afs_cell_lookup
r_int
id|afs_cell_lookup
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|namesz
comma
r_struct
id|afs_cell
op_star
op_star
id|_cell
)paren
(brace
r_struct
id|afs_cell
op_star
id|cell
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&bslash;&quot;%*.*s&bslash;&quot;,&quot;
comma
id|namesz
comma
id|namesz
comma
id|name
ques
c_cond
id|name
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
op_star
id|_cell
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
multiline_comment|/* if the cell was named, look for it in the cell record list */
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|cell
op_assign
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|cell
comma
op_amp
id|afs_cells
comma
id|link
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cell-&gt;name
comma
id|name
comma
id|namesz
)paren
op_eq
l_int|0
)paren
(brace
id|afs_get_cell
c_func
(paren
id|cell
)paren
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
id|cell
op_assign
l_int|NULL
suffix:semicolon
id|found
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cell
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|read_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|cell
op_assign
id|afs_cell_root
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cell
)paren
(brace
multiline_comment|/* this should not happen unless user tries to mount&n;&t;&t;&t; * when root cell is not set. Return an impossibly&n;&t;&t;&t; * bizzare errno to alert the user. Things like&n;&t;&t;&t; * ENOENT might be &quot;more appropriate&quot; but they happen&n;&t;&t;&t; * for other reasons.&n;&t;&t;&t; */
id|ret
op_assign
op_minus
id|EDESTADDRREQ
suffix:semicolon
)brace
r_else
(brace
id|afs_get_cell
c_func
(paren
id|cell
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
)brace
op_star
id|_cell
op_assign
id|cell
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d (%p)&quot;
comma
id|ret
comma
id|cell
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_lookup() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * try and get a cell record&n; */
DECL|function|afs_get_cell_maybe
r_struct
id|afs_cell
op_star
id|afs_get_cell_maybe
c_func
(paren
r_struct
id|afs_cell
op_star
op_star
id|_cell
)paren
(brace
r_struct
id|afs_cell
op_star
id|cell
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|cell
op_assign
op_star
id|_cell
suffix:semicolon
r_if
c_cond
(paren
id|cell
op_logical_and
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;link
)paren
)paren
id|afs_get_cell
c_func
(paren
id|cell
)paren
suffix:semicolon
r_else
id|cell
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
r_return
id|cell
suffix:semicolon
)brace
multiline_comment|/* end afs_get_cell_maybe() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * destroy a cell record&n; */
DECL|function|afs_put_cell
r_void
id|afs_put_cell
c_func
(paren
r_struct
id|afs_cell
op_star
id|cell
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cell
)paren
r_return
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{%d,%s}&quot;
comma
id|cell
comma
id|atomic_read
c_func
(paren
op_amp
id|cell-&gt;usage
)paren
comma
id|cell-&gt;name
)paren
suffix:semicolon
multiline_comment|/* sanity check */
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|cell-&gt;usage
)paren
op_le
l_int|0
)paren
suffix:semicolon
multiline_comment|/* to prevent a race, the decrement and the dequeue must be effectively&n;&t; * atomic */
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|atomic_dec_and_test
c_func
(paren
op_amp
id|cell-&gt;usage
)paren
)paren
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;sv_list
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;sv_graveyard
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;vl_list
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;vl_graveyard
)paren
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; [unused]&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_put_cell() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * destroy a cell record&n; */
DECL|function|afs_cell_destroy
r_static
r_void
id|afs_cell_destroy
c_func
(paren
r_struct
id|afs_cell
op_star
id|cell
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;%p{%d,%s}&quot;
comma
id|cell
comma
id|atomic_read
c_func
(paren
op_amp
id|cell-&gt;usage
)paren
comma
id|cell-&gt;name
)paren
suffix:semicolon
multiline_comment|/* to prevent a race, the decrement and the dequeue must be effectively&n;&t; * atomic */
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
multiline_comment|/* sanity check */
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|cell-&gt;usage
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|cell-&gt;link
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|afs_cells_sem
)paren
suffix:semicolon
id|afs_proc_cell_remove
c_func
(paren
id|cell
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|afs_proc_cells_sem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|cell-&gt;proc_link
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|afs_proc_cells_sem
)paren
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
id|cachefs_relinquish_cookie
c_func
(paren
id|cell-&gt;cache
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|up_write
c_func
(paren
op_amp
id|afs_cells_sem
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;sv_list
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;sv_graveyard
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;vl_list
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;vl_graveyard
)paren
)paren
suffix:semicolon
multiline_comment|/* finish cleaning up the cell */
id|kfree
c_func
(paren
id|cell
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; [destroyed]&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_destroy() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * lookup the server record corresponding to an Rx RPC peer&n; */
DECL|function|afs_server_find_by_peer
r_int
id|afs_server_find_by_peer
c_func
(paren
r_const
r_struct
id|rxrpc_peer
op_star
id|peer
comma
r_struct
id|afs_server
op_star
op_star
id|_server
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
r_struct
id|afs_cell
op_star
id|cell
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{a=%08x},&quot;
comma
id|peer
comma
id|ntohl
c_func
(paren
id|peer-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
multiline_comment|/* search the cell list */
id|read_lock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|cell
comma
op_amp
id|afs_cells
comma
id|link
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;? cell %s&quot;
comma
id|cell-&gt;name
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|cell-&gt;sv_lock
)paren
suffix:semicolon
multiline_comment|/* check the active list */
id|list_for_each_entry
c_func
(paren
id|server
comma
op_amp
id|cell-&gt;sv_list
comma
id|link
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;?? server %08x&quot;
comma
id|ntohl
c_func
(paren
id|server-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|server-&gt;addr
comma
op_amp
id|peer-&gt;addr
comma
r_sizeof
(paren
r_struct
id|in_addr
)paren
)paren
op_eq
l_int|0
)paren
r_goto
id|found_server
suffix:semicolon
)brace
multiline_comment|/* check the inactive list */
id|spin_lock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|server
comma
op_amp
id|cell-&gt;sv_graveyard
comma
id|link
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;?? dead server %08x&quot;
comma
id|ntohl
c_func
(paren
id|server-&gt;addr.s_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|server-&gt;addr
comma
op_amp
id|peer-&gt;addr
comma
r_sizeof
(paren
r_struct
id|in_addr
)paren
)paren
op_eq
l_int|0
)paren
r_goto
id|found_dead_server
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|cell-&gt;sv_lock
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = -ENOENT&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
multiline_comment|/* we found it in the graveyard - resurrect it */
id|found_dead_server
suffix:colon
id|list_del
c_func
(paren
op_amp
id|server-&gt;link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|server-&gt;link
comma
op_amp
id|cell-&gt;sv_list
)paren
suffix:semicolon
id|afs_get_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|afs_kafstimod_del_timer
c_func
(paren
op_amp
id|server-&gt;timeout
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
r_goto
id|success
suffix:semicolon
multiline_comment|/* we found it - increment its ref count and return it */
id|found_server
suffix:colon
id|afs_get_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|success
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|cell-&gt;sv_lock
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
op_star
id|_server
op_assign
id|server
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 (s=%p c=%p)&quot;
comma
id|server
comma
id|cell
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_server_find_by_peer() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * purge in-memory cell database on module unload or afs_init() failure&n; * - the timeout daemon is stopped before calling this&n; */
DECL|function|afs_cell_purge
r_void
id|afs_cell_purge
c_func
(paren
r_void
)paren
(brace
r_struct
id|afs_vlocation
op_star
id|vlocation
suffix:semicolon
r_struct
id|afs_cell
op_star
id|cell
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|afs_put_cell
c_func
(paren
id|afs_cell_root
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|afs_cells
)paren
)paren
(brace
id|cell
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* remove the next cell from the front of the list */
id|write_lock
c_func
(paren
op_amp
id|afs_cells_lock
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
id|afs_cells
)paren
)paren
(brace
id|cell
op_assign
id|list_entry
c_func
(paren
id|afs_cells.next
comma
r_struct
id|afs_cell
comma
id|link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|cell-&gt;link
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|afs_cells_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cell
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;PURGING CELL %s (%d)&quot;
comma
id|cell-&gt;name
comma
id|atomic_read
c_func
(paren
op_amp
id|cell-&gt;usage
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;sv_list
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;vl_list
)paren
)paren
suffix:semicolon
multiline_comment|/* purge the cell&squot;s VL graveyard list */
id|_debug
c_func
(paren
l_string|&quot; - clearing VL graveyard&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cell-&gt;vl_gylock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;vl_graveyard
)paren
)paren
(brace
id|vlocation
op_assign
id|list_entry
c_func
(paren
id|cell-&gt;vl_graveyard.next
comma
r_struct
id|afs_vlocation
comma
id|link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|vlocation-&gt;link
)paren
suffix:semicolon
id|afs_kafstimod_del_timer
c_func
(paren
op_amp
id|vlocation-&gt;timeout
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cell-&gt;vl_gylock
)paren
suffix:semicolon
id|afs_vlocation_do_timeout
c_func
(paren
id|vlocation
)paren
suffix:semicolon
multiline_comment|/* TODO: race if move to use krxtimod instead&n;&t;&t;&t;&t; * of kafstimod */
id|spin_lock
c_func
(paren
op_amp
id|cell-&gt;vl_gylock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cell-&gt;vl_gylock
)paren
suffix:semicolon
multiline_comment|/* purge the cell&squot;s server graveyard list */
id|_debug
c_func
(paren
l_string|&quot; - clearing server graveyard&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cell-&gt;sv_graveyard
)paren
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
id|server
op_assign
id|list_entry
c_func
(paren
id|cell-&gt;sv_graveyard.next
comma
r_struct
id|afs_server
comma
id|link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|server-&gt;link
)paren
suffix:semicolon
id|afs_kafstimod_del_timer
c_func
(paren
op_amp
id|server-&gt;timeout
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
id|afs_server_do_timeout
c_func
(paren
id|server
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cell-&gt;sv_gylock
)paren
suffix:semicolon
multiline_comment|/* now the cell should be left with no references */
id|afs_cell_destroy
c_func
(paren
id|cell
)paren
suffix:semicolon
)brace
)brace
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_purge() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * match a cell record obtained from the cache&n; */
macro_line|#ifdef AFS_CACHING_SUPPORT
DECL|function|afs_cell_cache_match
r_static
id|cachefs_match_val_t
id|afs_cell_cache_match
c_func
(paren
r_void
op_star
id|target
comma
r_const
r_void
op_star
id|entry
)paren
(brace
r_const
r_struct
id|afs_cache_cell
op_star
id|ccell
op_assign
id|entry
suffix:semicolon
r_struct
id|afs_cell
op_star
id|cell
op_assign
id|target
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%s},{%s}&quot;
comma
id|ccell-&gt;name
comma
id|cell-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ccell-&gt;name
comma
id|cell-&gt;name
comma
r_sizeof
(paren
id|ccell-&gt;name
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = SUCCESS&quot;
)paren
suffix:semicolon
r_return
id|CACHEFS_MATCH_SUCCESS
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot; = FAILED&quot;
)paren
suffix:semicolon
r_return
id|CACHEFS_MATCH_FAILED
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_cache_match() */
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * update a cell record in the cache&n; */
macro_line|#ifdef AFS_CACHING_SUPPORT
DECL|function|afs_cell_cache_update
r_static
r_void
id|afs_cell_cache_update
c_func
(paren
r_void
op_star
id|source
comma
r_void
op_star
id|entry
)paren
(brace
r_struct
id|afs_cache_cell
op_star
id|ccell
op_assign
id|entry
suffix:semicolon
r_struct
id|afs_cell
op_star
id|cell
op_assign
id|source
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p,%p&quot;
comma
id|source
comma
id|entry
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|ccell-&gt;name
comma
id|cell-&gt;name
comma
r_sizeof
(paren
id|ccell-&gt;name
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ccell-&gt;vl_servers
comma
id|cell-&gt;vl_addrs
comma
id|min
c_func
(paren
r_sizeof
(paren
id|ccell-&gt;vl_servers
)paren
comma
r_sizeof
(paren
id|cell-&gt;vl_addrs
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_cell_cache_update() */
macro_line|#endif
eof
