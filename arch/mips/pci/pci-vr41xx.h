multiline_comment|/*&n; * FILE NAME&n; *&t;arch/mips/vr41xx/common/pciu.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for PCI Control Unit of the NEC VR4100 series.&n; *&n; * Author: Yoichi Yuasa&n; *         yyuasa@mvista.com or source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * Changes:&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - New creation, NEC VR4122 and VR4131 are supported.&n; */
macro_line|#ifndef __VR41XX_PCIU_H
DECL|macro|__VR41XX_PCIU_H
mdefine_line|#define __VR41XX_PCIU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;(1 &lt;&lt; (x))
DECL|macro|PCIMMAW1REG
mdefine_line|#define PCIMMAW1REG&t;&t;&t;KSEG1ADDR(0x0f000c00)
DECL|macro|PCIMMAW2REG
mdefine_line|#define PCIMMAW2REG&t;&t;&t;KSEG1ADDR(0x0f000c04)
DECL|macro|PCITAW1REG
mdefine_line|#define PCITAW1REG&t;&t;&t;KSEG1ADDR(0x0f000c08)
DECL|macro|PCITAW2REG
mdefine_line|#define PCITAW2REG&t;&t;&t;KSEG1ADDR(0x0f000c0c)
DECL|macro|PCIMIOAWREG
mdefine_line|#define PCIMIOAWREG&t;&t;&t;KSEG1ADDR(0x0f000c10)
DECL|macro|INTERNAL_BUS_BASE_ADDRESS
mdefine_line|#define INTERNAL_BUS_BASE_ADDRESS&t;0xff000000
DECL|macro|ADDRESS_MASK
mdefine_line|#define ADDRESS_MASK&t;&t;&t;0x000fe000
DECL|macro|PCI_ACCESS_ENABLE
mdefine_line|#define PCI_ACCESS_ENABLE&t;&t;BIT(12)
DECL|macro|PCI_ADDRESS_SETTING
mdefine_line|#define PCI_ADDRESS_SETTING&t;&t;0x000000ff
DECL|macro|PCICONFDREG
mdefine_line|#define PCICONFDREG&t;&t;&t;KSEG1ADDR(0x0f000c14)
DECL|macro|PCICONFAREG
mdefine_line|#define PCICONFAREG&t;&t;&t;KSEG1ADDR(0x0f000c18)
DECL|macro|PCIMAILREG
mdefine_line|#define PCIMAILREG&t;&t;&t;KSEG1ADDR(0x0f000c1c)
DECL|macro|BUSERRADREG
mdefine_line|#define BUSERRADREG&t;&t;&t;KSEG1ADDR(0x0f000c24)
DECL|macro|ERROR_ADDRESS
mdefine_line|#define ERROR_ADDRESS&t;&t;&t;0xfffffffc
DECL|macro|INTCNTSTAREG
mdefine_line|#define INTCNTSTAREG&t;&t;&t;KSEG1ADDR(0x0f000c28)
DECL|macro|MABTCLR
mdefine_line|#define MABTCLR&t;&t;&t;&t;BIT(31)
DECL|macro|TRDYCLR
mdefine_line|#define TRDYCLR&t;&t;&t;&t;BIT(30)
DECL|macro|PARCLR
mdefine_line|#define PARCLR&t;&t;&t;&t;BIT(29)
DECL|macro|MBCLR
mdefine_line|#define MBCLR&t;&t;&t;&t;BIT(28)
DECL|macro|SERRCLR
mdefine_line|#define SERRCLR&t;&t;&t;&t;BIT(27)
DECL|macro|PCIEXACCREG
mdefine_line|#define PCIEXACCREG&t;&t;&t;KSEG1ADDR(0x0f000c2c)
DECL|macro|UNLOCK
mdefine_line|#define UNLOCK&t;&t;&t;&t;BIT(1)
DECL|macro|EAREQ
mdefine_line|#define EAREQ&t;&t;&t;&t;BIT(0)
DECL|macro|PCIRECONTREG
mdefine_line|#define PCIRECONTREG&t;&t;&t;KSEG1ADDR(0x0f000c30)
DECL|macro|RTRYCNT
mdefine_line|#define RTRYCNT&t;&t;&t;&t;0x000000ff
DECL|macro|PCIENREG
mdefine_line|#define PCIENREG&t;&t;&t;KSEG1ADDR(0x0f000c34)
DECL|macro|CONFIG_DONE
mdefine_line|#define CONFIG_DONE&t;&t;&t;BIT(2)
DECL|macro|PCICLKSELREG
mdefine_line|#define PCICLKSELREG&t;&t;&t;KSEG1ADDR(0x0f000c38)
DECL|macro|EQUAL_VTCLOCK
mdefine_line|#define EQUAL_VTCLOCK&t;&t;&t;0x00000002
DECL|macro|HALF_VTCLOCK
mdefine_line|#define HALF_VTCLOCK&t;&t;&t;0x00000000
DECL|macro|QUARTER_VTCLOCK
mdefine_line|#define QUARTER_VTCLOCK&t;&t;&t;0x00000001
DECL|macro|PCITRDYVREG
mdefine_line|#define PCITRDYVREG&t;&t;&t;KSEG1ADDR(0x0f000c3c)
DECL|macro|PCICLKRUNREG
mdefine_line|#define PCICLKRUNREG&t;&t;&t;KSEG1ADDR(0x0f000c60)
DECL|macro|PCIU_CONFIGREGS_BASE
mdefine_line|#define PCIU_CONFIGREGS_BASE&t;&t;KSEG1ADDR(0x0f000d00)
DECL|macro|VENDORIDREG
mdefine_line|#define VENDORIDREG&t;&t;&t;KSEG1ADDR(0x0f000d00)
DECL|macro|DEVICEIDREG
mdefine_line|#define DEVICEIDREG&t;&t;&t;KSEG1ADDR(0x0f000d00)
DECL|macro|COMMANDREG
mdefine_line|#define COMMANDREG&t;&t;&t;KSEG1ADDR(0x0f000d04)
DECL|macro|STATUSREG
mdefine_line|#define STATUSREG&t;&t;&t;KSEG1ADDR(0x0f000d04)
DECL|macro|REVIDREG
mdefine_line|#define REVIDREG&t;&t;&t;KSEG1ADDR(0x0f000d08)
DECL|macro|CLASSREG
mdefine_line|#define CLASSREG&t;&t;&t;KSEG1ADDR(0x0f000d08)
DECL|macro|CACHELSREG
mdefine_line|#define CACHELSREG&t;&t;&t;KSEG1ADDR(0x0f000d0c)
DECL|macro|LATTIMEREG
mdefine_line|#define LATTIMEREG&t;&t;&t;KSEG1ADDR(0x0f000d0c)
DECL|macro|MAILBAREG
mdefine_line|#define MAILBAREG&t;&t;&t;KSEG1ADDR(0x0f000d10)
DECL|macro|PCIMBA1REG
mdefine_line|#define PCIMBA1REG&t;&t;&t;KSEG1ADDR(0x0f000d14)
DECL|macro|PCIMBA2REG
mdefine_line|#define PCIMBA2REG&t;&t;&t;KSEG1ADDR(0x0f000d18)
DECL|macro|INTLINEREG
mdefine_line|#define INTLINEREG&t;&t;&t;KSEG1ADDR(0x0f000d3c)
DECL|macro|INTPINREG
mdefine_line|#define INTPINREG&t;&t;&t;KSEG1ADDR(0x0f000d3c)
DECL|macro|RETVALREG
mdefine_line|#define RETVALREG&t;&t;&t;KSEG1ADDR(0x0f000d40)
DECL|macro|PCIAPCNTREG
mdefine_line|#define PCIAPCNTREG&t;&t;&t;KSEG1ADDR(0x0f000d40)
DECL|macro|MPCIINTREG
mdefine_line|#define MPCIINTREG&t;&t;&t;KSEG1ADDR(0x0f0000b2)
DECL|macro|MAX_PCI_CLOCK
mdefine_line|#define MAX_PCI_CLOCK&t;&t;&t;33333333
DECL|macro|PCIU_CLOCK
mdefine_line|#define PCIU_CLOCK&t;&t;&t;0x0080
DECL|macro|PCI_CLOCK
mdefine_line|#define PCI_CLOCK&t;&t;&t;0x2000
DECL|function|pciu_read_config_byte
r_static
r_inline
r_int
id|pciu_read_config_byte
c_func
(paren
r_int
id|where
comma
id|u8
op_star
id|val
)paren
(brace
id|u32
id|data
suffix:semicolon
id|data
op_assign
id|readl
c_func
(paren
id|PCIU_CONFIGREGS_BASE
op_plus
id|where
)paren
suffix:semicolon
op_star
id|val
op_assign
(paren
id|u8
)paren
(paren
id|data
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pciu_read_config_word
r_static
r_inline
r_int
id|pciu_read_config_word
c_func
(paren
r_int
id|where
comma
id|u16
op_star
id|val
)paren
(brace
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|data
op_assign
id|readl
c_func
(paren
id|PCIU_CONFIGREGS_BASE
op_plus
id|where
)paren
suffix:semicolon
op_star
id|val
op_assign
(paren
id|u16
)paren
(paren
id|data
op_rshift
(paren
(paren
id|where
op_amp
l_int|2
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pciu_read_config_dword
r_static
r_inline
r_int
id|pciu_read_config_dword
c_func
(paren
r_int
id|where
comma
id|u32
op_star
id|val
)paren
(brace
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
id|val
op_assign
id|readl
c_func
(paren
id|PCIU_CONFIGREGS_BASE
op_plus
id|where
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pciu_write_config_byte
r_static
r_inline
r_int
id|pciu_write_config_byte
c_func
(paren
r_int
id|where
comma
id|u8
id|val
)paren
(brace
id|writel
c_func
(paren
id|val
comma
id|PCIU_CONFIGREGS_BASE
op_plus
id|where
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pciu_write_config_word
r_static
r_inline
r_int
id|pciu_write_config_word
c_func
(paren
r_int
id|where
comma
id|u16
id|val
)paren
(brace
id|writel
c_func
(paren
id|val
comma
id|PCIU_CONFIGREGS_BASE
op_plus
id|where
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pciu_write_config_dword
r_static
r_inline
r_int
id|pciu_write_config_dword
c_func
(paren
r_int
id|where
comma
id|u32
id|val
)paren
(brace
id|writel
c_func
(paren
id|val
comma
id|PCIU_CONFIGREGS_BASE
op_plus
id|where
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* __VR41XX_PCIU_H */
eof
