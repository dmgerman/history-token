macro_line|#ifndef __INCLUDED_TEA6415C__
DECL|macro|__INCLUDED_TEA6415C__
mdefine_line|#define __INCLUDED_TEA6415C__
multiline_comment|/* possible i2c-addresses */
DECL|macro|I2C_TEA6415C_1
mdefine_line|#define&t;I2C_TEA6415C_1&t;&t;0x03
DECL|macro|I2C_TEA6415C_2
mdefine_line|#define&t;I2C_TEA6415C_2&t;&t;0x43
multiline_comment|/* the tea6415c&squot;s design is quite brain-dead. although there are&n;   8 inputs and 6 outputs, these aren&squot;t enumerated in any way. because&n;   I don&squot;t want to say &quot;connect input pin 20 to output pin 17&quot;, I define&n;   a &quot;virtual&quot; pin-order. */
multiline_comment|/* input pins */
DECL|macro|TEA6415C_OUTPUT1
mdefine_line|#define TEA6415C_OUTPUT1 18
DECL|macro|TEA6415C_OUTPUT2
mdefine_line|#define TEA6415C_OUTPUT2 14
DECL|macro|TEA6415C_OUTPUT3
mdefine_line|#define TEA6415C_OUTPUT3 16
DECL|macro|TEA6415C_OUTPUT4
mdefine_line|#define TEA6415C_OUTPUT4 17
DECL|macro|TEA6415C_OUTPUT5
mdefine_line|#define TEA6415C_OUTPUT5 13
DECL|macro|TEA6415C_OUTPUT6
mdefine_line|#define TEA6415C_OUTPUT6 15
multiline_comment|/* output pins */
DECL|macro|TEA6415C_INPUT1
mdefine_line|#define TEA6415C_INPUT1 5
DECL|macro|TEA6415C_INPUT2
mdefine_line|#define TEA6415C_INPUT2 8
DECL|macro|TEA6415C_INPUT3
mdefine_line|#define TEA6415C_INPUT3 3
DECL|macro|TEA6415C_INPUT4
mdefine_line|#define TEA6415C_INPUT4 20
DECL|macro|TEA6415C_INPUT5
mdefine_line|#define TEA6415C_INPUT5 6
DECL|macro|TEA6415C_INPUT6
mdefine_line|#define TEA6415C_INPUT6 10
DECL|macro|TEA6415C_INPUT7
mdefine_line|#define TEA6415C_INPUT7 1
DECL|macro|TEA6415C_INPUT8
mdefine_line|#define TEA6415C_INPUT8 11
DECL|struct|tea6415c_multiplex
r_struct
id|tea6415c_multiplex
(brace
DECL|member|in
r_int
id|in
suffix:semicolon
multiline_comment|/* input-pin */
DECL|member|out
r_int
id|out
suffix:semicolon
multiline_comment|/* output-pin */
)brace
suffix:semicolon
DECL|macro|TEA6415C_SWITCH
mdefine_line|#define TEA6415C_SWITCH&t;&t;_IOW(&squot;v&squot;,1,struct tea6415c_multiplex)
macro_line|#endif
eof
