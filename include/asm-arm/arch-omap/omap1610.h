multiline_comment|/* linux/include/asm-arm/arch-omap/omap1610.h&n; *&n; * Hardware definitions for TI OMAP1610 processor.&n; *&n; * Cleanup for Linux-2.6 by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP1610_H
DECL|macro|__ASM_ARCH_OMAP1610_H
mdefine_line|#define __ASM_ARCH_OMAP1610_H
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Base addresses&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */
DECL|macro|OMAP_SRAM_BASE
mdefine_line|#define OMAP_SRAM_BASE&t;&t;0xD0000000
DECL|macro|OMAP_SRAM_SIZE
mdefine_line|#define OMAP_SRAM_SIZE&t;&t;(SZ_16K)
DECL|macro|OMAP_SRAM_START
mdefine_line|#define OMAP_SRAM_START&t;&t;0x20000000
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * System control registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP_RESET_CONTROL
mdefine_line|#define OMAP_RESET_CONTROL&t;0xfffe1140
DECL|macro|ARM_IDLECT3
mdefine_line|#define ARM_IDLECT3&t;&t;(CLKGEN_RESET_BASE + 0x24)
DECL|macro|CONF_VOLTAGE_CTRL_0
mdefine_line|#define CONF_VOLTAGE_CTRL_0&t;0xfffe1060
DECL|macro|CONF_VOLTAGE_VDDSHV6
mdefine_line|#define CONF_VOLTAGE_VDDSHV6&t;(1 &lt;&lt; 8)
DECL|macro|CONF_VOLTAGE_VDDSHV7
mdefine_line|#define CONF_VOLTAGE_VDDSHV7&t;(1 &lt;&lt; 9)
DECL|macro|CONF_VOLTAGE_VDDSHV8
mdefine_line|#define CONF_VOLTAGE_VDDSHV8&t;(1 &lt;&lt; 10)
DECL|macro|CONF_VOLTAGE_VDDSHV9
mdefine_line|#define CONF_VOLTAGE_VDDSHV9&t;(1 &lt;&lt; 11)
DECL|macro|SUBLVDS_CONF_VALID
mdefine_line|#define SUBLVDS_CONF_VALID&t;(1 &lt;&lt; 13)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * TIPB bus interface&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP_TIPB_SWITCH
mdefine_line|#define OMAP_TIPB_SWITCH&t;0xfffbc800
DECL|macro|TIPB_BRIDGE_INT
mdefine_line|#define TIPB_BRIDGE_INT&t;&t;0xfffeca00&t;/* Private TIPB_CNTL */
DECL|macro|PRIVATE_MPU_TIPB_CNTL
mdefine_line|#define PRIVATE_MPU_TIPB_CNTL&t;0xfffeca08
DECL|macro|TIPB_BRIDGE_EXT
mdefine_line|#define TIPB_BRIDGE_EXT&t;&t;0xfffed300&t;/* Public (Shared) TIPB_CNTL */
DECL|macro|PUBLIC_MPU_TIPB_CNTL
mdefine_line|#define PUBLIC_MPU_TIPB_CNTL&t;0xfffed308
DECL|macro|TIPB_SWITCH_CFG
mdefine_line|#define TIPB_SWITCH_CFG&t;&t;OMAP_TIPB_SWITCH
DECL|macro|MMCSD2_SSW_MPU_CONF
mdefine_line|#define MMCSD2_SSW_MPU_CONF&t;(TIPB_SWITCH_CFG + 0x160)
macro_line|#endif /*  __ASM_ARCH_OMAP1610_H */
eof
