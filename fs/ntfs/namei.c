multiline_comment|/*&n; * namei.c - NTFS kernel directory inode operations. Part of the Linux-NTFS&n; * &t;     project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &quot;ntfs.h&quot;
macro_line|#include &quot;dir.h&quot;
multiline_comment|/**&n; * ntfs_lookup - find the inode represented by a dentry in a directory inode&n; * @dir_ino:&t;directory inode in which to look for the inode&n; * @dent:&t;dentry representing the inode to look for&n; *&n; * In short, ntfs_lookup() looks for the inode represented by the dentry @dent&n; * in the directory inode @dir_ino and if found attaches the inode to the&n; * dentry @dent.&n; *&n; * In more detail, the dentry @dent specifies which inode to look for by&n; * supplying the name of the inode in @dent-&gt;d_name.name. ntfs_lookup()&n; * converts the name to Unicode and walks the contents of the directory inode&n; * @dir_ino looking for the converted Unicode name. If the name is found in the&n; * directory, the corresponding inode is loaded by calling ntfs_iget() on its&n; * inode number and the inode is associated with the dentry @dent via a call to&n; * d_add().&n; *&n; * If the name is not found in the directory, a NULL inode is inserted into the&n; * dentry @dent. The dentry is then termed a negative dentry.&n; *&n; * Only if an actual error occurs, do we return an error via ERR_PTR().&n; *&n; * In order to handle the case insensitivity issues of NTFS with regards to the&n; * dcache and the dcache requiring only one dentry per directory, we deal with&n; * dentry aliases that only differ in case in -&gt;ntfs_lookup() while maintining&n; * a case sensitive dcache. This means that we get the full benefit of dcache&n; * speed when the file/directory is looked up with the same case as returned by&n; * -&gt;ntfs_readdir() but that a lookup for any other case (or for the short file&n; * name) will not find anything in dcache and will enter -&gt;ntfs_lookup()&n; * instead, where we search the directory for a fully matching file name&n; * (including case) and if that is not found, we search for a file name that&n; * matches with different case and if that has non-POSIX semantics we return&n; * that. We actually do only one search (case sensitive) and keep tabs on&n; * whether we have found a case insensitive match in the process.&n; *&n; * To simplify matters for us, we do not treat the short vs long filenames as&n; * two hard links but instead if the lookup matches a short filename, we&n; * return the dentry for the corresponding long filename instead.&n; *&n; * There are three cases we need to distinguish here:&n; *&n; * 1) @dent perfectly matches (i.e. including case) a directory entry with a&n; *    file name in the WIN32 or POSIX namespaces. In this case&n; *    ntfs_lookup_inode_by_name() will return with name set to NULL and we&n; *    just d_add() @dent.&n; * 2) @dent matches (not including case) a directory entry with a file name in&n; *    the WIN32 namespace. In this case ntfs_lookup_inode_by_name() will return&n; *    with name set to point to a kmalloc()ed ntfs_name structure containing&n; *    the properly cased little endian Unicode name. We convert the name to the&n; *    current NLS code page, search if a dentry with this name already exists&n; *    and if so return that instead of @dent. The VFS will then destroy the old&n; *    @dent and use the one we returned. If a dentry is not found, we allocate&n; *    a new one, d_add() it, and return it as above.&n; * 3) @dent matches either perfectly or not (i.e. we don&squot;t care about case) a&n; *    directory entry with a file name in the DOS namespace. In this case&n; *    ntfs_lookup_inode_by_name() will return with name set to point to a&n; *    kmalloc()ed ntfs_name structure containing the mft reference (cpu endian)&n; *    of the inode. We use the mft reference to read the inode and to find the&n; *    file name in the WIN32 namespace corresponding to the matched short file&n; *    name. We then convert the name to the current NLS code page, and proceed&n; *    searching for a dentry with this name, etc, as in case 2), above.&n; */
DECL|function|ntfs_lookup
r_static
r_struct
id|dentry
op_star
id|ntfs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir_ino
comma
r_struct
id|dentry
op_star
id|dent
)paren
(brace
id|ntfs_volume
op_star
id|vol
op_assign
id|NTFS_SB
c_func
(paren
id|dir_ino-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|dent_inode
suffix:semicolon
id|uchar_t
op_star
id|uname
suffix:semicolon
id|ntfs_name
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
id|MFT_REF
id|mref
suffix:semicolon
r_int
r_int
id|dent_ino
suffix:semicolon
r_int
id|uname_len
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Looking up %s in directory inode 0x%lx.&quot;
comma
id|dent-&gt;d_name.name
comma
id|dir_ino-&gt;i_ino
)paren
suffix:semicolon
multiline_comment|/* Convert the name of the dentry to Unicode. */
id|uname_len
op_assign
id|ntfs_nlstoucs
c_func
(paren
id|vol
comma
id|dent-&gt;d_name.name
comma
id|dent-&gt;d_name.len
comma
op_amp
id|uname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uname_len
OL
l_int|0
)paren
(brace
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Failed to convert name to Unicode.&quot;
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|uname_len
)paren
suffix:semicolon
)brace
id|mref
op_assign
id|ntfs_lookup_inode_by_name
c_func
(paren
id|NTFS_I
c_func
(paren
id|dir_ino
)paren
comma
id|uname
comma
id|uname_len
comma
op_amp
id|name
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|ntfs_name_cache
comma
id|uname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR_MREF
c_func
(paren
id|mref
)paren
)paren
(brace
id|dent_ino
op_assign
id|MREF
c_func
(paren
id|mref
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Found inode 0x%lx. Calling ntfs_iget.&quot;
comma
id|dent_ino
)paren
suffix:semicolon
id|dent_inode
op_assign
id|ntfs_iget
c_func
(paren
id|vol-&gt;sb
comma
id|dent_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dent_inode
)paren
)paren
)paren
(brace
multiline_comment|/* Consistency check. */
r_if
c_cond
(paren
id|MSEQNO
c_func
(paren
id|mref
)paren
op_eq
id|NTFS_I
c_func
(paren
id|dent_inode
)paren
op_member_access_from_pointer
id|seq_no
op_logical_or
id|dent_ino
op_eq
id|FILE_MFT
)paren
(brace
multiline_comment|/* Perfect WIN32/POSIX match. -- Case 1. */
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
id|d_add
c_func
(paren
id|dent
comma
id|dent_inode
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Done.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t;&t; * We are too indented. Handle imperfect&n;&t;&t;&t;&t; * matches and short file names further below.&n;&t;&t;&t;&t; */
r_goto
id|handle_name
suffix:semicolon
)brace
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Found stale reference to inode &quot;
l_string|&quot;0x%lx (reference sequence number = &quot;
l_string|&quot;0x%x, inode sequence number = 0x%x, &quot;
l_string|&quot;returning -EIO. Run chkdsk.&quot;
comma
id|dent_ino
comma
id|MSEQNO
c_func
(paren
id|mref
)paren
comma
id|NTFS_I
c_func
(paren
id|dent_inode
)paren
op_member_access_from_pointer
id|seq_no
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dent_inode
)paren
suffix:semicolon
id|dent_inode
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
r_else
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;ntfs_iget(0x%lx) failed with &quot;
l_string|&quot;error code %li.&quot;
comma
id|dent_ino
comma
id|PTR_ERR
c_func
(paren
id|dent_inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
multiline_comment|/* Return the error code. */
r_return
(paren
r_struct
id|dentry
op_star
)paren
id|dent_inode
suffix:semicolon
)brace
multiline_comment|/* It is guaranteed that name is no longer allocated at this point. */
r_if
c_cond
(paren
id|MREF_ERR
c_func
(paren
id|mref
)paren
op_eq
op_minus
id|ENOENT
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Entry was not found, adding negative dentry.&quot;
)paren
suffix:semicolon
multiline_comment|/* The dcache will handle negative entries. */
id|d_add
c_func
(paren
id|dent
comma
l_int|NULL
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Done.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;ntfs_lookup_ino_by_name() failed with error &quot;
l_string|&quot;code %i.&quot;
comma
op_minus
id|MREF_ERR
c_func
(paren
id|mref
)paren
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|MREF_ERR
c_func
(paren
id|mref
)paren
)paren
suffix:semicolon
singleline_comment|// TODO: Consider moving this lot to a separate function! (AIA)
id|handle_name
suffix:colon
(brace
r_struct
id|dentry
op_star
id|real_dent
suffix:semicolon
id|MFT_RECORD
op_star
id|m
suffix:semicolon
id|attr_search_context
op_star
id|ctx
suffix:semicolon
id|ntfs_inode
op_star
id|ni
op_assign
id|NTFS_I
c_func
(paren
id|dent_inode
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_struct
id|qstr
id|nls_name
suffix:semicolon
id|nls_name.name
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|name-&gt;type
op_ne
id|FILE_NAME_DOS
)paren
(brace
multiline_comment|/* Case 2. */
id|nls_name.len
op_assign
(paren
r_int
)paren
id|ntfs_ucstonls
c_func
(paren
id|vol
comma
(paren
id|uchar_t
op_star
)paren
op_amp
id|name-&gt;name
comma
id|name-&gt;len
comma
(paren
r_int
r_char
op_star
op_star
)paren
op_amp
id|nls_name.name
comma
id|name-&gt;len
op_star
l_int|3
op_plus
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* if (name-&gt;type == FILE_NAME_DOS) */
(brace
multiline_comment|/* Case 3. */
id|FILE_NAME_ATTR
op_star
id|fn
suffix:semicolon
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
multiline_comment|/* Find the WIN32 name corresponding to the matched DOS name. */
id|ni
op_assign
id|NTFS_I
c_func
(paren
id|dent_inode
)paren
suffix:semicolon
id|m
op_assign
id|map_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|m
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|m
)paren
suffix:semicolon
id|m
op_assign
l_int|NULL
suffix:semicolon
id|ctx
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|ctx
op_assign
id|get_attr_search_ctx
c_func
(paren
id|ni
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctx
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_do
(brace
id|ATTR_RECORD
op_star
id|a
suffix:semicolon
id|u32
id|val_len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lookup_attr
c_func
(paren
id|AT_FILE_NAME
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|ctx
)paren
)paren
(brace
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Inode corrupt: No WIN32 &quot;
l_string|&quot;namespace counterpart to DOS &quot;
l_string|&quot;file name. Run chkdsk.&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
multiline_comment|/* Consistency checks. */
id|a
op_assign
id|ctx-&gt;attr
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;non_resident
op_logical_or
id|a-&gt;flags
)paren
r_goto
id|eio_err_out
suffix:semicolon
id|val_len
op_assign
id|le32_to_cpu
c_func
(paren
id|a
op_member_access_from_pointer
id|_ARA
c_func
(paren
id|value_length
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|a
op_member_access_from_pointer
id|_ARA
c_func
(paren
id|value_offset
)paren
)paren
op_plus
id|val_len
OG
id|le32_to_cpu
c_func
(paren
id|a-&gt;length
)paren
)paren
r_goto
id|eio_err_out
suffix:semicolon
id|fn
op_assign
(paren
id|FILE_NAME_ATTR
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|ctx-&gt;attr
op_plus
id|le16_to_cpu
c_func
(paren
id|ctx-&gt;attr
op_member_access_from_pointer
id|_ARA
c_func
(paren
id|value_offset
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u32
)paren
(paren
id|fn-&gt;file_name_length
op_star
r_sizeof
(paren
id|uchar_t
)paren
op_plus
r_sizeof
(paren
id|FILE_NAME_ATTR
)paren
)paren
OG
id|val_len
)paren
r_goto
id|eio_err_out
suffix:semicolon
)brace
r_while
c_loop
(paren
id|fn-&gt;file_name_type
op_ne
id|FILE_NAME_WIN32
)paren
suffix:semicolon
multiline_comment|/* Convert the found WIN32 name to current NLS code page. */
id|nls_name.len
op_assign
(paren
r_int
)paren
id|ntfs_ucstonls
c_func
(paren
id|vol
comma
(paren
id|uchar_t
op_star
)paren
op_amp
id|fn-&gt;file_name
comma
id|fn-&gt;file_name_length
comma
(paren
r_int
r_char
op_star
op_star
)paren
op_amp
id|nls_name.name
comma
id|fn-&gt;file_name_length
op_star
l_int|3
op_plus
l_int|1
)paren
suffix:semicolon
id|put_attr_search_ctx
c_func
(paren
id|ctx
)paren
suffix:semicolon
id|unmap_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
)brace
id|m
op_assign
l_int|NULL
suffix:semicolon
id|ctx
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Check if a conversion error occured. */
r_if
c_cond
(paren
(paren
r_int
)paren
id|nls_name.len
OL
l_int|0
)paren
(brace
id|err
op_assign
(paren
r_int
)paren
id|nls_name.len
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|nls_name.hash
op_assign
id|full_name_hash
c_func
(paren
id|nls_name.name
comma
id|nls_name.len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note: No need for dparent_lock as i_sem is held on the parent inode.&n;&t; */
multiline_comment|/* Does a dentry matching the nls_name exist already? */
id|real_dent
op_assign
id|d_lookup
c_func
(paren
id|dent-&gt;d_parent
comma
op_amp
id|nls_name
)paren
suffix:semicolon
multiline_comment|/* If not, create it now. */
r_if
c_cond
(paren
op_logical_neg
id|real_dent
)paren
(brace
id|real_dent
op_assign
id|d_alloc
c_func
(paren
id|dent-&gt;d_parent
comma
op_amp
id|nls_name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|nls_name.name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|real_dent
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|d_add
c_func
(paren
id|real_dent
comma
id|dent_inode
)paren
suffix:semicolon
r_return
id|real_dent
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|nls_name.name
)paren
suffix:semicolon
multiline_comment|/* Matching dentry exists, check if it is negative. */
r_if
c_cond
(paren
id|real_dent-&gt;d_inode
)paren
(brace
id|BUG_ON
c_func
(paren
id|real_dent-&gt;d_inode
op_ne
id|dent_inode
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Already have the inode and the dentry attached, decrement&n;&t;&t; * the reference count to balance the ntfs_iget() we did&n;&t;&t; * earlier on.&n;&t;&t; */
id|iput
c_func
(paren
id|dent_inode
)paren
suffix:semicolon
r_return
id|real_dent
suffix:semicolon
)brace
multiline_comment|/* Negative dentry: instantiate it. */
id|d_instantiate
c_func
(paren
id|real_dent
comma
id|dent_inode
)paren
suffix:semicolon
r_return
id|real_dent
suffix:semicolon
id|eio_err_out
suffix:colon
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Illegal file name attribute. Run chkdsk.&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|err_out
suffix:colon
r_if
c_cond
(paren
id|ctx
)paren
id|put_attr_search_ctx
c_func
(paren
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
)paren
id|unmap_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dent_inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Inode operations for directories.&n; */
DECL|variable|ntfs_dir_inode_ops
r_struct
id|inode_operations
id|ntfs_dir_inode_ops
op_assign
(brace
dot
id|lookup
op_assign
id|ntfs_lookup
comma
multiline_comment|/* VFS: Lookup directory. */
)brace
suffix:semicolon
eof
