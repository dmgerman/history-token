multiline_comment|/* Coda filesystem -- Linux Minicache&n; *&n; * Copyright (C) 1989 - 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon University encourages users of this software to&n; * contribute improvements to the Coda project. Contact Peter Braam&n; * &lt;coda@cs.cmu.edu&gt;&n; */
macro_line|#ifndef _CFSNC_HEADER_
DECL|macro|_CFSNC_HEADER_
mdefine_line|#define _CFSNC_HEADER_
multiline_comment|/* credential cache */
r_void
id|coda_cache_enter
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
r_void
id|coda_cache_clear_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|coda_cache_clear_all
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_int
id|coda_cache_check
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
multiline_comment|/* for downcalls and attributes and lookups */
r_void
id|coda_flag_inode_children
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
)paren
suffix:semicolon
macro_line|#endif /* _CFSNC_HEADER_ */
eof
