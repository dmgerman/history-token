multiline_comment|/******************************************************************************&n; *&n; * Name:    skproc.c&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.2 $&n; * Date:    $Date: 2003/08/12 16:45:29 $&n; * Purpose:&t;Funktions to display statictic data&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2003 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;Created 22-Nov-2000&n; *&t;Author: Mirko Lindner (mlindner@syskonnect.de)&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skproc.c,v $&n; *&t;Revision 1.2  2003/08/12 16:45:29  mlindner&n; *&t;Add: Removed SkNumber and SkDoDiv&n; *&t;Add: Counter output as (unsigned long long)&n; *&t;&n; *&t;Revision 1.1  2003/07/18 13:39:57  rroesler&n; *&t;Fix: Re-enter after CVS crash&n; *&t;&n; *&t;Revision 1.8  2003/06/27 14:41:42  rroesler&n; *&t;Corrected compiler-warning kernel 2.2&n; *&t;&n; *&t;Revision 1.7  2003/06/27 12:09:51  rroesler&n; *&t;corrected minor edits&n; *&t;&n; *&t;Revision 1.6  2003/05/26 12:58:53  mlindner&n; *&t;Add: Support for Kernel 2.5/2.6&n; *&t;&n; *&t;Revision 1.5  2003/03/19 14:40:47  mlindner&n; *&t;Fix: Editorial changes&n; *&t;&n; *&t;Revision 1.4  2003/02/25 14:16:37  mlindner&n; *&t;Fix: Copyright statement&n; *&t;&n; *&t;Revision 1.3  2002/10/02 12:59:51  mlindner&n; *&t;Add: Support for Yukon&n; *&t;Add: Speed check and setup&n; *&t;Add: Merge source for kernel 2.2.x and 2.4.x&n; *&t;Add: Read sensor names directly from VPD&n; *&t;Fix: Volt values&n; *&t;&n; *&t;Revision 1.2.2.7  2002/01/14 12:45:15  mlindner&n; *&t;Fix: Editorial changes&n; *&t;&n; *&t;Revision 1.2.2.6  2001/12/06 15:26:07  mlindner&n; *&t;Fix: Return value of proc_read&n; *&t;&n; *&t;Revision 1.2.2.5  2001/12/06 09:57:39  mlindner&n; *&t;New ProcFs entries&n; *&t;&n; *&t;Revision 1.2.2.4  2001/09/05 12:16:02  mlindner&n; *&t;Add: New ProcFs entries&n; *&t;Fix: Counter Errors (Jumbo == to long errors)&n; *&t;Fix: Kernel error compilation&n; *&t;Fix: too short counters&n; *&t;&n; *&t;Revision 1.2.2.3  2001/06/25 07:26:26  mlindner&n; *&t;Add: More error messages&n; *&t;&n; *&t;Revision 1.2.2.2  2001/03/15 12:50:13  mlindner&n; *&t;fix: ProcFS owner protection&n; *&t;&n; *&t;Revision 1.2.2.1  2001/03/12 16:43:48  mlindner&n; *&t;chg: 2.4 requirements for procfs&n; *&t;&n; *&t;Revision 1.1  2001/01/22 14:15:31  mlindner&n; *&t;added ProcFs functionality&n; *&t;Dual Net functionality integrated&n; *&t;Rlmt networks added&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;h/skdrv1st.h&quot;
macro_line|#include &quot;h/skdrv2nd.h&quot;
r_extern
r_struct
id|net_device
op_star
id|SkGeRootDev
suffix:semicolon
r_int
id|sk_proc_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|buffer_location
comma
id|off_t
id|offset
comma
r_int
id|buffer_length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * &t;sk_proc_read - print &quot;summaries&quot; entry &n; *&n; * Description:&n; *  This function fills the proc entry with statistic data about &n; *  the ethernet device.&n; *  &n; *&n; * Returns: buffer with statistic data&n; *&t;&n; */
DECL|function|sk_proc_read
r_int
id|sk_proc_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|buffer_location
comma
id|off_t
id|offset
comma
r_int
id|buffer_length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|t
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DEV_NET
op_star
id|pNet
suffix:semicolon
id|SK_AC
op_star
id|pAC
suffix:semicolon
r_char
id|sens_msg
(braket
l_int|50
)braket
suffix:semicolon
r_int
r_int
id|Flags
suffix:semicolon
r_int
r_int
id|Size
suffix:semicolon
r_struct
id|SK_NET_DEVICE
op_star
id|next
suffix:semicolon
r_struct
id|SK_NET_DEVICE
op_star
id|SkgeProcDev
op_assign
id|SkGeRootDev
suffix:semicolon
id|SK_PNMI_STRUCT_DATA
op_star
id|pPnmiStruct
suffix:semicolon
id|SK_PNMI_STAT
op_star
id|pPnmiStat
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|file
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|data
suffix:semicolon
r_while
c_loop
(paren
id|SkgeProcDev
)paren
(brace
id|pNet
op_assign
(paren
id|DEV_NET
op_star
)paren
id|SkgeProcDev-&gt;priv
suffix:semicolon
id|pAC
op_assign
id|pNet-&gt;pAC
suffix:semicolon
id|next
op_assign
id|pAC-&gt;Next
suffix:semicolon
id|pPnmiStruct
op_assign
op_amp
id|pAC-&gt;PnmiStruct
suffix:semicolon
multiline_comment|/* NetIndex in GetStruct is now required, zero is only dummy */
r_for
c_loop
(paren
id|t
op_assign
id|pAC-&gt;GIni.GIMacsFound
suffix:semicolon
id|t
OG
l_int|0
suffix:semicolon
id|t
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|pAC-&gt;GIni.GIMacsFound
op_eq
l_int|2
)paren
op_logical_and
id|pAC-&gt;RlmtNets
op_eq
l_int|1
)paren
id|t
op_decrement
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pAC-&gt;SlowPathLock
comma
id|Flags
)paren
suffix:semicolon
id|Size
op_assign
id|SK_PNMI_STRUCT_SIZE
suffix:semicolon
id|SkPnmiGetStruct
c_func
(paren
id|pAC
comma
id|pAC-&gt;IoBase
comma
id|pPnmiStruct
comma
op_amp
id|Size
comma
id|t
op_minus
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pAC-&gt;SlowPathLock
comma
id|Flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pAC-&gt;dev
(braket
id|t
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|name
comma
id|file-&gt;name
)paren
op_eq
l_int|0
)paren
(brace
id|pPnmiStat
op_assign
op_amp
id|pPnmiStruct-&gt;Stat
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;nDetailed statistic for device %s&bslash;n&quot;
comma
id|pAC-&gt;dev
(braket
id|t
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;=======================================&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Board statistics */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nBoard statistics&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Active Port                    %c&bslash;n&quot;
comma
l_char|&squot;A&squot;
op_plus
id|pAC-&gt;Rlmt.Net
(braket
id|t
op_minus
l_int|1
)braket
dot
id|Port
(braket
id|pAC-&gt;Rlmt
dot
id|Net
(braket
id|t
op_minus
l_int|1
)braket
dot
id|PrefPort
)braket
op_member_access_from_pointer
id|PortNumber
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Preferred Port                 %c&bslash;n&quot;
comma
l_char|&squot;A&squot;
op_plus
id|pAC-&gt;Rlmt.Net
(braket
id|t
op_minus
l_int|1
)braket
dot
id|Port
(braket
id|pAC-&gt;Rlmt
dot
id|Net
(braket
id|t
op_minus
l_int|1
)braket
dot
id|PrefPort
)braket
op_member_access_from_pointer
id|PortNumber
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Bus speed (MHz)                %d&bslash;n&quot;
comma
id|pPnmiStruct-&gt;BusSpeed
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Bus width (Bit)                %d&bslash;n&quot;
comma
id|pPnmiStruct-&gt;BusWidth
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Hardware revision              v%d.%d&bslash;n&quot;
comma
(paren
id|pAC-&gt;GIni.GIPciHwRev
op_rshift
l_int|4
)paren
op_amp
l_int|0x0F
comma
id|pAC-&gt;GIni.GIPciHwRev
op_amp
l_int|0x0F
)paren
suffix:semicolon
multiline_comment|/* Print sensor informations */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pAC-&gt;I2c.MaxSens
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Check type */
r_switch
c_cond
(paren
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenType
)paren
(brace
r_case
l_int|1
suffix:colon
id|strcpy
c_func
(paren
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|sens_msg
comma
l_string|&quot; (C)&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-25s      %d.%02d&bslash;n&quot;
comma
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
op_div
l_int|10
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
op_mod
l_int|10
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|sens_msg
comma
l_string|&quot; (F)&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-25s      %d.%02d&bslash;n&quot;
comma
id|sens_msg
comma
(paren
(paren
(paren
(paren
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
)paren
op_star
l_int|10
)paren
op_star
l_int|9
)paren
op_div
l_int|5
op_plus
l_int|3200
)paren
op_div
l_int|100
comma
(paren
(paren
(paren
(paren
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
)paren
op_star
l_int|10
)paren
op_star
l_int|9
)paren
op_div
l_int|5
op_plus
l_int|3200
)paren
op_mod
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|strcpy
c_func
(paren
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|sens_msg
comma
l_string|&quot; (V)&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-25s      %d.%03d&bslash;n&quot;
comma
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
op_div
l_int|1000
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
op_mod
l_int|1000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|strcpy
c_func
(paren
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|sens_msg
comma
l_string|&quot; (rpm)&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-25s      %d&bslash;n&quot;
comma
id|sens_msg
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*Receive statistics */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nReceive statistics&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Received bytes                 %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxOctetsOkCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Received packets               %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxOkCts
)paren
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|pAC-&gt;GIni.GP
(braket
l_int|0
)braket
dot
id|PhyType
op_eq
id|SK_PHY_XMAC
op_logical_and
id|pAC-&gt;HWRevision
OL
l_int|12
)paren
(brace
id|pPnmiStruct-&gt;InErrorsCts
op_assign
id|pPnmiStruct-&gt;InErrorsCts
op_minus
id|pPnmiStat-&gt;StatRxShortsCts
suffix:semicolon
id|pPnmiStat-&gt;StatRxShortsCts
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|pNet-&gt;Mtu
OG
l_int|1500
)paren
id|pPnmiStruct-&gt;InErrorsCts
op_assign
id|pPnmiStruct-&gt;InErrorsCts
op_minus
id|pPnmiStat-&gt;StatRxTooLongCts
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Receive errors                 %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStruct-&gt;InErrorsCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Receive dropped                %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStruct-&gt;RxNoBufCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Received multicast             %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxMulticastOkCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Receive error types&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   length                      %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxRuntCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   buffer overflow             %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxFifoOverflowCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   bad crc                     %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxFcsCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   framing                     %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxFramingCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   missed frames               %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxMissedCts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pNet-&gt;Mtu
OG
l_int|1500
)paren
id|pPnmiStat-&gt;StatRxTooLongCts
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   too long                    %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxTooLongCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   carrier extension           %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxCextCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   too short                   %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxShortsCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   symbol                      %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxSymbolCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   LLC MAC size                %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxIRLengthCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   carrier event               %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxCarrierCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   jabber                      %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatRxJabberCts
)paren
suffix:semicolon
multiline_comment|/*Transmit statistics */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nTransmit statistics&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Transmited bytes               %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxOctetsOkCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Transmited packets             %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxOkCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Transmit errors                %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxSingleCollisionCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Transmit dropped               %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStruct-&gt;TxNoBufCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Transmit collisions            %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxSingleCollisionCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Transmit error types&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   excessive collision         %ld&bslash;n&quot;
comma
id|pAC-&gt;stats.tx_aborted_errors
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   carrier                     %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxCarrierCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   fifo underrun               %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxFifoUnderrunCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   heartbeat                   %Ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|pPnmiStat-&gt;StatTxCarrierCts
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;   window                      %ld&bslash;n&quot;
comma
id|pAC-&gt;stats.tx_window_errors
)paren
suffix:semicolon
)brace
)brace
id|SkgeProcDev
op_assign
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|buffer_location
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|buffer_length
op_ge
id|len
op_minus
id|offset
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_return
(paren
id|min_t
c_func
(paren
r_int
comma
id|buffer_length
comma
id|len
op_minus
id|offset
)paren
)paren
suffix:semicolon
)brace
eof
