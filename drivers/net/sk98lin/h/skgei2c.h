multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgei2c.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.23 $&n; * Date:&t;$Date: 2002/12/19 14:34:27 $&n; * Purpose:&t;Special GEnesis defines for TWSI&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgei2c.h,v $&n; *&t;Revision 1.23  2002/12/19 14:34:27  rschmidt&n; *&t;Added cast in macros SK_I2C_SET_BIT() and SK_I2C_CLR_BIT()&n; *&t;Editorial changes (TWSI)&n; *&t;&n; *&t;Revision 1.22  2002/10/14 16:45:56  rschmidt&n; *&t;Editorial changes (TWSI)&n; *&t;&n; *&t;Revision 1.21  2002/08/13 08:42:24  rschmidt&n; *&t;Changed define for SK_MIN_SENSORS back to 5&n; *&t;Merged defines for PHY PLL 3V3 voltage (A and B)&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.20  2002/08/06 09:43:56  jschmalz&n; *&t;Extensions and changes for Yukon&n; *&t;&n; *&t;Revision 1.19  2002/08/02 12:00:08  rschmidt&n; *&t;Added defines for YUKON sensors&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.18  2001/08/16 12:44:33  afischer&n; *&t;LM80 sensor init values corrected&n; *&t;&n; *&t;Revision 1.17  1999/11/22 13:55:25  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.16  1999/11/12 08:24:10  malthoff&n; *&t;Change voltage warning and error limits&n; *&t;(warning +-5%, error +-10%).&n; *&t;&n; *&t;Revision 1.15  1999/09/14 14:14:43  malthoff&n; *&t;The 1000BT Dual Link adapter has got only one Fan.&n; *&t;The second Fan has been removed.&n; *&t;&n; *&t;Revision 1.14  1999/05/27 13:40:50  malthoff&n; *&t;Fan Divisor = 1. Assuming fan with 6500 rpm.&n; *&t;&n; *&t;Revision 1.13  1999/05/20 14:56:55  malthoff&n; *&t;Bug Fix: Missing brace in SK_LM80_FAN_FAKTOR.&n; *&t;&n; *&t;Revision 1.12  1999/05/20 09:22:00  cgoos&n; *&t;Changes for 1000Base-T (Fan sensors).&n; *&t;&n; *&t;Revision 1.11  1998/10/14 05:57:22  cgoos&n; *&t;Fixed compilation warnings.&n; *&t;&n; *&t;Revision 1.10  1998/09/04 08:37:00  malthoff&n; *&t;bugfix: correct the SK_I2C_GET_CTL() macro.&n; *&t;&n; *&t;Revision 1.9  1998/08/25 06:10:03  gklug&n; *&t;add: thresholds for all sensors&n; *&n; *&t;Revision 1.8  1998/08/20 11:37:42  gklug&n; *&t;chg: change Ioc to IoC&n; *&t;&n; *&t;Revision 1.7  1998/08/20 08:53:11  gklug&n; *&t;fix: compiler errors&n; *&t;add: Threshold values&n; *&t;&n; *&t;Revision 1.6  1998/08/17 11:37:09  malthoff&n; *&t;Bugfix in SK_I2C_CTL macro. The parameter &squot;dev&squot;&n; *&t;has to be shifted 9 bits.&n; *&t;&n; *&t;Revision 1.5  1998/08/17 06:52:21  malthoff&n; *&t;Remove unrequired macros.&n; *&t;Add macros for accessing TWSI SW register.&n; *&t;&n; *&t;Revision 1.4  1998/08/13 08:30:18  gklug&n; *&t;add: conversion factors for read values&n; *&t;add: new state SEN_VALEXT to read extension value of temperature sensor&n; *&n; *&t;Revision 1.3  1998/08/12 13:37:56  gklug&n; *&t;rmv: error numbers and messages&n; *&n; *&t;Revision 1.2  1998/08/11 07:54:38  gklug&n; *&t;add: sensor states for GE sensors&n; *&t;add: Macro to access TWSI hardware register&n; *&t;chg: Error messages for TWSI errors&n; *&n; *&t;Revision 1.1  1998/07/17 11:27:56  gklug&n; *&t;Created.&n; *&n; *&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * SKGEI2C.H&t;contains all SK-98xx specific defines for the TWSI handling&n; */
macro_line|#ifndef _INC_SKGEI2C_H_
DECL|macro|_INC_SKGEI2C_H_
mdefine_line|#define _INC_SKGEI2C_H_
multiline_comment|/*&n; * Macros to access the B2_I2C_CTRL&n; */
DECL|macro|SK_I2C_CTL
mdefine_line|#define SK_I2C_CTL(IoC, flag, dev, reg, burst) &bslash;&n;&t;SK_OUT32(IoC, B2_I2C_CTRL,&bslash;&n;&t;&t;(flag ? 0x80000000UL : 0x0L) | &bslash;&n;&t;&t;(((SK_U32) reg &lt;&lt; 16) &amp; I2C_ADDR) | &bslash;&n;&t;&t;(((SK_U32) dev &lt;&lt; 9) &amp; I2C_DEV_SEL) | &bslash;&n;&t;&t;(( burst &lt;&lt; 4) &amp; I2C_BURST_LEN))
DECL|macro|SK_I2C_STOP
mdefine_line|#define SK_I2C_STOP(IoC) {&t;&t;&t;&t;&bslash;&n;&t;SK_U32&t;I2cCtrl;&t;&t;&t;&t;&bslash;&n;&t;SK_IN32(IoC, B2_I2C_CTRL, &amp;I2cCtrl);&t;&t;&bslash;&n;&t;SK_OUT32(IoC, B2_I2C_CTRL, I2cCtrl | I2C_STOP);&t;&bslash;&n;}
DECL|macro|SK_I2C_GET_CTL
mdefine_line|#define SK_I2C_GET_CTL(IoC, pI2cCtrl)&t;SK_IN32(IoC, B2_I2C_CTRL, pI2cCtrl)
multiline_comment|/*&n; * Macros to access the TWSI SW Registers&n; */
DECL|macro|SK_I2C_SET_BIT
mdefine_line|#define SK_I2C_SET_BIT(IoC, SetBits) {&t;&t;&t;&bslash;&n;&t;SK_U8&t;OrgBits;&t;&t;&t;&t;&bslash;&n;&t;SK_IN8(IoC, B2_I2C_SW, &amp;OrgBits);&t;&t;&bslash;&n;&t;SK_OUT8(IoC, B2_I2C_SW, OrgBits | (SK_U8)(SetBits));&t;&bslash;&n;}
DECL|macro|SK_I2C_CLR_BIT
mdefine_line|#define SK_I2C_CLR_BIT(IoC, ClrBits) {&t;&t;&t;&bslash;&n;&t;SK_U8&t;OrgBits;&t;&t;&t;&t;&bslash;&n;&t;SK_IN8(IoC, B2_I2C_SW, &amp;OrgBits);&t;&t;&bslash;&n;&t;SK_OUT8(IoC, B2_I2C_SW, OrgBits &amp; ~((SK_U8)(ClrBits)));&t;&bslash;&n;}
DECL|macro|SK_I2C_GET_SW
mdefine_line|#define SK_I2C_GET_SW(IoC, pI2cSw)&t;SK_IN8(IoC, B2_I2C_SW, pI2cSw)
multiline_comment|/*&n; * define the possible sensor states&n; */
DECL|macro|SK_SEN_IDLE
mdefine_line|#define&t;SK_SEN_IDLE&t;&t;0&t;/* Idle: sensor not read */
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
mdefine_line|#define&t;SK_LM80_TEMPEXT_LSB&t;5&t;/* 0.5 degree LSB resolution for the&n;&t;&t;&t;&t;&t; * extension value&n;&t;&t;&t;&t;&t; */
DECL|macro|SK_LM80_FAN_FAKTOR
mdefine_line|#define SK_LM80_FAN_FAKTOR&t;((22500L*60)/(1*2))
multiline_comment|/* formula: counter = (22500*60)/(rpm * divisor * pulses/2)&n; * assuming: 6500rpm, 4 pulses, divisor 1&n; */
multiline_comment|/*&n; * Define sensor management data&n; * Maximum is reached on copperfield with dual Broadcom.&n; * Board specific maximum is in pAC-&gt;I2c.MaxSens&n; */
DECL|macro|SK_MAX_SENSORS
mdefine_line|#define&t;SK_MAX_SENSORS&t;8&t;/* maximal no. of installed sensors */
DECL|macro|SK_MIN_SENSORS
mdefine_line|#define&t;SK_MIN_SENSORS&t;5&t;/* minimal no. of installed sensors */
multiline_comment|/*&n; * To watch the statemachine (JS) use the timer in two ways instead of one as hitherto&n; */
DECL|macro|SK_TIMER_WATCH_STATEMACHINE
mdefine_line|#define&t;SK_TIMER_WATCH_STATEMACHINE&t;0&t;/* Watch the statemachine to finish in a specific time */
DECL|macro|SK_TIMER_NEW_GAUGING
mdefine_line|#define&t;SK_TIMER_NEW_GAUGING    &t;1&t;/* Start a new gauging when timer expires */
multiline_comment|/*&n; * Defines for the individual Thresholds&n; */
multiline_comment|/* Temperature sensor */
DECL|macro|SK_SEN_TEMP_HIGH_ERR
mdefine_line|#define&t;SK_SEN_TEMP_HIGH_ERR    800&t;/* Temperature High Err  Threshold */
DECL|macro|SK_SEN_TEMP_HIGH_WARN
mdefine_line|#define&t;SK_SEN_TEMP_HIGH_WARN&t;700&t;/* Temperature High Warn Threshold */
DECL|macro|SK_SEN_TEMP_LOW_WARN
mdefine_line|#define&t;SK_SEN_TEMP_LOW_WARN&t;100&t;/* Temperature Low  Warn Threshold */
DECL|macro|SK_SEN_TEMP_LOW_ERR
mdefine_line|#define&t;SK_SEN_TEMP_LOW_ERR       0&t;/* Temperature Low  Err  Threshold */
multiline_comment|/* VCC which should be 5 V */
DECL|macro|SK_SEN_PCI_5V_HIGH_ERR
mdefine_line|#define&t;SK_SEN_PCI_5V_HIGH_ERR  &t;5588&t;/* Voltage PCI High Err  Threshold */
DECL|macro|SK_SEN_PCI_5V_HIGH_WARN
mdefine_line|#define&t;SK_SEN_PCI_5V_HIGH_WARN     5346&t;/* Voltage PCI High Warn Threshold */
DECL|macro|SK_SEN_PCI_5V_LOW_WARN
mdefine_line|#define&t;SK_SEN_PCI_5V_LOW_WARN&t;&t;4664&t;/* Voltage PCI Low  Warn Threshold */
DECL|macro|SK_SEN_PCI_5V_LOW_ERR
mdefine_line|#define&t;SK_SEN_PCI_5V_LOW_ERR&t;&t;4422&t;/* Voltage PCI Low  Err  Threshold */
multiline_comment|/*&n; * VIO may be 5 V or 3.3 V. Initialization takes two parts:&n; * 1. Initialize lowest lower limit and highest higher limit.&n; * 2. After the first value is read correct the upper or the lower limit to&n; *    the appropriate C constant.&n; *&n; * Warning limits are +-5% of the exepected voltage.&n; * Error limits are +-10% of the expected voltage.&n; */
multiline_comment|/* Bug fix AF: 16.Aug.2001: Correct the init base of LM80 sensor */
DECL|macro|SK_SEN_PCI_IO_5V_HIGH_ERR
mdefine_line|#define&t;SK_SEN_PCI_IO_5V_HIGH_ERR&t;5566&t;/* + 10% V PCI-IO High Err Threshold */
DECL|macro|SK_SEN_PCI_IO_5V_HIGH_WARN
mdefine_line|#define&t;SK_SEN_PCI_IO_5V_HIGH_WARN&t;5324&t;/* +  5% V PCI-IO High Warn Threshold */
multiline_comment|/*&t;&t;5000&t;mVolt */
DECL|macro|SK_SEN_PCI_IO_5V_LOW_WARN
mdefine_line|#define&t;SK_SEN_PCI_IO_5V_LOW_WARN&t;4686&t;/* -  5% V PCI-IO Low Warn Threshold */
DECL|macro|SK_SEN_PCI_IO_5V_LOW_ERR
mdefine_line|#define&t;SK_SEN_PCI_IO_5V_LOW_ERR&t;4444&t;/* - 10% V PCI-IO Low Err Threshold */
DECL|macro|SK_SEN_PCI_IO_RANGE_LIMITER
mdefine_line|#define&t;SK_SEN_PCI_IO_RANGE_LIMITER&t;4000&t;/* 4000 mV range delimiter */
multiline_comment|/* correction values for the second pass */
DECL|macro|SK_SEN_PCI_IO_3V3_HIGH_ERR
mdefine_line|#define&t;SK_SEN_PCI_IO_3V3_HIGH_ERR&t;3850&t;/* + 15% V PCI-IO High Err Threshold */
DECL|macro|SK_SEN_PCI_IO_3V3_HIGH_WARN
mdefine_line|#define&t;SK_SEN_PCI_IO_3V3_HIGH_WARN&t;3674&t;/* + 10% V PCI-IO High Warn Threshold */
multiline_comment|/*&t;&t;3300&t;mVolt */
DECL|macro|SK_SEN_PCI_IO_3V3_LOW_WARN
mdefine_line|#define&t;SK_SEN_PCI_IO_3V3_LOW_WARN  2926&t;/* - 10% V PCI-IO Low Warn Threshold */
DECL|macro|SK_SEN_PCI_IO_3V3_LOW_ERR
mdefine_line|#define&t;SK_SEN_PCI_IO_3V3_LOW_ERR   2772&t;/* - 15% V PCI-IO Low Err  Threshold */
multiline_comment|/*&n; * VDD voltage&n; */
DECL|macro|SK_SEN_VDD_HIGH_ERR
mdefine_line|#define&t;SK_SEN_VDD_HIGH_ERR&t;    3630&t;/* Voltage ASIC High Err  Threshold */
DECL|macro|SK_SEN_VDD_HIGH_WARN
mdefine_line|#define&t;SK_SEN_VDD_HIGH_WARN    3476&t;/* Voltage ASIC High Warn Threshold */
DECL|macro|SK_SEN_VDD_LOW_WARN
mdefine_line|#define&t;SK_SEN_VDD_LOW_WARN     3146&t;/* Voltage ASIC Low  Warn Threshold */
DECL|macro|SK_SEN_VDD_LOW_ERR
mdefine_line|#define&t;SK_SEN_VDD_LOW_ERR      2970&t;/* Voltage ASIC Low  Err  Threshold */
multiline_comment|/*&n; * PHY PLL 3V3 voltage&n; */
DECL|macro|SK_SEN_PLL_3V3_HIGH_ERR
mdefine_line|#define&t;SK_SEN_PLL_3V3_HIGH_ERR&t;&t;3630&t;/* Voltage PMA High Err  Threshold */
DECL|macro|SK_SEN_PLL_3V3_HIGH_WARN
mdefine_line|#define&t;SK_SEN_PLL_3V3_HIGH_WARN&t;3476&t;/* Voltage PMA High Warn Threshold */
DECL|macro|SK_SEN_PLL_3V3_LOW_WARN
mdefine_line|#define&t;SK_SEN_PLL_3V3_LOW_WARN&t;&t;3146&t;/* Voltage PMA Low  Warn Threshold */
DECL|macro|SK_SEN_PLL_3V3_LOW_ERR
mdefine_line|#define&t;SK_SEN_PLL_3V3_LOW_ERR&t;&t;2970&t;/* Voltage PMA Low  Err  Threshold */
multiline_comment|/*&n; * VAUX (YUKON only)&n; */
DECL|macro|SK_SEN_VAUX_3V3_HIGH_ERR
mdefine_line|#define&t;SK_SEN_VAUX_3V3_HIGH_ERR&t;3630&t;/* Voltage VAUX High Err Threshold */
DECL|macro|SK_SEN_VAUX_3V3_HIGH_WARN
mdefine_line|#define&t;SK_SEN_VAUX_3V3_HIGH_WARN&t;3476&t;/* Voltage VAUX High Warn Threshold */
DECL|macro|SK_SEN_VAUX_3V3_LOW_WARN
mdefine_line|#define&t;SK_SEN_VAUX_3V3_LOW_WARN&t;3146&t;/* Voltage VAUX Low Warn Threshold */
DECL|macro|SK_SEN_VAUX_3V3_LOW_ERR
mdefine_line|#define&t;SK_SEN_VAUX_3V3_LOW_ERR&t;    2970&t;/* Voltage VAUX Low Err Threshold */
DECL|macro|SK_SEN_VAUX_0V_WARN_ERR
mdefine_line|#define&t;SK_SEN_VAUX_0V_WARN_ERR&t;       0&t;/* if VAUX not present */
DECL|macro|SK_SEN_VAUX_RANGE_LIMITER
mdefine_line|#define&t;SK_SEN_VAUX_RANGE_LIMITER&t;1000&t;/* 1000 mV range delimiter */
multiline_comment|/*&n; * PHY 2V5 voltage&n; */
DECL|macro|SK_SEN_PHY_2V5_HIGH_ERR
mdefine_line|#define&t;SK_SEN_PHY_2V5_HIGH_ERR&t;&t;2750&t;/* Voltage PHY High Err Threshold */
DECL|macro|SK_SEN_PHY_2V5_HIGH_WARN
mdefine_line|#define&t;SK_SEN_PHY_2V5_HIGH_WARN&t;2640&t;/* Voltage PHY High Warn Threshold */
DECL|macro|SK_SEN_PHY_2V5_LOW_WARN
mdefine_line|#define&t;SK_SEN_PHY_2V5_LOW_WARN&t;&t;2376&t;/* Voltage PHY Low Warn Threshold */
DECL|macro|SK_SEN_PHY_2V5_LOW_ERR
mdefine_line|#define&t;SK_SEN_PHY_2V5_LOW_ERR&t;&t;2222&t;/* Voltage PHY Low Err Threshold */
multiline_comment|/*&n; * ASIC Core 1V5 voltage (YUKON only)&n; */
DECL|macro|SK_SEN_CORE_1V5_HIGH_ERR
mdefine_line|#define&t;SK_SEN_CORE_1V5_HIGH_ERR    1650&t;/* Voltage ASIC Core High Err Threshold */
DECL|macro|SK_SEN_CORE_1V5_HIGH_WARN
mdefine_line|#define&t;SK_SEN_CORE_1V5_HIGH_WARN&t;1575&t;/* Voltage ASIC Core High Warn Threshold */
DECL|macro|SK_SEN_CORE_1V5_LOW_WARN
mdefine_line|#define&t;SK_SEN_CORE_1V5_LOW_WARN&t;1425&t;/* Voltage ASIC Core Low Warn Threshold */
DECL|macro|SK_SEN_CORE_1V5_LOW_ERR
mdefine_line|#define&t;SK_SEN_CORE_1V5_LOW_ERR &t;1350&t;/* Voltage ASIC Core Low Err Threshold */
multiline_comment|/*&n; * FAN 1 speed&n; */
multiline_comment|/* assuming: 6500rpm +-15%, 4 pulses,&n; * warning at:&t;80 %&n; * error at:&t;70 %&n; * no upper limit&n; */
DECL|macro|SK_SEN_FAN_HIGH_ERR
mdefine_line|#define&t;SK_SEN_FAN_HIGH_ERR&t;&t;20000&t;/* FAN Speed High Err Threshold */
DECL|macro|SK_SEN_FAN_HIGH_WARN
mdefine_line|#define&t;SK_SEN_FAN_HIGH_WARN&t;20000&t;/* FAN Speed High Warn Threshold */
DECL|macro|SK_SEN_FAN_LOW_WARN
mdefine_line|#define&t;SK_SEN_FAN_LOW_WARN &t;5200&t;/* FAN Speed Low Warn Threshold */
DECL|macro|SK_SEN_FAN_LOW_ERR
mdefine_line|#define&t;SK_SEN_FAN_LOW_ERR&t;&t;4550&t;/* FAN Speed Low Err Threshold */
multiline_comment|/*&n; * Some Voltages need dynamic thresholds&n; */
DECL|macro|SK_SEN_DYN_INIT_NONE
mdefine_line|#define&t;SK_SEN_DYN_INIT_NONE&t;&t; 0  /* No dynamic init of thresholds */
DECL|macro|SK_SEN_DYN_INIT_PCI_IO
mdefine_line|#define&t;SK_SEN_DYN_INIT_PCI_IO&t;&t;10  /* Init PCI-IO with new thresholds */
DECL|macro|SK_SEN_DYN_INIT_VAUX
mdefine_line|#define&t;SK_SEN_DYN_INIT_VAUX&t;&t;11  /* Init VAUX with new thresholds */
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
