multiline_comment|/*&n; *  linux/drivers/acorn/scsi/scsi.h&n; *&n; *  Copyright (C) 2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Commonly used scsi driver functions.&n; */
DECL|macro|BELT_AND_BRACES
mdefine_line|#define BELT_AND_BRACES
multiline_comment|/*&n; * The scatter-gather list handling.  This contains all&n; * the yucky stuff that needs to be fixed properly.&n; */
DECL|function|copy_SCp_to_sg
r_static
r_inline
r_int
id|copy_SCp_to_sg
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
id|Scsi_Pointer
op_star
id|SCp
comma
r_int
id|max
)paren
(brace
r_int
id|bufs
op_assign
id|SCp-&gt;buffers_residual
suffix:semicolon
id|BUG_ON
c_func
(paren
id|bufs
op_plus
l_int|1
OG
id|max
)paren
suffix:semicolon
id|sg-&gt;page
op_assign
id|virt_to_page
c_func
(paren
id|SCp-&gt;ptr
)paren
suffix:semicolon
id|sg-&gt;offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|SCp-&gt;ptr
)paren
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|sg-&gt;length
op_assign
id|SCp-&gt;this_residual
suffix:semicolon
r_if
c_cond
(paren
id|bufs
)paren
id|memcpy
c_func
(paren
id|sg
op_plus
l_int|1
comma
id|SCp-&gt;buffer
op_plus
l_int|1
comma
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|bufs
)paren
suffix:semicolon
r_return
id|bufs
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|next_SCp
r_static
r_inline
r_int
id|next_SCp
c_func
(paren
id|Scsi_Pointer
op_star
id|SCp
)paren
(brace
r_int
id|ret
op_assign
id|SCp-&gt;buffers_residual
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|SCp-&gt;buffer
op_increment
suffix:semicolon
id|SCp-&gt;buffers_residual
op_decrement
suffix:semicolon
id|SCp-&gt;ptr
op_assign
(paren
r_char
op_star
)paren
(paren
id|page_address
c_func
(paren
id|SCp-&gt;buffer-&gt;page
)paren
op_plus
id|SCp-&gt;buffer-&gt;offset
)paren
suffix:semicolon
id|SCp-&gt;this_residual
op_assign
id|SCp-&gt;buffer-&gt;length
suffix:semicolon
)brace
r_else
(brace
id|SCp-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
id|SCp-&gt;this_residual
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|get_next_SCp_byte
r_static
r_inline
r_int
r_char
id|get_next_SCp_byte
c_func
(paren
id|Scsi_Pointer
op_star
id|SCp
)paren
(brace
r_char
id|c
op_assign
op_star
id|SCp-&gt;ptr
suffix:semicolon
id|SCp-&gt;ptr
op_add_assign
l_int|1
suffix:semicolon
id|SCp-&gt;this_residual
op_sub_assign
l_int|1
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|function|put_next_SCp_byte
r_static
r_inline
r_void
id|put_next_SCp_byte
c_func
(paren
id|Scsi_Pointer
op_star
id|SCp
comma
r_int
r_char
id|c
)paren
(brace
op_star
id|SCp-&gt;ptr
op_assign
id|c
suffix:semicolon
id|SCp-&gt;ptr
op_add_assign
l_int|1
suffix:semicolon
id|SCp-&gt;this_residual
op_sub_assign
l_int|1
suffix:semicolon
)brace
DECL|function|init_SCp
r_static
r_inline
r_void
id|init_SCp
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|SCpnt-&gt;SCp.Message
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;SCp.Status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|buf
suffix:semicolon
id|SCpnt-&gt;SCp.buffer
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;buffer
suffix:semicolon
id|SCpnt-&gt;SCp.buffers_residual
op_assign
id|SCpnt-&gt;use_sg
op_minus
l_int|1
suffix:semicolon
id|SCpnt-&gt;SCp.ptr
op_assign
(paren
r_char
op_star
)paren
(paren
id|page_address
c_func
(paren
id|SCpnt-&gt;SCp.buffer-&gt;page
)paren
op_plus
id|SCpnt-&gt;SCp.buffer-&gt;offset
)paren
suffix:semicolon
id|SCpnt-&gt;SCp.this_residual
op_assign
id|SCpnt-&gt;SCp.buffer-&gt;length
suffix:semicolon
macro_line|#ifdef BELT_AND_BRACES
multiline_comment|/*&n;&t;&t; * Calculate correct buffer length.  Some commands&n;&t;&t; * come in with the wrong request_bufflen.&n;&t;&t; */
r_for
c_loop
(paren
id|buf
op_assign
l_int|0
suffix:semicolon
id|buf
op_le
id|SCpnt-&gt;SCp.buffers_residual
suffix:semicolon
id|buf
op_increment
)paren
id|len
op_add_assign
id|SCpnt-&gt;SCp.buffer
(braket
id|buf
)braket
dot
id|length
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;request_bufflen
op_ne
id|len
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;scsi%d.%c: bad request buffer &quot;
l_string|&quot;length %d, should be %ld&bslash;n&quot;
comma
id|SCpnt-&gt;host-&gt;host_no
comma
l_char|&squot;0&squot;
op_plus
id|SCpnt-&gt;target
comma
id|SCpnt-&gt;request_bufflen
comma
id|len
)paren
suffix:semicolon
id|SCpnt-&gt;request_bufflen
op_assign
id|len
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|SCpnt-&gt;SCp.buffer
op_assign
l_int|NULL
suffix:semicolon
id|SCpnt-&gt;SCp.buffers_residual
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;SCp.ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|SCpnt-&gt;request_buffer
suffix:semicolon
id|SCpnt-&gt;SCp.this_residual
op_assign
id|SCpnt-&gt;request_bufflen
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the upper SCSI layers pass a buffer, but zero length,&n;&t; * we aren&squot;t interested in the buffer pointer.&n;&t; */
r_if
c_cond
(paren
id|SCpnt-&gt;SCp.this_residual
op_eq
l_int|0
op_logical_and
id|SCpnt-&gt;SCp.ptr
)paren
(brace
macro_line|#if 0 
singleline_comment|//def BELT_AND_BRACES
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;scsi%d.%c: zero length buffer passed for &quot;
l_string|&quot;command &quot;
comma
id|SCpnt-&gt;host-&gt;host_no
comma
l_char|&squot;0&squot;
op_plus
id|SCpnt-&gt;target
)paren
suffix:semicolon
id|print_command
c_func
(paren
id|SCpnt-&gt;cmnd
)paren
suffix:semicolon
macro_line|#endif
id|SCpnt-&gt;SCp.ptr
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
