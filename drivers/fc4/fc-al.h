multiline_comment|/* fc-al.h: Definitions for Fibre Channel Arbitrated Loop topology.&n; *&n; * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * Sources:&n; *&t;Fibre Channel Arbitrated Loop (FC-AL), ANSI, Rev. 4.5, 1995&n; */
macro_line|#ifndef __FC_AL_H
DECL|macro|__FC_AL_H
mdefine_line|#define __FC_AL_H
multiline_comment|/* Loop initialization payloads */
DECL|macro|FC_AL_LISM
mdefine_line|#define&t;FC_AL_LISM&t;0x11010000&t;/* Select Master, 12B payload */
DECL|macro|FC_AL_LIFA
mdefine_line|#define FC_AL_LIFA&t;0x11020000&t;/* Fabric Assign AL_PA bitmap, 20B payload */
DECL|macro|FC_AL_LIPA
mdefine_line|#define FC_AL_LIPA&t;0x11030000&t;/* Previously Acquired AL_PA bitmap, 20B payload */
DECL|macro|FC_AL_LIHA
mdefine_line|#define FC_AL_LIHA&t;0x11040000&t;/* Hard Assigned AL_PA bitmap, 20B payload */
DECL|macro|FC_AL_LISA
mdefine_line|#define FC_AL_LISA&t;0x11050000&t;/* Soft Assigned AL_PA bitmap, 20B payload */
DECL|macro|FC_AL_LIRP
mdefine_line|#define FC_AL_LIRP&t;0x11060000&t;/* Report AL_PA position map, 132B payload */
DECL|macro|FC_AL_LILP
mdefine_line|#define FC_AL_LILP&t;0x11070000&t;/* Loop AL_PA position map, 132B payload */
r_typedef
r_struct
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|alpa
id|u8
id|alpa
(braket
l_int|127
)braket
suffix:semicolon
DECL|typedef|fc_al_posmap
)brace
id|fc_al_posmap
suffix:semicolon
macro_line|#endif /* !(__FC_H) */
eof
