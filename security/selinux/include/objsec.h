multiline_comment|/*&n; *  NSA Security-Enhanced Linux (SELinux) security module&n; *&n; *  This file contains the SELinux security data structures for kernel objects.&n; *&n; *  Author(s):  Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; *              Chris Vance, &lt;cvance@nai.com&gt;&n; *              Wayne Salamon, &lt;wsalamon@nai.com&gt;&n; *              James Morris &lt;jmorris@redhat.com&gt;&n; *&n; *  Copyright (C) 2001,2002 Networks Associates Technology, Inc.&n; *  Copyright (C) 2003 Red Hat, Inc., James Morris &lt;jmorris@redhat.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License version 2,&n; *      as published by the Free Software Foundation.&n; */
macro_line|#ifndef _SELINUX_OBJSEC_H_
DECL|macro|_SELINUX_OBJSEC_H_
mdefine_line|#define _SELINUX_OBJSEC_H_
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &quot;flask.h&quot;
macro_line|#include &quot;avc.h&quot;
DECL|struct|task_security_struct
r_struct
id|task_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
multiline_comment|/* back pointer to task object */
DECL|member|osid
id|u32
id|osid
suffix:semicolon
multiline_comment|/* SID prior to last execve */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* current SID */
DECL|member|exec_sid
id|u32
id|exec_sid
suffix:semicolon
multiline_comment|/* exec SID */
DECL|member|create_sid
id|u32
id|create_sid
suffix:semicolon
multiline_comment|/* fscreate SID */
DECL|member|avcr
r_struct
id|avc_entry_ref
id|avcr
suffix:semicolon
multiline_comment|/* reference to process permissions */
DECL|member|ptrace_sid
id|u32
id|ptrace_sid
suffix:semicolon
multiline_comment|/* SID of ptrace parent */
)brace
suffix:semicolon
DECL|struct|inode_security_struct
r_struct
id|inode_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* back pointer to inode object */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of inode_security_struct */
DECL|member|task_sid
id|u32
id|task_sid
suffix:semicolon
multiline_comment|/* SID of creating task */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* SID of this object */
DECL|member|sclass
id|u16
id|sclass
suffix:semicolon
multiline_comment|/* security class of this object */
DECL|member|avcr
r_struct
id|avc_entry_ref
id|avcr
suffix:semicolon
multiline_comment|/* reference to object permissions */
DECL|member|initialized
r_int
r_char
id|initialized
suffix:semicolon
multiline_comment|/* initialization flag */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|inherit
r_int
r_char
id|inherit
suffix:semicolon
multiline_comment|/* inherit SID from parent entry */
)brace
suffix:semicolon
DECL|struct|file_security_struct
r_struct
id|file_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
multiline_comment|/* back pointer to file object */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* SID of open file description */
DECL|member|fown_sid
id|u32
id|fown_sid
suffix:semicolon
multiline_comment|/* SID of file owner (for SIGIO) */
DECL|member|avcr
r_struct
id|avc_entry_ref
id|avcr
suffix:semicolon
multiline_comment|/* reference to fd permissions */
DECL|member|inode_avcr
r_struct
id|avc_entry_ref
id|inode_avcr
suffix:semicolon
multiline_comment|/* reference to object permissions */
)brace
suffix:semicolon
DECL|struct|superblock_security_struct
r_struct
id|superblock_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* back pointer to sb object */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of superblock_security_struct */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* SID of file system */
DECL|member|def_sid
id|u32
id|def_sid
suffix:semicolon
multiline_comment|/* default SID for labeling */
DECL|member|behavior
r_int
r_int
id|behavior
suffix:semicolon
multiline_comment|/* labeling behavior */
DECL|member|initialized
r_int
r_char
id|initialized
suffix:semicolon
multiline_comment|/* initialization flag */
DECL|member|proc
r_int
r_char
id|proc
suffix:semicolon
multiline_comment|/* proc fs */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|isec_head
r_struct
id|list_head
id|isec_head
suffix:semicolon
DECL|member|isec_lock
id|spinlock_t
id|isec_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|msg_security_struct
r_struct
id|msg_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|msg
r_struct
id|msg_msg
op_star
id|msg
suffix:semicolon
multiline_comment|/* back pointer */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* SID of message */
DECL|member|avcr
r_struct
id|avc_entry_ref
id|avcr
suffix:semicolon
multiline_comment|/* reference to permissions */
)brace
suffix:semicolon
DECL|struct|ipc_security_struct
r_struct
id|ipc_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|ipc_perm
r_struct
id|kern_ipc_perm
op_star
id|ipc_perm
suffix:semicolon
multiline_comment|/* back pointer */
DECL|member|sclass
id|u16
id|sclass
suffix:semicolon
multiline_comment|/* security class of this object */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* SID of IPC resource */
DECL|member|avcr
r_struct
id|avc_entry_ref
id|avcr
suffix:semicolon
multiline_comment|/* reference to permissions */
)brace
suffix:semicolon
DECL|struct|bprm_security_struct
r_struct
id|bprm_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|bprm
r_struct
id|linux_binprm
op_star
id|bprm
suffix:semicolon
multiline_comment|/* back pointer to bprm object */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* SID for transformed process */
DECL|member|set
r_int
r_char
id|set
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|netif_security_struct
r_struct
id|netif_security_struct
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* back pointer */
DECL|member|if_sid
id|u32
id|if_sid
suffix:semicolon
multiline_comment|/* SID for this interface */
DECL|member|msg_sid
id|u32
id|msg_sid
suffix:semicolon
multiline_comment|/* default SID for messages received on this interface */
)brace
suffix:semicolon
DECL|struct|sk_security_struct
r_struct
id|sk_security_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this module */
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* back pointer to sk object */
DECL|member|peer_sid
id|u32
id|peer_sid
suffix:semicolon
multiline_comment|/* SID of peer */
)brace
suffix:semicolon
r_extern
r_int
id|inode_security_set_sid
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
id|sid
)paren
suffix:semicolon
macro_line|#endif /* _SELINUX_OBJSEC_H_ */
eof
