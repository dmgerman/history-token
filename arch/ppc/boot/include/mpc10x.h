multiline_comment|/*&n; * arch/ppc/boot/include/mpc10.h&n; *&n; * Common defines for the Motorola SPS MPC106/8240/107 Host bridge/Mem&n; * ctrl/EPIC/etc.&n; *&n; * Author: Tom Rini &lt;trini@mvista.com&gt;&n; *&n; * This is a heavily stripped down version of:&n; * include/asm-ppc/mpc10x.h&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __BOOT_MPC10X_H__
DECL|macro|__BOOT_MPC10X_H__
mdefine_line|#define __BOOT_MPC10X_H__
multiline_comment|/*&n; * The values here don&squot;t completely map everything but should work in most&n; * cases.&n; *&n; * MAP A (PReP Map)&n; *   Processor: 0x80000000 - 0x807fffff -&gt; PCI I/O: 0x00000000 - 0x007fffff&n; *   Processor: 0xc0000000 - 0xdfffffff -&gt; PCI MEM: 0x00000000 - 0x1fffffff&n; *   PCI MEM:   0x80000000 -&gt; Processor System Memory: 0x00000000&n; *   EUMB mapped to: ioremap_base - 0x00100000 (ioremap_base - 1 MB)&n; *&n; * MAP B (CHRP Map)&n; *   Processor: 0xfe000000 - 0xfebfffff -&gt; PCI I/O: 0x00000000 - 0x00bfffff&n; *   Processor: 0x80000000 - 0xbfffffff -&gt; PCI MEM: 0x80000000 - 0xbfffffff&n; *   PCI MEM:   0x00000000 -&gt; Processor System Memory: 0x00000000&n; *   EUMB mapped to: ioremap_base - 0x00100000 (ioremap_base - 1 MB)&n; */
multiline_comment|/* Define the type of map to use */
DECL|macro|MPC10X_MEM_MAP_A
mdefine_line|#define&t;MPC10X_MEM_MAP_A&t;&t;1
DECL|macro|MPC10X_MEM_MAP_B
mdefine_line|#define&t;MPC10X_MEM_MAP_B&t;&t;2
multiline_comment|/* Map A (PReP Map) Defines */
DECL|macro|MPC10X_MAPA_CNFG_ADDR
mdefine_line|#define&t;MPC10X_MAPA_CNFG_ADDR&t;&t;0x80000cf8
DECL|macro|MPC10X_MAPA_CNFG_DATA
mdefine_line|#define&t;MPC10X_MAPA_CNFG_DATA&t;&t;0x80000cfc
multiline_comment|/* Map B (CHRP Map) Defines */
DECL|macro|MPC10X_MAPB_CNFG_ADDR
mdefine_line|#define&t;MPC10X_MAPB_CNFG_ADDR&t;&t;0xfec00000
DECL|macro|MPC10X_MAPB_CNFG_DATA
mdefine_line|#define&t;MPC10X_MAPB_CNFG_DATA&t;&t;0xfee00000
multiline_comment|/* Define offsets for the memory controller registers in the config space */
DECL|macro|MPC10X_MCTLR_MEM_START_1
mdefine_line|#define MPC10X_MCTLR_MEM_START_1&t;0x80&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_MEM_START_2
mdefine_line|#define MPC10X_MCTLR_MEM_START_2&t;0x84&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_START_1
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_START_1&t;0x88&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_START_2
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_START_2&t;0x8c&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_MEM_END_1
mdefine_line|#define MPC10X_MCTLR_MEM_END_1&t;&t;0x90&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_MEM_END_2
mdefine_line|#define MPC10X_MCTLR_MEM_END_2&t;&t;0x94&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_END_1
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_END_1&t;0x98&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_END_2
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_END_2&t;0x9c&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_MEM_BANK_ENABLES
mdefine_line|#define MPC10X_MCTLR_MEM_BANK_ENABLES&t;0xa0
macro_line|#endif&t;/* __BOOT_MPC10X_H__ */
eof
