multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN_PRIVATE_H
DECL|macro|_ASM_IA64_SN_SN_PRIVATE_H
mdefine_line|#define _ASM_IA64_SN_SN_PRIVATE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk_private.h&gt;
macro_line|#if defined(CONFIG_IA64_SGI_SN1)
macro_line|#include &lt;asm/sn/sn1/sn_private.h&gt;
macro_line|#elif defined(CONFIG_IA64_SGI_SN2)
macro_line|#include &lt;asm/sn/sn2/sn_private.h&gt;
macro_line|#endif
macro_line|#endif /* _ASM_IA64_SN_SN_PRIVATE_H */
eof
