macro_line|#ifndef _LINUX_FCNTL_H
DECL|macro|_LINUX_FCNTL_H
mdefine_line|#define _LINUX_FCNTL_H
macro_line|#include &lt;asm/fcntl.h&gt;
DECL|macro|F_SETLEASE
mdefine_line|#define F_SETLEASE&t;(F_LINUX_SPECIFIC_BASE+0)
DECL|macro|F_GETLEASE
mdefine_line|#define F_GETLEASE&t;(F_LINUX_SPECIFIC_BASE+1)
multiline_comment|/*&n; * Request nofications on a directory.&n; * See below for events that may be notified.&n; */
DECL|macro|F_NOTIFY
mdefine_line|#define F_NOTIFY&t;(F_LINUX_SPECIFIC_BASE+2)
multiline_comment|/*&n; * Types of directory notifications that may be requested.&n; */
DECL|macro|DN_ACCESS
mdefine_line|#define DN_ACCESS&t;0x00000001&t;/* File accessed */
DECL|macro|DN_MODIFY
mdefine_line|#define DN_MODIFY&t;0x00000002&t;/* File modified */
DECL|macro|DN_CREATE
mdefine_line|#define DN_CREATE&t;0x00000004&t;/* File created */
DECL|macro|DN_DELETE
mdefine_line|#define DN_DELETE&t;0x00000008&t;/* File removed */
DECL|macro|DN_RENAME
mdefine_line|#define DN_RENAME&t;0x00000010&t;/* File renamed */
DECL|macro|DN_ATTRIB
mdefine_line|#define DN_ATTRIB&t;0x00000020&t;/* File changed attibutes */
DECL|macro|DN_MULTISHOT
mdefine_line|#define DN_MULTISHOT&t;0x80000000&t;/* Don&squot;t remove notifier */
macro_line|#endif
eof
