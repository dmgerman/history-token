macro_line|#ifndef _ISERIES_VPDINFO_H
DECL|macro|_ISERIES_VPDINFO_H
mdefine_line|#define _ISERIES_VPDINFO_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_VpdInfo.h created by Allan Trautman Feb 08 2001.        */
multiline_comment|/************************************************************************/
multiline_comment|/* This code supports the location data fon on the IBM iSeries systems. */
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
multiline_comment|/*   Created, Feg  8, 2001                                              */
multiline_comment|/*   Reformated for Card, March 8, 2001                                 */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* Forward Declare                      */
multiline_comment|/************************************************************************/
multiline_comment|/* Location Data extracted from the VPD list and device info.           */
multiline_comment|/************************************************************************/
DECL|struct|LocationDataStruct
r_struct
id|LocationDataStruct
(brace
multiline_comment|/* Location data structure for device   */
DECL|member|Bus
id|u16
id|Bus
suffix:semicolon
multiline_comment|/* iSeries Bus Number&t;&t;    0x00*/
DECL|member|Board
id|u16
id|Board
suffix:semicolon
multiline_comment|/* iSeries Board                    0x02*/
DECL|member|FrameId
id|u8
id|FrameId
suffix:semicolon
multiline_comment|/* iSeries spcn Frame Id            0x04*/
DECL|member|PhbId
id|u8
id|PhbId
suffix:semicolon
multiline_comment|/* iSeries Phb Location             0x05*/
DECL|member|Card
id|u16
id|Card
suffix:semicolon
multiline_comment|/* iSeries Card Slot                0x06*/
DECL|member|CardLocation
r_char
id|CardLocation
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Char format of planar vpd        0x08*/
DECL|member|AgentId
id|u8
id|AgentId
suffix:semicolon
multiline_comment|/* iSeries AgentId                  0x0C*/
DECL|member|SecondaryAgentId
id|u8
id|SecondaryAgentId
suffix:semicolon
multiline_comment|/* iSeries Secondary Agent Id       0x0D*/
DECL|member|LinuxBus
id|u8
id|LinuxBus
suffix:semicolon
multiline_comment|/* Linux Bus Number                 0x0E*/
DECL|member|LinuxDevFn
id|u8
id|LinuxDevFn
suffix:semicolon
multiline_comment|/* Linux Device Function            0x0F*/
)brace
suffix:semicolon
DECL|typedef|LocationData
r_typedef
r_struct
id|LocationDataStruct
id|LocationData
suffix:semicolon
DECL|macro|LOCATION_DATA_SIZE
mdefine_line|#define LOCATION_DATA_SIZE      16
multiline_comment|/************************************************************************/
multiline_comment|/* Protypes                                                             */
multiline_comment|/************************************************************************/
r_extern
id|LocationData
op_star
id|iSeries_GetLocationData
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Device_Information
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _ISERIES_VPDINFO_H */
eof
