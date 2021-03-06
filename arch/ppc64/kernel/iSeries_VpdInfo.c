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
multiline_comment|/*   Ported to ppc64, August 20, 2001                                   */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/resource.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; * Size of Bus VPD data&n; */
DECL|macro|BUS_VPDSIZE
mdefine_line|#define BUS_VPDSIZE      1024
multiline_comment|/*&n; * Bus Vpd Tags&n; */
DECL|macro|VpdEndOfDataTag
mdefine_line|#define  VpdEndOfDataTag   0x78
DECL|macro|VpdEndOfAreaTag
mdefine_line|#define  VpdEndOfAreaTag   0x79
DECL|macro|VpdIdStringTag
mdefine_line|#define  VpdIdStringTag    0x82
DECL|macro|VpdVendorAreaTag
mdefine_line|#define  VpdVendorAreaTag  0x84
multiline_comment|/*&n; * Mfg Area Tags&n; */
DECL|macro|VpdFruFlag
mdefine_line|#define  VpdFruFlag       0x4647     
singleline_comment|// &quot;FG&quot;
DECL|macro|VpdFruFrameId
mdefine_line|#define  VpdFruFrameId    0x4649     
singleline_comment|// &quot;FI&quot;
DECL|macro|VpdSlotMapFormat
mdefine_line|#define  VpdSlotMapFormat 0x4D46     
singleline_comment|// &quot;MF&quot;
DECL|macro|VpdAsmPartNumber
mdefine_line|#define  VpdAsmPartNumber 0x504E     
singleline_comment|// &quot;PN&quot;
DECL|macro|VpdFruSerial
mdefine_line|#define  VpdFruSerial     0x534E     
singleline_comment|// &quot;SN&quot;
DECL|macro|VpdSlotMap
mdefine_line|#define  VpdSlotMap       0x534D     
singleline_comment|// &quot;SM&quot;
multiline_comment|/*&n; * Structures of the areas&n; */
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
DECL|member|AreaData1
id|u8
id|AreaData1
suffix:semicolon
DECL|member|AreaData2
id|u8
id|AreaData2
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|MfgArea
r_typedef
r_struct
id|MfgVpdAreaStruct
id|MfgArea
suffix:semicolon
DECL|macro|MFG_ENTRY_SIZE
mdefine_line|#define MFG_ENTRY_SIZE   3
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
multiline_comment|/*&n; * Formats the device information.&n; * - Pass in pci_dev* pointer to the device.&n; * - Pass in buffer to place the data.  Danger here is the buffer must&n; *   be as big as the client says it is.   Should be at least 128 bytes.&n; * Return will the length of the string data put in the buffer.&n; * Format:&n; * PCI: Bus  0, Device 26, Vendor 0x12AE  Frame  1, Card  C10  Ethernet&n; * controller&n; */
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
id|buffer
comma
r_int
id|BufferSize
)paren
(brace
r_struct
id|iSeries_Device_Node
op_star
id|DevNode
op_assign
(paren
r_struct
id|iSeries_Device_Node
op_star
)paren
id|PciDev-&gt;sysdata
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|DevNode
op_eq
l_int|NULL
)paren
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCI: iSeries_Device_Information DevNode is NULL&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BufferSize
OL
l_int|128
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCI: Bus%3d, Device%3d, Vendor %04X &quot;
comma
id|ISERIES_BUS
c_func
(paren
id|DevNode
)paren
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Frame%3d, Card %4s  &quot;
comma
id|DevNode-&gt;FrameId
comma
id|DevNode-&gt;CardLocation
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
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
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
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
macro_line|#endif
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse the Slot Area&n; */
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
r_struct
id|iSeries_Device_Node
op_star
id|DevNode
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
multiline_comment|/*&n;&t; * Parse Slot label until we find the one requrested&n;&t; */
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
id|DevNode-&gt;AgentId
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If Phb wasn&squot;t found, grab the entry first one found.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|DevNode-&gt;PhbId
op_eq
l_int|0xff
)paren
id|DevNode-&gt;PhbId
op_assign
id|SlotMapPtr-&gt;PhbId
suffix:semicolon
multiline_comment|/* Found it, extract the data. */
r_if
c_cond
(paren
id|SlotMapPtr-&gt;PhbId
op_eq
id|DevNode-&gt;PhbId
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|DevNode-&gt;CardLocation
comma
op_amp
id|SlotMapPtr-&gt;CardLocation
comma
l_int|3
)paren
suffix:semicolon
id|DevNode-&gt;CardLocation
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Point to the next Slot */
id|SlotMapPtr
op_assign
(paren
id|SlotMap
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|SlotMapPtr
op_plus
id|SLOT_ENTRY_SIZE
)paren
suffix:semicolon
id|SlotMapLen
op_sub_assign
id|SLOT_ENTRY_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Parse the Mfg Area&n; */
DECL|function|iSeries_Parse_MfgArea
r_static
r_void
id|iSeries_Parse_MfgArea
c_func
(paren
id|u8
op_star
id|AreaData
comma
r_int
id|AreaLen
comma
r_struct
id|iSeries_Device_Node
op_star
id|DevNode
)paren
(brace
id|MfgArea
op_star
id|MfgAreaPtr
op_assign
(paren
id|MfgArea
op_star
)paren
id|AreaData
suffix:semicolon
r_int
id|MfgAreaLen
op_assign
id|AreaLen
suffix:semicolon
id|u16
id|SlotMapFmt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Parse Mfg Data */
r_while
c_loop
(paren
id|MfgAreaLen
OG
l_int|0
)paren
(brace
r_int
id|MfgTagLen
op_assign
id|MfgAreaPtr-&gt;TagLength
suffix:semicolon
multiline_comment|/* Frame ID         (FI 4649020310 ) */
r_if
c_cond
(paren
id|MfgAreaPtr-&gt;Tag
op_eq
id|VpdFruFrameId
)paren
multiline_comment|/* FI  */
id|DevNode-&gt;FrameId
op_assign
id|MfgAreaPtr-&gt;AreaData1
suffix:semicolon
multiline_comment|/* Slot Map Format  (MF 4D46020004 ) */
r_else
r_if
c_cond
(paren
id|MfgAreaPtr-&gt;Tag
op_eq
id|VpdSlotMapFormat
)paren
multiline_comment|/* MF  */
id|SlotMapFmt
op_assign
(paren
id|MfgAreaPtr-&gt;AreaData1
op_star
l_int|256
)paren
op_plus
id|MfgAreaPtr-&gt;AreaData2
suffix:semicolon
multiline_comment|/* Slot Map         (SM 534D90 */
r_else
r_if
c_cond
(paren
id|MfgAreaPtr-&gt;Tag
op_eq
id|VpdSlotMap
)paren
(brace
multiline_comment|/* SM  */
id|SlotMap
op_star
id|SlotMapPtr
suffix:semicolon
r_if
c_cond
(paren
id|SlotMapFmt
op_eq
l_int|0x1004
)paren
id|SlotMapPtr
op_assign
(paren
id|SlotMap
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|MfgAreaPtr
op_plus
id|MFG_ENTRY_SIZE
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|SlotMapPtr
op_assign
(paren
id|SlotMap
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|MfgAreaPtr
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
id|DevNode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Point to the next Mfg Area&n;&t;&t; * Use defined size, sizeof give wrong answer&n;&t;&t; */
id|MfgAreaPtr
op_assign
(paren
id|MfgArea
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|MfgAreaPtr
op_plus
id|MfgTagLen
op_plus
id|MFG_ENTRY_SIZE
)paren
suffix:semicolon
id|MfgAreaLen
op_sub_assign
(paren
id|MfgTagLen
op_plus
id|MFG_ENTRY_SIZE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Look for &quot;BUS&quot;.. Data is not Null terminated.&n; * PHBID of 0xFF indicates PHB was not found in VPD Data.&n; */
DECL|function|iSeries_Parse_PhbId
r_static
r_int
id|iSeries_Parse_PhbId
c_func
(paren
id|u8
op_star
id|AreaPtr
comma
r_int
id|AreaLength
)paren
(brace
id|u8
op_star
id|PhbPtr
op_assign
id|AreaPtr
suffix:semicolon
r_int
id|DataLen
op_assign
id|AreaLength
suffix:semicolon
r_char
id|PhbId
op_assign
l_int|0xFF
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
(paren
op_star
id|PhbPtr
op_eq
l_char|&squot;B&squot;
)paren
op_logical_and
(paren
op_star
(paren
id|PhbPtr
op_plus
l_int|1
)paren
op_eq
l_char|&squot;U&squot;
)paren
op_logical_and
(paren
op_star
(paren
id|PhbPtr
op_plus
l_int|2
)paren
op_eq
l_char|&squot;S&squot;
)paren
)paren
(brace
id|PhbPtr
op_add_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
op_star
id|PhbPtr
op_eq
l_char|&squot; &squot;
)paren
op_increment
id|PhbPtr
suffix:semicolon
id|PhbId
op_assign
(paren
op_star
id|PhbPtr
op_amp
l_int|0x0F
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_increment
id|PhbPtr
suffix:semicolon
op_decrement
id|DataLen
suffix:semicolon
)brace
r_return
id|PhbId
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse out the VPD Areas&n; */
DECL|function|iSeries_Parse_Vpd
r_static
r_void
id|iSeries_Parse_Vpd
c_func
(paren
id|u8
op_star
id|VpdData
comma
r_int
id|VpdDataLen
comma
r_struct
id|iSeries_Device_Node
op_star
id|DevNode
)paren
(brace
id|u8
op_star
id|TagPtr
op_assign
id|VpdData
suffix:semicolon
r_int
id|DataLen
op_assign
id|VpdDataLen
op_minus
l_int|3
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|TagPtr
op_ne
id|VpdEndOfAreaTag
)paren
op_logical_and
(paren
id|DataLen
OG
l_int|0
)paren
)paren
(brace
r_int
id|AreaLen
op_assign
op_star
(paren
id|TagPtr
op_plus
l_int|1
)paren
op_plus
(paren
op_star
(paren
id|TagPtr
op_plus
l_int|2
)paren
op_star
l_int|256
)paren
suffix:semicolon
id|u8
op_star
id|AreaData
op_assign
id|TagPtr
op_plus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_star
id|TagPtr
op_eq
id|VpdIdStringTag
)paren
id|DevNode-&gt;PhbId
op_assign
id|iSeries_Parse_PhbId
c_func
(paren
id|AreaData
comma
id|AreaLen
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|TagPtr
op_eq
id|VpdVendorAreaTag
)paren
id|iSeries_Parse_MfgArea
c_func
(paren
id|AreaData
comma
id|AreaLen
comma
id|DevNode
)paren
suffix:semicolon
multiline_comment|/* Point to next Area. */
id|TagPtr
op_assign
id|AreaData
op_plus
id|AreaLen
suffix:semicolon
id|DataLen
op_sub_assign
id|AreaLen
suffix:semicolon
)brace
)brace
DECL|function|iSeries_Get_Location_Code
r_void
id|iSeries_Get_Location_Code
c_func
(paren
r_struct
id|iSeries_Device_Node
op_star
id|DevNode
)paren
(brace
r_int
id|BusVpdLen
op_assign
l_int|0
suffix:semicolon
id|u8
op_star
id|BusVpdPtr
op_assign
(paren
id|u8
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
r_if
c_cond
(paren
id|BusVpdPtr
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Bus VPD Buffer allocation failure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|BusVpdLen
op_assign
id|HvCallPci_getBusVpd
c_func
(paren
id|ISERIES_BUS
c_func
(paren
id|DevNode
)paren
comma
id|ISERIES_HV_ADDR
c_func
(paren
id|BusVpdPtr
)paren
comma
id|BUS_VPDSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BusVpdLen
op_eq
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|BusVpdPtr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Bus VPD Buffer zero length.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* printk(&quot;PCI: BusVpdPtr: %p, %d&bslash;n&quot;,BusVpdPtr, BusVpdLen); */
multiline_comment|/* Make sure this is what I think it is */
r_if
c_cond
(paren
op_star
id|BusVpdPtr
op_ne
id|VpdIdStringTag
)paren
(brace
multiline_comment|/* 0x82 */
id|printk
c_func
(paren
l_string|&quot;PCI: Bus VPD Buffer missing starting tag.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|BusVpdPtr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iSeries_Parse_Vpd
c_func
(paren
id|BusVpdPtr
comma
id|BusVpdLen
comma
id|DevNode
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|DevNode-&gt;Location
comma
l_string|&quot;Frame%3d, Card %-4s&quot;
comma
id|DevNode-&gt;FrameId
comma
id|DevNode-&gt;CardLocation
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|BusVpdPtr
)paren
suffix:semicolon
)brace
eof
