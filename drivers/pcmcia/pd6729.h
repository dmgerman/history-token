macro_line|#ifndef _INCLUDE_GUARD_PD6729_H_
DECL|macro|_INCLUDE_GUARD_PD6729_H_
mdefine_line|#define _INCLUDE_GUARD_PD6729_H_
multiline_comment|/* Debuging defines */
macro_line|#ifdef NOTRACE
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, args...) printk(fmt , ## args)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, args...) do {} while (0)
macro_line|#endif
multiline_comment|/* Flags for I365_GENCTL */
DECL|macro|I365_DF_VS1
mdefine_line|#define I365_DF_VS1&t;&t;0x40&t;/* DF-step Voltage Sense */
DECL|macro|I365_DF_VS2
mdefine_line|#define I365_DF_VS2&t;&t;0x80
multiline_comment|/* Fields in PD67_EXTERN_DATA */
DECL|macro|PD67_EXD_VS1
mdefine_line|#define PD67_EXD_VS1(s)&t;&t;(0x01 &lt;&lt; ((s) &lt;&lt; 1))
DECL|macro|PD67_EXD_VS2
mdefine_line|#define PD67_EXD_VS2(s)&t;&t;(0x02 &lt;&lt; ((s) &lt;&lt; 1))
DECL|struct|pd6729_socket
r_struct
id|pd6729_socket
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|io_base
r_int
r_int
id|io_base
suffix:semicolon
multiline_comment|/* base io address of the socket */
DECL|member|socket
r_struct
id|pcmcia_socket
id|socket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
