multiline_comment|/**&n; * @file buffer_sync.h&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#ifndef OPROFILE_BUFFER_SYNC_H
DECL|macro|OPROFILE_BUFFER_SYNC_H
mdefine_line|#define OPROFILE_BUFFER_SYNC_H
multiline_comment|/* add the necessary profiling hooks */
r_int
id|sync_start
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* remove the hooks */
r_void
id|sync_stop
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* sync the given CPU&squot;s buffer */
r_void
id|sync_buffer
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif /* OPROFILE_BUFFER_SYNC_H */
eof
