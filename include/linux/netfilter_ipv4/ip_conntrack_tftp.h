macro_line|#ifndef _IP_CT_TFTP
DECL|macro|_IP_CT_TFTP
mdefine_line|#define _IP_CT_TFTP
DECL|macro|TFTP_PORT
mdefine_line|#define TFTP_PORT 69
DECL|struct|tftphdr
r_struct
id|tftphdr
(brace
DECL|member|opcode
id|u_int16_t
id|opcode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TFTP_OPCODE_READ
mdefine_line|#define TFTP_OPCODE_READ&t;1
DECL|macro|TFTP_OPCODE_WRITE
mdefine_line|#define TFTP_OPCODE_WRITE&t;2
DECL|macro|TFTP_OPCODE_DATA
mdefine_line|#define TFTP_OPCODE_DATA&t;3
DECL|macro|TFTP_OPCODE_ACK
mdefine_line|#define TFTP_OPCODE_ACK&t;&t;4
DECL|macro|TFTP_OPCODE_ERROR
mdefine_line|#define TFTP_OPCODE_ERROR&t;5
macro_line|#endif /* _IP_CT_TFTP */
eof
