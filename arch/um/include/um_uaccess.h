multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __ARCH_UM_UACCESS_H
DECL|macro|__ARCH_UM_UACCESS_H
mdefine_line|#define __ARCH_UM_UACCESS_H
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#ifdef CONFIG_MODE_TT
macro_line|#include &quot;uaccess-tt.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_SKAS
macro_line|#include &quot;uaccess-skas.h&quot;
macro_line|#endif
DECL|macro|access_ok
mdefine_line|#define access_ok(type, addr, size) &bslash;&n;&t;CHOOSE_MODE_PROC(access_ok_tt, access_ok_skas, type, addr, size)
multiline_comment|/* this function will go away soon - use access_ok() instead */
DECL|function|verify_area
r_static
r_inline
r_int
id|__deprecated
id|verify_area
c_func
(paren
r_int
id|type
comma
r_const
r_void
id|__user
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
id|CHOOSE_MODE_PROC
c_func
(paren
id|verify_area_tt
comma
id|verify_area_skas
comma
id|type
comma
id|addr
comma
id|size
)paren
)paren
suffix:semicolon
)brace
DECL|function|copy_from_user
r_static
r_inline
r_int
id|copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
id|__user
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|copy_from_user_tt
comma
id|copy_from_user_skas
comma
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|copy_to_user
r_static
r_inline
r_int
id|copy_to_user
c_func
(paren
r_void
id|__user
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|copy_to_user_tt
comma
id|copy_to_user_skas
comma
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * strncpy_from_user: - Copy a NUL terminated string from userspace.&n; * @dst:   Destination address, in kernel space.  This buffer must be at&n; *         least @count bytes long.&n; * @src:   Source address, in user space.&n; * @count: Maximum number of bytes to copy, including the trailing NUL.&n; *&n; * Copies a NUL-terminated string from userspace to kernel space.&n; *&n; * On success, returns the length of the string (not including the trailing&n; * NUL).&n; *&n; * If access to userspace fails, returns -EFAULT (some data may have been&n; * copied).&n; *&n; * If @count is smaller than the length of the string, copies @count bytes&n; * and returns @count.&n; */
DECL|function|strncpy_from_user
r_static
r_inline
r_int
id|strncpy_from_user
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
id|__user
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|strncpy_from_user_tt
comma
id|strncpy_from_user_skas
comma
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * __clear_user: - Zero a block of memory in user space, with less checking.&n; * @to:   Destination address, in user space.&n; * @n:    Number of bytes to zero.&n; *&n; * Zero a block of memory in user space.  Caller must check&n; * the specified block with access_ok() before calling this function.&n; *&n; * Returns number of bytes that could not be cleared.&n; * On success, this will be zero.&n; */
DECL|function|__clear_user
r_static
r_inline
r_int
id|__clear_user
c_func
(paren
r_void
op_star
id|mem
comma
r_int
id|len
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|__clear_user_tt
comma
id|__clear_user_skas
comma
id|mem
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_user: - Zero a block of memory in user space.&n; * @to:   Destination address, in user space.&n; * @n:    Number of bytes to zero.&n; *&n; * Zero a block of memory in user space.&n; *&n; * Returns number of bytes that could not be cleared.&n; * On success, this will be zero.&n; */
DECL|function|clear_user
r_static
r_inline
r_int
id|clear_user
c_func
(paren
r_void
id|__user
op_star
id|mem
comma
r_int
id|len
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|clear_user_tt
comma
id|clear_user_skas
comma
id|mem
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * strlen_user: - Get the size of a string in user space.&n; * @str: The string to measure.&n; * @n:   The maximum valid length&n; *&n; * Get the size of a NUL-terminated string in user space.&n; *&n; * Returns the size of the string INCLUDING the terminating NUL.&n; * On exception, returns 0.&n; * If the string is too long, returns a value greater than @n.&n; */
DECL|function|strnlen_user
r_static
r_inline
r_int
id|strnlen_user
c_func
(paren
r_const
r_void
id|__user
op_star
id|str
comma
r_int
id|len
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|strnlen_user_tt
comma
id|strnlen_user_skas
comma
id|str
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
