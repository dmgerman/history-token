multiline_comment|/*&n; *  asm-ppc/hydra.h -- Mac I/O `Hydra&squot; definitions&n; *&n; *  Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is based on the following documentation:&n; *&n; *&t;Macintosh Technology in the Common Hardware Reference Platform&n; *&t;Apple Computer, Inc.&n; *&n; *&t;&#xfffd; Copyright 1995 Apple Computer, Inc. All rights reserved.&n; *&n; *  It&squot;s available online from http://chrp.apple.com/MacTech.pdf.&n; *  You can obtain paper copies of this book from computer bookstores or by&n; *  writing Morgan Kaufmann Publishers, Inc., 340 Pine Street, Sixth Floor, San&n; *  Francisco, CA 94104. Reference ISBN 1-55860-393-X.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _ASMPPC_HYDRA_H
DECL|macro|_ASMPPC_HYDRA_H
mdefine_line|#define _ASMPPC_HYDRA_H
macro_line|#ifdef __KERNEL__
DECL|struct|Hydra
r_struct
id|Hydra
(brace
multiline_comment|/* DBDMA Controller Register Space */
DECL|member|Pad1
r_char
id|Pad1
(braket
l_int|0x30
)braket
suffix:semicolon
DECL|member|CachePD
id|u_int
id|CachePD
suffix:semicolon
DECL|member|IDs
id|u_int
id|IDs
suffix:semicolon
DECL|member|Feature_Control
id|u_int
id|Feature_Control
suffix:semicolon
DECL|member|Pad2
r_char
id|Pad2
(braket
l_int|0x7fc4
)braket
suffix:semicolon
multiline_comment|/* DBDMA Channel Register Space */
DECL|member|SCSI_DMA
r_char
id|SCSI_DMA
(braket
l_int|0x100
)braket
suffix:semicolon
DECL|member|Pad3
r_char
id|Pad3
(braket
l_int|0x300
)braket
suffix:semicolon
DECL|member|SCCA_Tx_DMA
r_char
id|SCCA_Tx_DMA
(braket
l_int|0x100
)braket
suffix:semicolon
DECL|member|SCCA_Rx_DMA
r_char
id|SCCA_Rx_DMA
(braket
l_int|0x100
)braket
suffix:semicolon
DECL|member|SCCB_Tx_DMA
r_char
id|SCCB_Tx_DMA
(braket
l_int|0x100
)braket
suffix:semicolon
DECL|member|SCCB_Rx_DMA
r_char
id|SCCB_Rx_DMA
(braket
l_int|0x100
)braket
suffix:semicolon
DECL|member|Pad4
r_char
id|Pad4
(braket
l_int|0x7800
)braket
suffix:semicolon
multiline_comment|/* Device Register Space */
DECL|member|SCSI
r_char
id|SCSI
(braket
l_int|0x1000
)braket
suffix:semicolon
DECL|member|ADB
r_char
id|ADB
(braket
l_int|0x1000
)braket
suffix:semicolon
DECL|member|SCC_Legacy
r_char
id|SCC_Legacy
(braket
l_int|0x1000
)braket
suffix:semicolon
DECL|member|SCC
r_char
id|SCC
(braket
l_int|0x1000
)braket
suffix:semicolon
DECL|member|Pad9
r_char
id|Pad9
(braket
l_int|0x2000
)braket
suffix:semicolon
DECL|member|VIA
r_char
id|VIA
(braket
l_int|0x2000
)braket
suffix:semicolon
DECL|member|Pad10
r_char
id|Pad10
(braket
l_int|0x28000
)braket
suffix:semicolon
DECL|member|OpenPIC
r_char
id|OpenPIC
(braket
l_int|0x40000
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_volatile
r_struct
id|Hydra
op_star
id|Hydra
suffix:semicolon
multiline_comment|/*&n;     *  Feature Control Register&n;     */
DECL|macro|HYDRA_FC_SCC_CELL_EN
mdefine_line|#define HYDRA_FC_SCC_CELL_EN&t;0x00000001&t;/* Enable SCC Clock */
DECL|macro|HYDRA_FC_SCSI_CELL_EN
mdefine_line|#define HYDRA_FC_SCSI_CELL_EN&t;0x00000002&t;/* Enable SCSI Clock */
DECL|macro|HYDRA_FC_SCCA_ENABLE
mdefine_line|#define HYDRA_FC_SCCA_ENABLE&t;0x00000004&t;/* Enable SCC A Lines */
DECL|macro|HYDRA_FC_SCCB_ENABLE
mdefine_line|#define HYDRA_FC_SCCB_ENABLE&t;0x00000008&t;/* Enable SCC B Lines */
DECL|macro|HYDRA_FC_ARB_BYPASS
mdefine_line|#define HYDRA_FC_ARB_BYPASS&t;0x00000010&t;/* Bypass Internal Arbiter */
DECL|macro|HYDRA_FC_RESET_SCC
mdefine_line|#define HYDRA_FC_RESET_SCC&t;0x00000020&t;/* Reset SCC */
DECL|macro|HYDRA_FC_MPIC_ENABLE
mdefine_line|#define HYDRA_FC_MPIC_ENABLE&t;0x00000040&t;/* Enable OpenPIC */
DECL|macro|HYDRA_FC_SLOW_SCC_PCLK
mdefine_line|#define HYDRA_FC_SLOW_SCC_PCLK&t;0x00000080&t;/* 1=15.6672, 0=25 MHz */
DECL|macro|HYDRA_FC_MPIC_IS_MASTER
mdefine_line|#define HYDRA_FC_MPIC_IS_MASTER&t;0x00000100&t;/* OpenPIC Master Mode */
multiline_comment|/*&n;     *  OpenPIC Interrupt Sources&n;     */
DECL|macro|HYDRA_INT_SIO
mdefine_line|#define HYDRA_INT_SIO&t;&t;0
DECL|macro|HYDRA_INT_SCSI_DMA
mdefine_line|#define HYDRA_INT_SCSI_DMA&t;1
DECL|macro|HYDRA_INT_SCCA_TX_DMA
mdefine_line|#define HYDRA_INT_SCCA_TX_DMA&t;2
DECL|macro|HYDRA_INT_SCCA_RX_DMA
mdefine_line|#define HYDRA_INT_SCCA_RX_DMA&t;3
DECL|macro|HYDRA_INT_SCCB_TX_DMA
mdefine_line|#define HYDRA_INT_SCCB_TX_DMA&t;4
DECL|macro|HYDRA_INT_SCCB_RX_DMA
mdefine_line|#define HYDRA_INT_SCCB_RX_DMA&t;5
DECL|macro|HYDRA_INT_SCSI
mdefine_line|#define HYDRA_INT_SCSI&t;&t;6
DECL|macro|HYDRA_INT_SCCA
mdefine_line|#define HYDRA_INT_SCCA&t;&t;7
DECL|macro|HYDRA_INT_SCCB
mdefine_line|#define HYDRA_INT_SCCB&t;&t;8
DECL|macro|HYDRA_INT_VIA
mdefine_line|#define HYDRA_INT_VIA&t;&t;9
DECL|macro|HYDRA_INT_ADB
mdefine_line|#define HYDRA_INT_ADB&t;&t;10
DECL|macro|HYDRA_INT_ADB_NMI
mdefine_line|#define HYDRA_INT_ADB_NMI&t;11
DECL|macro|HYDRA_INT_EXT1
mdefine_line|#define HYDRA_INT_EXT1&t;&t;12&t;/* PCI IRQW */
DECL|macro|HYDRA_INT_EXT2
mdefine_line|#define HYDRA_INT_EXT2&t;&t;13&t;/* PCI IRQX */
DECL|macro|HYDRA_INT_EXT3
mdefine_line|#define HYDRA_INT_EXT3&t;&t;14&t;/* PCI IRQY */
DECL|macro|HYDRA_INT_EXT4
mdefine_line|#define HYDRA_INT_EXT4&t;&t;15&t;/* PCI IRQZ */
DECL|macro|HYDRA_INT_EXT5
mdefine_line|#define HYDRA_INT_EXT5&t;&t;16&t;/* IDE Primay/Secondary */
DECL|macro|HYDRA_INT_EXT6
mdefine_line|#define HYDRA_INT_EXT6&t;&t;17&t;/* IDE Secondary */
DECL|macro|HYDRA_INT_EXT7
mdefine_line|#define HYDRA_INT_EXT7&t;&t;18&t;/* Power Off Request */
DECL|macro|HYDRA_INT_SPARE
mdefine_line|#define HYDRA_INT_SPARE&t;&t;19
r_extern
r_int
id|hydra_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|macio_adb_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASMPPC_HYDRA_H */
eof
