multiline_comment|/*&n; * arch/ppc/platforms/mpc8555_cds.h&n; *&n; * MPC8555CDS board definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_MPC8555CDS_H__
DECL|macro|__MACH_MPC8555CDS_H__
mdefine_line|#define __MACH_MPC8555CDS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;syslib/ppc85xx_setup.h&gt;
macro_line|#include &lt;platforms/85xx/mpc85xx_cds_common.h&gt;
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;(CCSRBAR + MPC85xx_CPM_OFFSET)
macro_line|#endif /* __MACH_MPC8555CDS_H__ */
eof
