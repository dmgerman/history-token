multiline_comment|/*&n; * sysfs.h - definitions for the device driver filesystem&n; *&n; * Copyright (c) 2001,2002 Patrick Mochel&n; *&n; * Please see Documentation/filesystems/sysfs.txt for more information.&n; */
macro_line|#ifndef _SYSFS_H_
DECL|macro|_SYSFS_H_
mdefine_line|#define _SYSFS_H_
r_struct
id|kobject
suffix:semicolon
DECL|struct|attribute
r_struct
id|attribute
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sysfs_ops
r_struct
id|sysfs_ops
(brace
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|kobject
op_star
comma
r_struct
id|attribute
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|kobject
op_star
comma
r_struct
id|attribute
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|sysfs_create_dir
c_func
(paren
r_struct
id|kobject
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysfs_remove_dir
c_func
(paren
r_struct
id|kobject
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysfs_create_file
c_func
(paren
r_struct
id|kobject
op_star
comma
r_struct
id|attribute
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysfs_remove_file
c_func
(paren
r_struct
id|kobject
op_star
comma
r_struct
id|attribute
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysfs_create_link
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|kobject
op_star
id|target
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|sysfs_remove_link
c_func
(paren
r_struct
id|kobject
op_star
comma
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif /* _SYSFS_H_ */
eof
