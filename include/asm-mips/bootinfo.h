multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 2003 by Ralf Baechle&n; * Copyright (C) 1995, 1996 Andreas Busse&n; * Copyright (C) 1995, 1996 Stoned Elipot&n; * Copyright (C) 1995, 1996 Paul M. Antoine.&n; */
macro_line|#ifndef _ASM_BOOTINFO_H
DECL|macro|_ASM_BOOTINFO_H
mdefine_line|#define _ASM_BOOTINFO_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
multiline_comment|/*&n; * The MACH_GROUP_ IDs are the equivalent to PCI vendor IDs; the remaining&n; * MACH_ values equivalent to product IDs.  As such the numbers do not&n; * necessarily reflect technical relations or similarities between systems.&n; */
multiline_comment|/*&n; * Valid machtype values for group unknown&n; */
DECL|macro|MACH_GROUP_UNKNOWN
mdefine_line|#define MACH_GROUP_UNKNOWN      0&t;/* whatever...&t;&t;&t;*/
DECL|macro|MACH_UNKNOWN
mdefine_line|#define  MACH_UNKNOWN&t;&t;0&t;/* whatever...&t;&t;&t;*/
multiline_comment|/*&n; * Valid machtype values for group JAZZ&n; */
DECL|macro|MACH_GROUP_JAZZ
mdefine_line|#define MACH_GROUP_JAZZ&t;&t;1 &t;/* Jazz&t;&t;&t;&t;*/
DECL|macro|MACH_ACER_PICA_61
mdefine_line|#define  MACH_ACER_PICA_61&t;0&t;/* Acer PICA-61 (PICA1)&t;&t;*/
DECL|macro|MACH_MIPS_MAGNUM_4000
mdefine_line|#define  MACH_MIPS_MAGNUM_4000&t;1&t;/* Mips Magnum 4000 &quot;RC4030&quot;&t;*/
DECL|macro|MACH_OLIVETTI_M700
mdefine_line|#define  MACH_OLIVETTI_M700&t;2&t;/* Olivetti M700-10 (-15 ??)    */
multiline_comment|/*&n; * Valid machtype for group DEC&n; */
DECL|macro|MACH_GROUP_DEC
mdefine_line|#define MACH_GROUP_DEC          2&t;/* Digital Equipment&t;&t;*/
DECL|macro|MACH_DSUNKNOWN
mdefine_line|#define  MACH_DSUNKNOWN&t;&t;0
DECL|macro|MACH_DS23100
mdefine_line|#define  MACH_DS23100&t;&t;1&t;/* DECstation 2100 or 3100&t;*/
DECL|macro|MACH_DS5100
mdefine_line|#define  MACH_DS5100&t;&t;2&t;/* DECsystem 5100&t;&t;*/
DECL|macro|MACH_DS5000_200
mdefine_line|#define  MACH_DS5000_200&t;3&t;/* DECstation 5000/200&t;&t;*/
DECL|macro|MACH_DS5000_1XX
mdefine_line|#define  MACH_DS5000_1XX&t;4&t;/* DECstation 5000/120, 125, 133, 150 */
DECL|macro|MACH_DS5000_XX
mdefine_line|#define  MACH_DS5000_XX&t;&t;5&t;/* DECstation 5000/20, 25, 33, 50 */
DECL|macro|MACH_DS5000_2X0
mdefine_line|#define  MACH_DS5000_2X0&t;6&t;/* DECstation 5000/240, 260&t;*/
DECL|macro|MACH_DS5400
mdefine_line|#define  MACH_DS5400&t;&t;7&t;/* DECsystem 5400&t;&t;*/
DECL|macro|MACH_DS5500
mdefine_line|#define  MACH_DS5500&t;&t;8&t;/* DECsystem 5500&t;&t;*/
DECL|macro|MACH_DS5800
mdefine_line|#define  MACH_DS5800&t;&t;9&t;/* DECsystem 5800&t;&t;*/
DECL|macro|MACH_DS5900
mdefine_line|#define  MACH_DS5900&t;&t;10&t;/* DECsystem 5900&t;&t;*/
multiline_comment|/*&n; * Valid machtype for group ARC&n; */
DECL|macro|MACH_GROUP_ARC
mdefine_line|#define MACH_GROUP_ARC&t;&t;3&t;/* Deskstation&t;&t;&t;*/
DECL|macro|MACH_DESKSTATION_RPC44
mdefine_line|#define MACH_DESKSTATION_RPC44  0&t;/* Deskstation rPC44 */
DECL|macro|MACH_DESKSTATION_TYNE
mdefine_line|#define MACH_DESKSTATION_TYNE&t;1&t;/* Deskstation Tyne */
multiline_comment|/*&n; * Valid machtype for group SNI_RM&n; */
DECL|macro|MACH_GROUP_SNI_RM
mdefine_line|#define MACH_GROUP_SNI_RM&t;4&t;/* Siemens Nixdorf RM series&t;*/
DECL|macro|MACH_SNI_RM200_PCI
mdefine_line|#define  MACH_SNI_RM200_PCI&t;0&t;/* RM200/RM300/RM400 PCI series */
multiline_comment|/*&n; * Valid machtype for group ACN&n; */
DECL|macro|MACH_GROUP_ACN
mdefine_line|#define MACH_GROUP_ACN&t;&t;5
DECL|macro|MACH_ACN_MIPS_BOARD
mdefine_line|#define  MACH_ACN_MIPS_BOARD&t;0       /* ACN MIPS single board        */
multiline_comment|/*&n; * Valid machtype for group SGI&n; */
DECL|macro|MACH_GROUP_SGI
mdefine_line|#define MACH_GROUP_SGI          6&t;/* Silicon Graphics&t;&t;*/
DECL|macro|MACH_SGI_IP22
mdefine_line|#define  MACH_SGI_IP22&t;&t;0&t;/* Indy, Indigo2, Challenge S&t;*/
DECL|macro|MACH_SGI_IP27
mdefine_line|#define  MACH_SGI_IP27&t;&t;1&t;/* Origin 200, Origin 2000, Onyx 2 */
DECL|macro|MACH_SGI_IP28
mdefine_line|#define  MACH_SGI_IP28&t;&t;2&t;/* Indigo2 Impact&t;&t;*/
DECL|macro|MACH_SGI_IP32
mdefine_line|#define  MACH_SGI_IP32&t;&t;3&t;/* O2&t;&t;&t;&t;*/
multiline_comment|/*&n; * Valid machtype for group COBALT&n; */
DECL|macro|MACH_GROUP_COBALT
mdefine_line|#define MACH_GROUP_COBALT       7&t;/* Cobalt servers&t;&t;*/
DECL|macro|MACH_COBALT_27
mdefine_line|#define  MACH_COBALT_27&t;&t;0&t;/* Proto &quot;27&quot; hardware&t;&t;*/
multiline_comment|/*&n; * Valid machtype for group NEC DDB&n; */
DECL|macro|MACH_GROUP_NEC_DDB
mdefine_line|#define MACH_GROUP_NEC_DDB&t;8&t;/* NEC DDB&t;&t;&t;*/
DECL|macro|MACH_NEC_DDB5074
mdefine_line|#define  MACH_NEC_DDB5074&t;0&t;/* NEC DDB Vrc-5074 */
DECL|macro|MACH_NEC_DDB5476
mdefine_line|#define  MACH_NEC_DDB5476&t;1&t;/* NEC DDB Vrc-5476 */
DECL|macro|MACH_NEC_DDB5477
mdefine_line|#define  MACH_NEC_DDB5477&t;2&t;/* NEC DDB Vrc-5477 */
DECL|macro|MACH_NEC_ROCKHOPPER
mdefine_line|#define  MACH_NEC_ROCKHOPPER&t;3&t;/* Rockhopper base board */
DECL|macro|MACH_NEC_ROCKHOPPERII
mdefine_line|#define  MACH_NEC_ROCKHOPPERII&t;4&t;/* Rockhopper II base board */
multiline_comment|/*&n; * Valid machtype for group BAGET&n; */
DECL|macro|MACH_GROUP_BAGET
mdefine_line|#define MACH_GROUP_BAGET&t;9&t;/* Baget&t;&t;&t;*/
DECL|macro|MACH_BAGET201
mdefine_line|#define  MACH_BAGET201&t;&t;0&t;/* BT23-201 */
DECL|macro|MACH_BAGET202
mdefine_line|#define  MACH_BAGET202&t;&t;1&t;/* BT23-202 */
multiline_comment|/*&n; * Cosine boards.&n; */
DECL|macro|MACH_GROUP_COSINE
mdefine_line|#define MACH_GROUP_COSINE      10&t;/* CoSine Orion&t;&t;&t;*/
DECL|macro|MACH_COSINE_ORION
mdefine_line|#define  MACH_COSINE_ORION&t;0
multiline_comment|/*&n; * Valid machtype for group GALILEO&n; */
DECL|macro|MACH_GROUP_GALILEO
mdefine_line|#define MACH_GROUP_GALILEO     11&t;/* Galileo Eval Boards&t;&t;*/
DECL|macro|MACH_EV96100
mdefine_line|#define  MACH_EV96100&t;&t;0&t;/* EV96100 */
DECL|macro|MACH_EV64120A
mdefine_line|#define  MACH_EV64120A&t;&t;1&t;/* EV64120A */
multiline_comment|/*&n; * Valid machtype for group MOMENCO&n; */
DECL|macro|MACH_GROUP_MOMENCO
mdefine_line|#define MACH_GROUP_MOMENCO&t;12&t;/* Momentum Boards&t;&t;*/
DECL|macro|MACH_MOMENCO_OCELOT
mdefine_line|#define  MACH_MOMENCO_OCELOT&t;0
DECL|macro|MACH_MOMENCO_OCELOT_G
mdefine_line|#define  MACH_MOMENCO_OCELOT_G&t;1
DECL|macro|MACH_MOMENCO_OCELOT_C
mdefine_line|#define  MACH_MOMENCO_OCELOT_C&t;2
DECL|macro|MACH_MOMENCO_JAGUAR_ATX
mdefine_line|#define  MACH_MOMENCO_JAGUAR_ATX 3
DECL|macro|MACH_MOMENCO_OCELOT_3
mdefine_line|#define  MACH_MOMENCO_OCELOT_3&t;4
multiline_comment|/*&n; * Valid machtype for group ITE&n; */
DECL|macro|MACH_GROUP_ITE
mdefine_line|#define MACH_GROUP_ITE&t;&t;13&t;/* ITE Semi Eval Boards&t;&t;*/
DECL|macro|MACH_QED_4N_S01B
mdefine_line|#define  MACH_QED_4N_S01B&t;0&t;/* ITE8172 based eval board */
multiline_comment|/*&n; * Valid machtype for group PHILIPS&n; */
DECL|macro|MACH_GROUP_PHILIPS
mdefine_line|#define MACH_GROUP_PHILIPS     14
DECL|macro|MACH_PHILIPS_NINO
mdefine_line|#define  MACH_PHILIPS_NINO&t;0&t;/* Nino */
DECL|macro|MACH_PHILIPS_VELO
mdefine_line|#define  MACH_PHILIPS_VELO&t;1&t;/* Velo */
multiline_comment|/*&n; * Valid machtype for group Globespan&n; */
DECL|macro|MACH_GROUP_GLOBESPAN
mdefine_line|#define MACH_GROUP_GLOBESPAN   15&t;/* Globespan */
DECL|macro|MACH_IVR
mdefine_line|#define  MACH_IVR&t;&t;0&t;/* IVR eval board */
multiline_comment|/*&n; * Valid machtype for group SIBYTE&n; */
DECL|macro|MACH_GROUP_SIBYTE
mdefine_line|#define MACH_GROUP_SIBYTE&t;16&t;/* Sibyte / Broadcom */
DECL|macro|MACH_SWARM
mdefine_line|#define  MACH_SWARM              0
multiline_comment|/*&n; * Valid machtypes for group Toshiba&n; */
DECL|macro|MACH_GROUP_TOSHIBA
mdefine_line|#define MACH_GROUP_TOSHIBA&t;17 /* Toshiba Reference Systems TSBREF       */
DECL|macro|MACH_PALLAS
mdefine_line|#define  MACH_PALLAS&t;&t;0
DECL|macro|MACH_TOPAS
mdefine_line|#define  MACH_TOPAS&t;&t;1
DECL|macro|MACH_JMR
mdefine_line|#define  MACH_JMR&t;&t;2
DECL|macro|MACH_TOSHIBA_JMR3927
mdefine_line|#define  MACH_TOSHIBA_JMR3927&t;3&t;/* JMR-TX3927 CPU/IO board */
DECL|macro|MACH_TOSHIBA_RBTX4927
mdefine_line|#define  MACH_TOSHIBA_RBTX4927&t;4
DECL|macro|MACH_TOSHIBA_RBTX4937
mdefine_line|#define  MACH_TOSHIBA_RBTX4937&t;5
DECL|macro|GROUP_TOSHIBA_NAMES
mdefine_line|#define GROUP_TOSHIBA_NAMES&t;{ &quot;Pallas&quot;, &quot;TopasCE&quot;, &quot;JMR&quot;, &quot;JMR TX3927&quot;, &bslash;&n;&t;&t;&t;&t;  &quot;RBTX4927&quot;, &quot;RBTX4937&quot; }
multiline_comment|/*&n; * Valid machtype for group Alchemy&n; */
DECL|macro|MACH_GROUP_ALCHEMY
mdefine_line|#define MACH_GROUP_ALCHEMY     18&t;/* AMD Alchemy&t;*/
DECL|macro|MACH_PB1000
mdefine_line|#define  MACH_PB1000&t;&t;0&t;/* Au1000-based eval board */
DECL|macro|MACH_PB1100
mdefine_line|#define  MACH_PB1100&t;&t;1&t;/* Au1100-based eval board */
DECL|macro|MACH_PB1500
mdefine_line|#define  MACH_PB1500&t;&t;2&t;/* Au1500-based eval board */
DECL|macro|MACH_DB1000
mdefine_line|#define  MACH_DB1000&t;&t;3       /* Au1000-based eval board */
DECL|macro|MACH_DB1100
mdefine_line|#define  MACH_DB1100&t;&t;4       /* Au1100-based eval board */
DECL|macro|MACH_DB1500
mdefine_line|#define  MACH_DB1500&t;&t;5       /* Au1500-based eval board */
DECL|macro|MACH_XXS1500
mdefine_line|#define  MACH_XXS1500&t;&t;6       /* Au1500-based eval board */
DECL|macro|MACH_MTX1
mdefine_line|#define  MACH_MTX1&t;&t;7       /* 4G MTX-1 Au1500-based board */
DECL|macro|MACH_PB1550
mdefine_line|#define  MACH_PB1550&t;&t;8       /* Au1550-based eval board */
DECL|macro|MACH_DB1550
mdefine_line|#define  MACH_DB1550&t;&t;9       /* Au1550-based eval board */
multiline_comment|/*&n; * Valid machtype for group NEC_VR41XX&n; *&n; * Various NEC-based devices.&n; *&n; * FIXME: MACH_GROUPs should be by _MANUFACTURER_ of * the device, not by&n; *        technical properties, so no new additions to this group.&n; */
DECL|macro|MACH_GROUP_NEC_VR41XX
mdefine_line|#define MACH_GROUP_NEC_VR41XX  19
DECL|macro|MACH_NEC_OSPREY
mdefine_line|#define  MACH_NEC_OSPREY&t;0&t;/* Osprey eval board */
DECL|macro|MACH_NEC_EAGLE
mdefine_line|#define  MACH_NEC_EAGLE&t;&t;1&t;/* NEC Eagle/Hawk board */
DECL|macro|MACH_ZAO_CAPCELLA
mdefine_line|#define  MACH_ZAO_CAPCELLA&t;2&t;/* ZAO Networks Capcella */
DECL|macro|MACH_VICTOR_MPC30X
mdefine_line|#define  MACH_VICTOR_MPC30X&t;3&t;/* Victor MP-C303/304 */
DECL|macro|MACH_IBM_WORKPAD
mdefine_line|#define  MACH_IBM_WORKPAD&t;4&t;/* IBM WorkPad z50 */
DECL|macro|MACH_CASIO_E55
mdefine_line|#define  MACH_CASIO_E55&t;&t;5&t;/* CASIO CASSIOPEIA E-10/15/55/65 */
DECL|macro|MACH_TANBAC_TB0226
mdefine_line|#define  MACH_TANBAC_TB0226&t;6&t;/* TANBAC TB0226 (Mbase) */
DECL|macro|MACH_TANBAC_TB0229
mdefine_line|#define  MACH_TANBAC_TB0229&t;7&t;/* TANBAC TB0229 (VR4131DIMM) */
DECL|macro|MACH_GROUP_HP_LJ
mdefine_line|#define MACH_GROUP_HP_LJ&t;20&t;/* Hewlett Packard LaserJet&t;*/
DECL|macro|MACH_HP_LASERJET
mdefine_line|#define  MACH_HP_LASERJET&t;1
multiline_comment|/*&n; * Valid machtype for group LASAT&n; */
DECL|macro|MACH_GROUP_LASAT
mdefine_line|#define MACH_GROUP_LASAT       21
DECL|macro|MACH_LASAT_100
mdefine_line|#define  MACH_LASAT_100&t;&t;0&t;/* Masquerade II/SP100/SP50/SP25 */
DECL|macro|MACH_LASAT_200
mdefine_line|#define  MACH_LASAT_200&t;&t;1&t;/* Masquerade PRO/SP200 */
multiline_comment|/*&n; * Valid machtype for group TITAN&n; */
DECL|macro|MACH_GROUP_TITAN
mdefine_line|#define MACH_GROUP_TITAN       22&t;/* PMC-Sierra Titan&t;&t;*/
DECL|macro|MACH_TITAN_YOSEMITE
mdefine_line|#define  MACH_TITAN_YOSEMITE&t;1&t;/* PMC-Sierra Yosemite&t;&t;*/
DECL|macro|CL_SIZE
mdefine_line|#define CL_SIZE&t;&t;&t;COMMAND_LINE_SIZE
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mips_machtype
suffix:semicolon
r_extern
r_int
r_int
id|mips_machgroup
suffix:semicolon
DECL|macro|BOOT_MEM_MAP_MAX
mdefine_line|#define BOOT_MEM_MAP_MAX&t;32
DECL|macro|BOOT_MEM_RAM
mdefine_line|#define BOOT_MEM_RAM&t;&t;1
DECL|macro|BOOT_MEM_ROM_DATA
mdefine_line|#define BOOT_MEM_ROM_DATA&t;2
DECL|macro|BOOT_MEM_RESERVED
mdefine_line|#define BOOT_MEM_RESERVED&t;3
multiline_comment|/*&n; * A memory map that&squot;s built upon what was determined&n; * or specified on the command line.&n; */
DECL|struct|boot_mem_map
r_struct
id|boot_mem_map
(brace
DECL|member|nr_map
r_int
id|nr_map
suffix:semicolon
DECL|struct|boot_mem_map_entry
r_struct
id|boot_mem_map_entry
(brace
DECL|member|addr
id|phys_t
id|addr
suffix:semicolon
multiline_comment|/* start of memory segment */
DECL|member|size
id|phys_t
id|size
suffix:semicolon
multiline_comment|/* size of memory segment */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* type of memory segment */
DECL|member|map
)brace
id|map
(braket
id|BOOT_MEM_MAP_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|boot_mem_map
id|boot_mem_map
suffix:semicolon
r_extern
r_void
id|add_memory_region
c_func
(paren
id|phys_t
id|start
comma
id|phys_t
id|size
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|prom_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Initial kernel command line, usually setup by prom_init()&n; */
r_extern
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * Registers a0, a1, a3 and a4 as passed to the kenrel entry by firmware&n; */
r_extern
r_int
r_int
id|fw_arg0
comma
id|fw_arg1
comma
id|fw_arg2
comma
id|fw_arg3
suffix:semicolon
macro_line|#endif /* _ASM_BOOTINFO_H */
eof
