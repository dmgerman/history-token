multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tapechar.h&n; *    character device frontend for tape device driver&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; *&n; ****************************************************************************&n; */
macro_line|#ifndef TAPECHAR_H
DECL|macro|TAPECHAR_H
mdefine_line|#define TAPECHAR_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|TAPECHAR_DEVFSMODE
mdefine_line|#define TAPECHAR_DEVFSMODE 0020644 
singleline_comment|// chardev, rwx for user, rw for group&amp;others
DECL|macro|TAPECHAR_MAJOR
mdefine_line|#define TAPECHAR_MAJOR 0  /* get dynamic major since no major officialy defined for tape */
DECL|macro|TAPECHAR_NOREW_MINOR
mdefine_line|#define TAPECHAR_NOREW_MINOR(x) x    /* Minor for nonrewinding device */
DECL|macro|TAPECHAR_REW_MINOR
mdefine_line|#define TAPECHAR_REW_MINOR(x)  (x+1) /* Minor for rewinding device */
multiline_comment|/*&n; * Prototypes&n; */
id|ssize_t
id|tapechar_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
id|ssize_t
id|tapechar_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_int
id|tapechar_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|tapechar_open
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|tapechar_release
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|devfs_handle_t
id|tapechar_mkdevfstree
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tapechar_rmdevfstree
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
macro_line|#endif
r_void
id|tapechar_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|tapechar_uninit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* TAPECHAR_H */
eof
