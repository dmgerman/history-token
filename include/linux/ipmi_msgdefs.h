multiline_comment|/*&n; * ipmi_smi.h&n; *&n; * MontaVista IPMI system management interface&n; *&n; * Author: MontaVista Software, Inc.&n; *         Corey Minyard &lt;minyard@mvista.com&gt;&n; *         source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_IPMI_MSGDEFS_H
DECL|macro|__LINUX_IPMI_MSGDEFS_H
mdefine_line|#define __LINUX_IPMI_MSGDEFS_H
multiline_comment|/* Various definitions for IPMI messages used by almost everything in&n;   the IPMI stack. */
DECL|macro|IPMI_NETFN_APP_REQUEST
mdefine_line|#define IPMI_NETFN_APP_REQUEST&t;0x06
DECL|macro|IPMI_NETFN_APP_RESPONSE
mdefine_line|#define IPMI_NETFN_APP_RESPONSE&t;0x07
DECL|macro|IPMI_BMC_SLAVE_ADDR
mdefine_line|#define IPMI_BMC_SLAVE_ADDR&t;0x20
DECL|macro|IPMI_GET_DEVICE_ID_CMD
mdefine_line|#define IPMI_GET_DEVICE_ID_CMD&t;&t;0x01
DECL|macro|IPMI_CLEAR_MSG_FLAGS_CMD
mdefine_line|#define IPMI_CLEAR_MSG_FLAGS_CMD&t;0x30
DECL|macro|IPMI_GET_MSG_FLAGS_CMD
mdefine_line|#define IPMI_GET_MSG_FLAGS_CMD&t;&t;0x31
DECL|macro|IPMI_SEND_MSG_CMD
mdefine_line|#define IPMI_SEND_MSG_CMD&t;&t;0x34
DECL|macro|IPMI_GET_MSG_CMD
mdefine_line|#define IPMI_GET_MSG_CMD&t;&t;0x33
DECL|macro|IPMI_SET_BMC_GLOBAL_ENABLES_CMD
mdefine_line|#define IPMI_SET_BMC_GLOBAL_ENABLES_CMD&t;0x2e
DECL|macro|IPMI_GET_BMC_GLOBAL_ENABLES_CMD
mdefine_line|#define IPMI_GET_BMC_GLOBAL_ENABLES_CMD&t;0x2f
DECL|macro|IPMI_READ_EVENT_MSG_BUFFER_CMD
mdefine_line|#define IPMI_READ_EVENT_MSG_BUFFER_CMD&t;0x35
DECL|macro|IPMI_MAX_MSG_LENGTH
mdefine_line|#define IPMI_MAX_MSG_LENGTH&t;80
macro_line|#endif /* __LINUX_IPMI_MSGDEFS_H */
eof
