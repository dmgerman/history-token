macro_line|#ifndef _ISERIES_FLIGHTRECORDER_H
DECL|macro|_ISERIES_FLIGHTRECORDER_H
mdefine_line|#define _ISERIES_FLIGHTRECORDER_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_FlightRecorder.h created by Allan Trautman Jan 22 2001. */
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
multiline_comment|/*   Added Time stamp methods. Apr 12, 2001                             */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
multiline_comment|/* This is a generic Flight Recorder, simply stuffs line entries into a */
multiline_comment|/* buffer for debug purposes.                                           */
multiline_comment|/*                                                                      */
multiline_comment|/* To use,                                                              */
multiline_comment|/* 1. Create one, make it global so it isn&squot;t on the stack.              */
multiline_comment|/*     FlightRecorder  PciFlightRecorder;                               */
multiline_comment|/*                                                                      */
multiline_comment|/* 2. Optionally create a pointer to it, just makes it easier to use.   */
multiline_comment|/*     FlightRecorder* PciFr = &amp;PciFlightRecorder;                      */
multiline_comment|/*                                                                      */
multiline_comment|/* 3. Initialize with you signature.                                    */
multiline_comment|/*          iSeries_Fr_Initialize(PciFr, &quot;Pci Flight Recorder&quot;);        */
multiline_comment|/*                                                                      */
multiline_comment|/* 4. Log entries.                                                      */
multiline_comment|/*          PciFr-&gt;logEntry(PciFr,&quot;In Main&quot;);                           */
multiline_comment|/*                                                                      */
multiline_comment|/* 5. Later, you can find the Flight Recorder by looking in the         */
multiline_comment|/*    System.map                                                        */
multiline_comment|/************************************************************************/
r_struct
id|iSeries_FlightRecorder
suffix:semicolon
multiline_comment|/* Forward declares             */
r_struct
id|rtc_time
suffix:semicolon
r_void
id|logEntry
c_func
(paren
r_struct
id|iSeries_FlightRecorder
op_star
comma
r_char
op_star
id|Text
)paren
suffix:semicolon
r_void
id|logTime
c_func
(paren
r_struct
id|iSeries_FlightRecorder
op_star
comma
r_char
op_star
id|Text
)paren
suffix:semicolon
r_void
id|logDate
c_func
(paren
r_struct
id|iSeries_FlightRecorder
op_star
comma
r_char
op_star
id|Text
)paren
suffix:semicolon
DECL|macro|FlightRecorderSize
mdefine_line|#define FlightRecorderSize 4096 
multiline_comment|/************************************************************************/
multiline_comment|/* Generic Flight Recorder Structure                                    */
multiline_comment|/************************************************************************/
DECL|struct|iSeries_FlightRecorder
r_struct
id|iSeries_FlightRecorder
(brace
multiline_comment|/* Structure Defination         */
DECL|member|Signature
r_char
id|Signature
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Eye Catcher                  */
DECL|member|StartingPointer
r_char
op_star
id|StartingPointer
suffix:semicolon
multiline_comment|/* Buffer Starting Address      */
DECL|member|CurrentPointer
r_char
op_star
id|CurrentPointer
suffix:semicolon
multiline_comment|/* Next Entry Address           */
DECL|member|WrapCount
r_int
id|WrapCount
suffix:semicolon
multiline_comment|/* Number of Buffer Wraps       */
DECL|member|logEntry
r_void
(paren
op_star
id|logEntry
)paren
(paren
r_struct
id|iSeries_FlightRecorder
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|logTime
r_void
(paren
op_star
id|logTime
)paren
(paren
r_struct
id|iSeries_FlightRecorder
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|logDate
r_void
(paren
op_star
id|logDate
)paren
(paren
r_struct
id|iSeries_FlightRecorder
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|Buffer
r_char
id|Buffer
(braket
id|FlightRecorderSize
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|FlightRecorder
r_typedef
r_struct
id|iSeries_FlightRecorder
id|FlightRecorder
suffix:semicolon
multiline_comment|/* Short Name   */
r_extern
r_void
id|iSeries_Fr_Initialize
c_func
(paren
id|FlightRecorder
op_star
comma
r_char
op_star
id|Signature
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* extern void iSeries_LogFr_Entry(  FlightRecorder*, char* Text);      */
multiline_comment|/* extern void iSeries_LogFr_Date(   FlightRecorder*, char* Text);      */
multiline_comment|/* extern void iSeries_LogFr_Time(   FlightRecorder*, char* Text);      */
multiline_comment|/************************************************************************/
multiline_comment|/* PCI Flight Recorder Helpers                                          */
multiline_comment|/************************************************************************/
r_extern
id|FlightRecorder
op_star
id|PciFr
suffix:semicolon
multiline_comment|/* Ptr to Pci Fr               */
r_extern
r_char
op_star
id|PciFrBuffer
suffix:semicolon
multiline_comment|/* Ptr to Fr Work Buffer       */
DECL|macro|ISERIES_PCI_FR
mdefine_line|#define ISERIES_PCI_FR(buffer)      PciFr-&gt;logEntry(PciFr,buffer);
DECL|macro|ISERIES_PCI_FR_TIME
mdefine_line|#define ISERIES_PCI_FR_TIME(buffer) PciFr-&gt;logTime(PciFr,buffer);
DECL|macro|ISERIES_PCI_FR_DATE
mdefine_line|#define ISERIES_PCI_FR_DATE(buffer) PciFr-&gt;logDate(PciFr,buffer);
macro_line|#endif /* _ISERIES_FLIGHTRECORDER_H */
eof
