multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_vpdInfo.c created by Allan Trautman on Fri Feb  2 2001. */
multiline_comment|/************************************************************************/
multiline_comment|/* This code gets the card location of the hardware                     */
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
multiline_comment|/*   Created, Feb 2, 2001                                               */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/resource.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_VpdInfo.h&gt;
macro_line|#include &quot;iSeries_pci.h&quot;
multiline_comment|/************************************************/
multiline_comment|/* Size of Bus VPD data                         */
multiline_comment|/************************************************/
DECL|macro|BUS_VPDSIZE
mdefine_line|#define BUS_VPDSIZE      1024
multiline_comment|/************************************************/
multiline_comment|/* Bus Vpd Tags                                 */
multiline_comment|/************************************************/
DECL|macro|VpdEndOfDataTag
mdefine_line|#define  VpdEndOfDataTag   0x78
DECL|macro|VpdEndOfAreaTag
mdefine_line|#define  VpdEndOfAreaTag   0x79
DECL|macro|VpdIdStringTag
mdefine_line|#define  VpdIdStringTag    0x82
DECL|macro|VpdVendorAreaTag
mdefine_line|#define  VpdVendorAreaTag  0x84
multiline_comment|/************************************************/
multiline_comment|/* Mfg Area Tags                                */
multiline_comment|/************************************************/
DECL|macro|VpdAsmPartNumber
mdefine_line|#define  VpdAsmPartNumber 0x504E     
singleline_comment|// &quot;PN&quot;
DECL|macro|VpdFruFlag
mdefine_line|#define  VpdFruFlag       0x4647     
singleline_comment|// &quot;FG&quot;
DECL|macro|VpdFruLocation
mdefine_line|#define  VpdFruLocation   0x464C     
singleline_comment|// &quot;FL&quot;
DECL|macro|VpdFruFrameId
mdefine_line|#define  VpdFruFrameId    0x4649     
singleline_comment|// &quot;FI&quot;
DECL|macro|VpdFruPartNumber
mdefine_line|#define  VpdFruPartNumber 0x464E     
singleline_comment|// &quot;FN&quot;
DECL|macro|VpdFruPowerData
mdefine_line|#define  VpdFruPowerData  0x5052     
singleline_comment|// &quot;PR&quot;
DECL|macro|VpdFruSerial
mdefine_line|#define  VpdFruSerial     0x534E     
singleline_comment|// &quot;SN&quot;
DECL|macro|VpdFruType
mdefine_line|#define  VpdFruType       0x4343     
singleline_comment|// &quot;CC&quot;
DECL|macro|VpdFruCcinExt
mdefine_line|#define  VpdFruCcinExt    0x4345     
singleline_comment|// &quot;CE&quot;
DECL|macro|VpdFruRevision
mdefine_line|#define  VpdFruRevision   0x5256     
singleline_comment|// &quot;RV&quot;
DECL|macro|VpdSlotMapFormat
mdefine_line|#define  VpdSlotMapFormat 0x4D46     
singleline_comment|// &quot;MF&quot;
DECL|macro|VpdSlotMap
mdefine_line|#define  VpdSlotMap       0x534D     
singleline_comment|// &quot;SM&quot;
multiline_comment|/************************************************/
multiline_comment|/* Structures of the areas                      */
multiline_comment|/************************************************/
DECL|struct|BusVpdAreaStruct
r_struct
id|BusVpdAreaStruct
(brace
DECL|member|Tag
id|u8
id|Tag
suffix:semicolon
DECL|member|LowLength
id|u8
id|LowLength
suffix:semicolon
DECL|member|HighLength
id|u8
id|HighLength
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|BusVpdArea
r_typedef
r_struct
id|BusVpdAreaStruct
id|BusVpdArea
suffix:semicolon
DECL|macro|BUS_ENTRY_SIZE
mdefine_line|#define BUS_ENTRY_SIZE   3
DECL|struct|MfgVpdAreaStruct
r_struct
id|MfgVpdAreaStruct
(brace
DECL|member|Tag
id|u16
id|Tag
suffix:semicolon
DECL|member|TagLength
id|u8
id|TagLength
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|MfgVpdArea
r_typedef
r_struct
id|MfgVpdAreaStruct
id|MfgVpdArea
suffix:semicolon
DECL|macro|MFG_ENTRY_SIZE
mdefine_line|#define MFG_ENTRY_SIZE   3
DECL|struct|SlotMapFormatStruct
r_struct
id|SlotMapFormatStruct
(brace
DECL|member|Tag
id|u16
id|Tag
suffix:semicolon
DECL|member|TagLength
id|u8
id|TagLength
suffix:semicolon
DECL|member|Format
id|u16
id|Format
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|FrameIdMapStruct
r_struct
id|FrameIdMapStruct
(brace
DECL|member|Tag
id|u16
id|Tag
suffix:semicolon
DECL|member|TagLength
id|u8
id|TagLength
suffix:semicolon
DECL|member|FrameId
id|u8
id|FrameId
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|FrameIdMap
r_typedef
r_struct
id|FrameIdMapStruct
id|FrameIdMap
suffix:semicolon
DECL|struct|SlotMapStruct
r_struct
id|SlotMapStruct
(brace
DECL|member|AgentId
id|u8
id|AgentId
suffix:semicolon
DECL|member|SecondaryAgentId
id|u8
id|SecondaryAgentId
suffix:semicolon
DECL|member|PhbId
id|u8
id|PhbId
suffix:semicolon
DECL|member|CardLocation
r_char
id|CardLocation
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Parms
r_char
id|Parms
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|Reserved
r_char
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|SlotMap
r_typedef
r_struct
id|SlotMapStruct
id|SlotMap
suffix:semicolon
DECL|macro|SLOT_ENTRY_SIZE
mdefine_line|#define SLOT_ENTRY_SIZE   16
multiline_comment|/****************************************************************/
multiline_comment|/* Prototypes                                                   */
multiline_comment|/****************************************************************/
r_static
r_void
id|iSeries_Parse_Vpd
c_func
(paren
id|BusVpdArea
op_star
comma
r_int
comma
id|LocationData
op_star
)paren
suffix:semicolon
r_static
r_void
id|iSeries_Parse_MfgArea
c_func
(paren
id|MfgVpdArea
op_star
comma
r_int
comma
id|LocationData
op_star
)paren
suffix:semicolon
r_static
r_void
id|iSeries_Parse_SlotArea
c_func
(paren
id|SlotMap
op_star
comma
r_int
comma
id|LocationData
op_star
)paren
suffix:semicolon
r_static
r_void
id|iSeries_Parse_PhbId
c_func
(paren
id|BusVpdArea
op_star
comma
r_int
comma
id|LocationData
op_star
)paren
suffix:semicolon
multiline_comment|/****************************************************************/
multiline_comment|/*                                                              */
multiline_comment|/*                                                              */
multiline_comment|/*                                                              */
multiline_comment|/****************************************************************/
DECL|function|iSeries_GetLocationData
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
(brace
id|LocationData
op_star
id|LocationPtr
op_assign
l_int|0
suffix:semicolon
id|BusVpdArea
op_star
id|BusVpdPtr
op_assign
l_int|0
suffix:semicolon
r_int
id|BusVpdLen
op_assign
l_int|0
suffix:semicolon
id|BusVpdPtr
op_assign
(paren
id|BusVpdArea
op_star
)paren
id|kmalloc
c_func
(paren
id|BUS_VPDSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|BusVpdLen
op_assign
id|HvCallPci_getBusVpd
c_func
(paren
id|ISERIES_GET_LPAR_BUS
c_func
(paren
id|PciDev-&gt;bus-&gt;number
)paren
comma
id|REALADDR
c_func
(paren
id|BusVpdPtr
)paren
comma
id|BUS_VPDSIZE
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;PCI: VpdBuffer 0x%08X &bslash;n&quot;,(int)BusVpdPtr);          */
multiline_comment|/***************************************************************/
multiline_comment|/* Need to set Agent Id, Bus in location info before the call  */
multiline_comment|/***************************************************************/
id|LocationPtr
op_assign
(paren
id|LocationData
op_star
)paren
id|kmalloc
c_func
(paren
id|LOCATION_DATA_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|LocationPtr-&gt;Bus
op_assign
id|ISERIES_GET_LPAR_BUS
c_func
(paren
id|PciDev-&gt;bus-&gt;number
)paren
suffix:semicolon
id|LocationPtr-&gt;Board
op_assign
l_int|0
suffix:semicolon
id|LocationPtr-&gt;FrameId
op_assign
l_int|0
suffix:semicolon
id|iSeries_Parse_PhbId
c_func
(paren
id|BusVpdPtr
comma
id|BusVpdLen
comma
id|LocationPtr
)paren
suffix:semicolon
id|LocationPtr-&gt;Card
op_assign
id|PCI_SLOT
c_func
(paren
id|PciDev-&gt;devfn
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|LocationPtr-&gt;CardLocation
comma
l_string|&quot;Cxx&quot;
)paren
suffix:semicolon
id|LocationPtr-&gt;AgentId
op_assign
id|ISERIES_DECODE_DEVICE
c_func
(paren
id|PciDev-&gt;devfn
)paren
suffix:semicolon
id|LocationPtr-&gt;SecondaryAgentId
op_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* And for Reference only.                        */
id|LocationPtr-&gt;LinuxBus
op_assign
id|PciDev-&gt;bus-&gt;number
suffix:semicolon
id|LocationPtr-&gt;LinuxDevFn
op_assign
id|PciDev-&gt;devfn
suffix:semicolon
multiline_comment|/***************************************************************/
multiline_comment|/* Any data to process?                                        */
multiline_comment|/***************************************************************/
r_if
c_cond
(paren
id|BusVpdLen
OG
l_int|0
)paren
(brace
id|iSeries_Parse_Vpd
c_func
(paren
id|BusVpdPtr
comma
id|BUS_VPDSIZE
comma
id|LocationPtr
)paren
suffix:semicolon
)brace
r_else
(brace
id|ISERIES_PCI_FR
c_func
(paren
l_string|&quot;No VPD Data....&quot;
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|BusVpdPtr
)paren
suffix:semicolon
r_return
id|LocationPtr
suffix:semicolon
)brace
multiline_comment|/****************************************************************/
multiline_comment|/*                                                              */
multiline_comment|/****************************************************************/
DECL|function|iSeries_Parse_Vpd
r_void
id|iSeries_Parse_Vpd
c_func
(paren
id|BusVpdArea
op_star
id|VpdData
comma
r_int
id|VpdLen
comma
id|LocationData
op_star
id|LocationPtr
)paren
(brace
id|MfgVpdArea
op_star
id|MfgVpdPtr
op_assign
l_int|0
suffix:semicolon
r_int
id|BusTagLen
op_assign
l_int|0
suffix:semicolon
id|BusVpdArea
op_star
id|BusVpdPtr
op_assign
id|VpdData
suffix:semicolon
r_int
id|BusVpdLen
op_assign
id|VpdLen
suffix:semicolon
multiline_comment|/*************************************************************/
multiline_comment|/* Make sure this is what I think it is                      */
multiline_comment|/*************************************************************/
r_if
c_cond
(paren
id|BusVpdPtr-&gt;Tag
op_ne
id|VpdIdStringTag
)paren
(brace
multiline_comment|/*0x82     */
id|ISERIES_PCI_FR
c_func
(paren
l_string|&quot;Not 0x82 start.&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|BusTagLen
op_assign
(paren
id|BusVpdPtr-&gt;HighLength
op_star
l_int|256
)paren
op_plus
id|BusVpdPtr-&gt;LowLength
suffix:semicolon
id|BusTagLen
op_add_assign
id|BUS_ENTRY_SIZE
suffix:semicolon
id|BusVpdPtr
op_assign
(paren
id|BusVpdArea
op_star
)paren
(paren
(paren
id|u32
)paren
id|BusVpdPtr
op_plus
id|BusTagLen
)paren
suffix:semicolon
id|BusVpdLen
op_sub_assign
id|BusTagLen
suffix:semicolon
multiline_comment|/*************************************************************/
multiline_comment|/* Parse the Data                                            */
multiline_comment|/*************************************************************/
r_while
c_loop
(paren
id|BusVpdLen
OG
l_int|0
)paren
(brace
id|BusTagLen
op_assign
(paren
id|BusVpdPtr-&gt;HighLength
op_star
l_int|256
)paren
op_plus
id|BusVpdPtr-&gt;LowLength
suffix:semicolon
multiline_comment|/*********************************************************/
multiline_comment|/* End of data Found                                     */
multiline_comment|/*********************************************************/
r_if
c_cond
(paren
id|BusVpdPtr-&gt;Tag
op_eq
id|VpdEndOfAreaTag
)paren
(brace
id|BusVpdLen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Done, Make sure       */
)brace
multiline_comment|/*********************************************************/
multiline_comment|/* Was Mfg Data Found                                    */
multiline_comment|/*********************************************************/
r_else
r_if
c_cond
(paren
id|BusVpdPtr-&gt;Tag
op_eq
id|VpdVendorAreaTag
)paren
(brace
id|MfgVpdPtr
op_assign
(paren
id|MfgVpdArea
op_star
)paren
(paren
(paren
id|u32
)paren
id|BusVpdPtr
op_plus
id|BUS_ENTRY_SIZE
)paren
suffix:semicolon
id|iSeries_Parse_MfgArea
c_func
(paren
id|MfgVpdPtr
comma
id|BusTagLen
comma
id|LocationPtr
)paren
suffix:semicolon
)brace
multiline_comment|/********************************************************/
multiline_comment|/* On to the next tag.                                  */
multiline_comment|/********************************************************/
r_if
c_cond
(paren
id|BusVpdLen
OG
l_int|0
)paren
(brace
id|BusTagLen
op_add_assign
id|BUS_ENTRY_SIZE
suffix:semicolon
id|BusVpdPtr
op_assign
(paren
id|BusVpdArea
op_star
)paren
(paren
(paren
id|u32
)paren
id|BusVpdPtr
op_plus
id|BusTagLen
)paren
suffix:semicolon
id|BusVpdLen
op_sub_assign
id|BusTagLen
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*****************************************************************/
multiline_comment|/* Parse the Mfg Area                                            */
multiline_comment|/*****************************************************************/
DECL|function|iSeries_Parse_MfgArea
r_void
id|iSeries_Parse_MfgArea
c_func
(paren
id|MfgVpdArea
op_star
id|VpdDataPtr
comma
r_int
id|VpdLen
comma
id|LocationData
op_star
id|LocationPtr
)paren
(brace
id|SlotMap
op_star
id|SlotMapPtr
op_assign
l_int|0
suffix:semicolon
id|u16
id|SlotMapFmt
op_assign
l_int|0
suffix:semicolon
r_int
id|MfgTagLen
op_assign
l_int|0
suffix:semicolon
id|MfgVpdArea
op_star
id|MfgVpdPtr
op_assign
id|VpdDataPtr
suffix:semicolon
r_int
id|MfgVpdLen
op_assign
id|VpdLen
suffix:semicolon
multiline_comment|/*************************************************************/
multiline_comment|/* Parse Mfg Data                                            */
multiline_comment|/*************************************************************/
r_while
c_loop
(paren
id|MfgVpdLen
OG
l_int|0
)paren
(brace
id|MfgTagLen
op_assign
id|MfgVpdPtr-&gt;TagLength
suffix:semicolon
r_if
c_cond
(paren
id|MfgVpdPtr-&gt;Tag
op_eq
id|VpdFruFlag
)paren
(brace
)brace
multiline_comment|/* FG  */
r_else
r_if
c_cond
(paren
id|MfgVpdPtr-&gt;Tag
op_eq
id|VpdFruSerial
)paren
(brace
)brace
multiline_comment|/* SN  */
r_else
r_if
c_cond
(paren
id|MfgVpdPtr-&gt;Tag
op_eq
id|VpdAsmPartNumber
)paren
(brace
)brace
multiline_comment|/* PN  */
multiline_comment|/*********************************************************/
multiline_comment|/* Frame ID                                              */
multiline_comment|/*********************************************************/
r_if
c_cond
(paren
id|MfgVpdPtr-&gt;Tag
op_eq
id|VpdFruFrameId
)paren
(brace
multiline_comment|/* FI    */
id|LocationPtr-&gt;FrameId
op_assign
(paren
(paren
id|FrameIdMap
op_star
)paren
id|MfgVpdPtr
)paren
op_member_access_from_pointer
id|FrameId
suffix:semicolon
)brace
multiline_comment|/*********************************************************/
multiline_comment|/* Slot Map Format                                       */
multiline_comment|/*********************************************************/
r_else
r_if
c_cond
(paren
id|MfgVpdPtr-&gt;Tag
op_eq
id|VpdSlotMapFormat
)paren
(brace
multiline_comment|/* MF */
id|SlotMapFmt
op_assign
(paren
(paren
r_struct
id|SlotMapFormatStruct
op_star
)paren
id|MfgVpdPtr
)paren
op_member_access_from_pointer
id|Format
suffix:semicolon
)brace
multiline_comment|/*********************************************************/
multiline_comment|/* Slot Labels                                           */
multiline_comment|/*********************************************************/
r_else
r_if
c_cond
(paren
id|MfgVpdPtr-&gt;Tag
op_eq
id|VpdSlotMap
)paren
(brace
multiline_comment|/* SM */
r_if
c_cond
(paren
id|SlotMapFmt
op_eq
l_int|0x1004
)paren
(brace
id|SlotMapPtr
op_assign
(paren
id|SlotMap
op_star
)paren
(paren
(paren
id|u32
)paren
id|MfgVpdPtr
op_plus
id|MFG_ENTRY_SIZE
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|SlotMapPtr
op_assign
(paren
id|SlotMap
op_star
)paren
(paren
(paren
id|u32
)paren
id|MfgVpdPtr
op_plus
id|MFG_ENTRY_SIZE
)paren
suffix:semicolon
id|iSeries_Parse_SlotArea
c_func
(paren
id|SlotMapPtr
comma
id|MfgTagLen
comma
id|LocationPtr
)paren
suffix:semicolon
)brace
multiline_comment|/*********************************************************/
multiline_comment|/* Point to the next Mfg Area                            */
multiline_comment|/* Use defined size, sizeof give wrong answer            */
multiline_comment|/*********************************************************/
id|MfgTagLen
op_add_assign
id|MFG_ENTRY_SIZE
suffix:semicolon
id|MfgVpdPtr
op_assign
(paren
id|MfgVpdArea
op_star
)paren
(paren
(paren
id|u32
)paren
id|MfgVpdPtr
op_plus
id|MfgTagLen
)paren
suffix:semicolon
id|MfgVpdLen
op_sub_assign
id|MfgTagLen
suffix:semicolon
)brace
)brace
multiline_comment|/*****************************************************************/
multiline_comment|/* Look for &quot;BUS&quot; Tag to set the PhbId.                          */
multiline_comment|/*****************************************************************/
DECL|function|iSeries_Parse_PhbId
r_void
id|iSeries_Parse_PhbId
c_func
(paren
id|BusVpdArea
op_star
id|VpdData
comma
r_int
id|VpdLen
comma
id|LocationData
op_star
id|LocationPtr
)paren
(brace
r_int
id|PhbId
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Not found flag   */
r_char
op_star
id|PhbPtr
op_assign
(paren
r_char
op_star
)paren
id|VpdData
op_plus
l_int|3
suffix:semicolon
multiline_comment|/* Skip over 82 tag */
r_int
id|DataLen
op_assign
id|VpdLen
suffix:semicolon
r_while
c_loop
(paren
id|DataLen
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|PhbPtr
op_eq
l_char|&squot;B&squot;
op_logical_and
op_star
(paren
id|PhbPtr
op_plus
l_int|1
)paren
op_eq
l_char|&squot;U&squot;
op_logical_and
op_star
(paren
id|PhbPtr
op_plus
l_int|2
)paren
op_eq
l_char|&squot;S&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
(paren
id|PhbPtr
op_plus
l_int|3
)paren
op_eq
l_char|&squot; &squot;
)paren
(brace
id|PhbPtr
op_add_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/* Skip white spac*/
r_else
id|PhbPtr
op_add_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_star
id|PhbPtr
op_eq
l_char|&squot;0&squot;
)paren
id|PhbId
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t convert, */
r_else
r_if
c_cond
(paren
op_star
id|PhbPtr
op_eq
l_char|&squot;1&squot;
)paren
(brace
id|PhbId
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Sanity check   */
r_else
r_if
c_cond
(paren
op_star
id|PhbPtr
op_eq
l_char|&squot;2&squot;
)paren
(brace
id|PhbId
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*  values        */
id|DataLen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Exit loop.     */
)brace
op_increment
id|PhbPtr
suffix:semicolon
op_decrement
id|DataLen
suffix:semicolon
)brace
id|LocationPtr-&gt;PhbId
op_assign
id|PhbId
suffix:semicolon
)brace
multiline_comment|/*****************************************************************/
multiline_comment|/* Parse the Slot Area                                           */
multiline_comment|/*****************************************************************/
DECL|function|iSeries_Parse_SlotArea
r_void
id|iSeries_Parse_SlotArea
c_func
(paren
id|SlotMap
op_star
id|MapPtr
comma
r_int
id|MapLen
comma
id|LocationData
op_star
id|LocationPtr
)paren
(brace
r_int
id|SlotMapLen
op_assign
id|MapLen
suffix:semicolon
id|SlotMap
op_star
id|SlotMapPtr
op_assign
id|MapPtr
suffix:semicolon
multiline_comment|/*************************************************************/
multiline_comment|/* Parse Slot label until we find the one requrested         */
multiline_comment|/*************************************************************/
r_while
c_loop
(paren
id|SlotMapLen
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|SlotMapPtr-&gt;AgentId
op_eq
id|LocationPtr-&gt;AgentId
op_logical_and
id|SlotMapPtr-&gt;SecondaryAgentId
op_eq
id|LocationPtr-&gt;SecondaryAgentId
)paren
(brace
multiline_comment|/*****************************************************/
multiline_comment|/* If Phb wasn&squot;t found, grab the first one found.    */
multiline_comment|/*****************************************************/
r_if
c_cond
(paren
id|LocationPtr-&gt;PhbId
op_eq
l_int|0xff
)paren
(brace
id|LocationPtr-&gt;PhbId
op_assign
id|SlotMapPtr-&gt;PhbId
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SlotMapPtr-&gt;PhbId
op_eq
id|LocationPtr-&gt;PhbId
)paren
(brace
multiline_comment|/*****************************************************/
multiline_comment|/* Found what we were looking for, extract the data. */
multiline_comment|/*****************************************************/
id|memcpy
c_func
(paren
op_amp
id|LocationPtr-&gt;CardLocation
comma
op_amp
id|SlotMapPtr-&gt;CardLocation
comma
l_int|3
)paren
suffix:semicolon
id|LocationPtr-&gt;CardLocation
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Null terminate*/
id|SlotMapLen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We are done   */
)brace
)brace
multiline_comment|/*********************************************************/
multiline_comment|/* Point to the next Slot                                */
multiline_comment|/* Use defined size, sizeof may give wrong answer        */
multiline_comment|/*********************************************************/
id|SlotMapLen
op_sub_assign
id|SLOT_ENTRY_SIZE
suffix:semicolon
id|SlotMapPtr
op_assign
(paren
id|SlotMap
op_star
)paren
(paren
(paren
id|u32
)paren
id|SlotMapPtr
op_plus
id|SLOT_ENTRY_SIZE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Formats the device information.                                      */
multiline_comment|/* - Pass in pci_dev* pointer to the device.                            */
multiline_comment|/* - Pass in buffer to place the data.  Danger here is the buffer must  */
multiline_comment|/*   be as big as the client says it is.   Should be at least 128 bytes.*/
multiline_comment|/* Return will the length of the string data put in the buffer.         */
multiline_comment|/* Format:                                                              */
multiline_comment|/* PCI: Bus  0, Device 26, Vendor 0x12AE  iSeries: Bus  2, Device 34, Fr*/
multiline_comment|/* ame  1, Card  C10  Ethernet controller                               */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Device_Information
r_int
id|iSeries_Device_Information
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_char
op_star
id|Buffer
comma
r_int
id|BufferSize
)paren
(brace
id|LocationData
op_star
id|LocationPtr
suffix:semicolon
multiline_comment|/* VPD Information             */
r_char
op_star
id|BufPtr
op_assign
id|Buffer
suffix:semicolon
r_int
id|LineLen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|BufferSize
op_ge
l_int|128
)paren
(brace
id|LineLen
op_assign
id|sprintf
c_func
(paren
id|BufPtr
op_plus
id|LineLen
comma
l_string|&quot;PCI: Bus%3d, Device%3d, Vendor %04X  &quot;
comma
id|PciDev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|PciDev-&gt;devfn
)paren
comma
id|PciDev-&gt;vendor
)paren
suffix:semicolon
id|LocationPtr
op_assign
id|iSeries_GetLocationData
c_func
(paren
id|PciDev
)paren
suffix:semicolon
id|LineLen
op_add_assign
id|sprintf
c_func
(paren
id|BufPtr
op_plus
id|LineLen
comma
l_string|&quot;iSeries: Bus%3d, Device%3d, Frame%3d, Card %4s  &quot;
comma
id|LocationPtr-&gt;Bus
comma
id|LocationPtr-&gt;AgentId
comma
id|LocationPtr-&gt;FrameId
comma
id|LocationPtr-&gt;CardLocation
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|LocationPtr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_class_name
c_func
(paren
id|PciDev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|LineLen
op_add_assign
id|sprintf
c_func
(paren
id|BufPtr
op_plus
id|LineLen
comma
l_string|&quot;0x%04X  &quot;
comma
(paren
r_int
)paren
(paren
id|PciDev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|LineLen
op_add_assign
id|sprintf
c_func
(paren
id|BufPtr
op_plus
id|LineLen
comma
l_string|&quot;%s&quot;
comma
id|pci_class_name
c_func
(paren
id|PciDev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|LineLen
suffix:semicolon
)brace
eof