macro_line|#ifndef _GDTH_PROC_H
DECL|macro|_GDTH_PROC_H
mdefine_line|#define _GDTH_PROC_H
multiline_comment|/* gdth_proc.h &n; * $Id: gdth_proc.h,v 1.13 2003/02/27 14:59:25 achim Exp $&n; */
r_static
r_int
id|gdth_set_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
r_int
id|busnum
)paren
suffix:semicolon
r_static
r_int
id|gdth_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hanum
comma
r_int
id|busnum
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020503
r_static
r_void
id|gdth_do_req
c_func
(paren
id|Scsi_Request
op_star
id|srp
comma
id|gdth_cmd_str
op_star
id|cmd
comma
r_char
op_star
id|cmnd
comma
r_int
id|timeout
)paren
suffix:semicolon
r_static
r_int
id|gdth_set_asc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Request
op_star
id|scp
)paren
suffix:semicolon
macro_line|#ifdef GDTH_IOCTL_PROC
r_static
r_int
id|gdth_set_bin_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Request
op_star
id|scp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#elif LINUX_VERSION_CODE &gt;= 0x020322
r_static
r_void
id|gdth_do_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
comma
id|gdth_cmd_str
op_star
id|cmd
comma
r_char
op_star
id|cmnd
comma
r_int
id|timeout
)paren
suffix:semicolon
r_static
r_int
id|gdth_set_asc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
macro_line|#ifdef GDTH_IOCTL_PROC
r_static
r_int
id|gdth_set_bin_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else 
r_static
r_void
id|gdth_do_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
comma
id|gdth_cmd_str
op_star
id|cmd
comma
r_char
op_star
id|cmnd
comma
r_int
id|timeout
)paren
suffix:semicolon
r_static
r_int
id|gdth_set_asc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Cmnd
id|scp
)paren
suffix:semicolon
macro_line|#ifdef GDTH_IOCTL_PROC
r_static
r_int
id|gdth_set_bin_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Cmnd
id|scp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_static
r_char
op_star
id|gdth_ioctl_alloc
c_func
(paren
r_int
id|hanum
comma
r_int
id|size
comma
r_int
id|scratch
comma
id|ulong32
op_star
id|paddr
)paren
suffix:semicolon
r_static
r_void
id|gdth_ioctl_free
c_func
(paren
r_int
id|hanum
comma
r_int
id|size
comma
r_char
op_star
id|buf
comma
id|ulong32
id|paddr
)paren
suffix:semicolon
macro_line|#ifdef GDTH_IOCTL_PROC
r_static
r_int
id|gdth_ioctl_check_bin
c_func
(paren
r_int
id|hanum
comma
id|ushort
id|size
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|gdth_wait_completion
c_func
(paren
r_int
id|hanum
comma
r_int
id|busnum
comma
r_int
id|id
)paren
suffix:semicolon
r_static
r_void
id|gdth_stop_timeout
c_func
(paren
r_int
id|hanum
comma
r_int
id|busnum
comma
r_int
id|id
)paren
suffix:semicolon
r_static
r_void
id|gdth_start_timeout
c_func
(paren
r_int
id|hanum
comma
r_int
id|busnum
comma
r_int
id|id
)paren
suffix:semicolon
r_static
r_int
id|gdth_update_timeout
c_func
(paren
r_int
id|hanum
comma
id|Scsi_Cmnd
op_star
id|scp
comma
r_int
id|timeout
)paren
suffix:semicolon
r_void
id|gdth_scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
macro_line|#endif
eof
