multiline_comment|/**&n; * @file oprofile.h&n; *&n; * API for machine-specific interrupts to interface&n; * to oprofile.&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#ifndef OPROFILE_H
DECL|macro|OPROFILE_H
mdefine_line|#define OPROFILE_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_struct
id|super_block
suffix:semicolon
r_struct
id|dentry
suffix:semicolon
r_struct
id|file_operations
suffix:semicolon
multiline_comment|/* Operations structure to be filled in */
DECL|struct|oprofile_operations
r_struct
id|oprofile_operations
(brace
multiline_comment|/* create any necessary configuration files in the oprofile fs.&n;&t; * Optional. */
DECL|member|create_files
r_int
(paren
op_star
id|create_files
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
)paren
suffix:semicolon
multiline_comment|/* Do any necessary interrupt setup. Optional. */
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Do any necessary interrupt shutdown. Optional. */
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Start delivering interrupts. */
DECL|member|start
r_int
(paren
op_star
id|start
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Stop delivering interrupts. */
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* CPU identification string. */
DECL|member|cpu_type
r_char
op_star
id|cpu_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * One-time initialisation. *ops must be set to a filled-in&n; * operations structure.&n; * Return 0 on success.&n; */
r_int
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/**&n; * One-time exit/cleanup for the arch.&n; */
r_void
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; * Add a sample. This may be called from any context. Pass&n; * smp_processor_id() as cpu.&n; */
r_extern
r_void
id|oprofile_add_sample
c_func
(paren
r_int
r_int
id|eip
comma
r_int
r_int
id|is_kernel
comma
r_int
r_int
id|event
comma
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/**&n; * Create a file of the given name as a child of the given root, with&n; * the specified file operations.&n; */
r_int
id|oprofilefs_create_file
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
)paren
suffix:semicolon
multiline_comment|/** Create a file for read/write access to an unsigned long. */
r_int
id|oprofilefs_create_ulong
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
id|ulong
op_star
id|val
)paren
suffix:semicolon
multiline_comment|/** Create a file for read-only access to an unsigned long. */
r_int
id|oprofilefs_create_ro_ulong
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
id|ulong
op_star
id|val
)paren
suffix:semicolon
multiline_comment|/** Create a file for read-only access to an atomic_t. */
r_int
id|oprofilefs_create_ro_atomic
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
id|atomic_t
op_star
id|val
)paren
suffix:semicolon
multiline_comment|/** create a directory */
r_struct
id|dentry
op_star
id|oprofilefs_mkdir
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/**&n; * Write the given asciz string to the given user buffer @buf, updating *offset&n; * appropriately. Returns bytes written or -EFAULT.&n; */
id|ssize_t
id|oprofilefs_str_to_user
c_func
(paren
r_char
r_const
op_star
id|str
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
suffix:semicolon
multiline_comment|/**&n; * Convert an unsigned long value into ASCII and copy it to the user buffer @buf,&n; * updating *offset appropriately. Returns bytes written or -EFAULT.&n; */
id|ssize_t
id|oprofilefs_ulong_to_user
c_func
(paren
r_int
r_int
op_star
id|val
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
suffix:semicolon
multiline_comment|/**&n; * Read an ASCII string for a number from a userspace buffer and fill *val on success.&n; * Returns 0 on success, &lt; 0 on error.&n; */
r_int
id|oprofilefs_ulong_from_user
c_func
(paren
r_int
r_int
op_star
id|val
comma
r_char
r_const
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/** lock for read/write safety */
r_extern
id|spinlock_t
id|oprofilefs_lock
suffix:semicolon
macro_line|#endif /* OPROFILE_H */
eof
