macro_line|#ifndef __IT8712_H__
DECL|macro|__IT8712_H__
mdefine_line|#define __IT8712_H__
DECL|macro|LPC_BASE_ADDR
mdefine_line|#define LPC_BASE_ADDR&t;0x14000000
singleline_comment|// MB PnP configuration register 
DECL|macro|LPC_KEY_ADDR
mdefine_line|#define LPC_KEY_ADDR&t;0x1400002E
DECL|macro|LPC_DATA_ADDR
mdefine_line|#define LPC_DATA_ADDR&t;0x1400002F
singleline_comment|// Device LDN
DECL|macro|LDN_SERIAL1
mdefine_line|#define LDN_SERIAL1&t;0x01
DECL|macro|LDN_SERIAL2
mdefine_line|#define LDN_SERIAL2&t;0x02
DECL|macro|LDN_PARALLEL
mdefine_line|#define LDN_PARALLEL&t;0x03
DECL|macro|LDN_KEYBOARD
mdefine_line|#define LDN_KEYBOARD&t;0x05
DECL|macro|LDN_MOUSE
mdefine_line|#define LDN_MOUSE&t;0x06
DECL|macro|IT8712_UART1_PORT
mdefine_line|#define IT8712_UART1_PORT      0x3F8
DECL|macro|IT8712_UART2_PORT
mdefine_line|#define IT8712_UART2_PORT      0x2F8
macro_line|#ifndef ASM_ONLY
r_void
id|LPCSetConfig
c_func
(paren
r_char
id|LdnNumber
comma
r_char
id|Index
comma
r_char
id|data
)paren
suffix:semicolon
r_char
id|LPCGetConfig
c_func
(paren
r_char
id|LdnNumber
comma
r_char
id|Index
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
