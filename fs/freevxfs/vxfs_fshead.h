multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_FSHEAD_H_
DECL|macro|_VXFS_FSHEAD_H_
mdefine_line|#define _VXFS_FSHEAD_H_
macro_line|#ident &quot;$Id: vxfs_fshead.h,v 1.5 2001/04/24 19:28:36 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - fileset header structures.&n; *&n; * This file contains the physical structure of the VxFS&n; * fileset header.&n; */
multiline_comment|/*&n; * Fileset header &n; */
DECL|struct|vxfs_fsh
r_struct
id|vxfs_fsh
(brace
DECL|member|fsh_version
id|u_int32_t
id|fsh_version
suffix:semicolon
multiline_comment|/* Fileset header version */
DECL|member|fsh_fsindex
id|u_int32_t
id|fsh_fsindex
suffix:semicolon
DECL|member|fsh_time
id|u_int32_t
id|fsh_time
suffix:semicolon
DECL|member|fsh_utime
id|u_int32_t
id|fsh_utime
suffix:semicolon
DECL|member|fsh_extop
id|u_int32_t
id|fsh_extop
suffix:semicolon
DECL|member|fsh_ninodes
id|vx_ino_t
id|fsh_ninodes
suffix:semicolon
DECL|member|fsh_nau
id|u_int32_t
id|fsh_nau
suffix:semicolon
DECL|member|fsh_old_ilesize
id|u_int32_t
id|fsh_old_ilesize
suffix:semicolon
DECL|member|fsh_dflags
id|u_int32_t
id|fsh_dflags
suffix:semicolon
DECL|member|fsh_quota
id|u_int32_t
id|fsh_quota
suffix:semicolon
DECL|member|fsh_maxinode
id|vx_ino_t
id|fsh_maxinode
suffix:semicolon
DECL|member|fsh_iauino
id|vx_ino_t
id|fsh_iauino
suffix:semicolon
DECL|member|fsh_ilistino
id|vx_ino_t
id|fsh_ilistino
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fsh_lctino
id|vx_ino_t
id|fsh_lctino
suffix:semicolon
multiline_comment|/*&n;&t; * Slightly more fields follow, but they&n;&t; *  a) are not of any interested for us, and&n;&t; *  b) differ much in different vxfs versions/ports&n;&t; */
)brace
suffix:semicolon
macro_line|#endif /* _VXFS_FSHEAD_H_ */
eof
