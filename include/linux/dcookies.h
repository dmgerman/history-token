multiline_comment|/*&n; * dcookies.h&n; *&n; * Persistent cookie-path mappings&n; *&n; * Copyright 2002 John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#ifndef DCOOKIES_H
DECL|macro|DCOOKIES_H
mdefine_line|#define DCOOKIES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PROFILING
macro_line|#include &lt;linux/types.h&gt;
r_struct
id|dcookie_user
suffix:semicolon
multiline_comment|/**&n; * dcookie_register - register a user of dcookies&n; *&n; * Register as a dcookie user. Returns %NULL on failure.&n; */
r_struct
id|dcookie_user
op_star
id|dcookie_register
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; * dcookie_unregister - unregister a user of dcookies&n; *&n; * Unregister as a dcookie user. This may invalidate&n; * any dcookie values returned from get_dcookie().&n; */
r_void
id|dcookie_unregister
c_func
(paren
r_struct
id|dcookie_user
op_star
id|user
)paren
suffix:semicolon
multiline_comment|/**&n; * get_dcookie - acquire a dcookie&n; *&n; * Convert the given dentry/vfsmount pair into&n; * a cookie value.&n; *&n; * Returns -EINVAL if no living task has registered as a&n; * dcookie user.&n; *&n; * Returns 0 on success, with *cookie filled in&n; */
r_int
id|get_dcookie
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|vfsmount
op_star
id|vfsmnt
comma
r_int
r_int
op_star
id|cookie
)paren
suffix:semicolon
macro_line|#else
DECL|function|dcookie_register
r_struct
id|dcookie_user
op_star
id|dcookie_register
c_func
(paren
r_void
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dcookie_unregister
r_void
id|dcookie_unregister
c_func
(paren
r_struct
id|dcookie_user
op_star
id|user
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|get_dcookie
r_static
r_inline
r_int
id|get_dcookie
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|vfsmount
op_star
id|vfsmnt
comma
r_int
r_int
op_star
id|cookie
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROFILING */
macro_line|#endif /* DCOOKIES_H */
eof
