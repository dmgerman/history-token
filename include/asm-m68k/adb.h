multiline_comment|/*&n; * Definitions for talking to ADB and CUDA.  The CUDA is a microcontroller&n; * which controls the ADB, system power, RTC, and various other things on&n; * later Macintoshes&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
multiline_comment|/* First byte sent to or received from CUDA */
DECL|macro|ADB_PACKET
mdefine_line|#define ADB_PACKET&t;0
DECL|macro|CUDA_PACKET
mdefine_line|#define CUDA_PACKET&t;1
DECL|macro|ERROR_PACKET
mdefine_line|#define ERROR_PACKET&t;2
DECL|macro|TIMER_PACKET
mdefine_line|#define TIMER_PACKET&t;3
DECL|macro|POWER_PACKET
mdefine_line|#define POWER_PACKET&t;4
DECL|macro|MACIIC_PACKET
mdefine_line|#define MACIIC_PACKET&t;5
multiline_comment|/* ADB commands (2nd byte) */
DECL|macro|ADB_BUSRESET
mdefine_line|#define ADB_BUSRESET&t;&t;0
DECL|macro|ADB_FLUSH
mdefine_line|#define ADB_FLUSH(id)&t;&t;(1 + ((id) &lt;&lt; 4))
DECL|macro|ADB_WRITEREG
mdefine_line|#define ADB_WRITEREG(id, reg)&t;(8 + (reg) + ((id) &lt;&lt; 4))
DECL|macro|ADB_READREG
mdefine_line|#define ADB_READREG(id, reg)&t;(0xc + (reg) + ((id) &lt;&lt; 4))
multiline_comment|/* ADB default device IDs (upper 4 bits of 2nd byte) */
DECL|macro|ADB_DONGLE
mdefine_line|#define ADB_DONGLE&t;1&t;/* &quot;software execution control&quot; devices */
DECL|macro|ADB_KEYBOARD
mdefine_line|#define ADB_KEYBOARD&t;2
DECL|macro|ADB_MOUSE
mdefine_line|#define ADB_MOUSE&t;3
DECL|macro|ADB_TABLET
mdefine_line|#define ADB_TABLET&t;4
DECL|macro|ADB_MODEM
mdefine_line|#define ADB_MODEM&t;5
DECL|macro|ADB_MISC
mdefine_line|#define ADB_MISC&t;7&t;/* maybe a monitor */
multiline_comment|/* CUDA commands (2nd byte) */
DECL|macro|CUDA_WARM_START
mdefine_line|#define CUDA_WARM_START&t;&t;0
DECL|macro|CUDA_AUTOPOLL
mdefine_line|#define CUDA_AUTOPOLL&t;&t;1
DECL|macro|CUDA_GET_6805_ADDR
mdefine_line|#define CUDA_GET_6805_ADDR&t;2
DECL|macro|CUDA_GET_TIME
mdefine_line|#define CUDA_GET_TIME&t;&t;3
DECL|macro|CUDA_GET_PRAM
mdefine_line|#define CUDA_GET_PRAM&t;&t;7
DECL|macro|CUDA_SET_6805_ADDR
mdefine_line|#define CUDA_SET_6805_ADDR&t;8
DECL|macro|CUDA_SET_TIME
mdefine_line|#define CUDA_SET_TIME&t;&t;9
DECL|macro|CUDA_POWERDOWN
mdefine_line|#define CUDA_POWERDOWN&t;&t;0xa
DECL|macro|CUDA_POWERUP_TIME
mdefine_line|#define CUDA_POWERUP_TIME&t;0xb
DECL|macro|CUDA_SET_PRAM
mdefine_line|#define CUDA_SET_PRAM&t;&t;0xc
DECL|macro|CUDA_MS_RESET
mdefine_line|#define CUDA_MS_RESET&t;&t;0xd
DECL|macro|CUDA_SEND_DFAC
mdefine_line|#define CUDA_SEND_DFAC&t;&t;0xe
DECL|macro|CUDA_RESET_SYSTEM
mdefine_line|#define CUDA_RESET_SYSTEM&t;0x11
DECL|macro|CUDA_SET_IPL
mdefine_line|#define CUDA_SET_IPL&t;&t;0x12
DECL|macro|CUDA_SET_AUTO_RATE
mdefine_line|#define CUDA_SET_AUTO_RATE&t;0x14
DECL|macro|CUDA_GET_AUTO_RATE
mdefine_line|#define CUDA_GET_AUTO_RATE&t;0x16
DECL|macro|CUDA_SET_DEVICE_LIST
mdefine_line|#define CUDA_SET_DEVICE_LIST&t;0x19
DECL|macro|CUDA_GET_DEVICE_LIST
mdefine_line|#define CUDA_GET_DEVICE_LIST&t;0x1a
DECL|macro|CUDA_GET_SET_IIC
mdefine_line|#define CUDA_GET_SET_IIC&t;0x22
macro_line|#ifdef __KERNEL__
DECL|struct|adb_request
r_struct
id|adb_request
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|nbytes
r_int
id|nbytes
suffix:semicolon
DECL|member|reply
r_int
r_char
id|reply
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|reply_len
r_int
id|reply_len
suffix:semicolon
DECL|member|reply_expected
r_int
r_char
id|reply_expected
suffix:semicolon
DECL|member|sent
r_int
r_char
id|sent
suffix:semicolon
DECL|member|got_reply
r_int
r_char
id|got_reply
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
DECL|member|next
r_struct
id|adb_request
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_void
id|via_adb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|adb_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|nbytes
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|adb_send_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
)paren
suffix:semicolon
r_void
id|adb_poll
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|adb_register
c_func
(paren
r_int
id|default_id
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
r_char
op_star
comma
r_int
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL */
eof
