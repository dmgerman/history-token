multiline_comment|/*&n;* cycx_cfm.h&t;Cyclom 2X WAN Link Driver.&n;*&t;&t;Definitions for the Cyclom 2X Firmware Module (CFM).&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2003 Arnaldo Carvalho de Melo&n;*&n;* Based on sdlasfm.h by Gene Kozin &lt;74604.152@compuserve.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 1998/08/08&t;acme&t;&t;Initial version.&n;*/
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
multiline_comment|/**&n; *&t;struct cycx_fw_info - firmware module information.&n; *&t;@codeid - firmware ID&n; *&t;@version - firmware version number&n; *&t;@adapter - compatible adapter types&n; *&t;@memsize - minimum memory size&n; *&t;@reserved - reserved&n; *&t;@startoffs - entry point offset&n; *&t;@winoffs - dual-port memory window offset&n; *&t;@codeoffs - code load offset&n; *&t;@codesize - code size&n; *&t;@dataoffs - configuration data load offset&n; *&t;@datasize - configuration data size&n; */
DECL|struct|cycx_fw_info
r_struct
id|cycx_fw_info
(brace
DECL|member|codeid
r_int
r_int
id|codeid
suffix:semicolon
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|adapter
r_int
r_int
id|adapter
(braket
id|CFM_MAX_CYCX
)braket
suffix:semicolon
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|startoffs
r_int
r_int
id|startoffs
suffix:semicolon
DECL|member|winoffs
r_int
r_int
id|winoffs
suffix:semicolon
DECL|member|codeoffs
r_int
r_int
id|codeoffs
suffix:semicolon
DECL|member|codesize
r_int
r_int
id|codesize
suffix:semicolon
DECL|member|dataoffs
r_int
r_int
id|dataoffs
suffix:semicolon
DECL|member|datasize
r_int
r_int
id|datasize
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;struct cycx_firmware - CYCX firmware file structure&n; *&t;@signature - CFM file signature&n; *&t;@version - file format version&n; *&t;@checksum - info + image&n; *&t;@reserved - reserved&n; *&t;@descr - description string&n; *&t;@info - firmware module info&n; *&t;@image - code image (variable size)&n; */
DECL|struct|cycx_firmware
r_struct
id|cycx_firmware
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|descr
r_char
id|descr
(braket
id|CFM_DESCR_LEN
)braket
suffix:semicolon
DECL|member|info
r_struct
id|cycx_fw_info
id|info
suffix:semicolon
DECL|member|image
r_int
r_char
id|image
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cycx_fw_header
r_struct
id|cycx_fw_header
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
)brace
suffix:semicolon
macro_line|#endif&t;/* _CYCX_CFM_H */
eof
