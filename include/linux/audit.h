multiline_comment|/* audit.h -- Auditing support -*- linux-c -*-&n; *&n; * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.&n; * All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Written by Rickard E. (Rik) Faith &lt;faith@redhat.com&gt;&n; *&n; */
macro_line|#ifndef _LINUX_AUDIT_H_
DECL|macro|_LINUX_AUDIT_H_
mdefine_line|#define _LINUX_AUDIT_H_
multiline_comment|/* Request and reply types */
DECL|macro|AUDIT_GET
mdefine_line|#define AUDIT_GET      1000&t;/* Get status */
DECL|macro|AUDIT_SET
mdefine_line|#define AUDIT_SET      1001&t;/* Set status (enable/disable/auditd) */
DECL|macro|AUDIT_LIST
mdefine_line|#define AUDIT_LIST     1002&t;/* List filtering rules */
DECL|macro|AUDIT_ADD
mdefine_line|#define AUDIT_ADD      1003&t;/* Add filtering rule */
DECL|macro|AUDIT_DEL
mdefine_line|#define AUDIT_DEL      1004&t;/* Delete filtering rule */
DECL|macro|AUDIT_USER
mdefine_line|#define AUDIT_USER     1005&t;/* Send a message from user-space */
DECL|macro|AUDIT_LOGIN
mdefine_line|#define AUDIT_LOGIN    1006     /* Define the login id and informaiton */
DECL|macro|AUDIT_KERNEL
mdefine_line|#define AUDIT_KERNEL   2000&t;/* Asynchronous audit record. NOT A REQUEST. */
multiline_comment|/* Rule flags */
DECL|macro|AUDIT_PER_TASK
mdefine_line|#define AUDIT_PER_TASK 0x01&t;/* Apply rule at task creation (not syscall) */
DECL|macro|AUDIT_AT_ENTRY
mdefine_line|#define AUDIT_AT_ENTRY 0x02&t;/* Apply rule at syscall entry */
DECL|macro|AUDIT_AT_EXIT
mdefine_line|#define AUDIT_AT_EXIT  0x04&t;/* Apply rule at syscall exit */
DECL|macro|AUDIT_PREPEND
mdefine_line|#define AUDIT_PREPEND  0x10&t;/* Prepend to front of list */
multiline_comment|/* Rule actions */
DECL|macro|AUDIT_NEVER
mdefine_line|#define AUDIT_NEVER    0&t;/* Do not build context if rule matches */
DECL|macro|AUDIT_POSSIBLE
mdefine_line|#define AUDIT_POSSIBLE 1&t;/* Build context if rule matches  */
DECL|macro|AUDIT_ALWAYS
mdefine_line|#define AUDIT_ALWAYS   2&t;/* Generate audit record if rule matches */
multiline_comment|/* Rule structure sizes -- if these change, different AUDIT_ADD and&n; * AUDIT_LIST commands must be implemented. */
DECL|macro|AUDIT_MAX_FIELDS
mdefine_line|#define AUDIT_MAX_FIELDS   64
DECL|macro|AUDIT_BITMASK_SIZE
mdefine_line|#define AUDIT_BITMASK_SIZE 64
DECL|macro|AUDIT_WORD
mdefine_line|#define AUDIT_WORD(nr) ((__u32)((nr)/32))
DECL|macro|AUDIT_BIT
mdefine_line|#define AUDIT_BIT(nr)  (1 &lt;&lt; ((nr) - AUDIT_WORD(nr)*32))
multiline_comment|/* Rule fields */
multiline_comment|/* These are useful when checking the&n;&t;&t;&t;&t; * task structure at task creation time&n;&t;&t;&t;&t; * (AUDIT_PER_TASK).  */
DECL|macro|AUDIT_PID
mdefine_line|#define AUDIT_PID&t;0
DECL|macro|AUDIT_UID
mdefine_line|#define AUDIT_UID&t;1
DECL|macro|AUDIT_EUID
mdefine_line|#define AUDIT_EUID&t;2
DECL|macro|AUDIT_SUID
mdefine_line|#define AUDIT_SUID&t;3
DECL|macro|AUDIT_FSUID
mdefine_line|#define AUDIT_FSUID&t;4
DECL|macro|AUDIT_GID
mdefine_line|#define AUDIT_GID&t;5
DECL|macro|AUDIT_EGID
mdefine_line|#define AUDIT_EGID&t;6
DECL|macro|AUDIT_SGID
mdefine_line|#define AUDIT_SGID&t;7
DECL|macro|AUDIT_FSGID
mdefine_line|#define AUDIT_FSGID&t;8
DECL|macro|AUDIT_LOGINUID
mdefine_line|#define AUDIT_LOGINUID&t;9
DECL|macro|AUDIT_PERS
mdefine_line|#define AUDIT_PERS&t;10
multiline_comment|/* These are ONLY useful when checking&n;&t;&t;&t;&t; * at syscall exit time (AUDIT_AT_EXIT). */
DECL|macro|AUDIT_DEVMAJOR
mdefine_line|#define AUDIT_DEVMAJOR&t;100
DECL|macro|AUDIT_DEVMINOR
mdefine_line|#define AUDIT_DEVMINOR&t;101
DECL|macro|AUDIT_INODE
mdefine_line|#define AUDIT_INODE&t;102
DECL|macro|AUDIT_EXIT
mdefine_line|#define AUDIT_EXIT&t;103
DECL|macro|AUDIT_SUCCESS
mdefine_line|#define AUDIT_SUCCESS   104&t;/* exit &gt;= 0; value ignored */
DECL|macro|AUDIT_ARG0
mdefine_line|#define AUDIT_ARG0      200
DECL|macro|AUDIT_ARG1
mdefine_line|#define AUDIT_ARG1      (AUDIT_ARG0+1)
DECL|macro|AUDIT_ARG2
mdefine_line|#define AUDIT_ARG2      (AUDIT_ARG0+2)
DECL|macro|AUDIT_ARG3
mdefine_line|#define AUDIT_ARG3      (AUDIT_ARG0+3)
DECL|macro|AUDIT_NEGATE
mdefine_line|#define AUDIT_NEGATE    0x80000000
multiline_comment|/* Status symbols */
multiline_comment|/* Mask values */
DECL|macro|AUDIT_STATUS_ENABLED
mdefine_line|#define AUDIT_STATUS_ENABLED&t;&t;0x0001
DECL|macro|AUDIT_STATUS_FAILURE
mdefine_line|#define AUDIT_STATUS_FAILURE&t;&t;0x0002
DECL|macro|AUDIT_STATUS_PID
mdefine_line|#define AUDIT_STATUS_PID&t;&t;0x0004
DECL|macro|AUDIT_STATUS_RATE_LIMIT
mdefine_line|#define AUDIT_STATUS_RATE_LIMIT&t;&t;0x0008
DECL|macro|AUDIT_STATUS_BACKLOG_LIMIT
mdefine_line|#define AUDIT_STATUS_BACKLOG_LIMIT&t;0x0010
multiline_comment|/* Failure-to-log actions */
DECL|macro|AUDIT_FAIL_SILENT
mdefine_line|#define AUDIT_FAIL_SILENT&t;0
DECL|macro|AUDIT_FAIL_PRINTK
mdefine_line|#define AUDIT_FAIL_PRINTK&t;1
DECL|macro|AUDIT_FAIL_PANIC
mdefine_line|#define AUDIT_FAIL_PANIC&t;2
macro_line|#ifndef __KERNEL__
DECL|struct|audit_message
r_struct
id|audit_message
(brace
DECL|member|nlh
r_struct
id|nlmsghdr
id|nlh
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
l_int|1200
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|audit_status
r_struct
id|audit_status
(brace
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
multiline_comment|/* Bit mask for valid entries */
DECL|member|enabled
id|__u32
id|enabled
suffix:semicolon
multiline_comment|/* 1 = enabled, 0 = disbaled */
DECL|member|failure
id|__u32
id|failure
suffix:semicolon
multiline_comment|/* Failure-to-log action */
DECL|member|pid
id|__u32
id|pid
suffix:semicolon
multiline_comment|/* pid of auditd process */
DECL|member|rate_limit
id|__u32
id|rate_limit
suffix:semicolon
multiline_comment|/* messages rate limit (per second) */
DECL|member|backlog_limit
id|__u32
id|backlog_limit
suffix:semicolon
multiline_comment|/* waiting messages limit */
DECL|member|lost
id|__u32
id|lost
suffix:semicolon
multiline_comment|/* messages lost */
DECL|member|backlog
id|__u32
id|backlog
suffix:semicolon
multiline_comment|/* messages waiting in queue */
)brace
suffix:semicolon
DECL|struct|audit_rule
r_struct
id|audit_rule
(brace
multiline_comment|/* for AUDIT_LIST, AUDIT_ADD, and AUDIT_DEL */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* AUDIT_PER_{TASK,CALL}, AUDIT_PREPEND */
DECL|member|action
id|__u32
id|action
suffix:semicolon
multiline_comment|/* AUDIT_NEVER, AUDIT_POSSIBLE, AUDIT_ALWAYS */
DECL|member|field_count
id|__u32
id|field_count
suffix:semicolon
DECL|member|mask
id|__u32
id|mask
(braket
id|AUDIT_BITMASK_SIZE
)braket
suffix:semicolon
DECL|member|fields
id|__u32
id|fields
(braket
id|AUDIT_MAX_FIELDS
)braket
suffix:semicolon
DECL|member|values
id|__u32
id|values
(braket
id|AUDIT_MAX_FIELDS
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_AUDIT
r_struct
id|audit_buffer
suffix:semicolon
r_struct
id|audit_context
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUDITSYSCALL
multiline_comment|/* These are defined in auditsc.c */
multiline_comment|/* Public API */
r_extern
r_int
id|audit_alloc
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|audit_free
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|audit_syscall_entry
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|major
comma
r_int
r_int
id|a0
comma
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_int
r_int
id|a3
)paren
suffix:semicolon
r_extern
r_void
id|audit_syscall_exit
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|return_code
)paren
suffix:semicolon
r_extern
r_void
id|audit_getname
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|audit_putname
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|audit_inode
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|ino
comma
id|dev_t
id|rdev
)paren
suffix:semicolon
multiline_comment|/* Private API (for audit.c only) */
r_extern
r_int
id|audit_receive_filter
c_func
(paren
r_int
id|type
comma
r_int
id|pid
comma
r_int
id|uid
comma
r_int
id|seq
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|audit_get_stamp
c_func
(paren
r_struct
id|audit_context
op_star
id|ctx
comma
r_struct
id|timespec
op_star
id|t
comma
r_int
op_star
id|serial
)paren
suffix:semicolon
r_extern
r_int
id|audit_set_loginuid
c_func
(paren
r_struct
id|audit_context
op_star
id|ctx
comma
id|uid_t
id|loginuid
)paren
suffix:semicolon
r_extern
id|uid_t
id|audit_get_loginuid
c_func
(paren
r_struct
id|audit_context
op_star
id|ctx
)paren
suffix:semicolon
macro_line|#else
DECL|macro|audit_alloc
mdefine_line|#define audit_alloc(t) ({ 0; })
DECL|macro|audit_free
mdefine_line|#define audit_free(t) do { ; } while (0)
DECL|macro|audit_syscall_entry
mdefine_line|#define audit_syscall_entry(t,a,b,c,d,e) do { ; } while (0)
DECL|macro|audit_syscall_exit
mdefine_line|#define audit_syscall_exit(t,r) do { ; } while (0)
DECL|macro|audit_getname
mdefine_line|#define audit_getname(n) do { ; } while (0)
DECL|macro|audit_putname
mdefine_line|#define audit_putname(n) do { ; } while (0)
DECL|macro|audit_inode
mdefine_line|#define audit_inode(n,i,d) do { ; } while (0)
DECL|macro|audit_get_loginuid
mdefine_line|#define audit_get_loginuid(c) ({ -1; })
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIT
multiline_comment|/* These are defined in audit.c */
multiline_comment|/* Public API */
r_extern
r_void
id|audit_log
c_func
(paren
r_struct
id|audit_context
op_star
id|ctx
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|audit_buffer
op_star
id|audit_log_start
c_func
(paren
r_struct
id|audit_context
op_star
id|ctx
)paren
suffix:semicolon
r_extern
r_void
id|audit_log_format
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|audit_log_end
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
)paren
suffix:semicolon
r_extern
r_void
id|audit_log_end_fast
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
)paren
suffix:semicolon
r_extern
r_void
id|audit_log_end_irq
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
)paren
suffix:semicolon
r_extern
r_void
id|audit_log_d_path
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
comma
r_const
r_char
op_star
id|prefix
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|vfsmount
op_star
id|vfsmnt
)paren
suffix:semicolon
r_extern
r_int
id|audit_set_rate_limit
c_func
(paren
r_int
id|limit
)paren
suffix:semicolon
r_extern
r_int
id|audit_set_backlog_limit
c_func
(paren
r_int
id|limit
)paren
suffix:semicolon
r_extern
r_int
id|audit_set_enabled
c_func
(paren
r_int
id|state
)paren
suffix:semicolon
r_extern
r_int
id|audit_set_failure
c_func
(paren
r_int
id|state
)paren
suffix:semicolon
multiline_comment|/* Private API (for auditsc.c only) */
r_extern
r_void
id|audit_send_reply
c_func
(paren
r_int
id|pid
comma
r_int
id|seq
comma
r_int
id|type
comma
r_int
id|done
comma
r_int
id|multi
comma
r_void
op_star
id|payload
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|audit_log_lost
c_func
(paren
r_const
r_char
op_star
id|message
)paren
suffix:semicolon
macro_line|#else
DECL|macro|audit_log
mdefine_line|#define audit_log(t,f,...) do { ; } while (0)
DECL|macro|audit_log_start
mdefine_line|#define audit_log_start(t) ({ NULL; })
DECL|macro|audit_log_vformat
mdefine_line|#define audit_log_vformat(b,f,a) do { ; } while (0)
DECL|macro|audit_log_format
mdefine_line|#define audit_log_format(b,f,...) do { ; } while (0)
DECL|macro|audit_log_end
mdefine_line|#define audit_log_end(b) do { ; } while (0)
DECL|macro|audit_log_end_fast
mdefine_line|#define audit_log_end_fast(b) do { ; } while (0)
DECL|macro|audit_log_end_irq
mdefine_line|#define audit_log_end_irq(b) do { ; } while (0)
DECL|macro|audit_log_d_path
mdefine_line|#define audit_log_d_path(b,p,d,v) do { ; } while (0)
DECL|macro|audit_set_rate_limit
mdefine_line|#define audit_set_rate_limit(l) do { ; } while (0)
DECL|macro|audit_set_backlog_limit
mdefine_line|#define audit_set_backlog_limit(l) do { ; } while (0)
DECL|macro|audit_set_enabled
mdefine_line|#define audit_set_enabled(s) do { ; } while (0)
DECL|macro|audit_set_failure
mdefine_line|#define audit_set_failure(s) do { ; } while (0)
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
