multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgehw.h&n; * Project:&t;Gigabit Ethernet Adapters, Common Modules&n; * Version:&t;$Revision: 1.53 $&n; * Date:&t;$Date: 2003/07/04 12:39:01 $&n; * Purpose:&t;Defines and Macros for the Gigabit Ethernet Adapter Product Family&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; * $Log: skgehw.h,v $&n; * Revision 1.53  2003/07/04 12:39:01  rschmidt&n; * Added SK_FAR to pointers in XM_IN32() and GM_IN32() macros (for PXE)&n; * Editorial changes&n; *&n; * Revision 1.52  2003/05/13 17:16:36  mkarl&n; * Added SK_FAR for PXE.&n; * Editorial changes.&n; *&n; * Revision 1.51  2003/04/08 16:31:50  rschmidt&n; * Added defines for new Chip IDs (YUKON-Lite, YUKON-LP)&n; * Editorial changes&n; *&n; * Revision 1.50  2003/03/31 07:29:45  mkarl&n; * Corrected Copyright.&n; * Editorial changes.&n; *&n; * Revision 1.49  2003/01/28 09:43:49  rschmidt&n; * Added defines for PCI-Spec. 2.3 IRQ&n; * Added defines for CLK_RUN (YUKON-Lite)&n; * Editorial changes&n; *&n; * Revision 1.48  2002/12/05 10:25:11  rschmidt&n; * Added defines for Half Duplex Burst Mode On/Off&n; * Added defines for Rx GMAC FIFO Flush feature&n; * Editorial changes&n; *&n; * Revision 1.47  2002/11/12 17:01:31  rschmidt&n; * Added defines for WOL_CTL_DEFAULT&n; * Editorial changes&n; *&n; * Revision 1.46  2002/10/14 14:47:57  rschmidt&n; * Corrected bit mask for HW self test results&n; * Added defines for WOL Registers&n; * Editorial changes&n; *&n; * Revision 1.45  2002/10/11 09:25:22  mkarl&n; * Added bit mask for HW self test results.&n; *&n; * Revision 1.44  2002/08/16 14:44:36  rschmidt&n; * Added define GPC_HWCFG_GMII_FIB for YUKON Fiber&n; *&n; * Revision 1.43  2002/08/12 13:31:50  rschmidt&n; * Corrected macros for GMAC Address Registers: GM_INADDR(),&n; * GM_OUTADDR(), GM_INHASH, GM_OUTHASH.&n; * Editorial changes&n; *&n; * Revision 1.42  2002/08/08 15:37:56  rschmidt&n; * Added defines for Power Management Capabilities&n; * Editorial changes&n; *&n; * Revision 1.41  2002/07/23 16:02:25  rschmidt&n; * Added macro WOL_REG() to access WOL reg. (HW-Bug in YUKON 1st rev.)&n; *&n; * Revision 1.40  2002/07/15 15:41:37  rschmidt&n; * Added new defines for Power Management Cap. &amp; Control&n; * Editorial changes&n; *&n; * Revision 1.39  2002/06/10 09:37:07  rschmidt&n; * Added macros for the ADDR-Modul&n; *&n; * Revision 1.38  2002/06/05 08:15:19  rschmidt&n; * Added defines for WOL Registers&n; * Editorial changes&n; *&n; * Revision 1.37  2002/04/25 11:39:23  rschmidt&n; * Added new defines for PCI Our Register 1&n; * Added new registers and defines for YUKON (Rx FIFO, Tx FIFO,&n; * Time Stamp Timer, GMAC Control, GPHY Control,Link Control,&n; * GMAC IRQ Source and Mask, Wake-up Frame Pattern Match);&n; * Added new defines for Control/Status (VAUX available)&n; * Added Chip ID for YUKON&n; * Added define for descriptors with UDP ext. for YUKON&n; * Added macros to access the GMAC&n; * Added new Phy Type for Marvell 88E1011S (GPHY)&n; * Editorial changes&n; *&n; * Revision 1.36  2000/11/09 12:32:49  rassmann&n; * Renamed variables.&n; *&n; * Revision 1.35  2000/05/19 10:17:13  cgoos&n; * Added inactivity check in PHY_READ (in DEBUG mode only).&n; *&n; * Revision 1.34  1999/11/22 13:53:40  cgoos&n; * Changed license header to GPL.&n; *&n; * Revision 1.33  1999/08/27 11:17:10  malthoff&n; * It&squot;s more savely to put brackets around macro parameters.&n; * Brackets added for PHY_READ and PHY_WRITE.&n; *&n; * Revision 1.32  1999/05/19 07:31:01  cgoos&n; * Changes for 1000Base-T.&n; * Added HWAC_LINK_LED macro.&n; *&n; * Revision 1.31  1999/03/12 13:27:40  malthoff&n; * Remove __STDC__.&n; *&n; * Revision 1.30  1999/02/09 09:28:20  malthoff&n; * Add PCI_ERRBITS.&n; *&n; * Revision 1.29  1999/01/26 08:55:48  malthoff&n; * Bugfix: The 16 bit field relations inside the descriptor are&n; * &t;endianess dependend if the descriptor reversal feature&n; * &t;(PCI_REV_DESC bit in PCI_OUR_REG_2) is enabled.&n; * &t;Drivers which use this feature has to set the define&n; * &t;SK_USE_REV_DESC.&n; *&n; * Revision 1.28  1998/12/10 11:10:22  malthoff&n; * bug fix: IS_IRQ_STAT and IS_IRQ_MST_ERR has been twisted.&n; *&n; * Revision 1.27  1998/11/13 14:19:21  malthoff&n; * Bug Fix: The bit definition of B3_PA_CTRL has completely&n; * changed from HW Spec v1.3 to v1.5.&n; *&n; * Revision 1.26  1998/11/04 08:31:48  cgoos&n; * Fixed byte ordering in XM_OUTADDR/XM_OUTHASH macros.&n; *&n; * Revision 1.25  1998/11/04 07:16:25  cgoos&n; * Changed byte ordering in XM_INADDR/XM_INHASH again.&n; *&n; * Revision 1.24  1998/11/02 11:08:43  malthoff&n; * RxCtrl and TxCtrl must be volatile.&n; *&n; * Revision 1.23  1998/10/28 13:50:45  malthoff&n; * Fix: Endian support missing in XM_IN/OUT-ADDR/HASH macros.&n; *&n; * Revision 1.22  1998/10/26 08:01:36  malthoff&n; * RX_MFF_CTRL1 is split up into RX_MFF_CTRL1,&n; * RX_MFF_STAT_TO, and RX_MFF_TIST_TO.&n; * TX_MFF_CTRL1 is split up TX_MFF_CTRL1 and TX_MFF_WAF.&n; *&n; * Revision 1.21  1998/10/20 07:43:10  malthoff&n; * Fix: XM_IN/OUT/ADDR/HASH macros:&n; * The pointer must be casted.&n; *&n; * Revision 1.20  1998/10/19 15:53:59  malthoff&n; * Remove ML proto definitions.&n; *&n; * Revision 1.19  1998/10/16 14:40:17  gklug&n; * fix: typo B0_XM_IMSK regs&n; *&n; * Revision 1.18  1998/10/16 09:46:54  malthoff&n; * Remove temp defines for ML diag prototype.&n; * Fix register definition for B0_XM1_PHY_DATA, B0_XM1_PHY_DATA&n; * B0_XM2_PHY_DATA, B0_XM2_PHY_ADDR, B0_XA1_CSR, B0_XS1_CSR,&n; * B0_XS2_CSR, and B0_XA2_CSR.&n; *&n; * Revision 1.17  1998/10/14 06:03:14  cgoos&n; * Changed shifted constant to ULONG.&n; *&n; * Revision 1.16  1998/10/09 07:05:41  malthoff&n; * Rename ALL_PA_ENA_TO to PA_ENA_TO_ALL.&n; *&n; * Revision 1.15  1998/10/05 07:54:23  malthoff&n; * Split up RB_CTRL and it&squot;s bit definition into&n; * RB_CTRL, RB_TST1, and RB_TST2.&n; * Rename RB_RX_HTPP to RB_RX_LTPP.&n; * Add ALL_PA_ENA_TO. Modify F_WATER_MARK&n; * according to HW Spec. v1.5.&n; * Add MFF_TX_CTRL_DEF.&n; *&n; * Revision 1.14  1998/09/28 13:31:16  malthoff&n; * bug fix: B2_MAC_3 is 0x110 not 0x114&n; *&n; * Revision 1.13  1998/09/24 14:42:56  malthoff&n; * Split the RX_MFF_TST into RX_MFF_CTRL2,&n; * RX_MFF_TST1, and RX_MFF_TST2.&n; * Rename RX_MFF_CTRL to RX_MFF_CTRL1.&n; * Add BMU bit CSR_SV_IDLE.&n; * Add macros PHY_READ() and PHY_WRITE().&n; * Rename macro SK_ADDR() to SK_HW_ADDR()&n; * because of conflicts with the Address Module.&n; *&n; * Revision 1.12  1998/09/16 07:25:33  malthoff&n; * Change the parameter order in the XM_INxx and XM_OUTxx macros,&n; * to have the IoC as first parameter.&n; *&n; * Revision 1.11  1998/09/03 09:58:41  malthoff&n; * Rework the XM_xxx macros. Use {} instead of () to&n; * be compatible with SK_xxx macros which are defined&n; * with {}.&n; *&n; * Revision 1.10  1998/09/02 11:16:39  malthoff&n; * Temporary modify B2_I2C_SW to make tests with&n; * the GE/ML prototype.&n; *&n; * Revision 1.9  1998/08/19 09:11:49  gklug&n; * fix: struct are removed from c-source (see CCC)&n; * add: typedefs for all structs&n; *&n; * Revision 1.8  1998/08/18 08:27:27  malthoff&n; * Add some temporary workarounds to test GE&n; * sources with the ML.&n; *&n; * Revision 1.7  1998/07/03 14:42:26  malthoff&n; * bug fix: Correct macro XMA().&n; * Add temporary workaround to access the PCI config space over I/O&n; *&n; * Revision 1.6  1998/06/23 11:30:36  malthoff&n; * Remove &squot;;&squot; with &squot;,&squot; in macors.&n; *&n; * Revision 1.5  1998/06/22 14:20:57  malthoff&n; * Add macro SK_ADDR(Base,Addr).&n; *&n; * Revision 1.4  1998/06/19 13:35:43  malthoff&n; * change &squot;pGec&squot; with &squot;pAC&squot;&n; *&n; * Revision 1.3  1998/06/17 14:58:16  cvs&n; * Lost keywords reinserted.&n; *&n; * Revision 1.1  1998/06/17 14:16:36  cvs&n; * created&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKGEHW_H
DECL|macro|__INC_SKGEHW_H
mdefine_line|#define __INC_SKGEHW_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
DECL|macro|BIT_31
mdefine_line|#define BIT_31&t;&t;(1UL &lt;&lt; 31)
DECL|macro|BIT_30
mdefine_line|#define BIT_30&t;&t;(1L &lt;&lt; 30)
DECL|macro|BIT_29
mdefine_line|#define BIT_29&t;&t;(1L &lt;&lt; 29)
DECL|macro|BIT_28
mdefine_line|#define BIT_28&t;&t;(1L &lt;&lt; 28)
DECL|macro|BIT_27
mdefine_line|#define BIT_27&t;&t;(1L &lt;&lt; 27)
DECL|macro|BIT_26
mdefine_line|#define BIT_26&t;&t;(1L &lt;&lt; 26)
DECL|macro|BIT_25
mdefine_line|#define BIT_25&t;&t;(1L &lt;&lt; 25)
DECL|macro|BIT_24
mdefine_line|#define BIT_24&t;&t;(1L &lt;&lt; 24)
DECL|macro|BIT_23
mdefine_line|#define BIT_23&t;&t;(1L &lt;&lt; 23)
DECL|macro|BIT_22
mdefine_line|#define BIT_22&t;&t;(1L &lt;&lt; 22)
DECL|macro|BIT_21
mdefine_line|#define BIT_21&t;&t;(1L &lt;&lt; 21)
DECL|macro|BIT_20
mdefine_line|#define BIT_20&t;&t;(1L &lt;&lt; 20)
DECL|macro|BIT_19
mdefine_line|#define BIT_19&t;&t;(1L &lt;&lt; 19)
DECL|macro|BIT_18
mdefine_line|#define BIT_18&t;&t;(1L &lt;&lt; 18)
DECL|macro|BIT_17
mdefine_line|#define BIT_17&t;&t;(1L &lt;&lt; 17)
DECL|macro|BIT_16
mdefine_line|#define BIT_16&t;&t;(1L &lt;&lt; 16)
DECL|macro|BIT_15
mdefine_line|#define BIT_15&t;&t;(1L &lt;&lt; 15)
DECL|macro|BIT_14
mdefine_line|#define BIT_14&t;&t;(1L &lt;&lt; 14)
DECL|macro|BIT_13
mdefine_line|#define BIT_13&t;&t;(1L &lt;&lt; 13)
DECL|macro|BIT_12
mdefine_line|#define BIT_12&t;&t;(1L &lt;&lt; 12)
DECL|macro|BIT_11
mdefine_line|#define BIT_11&t;&t;(1L &lt;&lt; 11)
DECL|macro|BIT_10
mdefine_line|#define BIT_10&t;&t;(1L &lt;&lt; 10)
DECL|macro|BIT_9
mdefine_line|#define BIT_9&t;&t;(1L &lt;&lt; 9)
DECL|macro|BIT_8
mdefine_line|#define BIT_8&t;&t;(1L &lt;&lt; 8)
DECL|macro|BIT_7
mdefine_line|#define BIT_7&t;&t;(1L &lt;&lt; 7)
DECL|macro|BIT_6
mdefine_line|#define BIT_6&t;&t;(1L &lt;&lt; 6)
DECL|macro|BIT_5
mdefine_line|#define BIT_5&t;&t;(1L &lt;&lt; 5)
DECL|macro|BIT_4
mdefine_line|#define BIT_4&t;&t;(1L &lt;&lt; 4)
DECL|macro|BIT_3
mdefine_line|#define BIT_3&t;&t;(1L &lt;&lt; 3)
DECL|macro|BIT_2
mdefine_line|#define BIT_2&t;&t;(1L &lt;&lt; 2)
DECL|macro|BIT_1
mdefine_line|#define BIT_1&t;&t;(1L &lt;&lt; 1)
DECL|macro|BIT_0
mdefine_line|#define BIT_0&t;&t;1L
DECL|macro|BIT_15S
mdefine_line|#define BIT_15S&t;&t;(1U &lt;&lt; 15)
DECL|macro|BIT_14S
mdefine_line|#define BIT_14S&t;&t;(1 &lt;&lt; 14)
DECL|macro|BIT_13S
mdefine_line|#define BIT_13S&t;&t;(1 &lt;&lt; 13)
DECL|macro|BIT_12S
mdefine_line|#define BIT_12S&t;&t;(1 &lt;&lt; 12)
DECL|macro|BIT_11S
mdefine_line|#define BIT_11S&t;&t;(1 &lt;&lt; 11)
DECL|macro|BIT_10S
mdefine_line|#define BIT_10S&t;&t;(1 &lt;&lt; 10)
DECL|macro|BIT_9S
mdefine_line|#define BIT_9S&t;&t;(1 &lt;&lt; 9)
DECL|macro|BIT_8S
mdefine_line|#define BIT_8S&t;&t;(1 &lt;&lt; 8)
DECL|macro|BIT_7S
mdefine_line|#define BIT_7S &t;&t;(1 &lt;&lt; 7)
DECL|macro|BIT_6S
mdefine_line|#define BIT_6S&t;&t;(1 &lt;&lt; 6)
DECL|macro|BIT_5S
mdefine_line|#define BIT_5S&t;&t;(1 &lt;&lt; 5)
DECL|macro|BIT_4S
mdefine_line|#define BIT_4S&t;&t;(1 &lt;&lt; 4)
DECL|macro|BIT_3S
mdefine_line|#define BIT_3S&t;&t;(1 &lt;&lt; 3)
DECL|macro|BIT_2S
mdefine_line|#define BIT_2S&t;&t;(1 &lt;&lt; 2)
DECL|macro|BIT_1S
mdefine_line|#define BIT_1S&t;&t;(1 &lt;&lt; 1)
DECL|macro|BIT_0S
mdefine_line|#define BIT_0S&t;&t;1
DECL|macro|SHIFT31
mdefine_line|#define SHIFT31(x)&t;((x) &lt;&lt; 31)
DECL|macro|SHIFT30
mdefine_line|#define SHIFT30(x)&t;((x) &lt;&lt; 30)
DECL|macro|SHIFT29
mdefine_line|#define SHIFT29(x)&t;((x) &lt;&lt; 29)
DECL|macro|SHIFT28
mdefine_line|#define SHIFT28(x)&t;((x) &lt;&lt; 28)
DECL|macro|SHIFT27
mdefine_line|#define SHIFT27(x)&t;((x) &lt;&lt; 27)
DECL|macro|SHIFT26
mdefine_line|#define SHIFT26(x)&t;((x) &lt;&lt; 26)
DECL|macro|SHIFT25
mdefine_line|#define SHIFT25(x)&t;((x) &lt;&lt; 25)
DECL|macro|SHIFT24
mdefine_line|#define SHIFT24(x)&t;((x) &lt;&lt; 24)
DECL|macro|SHIFT23
mdefine_line|#define SHIFT23(x)&t;((x) &lt;&lt; 23)
DECL|macro|SHIFT22
mdefine_line|#define SHIFT22(x)&t;((x) &lt;&lt; 22)
DECL|macro|SHIFT21
mdefine_line|#define SHIFT21(x)&t;((x) &lt;&lt; 21)
DECL|macro|SHIFT20
mdefine_line|#define SHIFT20(x)&t;((x) &lt;&lt; 20)
DECL|macro|SHIFT19
mdefine_line|#define SHIFT19(x)&t;((x) &lt;&lt; 19)
DECL|macro|SHIFT18
mdefine_line|#define SHIFT18(x)&t;((x) &lt;&lt; 18)
DECL|macro|SHIFT17
mdefine_line|#define SHIFT17(x)&t;((x) &lt;&lt; 17)
DECL|macro|SHIFT16
mdefine_line|#define SHIFT16(x)&t;((x) &lt;&lt; 16)
DECL|macro|SHIFT15
mdefine_line|#define SHIFT15(x)&t;((x) &lt;&lt; 15)
DECL|macro|SHIFT14
mdefine_line|#define SHIFT14(x)&t;((x) &lt;&lt; 14)
DECL|macro|SHIFT13
mdefine_line|#define SHIFT13(x)&t;((x) &lt;&lt; 13)
DECL|macro|SHIFT12
mdefine_line|#define SHIFT12(x)&t;((x) &lt;&lt; 12)
DECL|macro|SHIFT11
mdefine_line|#define SHIFT11(x)&t;((x) &lt;&lt; 11)
DECL|macro|SHIFT10
mdefine_line|#define SHIFT10(x)&t;((x) &lt;&lt; 10)
DECL|macro|SHIFT9
mdefine_line|#define SHIFT9(x)&t;((x) &lt;&lt; 9)
DECL|macro|SHIFT8
mdefine_line|#define SHIFT8(x)&t;((x) &lt;&lt; 8)
DECL|macro|SHIFT7
mdefine_line|#define SHIFT7(x)&t;((x) &lt;&lt; 7)
DECL|macro|SHIFT6
mdefine_line|#define SHIFT6(x)&t;((x) &lt;&lt; 6)
DECL|macro|SHIFT5
mdefine_line|#define SHIFT5(x)&t;((x) &lt;&lt; 5)
DECL|macro|SHIFT4
mdefine_line|#define SHIFT4(x)&t;((x) &lt;&lt; 4)
DECL|macro|SHIFT3
mdefine_line|#define SHIFT3(x)&t;((x) &lt;&lt; 3)
DECL|macro|SHIFT2
mdefine_line|#define SHIFT2(x)&t;((x) &lt;&lt; 2)
DECL|macro|SHIFT1
mdefine_line|#define SHIFT1(x)&t;((x) &lt;&lt; 1)
DECL|macro|SHIFT0
mdefine_line|#define SHIFT0(x)&t;((x) &lt;&lt; 0)
multiline_comment|/*&n; * Configuration Space header&n; * Since this module is used for different OS&squot;, those may be&n; * duplicate on some of them (e.g. Linux). But to keep the&n; * common source, we have to live with this...&n; */
DECL|macro|PCI_VENDOR_ID
mdefine_line|#define PCI_VENDOR_ID&t;0x00&t;/* 16 bit&t;Vendor ID */
DECL|macro|PCI_DEVICE_ID
mdefine_line|#define PCI_DEVICE_ID&t;0x02&t;/* 16 bit&t;Device ID */
DECL|macro|PCI_COMMAND
mdefine_line|#define PCI_COMMAND&t;&t;0x04&t;/* 16 bit&t;Command */
DECL|macro|PCI_STATUS
mdefine_line|#define PCI_STATUS&t;&t;0x06&t;/* 16 bit&t;Status */
DECL|macro|PCI_REV_ID
mdefine_line|#define PCI_REV_ID&t;&t;0x08&t;/*  8 bit&t;Revision ID */
DECL|macro|PCI_CLASS_CODE
mdefine_line|#define PCI_CLASS_CODE&t;0x09&t;/* 24 bit&t;Class Code */
DECL|macro|PCI_CACHE_LSZ
mdefine_line|#define PCI_CACHE_LSZ&t;0x0c&t;/*  8 bit&t;Cache Line Size */
DECL|macro|PCI_LAT_TIM
mdefine_line|#define PCI_LAT_TIM&t;&t;0x0d&t;/*  8 bit&t;Latency Timer */
DECL|macro|PCI_HEADER_T
mdefine_line|#define PCI_HEADER_T&t;0x0e&t;/*  8 bit&t;Header Type */
DECL|macro|PCI_BIST
mdefine_line|#define PCI_BIST&t;&t;0x0f&t;/*  8 bit&t;Built-in selftest */
DECL|macro|PCI_BASE_1ST
mdefine_line|#define PCI_BASE_1ST&t;0x10&t;/* 32 bit&t;1st Base address */
DECL|macro|PCI_BASE_2ND
mdefine_line|#define PCI_BASE_2ND&t;0x14&t;/* 32 bit&t;2nd Base address */
multiline_comment|/* Byte 0x18..0x2b:&t;reserved */
DECL|macro|PCI_SUB_VID
mdefine_line|#define PCI_SUB_VID&t;&t;0x2c&t;/* 16 bit&t;Subsystem Vendor ID */
DECL|macro|PCI_SUB_ID
mdefine_line|#define PCI_SUB_ID&t;&t;0x2e&t;/* 16 bit&t;Subsystem ID */
DECL|macro|PCI_BASE_ROM
mdefine_line|#define PCI_BASE_ROM&t;0x30&t;/* 32 bit&t;Expansion ROM Base Address */
DECL|macro|PCI_CAP_PTR
mdefine_line|#define PCI_CAP_PTR&t;&t;0x34&t;/*  8 bit &t;Capabilities Ptr */
multiline_comment|/* Byte 0x35..0x3b:&t;reserved */
DECL|macro|PCI_IRQ_LINE
mdefine_line|#define PCI_IRQ_LINE&t;0x3c&t;/*  8 bit&t;Interrupt Line */
DECL|macro|PCI_IRQ_PIN
mdefine_line|#define PCI_IRQ_PIN&t;&t;0x3d&t;/*  8 bit&t;Interrupt Pin */
DECL|macro|PCI_MIN_GNT
mdefine_line|#define PCI_MIN_GNT&t;&t;0x3e&t;/*  8 bit&t;Min_Gnt */
DECL|macro|PCI_MAX_LAT
mdefine_line|#define PCI_MAX_LAT&t;&t;0x3f&t;/*  8 bit&t;Max_Lat */
multiline_comment|/* Device Dependent Region */
DECL|macro|PCI_OUR_REG_1
mdefine_line|#define PCI_OUR_REG_1&t;0x40&t;/* 32 bit &t;Our Register 1 */
DECL|macro|PCI_OUR_REG_2
mdefine_line|#define PCI_OUR_REG_2&t;0x44&t;/* 32 bit &t;Our Register 2 */
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
mdefine_line|#define PCI_VPD_CAP_ID&t;0x50&t;/*  8 bit &t;VPD Cap. ID */
DECL|macro|PCI_VPD_NITEM
mdefine_line|#define PCI_VPD_NITEM&t;0x51&t;/*  8 bit &t;Next Item Ptr */
DECL|macro|PCI_VPD_ADR_REG
mdefine_line|#define PCI_VPD_ADR_REG&t;0x52&t;/* 16 bit &t;VPD Address Register */
DECL|macro|PCI_VPD_DAT_REG
mdefine_line|#define PCI_VPD_DAT_REG&t;0x54&t;/* 32 bit &t;VPD Data Register */
multiline_comment|/* Byte 0x58..0x59:&t;reserved */
DECL|macro|PCI_SER_LD_CTRL
mdefine_line|#define PCI_SER_LD_CTRL&t;0x5a&t;/* 16 bit &t;SEEPROM Loader Ctrl (YUKON only) */
multiline_comment|/* Byte 0x5c..0xff:&t;reserved */
multiline_comment|/*&n; * I2C Address (PCI Config)&n; *&n; * Note: The temperature and voltage sensors are relocated on a different&n; *&t; I2C bus.&n; */
DECL|macro|I2C_ADDR_VPD
mdefine_line|#define I2C_ADDR_VPD&t;0xa0&t;/* I2C address for the VPD EEPROM */
multiline_comment|/*&n; * Define Bits and Values of the registers&n; */
multiline_comment|/*&t;PCI_COMMAND&t;16 bit&t;Command */
multiline_comment|/* Bit 15..11:&t;reserved */
DECL|macro|PCI_INT_DIS
mdefine_line|#define PCI_INT_DIS&t;&t;BIT_10S&t;&t;/* Interrupt INTx# disable (PCI 2.3) */
DECL|macro|PCI_FBTEN
mdefine_line|#define PCI_FBTEN&t;&t;BIT_9S&t;&t;/* Fast Back-To-Back enable */
DECL|macro|PCI_SERREN
mdefine_line|#define PCI_SERREN&t;&t;BIT_8S&t;&t;/* SERR enable */
DECL|macro|PCI_ADSTEP
mdefine_line|#define PCI_ADSTEP&t;&t;BIT_7S&t;&t;/* Address Stepping */
DECL|macro|PCI_PERREN
mdefine_line|#define PCI_PERREN&t;&t;BIT_6S&t;&t;/* Parity Report Response enable */
DECL|macro|PCI_VGA_SNOOP
mdefine_line|#define PCI_VGA_SNOOP&t;BIT_5S&t;&t;/* VGA palette snoop */
DECL|macro|PCI_MWIEN
mdefine_line|#define PCI_MWIEN&t;&t;BIT_4S&t;&t;/* Memory write an inv cycl ena */
DECL|macro|PCI_SCYCEN
mdefine_line|#define PCI_SCYCEN&t;&t;BIT_3S&t;&t;/* Special Cycle enable */
DECL|macro|PCI_BMEN
mdefine_line|#define PCI_BMEN&t;&t;BIT_2S&t;&t;/* Bus Master enable */
DECL|macro|PCI_MEMEN
mdefine_line|#define PCI_MEMEN&t;&t;BIT_1S&t;&t;/* Memory Space Access enable */
DECL|macro|PCI_IOEN
mdefine_line|#define PCI_IOEN&t;&t;BIT_0S&t;&t;/* I/O Space Access enable */
DECL|macro|PCI_COMMAND_VAL
mdefine_line|#define PCI_COMMAND_VAL&t;(PCI_FBTEN | PCI_SERREN | PCI_PERREN | PCI_MWIEN |&bslash;&n;&t;&t;&t;&t;&t;&t; PCI_BMEN | PCI_MEMEN | PCI_IOEN)
multiline_comment|/*&t;PCI_STATUS&t;16 bit&t;Status */
DECL|macro|PCI_PERR
mdefine_line|#define PCI_PERR&t;&t;BIT_15S&t;&t;/* Parity Error */
DECL|macro|PCI_SERR
mdefine_line|#define PCI_SERR&t;&t;BIT_14S&t;&t;/* Signaled SERR */
DECL|macro|PCI_RMABORT
mdefine_line|#define PCI_RMABORT&t;&t;BIT_13S&t;&t;/* Received Master Abort */
DECL|macro|PCI_RTABORT
mdefine_line|#define PCI_RTABORT&t;&t;BIT_12S&t;&t;/* Received Target Abort */
multiline_comment|/* Bit 11:&t;reserved */
DECL|macro|PCI_DEVSEL
mdefine_line|#define PCI_DEVSEL&t;&t;(3&lt;&lt;9)&t;&t;/* Bit 10.. 9:&t;DEVSEL Timing */
DECL|macro|PCI_DEV_FAST
mdefine_line|#define PCI_DEV_FAST&t;(0&lt;&lt;9)&t;&t;/*&t;&t;fast */
DECL|macro|PCI_DEV_MEDIUM
mdefine_line|#define PCI_DEV_MEDIUM&t;(1&lt;&lt;9)&t;&t;/*&t;&t;medium */
DECL|macro|PCI_DEV_SLOW
mdefine_line|#define PCI_DEV_SLOW&t;(2&lt;&lt;9)&t;&t;/*&t;&t;slow */
DECL|macro|PCI_DATAPERR
mdefine_line|#define PCI_DATAPERR&t;BIT_8S&t;&t;/* DATA Parity error detected */
DECL|macro|PCI_FB2BCAP
mdefine_line|#define PCI_FB2BCAP&t;&t;BIT_7S&t;&t;/* Fast Back-to-Back Capability */
DECL|macro|PCI_UDF
mdefine_line|#define PCI_UDF&t;&t;&t;BIT_6S&t;&t;/* User Defined Features */
DECL|macro|PCI_66MHZCAP
mdefine_line|#define PCI_66MHZCAP&t;BIT_5S&t;&t;/* 66 MHz PCI bus clock capable */
DECL|macro|PCI_NEWCAP
mdefine_line|#define PCI_NEWCAP&t;&t;BIT_4S&t;&t;/* New cap. list implemented */
DECL|macro|PCI_INT_STAT
mdefine_line|#define PCI_INT_STAT&t;BIT_3S&t;&t;/* Interrupt INTx# Status (PCI 2.3) */
multiline_comment|/* Bit  2.. 0:&t;reserved */
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
mdefine_line|#define PCI_HD_MF_DEV&t;BIT_7S&t;/* 0= single, 1= multi-func dev */
DECL|macro|PCI_HD_TYPE
mdefine_line|#define PCI_HD_TYPE&t;&t;0x7f&t;/* Bit 6..0:&t;Header Layout 0= normal */
multiline_comment|/*&t;PCI_BIST&t;8 bit&t;Built-in selftest */
multiline_comment|/*&t;Built-in Self test not supported (optional) */
multiline_comment|/*&t;PCI_BASE_1ST&t;32 bit&t;1st Base address */
DECL|macro|PCI_MEMSIZE
mdefine_line|#define PCI_MEMSIZE&t;&t;0x4000L&t;&t;/* use 16 kB Memory Base */
DECL|macro|PCI_MEMBASE_MSK
mdefine_line|#define PCI_MEMBASE_MSK 0xffffc000L&t;/* Bit 31..14:&t;Memory Base Address */
DECL|macro|PCI_MEMSIZE_MSK
mdefine_line|#define PCI_MEMSIZE_MSK 0x00003ff0L&t;/* Bit 13.. 4:&t;Memory Size Req. */
DECL|macro|PCI_PREFEN
mdefine_line|#define PCI_PREFEN&t;&t;BIT_3&t;&t;/* Prefetchable */
DECL|macro|PCI_MEM_TYP
mdefine_line|#define PCI_MEM_TYP&t;&t;(3L&lt;&lt;2)&t;&t;/* Bit&t;2.. 1:&t;Memory Type */
DECL|macro|PCI_MEM32BIT
mdefine_line|#define PCI_MEM32BIT&t;(0L&lt;&lt;1)&t;&t;/* Base addr anywhere in 32 Bit range */
DECL|macro|PCI_MEM1M
mdefine_line|#define PCI_MEM1M&t;&t;(1L&lt;&lt;1)&t;&t;/* Base addr below 1 MegaByte */
DECL|macro|PCI_MEM64BIT
mdefine_line|#define PCI_MEM64BIT&t;(2L&lt;&lt;1)&t;&t;/* Base addr anywhere in 64 Bit range */
DECL|macro|PCI_MEMSPACE
mdefine_line|#define PCI_MEMSPACE&t;BIT_0&t;&t;/* Memory Space Indicator */
multiline_comment|/*&t;PCI_BASE_2ND&t;32 bit&t;2nd Base address */
DECL|macro|PCI_IOBASE
mdefine_line|#define PCI_IOBASE&t;&t;0xffffff00L&t;/* Bit 31.. 8:&t;I/O Base address */
DECL|macro|PCI_IOSIZE
mdefine_line|#define PCI_IOSIZE&t;&t;0x000000fcL&t;/* Bit&t;7.. 2:&t;I/O Size Requirements */
multiline_comment|/* Bit&t;1:&t;reserved */
DECL|macro|PCI_IOSPACE
mdefine_line|#define PCI_IOSPACE&t;&t;BIT_0&t;&t;/* I/O Space Indicator */
multiline_comment|/*&t;PCI_BASE_ROM&t;32 bit&t;Expansion ROM Base Address */
DECL|macro|PCI_ROMBASE_MSK
mdefine_line|#define PCI_ROMBASE_MSK&t;0xfffe0000L&t;/* Bit 31..17:&t;ROM Base address */
DECL|macro|PCI_ROMBASE_SIZ
mdefine_line|#define PCI_ROMBASE_SIZ&t;(0x1cL&lt;&lt;14)&t;/* Bit 16..14:&t;Treat as Base or Size */
DECL|macro|PCI_ROMSIZE
mdefine_line|#define PCI_ROMSIZE&t;&t;(0x38L&lt;&lt;11)&t;/* Bit 13..11:&t;ROM Size Requirements */
multiline_comment|/* Bit 10.. 1:&t;reserved */
DECL|macro|PCI_ROMEN
mdefine_line|#define PCI_ROMEN&t;&t;BIT_0&t;&t;/* Address Decode enable */
multiline_comment|/* Device Dependent Region */
multiline_comment|/*&t;PCI_OUR_REG_1&t;&t;32 bit&t;Our Register 1 */
multiline_comment|/* Bit 31..29:&t;reserved */
DECL|macro|PCI_PHY_COMA
mdefine_line|#define PCI_PHY_COMA&t;BIT_28&t;&t;/* Set PHY to Coma Mode (YUKON only) */
DECL|macro|PCI_TEST_CAL
mdefine_line|#define PCI_TEST_CAL&t;BIT_27&t;&t;/* Test PCI buffer calib. (YUKON only) */
DECL|macro|PCI_EN_CAL
mdefine_line|#define PCI_EN_CAL&t;&t;BIT_26&t;&t;/* Enable PCI buffer calib. (YUKON only) */
DECL|macro|PCI_VIO
mdefine_line|#define PCI_VIO&t;&t;&t;BIT_25&t;&t;/* PCI I/O Voltage, 0 = 3.3V, 1 = 5V */
DECL|macro|PCI_DIS_BOOT
mdefine_line|#define PCI_DIS_BOOT&t;BIT_24&t;&t;/* Disable BOOT via ROM */
DECL|macro|PCI_EN_IO
mdefine_line|#define PCI_EN_IO&t;&t;BIT_23&t;&t;/* Mapping to I/O space */
DECL|macro|PCI_EN_FPROM
mdefine_line|#define PCI_EN_FPROM&t;BIT_22&t;&t;/* Enable FLASH mapping to memory */
multiline_comment|/*&t;&t;1 = Map Flash to memory */
multiline_comment|/*&t;&t;0 = Disable addr. dec */
DECL|macro|PCI_PAGESIZE
mdefine_line|#define PCI_PAGESIZE&t;(3L&lt;&lt;20)&t;/* Bit 21..20:&t;FLASH Page Size&t;*/
DECL|macro|PCI_PAGE_16
mdefine_line|#define PCI_PAGE_16&t;&t;(0L&lt;&lt;20)&t;/*&t;&t;16 k pages&t;*/
DECL|macro|PCI_PAGE_32K
mdefine_line|#define PCI_PAGE_32K&t;(1L&lt;&lt;20)&t;/*&t;&t;32 k pages&t;*/
DECL|macro|PCI_PAGE_64K
mdefine_line|#define PCI_PAGE_64K&t;(2L&lt;&lt;20)&t;/*&t;&t;64 k pages&t;*/
DECL|macro|PCI_PAGE_128K
mdefine_line|#define PCI_PAGE_128K&t;(3L&lt;&lt;20)&t;/*&t;&t;128 k pages&t;*/
multiline_comment|/* Bit 19:&t;reserved&t;*/
DECL|macro|PCI_PAGEREG
mdefine_line|#define PCI_PAGEREG&t;&t;(7L&lt;&lt;16)&t;/* Bit 18..16:&t;Page Register&t;*/
DECL|macro|PCI_NOTAR
mdefine_line|#define PCI_NOTAR&t;&t;BIT_15&t;&t;/* No turnaround cycle */
DECL|macro|PCI_FORCE_BE
mdefine_line|#define PCI_FORCE_BE&t;BIT_14&t;&t;/* Assert all BEs on MR */
DECL|macro|PCI_DIS_MRL
mdefine_line|#define PCI_DIS_MRL&t;&t;BIT_13&t;&t;/* Disable Mem Read Line */
DECL|macro|PCI_DIS_MRM
mdefine_line|#define PCI_DIS_MRM&t;&t;BIT_12&t;&t;/* Disable Mem Read Multiple */
DECL|macro|PCI_DIS_MWI
mdefine_line|#define PCI_DIS_MWI&t;&t;BIT_11&t;&t;/* Disable Mem Write &amp; Invalidate */
DECL|macro|PCI_DISC_CLS
mdefine_line|#define PCI_DISC_CLS&t;BIT_10&t;&t;/* Disc: cacheLsz bound */
DECL|macro|PCI_BURST_DIS
mdefine_line|#define PCI_BURST_DIS&t;BIT_9&t;&t;/* Burst Disable */
DECL|macro|PCI_DIS_PCI_CLK
mdefine_line|#define PCI_DIS_PCI_CLK&t;BIT_8&t;&t;/* Disable PCI clock driving */
DECL|macro|PCI_SKEW_DAS
mdefine_line|#define PCI_SKEW_DAS&t;(0xfL&lt;&lt;4)&t;/* Bit&t;7.. 4:&t;Skew Ctrl, DAS Ext */
DECL|macro|PCI_SKEW_BASE
mdefine_line|#define PCI_SKEW_BASE&t;0xfL&t;&t;/* Bit&t;3.. 0:&t;Skew Ctrl, Base&t;*/
multiline_comment|/*&t;PCI_OUR_REG_2&t;&t;32 bit&t;Our Register 2 */
DECL|macro|PCI_VPD_WR_THR
mdefine_line|#define PCI_VPD_WR_THR&t;(0xffL&lt;&lt;24)&t;/* Bit 31..24:&t;VPD Write Threshold */
DECL|macro|PCI_DEV_SEL
mdefine_line|#define PCI_DEV_SEL&t;&t;(0x7fL&lt;&lt;17)&t;/* Bit 23..17:&t;EEPROM Device Select */
DECL|macro|PCI_VPD_ROM_SZ
mdefine_line|#define PCI_VPD_ROM_SZ&t;(7L&lt;&lt;14)&t;/* Bit 16..14:&t;VPD ROM Size&t;*/
multiline_comment|/* Bit 13..12:&t;reserved&t;*/
DECL|macro|PCI_PATCH_DIR
mdefine_line|#define PCI_PATCH_DIR&t;(0xfL&lt;&lt;8)&t;/* Bit 11.. 8:&t;Ext Patches dir 3..0 */
DECL|macro|PCI_PATCH_DIR_3
mdefine_line|#define PCI_PATCH_DIR_3&t;BIT_11
DECL|macro|PCI_PATCH_DIR_2
mdefine_line|#define PCI_PATCH_DIR_2&t;BIT_10
DECL|macro|PCI_PATCH_DIR_1
mdefine_line|#define PCI_PATCH_DIR_1&t;BIT_9
DECL|macro|PCI_PATCH_DIR_0
mdefine_line|#define PCI_PATCH_DIR_0&t;BIT_8
DECL|macro|PCI_EXT_PATCHS
mdefine_line|#define PCI_EXT_PATCHS&t;(0xfL&lt;&lt;4)&t;/* Bit&t;7.. 4:&t;Extended Patches 3..0 */
DECL|macro|PCI_EXT_PATCH_3
mdefine_line|#define PCI_EXT_PATCH_3&t;BIT_7
DECL|macro|PCI_EXT_PATCH_2
mdefine_line|#define PCI_EXT_PATCH_2&t;BIT_6
DECL|macro|PCI_EXT_PATCH_1
mdefine_line|#define PCI_EXT_PATCH_1&t;BIT_5
DECL|macro|PCI_EXT_PATCH_0
mdefine_line|#define PCI_EXT_PATCH_0&t;BIT_4
DECL|macro|PCI_EN_DUMMY_RD
mdefine_line|#define PCI_EN_DUMMY_RD&t;BIT_3&t;&t;/* Enable Dummy Read */
DECL|macro|PCI_REV_DESC
mdefine_line|#define PCI_REV_DESC&t;BIT_2&t;&t;/* Reverse Desc. Bytes */
multiline_comment|/* Bit&t;1:&t;reserved */
DECL|macro|PCI_USEDATA64
mdefine_line|#define PCI_USEDATA64&t;BIT_0&t;&t;/* Use 64Bit Data bus ext */
multiline_comment|/* Power Management Region */
multiline_comment|/*&t;PCI_PM_CAP_REG&t;&t;16 bit&t;Power Management Capabilities */
DECL|macro|PCI_PME_SUP_MSK
mdefine_line|#define PCI_PME_SUP_MSK&t;(0x1f&lt;&lt;11)&t;/* Bit 15..11:&t;PM Event Support Mask */
DECL|macro|PCI_PME_D3C_SUP
mdefine_line|#define PCI_PME_D3C_SUP&t;BIT_15S&t;&t;/* PME from D3cold Support (if Vaux) */
DECL|macro|PCI_PME_D3H_SUP
mdefine_line|#define PCI_PME_D3H_SUP&t;BIT_14S&t;&t;/* PME from D3hot Support */
DECL|macro|PCI_PME_D2_SUP
mdefine_line|#define PCI_PME_D2_SUP&t;BIT_13S&t;&t;/* PME from D2 Support */
DECL|macro|PCI_PME_D1_SUP
mdefine_line|#define PCI_PME_D1_SUP&t;BIT_12S&t;&t;/* PME from D1 Support */
DECL|macro|PCI_PME_D0_SUP
mdefine_line|#define PCI_PME_D0_SUP&t;BIT_11S&t;&t;/* PME from D0 Support */
DECL|macro|PCI_PM_D2_SUP
mdefine_line|#define PCI_PM_D2_SUP&t;BIT_10S&t;&t;/* D2 Support in 33 MHz mode */
DECL|macro|PCI_PM_D1_SUP
mdefine_line|#define PCI_PM_D1_SUP&t;BIT_9S&t;&t;/* D1 Support */
multiline_comment|/* Bit&t;8.. 6:&t;reserved */
DECL|macro|PCI_PM_DSI
mdefine_line|#define PCI_PM_DSI&t;&t;BIT_5S&t;&t;/* Device Specific Initialization */
DECL|macro|PCI_PM_APS
mdefine_line|#define PCI_PM_APS&t;&t;BIT_4S&t;&t;/* Auxialiary Power Source */
DECL|macro|PCI_PME_CLOCK
mdefine_line|#define PCI_PME_CLOCK&t;BIT_3S&t;&t;/* PM Event Clock */
DECL|macro|PCI_PM_VER_MSK
mdefine_line|#define PCI_PM_VER_MSK&t;&t;7&t;&t;/* Bit&t;2.. 0:&t;PM PCI Spec. version */
multiline_comment|/*&t;PCI_PM_CTL_STS&t;&t;16 bit&t;Power Management Control/Status */
DECL|macro|PCI_PME_STATUS
mdefine_line|#define PCI_PME_STATUS&t;BIT_15S&t;&t;/* PME Status (YUKON only) */
DECL|macro|PCI_PM_DAT_SCL
mdefine_line|#define PCI_PM_DAT_SCL&t;(3&lt;&lt;13)&t;&t;/* Bit 14..13:&t;Data Reg. scaling factor */
DECL|macro|PCI_PM_DAT_SEL
mdefine_line|#define PCI_PM_DAT_SEL&t;(0xf&lt;&lt;9)&t;/* Bit 12.. 9:&t;PM data selector field */
DECL|macro|PCI_PME_EN
mdefine_line|#define PCI_PME_EN&t;&t;BIT_8S&t;&t;/* Enable PME# generation (YUKON only) */
multiline_comment|/* Bit&t;7.. 2:&t;reserved */
DECL|macro|PCI_PM_STATE_MSK
mdefine_line|#define PCI_PM_STATE_MSK&t;3&t;&t;/* Bit&t;1.. 0:&t;Power Management State */
DECL|macro|PCI_PM_STATE_D0
mdefine_line|#define PCI_PM_STATE_D0&t;&t;0&t;&t;/* D0:&t;Operational (default) */
DECL|macro|PCI_PM_STATE_D1
mdefine_line|#define PCI_PM_STATE_D1&t;&t;1&t;&t;/* D1:&t;(YUKON only) */
DECL|macro|PCI_PM_STATE_D2
mdefine_line|#define PCI_PM_STATE_D2&t;&t;2&t;&t;/* D2:&t;(YUKON only) */
DECL|macro|PCI_PM_STATE_D3
mdefine_line|#define PCI_PM_STATE_D3 &t;3&t;&t;/* D3:&t;HOT, Power Down and Reset */
multiline_comment|/* VPD Region */
multiline_comment|/*&t;PCI_VPD_ADR_REG&t;&t;16 bit&t;VPD Address Register */
DECL|macro|PCI_VPD_FLAG
mdefine_line|#define PCI_VPD_FLAG&t;BIT_15S&t;&t;/* starts VPD rd/wr cycle */
DECL|macro|PCI_VPD_ADR_MSK
mdefine_line|#define PCI_VPD_ADR_MSK&t;0x7fffL&t;&t;/* Bit 14.. 0:&t;VPD address mask */
multiline_comment|/*&t;Control Register File (Address Map) */
multiline_comment|/*&n; *&t;Bank 0&n; */
DECL|macro|B0_RAP
mdefine_line|#define B0_RAP&t;&t;&t;0x0000&t;/*  8 bit&t;Register Address Port */
multiline_comment|/* 0x0001 - 0x0003:&t;reserved */
DECL|macro|B0_CTST
mdefine_line|#define B0_CTST&t;&t;&t;0x0004&t;/* 16 bit&t;Control/Status register */
DECL|macro|B0_LED
mdefine_line|#define B0_LED&t;&t;&t;0x0006&t;/*  8 Bit&t;LED register */
DECL|macro|B0_POWER_CTRL
mdefine_line|#define B0_POWER_CTRL&t;0x0007&t;/*  8 Bit&t;Power Control reg (YUKON only) */
DECL|macro|B0_ISRC
mdefine_line|#define B0_ISRC&t;&t;&t;0x0008&t;/* 32 bit&t;Interrupt Source Register */
DECL|macro|B0_IMSK
mdefine_line|#define B0_IMSK&t;&t;&t;0x000c&t;/* 32 bit&t;Interrupt Mask Register */
DECL|macro|B0_HWE_ISRC
mdefine_line|#define B0_HWE_ISRC&t;&t;0x0010&t;/* 32 bit&t;HW Error Interrupt Src Reg */
DECL|macro|B0_HWE_IMSK
mdefine_line|#define B0_HWE_IMSK&t;&t;0x0014&t;/* 32 bit&t;HW Error Interrupt Mask Reg */
DECL|macro|B0_SP_ISRC
mdefine_line|#define B0_SP_ISRC&t;&t;0x0018&t;/* 32 bit&t;Special Interrupt Source Reg */
multiline_comment|/* 0x001c:&t;&t;reserved */
multiline_comment|/* B0 XMAC 1 registers (GENESIS only) */
DECL|macro|B0_XM1_IMSK
mdefine_line|#define B0_XM1_IMSK&t;&t;0x0020&t;/* 16 bit r/w&t;XMAC 1 Interrupt Mask Register*/
multiline_comment|/* 0x0022 - 0x0027:&t;reserved */
DECL|macro|B0_XM1_ISRC
mdefine_line|#define B0_XM1_ISRC&t;&t;0x0028&t;/* 16 bit ro&t;XMAC 1 Interrupt Status Reg */
multiline_comment|/* 0x002a - 0x002f:&t;reserved */
DECL|macro|B0_XM1_PHY_ADDR
mdefine_line|#define B0_XM1_PHY_ADDR 0x0030&t;/* 16 bit r/w&t;XMAC 1 PHY Address Register */
multiline_comment|/* 0x0032 - 0x0033:&t;reserved */
DECL|macro|B0_XM1_PHY_DATA
mdefine_line|#define B0_XM1_PHY_DATA 0x0034&t;/* 16 bit r/w&t;XMAC 1 PHY Data Register */
multiline_comment|/* 0x0036 - 0x003f:&t;reserved */
multiline_comment|/* B0 XMAC 2 registers (GENESIS only) */
DECL|macro|B0_XM2_IMSK
mdefine_line|#define B0_XM2_IMSK&t;&t;0x0040&t;/* 16 bit r/w&t;XMAC 2 Interrupt Mask Register*/
multiline_comment|/* 0x0042 - 0x0047:&t;reserved */
DECL|macro|B0_XM2_ISRC
mdefine_line|#define B0_XM2_ISRC&t;&t;0x0048&t;/* 16 bit ro&t;XMAC 2 Interrupt Status Reg */
multiline_comment|/* 0x004a - 0x004f:&t;reserved */
DECL|macro|B0_XM2_PHY_ADDR
mdefine_line|#define B0_XM2_PHY_ADDR 0x0050&t;/* 16 bit r/w&t;XMAC 2 PHY Address Register */
multiline_comment|/* 0x0052 - 0x0053:&t;reserved */
DECL|macro|B0_XM2_PHY_DATA
mdefine_line|#define B0_XM2_PHY_DATA 0x0054&t;/* 16 bit r/w&t;XMAC 2 PHY Data Register */
multiline_comment|/* 0x0056 - 0x005f:&t;reserved */
multiline_comment|/* BMU Control Status Registers */
DECL|macro|B0_R1_CSR
mdefine_line|#define B0_R1_CSR&t;&t;0x0060&t;/* 32 bit&t;BMU Ctrl/Stat Rx Queue 1 */
DECL|macro|B0_R2_CSR
mdefine_line|#define B0_R2_CSR&t;&t;0x0064&t;/* 32 bit&t;BMU Ctrl/Stat Rx Queue 2 */
DECL|macro|B0_XS1_CSR
mdefine_line|#define B0_XS1_CSR&t;&t;0x0068&t;/* 32 bit&t;BMU Ctrl/Stat Sync Tx Queue 1 */
DECL|macro|B0_XA1_CSR
mdefine_line|#define B0_XA1_CSR&t;&t;0x006c&t;/* 32 bit&t;BMU Ctrl/Stat Async Tx Queue 1*/
DECL|macro|B0_XS2_CSR
mdefine_line|#define B0_XS2_CSR&t;&t;0x0070&t;/* 32 bit&t;BMU Ctrl/Stat Sync Tx Queue 2 */
DECL|macro|B0_XA2_CSR
mdefine_line|#define B0_XA2_CSR&t;&t;0x0074&t;/* 32 bit&t;BMU Ctrl/Stat Async Tx Queue 2*/
multiline_comment|/* 0x0078 - 0x007f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 1&n; *&t;- completely empty (this is the RAP Block window)&n; *&t;Note: if RAP = 1 this page is reserved&n; */
multiline_comment|/*&n; *&t;Bank 2&n; */
multiline_comment|/* NA reg = 48 bit Network Address Register, 3x16 or 8x8 bit readable */
DECL|macro|B2_MAC_1
mdefine_line|#define B2_MAC_1&t;&t;0x0100&t;/* NA reg&t; MAC Address 1 */
multiline_comment|/* 0x0106 - 0x0107:&t;reserved */
DECL|macro|B2_MAC_2
mdefine_line|#define B2_MAC_2&t;&t;0x0108&t;/* NA reg&t; MAC Address 2 */
multiline_comment|/* 0x010e - 0x010f:&t;reserved */
DECL|macro|B2_MAC_3
mdefine_line|#define B2_MAC_3&t;&t;0x0110&t;/* NA reg&t; MAC Address 3 */
multiline_comment|/* 0x0116 - 0x0117:&t;reserved */
DECL|macro|B2_CONN_TYP
mdefine_line|#define B2_CONN_TYP&t;&t;0x0118&t;/*  8 bit&t;Connector type */
DECL|macro|B2_PMD_TYP
mdefine_line|#define B2_PMD_TYP&t;&t;0x0119&t;/*  8 bit&t;PMD type */
DECL|macro|B2_MAC_CFG
mdefine_line|#define B2_MAC_CFG&t;&t;0x011a&t;/*  8 bit&t;MAC Configuration / Chip Revision */
DECL|macro|B2_CHIP_ID
mdefine_line|#define B2_CHIP_ID&t;&t;0x011b&t;/*  8 bit &t;Chip Identification Number */
multiline_comment|/* Eprom registers are currently of no use */
DECL|macro|B2_E_0
mdefine_line|#define B2_E_0&t;&t;&t;0x011c&t;/*  8 bit&t;EPROM Byte 0 (ext. SRAM size */
DECL|macro|B2_E_1
mdefine_line|#define B2_E_1&t;&t;&t;0x011d&t;/*  8 bit&t;EPROM Byte 1 (PHY type) */
DECL|macro|B2_E_2
mdefine_line|#define B2_E_2&t;&t;&t;0x011e&t;/*  8 bit&t;EPROM Byte 2 */
DECL|macro|B2_E_3
mdefine_line|#define B2_E_3&t;&t;&t;0x011f&t;/*  8 bit&t;EPROM Byte 3 */
DECL|macro|B2_FAR
mdefine_line|#define B2_FAR&t;&t;&t;0x0120&t;/* 32 bit&t;Flash-Prom Addr Reg/Cnt */
DECL|macro|B2_FDP
mdefine_line|#define B2_FDP&t;&t;&t;0x0124&t;/*  8 bit&t;Flash-Prom Data Port */
multiline_comment|/* 0x0125 - 0x0127:&t;reserved */
DECL|macro|B2_LD_CRTL
mdefine_line|#define B2_LD_CRTL&t;&t;0x0128&t;/*  8 bit&t;EPROM loader control register */
DECL|macro|B2_LD_TEST
mdefine_line|#define B2_LD_TEST&t;&t;0x0129&t;/*  8 bit&t;EPROM loader test register */
multiline_comment|/* 0x012a - 0x012f:&t;reserved */
DECL|macro|B2_TI_INI
mdefine_line|#define B2_TI_INI&t;&t;0x0130&t;/* 32 bit&t;Timer Init Value */
DECL|macro|B2_TI_VAL
mdefine_line|#define B2_TI_VAL&t;&t;0x0134&t;/* 32 bit&t;Timer Value */
DECL|macro|B2_TI_CRTL
mdefine_line|#define B2_TI_CRTL&t;&t;0x0138&t;/*  8 bit&t;Timer Control */
DECL|macro|B2_TI_TEST
mdefine_line|#define B2_TI_TEST&t;&t;0x0139&t;/*  8 Bit&t;Timer Test */
multiline_comment|/* 0x013a - 0x013f:&t;reserved */
DECL|macro|B2_IRQM_INI
mdefine_line|#define B2_IRQM_INI&t;&t;0x0140&t;/* 32 bit&t;IRQ Moderation Timer Init Reg.*/
DECL|macro|B2_IRQM_VAL
mdefine_line|#define B2_IRQM_VAL&t;&t;0x0144&t;/* 32 bit&t;IRQ Moderation Timer Value */
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
mdefine_line|#define B2_TST_CTRL1&t;0x0158&t;/*  8 bit&t;Test Control Register 1 */
DECL|macro|B2_TST_CTRL2
mdefine_line|#define B2_TST_CTRL2&t;0x0159&t;/*  8 bit&t;Test Control Register 2 */
multiline_comment|/* 0x015a - 0x015b:&t;reserved */
DECL|macro|B2_GP_IO
mdefine_line|#define B2_GP_IO&t;&t;0x015c&t;/* 32 bit&t;General Purpose I/O Register */
DECL|macro|B2_I2C_CTRL
mdefine_line|#define B2_I2C_CTRL&t;&t;0x0160&t;/* 32 bit&t;I2C HW Control Register */
DECL|macro|B2_I2C_DATA
mdefine_line|#define B2_I2C_DATA&t;&t;0x0164&t;/* 32 bit&t;I2C HW Data Register */
DECL|macro|B2_I2C_IRQ
mdefine_line|#define B2_I2C_IRQ&t;&t;0x0168&t;/* 32 bit&t;I2C HW IRQ Register */
DECL|macro|B2_I2C_SW
mdefine_line|#define B2_I2C_SW&t;&t;0x016c&t;/* 32 bit&t;I2C SW Port Register */
multiline_comment|/* Blink Source Counter (GENESIS only) */
DECL|macro|B2_BSC_INI
mdefine_line|#define B2_BSC_INI&t;&t;0x0170&t;/* 32 bit&t;Blink Source Counter Init Val */
DECL|macro|B2_BSC_VAL
mdefine_line|#define B2_BSC_VAL&t;&t;0x0174&t;/* 32 bit&t;Blink Source Counter Value */
DECL|macro|B2_BSC_CTRL
mdefine_line|#define B2_BSC_CTRL&t;&t;0x0178&t;/*  8 bit&t;Blink Source Counter Control */
DECL|macro|B2_BSC_STAT
mdefine_line|#define B2_BSC_STAT&t;&t;0x0179&t;/*  8 bit&t;Blink Source Counter Status */
DECL|macro|B2_BSC_TST
mdefine_line|#define B2_BSC_TST&t;&t;0x017a&t;/* 16 bit&t;Blink Source Counter Test Reg */
multiline_comment|/* 0x017c - 0x017f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 3&n; */
multiline_comment|/* RAM Random Registers */
DECL|macro|B3_RAM_ADDR
mdefine_line|#define B3_RAM_ADDR&t;&t;0x0180&t;/* 32 bit&t;RAM Address, to read or write */
DECL|macro|B3_RAM_DATA_LO
mdefine_line|#define B3_RAM_DATA_LO&t;0x0184&t;/* 32 bit&t;RAM Data Word (low dWord) */
DECL|macro|B3_RAM_DATA_HI
mdefine_line|#define B3_RAM_DATA_HI&t;0x0188&t;/* 32 bit&t;RAM Data Word (high dWord) */
multiline_comment|/* 0x018c - 0x018f:&t;reserved */
multiline_comment|/* RAM Interface Registers */
multiline_comment|/*&n; * The HW-Spec. calls this registers Timeout Value 0..11. But this names are&n; * not usable in SW. Please notice these are NOT real timeouts, these are&n; * the number of qWords transferred continuously.&n; */
DECL|macro|B3_RI_WTO_R1
mdefine_line|#define B3_RI_WTO_R1&t;0x0190&t;/*  8 bit&t;WR Timeout Queue R1&t;&t;(TO0) */
DECL|macro|B3_RI_WTO_XA1
mdefine_line|#define B3_RI_WTO_XA1&t;0x0191&t;/*  8 bit&t;WR Timeout Queue XA1&t;(TO1) */
DECL|macro|B3_RI_WTO_XS1
mdefine_line|#define B3_RI_WTO_XS1&t;0x0192&t;/*  8 bit&t;WR Timeout Queue XS1&t;(TO2) */
DECL|macro|B3_RI_RTO_R1
mdefine_line|#define B3_RI_RTO_R1&t;0x0193&t;/*  8 bit&t;RD Timeout Queue R1&t;&t;(TO3) */
DECL|macro|B3_RI_RTO_XA1
mdefine_line|#define B3_RI_RTO_XA1&t;0x0194&t;/*  8 bit&t;RD Timeout Queue XA1&t;(TO4) */
DECL|macro|B3_RI_RTO_XS1
mdefine_line|#define B3_RI_RTO_XS1&t;0x0195&t;/*  8 bit&t;RD Timeout Queue XS1&t;(TO5) */
DECL|macro|B3_RI_WTO_R2
mdefine_line|#define B3_RI_WTO_R2&t;0x0196&t;/*  8 bit&t;WR Timeout Queue R2&t;&t;(TO6) */
DECL|macro|B3_RI_WTO_XA2
mdefine_line|#define B3_RI_WTO_XA2&t;0x0197&t;/*  8 bit&t;WR Timeout Queue XA2&t;(TO7) */
DECL|macro|B3_RI_WTO_XS2
mdefine_line|#define B3_RI_WTO_XS2&t;0x0198&t;/*  8 bit&t;WR Timeout Queue XS2&t;(TO8) */
DECL|macro|B3_RI_RTO_R2
mdefine_line|#define B3_RI_RTO_R2&t;0x0199&t;/*  8 bit&t;RD Timeout Queue R2&t;&t;(TO9) */
DECL|macro|B3_RI_RTO_XA2
mdefine_line|#define B3_RI_RTO_XA2&t;0x019a&t;/*  8 bit&t;RD Timeout Queue XA2&t;(TO10)*/
DECL|macro|B3_RI_RTO_XS2
mdefine_line|#define B3_RI_RTO_XS2&t;0x019b&t;/*  8 bit&t;RD Timeout Queue XS2&t;(TO11)*/
DECL|macro|B3_RI_TO_VAL
mdefine_line|#define B3_RI_TO_VAL&t;0x019c&t;/*  8 bit&t;Current Timeout Count Val */
multiline_comment|/* 0x019d - 0x019f:&t;reserved */
DECL|macro|B3_RI_CTRL
mdefine_line|#define B3_RI_CTRL&t;&t;0x01a0&t;/* 16 bit&t;RAM Interface Control Register */
DECL|macro|B3_RI_TEST
mdefine_line|#define B3_RI_TEST&t;&t;0x01a2&t;/*  8 bit&t;RAM Interface Test Register */
multiline_comment|/* 0x01a3 - 0x01af:&t;reserved */
multiline_comment|/* MAC Arbiter Registers (GENESIS only) */
multiline_comment|/* these are the no. of qWord transferred continuously and NOT real timeouts */
DECL|macro|B3_MA_TOINI_RX1
mdefine_line|#define B3_MA_TOINI_RX1&t;0x01b0&t;/*  8 bit&t;Timeout Init Val Rx Path MAC 1 */
DECL|macro|B3_MA_TOINI_RX2
mdefine_line|#define B3_MA_TOINI_RX2&t;0x01b1&t;/*  8 bit&t;Timeout Init Val Rx Path MAC 2 */
DECL|macro|B3_MA_TOINI_TX1
mdefine_line|#define B3_MA_TOINI_TX1&t;0x01b2&t;/*  8 bit&t;Timeout Init Val Tx Path MAC 1 */
DECL|macro|B3_MA_TOINI_TX2
mdefine_line|#define B3_MA_TOINI_TX2&t;0x01b3&t;/*  8 bit&t;Timeout Init Val Tx Path MAC 2 */
DECL|macro|B3_MA_TOVAL_RX1
mdefine_line|#define B3_MA_TOVAL_RX1&t;0x01b4&t;/*  8 bit&t;Timeout Value Rx Path MAC 1 */
DECL|macro|B3_MA_TOVAL_RX2
mdefine_line|#define B3_MA_TOVAL_RX2&t;0x01b5&t;/*  8 bit&t;Timeout Value Rx Path MAC 1 */
DECL|macro|B3_MA_TOVAL_TX1
mdefine_line|#define B3_MA_TOVAL_TX1&t;0x01b6&t;/*  8 bit&t;Timeout Value Tx Path MAC 2 */
DECL|macro|B3_MA_TOVAL_TX2
mdefine_line|#define B3_MA_TOVAL_TX2&t;0x01b7&t;/*  8 bit&t;Timeout Value Tx Path MAC 2 */
DECL|macro|B3_MA_TO_CTRL
mdefine_line|#define B3_MA_TO_CTRL&t;0x01b8&t;/* 16 bit&t;MAC Arbiter Timeout Ctrl Reg */
DECL|macro|B3_MA_TO_TEST
mdefine_line|#define B3_MA_TO_TEST&t;0x01ba&t;/* 16 bit&t;MAC Arbiter Timeout Test Reg */
multiline_comment|/* 0x01bc - 0x01bf:&t;reserved */
DECL|macro|B3_MA_RCINI_RX1
mdefine_line|#define B3_MA_RCINI_RX1&t;0x01c0&t;/*  8 bit&t;Recovery Init Val Rx Path MAC 1 */
DECL|macro|B3_MA_RCINI_RX2
mdefine_line|#define B3_MA_RCINI_RX2&t;0x01c1&t;/*  8 bit&t;Recovery Init Val Rx Path MAC 2 */
DECL|macro|B3_MA_RCINI_TX1
mdefine_line|#define B3_MA_RCINI_TX1&t;0x01c2&t;/*  8 bit&t;Recovery Init Val Tx Path MAC 1 */
DECL|macro|B3_MA_RCINI_TX2
mdefine_line|#define B3_MA_RCINI_TX2&t;0x01c3&t;/*  8 bit&t;Recovery Init Val Tx Path MAC 2 */
DECL|macro|B3_MA_RCVAL_RX1
mdefine_line|#define B3_MA_RCVAL_RX1&t;0x01c4&t;/*  8 bit&t;Recovery Value Rx Path MAC 1 */
DECL|macro|B3_MA_RCVAL_RX2
mdefine_line|#define B3_MA_RCVAL_RX2&t;0x01c5&t;/*  8 bit&t;Recovery Value Rx Path MAC 1 */
DECL|macro|B3_MA_RCVAL_TX1
mdefine_line|#define B3_MA_RCVAL_TX1&t;0x01c6&t;/*  8 bit&t;Recovery Value Tx Path MAC 2 */
DECL|macro|B3_MA_RCVAL_TX2
mdefine_line|#define B3_MA_RCVAL_TX2&t;0x01c7&t;/*  8 bit&t;Recovery Value Tx Path MAC 2 */
DECL|macro|B3_MA_RC_CTRL
mdefine_line|#define B3_MA_RC_CTRL&t;0x01c8&t;/* 16 bit&t;MAC Arbiter Recovery Ctrl Reg */
DECL|macro|B3_MA_RC_TEST
mdefine_line|#define B3_MA_RC_TEST&t;0x01ca&t;/* 16 bit&t;MAC Arbiter Recovery Test Reg */
multiline_comment|/* 0x01cc - 0x01cf:&t;reserved */
multiline_comment|/* Packet Arbiter Registers (GENESIS only) */
multiline_comment|/* these are real timeouts */
DECL|macro|B3_PA_TOINI_RX1
mdefine_line|#define B3_PA_TOINI_RX1&t;0x01d0&t;/* 16 bit&t;Timeout Init Val Rx Path MAC 1 */
multiline_comment|/* 0x01d2 - 0x01d3:&t;reserved */
DECL|macro|B3_PA_TOINI_RX2
mdefine_line|#define B3_PA_TOINI_RX2&t;0x01d4&t;/* 16 bit&t;Timeout Init Val Rx Path MAC 2 */
multiline_comment|/* 0x01d6 - 0x01d7:&t;reserved */
DECL|macro|B3_PA_TOINI_TX1
mdefine_line|#define B3_PA_TOINI_TX1&t;0x01d8&t;/* 16 bit&t;Timeout Init Val Tx Path MAC 1 */
multiline_comment|/* 0x01da - 0x01db:&t;reserved */
DECL|macro|B3_PA_TOINI_TX2
mdefine_line|#define B3_PA_TOINI_TX2&t;0x01dc&t;/* 16 bit&t;Timeout Init Val Tx Path MAC 2 */
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
multiline_comment|/* Transmit Arbiter Registers MAC 1 and 2, use MR_ADDR() to access */
DECL|macro|TXA_ITI_INI
mdefine_line|#define TXA_ITI_INI&t;&t;0x0200&t;/* 32 bit&t;Tx Arb Interval Timer Init Val*/
DECL|macro|TXA_ITI_VAL
mdefine_line|#define TXA_ITI_VAL&t;&t;0x0204&t;/* 32 bit&t;Tx Arb Interval Timer Value */
DECL|macro|TXA_LIM_INI
mdefine_line|#define TXA_LIM_INI&t;&t;0x0208&t;/* 32 bit&t;Tx Arb Limit Counter Init Val */
DECL|macro|TXA_LIM_VAL
mdefine_line|#define TXA_LIM_VAL&t;&t;0x020c&t;/* 32 bit&t;Tx Arb Limit Counter Value */
DECL|macro|TXA_CTRL
mdefine_line|#define TXA_CTRL&t;&t;0x0210&t;/*  8 bit&t;Tx Arbiter Control Register */
DECL|macro|TXA_TEST
mdefine_line|#define TXA_TEST&t;&t;0x0211&t;/*  8 bit&t;Tx Arbiter Test Register */
DECL|macro|TXA_STAT
mdefine_line|#define TXA_STAT&t;&t;0x0212&t;/*  8 bit&t;Tx Arbiter Status Register */
multiline_comment|/* 0x0213 - 0x027f:&t;reserved */
multiline_comment|/* 0x0280 - 0x0292:&t;MAC 2 */
multiline_comment|/* 0x0213 - 0x027f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 6&n; */
multiline_comment|/* External registers (GENESIS only) */
DECL|macro|B6_EXT_REG
mdefine_line|#define B6_EXT_REG&t;&t;0x0300
multiline_comment|/*&n; *&t;Bank 7&n; */
multiline_comment|/* This is a copy of the Configuration register file (lower half) */
DECL|macro|B7_CFG_SPC
mdefine_line|#define B7_CFG_SPC&t;&t;0x0380
multiline_comment|/*&n; *&t;Bank 8 - 15&n; */
multiline_comment|/* Receive and Transmit Queue Registers, use Q_ADDR() to access */
DECL|macro|B8_Q_REGS
mdefine_line|#define B8_Q_REGS&t;&t;0x0400
multiline_comment|/* Queue Register Offsets, use Q_ADDR() to access */
DECL|macro|Q_D
mdefine_line|#define Q_D&t;&t;0x00&t;/* 8*32&t;bit&t;Current Descriptor */
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
mdefine_line|#define Q_F&t;&t;0x38&t;/* 32 bit&t;Flag Register */
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
mdefine_line|#define B16_RAM_REGS&t;0x0800
multiline_comment|/* RAM Buffer Register Offsets, use RB_ADDR() to access */
DECL|macro|RB_START
mdefine_line|#define RB_START&t;&t;0x00&t;/* 32 bit&t;RAM Buffer Start Address */
DECL|macro|RB_END
mdefine_line|#define RB_END&t;&t;&t;0x04&t;/* 32 bit&t;RAM Buffer End Address */
DECL|macro|RB_WP
mdefine_line|#define RB_WP&t;&t;&t;0x08&t;/* 32 bit&t;RAM Buffer Write Pointer */
DECL|macro|RB_RP
mdefine_line|#define RB_RP&t;&t;&t;0x0c&t;/* 32 bit&t;RAM Buffer Read Pointer */
DECL|macro|RB_RX_UTPP
mdefine_line|#define RB_RX_UTPP&t;&t;0x10&t;/* 32 bit&t;Rx Upper Threshold, Pause Pack */
DECL|macro|RB_RX_LTPP
mdefine_line|#define RB_RX_LTPP&t;&t;0x14&t;/* 32 bit&t;Rx Lower Threshold, Pause Pack */
DECL|macro|RB_RX_UTHP
mdefine_line|#define RB_RX_UTHP&t;&t;0x18&t;/* 32 bit&t;Rx Upper Threshold, High Prio */
DECL|macro|RB_RX_LTHP
mdefine_line|#define RB_RX_LTHP&t;&t;0x1c&t;/* 32 bit&t;Rx Lower Threshold, High Prio */
multiline_comment|/* 0x10 - 0x1f:&t;reserved at Tx RAM Buffer Registers */
DECL|macro|RB_PC
mdefine_line|#define RB_PC&t;&t;&t;0x20&t;/* 32 bit&t;RAM Buffer Packet Counter */
DECL|macro|RB_LEV
mdefine_line|#define RB_LEV&t;&t;&t;0x24&t;/* 32 bit&t;RAM Buffer Level Register */
DECL|macro|RB_CTRL
mdefine_line|#define RB_CTRL&t;&t;&t;0x28&t;/*  8 bit&t;RAM Buffer Control Register */
DECL|macro|RB_TST1
mdefine_line|#define RB_TST1&t;&t;&t;0x29&t;/*  8 bit&t;RAM Buffer Test Register 1 */
DECL|macro|RB_TST2
mdefine_line|#define RB_TST2&t;&t;&t;0x2A&t;/*  8 bit&t;RAM Buffer Test Register 2 */
multiline_comment|/* 0x2c - 0x7f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 24&n; */
multiline_comment|/*&n; * Receive MAC FIFO, Receive LED, and Link_Sync regs (GENESIS only)&n; * use MR_ADDR() to access&n; */
DECL|macro|RX_MFF_EA
mdefine_line|#define RX_MFF_EA&t;&t;0x0c00&t;/* 32 bit&t;Receive MAC FIFO End Address */
DECL|macro|RX_MFF_WP
mdefine_line|#define RX_MFF_WP&t;&t;0x0c04&t;/* 32 bit &t;Receive MAC FIFO Write Pointer */
multiline_comment|/* 0x0c08 - 0x0c0b:&t;reserved */
DECL|macro|RX_MFF_RP
mdefine_line|#define RX_MFF_RP&t;&t;0x0c0c&t;/* 32 bit&t;Receive MAC FIFO Read Pointer */
DECL|macro|RX_MFF_PC
mdefine_line|#define RX_MFF_PC&t;&t;0x0c10&t;/* 32 bit&t;Receive MAC FIFO Packet Cnt */
DECL|macro|RX_MFF_LEV
mdefine_line|#define RX_MFF_LEV&t;&t;0x0c14&t;/* 32 bit&t;Receive MAC FIFO Level */
DECL|macro|RX_MFF_CTRL1
mdefine_line|#define RX_MFF_CTRL1&t;0x0c18&t;/* 16 bit&t;Receive MAC FIFO Control Reg 1*/
DECL|macro|RX_MFF_STAT_TO
mdefine_line|#define RX_MFF_STAT_TO&t;0x0c1a&t;/*  8 bit&t;Receive MAC Status Timeout */
DECL|macro|RX_MFF_TIST_TO
mdefine_line|#define RX_MFF_TIST_TO&t;0x0c1b&t;/*  8 bit&t;Receive MAC Time Stamp Timeout */
DECL|macro|RX_MFF_CTRL2
mdefine_line|#define RX_MFF_CTRL2&t;0x0c1c&t;/*  8 bit&t;Receive MAC FIFO Control Reg 2*/
DECL|macro|RX_MFF_TST1
mdefine_line|#define RX_MFF_TST1&t;&t;0x0c1d&t;/*  8 bit&t;Receive MAC FIFO Test Reg 1 */
DECL|macro|RX_MFF_TST2
mdefine_line|#define RX_MFF_TST2&t;&t;0x0c1e&t;/*  8 bit&t;Receive MAC FIFO Test Reg 2 */
multiline_comment|/* 0x0c1f:&t;reserved */
DECL|macro|RX_LED_INI
mdefine_line|#define RX_LED_INI&t;&t;0x0c20&t;/* 32 bit&t;Receive LED Cnt Init Value */
DECL|macro|RX_LED_VAL
mdefine_line|#define RX_LED_VAL&t;&t;0x0c24&t;/* 32 bit&t;Receive LED Cnt Current Value */
DECL|macro|RX_LED_CTRL
mdefine_line|#define RX_LED_CTRL&t;&t;0x0c28&t;/*  8 bit&t;Receive LED Cnt Control Reg */
DECL|macro|RX_LED_TST
mdefine_line|#define RX_LED_TST&t;&t;0x0c29&t;/*  8 bit&t;Receive LED Cnt Test Register */
multiline_comment|/* 0x0c2a - 0x0c2f:&t;reserved */
DECL|macro|LNK_SYNC_INI
mdefine_line|#define LNK_SYNC_INI&t;0x0c30&t;/* 32 bit&t;Link Sync Cnt Init Value */
DECL|macro|LNK_SYNC_VAL
mdefine_line|#define LNK_SYNC_VAL&t;0x0c34&t;/* 32 bit&t;Link Sync Cnt Current Value */
DECL|macro|LNK_SYNC_CTRL
mdefine_line|#define LNK_SYNC_CTRL&t;0x0c38&t;/*  8 bit&t;Link Sync Cnt Control Register */
DECL|macro|LNK_SYNC_TST
mdefine_line|#define LNK_SYNC_TST&t;0x0c39&t;/*  8 bit&t;Link Sync Cnt Test Register */
multiline_comment|/* 0x0c3a - 0x0c3b:&t;reserved */
DECL|macro|LNK_LED_REG
mdefine_line|#define LNK_LED_REG&t;&t;0x0c3c&t;/*  8 bit&t;Link LED Register */
multiline_comment|/* 0x0c3d - 0x0c3f:&t;reserved */
multiline_comment|/* Receive GMAC FIFO (YUKON only), use MR_ADDR() to access */
DECL|macro|RX_GMF_EA
mdefine_line|#define RX_GMF_EA&t;&t;0x0c40&t;/* 32 bit&t;Rx GMAC FIFO End Address */
DECL|macro|RX_GMF_AF_THR
mdefine_line|#define RX_GMF_AF_THR&t;0x0c44&t;/* 32 bit&t;Rx GMAC FIFO Almost Full Thresh. */
DECL|macro|RX_GMF_CTRL_T
mdefine_line|#define RX_GMF_CTRL_T&t;0x0c48&t;/* 32 bit&t;Rx GMAC FIFO Control/Test */
DECL|macro|RX_GMF_FL_MSK
mdefine_line|#define RX_GMF_FL_MSK&t;0x0c4c&t;/* 32 bit&t;Rx GMAC FIFO Flush Mask */
DECL|macro|RX_GMF_FL_THR
mdefine_line|#define RX_GMF_FL_THR&t;0x0c50&t;/* 32 bit&t;Rx GMAC FIFO Flush Threshold */
multiline_comment|/* 0x0c54 - 0x0c5f:&t;reserved */
DECL|macro|RX_GMF_WP
mdefine_line|#define RX_GMF_WP&t;&t;0x0c60&t;/* 32 bit &t;Rx GMAC FIFO Write Pointer */
multiline_comment|/* 0x0c64 - 0x0c67:&t;reserved */
DECL|macro|RX_GMF_WLEV
mdefine_line|#define RX_GMF_WLEV&t;&t;0x0c68&t;/* 32 bit &t;Rx GMAC FIFO Write Level */
multiline_comment|/* 0x0c6c - 0x0c6f:&t;reserved */
DECL|macro|RX_GMF_RP
mdefine_line|#define RX_GMF_RP&t;&t;0x0c70&t;/* 32 bit &t;Rx GMAC FIFO Read Pointer */
multiline_comment|/* 0x0c74 - 0x0c77:&t;reserved */
DECL|macro|RX_GMF_RLEV
mdefine_line|#define RX_GMF_RLEV&t;&t;0x0c78&t;/* 32 bit &t;Rx GMAC FIFO Read Level */
multiline_comment|/* 0x0c7c - 0x0c7f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 25&n; */
multiline_comment|/* 0x0c80 - 0x0cbf:&t;MAC 2 */
multiline_comment|/* 0x0cc0 - 0x0cff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 26&n; */
multiline_comment|/*&n; * Transmit MAC FIFO and Transmit LED Registers (GENESIS only),&n; * use MR_ADDR() to access&n; */
DECL|macro|TX_MFF_EA
mdefine_line|#define TX_MFF_EA&t;&t;0x0d00&t;/* 32 bit&t;Transmit MAC FIFO End Address */
DECL|macro|TX_MFF_WP
mdefine_line|#define TX_MFF_WP&t;&t;0x0d04&t;/* 32 bit &t;Transmit MAC FIFO WR Pointer */
DECL|macro|TX_MFF_WSP
mdefine_line|#define TX_MFF_WSP&t;&t;0x0d08&t;/* 32 bit&t;Transmit MAC FIFO WR Shadow Ptr */
DECL|macro|TX_MFF_RP
mdefine_line|#define TX_MFF_RP&t;&t;0x0d0c&t;/* 32 bit&t;Transmit MAC FIFO RD Pointer */
DECL|macro|TX_MFF_PC
mdefine_line|#define TX_MFF_PC&t;&t;0x0d10&t;/* 32 bit&t;Transmit MAC FIFO Packet Cnt */
DECL|macro|TX_MFF_LEV
mdefine_line|#define TX_MFF_LEV&t;&t;0x0d14&t;/* 32 bit&t;Transmit MAC FIFO Level */
DECL|macro|TX_MFF_CTRL1
mdefine_line|#define TX_MFF_CTRL1&t;0x0d18&t;/* 16 bit&t;Transmit MAC FIFO Ctrl Reg 1 */
DECL|macro|TX_MFF_WAF
mdefine_line|#define TX_MFF_WAF&t;&t;0x0d1a&t;/*  8 bit&t;Transmit MAC Wait after flush */
multiline_comment|/* 0x0c1b:&t;reserved */
DECL|macro|TX_MFF_CTRL2
mdefine_line|#define TX_MFF_CTRL2&t;0x0d1c&t;/*  8 bit&t;Transmit MAC FIFO Ctrl Reg 2 */
DECL|macro|TX_MFF_TST1
mdefine_line|#define TX_MFF_TST1&t;&t;0x0d1d&t;/*  8 bit&t;Transmit MAC FIFO Test Reg 1 */
DECL|macro|TX_MFF_TST2
mdefine_line|#define TX_MFF_TST2&t;&t;0x0d1e&t;/*  8 bit&t;Transmit MAC FIFO Test Reg 2 */
multiline_comment|/* 0x0d1f:&t;reserved */
DECL|macro|TX_LED_INI
mdefine_line|#define TX_LED_INI&t;&t;0x0d20&t;/* 32 bit&t;Transmit LED Cnt Init Value */
DECL|macro|TX_LED_VAL
mdefine_line|#define TX_LED_VAL&t;&t;0x0d24&t;/* 32 bit&t;Transmit LED Cnt Current Val */
DECL|macro|TX_LED_CTRL
mdefine_line|#define TX_LED_CTRL&t;&t;0x0d28&t;/*  8 bit&t;Transmit LED Cnt Control Reg */
DECL|macro|TX_LED_TST
mdefine_line|#define TX_LED_TST&t;&t;0x0d29&t;/*  8 bit&t;Transmit LED Cnt Test Reg */
multiline_comment|/* 0x0d2a - 0x0d3f:&t;reserved */
multiline_comment|/* Transmit GMAC FIFO (YUKON only), use MR_ADDR() to access */
DECL|macro|TX_GMF_EA
mdefine_line|#define TX_GMF_EA&t;&t;0x0d40&t;/* 32 bit&t;Tx GMAC FIFO End Address */
DECL|macro|TX_GMF_AE_THR
mdefine_line|#define TX_GMF_AE_THR&t;0x0d44&t;/* 32 bit&t;Tx GMAC FIFO Almost Empty Thresh.*/
DECL|macro|TX_GMF_CTRL_T
mdefine_line|#define TX_GMF_CTRL_T&t;0x0d48&t;/* 32 bit&t;Tx GMAC FIFO Control/Test */
multiline_comment|/* 0x0d4c - 0x0d5f:&t;reserved */
DECL|macro|TX_GMF_WP
mdefine_line|#define TX_GMF_WP&t;&t;0x0d60&t;/* 32 bit &t;Tx GMAC FIFO Write Pointer */
DECL|macro|TX_GMF_WSP
mdefine_line|#define TX_GMF_WSP&t;&t;0x0d64&t;/* 32 bit &t;Tx GMAC FIFO Write Shadow Ptr. */
DECL|macro|TX_GMF_WLEV
mdefine_line|#define TX_GMF_WLEV&t;&t;0x0d68&t;/* 32 bit &t;Tx GMAC FIFO Write Level */
multiline_comment|/* 0x0d6c - 0x0d6f:&t;reserved */
DECL|macro|TX_GMF_RP
mdefine_line|#define TX_GMF_RP&t;&t;0x0d70&t;/* 32 bit &t;Tx GMAC FIFO Read Pointer */
DECL|macro|TX_GMF_RSTP
mdefine_line|#define TX_GMF_RSTP&t;&t;0x0d74&t;/* 32 bit &t;Tx GMAC FIFO Restart Pointer */
DECL|macro|TX_GMF_RLEV
mdefine_line|#define TX_GMF_RLEV&t;&t;0x0d78&t;/* 32 bit &t;Tx GMAC FIFO Read Level */
multiline_comment|/* 0x0d7c - 0x0d7f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 27&n; */
multiline_comment|/* 0x0d80 - 0x0dbf:&t;MAC 2 */
multiline_comment|/* 0x0daa - 0x0dff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 28&n; */
multiline_comment|/* Descriptor Poll Timer Registers */
DECL|macro|B28_DPT_INI
mdefine_line|#define B28_DPT_INI&t;&t;0x0e00&t;/* 24 bit&t;Descriptor Poll Timer Init Val */
DECL|macro|B28_DPT_VAL
mdefine_line|#define B28_DPT_VAL&t;&t;0x0e04&t;/* 24 bit&t;Descriptor Poll Timer Curr Val */
DECL|macro|B28_DPT_CTRL
mdefine_line|#define B28_DPT_CTRL&t;0x0e08&t;/*  8 bit&t;Descriptor Poll Timer Ctrl Reg */
multiline_comment|/* 0x0e09:&t;reserved */
DECL|macro|B28_DPT_TST
mdefine_line|#define B28_DPT_TST&t;&t;0x0e0a&t;/*  8 bit&t;Descriptor Poll Timer Test Reg */
multiline_comment|/* 0x0e0b:&t;reserved */
multiline_comment|/* Time Stamp Timer Registers (YUKON only) */
multiline_comment|/* 0x0e10:&t;reserved */
DECL|macro|GMAC_TI_ST_VAL
mdefine_line|#define GMAC_TI_ST_VAL&t;0x0e14&t;/* 32 bit&t;Time Stamp Timer Curr Val */
DECL|macro|GMAC_TI_ST_CTRL
mdefine_line|#define GMAC_TI_ST_CTRL&t;0x0e18&t;/*  8 bit&t;Time Stamp Timer Ctrl Reg */
multiline_comment|/* 0x0e19:&t;reserved */
DECL|macro|GMAC_TI_ST_TST
mdefine_line|#define GMAC_TI_ST_TST&t;0x0e1a&t;/*  8 bit&t;Time Stamp Timer Test Reg */
multiline_comment|/* 0x0e1b - 0x0e7f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 29&n; */
multiline_comment|/* 0x0e80 - 0x0efc:&t;reserved */
multiline_comment|/*&n; *&t;Bank 30&n; */
multiline_comment|/* GMAC and GPHY Control Registers (YUKON only) */
DECL|macro|GMAC_CTRL
mdefine_line|#define GMAC_CTRL&t;&t;0x0f00&t;/* 32 bit&t;GMAC Control Reg */
DECL|macro|GPHY_CTRL
mdefine_line|#define GPHY_CTRL&t;&t;0x0f04&t;/* 32 bit&t;GPHY Control Reg */
DECL|macro|GMAC_IRQ_SRC
mdefine_line|#define GMAC_IRQ_SRC&t;0x0f08&t;/*  8 bit&t;GMAC Interrupt Source Reg */
multiline_comment|/* 0x0f09 - 0x0f0b:&t;reserved */
DECL|macro|GMAC_IRQ_MSK
mdefine_line|#define GMAC_IRQ_MSK&t;0x0f0c&t;/*  8 bit&t;GMAC Interrupt Mask Reg */
multiline_comment|/* 0x0f0d - 0x0f0f:&t;reserved */
DECL|macro|GMAC_LINK_CTRL
mdefine_line|#define GMAC_LINK_CTRL&t;0x0f10&t;/* 16 bit&t;Link Control Reg */
multiline_comment|/* 0x0f14 - 0x0f1f:&t;reserved */
multiline_comment|/* Wake-up Frame Pattern Match Control Registers (YUKON only) */
DECL|macro|WOL_REG_OFFS
mdefine_line|#define WOL_REG_OFFS&t;0x20&t;/* HW-Bug: Address is + 0x20 against spec. */
DECL|macro|WOL_CTRL_STAT
mdefine_line|#define WOL_CTRL_STAT&t;0x0f20&t;/* 16 bit&t;WOL Control/Status Reg */
DECL|macro|WOL_MATCH_CTL
mdefine_line|#define WOL_MATCH_CTL&t;0x0f22&t;/*  8 bit&t;WOL Match Control Reg */
DECL|macro|WOL_MATCH_RES
mdefine_line|#define WOL_MATCH_RES&t;0x0f23&t;/*  8 bit&t;WOL Match Result Reg */
DECL|macro|WOL_MAC_ADDR_LO
mdefine_line|#define WOL_MAC_ADDR_LO&t;0x0f24&t;/* 32 bit&t;WOL MAC Address Low */
DECL|macro|WOL_MAC_ADDR_HI
mdefine_line|#define WOL_MAC_ADDR_HI&t;0x0f28&t;/* 16 bit&t;WOL MAC Address High */
DECL|macro|WOL_PATT_RPTR
mdefine_line|#define WOL_PATT_RPTR&t;0x0f2c&t;/*  8 bit&t;WOL Pattern Read Ptr */
multiline_comment|/* use this macro to access above registers */
DECL|macro|WOL_REG
mdefine_line|#define WOL_REG(Reg)&t;((Reg) + (pAC-&gt;GIni.GIWolOffs))
multiline_comment|/* WOL Pattern Length Registers (YUKON only) */
DECL|macro|WOL_PATT_LEN_LO
mdefine_line|#define WOL_PATT_LEN_LO&t;0x0f30&t;&t;/* 32 bit&t;WOL Pattern Length 3..0 */
DECL|macro|WOL_PATT_LEN_HI
mdefine_line|#define WOL_PATT_LEN_HI&t;0x0f34&t;&t;/* 24 bit&t;WOL Pattern Length 6..4 */
multiline_comment|/* WOL Pattern Counter Registers (YUKON only) */
DECL|macro|WOL_PATT_CNT_0
mdefine_line|#define WOL_PATT_CNT_0&t;0x0f38&t;&t;/* 32 bit&t;WOL Pattern Counter 3..0 */
DECL|macro|WOL_PATT_CNT_4
mdefine_line|#define WOL_PATT_CNT_4&t;0x0f3c&t;&t;/* 24 bit&t;WOL Pattern Counter 6..4 */
multiline_comment|/* 0x0f40 - 0x0f7f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 31&n; */
multiline_comment|/* 0x0f80 - 0x0fff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 32&t;- 33&n; */
DECL|macro|WOL_PATT_RAM_1
mdefine_line|#define WOL_PATT_RAM_1&t;0x1000&t;/*  WOL Pattern RAM Link 1 */
multiline_comment|/*&n; *&t;Bank 0x22 - 0x3f&n; */
multiline_comment|/* 0x1100 - 0x1fff:&t;reserved */
multiline_comment|/*&n; *&t;Bank 0x40 - 0x4f&n; */
DECL|macro|BASE_XMAC_1
mdefine_line|#define BASE_XMAC_1&t;&t;0x2000&t;/* XMAC 1 registers */
multiline_comment|/*&n; *&t;Bank 0x50 - 0x5f&n; */
DECL|macro|BASE_GMAC_1
mdefine_line|#define BASE_GMAC_1&t;&t;0x2800&t;/* GMAC 1 registers */
multiline_comment|/*&n; *&t;Bank 0x60 - 0x6f&n; */
DECL|macro|BASE_XMAC_2
mdefine_line|#define BASE_XMAC_2&t;&t;0x3000&t;/* XMAC 2 registers */
multiline_comment|/*&n; *&t;Bank 0x70 - 0x7f&n; */
DECL|macro|BASE_GMAC_2
mdefine_line|#define BASE_GMAC_2&t;&t;0x3800&t;/* GMAC 2 registers */
multiline_comment|/*&n; *&t;Control Register Bit Definitions:&n; */
multiline_comment|/*&t;B0_RAP&t;&t;8 bit&t;Register Address Port */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|RAP_RAP
mdefine_line|#define RAP_RAP&t;&t;&t;0x3f&t;/* Bit 6..0:&t;0 = block 0,..,6f = block 6f */
multiline_comment|/*&t;B0_CTST&t;&t;16 bit&t;Control/Status register */
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|CS_CLK_RUN_HOT
mdefine_line|#define CS_CLK_RUN_HOT&t;BIT_13S&t;&t;/* CLK_RUN hot m. (YUKON-Lite only) */
DECL|macro|CS_CLK_RUN_RST
mdefine_line|#define CS_CLK_RUN_RST&t;BIT_12S&t;&t;/* CLK_RUN reset  (YUKON-Lite only) */
DECL|macro|CS_CLK_RUN_ENA
mdefine_line|#define CS_CLK_RUN_ENA&t;BIT_11S&t;&t;/* CLK_RUN enable (YUKON-Lite only) */
DECL|macro|CS_VAUX_AVAIL
mdefine_line|#define CS_VAUX_AVAIL&t;BIT_10S&t;&t;/* VAUX available (YUKON only) */
DECL|macro|CS_BUS_CLOCK
mdefine_line|#define CS_BUS_CLOCK&t;BIT_9S&t;&t;/* Bus Clock 0/1 = 33/66 MHz */
DECL|macro|CS_BUS_SLOT_SZ
mdefine_line|#define CS_BUS_SLOT_SZ&t;BIT_8S&t;&t;/* Slot Size 0/1 = 32/64 bit slot */
DECL|macro|CS_ST_SW_IRQ
mdefine_line|#define CS_ST_SW_IRQ&t;BIT_7S&t;&t;/* Set IRQ SW Request */
DECL|macro|CS_CL_SW_IRQ
mdefine_line|#define CS_CL_SW_IRQ&t;BIT_6S&t;&t;/* Clear IRQ SW Request */
DECL|macro|CS_STOP_DONE
mdefine_line|#define CS_STOP_DONE&t;BIT_5S&t;&t;/* Stop Master is finished */
DECL|macro|CS_STOP_MAST
mdefine_line|#define CS_STOP_MAST&t;BIT_4S&t;&t;/* Command Bit to stop the master */
DECL|macro|CS_MRST_CLR
mdefine_line|#define CS_MRST_CLR&t;&t;BIT_3S&t;&t;/* Clear Master reset&t;*/
DECL|macro|CS_MRST_SET
mdefine_line|#define CS_MRST_SET&t;&t;BIT_2S&t;&t;/* Set Master reset&t;*/
DECL|macro|CS_RST_CLR
mdefine_line|#define CS_RST_CLR&t;&t;BIT_1S&t;&t;/* Clear Software reset&t;*/
DECL|macro|CS_RST_SET
mdefine_line|#define CS_RST_SET&t;&t;BIT_0S&t;&t;/* Set   Software reset&t;*/
multiline_comment|/*&t;B0_LED&t;&t; 8 Bit&t;LED register */
multiline_comment|/* Bit  7.. 2:&t;reserved */
DECL|macro|LED_STAT_ON
mdefine_line|#define LED_STAT_ON&t;&t;BIT_1S&t;&t;/* Status LED on&t;*/
DECL|macro|LED_STAT_OFF
mdefine_line|#define LED_STAT_OFF&t;BIT_0S&t;&t;/* Status LED off&t;*/
multiline_comment|/*&t;B0_POWER_CTRL&t; 8 Bit&t;Power Control reg (YUKON only) */
DECL|macro|PC_VAUX_ENA
mdefine_line|#define PC_VAUX_ENA&t;&t;BIT_7&t;&t;/* Switch VAUX Enable  */
DECL|macro|PC_VAUX_DIS
mdefine_line|#define PC_VAUX_DIS&t;&t;BIT_6       /* Switch VAUX Disable */
DECL|macro|PC_VCC_ENA
mdefine_line|#define PC_VCC_ENA&t;&t;BIT_5       /* Switch VCC Enable  */
DECL|macro|PC_VCC_DIS
mdefine_line|#define PC_VCC_DIS&t;&t;BIT_4       /* Switch VCC Disable */
DECL|macro|PC_VAUX_ON
mdefine_line|#define PC_VAUX_ON&t;&t;BIT_3       /* Switch VAUX On  */
DECL|macro|PC_VAUX_OFF
mdefine_line|#define PC_VAUX_OFF&t;&t;BIT_2       /* Switch VAUX Off */
DECL|macro|PC_VCC_ON
mdefine_line|#define PC_VCC_ON&t;&t;BIT_1       /* Switch VCC On  */
DECL|macro|PC_VCC_OFF
mdefine_line|#define PC_VCC_OFF&t;&t;BIT_0       /* Switch VCC Off */
multiline_comment|/*&t;B0_ISRC&t;&t;32 bit&t;Interrupt Source Register */
multiline_comment|/*&t;B0_IMSK&t;&t;32 bit&t;Interrupt Mask Register */
multiline_comment|/*&t;B0_SP_ISRC&t;32 bit&t;Special Interrupt Source Reg */
multiline_comment|/*&t;B2_IRQM_MSK &t;32 bit&t;IRQ Moderation Mask */
DECL|macro|IS_ALL_MSK
mdefine_line|#define IS_ALL_MSK&t;&t;0xbfffffffUL&t;/* All Interrupt bits */
DECL|macro|IS_HW_ERR
mdefine_line|#define IS_HW_ERR&t;&t;BIT_31&t;&t;/* Interrupt HW Error */
multiline_comment|/* Bit 30:&t;reserved */
DECL|macro|IS_PA_TO_RX1
mdefine_line|#define IS_PA_TO_RX1&t;BIT_29&t;&t;/* Packet Arb Timeout Rx1 */
DECL|macro|IS_PA_TO_RX2
mdefine_line|#define IS_PA_TO_RX2&t;BIT_28&t;&t;/* Packet Arb Timeout Rx2 */
DECL|macro|IS_PA_TO_TX1
mdefine_line|#define IS_PA_TO_TX1&t;BIT_27&t;&t;/* Packet Arb Timeout Tx1 */
DECL|macro|IS_PA_TO_TX2
mdefine_line|#define IS_PA_TO_TX2&t;BIT_26&t;&t;/* Packet Arb Timeout Tx2 */
DECL|macro|IS_I2C_READY
mdefine_line|#define IS_I2C_READY&t;BIT_25&t;&t;/* IRQ on end of I2C Tx */
DECL|macro|IS_IRQ_SW
mdefine_line|#define IS_IRQ_SW&t;&t;BIT_24&t;&t;/* SW forced IRQ&t;*/
DECL|macro|IS_EXT_REG
mdefine_line|#define IS_EXT_REG&t;&t;BIT_23&t;&t;/* IRQ from LM80 or PHY (GENESIS only) */
multiline_comment|/* IRQ from PHY (YUKON only) */
DECL|macro|IS_TIMINT
mdefine_line|#define IS_TIMINT&t;&t;BIT_22&t;&t;/* IRQ from Timer&t;*/
DECL|macro|IS_MAC1
mdefine_line|#define IS_MAC1&t;&t;&t;BIT_21&t;&t;/* IRQ from MAC 1&t;*/
DECL|macro|IS_LNK_SYNC_M1
mdefine_line|#define IS_LNK_SYNC_M1&t;BIT_20&t;&t;/* Link Sync Cnt wrap MAC 1 */
DECL|macro|IS_MAC2
mdefine_line|#define IS_MAC2&t;&t;&t;BIT_19&t;&t;/* IRQ from MAC 2&t;*/
DECL|macro|IS_LNK_SYNC_M2
mdefine_line|#define IS_LNK_SYNC_M2&t;BIT_18&t;&t;/* Link Sync Cnt wrap MAC 2 */
multiline_comment|/* Receive Queue 1 */
DECL|macro|IS_R1_B
mdefine_line|#define IS_R1_B&t;&t;&t;BIT_17&t;&t;/* Q_R1 End of Buffer */
DECL|macro|IS_R1_F
mdefine_line|#define IS_R1_F&t;&t;&t;BIT_16&t;&t;/* Q_R1 End of Frame */
DECL|macro|IS_R1_C
mdefine_line|#define IS_R1_C&t;&t;&t;BIT_15&t;&t;/* Q_R1 Encoding Error */
multiline_comment|/* Receive Queue 2 */
DECL|macro|IS_R2_B
mdefine_line|#define IS_R2_B&t;&t;&t;BIT_14&t;&t;/* Q_R2 End of Buffer */
DECL|macro|IS_R2_F
mdefine_line|#define IS_R2_F&t;&t;&t;BIT_13&t;&t;/* Q_R2 End of Frame */
DECL|macro|IS_R2_C
mdefine_line|#define IS_R2_C&t;&t;&t;BIT_12&t;&t;/* Q_R2 Encoding Error */
multiline_comment|/* Synchronous Transmit Queue 1 */
DECL|macro|IS_XS1_B
mdefine_line|#define IS_XS1_B&t;&t;BIT_11&t;&t;/* Q_XS1 End of Buffer */
DECL|macro|IS_XS1_F
mdefine_line|#define IS_XS1_F&t;&t;BIT_10&t;&t;/* Q_XS1 End of Frame */
DECL|macro|IS_XS1_C
mdefine_line|#define IS_XS1_C&t;&t;BIT_9&t;&t;/* Q_XS1 Encoding Error */
multiline_comment|/* Asynchronous Transmit Queue 1 */
DECL|macro|IS_XA1_B
mdefine_line|#define IS_XA1_B&t;&t;BIT_8&t;&t;/* Q_XA1 End of Buffer */
DECL|macro|IS_XA1_F
mdefine_line|#define IS_XA1_F&t;&t;BIT_7&t;&t;/* Q_XA1 End of Frame */
DECL|macro|IS_XA1_C
mdefine_line|#define IS_XA1_C&t;&t;BIT_6&t;&t;/* Q_XA1 Encoding Error */
multiline_comment|/* Synchronous Transmit Queue 2 */
DECL|macro|IS_XS2_B
mdefine_line|#define IS_XS2_B&t;&t;BIT_5&t;&t;/* Q_XS2 End of Buffer */
DECL|macro|IS_XS2_F
mdefine_line|#define IS_XS2_F&t;&t;BIT_4&t;&t;/* Q_XS2 End of Frame */
DECL|macro|IS_XS2_C
mdefine_line|#define IS_XS2_C&t;&t;BIT_3&t;&t;/* Q_XS2 Encoding Error */
multiline_comment|/* Asynchronous Transmit Queue 2 */
DECL|macro|IS_XA2_B
mdefine_line|#define IS_XA2_B&t;&t;BIT_2&t;&t;/* Q_XA2 End of Buffer */
DECL|macro|IS_XA2_F
mdefine_line|#define IS_XA2_F&t;&t;BIT_1&t;&t;/* Q_XA2 End of Frame */
DECL|macro|IS_XA2_C
mdefine_line|#define IS_XA2_C&t;&t;BIT_0&t;&t;/* Q_XA2 Encoding Error */
multiline_comment|/*&t;B0_HWE_ISRC&t;32 bit&t;HW Error Interrupt Src Reg */
multiline_comment|/*&t;B0_HWE_IMSK&t;32 bit&t;HW Error Interrupt Mask Reg */
multiline_comment|/*&t;B2_IRQM_HWE_MSK 32 bit&t;IRQ Moderation HW Error Mask */
DECL|macro|IS_ERR_MSK
mdefine_line|#define IS_ERR_MSK&t;&t;0x00000fffL&t;/* &t;&t;All Error bits */
multiline_comment|/* Bit 31..14:&t;reserved */
DECL|macro|IS_IRQ_TIST_OV
mdefine_line|#define IS_IRQ_TIST_OV&t;BIT_13&t;/* Time Stamp Timer Overflow (YUKON only) */
DECL|macro|IS_IRQ_SENSOR
mdefine_line|#define IS_IRQ_SENSOR&t;BIT_12&t;/* IRQ from Sensor (YUKON only) */
DECL|macro|IS_IRQ_MST_ERR
mdefine_line|#define IS_IRQ_MST_ERR&t;BIT_11&t;/* IRQ master error detected */
DECL|macro|IS_IRQ_STAT
mdefine_line|#define IS_IRQ_STAT&t;&t;BIT_10&t;/* IRQ status exception */
DECL|macro|IS_NO_STAT_M1
mdefine_line|#define IS_NO_STAT_M1&t;BIT_9&t;/* No Rx Status from MAC 1 */
DECL|macro|IS_NO_STAT_M2
mdefine_line|#define IS_NO_STAT_M2&t;BIT_8&t;/* No Rx Status from MAC 2 */
DECL|macro|IS_NO_TIST_M1
mdefine_line|#define IS_NO_TIST_M1&t;BIT_7&t;/* No Time Stamp from MAC 1 */
DECL|macro|IS_NO_TIST_M2
mdefine_line|#define IS_NO_TIST_M2&t;BIT_6&t;/* No Time Stamp from MAC 2 */
DECL|macro|IS_RAM_RD_PAR
mdefine_line|#define IS_RAM_RD_PAR&t;BIT_5&t;/* RAM Read  Parity Error */
DECL|macro|IS_RAM_WR_PAR
mdefine_line|#define IS_RAM_WR_PAR&t;BIT_4&t;/* RAM Write Parity Error */
DECL|macro|IS_M1_PAR_ERR
mdefine_line|#define IS_M1_PAR_ERR&t;BIT_3&t;/* MAC 1 Parity Error */
DECL|macro|IS_M2_PAR_ERR
mdefine_line|#define IS_M2_PAR_ERR&t;BIT_2&t;/* MAC 2 Parity Error */
DECL|macro|IS_R1_PAR_ERR
mdefine_line|#define IS_R1_PAR_ERR&t;BIT_1&t;/* Queue R1 Parity Error */
DECL|macro|IS_R2_PAR_ERR
mdefine_line|#define IS_R2_PAR_ERR&t;BIT_0&t;/* Queue R2 Parity Error */
multiline_comment|/*&t;B2_CONN_TYP&t; 8 bit&t;Connector type */
multiline_comment|/*&t;B2_PMD_TYP&t; 8 bit&t;PMD type */
multiline_comment|/*&t;Values of connector and PMD type comply to SysKonnect internal std */
multiline_comment|/*&t;B2_MAC_CFG&t; 8 bit&t;MAC Configuration / Chip Revision */
DECL|macro|CFG_CHIP_R_MSK
mdefine_line|#define CFG_CHIP_R_MSK&t;(0xf&lt;&lt;4)&t;/* Bit 7.. 4: Chip Revision */
multiline_comment|/* Bit 3.. 2:&t;reserved */
DECL|macro|CFG_DIS_M2_CLK
mdefine_line|#define CFG_DIS_M2_CLK&t;BIT_1S&t;&t;/* Disable Clock for 2nd MAC */
DECL|macro|CFG_SNG_MAC
mdefine_line|#define CFG_SNG_MAC&t;&t;BIT_0S&t;&t;/* MAC Config: 0=2 MACs / 1=1 MAC*/
multiline_comment|/*&t;B2_CHIP_ID&t; 8 bit &t;Chip Identification Number */
DECL|macro|CHIP_ID_GENESIS
mdefine_line|#define CHIP_ID_GENESIS&t;&t;0x0a&t;/* Chip ID for GENESIS */
DECL|macro|CHIP_ID_YUKON
mdefine_line|#define CHIP_ID_YUKON&t;&t;0xb0&t;/* Chip ID for YUKON */
DECL|macro|CHIP_ID_YUKON_LITE
mdefine_line|#define CHIP_ID_YUKON_LITE&t;0xb1&t;/* Chip ID for YUKON-Lite (Rev. A1) */
DECL|macro|CHIP_ID_YUKON_LP
mdefine_line|#define CHIP_ID_YUKON_LP&t;0xb2&t;/* Chip ID for YUKON-LP */
multiline_comment|/*&t;B2_FAR&t;&t;32 bit&t;Flash-Prom Addr Reg/Cnt */
DECL|macro|FAR_ADDR
mdefine_line|#define FAR_ADDR&t;&t;0x1ffffL&t;/* Bit 16.. 0:&t;FPROM Address mask */
multiline_comment|/*&t;B2_LD_CRTL&t; 8 bit&t;EPROM loader control register */
multiline_comment|/*&t;Bits are currently reserved */
multiline_comment|/*&t;B2_LD_TEST&t; 8 bit&t;EPROM loader test register */
multiline_comment|/* Bit 7.. 4:&t;reserved */
DECL|macro|LD_T_ON
mdefine_line|#define LD_T_ON&t;&t;&t;BIT_3S&t;/* Loader Test mode on */
DECL|macro|LD_T_OFF
mdefine_line|#define LD_T_OFF&t;&t;BIT_2S&t;/* Loader Test mode off */
DECL|macro|LD_T_STEP
mdefine_line|#define LD_T_STEP&t;&t;BIT_1S&t;/* Decrement FPROM addr. Counter */
DECL|macro|LD_START
mdefine_line|#define LD_START&t;&t;BIT_0S&t;/* Start loading FPROM */
multiline_comment|/*&n; *&t;Timer Section&n; */
multiline_comment|/*&t;B2_TI_CRTL&t; 8 bit&t;Timer control */
multiline_comment|/*&t;B2_IRQM_CTRL&t; 8 bit&t;IRQ Moderation Timer Control */
multiline_comment|/* Bit 7.. 3:&t;reserved */
DECL|macro|TIM_START
mdefine_line|#define TIM_START&t;&t;BIT_2S&t;/* Start Timer */
DECL|macro|TIM_STOP
mdefine_line|#define TIM_STOP&t;&t;BIT_1S&t;/* Stop  Timer */
DECL|macro|TIM_CLR_IRQ
mdefine_line|#define TIM_CLR_IRQ&t;&t;BIT_0S&t;/* Clear Timer IRQ (!IRQM) */
multiline_comment|/*&t;B2_TI_TEST&t; 8 Bit&t;Timer Test */
multiline_comment|/*&t;B2_IRQM_TEST&t; 8 bit&t;IRQ Moderation Timer Test */
multiline_comment|/*&t;B28_DPT_TST&t; 8 bit&t;Descriptor Poll Timer Test Reg */
multiline_comment|/* Bit 7.. 3:&t;reserved */
DECL|macro|TIM_T_ON
mdefine_line|#define TIM_T_ON&t;&t;BIT_2S&t;/* Test mode on */
DECL|macro|TIM_T_OFF
mdefine_line|#define TIM_T_OFF&t;&t;BIT_1S&t;/* Test mode off */
DECL|macro|TIM_T_STEP
mdefine_line|#define TIM_T_STEP&t;&t;BIT_0S&t;/* Test step */
multiline_comment|/*&t;B28_DPT_INI&t;32 bit&t;Descriptor Poll Timer Init Val */
multiline_comment|/*&t;B28_DPT_VAL&t;32 bit&t;Descriptor Poll Timer Curr Val */
multiline_comment|/* Bit 31..24:&t;reserved */
DECL|macro|DPT_MSK
mdefine_line|#define DPT_MSK&t;&t;0x00ffffffL&t;/* Bit 23.. 0:&t;Desc Poll Timer Bits */
multiline_comment|/*&t;B28_DPT_CTRL&t; 8 bit&t;Descriptor Poll Timer Ctrl Reg */
multiline_comment|/* Bit  7.. 2:&t;reserved */
DECL|macro|DPT_START
mdefine_line|#define DPT_START&t;&t;BIT_1S&t;/* Start Descriptor Poll Timer */
DECL|macro|DPT_STOP
mdefine_line|#define DPT_STOP&t;&t;BIT_0S&t;/* Stop  Descriptor Poll Timer */
multiline_comment|/*&t;B2_E_3&t;&t;&t; 8 bit &t;lower 4 bits used for HW self test result */
DECL|macro|B2_E3_RES_MASK
mdefine_line|#define B2_E3_RES_MASK&t;0x0f
multiline_comment|/*&t;B2_TST_CTRL1&t; 8 bit&t;Test Control Register 1 */
DECL|macro|TST_FRC_DPERR_MR
mdefine_line|#define TST_FRC_DPERR_MR&t;BIT_7S&t;/* force DATAPERR on MST RD */
DECL|macro|TST_FRC_DPERR_MW
mdefine_line|#define TST_FRC_DPERR_MW&t;BIT_6S&t;/* force DATAPERR on MST WR */
DECL|macro|TST_FRC_DPERR_TR
mdefine_line|#define TST_FRC_DPERR_TR&t;BIT_5S&t;/* force DATAPERR on TRG RD */
DECL|macro|TST_FRC_DPERR_TW
mdefine_line|#define TST_FRC_DPERR_TW&t;BIT_4S&t;/* force DATAPERR on TRG WR */
DECL|macro|TST_FRC_APERR_M
mdefine_line|#define TST_FRC_APERR_M&t;&t;BIT_3S&t;/* force ADDRPERR on MST */
DECL|macro|TST_FRC_APERR_T
mdefine_line|#define TST_FRC_APERR_T&t;&t;BIT_2S&t;/* force ADDRPERR on TRG */
DECL|macro|TST_CFG_WRITE_ON
mdefine_line|#define TST_CFG_WRITE_ON&t;BIT_1S&t;/* Enable  Config Reg WR */
DECL|macro|TST_CFG_WRITE_OFF
mdefine_line|#define TST_CFG_WRITE_OFF&t;BIT_0S&t;/* Disable Config Reg WR */
multiline_comment|/*&t;B2_TST_CTRL2&t; 8 bit&t;Test Control Register 2 */
multiline_comment|/* Bit 7.. 4:&t;reserved */
multiline_comment|/* force the following error on the next master read/write&t;*/
DECL|macro|TST_FRC_DPERR_MR64
mdefine_line|#define TST_FRC_DPERR_MR64&t;BIT_3S&t;/* DataPERR RD 64&t;*/
DECL|macro|TST_FRC_DPERR_MW64
mdefine_line|#define TST_FRC_DPERR_MW64&t;BIT_2S&t;/* DataPERR WR 64&t;*/
DECL|macro|TST_FRC_APERR_1M64
mdefine_line|#define TST_FRC_APERR_1M64&t;BIT_1S&t;/* AddrPERR on 1. phase */
DECL|macro|TST_FRC_APERR_2M64
mdefine_line|#define TST_FRC_APERR_2M64&t;BIT_0S&t;/* AddrPERR on 2. phase */
multiline_comment|/*&t;B2_GP_IO&t;32 bit&t;General Purpose I/O Register */
multiline_comment|/* Bit 31..26:&t;reserved */
DECL|macro|GP_DIR_9
mdefine_line|#define GP_DIR_9&t;BIT_25&t;/* IO_9 direct, 0=In/1=Out */
DECL|macro|GP_DIR_8
mdefine_line|#define GP_DIR_8&t;BIT_24&t;/* IO_8 direct, 0=In/1=Out */
DECL|macro|GP_DIR_7
mdefine_line|#define GP_DIR_7&t;BIT_23&t;/* IO_7 direct, 0=In/1=Out */
DECL|macro|GP_DIR_6
mdefine_line|#define GP_DIR_6&t;BIT_22&t;/* IO_6 direct, 0=In/1=Out */
DECL|macro|GP_DIR_5
mdefine_line|#define GP_DIR_5&t;BIT_21&t;/* IO_5 direct, 0=In/1=Out */
DECL|macro|GP_DIR_4
mdefine_line|#define GP_DIR_4&t;BIT_20&t;/* IO_4 direct, 0=In/1=Out */
DECL|macro|GP_DIR_3
mdefine_line|#define GP_DIR_3&t;BIT_19&t;/* IO_3 direct, 0=In/1=Out */
DECL|macro|GP_DIR_2
mdefine_line|#define GP_DIR_2&t;BIT_18&t;/* IO_2 direct, 0=In/1=Out */
DECL|macro|GP_DIR_1
mdefine_line|#define GP_DIR_1&t;BIT_17&t;/* IO_1 direct, 0=In/1=Out */
DECL|macro|GP_DIR_0
mdefine_line|#define GP_DIR_0&t;BIT_16&t;/* IO_0 direct, 0=In/1=Out */
multiline_comment|/* Bit 15..10:&t;reserved */
DECL|macro|GP_IO_9
mdefine_line|#define GP_IO_9&t;&t;BIT_9&t;/* IO_9 pin */
DECL|macro|GP_IO_8
mdefine_line|#define GP_IO_8&t;&t;BIT_8&t;/* IO_8 pin */
DECL|macro|GP_IO_7
mdefine_line|#define GP_IO_7&t;&t;BIT_7&t;/* IO_7 pin */
DECL|macro|GP_IO_6
mdefine_line|#define GP_IO_6&t;&t;BIT_6&t;/* IO_6 pin */
DECL|macro|GP_IO_5
mdefine_line|#define GP_IO_5&t;&t;BIT_5&t;/* IO_5 pin */
DECL|macro|GP_IO_4
mdefine_line|#define GP_IO_4&t;&t;BIT_4&t;/* IO_4 pin */
DECL|macro|GP_IO_3
mdefine_line|#define GP_IO_3&t;&t;BIT_3&t;/* IO_3 pin */
DECL|macro|GP_IO_2
mdefine_line|#define GP_IO_2&t;&t;BIT_2&t;/* IO_2 pin */
DECL|macro|GP_IO_1
mdefine_line|#define GP_IO_1&t;&t;BIT_1&t;/* IO_1 pin */
DECL|macro|GP_IO_0
mdefine_line|#define GP_IO_0&t;&t;BIT_0&t;/* IO_0 pin */
multiline_comment|/*&t;B2_I2C_CTRL&t;32 bit&t;I2C HW Control Register */
DECL|macro|I2C_FLAG
mdefine_line|#define I2C_FLAG&t;&t;BIT_31&t;&t;/* Start read/write if WR */
DECL|macro|I2C_ADDR
mdefine_line|#define I2C_ADDR&t;&t;(0x7fffL&lt;&lt;16)&t;/* Bit 30..16:&t;Addr to be RD/WR */
DECL|macro|I2C_DEV_SEL
mdefine_line|#define I2C_DEV_SEL&t;&t;(0x7fL&lt;&lt;9)&t;&t;/* Bit 15.. 9:&t;I2C Device Select */
multiline_comment|/* Bit&t;8.. 5:&t;reserved&t;*/
DECL|macro|I2C_BURST_LEN
mdefine_line|#define I2C_BURST_LEN&t;BIT_4&t;&t;/* Burst Len, 1/4 bytes */
DECL|macro|I2C_DEV_SIZE
mdefine_line|#define I2C_DEV_SIZE&t;(7L&lt;&lt;1)&t;&t;/* Bit&t;3.. 1:&t;I2C Device Size&t;*/
DECL|macro|I2C_025K_DEV
mdefine_line|#define I2C_025K_DEV&t;(0L&lt;&lt;1)&t;&t;/*&t;&t;0: 256 Bytes or smal. */
DECL|macro|I2C_05K_DEV
mdefine_line|#define I2C_05K_DEV&t;&t;(1L&lt;&lt;1)&t;&t;/* &t;&t;1: 512&t;Bytes&t;*/
DECL|macro|I2C_1K_DEV
mdefine_line|#define I2C_1K_DEV&t;&t;(2L&lt;&lt;1)&t;&t;/*&t;&t;2: 1024 Bytes&t;*/
DECL|macro|I2C_2K_DEV
mdefine_line|#define I2C_2K_DEV&t;&t;(3L&lt;&lt;1)&t;&t;/*&t;&t;3: 2048&t;Bytes&t;*/
DECL|macro|I2C_4K_DEV
mdefine_line|#define I2C_4K_DEV&t;&t;(4L&lt;&lt;1)&t;&t;/*&t;&t;4: 4096 Bytes&t;*/
DECL|macro|I2C_8K_DEV
mdefine_line|#define I2C_8K_DEV&t;&t;(5L&lt;&lt;1)&t;&t;/*&t;&t;5: 8192 Bytes&t;*/
DECL|macro|I2C_16K_DEV
mdefine_line|#define I2C_16K_DEV&t;&t;(6L&lt;&lt;1)&t;&t;/*&t;&t;6: 16384 Bytes&t;*/
DECL|macro|I2C_32K_DEV
mdefine_line|#define I2C_32K_DEV&t;&t;(7L&lt;&lt;1)&t;&t;/*&t;&t;7: 32768 Bytes&t;*/
DECL|macro|I2C_STOP
mdefine_line|#define I2C_STOP&t;&t;BIT_0&t;&t;/* Interrupt I2C transfer */
multiline_comment|/*&t;B2_I2C_IRQ&t;32 bit&t;I2C HW IRQ Register */
multiline_comment|/* Bit 31.. 1&t;reserved */
DECL|macro|I2C_CLR_IRQ
mdefine_line|#define I2C_CLR_IRQ&t;&t;BIT_0&t;/* Clear I2C IRQ */
multiline_comment|/*&t;B2_I2C_SW&t;32 bit (8 bit access)&t;I2C HW SW Port Register */
multiline_comment|/* Bit  7.. 3:&t;reserved */
DECL|macro|I2C_DATA_DIR
mdefine_line|#define I2C_DATA_DIR&t;BIT_2S&t;&t;/* direction of I2C_DATA */
DECL|macro|I2C_DATA
mdefine_line|#define I2C_DATA&t;&t;BIT_1S&t;&t;/* I2C Data Port&t;*/
DECL|macro|I2C_CLK
mdefine_line|#define I2C_CLK&t;&t;&t;BIT_0S&t;&t;/* I2C Clock Port&t;*/
multiline_comment|/*&n; * I2C Address&n; */
DECL|macro|I2C_SENS_ADDR
mdefine_line|#define I2C_SENS_ADDR&t;LM80_ADDR&t;/* I2C Sensor Address, (Volt and Temp)*/
multiline_comment|/*&t;B2_BSC_CTRL&t; 8 bit&t;Blink Source Counter Control */
multiline_comment|/* Bit  7.. 2:&t;reserved */
DECL|macro|BSC_START
mdefine_line|#define BSC_START&t;BIT_1S&t;&t;/* Start Blink Source Counter */
DECL|macro|BSC_STOP
mdefine_line|#define BSC_STOP&t;BIT_0S&t;&t;/* Stop  Blink Source Counter */
multiline_comment|/*&t;B2_BSC_STAT&t; 8 bit&t;Blink Source Counter Status */
multiline_comment|/* Bit  7.. 1:&t;reserved */
DECL|macro|BSC_SRC
mdefine_line|#define BSC_SRC&t;&t;BIT_0S&t;&t;/* Blink Source, 0=Off / 1=On */
multiline_comment|/*&t;B2_BSC_TST&t;16 bit&t;Blink Source Counter Test Reg */
DECL|macro|BSC_T_ON
mdefine_line|#define BSC_T_ON&t;BIT_2S&t;&t;/* Test mode on */
DECL|macro|BSC_T_OFF
mdefine_line|#define BSC_T_OFF&t;BIT_1S&t;&t;/* Test mode off */
DECL|macro|BSC_T_STEP
mdefine_line|#define BSC_T_STEP&t;BIT_0S&t;&t;/* Test step */
multiline_comment|/*&t;B3_RAM_ADDR&t;32 bit&t;RAM Address, to read or write */
multiline_comment|/* Bit 31..19:&t;reserved */
DECL|macro|RAM_ADR_RAN
mdefine_line|#define RAM_ADR_RAN&t;0x0007ffffL&t;/* Bit 18.. 0:&t;RAM Address Range */
multiline_comment|/* RAM Interface Registers */
multiline_comment|/*&t;B3_RI_CTRL&t;16 bit&t;RAM Iface Control Register */
multiline_comment|/* Bit 15..10:&t;reserved */
DECL|macro|RI_CLR_RD_PERR
mdefine_line|#define RI_CLR_RD_PERR&t;BIT_9S&t;/* Clear IRQ RAM Read Parity Err */
DECL|macro|RI_CLR_WR_PERR
mdefine_line|#define RI_CLR_WR_PERR&t;BIT_8S&t;/* Clear IRQ RAM Write Parity Err*/
multiline_comment|/* Bit&t;7.. 2:&t;reserved */
DECL|macro|RI_RST_CLR
mdefine_line|#define RI_RST_CLR&t;&t;BIT_1S&t;/* Clear RAM Interface Reset */
DECL|macro|RI_RST_SET
mdefine_line|#define RI_RST_SET&t;&t;BIT_0S&t;/* Set   RAM Interface Reset */
multiline_comment|/*&t;B3_RI_TEST&t; 8 bit&t;RAM Iface Test Register */
multiline_comment|/* Bit 15.. 4:&t;reserved */
DECL|macro|RI_T_EV
mdefine_line|#define RI_T_EV&t;&t;&t;BIT_3S&t;/* Timeout Event occured */
DECL|macro|RI_T_ON
mdefine_line|#define RI_T_ON&t;&t;&t;BIT_2S&t;/* Timeout Timer Test On */
DECL|macro|RI_T_OFF
mdefine_line|#define RI_T_OFF&t;&t;BIT_1S&t;/* Timeout Timer Test Off */
DECL|macro|RI_T_STEP
mdefine_line|#define RI_T_STEP&t;&t;BIT_0S&t;/* Timeout Timer Step */
multiline_comment|/* MAC Arbiter Registers */
multiline_comment|/*&t;B3_MA_TO_CTRL&t;16 bit&t;MAC Arbiter Timeout Ctrl Reg */
multiline_comment|/* Bit 15.. 4:&t;reserved */
DECL|macro|MA_FOE_ON
mdefine_line|#define MA_FOE_ON&t;&t;BIT_3S&t;/* XMAC Fast Output Enable ON */
DECL|macro|MA_FOE_OFF
mdefine_line|#define MA_FOE_OFF&t;&t;BIT_2S&t;/* XMAC Fast Output Enable OFF */
DECL|macro|MA_RST_CLR
mdefine_line|#define MA_RST_CLR&t;&t;BIT_1S&t;/* Clear MAC Arbiter Reset */
DECL|macro|MA_RST_SET
mdefine_line|#define MA_RST_SET&t;&t;BIT_0S&t;/* Set   MAC Arbiter Reset */
multiline_comment|/*&t;B3_MA_RC_CTRL&t;16 bit&t;MAC Arbiter Recovery Ctrl Reg */
multiline_comment|/* Bit 15.. 8:&t;reserved */
DECL|macro|MA_ENA_REC_TX2
mdefine_line|#define MA_ENA_REC_TX2&t;BIT_7S&t;/* Enable  Recovery Timer TX2 */
DECL|macro|MA_DIS_REC_TX2
mdefine_line|#define MA_DIS_REC_TX2&t;BIT_6S&t;/* Disable Recovery Timer TX2 */
DECL|macro|MA_ENA_REC_TX1
mdefine_line|#define MA_ENA_REC_TX1&t;BIT_5S&t;/* Enable  Recovery Timer TX1 */
DECL|macro|MA_DIS_REC_TX1
mdefine_line|#define MA_DIS_REC_TX1&t;BIT_4S&t;/* Disable Recovery Timer TX1 */
DECL|macro|MA_ENA_REC_RX2
mdefine_line|#define MA_ENA_REC_RX2&t;BIT_3S&t;/* Enable  Recovery Timer RX2 */
DECL|macro|MA_DIS_REC_RX2
mdefine_line|#define MA_DIS_REC_RX2&t;BIT_2S&t;/* Disable Recovery Timer RX2 */
DECL|macro|MA_ENA_REC_RX1
mdefine_line|#define MA_ENA_REC_RX1&t;BIT_1S&t;/* Enable  Recovery Timer RX1 */
DECL|macro|MA_DIS_REC_RX1
mdefine_line|#define MA_DIS_REC_RX1&t;BIT_0S&t;/* Disable Recovery Timer RX1 */
multiline_comment|/* Packet Arbiter Registers */
multiline_comment|/*&t;B3_PA_CTRL&t;16 bit&t;Packet Arbiter Ctrl Register */
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|PA_CLR_TO_TX2
mdefine_line|#define PA_CLR_TO_TX2&t;BIT_13S&t;/* Clear IRQ Packet Timeout TX2 */
DECL|macro|PA_CLR_TO_TX1
mdefine_line|#define PA_CLR_TO_TX1&t;BIT_12S&t;/* Clear IRQ Packet Timeout TX1 */
DECL|macro|PA_CLR_TO_RX2
mdefine_line|#define PA_CLR_TO_RX2&t;BIT_11S&t;/* Clear IRQ Packet Timeout RX2 */
DECL|macro|PA_CLR_TO_RX1
mdefine_line|#define PA_CLR_TO_RX1&t;BIT_10S&t;/* Clear IRQ Packet Timeout RX1 */
DECL|macro|PA_ENA_TO_TX2
mdefine_line|#define PA_ENA_TO_TX2&t;BIT_9S&t;/* Enable  Timeout Timer TX2 */
DECL|macro|PA_DIS_TO_TX2
mdefine_line|#define PA_DIS_TO_TX2&t;BIT_8S&t;/* Disable Timeout Timer TX2 */
DECL|macro|PA_ENA_TO_TX1
mdefine_line|#define PA_ENA_TO_TX1&t;BIT_7S&t;/* Enable  Timeout Timer TX1 */
DECL|macro|PA_DIS_TO_TX1
mdefine_line|#define PA_DIS_TO_TX1&t;BIT_6S&t;/* Disable Timeout Timer TX1 */
DECL|macro|PA_ENA_TO_RX2
mdefine_line|#define PA_ENA_TO_RX2&t;BIT_5S&t;/* Enable  Timeout Timer RX2 */
DECL|macro|PA_DIS_TO_RX2
mdefine_line|#define PA_DIS_TO_RX2&t;BIT_4S&t;/* Disable Timeout Timer RX2 */
DECL|macro|PA_ENA_TO_RX1
mdefine_line|#define PA_ENA_TO_RX1&t;BIT_3S&t;/* Enable  Timeout Timer RX1 */
DECL|macro|PA_DIS_TO_RX1
mdefine_line|#define PA_DIS_TO_RX1&t;BIT_2S&t;/* Disable Timeout Timer RX1 */
DECL|macro|PA_RST_CLR
mdefine_line|#define PA_RST_CLR&t;&t;BIT_1S&t;/* Clear MAC Arbiter Reset */
DECL|macro|PA_RST_SET
mdefine_line|#define PA_RST_SET&t;&t;BIT_0S&t;/* Set   MAC Arbiter Reset */
DECL|macro|PA_ENA_TO_ALL
mdefine_line|#define PA_ENA_TO_ALL&t;(PA_ENA_TO_RX1 | PA_ENA_TO_RX2 |&bslash;&n;&t;&t;&t;&t;&t;&t;PA_ENA_TO_TX1 | PA_ENA_TO_TX2)
multiline_comment|/* Rx/Tx Path related Arbiter Test Registers */
multiline_comment|/*&t;B3_MA_TO_TEST&t;16 bit&t;MAC Arbiter Timeout Test Reg */
multiline_comment|/*&t;B3_MA_RC_TEST&t;16 bit&t;MAC Arbiter Recovery Test Reg */
multiline_comment|/*&t;B3_PA_TEST&t;16 bit&t;Packet Arbiter Test Register */
multiline_comment|/*&t;&t;&t;Bit 15, 11, 7, and 3 are reserved in B3_PA_TEST */
DECL|macro|TX2_T_EV
mdefine_line|#define TX2_T_EV&t;BIT_15S&t;&t;/* TX2 Timeout/Recv Event occured */
DECL|macro|TX2_T_ON
mdefine_line|#define TX2_T_ON&t;BIT_14S&t;&t;/* TX2 Timeout/Recv Timer Test On */
DECL|macro|TX2_T_OFF
mdefine_line|#define TX2_T_OFF&t;BIT_13S&t;&t;/* TX2 Timeout/Recv Timer Tst Off */
DECL|macro|TX2_T_STEP
mdefine_line|#define TX2_T_STEP&t;BIT_12S&t;&t;/* TX2 Timeout/Recv Timer Step */
DECL|macro|TX1_T_EV
mdefine_line|#define TX1_T_EV&t;BIT_11S&t;&t;/* TX1 Timeout/Recv Event occured */
DECL|macro|TX1_T_ON
mdefine_line|#define TX1_T_ON&t;BIT_10S&t;&t;/* TX1 Timeout/Recv Timer Test On */
DECL|macro|TX1_T_OFF
mdefine_line|#define TX1_T_OFF&t;BIT_9S&t;&t;/* TX1 Timeout/Recv Timer Tst Off */
DECL|macro|TX1_T_STEP
mdefine_line|#define TX1_T_STEP&t;BIT_8S&t;&t;/* TX1 Timeout/Recv Timer Step */
DECL|macro|RX2_T_EV
mdefine_line|#define RX2_T_EV&t;BIT_7S&t;&t;/* RX2 Timeout/Recv Event occured */
DECL|macro|RX2_T_ON
mdefine_line|#define RX2_T_ON&t;BIT_6S&t;&t;/* RX2 Timeout/Recv Timer Test On */
DECL|macro|RX2_T_OFF
mdefine_line|#define RX2_T_OFF&t;BIT_5S&t;&t;/* RX2 Timeout/Recv Timer Tst Off */
DECL|macro|RX2_T_STEP
mdefine_line|#define RX2_T_STEP&t;BIT_4S&t;&t;/* RX2 Timeout/Recv Timer Step */
DECL|macro|RX1_T_EV
mdefine_line|#define RX1_T_EV&t;BIT_3S&t;&t;/* RX1 Timeout/Recv Event occured */
DECL|macro|RX1_T_ON
mdefine_line|#define RX1_T_ON&t;BIT_2S&t;&t;/* RX1 Timeout/Recv Timer Test On */
DECL|macro|RX1_T_OFF
mdefine_line|#define RX1_T_OFF&t;BIT_1S&t;&t;/* RX1 Timeout/Recv Timer Tst Off */
DECL|macro|RX1_T_STEP
mdefine_line|#define RX1_T_STEP&t;BIT_0S&t;&t;/* RX1 Timeout/Recv Timer Step */
multiline_comment|/* Transmit Arbiter Registers MAC 1 and 2, use MR_ADDR() to access */
multiline_comment|/*&t;TXA_ITI_INI&t;32 bit&t;Tx Arb Interval Timer Init Val */
multiline_comment|/*&t;TXA_ITI_VAL&t;32 bit&t;Tx Arb Interval Timer Value */
multiline_comment|/*&t;TXA_LIM_INI&t;32 bit&t;Tx Arb Limit Counter Init Val */
multiline_comment|/*&t;TXA_LIM_VAL&t;32 bit&t;Tx Arb Limit Counter Value */
multiline_comment|/* Bit 31..24:&t;reserved */
DECL|macro|TXA_MAX_VAL
mdefine_line|#define TXA_MAX_VAL&t;0x00ffffffUL/* Bit 23.. 0:&t;Max TXA Timer/Cnt Val */
multiline_comment|/*&t;TXA_CTRL&t; 8 bit&t;Tx Arbiter Control Register */
DECL|macro|TXA_ENA_FSYNC
mdefine_line|#define TXA_ENA_FSYNC&t;BIT_7S&t;/* Enable  force of sync Tx queue */
DECL|macro|TXA_DIS_FSYNC
mdefine_line|#define TXA_DIS_FSYNC&t;BIT_6S&t;/* Disable force of sync Tx queue */
DECL|macro|TXA_ENA_ALLOC
mdefine_line|#define TXA_ENA_ALLOC&t;BIT_5S&t;/* Enable  alloc of free bandwidth */
DECL|macro|TXA_DIS_ALLOC
mdefine_line|#define TXA_DIS_ALLOC&t;BIT_4S&t;/* Disable alloc of free bandwidth */
DECL|macro|TXA_START_RC
mdefine_line|#define TXA_START_RC&t;BIT_3S&t;/* Start sync Rate Control */
DECL|macro|TXA_STOP_RC
mdefine_line|#define TXA_STOP_RC&t;&t;BIT_2S&t;/* Stop  sync Rate Control */
DECL|macro|TXA_ENA_ARB
mdefine_line|#define TXA_ENA_ARB&t;&t;BIT_1S&t;/* Enable  Tx Arbiter */
DECL|macro|TXA_DIS_ARB
mdefine_line|#define TXA_DIS_ARB&t;&t;BIT_0S&t;/* Disable Tx Arbiter */
multiline_comment|/*&t;TXA_TEST&t; 8 bit&t;Tx Arbiter Test Register */
multiline_comment|/* Bit 7.. 6:&t;reserved */
DECL|macro|TXA_INT_T_ON
mdefine_line|#define TXA_INT_T_ON&t;BIT_5S&t;/* Tx Arb Interval Timer Test On */
DECL|macro|TXA_INT_T_OFF
mdefine_line|#define TXA_INT_T_OFF&t;BIT_4S&t;/* Tx Arb Interval Timer Test Off */
DECL|macro|TXA_INT_T_STEP
mdefine_line|#define TXA_INT_T_STEP&t;BIT_3S&t;/* Tx Arb Interval Timer Step */
DECL|macro|TXA_LIM_T_ON
mdefine_line|#define TXA_LIM_T_ON&t;BIT_2S&t;/* Tx Arb Limit Timer Test On */
DECL|macro|TXA_LIM_T_OFF
mdefine_line|#define TXA_LIM_T_OFF&t;BIT_1S&t;/* Tx Arb Limit Timer Test Off */
DECL|macro|TXA_LIM_T_STEP
mdefine_line|#define TXA_LIM_T_STEP&t;BIT_0S&t;/* Tx Arb Limit Timer Step */
multiline_comment|/*&t;TXA_STAT&t; 8 bit&t;Tx Arbiter Status Register */
multiline_comment|/* Bit 7.. 1:&t;reserved */
DECL|macro|TXA_PRIO_XS
mdefine_line|#define TXA_PRIO_XS&t;&t;BIT_0S&t;/* sync queue has prio to send */
multiline_comment|/*&t;Q_BC&t;32 bit&t;Current Byte Counter */
multiline_comment|/* Bit 31..16:&t;reserved */
DECL|macro|BC_MAX
mdefine_line|#define BC_MAX&t;&t;&t;0xffff&t;/* Bit 15.. 0:&t;Byte counter */
multiline_comment|/* BMU Control Status Registers */
multiline_comment|/*&t;B0_R1_CSR&t;32 bit&t;BMU Ctrl/Stat Rx Queue 1 */
multiline_comment|/*&t;B0_R2_CSR&t;32 bit&t;BMU Ctrl/Stat Rx Queue 2 */
multiline_comment|/*&t;B0_XA1_CSR&t;32 bit&t;BMU Ctrl/Stat Sync Tx Queue 1 */
multiline_comment|/*&t;B0_XS1_CSR&t;32 bit&t;BMU Ctrl/Stat Async Tx Queue 1 */
multiline_comment|/*&t;B0_XA2_CSR&t;32 bit&t;BMU Ctrl/Stat Sync Tx Queue 2 */
multiline_comment|/*&t;B0_XS2_CSR&t;32 bit&t;BMU Ctrl/Stat Async Tx Queue 2 */
multiline_comment|/*&t;Q_CSR&t;&t;32 bit&t;BMU Control/Status Register */
multiline_comment|/* Bit 31..25:&t;reserved */
DECL|macro|CSR_SV_IDLE
mdefine_line|#define CSR_SV_IDLE&t;&t;BIT_24&t;&t;/* BMU SM Idle */
multiline_comment|/* Bit 23..22:&t;reserved */
DECL|macro|CSR_DESC_CLR
mdefine_line|#define CSR_DESC_CLR&t;BIT_21&t;&t;/* Clear Reset for Descr */
DECL|macro|CSR_DESC_SET
mdefine_line|#define CSR_DESC_SET&t;BIT_20&t;&t;/* Set   Reset for Descr */
DECL|macro|CSR_FIFO_CLR
mdefine_line|#define CSR_FIFO_CLR&t;BIT_19&t;&t;/* Clear Reset for FIFO */
DECL|macro|CSR_FIFO_SET
mdefine_line|#define CSR_FIFO_SET&t;BIT_18&t;&t;/* Set   Reset for FIFO */
DECL|macro|CSR_HPI_RUN
mdefine_line|#define CSR_HPI_RUN&t;&t;BIT_17&t;&t;/* Release HPI SM */
DECL|macro|CSR_HPI_RST
mdefine_line|#define CSR_HPI_RST&t;&t;BIT_16&t;&t;/* Reset   HPI SM to Idle */
DECL|macro|CSR_SV_RUN
mdefine_line|#define CSR_SV_RUN&t;&t;BIT_15&t;&t;/* Release Supervisor SM */
DECL|macro|CSR_SV_RST
mdefine_line|#define CSR_SV_RST&t;&t;BIT_14&t;&t;/* Reset   Supervisor SM */
DECL|macro|CSR_DREAD_RUN
mdefine_line|#define CSR_DREAD_RUN&t;BIT_13&t;&t;/* Release Descr Read SM */
DECL|macro|CSR_DREAD_RST
mdefine_line|#define CSR_DREAD_RST&t;BIT_12&t;&t;/* Reset   Descr Read SM */
DECL|macro|CSR_DWRITE_RUN
mdefine_line|#define CSR_DWRITE_RUN&t;BIT_11&t;&t;/* Release Descr Write SM */
DECL|macro|CSR_DWRITE_RST
mdefine_line|#define CSR_DWRITE_RST&t;BIT_10&t;&t;/* Reset   Descr Write SM */
DECL|macro|CSR_TRANS_RUN
mdefine_line|#define CSR_TRANS_RUN&t;BIT_9&t;&t;/* Release Transfer SM */
DECL|macro|CSR_TRANS_RST
mdefine_line|#define CSR_TRANS_RST&t;BIT_8&t;&t;/* Reset   Transfer SM */
DECL|macro|CSR_ENA_POL
mdefine_line|#define CSR_ENA_POL&t;&t;BIT_7&t;&t;/* Enable  Descr Polling */
DECL|macro|CSR_DIS_POL
mdefine_line|#define CSR_DIS_POL&t;&t;BIT_6&t;&t;/* Disable Descr Polling */
DECL|macro|CSR_STOP
mdefine_line|#define CSR_STOP&t;&t;BIT_5&t;&t;/* Stop  Rx/Tx Queue */
DECL|macro|CSR_START
mdefine_line|#define CSR_START&t;&t;BIT_4&t;&t;/* Start Rx/Tx Queue */
DECL|macro|CSR_IRQ_CL_P
mdefine_line|#define CSR_IRQ_CL_P&t;BIT_3&t;&t;/* (Rx)&t;Clear Parity IRQ */
DECL|macro|CSR_IRQ_CL_B
mdefine_line|#define CSR_IRQ_CL_B&t;BIT_2&t;&t;/* Clear EOB IRQ */
DECL|macro|CSR_IRQ_CL_F
mdefine_line|#define CSR_IRQ_CL_F&t;BIT_1&t;&t;/* Clear EOF IRQ */
DECL|macro|CSR_IRQ_CL_C
mdefine_line|#define CSR_IRQ_CL_C&t;BIT_0&t;&t;/* Clear ERR IRQ */
DECL|macro|CSR_SET_RESET
mdefine_line|#define CSR_SET_RESET&t;(CSR_DESC_SET | CSR_FIFO_SET | CSR_HPI_RST |&bslash;&n;&t;&t;&t;&t;&t;&t;CSR_SV_RST | CSR_DREAD_RST | CSR_DWRITE_RST |&bslash;&n;&t;&t;&t;&t;&t;&t;CSR_TRANS_RST)
DECL|macro|CSR_CLR_RESET
mdefine_line|#define CSR_CLR_RESET&t;(CSR_DESC_CLR | CSR_FIFO_CLR | CSR_HPI_RUN |&bslash;&n;&t;&t;&t;&t;&t;&t;CSR_SV_RUN | CSR_DREAD_RUN | CSR_DWRITE_RUN |&bslash;&n;&t;&t;&t;&t;&t;&t;CSR_TRANS_RUN)
multiline_comment|/*&t;Q_F&t;32 bit&t;Flag Register */
multiline_comment|/* Bit 31..28:&t;reserved */
DECL|macro|F_ALM_FULL
mdefine_line|#define F_ALM_FULL&t;&t;BIT_27&t;&t;/* Rx FIFO: almost full */
DECL|macro|F_EMPTY
mdefine_line|#define F_EMPTY&t;&t;&t;BIT_27&t;&t;/* Tx FIFO: empty flag */
DECL|macro|F_FIFO_EOF
mdefine_line|#define F_FIFO_EOF&t;&t;BIT_26&t;&t;/* Tag (EOF Flag) bit in FIFO */
DECL|macro|F_WM_REACHED
mdefine_line|#define F_WM_REACHED&t;BIT_25&t;&t;/* Watermark reached */
multiline_comment|/* reserved */
DECL|macro|F_FIFO_LEVEL
mdefine_line|#define F_FIFO_LEVEL&t;(0x1fL&lt;&lt;16)&t;/* Bit 23..16:&t;# of Qwords in FIFO */
multiline_comment|/* Bit 15..11: &t;reserved */
DECL|macro|F_WATER_MARK
mdefine_line|#define F_WATER_MARK&t;0x0007ffL&t;/* Bit 10.. 0:&t;Watermark */
multiline_comment|/*&t;Q_T1&t;32 bit&t;Test Register 1 */
multiline_comment|/*&t;&t;Holds four State Machine control Bytes */
DECL|macro|SM_CRTL_SV_MSK
mdefine_line|#define SM_CRTL_SV_MSK&t;(0xffL&lt;&lt;24)&t;/* Bit 31..24:&t;Control Supervisor SM */
DECL|macro|SM_CRTL_RD_MSK
mdefine_line|#define SM_CRTL_RD_MSK&t;(0xffL&lt;&lt;16)&t;/* Bit 23..16:&t;Control Read Desc SM */
DECL|macro|SM_CRTL_WR_MSK
mdefine_line|#define SM_CRTL_WR_MSK&t;(0xffL&lt;&lt;8)&t;/* Bit 15.. 8:&t;Control Write Desc SM */
DECL|macro|SM_CRTL_TR_MSK
mdefine_line|#define SM_CRTL_TR_MSK&t;0xffL&t;&t;/* Bit&t;7.. 0:&t;Control Transfer SM */
multiline_comment|/*&t;Q_T1_TR&t; 8 bit&t;Test Register 1 Transfer SM */
multiline_comment|/*&t;Q_T1_WR&t; 8 bit&t;Test Register 1 Write Descriptor SM */
multiline_comment|/*&t;Q_T1_RD&t; 8 bit&t;Test Register 1 Read Descriptor SM */
multiline_comment|/*&t;Q_T1_SV&t; 8 bit&t;Test Register 1 Supervisor SM */
multiline_comment|/* The control status byte of each machine looks like ... */
DECL|macro|SM_STATE
mdefine_line|#define SM_STATE&t;&t;0xf0&t;/* Bit 7.. 4:&t;State which shall be loaded */
DECL|macro|SM_LOAD
mdefine_line|#define SM_LOAD&t;&t;&t;BIT_3S&t;/* Load the SM with SM_STATE */
DECL|macro|SM_TEST_ON
mdefine_line|#define SM_TEST_ON&t;&t;BIT_2S&t;/* Switch on SM Test Mode */
DECL|macro|SM_TEST_OFF
mdefine_line|#define SM_TEST_OFF&t;&t;BIT_1S&t;/* Go off the Test Mode */
DECL|macro|SM_STEP
mdefine_line|#define SM_STEP&t;&t;&t;BIT_0S&t;/* Step the State Machine */
multiline_comment|/* The encoding of the states is not supported by the Diagnostics Tool */
multiline_comment|/*&t;Q_T2&t;32 bit&t;Test Register 2&t;*/
multiline_comment|/* Bit 31.. 8:&t;reserved */
DECL|macro|T2_AC_T_ON
mdefine_line|#define T2_AC_T_ON&t;&t;BIT_7&t;/* Address Counter Test Mode on */
DECL|macro|T2_AC_T_OFF
mdefine_line|#define T2_AC_T_OFF&t;&t;BIT_6&t;/* Address Counter Test Mode off */
DECL|macro|T2_BC_T_ON
mdefine_line|#define T2_BC_T_ON&t;&t;BIT_5&t;/* Byte Counter Test Mode on */
DECL|macro|T2_BC_T_OFF
mdefine_line|#define T2_BC_T_OFF&t;&t;BIT_4&t;/* Byte Counter Test Mode off */
DECL|macro|T2_STEP04
mdefine_line|#define T2_STEP04&t;&t;BIT_3&t;/* Inc AC/Dec BC by 4 */
DECL|macro|T2_STEP03
mdefine_line|#define T2_STEP03&t;&t;BIT_2&t;/* Inc AC/Dec BC by 3 */
DECL|macro|T2_STEP02
mdefine_line|#define T2_STEP02&t;&t;BIT_1&t;/* Inc AC/Dec BC by 2 */
DECL|macro|T2_STEP01
mdefine_line|#define T2_STEP01&t;&t;BIT_0&t;/* Inc AC/Dec BC by 1 */
multiline_comment|/*&t;Q_T3&t;32 bit&t;Test Register 3&t;*/
multiline_comment|/* Bit 31.. 7:&t;reserved */
DECL|macro|T3_MUX_MSK
mdefine_line|#define T3_MUX_MSK&t;&t;(7&lt;&lt;4)&t;/* Bit  6.. 4:&t;Mux Position */
multiline_comment|/* Bit  3:&t;reserved */
DECL|macro|T3_VRAM_MSK
mdefine_line|#define T3_VRAM_MSK&t;&t;7&t;&t;/* Bit  2.. 0:&t;Virtual RAM Buffer Address */
multiline_comment|/* RAM Buffer Register Offsets, use RB_ADDR(Queue, Offs) to access */
multiline_comment|/*&t;RB_START&t;32 bit&t;RAM Buffer Start Address */
multiline_comment|/*&t;RB_END&t;&t;32 bit&t;RAM Buffer End Address */
multiline_comment|/*&t;RB_WP&t;&t;32 bit&t;RAM Buffer Write Pointer */
multiline_comment|/*&t;RB_RP&t;&t;32 bit&t;RAM Buffer Read Pointer */
multiline_comment|/*&t;RB_RX_UTPP&t;32 bit&t;Rx Upper Threshold, Pause Pack */
multiline_comment|/*&t;RB_RX_LTPP&t;32 bit&t;Rx Lower Threshold, Pause Pack */
multiline_comment|/*&t;RB_RX_UTHP&t;32 bit&t;Rx Upper Threshold, High Prio */
multiline_comment|/*&t;RB_RX_LTHP&t;32 bit&t;Rx Lower Threshold, High Prio */
multiline_comment|/*&t;RB_PC&t;&t;32 bit&t;RAM Buffer Packet Counter */
multiline_comment|/*&t;RB_LEV&t;&t;32 bit&t;RAM Buffer Level Register */
multiline_comment|/* Bit 31..19:&t;reserved */
DECL|macro|RB_MSK
mdefine_line|#define RB_MSK&t;0x0007ffff&t;/* Bit 18.. 0:&t;RAM Buffer Pointer Bits */
multiline_comment|/*&t;RB_TST2&t;&t;&t; 8 bit&t;RAM Buffer Test Register 2 */
multiline_comment|/* Bit 7.. 4:&t;reserved */
DECL|macro|RB_PC_DEC
mdefine_line|#define RB_PC_DEC&t;&t;BIT_3S&t;/* Packet Counter Decrem */
DECL|macro|RB_PC_T_ON
mdefine_line|#define RB_PC_T_ON&t;&t;BIT_2S&t;/* Packet Counter Test On */
DECL|macro|RB_PC_T_OFF
mdefine_line|#define RB_PC_T_OFF&t;&t;BIT_1S&t;/* Packet Counter Tst Off */
DECL|macro|RB_PC_INC
mdefine_line|#define RB_PC_INC&t;&t;BIT_0S&t;/* Packet Counter Increm */
multiline_comment|/*&t;RB_TST1&t;&t;&t; 8 bit&t;RAM Buffer Test Register 1 */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|RB_WP_T_ON
mdefine_line|#define RB_WP_T_ON&t;&t;BIT_6S&t;/* Write Pointer Test On */
DECL|macro|RB_WP_T_OFF
mdefine_line|#define RB_WP_T_OFF&t;&t;BIT_5S&t;/* Write Pointer Test Off */
DECL|macro|RB_WP_INC
mdefine_line|#define RB_WP_INC&t;&t;BIT_4S&t;/* Write Pointer Increm */
multiline_comment|/* Bit 3:&t;reserved */
DECL|macro|RB_RP_T_ON
mdefine_line|#define RB_RP_T_ON&t;&t;BIT_2S&t;/* Read Pointer Test On */
DECL|macro|RB_RP_T_OFF
mdefine_line|#define RB_RP_T_OFF&t;&t;BIT_1S&t;/* Read Pointer Test Off */
DECL|macro|RB_RP_DEC
mdefine_line|#define RB_RP_DEC&t;&t;BIT_0S&t;/* Read Pointer Decrement */
multiline_comment|/*&t;RB_CTRL&t;&t;&t; 8 bit&t;RAM Buffer Control Register */
multiline_comment|/* Bit 7.. 6:&t;reserved */
DECL|macro|RB_ENA_STFWD
mdefine_line|#define RB_ENA_STFWD&t;BIT_5S&t;/* Enable  Store &amp; Forward */
DECL|macro|RB_DIS_STFWD
mdefine_line|#define RB_DIS_STFWD&t;BIT_4S&t;/* Disable Store &amp; Forward */
DECL|macro|RB_ENA_OP_MD
mdefine_line|#define RB_ENA_OP_MD&t;BIT_3S&t;/* Enable  Operation Mode */
DECL|macro|RB_DIS_OP_MD
mdefine_line|#define RB_DIS_OP_MD&t;BIT_2S&t;/* Disable Operation Mode */
DECL|macro|RB_RST_CLR
mdefine_line|#define RB_RST_CLR&t;&t;BIT_1S&t;/* Clear RAM Buf STM Reset */
DECL|macro|RB_RST_SET
mdefine_line|#define RB_RST_SET&t;&t;BIT_0S&t;/* Set   RAM Buf STM Reset */
multiline_comment|/* Receive and Transmit MAC FIFO Registers (GENESIS only) */
multiline_comment|/*&t;RX_MFF_EA&t;32 bit&t;Receive MAC FIFO End Address */
multiline_comment|/*&t;RX_MFF_WP&t;32 bit &t;Receive MAC FIFO Write Pointer */
multiline_comment|/*&t;RX_MFF_RP&t;32 bit&t;Receive MAC FIFO Read Pointer */
multiline_comment|/*&t;RX_MFF_PC&t;32 bit&t;Receive MAC FIFO Packet Counter */
multiline_comment|/*&t;RX_MFF_LEV&t;32 bit&t;Receive MAC FIFO Level */
multiline_comment|/*&t;TX_MFF_EA&t;32 bit&t;Transmit MAC FIFO End Address */
multiline_comment|/*&t;TX_MFF_WP&t;32 bit &t;Transmit MAC FIFO Write Pointer */
multiline_comment|/*&t;TX_MFF_WSP&t;32 bit&t;Transmit MAC FIFO WR Shadow Pointer */
multiline_comment|/*&t;TX_MFF_RP&t;32 bit&t;Transmit MAC FIFO Read Pointer */
multiline_comment|/*&t;TX_MFF_PC&t;32 bit&t;Transmit MAC FIFO Packet Cnt */
multiline_comment|/*&t;TX_MFF_LEV&t;32 bit&t;Transmit MAC FIFO Level */
multiline_comment|/* Bit 31.. 6:&t;reserved */
DECL|macro|MFF_MSK
mdefine_line|#define MFF_MSK&t;&t;&t;0x007fL&t;/* Bit&t;5.. 0:&t;MAC FIFO Address/Ptr Bits */
multiline_comment|/*&t;RX_MFF_CTRL1&t;16 bit&t;Receive MAC FIFO Control Reg 1 */
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|MFF_ENA_RDY_PAT
mdefine_line|#define MFF_ENA_RDY_PAT&t;BIT_13S&t;&t;/* Enable  Ready Patch */
DECL|macro|MFF_DIS_RDY_PAT
mdefine_line|#define MFF_DIS_RDY_PAT&t;BIT_12S&t;&t;/* Disable Ready Patch */
DECL|macro|MFF_ENA_TIM_PAT
mdefine_line|#define MFF_ENA_TIM_PAT&t;BIT_11S&t;&t;/* Enable  Timing Patch */
DECL|macro|MFF_DIS_TIM_PAT
mdefine_line|#define MFF_DIS_TIM_PAT&t;BIT_10S&t;&t;/* Disable Timing Patch */
DECL|macro|MFF_ENA_ALM_FUL
mdefine_line|#define MFF_ENA_ALM_FUL&t;BIT_9S&t;&t;/* Enable  AlmostFull Sign */
DECL|macro|MFF_DIS_ALM_FUL
mdefine_line|#define MFF_DIS_ALM_FUL&t;BIT_8S&t;&t;/* Disable AlmostFull Sign */
DECL|macro|MFF_ENA_PAUSE
mdefine_line|#define MFF_ENA_PAUSE&t;BIT_7S&t;&t;/* Enable  Pause Signaling */
DECL|macro|MFF_DIS_PAUSE
mdefine_line|#define MFF_DIS_PAUSE&t;BIT_6S&t;&t;/* Disable Pause Signaling */
DECL|macro|MFF_ENA_FLUSH
mdefine_line|#define MFF_ENA_FLUSH&t;BIT_5S&t;&t;/* Enable  Frame Flushing */
DECL|macro|MFF_DIS_FLUSH
mdefine_line|#define MFF_DIS_FLUSH&t;BIT_4S&t;&t;/* Disable Frame Flushing */
DECL|macro|MFF_ENA_TIST
mdefine_line|#define MFF_ENA_TIST&t;BIT_3S&t;&t;/* Enable  Time Stamp Gener */
DECL|macro|MFF_DIS_TIST
mdefine_line|#define MFF_DIS_TIST&t;BIT_2S&t;&t;/* Disable Time Stamp Gener */
DECL|macro|MFF_CLR_INTIST
mdefine_line|#define MFF_CLR_INTIST&t;BIT_1S&t;&t;/* Clear IRQ No Time Stamp */
DECL|macro|MFF_CLR_INSTAT
mdefine_line|#define MFF_CLR_INSTAT&t;BIT_0S&t;&t;/* Clear IRQ No Status */
DECL|macro|MFF_RX_CTRL_DEF
mdefine_line|#define MFF_RX_CTRL_DEF MFF_ENA_TIM_PAT
multiline_comment|/*&t;TX_MFF_CTRL1&t;16 bit&t;Transmit MAC FIFO Control Reg 1 */
DECL|macro|MFF_CLR_PERR
mdefine_line|#define MFF_CLR_PERR&t;BIT_15S&t;&t;/* Clear Parity Error IRQ */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|MFF_ENA_PKT_REC
mdefine_line|#define MFF_ENA_PKT_REC&t;BIT_13S&t;&t;/* Enable  Packet Recovery */
DECL|macro|MFF_DIS_PKT_REC
mdefine_line|#define MFF_DIS_PKT_REC BIT_12S&t;&t;/* Disable Packet Recovery */
multiline_comment|/*&t;MFF_ENA_TIM_PAT&t; (see RX_MFF_CTRL1) Bit 11:&t;Enable  Timing Patch */
multiline_comment|/*&t;MFF_DIS_TIM_PAT&t; (see RX_MFF_CTRL1) Bit 10:&t;Disable Timing Patch */
multiline_comment|/*&t;MFF_ENA_ALM_FUL&t; (see RX_MFF_CTRL1) Bit&t; 9:&t;Enable  Almost Full Sign */
multiline_comment|/*&t;MFF_DIS_ALM_FUL&t; (see RX_MFF_CTRL1) Bit&t; 8:&t;Disable Almost Full Sign */
DECL|macro|MFF_ENA_W4E
mdefine_line|#define MFF_ENA_W4E&t;&t;BIT_7S&t;&t;/* Enable  Wait for Empty */
DECL|macro|MFF_DIS_W4E
mdefine_line|#define MFF_DIS_W4E&t;&t;BIT_6S&t;&t;/* Disable Wait for Empty */
multiline_comment|/*&t;MFF_ENA_FLUSH&t; (see RX_MFF_CTRL1) Bit&t; 5:&t;Enable  Frame Flushing */
multiline_comment|/*&t;MFF_DIS_FLUSH&t; (see RX_MFF_CTRL1) Bit&t; 4:&t;Disable Frame Flushing */
DECL|macro|MFF_ENA_LOOPB
mdefine_line|#define MFF_ENA_LOOPB&t;BIT_3S&t;&t;/* Enable  Loopback */
DECL|macro|MFF_DIS_LOOPB
mdefine_line|#define MFF_DIS_LOOPB&t;BIT_2S&t;&t;/* Disable Loopback */
DECL|macro|MFF_CLR_MAC_RST
mdefine_line|#define MFF_CLR_MAC_RST&t;BIT_1S&t;&t;/* Clear XMAC Reset */
DECL|macro|MFF_SET_MAC_RST
mdefine_line|#define MFF_SET_MAC_RST&t;BIT_0S&t;&t;/* Set   XMAC Reset */
DECL|macro|MFF_TX_CTRL_DEF
mdefine_line|#define MFF_TX_CTRL_DEF&t;(MFF_ENA_PKT_REC | MFF_ENA_TIM_PAT | MFF_ENA_FLUSH)
multiline_comment|/*&t;RX_MFF_TST2&t; &t; 8 bit&t;Receive MAC FIFO Test Register 2 */
multiline_comment|/*&t;TX_MFF_TST2&t; &t; 8 bit&t;Transmit MAC FIFO Test Register 2 */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|MFF_WSP_T_ON
mdefine_line|#define MFF_WSP_T_ON&t;BIT_6S&t;/* Tx: Write Shadow Ptr TestOn */
DECL|macro|MFF_WSP_T_OFF
mdefine_line|#define MFF_WSP_T_OFF&t;BIT_5S&t;/* Tx: Write Shadow Ptr TstOff */
DECL|macro|MFF_WSP_INC
mdefine_line|#define MFF_WSP_INC&t;&t;BIT_4S&t;/* Tx: Write Shadow Ptr Increment */
DECL|macro|MFF_PC_DEC
mdefine_line|#define MFF_PC_DEC&t;&t;BIT_3S&t;/* Packet Counter Decrement */
DECL|macro|MFF_PC_T_ON
mdefine_line|#define MFF_PC_T_ON&t;&t;BIT_2S&t;/* Packet Counter Test On */
DECL|macro|MFF_PC_T_OFF
mdefine_line|#define MFF_PC_T_OFF&t;BIT_1S&t;/* Packet Counter Test Off */
DECL|macro|MFF_PC_INC
mdefine_line|#define MFF_PC_INC&t;&t;BIT_0S&t;/* Packet Counter Increment */
multiline_comment|/*&t;RX_MFF_TST1&t; &t; 8 bit&t;Receive MAC FIFO Test Register 1 */
multiline_comment|/*&t;TX_MFF_TST1&t; &t; 8 bit&t;Transmit MAC FIFO Test Register 1 */
multiline_comment|/* Bit 7:&t;reserved */
DECL|macro|MFF_WP_T_ON
mdefine_line|#define MFF_WP_T_ON&t;&t;BIT_6S&t;/* Write Pointer Test On */
DECL|macro|MFF_WP_T_OFF
mdefine_line|#define MFF_WP_T_OFF&t;BIT_5S&t;/* Write Pointer Test Off */
DECL|macro|MFF_WP_INC
mdefine_line|#define MFF_WP_INC&t;&t;BIT_4S&t;/* Write Pointer Increm */
multiline_comment|/* Bit 3:&t;reserved */
DECL|macro|MFF_RP_T_ON
mdefine_line|#define MFF_RP_T_ON&t;&t;BIT_2S&t;/* Read Pointer Test On */
DECL|macro|MFF_RP_T_OFF
mdefine_line|#define MFF_RP_T_OFF&t;BIT_1S&t;/* Read Pointer Test Off */
DECL|macro|MFF_RP_DEC
mdefine_line|#define MFF_RP_DEC&t;&t;BIT_0S&t;/* Read Pointer Decrement */
multiline_comment|/*&t;RX_MFF_CTRL2&t; 8 bit&t;Receive MAC FIFO Control Reg 2 */
multiline_comment|/*&t;TX_MFF_CTRL2&t; 8 bit&t;Transmit MAC FIFO Control Reg 2 */
multiline_comment|/* Bit 7..4:&t;reserved */
DECL|macro|MFF_ENA_OP_MD
mdefine_line|#define MFF_ENA_OP_MD&t;BIT_3S&t;/* Enable  Operation Mode */
DECL|macro|MFF_DIS_OP_MD
mdefine_line|#define MFF_DIS_OP_MD&t;BIT_2S&t;/* Disable Operation Mode */
DECL|macro|MFF_RST_CLR
mdefine_line|#define MFF_RST_CLR&t;&t;BIT_1S&t;/* Clear MAC FIFO Reset */
DECL|macro|MFF_RST_SET
mdefine_line|#define MFF_RST_SET&t;&t;BIT_0S&t;/* Set   MAC FIFO Reset */
multiline_comment|/*&t;Link LED Counter Registers (GENESIS only) */
multiline_comment|/*&t;RX_LED_CTRL&t;&t; 8 bit&t;Receive LED Cnt Control Reg */
multiline_comment|/*&t;TX_LED_CTRL&t;&t; 8 bit&t;Transmit LED Cnt Control Reg */
multiline_comment|/*&t;LNK_SYNC_CTRL&t; 8 bit&t;Link Sync Cnt Control Register */
multiline_comment|/* Bit 7.. 3:&t;reserved */
DECL|macro|LED_START
mdefine_line|#define LED_START&t;&t;BIT_2S&t;/* Start Timer */
DECL|macro|LED_STOP
mdefine_line|#define LED_STOP&t;&t;BIT_1S&t;/* Stop Timer */
DECL|macro|LED_STATE
mdefine_line|#define LED_STATE&t;&t;BIT_0S&t;/* Rx/Tx: LED State, 1=LED on */
DECL|macro|LED_CLR_IRQ
mdefine_line|#define LED_CLR_IRQ&t;&t;BIT_0S&t;/* Lnk: &t;Clear Link IRQ */
multiline_comment|/*&t;RX_LED_TST&t;&t; 8 bit&t;Receive LED Cnt Test Register */
multiline_comment|/*&t;TX_LED_TST&t;&t; 8 bit&t;Transmit LED Cnt Test Register */
multiline_comment|/*&t;LNK_SYNC_TST&t; 8 bit&t;Link Sync Cnt Test Register */
multiline_comment|/* Bit 7.. 3:&t;reserved */
DECL|macro|LED_T_ON
mdefine_line|#define LED_T_ON&t;&t;BIT_2S&t;/* LED Counter Test mode On */
DECL|macro|LED_T_OFF
mdefine_line|#define LED_T_OFF&t;&t;BIT_1S&t;/* LED Counter Test mode Off */
DECL|macro|LED_T_STEP
mdefine_line|#define LED_T_STEP&t;&t;BIT_0S&t;/* LED Counter Step */
multiline_comment|/*&t;LNK_LED_REG&t; &t; 8 bit&t;Link LED Register */
multiline_comment|/* Bit 7.. 6:&t;reserved */
DECL|macro|LED_BLK_ON
mdefine_line|#define LED_BLK_ON&t;&t;BIT_5S&t;/* Link LED Blinking On */
DECL|macro|LED_BLK_OFF
mdefine_line|#define LED_BLK_OFF&t;&t;BIT_4S&t;/* Link LED Blinking Off */
DECL|macro|LED_SYNC_ON
mdefine_line|#define LED_SYNC_ON&t;&t;BIT_3S&t;/* Use Sync Wire to switch LED */
DECL|macro|LED_SYNC_OFF
mdefine_line|#define LED_SYNC_OFF&t;BIT_2S&t;/* Disable Sync Wire Input */
DECL|macro|LED_ON
mdefine_line|#define LED_ON&t;&t;&t;BIT_1S&t;/* switch LED on */
DECL|macro|LED_OFF
mdefine_line|#define LED_OFF&t;&t;&t;BIT_0S&t;/* switch LED off */
multiline_comment|/*&t;Receive and Transmit GMAC FIFO Registers (YUKON only) */
multiline_comment|/*&t;RX_GMF_EA&t;&t;32 bit&t;Rx GMAC FIFO End Address */
multiline_comment|/*&t;RX_GMF_AF_THR&t;32 bit&t;Rx GMAC FIFO Almost Full Thresh. */
multiline_comment|/*&t;RX_GMF_WP&t;&t;32 bit &t;Rx GMAC FIFO Write Pointer */
multiline_comment|/*&t;RX_GMF_WLEV&t;&t;32 bit &t;Rx GMAC FIFO Write Level */
multiline_comment|/*&t;RX_GMF_RP&t;&t;32 bit &t;Rx GMAC FIFO Read Pointer */
multiline_comment|/*&t;RX_GMF_RLEV&t;&t;32 bit &t;Rx GMAC FIFO Read Level */
multiline_comment|/*&t;TX_GMF_EA&t;&t;32 bit&t;Tx GMAC FIFO End Address */
multiline_comment|/*&t;TX_GMF_AE_THR&t;32 bit&t;Tx GMAC FIFO Almost Empty Thresh.*/
multiline_comment|/*&t;TX_GMF_WP&t;&t;32 bit &t;Tx GMAC FIFO Write Pointer */
multiline_comment|/*&t;TX_GMF_WSP&t;&t;32 bit &t;Tx GMAC FIFO Write Shadow Ptr. */
multiline_comment|/*&t;TX_GMF_WLEV&t;&t;32 bit &t;Tx GMAC FIFO Write Level */
multiline_comment|/*&t;TX_GMF_RP&t;&t;32 bit &t;Tx GMAC FIFO Read Pointer */
multiline_comment|/*&t;TX_GMF_RSTP&t;&t;32 bit &t;Tx GMAC FIFO Restart Pointer */
multiline_comment|/*&t;TX_GMF_RLEV&t;&t;32 bit &t;Tx GMAC FIFO Read Level */
multiline_comment|/*&t;RX_GMF_CTRL_T&t;32 bit&t;Rx GMAC FIFO Control/Test */
multiline_comment|/* Bits 31..15:&t;reserved */
DECL|macro|GMF_WP_TST_ON
mdefine_line|#define GMF_WP_TST_ON&t;BIT_14&t;&t;/* Write Pointer Test On */
DECL|macro|GMF_WP_TST_OFF
mdefine_line|#define GMF_WP_TST_OFF&t;BIT_13&t;&t;/* Write Pointer Test Off */
DECL|macro|GMF_WP_STEP
mdefine_line|#define GMF_WP_STEP&t;&t;BIT_12&t;&t;/* Write Pointer Step/Increment */
multiline_comment|/* Bit 11:&t;reserved */
DECL|macro|GMF_RP_TST_ON
mdefine_line|#define GMF_RP_TST_ON&t;BIT_10&t;&t;/* Read Pointer Test On */
DECL|macro|GMF_RP_TST_OFF
mdefine_line|#define GMF_RP_TST_OFF&t;BIT_9&t;&t;/* Read Pointer Test Off */
DECL|macro|GMF_RP_STEP
mdefine_line|#define GMF_RP_STEP&t;&t;BIT_8&t;&t;/* Read Pointer Step/Increment */
DECL|macro|GMF_RX_F_FL_ON
mdefine_line|#define GMF_RX_F_FL_ON&t;BIT_7&t;&t;/* Rx FIFO Flush Mode On */
DECL|macro|GMF_RX_F_FL_OFF
mdefine_line|#define GMF_RX_F_FL_OFF&t;BIT_6&t;&t;/* Rx FIFO Flush Mode Off */
DECL|macro|GMF_CLI_RX_FO
mdefine_line|#define GMF_CLI_RX_FO&t;BIT_5&t;&t;/* Clear IRQ Rx FIFO Overrun */
DECL|macro|GMF_CLI_RX_FC
mdefine_line|#define GMF_CLI_RX_FC&t;BIT_4&t;&t;/* Clear IRQ Rx Frame Complete */
DECL|macro|GMF_OPER_ON
mdefine_line|#define GMF_OPER_ON&t;&t;BIT_3&t;&t;/* Operational Mode On */
DECL|macro|GMF_OPER_OFF
mdefine_line|#define GMF_OPER_OFF&t;BIT_2&t;&t;/* Operational Mode Off */
DECL|macro|GMF_RST_CLR
mdefine_line|#define GMF_RST_CLR&t;&t;BIT_1&t;&t;/* Clear GMAC FIFO Reset */
DECL|macro|GMF_RST_SET
mdefine_line|#define GMF_RST_SET&t;&t;BIT_0&t;&t;/* Set   GMAC FIFO Reset */
multiline_comment|/*&t;TX_GMF_CTRL_T&t;32 bit&t;Tx GMAC FIFO Control/Test */
multiline_comment|/* Bits 31..19:&t;reserved */
DECL|macro|GMF_WSP_TST_ON
mdefine_line|#define GMF_WSP_TST_ON&t;BIT_18&t;&t;/* Write Shadow Pointer Test On */
DECL|macro|GMF_WSP_TST_OFF
mdefine_line|#define GMF_WSP_TST_OFF&t;BIT_17&t;&t;/* Write Shadow Pointer Test Off */
DECL|macro|GMF_WSP_STEP
mdefine_line|#define GMF_WSP_STEP&t;BIT_16&t;&t;/* Write Shadow Pointer Step/Increment */
multiline_comment|/* Bits 15..7: same as for RX_GMF_CTRL_T */
DECL|macro|GMF_CLI_TX_FU
mdefine_line|#define GMF_CLI_TX_FU&t;BIT_6&t;&t;/* Clear IRQ Tx FIFO Underrun */
DECL|macro|GMF_CLI_TX_FC
mdefine_line|#define GMF_CLI_TX_FC&t;BIT_5&t;&t;/* Clear IRQ Tx Frame Complete */
DECL|macro|GMF_CLI_TX_PE
mdefine_line|#define GMF_CLI_TX_PE&t;BIT_4&t;&t;/* Clear IRQ Tx Parity Error */
multiline_comment|/* Bits 3..0: same as for RX_GMF_CTRL_T */
DECL|macro|GMF_RX_CTRL_DEF
mdefine_line|#define GMF_RX_CTRL_DEF&t;&t;(GMF_OPER_ON | GMF_RX_F_FL_ON)
DECL|macro|GMF_TX_CTRL_DEF
mdefine_line|#define GMF_TX_CTRL_DEF&t;&t;GMF_OPER_ON
DECL|macro|RX_GMF_FL_THR_DEF
mdefine_line|#define RX_GMF_FL_THR_DEF&t;0x0a&t;/* Rx GMAC FIFO Flush Threshold default */
multiline_comment|/*&t;GMAC_TI_ST_CTRL&t;&t;  8 bit&t;Time Stamp Timer Ctrl Reg (YUKON only) */
multiline_comment|/* Bit 7.. 3:&t;reserved */
DECL|macro|GMT_ST_START
mdefine_line|#define GMT_ST_START&t;BIT_2S&t;&t;/* Start Time Stamp Timer */
DECL|macro|GMT_ST_STOP
mdefine_line|#define GMT_ST_STOP&t;&t;BIT_1S&t;&t;/* Stop  Time Stamp Timer */
DECL|macro|GMT_ST_CLR_IRQ
mdefine_line|#define GMT_ST_CLR_IRQ&t;BIT_0S&t;&t;/* Clear Time Stamp Timer IRQ */
multiline_comment|/*&t;GMAC_CTRL&t;&t;32 bit&t;GMAC Control Reg (YUKON only) */
multiline_comment|/* Bits 31.. 8:&t;reserved */
DECL|macro|GMC_H_BURST_ON
mdefine_line|#define GMC_H_BURST_ON&t;BIT_7&t;&t;/* Half Duplex Burst Mode On */
DECL|macro|GMC_H_BURST_OFF
mdefine_line|#define GMC_H_BURST_OFF&t;BIT_6&t;&t;/* Half Duplex Burst Mode Off */
DECL|macro|GMC_F_LOOPB_ON
mdefine_line|#define GMC_F_LOOPB_ON&t;BIT_5&t;&t;/* FIFO Loopback On */
DECL|macro|GMC_F_LOOPB_OFF
mdefine_line|#define GMC_F_LOOPB_OFF&t;BIT_4&t;&t;/* FIFO Loopback Off */
DECL|macro|GMC_PAUSE_ON
mdefine_line|#define GMC_PAUSE_ON&t;BIT_3&t;&t;/* Pause On */
DECL|macro|GMC_PAUSE_OFF
mdefine_line|#define GMC_PAUSE_OFF&t;BIT_2&t;&t;/* Pause Off */
DECL|macro|GMC_RST_CLR
mdefine_line|#define GMC_RST_CLR&t;&t;BIT_1&t;&t;/* Clear GMAC Reset */
DECL|macro|GMC_RST_SET
mdefine_line|#define GMC_RST_SET&t;&t;BIT_0&t;&t;/* Set   GMAC Reset */
multiline_comment|/*&t;GPHY_CTRL&t;&t;32 bit&t;GPHY Control Reg (YUKON only) */
multiline_comment|/* Bits 31..29:&t;reserved */
DECL|macro|GPC_SEL_BDT
mdefine_line|#define GPC_SEL_BDT&t;&t;BIT_28&t;/* Select Bi-Dir. Transfer for MDC/MDIO */
DECL|macro|GPC_INT_POL_HI
mdefine_line|#define GPC_INT_POL_HI&t;BIT_27&t;/* IRQ Polarity is Active HIGH */
DECL|macro|GPC_75_OHM
mdefine_line|#define GPC_75_OHM&t;&t;BIT_26&t;/* Use 75 Ohm Termination instead of 50 */
DECL|macro|GPC_DIS_FC
mdefine_line|#define GPC_DIS_FC&t;&t;BIT_25&t;/* Disable Automatic Fiber/Copper Detection */
DECL|macro|GPC_DIS_SLEEP
mdefine_line|#define GPC_DIS_SLEEP&t;BIT_24&t;/* Disable Energy Detect */
DECL|macro|GPC_HWCFG_M_3
mdefine_line|#define GPC_HWCFG_M_3&t;BIT_23&t;/* HWCFG_MODE[3] */
DECL|macro|GPC_HWCFG_M_2
mdefine_line|#define GPC_HWCFG_M_2&t;BIT_22&t;/* HWCFG_MODE[2] */
DECL|macro|GPC_HWCFG_M_1
mdefine_line|#define GPC_HWCFG_M_1&t;BIT_21&t;/* HWCFG_MODE[1] */
DECL|macro|GPC_HWCFG_M_0
mdefine_line|#define GPC_HWCFG_M_0&t;BIT_20&t;/* HWCFG_MODE[0] */
DECL|macro|GPC_ANEG_0
mdefine_line|#define GPC_ANEG_0&t;&t;BIT_19&t;/* ANEG[0] */
DECL|macro|GPC_ENA_XC
mdefine_line|#define GPC_ENA_XC&t;&t;BIT_18&t;/* Enable MDI crossover */
DECL|macro|GPC_DIS_125
mdefine_line|#define GPC_DIS_125&t;&t;BIT_17&t;/* Disable 125 MHz clock */
DECL|macro|GPC_ANEG_3
mdefine_line|#define GPC_ANEG_3&t;&t;BIT_16&t;/* ANEG[3] */
DECL|macro|GPC_ANEG_2
mdefine_line|#define GPC_ANEG_2&t;&t;BIT_15&t;/* ANEG[2] */
DECL|macro|GPC_ANEG_1
mdefine_line|#define GPC_ANEG_1&t;&t;BIT_14&t;/* ANEG[1] */
DECL|macro|GPC_ENA_PAUSE
mdefine_line|#define GPC_ENA_PAUSE&t;BIT_13&t;/* Enable Pause (SYM_OR_REM) */
DECL|macro|GPC_PHYADDR_4
mdefine_line|#define GPC_PHYADDR_4&t;BIT_12&t;/* Bit 4 of Phy Addr */
DECL|macro|GPC_PHYADDR_3
mdefine_line|#define GPC_PHYADDR_3&t;BIT_11&t;/* Bit 3 of Phy Addr */
DECL|macro|GPC_PHYADDR_2
mdefine_line|#define GPC_PHYADDR_2&t;BIT_10&t;/* Bit 2 of Phy Addr */
DECL|macro|GPC_PHYADDR_1
mdefine_line|#define GPC_PHYADDR_1&t;BIT_9&t;/* Bit 1 of Phy Addr */
DECL|macro|GPC_PHYADDR_0
mdefine_line|#define GPC_PHYADDR_0&t;BIT_8&t;/* Bit 0 of Phy Addr */
multiline_comment|/* Bits  7..2:&t;reserved */
DECL|macro|GPC_RST_CLR
mdefine_line|#define GPC_RST_CLR&t;&t;BIT_1&t;/* Clear GPHY Reset */
DECL|macro|GPC_RST_SET
mdefine_line|#define GPC_RST_SET&t;&t;BIT_0&t;/* Set   GPHY Reset */
DECL|macro|GPC_HWCFG_GMII_COP
mdefine_line|#define GPC_HWCFG_GMII_COP&t;(GPC_HWCFG_M_3 | GPC_HWCFG_M_2 | &bslash;&n;&t;&t;&t;&t;&t;&t;&t; GPC_HWCFG_M_1 | GPC_HWCFG_M_0)
DECL|macro|GPC_HWCFG_GMII_FIB
mdefine_line|#define GPC_HWCFG_GMII_FIB&t;(&t;&t;&t;&t; GPC_HWCFG_M_2 | &bslash;&n;&t;&t;&t;&t;&t;&t;&t; GPC_HWCFG_M_1 | GPC_HWCFG_M_0)
DECL|macro|GPC_ANEG_ADV_ALL_M
mdefine_line|#define GPC_ANEG_ADV_ALL_M&t;(GPC_ANEG_3 | GPC_ANEG_2 | &bslash;&n;&t;&t;&t;&t;&t;&t;&t; GPC_ANEG_1 | GPC_ANEG_0)
multiline_comment|/* forced speed and duplex mode (don&squot;t mix with other ANEG bits) */
DECL|macro|GPC_FRC10MBIT_HALF
mdefine_line|#define GPC_FRC10MBIT_HALF&t;0
DECL|macro|GPC_FRC10MBIT_FULL
mdefine_line|#define GPC_FRC10MBIT_FULL&t;GPC_ANEG_0
DECL|macro|GPC_FRC100MBIT_HALF
mdefine_line|#define GPC_FRC100MBIT_HALF&t;GPC_ANEG_1
DECL|macro|GPC_FRC100MBIT_FULL
mdefine_line|#define GPC_FRC100MBIT_FULL&t;(GPC_ANEG_0 | GPC_ANEG_1)
multiline_comment|/* auto-negotiation with limited advertised speeds */
multiline_comment|/* mix only with master/slave settings (for copper) */
DECL|macro|GPC_ADV_1000_HALF
mdefine_line|#define GPC_ADV_1000_HALF&t;GPC_ANEG_2
DECL|macro|GPC_ADV_1000_FULL
mdefine_line|#define GPC_ADV_1000_FULL&t;GPC_ANEG_3
DECL|macro|GPC_ADV_ALL
mdefine_line|#define GPC_ADV_ALL&t;&t;&t;(GPC_ANEG_2 | GPC_ANEG_3)
multiline_comment|/* master/slave settings */
multiline_comment|/* only for copper with 1000 Mbps */
DECL|macro|GPC_FORCE_MASTER
mdefine_line|#define GPC_FORCE_MASTER&t;0
DECL|macro|GPC_FORCE_SLAVE
mdefine_line|#define GPC_FORCE_SLAVE&t;&t;GPC_ANEG_0
DECL|macro|GPC_PREF_MASTER
mdefine_line|#define GPC_PREF_MASTER&t;&t;GPC_ANEG_1
DECL|macro|GPC_PREF_SLAVE
mdefine_line|#define GPC_PREF_SLAVE&t;&t;(GPC_ANEG_1 | GPC_ANEG_0)
multiline_comment|/*&t;GMAC_IRQ_SRC&t; 8 bit&t;GMAC Interrupt Source Reg (YUKON only) */
multiline_comment|/*&t;GMAC_IRQ_MSK&t; 8 bit&t;GMAC Interrupt Mask   Reg (YUKON only) */
DECL|macro|GM_IS_TX_CO_OV
mdefine_line|#define GM_IS_TX_CO_OV&t;BIT_5&t;&t;/* Transmit Counter Overflow IRQ */
DECL|macro|GM_IS_RX_CO_OV
mdefine_line|#define GM_IS_RX_CO_OV&t;BIT_4&t;&t;/* Receive Counter Overflow IRQ */
DECL|macro|GM_IS_TX_FF_UR
mdefine_line|#define GM_IS_TX_FF_UR&t;BIT_3&t;&t;/* Transmit FIFO Underrun */
DECL|macro|GM_IS_TX_COMPL
mdefine_line|#define GM_IS_TX_COMPL&t;BIT_2&t;&t;/* Frame Transmission Complete */
DECL|macro|GM_IS_RX_FF_OR
mdefine_line|#define GM_IS_RX_FF_OR&t;BIT_1&t;&t;/* Receive FIFO Overrun */
DECL|macro|GM_IS_RX_COMPL
mdefine_line|#define GM_IS_RX_COMPL&t;BIT_0&t;&t;/* Frame Reception Complete */
DECL|macro|GMAC_DEF_MSK
mdefine_line|#define GMAC_DEF_MSK&t;(GM_IS_TX_CO_OV | GM_IS_RX_CO_OV | &bslash;&n;&t;&t;&t;&t;&t;&t;GM_IS_TX_FF_UR)
multiline_comment|/*&t;GMAC_LINK_CTRL&t;&t;16 bit&t;GMAC Link Control Reg (YUKON only) */
multiline_comment|/* Bits 15.. 2:&t;reserved */
DECL|macro|GMLC_RST_CLR
mdefine_line|#define GMLC_RST_CLR&t;BIT_1S&t;&t;/* Clear GMAC Link Reset */
DECL|macro|GMLC_RST_SET
mdefine_line|#define GMLC_RST_SET&t;BIT_0S&t;&t;/* Set   GMAC Link Reset */
multiline_comment|/*&t;WOL_CTRL_STAT&t;&t;16 bit&t;WOL Control/Status Reg */
DECL|macro|WOL_CTL_LINK_CHG_OCC
mdefine_line|#define WOL_CTL_LINK_CHG_OCC&t;&t;&t;BIT_15S
DECL|macro|WOL_CTL_MAGIC_PKT_OCC
mdefine_line|#define WOL_CTL_MAGIC_PKT_OCC&t;&t;&t;BIT_14S
DECL|macro|WOL_CTL_PATTERN_OCC
mdefine_line|#define WOL_CTL_PATTERN_OCC&t;&t;&t;&t;BIT_13S
DECL|macro|WOL_CTL_CLEAR_RESULT
mdefine_line|#define WOL_CTL_CLEAR_RESULT&t;&t;&t;BIT_12S
DECL|macro|WOL_CTL_ENA_PME_ON_LINK_CHG
mdefine_line|#define WOL_CTL_ENA_PME_ON_LINK_CHG&t;&t;BIT_11S
DECL|macro|WOL_CTL_DIS_PME_ON_LINK_CHG
mdefine_line|#define WOL_CTL_DIS_PME_ON_LINK_CHG&t;&t;BIT_10S
DECL|macro|WOL_CTL_ENA_PME_ON_MAGIC_PKT
mdefine_line|#define WOL_CTL_ENA_PME_ON_MAGIC_PKT&t;BIT_9S
DECL|macro|WOL_CTL_DIS_PME_ON_MAGIC_PKT
mdefine_line|#define WOL_CTL_DIS_PME_ON_MAGIC_PKT&t;BIT_8S
DECL|macro|WOL_CTL_ENA_PME_ON_PATTERN
mdefine_line|#define WOL_CTL_ENA_PME_ON_PATTERN&t;&t;BIT_7S
DECL|macro|WOL_CTL_DIS_PME_ON_PATTERN
mdefine_line|#define WOL_CTL_DIS_PME_ON_PATTERN&t;&t;BIT_6S
DECL|macro|WOL_CTL_ENA_LINK_CHG_UNIT
mdefine_line|#define WOL_CTL_ENA_LINK_CHG_UNIT&t;&t;BIT_5S
DECL|macro|WOL_CTL_DIS_LINK_CHG_UNIT
mdefine_line|#define WOL_CTL_DIS_LINK_CHG_UNIT&t;&t;BIT_4S
DECL|macro|WOL_CTL_ENA_MAGIC_PKT_UNIT
mdefine_line|#define WOL_CTL_ENA_MAGIC_PKT_UNIT&t;&t;BIT_3S
DECL|macro|WOL_CTL_DIS_MAGIC_PKT_UNIT
mdefine_line|#define WOL_CTL_DIS_MAGIC_PKT_UNIT&t;&t;BIT_2S
DECL|macro|WOL_CTL_ENA_PATTERN_UNIT
mdefine_line|#define WOL_CTL_ENA_PATTERN_UNIT&t;&t;BIT_1S
DECL|macro|WOL_CTL_DIS_PATTERN_UNIT
mdefine_line|#define WOL_CTL_DIS_PATTERN_UNIT&t;&t;BIT_0S
DECL|macro|WOL_CTL_DEFAULT
mdefine_line|#define WOL_CTL_DEFAULT&t;&t;&t;&t;&bslash;&n;&t;(WOL_CTL_DIS_PME_ON_LINK_CHG |&t;&bslash;&n;&t;WOL_CTL_DIS_PME_ON_PATTERN |&t;&bslash;&n;&t;WOL_CTL_DIS_PME_ON_MAGIC_PKT |&t;&bslash;&n;&t;WOL_CTL_DIS_LINK_CHG_UNIT |&t;&t;&bslash;&n;&t;WOL_CTL_DIS_PATTERN_UNIT |&t;&t;&bslash;&n;&t;WOL_CTL_DIS_MAGIC_PKT_UNIT)
multiline_comment|/*&t;WOL_MATCH_CTL&t;&t; 8 bit&t;WOL Match Control Reg */
DECL|macro|WOL_CTL_PATT_ENA
mdefine_line|#define WOL_CTL_PATT_ENA(x)&t;&t;&t;&t;(BIT_0 &lt;&lt; (x))
DECL|macro|SK_NUM_WOL_PATTERN
mdefine_line|#define SK_NUM_WOL_PATTERN&t;&t;7
DECL|macro|SK_PATTERN_PER_WORD
mdefine_line|#define SK_PATTERN_PER_WORD&t;&t;4
DECL|macro|SK_BITMASK_PATTERN
mdefine_line|#define SK_BITMASK_PATTERN&t;&t;7
DECL|macro|SK_POW_PATTERN_LENGTH
mdefine_line|#define SK_POW_PATTERN_LENGTH&t;128
DECL|macro|WOL_LENGTH_MSK
mdefine_line|#define WOL_LENGTH_MSK&t;&t;0x7f
DECL|macro|WOL_LENGTH_SHIFT
mdefine_line|#define WOL_LENGTH_SHIFT&t;8
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
multiline_comment|/* Physical Address Pointer to the next RxD */
DECL|member|RxAdrLo
id|SK_U32
id|RxAdrLo
suffix:semicolon
multiline_comment|/* Physical Rx Buffer Address lower dword */
DECL|member|RxAdrHi
id|SK_U32
id|RxAdrHi
suffix:semicolon
multiline_comment|/* Physical Rx Buffer Address upper dword */
DECL|member|RxStat
id|SK_U32
id|RxStat
suffix:semicolon
multiline_comment|/* Receive Frame Status Word */
DECL|member|RxTiSt
id|SK_U32
id|RxTiSt
suffix:semicolon
multiline_comment|/* Receive Time Stamp (from XMAC on GENESIS) */
macro_line|#ifndef&t;SK_USE_REV_DESC
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
multiline_comment|/*&n; * Drivers which use the reverse descriptor feature (PCI_OUR_REG_2)&n; * should set the define SK_USE_REV_DESC.&n; * Structures are &squot;normaly&squot; not endianess dependent. But in&n; * this case the SK_U16 fields are bound to bit positions inside the&n; * descriptor. RxTcpSum1 e.g. must start at bit 0 within the 6.th DWord.&n; * The bit positions inside a DWord are of course endianess dependent and&n; * swaps if the DWord is swapped by the hardware.&n; */
multiline_comment|/* Descriptor Bit Definition */
multiline_comment|/*&t;TxCtrl&t;&t;Transmit Buffer Control Field */
multiline_comment|/*&t;RxCtrl&t;&t;Receive  Buffer Control Field */
DECL|macro|BMU_OWN
mdefine_line|#define BMU_OWN&t;&t;&t;BIT_31&t;/* OWN bit: 0=host/1=BMU */
DECL|macro|BMU_STF
mdefine_line|#define BMU_STF&t;&t;&t;BIT_30&t;/* Start of Frame */
DECL|macro|BMU_EOF
mdefine_line|#define BMU_EOF&t;&t;&t;BIT_29&t;/* End of Frame */
DECL|macro|BMU_IRQ_EOB
mdefine_line|#define BMU_IRQ_EOB&t;&t;BIT_28&t;/* Req &quot;End of Buffer&quot; IRQ */
DECL|macro|BMU_IRQ_EOF
mdefine_line|#define BMU_IRQ_EOF&t;&t;BIT_27&t;/* Req &quot;End of Frame&quot; IRQ */
multiline_comment|/* TxCtrl specific bits */
DECL|macro|BMU_STFWD
mdefine_line|#define BMU_STFWD&t;&t;BIT_26&t;/* (Tx)&t;Store &amp; Forward Frame */
DECL|macro|BMU_NO_FCS
mdefine_line|#define BMU_NO_FCS&t;&t;BIT_25&t;/* (Tx) Disable MAC FCS (CRC) generation */
DECL|macro|BMU_SW
mdefine_line|#define BMU_SW&t;&t;&t;BIT_24&t;/* (Tx)&t;1 bit res. for SW use */
multiline_comment|/* RxCtrl specific bits */
DECL|macro|BMU_DEV_0
mdefine_line|#define BMU_DEV_0&t;&t;BIT_26&t;/* (Rx)&t;Transfer data to Dev0 */
DECL|macro|BMU_STAT_VAL
mdefine_line|#define BMU_STAT_VAL&t;BIT_25&t;/* (Rx)&t;Rx Status Valid */
DECL|macro|BMU_TIST_VAL
mdefine_line|#define BMU_TIST_VAL&t;BIT_24&t;/* (Rx)&t;Rx TimeStamp Valid */
multiline_comment|/* Bit 23..16:&t;BMU Check Opcodes */
DECL|macro|BMU_CHECK
mdefine_line|#define BMU_CHECK&t;&t;(0x55L&lt;&lt;16)&t;/* Default BMU check */
DECL|macro|BMU_TCP_CHECK
mdefine_line|#define BMU_TCP_CHECK&t;(0x56L&lt;&lt;16)&t;/* Descr with TCP ext */
DECL|macro|BMU_UDP_CHECK
mdefine_line|#define BMU_UDP_CHECK&t;(0x57L&lt;&lt;16)&t;/* Descr with UDP ext (YUKON only) */
DECL|macro|BMU_BBC
mdefine_line|#define BMU_BBC&t;&t;&t;0xffffL&t;/* Bit 15.. 0:&t;Buffer Byte Counter */
multiline_comment|/*&t;TxStat&t;&t;Transmit Frame Status Word */
multiline_comment|/*&t;RxStat&t;&t;Receive Frame Status Word */
multiline_comment|/*&n; *Note: TxStat is reserved for ASIC loopback mode only&n; *&n; *&t;The Bits of the Status words are defined in xmac_ii.h&n; *&t;(see XMR_FS bits)&n; */
multiline_comment|/* macros ********************************************************************/
multiline_comment|/* Receive and Transmit Queues */
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
multiline_comment|/*&n; *&t;Macro Q_ADDR()&n; *&n; *&t;Use this macro to access the Receive and Transmit Queue Registers.&n; *&n; * para:&n; *&t;Queue&t;Queue to access.&n; *&t;&t;&t;&t;Values: Q_R1, Q_R2, Q_XS1, Q_XA1, Q_XS2, and Q_XA2&n; *&t;Offs&t;Queue register offset.&n; *&t;&t;&t;&t;Values: Q_D, Q_DA_L ... Q_T2, Q_T3&n; *&n; * usage&t;SK_IN32(pAC, Q_ADDR(Q_R2, Q_BC), pVal)&n; */
DECL|macro|Q_ADDR
mdefine_line|#define Q_ADDR(Queue, Offs)&t;(B8_Q_REGS + (Queue) + (Offs))
multiline_comment|/*&n; *&t;Macro RB_ADDR()&n; *&n; *&t;Use this macro to access the RAM Buffer Registers.&n; *&n; * para:&n; *&t;Queue&t;Queue to access.&n; *&t;&t;&t;&t;Values: Q_R1, Q_R2, Q_XS1, Q_XA1, Q_XS2, and Q_XA2&n; *&t;Offs&t;Queue register offset.&n; *&t;&t;&t;&t;Values: RB_START, RB_END ... RB_LEV, RB_CTRL&n; *&n; * usage&t;SK_IN32(pAC, RB_ADDR(Q_R2, RB_RP), pVal)&n; */
DECL|macro|RB_ADDR
mdefine_line|#define RB_ADDR(Queue, Offs)&t;(B16_RAM_REGS + (Queue) + (Offs))
multiline_comment|/* MAC Related Registers */
DECL|macro|MAC_1
mdefine_line|#define MAC_1&t;&t;0&t;/* belongs to the port near the slot */
DECL|macro|MAC_2
mdefine_line|#define MAC_2&t;&t;1&t;/* belongs to the port far away from the slot */
multiline_comment|/*&n; *&t;Macro MR_ADDR()&n; *&n; *&t;Use this macro to access a MAC Related Registers inside the ASIC.&n; *&n; * para:&n; *&t;Mac&t;&t;MAC to access.&n; *&t;&t;&t;&t;Values: MAC_1, MAC_2&n; *&t;Offs&t;MAC register offset.&n; *&t;&t;&t;&t;Values: RX_MFF_EA, RX_MFF_WP ... LNK_LED_REG,&n; *&t;&t;&t;&t;&t;&t;TX_MFF_EA, TX_MFF_WP ... TX_LED_TST&n; *&n; * usage&t;SK_IN32(pAC, MR_ADDR(MAC_1, TX_MFF_EA), pVal)&n; */
DECL|macro|MR_ADDR
mdefine_line|#define MR_ADDR(Mac, Offs)&t;(((Mac) &lt;&lt; 7) + (Offs))
macro_line|#ifdef&t;SK_LITTLE_ENDIAN
DECL|macro|XM_WORD_LO
mdefine_line|#define XM_WORD_LO&t;0
DECL|macro|XM_WORD_HI
mdefine_line|#define XM_WORD_HI&t;1
macro_line|#else&t;/* !SK_LITTLE_ENDIAN */
DECL|macro|XM_WORD_LO
mdefine_line|#define XM_WORD_LO&t;1
DECL|macro|XM_WORD_HI
mdefine_line|#define XM_WORD_HI&t;0
macro_line|#endif&t;/* !SK_LITTLE_ENDIAN */
multiline_comment|/*&n; * macros to access the XMAC (GENESIS only)&n; *&n; * XM_IN16(),&t;&t;to read a 16 bit register (e.g. XM_MMU_CMD)&n; * XM_OUT16(),&t;&t;to write a 16 bit register (e.g. XM_MMU_CMD)&n; * XM_IN32(),&t;&t;to read a 32 bit register (e.g. XM_TX_EV_CNT)&n; * XM_OUT32(),&t;&t;to write a 32 bit register (e.g. XM_TX_EV_CNT)&n; * XM_INADDR(),&t;&t;to read a network address register (e.g. XM_SRC_CHK)&n; * XM_OUTADDR(),&t;to write a network address register (e.g. XM_SRC_CHK)&n; * XM_INHASH(),&t;&t;to read the XM_HSM_CHK register&n; * XM_OUTHASH()&t;&t;to write the XM_HSM_CHK register&n; *&n; * para:&n; *&t;Mac&t;&t;XMAC to access&t;&t;values: MAC_1 or MAC_2&n; *&t;IoC&t;&t;I/O context needed for SK I/O macros&n; *&t;Reg&t;&t;XMAC Register to read or write&n; *&t;(p)Val&t;Value or pointer to the value which should be read or written&n; *&n; * usage:&t;XM_OUT16(IoC, MAC_1, XM_MMU_CMD, Value);&n; */
DECL|macro|XMA
mdefine_line|#define XMA(Mac, Reg)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((BASE_XMAC_1 + (Mac) * (BASE_XMAC_2 - BASE_XMAC_1)) | ((Reg) &lt;&lt; 1))
DECL|macro|XM_IN16
mdefine_line|#define XM_IN16(IoC, Mac, Reg, pVal)&t;&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg)), (pVal))
DECL|macro|XM_OUT16
mdefine_line|#define XM_OUT16(IoC, Mac, Reg, Val)&t;&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg)), (Val))
DECL|macro|XM_IN32
mdefine_line|#define XM_IN32(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SK_U16 SK_FAR*)&amp;((SK_U16 SK_FAR*)(pVal))[XM_WORD_LO]);&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+2)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SK_U16 SK_FAR*)&amp;((SK_U16 SK_FAR*)(pVal))[XM_WORD_HI]);&t;&t;&bslash;&n;}
DECL|macro|XM_OUT32
mdefine_line|#define XM_OUT32(IoC, Mac, Reg, Val) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg)), (SK_U16)((Val) &amp; 0xffffL));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+2)), (SK_U16)(((Val) &gt;&gt; 16) &amp; 0xffffL));&bslash;&n;}
multiline_comment|/* Remember: we are always writing to / reading from LITTLE ENDIAN memory */
DECL|macro|XM_INADDR
mdefine_line|#define XM_INADDR(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U16&t;Word;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[0] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[1] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+2)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[2] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[3] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+4)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[4] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[5] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;}
DECL|macro|XM_OUTADDR
mdefine_line|#define XM_OUTADDR(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;SK_FAR *pByte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 SK_FAR *)&amp;((SK_U8 SK_FAR *)(pVal))[0];&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[0]) &amp; 0x00ff) |&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[1]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+2)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[2]) &amp; 0x00ff) |&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[3]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+4)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[4]) &amp; 0x00ff) |&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[5]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;}
DECL|macro|XM_INHASH
mdefine_line|#define XM_INHASH(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U16&t;Word;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;SK_FAR *pByte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 SK_FAR *)&amp;((SK_U8 SK_FAR *)(pVal))[0];&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[0] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[1] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+2)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[2] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[3] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+4)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[4] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[5] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), XMA((Mac), (Reg+6)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[6] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[7] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;}
DECL|macro|XM_OUTHASH
mdefine_line|#define XM_OUTHASH(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;SK_FAR *pByte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 SK_FAR *)&amp;((SK_U8 SK_FAR *)(pVal))[0];&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[0]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[1]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+2)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[2]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[3]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+4)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[4]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[5]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), XMA((Mac), (Reg+6)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[6]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[7]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * macros to access the GMAC (YUKON only)&n; *&n; * GM_IN16(),&t;&t;to read  a 16 bit register (e.g. GM_GP_STAT)&n; * GM_OUT16(),&t;&t;to write a 16 bit register (e.g. GM_GP_CTRL)&n; * GM_IN32(),&t;&t;to read  a 32 bit register (e.g. GM_)&n; * GM_OUT32(),&t;&t;to write a 32 bit register (e.g. GM_)&n; * GM_INADDR(),&t;&t;to read  a network address register (e.g. GM_SRC_ADDR_1L)&n; * GM_OUTADDR(),&t;to write a network address register (e.g. GM_SRC_ADDR_2L)&n; * GM_INHASH(),&t;&t;to read  the GM_MC_ADDR_H1 register&n; * GM_OUTHASH()&t;&t;to write the GM_MC_ADDR_H1 register&n; *&n; * para:&n; *&t;Mac&t;&t;GMAC to access&t;&t;values: MAC_1 or MAC_2&n; *&t;IoC&t;&t;I/O context needed for SK I/O macros&n; *&t;Reg&t;&t;GMAC Register to read or write&n; *&t;(p)Val&t;Value or pointer to the value which should be read or written&n; *&n; * usage:&t;GM_OUT16(IoC, MAC_1, GM_GP_CTRL, Value);&n; */
DECL|macro|GMA
mdefine_line|#define GMA(Mac, Reg)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((BASE_GMAC_1 + (Mac) * (BASE_GMAC_2 - BASE_GMAC_1)) | (Reg))
DECL|macro|GM_IN16
mdefine_line|#define GM_IN16(IoC, Mac, Reg, pVal)&t;&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg)), (pVal))
DECL|macro|GM_OUT16
mdefine_line|#define GM_OUT16(IoC, Mac, Reg, Val)&t;&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg)), (Val))
DECL|macro|GM_IN32
mdefine_line|#define GM_IN32(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SK_U16 SK_FAR*)&amp;((SK_U16 SK_FAR*)(pVal))[XM_WORD_LO]);&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg+4)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SK_U16 SK_FAR*)&amp;((SK_U16 SK_FAR*)(pVal))[XM_WORD_HI]);&t;&t;&bslash;&n;}
DECL|macro|GM_OUT32
mdefine_line|#define GM_OUT32(IoC, Mac, Reg, Val) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg)), (SK_U16)((Val) &amp; 0xffffL));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg+4)), (SK_U16)(((Val) &gt;&gt; 16) &amp; 0xffffL));&bslash;&n;}
DECL|macro|GM_INADDR
mdefine_line|#define GM_INADDR(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U16&t;Word;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[0] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[1] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg+4)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[2] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[3] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg+8)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[4] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[5] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;}
DECL|macro|GM_OUTADDR
mdefine_line|#define GM_OUTADDR(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;SK_FAR *pByte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 SK_FAR *)&amp;((SK_U8 SK_FAR *)(pVal))[0];&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[0]) &amp; 0x00ff) |&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[1]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg+4)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[2]) &amp; 0x00ff) |&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[3]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg+8)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[4]) &amp; 0x00ff) |&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[5]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;}
DECL|macro|GM_INHASH
mdefine_line|#define GM_INHASH(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U16&t;Word;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[0] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[1] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg+4)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[2] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[3] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg+8)), &amp;Word);&t;&t;&t;&bslash;&n;&t;pByte[4] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[5] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;&t;SK_IN16((IoC), GMA((Mac), (Reg+12)), &amp;Word);&t;&t;&bslash;&n;&t;pByte[6] = (SK_U8)(Word  &amp; 0x00ff);&t;&t;&t;&t;&t;&bslash;&n;&t;pByte[7] = (SK_U8)((Word &gt;&gt; 8) &amp; 0x00ff);&t;&t;&t;&bslash;&n;}
DECL|macro|GM_OUTHASH
mdefine_line|#define GM_OUTHASH(IoC, Mac, Reg, pVal) {&t;&t;&t;&t;&bslash;&n;&t;SK_U8&t;*pByte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pByte = (SK_U8 *)&amp;((SK_U8 *)(pVal))[0];&t;&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg)), (SK_U16)&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[0]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[1]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg+4)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[2]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[3]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg+8)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[4]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[5]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;&t;SK_OUT16((IoC), GMA((Mac), (Reg+12)), (SK_U16)&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[6]) &amp; 0x00ff)|&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((SK_U16)(pByte[7]) &lt;&lt; 8) &amp; 0xff00)));&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Different MAC Types&n; */
DECL|macro|SK_MAC_XMAC
mdefine_line|#define SK_MAC_XMAC&t;&t;0&t;/* Xaqti XMAC II */
DECL|macro|SK_MAC_GMAC
mdefine_line|#define SK_MAC_GMAC&t;&t;1&t;/* Marvell GMAC */
multiline_comment|/*&n; * Different PHY Types&n; */
DECL|macro|SK_PHY_XMAC
mdefine_line|#define SK_PHY_XMAC&t;&t;&t;0&t;/* integrated in XMAC II */
DECL|macro|SK_PHY_BCOM
mdefine_line|#define SK_PHY_BCOM&t;&t;&t;1&t;/* Broadcom BCM5400 */
DECL|macro|SK_PHY_LONE
mdefine_line|#define SK_PHY_LONE&t;&t;&t;2&t;/* Level One LXT1000 */
DECL|macro|SK_PHY_NAT
mdefine_line|#define SK_PHY_NAT&t;&t;&t;3&t;/* National DP83891 */
DECL|macro|SK_PHY_MARV_COPPER
mdefine_line|#define SK_PHY_MARV_COPPER&t;4&t;/* Marvell 88E1011S */
DECL|macro|SK_PHY_MARV_FIBER
mdefine_line|#define SK_PHY_MARV_FIBER&t;5&t;/* Marvell 88E1011S working on fiber */
multiline_comment|/*&n; * PHY addresses (bits 12..8 of PHY address reg)&n; */
DECL|macro|PHY_ADDR_XMAC
mdefine_line|#define PHY_ADDR_XMAC&t;(0&lt;&lt;8)
DECL|macro|PHY_ADDR_BCOM
mdefine_line|#define PHY_ADDR_BCOM&t;(1&lt;&lt;8)
DECL|macro|PHY_ADDR_LONE
mdefine_line|#define PHY_ADDR_LONE&t;(3&lt;&lt;8)
DECL|macro|PHY_ADDR_NAT
mdefine_line|#define PHY_ADDR_NAT&t;(0&lt;&lt;8)
multiline_comment|/* GPHY address (bits 15..11 of SMI control reg) */
DECL|macro|PHY_ADDR_MARV
mdefine_line|#define PHY_ADDR_MARV&t;0
multiline_comment|/*&n; * macros to access the PHY&n; *&n; * PHY_READ()&t;&t;read a 16 bit value from the PHY&n; * PHY_WRITE()&t;&t;write a 16 bit value to the PHY&n; *&n; * para:&n; * &t;IoC&t;&t;I/O context needed for SK I/O macros&n; * &t;pPort&t;Pointer to port struct for PhyAddr&n; * &t;Mac&t;&t;XMAC to access&t;&t;values: MAC_1 or MAC_2&n; * &t;PhyReg&t;PHY Register to read or write&n; * &t;(p)Val&t;Value or pointer to the value which should be read or&n; *&t;&t;&t;written.&n; *&n; * usage:&t;PHY_READ(IoC, pPort, MAC_1, PHY_CTRL, Value);&n; * Warning: a PHY_READ on an uninitialized PHY (PHY still in reset) never&n; *          comes back. This is checked in DEBUG mode.&n; */
macro_line|#ifndef DEBUG
DECL|macro|PHY_READ
mdefine_line|#define PHY_READ(IoC, pPort, Mac, PhyReg, pVal) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U16 Mmu;  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;XM_OUT16((IoC), (Mac), XM_PHY_ADDR, (PhyReg) | (pPort)-&gt;PhyAddr);&t;&bslash;&n;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_RDY) == 0);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|PHY_READ
mdefine_line|#define PHY_READ(IoC, pPort, Mac, PhyReg, pVal) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U16 Mmu;  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __i = 0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;XM_OUT16((IoC), (Mac), XM_PHY_ADDR, (PhyReg) | (pPort)-&gt;PhyAddr);&t;&bslash;&n;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__i++;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (__i &gt; 100000) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;SK_DBG_PRINTF(&quot;*****************************&bslash;n&quot;);&t;&t;&bslash;&n;&t;&t;&t;&t;SK_DBG_PRINTF(&quot;PHY_READ on uninitialized PHY&bslash;n&quot;);&t;&t;&bslash;&n;&t;&t;&t;&t;SK_DBG_PRINTF(&quot;*****************************&bslash;n&quot;);&t;&t;&bslash;&n;&t;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_RDY) == 0);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;XM_IN16((IoC), (Mac), XM_PHY_DATA, (pVal));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* DEBUG */
DECL|macro|PHY_WRITE
mdefine_line|#define PHY_WRITE(IoC, pPort, Mac, PhyReg, Val) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SK_U16 Mmu;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_BUSY) != 0);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;XM_OUT16((IoC), (Mac), XM_PHY_ADDR, (PhyReg) | (pPort)-&gt;PhyAddr);&t;&bslash;&n;&t;XM_OUT16((IoC), (Mac), XM_PHY_DATA, (Val));&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pPort)-&gt;PhyType != SK_PHY_XMAC) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do {  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XM_IN16((IoC), (Mac), XM_MMU_CMD, &amp;Mmu);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;} while ((Mmu &amp; XM_MMU_PHY_BUSY) != 0);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; *&t;Macro PCI_C()&n; *&n; *&t;Use this macro to access PCI config register from the I/O space.&n; *&n; * para:&n; *&t;Addr&t;PCI configuration register to access.&n; *&t;&t;&t;Values:&t;PCI_VENDOR_ID ... PCI_VPD_ADR_REG,&n; *&n; * usage&t;SK_IN16(pAC, PCI_C(PCI_VENDOR_ID), pVal);&n; */
DECL|macro|PCI_C
mdefine_line|#define PCI_C(Addr)&t;(B7_CFG_SPC + (Addr))&t;/* PCI Config Space */
multiline_comment|/*&n; *&t;Macro SK_HW_ADDR(Base, Addr)&n; *&n; *&t;Calculates the effective HW address&n; *&n; * para:&n; *&t;Base&t;I/O or memory base address&n; *&t;Addr&t;Address offset&n; *&n; * usage:&t;May be used in SK_INxx and SK_OUTxx macros&n; *&t;&t;#define SK_IN8(pAC, Addr, pVal) ...&bslash;&n; *&t;&t;&t;*pVal = (SK_U8)inp(SK_HW_ADDR(pAC-&gt;Hw.Iop, Addr)))&n; */
macro_line|#ifdef SK_MEM_MAPPED_IO
DECL|macro|SK_HW_ADDR
mdefine_line|#define SK_HW_ADDR(Base, Addr)&t;((Base) + (Addr))
macro_line|#else  /* SK_MEM_MAPPED_IO */
DECL|macro|SK_HW_ADDR
mdefine_line|#define SK_HW_ADDR(Base, Addr)&t;&bslash;&n;&t;&t;&t;((Base) + (((Addr) &amp; 0x7f) | (((Addr) &gt;&gt; 7 &gt; 0) ? 0x80 : 0)))
macro_line|#endif /* SK_MEM_MAPPED_IO */
DECL|macro|SZ_LONG
mdefine_line|#define SZ_LONG&t;(sizeof(SK_U32))
multiline_comment|/*&n; *&t;Macro SK_HWAC_LINK_LED()&n; *&n; *&t;Use this macro to set the link LED mode.&n; * para:&n; *&t;pAC&t;&t;Pointer to adapter context struct&n; *&t;IoC&t;&t;I/O context needed for SK I/O macros&n; *  Port&t;Port number&n; *&t;Mode&t;Mode to set for this LED&n; */
DECL|macro|SK_HWAC_LINK_LED
mdefine_line|#define SK_HWAC_LINK_LED(pAC, IoC, Port, Mode) &bslash;&n;&t;SK_OUT8(IoC, MR_ADDR(Port, LNK_LED_REG), Mode);
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKGEHW_H */
eof
