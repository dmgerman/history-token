multiline_comment|/*&n; * kref.c - library routines for handling generic reference counted objects&n; *&n; * Copyright (C) 2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (C) 2004 IBM Corp.&n; *&n; * based on kobject.h which was:&n; * Copyright (C) 2002-2003 Patrick Mochel &lt;mochel@osdl.org&gt;&n; * Copyright (C) 2002-2003 Open Source Development Labs&n; *&n; * This file is released under the GPLv2.&n; *&n; */
macro_line|#ifndef _KREF_H_
DECL|macro|_KREF_H_
mdefine_line|#define _KREF_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|kref
r_struct
id|kref
(brace
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
)brace
suffix:semicolon
r_void
id|kref_init
c_func
(paren
r_struct
id|kref
op_star
id|kref
)paren
suffix:semicolon
r_void
id|kref_get
c_func
(paren
r_struct
id|kref
op_star
id|kref
)paren
suffix:semicolon
r_void
id|kref_put
c_func
(paren
r_struct
id|kref
op_star
id|kref
comma
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|kref
op_star
id|kref
)paren
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _KREF_H_ */
eof
