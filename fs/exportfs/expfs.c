macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
DECL|variable|export_op_default
r_struct
id|export_operations
id|export_op_default
suffix:semicolon
DECL|macro|CALL
mdefine_line|#define&t;CALL(ops,fun) ((ops-&gt;fun)?(ops-&gt;fun):export_op_default.fun)
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, args...) do{}while(0)
multiline_comment|/**&n; * find_exported_dentry - helper routine to implement export_operations-&gt;decode_fh&n; * @sb:&t;&t;The &amp;super_block identifying the filesystem&n; * @obj:&t;An opaque identifier of the object to be found - passed to&n; *&t;&t;get_inode&n; * @parent:&t;An optional opqaue identifier of the parent of the object.&n; * @acceptable:&t;A function used to test possible &amp;dentries to see if they are&n; *&t;&t;acceptable&n; * @context:&t;A parameter to @acceptable so that it knows on what basis to&n; *&t;&t;judge.&n; *&n; * find_exported_dentry is the central helper routine to enable file systems&n; * to provide the decode_fh() export_operation.  It&squot;s main task is to take&n; * an &amp;inode, find or create an appropriate &amp;dentry structure, and possibly&n; * splice this into the dcache in the correct place.&n; *&n; * The decode_fh() operation provided by the filesystem should call&n; * find_exported_dentry() with the same parameters that it received except&n; * that instead of the file handle fragment, pointers to opaque identifiers&n; * for the object and optionally its parent are passed.  The default decode_fh&n; * routine passes one pointer to the start of the filehandle fragment, and&n; * one 8 bytes into the fragment.  It is expected that most filesystems will&n; * take this approach, though the offset to the parent identifier may well be&n; * different.&n; *&n; * find_exported_dentry() will call get_dentry to get an dentry pointer from&n; * the file system.  If any &amp;dentry in the d_alias list is acceptable, it will&n; * be returned.  Otherwise find_exported_dentry() will attempt to splice a new&n; * &amp;dentry into the dcache using get_name() and get_parent() to find the&n; * appropriate place.&n; */
r_struct
id|dentry
op_star
DECL|function|find_exported_dentry
id|find_exported_dentry
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|obj
comma
r_void
op_star
id|parent
comma
r_int
(paren
op_star
id|acceptable
)paren
(paren
r_void
op_star
id|context
comma
r_struct
id|dentry
op_star
id|de
)paren
comma
r_void
op_star
id|context
)paren
(brace
r_struct
id|dentry
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dentry
op_star
id|target_dir
suffix:semicolon
r_int
id|err
suffix:semicolon
r_struct
id|export_operations
op_star
id|nops
op_assign
id|sb-&gt;s_export_op
suffix:semicolon
r_struct
id|list_head
op_star
id|le
comma
op_star
id|head
suffix:semicolon
r_struct
id|dentry
op_star
id|toput
op_assign
l_int|NULL
suffix:semicolon
r_int
id|noprogress
suffix:semicolon
multiline_comment|/*&n;&t; * Attempt to find the inode.&n;&t; */
id|result
op_assign
id|CALL
c_func
(paren
id|sb-&gt;s_export_op
comma
id|get_dentry
)paren
(paren
id|sb
comma
id|obj
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ESTALE
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|NULL
)paren
r_goto
id|err_out
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|result
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|result
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|result-&gt;d_inode-&gt;i_mode
)paren
op_logical_and
(paren
id|result-&gt;d_flags
op_amp
id|DCACHE_DISCONNECTED
)paren
)paren
(brace
multiline_comment|/* it is an unconnected directory, we must connect it */
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|acceptable
c_func
(paren
id|context
comma
id|result
)paren
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|result-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* there is no other dentry, so fail */
r_goto
id|err_result
suffix:semicolon
)brace
multiline_comment|/* try any other aliases */
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|result-&gt;d_inode-&gt;i_dentry
suffix:semicolon
id|list_for_each
c_func
(paren
id|le
comma
id|head
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
id|le
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
id|dget_locked
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
id|toput
)paren
id|dput
c_func
(paren
id|toput
)paren
suffix:semicolon
id|toput
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dentry
op_ne
id|result
op_logical_and
id|acceptable
c_func
(paren
id|context
comma
id|dentry
)paren
)paren
(brace
id|dput
c_func
(paren
id|result
)paren
suffix:semicolon
id|dentry-&gt;d_vfs_flags
op_or_assign
id|DCACHE_REFERENCED
suffix:semicolon
r_return
id|dentry
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|toput
op_assign
id|dentry
suffix:semicolon
)brace
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
id|toput
)paren
id|dput
c_func
(paren
id|toput
)paren
suffix:semicolon
)brace
multiline_comment|/* It&squot;s a directory, or we are required to confirm the file&squot;s&n;&t; * location in the tree based on the parent information&n; &t; */
id|dprintk
c_func
(paren
l_string|&quot;find_exported_dentry: need to look harder for %s/%d&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
op_star
(paren
r_int
op_star
)paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|result-&gt;d_inode-&gt;i_mode
)paren
)paren
id|target_dir
op_assign
id|dget
c_func
(paren
id|result
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|parent
op_eq
l_int|NULL
)paren
r_goto
id|err_result
suffix:semicolon
id|target_dir
op_assign
id|CALL
c_func
(paren
id|sb-&gt;s_export_op
comma
id|get_dentry
)paren
(paren
id|sb
comma
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|target_dir
)paren
)paren
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|target_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_dir
op_eq
l_int|NULL
op_logical_or
id|IS_ERR
c_func
(paren
id|target_dir
)paren
)paren
r_goto
id|err_result
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now we need to make sure that target_dir is properly connected.&n;&t; * It may already be, as the flag isn&squot;t always updated when connection&n;&t; * happens.&n;&t; * So, we walk up parent links until we find a connected directory,&n;&t; * or we run out of directories.  Then we find the parent, find&n;&t; * the name of the child in that parent, and do a lookup.&n;&t; * This should connect the child into the parent&n;&t; * We then repeat.&n;&t; */
multiline_comment|/* it is possible that a confused file system might not let us complete &n;&t; * the path to the root.  For example, if get_parent returns a directory&n;&t; * in which we cannot find a name for the child.  While this implies a&n;&t; * very sick filesystem we don&squot;t want it to cause knfsd to spin.  Hence&n;&t; * the noprogress counter.  If we go through the loop 10 times (2 is&n;&t; * probably enough) without getting anywhere, we just give up&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|noprogress
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|target_dir-&gt;d_flags
op_amp
id|DCACHE_DISCONNECTED
op_logical_and
id|noprogress
op_increment
OL
l_int|10
)paren
(brace
r_struct
id|dentry
op_star
id|pd
op_assign
id|target_dir
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dparent_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|pd
)paren
op_logical_and
(paren
id|pd-&gt;d_parent-&gt;d_flags
op_amp
id|DCACHE_DISCONNECTED
)paren
)paren
id|pd
op_assign
id|pd-&gt;d_parent
suffix:semicolon
id|dget
c_func
(paren
id|pd
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dparent_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|pd
)paren
)paren
(brace
multiline_comment|/* must have found a connected parent - great */
id|pd-&gt;d_flags
op_and_assign
op_complement
id|DCACHE_DISCONNECTED
suffix:semicolon
id|noprogress
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pd
op_eq
id|sb-&gt;s_root
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;export: Eeek filesystem root is not connected, impossible&bslash;n&quot;
)paren
suffix:semicolon
id|pd-&gt;d_flags
op_and_assign
op_complement
id|DCACHE_DISCONNECTED
suffix:semicolon
id|noprogress
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we have hit the top of a disconnected path.  Try&n;&t;&t;&t; * to find parent and connect&n;&t;&t;&t; * note: racing with some other process renaming a&n;&t;&t;&t; * directory isn&squot;t much of a problem here.  If someone&n;&t;&t;&t; * renames the directory, it will end up properly&n;&t;&t;&t; * connected, which is what we want&n;&t;&t;&t; */
r_struct
id|dentry
op_star
id|ppd
suffix:semicolon
r_struct
id|dentry
op_star
id|npd
suffix:semicolon
r_char
id|nbuf
(braket
id|NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pd-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|ppd
op_assign
id|CALL
c_func
(paren
id|nops
comma
id|get_parent
)paren
(paren
id|pd
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pd-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|ppd
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|ppd
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;find_exported_dentry: get_parent of %ld failed, err %d&bslash;n&quot;
comma
id|pd-&gt;d_inode-&gt;i_ino
comma
id|err
)paren
suffix:semicolon
id|dput
c_func
(paren
id|pd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;find_exported_dentry: find name of %lu in %lu&bslash;n&quot;
comma
id|pd-&gt;d_inode-&gt;i_ino
comma
id|ppd-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|err
op_assign
id|CALL
c_func
(paren
id|nops
comma
id|get_name
)paren
(paren
id|ppd
comma
id|nbuf
comma
id|pd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|dput
c_func
(paren
id|ppd
)paren
suffix:semicolon
id|dput
c_func
(paren
id|pd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|ENOENT
)paren
multiline_comment|/* some race between get_parent and&n;&t;&t;&t;&t;&t; * get_name?  just try again&n;&t;&t;&t;&t;&t; */
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;find_exported_dentry: found name: %s&bslash;n&quot;
comma
id|nbuf
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ppd-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|npd
op_assign
id|lookup_one_len
c_func
(paren
id|nbuf
comma
id|ppd
comma
id|strlen
c_func
(paren
id|nbuf
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ppd-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|npd
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|npd
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;find_exported_dentry: lookup failed: %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|dput
c_func
(paren
id|ppd
)paren
suffix:semicolon
id|dput
c_func
(paren
id|pd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* we didn&squot;t really want npd, we really wanted&n;&t;&t;&t; * a side-effect of the lookup.&n;&t;&t;&t; * hopefully, npd == pd, though it isn&squot;t really&n;&t;&t;&t; * a problem if it isn&squot;t&n;&t;&t;&t; */
r_if
c_cond
(paren
id|npd
op_eq
id|pd
)paren
id|noprogress
op_assign
l_int|0
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;find_exported_dentry: npd != pd&bslash;n&quot;
)paren
suffix:semicolon
id|dput
c_func
(paren
id|npd
)paren
suffix:semicolon
id|dput
c_func
(paren
id|ppd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ROOT
c_func
(paren
id|pd
)paren
)paren
(brace
multiline_comment|/* something went wrong, we have to give up */
id|dput
c_func
(paren
id|pd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|dput
c_func
(paren
id|pd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|target_dir-&gt;d_flags
op_amp
id|DCACHE_DISCONNECTED
)paren
(brace
multiline_comment|/* something went wrong - oh-well */
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
op_minus
id|ESTALE
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_goto
id|err_target
suffix:semicolon
)brace
multiline_comment|/* if we weren&squot;t after a directory, have one more step to go */
r_if
c_cond
(paren
id|result
op_ne
id|target_dir
)paren
(brace
r_struct
id|dentry
op_star
id|nresult
suffix:semicolon
r_char
id|nbuf
(braket
id|NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|err
op_assign
id|CALL
c_func
(paren
id|nops
comma
id|get_name
)paren
(paren
id|target_dir
comma
id|nbuf
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|down
c_func
(paren
op_amp
id|target_dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|nresult
op_assign
id|lookup_one_len
c_func
(paren
id|nbuf
comma
id|target_dir
comma
id|strlen
c_func
(paren
id|nbuf
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|target_dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|nresult
)paren
)paren
(brace
r_if
c_cond
(paren
id|nresult-&gt;d_inode
)paren
(brace
id|dput
c_func
(paren
id|result
)paren
suffix:semicolon
id|result
op_assign
id|nresult
suffix:semicolon
)brace
r_else
id|dput
c_func
(paren
id|nresult
)paren
suffix:semicolon
)brace
)brace
)brace
id|dput
c_func
(paren
id|target_dir
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* now result is properly connected, it is our best bet */
r_if
c_cond
(paren
id|acceptable
c_func
(paren
id|context
comma
id|result
)paren
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* one last try of the aliases.. */
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|toput
op_assign
l_int|NULL
suffix:semicolon
id|head
op_assign
op_amp
id|result-&gt;d_inode-&gt;i_dentry
suffix:semicolon
id|list_for_each
c_func
(paren
id|le
comma
id|head
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
id|le
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
id|dget_locked
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
id|toput
)paren
id|dput
c_func
(paren
id|toput
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry
op_ne
id|result
op_logical_and
id|acceptable
c_func
(paren
id|context
comma
id|dentry
)paren
)paren
(brace
id|dput
c_func
(paren
id|result
)paren
suffix:semicolon
id|dentry-&gt;d_vfs_flags
op_or_assign
id|DCACHE_REFERENCED
suffix:semicolon
r_return
id|dentry
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|toput
op_assign
id|dentry
suffix:semicolon
)brace
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
id|toput
)paren
id|dput
c_func
(paren
id|toput
)paren
suffix:semicolon
multiline_comment|/* drat - I just cannot find anything acceptable */
id|dput
c_func
(paren
id|result
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ESTALE
)paren
suffix:semicolon
id|err_target
suffix:colon
id|dput
c_func
(paren
id|target_dir
)paren
suffix:semicolon
id|err_result
suffix:colon
id|dput
c_func
(paren
id|result
)paren
suffix:semicolon
id|err_out
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
DECL|function|get_parent
r_static
r_struct
id|dentry
op_star
id|get_parent
c_func
(paren
r_struct
id|dentry
op_star
id|child
)paren
(brace
multiline_comment|/* get_parent cannot be supported generically, the locking&n;&t; * is too icky.&n;&t; * instead, we just return EACCES.  If server reboots or inodes&n;&t; * get flushed, you lose&n;&t; */
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
DECL|struct|getdents_callback
r_struct
id|getdents_callback
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name that was found. It already points to a&n;&t;&t;&t;&t;   buffer NAME_MAX+1 is size */
DECL|member|ino
r_int
r_int
id|ino
suffix:semicolon
multiline_comment|/* the inum we are looking for */
DECL|member|found
r_int
id|found
suffix:semicolon
multiline_comment|/* inode matched? */
DECL|member|sequence
r_int
id|sequence
suffix:semicolon
multiline_comment|/* sequence counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * A rather strange filldir function to capture&n; * the name matching the specified inode number.&n; */
DECL|function|filldir_one
r_static
r_int
id|filldir_one
c_func
(paren
r_void
op_star
id|__buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
id|loff_t
id|pos
comma
id|ino_t
id|ino
comma
r_int
r_int
id|d_type
)paren
(brace
r_struct
id|getdents_callback
op_star
id|buf
op_assign
id|__buf
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;sequence
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;ino
op_eq
id|ino
)paren
(brace
id|memcpy
c_func
(paren
id|buf-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|buf-&gt;name
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|buf-&gt;found
op_assign
l_int|1
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * get_name - default export_operations-&gt;get_name function&n; * @dentry: the directory in which to find a name&n; * @name:   a pointer to a %NAME_MAX+1 char buffer to store the name&n; * @child:  the dentry for the child directory.&n; *&n; * calls readdir on the parent until it finds an entry with&n; * the same inode number as the child, and returns that.&n; */
DECL|function|get_name
r_static
r_int
id|get_name
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|name
comma
r_struct
id|dentry
op_star
id|child
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|file
id|file
suffix:semicolon
r_struct
id|getdents_callback
id|buffer
suffix:semicolon
id|error
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_fop
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Open the directory ...&n;&t; */
id|error
op_assign
id|init_private_file
c_func
(paren
op_amp
id|file
comma
id|dentry
comma
id|FMODE_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file.f_op-&gt;readdir
)paren
r_goto
id|out_close
suffix:semicolon
id|buffer.name
op_assign
id|name
suffix:semicolon
id|buffer.ino
op_assign
id|child-&gt;d_inode-&gt;i_ino
suffix:semicolon
id|buffer.found
op_assign
l_int|0
suffix:semicolon
id|buffer.sequence
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|old_seq
op_assign
id|buffer.sequence
suffix:semicolon
id|error
op_assign
id|vfs_readdir
c_func
(paren
op_amp
id|file
comma
id|filldir_one
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_break
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer.found
)paren
r_break
suffix:semicolon
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|old_seq
op_eq
id|buffer.sequence
)paren
r_break
suffix:semicolon
)brace
id|out_close
suffix:colon
r_if
c_cond
(paren
id|file.f_op-&gt;release
)paren
id|file.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|dir
comma
op_amp
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|export_iget
r_static
r_struct
id|dentry
op_star
id|export_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|ino
comma
id|__u32
id|generation
)paren
(brace
multiline_comment|/* iget isn&squot;t really right if the inode is currently unallocated!!&n;&t; * This should really all be done inside each filesystem&n;&t; *&n;&t; * ext2fs&squot; read_inode has been strengthed to return a bad_inode if&n;&t; * the inode had been deleted.&n;&t; *&n;&t; * Currently we don&squot;t know the generation for parent directory, so&n;&t; * a generation of 0 means &quot;accept any&quot;&n;&t; */
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|result
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ESTALE
)paren
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|generation
op_logical_and
id|inode-&gt;i_generation
op_ne
id|generation
)paren
)paren
(brace
multiline_comment|/* we didn&squot;t find the right inode.. */
id|dprintk
c_func
(paren
l_string|&quot;fh_verify: Inode %lu, Bad count: %d %d or version  %u %u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_nlink
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
comma
id|inode-&gt;i_generation
comma
id|generation
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ESTALE
)paren
suffix:semicolon
)brace
multiline_comment|/* now to find a dentry.&n;&t; * If possible, get a well-connected one&n;&t; */
id|result
op_assign
id|d_alloc_anon
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|result-&gt;d_vfs_flags
op_or_assign
id|DCACHE_REFERENCED
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|get_object
r_static
r_struct
id|dentry
op_star
id|get_object
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|vobjp
)paren
(brace
id|__u32
op_star
id|objp
op_assign
id|vobjp
suffix:semicolon
r_int
r_int
id|ino
op_assign
id|objp
(braket
l_int|0
)braket
suffix:semicolon
id|__u32
id|generation
op_assign
id|objp
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|export_iget
c_func
(paren
id|sb
comma
id|ino
comma
id|generation
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * export_encode_fh - default export_operations-&gt;encode_fh function&n; * @dentry:  the dentry to encode&n; * @fh:      where to store the file handle fragment&n; * @max_len: maximum length to store there&n; * @connectable: whether to store parent infomation&n; *&n; * This default encode_fh function assumes that the 32 inode number&n; * is suitable for locating an inode, and that the generation number&n; * can be used to check that it is still valid.  It places them in the&n; * filehandle fragment where export_decode_fh expects to find them.&n; */
DECL|function|export_encode_fh
r_static
r_int
id|export_encode_fh
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u32
op_star
id|fh
comma
r_int
op_star
id|max_len
comma
r_int
id|connectable
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|len
op_assign
op_star
id|max_len
suffix:semicolon
r_int
id|type
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|2
op_logical_or
(paren
id|connectable
op_logical_and
id|len
OL
l_int|4
)paren
)paren
r_return
l_int|255
suffix:semicolon
id|len
op_assign
l_int|2
suffix:semicolon
id|fh
(braket
l_int|0
)braket
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|fh
(braket
l_int|1
)braket
op_assign
id|inode-&gt;i_generation
suffix:semicolon
r_if
c_cond
(paren
id|connectable
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_struct
id|inode
op_star
id|parent
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dparent_lock
)paren
suffix:semicolon
id|parent
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
id|fh
(braket
l_int|2
)braket
op_assign
id|parent-&gt;i_ino
suffix:semicolon
id|fh
(braket
l_int|3
)braket
op_assign
id|parent-&gt;i_generation
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dparent_lock
)paren
suffix:semicolon
id|len
op_assign
l_int|4
suffix:semicolon
id|type
op_assign
l_int|2
suffix:semicolon
)brace
op_star
id|max_len
op_assign
id|len
suffix:semicolon
r_return
id|type
suffix:semicolon
)brace
multiline_comment|/**&n; * export_decode_fh - default export_operations-&gt;decode_fh function&n; * @sb:  The superblock&n; * @fh:  pointer to the file handle fragment&n; * @fh_len: length of file handle fragment&n; * @acceptable: function for testing acceptability of dentrys&n; * @context:   context for @acceptable&n; *&n; * This is the default decode_fh() function.&n; * a fileid_type of 1 indicates that the filehandlefragment&n; * just contains an object identifier understood by  get_dentry.&n; * a fileid_type of 2 says that there is also a directory&n; * identifier 8 bytes in to the filehandlefragement.&n; */
DECL|function|export_decode_fh
r_static
r_struct
id|dentry
op_star
id|export_decode_fh
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|__u32
op_star
id|fh
comma
r_int
id|fh_len
comma
r_int
id|fileid_type
comma
r_int
(paren
op_star
id|acceptable
)paren
(paren
r_void
op_star
id|context
comma
r_struct
id|dentry
op_star
id|de
)paren
comma
r_void
op_star
id|context
)paren
(brace
id|__u32
id|parent
(braket
l_int|2
)braket
suffix:semicolon
id|parent
(braket
l_int|0
)braket
op_assign
id|parent
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fh_len
template_param
l_int|2
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|fileid_type
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|fh_len
OG
l_int|2
)paren
id|parent
(braket
l_int|0
)braket
op_assign
id|fh
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fh_len
OG
l_int|3
)paren
id|parent
(braket
l_int|1
)braket
op_assign
id|fh
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_return
id|find_exported_dentry
c_func
(paren
id|sb
comma
id|fh
comma
id|parent
comma
id|acceptable
comma
id|context
)paren
suffix:semicolon
)brace
DECL|variable|export_op_default
r_struct
id|export_operations
id|export_op_default
op_assign
(brace
dot
id|decode_fh
op_assign
id|export_decode_fh
comma
dot
id|encode_fh
op_assign
id|export_encode_fh
comma
dot
id|get_name
op_assign
id|get_name
comma
dot
id|get_parent
op_assign
id|get_parent
comma
dot
id|get_dentry
op_assign
id|get_object
comma
)brace
suffix:semicolon
DECL|variable|export_op_default
id|EXPORT_SYMBOL
c_func
(paren
id|export_op_default
)paren
suffix:semicolon
DECL|variable|find_exported_dentry
id|EXPORT_SYMBOL
c_func
(paren
id|find_exported_dentry
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
