multiline_comment|/*&n; * Phase5 CybervisionPPC (TVP4020) definitions for the Permedia2 framebuffer&n; * driver.&n; *&n; * Copyright (c) 1998-1999 Ilario Nardinocchi (nardinoc@CS.UniBO.IT)&n; * --------------------------------------------------------------------------&n; * $Id: cvisionppc.h,v 1.8 1999/01/28 13:18:07 illo Exp $&n; * --------------------------------------------------------------------------&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef CVISIONPPC_H
DECL|macro|CVISIONPPC_H
mdefine_line|#define CVISIONPPC_H
macro_line|#ifndef PM2FB_H
macro_line|#include &quot;pm2fb.h&quot;
macro_line|#endif
DECL|struct|cvppc_par
r_struct
id|cvppc_par
(brace
DECL|member|pci_config
r_int
r_char
op_star
id|pci_config
suffix:semicolon
DECL|member|pci_bridge
r_int
r_char
op_star
id|pci_bridge
suffix:semicolon
DECL|member|user_flags
id|u32
id|user_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CSPPC_PCI_BRIDGE
mdefine_line|#define CSPPC_PCI_BRIDGE&t;&t;0xfffe0000
DECL|macro|CSPPC_BRIDGE_ENDIAN
mdefine_line|#define CSPPC_BRIDGE_ENDIAN&t;&t;0x0000
DECL|macro|CSPPC_BRIDGE_INT
mdefine_line|#define CSPPC_BRIDGE_INT&t;&t;0x0010
DECL|macro|CVPPC_PCI_CONFIG
mdefine_line|#define&t;CVPPC_PCI_CONFIG&t;&t;0xfffc0000
DECL|macro|CVPPC_ROM_ADDRESS
mdefine_line|#define CVPPC_ROM_ADDRESS&t;&t;0xe2000001
DECL|macro|CVPPC_REGS_REGION
mdefine_line|#define CVPPC_REGS_REGION&t;&t;0xef000000
DECL|macro|CVPPC_FB_APERTURE_ONE
mdefine_line|#define CVPPC_FB_APERTURE_ONE&t;&t;0xe0000000
DECL|macro|CVPPC_FB_APERTURE_TWO
mdefine_line|#define CVPPC_FB_APERTURE_TWO&t;&t;0xe1000000
DECL|macro|CVPPC_FB_SIZE
mdefine_line|#define CVPPC_FB_SIZE&t;&t;&t;0x00800000
DECL|macro|CVPPC_MEM_CONFIG_OLD
mdefine_line|#define CVPPC_MEM_CONFIG_OLD&t;&t;0xed61fcaa&t;/* FIXME Fujitsu?? */
DECL|macro|CVPPC_MEM_CONFIG_NEW
mdefine_line|#define CVPPC_MEM_CONFIG_NEW&t;&t;0xed41c532&t;/* FIXME USA?? */
DECL|macro|CVPPC_MEMCLOCK
mdefine_line|#define CVPPC_MEMCLOCK&t;&t;&t;83000&t;&t;/* in KHz */
multiline_comment|/* CVPPC_BRIDGE_ENDIAN */
DECL|macro|CSPPCF_BRIDGE_BIG_ENDIAN
mdefine_line|#define CSPPCF_BRIDGE_BIG_ENDIAN&t;0x02
multiline_comment|/* CVPPC_BRIDGE_INT */
DECL|macro|CSPPCF_BRIDGE_ACTIVE_INT2
mdefine_line|#define CSPPCF_BRIDGE_ACTIVE_INT2&t;0x01
macro_line|#endif&t;/* CVISIONPPC_H */
multiline_comment|/*****************************************************************************&n; * That&squot;s all folks!&n; *****************************************************************************/
eof
