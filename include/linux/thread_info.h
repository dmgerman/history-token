multiline_comment|/* thread_info.h: common low-level thread information accessors&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds&n; */
macro_line|#ifndef _LINUX_THREAD_INFO_H
DECL|macro|_LINUX_THREAD_INFO_H
mdefine_line|#define _LINUX_THREAD_INFO_H
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * flag set/clear/test wrappers&n; * - pass TIF_xxxx constants to these functions&n; */
DECL|function|set_thread_flag
r_static
r_inline
r_void
id|set_thread_flag
c_func
(paren
r_int
id|flag
)paren
(brace
id|set_bit
c_func
(paren
id|flag
comma
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
)brace
DECL|function|clear_thread_flag
r_static
r_inline
r_void
id|clear_thread_flag
c_func
(paren
r_int
id|flag
)paren
(brace
id|clear_bit
c_func
(paren
id|flag
comma
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
)brace
DECL|function|test_and_set_thread_flag
r_static
r_inline
r_int
id|test_and_set_thread_flag
c_func
(paren
r_int
id|flag
)paren
(brace
r_return
id|test_and_set_bit
c_func
(paren
id|flag
comma
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
)brace
DECL|function|test_and_clear_thread_flag
r_static
r_inline
r_int
id|test_and_clear_thread_flag
c_func
(paren
r_int
id|flag
)paren
(brace
r_return
id|test_and_clear_bit
c_func
(paren
id|flag
comma
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
)brace
DECL|function|test_thread_flag
r_static
r_inline
r_int
id|test_thread_flag
c_func
(paren
r_int
id|flag
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|flag
comma
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
)brace
DECL|function|set_ti_thread_flag
r_static
r_inline
r_void
id|set_ti_thread_flag
c_func
(paren
r_struct
id|thread_info
op_star
id|ti
comma
r_int
id|flag
)paren
(brace
id|set_bit
c_func
(paren
id|flag
comma
op_amp
id|ti-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|clear_ti_thread_flag
r_static
r_inline
r_void
id|clear_ti_thread_flag
c_func
(paren
r_struct
id|thread_info
op_star
id|ti
comma
r_int
id|flag
)paren
(brace
id|clear_bit
c_func
(paren
id|flag
comma
op_amp
id|ti-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|test_and_set_ti_thread_flag
r_static
r_inline
r_int
id|test_and_set_ti_thread_flag
c_func
(paren
r_struct
id|thread_info
op_star
id|ti
comma
r_int
id|flag
)paren
(brace
r_return
id|test_and_set_bit
c_func
(paren
id|flag
comma
op_amp
id|ti-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|test_and_clear_ti_thread_flag
r_static
r_inline
r_int
id|test_and_clear_ti_thread_flag
c_func
(paren
r_struct
id|thread_info
op_star
id|ti
comma
r_int
id|flag
)paren
(brace
r_return
id|test_and_clear_bit
c_func
(paren
id|flag
comma
op_amp
id|ti-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|test_ti_thread_flag
r_static
r_inline
r_int
id|test_ti_thread_flag
c_func
(paren
r_struct
id|thread_info
op_star
id|ti
comma
r_int
id|flag
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|flag
comma
op_amp
id|ti-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|set_need_resched
r_static
r_inline
r_void
id|set_need_resched
c_func
(paren
r_void
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
)brace
DECL|function|clear_need_resched
r_static
r_inline
r_void
id|clear_need_resched
c_func
(paren
r_void
)paren
(brace
id|clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_THREAD_INFO_H */
eof
