multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/klconfig.h&gt;.&n; *&n; * Copyright (C) 1992-1997,1999,2001-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IA64_SN_KLCONFIG_H
DECL|macro|_ASM_IA64_SN_KLCONFIG_H
mdefine_line|#define _ASM_IA64_SN_KLCONFIG_H
multiline_comment|/*&n; * The KLCONFIG structures store info about the various BOARDs found&n; * during Hardware Discovery. In addition, it stores info about the&n; * components found on the BOARDs.&n; */
multiline_comment|/*&n; * WARNING:&n; *&t;Certain assembly language routines (notably xxxxx.s) in the IP27PROM &n; *&t;will depend on the format of the data structures in this file.  In &n; *      most cases, rearranging the fields can seriously break things.   &n; *      Adding fields in the beginning or middle can also break things.&n; *      Add fields if necessary, to the end of a struct in such a way&n; *      that offsets of existing fields do not change.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/slotnum.h&gt;
macro_line|#include &lt;asm/sn/router.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/vector.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/kldir.h&gt;
macro_line|#include &lt;asm/sn/sn_fru.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_md.h&gt;
macro_line|#include &lt;asm/sn/geo.h&gt;
DECL|macro|KLCFGINFO_MAGIC
mdefine_line|#define KLCFGINFO_MAGIC&t;0xbeedbabe
DECL|typedef|klconf_off_t
r_typedef
id|s32
id|klconf_off_t
suffix:semicolon
DECL|macro|MAX_MODULE_ID
mdefine_line|#define&t;MAX_MODULE_ID&t;&t;255
DECL|macro|SIZE_PAD
mdefine_line|#define SIZE_PAD&t;&t;4096 /* 4k padding for structures */
multiline_comment|/* &n; * 1 NODE brick, 3 Router bricks (1 local, 1 meta, 1 repeater),&n; * 6 XIO Widgets, 1 Xbow, 1 gfx&n; */
DECL|macro|MAX_SLOTS_PER_NODE
mdefine_line|#define MAX_SLOTS_PER_NODE&t;(1 + 3 + 6 + 1 + 1) 
multiline_comment|/* XXX if each node is guranteed to have some memory */
DECL|macro|MAX_PCI_DEVS
mdefine_line|#define MAX_PCI_DEVS&t;&t;8
multiline_comment|/* lboard_t-&gt;brd_flags fields */
multiline_comment|/* All bits in this field are currently used. Try the pad fields if&n;   you need more flag bits */
DECL|macro|ENABLE_BOARD
mdefine_line|#define ENABLE_BOARD &t;&t;0x01
DECL|macro|FAILED_BOARD
mdefine_line|#define FAILED_BOARD  &t;&t;0x02
DECL|macro|DUPLICATE_BOARD
mdefine_line|#define DUPLICATE_BOARD &t;0x04    /* Boards like midplanes/routers which&n;                                   &t;   are discovered twice. Use one of them */
DECL|macro|VISITED_BOARD
mdefine_line|#define VISITED_BOARD&t;&t;0x08&t;/* Used for compact hub numbering. */
DECL|macro|LOCAL_MASTER_IO6
mdefine_line|#define LOCAL_MASTER_IO6&t;0x10    /* master io6 for that node */
DECL|macro|KLTYPE_IOBRICK_XBOW
mdefine_line|#define KLTYPE_IOBRICK_XBOW&t;(KLCLASS_MIDPLANE | 0x2)
multiline_comment|/* klinfo-&gt;flags fields */
DECL|macro|KLINFO_ENABLE
mdefine_line|#define KLINFO_ENABLE &t;&t;0x01    /* This component is enabled */
DECL|macro|KLINFO_FAILED
mdefine_line|#define KLINFO_FAILED   &t;0x02 &t;/* This component failed */
DECL|macro|KLINFO_DEVICE
mdefine_line|#define KLINFO_DEVICE   &t;0x04 &t;/* This component is a device */
DECL|macro|KLINFO_VISITED
mdefine_line|#define KLINFO_VISITED  &t;0x08 &t;/* This component has been visited */
DECL|macro|KLINFO_CONTROLLER
mdefine_line|#define KLINFO_CONTROLLER   &t;0x10 &t;/* This component is a device controller */
DECL|macro|KLINFO_INSTALL
mdefine_line|#define KLINFO_INSTALL   &t;0x20  &t;/* Install a driver */
DECL|macro|KLINFO_HEADLESS
mdefine_line|#define&t;KLINFO_HEADLESS&t;&t;0x40&t;/* Headless (or hubless) component */
multiline_comment|/* Structures to manage various data storage areas */
multiline_comment|/* The numbers must be contiguous since the array index i&n;   is used in the code to allocate various areas. &n;*/
DECL|macro|BOARD_STRUCT
mdefine_line|#define BOARD_STRUCT &t;&t;0
DECL|macro|COMPONENT_STRUCT
mdefine_line|#define COMPONENT_STRUCT &t;1
DECL|macro|ERRINFO_STRUCT
mdefine_line|#define ERRINFO_STRUCT &t;&t;2
DECL|macro|KLMALLOC_TYPE_MAX
mdefine_line|#define KLMALLOC_TYPE_MAX &t;(ERRINFO_STRUCT + 1)
DECL|macro|DEVICE_STRUCT
mdefine_line|#define DEVICE_STRUCT &t;&t;3
DECL|struct|console_s
r_typedef
r_struct
id|console_s
(brace
DECL|member|uart_base
id|__psunsigned_t
id|uart_base
suffix:semicolon
DECL|member|config_base
id|__psunsigned_t
id|config_base
suffix:semicolon
DECL|member|memory_base
id|__psunsigned_t
id|memory_base
suffix:semicolon
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|flag
r_int
id|flag
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|nasid
id|nasid_t
id|nasid
suffix:semicolon
DECL|member|wid
r_char
id|wid
suffix:semicolon
DECL|member|npci
r_char
id|npci
suffix:semicolon
DECL|member|baseio_nic
id|nic_t
id|baseio_nic
suffix:semicolon
DECL|typedef|console_t
)brace
id|console_t
suffix:semicolon
DECL|struct|klc_malloc_hdr
r_typedef
r_struct
id|klc_malloc_hdr
(brace
DECL|member|km_base
id|klconf_off_t
id|km_base
suffix:semicolon
DECL|member|km_limit
id|klconf_off_t
id|km_limit
suffix:semicolon
DECL|member|km_current
id|klconf_off_t
id|km_current
suffix:semicolon
DECL|typedef|klc_malloc_hdr_t
)brace
id|klc_malloc_hdr_t
suffix:semicolon
multiline_comment|/* Functions/macros needed to use this structure */
DECL|struct|kl_config_hdr
r_typedef
r_struct
id|kl_config_hdr
(brace
DECL|member|ch_magic
id|u64
id|ch_magic
suffix:semicolon
multiline_comment|/* set this to KLCFGINFO_MAGIC */
DECL|member|ch_version
id|u32
id|ch_version
suffix:semicolon
multiline_comment|/* structure version number */
DECL|member|ch_malloc_hdr_off
id|klconf_off_t
id|ch_malloc_hdr_off
suffix:semicolon
multiline_comment|/* offset of ch_malloc_hdr */
DECL|member|ch_cons_off
id|klconf_off_t
id|ch_cons_off
suffix:semicolon
multiline_comment|/* offset of ch_cons */
DECL|member|ch_board_info
id|klconf_off_t
id|ch_board_info
suffix:semicolon
multiline_comment|/* the link list of boards */
DECL|member|ch_cons_info
id|console_t
id|ch_cons_info
suffix:semicolon
multiline_comment|/* address info of the console */
DECL|member|ch_malloc_hdr
id|klc_malloc_hdr_t
id|ch_malloc_hdr
(braket
id|KLMALLOC_TYPE_MAX
)braket
suffix:semicolon
DECL|member|ch_sw_belief
id|confidence_t
id|ch_sw_belief
suffix:semicolon
multiline_comment|/* confidence that software is bad*/
DECL|member|ch_sn0net_belief
id|confidence_t
id|ch_sn0net_belief
suffix:semicolon
multiline_comment|/* confidence that sn0net is bad */
DECL|typedef|kl_config_hdr_t
)brace
id|kl_config_hdr_t
suffix:semicolon
DECL|macro|KL_CONFIG_HDR
mdefine_line|#define KL_CONFIG_HDR(_nasid) &t;((kl_config_hdr_t *)(KLCONFIG_ADDR(_nasid)))
DECL|macro|NODE_OFFSET_TO_LBOARD
mdefine_line|#define NODE_OFFSET_TO_LBOARD(nasid,off)        (lboard_t*)(NODE_CAC_BASE(nasid) + (off))
DECL|macro|KL_CONFIG_INFO
mdefine_line|#define KL_CONFIG_INFO(_nasid) root_lboard[nasid_to_cnodeid(_nasid)]
multiline_comment|/* --- New Macros for the changed kl_config_hdr_t structure --- */
DECL|macro|PTR_CH_CONS_INFO
mdefine_line|#define PTR_CH_CONS_INFO(_k)&t;((console_t *)&bslash;&n;&t;&t;&t;((__psunsigned_t)_k + (_k-&gt;ch_cons_off)))
DECL|macro|KL_CONFIG_CH_CONS_INFO
mdefine_line|#define KL_CONFIG_CH_CONS_INFO(_n)   PTR_CH_CONS_INFO(KL_CONFIG_HDR(_n))
multiline_comment|/* ------------------------------------------------------------- */
DECL|macro|KL_CONFIG_DUPLICATE_BOARD
mdefine_line|#define KL_CONFIG_DUPLICATE_BOARD(_brd)&t;((_brd)-&gt;brd_flags &amp; DUPLICATE_BOARD)
DECL|macro|XBOW_PORT_TYPE_HUB
mdefine_line|#define XBOW_PORT_TYPE_HUB(_xbowp, _link) &t;&bslash;&n;               ((_xbowp)-&gt;xbow_port_info[(_link) - BASE_XBOW_PORT].port_flag &amp; XBOW_PORT_HUB)
DECL|macro|XBOW_PORT_TYPE_IO
mdefine_line|#define XBOW_PORT_TYPE_IO(_xbowp, _link) &t;&bslash;&n;               ((_xbowp)-&gt;xbow_port_info[(_link) - BASE_XBOW_PORT].port_flag &amp; XBOW_PORT_IO)
DECL|macro|XBOW_PORT_IS_ENABLED
mdefine_line|#define XBOW_PORT_IS_ENABLED(_xbowp, _link) &t;&bslash;&n;               ((_xbowp)-&gt;xbow_port_info[(_link) - BASE_XBOW_PORT].port_flag &amp; XBOW_PORT_ENABLE)
DECL|macro|XBOW_PORT_NASID
mdefine_line|#define XBOW_PORT_NASID(_xbowp, _link) &t;&bslash;&n;               ((_xbowp)-&gt;xbow_port_info[(_link) - BASE_XBOW_PORT].port_nasid)
DECL|macro|XBOW_PORT_IO
mdefine_line|#define XBOW_PORT_IO     0x1
DECL|macro|XBOW_PORT_HUB
mdefine_line|#define XBOW_PORT_HUB    0x2
DECL|macro|XBOW_PORT_ENABLE
mdefine_line|#define XBOW_PORT_ENABLE 0x4
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
DECL|macro|KLCLASS_GFX
mdefine_line|#define KLCLASS_GFX&t;0x50&t;&t;/* graphics boards */
DECL|macro|KLCLASS_PSEUDO_GFX
mdefine_line|#define KLCLASS_PSEUDO_GFX&t;0x60&t;/* HDTV type cards that use a gfx&n;&t;&t;&t;&t;&t; * hw ifc to xtalk and are not gfx&n;&t;&t;&t;&t;&t; * class for sw purposes */
DECL|macro|KLCLASS_IOBRICK
mdefine_line|#define KLCLASS_IOBRICK&t;0x70&t;&t;/* IP35 iobrick */
DECL|macro|KLCLASS_MAX
mdefine_line|#define KLCLASS_MAX&t;8&t;&t;/* Bump this if a new CLASS is added */
DECL|macro|KLTYPE_MAX
mdefine_line|#define KLTYPE_MAX&t;11&t;&t;/* Bump this if a new CLASS is added */
DECL|macro|KLCLASS_UNKNOWN
mdefine_line|#define KLCLASS_UNKNOWN&t;0xf0
DECL|macro|KLCLASS
mdefine_line|#define KLCLASS(_x) ((_x) &amp; KLCLASS_MASK)
multiline_comment|/*&n; * board types&n; */
DECL|macro|KLTYPE_MASK
mdefine_line|#define KLTYPE_MASK&t;0x0f
DECL|macro|KLTYPE_NONE
mdefine_line|#define KLTYPE_NONE&t;0x00
DECL|macro|KLTYPE_EMPTY
mdefine_line|#define KLTYPE_EMPTY&t;0x00
DECL|macro|KLTYPE_WEIRDCPU
mdefine_line|#define KLTYPE_WEIRDCPU (KLCLASS_CPU | 0x0)
DECL|macro|KLTYPE_SNIA
mdefine_line|#define KLTYPE_SNIA&t;(KLCLASS_CPU | 0x1)
DECL|macro|KLTYPE_ROUTER
mdefine_line|#define KLTYPE_ROUTER     (KLCLASS_ROUTER | 0x1)
DECL|macro|KLTYPE_META_ROUTER
mdefine_line|#define KLTYPE_META_ROUTER (KLCLASS_ROUTER | 0x3)
DECL|macro|KLTYPE_REPEATER_ROUTER
mdefine_line|#define KLTYPE_REPEATER_ROUTER (KLCLASS_ROUTER | 0x4)
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
multiline_comment|/* The value of type should be more than 8 so that hinv prints&n; * out the board name from the NIC string. For values less than&n; * 8 the name of the board needs to be hard coded in a few places.&n; * When bringup started nic names had not standardized and so we&n; * had to hard code. (For people interested in history.) &n; */
DECL|macro|KLTYPE_UNKNOWN
mdefine_line|#define KLTYPE_UNKNOWN&t;(KLCLASS_UNKNOWN | 0xf)
DECL|macro|KLTYPE
mdefine_line|#define KLTYPE(_x) &t;((_x) &amp; KLTYPE_MASK)
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
id|confidence_t
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
multiline_comment|/*&n; *&t;Make sure we pass back the calias space address for local boards.&n; *&t;klconfig board traversal and error structure extraction defines.&n; */
DECL|macro|BOARD_SLOT
mdefine_line|#define BOARD_SLOT(_brd)&t;((_brd)-&gt;brd_slot)
DECL|macro|KLCF_CLASS
mdefine_line|#define KLCF_CLASS(_brd)&t;KLCLASS((_brd)-&gt;brd_type)
DECL|macro|KLCF_TYPE
mdefine_line|#define KLCF_TYPE(_brd)&t;&t;KLTYPE((_brd)-&gt;brd_type)
DECL|macro|KLCF_NUM_COMPS
mdefine_line|#define KLCF_NUM_COMPS(_brd)&t;((_brd)-&gt;brd_numcompts)
DECL|macro|KLCF_MODULE_ID
mdefine_line|#define KLCF_MODULE_ID(_brd)&t;((_brd)-&gt;brd_module)
DECL|macro|NODE_OFFSET_TO_KLINFO
mdefine_line|#define NODE_OFFSET_TO_KLINFO(n,off)    ((klinfo_t*) TO_NODE_CAC(n,off))
DECL|macro|KLCF_NEXT
mdefine_line|#define KLCF_NEXT(_brd)         &bslash;&n;        ((_brd)-&gt;brd_next_same ?     &bslash;&n;         (NODE_OFFSET_TO_LBOARD((_brd)-&gt;brd_next_same_host, (_brd)-&gt;brd_next_same)): NULL)
DECL|macro|KLCF_NEXT_ANY
mdefine_line|#define KLCF_NEXT_ANY(_brd)         &bslash;&n;        ((_brd)-&gt;brd_next_any ?     &bslash;&n;         (NODE_OFFSET_TO_LBOARD(NASID_GET(_brd), (_brd)-&gt;brd_next_any)): NULL)
DECL|macro|KLCF_COMP
mdefine_line|#define KLCF_COMP(_brd, _ndx)   &bslash;&n;                ((((_brd)-&gt;brd_compts[(_ndx)]) == 0) ? 0 : &bslash;&n;&t;&t;&t;(NODE_OFFSET_TO_KLINFO(NASID_GET(_brd), (_brd)-&gt;brd_compts[(_ndx)])))
DECL|macro|KLCF_COMP_TYPE
mdefine_line|#define KLCF_COMP_TYPE(_comp)&t;((_comp)-&gt;struct_type)
DECL|macro|KLCF_BRIDGE_W_ID
mdefine_line|#define KLCF_BRIDGE_W_ID(_comp)&t;((_comp)-&gt;physid)&t;/* Widget ID */
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
DECL|macro|KLCONFIG_INFO_ENABLED
mdefine_line|#define KLCONFIG_INFO_ENABLED(_i)&t;((_i)-&gt;flags &amp; KLINFO_ENABLE)
multiline_comment|/*&n; * Component structures.&n; * Following are the currently identified components:&n; * &t;CPU, HUB, MEM_BANK, &n; * &t;XBOW(consists of 16 WIDGETs, each of which can be HUB or GRAPHICS or BRIDGE)&n; * &t;BRIDGE, IOC3, SuperIO, SCSI, FDDI &n; * &t;ROUTER&n; * &t;GRAPHICS&n; */
DECL|macro|KLSTRUCT_UNKNOWN
mdefine_line|#define KLSTRUCT_UNKNOWN&t;0
DECL|macro|KLSTRUCT_CPU
mdefine_line|#define KLSTRUCT_CPU  &t;&t;1
DECL|macro|KLSTRUCT_HUB
mdefine_line|#define KLSTRUCT_HUB  &t;&t;2
DECL|macro|KLSTRUCT_MEMBNK
mdefine_line|#define KLSTRUCT_MEMBNK &t;3
DECL|macro|KLSTRUCT_XBOW
mdefine_line|#define KLSTRUCT_XBOW &t;&t;4
DECL|macro|KLSTRUCT_BRI
mdefine_line|#define KLSTRUCT_BRI &t;&t;5
DECL|macro|KLSTRUCT_ROU
mdefine_line|#define KLSTRUCT_ROU&t;&t;9
DECL|macro|KLSTRUCT_GFX
mdefine_line|#define KLSTRUCT_GFX &t;&t;10
DECL|macro|KLSTRUCT_SCSI
mdefine_line|#define KLSTRUCT_SCSI &t;&t;11
DECL|macro|KLSTRUCT_DISK
mdefine_line|#define KLSTRUCT_DISK &t;&t;14
DECL|macro|KLSTRUCT_CDROM
mdefine_line|#define KLSTRUCT_CDROM &t;&t;16
DECL|macro|KLSTRUCT_FIBERCHANNEL
mdefine_line|#define KLSTRUCT_FIBERCHANNEL &t;25
DECL|macro|KLSTRUCT_MOD_SERIAL_NUM
mdefine_line|#define KLSTRUCT_MOD_SERIAL_NUM 26
DECL|macro|KLSTRUCT_QLFIBRE
mdefine_line|#define KLSTRUCT_QLFIBRE        32
DECL|macro|KLSTRUCT_1394
mdefine_line|#define KLSTRUCT_1394           33
DECL|macro|KLSTRUCT_USB
mdefine_line|#define KLSTRUCT_USB&t;&t;34
DECL|macro|KLSTRUCT_USBKBD
mdefine_line|#define KLSTRUCT_USBKBD&t;&t;35
DECL|macro|KLSTRUCT_USBMS
mdefine_line|#define KLSTRUCT_USBMS&t;&t;36
DECL|macro|KLSTRUCT_SCSI_CTLR
mdefine_line|#define KLSTRUCT_SCSI_CTLR&t;37
DECL|macro|KLSTRUCT_PEBRICK
mdefine_line|#define KLSTRUCT_PEBRICK&t;38
DECL|macro|KLSTRUCT_GIGE
mdefine_line|#define KLSTRUCT_GIGE           39
DECL|macro|KLSTRUCT_IDE
mdefine_line|#define KLSTRUCT_IDE&t;&t;40
DECL|macro|KLSTRUCT_IOC4
mdefine_line|#define KLSTRUCT_IOC4&t;&t;41
DECL|macro|KLSTRUCT_IOC4UART
mdefine_line|#define KLSTRUCT_IOC4UART&t;42
DECL|macro|KLSTRUCT_IOC4_TTY
mdefine_line|#define KLSTRUCT_IOC4_TTY&t;43
DECL|macro|KLSTRUCT_IOC4PCKM
mdefine_line|#define KLSTRUCT_IOC4PCKM&t;44
DECL|macro|KLSTRUCT_IOC4MS
mdefine_line|#define KLSTRUCT_IOC4MS&t;&t;45
DECL|macro|KLSTRUCT_IOC4_ATA
mdefine_line|#define KLSTRUCT_IOC4_ATA&t;46
DECL|macro|KLSTRUCT_PCIGFX
mdefine_line|#define KLSTRUCT_PCIGFX&t;&t;47
multiline_comment|/*&n; * The port info in ip27_cfg area translates to a lboart_t in the &n; * KLCONFIG area. But since KLCONFIG does not use pointers, lboart_t&n; * is stored in terms of a nasid and a offset from start of KLCONFIG &n; * area  on that nasid.&n; */
DECL|struct|klport_s
r_typedef
r_struct
id|klport_s
(brace
DECL|member|port_nasid
id|nasid_t
id|port_nasid
suffix:semicolon
DECL|member|port_flag
r_int
r_char
id|port_flag
suffix:semicolon
DECL|member|port_offset
id|klconf_off_t
id|port_offset
suffix:semicolon
DECL|member|port_num
r_int
id|port_num
suffix:semicolon
DECL|typedef|klport_t
)brace
id|klport_t
suffix:semicolon
DECL|struct|klcpu_s
r_typedef
r_struct
id|klcpu_s
(brace
multiline_comment|/* CPU */
DECL|member|cpu_info
id|klinfo_t
id|cpu_info
suffix:semicolon
DECL|member|cpu_prid
r_int
r_int
id|cpu_prid
suffix:semicolon
multiline_comment|/* Processor PRID value */
DECL|member|cpu_fpirr
r_int
r_int
id|cpu_fpirr
suffix:semicolon
multiline_comment|/* FPU IRR value */
DECL|member|cpu_speed
r_int
r_int
id|cpu_speed
suffix:semicolon
multiline_comment|/* Speed in MHZ */
DECL|member|cpu_scachesz
r_int
r_int
id|cpu_scachesz
suffix:semicolon
multiline_comment|/* secondary cache size in MB */
DECL|member|cpu_scachespeed
r_int
r_int
id|cpu_scachespeed
suffix:semicolon
multiline_comment|/* secondary cache speed in MHz */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klcpu_t
)brace
id|klcpu_t
suffix:semicolon
DECL|macro|CPU_STRUCT_VERSION
mdefine_line|#define CPU_STRUCT_VERSION   2
DECL|struct|klhub_s
r_typedef
r_struct
id|klhub_s
(brace
multiline_comment|/* HUB */
DECL|member|hub_info
id|klinfo_t
id|hub_info
suffix:semicolon
DECL|member|hub_flags
r_int
r_int
id|hub_flags
suffix:semicolon
multiline_comment|/* PCFG_HUB_xxx flags */
DECL|macro|MAX_NI_PORTS
mdefine_line|#define MAX_NI_PORTS                    2
DECL|member|hub_port
id|klport_t
id|hub_port
(braket
id|MAX_NI_PORTS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* hub is connected to this */
DECL|member|hub_box_nic
id|nic_t
id|hub_box_nic
suffix:semicolon
multiline_comment|/* nic of containing box */
DECL|member|hub_mfg_nic
id|klconf_off_t
id|hub_mfg_nic
suffix:semicolon
multiline_comment|/* MFG NIC string */
DECL|member|hub_speed
id|u64
id|hub_speed
suffix:semicolon
multiline_comment|/* Speed of hub in HZ */
DECL|member|hub_io_module
id|moduleid_t
id|hub_io_module
suffix:semicolon
multiline_comment|/* attached io module */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klhub_t
)brace
id|klhub_t
suffix:semicolon
DECL|struct|klhub_uart_s
r_typedef
r_struct
id|klhub_uart_s
(brace
multiline_comment|/* HUB */
DECL|member|hubuart_info
id|klinfo_t
id|hubuart_info
suffix:semicolon
DECL|member|hubuart_flags
r_int
r_int
id|hubuart_flags
suffix:semicolon
multiline_comment|/* PCFG_HUB_xxx flags */
DECL|member|hubuart_box_nic
id|nic_t
id|hubuart_box_nic
suffix:semicolon
multiline_comment|/* nic of containing box */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klhub_uart_t
)brace
id|klhub_uart_t
suffix:semicolon
DECL|macro|MEMORY_STRUCT_VERSION
mdefine_line|#define MEMORY_STRUCT_VERSION   2
DECL|struct|klmembnk_s
r_typedef
r_struct
id|klmembnk_s
(brace
multiline_comment|/* MEMORY BANK */
DECL|member|membnk_info
id|klinfo_t
id|membnk_info
suffix:semicolon
DECL|member|membnk_memsz
r_int
id|membnk_memsz
suffix:semicolon
multiline_comment|/* Total memory in megabytes */
DECL|member|membnk_dimm_select
r_int
id|membnk_dimm_select
suffix:semicolon
multiline_comment|/* bank to physical addr mapping*/
DECL|member|membnk_bnksz
r_int
id|membnk_bnksz
(braket
id|MD_MEM_BANKS
)braket
suffix:semicolon
multiline_comment|/* Memory bank sizes */
DECL|member|membnk_attr
r_int
id|membnk_attr
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klmembnk_t
)brace
id|klmembnk_t
suffix:semicolon
DECL|macro|MAX_SERIAL_NUM_SIZE
mdefine_line|#define MAX_SERIAL_NUM_SIZE 10
DECL|struct|klmod_serial_num_s
r_typedef
r_struct
id|klmod_serial_num_s
(brace
DECL|member|snum_info
id|klinfo_t
id|snum_info
suffix:semicolon
r_union
(brace
DECL|member|snum_str
r_char
id|snum_str
(braket
id|MAX_SERIAL_NUM_SIZE
)braket
suffix:semicolon
DECL|member|snum_int
r_int
r_int
r_int
id|snum_int
suffix:semicolon
DECL|member|snum
)brace
id|snum
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klmod_serial_num_t
)brace
id|klmod_serial_num_t
suffix:semicolon
multiline_comment|/* Macros needed to access serial number structure in lboard_t.&n;   Hard coded values are necessary since we cannot treat &n;   serial number struct as a component without losing compatibility&n;   between prom versions. */
DECL|macro|GET_SNUM_COMP
mdefine_line|#define GET_SNUM_COMP(_l) &t;((klmod_serial_num_t *)&bslash;&n;&t;&t;&t;&t;KLCF_COMP(_l, _l-&gt;brd_numcompts))
DECL|macro|MAX_XBOW_LINKS
mdefine_line|#define MAX_XBOW_LINKS 16
DECL|struct|klxbow_s
r_typedef
r_struct
id|klxbow_s
(brace
multiline_comment|/* XBOW */
DECL|member|xbow_info
id|klinfo_t
id|xbow_info
suffix:semicolon
DECL|member|xbow_port_info
id|klport_t
id|xbow_port_info
(braket
id|MAX_XBOW_LINKS
)braket
suffix:semicolon
multiline_comment|/* Module number */
DECL|member|xbow_master_hub_link
r_int
id|xbow_master_hub_link
suffix:semicolon
multiline_comment|/* type of brd connected+component struct ptr+flags */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klxbow_t
)brace
id|klxbow_t
suffix:semicolon
DECL|macro|MAX_PCI_SLOTS
mdefine_line|#define MAX_PCI_SLOTS 8
DECL|struct|klpci_device_s
r_typedef
r_struct
id|klpci_device_s
(brace
DECL|member|pci_device_id
id|s32
id|pci_device_id
suffix:semicolon
multiline_comment|/* 32 bits of vendor/device ID. */
DECL|member|pci_device_pad
id|s32
id|pci_device_pad
suffix:semicolon
multiline_comment|/* 32 bits of padding. */
DECL|typedef|klpci_device_t
)brace
id|klpci_device_t
suffix:semicolon
DECL|macro|BRIDGE_STRUCT_VERSION
mdefine_line|#define BRIDGE_STRUCT_VERSION&t;2
DECL|struct|klbri_s
r_typedef
r_struct
id|klbri_s
(brace
multiline_comment|/* BRIDGE */
DECL|member|bri_info
id|klinfo_t
id|bri_info
suffix:semicolon
DECL|member|bri_eprominfo
r_int
r_char
id|bri_eprominfo
suffix:semicolon
multiline_comment|/* IO6prom connected to bridge */
DECL|member|bri_bustype
r_int
r_char
id|bri_bustype
suffix:semicolon
multiline_comment|/* PCI/VME BUS bridge/GIO */
DECL|member|pci_specific
id|u64
op_star
id|pci_specific
suffix:semicolon
multiline_comment|/* PCI Board config info */
DECL|member|bri_devices
id|klpci_device_t
id|bri_devices
(braket
id|MAX_PCI_DEVS
)braket
suffix:semicolon
multiline_comment|/* PCI IDs */
DECL|member|bri_mfg_nic
id|klconf_off_t
id|bri_mfg_nic
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klbri_t
)brace
id|klbri_t
suffix:semicolon
DECL|macro|ROUTER_VECTOR_VERS
mdefine_line|#define ROUTER_VECTOR_VERS&t;2
multiline_comment|/* XXX - Don&squot;t we need the number of ports here?!? */
DECL|struct|klrou_s
r_typedef
r_struct
id|klrou_s
(brace
multiline_comment|/* ROUTER */
DECL|member|rou_info
id|klinfo_t
id|rou_info
suffix:semicolon
DECL|member|rou_flags
r_int
r_int
id|rou_flags
suffix:semicolon
multiline_comment|/* PCFG_ROUTER_xxx flags */
DECL|member|rou_box_nic
id|nic_t
id|rou_box_nic
suffix:semicolon
multiline_comment|/* nic of the containing module */
DECL|member|rou_port
id|klport_t
id|rou_port
(braket
id|MAX_ROUTER_PORTS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* array index 1 to 6 */
DECL|member|rou_mfg_nic
id|klconf_off_t
id|rou_mfg_nic
suffix:semicolon
multiline_comment|/* MFG NIC string */
DECL|member|rou_vector
id|u64
id|rou_vector
suffix:semicolon
multiline_comment|/* vector from master node */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klrou_t
)brace
id|klrou_t
suffix:semicolon
multiline_comment|/*&n; *  Graphics Controller/Device&n; *&n; *  (IP27/IO6) Prom versions 6.13 (and 6.5.1 kernels) and earlier&n; *  used a couple different structures to store graphics information.&n; *  For compatibility reasons, the newer data structure preserves some&n; *  of the layout so that fields that are used in the old versions remain&n; *  in the same place (with the same info).  Determination of what version&n; *  of this structure we have is done by checking the cookie field.&n; */
DECL|macro|KLGFX_COOKIE
mdefine_line|#define KLGFX_COOKIE&t;0x0c0de000
DECL|struct|klgfx_s
r_typedef
r_struct
id|klgfx_s
(brace
multiline_comment|/* GRAPHICS Device */
DECL|member|gfx_info
id|klinfo_t
id|gfx_info
suffix:semicolon
DECL|member|old_gndevs
id|klconf_off_t
id|old_gndevs
suffix:semicolon
multiline_comment|/* for compatibility with older proms */
DECL|member|old_gdoff0
id|klconf_off_t
id|old_gdoff0
suffix:semicolon
multiline_comment|/* for compatibility with older proms */
DECL|member|cookie
r_int
r_int
id|cookie
suffix:semicolon
multiline_comment|/* for compatibility with older proms */
DECL|member|moduleslot
r_int
r_int
id|moduleslot
suffix:semicolon
DECL|member|gfx_next_pipe
r_struct
id|klgfx_s
op_star
id|gfx_next_pipe
suffix:semicolon
DECL|member|gfx_specific
id|u64
op_star
id|gfx_specific
suffix:semicolon
DECL|member|pad0
id|klconf_off_t
id|pad0
suffix:semicolon
multiline_comment|/* for compatibility with older proms */
DECL|member|gfx_mfg_nic
id|klconf_off_t
id|gfx_mfg_nic
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klgfx_t
)brace
id|klgfx_t
suffix:semicolon
DECL|macro|MAX_SCSI_DEVS
mdefine_line|#define MAX_SCSI_DEVS 16
multiline_comment|/*&n; * NOTE: THis is the max sized kl* structure and is used in klmalloc.c&n; * to allocate space of type COMPONENT. Make sure that if the size of&n; * any other component struct becomes more than this, then redefine&n; * that as the size to be klmalloced.&n; */
DECL|struct|klscsi_s
r_typedef
r_struct
id|klscsi_s
(brace
multiline_comment|/* SCSI Bus */
DECL|member|scsi_info
id|klinfo_t
id|scsi_info
suffix:semicolon
DECL|member|scsi_specific
id|u64
op_star
id|scsi_specific
suffix:semicolon
DECL|member|scsi_numdevs
r_int
r_char
id|scsi_numdevs
suffix:semicolon
DECL|member|scsi_devinfo
id|klconf_off_t
id|scsi_devinfo
(braket
id|MAX_SCSI_DEVS
)braket
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klscsi_t
)brace
id|klscsi_t
suffix:semicolon
DECL|struct|klscctl_s
r_typedef
r_struct
id|klscctl_s
(brace
multiline_comment|/* SCSI Controller */
DECL|member|scsi_info
id|klinfo_t
id|scsi_info
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|scsi_buscnt
r_int
r_int
id|scsi_buscnt
suffix:semicolon
multiline_comment|/* # busses this cntlr */
DECL|member|scsi_bus
r_void
op_star
id|scsi_bus
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Pointer to 2 klscsi_t&squot;s */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klscctl_t
)brace
id|klscctl_t
suffix:semicolon
DECL|struct|klscdev_s
r_typedef
r_struct
id|klscdev_s
(brace
multiline_comment|/* SCSI device */
DECL|member|scdev_info
id|klinfo_t
id|scdev_info
suffix:semicolon
DECL|member|scdev_cfg
r_struct
id|scsidisk_data
op_star
id|scdev_cfg
suffix:semicolon
multiline_comment|/* driver fills up this */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klscdev_t
)brace
id|klscdev_t
suffix:semicolon
DECL|struct|klttydev_s
r_typedef
r_struct
id|klttydev_s
(brace
multiline_comment|/* TTY device */
DECL|member|ttydev_info
id|klinfo_t
id|ttydev_info
suffix:semicolon
DECL|member|ttydev_cfg
r_struct
id|terminal_data
op_star
id|ttydev_cfg
suffix:semicolon
multiline_comment|/* driver fills up this */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klttydev_t
)brace
id|klttydev_t
suffix:semicolon
DECL|struct|klpcigfx_s
r_typedef
r_struct
id|klpcigfx_s
(brace
multiline_comment|/* PCI GFX */
DECL|member|gfx_info
id|klinfo_t
id|gfx_info
suffix:semicolon
DECL|typedef|klpcigfx_t
)brace
id|klpcigfx_t
suffix:semicolon
DECL|struct|klkbddev_s
r_typedef
r_struct
id|klkbddev_s
(brace
multiline_comment|/* KBD device */
DECL|member|kbddev_info
id|klinfo_t
id|kbddev_info
suffix:semicolon
DECL|member|kbddev_cfg
r_struct
id|keyboard_data
op_star
id|kbddev_cfg
suffix:semicolon
multiline_comment|/* driver fills up this */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klkbddev_t
)brace
id|klkbddev_t
suffix:semicolon
DECL|struct|klmsdev_s
r_typedef
r_struct
id|klmsdev_s
(brace
multiline_comment|/* mouse device */
DECL|member|msdev_info
id|klinfo_t
id|msdev_info
suffix:semicolon
DECL|member|msdev_cfg
r_void
op_star
id|msdev_cfg
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klmsdev_t
)brace
id|klmsdev_t
suffix:semicolon
multiline_comment|/*&n; * USB info&n; */
DECL|struct|klusb_s
r_typedef
r_struct
id|klusb_s
(brace
DECL|member|usb_info
id|klinfo_t
id|usb_info
suffix:semicolon
multiline_comment|/* controller info */
DECL|member|usb_bus
r_void
op_star
id|usb_bus
suffix:semicolon
multiline_comment|/* handle to usb_bus_t */
DECL|member|usb_controller
r_uint64
id|usb_controller
suffix:semicolon
multiline_comment|/* ptr to controller info */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|typedef|klusb_t
)brace
id|klusb_t
suffix:semicolon
DECL|union|klcomp_s
r_typedef
r_union
id|klcomp_s
(brace
DECL|member|kc_cpu
id|klcpu_t
id|kc_cpu
suffix:semicolon
DECL|member|kc_hub
id|klhub_t
id|kc_hub
suffix:semicolon
DECL|member|kc_mem
id|klmembnk_t
id|kc_mem
suffix:semicolon
DECL|member|kc_xbow
id|klxbow_t
id|kc_xbow
suffix:semicolon
DECL|member|kc_bri
id|klbri_t
id|kc_bri
suffix:semicolon
DECL|member|kc_rou
id|klrou_t
id|kc_rou
suffix:semicolon
DECL|member|kc_gfx
id|klgfx_t
id|kc_gfx
suffix:semicolon
DECL|member|kc_scsi
id|klscsi_t
id|kc_scsi
suffix:semicolon
DECL|member|kc_scsi_ctl
id|klscctl_t
id|kc_scsi_ctl
suffix:semicolon
DECL|member|kc_scsi_dev
id|klscdev_t
id|kc_scsi_dev
suffix:semicolon
DECL|member|kc_snum
id|klmod_serial_num_t
id|kc_snum
suffix:semicolon
DECL|member|kc_usb
id|klusb_t
id|kc_usb
suffix:semicolon
DECL|typedef|klcomp_t
)brace
id|klcomp_t
suffix:semicolon
DECL|union|kldev_s
r_typedef
r_union
id|kldev_s
(brace
multiline_comment|/* for device structure allocation */
DECL|member|kc_scsi_dev
id|klscdev_t
id|kc_scsi_dev
suffix:semicolon
DECL|member|kc_tty_dev
id|klttydev_t
id|kc_tty_dev
suffix:semicolon
DECL|member|kc_kbd_dev
id|klkbddev_t
id|kc_kbd_dev
suffix:semicolon
DECL|typedef|kldev_t
)brace
id|kldev_t
suffix:semicolon
multiline_comment|/* external declarations of Linux kernel functions. */
r_extern
id|lboard_t
op_star
id|root_lboard
(braket
)braket
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_lboard
c_func
(paren
id|lboard_t
op_star
id|start
comma
r_int
r_char
id|type
)paren
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
r_extern
id|klcpu_t
op_star
id|nasid_slice_to_cpuinfo
c_func
(paren
id|nasid_t
comma
r_int
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_gfxpipe
c_func
(paren
r_int
id|pipenum
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_lboard_class
c_func
(paren
id|lboard_t
op_star
id|start
comma
r_int
r_char
id|brd_class
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_nic_lboard
c_func
(paren
id|lboard_t
op_star
comma
id|nic_t
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_nic_type_lboard
c_func
(paren
id|nasid_t
comma
r_int
r_char
comma
id|nic_t
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_lboard_modslot
c_func
(paren
id|lboard_t
op_star
id|start
comma
id|geoid_t
id|geoid
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|find_lboard_module
c_func
(paren
id|lboard_t
op_star
id|start
comma
id|geoid_t
id|geoid
)paren
suffix:semicolon
r_extern
r_int
id|config_find_nic_router
c_func
(paren
id|nasid_t
comma
id|nic_t
comma
id|lboard_t
op_star
op_star
comma
id|klrou_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|config_find_nic_hub
c_func
(paren
id|nasid_t
comma
id|nic_t
comma
id|lboard_t
op_star
op_star
comma
id|klhub_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|config_find_xbow
c_func
(paren
id|nasid_t
comma
id|lboard_t
op_star
op_star
comma
id|klxbow_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|update_klcfg_cpuinfo
c_func
(paren
id|nasid_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|board_to_path
c_func
(paren
id|lboard_t
op_star
id|brd
comma
r_char
op_star
id|path
)paren
suffix:semicolon
r_extern
r_void
id|nic_name_convert
c_func
(paren
r_char
op_star
id|old_name
comma
r_char
op_star
id|new_name
)paren
suffix:semicolon
r_extern
r_int
id|module_brds
c_func
(paren
id|nasid_t
id|nasid
comma
id|lboard_t
op_star
op_star
id|module_brds
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|brd_from_key
c_func
(paren
r_uint64
id|key
)paren
suffix:semicolon
r_extern
r_void
id|device_component_canonical_name_get
c_func
(paren
id|lboard_t
op_star
comma
id|klinfo_t
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|board_serial_number_get
c_func
(paren
id|lboard_t
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
id|nasid_t
id|get_actual_nasid
c_func
(paren
id|lboard_t
op_star
id|brd
)paren
suffix:semicolon
r_extern
id|net_vec_t
id|klcfg_discover_route
c_func
(paren
id|lboard_t
op_star
comma
id|lboard_t
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_KLCONFIG_H */
eof
