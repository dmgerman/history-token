multiline_comment|/* (C) 1999-2003 Nemosoft Unv.&n;   (C) 2004      Luc Saillard (luc@saillard.org)&n;&n;   NOTE: this version of pwc is an unofficial (modified) release of pwc &amp; pcwx&n;   driver and thus may have bugs that are not present in the original version.&n;   Please send bug reports and support requests to &lt;luc@saillard.org&gt;.&n;   The decompression routines have been implemented by reverse-engineering the&n;   Nemosoft binary pwcx module. Caveat emptor.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
multiline_comment|/* This file is the bridge between the kernel module and the plugin; it&n;   describes the structures and datatypes used in both modules. Any&n;   significant change should be reflected by increasing the &n;   pwc_decompressor_version major number.&n; */
macro_line|#ifndef PWC_UNCOMPRESS_H
DECL|macro|PWC_UNCOMPRESS_H
mdefine_line|#define PWC_UNCOMPRESS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;pwc-ioctl.h&quot;
multiline_comment|/* from pwc-dec.h */
DECL|macro|PWCX_FLAG_PLANAR
mdefine_line|#define PWCX_FLAG_PLANAR        0x0001
multiline_comment|/* */
macro_line|#endif
eof
