multiline_comment|/* -*- c -*-&n; * linux/include/linux/auto_fs4.h&n; *&n; * Copyright 1999-2000 Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; */
macro_line|#ifndef _LINUX_AUTO_FS4_H
DECL|macro|_LINUX_AUTO_FS4_H
mdefine_line|#define _LINUX_AUTO_FS4_H
multiline_comment|/* Include common v3 definitions */
macro_line|#include &lt;linux/auto_fs.h&gt;
multiline_comment|/* autofs v4 definitions */
DECL|macro|AUTOFS_PROTO_VERSION
macro_line|#undef AUTOFS_PROTO_VERSION
DECL|macro|AUTOFS_MIN_PROTO_VERSION
macro_line|#undef AUTOFS_MIN_PROTO_VERSION
DECL|macro|AUTOFS_MAX_PROTO_VERSION
macro_line|#undef AUTOFS_MAX_PROTO_VERSION
DECL|macro|AUTOFS_PROTO_VERSION
mdefine_line|#define AUTOFS_PROTO_VERSION&t;&t;4
DECL|macro|AUTOFS_MIN_PROTO_VERSION
mdefine_line|#define AUTOFS_MIN_PROTO_VERSION&t;3
DECL|macro|AUTOFS_MAX_PROTO_VERSION
mdefine_line|#define AUTOFS_MAX_PROTO_VERSION&t;4
DECL|macro|AUTOFS_PROTO_SUBVERSION
mdefine_line|#define AUTOFS_PROTO_SUBVERSION         5
multiline_comment|/* Mask for expire behaviour */
DECL|macro|AUTOFS_EXP_IMMEDIATE
mdefine_line|#define AUTOFS_EXP_IMMEDIATE&t;&t;1
DECL|macro|AUTOFS_EXP_LEAVES
mdefine_line|#define AUTOFS_EXP_LEAVES&t;&t;2
multiline_comment|/* New message type */
DECL|macro|autofs_ptype_expire_multi
mdefine_line|#define autofs_ptype_expire_multi&t;2&t;/* Expire entry (umount request) */
multiline_comment|/* v4 multi expire (via pipe) */
DECL|struct|autofs_packet_expire_multi
r_struct
id|autofs_packet_expire_multi
(brace
DECL|member|hdr
r_struct
id|autofs_packet_hdr
id|hdr
suffix:semicolon
DECL|member|wait_queue_token
id|autofs_wqt_t
id|wait_queue_token
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|union|autofs_packet_union
r_union
id|autofs_packet_union
(brace
DECL|member|hdr
r_struct
id|autofs_packet_hdr
id|hdr
suffix:semicolon
DECL|member|missing
r_struct
id|autofs_packet_missing
id|missing
suffix:semicolon
DECL|member|expire
r_struct
id|autofs_packet_expire
id|expire
suffix:semicolon
DECL|member|expire_multi
r_struct
id|autofs_packet_expire_multi
id|expire_multi
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AUTOFS_IOC_EXPIRE_MULTI
mdefine_line|#define AUTOFS_IOC_EXPIRE_MULTI&t;&t;_IOW(0x93,0x66,int)
DECL|macro|AUTOFS_IOC_PROTOSUBVER
mdefine_line|#define AUTOFS_IOC_PROTOSUBVER&t;&t;_IOR(0x93,0x67,int)
DECL|macro|AUTOFS_IOC_ASKREGHOST
mdefine_line|#define AUTOFS_IOC_ASKREGHOST           _IOR(0x93,0x68,int)
DECL|macro|AUTOFS_IOC_TOGGLEREGHOST
mdefine_line|#define AUTOFS_IOC_TOGGLEREGHOST        _IOR(0x93,0x69,int)
DECL|macro|AUTOFS_IOC_ASKUMOUNT
mdefine_line|#define AUTOFS_IOC_ASKUMOUNT&t;&t;_IOR(0x93,0x70,int)
macro_line|#endif /* _LINUX_AUTO_FS4_H */
eof
