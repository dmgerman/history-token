macro_line|#ifndef __YENTA_H
DECL|macro|__YENTA_H
mdefine_line|#define __YENTA_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;pci_socket.h&quot;
DECL|macro|CB_SOCKET_EVENT
mdefine_line|#define CB_SOCKET_EVENT&t;&t;0x00
DECL|macro|CB_CSTSEVENT
mdefine_line|#define    CB_CSTSEVENT&t;&t;0x00000001&t;/* Card status event */
DECL|macro|CB_CD1EVENT
mdefine_line|#define    CB_CD1EVENT&t;&t;0x00000002&t;/* Card detect 1 change event */
DECL|macro|CB_CD2EVENT
mdefine_line|#define    CB_CD2EVENT&t;&t;0x00000004&t;/* Card detect 2 change event */
DECL|macro|CB_PWREVENT
mdefine_line|#define    CB_PWREVENT&t;&t;0x00000008&t;/* PWRCYCLE change event */
DECL|macro|CB_SOCKET_MASK
mdefine_line|#define CB_SOCKET_MASK&t;&t;0x04
DECL|macro|CB_CSTSMASK
mdefine_line|#define    CB_CSTSMASK&t;&t;0x00000001&t;/* Card status mask */
DECL|macro|CB_CDMASK
mdefine_line|#define    CB_CDMASK&t;&t;0x00000006&t;/* Card detect 1&amp;2 mask */
DECL|macro|CB_PWRMASK
mdefine_line|#define    CB_PWRMASK&t;&t;0x00000008&t;/* PWRCYCLE change mask */
DECL|macro|CB_SOCKET_STATE
mdefine_line|#define CB_SOCKET_STATE&t;&t;0x08
DECL|macro|CB_CARDSTS
mdefine_line|#define    CB_CARDSTS&t;&t;0x00000001&t;/* CSTSCHG status */
DECL|macro|CB_CDETECT1
mdefine_line|#define    CB_CDETECT1&t;&t;0x00000002&t;/* Card detect status 1 */
DECL|macro|CB_CDETECT2
mdefine_line|#define    CB_CDETECT2&t;&t;0x00000004&t;/* Card detect status 2 */
DECL|macro|CB_PWRCYCLE
mdefine_line|#define    CB_PWRCYCLE&t;&t;0x00000008&t;/* Socket powered */
DECL|macro|CB_16BITCARD
mdefine_line|#define    CB_16BITCARD&t;&t;0x00000010&t;/* 16-bit card detected */
DECL|macro|CB_CBCARD
mdefine_line|#define    CB_CBCARD&t;&t;0x00000020&t;/* CardBus card detected */
DECL|macro|CB_IREQCINT
mdefine_line|#define    CB_IREQCINT&t;&t;0x00000040&t;/* READY(xIRQ)/xCINT high */
DECL|macro|CB_NOTACARD
mdefine_line|#define    CB_NOTACARD&t;&t;0x00000080&t;/* Unrecognizable PC card detected */
DECL|macro|CB_DATALOST
mdefine_line|#define    CB_DATALOST&t;&t;0x00000100&t;/* Potential data loss due to card removal */
DECL|macro|CB_BADVCCREQ
mdefine_line|#define    CB_BADVCCREQ&t;&t;0x00000200&t;/* Invalid Vcc request by host software */
DECL|macro|CB_5VCARD
mdefine_line|#define    CB_5VCARD&t;&t;0x00000400&t;/* Card Vcc at 5.0 volts? */
DECL|macro|CB_3VCARD
mdefine_line|#define    CB_3VCARD&t;&t;0x00000800&t;/* Card Vcc at 3.3 volts? */
DECL|macro|CB_XVCARD
mdefine_line|#define    CB_XVCARD&t;&t;0x00001000&t;/* Card Vcc at X.X volts? */
DECL|macro|CB_YVCARD
mdefine_line|#define    CB_YVCARD&t;&t;0x00002000&t;/* Card Vcc at Y.Y volts? */
DECL|macro|CB_5VSOCKET
mdefine_line|#define    CB_5VSOCKET&t;&t;0x10000000&t;/* Socket Vcc at 5.0 volts? */
DECL|macro|CB_3VSOCKET
mdefine_line|#define    CB_3VSOCKET&t;&t;0x20000000&t;/* Socket Vcc at 3.3 volts? */
DECL|macro|CB_XVSOCKET
mdefine_line|#define    CB_XVSOCKET&t;&t;0x40000000&t;/* Socket Vcc at X.X volts? */
DECL|macro|CB_YVSOCKET
mdefine_line|#define    CB_YVSOCKET&t;&t;0x80000000&t;/* Socket Vcc at Y.Y volts? */
DECL|macro|CB_SOCKET_FORCE
mdefine_line|#define CB_SOCKET_FORCE&t;&t;0x0C
DECL|macro|CB_FCARDSTS
mdefine_line|#define    CB_FCARDSTS&t;&t;0x00000001&t;/* Force CSTSCHG */
DECL|macro|CB_FCDETECT1
mdefine_line|#define    CB_FCDETECT1&t;&t;0x00000002&t;/* Force CD1EVENT */
DECL|macro|CB_FCDETECT2
mdefine_line|#define    CB_FCDETECT2&t;&t;0x00000004&t;/* Force CD2EVENT */
DECL|macro|CB_FPWRCYCLE
mdefine_line|#define    CB_FPWRCYCLE&t;&t;0x00000008&t;/* Force PWREVENT */
DECL|macro|CB_F16BITCARD
mdefine_line|#define    CB_F16BITCARD&t;0x00000010&t;/* Force 16-bit PCMCIA card */
DECL|macro|CB_FCBCARD
mdefine_line|#define    CB_FCBCARD&t;&t;0x00000020&t;/* Force CardBus line */
DECL|macro|CB_FNOTACARD
mdefine_line|#define    CB_FNOTACARD&t;&t;0x00000080&t;/* Force NOTACARD */
DECL|macro|CB_FDATALOST
mdefine_line|#define    CB_FDATALOST&t;&t;0x00000100&t;/* Force data lost */
DECL|macro|CB_FBADVCCREQ
mdefine_line|#define    CB_FBADVCCREQ&t;0x00000200&t;/* Force bad Vcc request */
DECL|macro|CB_F5VCARD
mdefine_line|#define    CB_F5VCARD&t;&t;0x00000400&t;/* Force 5.0 volt card */
DECL|macro|CB_F3VCARD
mdefine_line|#define    CB_F3VCARD&t;&t;0x00000800&t;/* Force 3.3 volt card */
DECL|macro|CB_FXVCARD
mdefine_line|#define    CB_FXVCARD&t;&t;0x00001000&t;/* Force X.X volt card */
DECL|macro|CB_FYVCARD
mdefine_line|#define    CB_FYVCARD&t;&t;0x00002000&t;/* Force Y.Y volt card */
DECL|macro|CB_CVSTEST
mdefine_line|#define    CB_CVSTEST&t;&t;0x00004000&t;/* Card VS test */
DECL|macro|CB_SOCKET_CONTROL
mdefine_line|#define CB_SOCKET_CONTROL&t;0x10
DECL|macro|CB_SC_VPP_MASK
mdefine_line|#define  CB_SC_VPP_MASK&t;&t;0x00000007
DECL|macro|CB_SC_VPP_OFF
mdefine_line|#define   CB_SC_VPP_OFF&t;&t;0x00000000
DECL|macro|CB_SC_VPP_12V
mdefine_line|#define   CB_SC_VPP_12V&t;&t;0x00000001
DECL|macro|CB_SC_VPP_5V
mdefine_line|#define   CB_SC_VPP_5V&t;&t;0x00000002
DECL|macro|CB_SC_VPP_3V
mdefine_line|#define   CB_SC_VPP_3V&t;&t;0x00000003
DECL|macro|CB_SC_VPP_XV
mdefine_line|#define   CB_SC_VPP_XV&t;&t;0x00000004
DECL|macro|CB_SC_VPP_YV
mdefine_line|#define   CB_SC_VPP_YV&t;&t;0x00000005
DECL|macro|CB_SC_VCC_MASK
mdefine_line|#define  CB_SC_VCC_MASK&t;&t;0x00000070
DECL|macro|CB_SC_VCC_OFF
mdefine_line|#define   CB_SC_VCC_OFF&t;&t;0x00000000
DECL|macro|CB_SC_VCC_5V
mdefine_line|#define   CB_SC_VCC_5V&t;&t;0x00000020
DECL|macro|CB_SC_VCC_3V
mdefine_line|#define   CB_SC_VCC_3V&t;&t;0x00000030
DECL|macro|CB_SC_VCC_XV
mdefine_line|#define   CB_SC_VCC_XV&t;&t;0x00000040
DECL|macro|CB_SC_VCC_YV
mdefine_line|#define   CB_SC_VCC_YV&t;&t;0x00000050
DECL|macro|CB_SC_CCLK_STOP
mdefine_line|#define  CB_SC_CCLK_STOP&t;0x00000080
DECL|macro|CB_SOCKET_POWER
mdefine_line|#define CB_SOCKET_POWER&t;&t;0x20
DECL|macro|CB_SKTACCES
mdefine_line|#define    CB_SKTACCES&t;&t;0x02000000&t;/* A PC card access has occurred (clear on read) */
DECL|macro|CB_SKTMODE
mdefine_line|#define    CB_SKTMODE&t;&t;0x01000000&t;/* Clock frequency has changed (clear on read) */
DECL|macro|CB_CLKCTRLEN
mdefine_line|#define    CB_CLKCTRLEN&t;&t;0x00010000&t;/* Clock control enabled (RW) */
DECL|macro|CB_CLKCTRL
mdefine_line|#define    CB_CLKCTRL&t;&t;0x00000001&t;/* Stop(0) or slow(1) CB clock (RW) */
multiline_comment|/*&n; * Cardbus configuration space&n; */
DECL|macro|CB_BRIDGE_BASE
mdefine_line|#define CB_BRIDGE_BASE(m)&t;(0x1c + 8*(m))
DECL|macro|CB_BRIDGE_LIMIT
mdefine_line|#define CB_BRIDGE_LIMIT(m)&t;(0x20 + 8*(m))
DECL|macro|CB_BRIDGE_CONTROL
mdefine_line|#define CB_BRIDGE_CONTROL&t;0x3e
DECL|macro|CB_BRIDGE_CPERREN
mdefine_line|#define   CB_BRIDGE_CPERREN&t;0x00000001
DECL|macro|CB_BRIDGE_CSERREN
mdefine_line|#define   CB_BRIDGE_CSERREN&t;0x00000002
DECL|macro|CB_BRIDGE_ISAEN
mdefine_line|#define   CB_BRIDGE_ISAEN&t;0x00000004
DECL|macro|CB_BRIDGE_VGAEN
mdefine_line|#define   CB_BRIDGE_VGAEN&t;0x00000008
DECL|macro|CB_BRIDGE_MABTMODE
mdefine_line|#define   CB_BRIDGE_MABTMODE&t;0x00000020
DECL|macro|CB_BRIDGE_CRST
mdefine_line|#define   CB_BRIDGE_CRST&t;0x00000040
DECL|macro|CB_BRIDGE_INTR
mdefine_line|#define   CB_BRIDGE_INTR&t;0x00000080
DECL|macro|CB_BRIDGE_PREFETCH0
mdefine_line|#define   CB_BRIDGE_PREFETCH0&t;0x00000100
DECL|macro|CB_BRIDGE_PREFETCH1
mdefine_line|#define   CB_BRIDGE_PREFETCH1&t;0x00000200
DECL|macro|CB_BRIDGE_POSTEN
mdefine_line|#define   CB_BRIDGE_POSTEN&t;0x00000400
DECL|macro|CB_LEGACY_MODE_BASE
mdefine_line|#define CB_LEGACY_MODE_BASE&t;0x44
multiline_comment|/*&n; * ExCA area extensions in Yenta&n; */
DECL|macro|CB_MEM_PAGE
mdefine_line|#define CB_MEM_PAGE(map)&t;(0x40 + (map))
macro_line|#endif
eof
