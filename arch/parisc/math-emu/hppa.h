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
multiline_comment|/* amount is assumed to be a constant between 0 and 32 (non-inclusive) */
DECL|macro|Shiftdouble
mdefine_line|#define Shiftdouble(left,right,amount,dest)&t;&t;&t;&bslash;&n;    /* int left, right, amount, dest; */&t;&t;&t;&bslash;&n;    dest = ((left) &lt;&lt; (32-(amount))) | ((unsigned int)(right) &gt;&gt; (amount))
multiline_comment|/* amount must be less than 32 */
DECL|macro|Variableshiftdouble
mdefine_line|#define Variableshiftdouble(left,right,amount,dest)&t;&t;&bslash;&n;    /* unsigned int left, right;  int amount, dest; */&t;&t;&bslash;&n;    if (amount == 0) dest = right;&t;&t;&t;&t;&bslash;&n;    else dest = ((((unsigned) left)&amp;0x7fffffff) &lt;&lt; (32-(amount))) |&t;&bslash;&n;          ((unsigned) right &gt;&gt; (amount))
multiline_comment|/* amount must be between 0 and 32 (non-inclusive) */
DECL|macro|Variable_shift_double
mdefine_line|#define Variable_shift_double(left,right,amount,dest)&t;&t;&bslash;&n;    /* unsigned int left, right;  int amount, dest; */&t;&t;&bslash;&n;    dest = (left &lt;&lt; (32-(amount))) | ((unsigned) right &gt;&gt; (amount))
eof
