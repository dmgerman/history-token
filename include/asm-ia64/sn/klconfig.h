multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/klconfig.h&gt;.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef&t;_ASM_SN_KLCONFIG_H
DECL|macro|_ASM_SN_KLCONFIG_H
mdefine_line|#define&t;_ASM_SN_KLCONFIG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * klconfig.h&n; */
multiline_comment|/*&n; * The KLCONFIG structures store info about the various BOARDs found&n; * during Hardware Discovery. In addition, it stores info about the&n; * components found on the BOARDs.&n; */
multiline_comment|/*&n; * WARNING:&n; *&t;Certain assembly language routines (notably xxxxx.s) in the IP27PROM &n; *&t;will depend on the format of the data structures in this file.  In &n; *      most cases, rearranging the fields can seriously break things.   &n; *      Adding fields in the beginning or middle can also break things.&n; *      Add fields if necessary, to the end of a struct in such a way&n; *      that offsets of existing fields do not change.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/slotnum.h&gt;
macro_line|#include &lt;asm/sn/router.h&gt;
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn1/addrs.h&gt;
macro_line|#include &lt;asm/sn/vector.h&gt;
macro_line|#include &lt;asm/sn/agent.h&gt;
singleline_comment|// #include &lt;sys/graph.h&gt;
singleline_comment|// #include &lt;asm/sn/arc/types.h&gt;
macro_line|#include &lt;asm/sn/arc/hinv.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/kldir.h&gt;
macro_line|#include &lt;asm/sn/sn_fru.h&gt;
macro_line|#endif  /* CONFIG_SGI_IP35 ... */
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
macro_line|#if (defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)) &amp;&amp; defined(BRINGUP) /* MAX_SLOTS_PER_NODE??? */
multiline_comment|/* &n; * 1 NODE brick, 3 Router bricks (1 local, 1 meta, 1 repeater),&n; * 6 XIO Widgets, 1 Xbow, 1 gfx&n; */
DECL|macro|MAX_SLOTS_PER_NODE
mdefine_line|#define MAX_SLOTS_PER_NODE&t;(1 + 3 + 6 + 1 + 1) 
macro_line|#else
multiline_comment|/* &n; * 1 NODE brd, 2 Router brd (1 8p, 1 meta), 6 Widgets, &n; * 2 Midplanes assuming no pci card cages &n; */
DECL|macro|MAX_SLOTS_PER_NODE
mdefine_line|#define MAX_SLOTS_PER_NODE&t;(1 + 2 + 6 + 2) 
macro_line|#endif
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
mdefine_line|#define LOCAL_MASTER_IO6&t;0x10 &t;/* master io6 for that node */
DECL|macro|GLOBAL_MASTER_IO6
mdefine_line|#define GLOBAL_MASTER_IO6&t;0x20
DECL|macro|GLOBAL_MASTER_EXT
mdefine_line|#define GLOBAL_MASTER_EXT &t;0x40  &t;/* extend master io6 to other bus on ibrick */
DECL|macro|SECOND_NIC_PRESENT
mdefine_line|#define SECOND_NIC_PRESENT &t;0x80 &t;/* addons like MIO are present */
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
DECL|macro|IS_CONSOLE_IOC3
mdefine_line|#define IS_CONSOLE_IOC3(i)&t;((((klinfo_t *)i)-&gt;flags) &amp; KLINFO_INSTALL)
DECL|macro|GB2
mdefine_line|#define GB2&t;&t;0x80000000
DECL|macro|MAX_RSV_PTRS
mdefine_line|#define MAX_RSV_PTRS&t;32
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
DECL|macro|KL_CONFIG_INFO_OFFSET
mdefine_line|#define KL_CONFIG_INFO_OFFSET(_nasid)&t;&t;&t;&t;&t;&bslash;&n;        (KL_CONFIG_HDR(_nasid)-&gt;ch_board_info)
DECL|macro|KL_CONFIG_INFO_SET_OFFSET
mdefine_line|#define KL_CONFIG_INFO_SET_OFFSET(_nasid, _off)&t;&t;&t;&t;&bslash;&n;        (KL_CONFIG_HDR(_nasid)-&gt;ch_board_info = (_off))
macro_line|#ifndef __ia64
DECL|macro|KL_CONFIG_INFO
mdefine_line|#define KL_CONFIG_INFO(_nasid) &t;&t;&t;&t;&t;&t;&bslash;&n;        (lboard_t *)((KL_CONFIG_HDR(_nasid)-&gt;ch_board_info) ?&t;&t;&bslash;&n;&t; NODE_OFFSET_TO_K0((_nasid), KL_CONFIG_HDR(_nasid)-&gt;ch_board_info) : &bslash;&n;&t; 0)
macro_line|#else
DECL|macro|NODE_OFFSET_TO_LBOARD
mdefine_line|#define NODE_OFFSET_TO_LBOARD(nasid,off)        (lboard_t*)(NODE_CAC_BASE(nasid) + (off))
DECL|macro|KL_CONFIG_INFO
mdefine_line|#define KL_CONFIG_INFO(_nasid)                                          &bslash;&n;&t;(lboard_t *)((KL_CONFIG_HDR(_nasid)-&gt;ch_board_info) ?           &bslash;&n;&t; NODE_OFFSET_TO_LBOARD((_nasid), KL_CONFIG_HDR(_nasid)-&gt;ch_board_info) : &bslash;&n;&t; NULL)
macro_line|#endif&t;/* __ia64 */
DECL|macro|KL_CONFIG_MAGIC
mdefine_line|#define KL_CONFIG_MAGIC(_nasid)&t;&t;(KL_CONFIG_HDR(_nasid)-&gt;ch_magic)
DECL|macro|KL_CONFIG_CHECK_MAGIC
mdefine_line|#define KL_CONFIG_CHECK_MAGIC(_nasid)&t;&t;&t;&t;&t;&bslash;&n;        (KL_CONFIG_HDR(_nasid)-&gt;ch_magic == KLCFGINFO_MAGIC)
DECL|macro|KL_CONFIG_HDR_INIT_MAGIC
mdefine_line|#define KL_CONFIG_HDR_INIT_MAGIC(_nasid)&t;&bslash;&n;                  (KL_CONFIG_HDR(_nasid)-&gt;ch_magic = KLCFGINFO_MAGIC)
multiline_comment|/* --- New Macros for the changed kl_config_hdr_t structure --- */
DECL|macro|PTR_CH_MALLOC_HDR
mdefine_line|#define PTR_CH_MALLOC_HDR(_k)   ((klc_malloc_hdr_t *)&bslash;&n;&t;&t;&t;((__psunsigned_t)_k + (_k-&gt;ch_malloc_hdr_off)))
DECL|macro|KL_CONFIG_CH_MALLOC_HDR
mdefine_line|#define KL_CONFIG_CH_MALLOC_HDR(_n)   PTR_CH_MALLOC_HDR(KL_CONFIG_HDR(_n))
DECL|macro|PTR_CH_CONS_INFO
mdefine_line|#define PTR_CH_CONS_INFO(_k)&t;((console_t *)&bslash;&n;&t;&t;&t;((__psunsigned_t)_k + (_k-&gt;ch_cons_off)))
DECL|macro|KL_CONFIG_CH_CONS_INFO
mdefine_line|#define KL_CONFIG_CH_CONS_INFO(_n)   PTR_CH_CONS_INFO(KL_CONFIG_HDR(_n))
multiline_comment|/* ------------------------------------------------------------- */
DECL|macro|KL_CONFIG_INFO_START
mdefine_line|#define KL_CONFIG_INFO_START(_nasid)&t;&bslash;&n;        (klconf_off_t)(KLCONFIG_OFFSET(_nasid) + sizeof(kl_config_hdr_t))
DECL|macro|KL_CONFIG_BOARD_NASID
mdefine_line|#define KL_CONFIG_BOARD_NASID(_brd)&t;((_brd)-&gt;brd_nasid)
DECL|macro|KL_CONFIG_BOARD_SET_NEXT
mdefine_line|#define KL_CONFIG_BOARD_SET_NEXT(_brd, _off)&t;((_brd)-&gt;brd_next = (_off))
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
DECL|macro|SN0_PORT_FENCE_SHFT
mdefine_line|#define&t;SN0_PORT_FENCE_SHFT&t;0
DECL|macro|SN0_PORT_FENCE_MASK
mdefine_line|#define&t;SN0_PORT_FENCE_MASK&t;(1 &lt;&lt; SN0_PORT_FENCE_SHFT)
multiline_comment|/*&n; * The KLCONFIG area is organized as a LINKED LIST of BOARDs. A BOARD&n; * can be either &squot;LOCAL&squot; or &squot;REMOTE&squot;. LOCAL means it is attached to &n; * the LOCAL/current NODE. REMOTE means it is attached to a different&n; * node.(TBD - Need a way to treat ROUTER boards.)&n; *&n; * There are 2 different structures to represent these boards -&n; * lboard - Local board, rboard - remote board. These 2 structures&n; * can be arbitrarily mixed in the LINKED LIST of BOARDs. (Refer&n; * Figure below). The first byte of the rboard or lboard structure&n; * is used to find out its type - no unions are used.&n; * If it is a lboard, then the config info of this board will be found&n; * on the local node. (LOCAL NODE BASE + offset value gives pointer to &n; * the structure.&n; * If it is a rboard, the local structure contains the node number&n; * and the offset of the beginning of the LINKED LIST on the remote node.&n; * The details of the hardware on a remote node can be built locally,&n; * if required, by reading the LINKED LIST on the remote node and &n; * ignoring all the rboards on that node.&n; *&n; * The local node uses the REMOTE NODE NUMBER + OFFSET to point to the &n; * First board info on the remote node. The remote node list is &n; * traversed as the local list, using the REMOTE BASE ADDRESS and not&n; * the local base address and ignoring all rboard values.&n; *&n; * &n; KLCONFIG&n;&n; +------------+      +------------+      +------------+      +------------+&n; |  lboard    |  +--&gt;|   lboard   |  +--&gt;|   rboard   |  +--&gt;|   lboard   |&n; +------------+  |   +------------+  |   +------------+  |   +------------+&n; | board info |  |   | board info |  |   |errinfo,bptr|  |   | board info |&n; +------------+  |   +------------+  |   +------------+  |   +------------+&n; | offset     |--+   |  offset    |--+   |  offset    |--+   |offset=NULL |&n; +------------+      +------------+      +------------+      +------------+&n;&n;&n; +------------+&n; | board info |&n; +------------+       +--------------------------------+&n; | compt 1    |------&gt;| type, rev, diaginfo, size ...  |  (CPU)&n; +------------+       +--------------------------------+&n; | compt 2    |--+&n; +------------+  |    +--------------------------------+&n; |  ...       |  +---&gt;| type, rev, diaginfo, size ...  |  (MEM_BANK)&n; +------------+       +--------------------------------+&n; | errinfo    |--+&n; +------------+  |    +--------------------------------+&n;                 +---&gt;|r/l brd errinfo,compt err flags |&n;                      +--------------------------------+&n;&n; *&n; * Each BOARD consists of COMPONENTs and the BOARD structure has &n; * pointers (offsets) to its COMPONENT structure.&n; * The COMPONENT structure has version info, size and speed info, revision,&n; * error info and the NIC info. This structure can accomodate any&n; * BOARD with arbitrary COMPONENT composition.&n; *&n; * The ERRORINFO part of each BOARD has error information&n; * that describes errors about the BOARD itself. It also has flags to&n; * indicate the COMPONENT(s) on the board that have errors. The error &n; * information specific to the COMPONENT is present in the respective &n; * COMPONENT structure.&n; *&n; * The ERRORINFO structure is also treated like a COMPONENT, ie. the &n; * BOARD has pointers(offset) to the ERRORINFO structure. The rboard&n; * structure also has a pointer to the ERRORINFO structure. This is &n; * the place to store ERRORINFO about a REMOTE NODE, if the HUB on&n; * that NODE is not working or if the REMOTE MEMORY is BAD. In cases where &n; * only the CPU of the REMOTE NODE is disabled, the ERRORINFO pointer can&n; * be a NODE NUMBER, REMOTE OFFSET combination, pointing to error info &n; * which is present on the REMOTE NODE.(TBD)&n; * REMOTE ERRINFO can be stored on any of the nearest nodes &n; * or on all the nearest nodes.(TBD)&n; * Like BOARD structures, REMOTE ERRINFO structures can be built locally&n; * using the rboard errinfo pointer.&n; *&n; * In order to get useful information from this Data organization, a set of&n; * interface routines are provided (TBD). The important thing to remember while&n; * manipulating the structures, is that, the NODE number information should&n; * be used. If the NODE is non-zero (remote) then each offset should&n; * be added to the REMOTE BASE ADDR else it should be added to the LOCAL BASE ADDR. &n; * This includes offsets for BOARDS, COMPONENTS and ERRORINFO.&n; * &n; * Note that these structures do not provide much info about connectivity.&n; * That info will be part of HWGRAPH, which is an extension of the cfg_t&n; * data structure. (ref IP27prom/cfg.h) It has to be extended to include&n; * the IO part of the Network(TBD).&n; *&n; * The data structures below define the above concepts.&n; */
multiline_comment|/*&n; * Values for CPU types&n; */
DECL|macro|KL_CPU_R4000
mdefine_line|#define KL_CPU_R4000&t;&t;0x1&t;/* Standard R4000 */
DECL|macro|KL_CPU_TFP
mdefine_line|#define KL_CPU_TFP&t;&t;0x2&t;/* TFP processor */
DECL|macro|KL_CPU_R10000
mdefine_line|#define&t;KL_CPU_R10000&t;&t;0x3&t;/* R10000 (T5) */
DECL|macro|KL_CPU_NONE
mdefine_line|#define KL_CPU_NONE&t;&t;(-1)&t;/* no cpu present in slot */
multiline_comment|/*&n; * IP27 BOARD classes&n; */
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
mdefine_line|#define KLCLASS_MAX&t;7&t;&t;/* Bump this if a new CLASS is added */
DECL|macro|KLTYPE_MAX
mdefine_line|#define KLTYPE_MAX&t;10&t;&t;/* Bump this if a new CLASS is added */
DECL|macro|KLCLASS_UNKNOWN
mdefine_line|#define KLCLASS_UNKNOWN&t;0xf0
DECL|macro|KLCLASS
mdefine_line|#define KLCLASS(_x) ((_x) &amp; KLCLASS_MASK)
multiline_comment|/*&n; * IP27 board types&n; */
DECL|macro|KLTYPE_MASK
mdefine_line|#define KLTYPE_MASK&t;0x0f
DECL|macro|KLTYPE_NONE
mdefine_line|#define KLTYPE_NONE&t;0x00
DECL|macro|KLTYPE_EMPTY
mdefine_line|#define KLTYPE_EMPTY&t;0x00
DECL|macro|KLTYPE_WEIRDCPU
mdefine_line|#define KLTYPE_WEIRDCPU (KLCLASS_CPU | 0x0)
DECL|macro|KLTYPE_IP27
mdefine_line|#define KLTYPE_IP27&t;(KLCLASS_CPU | 0x1) /* 2 CPUs(R10K) per board */
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
DECL|macro|KLTYPE_IP35
mdefine_line|#define KLTYPE_IP35&t;KLTYPE_IP27
DECL|macro|KLTYPE_IP37
mdefine_line|#define KLTYPE_IP37&t;KLTYPE_IP35
macro_line|#endif
DECL|macro|KLTYPE_WEIRDIO
mdefine_line|#define KLTYPE_WEIRDIO&t;(KLCLASS_IO  | 0x0)
DECL|macro|KLTYPE_BASEIO
mdefine_line|#define KLTYPE_BASEIO&t;(KLCLASS_IO  | 0x1) /* IOC3, SuperIO, Bridge, SCSI */
DECL|macro|KLTYPE_IO6
mdefine_line|#define KLTYPE_IO6&t;KLTYPE_BASEIO       /* Additional name */
DECL|macro|KLTYPE_4CHSCSI
mdefine_line|#define KLTYPE_4CHSCSI&t;(KLCLASS_IO  | 0x2)
DECL|macro|KLTYPE_MSCSI
mdefine_line|#define KLTYPE_MSCSI&t;KLTYPE_4CHSCSI      /* Additional name */
DECL|macro|KLTYPE_ETHERNET
mdefine_line|#define KLTYPE_ETHERNET&t;(KLCLASS_IO  | 0x3)
DECL|macro|KLTYPE_MENET
mdefine_line|#define KLTYPE_MENET&t;KLTYPE_ETHERNET     /* Additional name */
DECL|macro|KLTYPE_FDDI
mdefine_line|#define KLTYPE_FDDI  &t;(KLCLASS_IO  | 0x4)
DECL|macro|KLTYPE_UNUSED
mdefine_line|#define KLTYPE_UNUSED&t;(KLCLASS_IO  | 0x5) /* XXX UNUSED */
DECL|macro|KLTYPE_HAROLD
mdefine_line|#define KLTYPE_HAROLD   (KLCLASS_IO  | 0x6) /* PCI SHOE BOX */
DECL|macro|KLTYPE_PCI
mdefine_line|#define KLTYPE_PCI&t;KLTYPE_HAROLD
DECL|macro|KLTYPE_VME
mdefine_line|#define KLTYPE_VME      (KLCLASS_IO  | 0x7) /* Any 3rd party VME card */
DECL|macro|KLTYPE_MIO
mdefine_line|#define KLTYPE_MIO   &t;(KLCLASS_IO  | 0x8)
DECL|macro|KLTYPE_FC
mdefine_line|#define KLTYPE_FC    &t;(KLCLASS_IO  | 0x9)
DECL|macro|KLTYPE_LINC
mdefine_line|#define KLTYPE_LINC    &t;(KLCLASS_IO  | 0xA)
DECL|macro|KLTYPE_TPU
mdefine_line|#define KLTYPE_TPU    &t;(KLCLASS_IO  | 0xB) /* Tensor Processing Unit */
DECL|macro|KLTYPE_GSN_A
mdefine_line|#define KLTYPE_GSN_A   &t;(KLCLASS_IO  | 0xC) /* Main GSN board */
DECL|macro|KLTYPE_GSN_B
mdefine_line|#define KLTYPE_GSN_B   &t;(KLCLASS_IO  | 0xD) /* Auxiliary GSN board */
DECL|macro|KLTYPE_SHOEHORN
mdefine_line|#define KLTYPE_SHOEHORN (KLCLASS_IO  | 0xE)
DECL|macro|KLTYPE_SERIAL_HIPPI
mdefine_line|#define KLTYPE_SERIAL_HIPPI (KLCLASS_IO  | 0xF)
DECL|macro|KLTYPE_GFX
mdefine_line|#define KLTYPE_GFX&t;(KLCLASS_GFX | 0x0) /* unknown graphics type */
DECL|macro|KLTYPE_GFX_KONA
mdefine_line|#define KLTYPE_GFX_KONA (KLCLASS_GFX | 0x1) /* KONA graphics on IP27 */
DECL|macro|KLTYPE_GFX_MGRA
mdefine_line|#define KLTYPE_GFX_MGRA (KLCLASS_GFX | 0x3) /* MGRAS graphics on IP27 */
DECL|macro|KLTYPE_WEIRDROUTER
mdefine_line|#define KLTYPE_WEIRDROUTER (KLCLASS_ROUTER | 0x0)
DECL|macro|KLTYPE_ROUTER
mdefine_line|#define KLTYPE_ROUTER     (KLCLASS_ROUTER | 0x1)
DECL|macro|KLTYPE_ROUTER2
mdefine_line|#define KLTYPE_ROUTER2    KLTYPE_ROUTER&t;&t;/* Obsolete! */
DECL|macro|KLTYPE_NULL_ROUTER
mdefine_line|#define KLTYPE_NULL_ROUTER (KLCLASS_ROUTER | 0x2)
DECL|macro|KLTYPE_META_ROUTER
mdefine_line|#define KLTYPE_META_ROUTER (KLCLASS_ROUTER | 0x3)
DECL|macro|KLTYPE_REPEATER_ROUTER
mdefine_line|#define KLTYPE_REPEATER_ROUTER (KLCLASS_ROUTER | 0x4)
DECL|macro|KLTYPE_WEIRDMIDPLANE
mdefine_line|#define KLTYPE_WEIRDMIDPLANE (KLCLASS_MIDPLANE | 0x0)
DECL|macro|KLTYPE_MIDPLANE8
mdefine_line|#define KLTYPE_MIDPLANE8  (KLCLASS_MIDPLANE | 0x1) /* 8 slot backplane */
DECL|macro|KLTYPE_MIDPLANE
mdefine_line|#define KLTYPE_MIDPLANE    KLTYPE_MIDPLANE8
DECL|macro|KLTYPE_IOBRICK_XBOW
mdefine_line|#define KLTYPE_IOBRICK_XBOW&t;(KLCLASS_MIDPLANE | 0x2)
DECL|macro|KLTYPE_IOBRICK
mdefine_line|#define KLTYPE_IOBRICK&t;&t;(KLCLASS_IOBRICK | 0x0)
DECL|macro|KLTYPE_IBRICK
mdefine_line|#define KLTYPE_IBRICK&t;&t;(KLCLASS_IOBRICK | 0x1)
DECL|macro|KLTYPE_PBRICK
mdefine_line|#define KLTYPE_PBRICK&t;&t;(KLCLASS_IOBRICK | 0x2)
DECL|macro|KLTYPE_XBRICK
mdefine_line|#define KLTYPE_XBRICK&t;&t;(KLCLASS_IOBRICK | 0x3)
DECL|macro|KLTYPE_PBRICK_BRIDGE
mdefine_line|#define KLTYPE_PBRICK_BRIDGE&t;KLTYPE_PBRICK
multiline_comment|/* The value of type should be more than 8 so that hinv prints&n; * out the board name from the NIC string. For values less than&n; * 8 the name of the board needs to be hard coded in a few places.&n; * When bringup started nic names had not standardized and so we&n; * had to hard code. (For people interested in history.) &n; */
DECL|macro|KLTYPE_XTHD
mdefine_line|#define KLTYPE_XTHD   &t;(KLCLASS_PSEUDO_GFX | 0x9)
DECL|macro|KLTYPE_UNKNOWN
mdefine_line|#define KLTYPE_UNKNOWN&t;(KLCLASS_UNKNOWN | 0xf)
DECL|macro|KLTYPE
mdefine_line|#define KLTYPE(_x) &t;((_x) &amp; KLTYPE_MASK)
DECL|macro|IS_MIO_PRESENT
mdefine_line|#define IS_MIO_PRESENT(l)&t;((l-&gt;brd_type == KLTYPE_BASEIO) &amp;&amp; &bslash;&n;&t;&t;&t;&t; (l-&gt;brd_flags &amp; SECOND_NIC_PRESENT))
DECL|macro|IS_MIO_IOC3
mdefine_line|#define IS_MIO_IOC3(l,n)&t;(IS_MIO_PRESENT(l) &amp;&amp; (n &gt; 2))
multiline_comment|/* &n; * board structures&n; */
DECL|macro|MAX_COMPTS_PER_BRD
mdefine_line|#define MAX_COMPTS_PER_BRD 24
DECL|macro|LOCAL_BOARD
mdefine_line|#define LOCAL_BOARD 1
DECL|macro|REMOTE_BOARD
mdefine_line|#define REMOTE_BOARD 2
DECL|macro|LBOARD_STRUCT_VERSION
mdefine_line|#define LBOARD_STRUCT_VERSION &t;2
DECL|struct|lboard_s
r_typedef
r_struct
id|lboard_s
(brace
DECL|member|brd_next
id|klconf_off_t
id|brd_next
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
DECL|member|brd_module
id|moduleid_t
id|brd_module
suffix:semicolon
multiline_comment|/* module to which it belongs */
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
DECL|member|brd_graph_link
id|devfs_handle_t
id|brd_graph_link
suffix:semicolon
multiline_comment|/* vertex hdl to connect extern compts */
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
DECL|member|brd_name
r_char
id|brd_name
(braket
l_int|32
)braket
suffix:semicolon
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
DECL|macro|KLCF_REMOTE
mdefine_line|#define KLCF_REMOTE(_brd)  &t;(((_brd)-&gt;struct_type &amp; LOCAL_BOARD) ? 0 : 1)
DECL|macro|KLCF_NUM_COMPS
mdefine_line|#define KLCF_NUM_COMPS(_brd)&t;((_brd)-&gt;brd_numcompts)
DECL|macro|KLCF_MODULE_ID
mdefine_line|#define KLCF_MODULE_ID(_brd)&t;((_brd)-&gt;brd_module)
macro_line|#ifndef __ia64
DECL|macro|KLCF_NEXT
mdefine_line|#define KLCF_NEXT(_brd) &t;&t;((_brd)-&gt;brd_next ? (lboard_t *)((_brd)-&gt;brd_next):  NULL)
DECL|macro|KLCF_COMP
mdefine_line|#define KLCF_COMP(_brd, _ndx)   &bslash;&n;&t;&t;(klinfo_t *)(NODE_OFFSET_TO_K0(NASID_GET(_brd), &bslash;&n;&t;&t;&t;&t;&t;&t;(_brd)-&gt;brd_compts[(_ndx)]))
DECL|macro|KLCF_COMP_ERROR
mdefine_line|#define KLCF_COMP_ERROR(_brd, _comp)    &bslash;&n;&t;&t;(NODE_OFFSET_TO_K0(NASID_GET(_brd), (_comp)-&gt;errinfo))
macro_line|#else
DECL|macro|NODE_OFFSET_TO_KLINFO
mdefine_line|#define NODE_OFFSET_TO_KLINFO(n,off)    ((klinfo_t*) TO_NODE_CAC(n,off))
DECL|macro|KLCF_NEXT
mdefine_line|#define KLCF_NEXT(_brd)         &bslash;&n;        ((_brd)-&gt;brd_next ?     &bslash;&n;         (NODE_OFFSET_TO_LBOARD(NASID_GET(_brd), (_brd)-&gt;brd_next)): NULL)
DECL|macro|KLCF_COMP
mdefine_line|#define KLCF_COMP(_brd, _ndx)   &bslash;&n;                (NODE_OFFSET_TO_KLINFO(NASID_GET(_brd), (_brd)-&gt;brd_compts[(_ndx)]))
DECL|macro|KLCF_COMP_ERROR
mdefine_line|#define KLCF_COMP_ERROR(_brd, _comp)    &bslash;&n;                (NODE_OFFSET_TO_K0(NASID_GET(_brd), (_comp)-&gt;errinfo))
macro_line|#endif /* __ia64 */
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
DECL|member|arcs_compt
id|COMPONENT
op_star
id|arcs_compt
suffix:semicolon
multiline_comment|/* ptr to the arcs struct for ease*/
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
DECL|macro|KLSTRUCT_IOC3
mdefine_line|#define KLSTRUCT_IOC3 &t;&t;6
DECL|macro|KLSTRUCT_PCI
mdefine_line|#define KLSTRUCT_PCI &t;&t;7
DECL|macro|KLSTRUCT_VME
mdefine_line|#define KLSTRUCT_VME &t;&t;8
DECL|macro|KLSTRUCT_ROU
mdefine_line|#define KLSTRUCT_ROU&t;&t;9
DECL|macro|KLSTRUCT_GFX
mdefine_line|#define KLSTRUCT_GFX &t;&t;10
DECL|macro|KLSTRUCT_SCSI
mdefine_line|#define KLSTRUCT_SCSI &t;&t;11
DECL|macro|KLSTRUCT_FDDI
mdefine_line|#define KLSTRUCT_FDDI &t;&t;12
DECL|macro|KLSTRUCT_MIO
mdefine_line|#define KLSTRUCT_MIO &t;&t;13
DECL|macro|KLSTRUCT_DISK
mdefine_line|#define KLSTRUCT_DISK &t;&t;14
DECL|macro|KLSTRUCT_TAPE
mdefine_line|#define KLSTRUCT_TAPE &t;&t;15
DECL|macro|KLSTRUCT_CDROM
mdefine_line|#define KLSTRUCT_CDROM &t;&t;16
DECL|macro|KLSTRUCT_HUB_UART
mdefine_line|#define KLSTRUCT_HUB_UART &t;17
DECL|macro|KLSTRUCT_IOC3ENET
mdefine_line|#define KLSTRUCT_IOC3ENET &t;18
DECL|macro|KLSTRUCT_IOC3UART
mdefine_line|#define KLSTRUCT_IOC3UART &t;19
DECL|macro|KLSTRUCT_UNUSED
mdefine_line|#define KLSTRUCT_UNUSED&t;&t;20 /* XXX UNUSED */
DECL|macro|KLSTRUCT_IOC3PCKM
mdefine_line|#define KLSTRUCT_IOC3PCKM       21
DECL|macro|KLSTRUCT_RAD
mdefine_line|#define KLSTRUCT_RAD        &t;22
DECL|macro|KLSTRUCT_HUB_TTY
mdefine_line|#define KLSTRUCT_HUB_TTY        23
DECL|macro|KLSTRUCT_IOC3_TTY
mdefine_line|#define KLSTRUCT_IOC3_TTY &t;24
multiline_comment|/* Early Access IO proms are compatible&n;   only with KLSTRUCT values upto 24. */
DECL|macro|KLSTRUCT_FIBERCHANNEL
mdefine_line|#define KLSTRUCT_FIBERCHANNEL &t;25
DECL|macro|KLSTRUCT_MOD_SERIAL_NUM
mdefine_line|#define KLSTRUCT_MOD_SERIAL_NUM 26
DECL|macro|KLSTRUCT_IOC3MS
mdefine_line|#define KLSTRUCT_IOC3MS         27
DECL|macro|KLSTRUCT_TPU
mdefine_line|#define KLSTRUCT_TPU            28
DECL|macro|KLSTRUCT_GSN_A
mdefine_line|#define KLSTRUCT_GSN_A          29
DECL|macro|KLSTRUCT_GSN_B
mdefine_line|#define KLSTRUCT_GSN_B          30
DECL|macro|KLSTRUCT_XTHD
mdefine_line|#define KLSTRUCT_XTHD           31
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
multiline_comment|/*&n; * These are the indices of various components within a lboard structure.&n; */
DECL|macro|IP27_CPU0_INDEX
mdefine_line|#define IP27_CPU0_INDEX 0
DECL|macro|IP27_CPU1_INDEX
mdefine_line|#define IP27_CPU1_INDEX 1
DECL|macro|IP27_HUB_INDEX
mdefine_line|#define IP27_HUB_INDEX 2
DECL|macro|IP27_MEM_INDEX
mdefine_line|#define IP27_MEM_INDEX 3
DECL|macro|BASEIO_BRIDGE_INDEX
mdefine_line|#define BASEIO_BRIDGE_INDEX 0
DECL|macro|BASEIO_IOC3_INDEX
mdefine_line|#define BASEIO_IOC3_INDEX 1
DECL|macro|BASEIO_SCSI1_INDEX
mdefine_line|#define BASEIO_SCSI1_INDEX 2
DECL|macro|BASEIO_SCSI2_INDEX
mdefine_line|#define BASEIO_SCSI2_INDEX 3
DECL|macro|MIDPLANE_XBOW_INDEX
mdefine_line|#define MIDPLANE_XBOW_INDEX 0
DECL|macro|ROUTER_COMPONENT_INDEX
mdefine_line|#define ROUTER_COMPONENT_INDEX 0
DECL|macro|CH4SCSI_BRIDGE_INDEX
mdefine_line|#define CH4SCSI_BRIDGE_INDEX 0
multiline_comment|/* Info holders for various hardware components */
DECL|typedef|pci_t
r_typedef
id|u64
op_star
id|pci_t
suffix:semicolon
DECL|typedef|vmeb_t
r_typedef
id|u64
op_star
id|vmeb_t
suffix:semicolon
DECL|typedef|vmed_t
r_typedef
id|u64
op_star
id|vmed_t
suffix:semicolon
DECL|typedef|fddi_t
r_typedef
id|u64
op_star
id|fddi_t
suffix:semicolon
DECL|typedef|scsi_t
r_typedef
id|u64
op_star
id|scsi_t
suffix:semicolon
DECL|typedef|mio_t
r_typedef
id|u64
op_star
id|mio_t
suffix:semicolon
DECL|typedef|graphics_t
r_typedef
id|u64
op_star
id|graphics_t
suffix:semicolon
DECL|typedef|router_t
r_typedef
id|u64
op_star
id|router_t
suffix:semicolon
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
id|uint
id|hub_flags
suffix:semicolon
multiline_comment|/* PCFG_HUB_xxx flags */
DECL|member|hub_port
id|klport_t
id|hub_port
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
id|uint
id|hubuart_flags
suffix:semicolon
multiline_comment|/* PCFG_HUB_xxx flags */
DECL|member|hubuart_box_nic
id|nic_t
id|hubuart_box_nic
suffix:semicolon
multiline_comment|/* nic of containing box */
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
DECL|typedef|klmembnk_t
)brace
id|klmembnk_t
suffix:semicolon
DECL|macro|KLCONFIG_MEMBNK_SIZE
mdefine_line|#define KLCONFIG_MEMBNK_SIZE(_info, _bank)&t;&bslash;&n;                            ((_info)-&gt;membnk_bnksz[(_bank)])
DECL|macro|MEMBNK_PREMIUM
mdefine_line|#define MEMBNK_PREMIUM 1
DECL|macro|KLCONFIG_MEMBNK_PREMIUM
mdefine_line|#define KLCONFIG_MEMBNK_PREMIUM(_info, _bank)&t;&bslash;&n;                            ((_info)-&gt;membnk_attr &amp; (MEMBNK_PREMIUM &lt;&lt; (_bank)))
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
id|pci_t
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
DECL|typedef|klbri_t
)brace
id|klbri_t
suffix:semicolon
DECL|macro|MAX_IOC3_TTY
mdefine_line|#define MAX_IOC3_TTY&t;2
DECL|struct|klioc3_s
r_typedef
r_struct
id|klioc3_s
(brace
multiline_comment|/* IOC3 */
DECL|member|ioc3_info
id|klinfo_t
id|ioc3_info
suffix:semicolon
DECL|member|ioc3_ssram
r_int
r_char
id|ioc3_ssram
suffix:semicolon
multiline_comment|/* Info about ssram */
DECL|member|ioc3_nvram
r_int
r_char
id|ioc3_nvram
suffix:semicolon
multiline_comment|/* Info about nvram */
DECL|member|ioc3_superio
id|klinfo_t
id|ioc3_superio
suffix:semicolon
multiline_comment|/* Info about superio */
DECL|member|ioc3_tty_off
id|klconf_off_t
id|ioc3_tty_off
suffix:semicolon
DECL|member|ioc3_enet
id|klinfo_t
id|ioc3_enet
suffix:semicolon
DECL|member|ioc3_enet_off
id|klconf_off_t
id|ioc3_enet_off
suffix:semicolon
DECL|member|ioc3_kbd_off
id|klconf_off_t
id|ioc3_kbd_off
suffix:semicolon
DECL|typedef|klioc3_t
)brace
id|klioc3_t
suffix:semicolon
DECL|macro|MAX_VME_SLOTS
mdefine_line|#define MAX_VME_SLOTS 8
DECL|struct|klvmeb_s
r_typedef
r_struct
id|klvmeb_s
(brace
multiline_comment|/* VME BRIDGE - PCI CTLR */
DECL|member|vmeb_info
id|klinfo_t
id|vmeb_info
suffix:semicolon
DECL|member|vmeb_specific
id|vmeb_t
id|vmeb_specific
suffix:semicolon
DECL|member|vmeb_brdinfo
id|klconf_off_t
id|vmeb_brdinfo
(braket
id|MAX_VME_SLOTS
)braket
suffix:semicolon
multiline_comment|/* VME Board config info */
DECL|typedef|klvmeb_t
)brace
id|klvmeb_t
suffix:semicolon
DECL|struct|klvmed_s
r_typedef
r_struct
id|klvmed_s
(brace
multiline_comment|/* VME DEVICE - VME BOARD */
DECL|member|vmed_info
id|klinfo_t
id|vmed_info
suffix:semicolon
DECL|member|vmed_specific
id|vmed_t
id|vmed_specific
suffix:semicolon
DECL|member|vmed_brdinfo
id|klconf_off_t
id|vmed_brdinfo
(braket
id|MAX_VME_SLOTS
)braket
suffix:semicolon
multiline_comment|/* VME Board config info */
DECL|typedef|klvmed_t
)brace
id|klvmed_t
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
id|uint
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
id|uint
id|cookie
suffix:semicolon
multiline_comment|/* for compatibility with older proms */
DECL|member|moduleslot
id|uint
id|moduleslot
suffix:semicolon
DECL|member|gfx_next_pipe
r_struct
id|klgfx_s
op_star
id|gfx_next_pipe
suffix:semicolon
DECL|member|gfx_specific
id|graphics_t
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
DECL|typedef|klgfx_t
)brace
id|klgfx_t
suffix:semicolon
DECL|struct|klxthd_s
r_typedef
r_struct
id|klxthd_s
(brace
DECL|member|xthd_info
id|klinfo_t
id|xthd_info
suffix:semicolon
DECL|member|xthd_mfg_nic
id|klconf_off_t
id|xthd_mfg_nic
suffix:semicolon
multiline_comment|/* MFG NIC string */
DECL|typedef|klxthd_t
)brace
id|klxthd_t
suffix:semicolon
DECL|struct|kltpu_s
r_typedef
r_struct
id|kltpu_s
(brace
multiline_comment|/* TPU board */
DECL|member|tpu_info
id|klinfo_t
id|tpu_info
suffix:semicolon
DECL|member|tpu_mfg_nic
id|klconf_off_t
id|tpu_mfg_nic
suffix:semicolon
multiline_comment|/* MFG NIC string */
DECL|typedef|kltpu_t
)brace
id|kltpu_t
suffix:semicolon
DECL|struct|klgsn_s
r_typedef
r_struct
id|klgsn_s
(brace
multiline_comment|/* GSN board */
DECL|member|gsn_info
id|klinfo_t
id|gsn_info
suffix:semicolon
DECL|member|gsn_mfg_nic
id|klconf_off_t
id|gsn_mfg_nic
suffix:semicolon
multiline_comment|/* MFG NIC string */
DECL|typedef|klgsn_t
)brace
id|klgsn_t
suffix:semicolon
DECL|macro|MAX_SCSI_DEVS
mdefine_line|#define MAX_SCSI_DEVS 16
multiline_comment|/*&n; * NOTE: THis is the max sized kl* structure and is used in klmalloc.c&n; * to allocate space of type COMPONENT. Make sure that if the size of&n; * any other component struct becomes more than this, then redefine&n; * that as the size to be klmalloced.&n; */
DECL|struct|klscsi_s
r_typedef
r_struct
id|klscsi_s
(brace
multiline_comment|/* SCSI Controller */
DECL|member|scsi_info
id|klinfo_t
id|scsi_info
suffix:semicolon
DECL|member|scsi_specific
id|scsi_t
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
DECL|typedef|klscsi_t
)brace
id|klscsi_t
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
DECL|typedef|klttydev_t
)brace
id|klttydev_t
suffix:semicolon
DECL|struct|klenetdev_s
r_typedef
r_struct
id|klenetdev_s
(brace
multiline_comment|/* ENET device */
DECL|member|enetdev_info
id|klinfo_t
id|enetdev_info
suffix:semicolon
DECL|member|enetdev_cfg
r_struct
id|net_data
op_star
id|enetdev_cfg
suffix:semicolon
multiline_comment|/* driver fills up this */
DECL|typedef|klenetdev_t
)brace
id|klenetdev_t
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
DECL|typedef|klmsdev_t
)brace
id|klmsdev_t
suffix:semicolon
DECL|macro|MAX_FDDI_DEVS
mdefine_line|#define MAX_FDDI_DEVS 10 /* XXX Is this true */
DECL|struct|klfddi_s
r_typedef
r_struct
id|klfddi_s
(brace
multiline_comment|/* FDDI */
DECL|member|fddi_info
id|klinfo_t
id|fddi_info
suffix:semicolon
DECL|member|fddi_specific
id|fddi_t
id|fddi_specific
suffix:semicolon
DECL|member|fddi_devinfo
id|klconf_off_t
id|fddi_devinfo
(braket
id|MAX_FDDI_DEVS
)braket
suffix:semicolon
DECL|typedef|klfddi_t
)brace
id|klfddi_t
suffix:semicolon
DECL|struct|klmio_s
r_typedef
r_struct
id|klmio_s
(brace
multiline_comment|/* MIO */
DECL|member|mio_info
id|klinfo_t
id|mio_info
suffix:semicolon
DECL|member|mio_specific
id|mio_t
id|mio_specific
suffix:semicolon
DECL|typedef|klmio_t
)brace
id|klmio_t
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
DECL|member|kc_ioc3
id|klioc3_t
id|kc_ioc3
suffix:semicolon
DECL|member|kc_vmeb
id|klvmeb_t
id|kc_vmeb
suffix:semicolon
DECL|member|kc_vmed
id|klvmed_t
id|kc_vmed
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
DECL|member|kc_scsi_dev
id|klscdev_t
id|kc_scsi_dev
suffix:semicolon
DECL|member|kc_fddi
id|klfddi_t
id|kc_fddi
suffix:semicolon
DECL|member|kc_mio
id|klmio_t
id|kc_mio
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
DECL|member|kc_enet_dev
id|klenetdev_t
id|kc_enet_dev
suffix:semicolon
DECL|member|kc_kbd_dev
id|klkbddev_t
id|kc_kbd_dev
suffix:semicolon
DECL|typedef|kldev_t
)brace
id|kldev_t
suffix:semicolon
multiline_comment|/* Data structure interface routines. TBD */
multiline_comment|/* Include launch info in this file itself? TBD */
multiline_comment|/*&n; * TBD - Can the ARCS and device driver related info also be included in the&n; * KLCONFIG area. On the IO4PROM, prom device driver info is part of cfgnode_t &n; * structure, viz private to the IO4prom.&n; */
multiline_comment|/* &n; * TBD - Allocation issues. &n; *&n; * Do we need to Mark off sepatate heaps for lboard_t, rboard_t, component, &n; * errinfo and allocate from them, or have a single heap and allocate all &n; * structures from it. Debug is easier in the former method since we can&n; * dump all similar structs in one command, but there will be lots of holes, &n; * in memory and max limits are needed for number of structures.&n; * Another way to make it organized, is to have a union of all components&n; * and allocate a aligned chunk of memory greater than the biggest&n; * component.&n; */
r_typedef
r_union
(brace
DECL|member|lbinfo
id|lboard_t
op_star
id|lbinfo
suffix:semicolon
DECL|typedef|biptr_t
)brace
id|biptr_t
suffix:semicolon
DECL|macro|BRI_PER_XBOW
mdefine_line|#define BRI_PER_XBOW 6
DECL|macro|PCI_PER_BRI
mdefine_line|#define PCI_PER_BRI  8
DECL|macro|DEV_PER_PCI
mdefine_line|#define DEV_PER_PCI  16
multiline_comment|/* Virtual dipswitch values (starting from switch &quot;7&quot;): */
DECL|macro|VDS_NOGFX
mdefine_line|#define VDS_NOGFX&t;&t;0x8000&t;/* Don&squot;t enable gfx and autoboot */
DECL|macro|VDS_NOMP
mdefine_line|#define VDS_NOMP&t;&t;0x100&t;/* Don&squot;t start slave processors */
DECL|macro|VDS_MANUMODE
mdefine_line|#define VDS_MANUMODE&t;&t;0x80&t;/* Manufacturing mode */
DECL|macro|VDS_NOARB
mdefine_line|#define VDS_NOARB&t;&t;0x40&t;/* No bootmaster arbitration */
DECL|macro|VDS_PODMODE
mdefine_line|#define VDS_PODMODE&t;&t;0x20&t;/* Go straight to POD mode */
DECL|macro|VDS_NO_DIAGS
mdefine_line|#define VDS_NO_DIAGS&t;&t;0x10&t;/* Don&squot;t run any diags after BM arb */
DECL|macro|VDS_DEFAULTS
mdefine_line|#define VDS_DEFAULTS&t;&t;0x08&t;/* Use default environment values */
DECL|macro|VDS_NOMEMCLEAR
mdefine_line|#define VDS_NOMEMCLEAR&t;&t;0x04&t;/* Don&squot;t run mem cfg code */
DECL|macro|VDS_2ND_IO4
mdefine_line|#define VDS_2ND_IO4&t;&t;0x02&t;/* Boot from the second IO4 */
DECL|macro|VDS_DEBUG_PROM
mdefine_line|#define VDS_DEBUG_PROM&t;&t;0x01&t;/* Print PROM debugging messages */
multiline_comment|/* external declarations of Linux kernel functions. */
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
id|xwidgetnum_t
id|nodevertex_widgetnum_get
c_func
(paren
id|devfs_handle_t
id|node_vtx
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|nodevertex_xbow_peer_get
c_func
(paren
id|devfs_handle_t
id|node_vtx
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
r_void
id|setup_gfxpipe_link
c_func
(paren
id|devfs_handle_t
id|vhdl
comma
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
id|find_lboard_module_class
c_func
(paren
id|lboard_t
op_star
id|start
comma
id|moduleid_t
id|mod
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
id|moduleid_t
id|mod
comma
id|slotid_t
id|slot
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
id|moduleid_t
id|mod
)paren
suffix:semicolon
r_extern
id|lboard_t
op_star
id|get_board_name
c_func
(paren
id|nasid_t
id|nasid
comma
id|moduleid_t
id|mod
comma
id|slotid_t
id|slot
comma
r_char
op_star
id|name
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
id|klcpu_t
op_star
id|get_cpuinfo
c_func
(paren
id|cpuid_t
id|cpu
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
id|moduleid_t
id|get_module_id
c_func
(paren
id|nasid_t
id|nasid
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
r_int
id|is_master_baseio
c_func
(paren
id|nasid_t
comma
id|moduleid_t
comma
id|slotid_t
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
macro_line|#endif /* _ASM_SN_KLCONFIG_H */
eof
