multiline_comment|/*&n; *  linux/fs/ncpfs/symlink.c&n; *&n; *  Code for allowing symbolic links on NCPFS (i.e. NetWare)&n; *  Symbolic links are not supported on native NetWare, so we use an&n; *  infrequently-used flag (Sh) and store a two-word magic header in&n; *  the file to make sure we don&squot;t accidentally use a non-link file&n; *  as a link.&n; *&n; *  When using the NFS namespace, we set the mode to indicate a symlink and&n; *  don&squot;t bother with the magic numbers.&n; *&n; *  from linux/fs/ext2/symlink.c&n; *&n; *  Copyright (C) 1998-99, Frank A. Vorstenbosch&n; *&n; *  ncpfs symlink handling code&n; *  NLS support (c) 1999 Petr Vandrovec&n; *  Modified 2000 Ben Harris, University of Cambridge for NFS NS meta-info&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
multiline_comment|/* these magic numbers must appear in the symlink file -- this makes it a bit&n;   more resilient against the magic attributes being set on random files. */
DECL|macro|NCP_SYMLINK_MAGIC0
mdefine_line|#define NCP_SYMLINK_MAGIC0&t;le32_to_cpu(0x6c6d7973)     /* &quot;symlnk-&gt;&quot; */
DECL|macro|NCP_SYMLINK_MAGIC1
mdefine_line|#define NCP_SYMLINK_MAGIC1&t;le32_to_cpu(0x3e2d6b6e)
multiline_comment|/* ----- read a symbolic link ------------------------------------------ */
DECL|function|ncp_symlink_readpage
r_static
r_int
id|ncp_symlink_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
id|error
comma
id|length
comma
id|len
suffix:semicolon
r_char
op_star
id|link
comma
op_star
id|rawlink
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|rawlink
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|NCP_MAX_SYMLINK_SIZE
comma
id|GFP_NFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rawlink
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDONLY
)paren
)paren
r_goto
id|failEIO
suffix:semicolon
id|error
op_assign
id|ncp_read_kernel
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
l_int|0
comma
id|NCP_MAX_SYMLINK_SIZE
comma
id|rawlink
comma
op_amp
id|length
)paren
suffix:semicolon
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* Close file handle if no other users... */
id|ncp_make_closed
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|failEIO
suffix:semicolon
r_if
c_cond
(paren
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_amp
id|NCPI_KLUDGE_SYMLINK
)paren
(brace
r_if
c_cond
(paren
id|length
OL
id|NCP_MIN_SYMLINK_SIZE
op_logical_or
(paren
(paren
id|__u32
op_star
)paren
id|rawlink
)paren
(braket
l_int|0
)braket
op_ne
id|NCP_SYMLINK_MAGIC0
op_logical_or
(paren
(paren
id|__u32
op_star
)paren
id|rawlink
)paren
(braket
l_int|1
)braket
op_ne
id|NCP_SYMLINK_MAGIC1
)paren
r_goto
id|failEIO
suffix:semicolon
id|link
op_assign
id|rawlink
op_plus
l_int|8
suffix:semicolon
id|length
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|link
op_assign
id|rawlink
suffix:semicolon
)brace
id|len
op_assign
id|NCP_MAX_SYMLINK_SIZE
suffix:semicolon
id|error
op_assign
id|ncp_vol2io
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|buf
comma
op_amp
id|len
comma
id|link
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rawlink
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|failEIO
suffix:colon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
id|kfree
c_func
(paren
id|rawlink
)paren
suffix:semicolon
id|fail
suffix:colon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|ncp_symlink_aops
r_struct
id|address_space_operations
id|ncp_symlink_aops
op_assign
(brace
dot
id|readpage
op_assign
id|ncp_symlink_readpage
comma
)brace
suffix:semicolon
multiline_comment|/* ----- create a new symbolic link -------------------------------------- */
DECL|function|ncp_symlink
r_int
id|ncp_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
op_star
id|rawlink
suffix:semicolon
r_int
id|length
comma
id|err
comma
id|i
comma
id|outlen
suffix:semicolon
r_int
id|kludge
suffix:semicolon
r_int
id|mode
comma
id|attr
suffix:semicolon
r_int
r_int
id|hdr
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_symlink(dir=%p,dentry=%p,symname=%s)&bslash;n&quot;
comma
id|dir
comma
id|dentry
comma
id|symname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncp_is_nfs_extras
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|dir
)paren
comma
id|NCP_FINFO
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|volNumber
)paren
)paren
id|kludge
op_assign
l_int|0
suffix:semicolon
r_else
macro_line|#ifdef CONFIG_NCPFS_EXTRAS
r_if
c_cond
(paren
id|NCP_SERVER
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|m.flags
op_amp
id|NCP_MOUNT_SYMLINKS
)paren
id|kludge
op_assign
l_int|1
suffix:semicolon
r_else
macro_line|#endif
multiline_comment|/* EPERM is returned by VFS if symlink procedure does not exist */
r_return
op_minus
id|EPERM
suffix:semicolon
id|rawlink
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|NCP_MAX_SYMLINK_SIZE
comma
id|GFP_NFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rawlink
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|kludge
)paren
(brace
id|mode
op_assign
l_int|0
suffix:semicolon
id|attr
op_assign
id|aSHARED
op_or
id|aHIDDEN
suffix:semicolon
(paren
(paren
id|__u32
op_star
)paren
id|rawlink
)paren
(braket
l_int|0
)braket
op_assign
id|NCP_SYMLINK_MAGIC0
suffix:semicolon
(paren
(paren
id|__u32
op_star
)paren
id|rawlink
)paren
(braket
l_int|1
)braket
op_assign
id|NCP_SYMLINK_MAGIC1
suffix:semicolon
id|hdr
op_assign
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|mode
op_assign
id|S_IFLNK
op_or
id|S_IRWXUGO
suffix:semicolon
id|attr
op_assign
l_int|0
suffix:semicolon
id|hdr
op_assign
l_int|0
suffix:semicolon
)brace
id|length
op_assign
id|strlen
c_func
(paren
id|symname
)paren
suffix:semicolon
multiline_comment|/* map to/from server charset, do not touch upper/lower case as&n;&t;   symlink can point out of ncp filesystem */
id|outlen
op_assign
id|NCP_MAX_SYMLINK_SIZE
op_minus
id|hdr
suffix:semicolon
id|err
op_assign
id|ncp_io2vol
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|dir
)paren
comma
id|rawlink
op_plus
id|hdr
comma
op_amp
id|outlen
comma
id|symname
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|failfree
suffix:semicolon
id|outlen
op_add_assign
id|hdr
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|ncp_create_new
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
comma
l_int|0
comma
id|attr
)paren
)paren
(brace
r_goto
id|failfree
suffix:semicolon
)brace
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_WRONLY
)paren
)paren
r_goto
id|failfree
suffix:semicolon
r_if
c_cond
(paren
id|ncp_write_kernel
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
l_int|0
comma
id|outlen
comma
id|rawlink
comma
op_amp
id|i
)paren
op_logical_or
id|i
op_ne
id|outlen
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ncp_make_closed
c_func
(paren
id|inode
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rawlink
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
suffix:semicolon
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ncp_make_closed
c_func
(paren
id|inode
)paren
suffix:semicolon
id|failfree
suffix:colon
suffix:semicolon
id|kfree
c_func
(paren
id|rawlink
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* ----- EOF ----- */
eof
