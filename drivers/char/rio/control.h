multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******           C O N T R O L   P A C K E T   H E A D E R S&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Jon Brawn&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _control_h
DECL|macro|_control_h
mdefine_line|#define _control_h
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_control_h_sccs = &quot;@(#)control.h&t;1.4&quot;; */
macro_line|#endif
DECL|macro|CONTROL
mdefine_line|#define&t;CONTROL&t;&t;&squot;^&squot;
DECL|macro|IFOAD
mdefine_line|#define IFOAD&t;&t;( CONTROL + 1 )
DECL|macro|IDENTIFY
mdefine_line|#define&t;IDENTIFY&t;( CONTROL + 2 )
DECL|macro|ZOMBIE
mdefine_line|#define&t;ZOMBIE&t;&t;( CONTROL + 3 )
DECL|macro|UFOAD
mdefine_line|#define&t;UFOAD&t;&t;( CONTROL + 4 )
DECL|macro|IWAIT
mdefine_line|#define IWAIT&t;&t;( CONTROL + 5 )
DECL|macro|IFOAD_MAGIC
mdefine_line|#define&t;IFOAD_MAGIC&t;0xF0AD&t;&t;/* of course */
DECL|macro|ZOMBIE_MAGIC
mdefine_line|#define&t;ZOMBIE_MAGIC&t;(~0xDEAD)&t;/* not dead -&gt; zombie */
DECL|macro|UFOAD_MAGIC
mdefine_line|#define&t;UFOAD_MAGIC&t;0xD1E&t;&t;/* kill-your-neighbour */
DECL|macro|IWAIT_MAGIC
mdefine_line|#define&t;IWAIT_MAGIC&t;0xB1DE&t;&t;/* Bide your time */
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
