multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tapechar.h&n; *    character device frontend for tape device driver&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Corporation&n; *    Author(s): Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; *  UNDER CONSTRUCTION: Work in progress...:-)&n; ****************************************************************************&n; */
macro_line|#ifndef TAPEBLOCK_H
DECL|macro|TAPEBLOCK_H
mdefine_line|#define TAPEBLOCK_H
DECL|macro|PARTN_BITS
mdefine_line|#define PARTN_BITS 0
DECL|macro|TAPEBLOCK_READAHEAD
mdefine_line|#define TAPEBLOCK_READAHEAD 30
DECL|macro|TAPEBLOCK_MAJOR
mdefine_line|#define TAPEBLOCK_MAJOR 0
r_static
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
r_static
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
id|tape_info_t
op_star
id|tape
)paren
suffix:semicolon
r_void
id|schedule_tapeblock_exec_IO
(paren
id|tape_info_t
op_star
id|tape
)paren
suffix:semicolon
r_static
r_int
id|tapeblock_mediumdetect
c_func
(paren
id|tape_info_t
op_star
id|tape
)paren
suffix:semicolon
macro_line|#endif
eof
