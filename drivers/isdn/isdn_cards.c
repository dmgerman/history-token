multiline_comment|/* $Id: isdn_cards.c,v 1.14 2000/11/23 20:45:14 kai Exp $&n;&n; * Linux ISDN subsystem, initialization for non-modularized drivers.&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@isdn4linux.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ISDN_DRV_ICN
r_extern
r_void
id|icn_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_HISAX
r_extern
r_void
id|HiSax_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_PCBIT
r_extern
r_void
id|pcbit_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ISDN_DRV_EICON_OLD) || defined(CONFIG_ISDN_DRV_EICON_DIVAS)
r_extern
r_void
id|eicon_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_ACT2000
r_extern
r_void
id|act2000_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_void
DECL|function|isdn_cards_init
id|isdn_cards_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if CONFIG_ISDN_DRV_ICN
id|icn_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_HISAX
id|HiSax_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_PCBIT
id|pcbit_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_ACT2000
id|act2000_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ISDN_DRV_EICON_OLD) || defined(CONFIG_ISDN_DRV_EICON_DIVAS)
id|eicon_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
