macro_line|#ifndef __UM_SLIP_H
DECL|macro|__UM_SLIP_H
mdefine_line|#define __UM_SLIP_H
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE 1500
multiline_comment|/* two bytes each for a (pathological) max packet of escaped chars +  * &n;  * terminating END char + initial END char                            */
DECL|macro|ENC_BUF_SIZE
mdefine_line|#define ENC_BUF_SIZE (2 * BUF_SIZE + 2)
DECL|struct|slip_data
r_struct
id|slip_data
(brace
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
r_sizeof
(paren
l_string|&quot;slnnnnn&bslash;0&quot;
)paren
)braket
suffix:semicolon
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
DECL|member|gate_addr
r_char
op_star
id|gate_addr
suffix:semicolon
DECL|member|slave
r_int
id|slave
suffix:semicolon
DECL|member|ibuf
r_char
id|ibuf
(braket
id|ENC_BUF_SIZE
)braket
suffix:semicolon
DECL|member|obuf
r_char
id|obuf
(braket
id|ENC_BUF_SIZE
)braket
suffix:semicolon
DECL|member|more
r_int
id|more
suffix:semicolon
multiline_comment|/* more data: do not read fd until ibuf has been drained */
DECL|member|pos
r_int
id|pos
suffix:semicolon
DECL|member|esc
r_int
id|esc
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|net_user_info
id|slip_user_info
suffix:semicolon
r_extern
r_int
id|set_umn_addr
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|addr
comma
r_char
op_star
id|ptp_addr
)paren
suffix:semicolon
r_extern
r_int
id|slip_user_read
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_struct
id|slip_data
op_star
id|pri
)paren
suffix:semicolon
r_extern
r_int
id|slip_user_write
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_struct
id|slip_data
op_star
id|pri
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
