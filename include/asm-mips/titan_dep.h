multiline_comment|/*&n; * Copyright 2003 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * Board specific definititions for the PMC-Sierra Yosemite&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __TITAN_DEP_H__
DECL|macro|__TITAN_DEP_H__
mdefine_line|#define __TITAN_DEP_H__
macro_line|#include &lt;asm/addrspace.h&gt;              /* for KSEG1ADDR() */
macro_line|#include &lt;asm/byteorder.h&gt;              /* for cpu_to_le32() */
DECL|macro|TITAN_READ
mdefine_line|#define TITAN_READ(ofs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile u32 *)(ocd_base+(ofs)))
DECL|macro|TITAN_READ_16
mdefine_line|#define TITAN_READ_16(ofs)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile u16 *)(ocd_base+(ofs)))
DECL|macro|TITAN_READ_8
mdefine_line|#define TITAN_READ_8(ofs)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile u8 *)(ocd_base+(ofs)))
DECL|macro|TITAN_WRITE
mdefine_line|#define TITAN_WRITE(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile u32 *)(ocd_base+(ofs)) = (data); } while (0)
DECL|macro|TITAN_WRITE_16
mdefine_line|#define TITAN_WRITE_16(ofs, data)&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile u16 *)(ocd_base+(ofs)) = (data); } while (0)
DECL|macro|TITAN_WRITE_8
mdefine_line|#define TITAN_WRITE_8(ofs, data)&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile u8 *)(ocd_base+(ofs)) = (data); } while (0)
multiline_comment|/*&n; * PCI specific defines&n; */
DECL|macro|TITAN_PCI_0_CONFIG_ADDRESS
mdefine_line|#define&t;TITAN_PCI_0_CONFIG_ADDRESS&t;0x780
DECL|macro|TITAN_PCI_0_CONFIG_DATA
mdefine_line|#define&t;TITAN_PCI_0_CONFIG_DATA&t;&t;0x784
multiline_comment|/*&n; * HT specific defines&n; */
DECL|macro|RM9000x2_HTLINK_REG
mdefine_line|#define RM9000x2_HTLINK_REG&t;&t;0xbb000644
DECL|macro|RM9000x2_BASE_ADDR
mdefine_line|#define RM9000x2_BASE_ADDR&t;&t;0xbb000000
DECL|macro|OCD_BASE
mdefine_line|#define OCD_BASE&t;&t;&t;0xfb000000UL
DECL|macro|OCD_SIZE
mdefine_line|#define OCD_SIZE&t;&t;&t;0x3000UL
r_extern
r_int
r_int
id|ocd_base
suffix:semicolon
multiline_comment|/*&n; * OCD Registers&n; */
DECL|macro|RM9000x2_OCD_LKB5
mdefine_line|#define RM9000x2_OCD_LKB5&t;&t;0x0128&t;&t;/* Ethernet */
DECL|macro|RM9000x2_OCD_LKM5
mdefine_line|#define RM9000x2_OCD_LKM5&t;&t;0x012c
DECL|macro|RM9000x2_OCD_LKB7
mdefine_line|#define RM9000x2_OCD_LKB7&t;&t;0x0138&t;&t;/* HT Region 0 */
DECL|macro|RM9000x2_OCD_LKM7
mdefine_line|#define RM9000x2_OCD_LKM7&t;&t;0x013c
DECL|macro|RM9000x2_OCD_LKB8
mdefine_line|#define RM9000x2_OCD_LKB8&t;&t;0x0140&t;&t;/* HT Region 1 */
DECL|macro|RM9000x2_OCD_LKM8
mdefine_line|#define RM9000x2_OCD_LKM8&t;&t;0x0144
DECL|macro|RM9000x2_OCD_LKB9
mdefine_line|#define RM9000x2_OCD_LKB9&t;&t;0x0148&t;&t;/* Local Bus */
DECL|macro|RM9000x2_OCD_LKM9
mdefine_line|#define RM9000x2_OCD_LKM9&t;&t;0x014c
DECL|macro|RM9000x2_OCD_LKB10
mdefine_line|#define RM9000x2_OCD_LKB10&t;&t;0x0150
DECL|macro|RM9000x2_OCD_LKM10
mdefine_line|#define RM9000x2_OCD_LKM10&t;&t;0x0154
DECL|macro|RM9000x2_OCD_LKB11
mdefine_line|#define RM9000x2_OCD_LKB11&t;&t;0x0158
DECL|macro|RM9000x2_OCD_LKM11
mdefine_line|#define RM9000x2_OCD_LKM11&t;&t;0x015c
DECL|macro|RM9000x2_OCD_LKB12
mdefine_line|#define RM9000x2_OCD_LKB12&t;&t;0x0160
DECL|macro|RM9000x2_OCD_LKM12
mdefine_line|#define RM9000x2_OCD_LKM12&t;&t;0x0164
DECL|macro|RM9000x2_OCD_LKB13
mdefine_line|#define RM9000x2_OCD_LKB13&t;&t;0x0168&t;&t;/* Scratch RAM */
DECL|macro|RM9000x2_OCD_LKM13
mdefine_line|#define RM9000x2_OCD_LKM13&t;&t;0x016c
DECL|macro|RM9000x2_OCD_LPD0
mdefine_line|#define RM9000x2_OCD_LPD0&t;&t;0x0200&t;&t;/* Local Bus */
DECL|macro|RM9000x2_OCD_LPD1
mdefine_line|#define RM9000x2_OCD_LPD1&t;&t;0x0210
DECL|macro|RM9000x2_OCD_LPD2
mdefine_line|#define RM9000x2_OCD_LPD2&t;&t;0x0220
DECL|macro|RM9000x2_OCD_LPD3
mdefine_line|#define RM9000x2_OCD_LPD3&t;&t;0x0230
DECL|macro|RM9000x2_OCD_HTDVID
mdefine_line|#define RM9000x2_OCD_HTDVID&t;&t;0x0600&t;/* HT Device Header */
DECL|macro|RM9000x2_OCD_HTSC
mdefine_line|#define RM9000x2_OCD_HTSC&t;&t;0x0604
DECL|macro|RM9000x2_OCD_HTCCR
mdefine_line|#define RM9000x2_OCD_HTCCR&t;&t;0x0608
DECL|macro|RM9000x2_OCD_HTBHL
mdefine_line|#define RM9000x2_OCD_HTBHL&t;&t;0x060c
DECL|macro|RM9000x2_OCD_HTBAR0
mdefine_line|#define RM9000x2_OCD_HTBAR0&t;&t;0x0610
DECL|macro|RM9000x2_OCD_HTBAR1
mdefine_line|#define RM9000x2_OCD_HTBAR1&t;&t;0x0614
DECL|macro|RM9000x2_OCD_HTBAR2
mdefine_line|#define RM9000x2_OCD_HTBAR2&t;&t;0x0618
DECL|macro|RM9000x2_OCD_HTBAR3
mdefine_line|#define RM9000x2_OCD_HTBAR3&t;&t;0x061c
DECL|macro|RM9000x2_OCD_HTBAR4
mdefine_line|#define RM9000x2_OCD_HTBAR4&t;&t;0x0620
DECL|macro|RM9000x2_OCD_HTBAR5
mdefine_line|#define RM9000x2_OCD_HTBAR5&t;&t;0x0624
DECL|macro|RM9000x2_OCD_HTCBCPT
mdefine_line|#define RM9000x2_OCD_HTCBCPT&t;&t;0x0628
DECL|macro|RM9000x2_OCD_HTSDVID
mdefine_line|#define RM9000x2_OCD_HTSDVID&t;&t;0x062c
DECL|macro|RM9000x2_OCD_HTXRA
mdefine_line|#define RM9000x2_OCD_HTXRA&t;&t;0x0630
DECL|macro|RM9000x2_OCD_HTCAP1
mdefine_line|#define RM9000x2_OCD_HTCAP1&t;&t;0x0634
DECL|macro|RM9000x2_OCD_HTIL
mdefine_line|#define RM9000x2_OCD_HTIL&t;&t;0x063c
DECL|macro|RM9000x2_OCD_HTLCC
mdefine_line|#define RM9000x2_OCD_HTLCC&t;&t;0x0640&t;/* HT Capability Block */
DECL|macro|RM9000x2_OCD_HTLINK
mdefine_line|#define RM9000x2_OCD_HTLINK&t;&t;0x0644
DECL|macro|RM9000x2_OCD_HTFQREV
mdefine_line|#define RM9000x2_OCD_HTFQREV&t;&t;0x0648
DECL|macro|RM9000x2_OCD_HTERCTL
mdefine_line|#define RM9000x2_OCD_HTERCTL&t;&t;0x0668&t;/* HT Controller */
DECL|macro|RM9000x2_OCD_HTRXDB
mdefine_line|#define RM9000x2_OCD_HTRXDB&t;&t;0x066c
DECL|macro|RM9000x2_OCD_HTIMPED
mdefine_line|#define RM9000x2_OCD_HTIMPED&t;&t;0x0670
DECL|macro|RM9000x2_OCD_HTSWIMP
mdefine_line|#define RM9000x2_OCD_HTSWIMP&t;&t;0x0674
DECL|macro|RM9000x2_OCD_HTCAL
mdefine_line|#define RM9000x2_OCD_HTCAL&t;&t;0x0678
DECL|macro|RM9000x2_OCD_HTBAA30
mdefine_line|#define RM9000x2_OCD_HTBAA30&t;&t;0x0680
DECL|macro|RM9000x2_OCD_HTBAA54
mdefine_line|#define RM9000x2_OCD_HTBAA54&t;&t;0x0684
DECL|macro|RM9000x2_OCD_HTMASK0
mdefine_line|#define RM9000x2_OCD_HTMASK0&t;&t;0x0688
DECL|macro|RM9000x2_OCD_HTMASK1
mdefine_line|#define RM9000x2_OCD_HTMASK1&t;&t;0x068c
DECL|macro|RM9000x2_OCD_HTMASK2
mdefine_line|#define RM9000x2_OCD_HTMASK2&t;&t;0x0690
DECL|macro|RM9000x2_OCD_HTMASK3
mdefine_line|#define RM9000x2_OCD_HTMASK3&t;&t;0x0694
DECL|macro|RM9000x2_OCD_HTMASK4
mdefine_line|#define RM9000x2_OCD_HTMASK4&t;&t;0x0698
DECL|macro|RM9000x2_OCD_HTMASK5
mdefine_line|#define RM9000x2_OCD_HTMASK5&t;&t;0x069c
DECL|macro|RM9000x2_OCD_HTIFCTL
mdefine_line|#define RM9000x2_OCD_HTIFCTL&t;&t;0x06a0
DECL|macro|RM9000x2_OCD_HTPLL
mdefine_line|#define RM9000x2_OCD_HTPLL&t;&t;0x06a4
DECL|macro|RM9000x2_OCD_HTSRI
mdefine_line|#define RM9000x2_OCD_HTSRI&t;&t;0x06b0
DECL|macro|RM9000x2_OCD_HTRXNUM
mdefine_line|#define RM9000x2_OCD_HTRXNUM&t;&t;0x06b4
DECL|macro|RM9000x2_OCD_HTTXNUM
mdefine_line|#define RM9000x2_OCD_HTTXNUM&t;&t;0x06b8
DECL|macro|RM9000x2_OCD_HTTXCNT
mdefine_line|#define RM9000x2_OCD_HTTXCNT&t;&t;0x06c8
DECL|macro|RM9000x2_OCD_HTERROR
mdefine_line|#define RM9000x2_OCD_HTERROR&t;&t;0x06d8
DECL|macro|RM9000x2_OCD_HTRCRCE
mdefine_line|#define RM9000x2_OCD_HTRCRCE&t;&t;0x06dc
DECL|macro|RM9000x2_OCD_HTEOI
mdefine_line|#define RM9000x2_OCD_HTEOI&t;&t;0x06e0
DECL|macro|RM9000x2_OCD_CRCR
mdefine_line|#define RM9000x2_OCD_CRCR&t;&t;0x06f0
DECL|macro|RM9000x2_OCD_HTCFGA
mdefine_line|#define RM9000x2_OCD_HTCFGA&t;&t;0x06f8
DECL|macro|RM9000x2_OCD_HTCFGD
mdefine_line|#define RM9000x2_OCD_HTCFGD&t;&t;0x06fc
DECL|macro|RM9000x2_OCD_INTMSG
mdefine_line|#define RM9000x2_OCD_INTMSG&t;&t;0x0a00
DECL|macro|RM9000x2_OCD_INTPIN0
mdefine_line|#define RM9000x2_OCD_INTPIN0&t;&t;0x0a40
DECL|macro|RM9000x2_OCD_INTPIN1
mdefine_line|#define RM9000x2_OCD_INTPIN1&t;&t;0x0a44
DECL|macro|RM9000x2_OCD_INTPIN2
mdefine_line|#define RM9000x2_OCD_INTPIN2&t;&t;0x0a48
DECL|macro|RM9000x2_OCD_INTPIN3
mdefine_line|#define RM9000x2_OCD_INTPIN3&t;&t;0x0a4c
DECL|macro|RM9000x2_OCD_INTPIN4
mdefine_line|#define RM9000x2_OCD_INTPIN4&t;&t;0x0a50
DECL|macro|RM9000x2_OCD_INTPIN5
mdefine_line|#define RM9000x2_OCD_INTPIN5&t;&t;0x0a54
DECL|macro|RM9000x2_OCD_INTPIN6
mdefine_line|#define RM9000x2_OCD_INTPIN6&t;&t;0x0a58
DECL|macro|RM9000x2_OCD_INTPIN7
mdefine_line|#define RM9000x2_OCD_INTPIN7&t;&t;0x0a5c
DECL|macro|RM9000x2_OCD_SEM
mdefine_line|#define RM9000x2_OCD_SEM&t;&t;0x0a60
DECL|macro|RM9000x2_OCD_SEMSET
mdefine_line|#define RM9000x2_OCD_SEMSET&t;&t;0x0a64
DECL|macro|RM9000x2_OCD_SEMCLR
mdefine_line|#define RM9000x2_OCD_SEMCLR&t;&t;0x0a68
DECL|macro|RM9000x2_OCD_TKT
mdefine_line|#define RM9000x2_OCD_TKT&t;&t;0x0a70
DECL|macro|RM9000x2_OCD_TKTINC
mdefine_line|#define RM9000x2_OCD_TKTINC&t;&t;0x0a74
DECL|macro|RM9000x2_OCD_NMICONFIG
mdefine_line|#define RM9000x2_OCD_NMICONFIG&t;&t;0x0ac0&t;&t;/* Interrupts */
DECL|macro|RM9000x2_OCD_INTP0PRI
mdefine_line|#define RM9000x2_OCD_INTP0PRI&t;&t;0x1a80
DECL|macro|RM9000x2_OCD_INTP1PRI
mdefine_line|#define RM9000x2_OCD_INTP1PRI&t;&t;0x1a80
DECL|macro|RM9000x2_OCD_INTP0STATUS0
mdefine_line|#define RM9000x2_OCD_INTP0STATUS0&t;0x1b00
DECL|macro|RM9000x2_OCD_INTP0MASK0
mdefine_line|#define RM9000x2_OCD_INTP0MASK0&t;&t;0x1b04
DECL|macro|RM9000x2_OCD_INTP0SET0
mdefine_line|#define RM9000x2_OCD_INTP0SET0&t;&t;0x1b08
DECL|macro|RM9000x2_OCD_INTP0CLEAR0
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR0&t;0x1b0c
DECL|macro|RM9000x2_OCD_INTP0STATUS1
mdefine_line|#define RM9000x2_OCD_INTP0STATUS1&t;0x1b10
DECL|macro|RM9000x2_OCD_INTP0MASK1
mdefine_line|#define RM9000x2_OCD_INTP0MASK1&t;&t;0x1b14
DECL|macro|RM9000x2_OCD_INTP0SET1
mdefine_line|#define RM9000x2_OCD_INTP0SET1&t;&t;0x1b18
DECL|macro|RM9000x2_OCD_INTP0CLEAR1
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR1&t;0x1b1c
DECL|macro|RM9000x2_OCD_INTP0STATUS2
mdefine_line|#define RM9000x2_OCD_INTP0STATUS2&t;0x1b20
DECL|macro|RM9000x2_OCD_INTP0MASK2
mdefine_line|#define RM9000x2_OCD_INTP0MASK2&t;&t;0x1b24
DECL|macro|RM9000x2_OCD_INTP0SET2
mdefine_line|#define RM9000x2_OCD_INTP0SET2&t;&t;0x1b28
DECL|macro|RM9000x2_OCD_INTP0CLEAR2
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR2&t;0x1b2c
DECL|macro|RM9000x2_OCD_INTP0STATUS3
mdefine_line|#define RM9000x2_OCD_INTP0STATUS3&t;0x1b30
DECL|macro|RM9000x2_OCD_INTP0MASK3
mdefine_line|#define RM9000x2_OCD_INTP0MASK3&t;&t;0x1b34
DECL|macro|RM9000x2_OCD_INTP0SET3
mdefine_line|#define RM9000x2_OCD_INTP0SET3&t;&t;0x1b38
DECL|macro|RM9000x2_OCD_INTP0CLEAR3
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR3&t;0x1b3c
DECL|macro|RM9000x2_OCD_INTP0STATUS4
mdefine_line|#define RM9000x2_OCD_INTP0STATUS4&t;0x1b40
DECL|macro|RM9000x2_OCD_INTP0MASK4
mdefine_line|#define RM9000x2_OCD_INTP0MASK4&t;&t;0x1b44
DECL|macro|RM9000x2_OCD_INTP0SET4
mdefine_line|#define RM9000x2_OCD_INTP0SET4&t;&t;0x1b48
DECL|macro|RM9000x2_OCD_INTP0CLEAR4
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR4&t;0x1b4c
DECL|macro|RM9000x2_OCD_INTP0STATUS5
mdefine_line|#define RM9000x2_OCD_INTP0STATUS5&t;0x1b50
DECL|macro|RM9000x2_OCD_INTP0MASK5
mdefine_line|#define RM9000x2_OCD_INTP0MASK5&t;&t;0x1b54
DECL|macro|RM9000x2_OCD_INTP0SET5
mdefine_line|#define RM9000x2_OCD_INTP0SET5&t;&t;0x1b58
DECL|macro|RM9000x2_OCD_INTP0CLEAR5
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR5&t;0x1b5c
DECL|macro|RM9000x2_OCD_INTP0STATUS6
mdefine_line|#define RM9000x2_OCD_INTP0STATUS6&t;0x1b60
DECL|macro|RM9000x2_OCD_INTP0MASK6
mdefine_line|#define RM9000x2_OCD_INTP0MASK6&t;&t;0x1b64
DECL|macro|RM9000x2_OCD_INTP0SET6
mdefine_line|#define RM9000x2_OCD_INTP0SET6&t;&t;0x1b68
DECL|macro|RM9000x2_OCD_INTP0CLEAR6
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR6&t;0x1b6c
DECL|macro|RM9000x2_OCD_INTP0STATUS7
mdefine_line|#define RM9000x2_OCD_INTP0STATUS7&t;0x1b70
DECL|macro|RM9000x2_OCD_INTP0MASK7
mdefine_line|#define RM9000x2_OCD_INTP0MASK7&t;&t;0x1b74
DECL|macro|RM9000x2_OCD_INTP0SET7
mdefine_line|#define RM9000x2_OCD_INTP0SET7&t;&t;0x1b78
DECL|macro|RM9000x2_OCD_INTP0CLEAR7
mdefine_line|#define RM9000x2_OCD_INTP0CLEAR7&t;0x1b7c
DECL|macro|RM9000x2_OCD_INTP1STATUS0
mdefine_line|#define RM9000x2_OCD_INTP1STATUS0&t;0x2b00
DECL|macro|RM9000x2_OCD_INTP1MASK0
mdefine_line|#define RM9000x2_OCD_INTP1MASK0&t;&t;0x2b04
DECL|macro|RM9000x2_OCD_INTP1SET0
mdefine_line|#define RM9000x2_OCD_INTP1SET0&t;&t;0x2b08
DECL|macro|RM9000x2_OCD_INTP1CLEAR0
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR0&t;0x2b0c
DECL|macro|RM9000x2_OCD_INTP1STATUS1
mdefine_line|#define RM9000x2_OCD_INTP1STATUS1&t;0x2b10
DECL|macro|RM9000x2_OCD_INTP1MASK1
mdefine_line|#define RM9000x2_OCD_INTP1MASK1&t;&t;0x2b14
DECL|macro|RM9000x2_OCD_INTP1SET1
mdefine_line|#define RM9000x2_OCD_INTP1SET1&t;&t;0x2b18
DECL|macro|RM9000x2_OCD_INTP1CLEAR1
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR1&t;0x2b1c
DECL|macro|RM9000x2_OCD_INTP1STATUS2
mdefine_line|#define RM9000x2_OCD_INTP1STATUS2&t;0x2b20
DECL|macro|RM9000x2_OCD_INTP1MASK2
mdefine_line|#define RM9000x2_OCD_INTP1MASK2&t;&t;0x2b24
DECL|macro|RM9000x2_OCD_INTP1SET2
mdefine_line|#define RM9000x2_OCD_INTP1SET2&t;&t;0x2b28
DECL|macro|RM9000x2_OCD_INTP1CLEAR2
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR2&t;0x2b2c
DECL|macro|RM9000x2_OCD_INTP1STATUS3
mdefine_line|#define RM9000x2_OCD_INTP1STATUS3&t;0x2b30
DECL|macro|RM9000x2_OCD_INTP1MASK3
mdefine_line|#define RM9000x2_OCD_INTP1MASK3&t;&t;0x2b34
DECL|macro|RM9000x2_OCD_INTP1SET3
mdefine_line|#define RM9000x2_OCD_INTP1SET3&t;&t;0x2b38
DECL|macro|RM9000x2_OCD_INTP1CLEAR3
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR3&t;0x2b3c
DECL|macro|RM9000x2_OCD_INTP1STATUS4
mdefine_line|#define RM9000x2_OCD_INTP1STATUS4&t;0x2b40
DECL|macro|RM9000x2_OCD_INTP1MASK4
mdefine_line|#define RM9000x2_OCD_INTP1MASK4&t;&t;0x2b44
DECL|macro|RM9000x2_OCD_INTP1SET4
mdefine_line|#define RM9000x2_OCD_INTP1SET4&t;&t;0x2b48
DECL|macro|RM9000x2_OCD_INTP1CLEAR4
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR4&t;0x2b4c
DECL|macro|RM9000x2_OCD_INTP1STATUS5
mdefine_line|#define RM9000x2_OCD_INTP1STATUS5&t;0x2b50
DECL|macro|RM9000x2_OCD_INTP1MASK5
mdefine_line|#define RM9000x2_OCD_INTP1MASK5&t;&t;0x2b54
DECL|macro|RM9000x2_OCD_INTP1SET5
mdefine_line|#define RM9000x2_OCD_INTP1SET5&t;&t;0x2b58
DECL|macro|RM9000x2_OCD_INTP1CLEAR5
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR5&t;0x2b5c
DECL|macro|RM9000x2_OCD_INTP1STATUS6
mdefine_line|#define RM9000x2_OCD_INTP1STATUS6&t;0x2b60
DECL|macro|RM9000x2_OCD_INTP1MASK6
mdefine_line|#define RM9000x2_OCD_INTP1MASK6&t;&t;0x2b64
DECL|macro|RM9000x2_OCD_INTP1SET6
mdefine_line|#define RM9000x2_OCD_INTP1SET6&t;&t;0x2b68
DECL|macro|RM9000x2_OCD_INTP1CLEAR6
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR6&t;0x2b6c
DECL|macro|RM9000x2_OCD_INTP1STATUS7
mdefine_line|#define RM9000x2_OCD_INTP1STATUS7&t;0x2b70
DECL|macro|RM9000x2_OCD_INTP1MASK7
mdefine_line|#define RM9000x2_OCD_INTP1MASK7&t;&t;0x2b74
DECL|macro|RM9000x2_OCD_INTP1SET7
mdefine_line|#define RM9000x2_OCD_INTP1SET7&t;&t;0x2b78
DECL|macro|RM9000x2_OCD_INTP1CLEAR7
mdefine_line|#define RM9000x2_OCD_INTP1CLEAR7&t;0x2b7c
DECL|macro|OCD_READ
mdefine_line|#define OCD_READ(reg)&t;&t;(*(volatile unsigned int *)(ocd_base + (reg)))
DECL|macro|OCD_WRITE
mdefine_line|#define OCD_WRITE(reg, val)&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile unsigned int *)(ocd_base + (reg)) = (val); } while (0)
multiline_comment|/*&n; * Hypertransport specific macros&n; */
DECL|macro|RM9K_WRITE
mdefine_line|#define RM9K_WRITE(ofs, data)   *(volatile u_int32_t *)(RM9000x2_BASE_ADDR+ofs) = data
DECL|macro|RM9K_WRITE_8
mdefine_line|#define RM9K_WRITE_8(ofs, data) *(volatile u8 *)(RM9000x2_BASE_ADDR+ofs) = data
DECL|macro|RM9K_WRITE_16
mdefine_line|#define RM9K_WRITE_16(ofs, data) *(volatile u16 *)(RM9000x2_BASE_ADDR+ofs) = data
DECL|macro|RM9K_READ
mdefine_line|#define RM9K_READ(ofs, val)     *(val) = *(volatile u_int32_t *)(RM9000x2_BASE_ADDR+ofs)
DECL|macro|RM9K_READ_8
mdefine_line|#define RM9K_READ_8(ofs, val)   *(val) = *(volatile u8 *)(RM9000x2_BASE_ADDR+ofs)
DECL|macro|RM9K_READ_16
mdefine_line|#define RM9K_READ_16(ofs, val)  *(val) = *(volatile u16 *)(RM9000x2_BASE_ADDR+ofs)
macro_line|#endif 
eof
