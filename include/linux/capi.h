multiline_comment|/* $Id: capi.h,v 1.4.6.1 2001/09/23 22:25:05 kai Exp $&n; * &n; * CAPI 2.0 Interface for Linux&n; * &n; * Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef __LINUX_CAPI_H__
DECL|macro|__LINUX_CAPI_H__
mdefine_line|#define __LINUX_CAPI_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;linux/kernelcapi.h&gt;
macro_line|#endif
multiline_comment|/*&n; * CAPI_REGISTER&n; */
DECL|struct|capi_register_params
r_typedef
r_struct
id|capi_register_params
(brace
multiline_comment|/* CAPI_REGISTER */
DECL|member|level3cnt
id|__u32
id|level3cnt
suffix:semicolon
multiline_comment|/* No. of simulatneous user data connections */
DECL|member|datablkcnt
id|__u32
id|datablkcnt
suffix:semicolon
multiline_comment|/* No. of buffered data messages */
DECL|member|datablklen
id|__u32
id|datablklen
suffix:semicolon
multiline_comment|/* Size of buffered data messages */
DECL|typedef|capi_register_params
)brace
id|capi_register_params
suffix:semicolon
DECL|macro|CAPI_REGISTER
mdefine_line|#define&t;CAPI_REGISTER&t;_IOW(&squot;C&squot;,0x01,struct capi_register_params)
multiline_comment|/*&n; * CAPI_GET_MANUFACTURER&n; */
DECL|macro|CAPI_MANUFACTURER_LEN
mdefine_line|#define CAPI_MANUFACTURER_LEN&t;&t;64
DECL|macro|CAPI_GET_MANUFACTURER
mdefine_line|#define&t;CAPI_GET_MANUFACTURER&t;_IOWR(&squot;C&squot;,0x06,CAPI_MANUFACTURER_LEN)
multiline_comment|/*&n; * CAPI_GET_VERSION&n; */
DECL|struct|capi_version
r_typedef
r_struct
id|capi_version
(brace
DECL|member|majorversion
id|__u32
id|majorversion
suffix:semicolon
DECL|member|minorversion
id|__u32
id|minorversion
suffix:semicolon
DECL|member|majormanuversion
id|__u32
id|majormanuversion
suffix:semicolon
DECL|member|minormanuversion
id|__u32
id|minormanuversion
suffix:semicolon
DECL|typedef|capi_version
)brace
id|capi_version
suffix:semicolon
DECL|macro|CAPI_GET_VERSION
mdefine_line|#define CAPI_GET_VERSION&t;_IOWR(&squot;C&squot;,0x07,struct capi_version)
multiline_comment|/*&n; * CAPI_GET_SERIAL&n; */
DECL|macro|CAPI_SERIAL_LEN
mdefine_line|#define CAPI_SERIAL_LEN&t;&t;8
DECL|macro|CAPI_GET_SERIAL
mdefine_line|#define CAPI_GET_SERIAL&t;&t;_IOWR(&squot;C&squot;,0x08, CAPI_SERIAL_LEN)
multiline_comment|/*&n; * CAPI_GET_PROFILE&n; */
DECL|struct|capi_profile
r_typedef
r_struct
id|capi_profile
(brace
DECL|member|ncontroller
id|__u16
id|ncontroller
suffix:semicolon
multiline_comment|/* number of installed controller */
DECL|member|nbchannel
id|__u16
id|nbchannel
suffix:semicolon
multiline_comment|/* number of B-Channels */
DECL|member|goptions
id|__u32
id|goptions
suffix:semicolon
multiline_comment|/* global options */
DECL|member|support1
id|__u32
id|support1
suffix:semicolon
multiline_comment|/* B1 protocols support */
DECL|member|support2
id|__u32
id|support2
suffix:semicolon
multiline_comment|/* B2 protocols support */
DECL|member|support3
id|__u32
id|support3
suffix:semicolon
multiline_comment|/* B3 protocols support */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|manu
id|__u32
id|manu
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* manufacturer specific information */
DECL|typedef|capi_profile
)brace
id|capi_profile
suffix:semicolon
DECL|macro|CAPI_GET_PROFILE
mdefine_line|#define CAPI_GET_PROFILE&t;_IOWR(&squot;C&squot;,0x09,struct capi_profile)
DECL|struct|capi_manufacturer_cmd
r_typedef
r_struct
id|capi_manufacturer_cmd
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|typedef|capi_manufacturer_cmd
)brace
id|capi_manufacturer_cmd
suffix:semicolon
multiline_comment|/*&n; * CAPI_MANUFACTURER_CMD&n; */
DECL|macro|CAPI_MANUFACTURER_CMD
mdefine_line|#define CAPI_MANUFACTURER_CMD&t;_IOWR(&squot;C&squot;,0x20, struct capi_manufacturer_cmd)
multiline_comment|/*&n; * CAPI_GET_ERRCODE&n; * capi errcode is set, * if read, write, or ioctl returns EIO,&n; * ioctl returns errcode directly, and in arg, if != 0&n; */
DECL|macro|CAPI_GET_ERRCODE
mdefine_line|#define CAPI_GET_ERRCODE&t;_IOR(&squot;C&squot;,0x21, __u16)
multiline_comment|/*&n; * CAPI_INSTALLED&n; */
DECL|macro|CAPI_INSTALLED
mdefine_line|#define CAPI_INSTALLED&t;&t;_IOR(&squot;C&squot;,0x22, __u16)
multiline_comment|/*&n; * member contr is input for&n; * CAPI_GET_MANUFACTURER, CAPI_VERSION, CAPI_GET_SERIAL&n; * and CAPI_GET_PROFILE&n; */
DECL|union|capi_ioctl_struct
r_typedef
r_union
id|capi_ioctl_struct
(brace
DECL|member|contr
id|__u32
id|contr
suffix:semicolon
DECL|member|rparams
id|capi_register_params
id|rparams
suffix:semicolon
DECL|member|manufacturer
id|__u8
id|manufacturer
(braket
id|CAPI_MANUFACTURER_LEN
)braket
suffix:semicolon
DECL|member|version
id|capi_version
id|version
suffix:semicolon
DECL|member|serial
id|__u8
id|serial
(braket
id|CAPI_SERIAL_LEN
)braket
suffix:semicolon
DECL|member|profile
id|capi_profile
id|profile
suffix:semicolon
DECL|member|cmd
id|capi_manufacturer_cmd
id|cmd
suffix:semicolon
DECL|member|errcode
id|__u16
id|errcode
suffix:semicolon
DECL|typedef|capi_ioctl_struct
)brace
id|capi_ioctl_struct
suffix:semicolon
multiline_comment|/*&n; * Middleware extension&n; */
DECL|macro|CAPIFLAG_HIGHJACKING
mdefine_line|#define CAPIFLAG_HIGHJACKING&t;0x0001
DECL|macro|CAPI_GET_FLAGS
mdefine_line|#define CAPI_GET_FLAGS&t;&t;_IOR(&squot;C&squot;,0x23, unsigned)
DECL|macro|CAPI_SET_FLAGS
mdefine_line|#define CAPI_SET_FLAGS&t;&t;_IOR(&squot;C&squot;,0x24, unsigned)
DECL|macro|CAPI_CLR_FLAGS
mdefine_line|#define CAPI_CLR_FLAGS&t;&t;_IOR(&squot;C&squot;,0x25, unsigned)
DECL|macro|CAPI_NCCI_OPENCOUNT
mdefine_line|#define CAPI_NCCI_OPENCOUNT&t;_IOR(&squot;C&squot;,0x26, unsigned)
DECL|macro|CAPI_NCCI_GETUNIT
mdefine_line|#define CAPI_NCCI_GETUNIT&t;_IOR(&squot;C&squot;,0x27, unsigned)
macro_line|#endif&t;&t;&t;&t;/* __LINUX_CAPI_H__ */
eof
