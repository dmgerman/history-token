multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle, Andreas Busse,&n; *                             Stoned Elipot and Paul M. Antoine.&n; */
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
mdefine_line|#define MACH_GROUP_SGI          6 /* Silicon Graphics                         */
DECL|macro|MACH_GROUP_COBALT
mdefine_line|#define MACH_GROUP_COBALT       7 /* Cobalt servers&t;&t; &t;      */
DECL|macro|MACH_GROUP_NEC_DDB
mdefine_line|#define MACH_GROUP_NEC_DDB&t;8 /* NEC DDB                                  */
DECL|macro|MACH_GROUP_BAGET
mdefine_line|#define MACH_GROUP_BAGET&t;9 /* Baget                                    */
DECL|macro|MACH_GROUP_COSINE
mdefine_line|#define MACH_GROUP_COSINE      10 /* CoSine Orion                             */
DECL|macro|MACH_GROUP_GALILEO
mdefine_line|#define MACH_GROUP_GALILEO     11 /* Galileo Eval Boards                      */
DECL|macro|MACH_GROUP_MOMENCO
mdefine_line|#define MACH_GROUP_MOMENCO     12 /* Momentum Boards                          */
DECL|macro|MACH_GROUP_ITE
mdefine_line|#define MACH_GROUP_ITE         13 /* ITE Semi Eval Boards                     */
DECL|macro|MACH_GROUP_PHILIPS
mdefine_line|#define MACH_GROUP_PHILIPS     14
DECL|macro|MACH_GROUP_GLOBESPAN
mdefine_line|#define MACH_GROUP_GLOBESPAN   15 /* Globespan PVR Referrence Board           */
DECL|macro|MACH_GROUP_SIBYTE
mdefine_line|#define MACH_GROUP_SIBYTE      16 /* Sibyte Eval Boards                       */
DECL|macro|MACH_GROUP_TOSHIBA
mdefine_line|#define MACH_GROUP_TOSHIBA     17 /* Toshiba Reference Systems TSBREF         */
DECL|macro|MACH_GROUP_ALCHEMY
mdefine_line|#define MACH_GROUP_ALCHEMY     18 /* Alchemy Semi Eval Boards*/
DECL|macro|GROUP_NAMES
mdefine_line|#define GROUP_NAMES { &quot;unknown&quot;, &quot;Jazz&quot;, &quot;Digital&quot;, &quot;ARC&quot;, &quot;SNI&quot;, &quot;ACN&quot;,      &bslash;&n;&t;&quot;SGI&quot;, &quot;Cobalt&quot;, &quot;NEC DDB&quot;, &quot;Baget&quot;, &quot;Cosine&quot;, &quot;Galileo&quot;, &quot;Momentum&quot;, &bslash;&n;&t;&quot;ITE&quot;, &quot;Philips&quot;, &quot;Globepspan&quot;, &quot;SiByte&quot;, &quot;Toshiba&quot;, &quot;Alchemy&quot; }
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
mdefine_line|#define MACH_SGI_CHALLENGE_S&t;1&t;/* The Challenge S server */
DECL|macro|MACH_SGI_INDIGO2
mdefine_line|#define MACH_SGI_INDIGO2&t;2&t;/* The Indigo2 system */
DECL|macro|GROUP_SGI_NAMES
mdefine_line|#define GROUP_SGI_NAMES { &quot;Indy&quot;, &quot;Challenge S&quot;, &quot;Indigo2&quot; }
multiline_comment|/*&n; * Valid machtype for group COBALT&n; */
DECL|macro|MACH_COBALT_27
mdefine_line|#define MACH_COBALT_27 &t;&t; 0&t;/* Proto &quot;27&quot; hardware */
DECL|macro|GROUP_COBALT_NAMES
mdefine_line|#define GROUP_COBALT_NAMES { &quot;Microserver 27&quot; }
multiline_comment|/*&n; * Valid machtype for group NEC DDB&n; */
DECL|macro|MACH_NEC_DDB5074
mdefine_line|#define MACH_NEC_DDB5074&t; 0&t;/* NEC DDB Vrc-5074 */
DECL|macro|MACH_NEC_DDB5476
mdefine_line|#define MACH_NEC_DDB5476         1      /* NEC DDB Vrc-5476 */
DECL|macro|MACH_NEC_DDB5477
mdefine_line|#define MACH_NEC_DDB5477         2      /* NEC DDB Vrc-5477 */
DECL|macro|GROUP_NEC_DDB_NAMES
mdefine_line|#define GROUP_NEC_DDB_NAMES { &quot;Vrc-5074&quot;, &quot;Vrc-5476&quot;, &quot;Vrc-5477&quot;}
multiline_comment|/*&n; * Valid machtype for group BAGET&n; */
DECL|macro|MACH_BAGET201
mdefine_line|#define MACH_BAGET201&t;&t;0&t;/* BT23-201 */
DECL|macro|MACH_BAGET202
mdefine_line|#define MACH_BAGET202&t;&t;1&t;/* BT23-202 */
DECL|macro|GROUP_BAGET_NAMES
mdefine_line|#define GROUP_BAGET_NAMES { &quot;BT23-201&quot;, &quot;BT23-202&quot; }
multiline_comment|/*&n; * Cosine boards.&n; */
DECL|macro|MACH_COSINE_ORION
mdefine_line|#define MACH_COSINE_ORION&t;0
DECL|macro|GROUP_COSINE_NAMES
mdefine_line|#define GROUP_COSINE_NAMES { &quot;Orion&quot; }
multiline_comment|/*&n; * Valid machtype for group GALILEO&n; */
DECL|macro|MACH_EV96100
mdefine_line|#define MACH_EV96100&t;&t;0&t;/* EV96100 */
DECL|macro|MACH_EV64120A
mdefine_line|#define MACH_EV64120A&t;&t;1&t;/* EV64120A */
DECL|macro|GROUP_GALILEO_NAMES
mdefine_line|#define GROUP_GALILEO_NAMES { &quot;EV96100&quot; , &quot;EV64120A&quot; }
multiline_comment|/*&n; * Valid machtype for group MOMENCO&n; */
DECL|macro|MACH_MOMENCO_OCELOT
mdefine_line|#define MACH_MOMENCO_OCELOT&t;&t;0
DECL|macro|GROUP_MOMENCO_NAMES
mdefine_line|#define GROUP_MOMENCO_NAMES { &quot;Ocelot&quot; }
multiline_comment|/*&n; * Valid machtype for group ITE&n; */
DECL|macro|MACH_QED_4N_S01B
mdefine_line|#define MACH_QED_4N_S01B&t;0&t;/* ITE8172 based eval board */
DECL|macro|GROUP_ITE_NAMES
mdefine_line|#define GROUP_ITE_NAMES { &quot;QED-4N-S01B&quot; } /* the actual board name */
multiline_comment|/*&n; * Valid machtype for group Globespan&n; */
DECL|macro|MACH_IVR
mdefine_line|#define MACH_IVR       0                  /* IVR eval board */
DECL|macro|GROUP_GLOBESPAN_NAMES
mdefine_line|#define GROUP_GLOBESPAN_NAMES { &quot;IVR&quot; }   /* the actual board name */   
multiline_comment|/*&n; * Valid machtype for group PHILIPS&n; */
DECL|macro|MACH_PHILIPS_NINO
mdefine_line|#define MACH_PHILIPS_NINO&t;0&t;/* Nino */
DECL|macro|MACH_PHILIPS_VELO
mdefine_line|#define MACH_PHILIPS_VELO&t;1&t;/* Velo */
DECL|macro|GROUP_PHILIPS_NAMES
mdefine_line|#define GROUP_PHILIPS_NAMES { &quot;Nino&quot; , &quot;Velo&quot; }
multiline_comment|/*&n; * Valid machtype for group SIBYTE&n; */
DECL|macro|MACH_SWARM
mdefine_line|#define MACH_SWARM              0
DECL|macro|GROUP_SIBYTE_NAMES
mdefine_line|#define GROUP_SIBYTE_NAMES {&quot;SWARM&quot; }
multiline_comment|/*&n; * Valid machtypes for group Toshiba&n; */
DECL|macro|MACH_PALLAS
mdefine_line|#define MACH_PALLAS&t;&t;0
DECL|macro|MACH_TOPAS
mdefine_line|#define MACH_TOPAS&t;&t;1
DECL|macro|MACH_JMR
mdefine_line|#define MACH_JMR&t;&t;2
DECL|macro|GROUP_TOSHIBA_NAMES
mdefine_line|#define GROUP_TOSHIBA_NAMES { &quot;Pallas&quot;, &quot;TopasCE&quot;, &quot;JMR&quot; }
multiline_comment|/*&n; * Valid machtype for group Alchemy&n; */
DECL|macro|MACH_PB1000
mdefine_line|#define MACH_PB1000&t;0&t;         /* Au1000-based eval board */
DECL|macro|GROUP_ALCHEMY_NAMES
mdefine_line|#define GROUP_ALCHEMY_NAMES { &quot;PB1000&quot; } /* the actual board name */
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
DECL|macro|CPU_RM7000
mdefine_line|#define CPU_RM7000&t;&t;28
DECL|macro|CPU_R5432
mdefine_line|#define CPU_R5432&t;&t;29
DECL|macro|CPU_4KC
mdefine_line|#define CPU_4KC&t;&t;&t;30
DECL|macro|CPU_5KC
mdefine_line|#define CPU_5KC&t;&t;&t;31
DECL|macro|CPU_R4310
mdefine_line|#define CPU_R4310&t;&t;32
DECL|macro|CPU_SB1
mdefine_line|#define CPU_SB1&t;&t;&t;33
DECL|macro|CPU_TX3912
mdefine_line|#define CPU_TX3912&t;&t;34
DECL|macro|CPU_TX3922
mdefine_line|#define CPU_TX3922&t;&t;35
DECL|macro|CPU_TX3927
mdefine_line|#define CPU_TX3927&t;&t;36
DECL|macro|CPU_AU1000
mdefine_line|#define CPU_AU1000&t;&t;37
DECL|macro|CPU_4KEC
mdefine_line|#define CPU_4KEC&t;&t;37
DECL|macro|CPU_4KSC
mdefine_line|#define CPU_4KSC&t;&t;38
DECL|macro|CPU_LAST
mdefine_line|#define CPU_LAST&t;&t;39
DECL|macro|CPU_NAMES
mdefine_line|#define CPU_NAMES { &quot;unknown&quot;, &quot;R2000&quot;, &quot;R3000&quot;, &quot;R3000A&quot;, &quot;R3041&quot;, &quot;R3051&quot;, &bslash;&n;        &quot;R3052&quot;, &quot;R3081&quot;, &quot;R3081E&quot;, &quot;R4000PC&quot;, &quot;R4000SC&quot;, &quot;R4000MC&quot;,         &bslash;&n;        &quot;R4200&quot;, &quot;R4400PC&quot;, &quot;R4400SC&quot;, &quot;R4400MC&quot;, &quot;R4600&quot;, &quot;R6000&quot;,          &bslash;&n;        &quot;R6000A&quot;, &quot;R8000&quot;, &quot;R10000&quot;, &quot;R4300&quot;, &quot;R4650&quot;, &quot;R4700&quot;, &quot;R5000&quot;,     &bslash;&n;        &quot;R5000A&quot;, &quot;R4640&quot;, &quot;Nevada&quot;, &quot;RM7000&quot;, &quot;R5432&quot;, &quot;MIPS 4Kc&quot;,          &bslash;&n;        &quot;MIPS 5Kc&quot;, &quot;R4310&quot;, &quot;SiByte SB1&quot;, &quot;TX3912&quot;, &quot;TX3922&quot;, &quot;TX3927&quot;,     &bslash;&n;&t;&quot;Au1000&quot;, &quot;MIPS 4KEc&quot;, &quot;MIPS 4KSc&quot; }
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;256
DECL|macro|BOOT_MEM_MAP_MAX
mdefine_line|#define BOOT_MEM_MAP_MAX&t;32
DECL|macro|BOOT_MEM_RAM
mdefine_line|#define BOOT_MEM_RAM&t;&t;1
DECL|macro|BOOT_MEM_ROM_DATA
mdefine_line|#define BOOT_MEM_ROM_DATA&t;2
DECL|macro|BOOT_MEM_RESERVED
mdefine_line|#define BOOT_MEM_RESERVED&t;3
macro_line|#ifndef __ASSEMBLY__
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
multiline_comment|/* This is the same as in Milo but renamed for the sake of kernel&squot;s */
multiline_comment|/* namespace */
DECL|struct|mips_arc_DisplayInfo
r_typedef
r_struct
id|mips_arc_DisplayInfo
(brace
multiline_comment|/* video adapter information */
DECL|member|cursor_x
r_int
r_int
id|cursor_x
suffix:semicolon
DECL|member|cursor_y
r_int
r_int
id|cursor_y
suffix:semicolon
DECL|member|columns
r_int
r_int
id|columns
suffix:semicolon
DECL|member|lines
r_int
r_int
id|lines
suffix:semicolon
DECL|typedef|mips_arc_DisplayInfo
)brace
id|mips_arc_DisplayInfo
suffix:semicolon
multiline_comment|/* default values for drive info */
DECL|macro|DEFAULT_DRIVE_INFO
mdefine_line|#define DEFAULT_DRIVE_INFO { {0,}}
multiline_comment|/*&n; * These are the kernel variables initialized from&n; * the tag. And they have to be initialized to dummy/default&n; * values in setup.c (or whereever suitable) so they are in&n; * .data section&n; */
r_extern
r_struct
id|mips_cpu
id|mips_cpu
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
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_BOOTINFO_H */
eof
