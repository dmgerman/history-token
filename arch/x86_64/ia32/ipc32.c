macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;asm-i386/ipc.h&gt;
id|asmlinkage
r_int
DECL|function|sys32_ipc
id|sys32_ipc
c_func
(paren
id|u32
id|call
comma
r_int
id|first
comma
r_int
id|second
comma
r_int
id|third
comma
id|compat_uptr_t
id|ptr
comma
id|u32
id|fifth
)paren
(brace
r_int
id|version
suffix:semicolon
id|version
op_assign
id|call
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* hack for backward compatibility */
id|call
op_and_assign
l_int|0xffff
suffix:semicolon
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SEMOP
suffix:colon
multiline_comment|/* struct sembuf is the same on 32 and 64bit :)) */
r_return
id|sys_semtimedop
c_func
(paren
id|first
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
comma
id|second
comma
l_int|NULL
)paren
suffix:semicolon
r_case
id|SEMTIMEDOP
suffix:colon
r_return
id|compat_sys_semtimedop
c_func
(paren
id|first
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
comma
id|second
comma
id|compat_ptr
c_func
(paren
id|fifth
)paren
)paren
suffix:semicolon
r_case
id|SEMGET
suffix:colon
r_return
id|sys_semget
c_func
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SEMCTL
suffix:colon
r_return
id|compat_sys_semctl
c_func
(paren
id|first
comma
id|second
comma
id|third
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_case
id|MSGSND
suffix:colon
r_return
id|compat_sys_msgsnd
c_func
(paren
id|first
comma
id|second
comma
id|third
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_case
id|MSGRCV
suffix:colon
r_return
id|compat_sys_msgrcv
c_func
(paren
id|first
comma
id|second
comma
id|fifth
comma
id|third
comma
id|version
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_case
id|MSGGET
suffix:colon
r_return
id|sys_msgget
c_func
(paren
(paren
id|key_t
)paren
id|first
comma
id|second
)paren
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
r_return
id|compat_sys_msgctl
c_func
(paren
id|first
comma
id|second
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_case
id|SHMAT
suffix:colon
r_return
id|compat_sys_shmat
c_func
(paren
id|first
comma
id|second
comma
id|third
comma
id|version
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SHMDT
suffix:colon
r_return
id|sys_shmdt
c_func
(paren
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
r_case
id|SHMGET
suffix:colon
r_return
id|sys_shmget
c_func
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
r_return
id|compat_sys_shmctl
c_func
(paren
id|first
comma
id|second
comma
id|compat_ptr
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
