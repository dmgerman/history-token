multiline_comment|/*&n; * rocket.h --- the exported interface of the rocket driver to&n; * its configuration program.&n; *&n; * Written by Theodore Ts&squot;o, Copyright 1997.&n; *&n; * Copyright 1994, 1997, 2003 Comtrol Corporation.    All Rights Reserved.&n; * &n; * The following source code is subject to Comtrol Corporation&squot;s&n; * Developer&squot;s License Agreement.&n; * &n; * This source code is protected by United States copyright law and &n; * international copyright treaties.&n; * &n; * This source code may only be used to develop software products that&n; * will operate with Comtrol brand hardware.&n; * &n; * You may not reproduce nor distribute this source code in its original&n; * form but must produce a derivative work which includes portions of&n; * this source code only.&n; * &n; * The portions of this source code which you use in your derivative&n; * work must bear Comtrol&squot;s copyright notice:&n; * &n; * &t;&t;Copyright 1994 Comtrol Corporation.&n; * &n; */
multiline_comment|/*  Model Information Struct */
r_typedef
r_struct
(brace
DECL|member|model
r_int
r_int
id|model
suffix:semicolon
DECL|member|modelString
r_char
id|modelString
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|numPorts
r_int
r_int
id|numPorts
suffix:semicolon
DECL|member|loadrm2
r_int
id|loadrm2
suffix:semicolon
DECL|member|startingPortNumber
r_int
id|startingPortNumber
suffix:semicolon
DECL|typedef|rocketModel_t
)brace
id|rocketModel_t
suffix:semicolon
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
DECL|member|rocketModel
id|rocketModel_t
id|rocketModel
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rocket_version
r_struct
id|rocket_version
(brace
DECL|member|rocket_version
r_char
id|rocket_version
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rocket_date
r_char
id|rocket_date
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
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
mdefine_line|#define ROCKET_SPD_HI&t;&t;0x00000010&t;/* Use 56000 instead of 38400 bps */
DECL|macro|ROCKET_SPD_VHI
mdefine_line|#define ROCKET_SPD_VHI&t;&t;0x00000020&t;/* Use 115200 instead of 38400 bps */
DECL|macro|ROCKET_SPD_SHI
mdefine_line|#define ROCKET_SPD_SHI&t;&t;0x00000030&t;/* Use 230400 instead of 38400 bps */
DECL|macro|ROCKET_SPD_WARP
mdefine_line|#define ROCKET_SPD_WARP&t;        0x00000040&t;/* Use 460800 instead of 38400 bps */
DECL|macro|ROCKET_SAK
mdefine_line|#define ROCKET_SAK&t;&t;0x00000080
DECL|macro|ROCKET_SESSION_LOCKOUT
mdefine_line|#define ROCKET_SESSION_LOCKOUT&t;0x00000100
DECL|macro|ROCKET_PGRP_LOCKOUT
mdefine_line|#define ROCKET_PGRP_LOCKOUT&t;0x00000200
DECL|macro|ROCKET_RTS_TOGGLE
mdefine_line|#define ROCKET_RTS_TOGGLE&t;0x00000400
DECL|macro|ROCKET_MODE_MASK
mdefine_line|#define ROCKET_MODE_MASK        0x00003000
DECL|macro|ROCKET_MODE_RS232
mdefine_line|#define ROCKET_MODE_RS232       0x00000000
DECL|macro|ROCKET_MODE_RS485
mdefine_line|#define ROCKET_MODE_RS485       0x00001000
DECL|macro|ROCKET_MODE_RS422
mdefine_line|#define ROCKET_MODE_RS422       0x00002000
DECL|macro|ROCKET_FLAGS
mdefine_line|#define ROCKET_FLAGS&t;&t;0x00003FFF
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
DECL|macro|RCKP_RESET_RM2
mdefine_line|#define RCKP_RESET_RM2&t;&t;0x00525005
DECL|macro|RCKP_GET_VERSION
mdefine_line|#define RCKP_GET_VERSION&t;0x00525006
multiline_comment|/*  Rocketport Models */
DECL|macro|MODEL_RP32INTF
mdefine_line|#define MODEL_RP32INTF        0x0001&t;/* RP 32 port w/external I/F   */
DECL|macro|MODEL_RP8INTF
mdefine_line|#define MODEL_RP8INTF         0x0002&t;/* RP 8 port w/external I/F    */
DECL|macro|MODEL_RP16INTF
mdefine_line|#define MODEL_RP16INTF        0x0003&t;/* RP 16 port w/external I/F   */
DECL|macro|MODEL_RP8OCTA
mdefine_line|#define MODEL_RP8OCTA         0x0005&t;/* RP 8 port w/octa cable      */
DECL|macro|MODEL_RP4QUAD
mdefine_line|#define MODEL_RP4QUAD         0x0004&t;/* RP 4 port w/quad cable      */
DECL|macro|MODEL_RP8J
mdefine_line|#define MODEL_RP8J            0x0006&t;/* RP 8 port w/RJ11 connectors */
DECL|macro|MODEL_RP4J
mdefine_line|#define MODEL_RP4J            0x0007&t;/* RP 4 port w/RJ45 connectors */
DECL|macro|MODEL_RP8SNI
mdefine_line|#define MODEL_RP8SNI          0x0008&t;/* RP 8 port w/ DB78 SNI connector */
DECL|macro|MODEL_RP16SNI
mdefine_line|#define MODEL_RP16SNI         0x0009&t;/* RP 16 port w/ DB78 SNI connector */
DECL|macro|MODEL_RPP4
mdefine_line|#define MODEL_RPP4            0x000A&t;/* RP Plus 4 port              */
DECL|macro|MODEL_RPP8
mdefine_line|#define MODEL_RPP8            0x000B&t;/* RP Plus 8 port              */
DECL|macro|MODEL_RP2_232
mdefine_line|#define MODEL_RP2_232         0x000E&t;/* RP Plus 2 port RS232        */
DECL|macro|MODEL_RP2_422
mdefine_line|#define MODEL_RP2_422         0x000F&t;/* RP Plus 2 port RS232        */
multiline_comment|/*  Rocketmodem II Models */
DECL|macro|MODEL_RP6M
mdefine_line|#define MODEL_RP6M            0x000C&t;/* RM 6 port                   */
DECL|macro|MODEL_RP4M
mdefine_line|#define MODEL_RP4M            0x000D&t;/* RM 4 port                   */
multiline_comment|/* Universal PCI boards */
DECL|macro|MODEL_UPCI_RP32INTF
mdefine_line|#define MODEL_UPCI_RP32INTF   0x0801&t;/* RP UPCI 32 port w/external I/F     */
DECL|macro|MODEL_UPCI_RP8INTF
mdefine_line|#define MODEL_UPCI_RP8INTF    0x0802&t;/* RP UPCI 8 port w/external I/F      */
DECL|macro|MODEL_UPCI_RP16INTF
mdefine_line|#define MODEL_UPCI_RP16INTF   0x0803&t;/* RP UPCI 16 port w/external I/F     */
DECL|macro|MODEL_UPCI_RP8OCTA
mdefine_line|#define MODEL_UPCI_RP8OCTA    0x0805&t;/* RP UPCI 8 port w/octa cable        */ 
DECL|macro|MODEL_UPCI_RM3_8PORT
mdefine_line|#define MODEL_UPCI_RM3_8PORT  0x080C&t;/* RP UPCI Rocketmodem III 8 port     */
DECL|macro|MODEL_UPCI_RM3_4PORT
mdefine_line|#define MODEL_UPCI_RM3_4PORT  0x080C&t;/* RP UPCI Rocketmodem III 4 port     */
multiline_comment|/*  Compact PCI 16 port  */
DECL|macro|MODEL_CPCI_RP16INTF
mdefine_line|#define MODEL_CPCI_RP16INTF   0x0903&t;/* RP Compact PCI 16 port w/external I/F */
multiline_comment|/* All ISA boards */
DECL|macro|MODEL_ISA
mdefine_line|#define MODEL_ISA             0x1000
eof
