multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_BEDROCK_H
DECL|macro|_ASM_IA64_SN_SN1_BEDROCK_H
mdefine_line|#define _ASM_IA64_SN_SN1_BEDROCK_H
multiline_comment|/* The secret password; used to release protection */
DECL|macro|HUB_PASSWORD
mdefine_line|#define HUB_PASSWORD&t;&t;0x53474972756c6573ull
DECL|macro|CHIPID_HUB
mdefine_line|#define CHIPID_HUB&t;&t;0x3012
DECL|macro|CHIPID_ROUTER
mdefine_line|#define CHIPID_ROUTER&t;&t;0x3017
DECL|macro|BEDROCK_REV_1_0
mdefine_line|#define BEDROCK_REV_1_0&t;&t;1
DECL|macro|BEDROCK_REV_1_1
mdefine_line|#define BEDROCK_REV_1_1&t;&t;2
DECL|macro|MAX_HUB_PATH
mdefine_line|#define MAX_HUB_PATH&t;&t;80
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/sn1/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubpi.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubmd.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubio.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubni.h&gt;
macro_line|#include &lt;asm/sn/sn1/hublb.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubxb.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubpi_next.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubmd_next.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubio_next.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubni_next.h&gt;
macro_line|#include &lt;asm/sn/sn1/hublb_next.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubxb_next.h&gt;
multiline_comment|/* Translation of uncached attributes */
DECL|macro|UATTR_HSPEC
mdefine_line|#define&t;UATTR_HSPEC&t;0
DECL|macro|UATTR_IO
mdefine_line|#define&t;UATTR_IO&t;1
DECL|macro|UATTR_MSPEC
mdefine_line|#define&t;UATTR_MSPEC&t;2
DECL|macro|UATTR_UNCAC
mdefine_line|#define&t;UATTR_UNCAC&t;3
macro_line|#if __ASSEMBLY__
multiline_comment|/*&n; * Get nasid into register, r (uses at)&n; */
DECL|macro|GET_NASID_ASM
mdefine_line|#define GET_NASID_ASM(r)&t;&t;&t;&t;&bslash;&n;&t;dli&t;r, LOCAL_HUB_ADDR(LB_REV_ID);&t;&bslash;&n;&t;ld&t;r, (r);&t;&t;&t;&t;&t;&bslash;&n;&t;and&t;r, LRI_NODEID_MASK;&t;&t;&t;&bslash;&n;&t;dsrl&t;r, LRI_NODEID_SHFT
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
multiline_comment|/* hub-as-widget iograph info, labelled by INFO_LBL_XWIDGET */
DECL|typedef|v_hub_t
r_typedef
r_struct
id|v_hub_s
op_star
id|v_hub_t
suffix:semicolon
DECL|typedef|rtc_time_t
r_typedef
r_uint64
id|rtc_time_t
suffix:semicolon
r_struct
id|nodepda_s
suffix:semicolon
r_int
id|hub_check_pci_equiv
c_func
(paren
r_void
op_star
id|addra
comma
r_void
op_star
id|addrb
)paren
suffix:semicolon
r_void
id|capture_hub_stats
c_func
(paren
id|cnodeid_t
comma
r_struct
id|nodepda_s
op_star
)paren
suffix:semicolon
r_void
id|init_hub_stats
c_func
(paren
id|cnodeid_t
comma
r_struct
id|nodepda_s
op_star
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_SN_SN1_BEDROCK_H */
eof
