multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgedrv.h&n; * Project:&t;Gigabit Ethernet Adapters, Common Modules&n; * Version:&t;$Revision: 1.10 $&n; * Date:&t;$Date: 2003/07/04 12:25:01 $&n; * Purpose:&t;Interface with the driver&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgedrv.h,v $&n; *&t;Revision 1.10  2003/07/04 12:25:01  rschmidt&n; *&t;Added event SK_DRV_DOWNSHIFT_DET for Downshift 4-Pair / 2-Pair&n; *&t;&n; *&t;Revision 1.9  2003/05/13 17:24:21  mkarl&n; *&t;Added events SK_DRV_LINK_UP and SK_DRV_LINK_DOWN for drivers not using&n; *&t;RLMT (SK_NO_RLMT).&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.8  2003/03/31 07:18:54  mkarl&n; *&t;Corrected Copyright.&n; *&t;&n; *&t;Revision 1.7  2003/03/18 09:43:47  rroesler&n; *&t;Added new event for timer&n; *&t;&n; *&t;Revision 1.6  2002/07/15 15:38:01  rschmidt&n; *&t;Power Management support&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.5  2002/04/25 11:05:47  rschmidt&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.4  1999/11/22 13:52:46  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.3  1998/12/01 13:31:39  cgoos&n; *&t;SWITCH INTERN Event added.&n; *&t;&n; *&t;Revision 1.2  1998/11/25 08:28:38  gklug&n; *&t;rmv: PORT SWITCH Event&n; *&t;&n; *&t;Revision 1.1  1998/09/29 06:14:07  gklug&n; *&t;add: driver events (initial version)&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKGEDRV_H_
DECL|macro|__INC_SKGEDRV_H_
mdefine_line|#define __INC_SKGEDRV_H_
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * Define the driver events.&n; * Usually the events are defined by the destination module.&n; * In case of the driver we put the definition of the events here.&n; */
DECL|macro|SK_DRV_PORT_RESET
mdefine_line|#define SK_DRV_PORT_RESET&t;&t; 1&t;/* The port needs to be reset */
DECL|macro|SK_DRV_NET_UP
mdefine_line|#define SK_DRV_NET_UP   &t;&t; 2&t;/* The net is operational */
DECL|macro|SK_DRV_NET_DOWN
mdefine_line|#define SK_DRV_NET_DOWN&t;&t;&t; 3&t;/* The net is down */
DECL|macro|SK_DRV_SWITCH_SOFT
mdefine_line|#define SK_DRV_SWITCH_SOFT&t;&t; 4&t;/* Ports switch with both links connected */
DECL|macro|SK_DRV_SWITCH_HARD
mdefine_line|#define SK_DRV_SWITCH_HARD&t;&t; 5&t;/* Port switch due to link failure */
DECL|macro|SK_DRV_RLMT_SEND
mdefine_line|#define SK_DRV_RLMT_SEND&t;&t; 6&t;/* Send a RLMT packet */
DECL|macro|SK_DRV_ADAP_FAIL
mdefine_line|#define SK_DRV_ADAP_FAIL&t;&t; 7&t;/* The whole adapter fails */
DECL|macro|SK_DRV_PORT_FAIL
mdefine_line|#define SK_DRV_PORT_FAIL&t;&t; 8&t;/* One port fails */
DECL|macro|SK_DRV_SWITCH_INTERN
mdefine_line|#define SK_DRV_SWITCH_INTERN&t; 9&t;/* Port switch by the driver itself */
DECL|macro|SK_DRV_POWER_DOWN
mdefine_line|#define SK_DRV_POWER_DOWN&t;&t;10&t;/* Power down mode */
DECL|macro|SK_DRV_TIMER
mdefine_line|#define SK_DRV_TIMER&t;&t;&t;11&t;/* Timer for free use */
macro_line|#ifdef SK_NO_RLMT
DECL|macro|SK_DRV_LINK_UP
mdefine_line|#define SK_DRV_LINK_UP  &t;&t;12&t;/* Link Up event for driver */
DECL|macro|SK_DRV_LINK_DOWN
mdefine_line|#define SK_DRV_LINK_DOWN&t;&t;13&t;/* Link Down event for driver */
macro_line|#endif
DECL|macro|SK_DRV_DOWNSHIFT_DET
mdefine_line|#define SK_DRV_DOWNSHIFT_DET&t;14&t;/* Downshift 4-Pair / 2-Pair (YUKON only) */
macro_line|#endif /* __INC_SKGEDRV_H_ */
eof
