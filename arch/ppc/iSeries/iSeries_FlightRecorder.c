multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_FlightRecorder.c created by Al Trautman on Jan 22 2001. */
multiline_comment|/************************************************************************/
multiline_comment|/* This code supports the pci interface on the IBM iSeries systems.     */
multiline_comment|/* Copyright (C) 20yy  &lt;Allan H Trautman&gt; &lt;IBM Corp&gt;                    */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is free software; you can redistribute it and/or modify */
multiline_comment|/* it under the terms of the GNU General Public License as published by */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or    */
multiline_comment|/* (at your option) any later version.                                  */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is distributed in the hope that it will be useful,      */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
multiline_comment|/* GNU General Public License for more details.                         */
multiline_comment|/*                                                                      */
multiline_comment|/* You should have received a copy of the GNU General Public License    */
multiline_comment|/* along with this program; if not, write to the:                       */
multiline_comment|/* Free Software Foundation, Inc.,                                      */
multiline_comment|/* 59 Temple Place, Suite 330,                                          */
multiline_comment|/* Boston, MA  02111-1307  USA                                          */
multiline_comment|/************************************************************************/
multiline_comment|/* Change Activity:                                                     */
multiline_comment|/*   Created, Jan 22, 2001                                              */
multiline_comment|/*   Added Time Stamps, April 12, 2001                                  */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_FlightRecorder.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
multiline_comment|/************************************************************************/
multiline_comment|/* Log entry into buffer,                                               */
multiline_comment|/* -&gt;If entry is going to wrap, log &quot;WRAP&quot; and start at the top.        */
multiline_comment|/************************************************************************/
DECL|function|iSeries_LogFr_Entry
r_void
id|iSeries_LogFr_Entry
c_func
(paren
id|FlightRecorder
op_star
id|Fr
comma
r_char
op_star
id|LogText
)paren
(brace
r_int
id|Residual
comma
id|TextLen
suffix:semicolon
r_if
c_cond
(paren
id|Fr-&gt;StartingPointer
OG
l_int|0
)paren
(brace
multiline_comment|/* Initialized yet?             */
id|Residual
op_assign
id|FlightRecorderSize
op_minus
(paren
id|Fr-&gt;CurrentPointer
op_minus
id|Fr-&gt;StartingPointer
)paren
suffix:semicolon
id|TextLen
op_assign
id|strlen
c_func
(paren
id|LogText
)paren
suffix:semicolon
multiline_comment|/* Length of Text               */
r_if
c_cond
(paren
id|TextLen
op_plus
l_int|16
OG
id|Residual
)paren
(brace
multiline_comment|/* Room for text or need to wrap*/
id|strcpy
c_func
(paren
id|Fr-&gt;CurrentPointer
comma
l_string|&quot;WRAP&quot;
)paren
suffix:semicolon
op_increment
id|Fr-&gt;WrapCount
suffix:semicolon
multiline_comment|/* Increment Wraps              */
id|Fr-&gt;CurrentPointer
op_assign
id|Fr-&gt;StartingPointer
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|Fr-&gt;CurrentPointer
comma
id|LogText
)paren
suffix:semicolon
id|Fr-&gt;CurrentPointer
op_add_assign
id|TextLen
op_plus
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|Fr-&gt;CurrentPointer
comma
l_string|&quot;&lt;=&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Log entry with time                                                  */
multiline_comment|/************************************************************************/
DECL|function|iSeries_LogFr_Time
r_void
id|iSeries_LogFr_Time
c_func
(paren
id|FlightRecorder
op_star
id|Fr
comma
r_char
op_star
id|LogText
)paren
(brace
r_struct
id|rtc_time
id|Rtc
suffix:semicolon
r_char
id|LogBuffer
(braket
l_int|256
)braket
suffix:semicolon
id|mf_getRtc
c_func
(paren
op_amp
id|Rtc
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|LogBuffer
comma
l_string|&quot;%02d:%02d:%02d %s&quot;
comma
id|Rtc.tm_hour
comma
id|Rtc.tm_min
comma
id|Rtc.tm_sec
comma
id|LogText
)paren
suffix:semicolon
id|iSeries_LogFr_Entry
c_func
(paren
id|Fr
comma
id|LogBuffer
)paren
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Log Entry with Date and call Time Log                                */
multiline_comment|/************************************************************************/
DECL|function|iSeries_LogFr_Date
r_void
id|iSeries_LogFr_Date
c_func
(paren
id|FlightRecorder
op_star
id|Fr
comma
r_char
op_star
id|LogText
)paren
(brace
r_struct
id|rtc_time
id|Rtc
suffix:semicolon
r_char
id|LogBuffer
(braket
l_int|256
)braket
suffix:semicolon
id|mf_getRtc
c_func
(paren
op_amp
id|Rtc
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|LogBuffer
comma
l_string|&quot;%02d.%02d.%02d %02d:%02d:%02d %s&quot;
comma
id|Rtc.tm_year
op_plus
l_int|1900
comma
id|Rtc.tm_mon
comma
id|Rtc.tm_mday
comma
id|Rtc.tm_hour
comma
id|Rtc.tm_min
comma
id|Rtc.tm_sec
comma
id|LogText
)paren
suffix:semicolon
id|iSeries_LogFr_Entry
c_func
(paren
id|Fr
comma
id|LogBuffer
)paren
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Initialized the Flight Recorder                                      */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Fr_Initialize
r_void
id|iSeries_Fr_Initialize
c_func
(paren
id|FlightRecorder
op_star
id|Fr
comma
r_char
op_star
id|Signature
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|Signature
)paren
OG
l_int|16
)paren
(brace
id|memcpy
c_func
(paren
id|Fr-&gt;Signature
comma
id|Signature
comma
l_int|16
)paren
suffix:semicolon
)brace
r_else
id|strcpy
c_func
(paren
id|Fr-&gt;Signature
comma
id|Signature
)paren
suffix:semicolon
id|Fr-&gt;StartingPointer
op_assign
op_amp
id|Fr-&gt;Buffer
(braket
l_int|0
)braket
suffix:semicolon
id|Fr-&gt;CurrentPointer
op_assign
id|Fr-&gt;StartingPointer
suffix:semicolon
id|Fr-&gt;logEntry
op_assign
id|iSeries_LogFr_Entry
suffix:semicolon
id|Fr-&gt;logDate
op_assign
id|iSeries_LogFr_Date
suffix:semicolon
id|Fr-&gt;logTime
op_assign
id|iSeries_LogFr_Time
suffix:semicolon
id|Fr
op_member_access_from_pointer
id|logEntry
c_func
(paren
id|Fr
comma
l_string|&quot;FR Initialized.&quot;
)paren
suffix:semicolon
multiline_comment|/* Note, can&squot;t use time yet!   */
)brace
eof
