multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_ROUTER_H
DECL|macro|_ASM_SN_ROUTER_H
mdefine_line|#define _ASM_SN_ROUTER_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if CONFIG_SGI_IP35 || CONFIG_IA64_SGI_SN1 || CONFIG_IA64_GENERIC
macro_line|#include &lt;asm/sn/sn1/router.h&gt;
macro_line|#endif
macro_line|#endif /* _ASM_SN_ROUTER_H */
eof
