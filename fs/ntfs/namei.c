multiline_comment|/*&n; * namei.c - NTFS kernel directory inode operations. Part of the Linux-NTFS&n; * &t;     project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
macro_line|#include &quot;dir.h&quot;
multiline_comment|/**&n; * ntfs_lookup - find the inode represented by a dentry in a directory inode&n; * @dir_ino:&t;directory inode in which to look for the inode&n; * @dent:&t;dentry representing the inode to look for&n; *&n; * In short, ntfs_lookup() looks for the inode represented by the dentry @dent&n; * in the directory inode @dir_ino and if found attaches the inode to the&n; * dentry @dent.&n; *&n; * In more detail, the dentry @dent specifies which inode to look for by&n; * supplying the name of the inode in @dent-&gt;d_name.name. ntfs_lookup()&n; * converts the name to Unicode and walks the contents of the directory inode&n; * @dir_ino looking for the converted Unicode name. If the name is found in the&n; * directory, the corresponding inode is loaded by calling iget() on its inode&n; * number and the inode is associated with the dentry @dent via a call to&n; * d_add().&n; *&n; * If the name is not found in the directory, a NULL inode is inserted into the&n; * dentry @dent. The dentry is then termed a negative dentry.&n; *&n; * Only if an actual error occurs, do we return an error via ERR_PTR().&n; *&n; * TODO: Implement the below! (AIA)&n; *&n; * In order to handle the case insensitivity issues of NTFS with regards to the&n; * dcache and the dcache requiring only one dentry per directory, we deal with&n; * dentry aliases that only differ in case in -&gt;ntfs_lookup() while maintining&n; * a case sensitive dcache. This means that we get the full benefit of dcache&n; * speed when the file/directory is looked up with the same case as returned by&n; * -&gt;ntfs_readdir() but that a lookup for any other case (or for the short file&n; * name) will not find anything in dcache and will enter -&gt;ntfs_lookup()&n; * instead, where we search the directory for a fully matching file name&n; * (including case) and if that is not found, we search for a file name that&n; * matches with different case and if that has non-POSIX semantics we return&n; * that. We actually do only one search (case sensitive) and keep tabs on&n; * whether we have found a case insensitive match in the process.&n; *&n; * To simplify matters for us, we do not treat the short vs long filenames as&n; * two hard links but instead if the lookup matches a short filename, we&n; * return the dentry for the corresponding long filename instead.&n; *&n; * There are three cases we need to distinguish here:&n; *&n; * 1) @dent perfectly matches (i.e. including case) a directory entry with a&n; *    file name in the WIN32 or POSIX namespaces. In this case&n; *    ntfs_lookup_inode_by_name() will return with name set to NULL and we&n; *    just d_add() @dent.&n; * 2) @dent matches (not including case) a directory entry with a file name in&n; *    the WIN32 or POSIX namespaces. In this case ntfs_lookup_inode_by_name()&n; *    will return with name set to point to a kmalloc()ed ntfs_name structure&n; *    containing the properly cased little endian Unicode name. We convert the&n; *    name to the current NLS code page, search if a dentry with this name&n; *    already exists and if so return that instead of @dent. The VFS will then&n; *    destroy the old @dent and use the one we returned. If a dentry is not&n; *    found, we allocate a new one, d_add() it, and return it as above.&n; * 3) @dent matches either perfectly or not (i.e. we don&squot;t care about case) a&n; *    directory entry with a file name in the DOS namespace. In this case&n; *    ntfs_lookup_inode_by_name() will return with name set to point to a&n; *    kmalloc()ed ntfs_name structure containing the mft reference (cpu endian)&n; *    of the inode. We use the mft reference to read the inode and to find the&n; *    file name in the WIN32 namespace corresponding to the matched short file&n; *    name. We then convert the name to the current NLS code page, and proceed&n; *    searching for a dentry with this name, etc, as in case 2), above.&n; */
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
id|u64
id|mref
suffix:semicolon
r_int
r_int
id|dent_ino
suffix:semicolon
id|uchar_t
op_star
id|uname
suffix:semicolon
r_int
id|uname_len
suffix:semicolon
id|ntfs_name
op_star
id|name
op_assign
l_int|NULL
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
singleline_comment|// TODO: Handle name. (AIA)
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
(paren
r_int
r_int
)paren
id|MREF
c_func
(paren
id|mref
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Found inode 0x%lx. Calling iget.&quot;
comma
id|dent_ino
)paren
suffix:semicolon
id|dent_inode
op_assign
id|iget
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
id|dent_inode
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
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Found stale reference to inode &quot;
l_string|&quot;0x%Lx (reference sequence number = &quot;
l_string|&quot;0x%x, inode sequence number = 0x%x, &quot;
l_string|&quot;returning -EACCES. Run chkdsk.&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|MREF
c_func
(paren
id|mref
)paren
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
)brace
r_else
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;iget(0x%Lx) failed, returning &quot;
l_string|&quot;-EACCES.&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|MREF
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
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
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
)brace
multiline_comment|/*&n; * Inode operations for directories.&n; */
DECL|variable|ntfs_dir_inode_ops
r_struct
id|inode_operations
id|ntfs_dir_inode_ops
op_assign
(brace
id|lookup
suffix:colon
id|ntfs_lookup
comma
multiline_comment|/* VFS: Lookup directory. */
)brace
suffix:semicolon
eof
