multiline_comment|/******************************************************************************&n; *&n; * Name:&t;lm80.h&t;&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.3 $&n; * Date:&t;$Date: 1999/11/22 13:41:19 $&n; * Purpose:&t;Contains all defines for the LM80 Chip&n; *&t;&t;(National Semiconductor).&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&t;$Log: lm80.h,v $&n; *&t;Revision 1.3  1999/11/22 13:41:19  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.2  1999/03/12 13:26:51  malthoff&n; *&t;remove __STDC__.&n; *&t;&n; *&t;Revision 1.1  1998/06/19 09:28:31  malthoff&n; *&t;created.&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_LM80_H
DECL|macro|__INC_LM80_H
mdefine_line|#define __INC_LM80_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * LM80 register definition&n; *&n; * All registers are 8 bit wide&n; */
DECL|macro|LM80_CFG
mdefine_line|#define&t;LM80_CFG&t;&t;0x00&t;/* Configuration Register */
DECL|macro|LM80_ISRC_1
mdefine_line|#define&t;LM80_ISRC_1&t;&t;0x01&t;/* Interrupt Status Register 1 */
DECL|macro|LM80_ISRC_2
mdefine_line|#define LM80_ISRC_2&t;&t;0x02&t;/* Interrupt Status Register 2 */
DECL|macro|LM80_IMSK_1
mdefine_line|#define LM80_IMSK_1&t;&t;0x03&t;/* Interrupt Mask Register 1 */
DECL|macro|LM80_IMSK_2
mdefine_line|#define LM80_IMSK_2&t;&t;0x04&t;/* Interrupt Mask Register 2 */
DECL|macro|LM80_FAN_CTRL
mdefine_line|#define LM80_FAN_CTRL&t;&t;0x05&t;/* Fan Devisor/RST#/OS# Register */
DECL|macro|LM80_TEMP_CTRL
mdefine_line|#define LM80_TEMP_CTRL&t;&t;0x06&t;/* OS# Config, Temp Res. Reg */
multiline_comment|/* 0x07 - 0x1f reserved&t;*/
multiline_comment|/* current values */
DECL|macro|LM80_VT0_IN
mdefine_line|#define LM80_VT0_IN&t;&t;0x20&t;/* current Voltage 0 value */
DECL|macro|LM80_VT1_IN
mdefine_line|#define LM80_VT1_IN&t;&t;0x21&t;/* current Voltage 1 value */
DECL|macro|LM80_VT2_IN
mdefine_line|#define LM80_VT2_IN&t;&t;0x22&t;/* current Voltage 2 value */
DECL|macro|LM80_VT3_IN
mdefine_line|#define LM80_VT3_IN&t;&t;0x23&t;/* current Voltage 3 value */
DECL|macro|LM80_VT4_IN
mdefine_line|#define LM80_VT4_IN&t;&t;0x24&t;/* current Voltage 4 value */
DECL|macro|LM80_VT5_IN
mdefine_line|#define LM80_VT5_IN&t;&t;0x25&t;/* current Voltage 5 value */
DECL|macro|LM80_VT6_IN
mdefine_line|#define LM80_VT6_IN&t;&t;0x26&t;/* current Voltage 6 value */
DECL|macro|LM80_TEMP_IN
mdefine_line|#define LM80_TEMP_IN&t;&t;0x27&t;/* current temperature value */
DECL|macro|LM80_FAN1_IN
mdefine_line|#define LM80_FAN1_IN&t;&t;0x28&t;/* current Fan 1 count */
DECL|macro|LM80_FAN2_IN
mdefine_line|#define LM80_FAN2_IN&t;&t;0x29&t;/* current Fan 2 count */
multiline_comment|/* limit values */
DECL|macro|LM80_VT0_HIGH_LIM
mdefine_line|#define LM80_VT0_HIGH_LIM&t;0x2a&t;/* high limit val for Voltage 0 */
DECL|macro|LM80_VT0_LOW_LIM
mdefine_line|#define LM80_VT0_LOW_LIM&t;0x2b&t;/* low limit val for Voltage 0 */
DECL|macro|LM80_VT1_HIGH_LIM
mdefine_line|#define LM80_VT1_HIGH_LIM&t;0x2c&t;/* high limit val for Voltage 1 */
DECL|macro|LM80_VT1_LOW_LIM
mdefine_line|#define LM80_VT1_LOW_LIM&t;0x2d&t;/* low limit val for Voltage 1 */
DECL|macro|LM80_VT2_HIGH_LIM
mdefine_line|#define LM80_VT2_HIGH_LIM&t;0x2e&t;/* high limit val for Voltage 2 */
DECL|macro|LM80_VT2_LOW_LIM
mdefine_line|#define LM80_VT2_LOW_LIM&t;0x2f&t;/* low limit val for Voltage 2 */
DECL|macro|LM80_VT3_HIGH_LIM
mdefine_line|#define LM80_VT3_HIGH_LIM&t;0x30&t;/* high limit val for Voltage 3 */
DECL|macro|LM80_VT3_LOW_LIM
mdefine_line|#define LM80_VT3_LOW_LIM&t;0x31&t;/* low limit val for Voltage 3 */
DECL|macro|LM80_VT4_HIGH_LIM
mdefine_line|#define LM80_VT4_HIGH_LIM&t;0x32&t;/* high limit val for Voltage 4 */
DECL|macro|LM80_VT4_LOW_LIM
mdefine_line|#define LM80_VT4_LOW_LIM&t;0x33&t;/* low limit val for Voltage 4 */
DECL|macro|LM80_VT5_HIGH_LIM
mdefine_line|#define LM80_VT5_HIGH_LIM&t;0x34&t;/* high limit val for Voltage 5 */
DECL|macro|LM80_VT5_LOW_LIM
mdefine_line|#define LM80_VT5_LOW_LIM&t;0x35&t;/* low limit val for Voltage 5 */
DECL|macro|LM80_VT6_HIGH_LIM
mdefine_line|#define LM80_VT6_HIGH_LIM&t;0x36&t;/* high limit val for Voltage 6 */
DECL|macro|LM80_VT6_LOW_LIM
mdefine_line|#define LM80_VT6_LOW_LIM&t;0x37&t;/* low limit val for Voltage 6 */
DECL|macro|LM80_THOT_LIM_UP
mdefine_line|#define LM80_THOT_LIM_UP&t;0x38&t;/* hot temperature limit (high) */
DECL|macro|LM80_THOT_LIM_LO
mdefine_line|#define LM80_THOT_LIM_LO&t;0x39&t;/* hot temperature limit (low) */
DECL|macro|LM80_TOS_LIM_UP
mdefine_line|#define LM80_TOS_LIM_UP&t;&t;0x3a&t;/* OS temperature limit (high) */
DECL|macro|LM80_TOS_LIM_LO
mdefine_line|#define LM80_TOS_LIM_LO&t;&t;0x3b&t;/* OS temperature limit (low) */
DECL|macro|LM80_FAN1_COUNT_LIM
mdefine_line|#define&t;LM80_FAN1_COUNT_LIM&t;0x3c&t;/* Fan 1 count limit (high) */
DECL|macro|LM80_FAN2_COUNT_LIM
mdefine_line|#define&t;LM80_FAN2_COUNT_LIM&t;0x3d&t;/* Fan 2 count limit (low) */
multiline_comment|/* 0x3e - 0x3f reserved&t;*/
multiline_comment|/*&n; * LM80 bit definitions&n; */
multiline_comment|/*&t;LM80_CFG&t;&t;Configuration Register */
DECL|macro|LM80_CFG_START
mdefine_line|#define LM80_CFG_START&t;&t;(1&lt;&lt;0)&t;/* start monitoring operation */
DECL|macro|LM80_CFG_INT_ENA
mdefine_line|#define LM80_CFG_INT_ENA&t;(1&lt;&lt;1)&t;/* enables the INT# Interrupt output */
DECL|macro|LM80_CFG_INT_POL
mdefine_line|#define LM80_CFG_INT_POL&t;(1&lt;&lt;2)&t;/* INT# pol: 0 act low, 1 act high */
DECL|macro|LM80_CFG_INT_CLR
mdefine_line|#define LM80_CFG_INT_CLR&t;(1&lt;&lt;3)&t;/* disables INT#/RST_OUT#/OS# outputs */
DECL|macro|LM80_CFG_RESET
mdefine_line|#define LM80_CFG_RESET&t;&t;(1&lt;&lt;4)&t;/* signals a reset */
DECL|macro|LM80_CFG_CHASS_CLR
mdefine_line|#define LM80_CFG_CHASS_CLR&t;(1&lt;&lt;5)&t;/* clears Chassis Intrusion (CI) pin */
DECL|macro|LM80_CFG_GPO
mdefine_line|#define LM80_CFG_GPO&t;&t;(1&lt;&lt;6)&t;/* drives the GPO# pin */
DECL|macro|LM80_CFG_INIT
mdefine_line|#define LM80_CFG_INIT&t;&t;(1&lt;&lt;7)&t;/* restore power on defaults */
multiline_comment|/*&t;LM80_ISRC_1&t;&t;Interrupt Status Register 1 */
multiline_comment|/*&t;LM80_IMSK_1&t;&t;Interrupt Mask Register 1 */
DECL|macro|LM80_IS_VT0
mdefine_line|#define LM80_IS_VT0&t;&t;(1&lt;&lt;0)&t;/* limit exceeded for Voltage 0 */
DECL|macro|LM80_IS_VT1
mdefine_line|#define LM80_IS_VT1&t;&t;(1&lt;&lt;1)&t;/* limit exceeded for Voltage 1 */
DECL|macro|LM80_IS_VT2
mdefine_line|#define LM80_IS_VT2&t;&t;(1&lt;&lt;2)&t;/* limit exceeded for Voltage 2 */
DECL|macro|LM80_IS_VT3
mdefine_line|#define LM80_IS_VT3&t;&t;(1&lt;&lt;3)&t;/* limit exceeded for Voltage 3 */
DECL|macro|LM80_IS_VT4
mdefine_line|#define LM80_IS_VT4&t;&t;(1&lt;&lt;4)&t;/* limit exceeded for Voltage 4 */
DECL|macro|LM80_IS_VT5
mdefine_line|#define LM80_IS_VT5&t;&t;(1&lt;&lt;5)&t;/* limit exceeded for Voltage 5 */
DECL|macro|LM80_IS_VT6
mdefine_line|#define LM80_IS_VT6&t;&t;(1&lt;&lt;6)&t;/* limit exceeded for Voltage 6 */
DECL|macro|LM80_IS_INT_IN
mdefine_line|#define LM80_IS_INT_IN&t;&t;(1&lt;&lt;7)&t;/* state of INT_IN# */
multiline_comment|/*&t;LM80_ISRC_2&t;&t;Interrupt Status Register 2 */
multiline_comment|/*&t;LM80_IMSK_2&t;&t;Interrupt Mask Register 2 */
DECL|macro|LM80_IS_TEMP
mdefine_line|#define&t;LM80_IS_TEMP&t;&t;(1&lt;&lt;0)&t;/* HOT temperature limit exceeded */
DECL|macro|LM80_IS_BTI
mdefine_line|#define LM80_IS_BTI&t;&t;(1&lt;&lt;1)&t;/* state of BTI# pin */
DECL|macro|LM80_IS_FAN1
mdefine_line|#define LM80_IS_FAN1&t;&t;(1&lt;&lt;2)&t;/* count limit exceeded for Fan 1 */
DECL|macro|LM80_IS_FAN2
mdefine_line|#define LM80_IS_FAN2&t;&t;(1&lt;&lt;3)&t;/* count limit exceeded for Fan 2 */
DECL|macro|LM80_IS_CI
mdefine_line|#define LM80_IS_CI&t;&t;(1&lt;&lt;4)&t;/* Chassis Intrusion occurred */
DECL|macro|LM80_IS_OS
mdefine_line|#define LM80_IS_OS&t;&t;(1&lt;&lt;5)&t;/* OS temperature limit exceeded */
multiline_comment|/* bit 6 and 7 are reserved in LM80_ISRC_2 */
DECL|macro|LM80_IS_HT_IRQ_MD
mdefine_line|#define LM80_IS_HT_IRQ_MD&t;(1&lt;&lt;6)&t;/* Hot temperature interrupt mode */
DECL|macro|LM80_IS_OT_IRQ_MD
mdefine_line|#define LM80_IS_OT_IRQ_MD&t;(1&lt;&lt;7)&t;/* OS temperature interrupt mode */
multiline_comment|/*&t;LM80_FAN_CTRL&t;&t;Fan Devisor/RST#/OS# Register */
DECL|macro|LM80_FAN1_MD_SEL
mdefine_line|#define LM80_FAN1_MD_SEL&t;(1&lt;&lt;0)&t;/* Fan 1 mode select */
DECL|macro|LM80_FAN2_MD_SEL
mdefine_line|#define LM80_FAN2_MD_SEL&t;(1&lt;&lt;1)&t;/* Fan 2 mode select */
DECL|macro|LM80_FAN1_PRM_CTL
mdefine_line|#define LM80_FAN1_PRM_CTL&t;(3&lt;&lt;2)&t;/* Fan 1 speed control */
DECL|macro|LM80_FAN2_PRM_CTL
mdefine_line|#define LM80_FAN2_PRM_CTL&t;(3&lt;&lt;4)&t;/* Fan 2 speed control */
DECL|macro|LM80_FAN_OS_ENA
mdefine_line|#define LM80_FAN_OS_ENA&t;&t;(1&lt;&lt;6)&t;/* enable OS mode on RST_OUT#/OS# pins*/
DECL|macro|LM80_FAN_RST_ENA
mdefine_line|#define LM80_FAN_RST_ENA&t;(1&lt;&lt;7)&t;/* sets RST_OUT#/OS# pins in RST mode */
multiline_comment|/*&t;LM80_TEMP_CTRL&t;&t;OS# Config, Temp Res. Reg */
DECL|macro|LM80_TEMP_OS_STAT
mdefine_line|#define&t;LM80_TEMP_OS_STAT&t;(1&lt;&lt;0)&t;/* mirrors the state of RST_OUT#/OS# */
DECL|macro|LM80_TEMP_OS_POL
mdefine_line|#define LM80_TEMP_OS_POL&t;(1&lt;&lt;1)&t;/* select OS# polarity */
DECL|macro|LM80_TEMP_OS_MODE
mdefine_line|#define LM80_TEMP_OS_MODE&t;(1&lt;&lt;2)&t;/* selects Interrupt mode */
DECL|macro|LM80_TEMP_RES
mdefine_line|#define LM80_TEMP_RES&t;&t;(1&lt;&lt;3)&t;/* selects 9 or 11 bit temp resulution*/
DECL|macro|LM80_TEMP_LSB
mdefine_line|#define LM80_TEMP_LSB&t;&t;(0xf&lt;&lt;4)/* 4 LSBs of 11 bit temp data */
DECL|macro|LM80_TEMP_LSB_9
mdefine_line|#define LM80_TEMP_LSB_9&t;&t;(1&lt;&lt;7)&t;/* LSB of 9 bit temperature data */
multiline_comment|/* 0x07 - 0x1f reserved&t;*/
multiline_comment|/*&t;LM80_VT0_IN&t;&t;current Voltage 0 value */
multiline_comment|/*&t;LM80_VT1_IN&t;&t;current Voltage 1 value */
multiline_comment|/*&t;LM80_VT2_IN&t;&t;current Voltage 2 value */
multiline_comment|/*&t;LM80_VT3_IN&t;&t;current Voltage 3 value */
multiline_comment|/*&t;LM80_VT4_IN&t;&t;current Voltage 4 value */
multiline_comment|/*&t;LM80_VT5_IN&t;&t;current Voltage 5 value */
multiline_comment|/*&t;LM80_VT6_IN&t;&t;current Voltage 6 value */
multiline_comment|/*&t;LM80_TEMP_IN&t;&t;current temperature value */
multiline_comment|/*&t;LM80_FAN1_IN&t;&t;current Fan 1 count */
multiline_comment|/*&t;LM80_FAN2_IN&t;&t;current Fan 2 count */
multiline_comment|/*&t;LM80_VT0_HIGH_LIM&t;high limit val for Voltage 0 */
multiline_comment|/*&t;LM80_VT0_LOW_LIM&t;low limit val for Voltage 0 */
multiline_comment|/*&t;LM80_VT1_HIGH_LIM&t;high limit val for Voltage 1 */
multiline_comment|/*&t;LM80_VT1_LOW_LIM&t;low limit val for Voltage 1 */
multiline_comment|/*&t;LM80_VT2_HIGH_LIM&t;high limit val for Voltage 2 */
multiline_comment|/*&t;LM80_VT2_LOW_LIM&t;low limit val for Voltage 2 */
multiline_comment|/*&t;LM80_VT3_HIGH_LIM&t;high limit val for Voltage 3 */
multiline_comment|/*&t;LM80_VT3_LOW_LIM&t;low limit val for Voltage 3 */
multiline_comment|/*&t;LM80_VT4_HIGH_LIM&t;high limit val for Voltage 4 */
multiline_comment|/*&t;LM80_VT4_LOW_LIM&t;low limit val for Voltage 4 */
multiline_comment|/*&t;LM80_VT5_HIGH_LIM&t;high limit val for Voltage 5 */
multiline_comment|/*&t;LM80_VT5_LOW_LIM&t;low limit val for Voltage 5 */
multiline_comment|/*&t;LM80_VT6_HIGH_LIM&t;high limit val for Voltage 6 */
multiline_comment|/*&t;LM80_VT6_LOW_LIM&t;low limit val for Voltage 6 */
multiline_comment|/*&t;LM80_THOT_LIM_UP&t;hot temperature limit (high) */
multiline_comment|/*&t;LM80_THOT_LIM_LO&t;hot temperature limit (low) */
multiline_comment|/*&t;LM80_TOS_LIM_UP&t;&t;OS temperature limit (high) */
multiline_comment|/*&t;LM80_TOS_LIM_LO&t;&t;OS temperature limit (low) */
multiline_comment|/*&t;LM80_FAN1_COUNT_LIM&t;Fan 1 count limit (high) */
multiline_comment|/*&t;LM80_FAN2_COUNT_LIM&t;Fan 2 count limit (low) */
multiline_comment|/* 0x3e - 0x3f reserved&t;*/
DECL|macro|LM80_ADDR
mdefine_line|#define LM80_ADDR&t;0x28&t;/* LM80 default addr */
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_LM80_H */
eof
