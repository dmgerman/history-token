multiline_comment|/* $Id: eicon_pci.h,v 1.6.6.1 2001/09/23 22:24:37 kai Exp $&n; *&n; * ISDN low-level module for Eicon active ISDN-Cards (PCI part).&n; *&n; * Copyright 1998-2000 by Armin Schindler (mac@melware.de)&n; * Copyright 1999,2000 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef eicon_pci_h
DECL|macro|eicon_pci_h
mdefine_line|#define eicon_pci_h
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * card&squot;s description&n; */
r_typedef
r_struct
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ&t;&t;          */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* No. of supported channels  */
DECL|member|card
r_void
op_star
id|card
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* card type                  */
DECL|member|master
r_int
r_char
id|master
suffix:semicolon
multiline_comment|/* Flag: Card is Quadro 1/4   */
DECL|typedef|eicon_pci_card
)brace
id|eicon_pci_card
suffix:semicolon
r_extern
r_int
id|eicon_pci_find_card
c_func
(paren
r_char
op_star
id|ID
)paren
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* eicon_pci_h */
eof
