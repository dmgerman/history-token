multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: ioctl.c,v 1.7 2003/10/04 08:33:06 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
DECL|function|jffs2_ioctl
r_int
id|jffs2_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
multiline_comment|/* Later, this will provide for lsattr.jffs2 and chattr.jffs2, which&n;&t;   will include compression support etc. */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
