multiline_comment|/*&n;   Driver for the Nxt2002 demodulator&n;*/
macro_line|#ifndef NXT2002_H
DECL|macro|NXT2002_H
mdefine_line|#define NXT2002_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
DECL|struct|nxt2002_config
r_struct
id|nxt2002_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* request firmware for device */
DECL|member|request_firmware
r_int
(paren
op_star
id|request_firmware
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_const
r_struct
id|firmware
op_star
op_star
id|fw
comma
r_char
op_star
id|name
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|nxt2002_attach
c_func
(paren
r_const
r_struct
id|nxt2002_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// NXT2002_H
eof
