multiline_comment|/* Driver for Microtech DPCM-USB CompactFlash/SmartMedia reader&n; *&n; * $Id: dpcm.c,v 1.3 2000/08/25 00:13:51 mdharm Exp $&n; *&n; * DPCM driver v0.1:&n; *&n; * First release&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 Brian Webb (webbb@earthlink.net)&n; *&n; * This device contains both a CompactFlash card reader, which&n; * usest the Control/Bulk w/o Interrupt protocol and&n; * a SmartMedia card reader that uses the same protocol&n; * as the SDDR09.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;dpcm.h&quot;
macro_line|#include &quot;sddr09.h&quot;
multiline_comment|/*&n; * Transport for the Microtech DPCM-USB&n; *&n; */
DECL|function|dpcm_transport
r_int
id|dpcm_transport
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|srb
op_eq
l_int|NULL
)paren
(brace
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;dpcm_transport: LUN=%d&bslash;n&quot;
comma
id|srb-&gt;lun
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|srb-&gt;lun
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;     * LUN 0 corresponds to the CompactFlash card reader.&n;     */
r_return
id|usb_stor_CB_transport
c_func
(paren
id|srb
comma
id|us
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR09
r_case
l_int|1
suffix:colon
multiline_comment|/*&n;     * LUN 1 corresponds to the SmartMedia card reader.&n;     */
multiline_comment|/*&n;     * Set the LUN to 0 (just in case).&n;     */
id|srb-&gt;lun
op_assign
l_int|0
suffix:semicolon
id|us-&gt;srb-&gt;lun
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|sddr09_transport
c_func
(paren
id|srb
comma
id|us
)paren
suffix:semicolon
id|srb-&gt;lun
op_assign
l_int|1
suffix:semicolon
id|us-&gt;srb-&gt;lun
op_assign
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|US_DEBUGP
c_func
(paren
l_string|&quot;dpcm_transport: Invalid LUN %d&bslash;n&quot;
comma
id|srb-&gt;lun
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
)brace
eof
