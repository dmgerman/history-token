macro_line|#ifndef _AV7110_CA_H_
DECL|macro|_AV7110_CA_H_
mdefine_line|#define _AV7110_CA_H_
r_struct
id|av7110
suffix:semicolon
r_extern
r_void
id|CI_handle
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
op_star
id|data
comma
id|u16
id|len
)paren
suffix:semicolon
r_extern
r_void
id|ci_get_data
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|cibuf
comma
id|u8
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|av7110_ca_register
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_void
id|av7110_ca_unregister
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_int
id|av7110_ca_init
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_void
id|av7110_ca_exit
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
macro_line|#endif /* _AV7110_CA_H_ */
eof
