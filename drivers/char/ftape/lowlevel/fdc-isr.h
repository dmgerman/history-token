macro_line|#ifndef _FDC_ISR_H
DECL|macro|_FDC_ISR_H
mdefine_line|#define _FDC_ISR_H
multiline_comment|/*&n; * Copyright (C) 1993-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/fdc-isr.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:07 $&n; *&n; *      This file declares the global variables necessary to&n; *      synchronize the interrupt service routine (isr) with the&n; *      remainder of the QIC-40/80/3010/3020 floppy-tape driver&n; *      &quot;ftape&quot; for Linux.&n; */
multiline_comment|/*&n; *      fdc-isr.c defined public variables&n; */
r_extern
r_volatile
r_int
id|ft_expected_stray_interrupts
suffix:semicolon
multiline_comment|/* masks stray interrupts */
r_extern
r_volatile
r_int
id|ft_seek_completed
suffix:semicolon
multiline_comment|/* flag set by isr */
r_extern
r_volatile
r_int
id|ft_interrupt_seen
suffix:semicolon
multiline_comment|/* flag set by isr */
r_extern
r_volatile
r_int
id|ft_hide_interrupt
suffix:semicolon
multiline_comment|/* flag set by isr */
multiline_comment|/*&n; *      fdc-io.c defined public functions&n; */
r_extern
r_void
id|fdc_isr
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *      A kernel hook that steals one interrupt from the floppy&n; *      driver (Should be fixed when the new fdc driver gets ready)&n; *      See the linux kernel source files:&n; *          drivers/block/floppy.c &amp; drivers/block/blk.h&n; *      for the details.&n; */
r_extern
r_void
(paren
op_star
id|do_floppy
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
