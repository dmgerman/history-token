macro_line|#ifndef __INCLUDED_TEA6420__
DECL|macro|__INCLUDED_TEA6420__
mdefine_line|#define __INCLUDED_TEA6420__
multiline_comment|/* possible addresses */
DECL|macro|I2C_TEA6420_1
mdefine_line|#define&t;I2C_TEA6420_1&t;&t;0x4c
DECL|macro|I2C_TEA6420_2
mdefine_line|#define&t;I2C_TEA6420_2&t;&t;0x4d
DECL|struct|tea6420_multiplex
r_struct
id|tea6420_multiplex
(brace
DECL|member|in
r_int
id|in
suffix:semicolon
multiline_comment|/* input of audio switch */
DECL|member|out
r_int
id|out
suffix:semicolon
multiline_comment|/* output of audio switch  */
DECL|member|gain
r_int
id|gain
suffix:semicolon
multiline_comment|/* gain of connection */
)brace
suffix:semicolon
DECL|macro|TEA6420_SWITCH
mdefine_line|#define TEA6420_SWITCH&t;&t;_IOW(&squot;v&squot;,1,struct tea6420_multiplex)
macro_line|#endif
eof
