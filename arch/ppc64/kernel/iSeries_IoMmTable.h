macro_line|#ifndef _ISERIES_IOMMTABLE_H
DECL|macro|_ISERIES_IOMMTABLE_H
mdefine_line|#define _ISERIES_IOMMTABLE_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_IoMmTable.h created by Allan Trautman on Dec 12 2001.   */
multiline_comment|/************************************************************************/
multiline_comment|/* Interfaces for the write/read Io address translation table.          */
multiline_comment|/* Copyright (C) 20yy  Allan H Trautman, IBM Corporation                */
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
multiline_comment|/*   Created December 12, 2000                                          */
multiline_comment|/*   Ported to ppc64, August 30, 2001                                   */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|iSeries_Device_Node
suffix:semicolon
r_extern
r_struct
id|iSeries_Device_Node
op_star
op_star
id|iSeries_IoMmTable
suffix:semicolon
r_extern
id|u8
op_star
id|iSeries_IoBarTable
suffix:semicolon
r_extern
r_int
r_int
id|iSeries_Base_Io_Memory
suffix:semicolon
r_extern
r_int
r_int
id|iSeries_Max_Io_Memory
suffix:semicolon
r_extern
r_int
r_int
id|iSeries_Base_Io_Memory
suffix:semicolon
r_extern
r_int
r_int
id|iSeries_IoMmTable_Entry_Size
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* iSeries_IoMmTable_Initialize                                         */
multiline_comment|/************************************************************************/
multiline_comment|/* - Initalizes the Address Translation Table and get it ready for use. */
multiline_comment|/*   Must be called before any client calls any of the other methods.   */
multiline_comment|/*                                                                      */
multiline_comment|/* Parameters: None.                                                    */
multiline_comment|/*                                                                      */
multiline_comment|/* Return: None.                                                        */
multiline_comment|/************************************************************************/
r_extern
r_void
id|iSeries_IoMmTable_Initialize
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_IoMmTable_Status
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* iSeries_allocateDeviceBars                                           */
multiline_comment|/************************************************************************/
multiline_comment|/* - Allocates ALL pci_dev BAR&squot;s and updates the resources with the BAR */
multiline_comment|/*   value.  BARS with zero length will not have the resources.  The    */
multiline_comment|/*   HvCallPci_getBarParms is used to get the size of the BAR space.    */
multiline_comment|/*   It calls iSeries_IoMmTable_AllocateEntry to allocate each entry.   */
multiline_comment|/*                                                                      */
multiline_comment|/* Parameters:                                                          */
multiline_comment|/* pci_dev = Pointer to pci_dev structure that will be mapped to pseudo */
multiline_comment|/*           I/O Address.                                               */
multiline_comment|/*                                                                      */
multiline_comment|/* Return:                                                              */
multiline_comment|/*   The pci_dev I/O resources updated with pseudo I/O Addresses.       */
multiline_comment|/************************************************************************/
r_extern
r_void
id|iSeries_allocateDeviceBars
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* iSeries_xlateIoMmAddress                                             */
multiline_comment|/************************************************************************/
multiline_comment|/* - Translates an I/O Memory address to Device Node that has been the  */
multiline_comment|/*   allocated the psuedo I/O Address.                                  */
multiline_comment|/*                                                                      */
multiline_comment|/* Parameters:                                                          */
multiline_comment|/* IoAddress = I/O Memory Address.                                      */
multiline_comment|/*                                                                      */
multiline_comment|/* Return:                                                              */
multiline_comment|/*   An iSeries_Device_Node to the device mapped to the I/O address. The*/
multiline_comment|/*   BarNumber and BarOffset are valid if the Device Node is returned.  */
multiline_comment|/************************************************************************/
r_extern
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
suffix:semicolon
macro_line|#endif /* _ISERIES_IOMMTABLE_H */
eof
