multiline_comment|/*&n; * arch/ppc/platforms/cpc710.h&n; * &n; * Definitions for the IBM CPC710 PCI Host Bridge&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __PPC_PLATFORMS_CPC710_H
DECL|macro|__PPC_PLATFORMS_CPC710_H
mdefine_line|#define __PPC_PLATFORMS_CPC710_H
multiline_comment|/* General bridge and memory controller registers */
DECL|macro|PIDR
mdefine_line|#define PIDR&t;0xff000008
DECL|macro|CNFR
mdefine_line|#define&t;CNFR&t;0xff00000c
DECL|macro|RSTR
mdefine_line|#define&t;RSTR&t;0xff000010
DECL|macro|UCTL
mdefine_line|#define UCTL&t;0xff001000
DECL|macro|MPSR
mdefine_line|#define&t;MPSR&t;0xff001010
DECL|macro|SIOC
mdefine_line|#define&t;SIOC&t;0xff001020
DECL|macro|ABCNTL
mdefine_line|#define&t;ABCNTL&t;0xff001030
DECL|macro|SRST
mdefine_line|#define SRST&t;0xff001040
DECL|macro|ERRC
mdefine_line|#define&t;ERRC&t;0xff001050
DECL|macro|SESR
mdefine_line|#define&t;SESR&t;0xff001060
DECL|macro|SEAR
mdefine_line|#define&t;SEAR&t;0xff001070
DECL|macro|PGCHP
mdefine_line|#define&t;PGCHP&t;0xff001100
DECL|macro|GPDIR
mdefine_line|#define&t;GPDIR&t;0xff001130
DECL|macro|ATAS
mdefine_line|#define&t;ATAS&t;0xff001160
DECL|macro|AVDG
mdefine_line|#define&t;AVDG&t;0xff001170
DECL|macro|MCCR
mdefine_line|#define&t;MCCR&t;0xff001200
DECL|macro|MESR
mdefine_line|#define&t;MESR&t;0xff001220
DECL|macro|MEAR
mdefine_line|#define&t;MEAR&t;0xff001230
DECL|macro|MCER0
mdefine_line|#define&t;MCER0&t;0xff001300
DECL|macro|MCER1
mdefine_line|#define&t;MCER1&t;0xff001310
DECL|macro|MCER2
mdefine_line|#define&t;MCER2&t;0xff001320
DECL|macro|MCER3
mdefine_line|#define&t;MCER3&t;0xff001330
DECL|macro|MCER4
mdefine_line|#define&t;MCER4&t;0xff001340
DECL|macro|MCER5
mdefine_line|#define&t;MCER5&t;0xff001350
DECL|macro|MCER6
mdefine_line|#define&t;MCER6&t;0xff001360
DECL|macro|MCER7
mdefine_line|#define&t;MCER7&t;0xff001370
multiline_comment|/*&n; * PCI32/64 configuration registers&n; * Given as offsets from their&n; * respective physical segment BAR&n; */
DECL|macro|PIBAR
mdefine_line|#define PIBAR&t;0x000f7800
DECL|macro|PMBAR
mdefine_line|#define PMBAR&t;0x000f7810
DECL|macro|MSIZE
mdefine_line|#define MSIZE&t;0x000f7f40
DECL|macro|IOSIZE
mdefine_line|#define IOSIZE&t;0x000f7f60
DECL|macro|SMBAR
mdefine_line|#define SMBAR&t;0x000f7f80
DECL|macro|SIBAR
mdefine_line|#define SIBAR&t;0x000f7fc0
DECL|macro|PSSIZE
mdefine_line|#define PSSIZE&t;0x000f8100
DECL|macro|PPSIZE
mdefine_line|#define PPSIZE&t;0x000f8110
DECL|macro|BARPS
mdefine_line|#define BARPS&t;0x000f8120
DECL|macro|BARPP
mdefine_line|#define BARPP&t;0x000f8130
DECL|macro|PSBAR
mdefine_line|#define PSBAR&t;0x000f8140
DECL|macro|PPBAR
mdefine_line|#define PPBAR&t;0x000f8150
multiline_comment|/* System standard configuration registers space */
DECL|macro|DCR
mdefine_line|#define&t;DCR&t;0xff200000
DECL|macro|DID
mdefine_line|#define&t;DID&t;0xff200004
DECL|macro|BAR
mdefine_line|#define&t;BAR&t;0xff200018
multiline_comment|/* Device specific configuration space */
DECL|macro|PCIENB
mdefine_line|#define&t;PCIENB&t;0xff201000
multiline_comment|/* Configuration space registers */
DECL|macro|CPC710_BUS_NUMBER
mdefine_line|#define CPC710_BUS_NUMBER&t;0x40
DECL|macro|CPC710_SUB_BUS_NUMBER
mdefine_line|#define CPC710_SUB_BUS_NUMBER&t;0x41
macro_line|#endif /* __PPC_PLATFORMS_CPC710_H */
eof
