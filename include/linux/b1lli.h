multiline_comment|/* $Id: b1lli.h,v 1.8.8.3 2001/09/23 22:25:05 kai Exp $&n; *&n; * ISDN lowlevel-module for AVM B1-card.&n; *&n; * Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef _B1LLI_H_
DECL|macro|_B1LLI_H_
mdefine_line|#define _B1LLI_H_
multiline_comment|/*&n; * struct for loading t4 file &n; */
DECL|struct|avmb1_t4file
r_typedef
r_struct
id|avmb1_t4file
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|typedef|avmb1_t4file
)brace
id|avmb1_t4file
suffix:semicolon
DECL|struct|avmb1_loaddef
r_typedef
r_struct
id|avmb1_loaddef
(brace
DECL|member|contr
r_int
id|contr
suffix:semicolon
DECL|member|t4file
id|avmb1_t4file
id|t4file
suffix:semicolon
DECL|typedef|avmb1_loaddef
)brace
id|avmb1_loaddef
suffix:semicolon
DECL|struct|avmb1_loadandconfigdef
r_typedef
r_struct
id|avmb1_loadandconfigdef
(brace
DECL|member|contr
r_int
id|contr
suffix:semicolon
DECL|member|t4file
id|avmb1_t4file
id|t4file
suffix:semicolon
DECL|member|t4config
id|avmb1_t4file
id|t4config
suffix:semicolon
DECL|typedef|avmb1_loadandconfigdef
)brace
id|avmb1_loadandconfigdef
suffix:semicolon
DECL|struct|avmb1_resetdef
r_typedef
r_struct
id|avmb1_resetdef
(brace
DECL|member|contr
r_int
id|contr
suffix:semicolon
DECL|typedef|avmb1_resetdef
)brace
id|avmb1_resetdef
suffix:semicolon
DECL|struct|avmb1_getdef
r_typedef
r_struct
id|avmb1_getdef
(brace
DECL|member|contr
r_int
id|contr
suffix:semicolon
DECL|member|cardtype
r_int
id|cardtype
suffix:semicolon
DECL|member|cardstate
r_int
id|cardstate
suffix:semicolon
DECL|typedef|avmb1_getdef
)brace
id|avmb1_getdef
suffix:semicolon
multiline_comment|/*&n; * struct for adding new cards &n; */
DECL|struct|avmb1_carddef
r_typedef
r_struct
id|avmb1_carddef
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|typedef|avmb1_carddef
)brace
id|avmb1_carddef
suffix:semicolon
DECL|macro|AVM_CARDTYPE_B1
mdefine_line|#define AVM_CARDTYPE_B1&t;&t;0
DECL|macro|AVM_CARDTYPE_T1
mdefine_line|#define AVM_CARDTYPE_T1&t;&t;1
DECL|macro|AVM_CARDTYPE_M1
mdefine_line|#define AVM_CARDTYPE_M1&t;&t;2
DECL|macro|AVM_CARDTYPE_M2
mdefine_line|#define AVM_CARDTYPE_M2&t;&t;3
DECL|struct|avmb1_extcarddef
r_typedef
r_struct
id|avmb1_extcarddef
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|cardtype
r_int
id|cardtype
suffix:semicolon
DECL|member|cardnr
r_int
id|cardnr
suffix:semicolon
multiline_comment|/* for HEMA/T1 */
DECL|typedef|avmb1_extcarddef
)brace
id|avmb1_extcarddef
suffix:semicolon
DECL|macro|AVMB1_LOAD
mdefine_line|#define&t;AVMB1_LOAD&t;&t;0&t;/* load image to card */
DECL|macro|AVMB1_ADDCARD
mdefine_line|#define AVMB1_ADDCARD&t;&t;1&t;/* add a new card */
DECL|macro|AVMB1_RESETCARD
mdefine_line|#define AVMB1_RESETCARD&t;&t;2&t;/* reset a card */
DECL|macro|AVMB1_LOAD_AND_CONFIG
mdefine_line|#define&t;AVMB1_LOAD_AND_CONFIG&t;3&t;/* load image and config to card */
DECL|macro|AVMB1_ADDCARD_WITH_TYPE
mdefine_line|#define&t;AVMB1_ADDCARD_WITH_TYPE&t;4&t;/* add a new card, with cardtype */
DECL|macro|AVMB1_GET_CARDINFO
mdefine_line|#define AVMB1_GET_CARDINFO&t;5&t;/* get cardtype */
DECL|macro|AVMB1_REMOVECARD
mdefine_line|#define AVMB1_REMOVECARD&t;6&t;/* remove a card (useful for T1) */
DECL|macro|AVMB1_REGISTERCARD_IS_OBSOLETE
mdefine_line|#define&t;AVMB1_REGISTERCARD_IS_OBSOLETE
macro_line|#endif&t;&t;&t;&t;/* _B1LLI_H_ */
eof
