multiline_comment|/* $Id: debug.h,v 1.2.8.1 2001/09/23 22:24:59 kai Exp $&n; *&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
DECL|macro|REQUEST_IRQ
mdefine_line|#define REQUEST_IRQ(a,b,c,d,e) request_irq(a,b,c,d,e)
DECL|macro|FREE_IRQ
mdefine_line|#define FREE_IRQ(a,b) free_irq(a,b)
eof
