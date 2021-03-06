multiline_comment|/******************************************************************************&n; *&n; * Name:&t;sklm80.c&n; * Project:&t;Gigabit Ethernet Adapters, TWSI-Module&n; * Version:&t;$Revision: 1.22 $&n; * Date:&t;$Date: 2003/10/20 09:08:21 $&n; * Purpose:&t;Functions to access Voltage and Temperature Sensor (LM80)&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
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
