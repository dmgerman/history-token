macro_line|#ifndef _LINUX_PROFILE_H
DECL|macro|_LINUX_PROFILE_H
mdefine_line|#define _LINUX_PROFILE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
DECL|enum|profile_type
r_enum
id|profile_type
(brace
DECL|enumerator|EXIT_TASK
id|EXIT_TASK
comma
DECL|enumerator|EXIT_MMAP
id|EXIT_MMAP
comma
DECL|enumerator|EXEC_UNMAP
id|EXEC_UNMAP
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PROFILING
r_struct
id|notifier_block
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
multiline_comment|/* task is in do_exit() */
r_void
id|profile_exit_task
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
multiline_comment|/* change of vma mappings */
r_void
id|profile_exec_unmap
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/* exit of all vmas for a task */
r_void
id|profile_exit_mmap
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_int
id|profile_event_register
c_func
(paren
r_enum
id|profile_type
comma
r_struct
id|notifier_block
op_star
id|n
)paren
suffix:semicolon
r_int
id|profile_event_unregister
c_func
(paren
r_enum
id|profile_type
comma
r_struct
id|notifier_block
op_star
id|n
)paren
suffix:semicolon
macro_line|#else
DECL|function|profile_event_register
r_static
r_inline
r_int
id|profile_event_register
c_func
(paren
r_enum
id|profile_type
id|t
comma
r_struct
id|notifier_block
op_star
id|n
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|profile_event_unregister
r_static
r_inline
r_int
id|profile_event_unregister
c_func
(paren
r_enum
id|profile_type
id|t
comma
r_struct
id|notifier_block
op_star
id|n
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|macro|profile_exit_task
mdefine_line|#define profile_exit_task(a) do { } while (0)
DECL|macro|profile_exec_unmap
mdefine_line|#define profile_exec_unmap(a) do { } while (0)
DECL|macro|profile_exit_mmap
mdefine_line|#define profile_exit_mmap(a) do { } while (0)
macro_line|#endif /* CONFIG_PROFILING */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_PROFILE_H */
eof
