multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifdef __NO_PA_HDRS
id|PA
id|header
id|file
op_decrement
r_do
op_logical_neg
id|include
id|this
id|header
id|file
r_for
c_loop
id|non
op_minus
id|PA
id|builds
dot
macro_line|#endif
multiline_comment|/*&n; *  These macros are designed to be portable to all machines that have&n; *  a wordsize greater than or equal to 32 bits that support the portable&n; *  C compiler and the standard C preprocessor.  Wordsize (default 32)&n; *  and bitfield assignment (default left-to-right,  unlike VAX, PDP-11)&n; *  should be predefined using the constants HOSTWDSZ and BITFRL and&n; *  the C compiler &quot;-D&quot; flag (e.g., -DHOSTWDSZ=36 -DBITFLR for the DEC-20).&n; *  Note that the macro arguments assume that the integer being referenced&n; *  is a 32-bit integer (right-justified on the 20) and that bit 0 is the&n; *  most significant bit.&n; */
macro_line|#ifndef HOSTWDSZ
DECL|macro|HOSTWDSZ
mdefine_line|#define&t;HOSTWDSZ&t;32
macro_line|#endif
multiline_comment|/*###########################  Macros  ######################################*/
multiline_comment|/*-------------------------------------------------------------------------&n; * NewDeclareBitField_Reference - Declare a structure similar to the simulator&n; * function &quot;DeclBitfR&quot; except its use is restricted to occur within a larger&n; * enclosing structure or union definition.  This declaration is an unnamed&n; * structure with the argument, name, as the member name and the argument,&n; * uname, as the element name. &n; *----------------------------------------------------------------------- */
DECL|macro|Bitfield_extract
mdefine_line|#define Bitfield_extract(start, length, object) &t;&bslash;&n;    ((object) &gt;&gt; (HOSTWDSZ - (start) - (length)) &amp; &t;&bslash;&n;    ((unsigned)-1 &gt;&gt; (HOSTWDSZ - (length))))
DECL|macro|Bitfield_signed_extract
mdefine_line|#define Bitfield_signed_extract(start, length, object) &bslash;&n;    ((int)((object) &lt;&lt; start) &gt;&gt; (HOSTWDSZ - (length)))
DECL|macro|Bitfield_mask
mdefine_line|#define Bitfield_mask(start, len, object)&t;&t;&bslash;&n;    ((object) &amp; (((unsigned)-1 &gt;&gt; (HOSTWDSZ-len)) &lt;&lt; (HOSTWDSZ-start-len)))
DECL|macro|Bitfield_deposit
mdefine_line|#define Bitfield_deposit(value,start,len,object)  object = &bslash;&n;    ((object) &amp; ~(((unsigned)-1 &gt;&gt; (HOSTWDSZ-len)) &lt;&lt; (HOSTWDSZ-start-len))) | &bslash;&n;    (((value) &amp; ((unsigned)-1 &gt;&gt; (HOSTWDSZ-len))) &lt;&lt; (HOSTWDSZ-start-len))
eof
