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
macro_line|#ifdef __KERNEL__
macro_line|#if BITS_PER_LONG == 32
DECL|macro|IS_GETLK32
mdefine_line|#define IS_GETLK32(cmd)&t;&t;((cmd) == F_GETLK)
DECL|macro|IS_SETLK32
mdefine_line|#define IS_SETLK32(cmd)&t;&t;((cmd) == F_SETLK)
DECL|macro|IS_SETLKW32
mdefine_line|#define IS_SETLKW32(cmd)&t;((cmd) == F_SETLKW)
DECL|macro|IS_GETLK64
mdefine_line|#define IS_GETLK64(cmd)&t;&t;((cmd) == F_GETLK64)
DECL|macro|IS_SETLK64
mdefine_line|#define IS_SETLK64(cmd)&t;&t;((cmd) == F_SETLK64)
DECL|macro|IS_SETLKW64
mdefine_line|#define IS_SETLKW64(cmd)&t;((cmd) == F_SETLKW64)
macro_line|#else
DECL|macro|IS_GETLK32
mdefine_line|#define IS_GETLK32(cmd)&t;&t;(0)
DECL|macro|IS_SETLK32
mdefine_line|#define IS_SETLK32(cmd)&t;&t;(0)
DECL|macro|IS_SETLKW32
mdefine_line|#define IS_SETLKW32(cmd)&t;(0)
DECL|macro|IS_GETLK64
mdefine_line|#define IS_GETLK64(cmd)&t;&t;((cmd) == F_GETLK)
DECL|macro|IS_SETLK64
mdefine_line|#define IS_SETLK64(cmd)&t;&t;((cmd) == F_SETLK)
DECL|macro|IS_SETLKW64
mdefine_line|#define IS_SETLKW64(cmd)&t;((cmd) == F_SETLKW)
macro_line|#endif /* BITS_PER_LONG == 32 */
DECL|macro|IS_GETLK
mdefine_line|#define IS_GETLK(cmd)&t;(IS_GETLK32(cmd)  || IS_GETLK64(cmd))
DECL|macro|IS_SETLK
mdefine_line|#define IS_SETLK(cmd)&t;(IS_SETLK32(cmd)  || IS_SETLK64(cmd))
DECL|macro|IS_SETLKW
mdefine_line|#define IS_SETLKW(cmd)&t;(IS_SETLKW32(cmd) || IS_SETLKW64(cmd))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
