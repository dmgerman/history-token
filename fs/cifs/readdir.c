multiline_comment|/*&n; *   fs/cifs/readdir.c&n; *&n; *   Directory search handling&n; * &n; *   Copyright (C) International Business Machines  Corp., 2004&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_unicode.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;cifs_fs_sb.h&quot;
r_extern
r_int
id|CIFSFindFirst2
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|searchName
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
comma
id|__u16
op_star
id|searchHandle
comma
r_struct
id|cifs_search_info
op_star
id|psrch_inf
)paren
suffix:semicolon
r_extern
r_int
id|CIFSFindNext2
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
id|__u16
id|searchHandle
comma
r_struct
id|cifs_search_info
op_star
id|psrch_inf
)paren
suffix:semicolon
r_extern
r_int
id|construct_dentry
c_func
(paren
r_struct
id|qstr
op_star
id|qstring
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|inode
op_star
op_star
id|ptmp_inode
comma
r_struct
id|dentry
op_star
op_star
id|pnew_dentry
)paren
suffix:semicolon
r_extern
r_void
id|fill_in_inode
c_func
(paren
r_struct
id|inode
op_star
id|tmp_inode
comma
id|FILE_DIRECTORY_INFO
op_star
id|pfindData
comma
r_int
op_star
id|pobject_type
)paren
suffix:semicolon
r_extern
r_void
id|unix_fill_in_inode
c_func
(paren
r_struct
id|inode
op_star
id|tmp_inode
comma
id|FILE_UNIX_INFO
op_star
id|pfindData
comma
r_int
op_star
id|pobject_type
)paren
suffix:semicolon
multiline_comment|/* BB fixme - add debug wrappers around this function to disable it fixme BB */
multiline_comment|/* static void dump_cifs_file_struct(struct file * file, char * label)&n;{&n;&t;struct cifsFileInfo * cf;&n;&n;&t;if(file) {&n;&t;&t;cf = (struct cifsFileInfo *)file-&gt;private_data;&n;&t;&t;if(cf == NULL) {&n;&t;&t;&t;cFYI(1,(&quot;empty cifs private file data&quot;));&n;&t;&t;&t;return;&n;&t;&t;}&n;&t;&t;if(cf-&gt;invalidHandle) {&n;&t;&t;&t;cFYI(1,(&quot;invalid handle&quot;));&n;&t;&t;}&n;&t;&t;if(cf-&gt;srch_inf.endOfSearch) {&n;&t;&t;&t;cFYI(1,(&quot;end of search&quot;));&n;&t;&t;}&n;&t;&t;if(cf-&gt;srch_inf.emptyDir) {&n;&t;&t;&t;cFYI(1,(&quot;empty dir&quot;));&n;&t;&t;}&n;&t;&t;&n;&t;}&n;} */
DECL|function|initiate_cifs_search
r_static
r_int
id|initiate_cifs_search
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|full_path
suffix:semicolon
r_struct
id|cifsFileInfo
op_star
id|cifsFile
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;private_data
op_eq
l_int|NULL
)paren
(brace
id|file-&gt;private_data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cifsFileInfo
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;private_data
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
id|file-&gt;private_data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cifsFileInfo
)paren
)paren
suffix:semicolon
)brace
id|cifsFile
op_assign
(paren
r_struct
id|cifsFileInfo
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|cifsFile-&gt;invalidHandle
op_assign
id|TRUE
suffix:semicolon
id|cifsFile-&gt;srch_inf.endOfSearch
op_assign
id|FALSE
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|file-&gt;f_dentry-&gt;d_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
r_if
c_cond
(paren
id|pTcon
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_dentry
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_sb-&gt;s_vfs_rename_sem
)paren
suffix:semicolon
id|full_path
op_assign
id|build_wildcard_path_from_dentry
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_sb-&gt;s_vfs_rename_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|full_path
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Full path: %s start at: %lld &quot;
comma
id|full_path
comma
id|file-&gt;f_pos
)paren
)paren
suffix:semicolon
multiline_comment|/* test for Unix extensions */
r_if
c_cond
(paren
id|pTcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
(brace
id|cifsFile-&gt;srch_inf.info_level
op_assign
id|SMB_FIND_FILE_UNIX
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cifs_sb-&gt;mnt_cifs_flags
op_amp
id|CIFS_MOUNT_SERVER_INUM
)paren
(brace
id|cifsFile-&gt;srch_inf.info_level
op_assign
id|SMB_FIND_FILE_ID_FULL_DIR_INFO
suffix:semicolon
)brace
r_else
multiline_comment|/* not srvinos - BB fixme add check for backlevel? */
(brace
id|cifsFile-&gt;srch_inf.info_level
op_assign
id|SMB_FIND_FILE_DIRECTORY_INFO
suffix:semicolon
)brace
id|rc
op_assign
id|CIFSFindFirst2
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|cifs_sb-&gt;local_nls
comma
op_amp
id|cifsFile-&gt;netfid
comma
op_amp
id|cifsFile-&gt;srch_inf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|cifsFile-&gt;invalidHandle
op_assign
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|full_path
)paren
(brace
id|kfree
c_func
(paren
id|full_path
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* return length of unicode string in bytes */
DECL|function|cifs_unicode_bytelen
r_static
r_int
id|cifs_unicode_bytelen
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|len
suffix:semicolon
id|__le16
op_star
id|ustr
op_assign
(paren
id|__le16
op_star
)paren
id|str
suffix:semicolon
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_le
id|PATH_MAX
suffix:semicolon
id|len
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ustr
(braket
id|len
)braket
op_eq
l_int|0
)paren
(brace
r_return
id|len
op_lshift
l_int|1
suffix:semicolon
)brace
)brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Unicode string longer than PATH_MAX found&quot;
)paren
)paren
suffix:semicolon
r_return
id|len
op_lshift
l_int|1
suffix:semicolon
)brace
DECL|function|nxt_dir_entry
r_static
r_char
op_star
id|nxt_dir_entry
c_func
(paren
r_char
op_star
id|old_entry
comma
r_char
op_star
id|end_of_smb
)paren
(brace
r_char
op_star
id|new_entry
suffix:semicolon
id|FILE_DIRECTORY_INFO
op_star
id|pDirInfo
op_assign
(paren
id|FILE_DIRECTORY_INFO
op_star
)paren
id|old_entry
suffix:semicolon
id|new_entry
op_assign
id|old_entry
op_plus
id|pDirInfo-&gt;NextEntryOffset
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;new entry %p old entry %p&quot;
comma
id|new_entry
comma
id|old_entry
)paren
)paren
suffix:semicolon
multiline_comment|/* validate that new_entry is not past end of SMB */
r_if
c_cond
(paren
id|new_entry
op_ge
id|end_of_smb
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;search entry %p began after end of SMB %p old entry is %p&quot;
comma
id|new_entry
comma
id|end_of_smb
comma
id|old_entry
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_return
id|new_entry
suffix:semicolon
)brace
DECL|macro|UNICODE_DOT
mdefine_line|#define UNICODE_DOT cpu_to_le16(0x2e)
multiline_comment|/* return 0 if no match and 1 for . (current directory) and 2 for .. (parent) */
DECL|function|cifs_entry_is_dot
r_static
r_int
id|cifs_entry_is_dot
c_func
(paren
r_char
op_star
id|current_entry
comma
r_struct
id|cifsFileInfo
op_star
id|cfile
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|filename
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.info_level
op_eq
l_int|0x202
)paren
(brace
id|FILE_UNIX_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_UNIX_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.unicode
)paren
(brace
id|len
op_assign
id|cifs_unicode_bytelen
c_func
(paren
id|filename
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* BB should we make this strnlen of PATH_MAX? */
id|len
op_assign
id|strnlen
c_func
(paren
id|filename
comma
l_int|5
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.info_level
op_eq
l_int|0x101
)paren
(brace
id|FILE_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.info_level
op_eq
l_int|0x102
)paren
(brace
id|FILE_FULL_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_FULL_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.info_level
op_eq
l_int|0x105
)paren
(brace
id|SEARCH_ID_FULL_DIR_INFO
op_star
id|pFindData
op_assign
(paren
id|SEARCH_ID_FULL_DIR_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.info_level
op_eq
l_int|0x104
)paren
(brace
id|FILE_BOTH_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_BOTH_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Unknown findfirst level %d&quot;
comma
id|cfile-&gt;srch_inf.info_level
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filename
)paren
(brace
r_if
c_cond
(paren
id|cfile-&gt;srch_inf.unicode
)paren
(brace
id|__le16
op_star
id|ufilename
op_assign
(paren
id|__le16
op_star
)paren
id|filename
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|2
)paren
(brace
multiline_comment|/* check for . */
r_if
c_cond
(paren
id|ufilename
(braket
l_int|0
)braket
op_eq
id|UNICODE_DOT
)paren
(brace
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|len
op_eq
l_int|4
)paren
(brace
multiline_comment|/* check for .. */
r_if
c_cond
(paren
(paren
id|ufilename
(braket
l_int|0
)braket
op_eq
id|UNICODE_DOT
)paren
op_logical_and
(paren
id|ufilename
(braket
l_int|1
)braket
op_eq
id|UNICODE_DOT
)paren
)paren
(brace
id|rc
op_assign
l_int|2
suffix:semicolon
)brace
)brace
)brace
r_else
multiline_comment|/* ASCII */
(brace
r_if
c_cond
(paren
id|len
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|filename
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|len
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|filename
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|filename
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
)paren
(brace
id|rc
op_assign
l_int|2
suffix:semicolon
)brace
)brace
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* find the corresponding entry in the search */
multiline_comment|/* Note that the SMB server returns search entries for . and .. which&n;   complicates logic here if we choose to parse for them and we do not&n;   assume that they are located in the findfirst return buffer.*/
multiline_comment|/* We start counting in the buffer with entry 2 and increment for every&n;   entry (do not increment for . or .. entry) */
DECL|function|find_cifs_entry
r_static
r_int
id|find_cifs_entry
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|pTcon
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
op_star
id|ppCurrentEntry
comma
r_int
op_star
id|num_to_ret
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|pos_in_buf
op_assign
l_int|0
suffix:semicolon
id|loff_t
id|first_entry_in_buffer
suffix:semicolon
id|loff_t
id|index_to_find
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_struct
id|cifsFileInfo
op_star
id|cifsFile
op_assign
(paren
r_struct
id|cifsFileInfo
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
multiline_comment|/* check if index in the buffer */
r_if
c_cond
(paren
(paren
id|cifsFile
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|ppCurrentEntry
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|num_to_ret
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
op_star
id|ppCurrentEntry
op_assign
l_int|NULL
suffix:semicolon
id|first_entry_in_buffer
op_assign
id|cifsFile-&gt;srch_inf.index_of_last_entry
op_minus
id|cifsFile-&gt;srch_inf.entries_in_buffer
suffix:semicolon
multiline_comment|/*&t;dump_cifs_file_struct(file, &quot;In fce &quot;);*/
r_if
c_cond
(paren
id|index_to_find
OL
id|first_entry_in_buffer
)paren
(brace
multiline_comment|/* close and restart search */
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;search backing up - close and restart search&quot;
)paren
)paren
suffix:semicolon
id|cifsFile-&gt;invalidHandle
op_assign
id|TRUE
suffix:semicolon
id|CIFSFindClose
c_func
(paren
id|xid
comma
id|pTcon
comma
id|cifsFile-&gt;netfid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifsFile-&gt;search_resume_name
)paren
(brace
id|kfree
c_func
(paren
id|cifsFile-&gt;search_resume_name
)paren
suffix:semicolon
id|cifsFile-&gt;search_resume_name
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;freeing SMB ff cache buf on search rewind&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
id|cifs_buf_release
c_func
(paren
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
)paren
suffix:semicolon
)brace
id|rc
op_assign
id|initiate_cifs_search
c_func
(paren
id|xid
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;error %d reinitiating a search on rewind&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cifsFile-&gt;srch_inf.endOfSearch
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;end of search&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
)brace
r_while
c_loop
(paren
(paren
id|index_to_find
op_ge
id|cifsFile-&gt;srch_inf.index_of_last_entry
)paren
op_logical_and
(paren
id|rc
op_eq
l_int|0
)paren
op_logical_and
(paren
id|cifsFile-&gt;srch_inf.endOfSearch
op_eq
id|FALSE
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;calling findnext2&quot;
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|CIFSFindNext2
c_func
(paren
id|xid
comma
id|pTcon
comma
id|cifsFile-&gt;netfid
comma
op_amp
id|cifsFile-&gt;srch_inf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|index_to_find
OL
id|cifsFile-&gt;srch_inf.index_of_last_entry
)paren
(brace
multiline_comment|/* we found the buffer that contains the entry */
multiline_comment|/* scan and find it */
r_int
id|i
suffix:semicolon
r_char
op_star
id|current_entry
suffix:semicolon
r_char
op_star
id|end_of_smb
op_assign
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
op_plus
id|smbCalcSize
c_func
(paren
(paren
r_struct
id|smb_hdr
op_star
)paren
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
)paren
suffix:semicolon
multiline_comment|/*&t;dump_cifs_file_struct(file,&quot;found entry in fce &quot;); */
id|first_entry_in_buffer
op_assign
id|cifsFile-&gt;srch_inf.index_of_last_entry
op_minus
id|cifsFile-&gt;srch_inf.entries_in_buffer
suffix:semicolon
id|pos_in_buf
op_assign
id|index_to_find
op_minus
id|first_entry_in_buffer
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;found entry - pos_in_buf %d&quot;
comma
id|pos_in_buf
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
id|current_entry
op_assign
id|cifsFile-&gt;srch_inf.srch_entries_start
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
(paren
id|pos_in_buf
)paren
)paren
op_logical_and
(paren
id|current_entry
op_ne
l_int|NULL
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* go entry to next entry figuring out which we need to start with */
multiline_comment|/* if( . or ..)&n;&t;&t;&t;&t;skip */
id|rc
op_assign
id|cifs_entry_is_dot
c_func
(paren
id|current_entry
comma
id|cifsFile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|1
)paren
multiline_comment|/* is . or .. so skip */
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Entry is .&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
multiline_comment|/* continue; */
)brace
r_else
r_if
c_cond
(paren
id|rc
op_eq
l_int|2
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Entry is ..&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
multiline_comment|/* continue; */
)brace
id|current_entry
op_assign
id|nxt_dir_entry
c_func
(paren
id|current_entry
comma
id|end_of_smb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|current_entry
op_eq
l_int|NULL
)paren
op_logical_and
(paren
id|i
OL
id|pos_in_buf
)paren
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;reached end of buf searching for pos in buf %d index to find %lld rc %d&quot;
comma
id|pos_in_buf
comma
id|index_to_find
comma
id|rc
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
)brace
id|rc
op_assign
l_int|0
suffix:semicolon
op_star
id|ppCurrentEntry
op_assign
id|current_entry
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;index not in buffer - could not findnext into it&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos_in_buf
op_ge
id|cifsFile-&gt;srch_inf.entries_in_buffer
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;can not return entries when pos_in_buf beyond last entry&quot;
)paren
)paren
suffix:semicolon
op_star
id|num_to_ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
op_star
id|num_to_ret
op_assign
id|cifsFile-&gt;srch_inf.entries_in_buffer
op_minus
id|pos_in_buf
suffix:semicolon
multiline_comment|/*&t;dump_cifs_file_struct(file, &quot;end fce &quot;);*/
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* inode num, inode type and filename returned */
DECL|function|cifs_get_name_from_search_buf
r_static
r_int
id|cifs_get_name_from_search_buf
c_func
(paren
r_struct
id|qstr
op_star
id|pqst
comma
r_char
op_star
id|current_entry
comma
id|__u16
id|level
comma
r_int
r_int
id|unicode
comma
r_struct
id|nls_table
op_star
id|nlt
comma
id|ino_t
op_star
id|pinum
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
op_star
id|pinum
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_UNIX
)paren
(brace
id|FILE_UNIX_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_UNIX_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unicode
)paren
(brace
id|len
op_assign
id|cifs_unicode_bytelen
c_func
(paren
id|filename
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* BB should we make this strnlen of PATH_MAX? */
id|len
op_assign
id|strnlen
c_func
(paren
id|filename
comma
id|PATH_MAX
)paren
suffix:semicolon
)brace
multiline_comment|/* BB fixme - hash low and high 32 bits if not 64 bit arch BB fixme */
op_star
id|pinum
op_assign
id|pFindData-&gt;UniqueId
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_DIRECTORY_INFO
)paren
(brace
id|FILE_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_FULL_DIRECTORY_INFO
)paren
(brace
id|FILE_FULL_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_FULL_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_ID_FULL_DIR_INFO
)paren
(brace
id|SEARCH_ID_FULL_DIR_INFO
op_star
id|pFindData
op_assign
(paren
id|SEARCH_ID_FULL_DIR_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
op_star
id|pinum
op_assign
id|pFindData-&gt;UniqueId
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_BOTH_DIRECTORY_INFO
)paren
(brace
id|FILE_BOTH_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_BOTH_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Unknown findfirst level %d&quot;
comma
id|level
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unicode
)paren
(brace
multiline_comment|/* BB fixme - test with long names */
multiline_comment|/* Note converted filename can be longer than in unicode */
id|pqst-&gt;len
op_assign
id|cifs_strfromUCS_le
c_func
(paren
(paren
r_char
op_star
)paren
id|pqst-&gt;name
comma
(paren
m_wchar_t
op_star
)paren
id|filename
comma
id|len
op_div
l_int|2
comma
id|nlt
)paren
suffix:semicolon
)brace
r_else
(brace
id|pqst-&gt;name
op_assign
id|filename
suffix:semicolon
id|pqst-&gt;len
op_assign
id|len
suffix:semicolon
)brace
id|pqst-&gt;hash
op_assign
id|full_name_hash
c_func
(paren
id|pqst-&gt;name
comma
id|pqst-&gt;len
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;filldir on %s&quot;
comma
id|pqst-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|cifs_filldir2
id|cifs_filldir2
c_func
(paren
r_char
op_star
id|pfindEntry
comma
r_struct
id|file
op_star
id|file
comma
id|filldir_t
id|filldir
comma
r_void
op_star
id|direntry
comma
r_char
op_star
id|scratch_buf
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|qstr
id|qstring
suffix:semicolon
r_struct
id|cifsFileInfo
op_star
id|pCifsF
suffix:semicolon
r_int
id|obj_type
suffix:semicolon
id|ino_t
id|inum
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|inode
op_star
id|tmp_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|tmp_dentry
suffix:semicolon
multiline_comment|/* get filename and len into qstring */
multiline_comment|/* get dentry */
multiline_comment|/* decide whether to create and populate ionde */
r_if
c_cond
(paren
(paren
id|direntry
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|file
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pCifsF
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scratch_buf
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|pfindEntry
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|pCifsF
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_dentry
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|file-&gt;f_dentry-&gt;d_sb
)paren
suffix:semicolon
id|qstring.name
op_assign
id|scratch_buf
suffix:semicolon
id|rc
op_assign
id|cifs_get_name_from_search_buf
c_func
(paren
op_amp
id|qstring
comma
id|pfindEntry
comma
id|pCifsF-&gt;srch_inf.info_level
comma
id|pCifsF-&gt;srch_inf.unicode
comma
id|cifs_sb-&gt;local_nls
comma
op_amp
id|inum
multiline_comment|/* returned */
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
id|rc
op_assign
id|construct_dentry
c_func
(paren
op_amp
id|qstring
comma
id|file
comma
op_amp
id|tmp_inode
comma
op_amp
id|tmp_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp_inode
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|tmp_dentry
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
)paren
(brace
multiline_comment|/* inode created, we need to hash it with right inode number */
r_if
c_cond
(paren
id|inum
op_ne
l_int|0
)paren
(brace
multiline_comment|/* BB fixme - hash the 2 32 quantities bits together if necessary BB */
id|tmp_inode-&gt;i_ino
op_assign
id|inum
suffix:semicolon
)brace
id|insert_inode_hash
c_func
(paren
id|tmp_inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pCifsF-&gt;srch_inf.info_level
op_eq
id|SMB_FIND_FILE_UNIX
)paren
(brace
id|unix_fill_in_inode
c_func
(paren
id|tmp_inode
comma
(paren
id|FILE_UNIX_INFO
op_star
)paren
id|pfindEntry
comma
op_amp
id|obj_type
)paren
suffix:semicolon
)brace
r_else
(brace
id|fill_in_inode
c_func
(paren
id|tmp_inode
comma
(paren
id|FILE_DIRECTORY_INFO
op_star
)paren
id|pfindEntry
comma
op_amp
id|obj_type
)paren
suffix:semicolon
)brace
id|rc
op_assign
id|filldir
c_func
(paren
id|direntry
comma
id|qstring.name
comma
id|qstring.len
comma
id|file-&gt;f_pos
comma
id|tmp_inode-&gt;i_ino
comma
id|obj_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;filldir rc = %d&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|tmp_dentry
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cifs_save_resume_key
r_int
id|cifs_save_resume_key
c_func
(paren
r_const
r_char
op_star
id|current_entry
comma
r_struct
id|cifsFileInfo
op_star
id|cifsFile
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|__u16
id|level
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cifsFile
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|current_entry
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|level
op_assign
id|cifsFile-&gt;srch_inf.info_level
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_UNIX
)paren
(brace
id|FILE_UNIX_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_UNIX_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cifsFile-&gt;srch_inf.unicode
)paren
(brace
id|len
op_assign
id|cifs_unicode_bytelen
c_func
(paren
id|filename
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* BB should we make this strnlen of PATH_MAX? */
id|len
op_assign
id|strnlen
c_func
(paren
id|filename
comma
id|PATH_MAX
)paren
suffix:semicolon
)brace
id|cifsFile-&gt;srch_inf.resume_key
op_assign
id|pFindData-&gt;ResumeKey
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_DIRECTORY_INFO
)paren
(brace
id|FILE_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
id|cifsFile-&gt;srch_inf.resume_key
op_assign
id|pFindData-&gt;FileIndex
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_FULL_DIRECTORY_INFO
)paren
(brace
id|FILE_FULL_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_FULL_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
id|cifsFile-&gt;srch_inf.resume_key
op_assign
id|pFindData-&gt;FileIndex
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_ID_FULL_DIR_INFO
)paren
(brace
id|SEARCH_ID_FULL_DIR_INFO
op_star
id|pFindData
op_assign
(paren
id|SEARCH_ID_FULL_DIR_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
id|cifsFile-&gt;srch_inf.resume_key
op_assign
id|pFindData-&gt;FileIndex
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SMB_FIND_FILE_BOTH_DIRECTORY_INFO
)paren
(brace
id|FILE_BOTH_DIRECTORY_INFO
op_star
id|pFindData
op_assign
(paren
id|FILE_BOTH_DIRECTORY_INFO
op_star
)paren
id|current_entry
suffix:semicolon
id|filename
op_assign
op_amp
id|pFindData-&gt;FileName
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|pFindData-&gt;FileNameLength
suffix:semicolon
id|cifsFile-&gt;srch_inf.resume_key
op_assign
id|pFindData-&gt;FileIndex
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Unknown findfirst level %d&quot;
comma
id|level
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cifsFile-&gt;srch_inf.resume_name_len
op_assign
id|len
suffix:semicolon
id|cifsFile-&gt;srch_inf.presume_name
op_assign
id|filename
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cifs_readdir2
r_int
id|cifs_readdir2
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|direntry
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|xid
comma
id|i
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_struct
id|cifsFileInfo
op_star
id|cifsFile
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|current_entry
suffix:semicolon
r_int
id|num_to_fill
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|tmp_buf
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|end_of_smb
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_dentry
op_eq
l_int|NULL
)paren
(brace
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&t;dump_cifs_file_struct(file, &quot;Begin rdir &quot;); */
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|file-&gt;f_dentry-&gt;d_sb
)paren
suffix:semicolon
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
r_if
c_cond
(paren
id|pTcon
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;readdir2 pos: %lld&quot;
comma
id|file-&gt;f_pos
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
r_switch
c_cond
(paren
(paren
r_int
)paren
id|file-&gt;f_pos
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*if (filldir(direntry, &quot;.&quot;, 1, file-&gt;f_pos,&n;&t;&t;     file-&gt;f_dentry-&gt;d_inode-&gt;i_ino, DT_DIR) &lt; 0) {&n;&t;&t;&t;cERROR(1, (&quot;Filldir for current dir failed &quot;));&n;&t;&t;&t;rc = -ENOMEM;&n;&t;&t;&t;break;&n;&t;&t;}&n;&t;&t;file-&gt;f_pos++; */
r_case
l_int|1
suffix:colon
multiline_comment|/* if (filldir(direntry, &quot;..&quot;, 2, file-&gt;f_pos,&n;&t;&t;     file-&gt;f_dentry-&gt;d_parent-&gt;d_inode-&gt;i_ino, DT_DIR) &lt; 0) {&n;&t;&t;&t;cERROR(1, (&quot;Filldir for parent dir failed &quot;));&n;&t;&t;&t;rc = -ENOMEM;&n;&t;&t;&t;break;&n;&t;&t;}&n;&t;&t;file-&gt;f_pos++; */
r_case
l_int|2
suffix:colon
multiline_comment|/* 1) If search is active, &n;&t;&t;&t;is in current search buffer? &n;&t;&t;&t;if it before then restart search&n;&t;&t;&t;if after then keep searching till find it */
r_if
c_cond
(paren
id|file-&gt;private_data
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
id|initiate_cifs_search
c_func
(paren
id|xid
comma
id|file
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;initiate cifs search rc %d&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|file-&gt;private_data
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|cifsFile
op_assign
(paren
r_struct
id|cifsFileInfo
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|cifsFile-&gt;srch_inf.endOfSearch
)paren
(brace
r_if
c_cond
(paren
id|cifsFile-&gt;srch_inf.emptyDir
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;End of search, empty dir&quot;
)paren
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* else {&n;&t;&t;&t;cifsFile-&gt;invalidHandle = TRUE;&n;&t;&t;&t;CIFSFindClose(xid, pTcon, cifsFile-&gt;netfid);&n;&t;&t;} &n;&t;&t;if(cifsFile-&gt;search_resume_name) {&n;&t;&t;&t;kfree(cifsFile-&gt;search_resume_name);&n;&t;&t;&t;cifsFile-&gt;search_resume_name = NULL;&n;&t;&t;} */
multiline_comment|/* BB account for . and .. in f_pos */
multiline_comment|/* dump_cifs_file_struct(file, &quot;rdir after default &quot;);*/
id|rc
op_assign
id|find_cifs_entry
c_func
(paren
id|xid
comma
id|pTcon
comma
id|file
comma
op_amp
id|current_entry
comma
op_amp
id|num_to_fill
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;fce error %d&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
r_goto
id|rddir2_exit
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;entry %lld found&quot;
comma
id|file-&gt;f_pos
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current_entry
op_eq
l_int|NULL
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;current search entry null,exiting&quot;
)paren
)paren
suffix:semicolon
r_goto
id|rddir2_exit
suffix:semicolon
)brace
multiline_comment|/* 2) initiate search, */
multiline_comment|/* 3) seek into search buffer */
multiline_comment|/* 4) if not found &amp;&amp; later - FindNext */
multiline_comment|/* else if earlier in search, close search and &n;&t;&t;&t;&t;restart, continuing search till found or EndOfSearch */
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;loop through %d times filling dir for net buf start %p&quot;
comma
id|num_to_fill
comma
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
id|end_of_smb
op_assign
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
op_plus
id|smbCalcSize
c_func
(paren
(paren
r_struct
id|smb_hdr
op_star
)paren
id|cifsFile-&gt;srch_inf.ntwrk_buf_start
)paren
suffix:semicolon
id|tmp_buf
op_assign
id|kmalloc
c_func
(paren
id|NAME_MAX
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;end of smb %p and tmp_buf %p current_entry %p&quot;
comma
id|end_of_smb
comma
id|tmp_buf
comma
id|current_entry
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|num_to_fill
)paren
op_logical_and
(paren
id|rc
op_eq
l_int|0
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|current_entry
op_eq
l_int|NULL
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;beyond end of smb with num to fill %d i %d&quot;
comma
id|num_to_fill
comma
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
r_break
suffix:semicolon
)brace
multiline_comment|/*&t;&t;&t;if((!(cifs_sb-&gt;mnt_cifs_flags &amp; CIFS_MOUNT_SERVER_INUM)) || &n;&t;&t;&t;   (cifsFile-&gt;srch_inf.info_level != something that supports server inodes)) {&n;&t;&t;&t;&t;create dentry&n;&t;&t;&t;&t;create inode&n;&t;&t;&t;&t;fill in inode new_inode (which makes number locally)&n;&t;&t;&t;}&n;&t;&t;&t;also create local inode for per reasons unless new mount parm says otherwise */
id|rc
op_assign
id|cifs_filldir2
c_func
(paren
id|current_entry
comma
id|file
comma
id|filldir
comma
id|direntry
comma
id|tmp_buf
)paren
suffix:semicolon
id|file-&gt;f_pos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_eq
id|cifsFile-&gt;srch_inf.index_of_last_entry
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;last entry in buf at pos %lld %s&quot;
comma
id|file-&gt;f_pos
comma
id|tmp_buf
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
multiline_comment|/* BB fixme save resume key BB */
id|cifs_save_resume_key
c_func
(paren
id|current_entry
comma
id|cifsFile
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
id|current_entry
op_assign
id|nxt_dir_entry
c_func
(paren
id|current_entry
comma
id|end_of_smb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp_buf
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|tmp_buf
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* end switch */
id|rddir2_exit
suffix:colon
multiline_comment|/* dump_cifs_file_struct(file, &quot;end rdir &quot;);  */
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
