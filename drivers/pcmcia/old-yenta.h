multiline_comment|/*&n; * yenta.h 1.16 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_YENTA_H
DECL|macro|_LINUX_YENTA_H
mdefine_line|#define _LINUX_YENTA_H
multiline_comment|/* PCI Configuration Registers */
DECL|macro|PCI_STATUS_CAPLIST
mdefine_line|#define PCI_STATUS_CAPLIST&t;&t;0x10
DECL|macro|PCI_CB_CAPABILITY_POINTER
mdefine_line|#define PCI_CB_CAPABILITY_POINTER&t;0x14&t;/* 8 bit */
DECL|macro|PCI_CAPABILITY_ID
mdefine_line|#define PCI_CAPABILITY_ID&t;&t;0x00&t;/* 8 bit */
DECL|macro|PCI_CAPABILITY_PM
mdefine_line|#define  PCI_CAPABILITY_PM&t;&t;0x01
DECL|macro|PCI_NEXT_CAPABILITY
mdefine_line|#define PCI_NEXT_CAPABILITY&t;&t;0x01&t;/* 8 bit */
DECL|macro|PCI_PM_CAPABILITIES
mdefine_line|#define PCI_PM_CAPABILITIES&t;&t;0x02&t;/* 16 bit */
DECL|macro|PCI_PMCAP_PME_D3COLD
mdefine_line|#define  PCI_PMCAP_PME_D3COLD&t;&t;0x8000
DECL|macro|PCI_PMCAP_PME_D3HOT
mdefine_line|#define  PCI_PMCAP_PME_D3HOT&t;&t;0x4000
DECL|macro|PCI_PMCAP_PME_D2
mdefine_line|#define  PCI_PMCAP_PME_D2&t;&t;0x2000
DECL|macro|PCI_PMCAP_PME_D1
mdefine_line|#define  PCI_PMCAP_PME_D1&t;&t;0x1000
DECL|macro|PCI_PMCAP_PME_D0
mdefine_line|#define  PCI_PMCAP_PME_D0&t;&t;0x0800
DECL|macro|PCI_PMCAP_D2_CAP
mdefine_line|#define  PCI_PMCAP_D2_CAP&t;&t;0x0400
DECL|macro|PCI_PMCAP_D1_CAP
mdefine_line|#define  PCI_PMCAP_D1_CAP&t;&t;0x0200
DECL|macro|PCI_PMCAP_DYN_DATA
mdefine_line|#define  PCI_PMCAP_DYN_DATA&t;&t;0x0100
DECL|macro|PCI_PMCAP_DSI
mdefine_line|#define  PCI_PMCAP_DSI&t;&t;&t;0x0020
DECL|macro|PCI_PMCAP_AUX_PWR
mdefine_line|#define  PCI_PMCAP_AUX_PWR&t;&t;0x0010
DECL|macro|PCI_PMCAP_PMECLK
mdefine_line|#define  PCI_PMCAP_PMECLK&t;&t;0x0008
DECL|macro|PCI_PMCAP_VERSION_MASK
mdefine_line|#define  PCI_PMCAP_VERSION_MASK&t;&t;0x0007
DECL|macro|PCI_PM_CONTROL_STATUS
mdefine_line|#define PCI_PM_CONTROL_STATUS&t;&t;0x04&t;/* 16 bit */
DECL|macro|PCI_PMCS_PME_STATUS
mdefine_line|#define  PCI_PMCS_PME_STATUS&t;&t;0x8000
DECL|macro|PCI_PMCS_DATASCALE_MASK
mdefine_line|#define  PCI_PMCS_DATASCALE_MASK&t;0x6000
DECL|macro|PCI_PMCS_DATASCALE_SHIFT
mdefine_line|#define  PCI_PMCS_DATASCALE_SHIFT&t;13
DECL|macro|PCI_PMCS_DATASEL_MASK
mdefine_line|#define  PCI_PMCS_DATASEL_MASK&t;&t;0x1e00
DECL|macro|PCI_PMCS_DATASEL_SHIFT
mdefine_line|#define  PCI_PMCS_DATASEL_SHIFT&t;&t;9
DECL|macro|PCI_PMCS_PME_ENABLE
mdefine_line|#define  PCI_PMCS_PME_ENABLE&t;&t;0x0100
DECL|macro|PCI_PMCS_PWR_STATE_MASK
mdefine_line|#define  PCI_PMCS_PWR_STATE_MASK&t;0x0003
DECL|macro|PCI_PMCS_PWR_STATE_D0
mdefine_line|#define  PCI_PMCS_PWR_STATE_D0&t;&t;0x0000
DECL|macro|PCI_PMCS_PWR_STATE_D1
mdefine_line|#define  PCI_PMCS_PWR_STATE_D1&t;&t;0x0001
DECL|macro|PCI_PMCS_PWR_STATE_D2
mdefine_line|#define  PCI_PMCS_PWR_STATE_D2&t;&t;0x0002
DECL|macro|PCI_PMCS_PWR_STATE_D3
mdefine_line|#define  PCI_PMCS_PWR_STATE_D3&t;&t;0x0003
DECL|macro|PCI_PM_BRIDGE_EXT
mdefine_line|#define PCI_PM_BRIDGE_EXT&t;&t;0x06&t;/* 8 bit */
DECL|macro|PCI_PM_DATA
mdefine_line|#define PCI_PM_DATA&t;&t;&t;0x07&t;/* 8 bit */
DECL|macro|CB_PRIMARY_BUS
mdefine_line|#define CB_PRIMARY_BUS&t;&t;&t;0x18&t;/* 8 bit */
DECL|macro|CB_CARDBUS_BUS
mdefine_line|#define CB_CARDBUS_BUS&t;&t;&t;0x19&t;/* 8 bit */
DECL|macro|CB_SUBORD_BUS
mdefine_line|#define CB_SUBORD_BUS&t;&t;&t;0x1a&t;/* 8 bit */
DECL|macro|CB_LATENCY_TIMER
mdefine_line|#define CB_LATENCY_TIMER&t;&t;0x1b&t;/* 8 bit */
DECL|macro|CB_MEM_BASE
mdefine_line|#define CB_MEM_BASE(m)&t;&t;&t;(0x1c + 8*(m))
DECL|macro|CB_MEM_LIMIT
mdefine_line|#define CB_MEM_LIMIT(m)&t;&t;&t;(0x20 + 8*(m))
DECL|macro|CB_IO_BASE
mdefine_line|#define CB_IO_BASE(m)&t;&t;&t;(0x2c + 8*(m))
DECL|macro|CB_IO_LIMIT
mdefine_line|#define CB_IO_LIMIT(m)&t;&t;&t;(0x30 + 8*(m))
DECL|macro|CB_BRIDGE_CONTROL
mdefine_line|#define CB_BRIDGE_CONTROL&t;&t;0x3e&t;/* 16 bit */
DECL|macro|CB_BCR_PARITY_ENA
mdefine_line|#define  CB_BCR_PARITY_ENA&t;&t;0x0001
DECL|macro|CB_BCR_SERR_ENA
mdefine_line|#define  CB_BCR_SERR_ENA&t;&t;0x0002
DECL|macro|CB_BCR_ISA_ENA
mdefine_line|#define  CB_BCR_ISA_ENA&t;&t;&t;0x0004
DECL|macro|CB_BCR_VGA_ENA
mdefine_line|#define  CB_BCR_VGA_ENA&t;&t;&t;0x0008
DECL|macro|CB_BCR_MABORT
mdefine_line|#define  CB_BCR_MABORT&t;&t;&t;0x0020
DECL|macro|CB_BCR_CB_RESET
mdefine_line|#define  CB_BCR_CB_RESET&t;&t;0x0040
DECL|macro|CB_BCR_ISA_IRQ
mdefine_line|#define  CB_BCR_ISA_IRQ&t;&t;&t;0x0080
DECL|macro|CB_BCR_PREFETCH
mdefine_line|#define  CB_BCR_PREFETCH(m)&t;&t;(0x0100 &lt;&lt; (m))
DECL|macro|CB_BCR_WRITE_POST
mdefine_line|#define  CB_BCR_WRITE_POST&t;&t;0x0400
DECL|macro|CB_LEGACY_MODE_BASE
mdefine_line|#define CB_LEGACY_MODE_BASE&t;&t;0x44
multiline_comment|/* Memory mapped registers */
DECL|macro|CB_SOCKET_EVENT
mdefine_line|#define CB_SOCKET_EVENT&t;&t;&t;0x0000
DECL|macro|CB_SE_CSTSCHG
mdefine_line|#define  CB_SE_CSTSCHG&t;&t;&t;0x00000001
DECL|macro|CB_SE_CCD1
mdefine_line|#define  CB_SE_CCD1&t;&t;&t;0x00000002
DECL|macro|CB_SE_CCD2
mdefine_line|#define  CB_SE_CCD2&t;&t;&t;0x00000004
DECL|macro|CB_SE_PWRCYCLE
mdefine_line|#define  CB_SE_PWRCYCLE&t;&t;&t;0x00000008
DECL|macro|CB_SOCKET_MASK
mdefine_line|#define CB_SOCKET_MASK&t;&t;&t;0x0004
DECL|macro|CB_SM_CSTSCHG
mdefine_line|#define  CB_SM_CSTSCHG&t;&t;&t;0x00000001
DECL|macro|CB_SM_CCD
mdefine_line|#define  CB_SM_CCD&t;&t;&t;0x00000006
DECL|macro|CB_SM_PWRCYCLE
mdefine_line|#define  CB_SM_PWRCYCLE&t;&t;&t;0x00000008
DECL|macro|CB_SOCKET_STATE
mdefine_line|#define CB_SOCKET_STATE&t;&t;&t;0x0008
DECL|macro|CB_SS_CSTSCHG
mdefine_line|#define  CB_SS_CSTSCHG&t;&t;&t;0x00000001
DECL|macro|CB_SS_CCD1
mdefine_line|#define  CB_SS_CCD1&t;&t;&t;0x00000002
DECL|macro|CB_SS_CCD2
mdefine_line|#define  CB_SS_CCD2&t;&t;&t;0x00000004
DECL|macro|CB_SS_PWRCYCLE
mdefine_line|#define  CB_SS_PWRCYCLE&t;&t;&t;0x00000008
DECL|macro|CB_SS_16BIT
mdefine_line|#define  CB_SS_16BIT&t;&t;&t;0x00000010
DECL|macro|CB_SS_32BIT
mdefine_line|#define  CB_SS_32BIT&t;&t;&t;0x00000020
DECL|macro|CB_SS_CINT
mdefine_line|#define  CB_SS_CINT&t;&t;&t;0x00000040
DECL|macro|CB_SS_BADCARD
mdefine_line|#define  CB_SS_BADCARD&t;&t;&t;0x00000080
DECL|macro|CB_SS_DATALOST
mdefine_line|#define  CB_SS_DATALOST&t;&t;&t;0x00000100
DECL|macro|CB_SS_BADVCC
mdefine_line|#define  CB_SS_BADVCC&t;&t;&t;0x00000200
DECL|macro|CB_SS_5VCARD
mdefine_line|#define  CB_SS_5VCARD&t;&t;&t;0x00000400
DECL|macro|CB_SS_3VCARD
mdefine_line|#define  CB_SS_3VCARD&t;&t;&t;0x00000800
DECL|macro|CB_SS_XVCARD
mdefine_line|#define  CB_SS_XVCARD&t;&t;&t;0x00001000
DECL|macro|CB_SS_YVCARD
mdefine_line|#define  CB_SS_YVCARD&t;&t;&t;0x00002000
DECL|macro|CB_SS_5VSOCKET
mdefine_line|#define  CB_SS_5VSOCKET&t;&t;&t;0x10000000
DECL|macro|CB_SS_3VSOCKET
mdefine_line|#define  CB_SS_3VSOCKET&t;&t;&t;0x20000000
DECL|macro|CB_SS_XVSOCKET
mdefine_line|#define  CB_SS_XVSOCKET&t;&t;&t;0x40000000
DECL|macro|CB_SS_YVSOCKET
mdefine_line|#define  CB_SS_YVSOCKET&t;&t;&t;0x80000000
DECL|macro|CB_SOCKET_FORCE
mdefine_line|#define CB_SOCKET_FORCE&t;&t;&t;0x000c
DECL|macro|CB_SF_CVSTEST
mdefine_line|#define  CB_SF_CVSTEST&t;&t;&t;0x00004000
DECL|macro|CB_SOCKET_CONTROL
mdefine_line|#define CB_SOCKET_CONTROL&t;&t;0x0010
DECL|macro|CB_SC_VPP_MASK
mdefine_line|#define  CB_SC_VPP_MASK&t;&t;&t;0x00000007
DECL|macro|CB_SC_VPP_OFF
mdefine_line|#define   CB_SC_VPP_OFF&t;&t;&t;0x00000000
DECL|macro|CB_SC_VPP_12V
mdefine_line|#define   CB_SC_VPP_12V&t;&t;&t;0x00000001
DECL|macro|CB_SC_VPP_5V
mdefine_line|#define   CB_SC_VPP_5V&t;&t;&t;0x00000002
DECL|macro|CB_SC_VPP_3V
mdefine_line|#define   CB_SC_VPP_3V&t;&t;&t;0x00000003
DECL|macro|CB_SC_VPP_XV
mdefine_line|#define   CB_SC_VPP_XV&t;&t;&t;0x00000004
DECL|macro|CB_SC_VPP_YV
mdefine_line|#define   CB_SC_VPP_YV&t;&t;&t;0x00000005
DECL|macro|CB_SC_VCC_MASK
mdefine_line|#define  CB_SC_VCC_MASK&t;&t;&t;0x00000070
DECL|macro|CB_SC_VCC_OFF
mdefine_line|#define   CB_SC_VCC_OFF&t;&t;&t;0x00000000
DECL|macro|CB_SC_VCC_5V
mdefine_line|#define   CB_SC_VCC_5V&t;&t;&t;0x00000020
DECL|macro|CB_SC_VCC_3V
mdefine_line|#define   CB_SC_VCC_3V&t;&t;&t;0x00000030
DECL|macro|CB_SC_VCC_XV
mdefine_line|#define   CB_SC_VCC_XV&t;&t;&t;0x00000040
DECL|macro|CB_SC_VCC_YV
mdefine_line|#define   CB_SC_VCC_YV&t;&t;&t;0x00000050
DECL|macro|CB_SC_CCLK_STOP
mdefine_line|#define  CB_SC_CCLK_STOP&t;&t;0x00000080
DECL|macro|CB_SOCKET_POWER
mdefine_line|#define CB_SOCKET_POWER&t;&t;&t;0x0020
DECL|macro|CB_SP_CLK_CTRL
mdefine_line|#define  CB_SP_CLK_CTRL&t;&t;&t;0x00000001
DECL|macro|CB_SP_CLK_CTRL_ENA
mdefine_line|#define  CB_SP_CLK_CTRL_ENA&t;&t;0x00010000
DECL|macro|CB_SP_CLK_MODE
mdefine_line|#define  CB_SP_CLK_MODE&t;&t;&t;0x01000000
DECL|macro|CB_SP_ACCESS
mdefine_line|#define  CB_SP_ACCESS&t;&t;&t;0x02000000
multiline_comment|/* Address bits 31..24 for memory windows for 16-bit cards,&n;   accessable only by memory mapping the 16-bit register set */
DECL|macro|CB_MEM_PAGE
mdefine_line|#define CB_MEM_PAGE(map)&t;&t;(0x40 + (map))
macro_line|#endif /* _LINUX_YENTA_H */
eof
