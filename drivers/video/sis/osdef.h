multiline_comment|/* $XFree86$ */
multiline_comment|/* $XdotOrg$ */
multiline_comment|/*&n; * OS depending defines&n; *&n; * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria&n; *&n; * If distributed as part of the Linux kernel, the following license terms&n; * apply:&n; *&n; * * This program is free software; you can redistribute it and/or modify&n; * * it under the terms of the GNU General Public License as published by&n; * * the Free Software Foundation; either version 2 of the named License,&n; * * or any later version.&n; * *&n; * * This program is distributed in the hope that it will be useful,&n; * * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * * GNU General Public License for more details.&n; * *&n; * * You should have received a copy of the GNU General Public License&n; * * along with this program; if not, write to the Free Software&n; * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; *&n; * Otherwise, the following license terms apply:&n; *&n; * * Redistribution and use in source and binary forms, with or without&n; * * modification, are permitted provided that the following conditions&n; * * are met:&n; * * 1) Redistributions of source code must retain the above copyright&n; * *    notice, this list of conditions and the following disclaimer.&n; * * 2) Redistributions in binary form must reproduce the above copyright&n; * *    notice, this list of conditions and the following disclaimer in the&n; * *    documentation and/or other materials provided with the distribution.&n; * * 3) The name of the author may not be used to endorse or promote products&n; * *    derived from this software without specific prior written permission.&n; * *&n; * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR&n; * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,&n; * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY&n; * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Author: &t;Thomas Winischhofer &lt;thomas@winischhofer.net&gt;&n; *&t;&t;Silicon Integrated Systems, Inc. (used by permission)&n; *&n; */
macro_line|#ifndef _SIS_OSDEF_H_
DECL|macro|_SIS_OSDEF_H_
mdefine_line|#define _SIS_OSDEF_H_
multiline_comment|/* The choices are: */
DECL|macro|LINUX_KERNEL
mdefine_line|#define LINUX_KERNEL&t;   /* Linux kernel framebuffer */
multiline_comment|/* #define LINUX_XF86 */
multiline_comment|/* XFree86/X.org */
macro_line|#ifdef OutPortByte
DECL|macro|OutPortByte
macro_line|#undef OutPortByte
macro_line|#endif
macro_line|#ifdef OutPortWord
DECL|macro|OutPortWord
macro_line|#undef OutPortWord
macro_line|#endif
macro_line|#ifdef OutPortLong
DECL|macro|OutPortLong
macro_line|#undef OutPortLong
macro_line|#endif
macro_line|#ifdef InPortByte
DECL|macro|InPortByte
macro_line|#undef InPortByte
macro_line|#endif
macro_line|#ifdef InPortWord
DECL|macro|InPortWord
macro_line|#undef InPortWord
macro_line|#endif
macro_line|#ifdef InPortLong
DECL|macro|InPortLong
macro_line|#undef InPortLong
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/*  LINUX KERNEL                                                      */
multiline_comment|/**********************************************************************/
macro_line|#ifdef LINUX_KERNEL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_FB_SIS_300
DECL|macro|SIS300
mdefine_line|#define SIS300
macro_line|#endif
macro_line|#ifdef CONFIG_FB_SIS_315
DECL|macro|SIS315H
mdefine_line|#define SIS315H
macro_line|#endif
macro_line|#if !defined(SIS300) &amp;&amp; !defined(SIS315H)
macro_line|#warning Neither CONFIG_FB_SIS_300 nor CONFIG_FB_SIS_315 is set
macro_line|#warning sisfb will not work!
macro_line|#endif
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) outb((u8)(v),(SISIOADDRESS)(p))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) outw((u16)(v),(SISIOADDRESS)(p))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) outl((u32)(v),(SISIOADDRESS)(p))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    inb((SISIOADDRESS)(p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    inw((SISIOADDRESS)(p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    inl((SISIOADDRESS)(p))
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset_io(MemoryAddress, value, MemorySize)
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/*  XFree86/X.org                                                    */
multiline_comment|/**********************************************************************/
macro_line|#ifdef LINUX_XF86
DECL|macro|SIS300
mdefine_line|#define SIS300
DECL|macro|SIS315H
mdefine_line|#define SIS315H
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) outSISREG((IOADDRESS)(p),(CARD8)(v))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) outSISREGW((IOADDRESS)(p),(CARD16)(v))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) outSISREGL((IOADDRESS)(p),(CARD32)(v))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    inSISREG((IOADDRESS)(p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    inSISREGW((IOADDRESS)(p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    inSISREGL((IOADDRESS)(p))
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset(MemoryAddress, value, MemorySize)
macro_line|#endif
macro_line|#endif  /* _OSDEF_H_ */
eof
