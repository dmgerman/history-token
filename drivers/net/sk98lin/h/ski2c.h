multiline_comment|/******************************************************************************&n; *&n; * Name:&t;ski2c.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.30 $&n; * Date:&t;$Date: 2001/04/05 11:38:09 $&n; * Purpose:&t;Defines to access Voltage and Temperature Sensor&n; *&t;&t;(taken from Monalisa (taken from Concentrator))&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: ski2c.h,v $&n; *&t;Revision 1.30  2001/04/05 11:38:09  rassmann&n; *&t;Set SenState to idle in SkI2cWaitIrq().&n; *&t;Changed error message in SkI2cWaitIrq().&n; *&t;&n; *&t;Revision 1.29  2000/08/03 14:28:17  rassmann&n; *&t;- Added function to wait for I2C being ready before resetting the board.&n; *&t;- Replaced one duplicate &quot;out of range&quot; message with correct one.&n; *&t;&n; *&t;Revision 1.28  1999/11/22 13:55:46  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.27  1999/05/20 09:23:10  cgoos&n; *&t;Changes for 1000Base-T (Fan sensors).&n; *&t;&n; *&t;Revision 1.26  1998/12/01 13:45:47  gklug&n; *&t;add: InitLevel to I2c struct&n; *&t;&n; *&t;Revision 1.25  1998/11/03 06:55:16  gklug&n; *&t;add: Dummy Reads to I2c struct&n; *&t;&n; *&t;Revision 1.24  1998/10/02 14:28:59  cgoos&n; *&t;Added prototype for SkI2cIsr.&n; *&t;&n; *&t;Revision 1.23  1998/09/08 12:20:11  gklug&n; *&t;add: prototypes for init and read functions&n; *&t;&n; *&t;Revision 1.22  1998/09/08 07:37:56  gklug&n; *&t;add: log error if PCI_IO voltage sensor could not be initialized&n; *&t;&n; *&t;Revision 1.21  1998/09/04 08:38:05  malthoff&n; *&t;Change the values for I2C_READ and I2C_WRITE&n; *&t;&n; *&t;Revision 1.20  1998/08/25 07:52:22  gklug&n; *&t;chg: Timestamps (last) added for logging&n; *&n; *&t;Revision 1.19  1998/08/25 06:09:00  gklug&n; *&t;rmv: warning and error levels of the individual sensors.&n; *&t;add: timing definitions for sending traps and logging errors&n; *&t;&n; *&t;Revision 1.18  1998/08/20 11:41:15  gklug&n; *&t;chg: omit STRCPY macro by using char * as Sensor Description&n; *&t;&n; *&t;Revision 1.17  1998/08/20 11:37:43  gklug&n; *&t;chg: change Ioc to IoC&n; *&t;&n; *&t;Revision 1.16  1998/08/20 11:30:38  gklug&n; *&t;fix: SenRead declaration&n; *&t;&n; *&t;Revision 1.15  1998/08/20 11:27:53  gklug&n; *&t;fix: Compile bugs with new awrning constants&n; *&t;&n; *&t;Revision 1.14  1998/08/20 08:53:12  gklug&n; *&t;fix: compiler errors&n; *&t;add: Threshold values&n; *&t;&n; *&t;Revision 1.13  1998/08/19 12:21:16  gklug&n; *&t;fix: remove struct from C files (see CCC)&n; *&t;add: typedefs for all structs&n; *&t;&n; *&t;Revision 1.12  1998/08/19 10:57:41  gklug&n; *&t;add: Warning levels&n; *&t;&n; *&t;Revision 1.11  1998/08/18 08:37:02  malthoff&n; *&t;Prototypes not required for SK_DIAG.&n; *&t;&n; *&t;Revision 1.10  1998/08/17 13:54:00  gklug&n; *&t;fix: declaration of event function&n; *&t;&n; *&t;Revision 1.9  1998/08/17 06:48:39  malthoff&n; *&t;Remove some unrequired macros.&n; *&t;Fix the compiler errors.&n; *&t;&n; *&t;Revision 1.8  1998/08/14 06:47:19  gklug&n; *&t;fix: Values are intergers&n; *&n; *&t;Revision 1.7  1998/08/14 06:26:05  gklug&n; *&t;add: Init error message&n; *&n; *&t;Revision 1.6  1998/08/13 08:31:08  gklug&n; *&t;add: Error message&n; *&n; *&t;Revision 1.5  1998/08/12 14:32:04  gklug&n; *&t;add: new error code/message&n; *&n; *&t;Revision 1.4  1998/08/12 13:39:08  gklug&n; *&t;chg: names of error messages&n; *&t;add: defines for Sensor type and thresholds&n; *&n; *&t;Revision 1.3  1998/08/11 07:57:16  gklug&n; *&t;add: sensor struct&n; *&t;add: Timeout defines&n; *&t;add: I2C control struct for pAC&n; *&n; *&t;Revision 1.2  1998/07/17 11:29:02  gklug&n; *&t;rmv: Microwire and SMTPANIC&n; *&n; *&t;Revision 1.1  1998/06/19 14:30:10  malthoff&n; *&t;Created. Sources taken from ML Project.&n; *&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * SKI2C.H&t;contains all I2C specific defines&n; */
macro_line|#ifndef _SKI2C_H_
DECL|macro|_SKI2C_H_
mdefine_line|#define _SKI2C_H_
DECL|typedef|SK_SENSOR
r_typedef
r_struct
id|s_Sensor
id|SK_SENSOR
suffix:semicolon
macro_line|#include &quot;h/skgei2c.h&quot;
multiline_comment|/*&n; * Define the I2c events.&n; */
DECL|macro|SK_I2CEV_IRQ
mdefine_line|#define SK_I2CEV_IRQ&t;1&t;/* IRQ happened Event */
DECL|macro|SK_I2CEV_TIM
mdefine_line|#define SK_I2CEV_TIM&t;2&t;/* Timeout event */
DECL|macro|SK_I2CEV_CLEAR
mdefine_line|#define SK_I2CEV_CLEAR&t;3&t;/* Clear Mib Values */
multiline_comment|/*&n; * Define READ and WRITE Constants.&n; */
DECL|macro|I2C_READ
mdefine_line|#define&t;I2C_READ&t;0
DECL|macro|I2C_WRITE
mdefine_line|#define&t;I2C_WRITE&t;1
DECL|macro|I2C_BURST
mdefine_line|#define I2C_BURST&t;1
DECL|macro|I2C_SIGLE
mdefine_line|#define I2C_SIGLE&t;0
DECL|macro|SKERR_I2C_E001
mdefine_line|#define&t;SKERR_I2C_E001&t;&t;(SK_ERRBASE_I2C+0)
DECL|macro|SKERR_I2C_E001MSG
mdefine_line|#define&t;SKERR_I2C_E001MSG&t;&quot;Sensor index unknown&quot;
DECL|macro|SKERR_I2C_E002
mdefine_line|#define&t;SKERR_I2C_E002&t;&t;(SKERR_I2C_E001+1)
DECL|macro|SKERR_I2C_E002MSG
mdefine_line|#define&t;SKERR_I2C_E002MSG&t;&quot;I2C: transfer does not complete.&bslash;n&quot;
DECL|macro|SKERR_I2C_E003
mdefine_line|#define&t;SKERR_I2C_E003&t;&t;(SKERR_I2C_E002+1)
DECL|macro|SKERR_I2C_E003MSG
mdefine_line|#define&t;SKERR_I2C_E003MSG&t;&quot;lm80: NAK on device send.&bslash;n&quot;
DECL|macro|SKERR_I2C_E004
mdefine_line|#define&t;SKERR_I2C_E004&t;&t;(SKERR_I2C_E003+1)
DECL|macro|SKERR_I2C_E004MSG
mdefine_line|#define&t;SKERR_I2C_E004MSG&t;&quot;lm80: NAK on register send.&bslash;n&quot;
DECL|macro|SKERR_I2C_E005
mdefine_line|#define&t;SKERR_I2C_E005&t;&t;(SKERR_I2C_E004+1)
DECL|macro|SKERR_I2C_E005MSG
mdefine_line|#define&t;SKERR_I2C_E005MSG&t;&quot;lm80: NAK on device (2) send.&bslash;n&quot;
DECL|macro|SKERR_I2C_E006
mdefine_line|#define&t;SKERR_I2C_E006&t;&t;(SKERR_I2C_E005+1)
DECL|macro|SKERR_I2C_E006MSG
mdefine_line|#define&t;SKERR_I2C_E006MSG&t;&quot;Unknown event&quot;
DECL|macro|SKERR_I2C_E007
mdefine_line|#define&t;SKERR_I2C_E007&t;&t;(SKERR_I2C_E006+1)
DECL|macro|SKERR_I2C_E007MSG
mdefine_line|#define&t;SKERR_I2C_E007MSG&t;&quot;LM80 read out of state&quot;
DECL|macro|SKERR_I2C_E008
mdefine_line|#define&t;SKERR_I2C_E008&t;&t;(SKERR_I2C_E007+1)
DECL|macro|SKERR_I2C_E008MSG
mdefine_line|#define&t;SKERR_I2C_E008MSG&t;&quot;unexpected sensor read completed&quot;
DECL|macro|SKERR_I2C_E009
mdefine_line|#define&t;SKERR_I2C_E009&t;&t;(SKERR_I2C_E008+1)
DECL|macro|SKERR_I2C_E009MSG
mdefine_line|#define&t;SKERR_I2C_E009MSG&t;&quot;WARNING: temperature sensor out of range&quot;
DECL|macro|SKERR_I2C_E010
mdefine_line|#define&t;SKERR_I2C_E010&t;&t;(SKERR_I2C_E009+1)
DECL|macro|SKERR_I2C_E010MSG
mdefine_line|#define&t;SKERR_I2C_E010MSG&t;&quot;WARNING: voltage sensor out of range&quot;
DECL|macro|SKERR_I2C_E011
mdefine_line|#define&t;SKERR_I2C_E011&t;&t;(SKERR_I2C_E010+1)
DECL|macro|SKERR_I2C_E011MSG
mdefine_line|#define&t;SKERR_I2C_E011MSG&t;&quot;ERROR: temperature sensor out of range&quot;
DECL|macro|SKERR_I2C_E012
mdefine_line|#define&t;SKERR_I2C_E012&t;&t;(SKERR_I2C_E011+1)
DECL|macro|SKERR_I2C_E012MSG
mdefine_line|#define&t;SKERR_I2C_E012MSG&t;&quot;ERROR: voltage sensor out of range&quot;
DECL|macro|SKERR_I2C_E013
mdefine_line|#define&t;SKERR_I2C_E013&t;&t;(SKERR_I2C_E012+1)
DECL|macro|SKERR_I2C_E013MSG
mdefine_line|#define&t;SKERR_I2C_E013MSG&t;&quot;ERROR: couldn&squot;t init sensor&quot;
DECL|macro|SKERR_I2C_E014
mdefine_line|#define&t;SKERR_I2C_E014&t;&t;(SKERR_I2C_E013+1)
DECL|macro|SKERR_I2C_E014MSG
mdefine_line|#define&t;SKERR_I2C_E014MSG&t;&quot;WARNING: fan sensor out of range&quot;
DECL|macro|SKERR_I2C_E015
mdefine_line|#define&t;SKERR_I2C_E015&t;&t;(SKERR_I2C_E014+1)
DECL|macro|SKERR_I2C_E015MSG
mdefine_line|#define&t;SKERR_I2C_E015MSG&t;&quot;ERROR: fan sensor out of range&quot;
DECL|macro|SKERR_I2C_E016
mdefine_line|#define&t;SKERR_I2C_E016&t;&t;(SKERR_I2C_E015+1)
DECL|macro|SKERR_I2C_E016MSG
mdefine_line|#define&t;SKERR_I2C_E016MSG&t;&quot;I2C: active transfer does not complete.&bslash;n&quot;
multiline_comment|/*&n; * Define Timeout values&n; */
DECL|macro|SK_I2C_TIM_LONG
mdefine_line|#define&t;SK_I2C_TIM_LONG&t;&t;2000000L&t;/* 2 seconds */
DECL|macro|SK_I2C_TIM_SHORT
mdefine_line|#define&t;SK_I2C_TIM_SHORT&t; 100000L&t;/* 100 milliseconds */
multiline_comment|/*&n; * Define trap and error log hold times&n; */
macro_line|#ifndef&t;SK_SEN_ERR_TR_HOLD
DECL|macro|SK_SEN_ERR_TR_HOLD
mdefine_line|#define&t;SK_SEN_ERR_TR_HOLD&t;&t;(4*SK_TICKS_PER_SEC)
macro_line|#endif
macro_line|#ifndef&t;SK_SEN_ERR_LOG_HOLD
DECL|macro|SK_SEN_ERR_LOG_HOLD
mdefine_line|#define&t;SK_SEN_ERR_LOG_HOLD&t;&t;(60*SK_TICKS_PER_SEC)
macro_line|#endif
macro_line|#ifndef&t;SK_SEN_WARN_TR_HOLD
DECL|macro|SK_SEN_WARN_TR_HOLD
mdefine_line|#define&t;SK_SEN_WARN_TR_HOLD&t;&t;(15*SK_TICKS_PER_SEC)
macro_line|#endif
macro_line|#ifndef&t;SK_SEN_WARN_LOG_HOLD
DECL|macro|SK_SEN_WARN_LOG_HOLD
mdefine_line|#define&t;SK_SEN_WARN_LOG_HOLD&t;(15*60*SK_TICKS_PER_SEC)
macro_line|#endif
multiline_comment|/*&n; * Defines for SenType&n; */
DECL|macro|SK_SEN_TEMP
mdefine_line|#define&t;SK_SEN_TEMP&t;1
DECL|macro|SK_SEN_VOLT
mdefine_line|#define&t;SK_SEN_VOLT&t;2
DECL|macro|SK_SEN_FAN
mdefine_line|#define&t;SK_SEN_FAN&t;3
multiline_comment|/*&n; * Define for the ErrorFlag&n; */
DECL|macro|SK_SEN_ERR_OK
mdefine_line|#define&t;SK_SEN_ERR_OK&t;1&t;/* Error Flag: O.K. */
DECL|macro|SK_SEN_ERR_WARN
mdefine_line|#define&t;SK_SEN_ERR_WARN&t;2&t;/* Error Flag: Warning */
DECL|macro|SK_SEN_ERR_ERR
mdefine_line|#define&t;SK_SEN_ERR_ERR&t;3&t;/* Error Flag: Error */
multiline_comment|/*&n; * Define the Sensor struct&n; */
DECL|struct|s_Sensor
r_struct
id|s_Sensor
(brace
DECL|member|SenDesc
r_char
op_star
id|SenDesc
suffix:semicolon
multiline_comment|/* Description */
DECL|member|SenType
r_int
id|SenType
suffix:semicolon
multiline_comment|/* Voltage or Temperature */
DECL|member|SenValue
id|SK_I32
id|SenValue
suffix:semicolon
multiline_comment|/* Current value of the sensor */
DECL|member|SenThreErrHigh
id|SK_I32
id|SenThreErrHigh
suffix:semicolon
multiline_comment|/* High error Threshhold of this sensor */
DECL|member|SenThreWarnHigh
id|SK_I32
id|SenThreWarnHigh
suffix:semicolon
multiline_comment|/* High warning Threshhold of this sensor */
DECL|member|SenThreErrLow
id|SK_I32
id|SenThreErrLow
suffix:semicolon
multiline_comment|/* Lower error Threshold of the sensor */
DECL|member|SenThreWarnLow
id|SK_I32
id|SenThreWarnLow
suffix:semicolon
multiline_comment|/* Lower warning Threshold of the sensor */
DECL|member|SenErrFlag
r_int
id|SenErrFlag
suffix:semicolon
multiline_comment|/* Sensor indicated an error */
DECL|member|SenInit
id|SK_BOOL
id|SenInit
suffix:semicolon
multiline_comment|/* Is sensor initialized? */
DECL|member|SenErrCts
id|SK_U64
id|SenErrCts
suffix:semicolon
multiline_comment|/* Error  trap counter */
DECL|member|SenWarnCts
id|SK_U64
id|SenWarnCts
suffix:semicolon
multiline_comment|/* Warning trap  counter */
DECL|member|SenBegErrTS
id|SK_U64
id|SenBegErrTS
suffix:semicolon
multiline_comment|/* Begin error timestamp */
DECL|member|SenBegWarnTS
id|SK_U64
id|SenBegWarnTS
suffix:semicolon
multiline_comment|/* Begin warning timestamp */
DECL|member|SenLastErrTrapTS
id|SK_U64
id|SenLastErrTrapTS
suffix:semicolon
multiline_comment|/* Last error trap timestamp */
DECL|member|SenLastErrLogTS
id|SK_U64
id|SenLastErrLogTS
suffix:semicolon
multiline_comment|/* Last error log timestamp */
DECL|member|SenLastWarnTrapTS
id|SK_U64
id|SenLastWarnTrapTS
suffix:semicolon
multiline_comment|/* Last warning trap timestamp */
DECL|member|SenLastWarnLogTS
id|SK_U64
id|SenLastWarnLogTS
suffix:semicolon
multiline_comment|/* Last warning log timestamp */
DECL|member|SenState
r_int
id|SenState
suffix:semicolon
multiline_comment|/* Sensor State (see HW specific include) */
DECL|member|SenRead
r_int
(paren
op_star
id|SenRead
)paren
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_struct
id|s_Sensor
op_star
id|pSen
)paren
suffix:semicolon
multiline_comment|/* Sensors read function */
DECL|member|SenReg
id|SK_U16
id|SenReg
suffix:semicolon
multiline_comment|/* Register Address for this sensor */
DECL|member|SenDev
id|SK_U8
id|SenDev
suffix:semicolon
multiline_comment|/* DeviceSelection for this sensor */
)brace
suffix:semicolon
DECL|struct|s_I2c
r_typedef
r_struct
id|s_I2c
(brace
DECL|member|SenTable
id|SK_SENSOR
id|SenTable
(braket
id|SK_MAX_SENSORS
)braket
suffix:semicolon
multiline_comment|/* Sensor Table */
DECL|member|CurrSens
r_int
id|CurrSens
suffix:semicolon
multiline_comment|/* Which sensor is currently queried */
DECL|member|MaxSens
r_int
id|MaxSens
suffix:semicolon
multiline_comment|/* Max. number of sensors */
DECL|member|InitLevel
r_int
id|InitLevel
suffix:semicolon
multiline_comment|/* Initialized Level */
macro_line|#ifndef SK_DIAG
DECL|member|DummyReads
r_int
id|DummyReads
suffix:semicolon
multiline_comment|/* Number of non-checked dummy reads */
DECL|member|SenTimer
id|SK_TIMER
id|SenTimer
suffix:semicolon
multiline_comment|/* Sensors timer */
macro_line|#endif&t;/* !SK_DIAG */
DECL|typedef|SK_I2C
)brace
id|SK_I2C
suffix:semicolon
r_extern
r_int
id|SkI2cReadSensor
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
macro_line|#ifndef SK_DIAG
r_extern
r_int
id|SkI2cEvent
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Event
comma
id|SK_EVPARA
id|Para
)paren
suffix:semicolon
r_extern
r_int
id|SkI2cInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Level
)paren
suffix:semicolon
r_extern
r_void
id|SkI2cWaitIrq
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
)paren
suffix:semicolon
r_extern
r_void
id|SkI2cIsr
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* n_SKI2C_H */
eof
