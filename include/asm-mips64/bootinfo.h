multiline_comment|/* $Id: bootinfo.h,v 1.1 1999/08/18 23:37:50 ralf Exp $&n; *&n; * bootinfo.h -- Definition of the Linux/MIPS boot information structure&n; *&n; * Copyright (C) 1995 - 1999 by Ralf Baechle&n; * Copyright (C) 1995, 1996 by Stoned Elipot and Paul M. Antoine.&n; * Copyright (C) 1999 Ralf Baechle&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_BOOTINFO_H
DECL|macro|_ASM_BOOTINFO_H
mdefine_line|#define _ASM_BOOTINFO_H
multiline_comment|/*&n; * Values for machgroup&n; */
DECL|macro|MACH_GROUP_UNKNOWN
mdefine_line|#define MACH_GROUP_UNKNOWN      0 /* whatever... */
DECL|macro|MACH_GROUP_JAZZ
mdefine_line|#define MACH_GROUP_JAZZ     &t;1 /* Jazz                                     */
DECL|macro|MACH_GROUP_DEC
mdefine_line|#define MACH_GROUP_DEC          2 /* Digital Equipment                        */
DECL|macro|MACH_GROUP_ARC
mdefine_line|#define MACH_GROUP_ARC&t;&t;3 /* Wreckstation Tyne, rPC44, possibly other */
DECL|macro|MACH_GROUP_SNI_RM
mdefine_line|#define MACH_GROUP_SNI_RM&t;4 /* Siemens Nixdorf RM series                */
DECL|macro|MACH_GROUP_ACN
mdefine_line|#define MACH_GROUP_ACN&t;&t;5
DECL|macro|MACH_GROUP_SGI
mdefine_line|#define MACH_GROUP_SGI          6 /* Silicon Graphics workstations and servers */
DECL|macro|MACH_GROUP_COBALT
mdefine_line|#define MACH_GROUP_COBALT       7 /* Cobalt servers&t;&t; &t;      */
DECL|macro|GROUP_NAMES
mdefine_line|#define GROUP_NAMES { &quot;unknown&quot;, &quot;Jazz&quot;, &quot;Digital&quot;, &quot;ARC&quot;, &bslash;&n;                      &quot;SNI&quot;, &quot;ACN&quot;, &quot;SGI&quot;, &quot;Cobalt&quot; }
multiline_comment|/*&n; * Valid machtype values for group unknown (low order halfword of mips_machtype)&n; */
DECL|macro|MACH_UNKNOWN
mdefine_line|#define MACH_UNKNOWN&t;&t;0&t;/* whatever...&t;&t;&t;*/
DECL|macro|GROUP_UNKNOWN_NAMES
mdefine_line|#define GROUP_UNKNOWN_NAMES { &quot;unknown&quot; }
multiline_comment|/*&n; * Valid machtype values for group JAZZ&n; */
DECL|macro|MACH_ACER_PICA_61
mdefine_line|#define MACH_ACER_PICA_61&t;0&t;/* Acer PICA-61 (PICA1)&t;&t;*/
DECL|macro|MACH_MIPS_MAGNUM_4000
mdefine_line|#define MACH_MIPS_MAGNUM_4000&t;1&t;/* Mips Magnum 4000 &quot;RC4030&quot;&t;*/
DECL|macro|MACH_OLIVETTI_M700
mdefine_line|#define MACH_OLIVETTI_M700      2&t;/* Olivetti M700-10 (-15 ??)    */
DECL|macro|GROUP_JAZZ_NAMES
mdefine_line|#define GROUP_JAZZ_NAMES { &quot;Acer PICA 61&quot;, &quot;Mips Magnum 4000&quot;, &quot;Olivetti M700&quot; }
multiline_comment|/*&n; * Valid machtype for group DEC &n; */
DECL|macro|MACH_DSUNKNOWN
mdefine_line|#define MACH_DSUNKNOWN&t;&t;0
DECL|macro|MACH_DS23100
mdefine_line|#define MACH_DS23100&t;&t;1&t;/* DECstation 2100 or 3100&t;*/
DECL|macro|MACH_DS5100
mdefine_line|#define MACH_DS5100&t;&t;2&t;/* DECstation 5100&t;&t;*/
DECL|macro|MACH_DS5000_200
mdefine_line|#define MACH_DS5000_200&t;&t;3&t;/* DECstation 5000/200&t;&t;*/
DECL|macro|MACH_DS5000_1XX
mdefine_line|#define MACH_DS5000_1XX&t;&t;4&t;/* DECstation 5000/120, 125, 133, 150 */
DECL|macro|MACH_DS5000_XX
mdefine_line|#define MACH_DS5000_XX&t;&t;5&t;/* DECstation 5000/20, 25, 33, 50 */
DECL|macro|MACH_DS5000_2X0
mdefine_line|#define MACH_DS5000_2X0&t;&t;6&t;/* DECstation 5000/240, 260&t;*/
DECL|macro|MACH_DS5400
mdefine_line|#define MACH_DS5400&t;&t;7&t;/* DECstation 5400&t;&t;*/
DECL|macro|MACH_DS5500
mdefine_line|#define MACH_DS5500&t;&t;8&t;/* DECstation 5500&t;&t;*/
DECL|macro|MACH_DS5800
mdefine_line|#define MACH_DS5800&t;&t;9&t;/* DECstation 5800&t;&t;*/
DECL|macro|GROUP_DEC_NAMES
mdefine_line|#define GROUP_DEC_NAMES { &quot;unknown&quot;, &quot;DECstation 2100/3100&quot;, &quot;DECstation 5100&quot;, &bslash;&n;&t;&quot;DECstation 5000/200&quot;, &quot;DECstation 5000/1xx&quot;, &quot;Personal DECstation 5000/xx&quot;, &bslash;&n;&t;&quot;DECstation 5000/2x0&quot;, &quot;DECstation 5400&quot;, &quot;DECstation 5500&quot;, &bslash;&n;&t;&quot;DECstation 5800&quot; }
multiline_comment|/*&n; * Valid machtype for group ARC&n; */
DECL|macro|MACH_DESKSTATION_RPC44
mdefine_line|#define MACH_DESKSTATION_RPC44  0&t;/* Deskstation rPC44 */
DECL|macro|MACH_DESKSTATION_TYNE
mdefine_line|#define MACH_DESKSTATION_TYNE&t;1&t;/* Deskstation Tyne */
DECL|macro|GROUP_ARC_NAMES
mdefine_line|#define GROUP_ARC_NAMES { &quot;Deskstation rPC44&quot;, &quot;Deskstation Tyne&quot; }
multiline_comment|/*&n; * Valid machtype for group SNI_RM&n; */
DECL|macro|MACH_SNI_RM200_PCI
mdefine_line|#define MACH_SNI_RM200_PCI&t;0&t;/* RM200/RM300/RM400 PCI series */
DECL|macro|GROUP_SNI_RM_NAMES
mdefine_line|#define GROUP_SNI_RM_NAMES { &quot;RM200 PCI&quot; }
multiline_comment|/*&n; * Valid machtype for group ACN&n; */
DECL|macro|MACH_ACN_MIPS_BOARD
mdefine_line|#define MACH_ACN_MIPS_BOARD&t;0       /* ACN MIPS single board        */
DECL|macro|GROUP_ACN_NAMES
mdefine_line|#define GROUP_ACN_NAMES { &quot;ACN&quot; }
multiline_comment|/*&n; * Valid machtype for group SGI&n; */
DECL|macro|MACH_SGI_INDY
mdefine_line|#define MACH_SGI_INDY&t;&t;0&t;/* R4?K and R5K Indy workstations */
DECL|macro|MACH_SGI_CHALLENGE_S
mdefine_line|#define MACH_SGI_CHALLENGE_S&t;1       /* The Challenge S server */
DECL|macro|MACH_SGI_INDIGO2
mdefine_line|#define MACH_SGI_INDIGO2&t;2&t;/* The Indigo2 system */
DECL|macro|MACH_SGI_IP27
mdefine_line|#define MACH_SGI_IP27&t;&t;3&t;/* Origin 200, Origin 2000, Onyx 2 */
DECL|macro|GROUP_SGI_NAMES
mdefine_line|#define GROUP_SGI_NAMES { &quot;Indy&quot;, &quot;Challenge S&quot;, &quot;Indigo2&quot;, &quot;IP27&quot; }
multiline_comment|/*&n; * Valid machtype for group COBALT&n; */
DECL|macro|MACH_COBALT_27
mdefine_line|#define MACH_COBALT_27 &t;&t; 0&t;/* Proto &quot;27&quot; hardware */
DECL|macro|GROUP_COBALT_NAMES
mdefine_line|#define GROUP_COBALT_NAMES { &quot;Microserver 27&quot; }
multiline_comment|/*&n; * Valid cputype values&n; */
DECL|macro|CPU_UNKNOWN
mdefine_line|#define CPU_UNKNOWN&t;&t;0
DECL|macro|CPU_R2000
mdefine_line|#define CPU_R2000&t;&t;1
DECL|macro|CPU_R3000
mdefine_line|#define CPU_R3000&t;&t;2
DECL|macro|CPU_R3000A
mdefine_line|#define CPU_R3000A&t;&t;3
DECL|macro|CPU_R3041
mdefine_line|#define CPU_R3041&t;&t;4
DECL|macro|CPU_R3051
mdefine_line|#define CPU_R3051&t;&t;5
DECL|macro|CPU_R3052
mdefine_line|#define CPU_R3052&t;&t;6
DECL|macro|CPU_R3081
mdefine_line|#define CPU_R3081&t;&t;7
DECL|macro|CPU_R3081E
mdefine_line|#define CPU_R3081E&t;&t;8
DECL|macro|CPU_R4000PC
mdefine_line|#define CPU_R4000PC&t;&t;9
DECL|macro|CPU_R4000SC
mdefine_line|#define CPU_R4000SC&t;&t;10
DECL|macro|CPU_R4000MC
mdefine_line|#define CPU_R4000MC&t;&t;11
DECL|macro|CPU_R4200
mdefine_line|#define CPU_R4200&t;&t;12
DECL|macro|CPU_R4400PC
mdefine_line|#define CPU_R4400PC&t;&t;13
DECL|macro|CPU_R4400SC
mdefine_line|#define CPU_R4400SC&t;&t;14
DECL|macro|CPU_R4400MC
mdefine_line|#define CPU_R4400MC&t;&t;15
DECL|macro|CPU_R4600
mdefine_line|#define CPU_R4600&t;&t;16
DECL|macro|CPU_R6000
mdefine_line|#define CPU_R6000&t;&t;17
DECL|macro|CPU_R6000A
mdefine_line|#define CPU_R6000A&t;&t;18
DECL|macro|CPU_R8000
mdefine_line|#define CPU_R8000&t;&t;19
DECL|macro|CPU_R10000
mdefine_line|#define CPU_R10000&t;&t;20
DECL|macro|CPU_R4300
mdefine_line|#define CPU_R4300&t;&t;21
DECL|macro|CPU_R4650
mdefine_line|#define CPU_R4650&t;&t;22
DECL|macro|CPU_R4700
mdefine_line|#define CPU_R4700&t;&t;23
DECL|macro|CPU_R5000
mdefine_line|#define CPU_R5000&t;&t;24
DECL|macro|CPU_R5000A
mdefine_line|#define CPU_R5000A&t;&t;25
DECL|macro|CPU_R4640
mdefine_line|#define CPU_R4640&t;&t;26
DECL|macro|CPU_NEVADA
mdefine_line|#define CPU_NEVADA&t;&t;27&t;/* RM5230, RM5260 */
DECL|macro|CPU_LAST
mdefine_line|#define CPU_LAST&t;&t;27
DECL|macro|CPU_NAMES
mdefine_line|#define CPU_NAMES { &quot;unknown&quot;, &quot;R2000&quot;, &quot;R3000&quot;, &quot;R3000A&quot;, &quot;R3041&quot;, &quot;R3051&quot;, &bslash;&n;        &quot;R3052&quot;, &quot;R3081&quot;, &quot;R3081E&quot;, &quot;R4000PC&quot;, &quot;R4000SC&quot;, &quot;R4000MC&quot;,         &bslash;&n;        &quot;R4200&quot;, &quot;R4400PC&quot;, &quot;R4400SC&quot;, &quot;R4400MC&quot;, &quot;R4600&quot;, &quot;R6000&quot;,          &bslash;&n;        &quot;R6000A&quot;, &quot;R8000&quot;, &quot;R10000&quot;, &quot;R4300&quot;, &quot;R4650&quot;, &quot;R4700&quot;, &quot;R5000&quot;,     &bslash;&n;        &quot;R5000A&quot;, &quot;R4640&quot;, &quot;Nevada&quot; }
DECL|macro|CL_SIZE
mdefine_line|#define CL_SIZE      (80)
DECL|macro|BOOT_MEM_MAP_MAX
mdefine_line|#define BOOT_MEM_MAP_MAX        32
DECL|macro|BOOT_MEM_RAM
mdefine_line|#define BOOT_MEM_RAM            1
DECL|macro|BOOT_MEM_ROM_DATA
mdefine_line|#define BOOT_MEM_ROM_DATA       2
DECL|macro|BOOT_MEM_RESERVED
mdefine_line|#define BOOT_MEM_RESERVED       3
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Some machine parameters passed by the bootloaders. &n; */
DECL|struct|drive_info_struct
r_struct
id|drive_info_struct
(brace
DECL|member|dummy
r_char
id|dummy
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
r_int
id|mips_memory_upper
suffix:semicolon
r_extern
r_int
r_int
id|mips_cputype
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
r_extern
r_int
r_int
id|mips_tlb_entries
suffix:semicolon
multiline_comment|/*&n; * A memory map that&squot;s built upon what was determined&n; * or specified on the command line.&n; */
DECL|struct|boot_mem_map
r_struct
id|boot_mem_map
(brace
DECL|member|nr_map
r_int
id|nr_map
suffix:semicolon
r_struct
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* start of memory segment */
DECL|member|size
r_int
r_int
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
r_int
r_int
id|start
comma
r_int
r_int
id|size
comma
r_int
id|type
)paren
suffix:semicolon
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
macro_line|#endif /* _ASM_BOOTINFO_H */
eof
