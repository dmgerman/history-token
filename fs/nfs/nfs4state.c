multiline_comment|/*&n; *  fs/nfs/nfs4state.c&n; *&n; *  Client-side XDR for NFSv4.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Implementation of the NFSv4 state model.  For the time being,&n; * this is minimal, but will be made much more complex in a&n; * subsequent patch.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
multiline_comment|/* This protects most of the client-side state. */
DECL|variable|state_spinlock
r_static
id|spinlock_t
id|state_spinlock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|zero_stateid
id|nfs4_stateid
id|zero_stateid
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|one_stateid
id|nfs4_stateid
id|one_stateid
op_assign
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|nfs4_clientid_list
)paren
suffix:semicolon
multiline_comment|/*&n; * nfs4_get_client(): returns an empty client structure&n; * nfs4_put_client(): drops reference to client structure&n; *&n; * Since these are allocated/deallocated very rarely, we don&squot;t&n; * bother putting them in a slab cache...&n; */
r_struct
id|nfs4_client
op_star
DECL|function|nfs4_alloc_client
id|nfs4_alloc_client
c_func
(paren
r_struct
id|in_addr
op_star
id|addr
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|clp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|clp
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|memset
c_func
(paren
id|clp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|clp
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|clp-&gt;cl_addr
comma
id|addr
comma
r_sizeof
(paren
id|clp-&gt;cl_addr
)paren
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|clp-&gt;cl_sem
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|clp-&gt;cl_state_owners
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|clp-&gt;cl_lock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|clp-&gt;cl_count
comma
l_int|1
)paren
suffix:semicolon
id|clp-&gt;cl_state
op_assign
id|NFS4CLNT_NEW
suffix:semicolon
)brace
r_return
id|clp
suffix:semicolon
)brace
r_void
DECL|function|nfs4_free_client
id|nfs4_free_client
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|clp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
r_struct
id|nfs4_client
op_star
DECL|function|nfs4_get_client
id|nfs4_get_client
c_func
(paren
r_struct
id|in_addr
op_star
id|addr
)paren
(brace
r_struct
id|nfs4_client
op_star
r_new
comma
op_star
id|clp
op_assign
l_int|NULL
suffix:semicolon
r_new
op_assign
id|nfs4_alloc_client
c_func
(paren
id|addr
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|state_spinlock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|clp
comma
op_amp
id|nfs4_clientid_list
comma
id|cl_servers
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|clp-&gt;cl_addr
comma
id|addr
comma
r_sizeof
(paren
id|clp-&gt;cl_addr
)paren
)paren
op_eq
l_int|0
)paren
r_goto
id|found
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
)paren
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|cl_servers
comma
op_amp
id|nfs4_clientid_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|state_spinlock
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
id|found
suffix:colon
id|atomic_inc
c_func
(paren
op_amp
id|clp-&gt;cl_count
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|state_spinlock
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
)paren
id|nfs4_free_client
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|clp
suffix:semicolon
)brace
r_void
DECL|function|nfs4_put_client
id|nfs4_put_client
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|clp-&gt;cl_count
comma
op_amp
id|state_spinlock
)paren
)paren
r_return
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|clp-&gt;cl_servers
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|state_spinlock
)paren
suffix:semicolon
id|nfs4_free_client
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|nfs4_alloc_lockowner_id
id|nfs4_alloc_lockowner_id
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
)paren
(brace
id|u32
id|res
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|state_spinlock
)paren
suffix:semicolon
id|res
op_assign
id|clp-&gt;cl_lockowner_id
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|state_spinlock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * nfs4_get_state_owner(): this is called on the OPEN or CREATE path to&n; * obtain a new state_owner.&n; *&n; * There are three state_owners (open_owner4 in rfc3010) per inode,&n; * one for each possible combination of share lock access. Since&n; * Linux does not support the deny access type, there are&n; * three (not 9) referenced by the nfs_inode:&n; *&n; * O_WRONLY: inode-&gt;wo_owner&n; * O_RDONLY: inode-&gt;ro_owner&n; * O_RDWR:   inode-&gt;rw_owner&n; *&n; * We create a new state_owner the first time a file is OPENed with&n; * one of the above shares. All other OPENs with a similar&n; * share use the single stateid associated with the inode.&n; *&n; */
r_struct
id|nfs4_state_owner
op_star
DECL|function|nfs4_get_state_owner
id|nfs4_get_state_owner
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
r_struct
id|nfs4_state_owner
op_star
id|sp
suffix:semicolon
id|sp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sp
)paren
r_return
l_int|NULL
suffix:semicolon
id|clp
op_assign
(paren
id|NFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
)paren
op_member_access_from_pointer
id|nfs4_state
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|clp
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|sp-&gt;so_sema
)paren
suffix:semicolon
id|sp-&gt;so_seqid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* arbitrary */
id|memset
c_func
(paren
id|sp-&gt;so_stateid
comma
l_int|0
comma
r_sizeof
(paren
id|nfs4_stateid
)paren
)paren
suffix:semicolon
id|sp-&gt;so_id
op_assign
id|nfs4_alloc_lockowner_id
c_func
(paren
id|clp
)paren
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
multiline_comment|/*&n; * Called for each non-null inode state_owner in nfs_clear_inode, &n; * or if nfs4_do_open fails.&n; */
r_void
DECL|function|nfs4_put_state_owner
id|nfs4_put_state_owner
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs4_state_owner
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sp
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|sp-&gt;so_flags
op_amp
id|O_ACCMODE
)paren
id|nfs4_do_close
c_func
(paren
id|inode
comma
id|sp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;* Called with sp-&gt;so_sema held.&n;*&n;* Increment the seqid if the OPEN/OPEN_DOWNGRADE/CLOSE succeeded, or&n;* failed with a seqid incrementing error -&n;* see comments nfs_fs.h:seqid_mutating_error()&n;*/
r_void
DECL|function|nfs4_increment_seqid
id|nfs4_increment_seqid
c_func
(paren
id|u32
id|status
comma
r_struct
id|nfs4_state_owner
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
id|status
op_eq
id|NFS_OK
op_logical_or
id|seqid_mutating_err
c_func
(paren
id|status
)paren
)paren
id|sp-&gt;so_seqid
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;* Called by nfs4_proc_open to set the appropriate stateid&n;*/
r_int
DECL|function|nfs4_set_inode_share
id|nfs4_set_inode_share
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs4_state_owner
op_star
id|sp
comma
r_int
r_int
id|open_flags
)paren
(brace
r_struct
id|nfs_inode
op_star
id|nfsi
op_assign
id|NFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|open_flags
op_amp
id|O_ACCMODE
)paren
(brace
r_case
id|O_RDONLY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|nfsi-&gt;ro_owner
)paren
(brace
id|nfsi-&gt;ro_owner
op_assign
id|sp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|O_WRONLY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|nfsi-&gt;wo_owner
)paren
(brace
id|nfsi-&gt;wo_owner
op_assign
id|sp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|O_RDWR
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|nfsi-&gt;rw_owner
)paren
(brace
id|nfsi-&gt;rw_owner
op_assign
id|sp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n;* Boolean test to determine if an OPEN call goes on the wire.&n;*&n;* Called by nfs4_proc_open.&n;*/
r_int
DECL|function|nfs4_test_state_owner
id|nfs4_test_state_owner
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|open_flags
)paren
(brace
r_struct
id|nfs_inode
op_star
id|nfsi
op_assign
id|NFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|open_flags
op_amp
id|O_ACCMODE
)paren
(brace
r_case
id|O_RDONLY
suffix:colon
r_if
c_cond
(paren
id|nfsi-&gt;ro_owner
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|O_WRONLY
suffix:colon
r_if
c_cond
(paren
id|nfsi-&gt;wo_owner
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|O_RDWR
suffix:colon
r_if
c_cond
(paren
id|nfsi-&gt;rw_owner
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_struct
id|nfs4_state_owner
op_star
DECL|function|nfs4_get_inode_share
id|nfs4_get_inode_share
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|open_flags
)paren
(brace
r_struct
id|nfs_inode
op_star
id|nfsi
op_assign
id|NFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|open_flags
op_amp
id|O_ACCMODE
)paren
(brace
r_case
id|O_RDONLY
suffix:colon
r_return
id|nfsi-&gt;ro_owner
suffix:semicolon
r_case
id|O_WRONLY
suffix:colon
r_return
id|nfsi-&gt;wo_owner
suffix:semicolon
r_case
id|O_RDWR
suffix:colon
r_return
id|nfsi-&gt;rw_owner
suffix:semicolon
)brace
multiline_comment|/* Duh gcc warning if we don&squot;t... */
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 8&n; * End:&n; */
eof
