multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;IT8172 system controller specific pci defines.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or support@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _8172PCI_H_
DECL|macro|_8172PCI_H_
mdefine_line|#define _8172PCI_H_
singleline_comment|// PCI configuration space Type0
DECL|macro|PCI_IDREG
mdefine_line|#define&t;PCI_IDREG&t;0x00
DECL|macro|PCI_CMDSTSREG
mdefine_line|#define&t;PCI_CMDSTSREG&t;0x04
DECL|macro|PCI_CLASSREG
mdefine_line|#define&t;PCI_CLASSREG&t;0x08
DECL|macro|PCI_BHLCREG
mdefine_line|#define&t;PCI_BHLCREG&t;0x0C
DECL|macro|PCI_BASE1REG
mdefine_line|#define&t;PCI_BASE1REG&t;0x10
DECL|macro|PCI_BASE2REG
mdefine_line|#define&t;PCI_BASE2REG&t;0x14
DECL|macro|PCI_BASE3REG
mdefine_line|#define&t;PCI_BASE3REG&t;0x18
DECL|macro|PCI_BASE4REG
mdefine_line|#define&t;PCI_BASE4REG&t;0x1C
DECL|macro|PCI_BASE5REG
mdefine_line|#define&t;PCI_BASE5REG&t;0x20
DECL|macro|PCI_BASE6REG
mdefine_line|#define&t;PCI_BASE6REG&t;0x24
DECL|macro|PCI_ROMBASEREG
mdefine_line|#define&t;PCI_ROMBASEREG&t;0x30
DECL|macro|PCI_INTRREG
mdefine_line|#define&t;PCI_INTRREG&t;0x3C
singleline_comment|// PCI configuration space Type1
DECL|macro|PCI_BUSNOREG
mdefine_line|#define&t;PCI_BUSNOREG&t;0x18
DECL|macro|IT_PCI_VENDORID
mdefine_line|#define&t;IT_PCI_VENDORID(x)&t;((x) &amp; 0xFFFF)
DECL|macro|IT_PCI_DEVICEID
mdefine_line|#define&t;IT_PCI_DEVICEID(x)&t;(((x)&gt;&gt;16) &amp; 0xFFFF)
singleline_comment|// Command register
DECL|macro|PCI_CMD_IOEN
mdefine_line|#define&t;PCI_CMD_IOEN&t;&t;0x00000001
DECL|macro|PCI_CMD_MEMEN
mdefine_line|#define&t;PCI_CMD_MEMEN&t;&t;0x00000002
DECL|macro|PCI_CMD_BUSMASTER
mdefine_line|#define&t;PCI_CMD_BUSMASTER&t;0x00000004
DECL|macro|PCI_CMD_SPCYCLE
mdefine_line|#define&t;PCI_CMD_SPCYCLE&t;&t;0x00000008
DECL|macro|PCI_CMD_WRINV
mdefine_line|#define&t;PCI_CMD_WRINV&t;&t;0x00000010
DECL|macro|PCI_CMD_VGASNOOP
mdefine_line|#define&t;PCI_CMD_VGASNOOP&t;0x00000020
DECL|macro|PCI_CMD_PERR
mdefine_line|#define&t;PCI_CMD_PERR&t;&t;0x00000040
DECL|macro|PCI_CMD_WAITCTRL
mdefine_line|#define&t;PCI_CMD_WAITCTRL&t;0x00000080
DECL|macro|PCI_CMD_SERR
mdefine_line|#define&t;PCI_CMD_SERR&t;&t;0x00000100
DECL|macro|PCI_CMD_FAST_BACKTOBACK
mdefine_line|#define&t;PCI_CMD_FAST_BACKTOBACK&t;0x00000200
singleline_comment|// Status register
DECL|macro|PCI_STS_66MHZ
mdefine_line|#define&t;PCI_STS_66MHZ&t;&t;0x00200000
DECL|macro|PCI_STS_SUPPORT_UDF
mdefine_line|#define&t;PCI_STS_SUPPORT_UDF&t;0x00400000
DECL|macro|PCI_STS_FAST_BACKTOBACK
mdefine_line|#define&t;PCI_STS_FAST_BACKTOBACK&t;0x00800000
DECL|macro|PCI_STS_DATA_PERR
mdefine_line|#define&t;PCI_STS_DATA_PERR&t;0x01000000
DECL|macro|PCI_STS_DEVSEL0
mdefine_line|#define&t;PCI_STS_DEVSEL0&t;&t;0x02000000
DECL|macro|PCI_STS_DEVSEL1
mdefine_line|#define&t;PCI_STS_DEVSEL1&t;&t;0x04000000
DECL|macro|PCI_STS_SIG_TGTABORT
mdefine_line|#define&t;PCI_STS_SIG_TGTABORT&t;0x08000000
DECL|macro|PCI_STS_RCV_TGTABORT
mdefine_line|#define&t;PCI_STS_RCV_TGTABORT&t;0x10000000
DECL|macro|PCI_STS_RCV_MSTABORT
mdefine_line|#define&t;PCI_STS_RCV_MSTABORT&t;0x20000000
DECL|macro|PCI_STS_SYSERR
mdefine_line|#define&t;PCI_STS_SYSERR&t;&t;0x40000000
DECL|macro|PCI_STS_DETCT_PERR
mdefine_line|#define&t;PCI_STS_DETCT_PERR&t;0x80000000
DECL|macro|IT_PCI_CLASS
mdefine_line|#define&t;IT_PCI_CLASS(x)&t;&t;(((x)&gt;&gt;24) &amp; 0xFF)
DECL|macro|IT_PCI_SUBCLASS
mdefine_line|#define&t;IT_PCI_SUBCLASS(x)&t;&t;(((x)&gt;&gt;16) &amp; 0xFF)
DECL|macro|IT_PCI_INTERFACE
mdefine_line|#define&t;IT_PCI_INTERFACE(x)&t;(((x)&gt;&gt;8) &amp; 0xFF)
DECL|macro|IT_PCI_REVISION
mdefine_line|#define&t;IT_PCI_REVISION(x)&t;&t;((x) &amp; 0xFF)
singleline_comment|// PCI class code
DECL|macro|PCI_CLASS_BRIDGE
mdefine_line|#define&t;PCI_CLASS_BRIDGE&t;&t;&t;0x06
singleline_comment|// bridge subclass
DECL|macro|PCI_SUBCLASS_BRIDGE_HOST
mdefine_line|#define&t;PCI_SUBCLASS_BRIDGE_HOST&t;&t;0x00
DECL|macro|PCI_SUBCLASS_BRIDGE_PCI
mdefine_line|#define&t;PCI_SUBCLASS_BRIDGE_PCI&t;&t;&t;0x04
singleline_comment|// BHLCREG
DECL|macro|IT_PCI_BIST
mdefine_line|#define&t;IT_PCI_BIST(x)&t;&t;(((x)&gt;&gt;24) &amp; 0xFF)
DECL|macro|IT_PCI_HEADERTYPE
mdefine_line|#define&t;IT_PCI_HEADERTYPE(x)&t;(((x)&gt;&gt;16) &amp; 0xFF)
DECL|macro|IT_PCI_LATENCYTIMER
mdefine_line|#define&t;IT_PCI_LATENCYTIMER(x)&t;(((x)&gt;&gt;8) &amp; 0xFF)
DECL|macro|IT_PCI_CACHELINESIZE
mdefine_line|#define&t;IT_PCI_CACHELINESIZE(x)&t;((x) &amp; 0xFF)
DECL|macro|PCI_MULTIFUNC
mdefine_line|#define&t;PCI_MULTIFUNC&t;0x80
singleline_comment|// INTRREG
DECL|macro|IT_PCI_MAXLAT
mdefine_line|#define&t;IT_PCI_MAXLAT(x)&t;&t;(((x)&gt;&gt;24) &amp; 0xFF)
DECL|macro|IT_PCI_MINGNT
mdefine_line|#define&t;IT_PCI_MINGNT(x)&t;&t;(((x)&gt;&gt;16) &amp; 0xFF)
DECL|macro|IT_PCI_INTRPIN
mdefine_line|#define&t;IT_PCI_INTRPIN(x)&t;&t;(((x)&gt;&gt;8) &amp; 0xFF)
DECL|macro|IT_PCI_INTRLINE
mdefine_line|#define&t;IT_PCI_INTRLINE(x)&t;&t;((x) &amp; 0xFF)
DECL|macro|PCI_VENDOR_NEC
mdefine_line|#define&t;PCI_VENDOR_NEC&t;0x1033
DECL|macro|PCI_VENDOR_DEC
mdefine_line|#define PCI_VENDOR_DEC&t;0x1101
macro_line|#endif 
singleline_comment|// _8172PCI_H_
eof
