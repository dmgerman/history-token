multiline_comment|/******************************************************************************&n; *&n; * Name:&t;sklm80.c&n; * Project:&t;Gigabit Ethernet Adapters, TWSI-Module&n; * Version:&t;$Revision: 1.22 $&n; * Date:&t;$Date: 2003/10/20 09:08:21 $&n; * Purpose:&t;Functions to access Voltage and Temperature Sensor (LM80)&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: sklm80.c,v $&n; *&t;Revision 1.22  2003/10/20 09:08:21  rschmidt&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.21  2003/09/23 09:29:04  malthoff&n; *&t;Parameter Dev_Size added to macro SK_I2C_CTL.&n; *&t;&n; *&t;Revision 1.20  2002/08/13 09:16:27  rschmidt&n; *&t;Changed return value for SkLm80ReadSensor() back to &squot;int&squot;&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.19  2002/08/06 09:43:31  jschmalz&n; *&t;Extensions and changes for Yukon.&n; *&t;&n; *&t;Revision 1.18  2002/08/02 12:26:57  rschmidt&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.17  1999/11/22 13:35:51  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.16  1999/05/27 14:05:47  malthoff&n; *&t;Fans: Set SenVal to 0 if the fan value is 0 or 0xff. Both values&n; *&t;are outside the limits (0: div zero error, 0xff: value not in&n; *&t;range, assume 0).&n; *&t;&n; *&t;Revision 1.15  1999/05/27 13:38:51  malthoff&n; *&t;Pervent from Division by zero errors.&n; *&t;&n; *&t;Revision 1.14  1999/05/20 09:20:01  cgoos&n; *&t;Changes for 1000Base-T (Fan sensors).&n; *&t;&n; *&t;Revision 1.13  1998/10/22 09:48:14  gklug&n; *&t;fix: SysKonnectFileId typo&n; *&t;&n; *&t;Revision 1.12  1998/10/09 06:12:06  malthoff&n; *&t;Remove ID_sccs by SysKonnectFileId.&n; *&t;&n; *&t;Revision 1.11  1998/09/04 08:33:48  malthoff&n; *&t;bug fix: SenState = SK_SEN_IDLE when&n; *&t;leaving SK_SEN_VALEXT state&n; *&t;&n; *&t;Revision 1.10  1998/08/20 12:02:10  gklug&n; *&t;fix: compiler warnings type mismatch&n; *&n; *&t;Revision 1.9  1998/08/20 11:37:38  gklug&n; *&t;chg: change Ioc to IoC&n; *&t;&n; *&t;Revision 1.8  1998/08/19 12:20:58  gklug&n; *&t;fix: remove struct from C files (see CCC)&n; *&t;&n; *&t;Revision 1.7  1998/08/17 07:04:57  malthoff&n; *&t;Take SkLm80RcvReg() function from ski2c.c.&n; *&t;Add IoC parameter to BREAK_OR_WAIT() macro.&n; *&t;&n; *&t;Revision 1.6  1998/08/14 07:11:28  malthoff&n; *&t;remove pAc with pAC.&n; *&n; *&t;Revision 1.5  1998/08/14 06:46:55  gklug&n; *&t;fix: temperature can get negative&n; *&n; *&t;Revision 1.4  1998/08/13 08:27:04  gklug&n; *&t;add: temperature reading now o.k.&n; *&t;fix: pSen declaration, SK_ERR_LOG call, ADDR macro&n; *&n; *&t;Revision 1.3  1998/08/13 07:28:21  gklug&n; *&t;fix: pSen was wrong initialized&n; *&t;add: correct conversion for voltage readings&n; *&n; *&t;Revision 1.2  1998/08/11 07:52:14  gklug&n; *&t;add: Lm80 read sensor function&n; *&n; *&t;Revision 1.1  1998/07/17 09:57:12  gklug&n; *&t;initial version&n; *&n; ******************************************************************************/
multiline_comment|/*&n;&t;LM80 functions&n;*/
macro_line|#if (defined(DEBUG) || ((!defined(LINT)) &amp;&amp; (!defined(SK_SLIM))))
DECL|variable|SysKonnectFileId
r_static
r_const
r_char
id|SysKonnectFileId
(braket
)braket
op_assign
l_string|&quot;@(#) $Id: sklm80.c,v 1.22 2003/10/20 09:08:21 rschmidt Exp $ (C) Marvell. &quot;
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;h/skdrv1st.h&quot;&t;&t;/* Driver Specific Definitions */
macro_line|#include &quot;h/lm80.h&quot;
macro_line|#include &quot;h/skdrv2nd.h&quot;&t;&t;/* Adapter Control- and Driver specific Def. */
macro_line|#ifdef&t;SK_DIAG
DECL|macro|BREAK_OR_WAIT
mdefine_line|#define&t;BREAK_OR_WAIT(pAC,IoC,Event)&t;SkI2cWait(pAC,IoC,Event)
macro_line|#else&t;/* nSK_DIAG */
DECL|macro|BREAK_OR_WAIT
mdefine_line|#define&t;BREAK_OR_WAIT(pAC,IoC,Event)&t;break
macro_line|#endif&t;/* nSK_DIAG */
macro_line|#ifdef&t;SK_DIAG
multiline_comment|/*&n; * read the register &squot;Reg&squot; from the device &squot;Dev&squot;&n; *&n; * return &t;read error&t;-1&n; *&t;&t;success&t;&t;the read value&n; */
DECL|function|SkLm80RcvReg
r_int
id|SkLm80RcvReg
c_func
(paren
id|SK_IOC
id|IoC
comma
multiline_comment|/* Adapter Context */
r_int
id|Dev
comma
multiline_comment|/* I2C device address */
r_int
id|Reg
)paren
multiline_comment|/* register to read */
(brace
r_int
id|Val
op_assign
l_int|0
suffix:semicolon
r_int
id|TempExt
suffix:semicolon
multiline_comment|/* Signal device number */
r_if
c_cond
(paren
id|SkI2cSndDev
c_func
(paren
id|IoC
comma
id|Dev
comma
id|I2C_WRITE
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SkI2cSndByte
c_func
(paren
id|IoC
comma
id|Reg
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* repeat start */
r_if
c_cond
(paren
id|SkI2cSndDev
c_func
(paren
id|IoC
comma
id|Dev
comma
id|I2C_READ
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|Reg
)paren
(brace
r_case
id|LM80_TEMP_IN
suffix:colon
id|Val
op_assign
(paren
r_int
)paren
id|SkI2cRcvByte
c_func
(paren
id|IoC
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* First: correct the value: it might be negative */
r_if
c_cond
(paren
(paren
id|Val
op_amp
l_int|0x80
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Value is negative */
id|Val
op_assign
id|Val
op_minus
l_int|256
suffix:semicolon
)brace
id|Val
op_assign
id|Val
op_star
id|SK_LM80_TEMP_LSB
suffix:semicolon
id|SkI2cStop
c_func
(paren
id|IoC
)paren
suffix:semicolon
id|TempExt
op_assign
(paren
r_int
)paren
id|SkLm80RcvReg
c_func
(paren
id|IoC
comma
id|LM80_ADDR
comma
id|LM80_TEMP_CTRL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Val
OG
l_int|0
)paren
(brace
id|Val
op_add_assign
(paren
(paren
id|TempExt
op_rshift
l_int|7
)paren
op_star
id|SK_LM80_TEMPEXT_LSB
)paren
suffix:semicolon
)brace
r_else
(brace
id|Val
op_sub_assign
(paren
(paren
id|TempExt
op_rshift
l_int|7
)paren
op_star
id|SK_LM80_TEMPEXT_LSB
)paren
suffix:semicolon
)brace
r_return
id|Val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LM80_VT0_IN
suffix:colon
r_case
id|LM80_VT1_IN
suffix:colon
r_case
id|LM80_VT2_IN
suffix:colon
r_case
id|LM80_VT3_IN
suffix:colon
id|Val
op_assign
(paren
r_int
)paren
id|SkI2cRcvByte
c_func
(paren
id|IoC
comma
l_int|1
)paren
op_star
id|SK_LM80_VT_LSB
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|Val
op_assign
(paren
r_int
)paren
id|SkI2cRcvByte
c_func
(paren
id|IoC
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|SkI2cStop
c_func
(paren
id|IoC
)paren
suffix:semicolon
r_return
id|Val
suffix:semicolon
)brace
macro_line|#endif&t;/* SK_DIAG */
multiline_comment|/*&n; * read a sensors value (LM80 specific)&n; *&n; * This function reads a sensors value from the I2C sensor chip LM80.&n; * The sensor is defined by its index into the sensors database in the struct&n; * pAC points to.&n; *&n; * Returns&t;1 if the read is completed&n; *&t;&t;0 if the read must be continued (I2C Bus still allocated)&n; */
DECL|function|SkLm80ReadSensor
r_int
id|SkLm80ReadSensor
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapter Context */
id|SK_IOC
id|IoC
comma
multiline_comment|/* I/O Context needed in level 1 and 2 */
id|SK_SENSOR
op_star
id|pSen
)paren
multiline_comment|/* Sensor to be read */
(brace
id|SK_I32
id|Value
suffix:semicolon
r_switch
c_cond
(paren
id|pSen-&gt;SenState
)paren
(brace
r_case
id|SK_SEN_IDLE
suffix:colon
multiline_comment|/* Send address to ADDR register */
id|SK_I2C_CTL
c_func
(paren
id|IoC
comma
id|I2C_READ
comma
id|pSen-&gt;SenDev
comma
id|I2C_025K_DEV
comma
id|pSen-&gt;SenReg
comma
l_int|0
)paren
suffix:semicolon
id|pSen-&gt;SenState
op_assign
id|SK_SEN_VALUE
suffix:semicolon
id|BREAK_OR_WAIT
c_func
(paren
id|pAC
comma
id|IoC
comma
id|I2C_READ
)paren
suffix:semicolon
r_case
id|SK_SEN_VALUE
suffix:colon
multiline_comment|/* Read value from data register */
id|SK_IN32
c_func
(paren
id|IoC
comma
id|B2_I2C_DATA
comma
(paren
(paren
id|SK_U32
op_star
)paren
op_amp
id|Value
)paren
)paren
suffix:semicolon
id|Value
op_and_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* only least significant byte is valid */
multiline_comment|/* Do NOT check the Value against the thresholds */
multiline_comment|/* Checking is done in the calling instance */
r_if
c_cond
(paren
id|pSen-&gt;SenType
op_eq
id|SK_SEN_VOLT
)paren
(brace
multiline_comment|/* Voltage sensor */
id|pSen-&gt;SenValue
op_assign
id|Value
op_star
id|SK_LM80_VT_LSB
suffix:semicolon
id|pSen-&gt;SenState
op_assign
id|SK_SEN_IDLE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pSen-&gt;SenType
op_eq
id|SK_SEN_FAN
)paren
(brace
r_if
c_cond
(paren
id|Value
op_ne
l_int|0
op_logical_and
id|Value
op_ne
l_int|0xff
)paren
(brace
multiline_comment|/* Fan speed counter */
id|pSen-&gt;SenValue
op_assign
id|SK_LM80_FAN_FAKTOR
op_div
id|Value
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Indicate Fan error */
id|pSen-&gt;SenValue
op_assign
l_int|0
suffix:semicolon
)brace
id|pSen-&gt;SenState
op_assign
id|SK_SEN_IDLE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* First: correct the value: it might be negative */
r_if
c_cond
(paren
(paren
id|Value
op_amp
l_int|0x80
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Value is negative */
id|Value
op_assign
id|Value
op_minus
l_int|256
suffix:semicolon
)brace
multiline_comment|/* We have a temperature sensor and need to get the signed extension.&n;&t;&t; * For now we get the extension from the last reading, so in the normal&n;&t;&t; * case we won&squot;t see flickering temperatures.&n;&t;&t; */
id|pSen-&gt;SenValue
op_assign
(paren
id|Value
op_star
id|SK_LM80_TEMP_LSB
)paren
op_plus
(paren
id|pSen-&gt;SenValue
op_mod
id|SK_LM80_TEMP_LSB
)paren
suffix:semicolon
multiline_comment|/* Send address to ADDR register */
id|SK_I2C_CTL
c_func
(paren
id|IoC
comma
id|I2C_READ
comma
id|pSen-&gt;SenDev
comma
id|I2C_025K_DEV
comma
id|LM80_TEMP_CTRL
comma
l_int|0
)paren
suffix:semicolon
id|pSen-&gt;SenState
op_assign
id|SK_SEN_VALEXT
suffix:semicolon
id|BREAK_OR_WAIT
c_func
(paren
id|pAC
comma
id|IoC
comma
id|I2C_READ
)paren
suffix:semicolon
r_case
id|SK_SEN_VALEXT
suffix:colon
multiline_comment|/* Read value from data register */
id|SK_IN32
c_func
(paren
id|IoC
comma
id|B2_I2C_DATA
comma
(paren
(paren
id|SK_U32
op_star
)paren
op_amp
id|Value
)paren
)paren
suffix:semicolon
id|Value
op_and_assign
id|LM80_TEMP_LSB_9
suffix:semicolon
multiline_comment|/* only bit 7 is valid */
multiline_comment|/* cut the LSB bit */
id|pSen-&gt;SenValue
op_assign
(paren
(paren
id|pSen-&gt;SenValue
op_div
id|SK_LM80_TEMP_LSB
)paren
op_star
id|SK_LM80_TEMP_LSB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSen-&gt;SenValue
OL
l_int|0
)paren
(brace
multiline_comment|/* Value negative: The bit value must be subtracted */
id|pSen-&gt;SenValue
op_sub_assign
(paren
(paren
id|Value
op_rshift
l_int|7
)paren
op_star
id|SK_LM80_TEMPEXT_LSB
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Value positive: The bit value must be added */
id|pSen-&gt;SenValue
op_add_assign
(paren
(paren
id|Value
op_rshift
l_int|7
)paren
op_star
id|SK_LM80_TEMPEXT_LSB
)paren
suffix:semicolon
)brace
id|pSen-&gt;SenState
op_assign
id|SK_SEN_IDLE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
id|SK_ERR_LOG
c_func
(paren
id|pAC
comma
id|SK_ERRCL_SW
comma
id|SKERR_I2C_E007
comma
id|SKERR_I2C_E007MSG
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Not completed */
r_return
l_int|0
suffix:semicolon
)brace
eof
