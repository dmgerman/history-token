multiline_comment|/*&n; * smc34c90.h 1.7 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_SMC34C90_H
DECL|macro|_LINUX_SMC34C90_H
mdefine_line|#define _LINUX_SMC34C90_H
macro_line|#ifndef PCI_VENDOR_ID_SMC
DECL|macro|PCI_VENDOR_ID_SMC
mdefine_line|#define PCI_VENDOR_ID_SMC&t;&t;0x10b3
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SMC_34C90
DECL|macro|PCI_DEVICE_ID_SMC_34C90
mdefine_line|#define PCI_DEVICE_ID_SMC_34C90&t;&t;0xb106
macro_line|#endif
multiline_comment|/* Register definitions for SMC 34C90 PCI-to-CardBus bridge */
multiline_comment|/* EEPROM Information Register */
DECL|macro|SMC34C90_EEINFO
mdefine_line|#define SMC34C90_EEINFO&t;&t;&t;0x0088
DECL|macro|SMC34C90_EEINFO_ONE_SOCKET
mdefine_line|#define SMC34C90_EEINFO_ONE_SOCKET&t;0x0001
DECL|macro|SMC34C90_EEINFO_5V_ONLY
mdefine_line|#define SMC34C90_EEINFO_5V_ONLY&t;&t;0x0002
DECL|macro|SMC34C90_EEINFO_ISA_IRQ
mdefine_line|#define SMC34C90_EEINFO_ISA_IRQ&t;&t;0x0004
DECL|macro|SMC34C90_EEINFO_ZV_PORT
mdefine_line|#define SMC34C90_EEINFO_ZV_PORT&t;&t;0x0008
DECL|macro|SMC34C90_EEINFO_RING
mdefine_line|#define SMC34C90_EEINFO_RING&t;&t;0x0010
DECL|macro|SMC34C90_EEINFO_LED
mdefine_line|#define SMC34C90_EEINFO_LED&t;&t;0x0020
macro_line|#endif /* _LINUX_SMC34C90_H */
eof
