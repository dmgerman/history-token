multiline_comment|/*&n; *   fs/cifs/ioctl.c&n; *&n; *   vfs operations that deal with io control&n; *&n; *   Copyright (C) International Business Machines  Corp., 2005&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
DECL|function|cifs_ioctl
r_int
id|cifs_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filep
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|ENOTTY
suffix:semicolon
multiline_comment|/* strange error - but the precedent */
macro_line|#ifdef CONFIG_CIFS_POSIX
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;ioctl file %p  cmd %u  arg %lu&quot;
comma
id|filep
comma
id|command
comma
id|arg
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|command
)paren
(brace
r_case
id|EXT2_IOC_GETFLAGS
suffix:colon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;get flags not implemented yet&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|EXT2_IOC_SETFLAGS
suffix:colon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;set flags not implemented yet&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_default
suffix:colon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;unsupported ioctl&quot;
)paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_CIFS_POSIX */
r_return
id|rc
suffix:semicolon
)brace
eof
