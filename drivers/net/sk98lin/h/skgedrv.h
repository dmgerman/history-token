multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgedrv.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.4 $&n; * Date:&t;$Date: 1999/11/22 13:52:46 $&n; * Purpose:&t;Interface with the driver&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgedrv.h,v $&n; *&t;Revision 1.4  1999/11/22 13:52:46  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.3  1998/12/01 13:31:39  cgoos&n; *&t;SWITCH INTERN Event added.&n; *&t;&n; *&t;Revision 1.2  1998/11/25 08:28:38  gklug&n; *&t;rmv: PORT SWITCH Event&n; *&t;&n; *&t;Revision 1.1  1998/09/29 06:14:07  gklug&n; *&t;add: driver events (initial version)&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKGEDRV_H_
DECL|macro|__INC_SKGEDRV_H_
mdefine_line|#define __INC_SKGEDRV_H_
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * Define the driver events.&n; * Usually the events are defined by the destination module. In case of the&n; * driver we put the definition of the events here.&n; */
DECL|macro|SK_DRV_PORT_RESET
mdefine_line|#define SK_DRV_PORT_RESET&t;1&t;/* The port needs to be reset */
DECL|macro|SK_DRV_NET_UP
mdefine_line|#define SK_DRV_NET_UP   &t;2&t;/* The net is now operational */
DECL|macro|SK_DRV_NET_DOWN
mdefine_line|#define SK_DRV_NET_DOWN&t;&t;3&t;/* The net is now down */
DECL|macro|SK_DRV_SWITCH_SOFT
mdefine_line|#define&t;SK_DRV_SWITCH_SOFT&t;4&t;/* Ports switch with both links conn */
DECL|macro|SK_DRV_SWITCH_HARD
mdefine_line|#define&t;SK_DRV_SWITCH_HARD&t;5&t;/* Port switch due to link failure */
DECL|macro|SK_DRV_RLMT_SEND
mdefine_line|#define&t;SK_DRV_RLMT_SEND&t;6&t;/* Send a RLMT packet */
DECL|macro|SK_DRV_ADAP_FAIL
mdefine_line|#define&t;SK_DRV_ADAP_FAIL&t;7&t;/* The whole adapter fails */
DECL|macro|SK_DRV_PORT_FAIL
mdefine_line|#define&t;SK_DRV_PORT_FAIL&t;8&t;/* One port fails */
DECL|macro|SK_DRV_SWITCH_INTERN
mdefine_line|#define&t;SK_DRV_SWITCH_INTERN&t;9&t;/* Port switch from driver to itself */
macro_line|#endif&t;/* __INC_SKGEDRV_H_ */
eof
