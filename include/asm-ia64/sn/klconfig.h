multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/klconfig.h&gt;.&n; *&n; * Copyright (C) 1992-1997,1999,2001-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IA64_SN_KLCONFIG_H
DECL|macro|_ASM_IA64_SN_KLCONFIG_H
mdefine_line|#define _ASM_IA64_SN_KLCONFIG_H
multiline_comment|/*&n; * The KLCONFIG structures store info about the various BOARDs found&n; * during Hardware Discovery. In addition, it stores info about the&n; * components found on the BOARDs.&n; */
DECL|typedef|klconf_off_t
r_typedef
id|s32
id|klconf_off_t
suffix:semicolon
multiline_comment|/* Functions/macros needed to use this structure */
DECL|struct|kl_config_hdr
r_typedef
r_struct
id|kl_config_hdr
(brace
DECL|member|pad
r_char
id|pad
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|ch_board_info
id|klconf_off_t
id|ch_board_info
suffix:semicolon
multiline_comment|/* the link list of boards */
DECL|member|pad0
r_char
id|pad0
(braket
l_int|88
)braket
suffix:semicolon
DECL|typedef|kl_config_hdr_t
)brace
id|kl_config_hdr_t
suffix:semicolon
DECL|macro|NODE_OFFSET_TO_LBOARD
mdefine_line|#define NODE_OFFSET_TO_LBOARD(nasid,off)        (lboard_t*)(GLOBAL_CAC_ADDR((nasid), (off)))
multiline_comment|/*&n; * The KLCONFIG area is organized as a LINKED LIST of BOARDs. A BOARD&n; * can be either &squot;LOCAL&squot; or &squot;REMOTE&squot;. LOCAL means it is attached to &n; * the LOCAL/current NODE. REMOTE means it is attached to a different&n; * node.(TBD - Need a way to treat ROUTER boards.)&n; *&n; * There are 2 different structures to represent these boards -&n; * lboard - Local board, rboard - remote board. These 2 structures&n; * can be arbitrarily mixed in the LINKED LIST of BOARDs. (Refer&n; * Figure below). The first byte of the rboard or lboard structure&n; * is used to find out its type - no unions are used.&n; * If it is a lboard, then the config info of this board will be found&n; * on the local node. (LOCAL NODE BASE + offset value gives pointer to &n; * the structure.&n; * If it is a rboard, the local structure contains the node number&n; * and the offset of the beginning of the LINKED LIST on the remote node.&n; * The details of the hardware on a remote node can be built locally,&n; * if required, by reading the LINKED LIST on the remote node and &n; * ignoring all the rboards on that node.&n; *&n; * The local node uses the REMOTE NODE NUMBER + OFFSET to point to the &n; * First board info on the remote node. The remote node list is &n; * traversed as the local list, using the REMOTE BASE ADDRESS and not&n; * the local base address and ignoring all rboard values.&n; *&n; * &n; KLCONFIG&n;&n; +------------+      +------------+      +------------+      +------------+&n; |  lboard    |  +--&gt;|   lboard   |  +--&gt;|   rboard   |  +--&gt;|   lboard   |&n; +------------+  |   +------------+  |   +------------+  |   +------------+&n; | board info |  |   | board info |  |   |errinfo,bptr|  |   | board info |&n; +------------+  |   +------------+  |   +------------+  |   +------------+&n; | offset     |--+   |  offset    |--+   |  offset    |--+   |offset=NULL |&n; +------------+      +------------+      +------------+      +------------+&n;&n;&n; +------------+&n; | board info |&n; +------------+       +--------------------------------+&n; | compt 1    |------&gt;| type, rev, diaginfo, size ...  |  (CPU)&n; +------------+       +--------------------------------+&n; | compt 2    |--+&n; +------------+  |    +--------------------------------+&n; |  ...       |  +---&gt;| type, rev, diaginfo, size ...  |  (MEM_BANK)&n; +------------+       +--------------------------------+&n; | errinfo    |--+&n; +------------+  |    +--------------------------------+&n;                 +---&gt;|r/l brd errinfo,compt err flags |&n;                      +--------------------------------+&n;&n; *&n; * Each BOARD consists of COMPONENTs and the BOARD structure has &n; * pointers (offsets) to its COMPONENT structure.&n; * The COMPONENT structure has version info, size and speed info, revision,&n; * error info and the NIC info. This structure can accommodate any&n; * BOARD with arbitrary COMPONENT composition.&n; *&n; * The ERRORINFO part of each BOARD has error information&n; * that describes errors about the BOARD itself. It also has flags to&n; * indicate the COMPONENT(s) on the board that have errors. The error &n; * information specific to the COMPONENT is present in the respective &n; * COMPONENT structure.&n; *&n; * The ERRORINFO structure is also treated like a COMPONENT, ie. the &n; * BOARD has pointers(offset) to the ERRORINFO structure. The rboard&n; * structure also has a pointer to the ERRORINFO structure. This is &n; * the place to store ERRORINFO about a REMOTE NODE, if the HUB on&n; * that NODE is not working or if the REMOTE MEMORY is BAD. In cases where &n; * only the CPU of the REMOTE NODE is disabled, the ERRORINFO pointer can&n; * be a NODE NUMBER, REMOTE OFFSET combination, pointing to error info &n; * which is present on the REMOTE NODE.(TBD)&n; * REMOTE ERRINFO can be stored on any of the nearest nodes &n; * or on all the nearest nodes.(TBD)&n; * Like BOARD structures, REMOTE ERRINFO structures can be built locally&n; * using the rboard errinfo pointer.&n; *&n; * In order to get useful information from this Data organization, a set of&n; * interface routines are provided (TBD). The important thing to remember while&n; * manipulating the structures, is that, the NODE number information should&n; * be used. If the NODE is non-zero (remote) then each offset should&n; * be added to the REMOTE BASE ADDR else it should be added to the LOCAL BASE ADDR. &n; * This includes offsets for BOARDS, COMPONENTS and ERRORINFO.&n; * &n; * Note that these structures do not provide much info about connectivity.&n; * That info will be part of HWGRAPH, which is an extension of the cfg_t&n; * data structure. (ref IP27prom/cfg.h) It has to be extended to include&n; * the IO part of the Network(TBD).&n; *&n; * The data structures below define the above concepts.&n; */
multiline_comment|/*&n; * BOARD classes&n; */
DECL|macro|KLCLASS_MASK
mdefine_line|#define KLCLASS_MASK&t;0xf0   
DECL|macro|KLCLASS_NONE
mdefine_line|#define KLCLASS_NONE&t;0x00
DECL|macro|KLCLASS_NODE
mdefine_line|#define KLCLASS_NODE&t;0x10             /* CPU, Memory and HUB board */
DECL|macro|KLCLASS_CPU
mdefine_line|#define KLCLASS_CPU&t;KLCLASS_NODE&t;
DECL|macro|KLCLASS_IO
mdefine_line|#define KLCLASS_IO&t;0x20             /* BaseIO, 4 ch SCSI, ethernet, FDDI &n;&t;&t;&t;&t;&t;    and the non-graphics widget boards */
DECL|macro|KLCLASS_ROUTER
mdefine_line|#define KLCLASS_ROUTER&t;0x30             /* Router board */
DECL|macro|KLCLASS_MIDPLANE
mdefine_line|#define KLCLASS_MIDPLANE 0x40            /* We need to treat this as a board&n;                                            so that we can record error info */
DECL|macro|KLCLASS_IOBRICK
mdefine_line|#define KLCLASS_IOBRICK&t;0x70&t;&t;/* IP35 iobrick */
DECL|macro|KLCLASS_MAX
mdefine_line|#define KLCLASS_MAX&t;8&t;&t;/* Bump this if a new CLASS is added */
DECL|macro|KLCLASS
mdefine_line|#define KLCLASS(_x) ((_x) &amp; KLCLASS_MASK)
multiline_comment|/*&n; * board types&n; */
DECL|macro|KLTYPE_MASK
mdefine_line|#define KLTYPE_MASK&t;0x0f
DECL|macro|KLTYPE
mdefine_line|#define KLTYPE(_x)      ((_x) &amp; KLTYPE_MASK)
DECL|macro|KLTYPE_SNIA
mdefine_line|#define KLTYPE_SNIA&t;(KLCLASS_CPU | 0x1)
DECL|macro|KLTYPE_TIO
mdefine_line|#define KLTYPE_TIO&t;(KLCLASS_CPU | 0x2)
DECL|macro|KLTYPE_ROUTER
mdefine_line|#define KLTYPE_ROUTER     (KLCLASS_ROUTER | 0x1)
DECL|macro|KLTYPE_META_ROUTER
mdefine_line|#define KLTYPE_META_ROUTER (KLCLASS_ROUTER | 0x3)
DECL|macro|KLTYPE_REPEATER_ROUTER
mdefine_line|#define KLTYPE_REPEATER_ROUTER (KLCLASS_ROUTER | 0x4)
DECL|macro|KLTYPE_IOBRICK_XBOW
mdefine_line|#define KLTYPE_IOBRICK_XBOW&t;(KLCLASS_MIDPLANE | 0x2)
DECL|macro|KLTYPE_IOBRICK
mdefine_line|#define KLTYPE_IOBRICK&t;&t;(KLCLASS_IOBRICK | 0x0)
DECL|macro|KLTYPE_NBRICK
mdefine_line|#define KLTYPE_NBRICK&t;&t;(KLCLASS_IOBRICK | 0x4)
DECL|macro|KLTYPE_PXBRICK
mdefine_line|#define KLTYPE_PXBRICK&t;&t;(KLCLASS_IOBRICK | 0x6)
DECL|macro|KLTYPE_IXBRICK
mdefine_line|#define KLTYPE_IXBRICK&t;&t;(KLCLASS_IOBRICK | 0x7)
DECL|macro|KLTYPE_CGBRICK
mdefine_line|#define KLTYPE_CGBRICK&t;&t;(KLCLASS_IOBRICK | 0x8)
DECL|macro|KLTYPE_OPUSBRICK
mdefine_line|#define KLTYPE_OPUSBRICK&t;(KLCLASS_IOBRICK | 0x9)
DECL|macro|KLTYPE_SABRICK
mdefine_line|#define KLTYPE_SABRICK          (KLCLASS_IOBRICK | 0xa)
DECL|macro|KLTYPE_IABRICK
mdefine_line|#define KLTYPE_IABRICK&t;&t;(KLCLASS_IOBRICK | 0xb)
DECL|macro|KLTYPE_PABRICK
mdefine_line|#define KLTYPE_PABRICK          (KLCLASS_IOBRICK | 0xc)
DECL|macro|KLTYPE_GABRICK
mdefine_line|#define KLTYPE_GABRICK&t;&t;(KLCLASS_IOBRICK | 0xd)
multiline_comment|/* &n; * board structures&n; */
DECL|macro|MAX_COMPTS_PER_BRD
mdefine_line|#define MAX_COMPTS_PER_BRD 24
DECL|struct|lboard_s
r_typedef
r_struct
id|lboard_s
(brace
DECL|member|brd_next_any
id|klconf_off_t
id|brd_next_any
suffix:semicolon
multiline_comment|/* Next BOARD */
DECL|member|struct_type
r_int
r_char
id|struct_type
suffix:semicolon
multiline_comment|/* type of structure, local or remote */
DECL|member|brd_type
r_int
r_char
id|brd_type
suffix:semicolon
multiline_comment|/* type+class */
DECL|member|brd_sversion
r_int
r_char
id|brd_sversion
suffix:semicolon
multiline_comment|/* version of this structure */
DECL|member|brd_brevision
r_int
r_char
id|brd_brevision
suffix:semicolon
multiline_comment|/* board revision */
DECL|member|brd_promver
r_int
r_char
id|brd_promver
suffix:semicolon
multiline_comment|/* board prom version, if any */
DECL|member|brd_flags
r_int
r_char
id|brd_flags
suffix:semicolon
multiline_comment|/* Enabled, Disabled etc */
DECL|member|brd_slot
r_int
r_char
id|brd_slot
suffix:semicolon
multiline_comment|/* slot number */
DECL|member|brd_debugsw
r_int
r_int
id|brd_debugsw
suffix:semicolon
multiline_comment|/* Debug switches */
DECL|member|brd_geoid
id|geoid_t
id|brd_geoid
suffix:semicolon
multiline_comment|/* geo id */
DECL|member|brd_partition
id|partid_t
id|brd_partition
suffix:semicolon
multiline_comment|/* Partition number */
DECL|member|brd_diagval
r_int
r_int
id|brd_diagval
suffix:semicolon
multiline_comment|/* diagnostic value */
DECL|member|brd_diagparm
r_int
r_int
id|brd_diagparm
suffix:semicolon
multiline_comment|/* diagnostic parameter */
DECL|member|brd_inventory
r_int
r_char
id|brd_inventory
suffix:semicolon
multiline_comment|/* inventory history */
DECL|member|brd_numcompts
r_int
r_char
id|brd_numcompts
suffix:semicolon
multiline_comment|/* Number of components */
DECL|member|brd_nic
id|nic_t
id|brd_nic
suffix:semicolon
multiline_comment|/* Number in CAN */
DECL|member|brd_nasid
id|nasid_t
id|brd_nasid
suffix:semicolon
multiline_comment|/* passed parameter */
DECL|member|brd_compts
id|klconf_off_t
id|brd_compts
(braket
id|MAX_COMPTS_PER_BRD
)braket
suffix:semicolon
multiline_comment|/* pointers to COMPONENTS */
DECL|member|brd_errinfo
id|klconf_off_t
id|brd_errinfo
suffix:semicolon
multiline_comment|/* Board&squot;s error information */
DECL|member|brd_parent
r_struct
id|lboard_s
op_star
id|brd_parent
suffix:semicolon
multiline_comment|/* Logical parent for this brd */
DECL|member|pad0
r_char
id|pad0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|brd_confidence
r_int
r_char
id|brd_confidence
suffix:semicolon
multiline_comment|/* confidence that the board is bad */
DECL|member|brd_owner
id|nasid_t
id|brd_owner
suffix:semicolon
multiline_comment|/* who owns this board */
DECL|member|brd_nic_flags
r_int
r_char
id|brd_nic_flags
suffix:semicolon
multiline_comment|/* To handle 8 more NICs */
DECL|member|pad1
r_char
id|pad1
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* future expansion */
DECL|member|brd_name
r_char
id|brd_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|brd_next_same_host
id|nasid_t
id|brd_next_same_host
suffix:semicolon
multiline_comment|/* host of next brd w/same nasid */
DECL|member|brd_next_same
id|klconf_off_t
id|brd_next_same
suffix:semicolon
multiline_comment|/* Next BOARD with same nasid */
DECL|typedef|lboard_t
)brace
id|lboard_t
suffix:semicolon
DECL|macro|KLCF_NUM_COMPS
mdefine_line|#define KLCF_NUM_COMPS(_brd)&t;((_brd)-&gt;brd_numcompts)
DECL|macro|NODE_OFFSET_TO_KLINFO
mdefine_line|#define NODE_OFFSET_TO_KLINFO(n,off)    ((klinfo_t*) TO_NODE_CAC(n,off))
DECL|macro|KLCF_NEXT
mdefine_line|#define KLCF_NEXT(_brd)         &bslash;&n;        ((_brd)-&gt;brd_next_same ?     &bslash;&n;         (NODE_OFFSET_TO_LBOARD((_brd)-&gt;brd_next_same_host, (_brd)-&gt;brd_next_same)): NULL)
DECL|macro|KLCF_NEXT_ANY
mdefine_line|#define KLCF_NEXT_ANY(_brd)         &bslash;&n;        ((_brd)-&gt;brd_next_any ?     &bslash;&n;         (NODE_OFFSET_TO_LBOARD(NASID_GET(_brd), (_brd)-&gt;brd_next_any)): NULL)
DECL|macro|KLCF_COMP
mdefine_line|#define KLCF_COMP(_brd, _ndx)   &bslash;&n;                ((((_brd)-&gt;brd_compts[(_ndx)]) == 0) ? 0 : &bslash;&n;&t;&t;&t;(NODE_OFFSET_TO_KLINFO(NASID_GET(_brd), (_brd)-&gt;brd_compts[(_ndx)])))
multiline_comment|/*&n; * Generic info structure. This stores common info about a &n; * component.&n; */
DECL|struct|klinfo_s
r_typedef
r_struct
id|klinfo_s
(brace
multiline_comment|/* Generic info */
DECL|member|struct_type
r_int
r_char
id|struct_type
suffix:semicolon
multiline_comment|/* type of this structure */
DECL|member|struct_version
r_int
r_char
id|struct_version
suffix:semicolon
multiline_comment|/* version of this structure */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* Enabled, disabled etc */
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
multiline_comment|/* component revision */
DECL|member|diagval
r_int
r_int
id|diagval
suffix:semicolon
multiline_comment|/* result of diagnostics */
DECL|member|diagparm
r_int
r_int
id|diagparm
suffix:semicolon
multiline_comment|/* diagnostic parameter */
DECL|member|inventory
r_int
r_char
id|inventory
suffix:semicolon
multiline_comment|/* previous inventory status */
DECL|member|partid
r_int
r_int
id|partid
suffix:semicolon
multiline_comment|/* widget part number */
DECL|member|nic
id|nic_t
id|nic
suffix:semicolon
multiline_comment|/* MUst be aligned properly */
DECL|member|physid
r_int
r_char
id|physid
suffix:semicolon
multiline_comment|/* physical id of component */
DECL|member|virtid
r_int
r_int
id|virtid
suffix:semicolon
multiline_comment|/* virtual id as seen by system */
DECL|member|widid
r_int
r_char
id|widid
suffix:semicolon
multiline_comment|/* Widget id - if applicable */
DECL|member|nasid
id|nasid_t
id|nasid
suffix:semicolon
multiline_comment|/* node number - from parent */
DECL|member|pad1
r_char
id|pad1
suffix:semicolon
multiline_comment|/* pad out structure. */
DECL|member|pad2
r_char
id|pad2
suffix:semicolon
multiline_comment|/* pad out structure. */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|errinfo
id|klconf_off_t
id|errinfo
suffix:semicolon
multiline_comment|/* component specific errors */
DECL|member|pad3
r_int
r_int
id|pad3
suffix:semicolon
multiline_comment|/* pci fields have moved over to */
DECL|member|pad4
r_int
r_int
id|pad4
suffix:semicolon
multiline_comment|/* klbri_t */
DECL|typedef|klinfo_t
)brace
id|klinfo_t
suffix:semicolon
DECL|function|find_lboard_any
r_static
r_inline
id|lboard_t
op_star
id|find_lboard_any
c_func
(paren
id|lboard_t
op_star
id|start
comma
r_int
r_char
id|brd_type
)paren
(brace
multiline_comment|/* Search all boards stored on this node. */
r_while
c_loop
(paren
id|start
)paren
(brace
r_if
c_cond
(paren
id|start-&gt;brd_type
op_eq
id|brd_type
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|KLCF_NEXT_ANY
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t find it. */
r_return
(paren
id|lboard_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* external declarations of Linux kernel functions. */
r_extern
id|lboard_t
op_star
id|root_lboard
(braket
)braket
suffix:semicolon
r_extern
id|klinfo_t
op_star
id|find_component
c_func
(paren
id|lboard_t
op_star
id|brd
comma
id|klinfo_t
op_star
id|kli
comma
r_int
r_char
id|type
)paren
suffix:semicolon
r_extern
id|klinfo_t
op_star
id|find_first_component
c_func
(paren
id|lboard_t
op_star
id|brd
comma
r_int
r_char
id|type
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_KLCONFIG_H */
eof
