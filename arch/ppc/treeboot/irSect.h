multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: irSect.h&n; *    &n; *    Description:&n; *      Defines variables to hold the absolute starting address and size&n; *      of the Linux kernel &quot;image&quot; and the initial RAM disk &quot;initrd&quot;   &n; *      sections within the boot loader.&n; *      &n; */
macro_line|#ifndef __IRSECT_H__
DECL|macro|__IRSECT_H__
mdefine_line|#define __IRSECT_H__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_extern
r_int
r_int
id|imageSect_start
suffix:semicolon
r_extern
r_int
r_int
id|imageSect_size
suffix:semicolon
r_extern
r_int
r_int
id|initrdSect_start
suffix:semicolon
r_extern
r_int
r_int
id|initrdSect_size
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __IRSECT_H__ */
eof
