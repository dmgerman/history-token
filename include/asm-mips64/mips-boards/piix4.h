multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Register definitions for Intel PIIX4 South Bridge Device.&n; *&n; */
macro_line|#ifndef PIIX4_H
DECL|macro|PIIX4_H
mdefine_line|#define PIIX4_H
multiline_comment|/************************************************************************&n; *  IO register offsets&n; ************************************************************************/
DECL|macro|PIIX4_ICTLR1_ICW1
mdefine_line|#define PIIX4_ICTLR1_ICW1&t;0x20
DECL|macro|PIIX4_ICTLR1_ICW2
mdefine_line|#define PIIX4_ICTLR1_ICW2&t;0x21
DECL|macro|PIIX4_ICTLR1_ICW3
mdefine_line|#define PIIX4_ICTLR1_ICW3&t;0x21
DECL|macro|PIIX4_ICTLR1_ICW4
mdefine_line|#define PIIX4_ICTLR1_ICW4&t;0x21
DECL|macro|PIIX4_ICTLR2_ICW1
mdefine_line|#define PIIX4_ICTLR2_ICW1&t;0xa0
DECL|macro|PIIX4_ICTLR2_ICW2
mdefine_line|#define PIIX4_ICTLR2_ICW2&t;0xa1
DECL|macro|PIIX4_ICTLR2_ICW3
mdefine_line|#define PIIX4_ICTLR2_ICW3&t;0xa1
DECL|macro|PIIX4_ICTLR2_ICW4
mdefine_line|#define PIIX4_ICTLR2_ICW4&t;0xa1
DECL|macro|PIIX4_ICTLR1_OCW1
mdefine_line|#define PIIX4_ICTLR1_OCW1&t;0x21
DECL|macro|PIIX4_ICTLR1_OCW2
mdefine_line|#define PIIX4_ICTLR1_OCW2&t;0x20
DECL|macro|PIIX4_ICTLR1_OCW3
mdefine_line|#define PIIX4_ICTLR1_OCW3&t;0x20
DECL|macro|PIIX4_ICTLR1_OCW4
mdefine_line|#define PIIX4_ICTLR1_OCW4&t;0x20
DECL|macro|PIIX4_ICTLR2_OCW1
mdefine_line|#define PIIX4_ICTLR2_OCW1&t;0xa1
DECL|macro|PIIX4_ICTLR2_OCW2
mdefine_line|#define PIIX4_ICTLR2_OCW2&t;0xa0
DECL|macro|PIIX4_ICTLR2_OCW3
mdefine_line|#define PIIX4_ICTLR2_OCW3&t;0xa0
DECL|macro|PIIX4_ICTLR2_OCW4
mdefine_line|#define PIIX4_ICTLR2_OCW4&t;0xa0
multiline_comment|/************************************************************************&n; *  Register encodings.&n; ************************************************************************/
DECL|macro|PIIX4_OCW2_NSEOI
mdefine_line|#define PIIX4_OCW2_NSEOI&t;(0x1 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_SEOI
mdefine_line|#define PIIX4_OCW2_SEOI&t;&t;(0x3 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_RNSEOI
mdefine_line|#define PIIX4_OCW2_RNSEOI&t;(0x5 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_RAEOIS
mdefine_line|#define PIIX4_OCW2_RAEOIS&t;(0x4 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_RAEOIC
mdefine_line|#define PIIX4_OCW2_RAEOIC&t;(0x0 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_RSEOI
mdefine_line|#define PIIX4_OCW2_RSEOI&t;(0x7 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_SP
mdefine_line|#define PIIX4_OCW2_SP&t;&t;(0x6 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_NOP
mdefine_line|#define PIIX4_OCW2_NOP&t;&t;(0x2 &lt;&lt; 5)
DECL|macro|PIIX4_OCW2_SEL
mdefine_line|#define PIIX4_OCW2_SEL          (0x0 &lt;&lt; 3)
DECL|macro|PIIX4_OCW2_ILS_0
mdefine_line|#define PIIX4_OCW2_ILS_0&t;0
DECL|macro|PIIX4_OCW2_ILS_1
mdefine_line|#define PIIX4_OCW2_ILS_1&t;1
DECL|macro|PIIX4_OCW2_ILS_2
mdefine_line|#define PIIX4_OCW2_ILS_2&t;2
DECL|macro|PIIX4_OCW2_ILS_3
mdefine_line|#define PIIX4_OCW2_ILS_3&t;3
DECL|macro|PIIX4_OCW2_ILS_4
mdefine_line|#define PIIX4_OCW2_ILS_4&t;4
DECL|macro|PIIX4_OCW2_ILS_5
mdefine_line|#define PIIX4_OCW2_ILS_5&t;5
DECL|macro|PIIX4_OCW2_ILS_6
mdefine_line|#define PIIX4_OCW2_ILS_6&t;6
DECL|macro|PIIX4_OCW2_ILS_7
mdefine_line|#define PIIX4_OCW2_ILS_7&t;7
DECL|macro|PIIX4_OCW2_ILS_8
mdefine_line|#define PIIX4_OCW2_ILS_8&t;0
DECL|macro|PIIX4_OCW2_ILS_9
mdefine_line|#define PIIX4_OCW2_ILS_9&t;1
DECL|macro|PIIX4_OCW2_ILS_10
mdefine_line|#define PIIX4_OCW2_ILS_10&t;2
DECL|macro|PIIX4_OCW2_ILS_11
mdefine_line|#define PIIX4_OCW2_ILS_11&t;3
DECL|macro|PIIX4_OCW2_ILS_12
mdefine_line|#define PIIX4_OCW2_ILS_12&t;4
DECL|macro|PIIX4_OCW2_ILS_13
mdefine_line|#define PIIX4_OCW2_ILS_13&t;5
DECL|macro|PIIX4_OCW2_ILS_14
mdefine_line|#define PIIX4_OCW2_ILS_14&t;6
DECL|macro|PIIX4_OCW2_ILS_15
mdefine_line|#define PIIX4_OCW2_ILS_15&t;7
DECL|macro|PIIX4_OCW3_SEL
mdefine_line|#define PIIX4_OCW3_SEL          (0x1 &lt;&lt; 3)
DECL|macro|PIIX4_OCW3_IRR
mdefine_line|#define PIIX4_OCW3_IRR          0x2
DECL|macro|PIIX4_OCW3_ISR
mdefine_line|#define PIIX4_OCW3_ISR          0x3
macro_line|#endif /* !(PIIX4_H) */
eof
