macro_line|#ifndef _PSMOUSE_H
DECL|macro|_PSMOUSE_H
mdefine_line|#define _PSMOUSE_H
DECL|macro|PSMOUSE_CMD_SETSCALE11
mdefine_line|#define PSMOUSE_CMD_SETSCALE11&t;0x00e6
DECL|macro|PSMOUSE_CMD_SETRES
mdefine_line|#define PSMOUSE_CMD_SETRES&t;0x10e8
DECL|macro|PSMOUSE_CMD_GETINFO
mdefine_line|#define PSMOUSE_CMD_GETINFO&t;0x03e9
DECL|macro|PSMOUSE_CMD_SETSTREAM
mdefine_line|#define PSMOUSE_CMD_SETSTREAM&t;0x00ea
DECL|macro|PSMOUSE_CMD_POLL
mdefine_line|#define PSMOUSE_CMD_POLL&t;0x03eb&t;
DECL|macro|PSMOUSE_CMD_GETID
mdefine_line|#define PSMOUSE_CMD_GETID&t;0x02f2
DECL|macro|PSMOUSE_CMD_SETRATE
mdefine_line|#define PSMOUSE_CMD_SETRATE&t;0x10f3
DECL|macro|PSMOUSE_CMD_ENABLE
mdefine_line|#define PSMOUSE_CMD_ENABLE&t;0x00f4
DECL|macro|PSMOUSE_CMD_RESET_DIS
mdefine_line|#define PSMOUSE_CMD_RESET_DIS&t;0x00f6
DECL|macro|PSMOUSE_CMD_RESET_BAT
mdefine_line|#define PSMOUSE_CMD_RESET_BAT&t;0x02ff
DECL|macro|PSMOUSE_RET_BAT
mdefine_line|#define PSMOUSE_RET_BAT&t;&t;0xaa
DECL|macro|PSMOUSE_RET_ACK
mdefine_line|#define PSMOUSE_RET_ACK&t;&t;0xfa
DECL|macro|PSMOUSE_RET_NAK
mdefine_line|#define PSMOUSE_RET_NAK&t;&t;0xfe
DECL|struct|psmouse
r_struct
id|psmouse
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|cmdbuf
r_int
r_char
id|cmdbuf
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|packet
r_int
r_char
id|packet
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|cmdcnt
r_int
r_char
id|cmdcnt
suffix:semicolon
DECL|member|pktcnt
r_int
r_char
id|pktcnt
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|model
r_int
r_char
id|model
suffix:semicolon
DECL|member|last
r_int
r_int
id|last
suffix:semicolon
DECL|member|acking
r_char
id|acking
suffix:semicolon
DECL|member|ack
r_volatile
r_char
id|ack
suffix:semicolon
DECL|member|error
r_char
id|error
suffix:semicolon
DECL|member|devname
r_char
id|devname
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PSMOUSE_PS2
mdefine_line|#define PSMOUSE_PS2&t;1
DECL|macro|PSMOUSE_PS2PP
mdefine_line|#define PSMOUSE_PS2PP&t;2
DECL|macro|PSMOUSE_PS2TPP
mdefine_line|#define PSMOUSE_PS2TPP&t;3
DECL|macro|PSMOUSE_GENPS
mdefine_line|#define PSMOUSE_GENPS&t;4
DECL|macro|PSMOUSE_IMPS
mdefine_line|#define PSMOUSE_IMPS&t;5
DECL|macro|PSMOUSE_IMEX
mdefine_line|#define PSMOUSE_IMEX&t;6
DECL|macro|PSMOUSE_SYNAPTICS
mdefine_line|#define PSMOUSE_SYNAPTICS 7
r_int
id|psmouse_command
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_char
op_star
id|param
comma
r_int
id|command
)paren
suffix:semicolon
r_extern
r_int
id|psmouse_smartscroll
suffix:semicolon
macro_line|#endif /* _PSMOUSE_H */
eof
