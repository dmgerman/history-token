multiline_comment|/*&n; *  Copyright (C) 2000 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __EC_H__
DECL|macro|__EC_H__
mdefine_line|#define __EC_H__
singleline_comment|// TODO: Linux-specific
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
multiline_comment|/*****************************************************************************&n; *                             Types &amp; Other Defines&n; *****************************************************************************/
DECL|macro|EC_DEFAULT_TIMEOUT
mdefine_line|#define EC_DEFAULT_TIMEOUT              1000            /* 1 second */
DECL|macro|EC_GPE_UNKNOWN
mdefine_line|#define EC_GPE_UNKNOWN                  0xFFFFFFFF
DECL|macro|EC_PORT_UNKNOWN
mdefine_line|#define EC_PORT_UNKNOWN                 0x00000000
DECL|macro|EC_BURST_ENABLE_ACKNOWLEDGE
mdefine_line|#define EC_BURST_ENABLE_ACKNOWLEDGE     0x90
multiline_comment|/* &n; * EC_COMMAND:&n; * -----------&n; */
DECL|typedef|EC_COMMAND
r_typedef
id|UINT8
id|EC_COMMAND
suffix:semicolon
DECL|macro|EC_COMMAND_UNKNOWN
mdefine_line|#define EC_COMMAND_UNKNOWN              ((EC_COMMAND) 0x00)
DECL|macro|EC_COMMAND_READ
mdefine_line|#define EC_COMMAND_READ                 ((EC_COMMAND) 0x80)
DECL|macro|EC_COMMAND_WRITE
mdefine_line|#define EC_COMMAND_WRITE                ((EC_COMMAND) 0x81)
DECL|macro|EC_COMMAND_QUERY
mdefine_line|#define EC_COMMAND_QUERY                ((EC_COMMAND) 0x84)
multiline_comment|/*&n; * EC_STATUS:&n; * ----------&n; * The encoding of the EC status register is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the output buffer is full).&n; * +-+-+-+-+-+-+-+-+&n; * |7|6|5|4|3|2|1|0|    &n; * +-+-+-+-+-+-+-+-+&n; *  | | | | | | | |&n; *  | | | | | | | +- Output Buffer Full (OBF)?&n; *  | | | | | | +--- Input Buffer Full (IBF)?&n; *  | | | | | +----- &lt;reserved&gt;&n; *  | | | | +------- data Register is command Byte?&n; *  | | | +--------- Burst Mode Enabled?&n; *  | | +----------- SCI event?&n; *  | +------------- SMI event?&n; *  +--------------- &lt;Reserved&gt;&n; *&n; */
DECL|typedef|EC_STATUS
r_typedef
id|UINT8
id|EC_STATUS
suffix:semicolon
DECL|macro|EC_FLAG_OUTPUT_BUFFER
mdefine_line|#define EC_FLAG_OUTPUT_BUFFER           ((EC_STATUS) 0x01)
DECL|macro|EC_FLAG_INPUT_BUFFER
mdefine_line|#define EC_FLAG_INPUT_BUFFER            ((EC_STATUS) 0x02)
DECL|macro|EC_FLAG_BURST_MODE
mdefine_line|#define EC_FLAG_BURST_MODE              ((EC_STATUS) 0x10)
DECL|macro|EC_FLAG_SCI
mdefine_line|#define EC_FLAG_SCI                     ((EC_STATUS) 0x20)
multiline_comment|/* &n; * EC_EVENT:&n; * ---------&n; */
DECL|typedef|EC_EVENT
r_typedef
id|UINT8
id|EC_EVENT
suffix:semicolon
DECL|macro|EC_EVENT_UNKNOWN
mdefine_line|#define EC_EVENT_UNKNOWN                ((EC_EVENT) 0x00)
DECL|macro|EC_EVENT_NONE
mdefine_line|#define EC_EVENT_NONE                   ((EC_EVENT) 0x00)
DECL|macro|EC_EVENT_OUTPUT_BUFFER_FULL
mdefine_line|#define EC_EVENT_OUTPUT_BUFFER_FULL&t;&t;((EC_EVENT) 0x01)
DECL|macro|EC_EVENT_INPUT_BUFFER_EMPTY
mdefine_line|#define EC_EVENT_INPUT_BUFFER_EMPTY  &t;((EC_EVENT) 0x02)
DECL|macro|EC_EVENT_SCI
mdefine_line|#define EC_EVENT_SCI                    ((EC_EVENT) 0x03)
multiline_comment|/*&n; * EC_REQUEST:&n; * -----------&n; */
r_typedef
r_struct
(brace
DECL|member|command
id|EC_COMMAND
id|command
suffix:semicolon
DECL|member|address
id|UINT8
id|address
suffix:semicolon
DECL|member|data
id|UINT8
id|data
suffix:semicolon
DECL|typedef|EC_REQUEST
)brace
id|EC_REQUEST
suffix:semicolon
macro_line|#endif  /* __EC_H__ */
eof
