multiline_comment|/*&n; * This file contains the exported interface of the rocket driver to&n; * its configuration program.&n; */
DECL|struct|rocket_config
r_struct
id|rocket_config
(brace
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|closing_wait
r_int
id|closing_wait
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rocket_ports
r_struct
id|rocket_ports
(brace
DECL|member|tty_major
r_int
id|tty_major
suffix:semicolon
DECL|member|callout_major
r_int
id|callout_major
suffix:semicolon
DECL|member|port_bitmap
r_int
id|port_bitmap
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Rocketport flags&n; */
DECL|macro|ROCKET_CALLOUT_NOHUP
mdefine_line|#define ROCKET_CALLOUT_NOHUP    0x00000001
DECL|macro|ROCKET_FORCE_CD
mdefine_line|#define ROCKET_FORCE_CD&t;&t;0x00000002
DECL|macro|ROCKET_HUP_NOTIFY
mdefine_line|#define ROCKET_HUP_NOTIFY&t;0x00000004
DECL|macro|ROCKET_SPLIT_TERMIOS
mdefine_line|#define ROCKET_SPLIT_TERMIOS&t;0x00000008
DECL|macro|ROCKET_SPD_MASK
mdefine_line|#define ROCKET_SPD_MASK&t;&t;0x00000070
DECL|macro|ROCKET_SPD_HI
mdefine_line|#define ROCKET_SPD_HI&t;&t;0x00000010 /* Use 56000 instead of 38400 bps */
DECL|macro|ROCKET_SPD_VHI
mdefine_line|#define ROCKET_SPD_VHI&t;&t;0x00000020 /* Use 115200 instead of 38400 bps*/
DECL|macro|ROCKET_SPD_SHI
mdefine_line|#define ROCKET_SPD_SHI&t;&t;0x00000030 /* Use 230400 instead of 38400 bps*/
DECL|macro|ROCKET_SPD_WARP
mdefine_line|#define ROCKET_SPD_WARP&t;        0x00000040 /* Use 460800 instead of 38400 bps*/
DECL|macro|ROCKET_SAK
mdefine_line|#define ROCKET_SAK&t;&t;0x00000080
DECL|macro|ROCKET_SESSION_LOCKOUT
mdefine_line|#define ROCKET_SESSION_LOCKOUT&t;0x00000100
DECL|macro|ROCKET_PGRP_LOCKOUT
mdefine_line|#define ROCKET_PGRP_LOCKOUT&t;0x00000200
DECL|macro|ROCKET_FLAGS
mdefine_line|#define ROCKET_FLAGS&t;&t;0x000003FF
DECL|macro|ROCKET_USR_MASK
mdefine_line|#define ROCKET_USR_MASK 0x0071&t;/* Legal flags that non-privileged&n;&t;&t;&t;&t; * users can set or reset */
multiline_comment|/*&n; * For closing_wait and closing_wait2&n; */
DECL|macro|ROCKET_CLOSING_WAIT_NONE
mdefine_line|#define ROCKET_CLOSING_WAIT_NONE&t;65535
DECL|macro|ROCKET_CLOSING_WAIT_INF
mdefine_line|#define ROCKET_CLOSING_WAIT_INF&t;&t;0
multiline_comment|/*&n; * Rocketport ioctls -- &quot;RP&quot;&n; */
DECL|macro|RCKP_GET_STRUCT
mdefine_line|#define RCKP_GET_STRUCT&t;&t;0x00525001
DECL|macro|RCKP_GET_CONFIG
mdefine_line|#define RCKP_GET_CONFIG&t;&t;0x00525002
DECL|macro|RCKP_SET_CONFIG
mdefine_line|#define RCKP_SET_CONFIG&t;&t;0x00525003
DECL|macro|RCKP_GET_PORTS
mdefine_line|#define RCKP_GET_PORTS&t;&t;0x00525004
eof
