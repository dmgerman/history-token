multiline_comment|/******************************************************************************&n; *&n; * Name:    skproc.c&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.2.2.2 $&n; * Date:    $Date: 2001/03/15 12:50:13 $&n; * Purpose:&t;Funktions to display statictic data&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;Created 22-Nov-2000&n; *&t;Author: Mirko Lindner (mlindner@syskonnect.de)&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skproc.c,v $&n; *&t;Revision 1.2.2.2  2001/03/15 12:50:13  mlindner&n; *&t;fix: ProcFS owner protection&n; *&t;&n; *&t;Revision 1.2.2.1  2001/03/12 16:43:48  mlindner&n; *&t;chg: 2.4 requirements for procfs&n; *&t;&n; *&t;Revision 1.1  2001/01/22 14:15:31  mlindner&n; *&t;added ProcFs functionality&n; *&t;Dual Net functionality integrated&n; *&t;Rlmt networks added&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;h/skdrv1st.h&quot;
macro_line|#include &quot;h/skdrv2nd.h&quot;
DECL|macro|ZEROPAD
mdefine_line|#define ZEROPAD&t;1&t;&t;/* pad with zero */
DECL|macro|SIGN
mdefine_line|#define SIGN&t;2&t;&t;/* unsigned/signed long */
DECL|macro|PLUS
mdefine_line|#define PLUS&t;4&t;&t;/* show plus */
DECL|macro|SPACE
mdefine_line|#define SPACE&t;8&t;&t;/* space if plus */
DECL|macro|LEFT
mdefine_line|#define LEFT&t;16&t;&t;/* left justified */
singleline_comment|//#define SPECIAL&t;32&t;&t;/* 0x */
DECL|macro|LARGE
mdefine_line|#define LARGE&t;64
r_extern
r_void
id|proc_fill_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|fill
)paren
suffix:semicolon
r_extern
r_char
op_star
id|SkNumber
c_func
(paren
r_char
op_star
id|str
comma
r_int
r_int
id|num
comma
r_int
id|base
comma
r_int
id|size
comma
r_int
id|precision
comma
r_int
id|type
)paren
suffix:semicolon
r_int
id|proc_read
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
DECL|variable|SK_Root_Dir_entry
r_static
r_const
r_char
id|SK_Root_Dir_entry
(braket
)braket
op_assign
l_string|&quot;sk98lin&quot;
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|root_dev
suffix:semicolon
DECL|variable|pSkRootDir
r_struct
id|proc_dir_entry
id|pSkRootDir
op_assign
(brace
l_int|0
comma
r_sizeof
(paren
id|SK_Root_Dir_entry
)paren
op_minus
l_int|1
comma
(paren
r_const
r_char
op_star
)paren
id|SK_Root_Dir_entry
comma
id|S_IFDIR
op_or
id|S_IRUGO
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * &t;proc_read - print &quot;summaries&quot; entry &n; *&n; * Description:&n; *  This function fills the proc entry with statistic data about &n; *  the ethernet device.&n; *  &n; *&n; * Returns: buffer with statistic data&n; *&t;&n; */
DECL|function|proc_read
r_int
id|proc_read
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
id|test_buf
(braket
l_int|100
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
id|net_device
op_star
id|next
suffix:semicolon
r_struct
id|net_device
op_star
id|SkgeProcDev
op_assign
id|root_dev
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
l_string|&quot;==================================&bslash;n&quot;
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
l_string|&quot;Active Port               %c&bslash;n&quot;
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
l_string|&quot;Preferred Port            %c&bslash;n&quot;
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
l_string|&quot;Bus speed (Mhz)           %d&bslash;n&quot;
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
l_string|&quot;Bus width (Bit)           %d&bslash;n&quot;
comma
id|pPnmiStruct-&gt;BusWidth
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SK_MAX_SENSORS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
comma
l_string|&quot;Temperature&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Temperature (C)           %d.%d&bslash;n&quot;
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Temperature (F)           %d.%d&bslash;n&quot;
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
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
comma
l_string|&quot;Speed Fan&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Speed Fan                 %d&bslash;n&quot;
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenValue
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-20s      %d.%d&bslash;n&quot;
comma
id|pAC-&gt;I2c.SenTable
(braket
id|i
)braket
dot
id|SenDesc
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
l_string|&quot;Received bytes            %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxOctetsOkCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Received packets          %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxOkCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Received errors           %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxFcsCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Received dropped          %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStruct-&gt;RxNoBufCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Received multicast        %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxMulticastOkCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Received errors types&bslash;n&quot;
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
l_string|&quot;   length errors          %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxRuntCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   over errors            %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxFifoOverflowCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   crc errors             %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxFcsCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   frame errors           %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxFramingCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   fifo errors            %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxFifoOverflowCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   missed errors          %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatRxMissedCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Transmit bytes            %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxOctetsOkCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Transmit packets          %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxOkCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Transmit errors           %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxSingleCollisionCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Transmit dropped          %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStruct-&gt;TxNoBufCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Transmit collisions       %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxSingleCollisionCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;Transmited errors types&bslash;n&quot;
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
l_string|&quot;   aborted errors         %ld&bslash;n&quot;
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
l_string|&quot;   carrier errors         %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxCarrierCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   fifo errors            %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxFifoUnderrunCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   heartbeat errors       %s&bslash;n&quot;
comma
id|SkNumber
c_func
(paren
id|test_buf
comma
id|pPnmiStat-&gt;StatTxCarrierCts
comma
l_int|10
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
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
l_string|&quot;   window errors          %ld&bslash;n&quot;
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
id|min
c_func
(paren
id|buffer_length
comma
id|len
op_minus
id|offset
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * SkDoDiv - convert 64bit number&n; *&n; * Description:&n; *&t;This function &quot;converts&quot; a long long number.&n; *&n; * Returns:&n; *&t;remainder of division&n; */
DECL|function|SkDoDiv
r_static
r_int
id|SkDoDiv
(paren
r_int
r_int
id|Dividend
comma
r_int
id|Divisor
comma
r_int
r_int
op_star
id|pErg
)paren
(brace
r_int
id|Rest
suffix:semicolon
r_int
r_int
id|Ergebnis
suffix:semicolon
r_int
id|Akku
suffix:semicolon
id|Akku
op_assign
id|Dividend
op_rshift
l_int|32
suffix:semicolon
id|Ergebnis
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|Akku
op_div
id|Divisor
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
id|Rest
op_assign
id|Akku
op_mod
id|Divisor
suffix:semicolon
id|Akku
op_assign
id|Rest
op_lshift
l_int|16
suffix:semicolon
id|Akku
op_or_assign
(paren
(paren
id|Dividend
op_amp
l_int|0xFFFF0000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|Ergebnis
op_add_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|Akku
op_div
id|Divisor
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
id|Rest
op_assign
id|Akku
op_mod
id|Divisor
suffix:semicolon
id|Akku
op_assign
id|Rest
op_lshift
l_int|16
suffix:semicolon
id|Akku
op_or_assign
(paren
id|Dividend
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
id|Ergebnis
op_add_assign
(paren
id|Akku
op_div
id|Divisor
)paren
suffix:semicolon
id|Rest
op_assign
id|Akku
op_mod
id|Divisor
suffix:semicolon
op_star
id|pErg
op_assign
id|Ergebnis
suffix:semicolon
r_return
(paren
id|Rest
)paren
suffix:semicolon
)brace
macro_line|#if 0
mdefine_line|#define do_div(n,base) ({ &bslash;&n;long long __res; &bslash;&n;__res = ((unsigned long long) n) % (unsigned) base; &bslash;&n;n = ((unsigned long long) n) / (unsigned) base; &bslash;&n;__res; })
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *&n; * SkNumber - Print results&n; *&n; * Description:&n; *&t;This function converts a long long number into a string.&n; *&n; * Returns:&n; *&t;number as string&n; */
DECL|function|SkNumber
r_char
op_star
id|SkNumber
c_func
(paren
r_char
op_star
id|str
comma
r_int
r_int
id|num
comma
r_int
id|base
comma
r_int
id|size
comma
r_int
id|precision
comma
r_int
id|type
)paren
(brace
r_char
id|c
comma
id|sign
comma
id|tmp
(braket
l_int|66
)braket
comma
op_star
id|strorg
op_assign
id|str
suffix:semicolon
r_const
r_char
op_star
id|digits
op_assign
l_string|&quot;0123456789abcdefghijklmnopqrstuvwxyz&quot;
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LARGE
)paren
id|digits
op_assign
l_string|&quot;0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ&quot;
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LEFT
)paren
id|type
op_and_assign
op_complement
id|ZEROPAD
suffix:semicolon
r_if
c_cond
(paren
id|base
template_param
l_int|36
)paren
r_return
l_int|0
suffix:semicolon
id|c
op_assign
(paren
id|type
op_amp
id|ZEROPAD
)paren
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot; &squot;
suffix:semicolon
id|sign
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SIGN
)paren
(brace
r_if
c_cond
(paren
id|num
OL
l_int|0
)paren
(brace
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|num
op_assign
op_minus
id|num
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|PLUS
)paren
(brace
id|sign
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|SPACE
)paren
(brace
id|sign
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
id|size
op_sub_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
id|size
op_decrement
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_while
c_loop
(paren
id|num
op_ne
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
id|digits
(braket
id|SkDoDiv
c_func
(paren
id|num
comma
id|base
comma
op_amp
id|num
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|precision
)paren
id|precision
op_assign
id|i
suffix:semicolon
id|size
op_sub_assign
id|precision
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
(paren
id|ZEROPAD
op_plus
id|LEFT
)paren
)paren
)paren
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sign
)paren
op_star
id|str
op_increment
op_assign
id|sign
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
(brace
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_star
id|str
op_increment
op_assign
id|digits
(braket
l_int|33
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
id|c
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|precision
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
id|tmp
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|str
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|strorg
suffix:semicolon
)brace
eof
