multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*  *********************************************************************&n;    *  &n;    *  Broadcom Common Firmware Environment (CFE)&n;    *  &n;    *  Error codes&t;&t;&t;&t;File: cfe_error.h&n;    *  &n;    *  CFE&squot;s global error code list is here.&n;    *  &n;    *  Author:  Mitch Lichtenberg&n;    *  &n;    ********************************************************************* */
DECL|macro|CFE_OK
mdefine_line|#define CFE_OK&t;&t;&t; 0
DECL|macro|CFE_ERR
mdefine_line|#define CFE_ERR                 -1&t;/* generic error */
DECL|macro|CFE_ERR_INV_COMMAND
mdefine_line|#define CFE_ERR_INV_COMMAND&t;-2
DECL|macro|CFE_ERR_EOF
mdefine_line|#define CFE_ERR_EOF&t;&t;-3
DECL|macro|CFE_ERR_IOERR
mdefine_line|#define CFE_ERR_IOERR&t;&t;-4
DECL|macro|CFE_ERR_NOMEM
mdefine_line|#define CFE_ERR_NOMEM&t;&t;-5
DECL|macro|CFE_ERR_DEVNOTFOUND
mdefine_line|#define CFE_ERR_DEVNOTFOUND&t;-6
DECL|macro|CFE_ERR_DEVOPEN
mdefine_line|#define CFE_ERR_DEVOPEN&t;&t;-7
DECL|macro|CFE_ERR_INV_PARAM
mdefine_line|#define CFE_ERR_INV_PARAM&t;-8
DECL|macro|CFE_ERR_ENVNOTFOUND
mdefine_line|#define CFE_ERR_ENVNOTFOUND&t;-9
DECL|macro|CFE_ERR_ENVREADONLY
mdefine_line|#define CFE_ERR_ENVREADONLY&t;-10
DECL|macro|CFE_ERR_NOTELF
mdefine_line|#define CFE_ERR_NOTELF&t;&t;-11
DECL|macro|CFE_ERR_NOT32BIT
mdefine_line|#define CFE_ERR_NOT32BIT &t;-12
DECL|macro|CFE_ERR_WRONGENDIAN
mdefine_line|#define CFE_ERR_WRONGENDIAN &t;-13
DECL|macro|CFE_ERR_BADELFVERS
mdefine_line|#define CFE_ERR_BADELFVERS &t;-14
DECL|macro|CFE_ERR_NOTMIPS
mdefine_line|#define CFE_ERR_NOTMIPS &t;-15
DECL|macro|CFE_ERR_BADELFFMT
mdefine_line|#define CFE_ERR_BADELFFMT &t;-16
DECL|macro|CFE_ERR_BADADDR
mdefine_line|#define CFE_ERR_BADADDR &t;-17
DECL|macro|CFE_ERR_FILENOTFOUND
mdefine_line|#define CFE_ERR_FILENOTFOUND&t;-18
DECL|macro|CFE_ERR_UNSUPPORTED
mdefine_line|#define CFE_ERR_UNSUPPORTED&t;-19
DECL|macro|CFE_ERR_HOSTUNKNOWN
mdefine_line|#define CFE_ERR_HOSTUNKNOWN&t;-20
DECL|macro|CFE_ERR_TIMEOUT
mdefine_line|#define CFE_ERR_TIMEOUT&t;&t;-21
DECL|macro|CFE_ERR_PROTOCOLERR
mdefine_line|#define CFE_ERR_PROTOCOLERR&t;-22
DECL|macro|CFE_ERR_NETDOWN
mdefine_line|#define CFE_ERR_NETDOWN&t;&t;-23
DECL|macro|CFE_ERR_NONAMESERVER
mdefine_line|#define CFE_ERR_NONAMESERVER&t;-24
DECL|macro|CFE_ERR_NOHANDLES
mdefine_line|#define CFE_ERR_NOHANDLES&t;-25
DECL|macro|CFE_ERR_ALREADYBOUND
mdefine_line|#define CFE_ERR_ALREADYBOUND&t;-26
DECL|macro|CFE_ERR_CANNOTSET
mdefine_line|#define CFE_ERR_CANNOTSET&t;-27
DECL|macro|CFE_ERR_NOMORE
mdefine_line|#define CFE_ERR_NOMORE&t;&t;-28
DECL|macro|CFE_ERR_BADFILESYS
mdefine_line|#define CFE_ERR_BADFILESYS&t;-29
DECL|macro|CFE_ERR_FSNOTAVAIL
mdefine_line|#define CFE_ERR_FSNOTAVAIL&t;-30
DECL|macro|CFE_ERR_INVBOOTBLOCK
mdefine_line|#define CFE_ERR_INVBOOTBLOCK&t;-31
DECL|macro|CFE_ERR_WRONGDEVTYPE
mdefine_line|#define CFE_ERR_WRONGDEVTYPE&t;-32
DECL|macro|CFE_ERR_BBCHECKSUM
mdefine_line|#define CFE_ERR_BBCHECKSUM&t;-33
DECL|macro|CFE_ERR_BOOTPROGCHKSUM
mdefine_line|#define CFE_ERR_BOOTPROGCHKSUM&t;-34
DECL|macro|CFE_ERR_LDRNOTAVAIL
mdefine_line|#define CFE_ERR_LDRNOTAVAIL&t;-35
DECL|macro|CFE_ERR_NOTREADY
mdefine_line|#define CFE_ERR_NOTREADY&t;-36
DECL|macro|CFE_ERR_GETMEM
mdefine_line|#define CFE_ERR_GETMEM          -37
DECL|macro|CFE_ERR_SETMEM
mdefine_line|#define CFE_ERR_SETMEM          -38
DECL|macro|CFE_ERR_NOTCONN
mdefine_line|#define CFE_ERR_NOTCONN&t;&t;-39
DECL|macro|CFE_ERR_ADDRINUSE
mdefine_line|#define CFE_ERR_ADDRINUSE&t;-40
eof
