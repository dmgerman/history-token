multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  LDT constants&t;&t;&t;&t;File: sb1250_ldt.h&n;    *  &n;    *  This module contains constants and macros to describe &n;    *  the LDT interface on the SB1250.  &n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_LDT_H
DECL|macro|_SB1250_LDT_H
mdefine_line|#define _SB1250_LDT_H
macro_line|#include &quot;sb1250_defs.h&quot;
DECL|macro|K_LDT_VENDOR_SIBYTE
mdefine_line|#define K_LDT_VENDOR_SIBYTE&t;0x166D
DECL|macro|K_LDT_DEVICE_SB1250
mdefine_line|#define K_LDT_DEVICE_SB1250&t;0x0002
multiline_comment|/*&n; * LDT Interface Type 1 (bridge) configuration header&n; */
DECL|macro|R_LDT_TYPE1_DEVICEID
mdefine_line|#define R_LDT_TYPE1_DEVICEID&t;0x0000
DECL|macro|R_LDT_TYPE1_CMDSTATUS
mdefine_line|#define R_LDT_TYPE1_CMDSTATUS&t;0x0004
DECL|macro|R_LDT_TYPE1_CLASSREV
mdefine_line|#define R_LDT_TYPE1_CLASSREV&t;0x0008
DECL|macro|R_LDT_TYPE1_DEVHDR
mdefine_line|#define R_LDT_TYPE1_DEVHDR&t;0x000C
DECL|macro|R_LDT_TYPE1_BAR0
mdefine_line|#define R_LDT_TYPE1_BAR0&t;0x0010&t;/* not used */
DECL|macro|R_LDT_TYPE1_BAR1
mdefine_line|#define R_LDT_TYPE1_BAR1&t;0x0014&t;/* not used */
DECL|macro|R_LDT_TYPE1_BUSID
mdefine_line|#define R_LDT_TYPE1_BUSID&t;0x0018&t;/* bus ID register */
DECL|macro|R_LDT_TYPE1_SECSTATUS
mdefine_line|#define R_LDT_TYPE1_SECSTATUS&t;0x001C&t;/* secondary status / I/O base/limit */
DECL|macro|R_LDT_TYPE1_MEMLIMIT
mdefine_line|#define R_LDT_TYPE1_MEMLIMIT&t;0x0020
DECL|macro|R_LDT_TYPE1_PREFETCH
mdefine_line|#define R_LDT_TYPE1_PREFETCH&t;0x0024
DECL|macro|R_LDT_TYPE1_PREF_BASE
mdefine_line|#define R_LDT_TYPE1_PREF_BASE&t;0x0028
DECL|macro|R_LDT_TYPE1_PREF_LIMIT
mdefine_line|#define R_LDT_TYPE1_PREF_LIMIT&t;0x002C
DECL|macro|R_LDT_TYPE1_IOLIMIT
mdefine_line|#define R_LDT_TYPE1_IOLIMIT&t;0x0030
DECL|macro|R_LDT_TYPE1_CAPPTR
mdefine_line|#define R_LDT_TYPE1_CAPPTR&t;0x0034
DECL|macro|R_LDT_TYPE1_ROMADDR
mdefine_line|#define R_LDT_TYPE1_ROMADDR&t;0x0038
DECL|macro|R_LDT_TYPE1_BRCTL
mdefine_line|#define R_LDT_TYPE1_BRCTL&t;0x003C
DECL|macro|R_LDT_TYPE1_CMD
mdefine_line|#define R_LDT_TYPE1_CMD&t;&t;0x0040
DECL|macro|R_LDT_TYPE1_LINKCTRL
mdefine_line|#define R_LDT_TYPE1_LINKCTRL&t;0x0044
DECL|macro|R_LDT_TYPE1_LINKFREQ
mdefine_line|#define R_LDT_TYPE1_LINKFREQ&t;0x0048
DECL|macro|R_LDT_TYPE1_RESERVED1
mdefine_line|#define R_LDT_TYPE1_RESERVED1&t;0x004C
DECL|macro|R_LDT_TYPE1_SRICMD
mdefine_line|#define R_LDT_TYPE1_SRICMD&t;0x0050
DECL|macro|R_LDT_TYPE1_SRITXNUM
mdefine_line|#define R_LDT_TYPE1_SRITXNUM&t;0x0054
DECL|macro|R_LDT_TYPE1_SRIRXNUM
mdefine_line|#define R_LDT_TYPE1_SRIRXNUM&t;0x0058
DECL|macro|R_LDT_TYPE1_ERRSTATUS
mdefine_line|#define R_LDT_TYPE1_ERRSTATUS   0x0068
DECL|macro|R_LDT_TYPE1_SRICTRL
mdefine_line|#define R_LDT_TYPE1_SRICTRL&t;0x006C
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|R_LDT_TYPE1_ADDSTATUS
mdefine_line|#define R_LDT_TYPE1_ADDSTATUS&t;0x0070
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|R_LDT_TYPE1_TXBUFCNT
mdefine_line|#define R_LDT_TYPE1_TXBUFCNT&t;0x00C8
DECL|macro|R_LDT_TYPE1_EXPCRC
mdefine_line|#define R_LDT_TYPE1_EXPCRC&t;0x00DC
DECL|macro|R_LDT_TYPE1_RXCRC
mdefine_line|#define R_LDT_TYPE1_RXCRC&t;0x00F0
multiline_comment|/*&n; * LDT Device ID register&n; */
DECL|macro|S_LDT_DEVICEID_VENDOR
mdefine_line|#define S_LDT_DEVICEID_VENDOR&t;&t;0
DECL|macro|M_LDT_DEVICEID_VENDOR
mdefine_line|#define M_LDT_DEVICEID_VENDOR&t;&t;_SB_MAKEMASK_32(16,S_LDT_DEVICEID_VENDOR)
DECL|macro|V_LDT_DEVICEID_VENDOR
mdefine_line|#define V_LDT_DEVICEID_VENDOR(x)&t;_SB_MAKEVALUE_32(x,S_LDT_DEVICEID_VENDOR)
DECL|macro|G_LDT_DEVICEID_VENDOR
mdefine_line|#define G_LDT_DEVICEID_VENDOR(x)&t;_SB_GETVALUE_32(x,S_LDT_DEVICEID_VENDOR,M_LDT_DEVICEID_VENDOR)
DECL|macro|S_LDT_DEVICEID_DEVICEID
mdefine_line|#define S_LDT_DEVICEID_DEVICEID&t;&t;16
DECL|macro|M_LDT_DEVICEID_DEVICEID
mdefine_line|#define M_LDT_DEVICEID_DEVICEID&t;&t;_SB_MAKEMASK_32(16,S_LDT_DEVICEID_DEVICEID)
DECL|macro|V_LDT_DEVICEID_DEVICEID
mdefine_line|#define V_LDT_DEVICEID_DEVICEID(x)&t;_SB_MAKEVALUE_32(x,S_LDT_DEVICEID_DEVICEID)
DECL|macro|G_LDT_DEVICEID_DEVICEID
mdefine_line|#define G_LDT_DEVICEID_DEVICEID(x)&t;_SB_GETVALUE_32(x,S_LDT_DEVICEID_DEVICEID,M_LDT_DEVICEID_DEVICEID)
multiline_comment|/*&n; * LDT Command Register (Table 8-13)&n; */
DECL|macro|M_LDT_CMD_IOSPACE_EN
mdefine_line|#define M_LDT_CMD_IOSPACE_EN&t;&t;_SB_MAKEMASK1_32(0)
DECL|macro|M_LDT_CMD_MEMSPACE_EN
mdefine_line|#define M_LDT_CMD_MEMSPACE_EN&t;&t;_SB_MAKEMASK1_32(1)
DECL|macro|M_LDT_CMD_MASTER_EN
mdefine_line|#define M_LDT_CMD_MASTER_EN&t;&t;_SB_MAKEMASK1_32(2)
DECL|macro|M_LDT_CMD_SPECCYC_EN
mdefine_line|#define M_LDT_CMD_SPECCYC_EN&t;&t;_SB_MAKEMASK1_32(3)
DECL|macro|M_LDT_CMD_MEMWRINV_EN
mdefine_line|#define M_LDT_CMD_MEMWRINV_EN&t;&t;_SB_MAKEMASK1_32(4)
DECL|macro|M_LDT_CMD_VGAPALSNP_EN
mdefine_line|#define M_LDT_CMD_VGAPALSNP_EN&t;&t;_SB_MAKEMASK1_32(5)
DECL|macro|M_LDT_CMD_PARERRRESP
mdefine_line|#define M_LDT_CMD_PARERRRESP&t;&t;_SB_MAKEMASK1_32(6)
DECL|macro|M_LDT_CMD_WAITCYCCTRL
mdefine_line|#define M_LDT_CMD_WAITCYCCTRL&t;&t;_SB_MAKEMASK1_32(7)
DECL|macro|M_LDT_CMD_SERR_EN
mdefine_line|#define M_LDT_CMD_SERR_EN&t;&t;_SB_MAKEMASK1_32(8)
DECL|macro|M_LDT_CMD_FASTB2B_EN
mdefine_line|#define M_LDT_CMD_FASTB2B_EN&t;&t;_SB_MAKEMASK1_32(9)
multiline_comment|/*&n; * LDT class and revision registers&n; */
DECL|macro|S_LDT_CLASSREV_REV
mdefine_line|#define S_LDT_CLASSREV_REV&t;&t;0
DECL|macro|M_LDT_CLASSREV_REV
mdefine_line|#define M_LDT_CLASSREV_REV&t;&t;_SB_MAKEMASK_32(8,S_LDT_CLASSREV_REV)
DECL|macro|V_LDT_CLASSREV_REV
mdefine_line|#define V_LDT_CLASSREV_REV(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_CLASSREV_REV)
DECL|macro|G_LDT_CLASSREV_REV
mdefine_line|#define G_LDT_CLASSREV_REV(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_CLASSREV_REV,M_LDT_CLASSREV_REV)
DECL|macro|S_LDT_CLASSREV_CLASS
mdefine_line|#define S_LDT_CLASSREV_CLASS&t;&t;8
DECL|macro|M_LDT_CLASSREV_CLASS
mdefine_line|#define M_LDT_CLASSREV_CLASS&t;&t;_SB_MAKEMASK_32(24,S_LDT_CLASSREV_CLASS)
DECL|macro|V_LDT_CLASSREV_CLASS
mdefine_line|#define V_LDT_CLASSREV_CLASS(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_CLASSREV_CLASS)
DECL|macro|G_LDT_CLASSREV_CLASS
mdefine_line|#define G_LDT_CLASSREV_CLASS(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_CLASSREV_CLASS,M_LDT_CLASSREV_CLASS)
DECL|macro|K_LDT_REV
mdefine_line|#define K_LDT_REV&t;&t;&t;0x01
DECL|macro|K_LDT_CLASS
mdefine_line|#define K_LDT_CLASS&t;&t;&t;0x060000
multiline_comment|/*&n; * Device Header (offset 0x0C)&n; */
DECL|macro|S_LDT_DEVHDR_CLINESZ
mdefine_line|#define S_LDT_DEVHDR_CLINESZ&t;&t;0
DECL|macro|M_LDT_DEVHDR_CLINESZ
mdefine_line|#define M_LDT_DEVHDR_CLINESZ&t;&t;_SB_MAKEMASK_32(8,S_LDT_DEVHDR_CLINESZ)
DECL|macro|V_LDT_DEVHDR_CLINESZ
mdefine_line|#define V_LDT_DEVHDR_CLINESZ(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_DEVHDR_CLINESZ)
DECL|macro|G_LDT_DEVHDR_CLINESZ
mdefine_line|#define G_LDT_DEVHDR_CLINESZ(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_DEVHDR_CLINESZ,M_LDT_DEVHDR_CLINESZ)
DECL|macro|S_LDT_DEVHDR_LATTMR
mdefine_line|#define S_LDT_DEVHDR_LATTMR&t;&t;8
DECL|macro|M_LDT_DEVHDR_LATTMR
mdefine_line|#define M_LDT_DEVHDR_LATTMR&t;&t;_SB_MAKEMASK_32(8,S_LDT_DEVHDR_LATTMR)
DECL|macro|V_LDT_DEVHDR_LATTMR
mdefine_line|#define V_LDT_DEVHDR_LATTMR(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_DEVHDR_LATTMR)
DECL|macro|G_LDT_DEVHDR_LATTMR
mdefine_line|#define G_LDT_DEVHDR_LATTMR(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_DEVHDR_LATTMR,M_LDT_DEVHDR_LATTMR)
DECL|macro|S_LDT_DEVHDR_HDRTYPE
mdefine_line|#define S_LDT_DEVHDR_HDRTYPE&t;&t;16
DECL|macro|M_LDT_DEVHDR_HDRTYPE
mdefine_line|#define M_LDT_DEVHDR_HDRTYPE&t;&t;_SB_MAKEMASK_32(8,S_LDT_DEVHDR_HDRTYPE)
DECL|macro|V_LDT_DEVHDR_HDRTYPE
mdefine_line|#define V_LDT_DEVHDR_HDRTYPE(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_DEVHDR_HDRTYPE)
DECL|macro|G_LDT_DEVHDR_HDRTYPE
mdefine_line|#define G_LDT_DEVHDR_HDRTYPE(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_DEVHDR_HDRTYPE,M_LDT_DEVHDR_HDRTYPE)
DECL|macro|K_LDT_DEVHDR_HDRTYPE_TYPE1
mdefine_line|#define K_LDT_DEVHDR_HDRTYPE_TYPE1&t;1
DECL|macro|S_LDT_DEVHDR_BIST
mdefine_line|#define S_LDT_DEVHDR_BIST&t;&t;24
DECL|macro|M_LDT_DEVHDR_BIST
mdefine_line|#define M_LDT_DEVHDR_BIST&t;&t;_SB_MAKEMASK_32(8,S_LDT_DEVHDR_BIST)
DECL|macro|V_LDT_DEVHDR_BIST
mdefine_line|#define V_LDT_DEVHDR_BIST(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_DEVHDR_BIST)
DECL|macro|G_LDT_DEVHDR_BIST
mdefine_line|#define G_LDT_DEVHDR_BIST(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_DEVHDR_BIST,M_LDT_DEVHDR_BIST)
multiline_comment|/*&n; * LDT Status Register (Table 8-14).  Note that these constants&n; * assume you&squot;ve read the command and status register &n; * together (32-bit read at offset 0x04)&n; *&n; * These bits also apply to the secondary status&n; * register (Table 8-15), offset 0x1C&n; */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_LDT_STATUS_VGAEN
mdefine_line|#define M_LDT_STATUS_VGAEN&t;&t;_SB_MAKEMASK1_32(3)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|M_LDT_STATUS_CAPLIST
mdefine_line|#define M_LDT_STATUS_CAPLIST&t;&t;_SB_MAKEMASK1_32(20)
DECL|macro|M_LDT_STATUS_66MHZCAP
mdefine_line|#define M_LDT_STATUS_66MHZCAP&t;&t;_SB_MAKEMASK1_32(21)
DECL|macro|M_LDT_STATUS_RESERVED2
mdefine_line|#define M_LDT_STATUS_RESERVED2&t;&t;_SB_MAKEMASK1_32(22)
DECL|macro|M_LDT_STATUS_FASTB2BCAP
mdefine_line|#define M_LDT_STATUS_FASTB2BCAP&t;&t;_SB_MAKEMASK1_32(23)
DECL|macro|M_LDT_STATUS_MSTRDPARERR
mdefine_line|#define M_LDT_STATUS_MSTRDPARERR&t;_SB_MAKEMASK1_32(24)
DECL|macro|S_LDT_STATUS_DEVSELTIMING
mdefine_line|#define S_LDT_STATUS_DEVSELTIMING&t;25
DECL|macro|M_LDT_STATUS_DEVSELTIMING
mdefine_line|#define M_LDT_STATUS_DEVSELTIMING&t;_SB_MAKEMASK_32(2,S_LDT_STATUS_DEVSELTIMING)
DECL|macro|V_LDT_STATUS_DEVSELTIMING
mdefine_line|#define V_LDT_STATUS_DEVSELTIMING(x)&t;_SB_MAKEVALUE_32(x,S_LDT_STATUS_DEVSELTIMING)
DECL|macro|G_LDT_STATUS_DEVSELTIMING
mdefine_line|#define G_LDT_STATUS_DEVSELTIMING(x)&t;_SB_GETVALUE_32(x,S_LDT_STATUS_DEVSELTIMING,M_LDT_STATUS_DEVSELTIMING)
DECL|macro|M_LDT_STATUS_SIGDTGTABORT
mdefine_line|#define M_LDT_STATUS_SIGDTGTABORT&t;_SB_MAKEMASK1_32(27)
DECL|macro|M_LDT_STATUS_RCVDTGTABORT
mdefine_line|#define M_LDT_STATUS_RCVDTGTABORT&t;_SB_MAKEMASK1_32(28)
DECL|macro|M_LDT_STATUS_RCVDMSTRABORT
mdefine_line|#define M_LDT_STATUS_RCVDMSTRABORT&t;_SB_MAKEMASK1_32(29)
DECL|macro|M_LDT_STATUS_SIGDSERR
mdefine_line|#define M_LDT_STATUS_SIGDSERR&t;&t;_SB_MAKEMASK1_32(30)
DECL|macro|M_LDT_STATUS_DETPARERR
mdefine_line|#define M_LDT_STATUS_DETPARERR&t;&t;_SB_MAKEMASK1_32(31)
multiline_comment|/*&n; * Bridge Control Register (Table 8-16).  Note that these &n; * constants assume you&squot;ve read the register as a 32-bit &n; * read (offset 0x3C)&n; */
DECL|macro|M_LDT_BRCTL_PARERRRESP_EN
mdefine_line|#define M_LDT_BRCTL_PARERRRESP_EN&t;_SB_MAKEMASK1_32(16)
DECL|macro|M_LDT_BRCTL_SERR_EN
mdefine_line|#define M_LDT_BRCTL_SERR_EN&t;&t;_SB_MAKEMASK1_32(17)
DECL|macro|M_LDT_BRCTL_ISA_EN
mdefine_line|#define M_LDT_BRCTL_ISA_EN&t;&t;_SB_MAKEMASK1_32(18)
DECL|macro|M_LDT_BRCTL_VGA_EN
mdefine_line|#define M_LDT_BRCTL_VGA_EN&t;&t;_SB_MAKEMASK1_32(19)
DECL|macro|M_LDT_BRCTL_MSTRABORTMODE
mdefine_line|#define M_LDT_BRCTL_MSTRABORTMODE&t;_SB_MAKEMASK1_32(21)
DECL|macro|M_LDT_BRCTL_SECBUSRESET
mdefine_line|#define M_LDT_BRCTL_SECBUSRESET&t;&t;_SB_MAKEMASK1_32(22)
DECL|macro|M_LDT_BRCTL_FASTB2B_EN
mdefine_line|#define M_LDT_BRCTL_FASTB2B_EN&t;&t;_SB_MAKEMASK1_32(23)
DECL|macro|M_LDT_BRCTL_PRIDISCARD
mdefine_line|#define M_LDT_BRCTL_PRIDISCARD&t;&t;_SB_MAKEMASK1_32(24)
DECL|macro|M_LDT_BRCTL_SECDISCARD
mdefine_line|#define M_LDT_BRCTL_SECDISCARD&t;&t;_SB_MAKEMASK1_32(25)
DECL|macro|M_LDT_BRCTL_DISCARDSTAT
mdefine_line|#define M_LDT_BRCTL_DISCARDSTAT&t;&t;_SB_MAKEMASK1_32(26)
DECL|macro|M_LDT_BRCTL_DISCARDSERR_EN
mdefine_line|#define M_LDT_BRCTL_DISCARDSERR_EN&t;_SB_MAKEMASK1_32(27)
multiline_comment|/*&n; * LDT Command Register (Table 8-17).  Note that these constants&n; * assume you&squot;ve read the command and status register together&n; * 32-bit read at offset 0x40&n; */
DECL|macro|M_LDT_CMD_WARMRESET
mdefine_line|#define M_LDT_CMD_WARMRESET&t;&t;_SB_MAKEMASK1_32(16)
DECL|macro|M_LDT_CMD_DOUBLEENDED
mdefine_line|#define M_LDT_CMD_DOUBLEENDED&t;&t;_SB_MAKEMASK1_32(17)
DECL|macro|S_LDT_CMD_CAPTYPE
mdefine_line|#define S_LDT_CMD_CAPTYPE&t;&t;29
DECL|macro|M_LDT_CMD_CAPTYPE
mdefine_line|#define M_LDT_CMD_CAPTYPE&t;&t;_SB_MAKEMASK_32(3,S_LDT_CMD_CAPTYPE)
DECL|macro|V_LDT_CMD_CAPTYPE
mdefine_line|#define V_LDT_CMD_CAPTYPE(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_CMD_CAPTYPE)
DECL|macro|G_LDT_CMD_CAPTYPE
mdefine_line|#define G_LDT_CMD_CAPTYPE(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_CMD_CAPTYPE,M_LDT_CMD_CAPTYPE)
multiline_comment|/*&n; * LDT link control register (Table 8-18), and (Table 8-19)&n; */
DECL|macro|M_LDT_LINKCTRL_CAPSYNCFLOOD_EN
mdefine_line|#define M_LDT_LINKCTRL_CAPSYNCFLOOD_EN&t;_SB_MAKEMASK1_32(1)
DECL|macro|M_LDT_LINKCTRL_CRCSTARTTEST
mdefine_line|#define M_LDT_LINKCTRL_CRCSTARTTEST&t;_SB_MAKEMASK1_32(2)
DECL|macro|M_LDT_LINKCTRL_CRCFORCEERR
mdefine_line|#define M_LDT_LINKCTRL_CRCFORCEERR&t;_SB_MAKEMASK1_32(3)
DECL|macro|M_LDT_LINKCTRL_LINKFAIL
mdefine_line|#define M_LDT_LINKCTRL_LINKFAIL&t;&t;_SB_MAKEMASK1_32(4)
DECL|macro|M_LDT_LINKCTRL_INITDONE
mdefine_line|#define M_LDT_LINKCTRL_INITDONE&t;&t;_SB_MAKEMASK1_32(5)
DECL|macro|M_LDT_LINKCTRL_EOC
mdefine_line|#define M_LDT_LINKCTRL_EOC&t;&t;_SB_MAKEMASK1_32(6)
DECL|macro|M_LDT_LINKCTRL_XMITOFF
mdefine_line|#define M_LDT_LINKCTRL_XMITOFF&t;&t;_SB_MAKEMASK1_32(7)
DECL|macro|S_LDT_LINKCTRL_CRCERR
mdefine_line|#define S_LDT_LINKCTRL_CRCERR&t;&t;8
DECL|macro|M_LDT_LINKCTRL_CRCERR
mdefine_line|#define M_LDT_LINKCTRL_CRCERR&t;&t;_SB_MAKEMASK_32(4,S_LDT_LINKCTRL_CRCERR)
DECL|macro|V_LDT_LINKCTRL_CRCERR
mdefine_line|#define V_LDT_LINKCTRL_CRCERR(x)&t;_SB_MAKEVALUE_32(x,S_LDT_LINKCTRL_CRCERR)
DECL|macro|G_LDT_LINKCTRL_CRCERR
mdefine_line|#define G_LDT_LINKCTRL_CRCERR(x)&t;_SB_GETVALUE_32(x,S_LDT_LINKCTRL_CRCERR,M_LDT_LINKCTRL_CRCERR)
DECL|macro|S_LDT_LINKCTRL_MAXIN
mdefine_line|#define S_LDT_LINKCTRL_MAXIN&t;&t;16
DECL|macro|M_LDT_LINKCTRL_MAXIN
mdefine_line|#define M_LDT_LINKCTRL_MAXIN&t;&t;_SB_MAKEMASK_32(3,S_LDT_LINKCTRL_MAXIN)
DECL|macro|V_LDT_LINKCTRL_MAXIN
mdefine_line|#define V_LDT_LINKCTRL_MAXIN(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_LINKCTRL_MAXIN)
DECL|macro|G_LDT_LINKCTRL_MAXIN
mdefine_line|#define G_LDT_LINKCTRL_MAXIN(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_LINKCTRL_MAXIN,M_LDT_LINKCTRL_MAXIN)
DECL|macro|M_LDT_LINKCTRL_DWFCLN
mdefine_line|#define M_LDT_LINKCTRL_DWFCLN&t;&t;_SB_MAKEMASK1_32(19)
DECL|macro|S_LDT_LINKCTRL_MAXOUT
mdefine_line|#define S_LDT_LINKCTRL_MAXOUT&t;&t;20
DECL|macro|M_LDT_LINKCTRL_MAXOUT
mdefine_line|#define M_LDT_LINKCTRL_MAXOUT&t;&t;_SB_MAKEMASK_32(3,S_LDT_LINKCTRL_MAXOUT)
DECL|macro|V_LDT_LINKCTRL_MAXOUT
mdefine_line|#define V_LDT_LINKCTRL_MAXOUT(x)&t;_SB_MAKEVALUE_32(x,S_LDT_LINKCTRL_MAXOUT)
DECL|macro|G_LDT_LINKCTRL_MAXOUT
mdefine_line|#define G_LDT_LINKCTRL_MAXOUT(x)&t;_SB_GETVALUE_32(x,S_LDT_LINKCTRL_MAXOUT,M_LDT_LINKCTRL_MAXOUT)
DECL|macro|M_LDT_LINKCTRL_DWFCOUT
mdefine_line|#define M_LDT_LINKCTRL_DWFCOUT&t;&t;_SB_MAKEMASK1_32(23)
DECL|macro|S_LDT_LINKCTRL_WIDTHIN
mdefine_line|#define S_LDT_LINKCTRL_WIDTHIN&t;&t;24
DECL|macro|M_LDT_LINKCTRL_WIDTHIN
mdefine_line|#define M_LDT_LINKCTRL_WIDTHIN&t;&t;_SB_MAKEMASK_32(3,S_LDT_LINKCTRL_WIDTHIN)
DECL|macro|V_LDT_LINKCTRL_WIDTHIN
mdefine_line|#define V_LDT_LINKCTRL_WIDTHIN(x)&t;_SB_MAKEVALUE_32(x,S_LDT_LINKCTRL_WIDTHIN)
DECL|macro|G_LDT_LINKCTRL_WIDTHIN
mdefine_line|#define G_LDT_LINKCTRL_WIDTHIN(x)&t;_SB_GETVALUE_32(x,S_LDT_LINKCTRL_WIDTHIN,M_LDT_LINKCTRL_WIDTHIN)
DECL|macro|M_LDT_LINKCTRL_DWFCLIN_EN
mdefine_line|#define M_LDT_LINKCTRL_DWFCLIN_EN&t;_SB_MAKEMASK1_32(27)
DECL|macro|S_LDT_LINKCTRL_WIDTHOUT
mdefine_line|#define S_LDT_LINKCTRL_WIDTHOUT&t;&t;28
DECL|macro|M_LDT_LINKCTRL_WIDTHOUT
mdefine_line|#define M_LDT_LINKCTRL_WIDTHOUT&t;&t;_SB_MAKEMASK_32(3,S_LDT_LINKCTRL_WIDTHOUT)
DECL|macro|V_LDT_LINKCTRL_WIDTHOUT
mdefine_line|#define V_LDT_LINKCTRL_WIDTHOUT(x)&t;_SB_MAKEVALUE_32(x,S_LDT_LINKCTRL_WIDTHOUT)
DECL|macro|G_LDT_LINKCTRL_WIDTHOUT
mdefine_line|#define G_LDT_LINKCTRL_WIDTHOUT(x)&t;_SB_GETVALUE_32(x,S_LDT_LINKCTRL_WIDTHOUT,M_LDT_LINKCTRL_WIDTHOUT)
DECL|macro|M_LDT_LINKCTRL_DWFCOUT_EN
mdefine_line|#define M_LDT_LINKCTRL_DWFCOUT_EN&t;_SB_MAKEMASK1_32(31)
multiline_comment|/*&n; * LDT Link frequency register  (Table 8-20) offset 0x48&n; */
DECL|macro|S_LDT_LINKFREQ_FREQ
mdefine_line|#define S_LDT_LINKFREQ_FREQ&t;&t;8
DECL|macro|M_LDT_LINKFREQ_FREQ
mdefine_line|#define M_LDT_LINKFREQ_FREQ&t;&t;_SB_MAKEMASK_32(4,S_LDT_LINKFREQ_FREQ)
DECL|macro|V_LDT_LINKFREQ_FREQ
mdefine_line|#define V_LDT_LINKFREQ_FREQ(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_LINKFREQ_FREQ)
DECL|macro|G_LDT_LINKFREQ_FREQ
mdefine_line|#define G_LDT_LINKFREQ_FREQ(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_LINKFREQ_FREQ,M_LDT_LINKFREQ_FREQ)
DECL|macro|K_LDT_LINKFREQ_200MHZ
mdefine_line|#define K_LDT_LINKFREQ_200MHZ&t;&t;0
DECL|macro|K_LDT_LINKFREQ_300MHZ
mdefine_line|#define K_LDT_LINKFREQ_300MHZ&t;&t;1
DECL|macro|K_LDT_LINKFREQ_400MHZ
mdefine_line|#define K_LDT_LINKFREQ_400MHZ&t;&t;2
DECL|macro|K_LDT_LINKFREQ_500MHZ
mdefine_line|#define K_LDT_LINKFREQ_500MHZ&t;&t;3
DECL|macro|K_LDT_LINKFREQ_600MHZ
mdefine_line|#define K_LDT_LINKFREQ_600MHZ&t;&t;4
DECL|macro|K_LDT_LINKFREQ_800MHZ
mdefine_line|#define K_LDT_LINKFREQ_800MHZ&t;&t;5
DECL|macro|K_LDT_LINKFREQ_1000MHZ
mdefine_line|#define K_LDT_LINKFREQ_1000MHZ&t;&t;6
multiline_comment|/*&n; * LDT SRI Command Register (Table 8-21).  Note that these constants&n; * assume you&squot;ve read the command and status register together&n; * 32-bit read at offset 0x50&n; */
DECL|macro|M_LDT_SRICMD_SIPREADY
mdefine_line|#define M_LDT_SRICMD_SIPREADY&t;&t;_SB_MAKEMASK1_32(16)
DECL|macro|M_LDT_SRICMD_SYNCPTRCTL
mdefine_line|#define M_LDT_SRICMD_SYNCPTRCTL&t;&t;_SB_MAKEMASK1_32(17)
DECL|macro|M_LDT_SRICMD_REDUCESYNCZERO
mdefine_line|#define M_LDT_SRICMD_REDUCESYNCZERO&t;_SB_MAKEMASK1_32(18)
macro_line|#if SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
DECL|macro|M_LDT_SRICMD_DISSTARVATIONCNT
mdefine_line|#define M_LDT_SRICMD_DISSTARVATIONCNT&t;_SB_MAKEMASK1_32(19)&t;/* PASS1 */
macro_line|#endif /* up to 1250 PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_LDT_SRICMD_DISMULTTXVLD
mdefine_line|#define M_LDT_SRICMD_DISMULTTXVLD&t;_SB_MAKEMASK1_32(19)
DECL|macro|M_LDT_SRICMD_EXPENDIAN
mdefine_line|#define M_LDT_SRICMD_EXPENDIAN&t;&t;_SB_MAKEMASK1_32(26)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_LDT_SRICMD_RXMARGIN
mdefine_line|#define S_LDT_SRICMD_RXMARGIN&t;&t;20
DECL|macro|M_LDT_SRICMD_RXMARGIN
mdefine_line|#define M_LDT_SRICMD_RXMARGIN&t;&t;_SB_MAKEMASK_32(5,S_LDT_SRICMD_RXMARGIN)
DECL|macro|V_LDT_SRICMD_RXMARGIN
mdefine_line|#define V_LDT_SRICMD_RXMARGIN(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICMD_RXMARGIN)
DECL|macro|G_LDT_SRICMD_RXMARGIN
mdefine_line|#define G_LDT_SRICMD_RXMARGIN(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICMD_RXMARGIN,M_LDT_SRICMD_RXMARGIN)
DECL|macro|M_LDT_SRICMD_LDTPLLCOMPAT
mdefine_line|#define M_LDT_SRICMD_LDTPLLCOMPAT&t;_SB_MAKEMASK1_32(25)
DECL|macro|S_LDT_SRICMD_TXINITIALOFFSET
mdefine_line|#define S_LDT_SRICMD_TXINITIALOFFSET&t;28
DECL|macro|M_LDT_SRICMD_TXINITIALOFFSET
mdefine_line|#define M_LDT_SRICMD_TXINITIALOFFSET&t;_SB_MAKEMASK_32(3,S_LDT_SRICMD_TXINITIALOFFSET)
DECL|macro|V_LDT_SRICMD_TXINITIALOFFSET
mdefine_line|#define V_LDT_SRICMD_TXINITIALOFFSET(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICMD_TXINITIALOFFSET)
DECL|macro|G_LDT_SRICMD_TXINITIALOFFSET
mdefine_line|#define G_LDT_SRICMD_TXINITIALOFFSET(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICMD_TXINITIALOFFSET,M_LDT_SRICMD_TXINITIALOFFSET)
DECL|macro|M_LDT_SRICMD_LINKFREQDIRECT
mdefine_line|#define M_LDT_SRICMD_LINKFREQDIRECT&t;_SB_MAKEMASK1_32(31)
multiline_comment|/*&n; * LDT Error control and status register (Table 8-22) (Table 8-23)&n; */
DECL|macro|M_LDT_ERRCTL_PROTFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_PROTFATAL_EN&t;_SB_MAKEMASK1_32(0)
DECL|macro|M_LDT_ERRCTL_PROTNONFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_PROTNONFATAL_EN&t;_SB_MAKEMASK1_32(1)
DECL|macro|M_LDT_ERRCTL_PROTSYNCFLOOD_EN
mdefine_line|#define M_LDT_ERRCTL_PROTSYNCFLOOD_EN&t;_SB_MAKEMASK1_32(2)
DECL|macro|M_LDT_ERRCTL_OVFFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_OVFFATAL_EN&t;_SB_MAKEMASK1_32(3)
DECL|macro|M_LDT_ERRCTL_OVFNONFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_OVFNONFATAL_EN&t;_SB_MAKEMASK1_32(4)
DECL|macro|M_LDT_ERRCTL_OVFSYNCFLOOD_EN
mdefine_line|#define M_LDT_ERRCTL_OVFSYNCFLOOD_EN&t;_SB_MAKEMASK1_32(5)
DECL|macro|M_LDT_ERRCTL_EOCNXAFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_EOCNXAFATAL_EN&t;_SB_MAKEMASK1_32(6)
DECL|macro|M_LDT_ERRCTL_EOCNXANONFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_EOCNXANONFATAL_EN&t;_SB_MAKEMASK1_32(7)
DECL|macro|M_LDT_ERRCTL_EOCNXASYNCFLOOD_EN
mdefine_line|#define M_LDT_ERRCTL_EOCNXASYNCFLOOD_EN&t;_SB_MAKEMASK1_32(8)
DECL|macro|M_LDT_ERRCTL_CRCFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_CRCFATAL_EN&t;_SB_MAKEMASK1_32(9)
DECL|macro|M_LDT_ERRCTL_CRCNONFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_CRCNONFATAL_EN&t;_SB_MAKEMASK1_32(10)
DECL|macro|M_LDT_ERRCTL_SERRFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_SERRFATAL_EN&t;_SB_MAKEMASK1_32(11)
DECL|macro|M_LDT_ERRCTL_SRCTAGFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_SRCTAGFATAL_EN&t;_SB_MAKEMASK1_32(12)
DECL|macro|M_LDT_ERRCTL_SRCTAGNONFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_SRCTAGNONFATAL_EN&t;_SB_MAKEMASK1_32(13)
DECL|macro|M_LDT_ERRCTL_SRCTAGSYNCFLOOD_EN
mdefine_line|#define M_LDT_ERRCTL_SRCTAGSYNCFLOOD_EN&t;_SB_MAKEMASK1_32(14)
DECL|macro|M_LDT_ERRCTL_MAPNXAFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_MAPNXAFATAL_EN&t;_SB_MAKEMASK1_32(15)
DECL|macro|M_LDT_ERRCTL_MAPNXANONFATAL_EN
mdefine_line|#define M_LDT_ERRCTL_MAPNXANONFATAL_EN&t;_SB_MAKEMASK1_32(16)
DECL|macro|M_LDT_ERRCTL_MAPNXASYNCFLOOD_EN
mdefine_line|#define M_LDT_ERRCTL_MAPNXASYNCFLOOD_EN&t;_SB_MAKEMASK1_32(17)
DECL|macro|M_LDT_ERRCTL_PROTOERR
mdefine_line|#define M_LDT_ERRCTL_PROTOERR&t;&t;_SB_MAKEMASK1_32(24)
DECL|macro|M_LDT_ERRCTL_OVFERR
mdefine_line|#define M_LDT_ERRCTL_OVFERR&t;&t;_SB_MAKEMASK1_32(25)
DECL|macro|M_LDT_ERRCTL_EOCNXAERR
mdefine_line|#define M_LDT_ERRCTL_EOCNXAERR&t;&t;_SB_MAKEMASK1_32(26)
DECL|macro|M_LDT_ERRCTL_SRCTAGERR
mdefine_line|#define M_LDT_ERRCTL_SRCTAGERR&t;&t;_SB_MAKEMASK1_32(27)
DECL|macro|M_LDT_ERRCTL_MAPNXAERR
mdefine_line|#define M_LDT_ERRCTL_MAPNXAERR&t;&t;_SB_MAKEMASK1_32(28)
multiline_comment|/*&n; * SRI Control register (Table 8-24, 8-25)  Offset 0x6C&n; */
DECL|macro|S_LDT_SRICTRL_NEEDRESP
mdefine_line|#define S_LDT_SRICTRL_NEEDRESP&t;&t;0
DECL|macro|M_LDT_SRICTRL_NEEDRESP
mdefine_line|#define M_LDT_SRICTRL_NEEDRESP&t;&t;_SB_MAKEMASK_32(2,S_LDT_SRICTRL_NEEDRESP)
DECL|macro|V_LDT_SRICTRL_NEEDRESP
mdefine_line|#define V_LDT_SRICTRL_NEEDRESP(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_NEEDRESP)
DECL|macro|G_LDT_SRICTRL_NEEDRESP
mdefine_line|#define G_LDT_SRICTRL_NEEDRESP(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_NEEDRESP,M_LDT_SRICTRL_NEEDRESP)
DECL|macro|S_LDT_SRICTRL_NEEDNPREQ
mdefine_line|#define S_LDT_SRICTRL_NEEDNPREQ&t;&t;2
DECL|macro|M_LDT_SRICTRL_NEEDNPREQ
mdefine_line|#define M_LDT_SRICTRL_NEEDNPREQ&t;&t;_SB_MAKEMASK_32(2,S_LDT_SRICTRL_NEEDNPREQ)
DECL|macro|V_LDT_SRICTRL_NEEDNPREQ
mdefine_line|#define V_LDT_SRICTRL_NEEDNPREQ(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_NEEDNPREQ)
DECL|macro|G_LDT_SRICTRL_NEEDNPREQ
mdefine_line|#define G_LDT_SRICTRL_NEEDNPREQ(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_NEEDNPREQ,M_LDT_SRICTRL_NEEDNPREQ)
DECL|macro|S_LDT_SRICTRL_NEEDPREQ
mdefine_line|#define S_LDT_SRICTRL_NEEDPREQ&t;&t;4
DECL|macro|M_LDT_SRICTRL_NEEDPREQ
mdefine_line|#define M_LDT_SRICTRL_NEEDPREQ&t;&t;_SB_MAKEMASK_32(2,S_LDT_SRICTRL_NEEDPREQ)
DECL|macro|V_LDT_SRICTRL_NEEDPREQ
mdefine_line|#define V_LDT_SRICTRL_NEEDPREQ(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_NEEDPREQ)
DECL|macro|G_LDT_SRICTRL_NEEDPREQ
mdefine_line|#define G_LDT_SRICTRL_NEEDPREQ(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_NEEDPREQ,M_LDT_SRICTRL_NEEDPREQ)
DECL|macro|S_LDT_SRICTRL_WANTRESP
mdefine_line|#define S_LDT_SRICTRL_WANTRESP&t;&t;8
DECL|macro|M_LDT_SRICTRL_WANTRESP
mdefine_line|#define M_LDT_SRICTRL_WANTRESP&t;&t;_SB_MAKEMASK_32(2,S_LDT_SRICTRL_WANTRESP)
DECL|macro|V_LDT_SRICTRL_WANTRESP
mdefine_line|#define V_LDT_SRICTRL_WANTRESP(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_WANTRESP)
DECL|macro|G_LDT_SRICTRL_WANTRESP
mdefine_line|#define G_LDT_SRICTRL_WANTRESP(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_WANTRESP,M_LDT_SRICTRL_WANTRESP)
DECL|macro|S_LDT_SRICTRL_WANTNPREQ
mdefine_line|#define S_LDT_SRICTRL_WANTNPREQ&t;&t;10
DECL|macro|M_LDT_SRICTRL_WANTNPREQ
mdefine_line|#define M_LDT_SRICTRL_WANTNPREQ&t;&t;_SB_MAKEMASK_32(2,S_LDT_SRICTRL_WANTNPREQ)
DECL|macro|V_LDT_SRICTRL_WANTNPREQ
mdefine_line|#define V_LDT_SRICTRL_WANTNPREQ(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_WANTNPREQ)
DECL|macro|G_LDT_SRICTRL_WANTNPREQ
mdefine_line|#define G_LDT_SRICTRL_WANTNPREQ(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_WANTNPREQ,M_LDT_SRICTRL_WANTNPREQ)
DECL|macro|S_LDT_SRICTRL_WANTPREQ
mdefine_line|#define S_LDT_SRICTRL_WANTPREQ&t;&t;12
DECL|macro|M_LDT_SRICTRL_WANTPREQ
mdefine_line|#define M_LDT_SRICTRL_WANTPREQ&t;&t;_SB_MAKEMASK_32(2,S_LDT_SRICTRL_WANTPREQ)
DECL|macro|V_LDT_SRICTRL_WANTPREQ
mdefine_line|#define V_LDT_SRICTRL_WANTPREQ(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_WANTPREQ)
DECL|macro|G_LDT_SRICTRL_WANTPREQ
mdefine_line|#define G_LDT_SRICTRL_WANTPREQ(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_WANTPREQ,M_LDT_SRICTRL_WANTPREQ)
DECL|macro|S_LDT_SRICTRL_BUFRELSPACE
mdefine_line|#define S_LDT_SRICTRL_BUFRELSPACE&t;16
DECL|macro|M_LDT_SRICTRL_BUFRELSPACE
mdefine_line|#define M_LDT_SRICTRL_BUFRELSPACE&t;_SB_MAKEMASK_32(4,S_LDT_SRICTRL_BUFRELSPACE)
DECL|macro|V_LDT_SRICTRL_BUFRELSPACE
mdefine_line|#define V_LDT_SRICTRL_BUFRELSPACE(x)&t;_SB_MAKEVALUE_32(x,S_LDT_SRICTRL_BUFRELSPACE)
DECL|macro|G_LDT_SRICTRL_BUFRELSPACE
mdefine_line|#define G_LDT_SRICTRL_BUFRELSPACE(x)&t;_SB_GETVALUE_32(x,S_LDT_SRICTRL_BUFRELSPACE,M_LDT_SRICTRL_BUFRELSPACE)
multiline_comment|/*&n; * LDT SRI Transmit Buffer Count register (Table 8-26)&n; */
DECL|macro|S_LDT_TXBUFCNT_PCMD
mdefine_line|#define S_LDT_TXBUFCNT_PCMD&t;&t;0
DECL|macro|M_LDT_TXBUFCNT_PCMD
mdefine_line|#define M_LDT_TXBUFCNT_PCMD&t;&t;_SB_MAKEMASK_32(4,S_LDT_TXBUFCNT_PCMD)
DECL|macro|V_LDT_TXBUFCNT_PCMD
mdefine_line|#define V_LDT_TXBUFCNT_PCMD(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_TXBUFCNT_PCMD)
DECL|macro|G_LDT_TXBUFCNT_PCMD
mdefine_line|#define G_LDT_TXBUFCNT_PCMD(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_TXBUFCNT_PCMD,M_LDT_TXBUFCNT_PCMD)
DECL|macro|S_LDT_TXBUFCNT_PDATA
mdefine_line|#define S_LDT_TXBUFCNT_PDATA&t;&t;4
DECL|macro|M_LDT_TXBUFCNT_PDATA
mdefine_line|#define M_LDT_TXBUFCNT_PDATA&t;&t;_SB_MAKEMASK_32(4,S_LDT_TXBUFCNT_PDATA)
DECL|macro|V_LDT_TXBUFCNT_PDATA
mdefine_line|#define V_LDT_TXBUFCNT_PDATA(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_TXBUFCNT_PDATA)
DECL|macro|G_LDT_TXBUFCNT_PDATA
mdefine_line|#define G_LDT_TXBUFCNT_PDATA(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_TXBUFCNT_PDATA,M_LDT_TXBUFCNT_PDATA)
DECL|macro|S_LDT_TXBUFCNT_NPCMD
mdefine_line|#define S_LDT_TXBUFCNT_NPCMD&t;&t;8
DECL|macro|M_LDT_TXBUFCNT_NPCMD
mdefine_line|#define M_LDT_TXBUFCNT_NPCMD&t;&t;_SB_MAKEMASK_32(4,S_LDT_TXBUFCNT_NPCMD)
DECL|macro|V_LDT_TXBUFCNT_NPCMD
mdefine_line|#define V_LDT_TXBUFCNT_NPCMD(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_TXBUFCNT_NPCMD)
DECL|macro|G_LDT_TXBUFCNT_NPCMD
mdefine_line|#define G_LDT_TXBUFCNT_NPCMD(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_TXBUFCNT_NPCMD,M_LDT_TXBUFCNT_NPCMD)
DECL|macro|S_LDT_TXBUFCNT_NPDATA
mdefine_line|#define S_LDT_TXBUFCNT_NPDATA&t;&t;12
DECL|macro|M_LDT_TXBUFCNT_NPDATA
mdefine_line|#define M_LDT_TXBUFCNT_NPDATA&t;&t;_SB_MAKEMASK_32(4,S_LDT_TXBUFCNT_NPDATA)
DECL|macro|V_LDT_TXBUFCNT_NPDATA
mdefine_line|#define V_LDT_TXBUFCNT_NPDATA(x)&t;_SB_MAKEVALUE_32(x,S_LDT_TXBUFCNT_NPDATA)
DECL|macro|G_LDT_TXBUFCNT_NPDATA
mdefine_line|#define G_LDT_TXBUFCNT_NPDATA(x)&t;_SB_GETVALUE_32(x,S_LDT_TXBUFCNT_NPDATA,M_LDT_TXBUFCNT_NPDATA)
DECL|macro|S_LDT_TXBUFCNT_RCMD
mdefine_line|#define S_LDT_TXBUFCNT_RCMD&t;&t;16
DECL|macro|M_LDT_TXBUFCNT_RCMD
mdefine_line|#define M_LDT_TXBUFCNT_RCMD&t;&t;_SB_MAKEMASK_32(4,S_LDT_TXBUFCNT_RCMD)
DECL|macro|V_LDT_TXBUFCNT_RCMD
mdefine_line|#define V_LDT_TXBUFCNT_RCMD(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_TXBUFCNT_RCMD)
DECL|macro|G_LDT_TXBUFCNT_RCMD
mdefine_line|#define G_LDT_TXBUFCNT_RCMD(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_TXBUFCNT_RCMD,M_LDT_TXBUFCNT_RCMD)
DECL|macro|S_LDT_TXBUFCNT_RDATA
mdefine_line|#define S_LDT_TXBUFCNT_RDATA&t;&t;20
DECL|macro|M_LDT_TXBUFCNT_RDATA
mdefine_line|#define M_LDT_TXBUFCNT_RDATA&t;&t;_SB_MAKEMASK_32(4,S_LDT_TXBUFCNT_RDATA)
DECL|macro|V_LDT_TXBUFCNT_RDATA
mdefine_line|#define V_LDT_TXBUFCNT_RDATA(x)&t;&t;_SB_MAKEVALUE_32(x,S_LDT_TXBUFCNT_RDATA)
DECL|macro|G_LDT_TXBUFCNT_RDATA
mdefine_line|#define G_LDT_TXBUFCNT_RDATA(x)&t;&t;_SB_GETVALUE_32(x,S_LDT_TXBUFCNT_RDATA,M_LDT_TXBUFCNT_RDATA)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
multiline_comment|/*&n; * Additional Status Register&n; */
DECL|macro|S_LDT_ADDSTATUS_TGTDONE
mdefine_line|#define S_LDT_ADDSTATUS_TGTDONE&t;&t;0
DECL|macro|M_LDT_ADDSTATUS_TGTDONE
mdefine_line|#define M_LDT_ADDSTATUS_TGTDONE&t;&t;_SB_MAKEMASK_32(8,S_LDT_ADDSTATUS_TGTDONE)
DECL|macro|V_LDT_ADDSTATUS_TGTDONE
mdefine_line|#define V_LDT_ADDSTATUS_TGTDONE(x)&t;_SB_MAKEVALUE_32(x,S_LDT_ADDSTATUS_TGTDONE)
DECL|macro|G_LDT_ADDSTATUS_TGTDONE
mdefine_line|#define G_LDT_ADDSTATUS_TGTDONE(x)&t;_SB_GETVALUE_32(x,S_LDT_ADDSTATUS_TGTDONE,M_LDT_ADDSTATUS_TGTDONE)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
macro_line|#endif
eof
