multiline_comment|/*&n; *  linux/arch/arm/drivers/char/serial-atomwide.c&n; *&n; *  Copyright (C) 1996 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   02-05-1996&t;RMK&t;Created&n; *   07-05-1996&t;RMK&t;Altered for greater number of cards.&n; *   30-07-1996&t;RMK&t;Now uses generic card code.&n; */
DECL|macro|MY_CARD_LIST
mdefine_line|#define MY_CARD_LIST { MANU_ATOMWIDE, PROD_ATOMWIDE_3PSERIAL }
DECL|macro|MY_NUMPORTS
mdefine_line|#define MY_NUMPORTS 3
DECL|macro|MY_BAUD_BASE
mdefine_line|#define MY_BAUD_BASE (7372800 / 16)
DECL|macro|MY_BASE_ADDRESS
mdefine_line|#define MY_BASE_ADDRESS(ec) &bslash;&n;&t;ecard_address ((ec), ECARD_IOC, ECARD_SLOW) + (0x2000 &gt;&gt; 2)
DECL|macro|MY_PORT_ADDRESS
mdefine_line|#define MY_PORT_ADDRESS(port,cardaddr) &bslash;&n;&t;((cardaddr) + 0x200 - (port) * 0x100)
DECL|macro|INIT
mdefine_line|#define INIT serial_card_atomwide_init
DECL|macro|EXIT
mdefine_line|#define EXIT serial_card_atomwide_exit
macro_line|#include &quot;serial-card.c&quot;
eof
