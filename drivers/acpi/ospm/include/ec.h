multiline_comment|/*****************************************************************************&n; *&n; * Module Name: ec.h&n; *   $Revision: 19 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __EC_H__
DECL|macro|__EC_H__
mdefine_line|#define __EC_H__
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
macro_line|#include &lt;bm.h&gt;
multiline_comment|/*****************************************************************************&n; *                            Types &amp; Other Defines&n; *****************************************************************************/
DECL|macro|EC_DEFAULT_TIMEOUT
mdefine_line|#define EC_DEFAULT_TIMEOUT&t;1000&t;&t;/* 1 second */
DECL|macro|EC_GPE_UNKNOWN
mdefine_line|#define EC_GPE_UNKNOWN&t;&t;0xFFFFFFFF
DECL|macro|EC_PORT_UNKNOWN
mdefine_line|#define EC_PORT_UNKNOWN&t;&t;0x00000000
DECL|macro|EC_BURST_ENABLE_ACKNOWLEDGE
mdefine_line|#define EC_BURST_ENABLE_ACKNOWLEDGE 0x90
multiline_comment|/*&n; * Commands:&n; * ---------&n; */
DECL|typedef|EC_COMMAND
r_typedef
id|u8
id|EC_COMMAND
suffix:semicolon
DECL|macro|EC_COMMAND_UNKNOWN
mdefine_line|#define EC_COMMAND_UNKNOWN&t;((EC_COMMAND) 0x00)
DECL|macro|EC_COMMAND_READ
mdefine_line|#define EC_COMMAND_READ&t;&t;((EC_COMMAND) 0x80)
DECL|macro|EC_COMMAND_WRITE
mdefine_line|#define EC_COMMAND_WRITE&t;((EC_COMMAND) 0x81)
DECL|macro|EC_COMMAND_QUERY
mdefine_line|#define EC_COMMAND_QUERY&t;((EC_COMMAND) 0x84)
multiline_comment|/*&n; * EC_STATUS:&n; * ----------&n; * The encoding of the EC status register is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the output buffer is full).&n; * +-+-+-+-+-+-+-+-+&n; * |7|6|5|4|3|2|1|0|&n; * +-+-+-+-+-+-+-+-+&n; *  | | | | | | | |&n; *  | | | | | | | +- Output Buffer Full (OBF)?&n; *  | | | | | | +--- Input Buffer Full (IBF)?&n; *  | | | | | +----- &lt;reserved&gt;&n; *  | | | | +------- data Register is command Byte?&n; *  | | | +--------- Burst Mode Enabled?&n; *  | | +----------- SCI event?&n; *  | +------------- SMI event?&n; *  +--------------- &lt;Reserved&gt;&n; *&n; */
DECL|typedef|EC_STATUS
r_typedef
id|u32
id|EC_STATUS
suffix:semicolon
DECL|macro|EC_FLAG_OUTPUT_BUFFER
mdefine_line|#define EC_FLAG_OUTPUT_BUFFER&t;((EC_STATUS) 0x01)
DECL|macro|EC_FLAG_INPUT_BUFFER
mdefine_line|#define EC_FLAG_INPUT_BUFFER&t;((EC_STATUS) 0x02)
DECL|macro|EC_FLAG_BURST_MODE
mdefine_line|#define EC_FLAG_BURST_MODE&t;((EC_STATUS) 0x10)
DECL|macro|EC_FLAG_SCI
mdefine_line|#define EC_FLAG_SCI&t;&t;((EC_STATUS) 0x20)
multiline_comment|/*&n; * EC_EVENT:&n; * ---------&n; */
DECL|typedef|EC_EVENT
r_typedef
id|u32
id|EC_EVENT
suffix:semicolon
DECL|macro|EC_EVENT_UNKNOWN
mdefine_line|#define EC_EVENT_UNKNOWN&t;((EC_EVENT) 0x00)
DECL|macro|EC_EVENT_NONE
mdefine_line|#define EC_EVENT_NONE&t;&t;((EC_EVENT) 0x00)
DECL|macro|EC_EVENT_OUTPUT_BUFFER_FULL
mdefine_line|#define EC_EVENT_OUTPUT_BUFFER_FULL ((EC_EVENT) 0x01)
DECL|macro|EC_EVENT_INPUT_BUFFER_EMPTY
mdefine_line|#define EC_EVENT_INPUT_BUFFER_EMPTY ((EC_EVENT) 0x02)
DECL|macro|EC_EVENT_SCI
mdefine_line|#define EC_EVENT_SCI&t;&t;((EC_EVENT) 0x03)
multiline_comment|/*&n; * Hardware IDs:&n; * -------------&n; */
DECL|macro|EC_HID_EC
mdefine_line|#define EC_HID_EC&t;&t;&quot;PNP0C09&quot;
multiline_comment|/*&n; * EC_REQUEST:&n; * -----------&n; */
r_typedef
r_struct
(brace
DECL|member|command
id|EC_COMMAND
id|command
suffix:semicolon
DECL|member|address
id|u8
id|address
suffix:semicolon
DECL|member|data
id|u8
id|data
suffix:semicolon
DECL|typedef|EC_REQUEST
)brace
id|EC_REQUEST
suffix:semicolon
multiline_comment|/*&n; * Device Context:&n; * ---------------&n; */
r_typedef
r_struct
(brace
DECL|member|device_handle
id|BM_HANDLE
id|device_handle
suffix:semicolon
DECL|member|acpi_handle
id|acpi_handle
id|acpi_handle
suffix:semicolon
DECL|member|gpe_bit
id|u32
id|gpe_bit
suffix:semicolon
DECL|member|status_port
id|u32
id|status_port
suffix:semicolon
DECL|member|command_port
id|u32
id|command_port
suffix:semicolon
DECL|member|data_port
id|u32
id|data_port
suffix:semicolon
DECL|member|use_global_lock
id|u32
id|use_global_lock
suffix:semicolon
DECL|member|query_data
id|u8
id|query_data
suffix:semicolon
DECL|member|mutex
id|acpi_handle
id|mutex
suffix:semicolon
DECL|typedef|EC_CONTEXT
)brace
id|EC_CONTEXT
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                             Function Prototypes&n; *****************************************************************************/
multiline_comment|/* ec.c */
id|acpi_status
id|ec_initialize
c_func
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|ec_terminate
c_func
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|ec_notify
(paren
id|u32
id|notify_type
comma
id|u32
id|device
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|ec_request
c_func
(paren
id|BM_REQUEST
op_star
id|request_info
comma
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/* ectransx.c */
id|acpi_status
id|ec_transaction
(paren
id|EC_CONTEXT
op_star
id|ec
comma
id|EC_REQUEST
op_star
id|ec_request
)paren
suffix:semicolon
id|acpi_status
id|ec_io_read
(paren
id|EC_CONTEXT
op_star
id|ec
comma
id|u32
id|io_port
comma
id|u8
op_star
id|data
comma
id|EC_EVENT
id|wait_event
)paren
suffix:semicolon
id|acpi_status
id|ec_io_write
(paren
id|EC_CONTEXT
op_star
id|ec
comma
id|u32
id|io_port
comma
id|u8
id|data
comma
id|EC_EVENT
id|wait_event
)paren
suffix:semicolon
multiline_comment|/* ecgpe.c */
id|acpi_status
id|ec_install_gpe_handler
(paren
id|EC_CONTEXT
op_star
id|ec
)paren
suffix:semicolon
id|acpi_status
id|ec_remove_gpe_handler
(paren
id|EC_CONTEXT
op_star
id|ec
)paren
suffix:semicolon
multiline_comment|/* ecspace.c */
id|acpi_status
id|ec_install_space_handler
(paren
id|EC_CONTEXT
op_star
id|ec
)paren
suffix:semicolon
id|acpi_status
id|ec_remove_space_handler
(paren
id|EC_CONTEXT
op_star
id|ec
)paren
suffix:semicolon
macro_line|#endif  /* __EC_H__ */
eof
