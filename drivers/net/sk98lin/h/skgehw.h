multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgehw.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.35 $&n; * Date:&t;$Date: 2000/05/19 10:17:13 $&n; * Purpose:&t;Defines and Macros for the Gigabit Ethernet Adapter Product&n; *&t;&t;Family&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; * $Log: skgehw.h,v $&n; * Revision 1.35  2000/05/19 10:17:13  cgoos&n; * Added inactivity check in PHY_READ (in DEBUG mode only).&n; *&n; * Revision 1.34  1999/11/22 13:53:40  cgoos&n; * Changed license header to GPL.&n; *&n; * Revision 1.33  1999/08/27 11:17:10  malthoff&n; * It&squot;s more savely to put bracket around marco parameters.&n; * Brackets added for PHY_READ and PHY_WRITE.&n; *&n; * Revision 1.32  1999/05/19 07:31:01  cgoos&n; * Changes for 1000Base-T.&n; * Added HWAC_LINK_LED macro.&n; *&n; * Revision 1.31  1999/03/12 13:27:40  malthoff&n; * Remove __STDC__.&n; *&n; * Revision 1.30  1999/02/09 09:28:20  malthoff&n; * Add PCI_ERRBITS.&n; *&n; * Revision 1.29  1999/01/26 08:55:48  malthoff&n; * Bugfix: The 16 bit field releations inside the descriptor are&n; * &t;endianess dependend if the descriptor reversal feature&n; * &t;(PCI_REV_DESC bit in PCI_OUR_REG_2) is enabled.&n; * &t;Drivers which use this feature has to set the define&n; * &t;SK_USE_REV_DESC.&n; *&n; * Revision 1.28  1998/12/10 11:10:22  malthoff&n; * bug fix: IS_IRQ_STAT and IS_IRQ_MST_ERR has been twisted.&n; *&n; * Revision 1.27  1998/11/13 14:19:21  malthoff&n; * Bug Fix: The bit definition of B3_PA_CTRL has completely&n; * changed from HW Spec v1.3 to v1.5.&n; *&n; * Revision 1.26  1998/11/04 08:31:48  cgoos&n; * Fixed byte ordering in XM_OUTADDR/XM_OUTHASH macros.&n; *&n; * Revision 1.25  1998/11/04 07:16:25  cgoos&n; * Changed byte ordering in XM_INADDR/XM_INHASH again.&n; *&n; * Revision 1.24  1998/11/02 11:08:43  malthoff&n; * RxCtrl and TxCtrl must be volatile.&n; *&n; * Revision 1.23  1998/10/28 13:50:45  malthoff&n; * Fix: Endian support missing in XM_IN/OUT-ADDR/HASH macros.&n; *&n; * Revision 1.22  1998/10/26 08:01:36  malthoff&n; * RX_MFF_CTRL1 is split up into RX_MFF_CTRL1,&n; * RX_MFF_STAT_TO, and RX_MFF_TIST_TO.&n; * TX_MFF_CTRL1 is split up TX_MFF_CTRL1 and TX_MFF_WAF.&n; *&n; * Revision 1.21  1998/10/20 07:43:10  malthoff&n; * Fix: XM_IN/OUT/ADDR/HASH macros:&n; * The pointer must be casted.&n; *&n; * Revision 1.20  1998/10/19 15:53:59  malthoff&n; * Remove ML proto definitions.&n; *&n; * Revision 1.19  1998/10/16 14:40:17  gklug&n; * fix: typo B0_XM_IMSK regs&n; *&n; * Revision 1.18  1998/10/16 09:46:54  malthoff&n; * Remove temp defines for ML diag prototyp.&n; * Fix register definition for B0_XM1_PHY_DATA, B0_XM1_PHY_DATA&n; * B0_XM2_PHY_DATA, B0_XM2_PHY_ADDR, B0_XA1_CSR, B0_XS1_CSR,&n; * B0_XS2_CSR, and B0_XA2_CSR.&n; *&n; * Revision 1.17  1998/10/14 06:03:14  cgoos&n; * Changed shifted constant to ULONG.&n; *&n; * Revision 1.16  1998/10/09 07:05:41  malthoff&n; * Rename ALL_PA_ENA_TO to PA_ENA_TO_ALL.&n; *&n; * Revision 1.15  1998/10/05 07:54:23  malthoff&n; * Split up RB_CTRL and it&squot;s bit definition into&n; * RB_CTRL, RB_TST1, and RB_TST2.&n; * Rename RB_RX_HTPP to RB_RX_LTPP.&n; * Add ALL_PA_ENA_TO. Modify F_WATER_MARK&n; * according to HW Spec. v1.5.&n; * Add MFF_TX_CTRL_DEF.&n; *&n; * Revision 1.14  1998/09/28 13:31:16  malthoff&n; * bug fix: B2_MAC_3 is 0x110 not 0x114&n; *&n; * Revision 1.13  1998/09/24 14:42:56  malthoff&n; * Split the RX_MFF_TST into RX_MFF_CTRL2,&n; * RX_MFF_TST1, and RX_MFF_TST2.&n; * Rename RX_MFF_CTRL to RX_MFF_CTRL1.&n; * Add BMU bit CSR_SV_IDLE.&n; * Add macros PHY_READ() and PHY_WRITE().&n; * Rename macro SK_ADDR() to SK_HW_ADDR()&n; * because of conflicts with the Address Module.&n; *&n; * Revision 1.12  1998/09/16 07:25:33  malthoff&n; * Change the parameter order in the XM_INxx and XM_OUTxx macros,&n; * to have the IoC as first parameter.&n; *&n; * Revision 1.11  1998/09/03 09:58:41  malthoff&n; * Rework the XM_xxx macros. Use {} instead of () to&n; * be compatible with SK_xxx macros which are defined&n; * with {}.&n; *&n; * Revision 1.10  1998/09/02 11:16:39  malthoff&n; * Temporary modify B2_I2C_SW to make tests with&n; * the GE/ML prototyp.&n; *&n; * Revision 1.9  1998/08/19 09:11:49  gklug&n; * fix: struct are removed from c-source (see CCC)&n; * add: typedefs for all structs&n; *&n; * Revision 1.8  1998/08/18 08:27:27  malthoff&n; * Add some temporary workarounds to test GE&n; * sources with the ML.&n; *&n; * Revision 1.7  1998/07/03 14:42:26  malthoff&n; * bug fix: Correct macro XMA().&n; * Add temporary workaround to access the PCI config space over IO&n; *&n; * Revision 1.6  1998/06/23 11:30:36  malthoff&n; * Remove &squot;;&squot; with &squot;,&squot; in macors.&n; *&n; * Revision 1.5  1998/06/22 14:20:57  malthoff&n; * Add macro SK_ADDR(Base,Addr).&n; *&n; * Revision 1.4  1998/06/19 13:35:43  malthoff&n; * change &squot;pGec&squot; with &squot;pAC&squot;&n; *&n; * Revision 1.3  1998/06/17 14:58:16  cvs&n; * Lost keywords reinserted.&n; *&n; * Revision 1.1  1998/06/17 14:16:36  cvs&n; * created&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKGEHW_H
DECL|macro|__INC_SKGEHW_H
mdefine_line|#define __INC_SKGEHW_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * Configuration Space header&n; * Since this module is used for different OS&squot;, those may be&n; * duplicate on some of them (e.g. Linux). But to keep the&n; * common source, we have to live with this...&n; */
DECL|macro|PCI_VENDOR_ID
mdefine_line|#define&t;PCI_VENDOR_ID&t;0x00&t;/* 16 bit&t;Vendor ID */
DECL|macro|PCI_DEVICE_ID
mdefine_line|#define&t;PCI_DEVICE_ID&t;0x02&t;/* 16 bit&t;Device ID */
DECL|macro|PCI_COMMAND
mdefine_line|#define&t;PCI_COMMAND&t;0x04&t;/* 16 bit&t;Command */
DECL|macro|PCI_STATUS
mdefine_line|#define&t;PCI_STATUS&t;0x06&t;/* 16 bit&t;Status */
DECL|macro|PCI_REV_ID
mdefine_line|#define&t;PCI_REV_ID&t;0x08&t;/*  8 bit&t;Revision ID */
DECL|macro|PCI_CLASS_CODE
mdefine_line|#define&t;PCI_CLASS_CODE&t;0x09&t;/* 24 bit&t;Class Code */
DECL|macro|PCI_CACHE_LSZ
mdefine_line|#define&t;PCI_CACHE_LSZ&t;0x0c&t;/*  8 bit&t;Cache Line Size */
DECL|macro|PCI_LAT_TIM
mdefine_line|#define&t;PCI_LAT_TIM&t;0x0d&t;/*  8 bit&t;Latency Timer */
DECL|macro|PCI_HEADER_T
mdefine_line|#define&t;PCI_HEADER_T&t;0x0e&t;/*  8 bit&t;Header Type */
DECL|macro|PCI_BIST
mdefine_line|#define&t;PCI_BIST&t;0x0f&t;/*  8 bit&t;Built-in selftest */
DECL|macro|PCI_BASE_1ST
mdefine_line|#define&t;PCI_BASE_1ST&t;0x10&t;/* 32 bit&t;1st Base address */
DECL|macro|PCI_BASE_2ND
mdefine_line|#define&t;PCI_BASE_2ND&t;0x14&t;/* 32 bit&t;2nd Base address */
multiline_comment|/* Byte 18..2b:&t;reserved */
DECL|macro|PCI_SUB_VID
mdefine_line|#define&t;PCI_SUB_VID&t;0x2c&t;/* 16 bit&t;Subsystem Vendor ID */
DECL|macro|PCI_SUB_ID
mdefine_line|#define&t;PCI_SUB_ID&t;0x2e&t;/* 16 bit&t;Subsystem ID */
DECL|macro|PCI_BASE_ROM
mdefine_line|#define&t;PCI_BASE_ROM&t;0x30&t;/* 32 bit&t;Expansion ROM Base Address */
multiline_comment|/* Byte 34..33:&t;reserved */
DECL|macro|PCI_CAP_PTR
mdefine_line|#define PCI_CAP_PTR&t;0x34&t;/*  8 bit &t;Capabilities Ptr */
multiline_comment|/* Byte 35..3b:&t;reserved */
DECL|macro|PCI_IRQ_LINE
mdefine_line|#define&t;PCI_IRQ_LINE&t;0x3c&t;/*  8 bit&t;Interrupt Line */
DECL|macro|PCI_IRQ_PIN
mdefine_line|#define&t;PCI_IRQ_PIN&t;0x3d&t;/*  8 bit&t;Interrupt Pin */
DECL|macro|PCI_MIN_GNT
mdefine_line|#define&t;PCI_MIN_GNT&t;0x3e&t;/*  8 bit&t;Min_Gnt */
DECL|macro|PCI_MAX_LAT
mdefine_line|#define&t;PCI_MAX_LAT&t;0x3f&t;/*  8 bit&t;Max_Lat */
multiline_comment|/* Device Dependent Region */
DECL|macro|PCI_OUR_REG_1
mdefine_line|#define&t;PCI_OUR_REG_1&t;0x40&t;/* 32 bit &t;Our Register 1 */
DECL|macro|PCI_OUR_REG_2
mdefine_line|#define&t;PCI_OUR_REG_2&t;0x44&t;/* 32 bit &t;Our Register 2 */
multiline_comment|/* Power Management Region */
DECL|macro|PCI_PM_CAP_ID
mdefine_line|#define PCI_PM_CAP_ID&t;0x48&t;/*  8 bit &t;Power Management Cap. ID */
DECL|macro|PCI_PM_NITEM
mdefine_line|#define PCI_PM_NITEM&t;0x49&t;/*  8 bit &t;Next Item Ptr */
DECL|macro|PCI_PM_CAP_REG
mdefine_line|#define PCI_PM_CAP_REG&t;0x4a&t;/* 16 bit &t;Power Management Capabilities */
DECL|macro|PCI_PM_CTL_STS
mdefine_line|#define PCI_PM_CTL_STS&t;0x4c&t;/* 16 bit &t;Power Manag. Control/Status */
multiline_comment|/* Byte 0x4e:&t;reserved */
DECL|macro|PCI_PM_DAT_REG
mdefine_line|#define PCI_PM_DAT_REG&t;0x4f&t;/*  8 bit &t;Power Manag. Data Register */
multiline_comment|/* VPD Region */
DECL|macro|PCI_VPD_CAP_ID
mdefine_line|#define&t;PCI_VPD_CAP_ID&t;0x50&t;/*  8 bit &t;VPD Cap. ID */
DECL|macro|PCI_VPD_NITEM
mdefine_line|#define PCI_VPD_NITEM&t;0x51&t;/*  8 bit &t;Next Item Ptr */
DECL|macro|PCI_VPD_ADR_REG
mdefine_line|#define PCI_VPD_ADR_REG&t;0x52&t;/* 16 bit &t;VPD Address Register */
DECL|macro|PCI_VPD_DAT_REG
mdefine_line|#define PCI_VPD_DAT_REG&t;0x54&t;/* 32 bit &t;VPD Data Register */
multiline_comment|/* Byte 58..ff:&t;reserved */
multiline_comment|/*&n; * I2C Address (PCI Config)&n; *&n; * Note: The temperature and voltage sensors are relocated on a different&n; *&t; I2C bus.&n; */
DECL|macro|I2C_ADDR_VPD
mdefine_line|#define I2C_ADDR_VPD&t;0xA0&t;/* I2C address for the VPD EEPROM */
multiline_comment|/*&n; * Define Bits and Values of the registers&n; */
multiline_comment|/*&t;PCI_VENDOR_ID&t;16 bit&t;Vendor ID */
multiline_comment|/*&t;PCI_DEVICE_ID&t;16 bit&t;Device ID */
multiline_comment|/* Values for Vendor ID and Device ID shall be patched into the code */
multiline_comment|/*&t;PCI_COMMAND&t;16 bit&t;Command */
multiline_comment|/* Bit 15..10:&t;reserved */
DECL|macro|PCI_FBTEN
mdefine_line|#define&t;PCI_FBTEN&t;(1&lt;&lt;9)&t;/* Bit 9:&t;Fast Back-To-Back enable */
DECL|macro|PCI_SERREN
mdefine_line|#define&t;PCI_SERREN&t;(1&lt;&lt;8)&t;/* Bit 8:&t;SERR enable */
DECL|macro|PCI_ADSTEP
mdefine_line|#define&t;PCI_ADSTEP&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Address Stepping */
DECL|macro|PCI_PERREN
mdefine_line|#define&t;PCI_PERREN&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Parity Report Response enable */
DECL|macro|PCI_VGA_SNOOP
mdefine_line|#define&t;PCI_VGA_SNOOP&t;(1&lt;&lt;5)&t;/* Bit 5:&t;VGA palette snoop */
DECL|macro|PCI_MWIEN
mdefine_line|#define&t;PCI_MWIEN&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Memory write an inv cycl ena */
DECL|macro|PCI_SCYCEN
mdefine_line|#define&t;PCI_SCYCEN&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Special Cycle enable */
DECL|macro|PCI_BMEN
mdefine_line|#define&t;PCI_BMEN&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Bus Master enable */
DECL|macro|PCI_MEMEN
mdefine_line|#define&t;PCI_MEMEN&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Memory Space Access enable */
DECL|macro|PCI_IOEN
mdefine_line|#define&t;PCI_IOEN&t;(1&lt;&lt;0)&t;/* Bit 0:&t;IO Space Access enable */
multiline_comment|/*&t;PCI_STATUS&t;16 bit&t;Status */
DECL|macro|PCI_PERR
mdefine_line|#define&t;PCI_PERR&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Parity Error */
DECL|macro|PCI_SERR
mdefine_line|#define&t;PCI_SERR&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Signaled SERR */
DECL|macro|PCI_RMABORT
mdefine_line|#define&t;PCI_RMABORT&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Received Master Abort */
DECL|macro|PCI_RTABORT
mdefine_line|#define&t;PCI_RTABORT&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Received Target Abort */
multiline_comment|/* Bit 11:&t;reserved */
DECL|macro|PCI_DEVSEL
mdefine_line|#define&t;PCI_DEVSEL&t;(3&lt;&lt;9)&t;/* Bit 10..9:&t;DEVSEL Timing */
DECL|macro|PCI_DEV_FAST
mdefine_line|#define&t;PCI_DEV_FAST&t;(0&lt;&lt;9)&t;/*&t;&t;fast */
DECL|macro|PCI_DEV_MEDIUM
mdefine_line|#define&t;PCI_DEV_MEDIUM&t;(1&lt;&lt;9)&t;/*&t;&t;medium */
DECL|macro|PCI_DEV_SLOW
mdefine_line|#define&t;PCI_DEV_SLOW&t;(2&lt;&lt;9)&t;/*&t;&t;slow */
DECL|macro|PCI_DATAPERR
mdefine_line|#define&t;PCI_DATAPERR&t;(1&lt;&lt;8)&t;/* Bit 8:&t;DATA Parity error detected */
DECL|macro|PCI_FB2BCAP
mdefine_line|#define&t;PCI_FB2BCAP&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Fast Back-to-Back Capability */
DECL|macro|PCI_UDF
mdefine_line|#define&t;PCI_UDF&t;&t;(1&lt;&lt;6)&t;/* Bit 6:&t;User Defined Features */
DECL|macro|PCI_66MHZCAP
mdefine_line|#define PCI_66MHZCAP&t;(1&lt;&lt;5)&t;/* Bit 5:&t;66 MHz PCI bus clock capable */
DECL|macro|PCI_NEWCAP
mdefine_line|#define PCI_NEWCAP&t;(1&lt;&lt;4)&t;/* Bit 4:&t;New cap. list implemented */
multiline_comment|/* Bit 3..0:&t;reserved */
DECL|macro|PCI_ERRBITS
mdefine_line|#define PCI_ERRBITS&t;(PCI_PERR | PCI_SERR | PCI_RMABORT | PCI_RTABORT |&bslash;&n;&t;&t;&t;PCI_DATAPERR)
multiline_comment|/*&t;PCI_CLASS_CODE&t;24 bit&t;Class Code */
multiline_comment|/*&t;Byte 2:&t;&t;Base Class&t;&t;(02) */
multiline_comment|/*&t;Byte 1:&t;&t;SubClass&t;&t;(00) */
multiline_comment|/*&t;Byte 0:&t;&t;Programming Interface&t;(00) */
multiline_comment|/*&t;PCI_CACHE_LSZ&t;8 bit&t;Cache Line Size */
multiline_comment|/*&t;Possible values: 0,2,4,8,16,32,64,128&t;*/
multiline_comment|/*&t;PCI_HEADER_T&t;8 bit&t;Header Type */
DECL|macro|PCI_HD_MF_DEV
mdefine_line|#define&t;PCI_HD_MF_DEV&t;(1&lt;&lt;7)&t;/* Bit 7:&t;0= single, 1= multi-func dev */
DECL|macro|PCI_HD_TYPE
mdefine_line|#define&t;PCI_HD_TYPE&t;0x7f&t;/* Bit 6..0:&t;Header Layout 0= normal */
multiline_comment|/*&t;PCI_BIST&t;8 bit&t;Built-in selftest */
multiline_comment|/*&t;Built-in Self test not supported (optional) */
multiline_comment|/*&t;PCI_BASE_1ST&t;32 bit&t;1st Base address */
DECL|macro|PCI_MEMSIZE
mdefine_line|#define&t;PCI_MEMSIZE&t;0x4000L&t;&t;/* use 16 kB Memory Base */
DECL|macro|PCI_MEMBASE_MSK
mdefine_line|#define&t;PCI_MEMBASE_MSK 0xffffc000L&t;/* Bit 31..14:&t;Memory Base Address */
DECL|macro|PCI_MEMSIZE_MSK
mdefine_line|#define&t;PCI_MEMSIZE_MSK 0x00003ff0L&t;/* Bit 13.. 4:&t;Memory Size Req. */
DECL|macro|PCI_PREFEN
mdefine_line|#define&t;PCI_PREFEN&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Prefetchable */
DECL|macro|PCI_MEM_TYP
mdefine_line|#define&t;PCI_MEM_TYP&t;(3L&lt;&lt;2)&t;&t;/* Bit&t;2.. 1:&t;Memory Type */
DECL|macro|PCI_MEM32BIT
mdefine_line|#define&t;PCI_MEM32BIT&t;(0L&lt;&lt;1)&t;&t;/* Base addr anywhere in 32 Bit range */
DECL|macro|PCI_MEM1M
mdefine_line|#define&t;PCI_MEM1M&t;(1L&lt;&lt;1)&t;&t;/* Base addr below 1 MegaByte */
DECL|macro|PCI_MEM64BIT
mdefine_line|#define&t;PCI_MEM64BIT&t;(2L&lt;&lt;1)&t;&t;/* Base addr anywhere in 64 Bit range */
DECL|macro|PCI_MEMSPACE
mdefine_line|#define&t;PCI_MEMSPACE&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Memory Space Indic. */
multiline_comment|/*&t;PCI_BASE_2ND&t;32 bit&t;2nd Base address */
DECL|macro|PCI_IOBASE
mdefine_line|#define&t;PCI_IOBASE&t;0xffffff00L&t;/* Bit 31..8:&t;I/O Base address */
DECL|macro|PCI_IOSIZE
mdefine_line|#define&t;PCI_IOSIZE&t;0x000000fcL&t;/* Bit&t;7..2:&t;I/O Size Requirements */
multiline_comment|/* Bit&t;1:&t;reserved */
DECL|macro|PCI_IOSPACE
mdefine_line|#define&t;PCI_IOSPACE&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;I/O Space Indicator */
multiline_comment|/*&t;PCI_BASE_ROM&t;32 bit&t;Expansion ROM Base Address */
DECL|macro|PCI_ROMBASE
mdefine_line|#define&t;PCI_ROMBASE&t;(0xfffeL&lt;&lt;17)&t;/* Bit 31..17:&t;ROM BASE address (1st)*/
DECL|macro|PCI_ROMBASZ
mdefine_line|#define&t;PCI_ROMBASZ&t;(0x1cL&lt;&lt;14)&t;/* Bit 16..14:&t;Treat as BASE or SIZE */
DECL|macro|PCI_ROMSIZE
mdefine_line|#define&t;PCI_ROMSIZE&t;(0x38L&lt;&lt;11)&t;/* Bit 13..11:&t;ROM Size Requirements */
multiline_comment|/* Bit 10.. 1:&t;reserved */
DECL|macro|PCI_ROMEN
mdefine_line|#define&t;PCI_ROMEN&t;(0x1L&lt;&lt;0)&t;/* Bit 0:&t;Address Decode enable */
multiline_comment|/* Device Dependent Region */
multiline_comment|/*&t;PCI_OUR_REG_1&t;&t;32 bit&t;Our Register 1 */
multiline_comment|/* Bit 31..26:&t;reserved */
DECL|macro|PCI_VIO
mdefine_line|#define PCI_VIO&t;&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;PCI IO Voltage, */
multiline_comment|/*&t;&t;0 = 3.3V / 1 = 5V */
DECL|macro|PCI_EN_BOOT
mdefine_line|#define&t;PCI_EN_BOOT&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;Enable BOOT via ROM */
multiline_comment|/*&t;&t;1 = Don&squot;t boot wth ROM*/
multiline_comment|/*&t;&t;0 = Boot with ROM */
DECL|macro|PCI_EN_IO
mdefine_line|#define&t;PCI_EN_IO&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;Mapping to IO space */
DECL|macro|PCI_EN_FPROM
mdefine_line|#define&t;PCI_EN_FPROM&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;FLASH mapped to mem? */
multiline_comment|/*&t;&t;1 = Map Flash to Mem */
multiline_comment|/*&t;&t;0 = Disable addr. dec*/
DECL|macro|PCI_PAGESIZE
mdefine_line|#define&t;PCI_PAGESIZE&t;(3L&lt;&lt;20)&t;/* Bit 21..20:&t;FLASH Page Size&t;*/
DECL|macro|PCI_PAGE_16
mdefine_line|#define&t;PCI_PAGE_16&t;(0L&lt;&lt;20)&t;/*&t;&t;16 k pages&t;*/
DECL|macro|PCI_PAGE_32K
mdefine_line|#define&t;PCI_PAGE_32K&t;(1L&lt;&lt;20)&t;/*&t;&t;32 k pages&t;*/
DECL|macro|PCI_PAGE_64K
mdefine_line|#define&t;PCI_PAGE_64K&t;(2L&lt;&lt;20)&t;/*&t;&t;64 k pages&t;*/
DECL|macro|PCI_PAGE_128K
mdefine_line|#define&t;PCI_PAGE_128K&t;(3L&lt;&lt;20)&t;/*&t;&t;128 k pages&t;*/
multiline_comment|/* Bit 19:&t;reserved&t;*/
DECL|macro|PCI_PAGEREG
mdefine_line|#define&t;PCI_PAGEREG&t;(7L&lt;&lt;16)&t;/* Bit 18..16:&t;Page Register&t;*/
DECL|macro|PCI_NOTAR
mdefine_line|#define PCI_NOTAR&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;No turnaround cycle */
DECL|macro|PCI_FORCE_BE
mdefine_line|#define&t;PCI_FORCE_BE&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Assert all BEs on MR */
DECL|macro|PCI_DIS_MRL
mdefine_line|#define&t;PCI_DIS_MRL&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Disable Mem R Line */
DECL|macro|PCI_DIS_MRM
mdefine_line|#define&t;PCI_DIS_MRM&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Disable Mem R multip */
DECL|macro|PCI_DIS_MWI
mdefine_line|#define&t;PCI_DIS_MWI&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Disable Mem W &amp; inv */
DECL|macro|PCI_DISC_CLS
mdefine_line|#define&t;PCI_DISC_CLS&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Disc: cacheLsz bound */
DECL|macro|PCI_BURST_DIS
mdefine_line|#define&t;PCI_BURST_DIS&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Burst Disable */
DECL|macro|PCI_DIS_PCI_CLK
mdefine_line|#define&t;PCI_DIS_PCI_CLK&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Disable PCI clock driv*/
DECL|macro|PCI_SKEW_DAS
mdefine_line|#define&t;PCI_SKEW_DAS&t;(0xfL&lt;&lt;4)&t;/* Bit&t;7..4:&t;Skew Ctrl, DAS Ext */
DECL|macro|PCI_SKEW_BASE
mdefine_line|#define&t;PCI_SKEW_BASE&t;(0xfL&lt;&lt;0)&t;/* Bit&t;3..0:&t;Skew Ctrl, Base&t;*/
multiline_comment|/*&t;PCI_OUR_REG_2&t;&t;32 bit&t;Our Register 2 */
DECL|macro|PCI_VPD_WR_THR
mdefine_line|#define PCI_VPD_WR_THR&t;(0xffL&lt;&lt;24)&t;/* Bit 31..24:&t;VPD Write Threshold */
DECL|macro|PCI_DEV_SEL
mdefine_line|#define&t;PCI_DEV_SEL&t;(0x7fL&lt;&lt;17)&t;/* Bit 23..17:&t;EEPROM Device Select */
DECL|macro|PCI_VPD_ROM_SZ
mdefine_line|#define&t;PCI_VPD_ROM_SZ&t;(7L&lt;&lt;14)&t;/* Bit 16..14:&t;VPD ROM Size&t;*/
multiline_comment|/* Bit 13..12:&t;reserved&t;*/
DECL|macro|PCI_PATCH_DIR
mdefine_line|#define&t;PCI_PATCH_DIR&t;(0xfL&lt;&lt;8)&t;/* Bit 11.. 8:&t;Ext Patchs dir 3..0 */
DECL|macro|PCI_PATCH_DIR_0
mdefine_line|#define&t;PCI_PATCH_DIR_0&t;(1L&lt;&lt;8)
DECL|macro|PCI_PATCH_DIR_1
mdefine_line|#define&t;PCI_PATCH_DIR_1&t;(1L&lt;&lt;9)
DECL|macro|PCI_PATCH_DIR_2
mdefine_line|#define&t;PCI_PATCH_DIR_2&t;(1L&lt;&lt;10)
DECL|macro|PCI_PATCH_DIR_3
mdefine_line|#define&t;PCI_PATCH_DIR_3&t;(1L&lt;&lt;11)
DECL|macro|PCI_EXT_PATCHS
mdefine_line|#define PCI_EXT_PATCHS&t;(0xfL&lt;&lt;4)&t;/* Bit&t;7..4:&t;Extended Patches 3..0 */
DECL|macro|PCI_EXT_PATCH_0
mdefine_line|#define&t;PCI_EXT_PATCH_0&t;(1L&lt;&lt;4)
DECL|macro|PCI_EXT_PATCH_1
mdefine_line|#define&t;PCI_EXT_PATCH_1&t;(1L&lt;&lt;5)
DECL|macro|PCI_EXT_PATCH_2
mdefine_line|#define&t;PCI_EXT_PATCH_2&t;(1L&lt;&lt;6)
DECL|macro|PCI_EXT_PATCH_3
mdefine_line|#define&t;PCI_EXT_PATCH_3&t;(1L&lt;&lt;7)
DECL|macro|PCI_EN_DUMMY_RD
mdefine_line|#define&t;PCI_EN_DUMMY_RD&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Enable Dummy Read */
DECL|macro|PCI_REV_DESC
mdefine_line|#define PCI_REV_DESC&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Reverse Desc. Bytes */
multiline_comment|/* Bit&t;1:&t;reserved */
DECL|macro|PCI_USEDATA64
mdefine_line|#define PCI_USEDATA64&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Use 64Bit Data bus ext*/
multiline_comment|/* Power Management Region */
multiline_comment|/*&t;PCI_PM_CAP_REG&t;&t;16 bit&t;Power Management Capabilities */
DECL|macro|PCI_PME_SUP
mdefine_line|#define&t;PCI_PME_SUP&t;(0x1f&lt;&lt;11)&t;/* Bit 15..11:&t;PM Manag. Event Sup */
DECL|macro|PCI_PM_D2_SUB
mdefine_line|#define PCI_PM_D2_SUB&t;(1&lt;&lt;10)&t;&t;/* Bit 10:&t;D2 Support Bit */
DECL|macro|PCI_PM_D1_SUB
mdefine_line|#define PCI_PM_D1_SUB&t;(1&lt;&lt;9)&t;&t;/* Bit&t;9:&t;D1 Support Bit */
multiline_comment|/* Bit&t;8..6:&t;reserved */
DECL|macro|PCI_PM_DSI
mdefine_line|#define PCI_PM_DSI&t;(1&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Device Specific Init.*/
DECL|macro|PCI_PM_APS
mdefine_line|#define PCI_PM_APS&t;(1&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Auxialiary Power Src */
DECL|macro|PCI_PME_CLOCK
mdefine_line|#define PCI_PME_CLOCK&t;(1&lt;&lt;3)&t;&t;/* Bit&t;3:&t;PM Event Clock */
DECL|macro|PCI_PM_VER
mdefine_line|#define PCI_PM_VER&t;(7&lt;&lt;0)&t;&t;/* Bit&t;2..0:&t;PM PCI Spec. version */
multiline_comment|/*&t;PCI_PM_CTL_STS&t;&t;16 bit&t;Power Manag. Control/Status */
DECL|macro|PCI_PME_STATUS
mdefine_line|#define&t;PCI_PME_STATUS&t;(1&lt;&lt;15)&t;&t;/* Bit 15: &t;PGA doesn&squot;t sup. PME# */
DECL|macro|PCI_PM_DAT_SCL
mdefine_line|#define PCI_PM_DAT_SCL&t;(3&lt;&lt;13)&t;&t;/* Bit 14..13:&t;dat reg Scaling factor*/
DECL|macro|PCI_PM_DAT_SEL
mdefine_line|#define PCI_PM_DAT_SEL&t;(0xf&lt;&lt;9)&t;/* Bit 12.. 9:&t;PM data selector field*/
DECL|macro|PCI_PME_EN
mdefine_line|#define PCI_PME_EN&t;(1&lt;&lt;8)&t;&t;/* Bit&t;8:&t;PGA doesn&squot;t sup. PME# */
multiline_comment|/* Bit&t;7.. 2:&t;reserved */
DECL|macro|PCI_PM_STATE
mdefine_line|#define PCI_PM_STATE&t;(3&lt;&lt;0)&t;&t;/* Bit&t;1.. 0:&t;Power Management State*/
DECL|macro|PCI_PM_STATE_D0
mdefine_line|#define PCI_PM_STATE_D0&t;(0&lt;&lt;0)&t;&t;/* D0:&t;Operational (default) */
DECL|macro|PCI_PM_STATE_D1
mdefine_line|#define&t;PCI_PM_STATE_D1&t;(1&lt;&lt;0)&t;&t;/* D1:&t;not supported */
DECL|macro|PCI_PM_STATE_D2
mdefine_line|#define PCI_PM_STATE_D2&t;(2&lt;&lt;0)&t;&t;/* D2:&t;not supported */
DECL|macro|PCI_PM_STATE_D3
mdefine_line|#define PCI_PM_STATE_D3 (3&lt;&lt;0)&t;&t;/* D3:&t;HOT, Power Down and Reset */
multiline_comment|/* VPD Region */
multiline_comment|/*&t;PCI_VPD_ADR_REG&t;&t;16 bit&t;VPD Address Register */
DECL|macro|PCI_VPD_FLAG
mdefine_line|#define&t;PCI_VPD_FLAG&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;starts VPD rd/wd cycle*/
DECL|macro|PCI_VPD_ADDR
mdefine_line|#define PCI_VPD_ADDR&t;(0x3fffL&lt;&lt;0)&t;/* Bit 14..0:&t;VPD address */
multiline_comment|/*&n; *&t;Control Register File:&n; *&t;Bank 0&n; */
DECL|macro|B0_RAP
mdefine_line|#define&t;B0_RAP&t;&t;0x0000&t;/*  8 bit&t;Register Address Port */
multiline_comment|/* 0x0001 - 0x0003:&t;reserved */
DECL|macro|B0_CTST
mdefine_line|#define&t;B0_CTST&t;&t;0x0004&t;/* 16 bit&t;Control/Status register */
DECL|macro|B0_LED
mdefine_line|#define&t;B0_LED&t;&t;0x0006&t;/*  8 Bit&t;LED register */
multiline_comment|/* 0x0007:&t;&t;reserved */
DECL|macro|B0_ISRC
mdefine_line|#define&t;B0_ISRC&t;&t;0x0008&t;/* 32 bit&t;Interrupt Source Register */
DECL|macro|B0_IMSK
mdefine_line|#define&t;B0_IMSK&t;&t;0x000c&t;/* 32 bit&t;Interrupt Mask Register */
DECL|macro|B0_HWE_ISRC
mdefine_line|#define B0_HWE_ISRC&t;0x0010&t;/* 32 bit&t;HW Error Interrupt Src Reg */
DECL|macro|B0_HWE_IMSK
mdefine_line|#define B0_HWE_IMSK&t;0x0014&t;/* 32 bit&t;HW Error Interrupt Mask Reg */
DECL|macro|B0_SP_ISRC
mdefine_line|#define B0_SP_ISRC&t;0x0018&t;/* 32 bit&t;Special Interrupt Source Reg */
multiline_comment|/* 0x001c:&t;&t;reserved */
multiline_comment|/* B0 XMAC 1 registers */
DECL|macro|B0_XM1_IMSK
mdefine_line|#define&t;B0_XM1_IMSK&t;0x0020&t;/* 16 bit r/w&t;XMAC 1 Interrupt Mask Register*/
multiline_comment|/* 0x0022 - 0x0027&t;reserved */
DECL|macro|B0_XM1_ISRC
mdefine_line|#define B0_XM1_ISRC&t;0x0028&t;/* 16 bit ro&t;XMAC 1 Interrupt Status Reg */
multiline_comment|/* 0x002a - 0x002f&t;reserved */
DECL|macro|B0_XM1_PHY_ADDR
mdefine_line|#define B0_XM1_PHY_ADDR 0x0030&t;/* 16 bit r/w&t;XMAC 1 PHY Address Register */
multiline_comment|/* 0x0032 - 0x0033&t;reserved */
DECL|macro|B0_XM1_PHY_DATA
mdefine_line|#define B0_XM1_PHY_DATA 0x0034&t;/* 16 bit r/w&t;XMAC 1 PHY Data Register */
multiline_comment|/* 0x0036 - 0x003f&t;reserved */
multiline_comment|/* B0 XMAC 2 registers */
DECL|macro|B0_XM2_IMSK
mdefine_line|#define&t;B0_XM2_IMSK&t;0x0040&t;/* 16 bit r/w&t;XMAC 2 Interrupt Mask Register*/
multiline_comment|/* 0x0042 - 0x0047&t;reserved */
DECL|macro|B0_XM2_ISRC
mdefine_line|#define B0_XM2_ISRC&t;0x0048&t;/* 16 bit ro&t;XMAC 2 Interrupt Status Reg */
multiline_comment|/* 0x004a - 0x004f&t;reserved */
DECL|macro|B0_XM2_PHY_ADDR
mdefine_line|#define B0_XM2_PHY_ADDR 0x0050&t;/* 16 bit r/w&t;XMAC 2 PHY Address Register */
multiline_comment|/* 0x0052 - 0x0053&t;reserved */
DECL|macro|B0_XM2_PHY_DATA
mdefine_line|#define B0_XM2_PHY_DATA 0x0054&t;/* 16 bit r/w&t;XMAC 2 PHY Data Register */
multiline_comment|/* 0x0056 - 0x005f&t;reserved */
multiline_comment|/* BMU Control Status Registers */
DECL|macro|B0_R1_CSR
mdefine_line|#define&t;B0_R1_CSR&t;0x0060&t;/* 32 bit&t;BMU Ctrl/Stat Rx Queue 1 */
DECL|macro|B0_R2_CSR
mdefine_line|#define&t;B0_R2_CSR&t;0x0064&t;/* 32 bit&t;BMU Ctrl/Stat Rx Queue 2 */
DECL|macro|B0_XS1_CSR
mdefine_line|#define&t;B0_XS1_CSR&t;0x0068&t;/* 32 bit&t;BMU Ctrl/Stat Sync Tx Queue 1 */
DECL|macro|B0_XA1_CSR
mdefine_line|#define&t;B0_XA1_CSR&t;0x006c&t;/* 32 bit&t;BMU Ctrl/Stat Async Tx Queue 1*/
DECL|macro|B0_XS2_CSR
mdefine_line|#define&t;B0_XS2_CSR&t;0x0070&t;/* 32 bit&t;BMU Ctrl/Stat Sync Tx Queue 2 */
DECL|macro|B0_XA2_CSR
mdefine_line|#define&t;B0_XA2_CSR&t;0x0074&t;/* 32 bit&t;BMU Ctrl/Stat Async Tx Queue 2*/
multiline_comment|/* x0078 - 0x007f&t;reserved */
multiline_comment|/*&n; *&t;Bank 1&n; *&t;- completely empty (this is the RAP Block window)&n; *&t;Note: if RAP = 1 this page is reserved&n; */
multiline_comment|/*&n; *&t;Bank 2&n; */
multiline_comment|/* NA reg = 48 bit Network Address Register, 3x16 or 8x8 bit readable */
DECL|macro|B2_MAC_1
mdefine_line|#define&t;B2_MAC_1&t;0x0100&t;/* NA reg&t; MAC Address 1 */
multiline_comment|/* 0x0106 - 0x0107&t;reserved */
DECL|macro|B2_MAC_2
mdefine_line|#define&t;B2_MAC_2&t;0x0108&t;/* NA reg&t; MAC Address 2 */
multiline_comment|/* 0x010e - 0x010f&t;reserved */
DECL|macro|B2_MAC_3
mdefine_line|#define&t;B2_MAC_3&t;0x0110&t;/* NA reg&t; MAC Address 3 */
multiline_comment|/* 0x0116 - 0x0117&t;reserved */
DECL|macro|B2_CONN_TYP
mdefine_line|#define B2_CONN_TYP&t;0x0118&t;/*  8 bit&t;Connector type */
DECL|macro|B2_PMD_TYP
mdefine_line|#define B2_PMD_TYP&t;0x0119&t;/*  8 bit&t;PMD type */
DECL|macro|B2_MAC_CFG
mdefine_line|#define B2_MAC_CFG&t;0x011a&t;/*  8 bit&t;MAC Configuration */
DECL|macro|B2_CHIP_REV
mdefine_line|#define B2_CHIP_REV&t;0x011b&t;/*  8 bit &t;Queen Chip Revision Number */
multiline_comment|/* Eprom registers are currently of no use */
DECL|macro|B2_E_0
mdefine_line|#define B2_E_0&t;&t;0x011c&t;/*  8 bit&t;EPROM Byte 0 */
DECL|macro|B2_E_1
mdefine_line|#define B2_E_1&t;&t;0x011d&t;/*  8 bit&t;EPROM Byte 1 */
DECL|macro|B2_E_2
mdefine_line|#define B2_E_2&t;&t;0x011e&t;/*  8 bit&t;EPROM Byte 2 */
DECL|macro|B2_E_3
mdefine_line|#define B2_E_3&t;&t;0x011f&t;/*  8 bit&t;EPROM Byte 3 */
DECL|macro|B2_FAR
mdefine_line|#define B2_FAR&t;&t;0x0120&t;/* 32 bit&t;Flash-Prom Addr Reg/Cnt */
DECL|macro|B2_FDP
mdefine_line|#define B2_FDP&t;&t;0x0124&t;/*  8 bit&t;Flash-Prom Data Port */
multiline_comment|/* 0x0125 - 0x0127:&t;reserved */
DECL|macro|B2_LD_CRTL
mdefine_line|#define B2_LD_CRTL&t;0x0128&t;/*  8 bit&t;EPROM loader control register */
DECL|macro|B2_LD_TEST
mdefine_line|#define B2_LD_TEST&t;0x0129&t;/*  8 bit&t;EPROM loader test register */
multiline_comment|/* 0x012a - 0x012f:&t;reserved */
DECL|macro|B2_TI_INI
mdefine_line|#define B2_TI_INI&t;0x0130&t;/* 32 bit&t;Timer init value */
DECL|macro|B2_TI_VAL
mdefine_line|#define B2_TI_VAL&t;0x0134&t;/* 32 bit&t;Timer value */
DECL|macro|B2_TI_CRTL
mdefine_line|#define B2_TI_CRTL&t;0x0138&t;/*  8 bit&t;Timer control */
DECL|macro|B2_TI_TEST
mdefine_line|#define B2_TI_TEST&t;0x0139&t;/*  8 Bit&t;Timer Test */
multiline_comment|/* 0x013a - 0x013f:&t;reserved */
DECL|macro|B2_IRQM_INI
mdefine_line|#define B2_IRQM_INI&t;0x0140&t;/* 32 bit&t;IRQ Moderation Timer Init Reg.*/
DECL|macro|B2_IRQM_VAL
mdefine_line|#define B2_IRQM_VAL&t;0x0144&t;/* 32 bit&t;IRQ Moderation Timer Value */
DECL|macro|B2_IRQM_CTRL
mdefine_line|#define B2_IRQM_CTRL&t;0x0148&t;/*  8 bit&t;IRQ Moderation Timer Control */
DECL|macro|B2_IRQM_TEST
mdefine_line|#define B2_IRQM_TEST&t;0x0149&t;/*  8 bit&t;IRQ Moderation Timer Test */
DECL|macro|B2_IRQM_MSK
mdefine_line|#define B2_IRQM_MSK &t;0x014c&t;/* 32 bit&t;IRQ Moderation Mask */
DECL|macro|B2_IRQM_HWE_MSK
mdefine_line|#define B2_IRQM_HWE_MSK 0x0150&t;/* 32 bit&t;IRQ Moderation HW Error Mask */
multiline_comment|/* 0x0154 - 0x0157:&t;reserved */
DECL|macro|B2_TST_CTRL1
mdefine_line|#define&t;B2_TST_CTRL1&t;0x0158&t;/*  8 bit&t;Test Control Register 1 */
DECL|macro|B2_TST_CTRL2
mdefine_line|#define B2_TST_CTRL2&t;0x0159&t;/*  8 bit&t;Test Control Register 2 */
multiline_comment|/* 0x015a - 0x015b:&t;reserved */
DECL|macro|B2_GP_IO
mdefine_line|#define B2_GP_IO&t;0x015c&t;/* 32 bit&t;General Purpose IO Register */
DECL|macro|B2_I2C_CTRL
mdefine_line|#define B2_I2C_CTRL&t;0x0160&t;/* 32 bit&t;I2C HW Control Register */
DECL|macro|B2_I2C_DATA
mdefine_line|#define B2_I2C_DATA&t;0x0164&t;/* 32 bit&t;I2C HW Data Register */
DECL|macro|B2_I2C_IRQ
mdefine_line|#define B2_I2C_IRQ&t;0x0168&t;/* 32 bit&t;I2C HW IRQ Register */
DECL|macro|B2_I2C_SW
mdefine_line|#define B2_I2C_SW&t;0x016c&t;/* 32 bit&t;I2C SW Port Register */
DECL|macro|B2_BSC_INI
mdefine_line|#define B2_BSC_INI&t;0x0170&t;/* 32 bit&t;Blink Source Counter Init Val */
DECL|macro|B2_BSC_VAL
mdefine_line|#define B2_BSC_VAL&t;0x0174&t;/* 32 bit&t;Blink Source Counter Value */
DECL|macro|B2_BSC_CTRL
mdefine_line|#define B2_BSC_CTRL&t;0x0178&t;/*  8 bit&t;Blink Source Counter Control */
DECL|macro|B2_BSC_STAT
mdefine_line|#define B2_BSC_STAT&t;0x0179&t;/*  8 bit&t;Blink Source Counter Status */
DECL|macro|B2_BSC_TST
mdefine_line|#define B2_BSC_TST&t;0x017a&t;/* 16 bit&t;Blink Source Counter Test Reg */
multiline_comment|/* 0x017c - 0x017f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 3&n; */
DECL|macro|B3_RAM_ADDR
mdefine_line|#define B3_RAM_ADDR&t;0x0180&t;/* 32 bit&t;RAM Address, to read or write */
DECL|macro|B3_RAM_DATA_LO
mdefine_line|#define B3_RAM_DATA_LO&t;0x0184&t;/* 32 bit&t;RAM Data Word (low dWord) */
DECL|macro|B3_RAM_DATA_HI
mdefine_line|#define B3_RAM_DATA_HI&t;0x0188&t;/* 32 bit&t;RAM Data Word (high dWord) */
multiline_comment|/* 0x018c - 0x018f:&t;reserved */
multiline_comment|/* RAM Interface Registers */
multiline_comment|/*&n; * The HW-Spec. call this registers Timeout Value 0..11. But this names are&n; * not usable in SW. Please notice these are NOT real timeouts, these are&n; * the number of qWords transfered continously.&n; */
DECL|macro|B3_RI_WTO_R1
mdefine_line|#define B3_RI_WTO_R1&t;0x0190&t;/* 8 bit RAM Iface WR Timeout Queue R1&t;(TO0) */
DECL|macro|B3_RI_WTO_XA1
mdefine_line|#define B3_RI_WTO_XA1&t;0x0191&t;/* 8 bit RAM Iface WR Timeout Queue XA1&t;(TO1) */
DECL|macro|B3_RI_WTO_XS1
mdefine_line|#define B3_RI_WTO_XS1&t;0x0192&t;/* 8 bit RAM Iface WR Timeout Queue XS1 (TO2) */
DECL|macro|B3_RI_RTO_R1
mdefine_line|#define B3_RI_RTO_R1&t;0x0193&t;/* 8 bit RAM Iface RD Timeout Queue R1&t;(TO3) */
DECL|macro|B3_RI_RTO_XA1
mdefine_line|#define B3_RI_RTO_XA1&t;0x0194&t;/* 8 bit RAM Iface RD Timeout Queue XA1&t;(TO4) */
DECL|macro|B3_RI_RTO_XS1
mdefine_line|#define B3_RI_RTO_XS1&t;0x0195&t;/* 8 bit RAM Iface RD Timeout Queue XS1&t;(TO5) */
DECL|macro|B3_RI_WTO_R2
mdefine_line|#define B3_RI_WTO_R2&t;0x0196&t;/* 8 bit RAM Iface WR Timeout Queue R2&t;(TO6) */
DECL|macro|B3_RI_WTO_XA2
mdefine_line|#define B3_RI_WTO_XA2&t;0x0197&t;/* 8 bit RAM Iface WR Timeout Queue XA2&t;(TO7) */
DECL|macro|B3_RI_WTO_XS2
mdefine_line|#define B3_RI_WTO_XS2&t;0x0198&t;/* 8 bit RAM Iface WR Timeout Queue XS2&t;(TO8) */
DECL|macro|B3_RI_RTO_R2
mdefine_line|#define B3_RI_RTO_R2&t;0x0199&t;/* 8 bit RAM Iface RD Timeout Queue R2&t;(TO9) */
DECL|macro|B3_RI_RTO_XA2
mdefine_line|#define B3_RI_RTO_XA2&t;0x019a&t;/* 8 bit RAM Iface RD Timeout Queue XA2&t;(TO10)*/
DECL|macro|B3_RI_RTO_XS2
mdefine_line|#define B3_RI_RTO_XS2&t;0x019b&t;/* 8 bit RAM Iface RD Timeout Queue XS2&t;(TO11)*/
DECL|macro|B3_RI_TO_VAL
mdefine_line|#define B3_RI_TO_VAL&t;0x019c&t;/* 8 bit RAM Iface Current Timeout Count Val */
multiline_comment|/* 0x019d - 0x019f&t;reserved */
DECL|macro|B3_RI_CTRL
mdefine_line|#define B3_RI_CTRL&t;0x01a0&t;/* 16 bit&t;RAM Iface Control Register */
DECL|macro|B3_RI_TEST
mdefine_line|#define B3_RI_TEST&t;0x01a2&t;/*  8 bit&t;RAM Iface Test Register */
multiline_comment|/* 0x01a3 - 0x01af&t;reserved */
multiline_comment|/* MAC Arbiter Registers */
multiline_comment|/* Please notice these are the number of qWord tranfered continously and */
multiline_comment|/* NOT real timeouts */
DECL|macro|B3_MA_TOINI_RX1
mdefine_line|#define B3_MA_TOINI_RX1&t;0x01b0&t;/* 8 bit Timeout Init Value Rx Path MAC 1 */
DECL|macro|B3_MA_TOINI_RX2
mdefine_line|#define B3_MA_TOINI_RX2&t;0x01b1&t;/* 8 bit Timeout Init Value Rx Path MAC 2 */
DECL|macro|B3_MA_TOINI_TX1
mdefine_line|#define B3_MA_TOINI_TX1&t;0x01b2&t;/* 8 bit Timeout Init Value Tx Path MAC 1 */
DECL|macro|B3_MA_TOINI_TX2
mdefine_line|#define B3_MA_TOINI_TX2&t;0x01b3&t;/* 8 bit Timeout Init Value Tx Path MAC 2 */
DECL|macro|B3_MA_TOVAL_RX1
mdefine_line|#define B3_MA_TOVAL_RX1&t;0x01b4&t;/* 8 bit Timeout Value Rx Path MAC 1 */
DECL|macro|B3_MA_TOVAL_RX2
mdefine_line|#define B3_MA_TOVAL_RX2&t;0x01b5&t;/* 8 bit Timeout Value Rx Path MAC 1 */
DECL|macro|B3_MA_TOVAL_TX1
mdefine_line|#define B3_MA_TOVAL_TX1&t;0x01b6&t;/* 8 bit Timeout Value Tx Path MAC 2 */
DECL|macro|B3_MA_TOVAL_TX2
mdefine_line|#define B3_MA_TOVAL_TX2&t;0x01b7&t;/* 8 bit Timeout Value Tx Path MAC 2 */
DECL|macro|B3_MA_TO_CTRL
mdefine_line|#define B3_MA_TO_CTRL&t;0x01b8&t;/* 16 bit&t;MAC Arbiter Timeout Ctrl Reg */
DECL|macro|B3_MA_TO_TEST
mdefine_line|#define B3_MA_TO_TEST&t;0x01ba&t;/* 16 bit&t;MAC Arbiter Timeout Test Reg */
multiline_comment|/* 0x01bc - 0x01bf&t;reserved */
DECL|macro|B3_MA_RCINI_RX1
mdefine_line|#define B3_MA_RCINI_RX1&t;0x01c0&t;/* 8 bit Recovery Init Value Rx Path MAC 1 */
DECL|macro|B3_MA_RCINI_RX2
mdefine_line|#define B3_MA_RCINI_RX2&t;0x01c1&t;/* 8 bit Recovery Init Value Rx Path MAC 2 */
DECL|macro|B3_MA_RCINI_TX1
mdefine_line|#define B3_MA_RCINI_TX1&t;0x01c2&t;/* 8 bit Recovery Init Value Tx Path MAC 1 */
DECL|macro|B3_MA_RCINI_TX2
mdefine_line|#define B3_MA_RCINI_TX2&t;0x01c3&t;/* 8 bit Recovery Init Value Tx Path MAC 2 */
DECL|macro|B3_MA_RCVAL_RX1
mdefine_line|#define B3_MA_RCVAL_RX1&t;0x01c4&t;/* 8 bit Recovery Value Rx Path MAC 1 */
DECL|macro|B3_MA_RCVAL_RX2
mdefine_line|#define B3_MA_RCVAL_RX2&t;0x01c5&t;/* 8 bit Recovery Value Rx Path MAC 1 */
DECL|macro|B3_MA_RCVAL_TX1
mdefine_line|#define B3_MA_RCVAL_TX1&t;0x01c6&t;/* 8 bit Recovery Value Tx Path MAC 2 */
DECL|macro|B3_MA_RCVAL_TX2
mdefine_line|#define B3_MA_RCVAL_TX2&t;0x01c7&t;/* 8 bit Recovery Value Tx Path MAC 2 */
DECL|macro|B3_MA_RC_CTRL
mdefine_line|#define B3_MA_RC_CTRL&t;0x01c8&t;/* 16 bit&t;MAC Arbiter Recovery Ctrl Reg */
DECL|macro|B3_MA_RC_TEST
mdefine_line|#define B3_MA_RC_TEST&t;0x01ca&t;/* 16 bit&t;MAC Arbiter Recovery Test Reg */
multiline_comment|/* 0x01cc - 0x01cf&t;reserved */
multiline_comment|/* Packet Arbiter Registers, This are real timeouts */
DECL|macro|B3_PA_TOINI_RX1
mdefine_line|#define B3_PA_TOINI_RX1&t;0x01d0&t;/* 16 bit&t;Timeout Init Val Rx Path MAC 1*/
multiline_comment|/* 0x01d2 - 0x01d3:&t;reserved */
DECL|macro|B3_PA_TOINI_RX2
mdefine_line|#define B3_PA_TOINI_RX2&t;0x01d4&t;/* 16 bit&t;Timeout Init Val Rx Path MAC 2*/
multiline_comment|/* 0x01d6 - 0x01d7:&t;reserved */
DECL|macro|B3_PA_TOINI_TX1
mdefine_line|#define B3_PA_TOINI_TX1&t;0x01d8&t;/* 16 bit&t;Timeout Init Val Tx Path MAC 1*/
multiline_comment|/* 0x01da - 0x01db:&t;reserved */
DECL|macro|B3_PA_TOINI_TX2
mdefine_line|#define B3_PA_TOINI_TX2&t;0x01dc&t;/* 16 bit&t;Timeout Init Val Tx Path MAC 2*/
multiline_comment|/* 0x01de - 0x01df:&t;reserved */
DECL|macro|B3_PA_TOVAL_RX1
mdefine_line|#define B3_PA_TOVAL_RX1&t;0x01e0&t;/* 16 bit&t;Timeout Val Rx Path MAC 1 */
multiline_comment|/* 0x01e2 - 0x01e3:&t;reserved */
DECL|macro|B3_PA_TOVAL_RX2
mdefine_line|#define B3_PA_TOVAL_RX2&t;0x01e4&t;/* 16 bit&t;Timeout Val Rx Path MAC 2 */
multiline_comment|/* 0x01e6 - 0x01e7:&t;reserved */
DECL|macro|B3_PA_TOVAL_TX1
mdefine_line|#define B3_PA_TOVAL_TX1&t;0x01e8&t;/* 16 bit&t;Timeout Val Tx Path MAC 1 */
multiline_comment|/* 0x01ea - 0x01eb:&t;reserved */
DECL|macro|B3_PA_TOVAL_TX2
mdefine_line|#define B3_PA_TOVAL_TX2&t;0x01ec&t;/* 16 bit&t;Timeout Val Tx Path MAC 2 */
multiline_comment|/* 0x01ee - 0x01ef:&t;reserved */
DECL|macro|B3_PA_CTRL
mdefine_line|#define B3_PA_CTRL&t;0x01f0&t;/* 16 bit&t;Packet Arbiter Ctrl Register */
DECL|macro|B3_PA_TEST
mdefine_line|#define B3_PA_TEST&t;0x01f2&t;/* 16 bit&t;Packet Arbiter Test Register */
multiline_comment|/* 0x01f4 - 0x01ff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 4 - 5&n; */
multiline_comment|/* Transmit Arbiter Registers MAC 1 and 2, user MR_ADDR() to address */
DECL|macro|TXA_ITI_INI
mdefine_line|#define TXA_ITI_INI&t;0x0200&t;/* 32 bit&t;Tx Arb Interval Timer Init Val*/
DECL|macro|TXA_ITI_VAL
mdefine_line|#define TXA_ITI_VAL&t;0x0204&t;/* 32 bit&t;Tx Arb Interval Timer Value */
DECL|macro|TXA_LIM_INI
mdefine_line|#define TXA_LIM_INI&t;0x0208&t;/* 32 bit&t;Tx Arb Limit Counter Init Val */
DECL|macro|TXA_LIM_VAL
mdefine_line|#define TXA_LIM_VAL&t;0x020c&t;/* 32 bit&t;Tx Arb Limit Counter Value */
DECL|macro|TXA_CTRL
mdefine_line|#define TXA_CTRL&t;0x0210&t;/*  8 bit&t;Tx Arbiter Control Register */
DECL|macro|TXA_TEST
mdefine_line|#define TXA_TEST&t;0x0211&t;/*  8 bit&t;Tx Arbiter Test Register */
DECL|macro|TXA_STAT
mdefine_line|#define TXA_STAT&t;0x0212&t;/*  8 bit&t;Tx Arbiter Status Register */
multiline_comment|/* 0x0213 - 0x027f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 6&n; */
multiline_comment|/* External registers */
DECL|macro|B6_EXT_REG
mdefine_line|#define B6_EXT_REG&t;0x0300
multiline_comment|/*&n; *&t;Bank 7&n; */
multiline_comment|/* This is a copy of the Configuration register file (lower half) */
DECL|macro|B7_CFG_SPC
mdefine_line|#define B7_CFG_SPC&t;0x0380
multiline_comment|/*&n; *&t;Bank 8 - 15&n; */
multiline_comment|/* Receive and Transmit Queue Registers, use Q_ADDR() to access */
DECL|macro|B8_Q_REGS
mdefine_line|#define&t;B8_Q_REGS&t;0x0400
multiline_comment|/* Queue Register Offsets, use Q_ADDR() to access */
DECL|macro|Q_D
mdefine_line|#define Q_D&t;0x00&t;/* 8*32&t;bit&t;Current Descriptor */
DECL|macro|Q_DA_L
mdefine_line|#define Q_DA_L&t;0x20&t;/* 32 bit&t;Current Descriptor Address Low dWord */
DECL|macro|Q_DA_H
mdefine_line|#define Q_DA_H&t;0x24&t;/* 32 bit&t;Current Descriptor Address High dWord */
DECL|macro|Q_AC_L
mdefine_line|#define Q_AC_L&t;0x28&t;/* 32 bit&t;Current Address Counter Low dWord */
DECL|macro|Q_AC_H
mdefine_line|#define Q_AC_H&t;0x2c&t;/* 32 bit&t;Current Address Counter High dWord */
DECL|macro|Q_BC
mdefine_line|#define Q_BC&t;0x30&t;/* 32 bit&t;Current Byte Counter */
DECL|macro|Q_CSR
mdefine_line|#define Q_CSR&t;0x34&t;/* 32 bit&t;BMU Control/Status Register */
DECL|macro|Q_F
mdefine_line|#define Q_F&t;0x38&t;/* 32 bit&t;Flag Register */
DECL|macro|Q_T1
mdefine_line|#define Q_T1&t;0x3c&t;/* 32 bit&t;Test Register 1 */
DECL|macro|Q_T1_TR
mdefine_line|#define Q_T1_TR&t;0x3c&t;/*  8 bit&t;Test Register 1 Transfer SM */
DECL|macro|Q_T1_WR
mdefine_line|#define Q_T1_WR&t;0x3d&t;/*  8 bit&t;Test Register 1 Write Descriptor SM */
DECL|macro|Q_T1_RD
mdefine_line|#define Q_T1_RD&t;0x3e&t;/*  8 bit&t;Test Register 1 Read Descriptor SM */
DECL|macro|Q_T1_SV
mdefine_line|#define Q_T1_SV&t;0x3f&t;/*  8 bit&t;Test Register 1 Supervisor SM */
DECL|macro|Q_T2
mdefine_line|#define Q_T2&t;0x40&t;/* 32 bit&t;Test Register 2&t;*/
DECL|macro|Q_T3
mdefine_line|#define Q_T3&t;0x44&t;/* 32 bit&t;Test Register 3&t;*/
multiline_comment|/* 0x48 - 0x7f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 16 - 23&n; */
multiline_comment|/* RAM Buffer Registers */
DECL|macro|B16_RAM_REGS
mdefine_line|#define&t;B16_RAM_REGS&t;0x0800
multiline_comment|/* RAM Buffer Register Offsets */
multiline_comment|/* use RB_ADDR(Queue,Offs) to address */
DECL|macro|RB_START
mdefine_line|#define RB_START&t;0x00&t;/* 32 bit&t;RAM Buffer Start Address */
DECL|macro|RB_END
mdefine_line|#define RB_END&t;&t;0x04&t;/* 32 bit&t;RAM Buffer End Address */
DECL|macro|RB_WP
mdefine_line|#define RB_WP&t;&t;0x08&t;/* 32 bit&t;RAM Buffer Write Pointer */
DECL|macro|RB_RP
mdefine_line|#define RB_RP&t;&t;0x0c&t;/* 32 bit&t;RAM Buffer Read Pointer */
DECL|macro|RB_RX_UTPP
mdefine_line|#define RB_RX_UTPP&t;0x10&t;/* 32 bit&t;Rx Upper Threshold, Pause Pack*/
DECL|macro|RB_RX_LTPP
mdefine_line|#define RB_RX_LTPP&t;0x14&t;/* 32 bit&t;Rx Lower Threshold, Pause Pack*/
DECL|macro|RB_RX_UTHP
mdefine_line|#define RB_RX_UTHP&t;0x18&t;/* 32 bit&t;Rx Upper Threshold, High Prio */
DECL|macro|RB_RX_LTHP
mdefine_line|#define RB_RX_LTHP&t;0x1c&t;/* 32 bit&t;Rx Lower Threshold, High Prio */
multiline_comment|/* 0x10 - 0x1f:&t;&t;reserved for Tx RAM Buffer Registers */
DECL|macro|RB_PC
mdefine_line|#define RB_PC&t;&t;0x20&t;/* 32 bit&t;RAM Buffer Packet Counter */
DECL|macro|RB_LEV
mdefine_line|#define RB_LEV&t;&t;0x24&t;/* 32 bit&t;RAM Buffer Level Register */
DECL|macro|RB_CTRL
mdefine_line|#define RB_CTRL&t;&t;0x28&t;/*  8 bit&t;RAM Buffer Control Register */
DECL|macro|RB_TST1
mdefine_line|#define RB_TST1&t;&t;0x29&t;/*  8 bit&t;RAM Buffer Test Register 1 */
DECL|macro|RB_TST2
mdefine_line|#define RB_TST2&t;&t;0x2A&t;/*  8 bit&t;RAM Buffer Test Register 2 */
multiline_comment|/* 0x2c - 0x7f:&t;&t;reserved */
multiline_comment|/*&n; *&t;Bank 24 - 25&n; */
multiline_comment|/* Receive MAC FIFO, Receive LED, and Link Sync regs, use MR_ADDR() to address*/
DECL|macro|RX_MFF_EA
mdefine_line|#define RX_MFF_EA&t;0x0c00&t;/* 32 bit&t;Receive MAC FIFO End Address */
DECL|macro|RX_MFF_WP
mdefine_line|#define RX_MFF_WP&t;0x0c04&t;/* 32 bit &t;Receive MAC FIFO Write Pointer*/
multiline_comment|/* 0x0c08 - 0x0c0b&t;reserved */
DECL|macro|RX_MFF_RP
mdefine_line|#define RX_MFF_RP&t;0x0c0c&t;/* 32 bit&t;Receive MAC FIFO Read Pointer */
DECL|macro|RX_MFF_PC
mdefine_line|#define RX_MFF_PC&t;0x0c10&t;/* 32 bit&t;Receive MAC FIFO Packet Cnt */
DECL|macro|RX_MFF_LEV
mdefine_line|#define RX_MFF_LEV&t;0x0c14&t;/* 32 bit&t;Receive MAC FIFO Level */
DECL|macro|RX_MFF_CTRL1
mdefine_line|#define RX_MFF_CTRL1&t;0x0c18&t;/* 16 bit&t;Receive MAC FIFO Control Reg 1*/
DECL|macro|RX_MFF_STAT_TO
mdefine_line|#define RX_MFF_STAT_TO&t;0x0c1a&t;/*  8 bit&t;Receive MAC Status Timeout */
DECL|macro|RX_MFF_TIST_TO
mdefine_line|#define RX_MFF_TIST_TO&t;0x0c1b&t;/*  8 bit&t;Receive MAC Timestamp Timeout */
DECL|macro|RX_MFF_CTRL2
mdefine_line|#define RX_MFF_CTRL2&t;0x0c1c&t;/*  8 bit&t;Receive MAC FIFO Control Reg 2*/
DECL|macro|RX_MFF_TST1
mdefine_line|#define RX_MFF_TST1&t;0x0c1d&t;/*  8 bit&t;Receive MAC FIFO Test Reg 1 */
DECL|macro|RX_MFF_TST2
mdefine_line|#define RX_MFF_TST2&t;0x0c1e&t;/*  8 bit&t;Receive MAC FIFO Test Reg 2 */
multiline_comment|/* 0x0c1f&t;&t;reserved */
DECL|macro|RX_LED_INI
mdefine_line|#define RX_LED_INI&t;0x0c20&t;/* 32 bit&t;Receive LED Cnt Init Value */
DECL|macro|RX_LED_VAL
mdefine_line|#define RX_LED_VAL&t;0x0c24&t;/* 32 bit&t;Receive LED Cnt Current Value */
DECL|macro|RX_LED_CTRL
mdefine_line|#define RX_LED_CTRL&t;0x0c28&t;/*  8 bit&t;Receive LED Cnt Control Reg */
DECL|macro|RX_LED_TST
mdefine_line|#define RX_LED_TST&t;0x0c29&t;/*  8 bit&t;Receive LED Cnt Test Register */
multiline_comment|/* 0x0c2a - 0x0c2f&t;reserved */
DECL|macro|LNK_SYNC_INI
mdefine_line|#define LNK_SYNC_INI&t;0x0c30&t;/* 32 bit&t;Link Sync Cnt Init Value */
DECL|macro|LNK_SYNC_VAL
mdefine_line|#define LNK_SYNC_VAL&t;0x0c34&t;/* 32 bit&t;Link Sync Cnt Current Value */
DECL|macro|LNK_SYNC_CTRL
mdefine_line|#define LNK_SYNC_CTRL&t;0x0c38&t;/*  8 bit&t;Link Sync Cnt Control Register*/
DECL|macro|LNK_SYNC_TST
mdefine_line|#define LNK_SYNC_TST&t;0x0c39&t;/*  8 bit&t;Link Sync Cnt Test Register */
multiline_comment|/* 0x0c3a - 0x0c3b&t;reserved */
DECL|macro|LNK_LED_REG
mdefine_line|#define LNK_LED_REG&t;0x0c3c&t;/*  8 bit&t;Link LED Register */
multiline_comment|/* 0x0c3d - 0x0c7f&t;reserved */
multiline_comment|/*&n; *&t;Bank 26 - 27&n; */
multiline_comment|/* Transmit MAC FIFO and Transmit LED Registers, use MR_ADDR() to address */
DECL|macro|TX_MFF_EA
mdefine_line|#define TX_MFF_EA&t;0x0d00&t;/* 32 bit&t;Transmit MAC FIFO End Address */
DECL|macro|TX_MFF_WP
mdefine_line|#define TX_MFF_WP&t;0x0d04&t;/* 32 bit &t;Transmit MAC FIFO WR Pointer */
DECL|macro|TX_MFF_WSP
mdefine_line|#define TX_MFF_WSP&t;0x0d08&t;/* 32 bit&t;Transmit MAC FIFO WR Shadow Pt*/
DECL|macro|TX_MFF_RP
mdefine_line|#define TX_MFF_RP&t;0x0d0c&t;/* 32 bit&t;Transmit MAC FIFO RD Pointer */
DECL|macro|TX_MFF_PC
mdefine_line|#define TX_MFF_PC&t;0x0d10&t;/* 32 bit&t;Transmit MAC FIFO Packet Cnt */
DECL|macro|TX_MFF_LEV
mdefine_line|#define TX_MFF_LEV&t;0x0d14&t;/* 32 bit&t;Transmit MAC FIFO Level */
DECL|macro|TX_MFF_CTRL1
mdefine_line|#define TX_MFF_CTRL1&t;0x0d18&t;/* 16 bit&t;Transmit MAC FIFO Ctrl Reg 1 */
DECL|macro|TX_MFF_WAF
mdefine_line|#define TX_MFF_WAF&t;0x0d1a&t;/*  8 bit&t;Transmit MAC Wait after flush*/
multiline_comment|/* 0x0c1b&t;&t;reserved */
DECL|macro|TX_MFF_CTRL2
mdefine_line|#define TX_MFF_CTRL2&t;0x0d1c&t;/*  8 bit&t;Transmit MAC FIFO Ctrl Reg 2 */
DECL|macro|TX_MFF_TST1
mdefine_line|#define TX_MFF_TST1&t;0x0d1d&t;/*  8 bit&t;Transmit MAC FIFO Test Reg 1 */
DECL|macro|TX_MFF_TST2
mdefine_line|#define TX_MFF_TST2&t;0x0d1e&t;/*  8 bit&t;Transmit MAC FIFO Test Reg 2 */
multiline_comment|/* 0x0d1f&t;&t;reserved */
DECL|macro|TX_LED_INI
mdefine_line|#define TX_LED_INI&t;0x0d20&t;/* 32 bit&t;Transmit LED Cnt Init Value */
DECL|macro|TX_LED_VAL
mdefine_line|#define TX_LED_VAL&t;0x0d24&t;/* 32 bit&t;Transmit LED Cnt Current Val */
DECL|macro|TX_LED_CTRL
mdefine_line|#define TX_LED_CTRL&t;0x0d28&t;/*  8 bit&t;Transmit LED Cnt Control Reg */
DECL|macro|TX_LED_TST
mdefine_line|#define TX_LED_TST&t;0x0d29&t;/*  8 bit&t;Transmit LED Cnt Test Register*/
multiline_comment|/* 0x0d2a - 0x0d7f&t;reserved */
multiline_comment|/*&n; *&t;Bank 28&n; */
multiline_comment|/* Descriptor Poll Timer Registers */
DECL|macro|B28_DPT_INI
mdefine_line|#define B28_DPT_INI&t;0x0e00&t;/* 32 bit&t;Descriptor Poll Timer Init Val*/
DECL|macro|B28_DPT_VAL
mdefine_line|#define B28_DPT_VAL&t;0x0e04&t;/* 32 bit&t;Descriptor Poll Timer Curr Val*/
DECL|macro|B28_DPT_CTRL
mdefine_line|#define B28_DPT_CTRL&t;0x0e08&t;/*  8 bit&t;Descriptor Poll Timer Ctrl Reg*/
multiline_comment|/* 0x0e09:&t;&t;reserved */
DECL|macro|B28_DPT_TST
mdefine_line|#define B28_DPT_TST&t;0x0e0a&t;/*  8 bit&t;Descriptor Poll Timer Test Reg*/
multiline_comment|/* 0x0e0b - 0x0e8f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 29 - 31&n; */
multiline_comment|/* 0x0e90 - 0x0fff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 0x20 - 0x3f&n; */
multiline_comment|/* 0x1000 - 0x1fff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 0x40 - 0x4f&n; */
multiline_comment|/* XMAC 1 registers */
DECL|macro|B40_XMAC1
mdefine_line|#define B40_XMAC1&t;0x2000
multiline_comment|/*&n; *&t;Bank 0x50 - 0x5f&n; */
multiline_comment|/* 0x2800 - 0x2fff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 0x60 - 0x6f&n; */
multiline_comment|/* XMAC 2 registers */
DECL|macro|B40_XMAC2
mdefine_line|#define B40_XMAC2&t;0x3000
multiline_comment|/*&n; *&t;Bank 0x70 - 0x7f&n; */
multiline_comment|/* 0x3800 - 0x3fff:&t;reserved */
multiline_comment|/*&n; *&t;Control Register Bit Definitions:&n; */
multiline_comment|/*&t;B0_RAP&t;&t;8 bit&t;Register Address Port */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|RAP_RAP
mdefine_line|#define&t;RAP_RAP&t;&t;0x3f&t;/* Bit 6..0:&t;0 = block 0, .., 6f = block 6f*/
multiline_comment|/*&t;B0_CTST&t;&t;16 bit&t;Control/Status register */
multiline_comment|/* Bit 15..10:&t;reserved */
DECL|macro|CS_BUS_CLOCK
mdefine_line|#define CS_BUS_CLOCK&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Bus Clock 0/1 = 33/66MHz */
DECL|macro|CS_BUS_SLOT_SZ
mdefine_line|#define CS_BUS_SLOT_SZ&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Slot Size 0/1 = 32/64 bit slot*/
DECL|macro|CS_ST_SW_IRQ
mdefine_line|#define CS_ST_SW_IRQ&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;Set IRQ SW Request&t;*/
DECL|macro|CS_CL_SW_IRQ
mdefine_line|#define CS_CL_SW_IRQ&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Clear IRQ SW Request&t;*/
DECL|macro|CS_STOP_DONE
mdefine_line|#define CS_STOP_DONE&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Stop Master is finished */
DECL|macro|CS_STOP_MAST
mdefine_line|#define&t;CS_STOP_MAST&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Command Bit to stop the master*/
DECL|macro|CS_MRST_CLR
mdefine_line|#define&t;CS_MRST_CLR&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Clear Master reset&t;*/
DECL|macro|CS_MRST_SET
mdefine_line|#define&t;CS_MRST_SET&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Set Master reset&t;*/
DECL|macro|CS_RST_CLR
mdefine_line|#define&t;CS_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Clear Software reset&t;*/
DECL|macro|CS_RST_SET
mdefine_line|#define&t;CS_RST_SET&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Set Software reset&t;*/
multiline_comment|/*&t;B0_LED&t;&t; 8 Bit&t;LED register */
multiline_comment|/* Bit 7..2:&t;reserved */
DECL|macro|LED_STAT_ON
mdefine_line|#define LED_STAT_ON&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Status LED on&t;*/
DECL|macro|LED_STAT_OFF
mdefine_line|#define LED_STAT_OFF&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Status LED off&t;*/
multiline_comment|/*&t;B0_ISRC&t;&t;32 bit&t;Interrupt Source Register */
multiline_comment|/*&t;B0_IMSK&t;&t;32 bit&t;Interrupt Mask Register */
multiline_comment|/*&t;B0_SP_ISRC&t;32 bit&t;Special Interrupt Source Reg */
multiline_comment|/*&t;B2_IRQM_MSK &t;32 bit&t;IRQ Moderation Mask */
DECL|macro|IS_ALL_MSK
mdefine_line|#define IS_ALL_MSK&t;0xbfffffffL&t;/* &t;&t;All Interrupt bits */
DECL|macro|IS_HW_ERR
mdefine_line|#define IS_HW_ERR&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;Interrupt HW Error */
multiline_comment|/* Bit 30:&t;reserved */
DECL|macro|IS_PA_TO_RX1
mdefine_line|#define IS_PA_TO_RX1&t;(1L&lt;&lt;29)&t;/* Bit 29:&t;Packet Arb Timeout Rx1*/
DECL|macro|IS_PA_TO_RX2
mdefine_line|#define IS_PA_TO_RX2&t;(1L&lt;&lt;28)&t;/* Bit 28:&t;Packet Arb Timeout Rx2*/
DECL|macro|IS_PA_TO_TX1
mdefine_line|#define IS_PA_TO_TX1&t;(1L&lt;&lt;27)&t;/* Bit 27:&t;Packet Arb Timeout Tx1*/
DECL|macro|IS_PA_TO_TX2
mdefine_line|#define IS_PA_TO_TX2&t;(1L&lt;&lt;26)&t;/* Bit 26:&t;Packet Arb Timeout Tx2*/
DECL|macro|IS_I2C_READY
mdefine_line|#define IS_I2C_READY&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;IRQ on end of I2C tx */
DECL|macro|IS_IRQ_SW
mdefine_line|#define IS_IRQ_SW&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;SW forced IRQ&t;*/
DECL|macro|IS_EXT_REG
mdefine_line|#define IS_EXT_REG&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;IRQ from external reg */
DECL|macro|IS_TIMINT
mdefine_line|#define&t;IS_TIMINT&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;IRQ from Timer&t;*/
DECL|macro|IS_MAC1
mdefine_line|#define IS_MAC1&t;&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;IRQ from MAC 1&t;*/
DECL|macro|IS_LNK_SYNC_M1
mdefine_line|#define IS_LNK_SYNC_M1&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;Link Sync Cnt wrap M1 */
DECL|macro|IS_MAC2
mdefine_line|#define IS_MAC2&t;&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;IRQ from MAC 2&t;*/
DECL|macro|IS_LNK_SYNC_M2
mdefine_line|#define IS_LNK_SYNC_M2&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Link Sync Cnt wrap M2 */
multiline_comment|/* Receive Queue 1 */
DECL|macro|IS_R1_B
mdefine_line|#define&t;IS_R1_B&t;&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Q_R1 End of Buffer */
DECL|macro|IS_R1_F
mdefine_line|#define&t;IS_R1_F&t;&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;Q_R1 End of Frame */
DECL|macro|IS_R1_C
mdefine_line|#define&t;IS_R1_C&t;&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Q_R1 Encoding Error */
multiline_comment|/* Receive Queue 2 */
DECL|macro|IS_R2_B
mdefine_line|#define&t;IS_R2_B&t;&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Q_R2 End of Buffer */
DECL|macro|IS_R2_F
mdefine_line|#define&t;IS_R2_F&t;&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Q_R2 End of Frame */
DECL|macro|IS_R2_C
mdefine_line|#define&t;IS_R2_C&t;&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Q_R2 Encoding Error */
multiline_comment|/* Synchronous Transmit Queue 1 */
DECL|macro|IS_XS1_B
mdefine_line|#define&t;IS_XS1_B&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Q_XS1 End of Buffer */
DECL|macro|IS_XS1_F
mdefine_line|#define&t;IS_XS1_F&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Q_XS1 End of Frame */
DECL|macro|IS_XS1_C
mdefine_line|#define&t;IS_XS1_C&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Q_XS1 Encoding Error */
multiline_comment|/* Asynchronous Transmit Queue 1 */
DECL|macro|IS_XA1_B
mdefine_line|#define&t;IS_XA1_B&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Q_XA1 End of Buffer */
DECL|macro|IS_XA1_F
mdefine_line|#define&t;IS_XA1_F&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Q_XA1 End of Frame */
DECL|macro|IS_XA1_C
mdefine_line|#define&t;IS_XA1_C&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Q_XA1 Encoding Error */
multiline_comment|/* Synchronous Transmit Queue 2 */
DECL|macro|IS_XS2_B
mdefine_line|#define&t;IS_XS2_B&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Q_XS2 End of Buffer */
DECL|macro|IS_XS2_F
mdefine_line|#define&t;IS_XS2_F&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Q_XS2 End of Frame */
DECL|macro|IS_XS2_C
mdefine_line|#define&t;IS_XS2_C&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Q_XS2 Encoding Error */
multiline_comment|/* Asynchronous Transmit Queue 2 */
DECL|macro|IS_XA2_B
mdefine_line|#define&t;IS_XA2_B&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Q_XA2 End of Buffer */
DECL|macro|IS_XA2_F
mdefine_line|#define&t;IS_XA2_F&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Q_XA2 End of Frame */
DECL|macro|IS_XA2_C
mdefine_line|#define&t;IS_XA2_C&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Q_XA2 Encoding Error */
multiline_comment|/*&t;B0_HWE_ISRC&t;32 bit&t;HW Error Interrupt Src Reg */
multiline_comment|/*&t;B0_HWE_IMSK&t;32 bit&t;HW Error Interrupt Mask Reg */
multiline_comment|/*&t;B2_IRQM_HWE_MSK 32 bit&t;IRQ Moderation HW Error Mask */
DECL|macro|IS_ERR_MSK
mdefine_line|#define IS_ERR_MSK&t;0x00000fffL&t;/* &t;&t;All Error bits */
multiline_comment|/* Bit 31..12:&t;reserved */
DECL|macro|IS_IRQ_MST_ERR
mdefine_line|#define&t;IS_IRQ_MST_ERR&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;IRQ master error */
multiline_comment|/*&t;PERR,RMABORT,RTABORT,DATAPERR */
DECL|macro|IS_IRQ_STAT
mdefine_line|#define&t;IS_IRQ_STAT&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;IRQ status execption */
multiline_comment|/*&t;RMABORT, RTABORT, DATAPERR */
DECL|macro|IS_NO_STAT_M1
mdefine_line|#define IS_NO_STAT_M1&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;No Rx Status from MAC1*/
DECL|macro|IS_NO_STAT_M2
mdefine_line|#define IS_NO_STAT_M2&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;No Rx Status from MAC2*/
DECL|macro|IS_NO_TIST_M1
mdefine_line|#define IS_NO_TIST_M1&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;No Timestamp from MAC1*/
DECL|macro|IS_NO_TIST_M2
mdefine_line|#define IS_NO_TIST_M2&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;No Timestamp from MAC2*/
DECL|macro|IS_RAM_RD_PAR
mdefine_line|#define IS_RAM_RD_PAR&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;RAM Read Parity Error */
DECL|macro|IS_RAM_WR_PAR
mdefine_line|#define IS_RAM_WR_PAR&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;RAM Write Parity Error*/
DECL|macro|IS_M1_PAR_ERR
mdefine_line|#define IS_M1_PAR_ERR&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;MAC 1 Parity Error */
DECL|macro|IS_M2_PAR_ERR
mdefine_line|#define IS_M2_PAR_ERR&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;MAC 2 Parity Error */
DECL|macro|IS_R1_PAR_ERR
mdefine_line|#define IS_R1_PAR_ERR&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Queue R1 Parity Error */
DECL|macro|IS_R2_PAR_ERR
mdefine_line|#define IS_R2_PAR_ERR&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Queue R2 Parity Error */
multiline_comment|/*&t;B2_CONN_TYP&t; 8 bit&t;Connector type */
multiline_comment|/*&t;B2_PMD_TYP&t; 8 bit&t;PMD type */
multiline_comment|/*&t;Values of connector and PMD type comply to SysKonnect internal std */
multiline_comment|/*&t;B2_MAC_CFG&t; 8 bit&t;MAC Configuration */
multiline_comment|/* Bit 7..2:&t;reserved */
DECL|macro|CFG_DIS_M2_CLK
mdefine_line|#define&t;CFG_DIS_M2_CLK&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Disable Clock for 2nd MAC */
DECL|macro|CFG_SNG_MAC
mdefine_line|#define CFG_SNG_MAC&t;(1&lt;&lt;0)&t;/* Bit 0:&t;MAC Config: 1=2 MACs / 0=1 MAC*/
multiline_comment|/*&t;B2_CHIP_REV&t; 8 bit &t;Queen Chip Revision Number */
DECL|macro|FIRST_CHIP_REV
mdefine_line|#define FIRST_CHIP_REV&t;0x0a&t;/* Initial Revision Value */
multiline_comment|/*&t;B2_FAR&t;&t;32 bit&t;Flash-Prom Addr Reg/Cnt */
DECL|macro|FAR_ADDR
mdefine_line|#define&t;FAR_ADDR&t;0x1ffffL&t;/* Bit 16..0:&t;FPROM Address mask */
multiline_comment|/*&t;B2_LD_CRTL&t; 8 bit&t;EPROM loader control register */
multiline_comment|/*&t;Bits are currently reserved */
multiline_comment|/*&t;B2_LD_TEST&t; 8 bit&t;EPROM loader test register */
multiline_comment|/* Bit 7..4:&t;reserved */
DECL|macro|LD_T_ON
mdefine_line|#define&t;LD_T_ON&t;&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Loader Testmode on */
DECL|macro|LD_T_OFF
mdefine_line|#define&t;LD_T_OFF&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Loader Testmode off */
DECL|macro|LD_T_STEP
mdefine_line|#define&t;LD_T_STEP&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Decrement FPROM addr. Counter */
DECL|macro|LD_START
mdefine_line|#define&t;LD_START&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Start loading FPROM */
multiline_comment|/*&n; *&t;Timer Section&n; */
multiline_comment|/*&t;B2_TI_CRTL&t; 8 bit&t;Timer control */
multiline_comment|/*&t;B2_IRQM_CTRL&t; 8 bit&t;IRQ Moderation Timer Control */
multiline_comment|/* Bit 7..3:&t;reserved */
DECL|macro|TIM_START
mdefine_line|#define TIM_START&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Start Timer */
DECL|macro|TIM_STOP
mdefine_line|#define TIM_STOP&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Stop Timer */
DECL|macro|TIM_CLR_IRQ
mdefine_line|#define TIM_CLR_IRQ&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Clear Timer IRQ, (!IRQM) */
multiline_comment|/*&t;B2_TI_TEST&t; 8 Bit&t;Timer Test */
multiline_comment|/*&t;B2_IRQM_TEST&t; 8 bit&t;IRQ Moderation Timer Test */
multiline_comment|/*&t;B28_DPT_TST&t; 8 bit&t;Descriptor Poll Timer Test Reg */
multiline_comment|/* Bit 7..3:&t;reserved */
DECL|macro|TIM_T_ON
mdefine_line|#define&t;TIM_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Test mode on */
DECL|macro|TIM_T_OFF
mdefine_line|#define&t;TIM_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Test mode off */
DECL|macro|TIM_T_STEP
mdefine_line|#define&t;TIM_T_STEP&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Test step */
multiline_comment|/*&t;B28_DPT_INI&t;32 bit&t;Descriptor Poll Timer Init Val */
multiline_comment|/*&t;B28_DPT_VAL&t;32 bit&t;Descriptor Poll Timer Curr Val */
multiline_comment|/* Bit 31..24:&t;reserved */
DECL|macro|DPT_MSK
mdefine_line|#define DPT_MSK&t;0x00ffffffL&t;/* Bit 23.. 0:&t;Desc Poll Timer Bits */
multiline_comment|/*&t;B28_DPT_CTRL&t; 8 bit&t;Descriptor Poll Timer Ctrl Reg */
multiline_comment|/* Bit 7..2:&t;reserved */
DECL|macro|DPT_START
mdefine_line|#define DPT_START&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Start Desciptor Poll Timer */
DECL|macro|DPT_STOP
mdefine_line|#define DPT_STOP&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Stop Desciptor Poll Timer */
multiline_comment|/*&t;B2_TST_CTRL1&t; 8 bit&t;Test Control Register 1 */
DECL|macro|TST_FRC_DPERR_MR
mdefine_line|#define&t;TST_FRC_DPERR_MR&t;(1&lt;&lt;7)&t;/* Bit 7: force DATAPERR on MST RD */
DECL|macro|TST_FRC_DPERR_MW
mdefine_line|#define&t;TST_FRC_DPERR_MW&t;(1&lt;&lt;6)&t;/* Bit 6: force DATAPERR on MST WR */
DECL|macro|TST_FRC_DPERR_TR
mdefine_line|#define&t;TST_FRC_DPERR_TR&t;(1&lt;&lt;5)&t;/* Bit 5: force DATAPERR on TRG RD */
DECL|macro|TST_FRC_DPERR_TW
mdefine_line|#define&t;TST_FRC_DPERR_TW&t;(1&lt;&lt;4)&t;/* Bit 4: force DATAPERR on TRG WR */
DECL|macro|TST_FRC_APERR_M
mdefine_line|#define&t;TST_FRC_APERR_M&t;&t;(1&lt;&lt;3)&t;/* Bit 3: force ADDRPERR on MST */
DECL|macro|TST_FRC_APERR_T
mdefine_line|#define&t;TST_FRC_APERR_T&t;&t;(1&lt;&lt;2)&t;/* Bit 2: force ADDRPERR on TRG */
DECL|macro|TST_CFG_WRITE_ON
mdefine_line|#define&t;TST_CFG_WRITE_ON&t;(1&lt;&lt;1)&t;/* Bit 1: Enable Config Reg WR */
DECL|macro|TST_CFG_WRITE_OFF
mdefine_line|#define&t;TST_CFG_WRITE_OFF&t;(1&lt;&lt;0)&t;/* Bit 0: Disable Config Reg WR */
multiline_comment|/*&t;B2_TST_CTRL2&t; 8 bit&t;Test Control Register 2 */
multiline_comment|/* Bit 7..4:&t;reserved */
multiline_comment|/* force the following error on */
multiline_comment|/* the next master read/write&t;*/
DECL|macro|TST_FRC_DPERR_MR64
mdefine_line|#define TST_FRC_DPERR_MR64&t;(1&lt;&lt;3)&t;/* Bit 3:&t;DataPERR RD 64&t;*/
DECL|macro|TST_FRC_DPERR_MW64
mdefine_line|#define TST_FRC_DPERR_MW64&t;(1&lt;&lt;2)&t;/* Bit 2:&t;DataPERR WR 64&t;*/
DECL|macro|TST_FRC_APERR_1M64
mdefine_line|#define TST_FRC_APERR_1M64&t;(1&lt;&lt;1)&t;/* Bit 1:&t;AddrPERR on 1. phase */
DECL|macro|TST_FRC_APERR_2M64
mdefine_line|#define TST_FRC_APERR_2M64&t;(1&lt;&lt;0)&t;/* Bit 0:&t;AddrPERR on 2. phase */
multiline_comment|/*&t;B2_GP_IO&t;32 bit&t;General Purpose IO Register */
multiline_comment|/* Bit 31..26:&t;reserved */
DECL|macro|GP_DIR_9
mdefine_line|#define&t;GP_DIR_9&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;IO_9 direct, 0=I/1=O */
DECL|macro|GP_DIR_8
mdefine_line|#define&t;GP_DIR_8&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;IO_8 direct, 0=I/1=O */
DECL|macro|GP_DIR_7
mdefine_line|#define&t;GP_DIR_7&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;IO_7 direct, 0=I/1=O */
DECL|macro|GP_DIR_6
mdefine_line|#define&t;GP_DIR_6&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;IO_6 direct, 0=I/1=O */
DECL|macro|GP_DIR_5
mdefine_line|#define&t;GP_DIR_5&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;IO_5 direct, 0=I/1=O */
DECL|macro|GP_DIR_4
mdefine_line|#define&t;GP_DIR_4&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;IO_4 direct, 0=I/1=O */
DECL|macro|GP_DIR_3
mdefine_line|#define&t;GP_DIR_3&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;IO_3 direct, 0=I/1=O */
DECL|macro|GP_DIR_2
mdefine_line|#define&t;GP_DIR_2&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;IO_2 direct, 0=I/1=O */
DECL|macro|GP_DIR_1
mdefine_line|#define&t;GP_DIR_1&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;IO_1 direct, 0=I/1=O */
DECL|macro|GP_DIR_0
mdefine_line|#define&t;GP_DIR_0&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;IO_0 direct, 0=I/1=O */
multiline_comment|/* Bit 15..10:&t;reserved */
DECL|macro|GP_IO_9
mdefine_line|#define&t;GP_IO_9&t;&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;IO_9 pin */
DECL|macro|GP_IO_8
mdefine_line|#define&t;GP_IO_8&t;&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;IO_8 pin */
DECL|macro|GP_IO_7
mdefine_line|#define&t;GP_IO_7&t;&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;IO_7 pin */
DECL|macro|GP_IO_6
mdefine_line|#define&t;GP_IO_6&t;&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;IO_6 pin */
DECL|macro|GP_IO_5
mdefine_line|#define&t;GP_IO_5&t;&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;IO_5 pin */
DECL|macro|GP_IO_4
mdefine_line|#define&t;GP_IO_4&t;&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;IO_4 pin */
DECL|macro|GP_IO_3
mdefine_line|#define&t;GP_IO_3&t;&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;IO_3 pin */
DECL|macro|GP_IO_2
mdefine_line|#define&t;GP_IO_2&t;&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;IO_2 pin */
DECL|macro|GP_IO_1
mdefine_line|#define&t;GP_IO_1&t;&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;IO_1 pin */
DECL|macro|GP_IO_0
mdefine_line|#define&t;GP_IO_0&t;&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;IO_0 pin */
multiline_comment|/*&t;B2_I2C_CTRL&t;32 bit&t;I2C HW Control Register */
DECL|macro|I2C_FLAG
mdefine_line|#define&t;I2C_FLAG&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;Start read/write if WR*/
DECL|macro|I2C_ADDR
mdefine_line|#define I2C_ADDR&t;(0x7fffL&lt;&lt;16)&t;/* Bit 30..16:&t;Addr to be RD/WR */
DECL|macro|I2C_DEV_SEL
mdefine_line|#define&t;I2C_DEV_SEL&t;(0x7fL&lt;&lt;9)&t;/* Bit 15.. 9:&t;I2C Device Select */
multiline_comment|/* Bit&t;8.. 5:&t;reserved&t;*/
DECL|macro|I2C_BURST_LEN
mdefine_line|#define I2C_BURST_LEN&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Burst Len, 1/4 bytes */
DECL|macro|I2C_DEV_SIZE
mdefine_line|#define I2C_DEV_SIZE&t;(7L&lt;&lt;1)&t;&t;/* Bit&t;3.. 1:&t;I2C Device Size&t;*/
DECL|macro|I2C_025K_DEV
mdefine_line|#define I2C_025K_DEV&t;(0L&lt;&lt;1)&t;&t;/*&t;&t;0: 256 Bytes or smal. */
DECL|macro|I2C_05K_DEV
mdefine_line|#define I2C_05K_DEV&t;(1L&lt;&lt;1)&t;&t;/* &t;&t;1: 512&t;Bytes&t;*/
DECL|macro|I2C_1K_DEV
mdefine_line|#define&t;I2C_1K_DEV&t;(2L&lt;&lt;1)&t;&t;/*&t;&t;2: 1024 Bytes&t;*/
DECL|macro|I2C_2K_DEV
mdefine_line|#define I2C_2K_DEV&t;(3L&lt;&lt;1)&t;&t;/*&t;&t;3: 2048&t;Bytes&t;*/
DECL|macro|I2C_4K_DEV
mdefine_line|#define&t;I2C_4K_DEV&t;(4L&lt;&lt;1)&t;&t;/*&t;&t;4: 4096 Bytes&t;*/
DECL|macro|I2C_8K_DEV
mdefine_line|#define&t;I2C_8K_DEV&t;(5L&lt;&lt;1)&t;&t;/*&t;&t;5: 8192 Bytes&t;*/
DECL|macro|I2C_16K_DEV
mdefine_line|#define&t;I2C_16K_DEV&t;(6L&lt;&lt;1)&t;&t;/*&t;&t;6: 16384 Bytes&t;*/
DECL|macro|I2C_32K_DEV
mdefine_line|#define&t;I2C_32K_DEV&t;(7L&lt;&lt;1)&t;&t;/*&t;&t;7: 32768 Bytes&t;*/
DECL|macro|I2C_STOP
mdefine_line|#define I2C_STOP&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Interrupt I2C transfer*/
multiline_comment|/*&t;B2_I2C_IRQ&t;32 bit&t;I2C HW IRQ Register */
multiline_comment|/* Bit 31..1&t;reserved */
DECL|macro|I2C_CLR_IRQ
mdefine_line|#define I2C_CLR_IRQ&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Clear I2C IRQ */
multiline_comment|/*&t;B2_I2C_SW&t;32 bit&t;I2C HW SW Port Register */
multiline_comment|/* Bit 7..3:&t;reserved */
DECL|macro|I2C_DATA_DIR
mdefine_line|#define&t;I2C_DATA_DIR&t;(1&lt;&lt;2)&t;/* Bit 2:&t;direction of I2C_DATA */
DECL|macro|I2C_DATA
mdefine_line|#define I2C_DATA&t;(1&lt;&lt;1)&t;/* Bit 1:&t;I2C Data Port&t;*/
DECL|macro|I2C_CLK
mdefine_line|#define&t;I2C_CLK&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;I2C Clock Port&t;*/
multiline_comment|/*&n; * I2C Address&n; */
DECL|macro|I2C_SENS_ADDR
mdefine_line|#define&t;I2C_SENS_ADDR&t;LM80_ADDR&t;/* I2C Sensor Address, (Volt and Temp)*/
multiline_comment|/*&t;B2_BSC_CTRL&t; 8 bit&t;Blink Source Counter Control */
multiline_comment|/* Bit 7..2:&t;reserved */
DECL|macro|BSC_START
mdefine_line|#define BSC_START&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Start Blink Source Counter */
DECL|macro|BSC_STOP
mdefine_line|#define BSC_STOP&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Stop Blink Source Counter */
multiline_comment|/*&t;B2_BSC_STAT&t; 8 bit&t;Blink Source Counter Status */
multiline_comment|/* Bit 7..1:&t;reserved */
DECL|macro|BSC_SRC
mdefine_line|#define BSC_SRC&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Blink Source, 0=Off / 1=On */
multiline_comment|/*&t;B2_BSC_TST&t;16 bit&t;Blink Source Counter Test Reg */
DECL|macro|BSC_T_ON
mdefine_line|#define&t;BSC_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Test mode on */
DECL|macro|BSC_T_OFF
mdefine_line|#define&t;BSC_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Test mode off */
DECL|macro|BSC_T_STEP
mdefine_line|#define&t;BSC_T_STEP&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Test step */
multiline_comment|/*&t;B3_RAM_ADDR&t;32 bit&t;RAM Address, to read or write */
multiline_comment|/* Bit 31..19:&t;reserved */
DECL|macro|RAM_ADR_RAN
mdefine_line|#define RAM_ADR_RAN&t;0x0007ffffL&t;/* Bit 18.. 0:&t;RAM Address Range */
multiline_comment|/* RAM Interface Registers */
multiline_comment|/*&t;B3_RI_CTRL&t;16 bit&t;RAM Iface Control Register */
multiline_comment|/* Bit 15..10:&t;reserved */
DECL|macro|RI_CLR_RD_PERR
mdefine_line|#define RI_CLR_RD_PERR&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Clear IRQ RAM Read Parity Err */
DECL|macro|RI_CLR_WR_PERR
mdefine_line|#define RI_CLR_WR_PERR&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Clear IRQ RAM Write Parity Err*/
multiline_comment|/* Bit&t;7..2:&t;reserved */
DECL|macro|RI_RST_CLR
mdefine_line|#define RI_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Clear RAM Interface Reset */
DECL|macro|RI_RST_SET
mdefine_line|#define RI_RST_SET&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Set RAM Interface Reset */
multiline_comment|/*&t;B3_RI_TEST&t; 8 bit&t;RAM Iface Test Register */
multiline_comment|/* Bit 15..4:&t;reserved */
DECL|macro|RI_T_EV
mdefine_line|#define RI_T_EV&t;&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Timeout Event occured */
DECL|macro|RI_T_ON
mdefine_line|#define RI_T_ON&t;&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Timeout Timer Test On */
DECL|macro|RI_T_OFF
mdefine_line|#define RI_T_OFF&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Timeout Timer Test Off */
DECL|macro|RI_T_STEP
mdefine_line|#define RI_T_STEP&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Timeout Timer Step */
multiline_comment|/* MAC Arbiter Registers */
multiline_comment|/*&t;B3_MA_TO_CTRL&t;16 bit&t;MAC Arbiter Timeout Ctrl Reg */
multiline_comment|/* Bit 15..4:&t;reserved */
DECL|macro|MA_FOE_ON
mdefine_line|#define MA_FOE_ON&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;XMAC Fast Output Enable ON */
DECL|macro|MA_FOE_OFF
mdefine_line|#define MA_FOE_OFF&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;XMAC Fast Output Enable OFF */
DECL|macro|MA_RST_CLR
mdefine_line|#define MA_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Clear MAC Arbiter Reset */
DECL|macro|MA_RST_SET
mdefine_line|#define MA_RST_SET&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Set MAC Arbiter Reset */
multiline_comment|/*&t;B3_MA_RC_CTRL&t;16 bit&t;MAC Arbiter Recovery Ctrl Reg */
multiline_comment|/* Bit 15..8:&t;reserved */
DECL|macro|MA_ENA_REC_TX2
mdefine_line|#define MA_ENA_REC_TX2&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;Enable Recovery Timer TX2 */
DECL|macro|MA_DIS_REC_TX2
mdefine_line|#define MA_DIS_REC_TX2&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Disable Recovery Timer TX2 */
DECL|macro|MA_ENA_REC_TX1
mdefine_line|#define MA_ENA_REC_TX1&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Enable Recovery Timer TX1 */
DECL|macro|MA_DIS_REC_TX1
mdefine_line|#define MA_DIS_REC_TX1&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Disable Recovery Timer TX1 */
DECL|macro|MA_ENA_REC_RX2
mdefine_line|#define MA_ENA_REC_RX2&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Enable Recovery Timer RX2 */
DECL|macro|MA_DIS_REC_RX2
mdefine_line|#define MA_DIS_REC_RX2&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Disable Recovery Timer RX2 */
DECL|macro|MA_ENA_REC_RX1
mdefine_line|#define MA_ENA_REC_RX1&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Enable Recovery Timer RX1 */
DECL|macro|MA_DIS_REC_RX1
mdefine_line|#define MA_DIS_REC_RX1&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Disable Recovery Timer RX1 */
multiline_comment|/* Packet Arbiter Registers */
multiline_comment|/*&t;B3_PA_CTRL&t;16 bit&t;Packet Arbiter Ctrl Register */
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|PA_CLR_TO_TX2
mdefine_line|#define PA_CLR_TO_TX2&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Clear IRQ Packet Timeout TX2 */
DECL|macro|PA_CLR_TO_TX1
mdefine_line|#define PA_CLR_TO_TX1&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Clear IRQ Packet Timeout TX1 */
DECL|macro|PA_CLR_TO_RX2
mdefine_line|#define PA_CLR_TO_RX2&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Clear IRQ Packet Timeout RX2 */
DECL|macro|PA_CLR_TO_RX1
mdefine_line|#define PA_CLR_TO_RX1&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Clear IRQ Packet Timeout RX1 */
DECL|macro|PA_ENA_TO_TX2
mdefine_line|#define PA_ENA_TO_TX2&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Enable Timeout Timer TX2 */
DECL|macro|PA_DIS_TO_TX2
mdefine_line|#define PA_DIS_TO_TX2&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Disable Timeout Timer TX2 */
DECL|macro|PA_ENA_TO_TX1
mdefine_line|#define PA_ENA_TO_TX1&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;Enable Timeout Timer TX1 */
DECL|macro|PA_DIS_TO_TX1
mdefine_line|#define PA_DIS_TO_TX1&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Disable Timeout Timer TX1 */
DECL|macro|PA_ENA_TO_RX2
mdefine_line|#define PA_ENA_TO_RX2&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Enable Timeout Timer RX2 */
DECL|macro|PA_DIS_TO_RX2
mdefine_line|#define PA_DIS_TO_RX2&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Disable Timeout Timer RX2 */
DECL|macro|PA_ENA_TO_RX1
mdefine_line|#define PA_ENA_TO_RX1&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Enable Timeout Timer RX1 */
DECL|macro|PA_DIS_TO_RX1
mdefine_line|#define PA_DIS_TO_RX1&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Disable Timeout Timer RX1 */
DECL|macro|PA_RST_CLR
mdefine_line|#define PA_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Clear MAC Arbiter Reset */
DECL|macro|PA_RST_SET
mdefine_line|#define PA_RST_SET&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Set MAC Arbiter Reset */
DECL|macro|PA_ENA_TO_ALL
mdefine_line|#define PA_ENA_TO_ALL&t;(PA_ENA_TO_RX1 | PA_ENA_TO_RX2 |&bslash;&n;&t;&t;&t; PA_ENA_TO_TX1 | PA_ENA_TO_TX2)
multiline_comment|/* Rx/Tx Path related Arbiter Test Registers */
multiline_comment|/*&t;B3_MA_TO_TEST&t;16 bit&t;MAC Arbiter Timeout Test Reg */
multiline_comment|/*&t;B3_MA_RC_TEST&t;16 bit&t;MAC Arbiter Recovery Test Reg */
multiline_comment|/*&t;B3_PA_TEST&t;16 bit&t;Packet Arbiter Test Register */
multiline_comment|/*&t;&t;&t;Bit 15, 11, 7, and 3 are reserved in B3_PA_TEST */
DECL|macro|TX2_T_EV
mdefine_line|#define TX2_T_EV&t;(1&lt;&lt;15)&t;/* Bit 15: &t;TX2 Timeout/Recv Event occured*/
DECL|macro|TX2_T_ON
mdefine_line|#define TX2_T_ON&t;(1&lt;&lt;14)&t;/* Bit 14:&t;TX2 Timeout/Recv Timer Test On*/
DECL|macro|TX2_T_OFF
mdefine_line|#define TX2_T_OFF&t;(1&lt;&lt;13)&t;/* Bit 13:&t;TX2 Timeout/Recv Timer Tst Off*/
DECL|macro|TX2_T_STEP
mdefine_line|#define TX2_T_STEP&t;(1&lt;&lt;12)&t;/* Bit 12:&t;TX2 Timeout/Recv Timer Step */
DECL|macro|TX1_T_EV
mdefine_line|#define TX1_T_EV&t;(1&lt;&lt;11)&t;/* Bit 11:&t;TX1 Timeout/Recv Event occured*/
DECL|macro|TX1_T_ON
mdefine_line|#define TX1_T_ON&t;(1&lt;&lt;10)&t;/* Bit 10:&t;TX1 Timeout/Recv Timer Test On*/
DECL|macro|TX1_T_OFF
mdefine_line|#define TX1_T_OFF&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;TX1 Timeout/Recv Timer Tst Off*/
DECL|macro|TX1_T_STEP
mdefine_line|#define TX1_T_STEP&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;TX1 Timeout/Recv Timer Step */
DECL|macro|RX2_T_EV
mdefine_line|#define RX2_T_EV&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;RX2 Timeout/Recv Event occured*/
DECL|macro|RX2_T_ON
mdefine_line|#define RX2_T_ON&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;RX2 Timeout/Recv Timer Test On*/
DECL|macro|RX2_T_OFF
mdefine_line|#define RX2_T_OFF&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;RX2 Timeout/Recv Timer Tst Off*/
DECL|macro|RX2_T_STEP
mdefine_line|#define RX2_T_STEP&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;RX2 Timeout/Recv Timer Step */
DECL|macro|RX1_T_EV
mdefine_line|#define RX1_T_EV&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;RX1 Timeout/Recv Event occured*/
DECL|macro|RX1_T_ON
mdefine_line|#define RX1_T_ON&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;RX1 Timeout/Recv Timer Test On*/
DECL|macro|RX1_T_OFF
mdefine_line|#define RX1_T_OFF&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;RX1 Timeout/Recv Timer Tst Off*/
DECL|macro|RX1_T_STEP
mdefine_line|#define RX1_T_STEP&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;RX1 Timeout/Recv Timer Step */
multiline_comment|/* Transmit Arbiter Registers MAC 1 and 2, user MR_ADDR() to address */
multiline_comment|/*&t;TXA_ITI_INI&t;32 bit&t;Tx Arb Interval Timer Init Val */
multiline_comment|/*&t;TXA_ITI_VAL&t;32 bit&t;Tx Arb Interval Timer Value */
multiline_comment|/*&t;TXA_LIM_INI&t;32 bit&t;Tx Arb Limit Counter Init Val */
multiline_comment|/*&t;TXA_LIM_VAL&t;32 bit&t;Tx Arb Limit Counter Value */
multiline_comment|/* Bit 31..24:&t;reserved */
DECL|macro|TXA_MAX_VAL
mdefine_line|#define&t;TXA_MAX_VAL&t;0x00ffffffL&t;/* Bit 23.. 0:&t;Max TXA Timer/Cnt Val */
multiline_comment|/*&t;TXA_CTRL&t; 8 bit&t;Tx Arbiter Control Register */
DECL|macro|TXA_ENA_FSYNC
mdefine_line|#define TXA_ENA_FSYNC&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Enable force of sync tx queue */
DECL|macro|TXA_DIS_FSYNC
mdefine_line|#define TXA_DIS_FSYNC&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Disable force of sync tx queue*/
DECL|macro|TXA_ENA_ALLOC
mdefine_line|#define TXA_ENA_ALLOC&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Enable alloc of free bandwidth*/
DECL|macro|TXA_DIS_ALLOC
mdefine_line|#define TXA_DIS_ALLOC&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Disabl alloc of free bandwidth*/
DECL|macro|TXA_START_RC
mdefine_line|#define TXA_START_RC&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Start sync Rate Control */
DECL|macro|TXA_STOP_RC
mdefine_line|#define TXA_STOP_RC&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Stop sync Rate Control */
DECL|macro|TXA_ENA_ARB
mdefine_line|#define TXA_ENA_ARB&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Enable Tx Arbiter */
DECL|macro|TXA_DIS_ARB
mdefine_line|#define TXA_DIS_ARB&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Disable Tx Arbiter */
multiline_comment|/*&t;TXA_TEST&t; 8 bit&t;Tx Arbiter Test Register */
multiline_comment|/* Bit 7..6:&t;reserved */
DECL|macro|TXA_INT_T_ON
mdefine_line|#define TXA_INT_T_ON&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Tx Arb Interval Timer Test On */
DECL|macro|TXA_INT_T_OFF
mdefine_line|#define TXA_INT_T_OFF&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Tx Arb Interval Timer Test Off*/
DECL|macro|TXA_INT_T_STEP
mdefine_line|#define TXA_INT_T_STEP&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Tx Arb Interval Timer Step */
DECL|macro|TXA_LIM_T_ON
mdefine_line|#define TXA_LIM_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Tx Arb Limit Timer Test On */
DECL|macro|TXA_LIM_T_OFF
mdefine_line|#define TXA_LIM_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Tx Arb Limit Timer Test Off */
DECL|macro|TXA_LIM_T_STEP
mdefine_line|#define TXA_LIM_T_STEP&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Tx Arb Limit Timer Step */
multiline_comment|/*&t;TXA_STAT&t; 8 bit&t;Tx Arbiter Status Register */
multiline_comment|/* Bit 7..1:&t;reserved */
DECL|macro|TXA_PRIO_XS
mdefine_line|#define&t;TXA_PRIO_XS&t;(1&lt;&lt;0)&t;/* Bit 0:&t;sync queue has prio to send */
multiline_comment|/*&t;Q_BC&t;32 bit&t;Current Byte Counter */
multiline_comment|/* Bit 31..16:&t;reserved */
DECL|macro|BC_MAX
mdefine_line|#define BC_MAX&t;&t;0xffff&t;/* Bit 15.. 0:&t;Byte counter */
multiline_comment|/* BMU Control Status Registers */
multiline_comment|/*&t;B0_R1_CSR&t;32 bit&t;BMU Ctrl/Stat Rx Queue 1 */
multiline_comment|/*&t;B0_R2_CSR&t;32 bit&t;BMU Ctrl/Stat Rx Queue 2 */
multiline_comment|/*&t;B0_XA1_CSR&t;32 bit&t;BMU Ctrl/Stat Sync Tx Queue 1 */
multiline_comment|/*&t;B0_XS1_CSR&t;32 bit&t;BMU Ctrl/Stat Async Tx Queue 1 */
multiline_comment|/*&t;B0_XA2_CSR&t;32 bit&t;BMU Ctrl/Stat Sync Tx Queue 2 */
multiline_comment|/*&t;B0_XS2_CSR&t;32 bit&t;BMU Ctrl/Stat Async Tx Queue 2 */
multiline_comment|/*&t;Q_CSR&t;32 bit&t;BMU Control/Status Register */
multiline_comment|/* Bit 31..25:&t;reserved */
DECL|macro|CSR_SV_IDLE
mdefine_line|#define CSR_SV_IDLE&t;(1L&lt;&lt;24)&t;/* Bit 24: &t;BMU SM Idle */
multiline_comment|/* Bit 23..22:&t;reserved */
DECL|macro|CSR_DESC_CLR
mdefine_line|#define&t;CSR_DESC_CLR&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;Clear Reset for Descr */
DECL|macro|CSR_DESC_SET
mdefine_line|#define&t;CSR_DESC_SET&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;Set Reset for Descr */
DECL|macro|CSR_FIFO_CLR
mdefine_line|#define&t;CSR_FIFO_CLR&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Clear Reset for FIFO */
DECL|macro|CSR_FIFO_SET
mdefine_line|#define&t;CSR_FIFO_SET&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Set Reset for FIFO */
DECL|macro|CSR_HPI_RUN
mdefine_line|#define&t;CSR_HPI_RUN&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Release HPI SM */
DECL|macro|CSR_HPI_RST
mdefine_line|#define&t;CSR_HPI_RST&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;Reset HPI SM to Idle */
DECL|macro|CSR_SV_RUN
mdefine_line|#define&t;CSR_SV_RUN&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Release Supervisor SM */
DECL|macro|CSR_SV_RST
mdefine_line|#define&t;CSR_SV_RST&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Reset Supervisor SM */
DECL|macro|CSR_DREAD_RUN
mdefine_line|#define&t;CSR_DREAD_RUN&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Release Descr Read SM */
DECL|macro|CSR_DREAD_RST
mdefine_line|#define&t;CSR_DREAD_RST&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Reset Descr Read SM */
DECL|macro|CSR_DWRITE_RUN
mdefine_line|#define&t;CSR_DWRITE_RUN&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Rel. Descr Write SM */
DECL|macro|CSR_DWRITE_RST
mdefine_line|#define&t;CSR_DWRITE_RST&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Reset Descr Write SM */
DECL|macro|CSR_TRANS_RUN
mdefine_line|#define&t;CSR_TRANS_RUN&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Release Transfer SM */
DECL|macro|CSR_TRANS_RST
mdefine_line|#define&t;CSR_TRANS_RST&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Reset Transfer SM */
DECL|macro|CSR_ENA_POL
mdefine_line|#define CSR_ENA_POL&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Enable Descr Polling */
DECL|macro|CSR_DIS_POL
mdefine_line|#define CSR_DIS_POL&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Disable Descr Polling */
DECL|macro|CSR_STOP
mdefine_line|#define CSR_STOP&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Stop Rx/Tx Queue */
DECL|macro|CSR_START
mdefine_line|#define&t;CSR_START&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Start Rx/Tx Queue */
DECL|macro|CSR_IRQ_CL_P
mdefine_line|#define&t;CSR_IRQ_CL_P&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3: (Rx)&t;Clear Parity IRQ */
DECL|macro|CSR_IRQ_CL_B
mdefine_line|#define&t;CSR_IRQ_CL_B&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Clear EOB IRQ */
DECL|macro|CSR_IRQ_CL_F
mdefine_line|#define&t;CSR_IRQ_CL_F&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Clear EOF IRQ */
DECL|macro|CSR_IRQ_CL_C
mdefine_line|#define&t;CSR_IRQ_CL_C&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Clear ERR IRQ */
DECL|macro|CSR_SET_RESET
mdefine_line|#define CSR_SET_RESET&t;(CSR_DESC_SET|CSR_FIFO_SET|CSR_HPI_RST|CSR_SV_RST|&bslash;&n;&t;&t;&t;CSR_DREAD_RST|CSR_DWRITE_RST|CSR_TRANS_RST)
DECL|macro|CSR_CLR_RESET
mdefine_line|#define CSR_CLR_RESET&t;(CSR_DESC_CLR|CSR_FIFO_CLR|CSR_HPI_RUN|CSR_SV_RUN|&bslash;&n;&t;&t;&t;CSR_DREAD_RUN|CSR_DWRITE_RUN|CSR_TRANS_RUN)
multiline_comment|/*&t;Q_F&t;32 bit&t;Flag Register */
multiline_comment|/* Bit 28..31:&t;reserved */
DECL|macro|F_ALM_FULL
mdefine_line|#define F_ALM_FULL&t;(1L&lt;&lt;27) (Rx)&t;/* Bit 27: (Rx)&t;FIFO almost full */
DECL|macro|F_EMPTY
mdefine_line|#define F_EMPTY&t;&t;(1L&lt;&lt;27) (Tx)&t;/* Bit 27: (Tx)&t;FIFO empty flag */
DECL|macro|F_FIFO_EOF
mdefine_line|#define F_FIFO_EOF&t;(1L&lt;&lt;26)&t;/* Bit 26: &t;Fag bit in FIFO */
DECL|macro|F_WM_REACHED
mdefine_line|#define F_WM_REACHED&t;(1L&lt;&lt;25)&t;/* Bit 25: &t;Watermark reached */
multiline_comment|/* Bit 24:&t;reserved */
DECL|macro|F_FIFO_LEVEL
mdefine_line|#define F_FIFO_LEVEL&t;(0x1fL&lt;&lt;16)&t;/* Bit 23..16:&t;# of Qwords in FIFO */
multiline_comment|/* Bit 15..11: &t;reserved */
DECL|macro|F_WATER_MARK
mdefine_line|#define F_WATER_MARK&t;0x0007ffL&t;/* Bit 10.. 0:&t;Watermark */
multiline_comment|/*&t;Q_T1&t;32 bit&t;Test Register 1 */
multiline_comment|/*&t;&t;Holds four State Machine control Bytes */
DECL|macro|SM_CRTL_SV
mdefine_line|#define&t;SM_CRTL_SV&t;(0xffL&lt;&lt;24)&t;/* Bit 31..24:&t;Control Supervisor SM */
DECL|macro|SM_CRTL_RD
mdefine_line|#define&t;SM_CRTL_RD&t;(0xffL&lt;&lt;16)&t;/* Bit 23..16:&t;Control Read Desc SM */
DECL|macro|SM_CRTL_WR
mdefine_line|#define&t;SM_CRTL_WR&t;(0xffL&lt;&lt;8)&t;/* Bit 15.. 8:&t;Control Write Desc SM */
DECL|macro|SM_CRTL_TR
mdefine_line|#define&t;SM_CRTL_TR&t;(0xffL&lt;&lt;0)&t;/* Bit&t;7.. 0:&t;Control Transfer SM */
multiline_comment|/*&t;Q_T1_TR&t; 8 bit&t;Test Register 1 Transfer SM */
multiline_comment|/*&t;Q_T1_WR&t; 8 bit&t;Test Register 1 Write Descriptor SM */
multiline_comment|/*&t;Q_T1_RD&t; 8 bit&t;Test Register 1 Read Descriptor SM */
multiline_comment|/*&t;Q_T1_SV&t; 8 bit&t;Test Register 1 Supervisor SM */
multiline_comment|/* The control status byte of each machine looks like ... */
DECL|macro|SM_STATE
mdefine_line|#define&t;SM_STATE&t;0xf0&t;/* Bit 7..4:&t;State which shall be loaded */
DECL|macro|SM_LOAD
mdefine_line|#define&t;SM_LOAD&t;&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Load the SM with SM_STATE */
DECL|macro|SM_TEST_ON
mdefine_line|#define&t;SM_TEST_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Switch on SM Test Mode */
DECL|macro|SM_TEST_OFF
mdefine_line|#define&t;SM_TEST_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Go off the Test Mode */
DECL|macro|SM_STEP
mdefine_line|#define&t;SM_STEP&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Step the State Machine */
multiline_comment|/* The encoding of the states is not supported by the Diagnostics Tool */
multiline_comment|/*&t;Q_T2&t;32 bit&t;Test Register 2&t;*/
multiline_comment|/* Bit 31..8:&t;reserved */
DECL|macro|T2_AC_T_ON
mdefine_line|#define&t;T2_AC_T_ON&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Address Counter Test Mode on */
DECL|macro|T2_AC_T_OFF
mdefine_line|#define&t;T2_AC_T_OFF&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Address Counter Test Mode off*/
DECL|macro|T2_BC_T_ON
mdefine_line|#define&t;T2_BC_T_ON&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Byte Counter Test Mode on */
DECL|macro|T2_BC_T_OFF
mdefine_line|#define&t;T2_BC_T_OFF&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Byte Counter Test Mode off */
DECL|macro|T2_STEP04
mdefine_line|#define&t;T2_STEP04&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Inc AC/Dec BC by 4 */
DECL|macro|T2_STEP03
mdefine_line|#define&t;T2_STEP03&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Inc AC/Dec BC by 3 */
DECL|macro|T2_STEP02
mdefine_line|#define&t;T2_STEP02&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Inc AC/Dec BC by 2 */
DECL|macro|T2_STEP01
mdefine_line|#define&t;T2_STEP01&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Inc AC/Dec BC by 1 */
multiline_comment|/*&t;Q_T3&t;32 bit&t;Test Register 3&t;*/
multiline_comment|/* Bit 31..7:&t;reserved */
DECL|macro|T3_MUX
mdefine_line|#define&t;T3_MUX&t;&t;(7&lt;&lt;4)&t;/* Bit 6.. 4:&t;Mux Position */
multiline_comment|/* Bit 3:&t;reserved */
DECL|macro|T3_VRAM
mdefine_line|#define&t;T3_VRAM&t;&t;(7&lt;&lt;0)&t;/* Bit 2.. 0:&t;Virtual RAM Buffer Address */
multiline_comment|/* RAM Buffer Register Offsets */
multiline_comment|/* use RB_ADDR(Queue,Offs) to address */
multiline_comment|/*&t;RB_START&t;32 bit&t;RAM Buffer Start Address */
multiline_comment|/*&t;RB_END&t;&t;32 bit&t;RAM Buffer End Address */
multiline_comment|/*&t;RB_WP&t;&t;32 bit&t;RAM Buffer Write Pointer */
multiline_comment|/*&t;RB_RP&t;&t;32 bit&t;RAM Buffer Read Pointer */
multiline_comment|/*&t;RB_RX_UTPP&t;32 bit&t;Rx Upper Threshold, Pause Pack */
multiline_comment|/*&t;RB_RX_LTPP&t;32 bit&t;Rx Lower Threshold, Pasue Pack */
multiline_comment|/*&t;RB_RX_UTHP&t;32 bit&t;Rx Upper Threshold, High Prio */
multiline_comment|/*&t;RB_RX_LTHP&t;32 bit&t;Rx Lower Threshold, High Prio */
multiline_comment|/*&t;RB_PC&t;&t;32 bit&t;RAM Buffer Packet Counter */
multiline_comment|/*&t;RB_LEV&t;&t;32 bit&t;RAM Buffer Level Register */
multiline_comment|/* Bit 31..19:&t;reserved */
DECL|macro|RB_MSK
mdefine_line|#define RB_MSK&t;0x0007ffff&t;/* Bit 18.. 0:&t;RAM Buffer Pointer Bits */
multiline_comment|/*&t;RB_TST2&t;&t;8 bit&t;RAM Buffer Test Register 2 */
multiline_comment|/* Bit 4..7:&t;reserved */
DECL|macro|RB_PC_DEC
mdefine_line|#define&t;RB_PC_DEC&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Packet Counter Decrem */
DECL|macro|RB_PC_T_ON
mdefine_line|#define RB_PC_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Packet Counter Test On */
DECL|macro|RB_PC_T_OFF
mdefine_line|#define RB_PC_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Packet Counter Tst Off */
DECL|macro|RB_PC_INC
mdefine_line|#define RB_PC_INC&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Packet Counter Increm */
multiline_comment|/*&t;RB_TST1&t;&t;8 bit&t;RAM Buffer Test Register 1 */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|RB_WP_T_ON
mdefine_line|#define RB_WP_T_ON&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Write Pointer Test On */
DECL|macro|RB_WP_T_OFF
mdefine_line|#define RB_WP_T_OFF&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Write Pointer Test Off */
DECL|macro|RB_WP_INC
mdefine_line|#define RB_WP_INC&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Write Pointer Increm */
multiline_comment|/* Bit 3:&t;reserved */
DECL|macro|RB_RP_T_ON
mdefine_line|#define RB_RP_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Read Pointer Test On */
DECL|macro|RB_RP_T_OFF
mdefine_line|#define RB_RP_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Read Pointer Test Off */
DECL|macro|RB_RP_DEC
mdefine_line|#define RB_RP_DEC&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Read Pointer Decrement */
multiline_comment|/*&t;RB_CTRL&t;&t;8 bit&t;RAM Buffer Control Register */
multiline_comment|/* Bit&t;7..6:&t;reserved */
DECL|macro|RB_ENA_STFWD
mdefine_line|#define RB_ENA_STFWD&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Enable Store &amp; Forward */
DECL|macro|RB_DIS_STFWD
mdefine_line|#define RB_DIS_STFWD&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Disab. Store &amp; Forward */
DECL|macro|RB_ENA_OP_MD
mdefine_line|#define RB_ENA_OP_MD&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Enable Operation Mode */
DECL|macro|RB_DIS_OP_MD
mdefine_line|#define RB_DIS_OP_MD&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Disab. Operation Mode */
DECL|macro|RB_RST_CLR
mdefine_line|#define RB_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Clr RAM Buf STM Reset */
DECL|macro|RB_RST_SET
mdefine_line|#define RB_RST_SET&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Set RAM Buf STM Reset */
multiline_comment|/* Receive and Transmit MAC FIFO Registers, use MR_ADDR() to address */
multiline_comment|/*&t;RX_MFF_EA&t;32 bit&t;Receive MAC FIFO End Address */
multiline_comment|/*&t;RX_MFF_WP&t;32 bit &t;Receive MAC FIFO Write Pointer */
multiline_comment|/*&t;RX_MFF_RP&t;32 bit&t;Receive MAC FIFO Read Pointer */
multiline_comment|/*&t;RX_MFF_PC&t;32 bit&t;Receive MAC FIFO Packet Counter*/
multiline_comment|/*&t;RX_MFF_LEV&t;32 bit&t;Receive MAC FIFO Level */
multiline_comment|/*&t;TX_MFF_EA&t;32 bit&t;Transmit MAC FIFO End Address */
multiline_comment|/*&t;TX_MFF_WP&t;32 bit &t;Transmit MAC FIFO Write Pointer*/
multiline_comment|/*&t;TX_MFF_WSP&t;32 bit&t;Transmit MAC FIFO WR Shadow Pt*/
multiline_comment|/*&t;TX_MFF_RP&t;32 bit&t;Transmit MAC FIFO Read Pointer */
multiline_comment|/*&t;TX_MFF_PC&t;32 bit&t;Transmit MAC FIFO Packet Cnt */
multiline_comment|/*&t;TX_MFF_LEV&t;32 bit&t;Transmit MAC FIFO Level */
multiline_comment|/* Bit 31..6:&t;reserved */
DECL|macro|MFF_MSK
mdefine_line|#define MFF_MSK&t;&t;0x007fL&t;/* Bit&t;5..0:&t;MAC FIFO Address/Pointer Bits */
multiline_comment|/*&t;RX_MFF_CTRL1&t;16 bit&t;Receive MAC FIFO Control Reg 1 */
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|MFF_ENA_RDY_PAT
mdefine_line|#define MFF_ENA_RDY_PAT&t;(1&lt;&lt;13)&t;&t;/* Bit 13:&t;Enable Ready Patch */
DECL|macro|MFF_DIS_RDY_PAT
mdefine_line|#define MFF_DIS_RDY_PAT&t;(1&lt;&lt;12)&t;&t;/* Bit 12:&t;Disable Ready Patch */
DECL|macro|MFF_ENA_TIM_PAT
mdefine_line|#define MFF_ENA_TIM_PAT&t;(1&lt;&lt;11)&t;&t;/* Bit 11:&t;Enable Timing Patch */
DECL|macro|MFF_DIS_TIM_PAT
mdefine_line|#define MFF_DIS_TIM_PAT&t;(1&lt;&lt;10)&t;&t;/* Bit 10:&t;Disable Timing Patch */
DECL|macro|MFF_ENA_ALM_FUL
mdefine_line|#define MFF_ENA_ALM_FUL&t;(1&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Enable AlmostFull Sign*/
DECL|macro|MFF_DIS_ALM_FUL
mdefine_line|#define MFF_DIS_ALM_FUL&t;(1&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Disab. AlmostFull Sign*/
DECL|macro|MFF_ENA_PAUSE
mdefine_line|#define MFF_ENA_PAUSE&t;(1&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Enable Pause Signaling*/
DECL|macro|MFF_DIS_PAUSE
mdefine_line|#define MFF_DIS_PAUSE&t;(1&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Disab. Pause Signaling*/
DECL|macro|MFF_ENA_FLUSH
mdefine_line|#define MFF_ENA_FLUSH&t;(1&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Enable Frame Flushing */
DECL|macro|MFF_DIS_FLUSH
mdefine_line|#define MFF_DIS_FLUSH&t;(1&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Disab. Frame Flushing */
DECL|macro|MFF_ENA_TIST
mdefine_line|#define MFF_ENA_TIST&t;(1&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Enable Timestamp Gener*/
DECL|macro|MFF_DIS_TIST
mdefine_line|#define MFF_DIS_TIST&t;(1&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Disab. Timestamp Gener*/
DECL|macro|MFF_CLR_INTIST
mdefine_line|#define MFF_CLR_INTIST&t;(1&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Clear IRQ No Timestamp*/
DECL|macro|MFF_CLR_INSTAT
mdefine_line|#define MFF_CLR_INSTAT&t;(1&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Clear IRQ No Status */
DECL|macro|MFF_RX_CTRL_DEF
mdefine_line|#define MFF_RX_CTRL_DEF MFF_ENA_TIM_PAT
multiline_comment|/*&t;TX_MFF_CTRL1&t;16 bit&t;Transmit MAC FIFO Control Reg 1 */
DECL|macro|MFF_CLR_PERR
mdefine_line|#define MFF_CLR_PERR&t;(1&lt;&lt;15)&t;&t;/* Bit 15:&t;Clear Parity Error IRQ*/
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|MFF_ENA_PKT_REC
mdefine_line|#define MFF_ENA_PKT_REC&t;(1&lt;&lt;13)&t;&t;/* Bit 13:&t;Enable Packet Recovery*/
DECL|macro|MFF_DIS_PKT_REC
mdefine_line|#define MFF_DIS_PKT_REC (1&lt;&lt;12)&t;&t;/* Bit 12:&t;Disable Packet Recov. */
multiline_comment|/*&t;MFF_ENA_TIM_PAT&t; (see RX_MFF_CTRL1)Bit 11:&t;Enable Timing Patch */
multiline_comment|/*&t;MFF_DIS_TIM_PAT&t; (see RX_MFF_CTRL1)Bit 10:&t;Disable Timing Patch */
multiline_comment|/*&t;MFF_ENA_ALM_FUL&t; (see RX_MFF_CTRL1)Bit&t;9:&t;Enable AlmostFull Sign*/
multiline_comment|/*&t;MFF_DIS_ALM_FUL&t; (see RX_MFF_CTRL1)Bit&t;8:&t;Disab. AlmostFull Sign*/
DECL|macro|MFF_ENA_W4E
mdefine_line|#define&t;MFF_ENA_W4E&t;(1&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Enable Wait for Empty */
DECL|macro|MFF_DIS_W4E
mdefine_line|#define MFF_DIS_W4E&t;(1&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Disab. Wait for Empty */
multiline_comment|/*&t;MFF_ENA_FLUSH&t; (see RX_MFF_CTRL1)Bit&t;5:&t;Enable Frame Flushing */
multiline_comment|/*&t;MFF_DIS_FLUSH&t; (see RX_MFF_CTRL1)Bit&t;4:&t;Disab. Frame Flushing */
DECL|macro|MFF_ENA_LOOPB
mdefine_line|#define MFF_ENA_LOOPB&t;(1&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Enable Loopback */
DECL|macro|MFF_DIS_LOOPB
mdefine_line|#define MFF_DIS_LOOPB&t;(1&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Disable Loopback */
DECL|macro|MFF_CLR_MAC_RST
mdefine_line|#define MFF_CLR_MAC_RST&t;(1&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Clear XMAC Reset */
DECL|macro|MFF_SET_MAC_RST
mdefine_line|#define MFF_SET_MAC_RST&t;(1&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Set XMAC Reset */
DECL|macro|MFF_TX_CTRL_DEF
mdefine_line|#define MFF_TX_CTRL_DEF&t;(MFF_ENA_PKT_REC | MFF_ENA_TIM_PAT | MFF_ENA_FLUSH)
multiline_comment|/*&t;RX_MFF_TST2&t; 8 bit&t;Receive MAC FIFO Test Register 2 */
multiline_comment|/*&t;TX_MFF_TST2&t; 8 bit&t;Transmit MAC FIFO Test Register 2 */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|MFF_WSP_T_ON
mdefine_line|#define MFF_WSP_T_ON&t;(1&lt;&lt;6)&t;/* Bit 6: (Tx)&t;Write Shadow Pt TestOn */
DECL|macro|MFF_WSP_T_OFF
mdefine_line|#define MFF_WSP_T_OFF&t;(1&lt;&lt;5)&t;/* Bit 5: (Tx)&t;Write Shadow Pt TstOff */
DECL|macro|MFF_WSP_INC
mdefine_line|#define MFF_WSP_INC&t;(1&lt;&lt;4)&t;/* Bit 4: (Tx)&t;Write Shadow Pt Increm */
DECL|macro|MFF_PC_DEC
mdefine_line|#define&t;MFF_PC_DEC&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Packet Counter Decrem  */
DECL|macro|MFF_PC_T_ON
mdefine_line|#define MFF_PC_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Packet Counter Test On */
DECL|macro|MFF_PC_T_OFF
mdefine_line|#define MFF_PC_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Packet Counter Tst Off */
DECL|macro|MFF_PC_INC
mdefine_line|#define MFF_PC_INC&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Packet Counter Increm  */
multiline_comment|/*&t;RX_MFF_TST1&t; 8 bit&t;Receive MAC FIFO Test Register 1 */
multiline_comment|/*&t;TX_MFF_TST1&t; 8 bit&t;Transmit MAC FIFO Test Register 1 */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|MFF_WP_T_ON
mdefine_line|#define MFF_WP_T_ON&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Write Pointer Test On */
DECL|macro|MFF_WP_T_OFF
mdefine_line|#define MFF_WP_T_OFF&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Write Pointer Test Off */
DECL|macro|MFF_WP_INC
mdefine_line|#define MFF_WP_INC&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Write Pointer Increm */
multiline_comment|/* Bit 3:&t;reserved */
DECL|macro|MFF_RP_T_ON
mdefine_line|#define MFF_RP_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Read Pointer Test On */
DECL|macro|MFF_RP_T_OFF
mdefine_line|#define MFF_RP_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Read Pointer Test Off */
DECL|macro|MFF_RP_DEC
mdefine_line|#define MFF_RP_DEC&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Read Pointer Decrement */
multiline_comment|/*&t;RX_MFF_CTRL2&t; 8 bit&t;Receive MAC FIFO Control Reg 2 */
multiline_comment|/*&t;TX_MFF_CTRL2&t; 8 bit&t;Transmit MAC FIFO Control Reg 2 */
multiline_comment|/* Bit 7..4:&t;reserved */
DECL|macro|MFF_ENA_OP_MD
mdefine_line|#define MFF_ENA_OP_MD&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Enable Operation Mode */
DECL|macro|MFF_DIS_OP_MD
mdefine_line|#define MFF_DIS_OP_MD&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Disab. Operation Mode */
DECL|macro|MFF_RST_CLR
mdefine_line|#define MFF_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Clear MAC FIFO Reset */
DECL|macro|MFF_RST_SET
mdefine_line|#define MFF_RST_SET&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Set MAC FIFO Reset */
multiline_comment|/* Receive, Transmit, and Link LED Counter Registers */
multiline_comment|/*&t;RX_LED_CTRL&t; 8 bit&t;Receive LED Cnt Control Reg */
multiline_comment|/*&t;TX_LED_CTRL&t; 8 bit&t;Transmit LED Cnt Control Reg */
multiline_comment|/*&t;LNK_SYNC_CTRL&t; 8 bit&t;Link Sync Cnt Control Register */
multiline_comment|/* Bit 7..3:&t;reserved */
DECL|macro|LED_START
mdefine_line|#define LED_START&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Start Timer */
DECL|macro|LED_STOP
mdefine_line|#define LED_STOP&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Stop Timer */
DECL|macro|LED_STATE
mdefine_line|#define LED_STATE&t;(1&lt;&lt;0)&t;/* Bit 0:(Rx/Tx)LED State, 1=LED on */
DECL|macro|LED_CLR_IRQ
mdefine_line|#define LED_CLR_IRQ&t;(1&lt;&lt;0)&t;/* Bit 0:(Lnk) &t;Clear Link IRQ */
multiline_comment|/*&t;RX_LED_TST&t; 8 bit&t;Receive LED Cnt Test Register */
multiline_comment|/*&t;TX_LED_TST&t; 8 bit&t;Transmit LED Cnt Test Register */
multiline_comment|/*&t;LNK_SYNC_TST&t; 8 bit&t;Link Sync Cnt Test Register */
multiline_comment|/* Bit 7..3:&t;reserved */
DECL|macro|LED_T_ON
mdefine_line|#define LED_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2:&t;LED Counter Testmode On */
DECL|macro|LED_T_OFF
mdefine_line|#define LED_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1:&t;LED Counter Testmode Off */
DECL|macro|LED_T_STEP
mdefine_line|#define LED_T_STEP&t;(1&lt;&lt;0)&t;/* Bit 0:&t;LED Counter Step */
multiline_comment|/*&t;LNK_LED_REG&t; 8 bit&t;Link LED Register */
multiline_comment|/* Bit 7..6:&t;reserved */
DECL|macro|LED_BLK_ON
mdefine_line|#define LED_BLK_ON&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Link LED Blinking On */
DECL|macro|LED_BLK_OFF
mdefine_line|#define LED_BLK_OFF&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Link LED Blinking Off */
DECL|macro|LED_SYNC_ON
mdefine_line|#define LED_SYNC_ON&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Use Sync Wire to switch LED */
DECL|macro|LED_SYNC_OFF
mdefine_line|#define LED_SYNC_OFF&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Disable Sync Wire Input */
DECL|macro|LED_ON
mdefine_line|#define LED_ON&t;&t;(1&lt;&lt;1)&t;/* Bit 1:&t;switch LED on */
DECL|macro|LED_OFF
mdefine_line|#define LED_OFF&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;switch LED off */
multiline_comment|/* Receive and Transmit Descriptors ******************************************/
multiline_comment|/* Transmit Descriptor struct */
DECL|struct|s_HwTxd
r_typedef
r_struct
id|s_HwTxd
(brace
DECL|member|TxCtrl
id|SK_U32
r_volatile
id|TxCtrl
suffix:semicolon
multiline_comment|/* Transmit Buffer Control Field */
DECL|member|TxNext
id|SK_U32
id|TxNext
suffix:semicolon
multiline_comment|/* Physical Address Pointer to the next TxD */
DECL|member|TxAdrLo
id|SK_U32
id|TxAdrLo
suffix:semicolon
multiline_comment|/* Physical Tx Buffer Address lower dword */
DECL|member|TxAdrHi
id|SK_U32
id|TxAdrHi
suffix:semicolon
multiline_comment|/* Physical Tx Buffer Address upper dword */
DECL|member|TxStat
id|SK_U32
id|TxStat
suffix:semicolon
multiline_comment|/* Transmit Frame Status Word */
macro_line|#ifndef&t;SK_USE_REV_DESC
DECL|member|TxTcpOffs
id|SK_U16
id|TxTcpOffs
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Value */
DECL|member|TxRes1
id|SK_U16
id|TxRes1
suffix:semicolon
multiline_comment|/* 16 bit reserved field */
DECL|member|TxTcpWp
id|SK_U16
id|TxTcpWp
suffix:semicolon
multiline_comment|/* TCP Checksum Write Position */
DECL|member|TxTcpSp
id|SK_U16
id|TxTcpSp
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Position */
macro_line|#else&t;/* SK_USE_REV_DESC */
DECL|member|TxRes1
id|SK_U16
id|TxRes1
suffix:semicolon
multiline_comment|/* 16 bit reserved field */
DECL|member|TxTcpOffs
id|SK_U16
id|TxTcpOffs
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Value */
DECL|member|TxTcpSp
id|SK_U16
id|TxTcpSp
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Position */
DECL|member|TxTcpWp
id|SK_U16
id|TxTcpWp
suffix:semicolon
multiline_comment|/* TCP Checksum Write Position */
macro_line|#endif&t;/* SK_USE_REV_DESC */
DECL|member|TxRes2
id|SK_U32
id|TxRes2
suffix:semicolon
multiline_comment|/* 32 bit reserved field */
DECL|typedef|SK_HWTXD
)brace
id|SK_HWTXD
suffix:semicolon
multiline_comment|/* Receive Descriptor struct */
DECL|struct|s_HwRxd
r_typedef
r_struct
id|s_HwRxd
(brace
DECL|member|RxCtrl
id|SK_U32
r_volatile
id|RxCtrl
suffix:semicolon
multiline_comment|/* Receive Buffer Control Field */
DECL|member|RxNext
id|SK_U32
id|RxNext
suffix:semicolon
multiline_comment|/* Physical Address Pointer to the next TxD */
DECL|member|RxAdrLo
id|SK_U32
id|RxAdrLo
suffix:semicolon
multiline_comment|/* Physical Receive Buffer Address lower dword*/
DECL|member|RxAdrHi
id|SK_U32
id|RxAdrHi
suffix:semicolon
multiline_comment|/* Physical Receive Buffer Address upper dword*/
DECL|member|RxStat
id|SK_U32
id|RxStat
suffix:semicolon
multiline_comment|/* Receive Frame Status Word */
DECL|member|RxTiSt
id|SK_U32
id|RxTiSt
suffix:semicolon
multiline_comment|/* Receive Timestamp provided by the XMAC */
macro_line|#ifndef&t;SK_USE_REV_DESC&t;
DECL|member|RxTcpSum1
id|SK_U16
id|RxTcpSum1
suffix:semicolon
multiline_comment|/* TCP Checksum 1 */
DECL|member|RxTcpSum2
id|SK_U16
id|RxTcpSum2
suffix:semicolon
multiline_comment|/* TCP Checksum 2 */
DECL|member|RxTcpSp1
id|SK_U16
id|RxTcpSp1
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Position 1 */
DECL|member|RxTcpSp2
id|SK_U16
id|RxTcpSp2
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Position 2 */
macro_line|#else&t;/* SK_USE_REV_DESC */
DECL|member|RxTcpSum2
id|SK_U16
id|RxTcpSum2
suffix:semicolon
multiline_comment|/* TCP Checksum 2 */
DECL|member|RxTcpSum1
id|SK_U16
id|RxTcpSum1
suffix:semicolon
multiline_comment|/* TCP Checksum 1 */
DECL|member|RxTcpSp2
id|SK_U16
id|RxTcpSp2
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Position 2 */
DECL|member|RxTcpSp1
id|SK_U16
id|RxTcpSp1
suffix:semicolon
multiline_comment|/* TCP Checksum Calculation Start Position 1 */
macro_line|#endif&t;/* SK_USE_REV_DESC */
DECL|typedef|SK_HWRXD
)brace
id|SK_HWRXD
suffix:semicolon
multiline_comment|/*&n; * Drivers which use the reverse descriptor feature (PCI_OUR_REG_2)&n; * should set the define SK_USE_REV_DESC.&n; * Structures are &squot;normaly&squot; not endianess dependent. But in &n; * this case the SK_U16 fields are bound to bit positions inside the&n; * descriptor. RxTcpSum1 e.g. must start at bit 0 within the 6.th DWord.&n; * The bit positions inside a DWord are of course endianess dependent and&n; * swaps if the DWord is swaped by the hardware.&n; */
multiline_comment|/* Descriptor Bit Definition */
multiline_comment|/*&t;TxCtrl&t;&t;Transmit Buffer Control Field */
multiline_comment|/*&t;RxCtrl&t;&t;Receive Buffer Control Field */
DECL|macro|BMU_OWN
mdefine_line|#define&t;BMU_OWN&t;&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;OWN bit: 0=host/1=BMU */
DECL|macro|BMU_STF
mdefine_line|#define&t;BMU_STF&t;&t;(1L&lt;&lt;30)&t;/* Bit 30:&t;Start of Frame ? */
DECL|macro|BMU_EOF
mdefine_line|#define&t;BMU_EOF&t;&t;(1L&lt;&lt;29)&t;/* Bit 29:&t;End of Frame ?&t;*/
DECL|macro|BMU_IRQ_EOB
mdefine_line|#define&t;BMU_IRQ_EOB&t;(1L&lt;&lt;28)&t;/* Bit 28:&t;Req &quot;End of Buff&quot; IRQ */
DECL|macro|BMU_IRQ_EOF
mdefine_line|#define&t;BMU_IRQ_EOF&t;(1L&lt;&lt;27)&t;/* Bit 27:&t;Req &quot;End of Frame&quot; IRQ*/
multiline_comment|/* TxCtrl specific bits */
DECL|macro|BMU_STFWD
mdefine_line|#define BMU_STFWD&t;(1L&lt;&lt;26)&t;/* Bit 26: (Tx)&t;Store&amp;Forward Frame */
DECL|macro|BMU_NO_FCS
mdefine_line|#define BMU_NO_FCS&t;(1L&lt;&lt;25)&t;/* Bit 25: (Tx) disable XMAC FCS gener*/
DECL|macro|BMU_SW
mdefine_line|#define BMU_SW&t;&t;(1L&lt;&lt;24)&t;/* Bit 24: (Tx)&t;1 bit res. for SW use */
multiline_comment|/* RxCtrl specific bits */
DECL|macro|BMU_DEV_0
mdefine_line|#define&t;BMU_DEV_0&t;(1L&lt;&lt;26)&t;/* Bit 26: (Rx)&t;transfer data to Dev0 */
DECL|macro|BMU_STAT_VAL
mdefine_line|#define BMU_STAT_VAL&t;(1L&lt;&lt;25)&t;/* Bit 25: (Rx)&t;RxStat Valid */
DECL|macro|BMU_TIST_VAL
mdefine_line|#define BMU_TIST_VAL&t;(1L&lt;&lt;24)&t;/* Bit 24: (Rx)&t;RxTiSt Valid */
multiline_comment|/* Bit 23..16:&t;BMU Check Opcodes */
DECL|macro|BMU_CHECK
mdefine_line|#define&t;BMU_CHECK&t;0x00550000L&t;/* &t;&t;Default BMU check */
DECL|macro|BMU_TCP_CHECK
mdefine_line|#define&t;BMU_TCP_CHECK&t;0x00560000L&t;/* &t;&t;Descr with TCP ext */
DECL|macro|BMU_BBC
mdefine_line|#define&t;BMU_BBC&t;&t;0x0000FFFFL&t;/* Bit 15..0:&t;Buffer Byte Counter */
multiline_comment|/*&t;TxStat&t;&t;Transmit Frame Status Word */
multiline_comment|/*&t;RxStat&t;&t;Receive Frame Status Word */
multiline_comment|/*&n; *Note: TxStat is reserved for ASIC loopback mode only&n; *&n; *&t;The Bits of the Status words are defined in xmac_ii.h&n; *&t;(see XMR_FS bits)&n; */
multiline_comment|/* other defines *************************************************************/
multiline_comment|/*&n; * FlashProm specification&n; */
DECL|macro|MAX_PAGES
mdefine_line|#define&t;MAX_PAGES&t;0x20000L&t;/* Every byte has a single page */
DECL|macro|MAX_FADDR
mdefine_line|#define&t;MAX_FADDR&t;1&t;&t;/* 1 byte per page */
DECL|macro|SKFDDI_PSZ
mdefine_line|#define&t;SKFDDI_PSZ&t;8&t;&t;/* address PROM size */
multiline_comment|/* macros ********************************************************************/
multiline_comment|/*&n; * Receive and Transmit Queues&n; */
DECL|macro|Q_R1
mdefine_line|#define Q_R1&t;0x0000&t;&t;/* Receive Queue 1 */
DECL|macro|Q_R2
mdefine_line|#define Q_R2&t;0x0080&t;&t;/* Receive Queue 2 */
DECL|macro|Q_XS1
mdefine_line|#define Q_XS1&t;0x0200&t;&t;/* Synchronous Transmit Queue 1 */
DECL|macro|Q_XA1
mdefine_line|#define Q_XA1&t;0x0280&t;&t;/* Asynchronous Transmit Queue 1 */
DECL|macro|Q_XS2
mdefine_line|#define Q_XS2&t;0x0300&t;&t;/* Synchronous Transmit Queue 2 */
DECL|macro|Q_XA2
mdefine_line|#define Q_XA2&t;0x0380&t;&t;/* Asynchronous Transmit Queue 2 */
multiline_comment|/*&n; *&t;Macro Q_ADDR()&n; *&n; *&t;Use this macro to address the Receive and Transmit Queue Registers.&n; *&n; * para&t;Queue&t;Queue to address.&n; *&t;&t;&t;Values: Q_R1, Q_R2, Q_XS1, Q_XA1, Q_XS2, and Q_XA2&n; *&t;Offs&t;Queue register offset.&n; *&t;&t;&t;Values: Q_D, Q_DA_L ... Q_T2, Q_T3&n; *&n; * usage&t;SK_IN32(pAC,Q_ADDR(Q_R2,Q_BC),pVal)&n; */
DECL|macro|Q_ADDR
mdefine_line|#define Q_ADDR(Queue,Offs)&t;(B8_Q_REGS + (Queue) + (Offs))
multiline_comment|/*&n; *&t;Macro RB_ADDR()&n; *&n; *&t;Use this macro to address the RAM Buffer Registers.&n; *&n; * para&t;Queue&t;Queue to address.&n; *&t;&t;&t;Values: Q_R1, Q_R2, Q_XS1, Q_XA1, Q_XS2, and Q_XA2&n; *&t;Offs&t;Queue register offset.&n; *&t;&t;&t;Values: RB_START, RB_END ... RB_LEV, RB_CTRL&n; *&n; * usage&t;SK_IN32(pAC,RB_ADDR(Q_R2,RB_RP),pVal)&n; */
DECL|macro|RB_ADDR
mdefine_line|#define RB_ADDR(Queue,Offs)&t;(B16_RAM_REGS + (Queue) + (Offs))
multiline_comment|/*&n; * MAC Related Registers&n; */
DECL|macro|MAC_1
mdefine_line|#define&t;MAC_1&t;&t;0&t;/* belongs to the port near the slot */
DECL|macro|MAC_2
mdefine_line|#define MAC_2&t;&t;1&t;/* belongs to the port far away from the slot */
multiline_comment|/*&n; *&t;Macro MR_ADDR()&n; *&n; *&t;Use this macro to address a MAC Related Registers in side the ASIC.&n; *&n; * para&t;Queue&t;Queue to address.&n; *&t;&t;&t;Values:&t;TXA_ITI_INI&t;...&t;TXA_TEST,&n; *&t;&t;&t;&t;RX_MFF_EA&t;...&t;RX_LED_TST,&n; *&t;&t;&t;&t;LNK_SYNC_INI&t;...&t;LNK_LED_REG, and&n; *&t;&t;&t;&t;TX_MFF_EA&t;...&t;TX_LED_TST&n; *&t;Mac&t;MAC to address.&n; *&t;&t;&t;Values: MAC_1, MAC_2&n; *&n; * usage&t;SK_IN32(pAC,MR_ADDR(MAC_1,TX_MFF_EA),pVal)&n; */
DECL|macro|MR_ADDR
mdefine_line|#define MR_ADDR(Mac,Offs)&t;(((Mac) &lt;&lt; 7) + (Offs))
multiline_comment|/*&n; * macros to access the XMAC&n; *&n; * XM_IN16(),&t;&t;to read a 16 bit register (e.g. XM_MMU_CMD)&n; * XM_OUT16(),&t;&t;to write a 16 bit register (e.g. XM_MMU_CMD)&n; * XM_IN32(),&t;&t;to read a 32 bit register (e.g. XM_TX_EV_CNT)&n; * XM_OUT32(),&t;&t;to write a 32 bit register (e.g. XM_TX_EV_CNT)&n; * XM_INADDR(),&t;&t;to read a network address register (e.g. XM_SRC_CHK)&n; * XM_OUTADDR(),&t;to write a network address register (e.g. XM_SRC_CHK)&n; * XM_INHASH(),&t;&t;to read the XM_HSM_CHK register&n; * XM_OUTHASH()&t;&t;to write the XM_HSM_CHK register&n; *&n; * para:&t;Mac&t;XMAC to address&t;&t;values: MAC_1 or MAC_2&n; *&t;&t;IoC&t;I/O context needed for SK IO macros&n; *&t;&t;Reg&t;XMAC Register to read or write&n; *&t;&t;(p)Val&t;Value or pointer to the value which should be read or&n; *&t;&t;&t;written.&n; *&n; * usage:&t;XM_OUT16(IoC, MAC_1, XM_MMU_CMD, Value) ;&n; */
macro_line|#ifdef&t;SK_LITTLE_ENDIAN
DECL|macro|XM_WORD_LO
mdefine_line|#define&t;XM_WORD_LO&t;0
DECL|macro|XM_WORD_HI
mdefine_line|#define XM_WORD_HI&t;1
macro_line|#else&t;/* !SK_LITTLE_ENDIAN */
DECL|macro|XM_WORD_LO
mdefine_line|#define&t;XM_WORD_LO&t;1
DECL|macro|XM_WORD_HI
mdefine_line|#define XM_WORD_HI&t;0
macro_line|#endif&t;/* !SK_LITTLE_ENDIAN */
DECL|macro|XMA
mdefine_line|#define&t;XMA(Mac,Reg)&t;(((0x1000 &lt;&lt; (Mac)) + 0x1000) | ((Reg) &lt;&lt; 1))
DECL|macro|XM_IN16
mdefine_line|#define XM_IN16(IoC,Mac,Reg,pVal)&t;SK_IN16((IoC),XMA((Mac),(Reg)),(pVal))
DECL|macro|XM_OUT16
mdefine_line|#define XM_OUT16(IoC,Mac,Reg,Val)&t;SK_OUT16((IoC),XMA((Mac),(Reg)),(Val))
DECL|macro|XM_IN32
mdefine_line|#define XM_IN32(IoC,Mac,Reg,pVal) {&t;&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC),XMA((Mac),(Reg)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SK_U16 *)&amp;((SK_U16 *)(pVal))[XM_WORD_LO]);&t;&t;&bslash;&n;&t;SK_IN16((IoC),XMA((Mac),(Reg+2)),&t;&t;&t;&t;&bslash;&n;&t;&t;(SK_U16 *)&amp;((SK_U16 *)(pVal))[XM_WORD_HI]);&t;&t;&bslash;&n;}
DECL|macro|XM_OUT32
mdefine_line|#define XM_OUT32(IoC,Mac,Reg,Val) {&t;&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC),XMA((Mac),(Reg)), (SK_U16)((Val) &amp; 0x0000ffffL));&bslash;&n;&t;SK_OUT16((IoC),XMA((Mac),(Reg+2)),(SK_U16)(((Val)&gt;&gt;16) &amp; 0x0000ffffL));&bslash;&n;}
multiline_comment|/*&n; * Remember: we are always writing to / reading from LITTLE ENDIAN memory&n; */
DECL|macro|XM_INADDR
mdefine_line|#define XM_INADDR(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U16&t;Word;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[0] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[1] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+2)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[2] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[3] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+4)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[4] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[5] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;}
DECL|macro|XM_OUTADDR
mdefine_line|#define XM_OUTADDR(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[0]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[1]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+2)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[2]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[3]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+4)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[4]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[5]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;}
DECL|macro|XM_INHASH
mdefine_line|#define XM_INHASH(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U16&t;Word;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[0] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[1] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+2)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[2] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[3] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+4)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[4] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[5] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+6)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[6] = (SK_U8) (Word  &amp; 0x00ff);&t;&t;&t;&t;&bslash;&n;&t;pByte[7] = (SK_U8) ((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;}
DECL|macro|XM_OUTHASH
mdefine_line|#define XM_OUTHASH(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[0]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[1]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+2)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[2]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[3]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+4)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[4]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[5]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+6)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[6]) &amp; 0x00ff)|&t;&t;&t;&bslash;&n;&t;&t; (((SK_U16)(pByte[7]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Different PHY Types&n; */
DECL|macro|SK_PHY_XMAC
mdefine_line|#define SK_PHY_XMAC&t;0&t;/* integrated in Xmac II*/
DECL|macro|SK_PHY_BCOM
mdefine_line|#define SK_PHY_BCOM&t;1&t;/* Broadcom BCM5400 */
DECL|macro|SK_PHY_LONE
mdefine_line|#define SK_PHY_LONE&t;2&t;/* Level One LXT1000 */
DECL|macro|SK_PHY_NAT
mdefine_line|#define SK_PHY_NAT&t;3&t;/* National DP83891 */ 
multiline_comment|/*&n; * PHY addresses (bits 8..12 of PHY address reg)&n; */
DECL|macro|PHY_ADDR_XMAC
mdefine_line|#define PHY_ADDR_XMAC&t;(0&lt;&lt;8)
DECL|macro|PHY_ADDR_BCOM
mdefine_line|#define PHY_ADDR_BCOM&t;(1&lt;&lt;8)
DECL|macro|PHY_ADDR_LONE
mdefine_line|#define PHY_ADDR_LONE&t;(3&lt;&lt;8)
DECL|macro|PHY_ADDR_NAT
mdefine_line|#define PHY_ADDR_NAT&t;(0&lt;&lt;8)
multiline_comment|/*&n; * macros to access the PHY&n; *&n; * PHY_READ()&t;&t;read a 16 bit value from the PHY&n; * PHY_WIRTE()&t;&t;write a 16 bit value to the PHY&n; *&n; * para:&t;IoC&t;I/O context needed for SK IO macros&n; *&t;&t;pPort&t;Pointer to port struct for PhyAddr&n; * &t;&t;Mac&t;XMAC to address&t;&t;values: MAC_1 or MAC_2&n; *&t;&t;PhyReg&t;PHY Register to read or write&n; *&t;&t;(p)Val&t;Value or pointer to the value which should be read or&n; *&t;&t;&t;written.&n; *&n; * usage:&t;PHY_READ(IoC, pPort, MAC_1, PHY_CTRL, Value);&n; * Warning: a PHY_READ on an uninitialized PHY (PHY still in reset) never&n; *          comes back. This is checked in DEBUG mode.&n; */
macro_line|#ifndef DEBUG
DECL|macro|PHY_READ
mdefine_line|#define PHY_READ(IoC, pPort, Mac, PhyReg, pVal) {&t;&t;&t;&bslash;&n;&t;SK_U16 Mmu;  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;XM_OUT16((IoC),(Mac), XM_PHY_ADDR, (PhyReg)|(pPort)-&gt;PhyAddr);&t;&bslash;&n;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_RDY) == 0);&t;&t;&t;&bslash;&n;&t;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|PHY_READ
mdefine_line|#define PHY_READ(IoC, pPort, Mac, PhyReg, pVal) {&t;&t;&t;&bslash;&n;&t;SK_U16 Mmu;  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __i = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;XM_OUT16((IoC),(Mac), XM_PHY_ADDR, (PhyReg)|(pPort)-&gt;PhyAddr);&t;&bslash;&n;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&bslash;&n;&t;&t;&t;__i++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (__i &gt; 10000) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;SK_DBG_PRINTF(&quot;*****************************&bslash;n&quot;); &bslash;&n;&t;&t;&t;&t;SK_DBG_PRINTF(&quot;PHY_READ on uninitialized PHY&bslash;n&quot;); &bslash;&n;&t;&t;&t;&t;SK_DBG_PRINTF(&quot;*****************************&bslash;n&quot;); &bslash;&n;&t;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_RDY) == 0);&t;&t;&t;&bslash;&n;&t;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif
DECL|macro|PHY_WRITE
mdefine_line|#define PHY_WRITE(IoC, pPort, Mac, PhyReg, Val) {&t;&t;&t;&bslash;&n;&t;SK_U16 Mmu;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_BUSY) != 0);&t;&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;XM_OUT16((IoC), (Mac), XM_PHY_ADDR, (PhyReg)|(pPort)-&gt;PhyAddr);&t;&bslash;&n;&t;XM_OUT16((IoC), (Mac), XM_PHY_DATA, (Val));&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_BUSY) != 0);&t;&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; *&t;Macro PCI_C()&n; *&n; *&t;Use this macro to address PCI config register from the IO space.&n; *&n; * para&t;Addr&t;PCI configuration register to address.&n; *&t;&t;&t;Values:&t;PCI_VENDOR_ID&t;...&t;PCI_VPD_ADDR,&n; *&n; * usage&t;SK_IN16(pAC,PCI_C(PCI_VENDOR_ID),pVal);&n; */
DECL|macro|PCI_C
mdefine_line|#define PCI_C(Addr)&t;(B7_CFG_SPC + (Addr))&t;/* PCI Config Space */
multiline_comment|/*&n; *&t;Macro SK_ADDR(Base,Addr)&n; *&n; *&t;Calculates the effective HW address&n; *&n; * para Base&t;IO- or memory base address&n; *&t;Addr&t;Address offset&n; *&n; * usage:&t;May be used in SK_INxx and SK_OUTxx macros&n; *&t;&t;#define SK_IN8(pAC,Addr,pVal) ...&bslash;&n; *&t;&t;&t;*pVal = (SK_U8) inp(SK_ADDR(pAC-&gt;Hw.Iop,Addr)))&n; */
macro_line|#ifdef&t;SK_MEM_MAPPED_IO
DECL|macro|SK_HW_ADDR
mdefine_line|#define&t;SK_HW_ADDR(Base,Addr)&t;((Base)+(Addr))
macro_line|#else&t;/* SK_MEM_MAPPED_IO */
DECL|macro|SK_HW_ADDR
mdefine_line|#define SK_HW_ADDR(Base,Addr)&t;((Base)+(((Addr)&amp;0x7F)|((Addr)&gt;&gt;7 ? 0x80:0)))
macro_line|#endif&t;/* SK_MEM_MAPPED_IO */
DECL|macro|SZ_LONG
mdefine_line|#define&t;SZ_LONG&t;(sizeof(SK_U32))
multiline_comment|/*&n; *&t;Macro SK_HWAC_LINK_LED()&n; *&n; *&t;Use this macro to set the link LED mode.&n; * para pAC&t;Pointer to adapter context struct&n; *&t;IoC&t;I/O context needed for SK IO macros&n; *     &t;Port&t;Port number&n; *&t;Mode&t;Mode to set for this LED&n; */
DECL|macro|SK_HWAC_LINK_LED
mdefine_line|#define SK_HWAC_LINK_LED(pAC, IoC, Port, Mode) &bslash;&n;SK_OUT8(IoC, MR_ADDR(Port,LNK_LED_REG), Mode); 
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKGEHW_H */
eof
