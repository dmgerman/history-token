multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_WAR_H
DECL|macro|_ASM_SN_WAR_H
mdefine_line|#define _ASM_SN_WAR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined (CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
macro_line|#include &lt;asm/sn/sn1/war.h&gt;
macro_line|#endif
macro_line|#endif /* _ASM_SN_WAR_H */
eof
