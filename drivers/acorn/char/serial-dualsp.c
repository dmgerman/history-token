multiline_comment|/*&n; *  linux/drivers/acorn/char/serial-dualsp.c&n; *&n; *  Copyright (C) 1996 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   30-07-1996&t;RMK&t;Created&n; */
DECL|macro|MY_CARD_LIST
mdefine_line|#define MY_CARD_LIST { MANU_SERPORT, PROD_SERPORT_DSPORT }
DECL|macro|MY_NUMPORTS
mdefine_line|#define MY_NUMPORTS 2
DECL|macro|MY_BAUD_BASE
mdefine_line|#define MY_BAUD_BASE (3686400 / 16)
DECL|macro|MY_BASE_ADDRESS
mdefine_line|#define MY_BASE_ADDRESS(ec) &bslash;&n;&t;ecard_address (ec, ECARD_IOC, ECARD_SLOW) + (0x2000 &gt;&gt; 2)
DECL|macro|MY_PORT_ADDRESS
mdefine_line|#define MY_PORT_ADDRESS(port,cardaddress) &bslash;&n;&t;((cardaddress) + (port) * 8)
DECL|macro|INIT
mdefine_line|#define INIT serial_card_dualsp_init
DECL|macro|EXIT
mdefine_line|#define EXIT serial_card_dualsp_exit
macro_line|#include &quot;serial-card.c&quot;
eof
