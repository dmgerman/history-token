multiline_comment|/*&n; * $Id: b1lli.h,v 1.8.8.1 2001/03/15 09:58:30 kai Exp $&n; *&n; * ISDN lowlevel-module for AVM B1-card.&n; *&n; * Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * $Log: b1lli.h,v $&n; * Revision 1.8.8.1  2001/03/15 09:58:30  kai&n; * spelling fix&n; *&n; * Revision 1.8  1999/07/01 15:26:54  calle&n; * complete new version (I love it):&n; * + new hardware independed &quot;capi_driver&quot; interface that will make it easy to:&n; *   - support other controllers with CAPI-2.0 (i.e. USB Controller)&n; *   - write a CAPI-2.0 for the passive cards&n; *   - support serial link CAPI-2.0 boxes.&n; * + wrote &quot;capi_driver&quot; for all supported cards.&n; * + &quot;capi_driver&quot; (supported cards) now have to be configured with&n; *   make menuconfig, in the past all supported cards where included&n; *   at once.&n; * + new and better informations in /proc/capi/&n; * + new ioctl to switch trace of capi messages per controller&n; *   using &quot;avmcapictrl trace [contr] on|off|....&quot;&n; * + complete testcircle with all supported cards and also the&n; *   PCMCIA cards (now patch for pcmcia-cs-3.0.13 needed) done.&n; *&n; * Revision 1.7  1999/06/21 15:24:25  calle&n; * extend information in /proc.&n; *&n; * Revision 1.6  1999/04/15 19:49:36  calle&n; * fix fuer die B1-PCI. Jetzt geht z.B. auch IRQ 17 ...&n; *&n; * Revision 1.5  1998/10/25 14:50:28  fritz&n; * Backported from MIPS (Cobalt).&n; *&n; * Revision 1.4  1998/03/29 16:05:02  calle&n; * changes from 2.0 tree merged.&n; *&n; * Revision 1.1.2.9  1998/03/20 14:30:02  calle&n; * added cardnr to detect if you try to add same T1 to different io address.&n; * change number of nccis depending on number of channels.&n; *&n; * Revision 1.1.2.8  1998/03/04 17:32:33  calle&n; * Changes for T1.&n; *&n; * Revision 1.1.2.7  1998/02/27 15:38:29  calle&n; * T1 running with slow link.&n; *&n; * Revision 1.1.2.6  1998/02/24 17:57:36  calle&n; * changes for T1.&n; *&n; * Revision 1.3  1998/01/31 10:54:37  calle&n; * include changes for PCMCIA cards from 2.0 version&n; *&n; * Revision 1.2  1997/12/10 19:38:42  calle&n; * get changes from 2.0 tree&n; *&n; * Revision 1.1.2.2  1997/11/26 16:57:26  calle&n; * more changes for B1/M1/T1.&n; *&n; * Revision 1.1.2.1  1997/11/26 10:47:01  calle&n; * prepared for M1 (Mobile) and T1 (PMX) cards.&n; * prepared to set configuration after load to support other D-channel&n; * protocols, point-to-point and leased lines.&n; *&n; * Revision 1.1  1997/03/04 21:27:32  calle&n; * First version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; */
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
