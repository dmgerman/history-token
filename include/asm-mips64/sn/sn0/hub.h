multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SN_SN0_HUB_H
DECL|macro|_ASM_SN_SN0_HUB_H
mdefine_line|#define _ASM_SN_SN0_HUB_H
multiline_comment|/* The secret password; used to release protection */
DECL|macro|HUB_PASSWORD
mdefine_line|#define HUB_PASSWORD&t;&t;0x53474972756c6573ull
DECL|macro|CHIPID_HUB
mdefine_line|#define CHIPID_HUB&t;&t;0
DECL|macro|CHIPID_ROUTER
mdefine_line|#define CHIPID_ROUTER&t;&t;1
DECL|macro|HUB_REV_1_0
mdefine_line|#define HUB_REV_1_0&t;&t;1
DECL|macro|HUB_REV_2_0
mdefine_line|#define HUB_REV_2_0&t;&t;2
DECL|macro|HUB_REV_2_1
mdefine_line|#define HUB_REV_2_1&t;&t;3
DECL|macro|HUB_REV_2_2
mdefine_line|#define HUB_REV_2_2&t;&t;4
DECL|macro|HUB_REV_2_3
mdefine_line|#define HUB_REV_2_3             5
DECL|macro|HUB_REV_2_4
mdefine_line|#define HUB_REV_2_4             6
DECL|macro|MAX_HUB_PATH
mdefine_line|#define MAX_HUB_PATH&t;&t;80
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubpi.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubmd.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubio.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubni.h&gt;
singleline_comment|//#include &lt;asm/sn/sn0/hubcore.h&gt;
macro_line|#ifdef SABLE
DECL|macro|IP27_NO_HUBUART_INT
mdefine_line|#define IP27_NO_HUBUART_INT&t;1
macro_line|#endif
multiline_comment|/* Translation of uncached attributes */
DECL|macro|UATTR_HSPEC
mdefine_line|#define&t;UATTR_HSPEC&t;0
DECL|macro|UATTR_IO
mdefine_line|#define&t;UATTR_IO&t;1
DECL|macro|UATTR_MSPEC
mdefine_line|#define&t;UATTR_MSPEC&t;2
DECL|macro|UATTR_UNCAC
mdefine_line|#define&t;UATTR_UNCAC&t;3
macro_line|#endif /* _ASM_SN_SN0_HUB_H */
eof
