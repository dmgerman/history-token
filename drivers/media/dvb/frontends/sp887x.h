multiline_comment|/*&n;   Driver for the Spase sp887x demodulator&n;*/
macro_line|#ifndef SP887X_H
DECL|macro|SP887X_H
mdefine_line|#define SP887X_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
DECL|struct|sp887x_config
r_struct
id|sp887x_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* PLL maintenance */
DECL|member|pll_init
r_int
(paren
op_star
id|pll_init
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
multiline_comment|/* this should return the actual frequency tuned to */
DECL|member|pll_set
r_int
(paren
op_star
id|pll_set
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|params
)paren
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
id|sp887x_attach
c_func
(paren
r_const
r_struct
id|sp887x_config
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
singleline_comment|// SP887X_H
eof
