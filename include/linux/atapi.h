multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
multiline_comment|/*&n; * With each packet command, we allocate a buffer.&n; * This is used for several packet&n; * commands (Not for READ/WRITE commands).&n; */
DECL|macro|IDEFLOPPY_PC_BUFFER_SIZE
mdefine_line|#define IDEFLOPPY_PC_BUFFER_SIZE&t;256
DECL|macro|IDETAPE_PC_BUFFER_SIZE
mdefine_line|#define IDETAPE_PC_BUFFER_SIZE&t;&t;256
multiline_comment|/* This struct get&squot;s shared between different drivers.&n; */
DECL|struct|atapi_packet_command
r_struct
id|atapi_packet_command
(brace
DECL|member|c
id|u8
id|c
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Actual packet bytes */
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Size of our data buffer */
DECL|member|current_position
r_char
op_star
id|current_position
suffix:semicolon
multiline_comment|/* Pointer into the above buffer */
DECL|member|request_transfer
r_int
id|request_transfer
suffix:semicolon
multiline_comment|/* Bytes to transfer */
DECL|member|actually_transferred
r_int
id|actually_transferred
suffix:semicolon
multiline_comment|/* Bytes actually transferred */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Status/Action bit flags: long for set_bit */
multiline_comment|/* FIXME: the following is ugly as hell, but the only way we can start&n;&t; * actually to unify the code.&n;&t; */
multiline_comment|/* driver specific data. */
multiline_comment|/* floppy/tape */
DECL|member|retries
r_int
id|retries
suffix:semicolon
multiline_comment|/* On each retry, we increment retries */
DECL|member|error
r_int
id|error
suffix:semicolon
multiline_comment|/* Error code */
DECL|member|b_data
r_char
op_star
id|b_data
suffix:semicolon
multiline_comment|/* Pointer which runs on the buffers */
DECL|member|b_count
r_int
r_int
id|b_count
suffix:semicolon
multiline_comment|/* Missing/Available data on the current buffer */
DECL|member|pc_buffer
id|u8
id|pc_buffer
(braket
id|IDEFLOPPY_PC_BUFFER_SIZE
)braket
suffix:semicolon
multiline_comment|/* Temporary buffer */
multiline_comment|/* Called when this packet command is completed */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
multiline_comment|/* only tape */
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
multiline_comment|/* only scsi */
r_struct
(brace
DECL|member|b_count
r_int
r_int
id|b_count
suffix:semicolon
multiline_comment|/* Bytes transferred from current entry */
DECL|member|sg
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
multiline_comment|/* Scatter gather table */
DECL|member|scsi_cmd
r_struct
id|scsi_cmnd
op_star
id|scsi_cmd
suffix:semicolon
multiline_comment|/* SCSI command */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Scsi completion routine */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* Command timeout */
DECL|member|s
)brace
id|s
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|atapi_discard_data
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|bcount
)paren
suffix:semicolon
r_extern
r_void
id|atapi_write_zeros
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|bcount
)paren
suffix:semicolon
r_extern
r_void
id|atapi_init_pc
c_func
(paren
r_struct
id|atapi_packet_command
op_star
id|pc
)paren
suffix:semicolon
eof
