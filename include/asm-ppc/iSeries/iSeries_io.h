macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#ifndef _ISERIES_IO_H
DECL|macro|_ISERIES_IO_H
mdefine_line|#define _ISERIES_IO_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_io.h created by Allan Trautman on Thu Dec 28 2000.      */
multiline_comment|/************************************************************************/
multiline_comment|/* Remaps the io.h for the iSeries Io                                   */
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
multiline_comment|/*   Created December 28, 2000                                          */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
r_extern
id|u8
id|iSeries_Readb
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
id|u16
id|iSeries_Readw
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
id|u32
id|iSeries_Readl
c_func
(paren
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_Writeb
c_func
(paren
id|u8
id|IoData
comma
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_Writew
c_func
(paren
id|u16
id|IoData
comma
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_Writel
c_func
(paren
id|u32
id|IoData
comma
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
r_void
op_star
id|iSeries_memcpy_toio
c_func
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|source
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
op_star
id|iSeries_memcpy_fromio
c_func
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|source
comma
r_int
id|n
)paren
suffix:semicolon
macro_line|#endif /*  _ISERIES_IO_H         */
macro_line|#endif /*  CONFIG_PPC_ISERIES  */
eof
