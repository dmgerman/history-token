multiline_comment|/*&n;  File: linux/xattr.h&n;&n;  Extended attributes handling.&n;&n;  Copyright (C) 2001 by Andreas Gruenbacher &lt;a.gruenbacher@computer.org&gt;&n;  Copyright (C) 2001 SGI - Silicon Graphics, Inc &lt;linux-xfs@oss.sgi.com&gt;&n;*/
macro_line|#ifndef _LINUX_XATTR_H
DECL|macro|_LINUX_XATTR_H
mdefine_line|#define _LINUX_XATTR_H
DECL|macro|XATTR_CREATE
mdefine_line|#define XATTR_CREATE&t;0x1&t;/* set value, fail if attr already exists */
DECL|macro|XATTR_REPLACE
mdefine_line|#define XATTR_REPLACE&t;0x2&t;/* set value, fail if attr does not exist */
macro_line|#endif&t;/* _LINUX_XATTR_H */
eof
