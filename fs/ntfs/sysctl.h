multiline_comment|/*  sysctl.h - Header file for sysctl.c&n; *&n; *  Copyright (C) 1997 Martin von L&#xfffd;wis&n; *  Copyright (C) 1997 R&#xfffd;gis Duchesne&n; *&n; */
macro_line|#ifdef DEBUG
r_extern
r_int
id|ntdebug
suffix:semicolon
r_void
id|ntfs_sysctl
c_func
(paren
r_int
id|add
)paren
suffix:semicolon
DECL|macro|SYSCTL
mdefine_line|#define SYSCTL(x)&t;ntfs_sysctl(x)
macro_line|#else
DECL|macro|SYSCTL
mdefine_line|#define SYSCTL(x)
macro_line|#endif /* DEBUG */
eof
