multiline_comment|/************************************************************************/
multiline_comment|/* This module supports the iSeries I/O Address translation mapping     */
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
multiline_comment|/*   Created, December 14, 2000                                         */
multiline_comment|/*   Added Bar table for IoMm performance.                              */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/resource.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_FlightRecorder.h&gt;
macro_line|#include &quot;iSeries_IoMmTable.h&quot;
macro_line|#include &quot;iSeries_pci.h&quot;
r_void
id|iSeries_allocateDeviceBars
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDevPtr
)paren
suffix:semicolon
multiline_comment|/*******************************************************************/
multiline_comment|/* Table defines                                                   */
multiline_comment|/* Entry size is 4 MB * 1024 Entries = 4GB.                        */
multiline_comment|/*******************************************************************/
DECL|macro|iSeries_IoMmTable_Entry_Size
mdefine_line|#define iSeries_IoMmTable_Entry_Size   0x00400000  
DECL|macro|iSeries_IoMmTable_Size
mdefine_line|#define iSeries_IoMmTable_Size         1024
DECL|macro|iSeries_Base_Io_Memory
mdefine_line|#define iSeries_Base_Io_Memory         0xFFFFFFFF
multiline_comment|/*******************************************************************/
multiline_comment|/* Static and Global variables                                     */
multiline_comment|/*******************************************************************/
DECL|variable|iSeries_IoMmTable
r_struct
id|pci_dev
op_star
id|iSeries_IoMmTable
(braket
id|iSeries_IoMmTable_Size
)braket
suffix:semicolon
DECL|variable|iSeries_IoBarTable
id|u8
id|iSeries_IoBarTable
(braket
id|iSeries_IoMmTable_Size
)braket
suffix:semicolon
DECL|variable|iSeries_CurrentIndex
r_static
r_int
id|iSeries_CurrentIndex
suffix:semicolon
DECL|variable|iSeriesPciIoText
r_static
r_char
op_star
id|iSeriesPciIoText
op_assign
l_string|&quot;iSeries PCI I/O&quot;
suffix:semicolon
DECL|variable|iSeriesIoMmTableLock
r_static
id|spinlock_t
id|iSeriesIoMmTableLock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*******************************************************************/
multiline_comment|/* iSeries_IoMmTable_Initialize                                    */
multiline_comment|/*******************************************************************/
multiline_comment|/* - Initalizes the Address Translation Table and get it ready for */
multiline_comment|/*   use.  Must be called before any client calls any of the other */
multiline_comment|/*   methods.                                                      */
multiline_comment|/*******************************************************************/
DECL|function|iSeries_IoMmTable_Initialize
r_void
id|iSeries_IoMmTable_Initialize
c_func
(paren
r_void
)paren
(brace
r_int
id|Index
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|Index
op_assign
l_int|0
suffix:semicolon
id|Index
OL
id|iSeries_IoMmTable_Size
suffix:semicolon
op_increment
id|Index
)paren
(brace
id|iSeries_IoMmTable
(braket
id|Index
)braket
op_assign
l_int|NULL
suffix:semicolon
id|iSeries_IoBarTable
(braket
id|Index
)braket
op_assign
l_int|0xFF
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
id|iSeries_CurrentIndex
op_assign
id|iSeries_IoMmTable_Size
op_minus
l_int|1
suffix:semicolon
id|ISERIES_PCI_FR
c_func
(paren
l_string|&quot;IoMmTable Init.&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************/
multiline_comment|/* iSeries_allocateDeviceBars                                      */
multiline_comment|/*******************************************************************/
multiline_comment|/* - Allocates ALL pci_dev BAR&squot;s and updates the resources with the*/
multiline_comment|/*   BAR value.  BARS with zero length will have the resources     */
multiline_comment|/*   The HvCallPci_getBarParms is used to get the size of the BAR  */
multiline_comment|/*   space.  It calls iSeries_IoMmTable_AllocateEntry to allocate  */
multiline_comment|/*   each entry.                                                   */
multiline_comment|/* - Loops through The Bar resourses(0 - 5) including the the ROM  */
multiline_comment|/*   is resource(6).                                               */
multiline_comment|/*******************************************************************/
DECL|function|iSeries_allocateDeviceBars
r_void
id|iSeries_allocateDeviceBars
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDevPtr
)paren
(brace
r_struct
id|resource
op_star
id|BarResource
suffix:semicolon
r_int
id|BarNumber
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Current Bar Number      */
r_if
c_cond
(paren
id|PciTraceFlag
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: iSeries_allocateDeviceBars 0x%08X&bslash;n&quot;
comma
(paren
r_int
)paren
id|PciDevPtr
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|PciFrBuffer
comma
l_string|&quot;IoBars %08X&quot;
comma
(paren
r_int
)paren
id|PciDevPtr
)paren
suffix:semicolon
id|ISERIES_PCI_FR
c_func
(paren
id|PciFrBuffer
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|BarNumber
op_assign
l_int|0
suffix:semicolon
id|BarNumber
op_le
id|PCI_ROM_RESOURCE
suffix:semicolon
op_increment
id|BarNumber
)paren
(brace
id|BarResource
op_assign
op_amp
id|PciDevPtr-&gt;resource
(braket
id|BarNumber
)braket
suffix:semicolon
id|iSeries_IoMmTable_AllocateEntry
c_func
(paren
id|PciDevPtr
comma
id|BarNumber
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************/
multiline_comment|/* iSeries_IoMmTable_AllocateEntry                                 */
multiline_comment|/*******************************************************************/
multiline_comment|/* Adds pci_dev entry in address translation table                 */
multiline_comment|/*******************************************************************/
multiline_comment|/* - Allocates the number of entries required in table base on BAR */
multiline_comment|/*   size.                                                         */
multiline_comment|/* - This version, allocates top down, starting at 4GB.            */
multiline_comment|/* - The size is round up to be a multiple of entry size.          */
multiline_comment|/* - CurrentIndex is decremented to keep track of the last entry.  */
multiline_comment|/* - Builds the resource entry for allocated BARs.                 */
multiline_comment|/*******************************************************************/
DECL|function|iSeries_IoMmTable_AllocateEntry
r_void
id|iSeries_IoMmTable_AllocateEntry
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDevPtr
comma
id|u32
id|BarNumber
)paren
(brace
r_struct
id|resource
op_star
id|BarResource
op_assign
op_amp
id|PciDevPtr-&gt;resource
(braket
id|BarNumber
)braket
suffix:semicolon
r_int
id|BarSize
op_assign
id|BarResource-&gt;end
op_minus
id|BarResource-&gt;start
suffix:semicolon
id|u32
id|BarStartAddr
suffix:semicolon
id|u32
id|BarEndAddr
suffix:semicolon
multiline_comment|/***************************************************************/
multiline_comment|/* No space to allocate, skip Allocation.                      */
multiline_comment|/***************************************************************/
r_if
c_cond
(paren
id|BarSize
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Quick stage exit        */
multiline_comment|/***************************************************************/
multiline_comment|/* Allocate the table entries needed.                          */
multiline_comment|/***************************************************************/
id|spin_lock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|BarSize
OG
l_int|0
)paren
(brace
id|iSeries_IoMmTable
(braket
id|iSeries_CurrentIndex
)braket
op_assign
id|PciDevPtr
suffix:semicolon
id|iSeries_IoBarTable
(braket
id|iSeries_CurrentIndex
)braket
op_assign
id|BarNumber
suffix:semicolon
id|BarSize
op_sub_assign
id|iSeries_IoMmTable_Entry_Size
suffix:semicolon
op_decrement
id|iSeries_CurrentIndex
suffix:semicolon
multiline_comment|/* Next Free entry         */
)brace
id|spin_unlock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
id|BarStartAddr
op_assign
id|iSeries_IoMmTable_Entry_Size
op_star
(paren
id|iSeries_CurrentIndex
op_plus
l_int|1
)paren
suffix:semicolon
id|BarEndAddr
op_assign
id|BarStartAddr
op_plus
(paren
id|u32
)paren
(paren
id|BarResource-&gt;end
op_minus
id|BarResource-&gt;start
)paren
suffix:semicolon
multiline_comment|/***************************************************************/
multiline_comment|/* Build Resource info                                         */
multiline_comment|/***************************************************************/
id|BarResource-&gt;name
op_assign
id|iSeriesPciIoText
suffix:semicolon
id|BarResource-&gt;start
op_assign
(paren
r_int
)paren
id|BarStartAddr
suffix:semicolon
id|BarResource-&gt;end
op_assign
(paren
r_int
)paren
id|BarEndAddr
suffix:semicolon
multiline_comment|/***************************************************************/
multiline_comment|/* Tracing                                                     */
multiline_comment|/***************************************************************/
r_if
c_cond
(paren
id|PciTraceFlag
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: BarAloc %04X-%08X-%08X&bslash;n&quot;
comma
id|iSeries_CurrentIndex
op_plus
l_int|1
comma
(paren
r_int
)paren
id|BarStartAddr
comma
(paren
r_int
)paren
id|BarEndAddr
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|PciFrBuffer
comma
l_string|&quot;IoMmAloc %04X-%08X-%08X&quot;
comma
id|iSeries_CurrentIndex
op_plus
l_int|1
comma
(paren
r_int
)paren
id|BarStartAddr
comma
(paren
r_int
)paren
id|BarEndAddr
)paren
suffix:semicolon
id|ISERIES_PCI_FR
c_func
(paren
id|PciFrBuffer
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************/
multiline_comment|/* Translates an I/O Memory address to pci_dev*                    */
multiline_comment|/*******************************************************************/
DECL|function|iSeries_xlateIoMmAddress
r_struct
id|pci_dev
op_star
id|iSeries_xlateIoMmAddress
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
(brace
r_int
id|PciDevIndex
suffix:semicolon
r_struct
id|pci_dev
op_star
id|PciDevPtr
suffix:semicolon
id|PciDevIndex
op_assign
(paren
id|u32
)paren
id|IoAddress
op_div
id|iSeries_IoMmTable_Entry_Size
suffix:semicolon
id|PciDevPtr
op_assign
id|iSeries_IoMmTable
(braket
id|PciDevIndex
)braket
suffix:semicolon
r_if
c_cond
(paren
id|PciDevPtr
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Invalid I/O Address: 0x%08X&bslash;n&quot;
comma
(paren
r_int
)paren
id|IoAddress
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|PciFrBuffer
comma
l_string|&quot;Invalid MMIO Address 0x%08X&quot;
comma
(paren
r_int
)paren
id|IoAddress
)paren
suffix:semicolon
id|ISERIES_PCI_FR
c_func
(paren
id|PciFrBuffer
)paren
suffix:semicolon
)brace
r_return
id|PciDevPtr
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Returns the Bar number of Address                                    */
multiline_comment|/************************************************************************/
DECL|function|iSeries_IoMmTable_Bar
r_int
id|iSeries_IoMmTable_Bar
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
(brace
r_int
id|BarIndex
op_assign
(paren
id|u32
)paren
id|IoAddress
op_div
id|iSeries_IoMmTable_Entry_Size
suffix:semicolon
r_int
id|BarNumber
op_assign
id|iSeries_IoBarTable
(braket
id|BarIndex
)braket
suffix:semicolon
r_return
id|BarNumber
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Return the Bar Base Address or 0.                                    */
multiline_comment|/************************************************************************/
DECL|function|iSeries_IoMmTable_BarBase
id|u32
op_star
id|iSeries_IoMmTable_BarBase
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
(brace
id|u32
id|BaseAddr
op_assign
op_minus
l_int|1
suffix:semicolon
id|pciDev
op_star
id|PciDev
op_assign
id|iSeries_xlateIoMmAddress
c_func
(paren
id|IoAddress
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PciDev
op_ne
l_int|0
)paren
(brace
r_int
id|BarNumber
op_assign
id|iSeries_IoMmTable_Bar
c_func
(paren
id|IoAddress
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BarNumber
op_ne
op_minus
l_int|1
)paren
(brace
id|BaseAddr
op_assign
(paren
op_amp
id|PciDev-&gt;resource
(braket
id|BarNumber
)braket
)paren
op_member_access_from_pointer
id|start
suffix:semicolon
)brace
)brace
r_return
(paren
id|u32
op_star
)paren
id|BaseAddr
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Return the Bar offset within the Bar Space                           */
multiline_comment|/* Note: Assumes that address is valid.                                 */
multiline_comment|/************************************************************************/
DECL|function|iSeries_IoMmTable_BarOffset
id|u32
id|iSeries_IoMmTable_BarOffset
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
(brace
id|u32
id|BaseAddr
op_assign
(paren
id|u32
)paren
id|iSeries_IoMmTable_BarBase
c_func
(paren
id|IoAddress
)paren
suffix:semicolon
r_return
(paren
id|u32
)paren
id|IoAddress
op_minus
id|BaseAddr
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Return 0 if Address is valid I/O Address                             */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Is_IoMmAddress
r_int
id|iSeries_Is_IoMmAddress
c_func
(paren
r_int
r_int
id|IoAddress
)paren
(brace
r_if
c_cond
(paren
id|iSeries_IoMmTable_Bar
c_func
(paren
(paren
id|u32
op_star
)paren
id|IoAddress
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Helper Methods to get TableSize and TableSizeEntry.                  */
multiline_comment|/************************************************************************/
DECL|function|iSeries_IoMmTable_TableEntrySize
id|u32
id|iSeries_IoMmTable_TableEntrySize
c_func
(paren
r_void
)paren
(brace
r_return
id|iSeries_IoMmTable_Entry_Size
suffix:semicolon
)brace
DECL|function|iSeries_IoMmTable_TableSize
id|u32
id|iSeries_IoMmTable_TableSize
c_func
(paren
r_void
)paren
(brace
r_return
id|iSeries_IoMmTable_Size
suffix:semicolon
)brace
eof
