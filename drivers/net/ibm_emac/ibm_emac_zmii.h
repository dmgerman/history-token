multiline_comment|/*&n; * ocp_zmii.h&n; *&n; * Defines for the IBM ZMII bridge&n; *&n; *      Armin Kuster akuster@mvista.com&n; *      Dec, 2001&n; *&n; * Copyright 2001 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef _IBM_EMAC_ZMII_H_
DECL|macro|_IBM_EMAC_ZMII_H_
mdefine_line|#define _IBM_EMAC_ZMII_H_
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* ZMII bridge registers */
DECL|struct|zmii_regs
r_struct
id|zmii_regs
(brace
DECL|member|fer
id|u32
id|fer
suffix:semicolon
multiline_comment|/* Function enable reg */
DECL|member|ssr
id|u32
id|ssr
suffix:semicolon
multiline_comment|/* Speed select reg */
DECL|member|smiirs
id|u32
id|smiirs
suffix:semicolon
multiline_comment|/* SMII status reg */
)brace
suffix:semicolon
DECL|macro|ZMII_INPUTS
mdefine_line|#define ZMII_INPUTS&t;4
multiline_comment|/* ZMII device */
DECL|struct|ibm_ocp_zmii
r_struct
id|ibm_ocp_zmii
(brace
DECL|member|base
r_struct
id|zmii_regs
op_star
id|base
suffix:semicolon
DECL|member|mode
r_int
id|mode
(braket
id|ZMII_INPUTS
)braket
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* number of EMACs using this ZMII bridge */
)brace
suffix:semicolon
multiline_comment|/* Fuctional Enable Reg */
DECL|macro|ZMII_FER_MASK
mdefine_line|#define ZMII_FER_MASK(x)&t;(0xf0000000 &gt;&gt; (4*x))
DECL|macro|ZMII_MDI0
mdefine_line|#define ZMII_MDI0&t;0x80000000
DECL|macro|ZMII_SMII0
mdefine_line|#define ZMII_SMII0&t;0x40000000
DECL|macro|ZMII_RMII0
mdefine_line|#define ZMII_RMII0&t;0x20000000
DECL|macro|ZMII_MII0
mdefine_line|#define ZMII_MII0&t;0x10000000
DECL|macro|ZMII_MDI1
mdefine_line|#define ZMII_MDI1&t;0x08000000
DECL|macro|ZMII_SMII1
mdefine_line|#define ZMII_SMII1&t;0x04000000
DECL|macro|ZMII_RMII1
mdefine_line|#define ZMII_RMII1&t;0x02000000
DECL|macro|ZMII_MII1
mdefine_line|#define ZMII_MII1&t;0x01000000
DECL|macro|ZMII_MDI2
mdefine_line|#define ZMII_MDI2&t;0x00800000
DECL|macro|ZMII_SMII2
mdefine_line|#define ZMII_SMII2&t;0x00400000
DECL|macro|ZMII_RMII2
mdefine_line|#define ZMII_RMII2&t;0x00200000
DECL|macro|ZMII_MII2
mdefine_line|#define ZMII_MII2&t;0x00100000
DECL|macro|ZMII_MDI3
mdefine_line|#define ZMII_MDI3&t;0x00080000
DECL|macro|ZMII_SMII3
mdefine_line|#define ZMII_SMII3&t;0x00040000
DECL|macro|ZMII_RMII3
mdefine_line|#define ZMII_RMII3&t;0x00020000
DECL|macro|ZMII_MII3
mdefine_line|#define ZMII_MII3&t;0x00010000
multiline_comment|/* Speed Selection reg */
DECL|macro|ZMII_SCI0
mdefine_line|#define ZMII_SCI0&t;0x40000000
DECL|macro|ZMII_FSS0
mdefine_line|#define ZMII_FSS0&t;0x20000000
DECL|macro|ZMII_SP0
mdefine_line|#define ZMII_SP0&t;0x10000000
DECL|macro|ZMII_SCI1
mdefine_line|#define ZMII_SCI1&t;0x04000000
DECL|macro|ZMII_FSS1
mdefine_line|#define ZMII_FSS1&t;0x02000000
DECL|macro|ZMII_SP1
mdefine_line|#define ZMII_SP1&t;0x01000000
DECL|macro|ZMII_SCI2
mdefine_line|#define ZMII_SCI2&t;0x00400000
DECL|macro|ZMII_FSS2
mdefine_line|#define ZMII_FSS2&t;0x00200000
DECL|macro|ZMII_SP2
mdefine_line|#define ZMII_SP2&t;0x00100000
DECL|macro|ZMII_SCI3
mdefine_line|#define ZMII_SCI3&t;0x00040000
DECL|macro|ZMII_FSS3
mdefine_line|#define ZMII_FSS3&t;0x00020000
DECL|macro|ZMII_SP3
mdefine_line|#define ZMII_SP3&t;0x00010000
DECL|macro|ZMII_MII0_100MB
mdefine_line|#define ZMII_MII0_100MB&t;ZMII_SP0
DECL|macro|ZMII_MII0_10MB
mdefine_line|#define ZMII_MII0_10MB&t;~ZMII_SP0
DECL|macro|ZMII_MII1_100MB
mdefine_line|#define ZMII_MII1_100MB&t;ZMII_SP1
DECL|macro|ZMII_MII1_10MB
mdefine_line|#define ZMII_MII1_10MB&t;~ZMII_SP1
DECL|macro|ZMII_MII2_100MB
mdefine_line|#define ZMII_MII2_100MB&t;ZMII_SP2
DECL|macro|ZMII_MII2_10MB
mdefine_line|#define ZMII_MII2_10MB&t;~ZMII_SP2
DECL|macro|ZMII_MII3_100MB
mdefine_line|#define ZMII_MII3_100MB&t;ZMII_SP3
DECL|macro|ZMII_MII3_10MB
mdefine_line|#define ZMII_MII3_10MB&t;~ZMII_SP3
multiline_comment|/* SMII Status reg */
DECL|macro|ZMII_STS0
mdefine_line|#define ZMII_STS0 0xFF000000&t;/* EMAC0 smii status mask */
DECL|macro|ZMII_STS1
mdefine_line|#define ZMII_STS1 0x00FF0000&t;/* EMAC1 smii status mask */
DECL|macro|SMII
mdefine_line|#define SMII&t;0
DECL|macro|RMII
mdefine_line|#define RMII&t;1
DECL|macro|MII
mdefine_line|#define MII&t;2
DECL|macro|MDI
mdefine_line|#define MDI&t;3
macro_line|#endif&t;&t;&t;&t;/* _IBM_EMAC_ZMII_H_ */
eof
