macro_line|#ifndef S390_PROC_H
DECL|macro|S390_PROC_H
mdefine_line|#define S390_PROC_H
r_extern
r_int
id|cio_procfs_device_purge
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cio_procfs_device_create
(paren
r_int
id|devno
)paren
suffix:semicolon
r_extern
r_int
id|cio_procfs_device_remove
(paren
r_int
id|devno
)paren
suffix:semicolon
singleline_comment|//FIXME: shouldn`t this be &squot;struct{unsigned int len; char data[0]};&squot; ?
multiline_comment|/*&n; * Display info on subchannels in /proc/subchannels.&n; * Adapted from procfs stuff in dasd.c by Cornelia Huck, 02/28/01.&n; */
r_typedef
r_struct
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|typedef|tempinfo_t
)brace
id|tempinfo_t
suffix:semicolon
macro_line|#endif
eof
