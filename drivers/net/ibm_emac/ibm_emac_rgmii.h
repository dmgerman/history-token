multiline_comment|/*&n; * Defines for the IBM RGMII bridge&n; *&n; * Based on ocp_zmii.h/ibm_emac_zmii.h&n; * Armin Kuster akuster@mvista.com&n; *&n; * Copyright 2004 MontaVista Software, Inc.&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef _IBM_EMAC_RGMII_H_
DECL|macro|_IBM_EMAC_RGMII_H_
mdefine_line|#define _IBM_EMAC_RGMII_H_
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* RGMII bridge */
DECL|struct|rgmii_regs
r_typedef
r_struct
id|rgmii_regs
(brace
DECL|member|fer
id|u32
id|fer
suffix:semicolon
multiline_comment|/* Function enable register */
DECL|member|ssr
id|u32
id|ssr
suffix:semicolon
multiline_comment|/* Speed select register */
DECL|typedef|rgmii_t
)brace
id|rgmii_t
suffix:semicolon
DECL|macro|RGMII_INPUTS
mdefine_line|#define RGMII_INPUTS&t;&t;&t;4
multiline_comment|/* RGMII device */
DECL|struct|ibm_ocp_rgmii
r_struct
id|ibm_ocp_rgmii
(brace
DECL|member|base
r_struct
id|rgmii_regs
op_star
id|base
suffix:semicolon
DECL|member|mode
r_int
id|mode
(braket
id|RGMII_INPUTS
)braket
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* number of EMACs using this RGMII bridge */
)brace
suffix:semicolon
multiline_comment|/* Fuctional Enable Reg */
DECL|macro|RGMII_FER_MASK
mdefine_line|#define RGMII_FER_MASK(x)&t;&t;(0x00000007 &lt;&lt; (4*x))
DECL|macro|RGMII_RTBI
mdefine_line|#define RGMII_RTBI&t;&t;&t;0x00000004
DECL|macro|RGMII_RGMII
mdefine_line|#define RGMII_RGMII&t;&t;&t;0x00000005
DECL|macro|RGMII_TBI
mdefine_line|#define RGMII_TBI  &t;&t;&t;0x00000006
DECL|macro|RGMII_GMII
mdefine_line|#define RGMII_GMII &t;&t;&t;0x00000007
multiline_comment|/* Speed Selection reg */
DECL|macro|RGMII_SP2_100
mdefine_line|#define RGMII_SP2_100&t;0x00000002
DECL|macro|RGMII_SP2_1000
mdefine_line|#define RGMII_SP2_1000&t;0x00000004
DECL|macro|RGMII_SP3_100
mdefine_line|#define RGMII_SP3_100&t;0x00000200
DECL|macro|RGMII_SP3_1000
mdefine_line|#define RGMII_SP3_1000&t;0x00000400
DECL|macro|RGMII_MII2_SPDMASK
mdefine_line|#define RGMII_MII2_SPDMASK&t; 0x00000007
DECL|macro|RGMII_MII3_SPDMASK
mdefine_line|#define RGMII_MII3_SPDMASK&t; 0x00000700
DECL|macro|RGMII_MII2_100MB
mdefine_line|#define RGMII_MII2_100MB&t; RGMII_SP2_100 &amp; ~RGMII_SP2_1000
DECL|macro|RGMII_MII2_1000MB
mdefine_line|#define RGMII_MII2_1000MB &t; RGMII_SP2_1000 &amp; ~RGMII_SP2_100
DECL|macro|RGMII_MII2_10MB
mdefine_line|#define RGMII_MII2_10MB&t;&t; ~(RGMII_SP2_100 | RGMII_SP2_1000)
DECL|macro|RGMII_MII3_100MB
mdefine_line|#define RGMII_MII3_100MB&t; RGMII_SP3_100 &amp; ~RGMII_SP3_1000
DECL|macro|RGMII_MII3_1000MB
mdefine_line|#define RGMII_MII3_1000MB &t; RGMII_SP3_1000 &amp; ~RGMII_SP3_100
DECL|macro|RGMII_MII3_10MB
mdefine_line|#define RGMII_MII3_10MB&t;&t; ~(RGMII_SP3_100 | RGMII_SP3_1000)
DECL|macro|RTBI
mdefine_line|#define RTBI&t;&t;0
DECL|macro|RGMII
mdefine_line|#define RGMII&t;&t;1
DECL|macro|TBI
mdefine_line|#define TBI&t;&t;2
DECL|macro|GMII
mdefine_line|#define GMII&t;&t;3
macro_line|#endif&t;&t;&t;&t;/* _IBM_EMAC_RGMII_H_ */
eof
