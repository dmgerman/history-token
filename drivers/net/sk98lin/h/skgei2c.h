multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgei2c.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.17 $&n; * Date:&t;$Date: 1999/11/22 13:55:25 $&n; * Purpose:&t;Special genesis defines for I2C&n; *&t;&t;(taken from Monalisa (taken from Concentrator))&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgei2c.h,v $&n; *&t;Revision 1.17  1999/11/22 13:55:25  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.16  1999/11/12 08:24:10  malthoff&n; *&t;Change voltage warning and error limits&n; *&t;(warning +-5%, error +-10%).&n; *&t;&n; *&t;Revision 1.15  1999/09/14 14:14:43  malthoff&n; *&t;The 1000BT Dual Link adapter has got only one Fan.&n; *&t;The second Fan has been removed.&n; *&t;&n; *&t;Revision 1.14  1999/05/27 13:40:50  malthoff&n; *&t;Fan Divisor = 1. Assuming fan with 6500 rpm.&n; *&t;&n; *&t;Revision 1.13  1999/05/20 14:56:55  malthoff&n; *&t;Bug Fix: Missing brace in SK_LM80_FAN_FAKTOR.&n; *&t;&n; *&t;Revision 1.12  1999/05/20 09:22:00  cgoos&n; *&t;Changes for 1000Base-T (Fan sensors).&n; *&t;&n; *&t;Revision 1.11  1998/10/14 05:57:22  cgoos&n; *&t;Fixed compilation warnings.&n; *&t;&n; *&t;Revision 1.10  1998/09/04 08:37:00  malthoff&n; *&t;bugfix: correct the SK_I2C_GET_CTL() macro.&n; *&t;&n; *&t;Revision 1.9  1998/08/25 06:10:03  gklug&n; *&t;add: thresholds for all sensors&n; *&n; *&t;Revision 1.8  1998/08/20 11:37:42  gklug&n; *&t;chg: change Ioc to IoC&n; *&t;&n; *&t;Revision 1.7  1998/08/20 08:53:11  gklug&n; *&t;fix: compiler errors&n; *&t;add: Threshold values&n; *&t;&n; *&t;Revision 1.6  1998/08/17 11:37:09  malthoff&n; *&t;Bugfix in SK_I2C_CTL macro. The parameter &squot;dev&squot;&n; *&t;has to be shifted 9 bits.&n; *&t;&n; *&t;Revision 1.5  1998/08/17 06:52:21  malthoff&n; *&t;Remove unrequired macros.&n; *&t;Add macros for accessing I2C SW register.&n; *&t;&n; *&t;Revision 1.4  1998/08/13 08:30:18  gklug&n; *&t;add: conversion factors for read values&n; *&t;add: new state SEN_VALEXT to read extension value of temperature sensor&n; *&n; *&t;Revision 1.3  1998/08/12 13:37:56  gklug&n; *&t;rmv: error numbers and messages&n; *&n; *&t;Revision 1.2  1998/08/11 07:54:38  gklug&n; *&t;add: sensor states for GE sensors&n; *&t;add: Macro to access I2c hardware register&n; *&t;chg: Error messages for I2c errors&n; *&n; *&t;Revision 1.1  1998/07/17 11:27:56  gklug&n; *&t;Created.&n; *&n; *&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * SKGEI2C.H&t;contains all SK-98xx specific defines for the I2C handling&n; */
macro_line|#ifndef _INC_SKGEI2C_H_
DECL|macro|_INC_SKGEI2C_H_
mdefine_line|#define _INC_SKGEI2C_H_
multiline_comment|/*&n; * Macros to access the B2_I2C_CTRL&n; */
DECL|macro|SK_I2C_CTL
mdefine_line|#define SK_I2C_CTL(IoC,flag,dev,reg,burst) &bslash;&n;&t;SK_OUT32(IoC,B2_I2C_CTRL,&bslash;&n;&t;&t;(flag ? 0x80000000UL : 0x0L ) | &bslash;&n;&t;&t;(((SK_U32) reg &lt;&lt; 16) &amp; I2C_ADDR) | &bslash;&n;&t;&t;(((SK_U32) dev &lt;&lt; 9) &amp; I2C_DEV_SEL) | &bslash;&n;&t;&t;(( burst &lt;&lt; 4) &amp; I2C_BURST_LEN) )
DECL|macro|SK_I2C_STOP
mdefine_line|#define SK_I2C_STOP(IoC) {&t;&t;&t;&t;&bslash;&n;&t;SK_U32&t;I2cCtrl;&t;&t;&t;&t;&bslash;&n;&t;SK_IN32(IoC, B2_I2C_CTRL, &amp;I2cCtrl);&t;&t;&bslash;&n;&t;SK_OUT32(IoC, B2_I2C_CTRL, I2cCtrl | I2C_STOP);&t;&bslash;&n;}
DECL|macro|SK_I2C_GET_CTL
mdefine_line|#define SK_I2C_GET_CTL(Ioc,pI2cCtrl)&t;SK_IN32(Ioc,B2_I2C_CTRL,pI2cCtrl)
multiline_comment|/*&n; * Macros to access the I2C SW Registers&n; */
DECL|macro|SK_I2C_SET_BIT
mdefine_line|#define SK_I2C_SET_BIT(IoC, SetBits) {&t;&t;&t;&bslash;&n;&t;SK_U8&t;OrgBits;&t;&t;&t;&t;&bslash;&n;&t;SK_IN8(IoC, B2_I2C_SW, &amp;OrgBits);&t;&t;&bslash;&n;&t;SK_OUT8(IoC, B2_I2C_SW, OrgBits | (SetBits));&t;&bslash;&n;}
DECL|macro|SK_I2C_CLR_BIT
mdefine_line|#define SK_I2C_CLR_BIT(IoC,ClrBits) {&t;&t;&t;&bslash;&n;&t;SK_U8&t;OrgBits;&t;&t;&t;&t;&bslash;&n;&t;SK_IN8(IoC, B2_I2C_SW, &amp;OrgBits);&t;&t;&bslash;&n;&t;SK_OUT8(IoC, B2_I2C_SW, OrgBits &amp; ~(ClrBits));&t;&bslash;&n;}
DECL|macro|SK_I2C_GET_SW
mdefine_line|#define SK_I2C_GET_SW(IoC,pI2cSw)&t;SK_IN8(IoC,B2_I2C_SW,pI2cSw)
multiline_comment|/*&n; * define the possible sensor states&n; */
DECL|macro|SK_SEN_IDLE
mdefine_line|#define&t;SK_SEN_IDLE&t;0&t;/* Idle: sensor not read */
DECL|macro|SK_SEN_VALUE
mdefine_line|#define&t;SK_SEN_VALUE&t;1&t;/* Value Read cycle */
DECL|macro|SK_SEN_VALEXT
mdefine_line|#define&t;SK_SEN_VALEXT&t;2&t;/* Extended Value Read cycle */
multiline_comment|/*&n; * Conversion factor to convert read Voltage sensor to milli Volt&n; * Conversion factor to convert read Temperature sensor to 10th degree Celsius&n; */
DECL|macro|SK_LM80_VT_LSB
mdefine_line|#define&t;SK_LM80_VT_LSB&t;&t;22&t;/* 22mV LSB resolution */
DECL|macro|SK_LM80_TEMP_LSB
mdefine_line|#define&t;SK_LM80_TEMP_LSB&t;10&t;/* 1 degree LSB resolution */
DECL|macro|SK_LM80_TEMPEXT_LSB
mdefine_line|#define&t;SK_LM80_TEMPEXT_LSB&t;5&t;/* 0.5 degree LSB resolution for the&n;&t;&t;&t;&t;&t; * extension value &n;&t;&t;&t;&t;&t; */
DECL|macro|SK_LM80_FAN_FAKTOR
mdefine_line|#define SK_LM80_FAN_FAKTOR&t;((22500L*60)/(1*2))
multiline_comment|/* formula: counter = (22500*60)/(rpm * divisor * pulses/2)&n; * assuming: 6500rpm, 4 pulses, divisor 1&n; */
multiline_comment|/*&n; * Define sensor management data&n; * Maximum is reached on copperfield with dual Broadcom.&n; * Board specific maximum is in pAC-&gt;I2c.MaxSens&n; */
DECL|macro|SK_MAX_SENSORS
mdefine_line|#define&t;SK_MAX_SENSORS&t;8&t;/* maximal no. of installed sensors */
DECL|macro|SK_MIN_SENSORS
mdefine_line|#define&t;SK_MIN_SENSORS&t;5&t;/* minimal no. of installed sensors */
multiline_comment|/*&n; * Defines for the individual Thresholds&n; */
multiline_comment|/* Temperature sensor */
DECL|macro|SK_SEN_ERRHIGH0
mdefine_line|#define&t;SK_SEN_ERRHIGH0&t;&t;800&t;/* Temperature High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH0
mdefine_line|#define&t;SK_SEN_WARNHIGH0&t;700&t;/* Temperature High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW0
mdefine_line|#define&t;SK_SEN_WARNLOW0&t;&t;100&t;/* Temperature Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW0
mdefine_line|#define&t;SK_SEN_ERRLOW0&t;&t;0&t;/* Temperature Low Warn Threshold */
multiline_comment|/* VCC which should be 5 V */
DECL|macro|SK_SEN_ERRHIGH1
mdefine_line|#define&t;SK_SEN_ERRHIGH1&t;&t;5588&t;/* Voltage PCI High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH1
mdefine_line|#define&t;SK_SEN_WARNHIGH1&t;5346&t;/* Voltage PCI High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW1
mdefine_line|#define&t;SK_SEN_WARNLOW1&t;&t;4664&t;/* Voltage PCI Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW1
mdefine_line|#define&t;SK_SEN_ERRLOW1&t;&t;4422&t;/* Voltage PCI Low Warn Threshold */
multiline_comment|/*&n; * VIO may be 5 V or 3.3 V. Initialization takes two parts:&n; * 1. Initialize lowest lower limit and highest higher limit.&n; * 2. After the first value is read correct the upper or the lower limit to&n; *    the appropriate C constant.&n; *&n; * Warning limits are +-5% of the exepected voltage.&n; * Error limits are +-10% of the expected voltage.&n; */
DECL|macro|SK_SEN_ERRHIGH2
mdefine_line|#define&t;SK_SEN_ERRHIGH2&t;&t;5588&t;/* Voltage PCI-IO High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH2
mdefine_line|#define&t;SK_SEN_WARNHIGH2&t;5346&t;/* Voltage PCI-IO High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW2
mdefine_line|#define&t;SK_SEN_WARNLOW2&t;&t;3146&t;/* Voltage PCI-IO Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW2
mdefine_line|#define&t;SK_SEN_ERRLOW2&t;&t;2970&t;/* Voltage PCI-IO Low Warn Threshold */
multiline_comment|/* correction values for the second pass */
DECL|macro|SK_SEN_ERRHIGH2C
mdefine_line|#define&t;SK_SEN_ERRHIGH2C&t;3630&t;/* Voltage PCI-IO High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH2C
mdefine_line|#define&t;SK_SEN_WARNHIGH2C&t;3476&t;/* Voltage PCI-IO High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW2C
mdefine_line|#define&t;SK_SEN_WARNLOW2C&t;4664&t;/* Voltage PCI-IO Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW2C
mdefine_line|#define&t;SK_SEN_ERRLOW2C&t;&t;4422&t;/* Voltage PCI-IO Low Warn Threshold */
multiline_comment|/*&n; * VDD voltage&n; */
DECL|macro|SK_SEN_ERRHIGH3
mdefine_line|#define&t;SK_SEN_ERRHIGH3&t;&t;3630&t;/* Voltage ASIC High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH3
mdefine_line|#define&t;SK_SEN_WARNHIGH3&t;3476&t;/* Voltage ASIC High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW3
mdefine_line|#define&t;SK_SEN_WARNLOW3&t;&t;3146&t;/* Voltage ASIC Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW3
mdefine_line|#define&t;SK_SEN_ERRLOW3&t;&t;2970&t;/* Voltage ASIC Low Warn Threshold */
multiline_comment|/*&n; * PLC_3V3 voltage&n; * PHY_PLL_A_3V3 voltage&n; */
DECL|macro|SK_SEN_ERRHIGH4
mdefine_line|#define&t;SK_SEN_ERRHIGH4&t;&t;3630&t;/* Voltage PMA High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH4
mdefine_line|#define&t;SK_SEN_WARNHIGH4&t;3476&t;/* Voltage PMA High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW4
mdefine_line|#define&t;SK_SEN_WARNLOW4&t;&t;3146&t;/* Voltage PMA Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW4
mdefine_line|#define&t;SK_SEN_ERRLOW4&t;&t;2970&t;/* Voltage PMA Low Warn Threshold */
multiline_comment|/*&n; * PHY_2V5 voltage&n; */
DECL|macro|SK_SEN_ERRHIGH5
mdefine_line|#define&t;SK_SEN_ERRHIGH5&t;&t;2750&t;/* Voltage PHY High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH5
mdefine_line|#define&t;SK_SEN_WARNHIGH5&t;2640&t;/* Voltage PHY High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW5
mdefine_line|#define&t;SK_SEN_WARNLOW5&t;&t;2376&t;/* Voltage PHY Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW5
mdefine_line|#define&t;SK_SEN_ERRLOW5&t;&t;2222&t;/* Voltage PHY Low Warn Threshold */
multiline_comment|/*&n; * PHY_PLL_B_3V3 voltage&n; */
DECL|macro|SK_SEN_ERRHIGH6
mdefine_line|#define&t;SK_SEN_ERRHIGH6&t;&t;3630&t;/* Voltage PMA High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH6
mdefine_line|#define&t;SK_SEN_WARNHIGH6&t;3476&t;/* Voltage PMA High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW6
mdefine_line|#define&t;SK_SEN_WARNLOW6&t;&t;3146&t;/* Voltage PMA Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW6
mdefine_line|#define&t;SK_SEN_ERRLOW6&t;&t;2970&t;/* Voltage PMA Low Warn Threshold */
multiline_comment|/*&n; * FAN 1 speed&n; */
multiline_comment|/* assuming: 6500rpm +-15%, 4 pulses,&n; * warning at:&t;80 %&n; * error at:&t;70 %&n; * no upper limit&n; */
DECL|macro|SK_SEN_ERRHIGH
mdefine_line|#define&t;SK_SEN_ERRHIGH&t;&t;20000&t;/* FAN Speed High Err Threshold */
DECL|macro|SK_SEN_WARNHIGH
mdefine_line|#define&t;SK_SEN_WARNHIGH&t;&t;20000&t;/* FAN Speed High Warn Threshold */
DECL|macro|SK_SEN_WARNLOW
mdefine_line|#define&t;SK_SEN_WARNLOW&t;&t;5200&t;/* FAN Speed Low Err Threshold */
DECL|macro|SK_SEN_ERRLOW
mdefine_line|#define&t;SK_SEN_ERRLOW&t;&t;4550&t;/* FAN Speed Low Warn Threshold */
r_extern
r_int
id|SkLm80ReadSensor
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_SENSOR
op_star
id|pSen
)paren
suffix:semicolon
macro_line|#endif&t;/* n_INC_SKGEI2C_H */
eof
