multiline_comment|/*****************************************************************************&n;* sdlasfm.h&t;WANPIPE(tm) Multiprotocol WAN Link Driver.&n;*&t;&t;Definitions for the SDLA Firmware Module (SFM).&n;*&n;* Author: &t;Gideon Hack &t;&n;*&n;* Copyright:&t;(c) 1995-1999 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jun 02, 1999  Gideon Hack&t;Added support for the S514 adapter.&n;* Dec 11, 1996&t;Gene Kozin&t;Cosmetic changes&n;* Apr 16, 1996&t;Gene Kozin&t;Changed adapter &amp; firmware IDs. Version 2&n;* Dec 15, 1995&t;Gene Kozin&t;Structures chaned&n;* Nov 09, 1995&t;Gene Kozin&t;Initial version.&n;*****************************************************************************/
macro_line|#ifndef&t;_SDLASFM_H
DECL|macro|_SDLASFM_H
mdefine_line|#define&t;_SDLASFM_H
multiline_comment|/****** Defines *************************************************************/
DECL|macro|SFM_VERSION
mdefine_line|#define&t;SFM_VERSION&t;2
DECL|macro|SFM_SIGNATURE
mdefine_line|#define&t;SFM_SIGNATURE&t;&quot;SFM - Sangoma SDLA Firmware Module&quot;
multiline_comment|/* min/max */
DECL|macro|SFM_IMAGE_SIZE
mdefine_line|#define&t;SFM_IMAGE_SIZE&t;0x8000&t;/* max size of SDLA code image file */
DECL|macro|SFM_DESCR_LEN
mdefine_line|#define&t;SFM_DESCR_LEN&t;256&t;/* max length of description string */
DECL|macro|SFM_MAX_SDLA
mdefine_line|#define&t;SFM_MAX_SDLA&t;16&t;/* max number of compatible adapters */
multiline_comment|/* Adapter types */
DECL|macro|SDLA_S502A
mdefine_line|#define SDLA_S502A&t;5020
DECL|macro|SDLA_S502E
mdefine_line|#define SDLA_S502E&t;5021
DECL|macro|SDLA_S503
mdefine_line|#define SDLA_S503&t;5030
DECL|macro|SDLA_S508
mdefine_line|#define SDLA_S508&t;5080
DECL|macro|SDLA_S507
mdefine_line|#define SDLA_S507&t;5070
DECL|macro|SDLA_S509
mdefine_line|#define SDLA_S509&t;5090
DECL|macro|SDLA_S514
mdefine_line|#define SDLA_S514&t;5140
multiline_comment|/* S514 PCI adapter CPU numbers */
DECL|macro|S514_CPU_A
mdefine_line|#define S514_CPU_A&t;&squot;A&squot;
DECL|macro|S514_CPU_B
mdefine_line|#define S514_CPU_B&t;&squot;B&squot;
multiline_comment|/* Firmware identification numbers:&n; *    0  ..  999&t;Test &amp; Diagnostics&n; *  1000 .. 1999&t;Streaming HDLC&n; *  2000 .. 2999&t;Bisync&n; *  3000 .. 3999&t;SDLC&n; *  4000 .. 4999&t;HDLC&n; *  5000 .. 5999&t;X.25&n; *  6000 .. 6999&t;Frame Relay&n; *  7000 .. 7999&t;PPP&n; *  8000 .. 8999        Cisco HDLC&n; */
DECL|macro|SFID_CALIB502
mdefine_line|#define&t;SFID_CALIB502&t; 200
DECL|macro|SFID_STRM502
mdefine_line|#define&t;SFID_STRM502&t;1200
DECL|macro|SFID_STRM508
mdefine_line|#define&t;SFID_STRM508&t;1800
DECL|macro|SFID_BSC502
mdefine_line|#define&t;SFID_BSC502&t;2200
DECL|macro|SFID_SDLC502
mdefine_line|#define&t;SFID_SDLC502&t;3200
DECL|macro|SFID_HDLC502
mdefine_line|#define&t;SFID_HDLC502&t;4200
DECL|macro|SFID_HDLC508
mdefine_line|#define&t;SFID_HDLC508&t;4800
DECL|macro|SFID_X25_502
mdefine_line|#define&t;SFID_X25_502&t;5200
DECL|macro|SFID_X25_508
mdefine_line|#define&t;SFID_X25_508&t;5800
DECL|macro|SFID_FR502
mdefine_line|#define&t;SFID_FR502&t;6200
DECL|macro|SFID_FR508
mdefine_line|#define&t;SFID_FR508&t;6800
DECL|macro|SFID_PPP502
mdefine_line|#define&t;SFID_PPP502&t;7200
DECL|macro|SFID_PPP508
mdefine_line|#define&t;SFID_PPP508&t;7800
DECL|macro|SFID_PPP514
mdefine_line|#define SFID_PPP514&t;7140
DECL|macro|SFID_CHDLC508
mdefine_line|#define&t;SFID_CHDLC508&t;8800
DECL|macro|SFID_CHDLC514
mdefine_line|#define SFID_CHDLC514&t;8140
multiline_comment|/****** Data Types **********************************************************/
DECL|struct|sfm_info
r_typedef
r_struct
id|sfm_info
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
multiline_comment|/* firmaware version number */
DECL|member|adapter
r_int
r_int
id|adapter
(braket
id|SFM_MAX_SDLA
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
DECL|typedef|sfm_info_t
)brace
id|sfm_info_t
suffix:semicolon
DECL|struct|sfm
r_typedef
r_struct
id|sfm
multiline_comment|/* SDLA firmware file structire */
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* SFM file signature */
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
id|SFM_DESCR_LEN
)braket
suffix:semicolon
multiline_comment|/* description string */
DECL|member|info
id|sfm_info_t
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
DECL|typedef|sfm_t
)brace
id|sfm_t
suffix:semicolon
macro_line|#endif&t;/* _SDLASFM_H */
eof
