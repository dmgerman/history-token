multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file has definitions for the hub and snac interfaces.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SGI_SN_AGENT_H
DECL|macro|_ASM_SGI_SN_AGENT_H
mdefine_line|#define _ASM_SGI_SN_AGENT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
singleline_comment|//#include &lt;asm/sn/io.h&gt;
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
macro_line|#include &lt;asm/sn/sn1/bedrock.h&gt;
macro_line|#endif&t;/* CONFIG_SGI_IP35 */
multiline_comment|/*&n; * NIC register macros&n; */
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
DECL|macro|HUB_NIC_ADDR
mdefine_line|#define HUB_NIC_ADDR(_cpuid) &t;&t;&t;&t;&t;&t;   &bslash;&n;&t;REMOTE_HUB_ADDR(COMPACT_TO_NASID_NODEID(cputocnode(_cpuid)),       &bslash;&n;&t;&t;LB_MICROLAN_CTL)
macro_line|#endif
DECL|macro|SET_HUB_NIC
mdefine_line|#define SET_HUB_NIC(_my_cpuid, _val) &t;&t;&t;&t;  &t;   &bslash;&n;&t;(HUB_S(HUB_NIC_ADDR(_my_cpuid), (_val)))
DECL|macro|SET_MY_HUB_NIC
mdefine_line|#define SET_MY_HUB_NIC(_v) &t;&t;&t;&t;&t;           &bslash;&n;&t;SET_HUB_NIC(cpuid(), (_v))
DECL|macro|GET_HUB_NIC
mdefine_line|#define GET_HUB_NIC(_my_cpuid) &t;&t;&t;&t;&t;&t;   &bslash;&n;&t;(HUB_L(HUB_NIC_ADDR(_my_cpuid)))
DECL|macro|GET_MY_HUB_NIC
mdefine_line|#define GET_MY_HUB_NIC() &t;&t;&t;&t;&t;&t;   &bslash;&n;&t;GET_HUB_NIC(cpuid())
macro_line|#endif /* _ASM_SGI_SN_AGENT_H */
eof
