multiline_comment|/*&n; *&n; *   Copyright (c) International Business Machines  Corp., 2000,2002&n; *   Modified by Steve French (sfrench@us.ibm.com)&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n;*/
DECL|macro|CIFS_DEBUG
mdefine_line|#define CIFS_DEBUG&t;&t;/* BB temporary */
macro_line|#ifndef _H_CIFS_DEBUG
DECL|macro|_H_CIFS_DEBUG
mdefine_line|#define _H_CIFS_DEBUG
r_void
id|cifs_dump_mem
c_func
(paren
r_char
op_star
id|label
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|traceSMB
suffix:semicolon
multiline_comment|/* flag which enables the function below */
r_void
id|dump_smb
c_func
(paren
r_struct
id|smb_hdr
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;debug ON&n; *&t;--------&n; */
macro_line|#ifdef CIFS_DEBUG
multiline_comment|/* information message: e.g., configuration, major event */
r_extern
r_int
id|cifsFYI
suffix:semicolon
DECL|macro|cifsfyi
mdefine_line|#define cifsfyi(format,arg...) if (cifsFYI) printk(KERN_DEBUG &quot; &quot; __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; &quot;&quot; , ## arg)
DECL|macro|cFYI
mdefine_line|#define cFYI(button,prspec) if (button) cifsfyi prspec
DECL|macro|cifswarn
mdefine_line|#define cifswarn(format, arg...) printk(KERN_WARNING &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
multiline_comment|/* debug event message: */
r_extern
r_int
id|cifsERROR
suffix:semicolon
DECL|macro|cEVENT
mdefine_line|#define cEVENT(format,arg...) if (cifsERROR) printk(KERN_EVENT __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
multiline_comment|/* error event message: e.g., i/o error */
DECL|macro|cifserror
mdefine_line|#define cifserror(format,arg...) if (cifsERROR) printk(KERN_ERR &quot; CIFS VFS: &quot; format &quot;&bslash;n&quot; &quot;&quot; , ## arg)
DECL|macro|cERROR
mdefine_line|#define cERROR(button, prspec) if (button) cifserror prspec
multiline_comment|/*&n; *&t;debug OFF&n; *&t;---------&n; */
macro_line|#else&t;&t;/* _CIFS_DEBUG */
DECL|macro|cERROR
mdefine_line|#define cERROR(button,prspec)
DECL|macro|cEVENT
mdefine_line|#define cEVENT(format,arg...)
DECL|macro|cFYI
mdefine_line|#define cFYI(button, prspec)
DECL|macro|cifserror
mdefine_line|#define cifserror(format,arg...)
macro_line|#endif&t;&t;/* _CIFS_DEBUG */
multiline_comment|/*&n; *&t;statistics&n; *&t;----------&n; */
macro_line|#ifdef&t;_CIFS_STATISTICS
DECL|macro|INCREMENT
mdefine_line|#define&t;INCREMENT(x)&t;((x)++)
DECL|macro|DECREMENT
mdefine_line|#define&t;DECREMENT(x)&t;((x)--)
DECL|macro|HIGHWATERMARK
mdefine_line|#define&t;HIGHWATERMARK(x,y)&t;x = MAX((x), (y))
macro_line|#else
DECL|macro|INCREMENT
mdefine_line|#define&t;INCREMENT(x)
DECL|macro|DECREMENT
mdefine_line|#define&t;DECREMENT(x)
DECL|macro|HIGHWATERMARK
mdefine_line|#define&t;HIGHWATERMARK(x,y)
macro_line|#endif&t;&t;&t;&t;/* _CIFS_STATISTICS */
macro_line|#endif&t;&t;&t;&t;/* _H_CIFS_DEBUG */
eof
