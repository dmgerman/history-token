multiline_comment|/* $Id: b1pcmcia.h,v 1.1.8.2 2001/09/23 22:25:05 kai Exp $&n; *&n; * Exported functions of module b1pcmcia to be called by&n; * avm_cs card services module.&n; *&n; * Copyright 1999 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef _B1PCMCIA_H_
DECL|macro|_B1PCMCIA_H_
mdefine_line|#define _B1PCMCIA_H_
r_int
id|b1pcmcia_addcard_b1
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
id|b1pcmcia_addcard_m1
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
id|b1pcmcia_addcard_m2
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
id|b1pcmcia_delcard
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif&t;/* _B1PCMCIA_H_ */
eof
