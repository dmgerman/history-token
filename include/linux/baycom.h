multiline_comment|/*&n; * The Linux BAYCOM driver for the Baycom serial 1200 baud modem&n; * and the parallel 9600 baud modem&n; * (C) 1997-1998 by Thomas Sailer, HB9JNX/AE4WA&n; */
macro_line|#ifndef _BAYCOM_H
DECL|macro|_BAYCOM_H
mdefine_line|#define _BAYCOM_H
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * structs for the IOCTL commands&n; */
DECL|struct|baycom_debug_data
r_struct
id|baycom_debug_data
(brace
DECL|member|debug1
r_int
r_int
id|debug1
suffix:semicolon
DECL|member|debug2
r_int
r_int
id|debug2
suffix:semicolon
DECL|member|debug3
r_int
id|debug3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|baycom_ioctl
r_struct
id|baycom_ioctl
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
r_union
(brace
DECL|member|dbg
r_struct
id|baycom_debug_data
id|dbg
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * ioctl values change for baycom&n; */
DECL|macro|BAYCOMCTL_GETDEBUG
mdefine_line|#define BAYCOMCTL_GETDEBUG       0x92
multiline_comment|/* -------------------------------------------------------------------- */
macro_line|#endif /* _BAYCOM_H */
multiline_comment|/* --------------------------------------------------------------------- */
eof
