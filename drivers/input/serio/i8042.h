macro_line|#ifndef _I8042_H
DECL|macro|_I8042_H
mdefine_line|#define _I8042_H
multiline_comment|/*&n; * $Id: i8042.h,v 1.6 2001/10/05 22:48:09 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
multiline_comment|/*&n; * If you want to reset your i8042 upon boot, define this.&n; */
DECL|macro|I8042_RESET
macro_line|#undef I8042_RESET
multiline_comment|/*&n; * If you want to trace all the i/o the i8042 module does for&n; * debugging purposes, define this.&n; */
DECL|macro|I8042_DEBUG_IO
macro_line|#undef I8042_DEBUG_IO
multiline_comment|/*&n; * On most PC based systems the keyboard IRQ is 1.&n; */
DECL|macro|I8042_KBD_IRQ
mdefine_line|#define I8042_KBD_IRQ CONFIG_I8042_KBD_IRQ 
multiline_comment|/*&n; * On most PC based systems the aux port IRQ is 12. There are exceptions,&n; * though. Unfortunately IRQ probing is not possible without touching&n; * the device attached to the port.&n; */
DECL|macro|I8042_AUX_IRQ
mdefine_line|#define I8042_AUX_IRQ CONFIG_I8042_AUX_IRQ
multiline_comment|/*&n; * This is in 50us units, the time we wait for the i8042 to react. This&n; * has to be long enough for the i8042 itself to timeout on sending a byte&n; * to a non-existent mouse.&n; */
DECL|macro|I8042_CTL_TIMEOUT
mdefine_line|#define I8042_CTL_TIMEOUT&t;10000
multiline_comment|/*&n; * Register numbers.&n; */
DECL|macro|I8042_COMMAND_REG
mdefine_line|#define I8042_COMMAND_REG&t;CONFIG_I8042_REG_BASE + 4&t;
DECL|macro|I8042_STATUS_REG
mdefine_line|#define I8042_STATUS_REG&t;CONFIG_I8042_REG_BASE + 4&t;
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG&t;&t;CONFIG_I8042_REG_BASE&t;
multiline_comment|/*&n; * Status register bits.&n; */
DECL|macro|I8042_STR_PARITY
mdefine_line|#define I8042_STR_PARITY&t;0x80
DECL|macro|I8042_STR_TIMEOUT
mdefine_line|#define I8042_STR_TIMEOUT&t;0x40
DECL|macro|I8042_STR_AUXDATA
mdefine_line|#define I8042_STR_AUXDATA&t;0x20
DECL|macro|I8042_STR_KEYLOCK
mdefine_line|#define I8042_STR_KEYLOCK&t;0x10
DECL|macro|I8042_STR_CMDDAT
mdefine_line|#define I8042_STR_CMDDAT&t;0x08
DECL|macro|I8042_STR_IBF
mdefine_line|#define I8042_STR_IBF&t;&t;0x02
DECL|macro|I8042_STR_OBF
mdefine_line|#define&t;I8042_STR_OBF&t;&t;0x01
multiline_comment|/*&n; * Control register bits.&n; */
DECL|macro|I8042_CTR_KBDINT
mdefine_line|#define I8042_CTR_KBDINT&t;0x01
DECL|macro|I8042_CTR_AUXINT
mdefine_line|#define I8042_CTR_AUXINT&t;0x02
DECL|macro|I8042_CTR_IGNKEYLOCK
mdefine_line|#define I8042_CTR_IGNKEYLOCK&t;0x08
DECL|macro|I8042_CTR_KBDDIS
mdefine_line|#define I8042_CTR_KBDDIS&t;0x10
DECL|macro|I8042_CTR_AUXDIS
mdefine_line|#define I8042_CTR_AUXDIS&t;0x20
DECL|macro|I8042_CTR_XLATE
mdefine_line|#define I8042_CTR_XLATE&t;&t;0x40
multiline_comment|/*&n; * Commands.&n; */
DECL|macro|I8042_CMD_CTL_RCTR
mdefine_line|#define I8042_CMD_CTL_RCTR&t;0x0120
DECL|macro|I8042_CMD_CTL_WCTR
mdefine_line|#define I8042_CMD_CTL_WCTR&t;0x1060
DECL|macro|I8042_CMD_CTL_TEST
mdefine_line|#define I8042_CMD_CTL_TEST&t;0x01aa
DECL|macro|I8042_CMD_KBD_DISABLE
mdefine_line|#define I8042_CMD_KBD_DISABLE&t;0x00ad
DECL|macro|I8042_CMD_KBD_ENABLE
mdefine_line|#define I8042_CMD_KBD_ENABLE&t;0x00ae
DECL|macro|I8042_CMD_KBD_TEST
mdefine_line|#define I8042_CMD_KBD_TEST&t;0x01ab
DECL|macro|I8042_CMD_KBD_LOOP
mdefine_line|#define I8042_CMD_KBD_LOOP&t;0x11d2
DECL|macro|I8042_CMD_AUX_DISABLE
mdefine_line|#define I8042_CMD_AUX_DISABLE&t;0x00a7
DECL|macro|I8042_CMD_AUX_ENABLE
mdefine_line|#define I8042_CMD_AUX_ENABLE&t;0x00a8
DECL|macro|I8042_CMD_AUX_TEST
mdefine_line|#define I8042_CMD_AUX_TEST&t;0x01a9
DECL|macro|I8042_CMD_AUX_SEND
mdefine_line|#define I8042_CMD_AUX_SEND&t;0x10d4
DECL|macro|I8042_CMD_AUX_LOOP
mdefine_line|#define I8042_CMD_AUX_LOOP&t;0x11d3
multiline_comment|/*&n; * Return codes.&n; */
DECL|macro|I8042_RET_CTL_TEST
mdefine_line|#define I8042_RET_CTL_TEST&t;0x55
multiline_comment|/*&n; * Expected maximum internal i8042 buffer size. This is used for flushing&n; * the i8042 buffers. 32 should be more than enough.&n; */
DECL|macro|I8042_BUFFER_SIZE
mdefine_line|#define I8042_BUFFER_SIZE&t;32
macro_line|#endif /* _I8042_H */
eof
