multiline_comment|/*&n; * arch/ppc/platforms/mpc8560_ads.h&n; *&n; * MPC8540ADS board definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_MPC8560ADS_H
DECL|macro|__MACH_MPC8560ADS_H
mdefine_line|#define __MACH_MPC8560ADS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;syslib/ppc85xx_setup.h&gt;
macro_line|#include &lt;platforms/85xx/mpc85xx_ads_common.h&gt;
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;(CCSRBAR + MPC85xx_CPM_OFFSET)
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;MPC85xx_IRQ_EXT7
macro_line|#endif&t;&t;&t;&t;/* __MACH_MPC8560ADS_H */
eof
