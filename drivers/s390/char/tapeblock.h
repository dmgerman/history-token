multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tapeblock.h&n; *    character device frontend for tape device driver&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; *&n; ****************************************************************************&n; */
macro_line|#ifndef TAPEBLOCK_H
DECL|macro|TAPEBLOCK_H
mdefine_line|#define TAPEBLOCK_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|TAPEBLOCK_READAHEAD
mdefine_line|#define TAPEBLOCK_READAHEAD 30
DECL|macro|TAPEBLOCK_MAJOR
mdefine_line|#define TAPEBLOCK_MAJOR 0
DECL|macro|TAPEBLOCK_DEVFSMODE
mdefine_line|#define TAPEBLOCK_DEVFSMODE 0060644 
singleline_comment|// blkdev, rwx for user, rw for group&amp;others
r_int
id|tapeblock_open
c_func
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
id|tapeblock_release
c_func
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
r_void
id|tapeblock_setup
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tapeblock_schedule_exec_io
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_int
id|tapeblock_mediumdetect
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|devfs_handle_t
id|tapeblock_mkdevfstree
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tapeblock_rmdevfstree
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
macro_line|#endif
r_int
id|tapeblock_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|tapeblock_uninit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
