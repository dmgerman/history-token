multiline_comment|/* &n; * Motion Eye video4linux driver for Sony Vaio PictureBook&n; *&n; * Copyright (C) 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * Copyright (C) 2000 Andrew Tridgell &lt;tridge@valinux.com&gt;&n; *&n; * Earlier work by Werner Almesberger, Paul `Rusty&squot; Russell and Paul Mackerras.&n; * &n; * Some parts borrowed from various video4linux drivers, especially&n; * bttv-driver.c and zoran.c, see original files for credits.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _MEYE_PRIV_H_
DECL|macro|_MEYE_PRIV_H_
mdefine_line|#define _MEYE_PRIV_H_
DECL|macro|MEYE_DRIVER_MAJORVERSION
mdefine_line|#define MEYE_DRIVER_MAJORVERSION&t;1
DECL|macro|MEYE_DRIVER_MINORVERSION
mdefine_line|#define MEYE_DRIVER_MINORVERSION&t;3
multiline_comment|/****************************************************************************/
multiline_comment|/* Motion JPEG chip registers                                               */
multiline_comment|/****************************************************************************/
multiline_comment|/* Motion JPEG chip PCI configuration registers */
DECL|macro|MCHIP_PCI_POWER_CSR
mdefine_line|#define MCHIP_PCI_POWER_CSR&t;&t;0x54
DECL|macro|MCHIP_PCI_MCORE_STATUS
mdefine_line|#define MCHIP_PCI_MCORE_STATUS&t;&t;0x60&t;/* see HIC_STATUS   */
DECL|macro|MCHIP_PCI_HOSTUSEREQ_SET
mdefine_line|#define MCHIP_PCI_HOSTUSEREQ_SET&t;0x64
DECL|macro|MCHIP_PCI_HOSTUSEREQ_CLR
mdefine_line|#define MCHIP_PCI_HOSTUSEREQ_CLR&t;0x68
DECL|macro|MCHIP_PCI_LOWPOWER_SET
mdefine_line|#define MCHIP_PCI_LOWPOWER_SET&t;&t;0x6c
DECL|macro|MCHIP_PCI_LOWPOWER_CLR
mdefine_line|#define MCHIP_PCI_LOWPOWER_CLR&t;&t;0x70
DECL|macro|MCHIP_PCI_SOFTRESET_SET
mdefine_line|#define MCHIP_PCI_SOFTRESET_SET&t;&t;0x74
multiline_comment|/* Motion JPEG chip memory mapped registers */
DECL|macro|MCHIP_MM_REGS
mdefine_line|#define MCHIP_MM_REGS&t;&t;&t;0x200&t;&t;/* 512 bytes        */
DECL|macro|MCHIP_REG_TIMEOUT
mdefine_line|#define MCHIP_REG_TIMEOUT&t;&t;1000&t;&t;/* reg access, ~us  */
DECL|macro|MCHIP_MCC_VRJ_TIMEOUT
mdefine_line|#define MCHIP_MCC_VRJ_TIMEOUT&t;&t;1000&t;&t;/* MCC &amp; VRJ access */
DECL|macro|MCHIP_MM_PCI_MODE
mdefine_line|#define MCHIP_MM_PCI_MODE&t;&t;0x00&t;&t;/* PCI access mode */
DECL|macro|MCHIP_MM_PCI_MODE_RETRY
mdefine_line|#define MCHIP_MM_PCI_MODE_RETRY&t;&t;0x00000001&t;/* retry mode */
DECL|macro|MCHIP_MM_PCI_MODE_MASTER
mdefine_line|#define MCHIP_MM_PCI_MODE_MASTER&t;0x00000002&t;/* master access */
DECL|macro|MCHIP_MM_PCI_MODE_READ_LINE
mdefine_line|#define MCHIP_MM_PCI_MODE_READ_LINE&t;0x00000004&t;/* read line */
DECL|macro|MCHIP_MM_INTA
mdefine_line|#define MCHIP_MM_INTA&t;&t;&t;0x04&t;&t;/* Int status/mask */
DECL|macro|MCHIP_MM_INTA_MCC
mdefine_line|#define MCHIP_MM_INTA_MCC&t;&t;0x00000001&t;/* MCC interrupt */
DECL|macro|MCHIP_MM_INTA_VRJ
mdefine_line|#define MCHIP_MM_INTA_VRJ&t;&t;0x00000002&t;/* VRJ interrupt */
DECL|macro|MCHIP_MM_INTA_HIC_1
mdefine_line|#define MCHIP_MM_INTA_HIC_1&t;&t;0x00000004&t;/* one frame done */
DECL|macro|MCHIP_MM_INTA_HIC_1_MASK
mdefine_line|#define MCHIP_MM_INTA_HIC_1_MASK&t;0x00000400&t;/* 1: enable */
DECL|macro|MCHIP_MM_INTA_HIC_END
mdefine_line|#define MCHIP_MM_INTA_HIC_END&t;&t;0x00000008&t;/* all frames done */
DECL|macro|MCHIP_MM_INTA_HIC_END_MASK
mdefine_line|#define MCHIP_MM_INTA_HIC_END_MASK&t;0x00000800
DECL|macro|MCHIP_MM_INTA_JPEG
mdefine_line|#define MCHIP_MM_INTA_JPEG&t;&t;0x00000010&t;/* decompress. error */
DECL|macro|MCHIP_MM_INTA_JPEG_MASK
mdefine_line|#define MCHIP_MM_INTA_JPEG_MASK&t;&t;0x00001000
DECL|macro|MCHIP_MM_INTA_CAPTURE
mdefine_line|#define MCHIP_MM_INTA_CAPTURE&t;&t;0x00000020&t;/* capture end */
DECL|macro|MCHIP_MM_INTA_PCI_ERR
mdefine_line|#define MCHIP_MM_INTA_PCI_ERR&t;&t;0x00000040&t;/* PCI error */
DECL|macro|MCHIP_MM_INTA_PCI_ERR_MASK
mdefine_line|#define MCHIP_MM_INTA_PCI_ERR_MASK&t;0x00004000
DECL|macro|MCHIP_MM_PT_ADDR
mdefine_line|#define MCHIP_MM_PT_ADDR&t;&t;0x08&t;&t;/* page table address */
multiline_comment|/* n*4kB */
DECL|macro|MCHIP_NB_PAGES
mdefine_line|#define MCHIP_NB_PAGES&t;&t;&t;1024&t;&t;/* pages for display */
DECL|macro|MCHIP_NB_PAGES_MJPEG
mdefine_line|#define MCHIP_NB_PAGES_MJPEG&t;&t;256&t;&t;/* pages for mjpeg */
DECL|macro|MCHIP_MM_FIR
mdefine_line|#define MCHIP_MM_FIR(n)&t;&t;&t;(0x0c+(n)*4)&t;/* Frame info 0-3 */
DECL|macro|MCHIP_MM_FIR_RDY
mdefine_line|#define MCHIP_MM_FIR_RDY&t;&t;0x00000001&t;/* frame ready */
DECL|macro|MCHIP_MM_FIR_FAILFR_MASK
mdefine_line|#define MCHIP_MM_FIR_FAILFR_MASK&t;0xf8000000&t;/* # of failed frames */
DECL|macro|MCHIP_MM_FIR_FAILFR_SHIFT
mdefine_line|#define MCHIP_MM_FIR_FAILFR_SHIFT&t;27
multiline_comment|/* continuous comp/decomp mode */
DECL|macro|MCHIP_MM_FIR_C_ENDL_MASK
mdefine_line|#define MCHIP_MM_FIR_C_ENDL_MASK&t;0x000007fe&t;/* end DW [10] */
DECL|macro|MCHIP_MM_FIR_C_ENDL_SHIFT
mdefine_line|#define MCHIP_MM_FIR_C_ENDL_SHIFT&t;1
DECL|macro|MCHIP_MM_FIR_C_ENDP_MASK
mdefine_line|#define MCHIP_MM_FIR_C_ENDP_MASK&t;0x0007f800&t;/* end page [8] */
DECL|macro|MCHIP_MM_FIR_C_ENDP_SHIFT
mdefine_line|#define MCHIP_MM_FIR_C_ENDP_SHIFT&t;11
DECL|macro|MCHIP_MM_FIR_C_STARTP_MASK
mdefine_line|#define MCHIP_MM_FIR_C_STARTP_MASK&t;0x07f80000&t;/* start page [8] */
DECL|macro|MCHIP_MM_FIR_C_STARTP_SHIFT
mdefine_line|#define MCHIP_MM_FIR_C_STARTP_SHIFT&t;19
multiline_comment|/* continuous picture output mode */
DECL|macro|MCHIP_MM_FIR_O_STARTP_MASK
mdefine_line|#define MCHIP_MM_FIR_O_STARTP_MASK&t;0x7ffe0000&t;/* start page [10] */
DECL|macro|MCHIP_MM_FIR_O_STARTP_SHIFT
mdefine_line|#define MCHIP_MM_FIR_O_STARTP_SHIFT&t;17
DECL|macro|MCHIP_MM_FIFO_DATA
mdefine_line|#define MCHIP_MM_FIFO_DATA&t;&t;0x1c&t;&t;/* PCI TGT FIFO data */
DECL|macro|MCHIP_MM_FIFO_STATUS
mdefine_line|#define MCHIP_MM_FIFO_STATUS&t;&t;0x20&t;&t;/* PCI TGT FIFO stat */
DECL|macro|MCHIP_MM_FIFO_MASK
mdefine_line|#define MCHIP_MM_FIFO_MASK&t;&t;0x00000003
DECL|macro|MCHIP_MM_FIFO_WAIT_OR_READY
mdefine_line|#define MCHIP_MM_FIFO_WAIT_OR_READY&t;0x00000002      /* Bits common to WAIT &amp; READY*/
DECL|macro|MCHIP_MM_FIFO_IDLE
mdefine_line|#define MCHIP_MM_FIFO_IDLE&t;&t;0x0&t;&t;/* HIC idle */
DECL|macro|MCHIP_MM_FIFO_IDLE1
mdefine_line|#define MCHIP_MM_FIFO_IDLE1&t;&t;0x1&t;&t;/* idem ??? */
DECL|macro|MCHIP_MM_FIFO_WAIT
mdefine_line|#define&t;MCHIP_MM_FIFO_WAIT&t;&t;0x2&t;&t;/* wait request */
DECL|macro|MCHIP_MM_FIFO_READY
mdefine_line|#define MCHIP_MM_FIFO_READY&t;&t;0x3&t;&t;/* data ready */
DECL|macro|MCHIP_HIC_HOST_USEREQ
mdefine_line|#define MCHIP_HIC_HOST_USEREQ&t;&t;0x40&t;&t;/* host uses MCORE */
DECL|macro|MCHIP_HIC_TP_BUSY
mdefine_line|#define MCHIP_HIC_TP_BUSY&t;&t;0x44&t;&t;/* taking picture */
DECL|macro|MCHIP_HIC_PIC_SAVED
mdefine_line|#define MCHIP_HIC_PIC_SAVED&t;&t;0x48&t;&t;/* pic in SDRAM */
DECL|macro|MCHIP_HIC_LOWPOWER
mdefine_line|#define MCHIP_HIC_LOWPOWER&t;&t;0x4c&t;&t;/* clock stopped */
DECL|macro|MCHIP_HIC_CTL
mdefine_line|#define MCHIP_HIC_CTL&t;&t;&t;0x50&t;&t;/* HIC control */
DECL|macro|MCHIP_HIC_CTL_SOFT_RESET
mdefine_line|#define MCHIP_HIC_CTL_SOFT_RESET&t;0x00000001&t;/* MCORE reset */
DECL|macro|MCHIP_HIC_CTL_MCORE_RDY
mdefine_line|#define MCHIP_HIC_CTL_MCORE_RDY&t;&t;0x00000002&t;/* MCORE ready */
DECL|macro|MCHIP_HIC_CMD
mdefine_line|#define MCHIP_HIC_CMD&t;&t;&t;0x54&t;&t;/* HIC command */
DECL|macro|MCHIP_HIC_CMD_BITS
mdefine_line|#define MCHIP_HIC_CMD_BITS&t;&t;0x00000003      /* cmd width=[1:0]*/
DECL|macro|MCHIP_HIC_CMD_NOOP
mdefine_line|#define MCHIP_HIC_CMD_NOOP&t;&t;0x0
DECL|macro|MCHIP_HIC_CMD_START
mdefine_line|#define MCHIP_HIC_CMD_START&t;&t;0x1
DECL|macro|MCHIP_HIC_CMD_STOP
mdefine_line|#define MCHIP_HIC_CMD_STOP&t;&t;0x2
DECL|macro|MCHIP_HIC_MODE
mdefine_line|#define MCHIP_HIC_MODE&t;&t;&t;0x58
DECL|macro|MCHIP_HIC_MODE_NOOP
mdefine_line|#define MCHIP_HIC_MODE_NOOP&t;&t;0x0
DECL|macro|MCHIP_HIC_MODE_STILL_CAP
mdefine_line|#define MCHIP_HIC_MODE_STILL_CAP&t;0x1&t;&t;/* still pic capt */
DECL|macro|MCHIP_HIC_MODE_DISPLAY
mdefine_line|#define MCHIP_HIC_MODE_DISPLAY&t;&t;0x2&t;&t;/* display */
DECL|macro|MCHIP_HIC_MODE_STILL_COMP
mdefine_line|#define MCHIP_HIC_MODE_STILL_COMP&t;0x3&t;&t;/* still pic comp. */
DECL|macro|MCHIP_HIC_MODE_STILL_DECOMP
mdefine_line|#define MCHIP_HIC_MODE_STILL_DECOMP&t;0x4&t;&t;/* still pic decomp. */
DECL|macro|MCHIP_HIC_MODE_CONT_COMP
mdefine_line|#define MCHIP_HIC_MODE_CONT_COMP&t;0x5&t;&t;/* cont capt+comp */
DECL|macro|MCHIP_HIC_MODE_CONT_DECOMP
mdefine_line|#define MCHIP_HIC_MODE_CONT_DECOMP&t;0x6&t;&t;/* cont decomp+disp */
DECL|macro|MCHIP_HIC_MODE_STILL_OUT
mdefine_line|#define MCHIP_HIC_MODE_STILL_OUT&t;0x7&t;&t;/* still pic output */
DECL|macro|MCHIP_HIC_MODE_CONT_OUT
mdefine_line|#define MCHIP_HIC_MODE_CONT_OUT&t;&t;0x8&t;&t;/* cont output */
DECL|macro|MCHIP_HIC_STATUS
mdefine_line|#define MCHIP_HIC_STATUS&t;&t;0x5c
DECL|macro|MCHIP_HIC_STATUS_MCC_RDY
mdefine_line|#define MCHIP_HIC_STATUS_MCC_RDY&t;0x00000001&t;/* MCC reg acc ok */
DECL|macro|MCHIP_HIC_STATUS_VRJ_RDY
mdefine_line|#define MCHIP_HIC_STATUS_VRJ_RDY&t;0x00000002&t;/* VRJ reg acc ok */
DECL|macro|MCHIP_HIC_STATUS_IDLE
mdefine_line|#define MCHIP_HIC_STATUS_IDLE           0x00000003
DECL|macro|MCHIP_HIC_STATUS_CAPDIS
mdefine_line|#define MCHIP_HIC_STATUS_CAPDIS&t;&t;0x00000004&t;/* cap/disp in prog */
DECL|macro|MCHIP_HIC_STATUS_COMPDEC
mdefine_line|#define MCHIP_HIC_STATUS_COMPDEC&t;0x00000008&t;/* (de)comp in prog */
DECL|macro|MCHIP_HIC_STATUS_BUSY
mdefine_line|#define MCHIP_HIC_STATUS_BUSY&t;&t;0x00000010&t;/* HIC busy */
DECL|macro|MCHIP_HIC_S_RATE
mdefine_line|#define MCHIP_HIC_S_RATE&t;&t;0x60&t;&t;/* MJPEG # frames */
DECL|macro|MCHIP_HIC_PCI_VFMT
mdefine_line|#define MCHIP_HIC_PCI_VFMT&t;&t;0x64&t;&t;/* video format */
DECL|macro|MCHIP_HIC_PCI_VFMT_YVYU
mdefine_line|#define MCHIP_HIC_PCI_VFMT_YVYU&t;&t;0x00000001&t;/* 0: V Y&squot; U Y */
multiline_comment|/* 1: Y&squot; V Y U */
DECL|macro|MCHIP_MCC_CMD
mdefine_line|#define MCHIP_MCC_CMD&t;&t;&t;0x80&t;&t;/* MCC commands */
DECL|macro|MCHIP_MCC_CMD_INITIAL
mdefine_line|#define MCHIP_MCC_CMD_INITIAL&t;&t;0x0&t;&t;/* idle ? */
DECL|macro|MCHIP_MCC_CMD_IIC_START_SET
mdefine_line|#define MCHIP_MCC_CMD_IIC_START_SET&t;0x1
DECL|macro|MCHIP_MCC_CMD_IIC_END_SET
mdefine_line|#define MCHIP_MCC_CMD_IIC_END_SET&t;0x2
DECL|macro|MCHIP_MCC_CMD_FM_WRITE
mdefine_line|#define MCHIP_MCC_CMD_FM_WRITE&t;&t;0x3&t;&t;/* frame memory */
DECL|macro|MCHIP_MCC_CMD_FM_READ
mdefine_line|#define MCHIP_MCC_CMD_FM_READ&t;&t;0x4
DECL|macro|MCHIP_MCC_CMD_FM_STOP
mdefine_line|#define MCHIP_MCC_CMD_FM_STOP&t;&t;0x5
DECL|macro|MCHIP_MCC_CMD_CAPTURE
mdefine_line|#define MCHIP_MCC_CMD_CAPTURE&t;&t;0x6
DECL|macro|MCHIP_MCC_CMD_DISPLAY
mdefine_line|#define MCHIP_MCC_CMD_DISPLAY&t;&t;0x7
DECL|macro|MCHIP_MCC_CMD_END_DISP
mdefine_line|#define MCHIP_MCC_CMD_END_DISP&t;&t;0x8
DECL|macro|MCHIP_MCC_CMD_STILL_COMP
mdefine_line|#define MCHIP_MCC_CMD_STILL_COMP&t;0x9
DECL|macro|MCHIP_MCC_CMD_STILL_DECOMP
mdefine_line|#define MCHIP_MCC_CMD_STILL_DECOMP&t;0xa
DECL|macro|MCHIP_MCC_CMD_STILL_OUTPUT
mdefine_line|#define MCHIP_MCC_CMD_STILL_OUTPUT&t;0xb
DECL|macro|MCHIP_MCC_CMD_CONT_OUTPUT
mdefine_line|#define MCHIP_MCC_CMD_CONT_OUTPUT&t;0xc
DECL|macro|MCHIP_MCC_CMD_CONT_COMP
mdefine_line|#define MCHIP_MCC_CMD_CONT_COMP&t;&t;0xd
DECL|macro|MCHIP_MCC_CMD_CONT_DECOMP
mdefine_line|#define MCHIP_MCC_CMD_CONT_DECOMP&t;0xe
DECL|macro|MCHIP_MCC_CMD_RESET
mdefine_line|#define MCHIP_MCC_CMD_RESET&t;&t;0xf&t;&t;/* MCC reset */
DECL|macro|MCHIP_MCC_IIC_WR
mdefine_line|#define MCHIP_MCC_IIC_WR&t;&t;0x84
DECL|macro|MCHIP_MCC_MCC_WR
mdefine_line|#define MCHIP_MCC_MCC_WR&t;&t;0x88
DECL|macro|MCHIP_MCC_MCC_RD
mdefine_line|#define MCHIP_MCC_MCC_RD&t;&t;0x8c
DECL|macro|MCHIP_MCC_STATUS
mdefine_line|#define MCHIP_MCC_STATUS&t;&t;0x90
DECL|macro|MCHIP_MCC_STATUS_CAPT
mdefine_line|#define MCHIP_MCC_STATUS_CAPT&t;&t;0x00000001&t;/* capturing */
DECL|macro|MCHIP_MCC_STATUS_DISP
mdefine_line|#define MCHIP_MCC_STATUS_DISP&t;&t;0x00000002&t;/* displaying */
DECL|macro|MCHIP_MCC_STATUS_COMP
mdefine_line|#define MCHIP_MCC_STATUS_COMP&t;&t;0x00000004&t;/* compressing */
DECL|macro|MCHIP_MCC_STATUS_DECOMP
mdefine_line|#define MCHIP_MCC_STATUS_DECOMP&t;&t;0x00000008&t;/* decompressing */
DECL|macro|MCHIP_MCC_STATUS_MCC_WR
mdefine_line|#define MCHIP_MCC_STATUS_MCC_WR&t;&t;0x00000010&t;/* register ready */
DECL|macro|MCHIP_MCC_STATUS_MCC_RD
mdefine_line|#define MCHIP_MCC_STATUS_MCC_RD&t;&t;0x00000020&t;/* register ready */
DECL|macro|MCHIP_MCC_STATUS_IIC_WR
mdefine_line|#define MCHIP_MCC_STATUS_IIC_WR&t;&t;0x00000040&t;/* register ready */
DECL|macro|MCHIP_MCC_STATUS_OUTPUT
mdefine_line|#define MCHIP_MCC_STATUS_OUTPUT&t;&t;0x00000080&t;/* output in prog */
DECL|macro|MCHIP_MCC_SIG_POLARITY
mdefine_line|#define MCHIP_MCC_SIG_POLARITY&t;&t;0x94
DECL|macro|MCHIP_MCC_SIG_POL_VS_H
mdefine_line|#define MCHIP_MCC_SIG_POL_VS_H&t;&t;0x00000001&t;/* VS active-high */
DECL|macro|MCHIP_MCC_SIG_POL_HS_H
mdefine_line|#define MCHIP_MCC_SIG_POL_HS_H&t;&t;0x00000002&t;/* HS active-high */
DECL|macro|MCHIP_MCC_SIG_POL_DOE_H
mdefine_line|#define MCHIP_MCC_SIG_POL_DOE_H&t;&t;0x00000004&t;/* DOE active-high */
DECL|macro|MCHIP_MCC_IRQ
mdefine_line|#define MCHIP_MCC_IRQ&t;&t;&t;0x98
DECL|macro|MCHIP_MCC_IRQ_CAPDIS_STRT
mdefine_line|#define MCHIP_MCC_IRQ_CAPDIS_STRT&t;0x00000001&t;/* cap/disp started */
DECL|macro|MCHIP_MCC_IRQ_CAPDIS_STRT_MASK
mdefine_line|#define MCHIP_MCC_IRQ_CAPDIS_STRT_MASK&t;0x00000010
DECL|macro|MCHIP_MCC_IRQ_CAPDIS_END
mdefine_line|#define MCHIP_MCC_IRQ_CAPDIS_END&t;0x00000002&t;/* cap/disp ended */
DECL|macro|MCHIP_MCC_IRQ_CAPDIS_END_MASK
mdefine_line|#define MCHIP_MCC_IRQ_CAPDIS_END_MASK&t;0x00000020
DECL|macro|MCHIP_MCC_IRQ_COMPDEC_STRT
mdefine_line|#define MCHIP_MCC_IRQ_COMPDEC_STRT&t;0x00000004&t;/* (de)comp started */
DECL|macro|MCHIP_MCC_IRQ_COMPDEC_STRT_MASK
mdefine_line|#define MCHIP_MCC_IRQ_COMPDEC_STRT_MASK&t;0x00000040
DECL|macro|MCHIP_MCC_IRQ_COMPDEC_END
mdefine_line|#define MCHIP_MCC_IRQ_COMPDEC_END&t;0x00000008&t;/* (de)comp ended */
DECL|macro|MCHIP_MCC_IRQ_COMPDEC_END_MASK
mdefine_line|#define MCHIP_MCC_IRQ_COMPDEC_END_MASK&t;0x00000080
DECL|macro|MCHIP_MCC_HSTART
mdefine_line|#define MCHIP_MCC_HSTART&t;&t;0x9c&t;&t;/* video in */
DECL|macro|MCHIP_MCC_VSTART
mdefine_line|#define MCHIP_MCC_VSTART&t;&t;0xa0
DECL|macro|MCHIP_MCC_HCOUNT
mdefine_line|#define MCHIP_MCC_HCOUNT&t;&t;0xa4
DECL|macro|MCHIP_MCC_VCOUNT
mdefine_line|#define MCHIP_MCC_VCOUNT&t;&t;0xa8
DECL|macro|MCHIP_MCC_R_XBASE
mdefine_line|#define MCHIP_MCC_R_XBASE&t;&t;0xac&t;&t;/* capt/disp */
DECL|macro|MCHIP_MCC_R_YBASE
mdefine_line|#define MCHIP_MCC_R_YBASE&t;&t;0xb0
DECL|macro|MCHIP_MCC_R_XRANGE
mdefine_line|#define MCHIP_MCC_R_XRANGE&t;&t;0xb4
DECL|macro|MCHIP_MCC_R_YRANGE
mdefine_line|#define MCHIP_MCC_R_YRANGE&t;&t;0xb8
DECL|macro|MCHIP_MCC_B_XBASE
mdefine_line|#define MCHIP_MCC_B_XBASE&t;&t;0xbc&t;&t;/* comp/decomp */
DECL|macro|MCHIP_MCC_B_YBASE
mdefine_line|#define MCHIP_MCC_B_YBASE&t;&t;0xc0
DECL|macro|MCHIP_MCC_B_XRANGE
mdefine_line|#define MCHIP_MCC_B_XRANGE&t;&t;0xc4
DECL|macro|MCHIP_MCC_B_YRANGE
mdefine_line|#define MCHIP_MCC_B_YRANGE&t;&t;0xc8
DECL|macro|MCHIP_MCC_R_SAMPLING
mdefine_line|#define MCHIP_MCC_R_SAMPLING&t;&t;0xcc&t;&t;/* 1: 1:4 */
DECL|macro|MCHIP_VRJ_CMD
mdefine_line|#define MCHIP_VRJ_CMD&t;&t;&t;0x100&t;&t;/* VRJ commands */
multiline_comment|/* VRJ registers (see table 12.2.4) */
DECL|macro|MCHIP_VRJ_COMPRESSED_DATA
mdefine_line|#define MCHIP_VRJ_COMPRESSED_DATA&t;0x1b0
DECL|macro|MCHIP_VRJ_PIXEL_DATA
mdefine_line|#define MCHIP_VRJ_PIXEL_DATA&t;&t;0x1b8
DECL|macro|MCHIP_VRJ_BUS_MODE
mdefine_line|#define MCHIP_VRJ_BUS_MODE&t;&t;0x100
DECL|macro|MCHIP_VRJ_SIGNAL_ACTIVE_LEVEL
mdefine_line|#define MCHIP_VRJ_SIGNAL_ACTIVE_LEVEL&t;0x108
DECL|macro|MCHIP_VRJ_PDAT_USE
mdefine_line|#define MCHIP_VRJ_PDAT_USE&t;&t;0x110
DECL|macro|MCHIP_VRJ_MODE_SPECIFY
mdefine_line|#define MCHIP_VRJ_MODE_SPECIFY&t;&t;0x118
DECL|macro|MCHIP_VRJ_LIMIT_COMPRESSED_LO
mdefine_line|#define MCHIP_VRJ_LIMIT_COMPRESSED_LO&t;0x120
DECL|macro|MCHIP_VRJ_LIMIT_COMPRESSED_HI
mdefine_line|#define MCHIP_VRJ_LIMIT_COMPRESSED_HI&t;0x124
DECL|macro|MCHIP_VRJ_COMP_DATA_FORMAT
mdefine_line|#define MCHIP_VRJ_COMP_DATA_FORMAT&t;0x128
DECL|macro|MCHIP_VRJ_TABLE_DATA
mdefine_line|#define MCHIP_VRJ_TABLE_DATA&t;&t;0x140
DECL|macro|MCHIP_VRJ_RESTART_INTERVAL
mdefine_line|#define MCHIP_VRJ_RESTART_INTERVAL&t;0x148
DECL|macro|MCHIP_VRJ_NUM_LINES
mdefine_line|#define MCHIP_VRJ_NUM_LINES&t;&t;0x150
DECL|macro|MCHIP_VRJ_NUM_PIXELS
mdefine_line|#define MCHIP_VRJ_NUM_PIXELS&t;&t;0x158
DECL|macro|MCHIP_VRJ_NUM_COMPONENTS
mdefine_line|#define MCHIP_VRJ_NUM_COMPONENTS&t;0x160
DECL|macro|MCHIP_VRJ_SOF1
mdefine_line|#define MCHIP_VRJ_SOF1&t;&t;&t;0x168
DECL|macro|MCHIP_VRJ_SOF2
mdefine_line|#define MCHIP_VRJ_SOF2&t;&t;&t;0x170
DECL|macro|MCHIP_VRJ_SOF3
mdefine_line|#define MCHIP_VRJ_SOF3&t;&t;&t;0x178
DECL|macro|MCHIP_VRJ_SOF4
mdefine_line|#define MCHIP_VRJ_SOF4&t;&t;&t;0x180
DECL|macro|MCHIP_VRJ_SOS
mdefine_line|#define MCHIP_VRJ_SOS&t;&t;&t;0x188
DECL|macro|MCHIP_VRJ_SOFT_RESET
mdefine_line|#define MCHIP_VRJ_SOFT_RESET&t;&t;0x190
DECL|macro|MCHIP_VRJ_STATUS
mdefine_line|#define MCHIP_VRJ_STATUS&t;&t;0x1c0
DECL|macro|MCHIP_VRJ_STATUS_BUSY
mdefine_line|#define MCHIP_VRJ_STATUS_BUSY&t;&t;0x00001
DECL|macro|MCHIP_VRJ_STATUS_COMP_ACCESS
mdefine_line|#define MCHIP_VRJ_STATUS_COMP_ACCESS&t;0x00002
DECL|macro|MCHIP_VRJ_STATUS_PIXEL_ACCESS
mdefine_line|#define MCHIP_VRJ_STATUS_PIXEL_ACCESS&t;0x00004
DECL|macro|MCHIP_VRJ_STATUS_ERROR
mdefine_line|#define MCHIP_VRJ_STATUS_ERROR&t;&t;0x00008
DECL|macro|MCHIP_VRJ_IRQ_FLAG
mdefine_line|#define MCHIP_VRJ_IRQ_FLAG&t;&t;0x1c8
DECL|macro|MCHIP_VRJ_ERROR_REPORT
mdefine_line|#define MCHIP_VRJ_ERROR_REPORT&t;&t;0x1d8
DECL|macro|MCHIP_VRJ_START_COMMAND
mdefine_line|#define MCHIP_VRJ_START_COMMAND&t;&t;0x1a0
multiline_comment|/****************************************************************************/
multiline_comment|/* Driver definitions.                                                      */
multiline_comment|/****************************************************************************/
multiline_comment|/* Sony Programmable I/O Controller for accessing the camera commands */
macro_line|#include &lt;linux/sonypi.h&gt;
multiline_comment|/* private API definitions */
macro_line|#include &lt;linux/meye.h&gt;
multiline_comment|/* Enable jpg software correction */
DECL|macro|MEYE_JPEG_CORRECTION
mdefine_line|#define MEYE_JPEG_CORRECTION&t;1
multiline_comment|/* Maximum size of a buffer */
DECL|macro|MEYE_MAX_BUFSIZE
mdefine_line|#define MEYE_MAX_BUFSIZE&t;614400&t;/* 640 * 480 * 2 */
multiline_comment|/* Maximum number of buffers */
DECL|macro|MEYE_MAX_BUFNBRS
mdefine_line|#define MEYE_MAX_BUFNBRS&t;32
multiline_comment|/* State of a buffer */
DECL|macro|MEYE_BUF_UNUSED
mdefine_line|#define MEYE_BUF_UNUSED&t;0&t;/* not used */
DECL|macro|MEYE_BUF_USING
mdefine_line|#define MEYE_BUF_USING&t;1&t;/* currently grabbing / playing */
DECL|macro|MEYE_BUF_DONE
mdefine_line|#define MEYE_BUF_DONE&t;2&t;/* done */
multiline_comment|/* grab buffer */
DECL|struct|meye_grab_buffer
r_struct
id|meye_grab_buffer
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* state of buffer */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of jpg frame */
)brace
suffix:semicolon
multiline_comment|/* queues containing the buffer indices */
DECL|macro|MEYE_QUEUE_SIZE
mdefine_line|#define MEYE_QUEUE_SIZE&t;MEYE_MAX_BUFNBRS
DECL|struct|meye_queue
r_struct
id|meye_queue
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
multiline_comment|/* queue head */
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
multiline_comment|/* queue tail */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* queue length */
DECL|member|s_lock
id|spinlock_t
id|s_lock
suffix:semicolon
multiline_comment|/* spinlock protecting the queue */
DECL|member|proc_list
id|wait_queue_head_t
id|proc_list
suffix:semicolon
multiline_comment|/* wait queue */
DECL|member|buf
r_int
id|buf
(braket
id|MEYE_QUEUE_SIZE
)braket
suffix:semicolon
multiline_comment|/* queue contents */
)brace
suffix:semicolon
multiline_comment|/* Motion Eye device structure */
DECL|struct|meye
r_struct
id|meye
(brace
multiline_comment|/* mchip related */
DECL|member|mchip_dev
r_struct
id|pci_dev
op_star
id|mchip_dev
suffix:semicolon
multiline_comment|/* pci device */
DECL|member|mchip_irq
id|u8
id|mchip_irq
suffix:semicolon
multiline_comment|/* irq */
DECL|member|mchip_mode
id|u8
id|mchip_mode
suffix:semicolon
multiline_comment|/* actual mchip mode: HIC_MODE... */
DECL|member|mchip_fnum
id|u8
id|mchip_fnum
suffix:semicolon
multiline_comment|/* current mchip frame number */
DECL|member|mchip_mmregs
r_int
r_char
op_star
id|mchip_mmregs
suffix:semicolon
multiline_comment|/* mchip: memory mapped registers */
DECL|member|mchip_ptable
id|u8
op_star
id|mchip_ptable
(braket
id|MCHIP_NB_PAGES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* mchip: ptable + ptable toc */
DECL|member|mchip_dmahandle
id|dma_addr_t
id|mchip_dmahandle
suffix:semicolon
multiline_comment|/* mchip: dma handle to ptable toc */
DECL|member|grab_fbuffer
r_int
r_char
op_star
id|grab_fbuffer
suffix:semicolon
multiline_comment|/* capture framebuffer */
multiline_comment|/* list of buffers */
DECL|member|grab_buffer
r_struct
id|meye_grab_buffer
id|grab_buffer
(braket
id|MEYE_MAX_BUFNBRS
)braket
suffix:semicolon
multiline_comment|/* other */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* semaphore for open/mmap... */
DECL|member|grabq
r_struct
id|meye_queue
id|grabq
suffix:semicolon
multiline_comment|/* queue for buffers to be grabbed */
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
multiline_comment|/* video device parameters */
DECL|member|picture
r_struct
id|video_picture
id|picture
suffix:semicolon
multiline_comment|/* video picture parameters */
DECL|member|params
r_struct
id|meye_params
id|params
suffix:semicolon
multiline_comment|/* additional parameters */
)brace
suffix:semicolon
macro_line|#endif
eof
