multiline_comment|/*     &n; **********************************************************************&n; *     sblive_fx.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _EFXMGR_H
DECL|macro|_EFXMGR_H
mdefine_line|#define _EFXMGR_H
DECL|macro|WRITE_EFX
mdefine_line|#define WRITE_EFX(a, b, c) sblive_writeptr((a), MICROCODEBASE + (b), 0, (c))
DECL|macro|OP
mdefine_line|#define OP(op, z, w, x, y) &bslash;&n;        do { WRITE_EFX(card, (pc) * 2, ((x) &lt;&lt; 10) | (y)); &bslash;&n;        WRITE_EFX(card, (pc) * 2 + 1, ((op) &lt;&lt; 20) | ((z) &lt;&lt; 10) | (w)); &bslash;&n;        ++pc; } while (0)
macro_line|#endif /* _EFXMGR_H */
eof
