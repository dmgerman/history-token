multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __KERN_H__
DECL|macro|__KERN_H__
mdefine_line|#define __KERN_H__
multiline_comment|/* These are all user-mode things which are convenient to call directly&n; * from kernel code and for which writing a wrapper is too much of a pain.&n; * The regular include files can&squot;t be included because this file is included&n; * only into kernel code, and user-space includes conflict with kernel&n; * includes.&n; */
r_extern
r_int
id|errno
suffix:semicolon
r_extern
r_int
id|clone
c_func
(paren
r_int
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|sp
comma
r_int
id|flags
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|sleep
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_char
op_star
id|strerror
c_func
(paren
r_int
id|errnum
)paren
suffix:semicolon
r_extern
r_char
op_star
id|ptsname
c_func
(paren
r_int
id|__fd
)paren
suffix:semicolon
r_extern
r_int
id|munmap
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|sbrk
c_func
(paren
r_int
id|increment
)paren
suffix:semicolon
r_extern
r_void
op_star
id|malloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|perror
c_func
(paren
r_char
op_star
id|err
)paren
suffix:semicolon
r_extern
r_int
id|kill
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_int
id|getuid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pause
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|write
c_func
(paren
r_int
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
m_exit
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|close
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|read
c_func
(paren
r_int
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pipe
c_func
(paren
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sched_yield
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
