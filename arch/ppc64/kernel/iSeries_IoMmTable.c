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
multiline_comment|/*   Ported to ppc64                                                    */
multiline_comment|/*   Added dynamic table allocation                                     */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/resource.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/flight_recorder.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#include &quot;iSeries_IoMmTable.h&quot;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*******************************************************************/
multiline_comment|/* Table defines                                                   */
multiline_comment|/* Each Entry size is 4 MB * 1024 Entries = 4GB I/O address space. */
multiline_comment|/*******************************************************************/
DECL|macro|Max_Entries
mdefine_line|#define Max_Entries 1024
DECL|variable|iSeries_IoMmTable_Entry_Size
r_int
r_int
id|iSeries_IoMmTable_Entry_Size
op_assign
l_int|0x0000000000400000
suffix:semicolon
DECL|variable|iSeries_Base_Io_Memory
r_int
r_int
id|iSeries_Base_Io_Memory
op_assign
l_int|0xE000000000000000
suffix:semicolon
DECL|variable|iSeries_Max_Io_Memory
r_int
r_int
id|iSeries_Max_Io_Memory
op_assign
l_int|0xE000000000000000
suffix:semicolon
DECL|variable|iSeries_CurrentIndex
r_static
r_int
id|iSeries_CurrentIndex
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*******************************************************************/
multiline_comment|/* Lookup Tables.                                                  */
multiline_comment|/*******************************************************************/
DECL|variable|iSeries_IoMmTable
r_struct
id|iSeries_Device_Node
op_star
op_star
id|iSeries_IoMmTable
suffix:semicolon
DECL|variable|iSeries_IoBarTable
id|u8
op_star
id|iSeries_IoBarTable
suffix:semicolon
multiline_comment|/*******************************************************************/
multiline_comment|/* Static and Global variables                                     */
multiline_comment|/*******************************************************************/
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
multiline_comment|/* Allocates and initalizes the Address Translation Table and Bar  */
multiline_comment|/* Tables to get them ready for use.  Must be called before any    */
multiline_comment|/* I/O space is handed out to the device BARs.                     */
multiline_comment|/* A follow up method,iSeries_IoMmTable_Status can be called to    */
multiline_comment|/* adjust the table after the device BARs have been assiged to     */
multiline_comment|/* resize the table.                                               */
multiline_comment|/*******************************************************************/
DECL|function|iSeries_IoMmTable_Initialize
r_void
id|iSeries_IoMmTable_Initialize
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
id|iSeries_IoMmTable
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_void
op_star
)paren
op_star
id|Max_Entries
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|iSeries_IoBarTable
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|u8
)paren
op_star
id|Max_Entries
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
id|PCIFR
c_func
(paren
l_string|&quot;IoMmTable Initialized 0x%p&quot;
comma
id|iSeries_IoMmTable
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iSeries_IoMmTable
op_eq
l_int|NULL
op_logical_or
id|iSeries_IoBarTable
op_eq
l_int|NULL
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;PCI: I/O tables allocation failed.&bslash;n&quot;
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
multiline_comment|/* - Allocates starting at iSeries_Base_Io_Memory and increases.   */
multiline_comment|/* - The size is round up to be a multiple of entry size.          */
multiline_comment|/* - CurrentIndex is incremented to keep track of the last entry.  */
multiline_comment|/* - Builds the resource entry for allocated BARs.                 */
multiline_comment|/*******************************************************************/
DECL|function|iSeries_IoMmTable_AllocateEntry
r_static
r_void
id|iSeries_IoMmTable_AllocateEntry
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_int
id|BarNumber
)paren
(brace
r_struct
id|resource
op_star
id|BarResource
op_assign
op_amp
id|PciDev-&gt;resource
(braket
id|BarNumber
)braket
suffix:semicolon
r_int
id|BarSize
op_assign
id|pci_resource_len
c_func
(paren
id|PciDev
comma
id|BarNumber
)paren
suffix:semicolon
multiline_comment|/***********************************************************/
multiline_comment|/* No space to allocate, quick exit, skip Allocation.      */
multiline_comment|/***********************************************************/
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
multiline_comment|/***********************************************************/
multiline_comment|/* Set Resource values.                                    */
multiline_comment|/***********************************************************/
id|spin_lock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
)paren
suffix:semicolon
id|BarResource-&gt;name
op_assign
id|iSeriesPciIoText
suffix:semicolon
id|BarResource-&gt;start
op_assign
id|iSeries_IoMmTable_Entry_Size
op_star
id|iSeries_CurrentIndex
suffix:semicolon
id|BarResource-&gt;start
op_add_assign
id|iSeries_Base_Io_Memory
suffix:semicolon
id|BarResource-&gt;end
op_assign
id|BarResource-&gt;start
op_plus
id|BarSize
op_minus
l_int|1
suffix:semicolon
multiline_comment|/***********************************************************/
multiline_comment|/* Allocate the number of table entries needed for BAR.    */
multiline_comment|/***********************************************************/
r_while
c_loop
(paren
id|BarSize
OG
l_int|0
)paren
(brace
op_star
(paren
id|iSeries_IoMmTable
op_plus
id|iSeries_CurrentIndex
)paren
op_assign
(paren
r_struct
id|iSeries_Device_Node
op_star
)paren
id|PciDev-&gt;sysdata
suffix:semicolon
op_star
(paren
id|iSeries_IoBarTable
op_plus
id|iSeries_CurrentIndex
)paren
op_assign
id|BarNumber
suffix:semicolon
id|BarSize
op_sub_assign
id|iSeries_IoMmTable_Entry_Size
suffix:semicolon
op_increment
id|iSeries_CurrentIndex
suffix:semicolon
)brace
id|iSeries_Max_Io_Memory
op_assign
(paren
id|iSeries_IoMmTable_Entry_Size
op_star
id|iSeries_CurrentIndex
)paren
op_plus
id|iSeries_Base_Io_Memory
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|iSeriesIoMmTableLock
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
id|PciDev
)paren
(brace
r_struct
id|resource
op_star
id|BarResource
suffix:semicolon
r_int
id|BarNumber
suffix:semicolon
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
id|PciDev-&gt;resource
(braket
id|BarNumber
)braket
suffix:semicolon
id|iSeries_IoMmTable_AllocateEntry
c_func
(paren
id|PciDev
comma
id|BarNumber
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Translates the IoAddress to the device that is mapped to IoSpace.    */
multiline_comment|/* This code is inlined, see the iSeries_pci.c file for the replacement.*/
multiline_comment|/************************************************************************/
DECL|function|iSeries_xlateIoMmAddress
r_struct
id|iSeries_Device_Node
op_star
id|iSeries_xlateIoMmAddress
c_func
(paren
r_void
op_star
id|IoAddress
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/************************************************************************&n; * Status hook for IoMmTable&n; ************************************************************************/
DECL|function|iSeries_IoMmTable_Status
r_void
id|iSeries_IoMmTable_Status
c_func
(paren
r_void
)paren
(brace
id|PCIFR
c_func
(paren
l_string|&quot;IoMmTable......: 0x%p&quot;
comma
id|iSeries_IoMmTable
)paren
suffix:semicolon
id|PCIFR
c_func
(paren
l_string|&quot;IoMmTable Range: 0x%p to 0x%p&quot;
comma
id|iSeries_Base_Io_Memory
comma
id|iSeries_Max_Io_Memory
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
