multiline_comment|/*&n;* cycx_cfm.h&t;Cyclom 2X WAN Link Driver.&n;*&t;&t;Definitions for the Cyclom 2X Firmware Module (CFM).&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2000 Arnaldo Carvalho de Melo&n;*&n;* Based on sdlasfm.h by Gene Kozin &lt;74604.152@compuserve.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 1998/08/08&t;acme&t;&t;Initial version.&n;*/
macro_line|#ifndef&t;_CYCX_CFM_H
DECL|macro|_CYCX_CFM_H
mdefine_line|#define&t;_CYCX_CFM_H
multiline_comment|/* Defines */
DECL|macro|CFM_VERSION
mdefine_line|#define&t;CFM_VERSION&t;2
DECL|macro|CFM_SIGNATURE
mdefine_line|#define&t;CFM_SIGNATURE&t;&quot;CFM - Cyclades CYCX Firmware Module&quot;
multiline_comment|/* min/max */
DECL|macro|CFM_IMAGE_SIZE
mdefine_line|#define&t;CFM_IMAGE_SIZE&t;0x20000&t;/* max size of CYCX code image file */
DECL|macro|CFM_DESCR_LEN
mdefine_line|#define&t;CFM_DESCR_LEN&t;256&t;/* max length of description string */
DECL|macro|CFM_MAX_CYCX
mdefine_line|#define&t;CFM_MAX_CYCX&t;1&t;/* max number of compatible adapters */
DECL|macro|CFM_LOAD_BUFSZ
mdefine_line|#define&t;CFM_LOAD_BUFSZ&t;0x400&t;/* buffer size for reset code (buffer_load) */
multiline_comment|/* Firmware Commands */
DECL|macro|GEN_POWER_ON
mdefine_line|#define GEN_POWER_ON&t;0x1280
DECL|macro|GEN_SET_SEG
mdefine_line|#define GEN_SET_SEG&t;0x1401&t;/* boot segment setting. */
DECL|macro|GEN_BOOT_DAT
mdefine_line|#define GEN_BOOT_DAT&t;0x1402&t;/* boot data. */
DECL|macro|GEN_START
mdefine_line|#define GEN_START&t;0x1403&t;/* board start. */
DECL|macro|GEN_DEFPAR
mdefine_line|#define GEN_DEFPAR&t;0x1404&t;/* buffer length for boot. */
multiline_comment|/* Adapter Types */
DECL|macro|CYCX_2X
mdefine_line|#define CYCX_2X&t;&t;2
multiline_comment|/* for now only the 2X is supported, no plans to support 8X or 16X */
DECL|macro|CYCX_8X
mdefine_line|#define CYCX_8X&t;&t;8
DECL|macro|CYCX_16X
mdefine_line|#define CYCX_16X&t;16
DECL|macro|CFID_X25_2X
mdefine_line|#define&t;CFID_X25_2X&t;5200
multiline_comment|/* Data Types */
DECL|struct|cfm_info
r_typedef
r_struct
id|cfm_info
multiline_comment|/* firmware module information */
(brace
DECL|member|codeid
r_int
r_int
id|codeid
suffix:semicolon
multiline_comment|/* firmware ID */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* firmware version number */
DECL|member|adapter
r_int
r_int
id|adapter
(braket
id|CFM_MAX_CYCX
)braket
suffix:semicolon
multiline_comment|/* compatible adapter types */
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
multiline_comment|/* minimum memory size */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|startoffs
r_int
r_int
id|startoffs
suffix:semicolon
multiline_comment|/* entry point offset */
DECL|member|winoffs
r_int
r_int
id|winoffs
suffix:semicolon
multiline_comment|/* dual-port memory window offset */
DECL|member|codeoffs
r_int
r_int
id|codeoffs
suffix:semicolon
multiline_comment|/* code load offset */
DECL|member|codesize
r_int
r_int
id|codesize
suffix:semicolon
multiline_comment|/* code size */
DECL|member|dataoffs
r_int
r_int
id|dataoffs
suffix:semicolon
multiline_comment|/* configuration data load offset */
DECL|member|datasize
r_int
r_int
id|datasize
suffix:semicolon
multiline_comment|/* configuration data size */
DECL|typedef|cfm_info_t
)brace
id|cfm_info_t
suffix:semicolon
DECL|struct|cfm
r_typedef
r_struct
id|cfm
multiline_comment|/* CYCX firmware file structure */
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* CFM file signature */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* file format version */
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
multiline_comment|/* info + image */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|descr
r_char
id|descr
(braket
id|CFM_DESCR_LEN
)braket
suffix:semicolon
multiline_comment|/* description string */
DECL|member|info
id|cfm_info_t
id|info
suffix:semicolon
multiline_comment|/* firmware module info */
DECL|member|image
r_int
r_char
id|image
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* code image (variable size) */
DECL|typedef|cfm_t
)brace
id|cfm_t
suffix:semicolon
DECL|struct|cycx_header_s
r_typedef
r_struct
id|cycx_header_s
(brace
DECL|member|reset_size
r_int
r_int
id|reset_size
suffix:semicolon
DECL|member|data_size
r_int
r_int
id|data_size
suffix:semicolon
DECL|member|code_size
r_int
r_int
id|code_size
suffix:semicolon
DECL|typedef|cycx_header_t
)brace
id|cycx_header_t
suffix:semicolon
macro_line|#endif&t;/* _CYCX_CFM_H */
eof
