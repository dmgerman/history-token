multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * With each packet command, we allocate a buffer.&n; * This is used for several packet&n; * commands (Not for READ/WRITE commands).&n; */
DECL|macro|IDEFLOPPY_PC_BUFFER_SIZE
mdefine_line|#define IDEFLOPPY_PC_BUFFER_SIZE&t;256
DECL|macro|IDETAPE_PC_BUFFER_SIZE
mdefine_line|#define IDETAPE_PC_BUFFER_SIZE&t;&t;256
multiline_comment|/*&n; * Packet flags bits.&n; */
DECL|macro|PC_ABORT
mdefine_line|#define&t;PC_ABORT&t;&t;0&t;/* set when an error is considered normal - we won&squot;t retry */
DECL|macro|PC_WAIT_FOR_DSC
mdefine_line|#define PC_WAIT_FOR_DSC&t;&t;1&t;/* 1 when polling for DSC on a media access command */
DECL|macro|PC_DMA_RECOMMENDED
mdefine_line|#define PC_DMA_RECOMMENDED&t;2&t;/* 1 when we prefer to use DMA if possible */
DECL|macro|PC_DMA_IN_PROGRESS
mdefine_line|#define&t;PC_DMA_IN_PROGRESS&t;3&t;/* 1 while DMA in progress */
DECL|macro|PC_DMA_ERROR
mdefine_line|#define&t;PC_DMA_ERROR&t;&t;4&t;/* 1 when encountered problem during DMA */
DECL|macro|PC_WRITING
mdefine_line|#define&t;PC_WRITING&t;&t;5&t;/* data direction */
DECL|macro|PC_SUPPRESS_ERROR
mdefine_line|#define&t;PC_SUPPRESS_ERROR&t;6&t;/* suppress error reporting */
DECL|macro|PC_TRANSFORM
mdefine_line|#define PC_TRANSFORM&t;&t;7&t;/* transform SCSI commands */
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
id|atapi_init_pc
c_func
(paren
r_struct
id|atapi_packet_command
op_star
id|pc
)paren
suffix:semicolon
r_extern
r_void
id|atapi_discard_data
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
r_int
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
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|atapi_read
c_func
(paren
r_struct
id|ata_device
op_star
comma
id|u8
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|atapi_write
c_func
(paren
r_struct
id|ata_device
op_star
comma
id|u8
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;ATAPI Status Register.&n; */
r_typedef
r_union
(brace
id|u8
id|all
suffix:colon
l_int|8
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|check
id|u8
id|check
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Error occurred */
DECL|member|idx
id|u8
id|idx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|corr
id|u8
id|corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Correctable error occurred */
DECL|member|drq
id|u8
id|drq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data is request by the device */
DECL|member|dsc
id|u8
id|dsc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Media access command finished / Buffer availability */
DECL|member|reserved5
id|u8
id|reserved5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|drdy
id|u8
id|drdy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Ignored for ATAPI commands (ready to accept ATA command) */
DECL|member|bsy
id|u8
id|bsy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device has access to the command block */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|bsy
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|drdy
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved5
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|dsc
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|drq
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|corr
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|idx
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|check
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_status_reg_t
)brace
id|atapi_status_reg_t
suffix:semicolon
multiline_comment|/*&n; *&t;ATAPI error register.&n; */
r_typedef
r_union
(brace
id|u8
id|all
suffix:colon
l_int|8
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|ili
id|u8
id|ili
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Illegal Length Indication */
DECL|member|eom
id|u8
id|eom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* End Of Media Detected */
DECL|member|abrt
id|u8
id|abrt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Aborted command - As defined by ATA */
DECL|member|mcr
id|u8
id|mcr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Media Change Requested - As defined by ATA */
DECL|member|sense_key
id|u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Sense key of the last failed packet command */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
id|u8
id|mcr
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|abrt
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|eom
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|ili
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_error_reg_t
)brace
id|atapi_error_reg_t
suffix:semicolon
multiline_comment|/* Currently unused, but please do not remove.  --bkz */
multiline_comment|/*&n; *&t;ATAPI Feature Register.&n; */
r_typedef
r_union
(brace
id|u8
id|all
suffix:colon
l_int|8
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|dma
id|u8
id|dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Using DMA or PIO */
DECL|member|reserved321
id|u8
id|reserved321
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|reserved654
id|u8
id|reserved654
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Reserved (Tag Type) */
DECL|member|reserved7
id|u8
id|reserved7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|reserved7
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved654
suffix:colon
l_int|3
suffix:semicolon
id|u8
id|reserved321
suffix:colon
l_int|3
suffix:semicolon
id|u8
id|dma
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_feature_reg_t
)brace
id|atapi_feature_reg_t
suffix:semicolon
multiline_comment|/*&n; *&t;ATAPI Byte Count Register.&n; */
r_typedef
r_union
(brace
id|u16
id|all
suffix:colon
l_int|16
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|low
id|u8
id|low
suffix:semicolon
multiline_comment|/* LSB */
DECL|member|high
id|u8
id|high
suffix:semicolon
multiline_comment|/* MSB */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|high
suffix:semicolon
id|u8
id|low
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_bcount_reg_t
)brace
id|atapi_bcount_reg_t
suffix:semicolon
multiline_comment|/*&n; *&t;ATAPI Interrupt Reason Register.&n; */
r_typedef
r_union
(brace
id|u8
id|all
suffix:colon
l_int|8
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|cod
id|u8
id|cod
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Information transferred is command (1) or data (0) */
DECL|member|io
id|u8
id|io
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device requests us to read (1) or write (0) */
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Reserved */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
id|u8
id|io
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|cod
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_ireason_reg_t
)brace
id|atapi_ireason_reg_t
suffix:semicolon
multiline_comment|/* Currently unused, but please do not remove.  --bkz */
multiline_comment|/*&n; *&t;ATAPI Drive Select Register.&n; */
r_typedef
r_union
(brace
id|u8
id|all
suffix:colon
l_int|8
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|sam_lun
id|u8
id|sam_lun
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Logical unit number */
DECL|member|reserved3
id|u8
id|reserved3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|drv
id|u8
id|drv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The responding drive will be drive 0 (0) or drive 1 (1) */
DECL|member|one5
id|u8
id|one5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be set to 1 */
DECL|member|reserved6
id|u8
id|reserved6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|one7
id|u8
id|one7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be set to 1 */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|one7
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved6
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|one5
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|drv
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved3
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|sam_lun
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_drivesel_reg_t
)brace
id|atapi_drivesel_reg_t
suffix:semicolon
multiline_comment|/* Currently unused, but please do not remove.  --bkz */
multiline_comment|/*&n; *&t;ATAPI Device Control Register.&n; */
r_typedef
r_union
(brace
id|u8
id|all
suffix:colon
l_int|8
suffix:semicolon
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|zero0
id|u8
id|zero0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be set to zero */
DECL|member|nien
id|u8
id|nien
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device interrupt is disabled (1) or enabled (0) */
DECL|member|srst
id|u8
id|srst
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ATA software reset. ATAPI devices should use the new ATAPI srst. */
DECL|member|one3
id|u8
id|one3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be set to 1 */
DECL|member|reserved4567
id|u8
id|reserved4567
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Reserved */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|reserved4567
suffix:colon
l_int|4
suffix:semicolon
id|u8
id|one3
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|srst
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|nien
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|zero0
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|atapi_control_reg_t
)brace
id|atapi_control_reg_t
suffix:semicolon
multiline_comment|/*&n; *&t;The following is used to format the general configuration word&n; *&t;of the ATAPI IDENTIFY DEVICE command.&n; */
DECL|struct|atapi_id_gcw
r_struct
id|atapi_id_gcw
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|packet_size
id|u8
id|packet_size
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Packet Size */
DECL|member|reserved234
id|u8
id|reserved234
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|drq_type
id|u8
id|drq_type
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Command packet DRQ type */
DECL|member|removable
id|u8
id|removable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Removable media */
DECL|member|device_type
id|u8
id|device_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Device type */
DECL|member|reserved13
id|u8
id|reserved13
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|protocol
id|u8
id|protocol
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Protocol type */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|protocol
suffix:colon
l_int|2
suffix:semicolon
id|u8
id|reserved13
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|device_type
suffix:colon
l_int|5
suffix:semicolon
id|u8
id|removable
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|drq_type
suffix:colon
l_int|2
suffix:semicolon
id|u8
id|reserved234
suffix:colon
l_int|3
suffix:semicolon
id|u8
id|packet_size
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;INQUIRY packet command - Data Format.&n; */
r_typedef
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|device_type
id|u8
id|device_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Peripheral Device Type */
DECL|member|reserved0_765
id|u8
id|reserved0_765
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Peripheral Qualifier - Reserved */
DECL|member|reserved1_6t0
id|u8
id|reserved1_6t0
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|rmb
id|u8
id|rmb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Removable Medium Bit */
DECL|member|ansi_version
id|u8
id|ansi_version
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* ANSI Version */
DECL|member|ecma_version
id|u8
id|ecma_version
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* ECMA Version */
DECL|member|iso_version
id|u8
id|iso_version
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* ISO Version */
DECL|member|response_format
id|u8
id|response_format
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Response Data Format */
DECL|member|reserved3_45
id|u8
id|reserved3_45
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|reserved3_6
id|u8
id|reserved3_6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TrmIOP - Reserved */
DECL|member|reserved3_7
id|u8
id|reserved3_7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* AENC - Reserved */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|reserved0_765
suffix:colon
l_int|3
suffix:semicolon
id|u8
id|device_type
suffix:colon
l_int|5
suffix:semicolon
id|u8
id|rmb
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved1_6t0
suffix:colon
l_int|7
suffix:semicolon
id|u8
id|iso_version
suffix:colon
l_int|2
suffix:semicolon
id|u8
id|ecma_version
suffix:colon
l_int|3
suffix:semicolon
id|u8
id|ansi_version
suffix:colon
l_int|3
suffix:semicolon
id|u8
id|reserved3_7
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved3_6
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved3_45
suffix:colon
l_int|2
suffix:semicolon
id|u8
id|response_format
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|additional_length
id|u8
id|additional_length
suffix:semicolon
multiline_comment|/* Additional Length (total_length-4) */
DECL|member|rsv5
DECL|member|rsv6
DECL|member|rsv7
id|u8
id|rsv5
comma
id|rsv6
comma
id|rsv7
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|vendor_id
id|u8
id|vendor_id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Vendor Identification */
DECL|member|product_id
id|u8
id|product_id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Product Identification */
DECL|member|revision_level
id|u8
id|revision_level
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Revision Level */
DECL|member|vendor_specific
id|u8
id|vendor_specific
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Vendor Specific - Optional */
DECL|member|reserved56t95
id|u8
id|reserved56t95
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* Reserved - Optional */
multiline_comment|/* Additional information may be returned */
DECL|typedef|atapi_inquiry_result_t
)brace
id|atapi_inquiry_result_t
suffix:semicolon
multiline_comment|/*&n; *&t;REQUEST SENSE packet command result - Data Format.&n; */
DECL|struct|atapi_request_sense
r_typedef
r_struct
id|atapi_request_sense
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|error_code
id|u8
id|error_code
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Error Code (0x70 - current or 0x71 - deferred) */
DECL|member|valid
id|u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The information field conforms to standard */
DECL|member|reserved1
id|u8
id|reserved1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Reserved (Segment Number) */
DECL|member|sense_key
id|u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Sense Key */
DECL|member|reserved2_4
id|u8
id|reserved2_4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ili
id|u8
id|ili
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Incorrect Length Indicator */
DECL|member|eom
id|u8
id|eom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* End Of Medium */
DECL|member|filemark
id|u8
id|filemark
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Filemark */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|error_code
suffix:colon
l_int|7
suffix:semicolon
id|u8
id|reserved1
suffix:colon
l_int|8
suffix:semicolon
id|u8
id|filemark
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|eom
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|ili
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|reserved2_4
suffix:colon
l_int|1
suffix:semicolon
id|u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|information
id|u32
id|information
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|asl
id|u8
id|asl
suffix:semicolon
multiline_comment|/* Additional sense length (n-7) */
DECL|member|command_specific
id|u32
id|command_specific
suffix:semicolon
multiline_comment|/* Additional command specific information */
DECL|member|asc
id|u8
id|asc
suffix:semicolon
multiline_comment|/* Additional Sense Code */
DECL|member|ascq
id|u8
id|ascq
suffix:semicolon
multiline_comment|/* Additional Sense Code Qualifier */
DECL|member|replaceable_unit_code
id|u8
id|replaceable_unit_code
suffix:semicolon
multiline_comment|/* Field Replaceable Unit Code */
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|sk_specific1
id|u8
id|sk_specific1
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Sense Key Specific */
DECL|member|sksv
id|u8
id|sksv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sense Key Specific information is valid */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
DECL|member|sksv
id|u8
id|sksv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sense Key Specific information is valid */
DECL|member|sk_specific1
id|u8
id|sk_specific1
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Sense Key Specific */
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|sk_specific
id|u8
id|sk_specific
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Sense Key Specific */
DECL|member|pad
id|u8
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Padding to 20 bytes */
DECL|typedef|atapi_request_sense_result_t
)brace
id|atapi_request_sense_result_t
suffix:semicolon
eof
