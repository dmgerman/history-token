multiline_comment|/*&n; * Defines for the IBM TAH&n; *&n; * Copyright 2004 MontaVista Software, Inc.&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef _IBM_EMAC_TAH_H
DECL|macro|_IBM_EMAC_TAH_H
mdefine_line|#define _IBM_EMAC_TAH_H
multiline_comment|/* TAH */
DECL|struct|tah_regs
r_typedef
r_struct
id|tah_regs
(brace
DECL|member|tah_revid
id|u32
id|tah_revid
suffix:semicolon
DECL|member|pad
id|u32
id|pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tah_mr
id|u32
id|tah_mr
suffix:semicolon
DECL|member|tah_ssr0
id|u32
id|tah_ssr0
suffix:semicolon
DECL|member|tah_ssr1
id|u32
id|tah_ssr1
suffix:semicolon
DECL|member|tah_ssr2
id|u32
id|tah_ssr2
suffix:semicolon
DECL|member|tah_ssr3
id|u32
id|tah_ssr3
suffix:semicolon
DECL|member|tah_ssr4
id|u32
id|tah_ssr4
suffix:semicolon
DECL|member|tah_ssr5
id|u32
id|tah_ssr5
suffix:semicolon
DECL|member|tah_tsr
id|u32
id|tah_tsr
suffix:semicolon
DECL|typedef|tah_t
)brace
id|tah_t
suffix:semicolon
multiline_comment|/* TAH engine */
DECL|macro|TAH_MR_CVR
mdefine_line|#define TAH_MR_CVR&t;&t;&t;0x80000000
DECL|macro|TAH_MR_SR
mdefine_line|#define TAH_MR_SR&t;&t;&t;0x40000000
DECL|macro|TAH_MR_ST_256
mdefine_line|#define TAH_MR_ST_256&t;&t;&t;0x01000000
DECL|macro|TAH_MR_ST_512
mdefine_line|#define TAH_MR_ST_512&t;&t;&t;0x02000000
DECL|macro|TAH_MR_ST_768
mdefine_line|#define TAH_MR_ST_768&t;&t;&t;0x03000000
DECL|macro|TAH_MR_ST_1024
mdefine_line|#define TAH_MR_ST_1024&t;&t;&t;0x04000000
DECL|macro|TAH_MR_ST_1280
mdefine_line|#define TAH_MR_ST_1280&t;&t;&t;0x05000000
DECL|macro|TAH_MR_ST_1536
mdefine_line|#define TAH_MR_ST_1536&t;&t;&t;0x06000000
DECL|macro|TAH_MR_TFS_16KB
mdefine_line|#define TAH_MR_TFS_16KB&t;&t;&t;0x00000000
DECL|macro|TAH_MR_TFS_2KB
mdefine_line|#define TAH_MR_TFS_2KB&t;&t;&t;0x00200000
DECL|macro|TAH_MR_TFS_4KB
mdefine_line|#define TAH_MR_TFS_4KB&t;&t;&t;0x00400000
DECL|macro|TAH_MR_TFS_6KB
mdefine_line|#define TAH_MR_TFS_6KB&t;&t;&t;0x00600000
DECL|macro|TAH_MR_TFS_8KB
mdefine_line|#define TAH_MR_TFS_8KB&t;&t;&t;0x00800000
DECL|macro|TAH_MR_TFS_10KB
mdefine_line|#define TAH_MR_TFS_10KB&t;&t;&t;0x00a00000
DECL|macro|TAH_MR_DTFP
mdefine_line|#define TAH_MR_DTFP&t;&t;&t;0x00100000
DECL|macro|TAH_MR_DIG
mdefine_line|#define TAH_MR_DIG&t;&t;&t;0x00080000
macro_line|#endif&t;&t;&t;&t;/* _IBM_EMAC_TAH_H */
eof
