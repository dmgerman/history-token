multiline_comment|/*&n; *  linux/include/asm-mips/tx3912.h&n; *&n; *  Copyright (C) 2001 Steven J. Hill (sjhill@realitydiluted.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Register includes for TMPR3912/05 and PR31700 processors&n; */
macro_line|#ifndef __TX3912_H__
DECL|macro|__TX3912_H__
mdefine_line|#define __TX3912_H__
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/******************************************************************************&n;*&n;* &t;01  General macro definitions&n;*&n;******************************************************************************/
DECL|macro|REGISTER_BASE
mdefine_line|#define REGISTER_BASE   0xb0c00000
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|macro|REG_AT
mdefine_line|#define REG_AT(x)&t;(*((volatile unsigned long *)(REGISTER_BASE + x)))
macro_line|#else
DECL|macro|REG_AT
mdefine_line|#define REG_AT(x)   (REGISTER_BASE + x)
macro_line|#endif
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;(1 &lt;&lt; x)
multiline_comment|/******************************************************************************&n;*&n;* &t;02  Bus Interface Unit&n;*&n;******************************************************************************/
DECL|macro|MemConfig0
mdefine_line|#define MemConfig0    REG_AT(0x000)
DECL|macro|MemConfig1
mdefine_line|#define MemConfig1    REG_AT(0x004)
DECL|macro|MemConfig2
mdefine_line|#define MemConfig2    REG_AT(0x008)
DECL|macro|MemConfig3
mdefine_line|#define MemConfig3    REG_AT(0x00c)
DECL|macro|MemConfig4
mdefine_line|#define MemConfig4    REG_AT(0x010)
DECL|macro|MemConfig5
mdefine_line|#define MemConfig5    REG_AT(0x014)
DECL|macro|MemConfig6
mdefine_line|#define MemConfig6    REG_AT(0x018)
DECL|macro|MemConfig7
mdefine_line|#define MemConfig7    REG_AT(0x01c)
DECL|macro|MemConfig8
mdefine_line|#define MemConfig8    REG_AT(0x020)
multiline_comment|/* Memory config register 1 */
DECL|macro|MEM1_ENCS1USER
mdefine_line|#define MEM1_ENCS1USER&t;BIT(21)
multiline_comment|/* Memory config register 3 */
DECL|macro|MEM3_CARD1ACCVAL_MASK
mdefine_line|#define MEM3_CARD1ACCVAL_MASK&t;(BIT(24) | BIT(25) | BIT(26) | BIT(27))
DECL|macro|MEM3_CARD1IOEN
mdefine_line|#define MEM3_CARD1IOEN&t;&t;BIT(4)
multiline_comment|/* Memory config register 4 */
DECL|macro|MEM4_ARBITRATIONEN
mdefine_line|#define MEM4_ARBITRATIONEN&t;BIT(29)
DECL|macro|MEM4_MEMPOWERDOWN
mdefine_line|#define MEM4_MEMPOWERDOWN&t;BIT(16)
DECL|macro|MEM4_ENREFRESH1
mdefine_line|#define MEM4_ENREFRESH1&t;&t;BIT(15)
DECL|macro|MEM4_ENREFRESH0
mdefine_line|#define MEM4_ENREFRESH0&t;&t;BIT(14)
DECL|macro|MEM4_ENWATCH
mdefine_line|#define MEM4_ENWATCH            BIT(24)
DECL|macro|MEM4_WATCHTIMEVAL_MASK
mdefine_line|#define MEM4_WATCHTIMEVAL_MASK  (0xf)
DECL|macro|MEM4_WATCHTIMEVAL_SHIFT
mdefine_line|#define MEM4_WATCHTIMEVAL_SHIFT (20)
DECL|macro|MEM4_WATCHTIME_VALUE
mdefine_line|#define MEM4_WATCHTIME_VALUE    (0xf)
multiline_comment|/*&n; ***********************************************************************&n; *&t;&t;&t;&t;&t;&t;&t;&t;       *&n; * 06  Clock Module&t;&t;&t;&t;&t;&t;       *&n; *&t;&t;&t;&t;&t;&t;&t;&t;       *&n; ***********************************************************************&n; */
DECL|macro|TX3912_CLK_CTRL_BASE
mdefine_line|#define TX3912_CLK_CTRL_BASE&t;&t;&t;(REGISTER_BASE + 0x1c0)
DECL|macro|TX3912_CLK_CTRL_CHICLKDIV_MASK
mdefine_line|#define TX3912_CLK_CTRL_CHICLKDIV_MASK&t;&t;0xff000000
DECL|macro|TX3912_CLK_CTRL_CHICLKDIV_SHIFT
mdefine_line|#define TX3912_CLK_CTRL_CHICLKDIV_SHIFT&t;&t;24
DECL|macro|TX3912_CLK_CTRL_ENCLKTEST
mdefine_line|#define TX3912_CLK_CTRL_ENCLKTEST&t;&t;0x00800000
DECL|macro|TX3912_CLK_CTRL_CLKTESTSELSIB
mdefine_line|#define TX3912_CLK_CTRL_CLKTESTSELSIB&t;&t;0x00400000
DECL|macro|TX3912_CLK_CTRL_CHIMCLKSEL
mdefine_line|#define TX3912_CLK_CTRL_CHIMCLKSEL&t;&t;0x00200000
DECL|macro|TX3912_CLK_CTRL_CHICLKDIR
mdefine_line|#define TX3912_CLK_CTRL_CHICLKDIR&t;&t;0x00100000
DECL|macro|TX3912_CLK_CTRL_ENCHIMCLK
mdefine_line|#define TX3912_CLK_CTRL_ENCHIMCLK&t;&t;0x00080000
DECL|macro|TX3912_CLK_CTRL_ENVIDCLK
mdefine_line|#define TX3912_CLK_CTRL_ENVIDCLK&t;&t;0x00040000
DECL|macro|TX3912_CLK_CTRL_ENMBUSCLK
mdefine_line|#define TX3912_CLK_CTRL_ENMBUSCLK&t;&t;0x00020000
DECL|macro|TX3912_CLK_CTRL_ENSPICLK
mdefine_line|#define TX3912_CLK_CTRL_ENSPICLK&t;&t;0x00010000
DECL|macro|TX3912_CLK_CTRL_ENTIMERCLK
mdefine_line|#define TX3912_CLK_CTRL_ENTIMERCLK&t;&t;0x00008000
DECL|macro|TX3912_CLK_CTRL_ENFASTTIMERCLK
mdefine_line|#define TX3912_CLK_CTRL_ENFASTTIMERCLK&t;&t;0x00004000
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIR
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIR&t;&t;0x00002000
DECL|macro|TX3912_CLK_CTRL_RESERVED
mdefine_line|#define TX3912_CLK_CTRL_RESERVED&t;&t;0x00001000
DECL|macro|TX3912_CLK_CTRL_ENSIBMCLK
mdefine_line|#define TX3912_CLK_CTRL_ENSIBMCLK&t;&t;0x00000800
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_MASK
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_MASK&t;&t;0x00000700
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_SHIFT
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_SHIFT&t;8
DECL|macro|TX3912_CLK_CTRL_CSERSEL
mdefine_line|#define TX3912_CLK_CTRL_CSERSEL&t;&t;&t;0x00000080
DECL|macro|TX3912_CLK_CTRL_CSERDIV_MASK
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_MASK&t;&t;0x00000070
DECL|macro|TX3912_CLK_CTRL_CSERDIV_SHIFT
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_SHIFT&t;&t;4
DECL|macro|TX3912_CLK_CTRL_ENCSERCLK
mdefine_line|#define TX3912_CLK_CTRL_ENCSERCLK&t;&t;0x00000008
DECL|macro|TX3912_CLK_CTRL_ENIRCLK
mdefine_line|#define TX3912_CLK_CTRL_ENIRCLK&t;&t;&t;0x00000004
DECL|macro|TX3912_CLK_CTRL_ENUARTACLK
mdefine_line|#define TX3912_CLK_CTRL_ENUARTACLK&t;&t;0x00000002
DECL|macro|TX3912_CLK_CTRL_ENUARTBCLK
mdefine_line|#define TX3912_CLK_CTRL_ENUARTBCLK&t;&t;0x00000001
multiline_comment|/******************************************************************************&n;*&n;* &t;07  CHI module&n;*&n;******************************************************************************/
DECL|macro|CHIControl
mdefine_line|#define CHIControl&t;&t;REG_AT(0x1D8)
DECL|macro|CHIPointerEnable
mdefine_line|#define CHIPointerEnable&t;REG_AT(0x1DC)
DECL|macro|CHIReceivePtrA
mdefine_line|#define CHIReceivePtrA&t;&t;REG_AT(0x1E0)
DECL|macro|CHIReceivePtrB
mdefine_line|#define CHIReceivePtrB&t;&t;REG_AT(0x1E4)
DECL|macro|CHITransmitPtrA
mdefine_line|#define CHITransmitPtrA&t;&t;REG_AT(0x1E8)
DECL|macro|CHITransmitPtrB
mdefine_line|#define CHITransmitPtrB&t;&t;REG_AT(0x1EC)
DECL|macro|CHISize
mdefine_line|#define CHISize&t;&t;&t;REG_AT(0x1F0)
DECL|macro|CHIReceiveStart
mdefine_line|#define CHIReceiveStart&t;&t;REG_AT(0x1F4)
DECL|macro|CHITransmitStart
mdefine_line|#define CHITransmitStart&t;REG_AT(0x1F8)
DECL|macro|CHIHoldingReg
mdefine_line|#define CHIHoldingReg&t;&t;REG_AT(0x1FC)
multiline_comment|/* CHI Control Register */
multiline_comment|/* &lt;incomplete!&gt; */
DECL|macro|CHI_RXEN
mdefine_line|#define&t;CHI_RXEN&t;&t;BIT(2)
DECL|macro|CHI_TXEN
mdefine_line|#define&t;CHI_TXEN&t;&t;BIT(1)
DECL|macro|CHI_ENCHI
mdefine_line|#define&t;CHI_ENCHI&t;&t;BIT(0)
multiline_comment|/******************************************************************************&n;*&n;*&t;08  Interrupt module&n;*&n;******************************************************************************/
multiline_comment|/* Register locations */
DECL|macro|IntStatus1
mdefine_line|#define IntStatus1    REG_AT(0x100)
DECL|macro|IntStatus2
mdefine_line|#define IntStatus2    REG_AT(0x104)
DECL|macro|IntStatus3
mdefine_line|#define IntStatus3    REG_AT(0x108)
DECL|macro|IntStatus4
mdefine_line|#define IntStatus4    REG_AT(0x10c)
DECL|macro|IntStatus5
mdefine_line|#define IntStatus5    REG_AT(0x110)
DECL|macro|IntStatus6
mdefine_line|#define IntStatus6    REG_AT(0x114)
DECL|macro|IntClear1
mdefine_line|#define IntClear1     REG_AT(0x100)
DECL|macro|IntClear2
mdefine_line|#define IntClear2     REG_AT(0x104)
DECL|macro|IntClear3
mdefine_line|#define IntClear3     REG_AT(0x108)
DECL|macro|IntClear4
mdefine_line|#define IntClear4     REG_AT(0x10c)
DECL|macro|IntClear5
mdefine_line|#define IntClear5     REG_AT(0x110)
DECL|macro|IntClear6
mdefine_line|#define IntClear6     REG_AT(0x114)
DECL|macro|IntEnable1
mdefine_line|#define IntEnable1    REG_AT(0x118)
DECL|macro|IntEnable2
mdefine_line|#define IntEnable2    REG_AT(0x11c)
DECL|macro|IntEnable3
mdefine_line|#define IntEnable3    REG_AT(0x120)
DECL|macro|IntEnable4
mdefine_line|#define IntEnable4    REG_AT(0x124)
DECL|macro|IntEnable5
mdefine_line|#define IntEnable5    REG_AT(0x128)
DECL|macro|IntEnable6
mdefine_line|#define IntEnable6    REG_AT(0x12c)
multiline_comment|/* Interrupt Status Register 1 at offset 100 */
DECL|macro|INT1_LCDINT
mdefine_line|#define INT1_LCDINT&t;&t;BIT(31)
DECL|macro|INT1_DFINT
mdefine_line|#define INT1_DFINT              BIT(30)
DECL|macro|INT1_CHIDMAHALF
mdefine_line|#define INT1_CHIDMAHALF&t;&t;BIT(29)
DECL|macro|INT1_CHIDMAFULL
mdefine_line|#define INT1_CHIDMAFULL&t;&t;BIT(28)
DECL|macro|INT1_CHIDMACNTINT
mdefine_line|#define INT1_CHIDMACNTINT       BIT(27)
DECL|macro|INT1_CHIRXAINT
mdefine_line|#define INT1_CHIRXAINT&t;&t;BIT(26)
DECL|macro|INT1_CHIRXBINT
mdefine_line|#define INT1_CHIRXBINT&t;&t;BIT(25)
DECL|macro|INT1_CHIACTINT
mdefine_line|#define INT1_CHIACTINT          BIT(24)
DECL|macro|INT1_CHIERRINT
mdefine_line|#define INT1_CHIERRINT          BIT(23)
DECL|macro|INT1_SND0_5INT
mdefine_line|#define INT1_SND0_5INT          BIT(22)
DECL|macro|INT1_SND1_0INT
mdefine_line|#define INT1_SND1_0INT&t;&t;BIT(21)
DECL|macro|INT1_TEL0_5INT
mdefine_line|#define INT1_TEL0_5INT          BIT(20)
DECL|macro|INT1_TEL1_0INT
mdefine_line|#define INT1_TEL1_0INT          BIT(19)
DECL|macro|INT1_SNDDMACNTINT
mdefine_line|#define INT1_SNDDMACNTINT       BIT(18)
DECL|macro|INT1_TELDMACNTINT
mdefine_line|#define INT1_TELDMACNTINT       BIT(17)
DECL|macro|INT1_LSNDCLIPINT
mdefine_line|#define INT1_LSNDCLIPINT        BIT(16)
DECL|macro|INT1_RSNDCLIPINT
mdefine_line|#define INT1_RSNDCLIPINT        BIT(15)
DECL|macro|INT1_VALSNDPOSINT
mdefine_line|#define INT1_VALSNDPOSINT       BIT(14)
DECL|macro|INT1_VALSNDNEGINT
mdefine_line|#define INT1_VALSNDNEGINT       BIT(13)
DECL|macro|INT1_VALTELPOSINT
mdefine_line|#define INT1_VALTELPOSINT       BIT(12)
DECL|macro|INT1_VALTELNEGINT
mdefine_line|#define INT1_VALTELNEGINT       BIT(11)
DECL|macro|INT1_SNDININT
mdefine_line|#define INT1_SNDININT           BIT(10)
DECL|macro|INT1_TELININT
mdefine_line|#define INT1_TELININT           BIT(9)
DECL|macro|INT1_SIBSF0INT
mdefine_line|#define INT1_SIBSF0INT          BIT(8)
DECL|macro|INT1_SIBSF1INT
mdefine_line|#define INT1_SIBSF1INT          BIT(7)
DECL|macro|INT1_SIBIRQPOSINT
mdefine_line|#define INT1_SIBIRQPOSINT       BIT(6)
DECL|macro|INT1_SIBIRQNEGINT
mdefine_line|#define INT1_SIBIRQNEGINT       BIT(5)
multiline_comment|/* Interrupt Status Register 2 at offset 104 */
DECL|macro|INT2_UARTARXINT
mdefine_line|#define INT2_UARTARXINT&t;&t;BIT(31)
DECL|macro|INT2_UARTARXOVERRUN
mdefine_line|#define INT2_UARTARXOVERRUN&t;BIT(30)
DECL|macro|INT2_UARTAFRAMEINT
mdefine_line|#define INT2_UARTAFRAMEINT&t;BIT(29)
DECL|macro|INT2_UARTABREAKINT
mdefine_line|#define INT2_UARTABREAKINT&t;BIT(28)
DECL|macro|INT2_UARTATXINT
mdefine_line|#define INT2_UARTATXINT&t;&t;BIT(26)
DECL|macro|INT2_UARTATXOVERRUN
mdefine_line|#define INT2_UARTATXOVERRUN&t;BIT(25)
DECL|macro|INT2_UARTAEMPTY
mdefine_line|#define INT2_UARTAEMPTY&t;&t;BIT(24)
DECL|macro|INT2_UARTBRXINT
mdefine_line|#define INT2_UARTBRXINT&t;&t;BIT(21)
DECL|macro|INT2_UARTBRXOVERRUN
mdefine_line|#define INT2_UARTBRXOVERRUN&t;BIT(20)
DECL|macro|INT2_UARTBFRAMEINT
mdefine_line|#define INT2_UARTBFRAMEINT&t;BIT(29)
DECL|macro|INT2_UARTBBREAKINT
mdefine_line|#define INT2_UARTBBREAKINT&t;BIT(18)
DECL|macro|INT2_UARTBTXINT
mdefine_line|#define INT2_UARTBTXINT&t;&t;BIT(16)
DECL|macro|INT2_UARTBTXOVERRUN
mdefine_line|#define INT2_UARTBTXOVERRUN&t;BIT(15)
DECL|macro|INT2_UARTBEMPTY
mdefine_line|#define INT2_UARTBEMPTY&t;&t;BIT(14)
DECL|macro|INT2_UARTA_RX
mdefine_line|#define INT2_UARTA_RX&t;&t;(BIT(31) | BIT(30) | BIT(29) | BIT(28) | BIT(27))
DECL|macro|INT2_UARTA_TX
mdefine_line|#define INT2_UARTA_TX&t;&t;(BIT(26) | BIT(25) | BIT(24))
DECL|macro|INT2_UARTA_DMA
mdefine_line|#define INT2_UARTA_DMA&t;&t;(BIT(23) | BIT(22))
DECL|macro|INT2_UARTB_RX
mdefine_line|#define INT2_UARTB_RX&t;&t;(BIT(21) | BIT(20) | BIT(19) | BIT(18) | BIT(17))
DECL|macro|INT2_UARTB_TX
mdefine_line|#define INT2_UARTB_TX&t;&t;(BIT(16) | BIT(15) | BIT(14))
DECL|macro|INT2_UARTB_DMA
mdefine_line|#define INT2_UARTB_DMA&t;&t;(BIT(13) | BIT(12))
multiline_comment|/* Interrupt Status Register 5 */
DECL|macro|INT5_RTCINT
mdefine_line|#define INT5_RTCINT&t; BIT(31)
DECL|macro|INT5_ALARMINT
mdefine_line|#define INT5_ALARMINT&t; BIT(30)
DECL|macro|INT5_PERIODICINT
mdefine_line|#define INT5_PERIODICINT BIT(29)
DECL|macro|INT5_POSPWRINT
mdefine_line|#define INT5_POSPWRINT &t; BIT(27)
DECL|macro|INT5_NEGPWRINT
mdefine_line|#define INT5_NEGPWRINT&t; BIT(26)
DECL|macro|INT5_POSPWROKINT
mdefine_line|#define INT5_POSPWROKINT BIT(25)
DECL|macro|INT5_NEGPWROKINT
mdefine_line|#define INT5_NEGPWROKINT BIT(24)
DECL|macro|INT5_POSONBUTINT
mdefine_line|#define INT5_POSONBUTINT BIT(23)
DECL|macro|INT5_NEGONBUTINT
mdefine_line|#define INT5_NEGONBUTINT BIT(22)
DECL|macro|INT5_SPIAVAILINT
mdefine_line|#define INT5_SPIAVAILINT BIT(21)        /* 0x0020 0000 */
DECL|macro|INT5_SPIERRINT
mdefine_line|#define INT5_SPIERRINT   BIT(20)        /* 0x0010 0000 */
DECL|macro|INT5_SPIRCVINT
mdefine_line|#define INT5_SPIRCVINT&t; BIT(19)&t;/* 0x0008 0000 */
DECL|macro|INT5_SPIEMPTYINT
mdefine_line|#define INT5_SPIEMPTYINT BIT(18)&t;/* 0x0004 0000 */
DECL|macro|INT5_IOPOSINT6
mdefine_line|#define INT5_IOPOSINT6&t; BIT(13)
DECL|macro|INT5_IOPOSINT5
mdefine_line|#define INT5_IOPOSINT5&t; BIT(12)
DECL|macro|INT5_IOPOSINT4
mdefine_line|#define INT5_IOPOSINT4&t; BIT(11)
DECL|macro|INT5_IOPOSINT3
mdefine_line|#define INT5_IOPOSINT3&t; BIT(10)
DECL|macro|INT5_IOPOSINT2
mdefine_line|#define INT5_IOPOSINT2&t; BIT(9)
DECL|macro|INT5_IOPOSINT1
mdefine_line|#define INT5_IOPOSINT1&t; BIT(8)
DECL|macro|INT5_IOPOSINT0
mdefine_line|#define INT5_IOPOSINT0&t; BIT(7)
DECL|macro|INT5_IONEGINT6
mdefine_line|#define INT5_IONEGINT6&t; BIT(6)
DECL|macro|INT5_IONEGINT5
mdefine_line|#define INT5_IONEGINT5&t; BIT(5)
DECL|macro|INT5_IONEGINT4
mdefine_line|#define INT5_IONEGINT4&t; BIT(4)
DECL|macro|INT5_IONEGINT3
mdefine_line|#define INT5_IONEGINT3&t; BIT(3)
DECL|macro|INT5_IONEGINT2
mdefine_line|#define INT5_IONEGINT2&t; BIT(2)
DECL|macro|INT5_IONEGINT1
mdefine_line|#define INT5_IONEGINT1&t; BIT(1)
DECL|macro|INT5_IONEGINT0
mdefine_line|#define INT5_IONEGINT0&t; BIT(0)
DECL|macro|INT5_IONEGINT_SHIFT
mdefine_line|#define INT5_IONEGINT_SHIFT 0
DECL|macro|INT5_IONEGINT_MASK
mdefine_line|#define&t;INT5_IONEGINT_MASK  (0x7F&lt;&lt;INT5_IONEGINT_SHIFT)
DECL|macro|INT5_IOPOSINT_SHIFT
mdefine_line|#define INT5_IOPOSINT_SHIFT 7
DECL|macro|INT5_IOPOSINT_MASK
mdefine_line|#define&t;INT5_IOPOSINT_MASK  (0x7F&lt;&lt;INT5_IOPOSINT_SHIFT)
multiline_comment|/* Interrupt Status Register 6 */
DECL|macro|INT6_IRQHIGH
mdefine_line|#define INT6_IRQHIGH&t;BIT(31)
DECL|macro|INT6_IRQLOW
mdefine_line|#define INT6_IRQLOW&t;BIT(30)
DECL|macro|INT6_INTVECT
mdefine_line|#define INT6_INTVECT&t;(BIT(5) | BIT(4) | BIT(3) | BIT(2))
multiline_comment|/* Interrupt Enable Register 6 */
DECL|macro|INT6_GLOBALEN
mdefine_line|#define INT6_GLOBALEN&t;&t;BIT(18)
DECL|macro|INT6_PWROKINT
mdefine_line|#define INT6_PWROKINT&t;&t;BIT(15)
DECL|macro|INT6_ALARMINT
mdefine_line|#define&t;INT6_ALARMINT&t;&t;BIT(14)
DECL|macro|INT6_PERIODICINT
mdefine_line|#define INT6_PERIODICINT &t;BIT(13)
DECL|macro|INT6_MBUSINT
mdefine_line|#define&t;INT6_MBUSINT&t;&t;BIT(12)
DECL|macro|INT6_UARTARXINT
mdefine_line|#define INT6_UARTARXINT&t;&t;BIT(11)
DECL|macro|INT6_UARTBRXINT
mdefine_line|#define INT6_UARTBRXINT&t;&t;BIT(10)
DECL|macro|INT6_MFIOPOSINT1619
mdefine_line|#define&t;INT6_MFIOPOSINT1619&t;BIT(9)
DECL|macro|INT6_IOPOSINT56
mdefine_line|#define INT6_IOPOSINT56         BIT(8)
DECL|macro|INT6_MFIONEGINT1619
mdefine_line|#define&t;INT6_MFIONEGINT1619&t;BIT(7)
DECL|macro|INT6_IONEGINT56
mdefine_line|#define INT6_IONEGINT56         BIT(6)
DECL|macro|INT6_MBUSDMAFULLINT
mdefine_line|#define&t;INT6_MBUSDMAFULLINT&t;BIT(5)
DECL|macro|INT6_SNDDMACNTINT
mdefine_line|#define&t;INT6_SNDDMACNTINT&t;BIT(4)
DECL|macro|INT6_TELDMACNTINT
mdefine_line|#define&t;INT6_TELDMACNTINT&t;BIT(3)
DECL|macro|INT6_CHIDMACNTINT
mdefine_line|#define&t;INT6_CHIDMACNTINT&t;BIT(2)
DECL|macro|INT6_IOPOSNEGINT0
mdefine_line|#define INT6_IOPOSNEGINT0       BIT(1)
multiline_comment|/******************************************************************************&n;*&n;*&t;09  GPIO and MFIO modules&n;*&n;******************************************************************************/
DECL|macro|IOControl
mdefine_line|#define IOControl   &t;REG_AT(0x180)
DECL|macro|MFIOOutput
mdefine_line|#define MFIOOutput   &t;REG_AT(0x184)
DECL|macro|MFIODirection
mdefine_line|#define MFIODirection  &t;REG_AT(0x188)
DECL|macro|MFIOInput
mdefine_line|#define MFIOInput  &t;REG_AT(0x18c)
DECL|macro|MFIOSelect
mdefine_line|#define MFIOSelect   &t;REG_AT(0x190)
DECL|macro|IOPowerDown
mdefine_line|#define IOPowerDown   &t;REG_AT(0x194)
DECL|macro|MFIOPowerDown
mdefine_line|#define MFIOPowerDown  &t;REG_AT(0x198)
DECL|macro|IODIN_MASK
mdefine_line|#define IODIN_MASK      0x0000007f
DECL|macro|IODIN_SHIFT
mdefine_line|#define IODIN_SHIFT     0
DECL|macro|IODOUT_MASK
mdefine_line|#define IODOUT_MASK     0x00007f00
DECL|macro|IODOUT_SHIFT
mdefine_line|#define IODOUT_SHIFT    8
DECL|macro|IODIREC_MASK
mdefine_line|#define IODIREC_MASK    0x007f0000
DECL|macro|IODIREC_SHIFT
mdefine_line|#define IODIREC_SHIFT   16
DECL|macro|IODEBSEL_MASK
mdefine_line|#define IODEBSEL_MASK   0x7f000000
DECL|macro|IODEBSEL_SHIFT
mdefine_line|#define IODEBSEL_SHIFT  24
multiline_comment|/******************************************************************************&n;*&n;*&t;10  IR module&n;*&n;******************************************************************************/
DECL|macro|IRControl1
mdefine_line|#define IRControl1                  REG_AT(0x0a0)
DECL|macro|IRControl2
mdefine_line|#define IRControl2                  REG_AT(0x0a4)
multiline_comment|/* IR Control 1 Register */
DECL|macro|IR_CARDRET
mdefine_line|#define IR_CARDRET                  BIT(24)
DECL|macro|IR_BAUDVAL_MASK
mdefine_line|#define IR_BAUDVAL_MASK             0x00ff0000
DECL|macro|IR_BAUDVAL_SHIFT
mdefine_line|#define IR_BAUDVAL_SHIFT            16
DECL|macro|IR_TESTIR
mdefine_line|#define IR_TESTIR                   BIT(4)
DECL|macro|IR_DTINVERT
mdefine_line|#define IR_DTINVERT                 BIT(3)
DECL|macro|IR_RXPWR
mdefine_line|#define IR_RXPWR                    BIT(2)
DECL|macro|IR_ENSTATE
mdefine_line|#define IR_ENSTATE                  BIT(1)
DECL|macro|IR_ENCONSM
mdefine_line|#define IR_ENCONSM                  BIT(0)
multiline_comment|/* IR Control 2 Register */
DECL|macro|IR_PER_MASK
mdefine_line|#define IR_PER_MASK                 0xff000000
DECL|macro|IR_PER_SHIFT
mdefine_line|#define IR_PER_SHIFT                24
DECL|macro|IR_ONTIME_MASK
mdefine_line|#define IR_ONTIME_MASK              0x00ff0000
DECL|macro|IR_ONTIME_SHIFT
mdefine_line|#define IR_ONTIME_SHIFT             16
DECL|macro|IR_DELAYVAL_MASK
mdefine_line|#define IR_DELAYVAL_MASK            0x0000ff00
DECL|macro|IR_DELAYVAL_SHIFT
mdefine_line|#define IR_DELAYVAL_SHIFT           8
DECL|macro|IR_WAITVAL_MASK
mdefine_line|#define IR_WAITVAL_MASK             0x000000ff
DECL|macro|IR_WAITVAL_SHIFT
mdefine_line|#define IR_WAITVAL_SHIFT            0
multiline_comment|/******************************************************************************&n;*&n;*&t;11  Magicbus Module&n;*&n;******************************************************************************/
DECL|macro|MbusCntrl1
mdefine_line|#define MbusCntrl1&t;&t;REG_AT(0x0e0)
DECL|macro|MbusCntrl2
mdefine_line|#define MbusCntrl2&t;&t;REG_AT(0x0e4)
DECL|macro|MbusDMACntrl1
mdefine_line|#define MbusDMACntrl1&t;&t;REG_AT(0x0e8)
DECL|macro|MbusDMACntrl2
mdefine_line|#define MbusDMACntrl2&t;&t;REG_AT(0x0ec)
DECL|macro|MbusDMACount
mdefine_line|#define MbusDMACount&t;&t;REG_AT(0x0f0)
DECL|macro|MbusTxReg
mdefine_line|#define MbusTxReg&t;&t;REG_AT(0x0f4)
DECL|macro|MbusRxReg
mdefine_line|#define MbusRxReg&t;&t;REG_AT(0x0f8)
DECL|macro|MBUS_CLKPOL
mdefine_line|#define&t;MBUS_CLKPOL&t;&t;BIT(4)
DECL|macro|MBUS_SLAVE
mdefine_line|#define&t;MBUS_SLAVE&t;&t;BIT(3)
DECL|macro|MBUS_FSLAVE
mdefine_line|#define&t;MBUS_FSLAVE&t;&t;BIT(2)
DECL|macro|MBUS_LONG
mdefine_line|#define&t;MBUS_LONG&t;&t;BIT(1)
DECL|macro|MBUS_ENMBUS
mdefine_line|#define&t;MBUS_ENMBUS&t;&t;BIT(0)
multiline_comment|/******************************************************************************&n;*&n;*&t;12  Power module&n;*&n;******************************************************************************/
DECL|macro|PowerControl
mdefine_line|#define PowerControl   &t;            REG_AT(0x1C4)
DECL|macro|PWR_ONBUTN
mdefine_line|#define PWR_ONBUTN                  BIT(31)
DECL|macro|PWR_PWRINT
mdefine_line|#define PWR_PWRINT                  BIT(30)
DECL|macro|PWR_PWROK
mdefine_line|#define PWR_PWROK                   BIT(29)
DECL|macro|PWR_VIDRF_MASK
mdefine_line|#define PWR_VIDRF_MASK              (BIT(28) | BIT(27))
DECL|macro|PWR_VIDRF_SHIFT
mdefine_line|#define PWR_VIDRF_SHIFT             27
DECL|macro|PWR_SLOWBUS
mdefine_line|#define PWR_SLOWBUS                 BIT(26)
DECL|macro|PWR_DIVMOD
mdefine_line|#define PWR_DIVMOD                  BIT(25)
DECL|macro|PWR_STPTIMERVAL_MASK
mdefine_line|#define PWR_STPTIMERVAL_MASK        (BIT(15) | BIT(14) | BIT(13) | BIT(12))
DECL|macro|PWR_STPTIMERVAL_SHIFT
mdefine_line|#define PWR_STPTIMERVAL_SHIFT       12
DECL|macro|PWR_ENSTPTIMER
mdefine_line|#define PWR_ENSTPTIMER              BIT(11)
DECL|macro|PWR_ENFORCESHUTDWN
mdefine_line|#define PWR_ENFORCESHUTDWN          BIT(10)
DECL|macro|PWR_FORCESHUTDWN
mdefine_line|#define PWR_FORCESHUTDWN            BIT(9)
DECL|macro|PWR_FORCESHUTDWNOCC
mdefine_line|#define PWR_FORCESHUTDWNOCC         BIT(8)
DECL|macro|PWR_SELC2MS
mdefine_line|#define PWR_SELC2MS                 BIT(7)
DECL|macro|PWR_BPDBVCC3
mdefine_line|#define PWR_BPDBVCC3                BIT(5)
DECL|macro|PWR_STOPCPU
mdefine_line|#define PWR_STOPCPU                 BIT(4)
DECL|macro|PWR_DBNCONBUTN
mdefine_line|#define PWR_DBNCONBUTN              BIT(3)
DECL|macro|PWR_COLDSTART
mdefine_line|#define PWR_COLDSTART               BIT(2)
DECL|macro|PWR_PWRCS
mdefine_line|#define PWR_PWRCS                   BIT(1)
DECL|macro|PWR_VCCON
mdefine_line|#define PWR_VCCON                   BIT(0)
multiline_comment|/******************************************************************************&n;*&n;*&t;13  SIB (Serial Interconnect Bus) Module&n;*&n;******************************************************************************/
multiline_comment|/* Register locations */
DECL|macro|SIBSize
mdefine_line|#define SIBSize&t;      &t;        REG_AT(0x060)
DECL|macro|SIBSoundRXStart
mdefine_line|#define SIBSoundRXStart&t;      &t;REG_AT(0x064)
DECL|macro|SIBSoundTXStart
mdefine_line|#define SIBSoundTXStart         REG_AT(0x068)
DECL|macro|SIBTelecomRXStart
mdefine_line|#define SIBTelecomRXStart       REG_AT(0x06C)
DECL|macro|SIBTelecomTXStart
mdefine_line|#define SIBTelecomTXStart       REG_AT(0x070)
DECL|macro|SIBControl
mdefine_line|#define SIBControl              REG_AT(0x074)
DECL|macro|SIBSoundTXRXHolding
mdefine_line|#define SIBSoundTXRXHolding     REG_AT(0x078)
DECL|macro|SIBTelecomTXRXHolding
mdefine_line|#define SIBTelecomTXRXHolding   REG_AT(0x07C)
DECL|macro|SIBSubFrame0Control
mdefine_line|#define SIBSubFrame0Control     REG_AT(0x080)
DECL|macro|SIBSubFrame1Control
mdefine_line|#define SIBSubFrame1Control     REG_AT(0x084)
DECL|macro|SIBSubFrame0Status
mdefine_line|#define SIBSubFrame0Status      REG_AT(0x088)
DECL|macro|SIBSubFrame1Status
mdefine_line|#define SIBSubFrame1Status      REG_AT(0x08C)
DECL|macro|SIBDMAControl
mdefine_line|#define SIBDMAControl           REG_AT(0x090)
multiline_comment|/* SIB Size Register */
DECL|macro|SIB_SNDSIZE_MASK
mdefine_line|#define SIB_SNDSIZE_MASK        0x3ffc0000
DECL|macro|SIB_SNDSIZE_SHIFT
mdefine_line|#define SIB_SNDSIZE_SHIFT       18
DECL|macro|SIB_TELSIZE_MASK
mdefine_line|#define SIB_TELSIZE_MASK        0x00003ffc
DECL|macro|SIB_TELSIZE_SHIFT
mdefine_line|#define SIB_TELSIZE_SHIFT       2
multiline_comment|/* SIB Control Register */
DECL|macro|SIB_SIBIRQ
mdefine_line|#define SIB_SIBIRQ              BIT(31)
DECL|macro|SIB_ENCNTTEST
mdefine_line|#define SIB_ENCNTTEST           BIT(30)
DECL|macro|SIB_ENDMATEST
mdefine_line|#define SIB_ENDMATEST           BIT(29)
DECL|macro|SIB_SNDMONO
mdefine_line|#define SIB_SNDMONO             BIT(28)
DECL|macro|SIB_RMONOSNDIN
mdefine_line|#define SIB_RMONOSNDIN          BIT(27)
DECL|macro|SIB_SIBSCLKDIV_MASK
mdefine_line|#define SIB_SIBSCLKDIV_MASK     (BIT(26) | BIT(25) | BIT(24))
DECL|macro|SIB_SIBSCLKDIV_SHIFT
mdefine_line|#define SIB_SIBSCLKDIV_SHIFT    24
DECL|macro|SIB_TEL16
mdefine_line|#define SIB_TEL16               BIT(23)
DECL|macro|SIB_TELFSDIV_MASK
mdefine_line|#define SIB_TELFSDIV_MASK       0x007f0000
DECL|macro|SIB_TELFSDIV_SHIFT
mdefine_line|#define SIB_TELFSDIV_SHIFT      16
DECL|macro|SIB_SND16
mdefine_line|#define SIB_SND16               BIT(15)
DECL|macro|SIB_SNDFSDIV_MASK
mdefine_line|#define SIB_SNDFSDIV_MASK       0x00007f00
DECL|macro|SIB_SNDFSDIV_SHIFT
mdefine_line|#define SIB_SNDFSDIV_SHIFT      8
DECL|macro|SIB_SELTELSF1
mdefine_line|#define SIB_SELTELSF1           BIT(7)
DECL|macro|SIB_SELSNDSF1
mdefine_line|#define SIB_SELSNDSF1           BIT(6)
DECL|macro|SIB_ENTEL
mdefine_line|#define SIB_ENTEL               BIT(5)
DECL|macro|SIB_ENSND
mdefine_line|#define SIB_ENSND               BIT(4)
DECL|macro|SIB_SIBLOOP
mdefine_line|#define SIB_SIBLOOP             BIT(3)
DECL|macro|SIB_ENSF1
mdefine_line|#define SIB_ENSF1               BIT(2)
DECL|macro|SIB_ENSF0
mdefine_line|#define SIB_ENSF0               BIT(1)
DECL|macro|SIB_ENSIB
mdefine_line|#define SIB_ENSIB               BIT(0)
multiline_comment|/* SIB Frame Format (SIBSubFrame0Status and SIBSubFrame1Status) */
DECL|macro|SIB_REGISTER_EXT
mdefine_line|#define SIB_REGISTER_EXT        BIT(31)  /* Must be zero */
DECL|macro|SIB_ADDRESS_MASK
mdefine_line|#define SIB_ADDRESS_MASK        0x78000000
DECL|macro|SIB_ADDRESS_SHIFT
mdefine_line|#define SIB_ADDRESS_SHIFT       27
DECL|macro|SIB_WRITE
mdefine_line|#define SIB_WRITE               BIT(26)
DECL|macro|SIB_AUD_VALID
mdefine_line|#define SIB_AUD_VALID           BIT(17)
DECL|macro|SIB_TEL_VALID
mdefine_line|#define SIB_TEL_VALID           BIT(16)
DECL|macro|SIB_DATA_MASK
mdefine_line|#define SIB_DATA_MASK           0x00ff
DECL|macro|SIB_DATA_SHIFT
mdefine_line|#define SIB_DATA_SHIFT          0
multiline_comment|/* SIB DMA Control Register */
DECL|macro|SIB_SNDBUFF1TIME
mdefine_line|#define SIB_SNDBUFF1TIME        BIT(31)
DECL|macro|SIB_SNDDMALOOP
mdefine_line|#define SIB_SNDDMALOOP          BIT(30)
DECL|macro|SIB_SNDDMAPTR_MASK
mdefine_line|#define SIB_SNDDMAPTR_MASK      0x3ffc0000
DECL|macro|SIB_SNDDMAPTR_SHIFT
mdefine_line|#define SIB_SNDDMAPTR_SHIFT     18
DECL|macro|SIB_ENDMARXSND
mdefine_line|#define SIB_ENDMARXSND          BIT(17)
DECL|macro|SIB_ENDMATXSND
mdefine_line|#define SIB_ENDMATXSND          BIT(16)
DECL|macro|SIB_TELBUFF1TIME
mdefine_line|#define SIB_TELBUFF1TIME        BIT(15)
DECL|macro|SIB_TELDMALOOP
mdefine_line|#define SIB_TELDMALOOP          BIT(14)
DECL|macro|SIB_TELDMAPTR_MASK
mdefine_line|#define SIB_TELDMAPTR_MASK      0x00003ffc
DECL|macro|SIB_TELDMAPTR_SHIFT
mdefine_line|#define SIB_TELDMAPTR_SHIFT     2
DECL|macro|SIB_ENDMARXTEL
mdefine_line|#define SIB_ENDMARXTEL          BIT(1)
DECL|macro|SIB_ENDMATXTEL
mdefine_line|#define SIB_ENDMATXTEL          BIT(0)
multiline_comment|/******************************************************************************&n;*&n;* &t;14  SPI module&n;*&n;******************************************************************************/
DECL|macro|SPIControl
mdefine_line|#define SPIControl&t;&t;REG_AT(0x160)
DECL|macro|SPITransmit
mdefine_line|#define SPITransmit&t;&t;REG_AT(0x164)
DECL|macro|SPIReceive
mdefine_line|#define SPIReceive&t;&t;REG_AT(0x164)
DECL|macro|SPI_SPION
mdefine_line|#define SPI_SPION&t;&t;BIT(17)
DECL|macro|SPI_EMPTY
mdefine_line|#define SPI_EMPTY&t;&t;BIT(16)
DECL|macro|SPI_DELAYVAL_MASK
mdefine_line|#define SPI_DELAYVAL_MASK&t;(BIT(12) | BIT(13) | BIT(14) | BIT(15))
DECL|macro|SPI_DELAYVAL_SHIFT
mdefine_line|#define SPI_DELAYVAL_SHIFT&t;12
DECL|macro|SPI_BAUDRATE_MASK
mdefine_line|#define&t;SPI_BAUDRATE_MASK&t;(BIT(8) | BIT(9) | BIT(10) | BIT(11))
DECL|macro|SPI_BAUDRATE_SHIFT
mdefine_line|#define&t;SPI_BAUDRATE_SHIFT&t;8
DECL|macro|SPI_PHAPOL
mdefine_line|#define&t;SPI_PHAPOL&t;&t;BIT(5)
DECL|macro|SPI_CLKPOL
mdefine_line|#define&t;SPI_CLKPOL&t;&t;BIT(4)
DECL|macro|SPI_WORD
mdefine_line|#define&t;SPI_WORD&t;&t;BIT(2)
DECL|macro|SPI_LSB
mdefine_line|#define&t;SPI_LSB&t;&t;&t;BIT(1)
DECL|macro|SPI_ENSPI
mdefine_line|#define&t;SPI_ENSPI&t;&t;BIT(0)
multiline_comment|/******************************************************************************&n;*&n;*&t;15  Timer module&n;*&n;******************************************************************************/
DECL|macro|RTChigh
mdefine_line|#define RTChigh&t;      &t;REG_AT(0x140)
DECL|macro|RTClow
mdefine_line|#define RTClow&t;        REG_AT(0x144)
DECL|macro|RTCalarmHigh
mdefine_line|#define RTCalarmHigh    REG_AT(0x148)
DECL|macro|RTCalarmLow
mdefine_line|#define RTCalarmLow     REG_AT(0x14c)
DECL|macro|RTCtimerControl
mdefine_line|#define RTCtimerControl REG_AT(0x150)
DECL|macro|RTCperiodTimer
mdefine_line|#define RTCperiodTimer  REG_AT(0x154)
multiline_comment|/* RTC Timer Control */
DECL|macro|TIM_FREEZEPRE
mdefine_line|#define TIM_FREEZEPRE&t;BIT(7)
DECL|macro|TIM_FREEZERTC
mdefine_line|#define TIM_FREEZERTC&t;BIT(6)
DECL|macro|TIM_FREEZETIMER
mdefine_line|#define TIM_FREEZETIMER&t;BIT(5)
DECL|macro|TIM_ENPERTIMER
mdefine_line|#define TIM_ENPERTIMER&t;BIT(4)
DECL|macro|TIM_RTCCLEAR
mdefine_line|#define TIM_RTCCLEAR&t;BIT(3)
DECL|macro|RTC_HIGHMASK
mdefine_line|#define&t;RTC_HIGHMASK&t;(0xFF)
multiline_comment|/* RTC Periodic Timer */
DECL|macro|TIM_PERCNT
mdefine_line|#define&t;TIM_PERCNT&t;0xFFFF0000
DECL|macro|TIM_PERVAL
mdefine_line|#define&t;TIM_PERVAL&t;0x0000FFFF
multiline_comment|/* For a system clock frequency of 36.864MHz, the timer counts at one tick&n;   every 868nS (ie CLK/32). Therefore 11520 counts gives a 10mS interval&n; */
DECL|macro|PER_TIMER_COUNT
mdefine_line|#define PER_TIMER_COUNT (1152000/HZ)
multiline_comment|/*&n; ***********************************************************************&n; *&t;&t;&t;&t;&t;&t;&t;&t;       *&n; * 15  UART Module&t;&t;&t;&t;&t;&t;       *&n; *&t;&t;&t;&t;&t;&t;&t;&t;       *&n; ***********************************************************************&n; */
DECL|macro|TX3912_UARTA_BASE
mdefine_line|#define TX3912_UARTA_BASE       (REGISTER_BASE + 0x0b0)
DECL|macro|TX3912_UARTB_BASE
mdefine_line|#define TX3912_UARTB_BASE       (REGISTER_BASE + 0x0c8)
multiline_comment|/*&n; * TX3912 UART register offsets&n; */
DECL|macro|TX3912_UART_CTRL1
mdefine_line|#define TX3912_UART_CTRL1       0x00
DECL|macro|TX3912_UART_CTRL2
mdefine_line|#define TX3912_UART_CTRL2       0x04
DECL|macro|TX3912_UART_DMA_CTRL1
mdefine_line|#define TX3912_UART_DMA_CTRL1   0x08
DECL|macro|TX3912_UART_DMA_CTRL2
mdefine_line|#define TX3912_UART_DMA_CTRL2   0x0c
DECL|macro|TX3912_UART_DMA_CNT
mdefine_line|#define TX3912_UART_DMA_CNT     0x10
DECL|macro|TX3912_UART_DATA
mdefine_line|#define TX3912_UART_DATA        0x14
DECL|macro|UartA_Ctrl1
mdefine_line|#define UartA_Ctrl1   REG_AT(0x0b0)
DECL|macro|UartA_Data
mdefine_line|#define UartA_Data    REG_AT(0x0c4)
multiline_comment|/*&n; * Defines for UART Control Register 1&n; */
DECL|macro|TX3912_UART_CTRL1_UARTON
mdefine_line|#define TX3912_UART_CTRL1_UARTON&t;0x80000000
DECL|macro|UART_TX_EMPTY
mdefine_line|#define UART_TX_EMPTY&t;&t;BIT(30)
DECL|macro|UART_PRX_HOLD_FULL
mdefine_line|#define UART_PRX_HOLD_FULL&t;BIT(29)
DECL|macro|UART_RX_HOLD_FULL
mdefine_line|#define UART_RX_HOLD_FULL&t;BIT(28)
DECL|macro|UART_EN_DMA_RX
mdefine_line|#define UART_EN_DMA_RX &t;&t;BIT(15)
DECL|macro|UART_EN_DMA_TX
mdefine_line|#define UART_EN_DMA_TX &t;&t;BIT(14)
DECL|macro|UART_BREAK_HALT
mdefine_line|#define UART_BREAK_HALT &t;BIT(12)
DECL|macro|UART_DMA_LOOP
mdefine_line|#define UART_DMA_LOOP&t;&t;BIT(10)
DECL|macro|UART_PULSE_THREE
mdefine_line|#define UART_PULSE_THREE&t;BIT(9)
DECL|macro|UART_PULSE_SIX
mdefine_line|#define UART_PULSE_SIX&t;&t;BIT(8)
DECL|macro|UART_DT_INVERT
mdefine_line|#define UART_DT_INVERT&t;&t;BIT(7)
DECL|macro|UART_DIS_TXD
mdefine_line|#define UART_DIS_TXD&t;&t;BIT(6)
DECL|macro|UART_LOOPBACK
mdefine_line|#define UART_LOOPBACK&t;&t;BIT(4)
DECL|macro|TX3912_UART_CTRL1_ENUART
mdefine_line|#define TX3912_UART_CTRL1_ENUART&t;0x00000001
DECL|macro|SER_SEVEN_BIT
mdefine_line|#define SER_SEVEN_BIT&t;&t;BIT(3)
DECL|macro|SER_EIGHT_BIT
mdefine_line|#define SER_EIGHT_BIT&t;&t;    0
DECL|macro|SER_EVEN_PARITY
mdefine_line|#define SER_EVEN_PARITY &t;(BIT(2) | BIT(1))
DECL|macro|SER_ODD_PARITY
mdefine_line|#define SER_ODD_PARITY  &t;BIT(1)
DECL|macro|SER_NO_PARITY
mdefine_line|#define SER_NO_PARITY&t;&t;    0
DECL|macro|SER_TWO_STOP
mdefine_line|#define SER_TWO_STOP&t;&t;BIT(5)
DECL|macro|SER_ONE_STOP
mdefine_line|#define SER_ONE_STOP&t;&t;    0
multiline_comment|/*&n; * Defines for UART Control Register 2&n; *&n; *              3.6864MHz&n; * divisors =  ----------- - 1&n; *             (baud * 16)&n; */
DECL|macro|TX3912_UART_CTRL2_B230400
mdefine_line|#define TX3912_UART_CTRL2_B230400&t;0x000&t;/*   0 */
DECL|macro|TX3912_UART_CTRL2_B115200
mdefine_line|#define TX3912_UART_CTRL2_B115200&t;0x001&t;/*   1 */
DECL|macro|TX3912_UART_CTRL2_B76800
mdefine_line|#define TX3912_UART_CTRL2_B76800&t;0x002&t;/*   2 */
DECL|macro|TX3912_UART_CTRL2_B57600
mdefine_line|#define TX3912_UART_CTRL2_B57600&t;0x003&t;/*   3 */
DECL|macro|TX3912_UART_CTRL2_B38400
mdefine_line|#define TX3912_UART_CTRL2_B38400&t;0x005&t;/*   5 */
DECL|macro|TX3912_UART_CTRL2_B19200
mdefine_line|#define TX3912_UART_CTRL2_B19200&t;0x00b&t;/*  11 */
DECL|macro|TX3912_UART_CTRL2_B9600
mdefine_line|#define TX3912_UART_CTRL2_B9600&t;&t;0x016&t;/*  22 */
DECL|macro|TX3912_UART_CTRL2_B4800
mdefine_line|#define TX3912_UART_CTRL2_B4800&t;&t;0x02f&t;/*  47 */
DECL|macro|TX3912_UART_CTRL2_B2400
mdefine_line|#define TX3912_UART_CTRL2_B2400&t;&t;0x05f&t;/*  95 */
DECL|macro|TX3912_UART_CTRL2_B1200
mdefine_line|#define TX3912_UART_CTRL2_B1200&t;&t;0x0bf&t;/* 191 */
DECL|macro|TX3912_UART_CTRL2_B600
mdefine_line|#define TX3912_UART_CTRL2_B600&t;&t;0x17f&t;/* 383 */
DECL|macro|TX3912_UART_CTRL2_B300
mdefine_line|#define TX3912_UART_CTRL2_B300&t;&t;0x2ff&t;/* 767 */
macro_line|#endif&t;/* __TX3912_H__ */
eof
