multiline_comment|/*&n; * arch/ppc/syslib/mpc52xx_pci.h&n; *&n; * PCI Include file the Freescale MPC52xx embedded cpu chips&n; *&n; *&n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Inspired from code written by Dale Farnsworth &lt;dfarnsworth@mvista.com&gt;&n; * for the 2.4 kernel.&n; *&n; * Copyright (C) 2004 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; * Copyright (C) 2003 MontaVista, Software, Inc.&n; *&n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#ifndef __SYSLIB_MPC52xx_PCI_H__
DECL|macro|__SYSLIB_MPC52xx_PCI_H__
mdefine_line|#define __SYSLIB_MPC52xx_PCI_H__
multiline_comment|/* ======================================================================== */
multiline_comment|/* PCI windows config                                                       */
multiline_comment|/* ======================================================================== */
multiline_comment|/*&n; * Master windows : MPC52xx -&gt; PCI&n; *&n; *  0x80000000 -&gt; 0x9FFFFFFF       PCI Mem prefetchable          IW0BTAR&n; *  0xA0000000 -&gt; 0xAFFFFFFF       PCI Mem                       IW1BTAR&n; *  0xB0000000 -&gt; 0xB0FFFFFF       PCI IO                        IW2BTAR&n; *&n; * Slave windows  : PCI -&gt; MPC52xx&n; *&n; *  0xF0000000 -&gt; 0xF003FFFF       MPC52xx MBAR                  TBATR0&n; *  0x00000000 -&gt; 0x3FFFFFFF       MPC52xx local memory          TBATR1&n; */
DECL|macro|MPC52xx_PCI_MEM_OFFSET
mdefine_line|#define MPC52xx_PCI_MEM_OFFSET &t;0x00000000&t;/* Offset for MEM MMIO */
DECL|macro|MPC52xx_PCI_MEM_START
mdefine_line|#define MPC52xx_PCI_MEM_START&t;0x80000000
DECL|macro|MPC52xx_PCI_MEM_SIZE
mdefine_line|#define MPC52xx_PCI_MEM_SIZE&t;0x20000000
DECL|macro|MPC52xx_PCI_MEM_STOP
mdefine_line|#define MPC52xx_PCI_MEM_STOP&t;(MPC52xx_PCI_MEM_START+MPC52xx_PCI_MEM_SIZE-1)
DECL|macro|MPC52xx_PCI_MMIO_START
mdefine_line|#define MPC52xx_PCI_MMIO_START&t;0xa0000000
DECL|macro|MPC52xx_PCI_MMIO_SIZE
mdefine_line|#define MPC52xx_PCI_MMIO_SIZE&t;0x10000000
DECL|macro|MPC52xx_PCI_MMIO_STOP
mdefine_line|#define MPC52xx_PCI_MMIO_STOP&t;(MPC52xx_PCI_MMIO_START+MPC52xx_PCI_MMIO_SIZE-1)
DECL|macro|MPC52xx_PCI_IO_BASE
mdefine_line|#define MPC52xx_PCI_IO_BASE&t;0xb0000000
DECL|macro|MPC52xx_PCI_IO_START
mdefine_line|#define MPC52xx_PCI_IO_START&t;0x00000000
DECL|macro|MPC52xx_PCI_IO_SIZE
mdefine_line|#define MPC52xx_PCI_IO_SIZE&t;0x01000000
DECL|macro|MPC52xx_PCI_IO_STOP
mdefine_line|#define MPC52xx_PCI_IO_STOP&t;(MPC52xx_PCI_IO_START+MPC52xx_PCI_IO_SIZE-1)
DECL|macro|MPC52xx_PCI_TARGET_IO
mdefine_line|#define MPC52xx_PCI_TARGET_IO&t;MPC52xx_MBAR
DECL|macro|MPC52xx_PCI_TARGET_MEM
mdefine_line|#define MPC52xx_PCI_TARGET_MEM&t;0x00000000
multiline_comment|/* ======================================================================== */
multiline_comment|/* Structures mapping &amp; Defines for PCI Unit                                */
multiline_comment|/* ======================================================================== */
DECL|macro|MPC52xx_PCI_GSCR_BM
mdefine_line|#define MPC52xx_PCI_GSCR_BM&t;&t;0x40000000
DECL|macro|MPC52xx_PCI_GSCR_PE
mdefine_line|#define MPC52xx_PCI_GSCR_PE&t;&t;0x20000000
DECL|macro|MPC52xx_PCI_GSCR_SE
mdefine_line|#define MPC52xx_PCI_GSCR_SE&t;&t;0x10000000
DECL|macro|MPC52xx_PCI_GSCR_XLB2PCI_MASK
mdefine_line|#define MPC52xx_PCI_GSCR_XLB2PCI_MASK&t;0x07000000
DECL|macro|MPC52xx_PCI_GSCR_XLB2PCI_SHIFT
mdefine_line|#define MPC52xx_PCI_GSCR_XLB2PCI_SHIFT&t;24
DECL|macro|MPC52xx_PCI_GSCR_IPG2PCI_MASK
mdefine_line|#define MPC52xx_PCI_GSCR_IPG2PCI_MASK&t;0x00070000
DECL|macro|MPC52xx_PCI_GSCR_IPG2PCI_SHIFT
mdefine_line|#define MPC52xx_PCI_GSCR_IPG2PCI_SHIFT&t;16
DECL|macro|MPC52xx_PCI_GSCR_BME
mdefine_line|#define MPC52xx_PCI_GSCR_BME&t;&t;0x00004000
DECL|macro|MPC52xx_PCI_GSCR_PEE
mdefine_line|#define MPC52xx_PCI_GSCR_PEE&t;&t;0x00002000
DECL|macro|MPC52xx_PCI_GSCR_SEE
mdefine_line|#define MPC52xx_PCI_GSCR_SEE&t;&t;0x00001000
DECL|macro|MPC52xx_PCI_GSCR_PR
mdefine_line|#define MPC52xx_PCI_GSCR_PR&t;&t;0x00000001
DECL|macro|MPC52xx_PCI_IWBTAR_TRANSLATION
mdefine_line|#define MPC52xx_PCI_IWBTAR_TRANSLATION(proc_ad,pci_ad,size)&t;  &bslash;&n;&t;&t;( ( (proc_ad) &amp; 0xff000000 )&t;&t;&t;| &bslash;&n;&t;&t;  ( (((size) - 1) &gt;&gt; 8) &amp; 0x00ff0000 )&t;&t;| &bslash;&n;&t;&t;  ( ((pci_ad) &gt;&gt; 16) &amp; 0x0000ff00 ) )
DECL|macro|MPC52xx_PCI_IWCR_PACK
mdefine_line|#define MPC52xx_PCI_IWCR_PACK(win0,win1,win2)&t;(((win0) &lt;&lt; 24) | &bslash;&n;&t;&t;&t;&t;&t;&t; ((win1) &lt;&lt; 16) | &bslash;&n;&t;&t;&t;&t;&t;&t; ((win2) &lt;&lt;  8))
DECL|macro|MPC52xx_PCI_IWCR_DISABLE
mdefine_line|#define MPC52xx_PCI_IWCR_DISABLE&t;0x0
DECL|macro|MPC52xx_PCI_IWCR_ENABLE
mdefine_line|#define MPC52xx_PCI_IWCR_ENABLE&t;&t;0x1
DECL|macro|MPC52xx_PCI_IWCR_READ
mdefine_line|#define MPC52xx_PCI_IWCR_READ&t;&t;0x0
DECL|macro|MPC52xx_PCI_IWCR_READ_LINE
mdefine_line|#define MPC52xx_PCI_IWCR_READ_LINE&t;0x2
DECL|macro|MPC52xx_PCI_IWCR_READ_MULTI
mdefine_line|#define MPC52xx_PCI_IWCR_READ_MULTI&t;0x4
DECL|macro|MPC52xx_PCI_IWCR_MEM
mdefine_line|#define MPC52xx_PCI_IWCR_MEM&t;&t;0x0
DECL|macro|MPC52xx_PCI_IWCR_IO
mdefine_line|#define MPC52xx_PCI_IWCR_IO&t;&t;0x8
DECL|macro|MPC52xx_PCI_TCR_P
mdefine_line|#define MPC52xx_PCI_TCR_P&t;&t;0x01000000
DECL|macro|MPC52xx_PCI_TCR_LD
mdefine_line|#define MPC52xx_PCI_TCR_LD&t;&t;0x00010000
DECL|macro|MPC52xx_PCI_TBATR_DISABLE
mdefine_line|#define MPC52xx_PCI_TBATR_DISABLE&t;0x0
DECL|macro|MPC52xx_PCI_TBATR_ENABLE
mdefine_line|#define MPC52xx_PCI_TBATR_ENABLE&t;0x1
macro_line|#ifndef __ASSEMBLY__
DECL|struct|mpc52xx_pci
r_struct
id|mpc52xx_pci
(brace
DECL|member|idr
id|u32
id|idr
suffix:semicolon
multiline_comment|/* PCI + 0x00 */
DECL|member|scr
id|u32
id|scr
suffix:semicolon
multiline_comment|/* PCI + 0x04 */
DECL|member|ccrir
id|u32
id|ccrir
suffix:semicolon
multiline_comment|/* PCI + 0x08 */
DECL|member|cr1
id|u32
id|cr1
suffix:semicolon
multiline_comment|/* PCI + 0x0C */
DECL|member|bar0
id|u32
id|bar0
suffix:semicolon
multiline_comment|/* PCI + 0x10 */
DECL|member|bar1
id|u32
id|bar1
suffix:semicolon
multiline_comment|/* PCI + 0x14 */
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* PCI + 0x18 */
DECL|member|ccpr
id|u32
id|ccpr
suffix:semicolon
multiline_comment|/* PCI + 0x28 */
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* PCI + 0x2C */
DECL|member|erbar
id|u32
id|erbar
suffix:semicolon
multiline_comment|/* PCI + 0x30 */
DECL|member|cpr
id|u32
id|cpr
suffix:semicolon
multiline_comment|/* PCI + 0x34 */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI + 0x38 */
DECL|member|cr2
id|u32
id|cr2
suffix:semicolon
multiline_comment|/* PCI + 0x3C */
DECL|member|reserved3
id|u8
id|reserved3
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* PCI + 0x40 */
DECL|member|gscr
id|u32
id|gscr
suffix:semicolon
multiline_comment|/* PCI + 0x60 */
DECL|member|tbatr0
id|u32
id|tbatr0
suffix:semicolon
multiline_comment|/* PCI + 0x64 */
DECL|member|tbatr1
id|u32
id|tbatr1
suffix:semicolon
multiline_comment|/* PCI + 0x68 */
DECL|member|tcr
id|u32
id|tcr
suffix:semicolon
multiline_comment|/* PCI + 0x6C */
DECL|member|iw0btar
id|u32
id|iw0btar
suffix:semicolon
multiline_comment|/* PCI + 0x70 */
DECL|member|iw1btar
id|u32
id|iw1btar
suffix:semicolon
multiline_comment|/* PCI + 0x74 */
DECL|member|iw2btar
id|u32
id|iw2btar
suffix:semicolon
multiline_comment|/* PCI + 0x78 */
DECL|member|reserved4
id|u8
id|reserved4
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI + 0x7C */
DECL|member|iwcr
id|u32
id|iwcr
suffix:semicolon
multiline_comment|/* PCI + 0x80 */
DECL|member|icr
id|u32
id|icr
suffix:semicolon
multiline_comment|/* PCI + 0x84 */
DECL|member|isr
id|u32
id|isr
suffix:semicolon
multiline_comment|/* PCI + 0x88 */
DECL|member|arb
id|u32
id|arb
suffix:semicolon
multiline_comment|/* PCI + 0x8C */
DECL|member|reserved5
id|u8
id|reserved5
(braket
l_int|104
)braket
suffix:semicolon
multiline_comment|/* PCI + 0x90 */
DECL|member|car
id|u32
id|car
suffix:semicolon
multiline_comment|/* PCI + 0xF8 */
DECL|member|reserved6
id|u8
id|reserved6
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI + 0xFC */
)brace
suffix:semicolon
macro_line|#endif  /* __ASSEMBLY__ */
macro_line|#endif  /* __SYSLIB_MPC52xx_PCI_H__ */
eof
