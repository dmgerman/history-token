macro_line|#ifndef __LINUX_UIO_H
DECL|macro|__LINUX_UIO_H
mdefine_line|#define __LINUX_UIO_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; *&t;Berkeley style UIO structures&t;-&t;Alan Cox 1994.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* A word of warning: Our uio structure will clash with the C library one (which is now obsolete). Remove the C&n;   library one from sys/uio.h if you have a very old library set */
DECL|struct|iovec
r_struct
id|iovec
(brace
DECL|member|iov_base
r_void
op_star
id|iov_base
suffix:semicolon
multiline_comment|/* BSD uses caddr_t (1003.1g requires void *) */
DECL|member|iov_len
id|__kernel_size_t
id|iov_len
suffix:semicolon
multiline_comment|/* Must be size_t (1003.1g) */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;UIO_MAXIOV shall be at least 16 1003.1g (5.4.1.1)&n; */
DECL|macro|UIO_FASTIOV
mdefine_line|#define UIO_FASTIOV&t;8
DECL|macro|UIO_MAXIOV
mdefine_line|#define UIO_MAXIOV&t;1024
macro_line|#if 0
mdefine_line|#define UIO_MAXIOV&t;16&t;/* Maximum iovec&squot;s in one operation &n;&t;&t;&t;&t;   16 matches BSD */
multiline_comment|/* Beg pardon: BSD has 1024 --ANK */
macro_line|#endif
macro_line|#endif
eof
