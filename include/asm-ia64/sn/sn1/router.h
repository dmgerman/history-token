multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef&t;_ASM_SN_SN1_ROUTER_H
DECL|macro|_ASM_SN_SN1_ROUTER_H
mdefine_line|#define&t;_ASM_SN_SN1_ROUTER_H
multiline_comment|/*&n; * Router Register definitions&n; *&n; * Macro argument _L always stands for a link number (1 to 8, inclusive).&n; */
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
macro_line|#include &lt;asm/sn/vector.h&gt;
macro_line|#include &lt;asm/sn/slotnum.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
DECL|typedef|router_reg_t
r_typedef
r_uint64
id|router_reg_t
suffix:semicolon
DECL|macro|MAX_ROUTERS
mdefine_line|#define MAX_ROUTERS&t;64
DECL|macro|MAX_ROUTER_PATH
mdefine_line|#define MAX_ROUTER_PATH&t;80
DECL|macro|ROUTER_REG_CAST
mdefine_line|#define ROUTER_REG_CAST&t;&t;(volatile router_reg_t *)
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST&t;&t;(__psunsigned_t)
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST&t;&t;(uint64_t)
DECL|typedef|port_no_t
r_typedef
r_int
r_char
id|port_no_t
suffix:semicolon
multiline_comment|/* Type for router port number      */
macro_line|#elif _LANGUAGE_ASSEMBLY
DECL|macro|ROUTERREG_CAST
mdefine_line|#define ROUTERREG_CAST
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST
macro_line|#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
DECL|macro|MAX_ROUTER_PORTS
mdefine_line|#define MAX_ROUTER_PORTS (8)&t; /* Max. number of ports on a router */
DECL|macro|ALL_PORTS
mdefine_line|#define ALL_PORTS ((1 &lt;&lt; MAX_ROUTER_PORTS) - 1)&t;/* for 0 based references */
DECL|macro|PORT_INVALID
mdefine_line|#define PORT_INVALID (-1)&t; /* Invalid port number              */
DECL|macro|IS_META
mdefine_line|#define&t;IS_META(_rp)&t;((_rp)-&gt;flags &amp; PCFG_ROUTER_META)
DECL|macro|IS_REPEATER
mdefine_line|#define&t;IS_REPEATER(_rp)((_rp)-&gt;flags &amp; PCFG_ROUTER_REPEATER)
multiline_comment|/*&n; * RR_TURN makes a given number of clockwise turns (0 to 7) from an inport&n; * port to generate an output port.&n; *&n; * RR_DISTANCE returns the number of turns necessary (0 to 7) to go from&n; * an input port (_L1 = 1 to 8) to an output port ( _L2 = 1 to 8).&n; *&n; * These are written to work on unsigned data.&n; */
DECL|macro|RR_TURN
mdefine_line|#define RR_TURN(_L, count)&t;((_L) + (count) &gt; MAX_ROUTER_PORTS ?&t;&bslash;&n;&t;&t;&t;&t; (_L) + (count) - MAX_ROUTER_PORTS :&t;&bslash;&n;&t;&t;&t;&t; (_L) + (count))
DECL|macro|RR_DISTANCE
mdefine_line|#define RR_DISTANCE(_LS, _LD)&t;((_LD) &gt;= (_LS) ?&t;&t;&t;&bslash;&n;&t;&t;&t;&t; (_LD) - (_LS) :&t;&t;&t;&bslash;&n;&t;&t;&t;&t; (_LD) + MAX_ROUTER_PORTS - (_LS))
multiline_comment|/* Router register addresses */
DECL|macro|RR_STATUS_REV_ID
mdefine_line|#define RR_STATUS_REV_ID&t;0x00000&t;/* Status register and Revision ID  */
DECL|macro|RR_PORT_RESET
mdefine_line|#define RR_PORT_RESET&t;&t;0x00008&t;/* Multiple port reset              */
DECL|macro|RR_PROT_CONF
mdefine_line|#define RR_PROT_CONF&t;&t;0x00010&t;/* Inter-partition protection conf. */
DECL|macro|RR_GLOBAL_PORT_DEF
mdefine_line|#define RR_GLOBAL_PORT_DEF&t;0x00018 /* Global Port definitions          */
DECL|macro|RR_GLOBAL_PARMS0
mdefine_line|#define RR_GLOBAL_PARMS0&t;0x00020&t;/* Parameters shared by all 8 ports */
DECL|macro|RR_GLOBAL_PARMS1
mdefine_line|#define RR_GLOBAL_PARMS1&t;0x00028&t;/* Parameters shared by all 8 ports */
DECL|macro|RR_DIAG_PARMS
mdefine_line|#define RR_DIAG_PARMS&t;&t;0x00030&t;/* Parameters for diag. testing     */
DECL|macro|RR_DEBUG_ADDR
mdefine_line|#define RR_DEBUG_ADDR&t;&t;0x00038 /* Debug address select - debug port*/
DECL|macro|RR_LB_TO_L2
mdefine_line|#define RR_LB_TO_L2&t;&t;0x00040 /* Local Block to L2 cntrl intf reg */ 
DECL|macro|RR_L2_TO_LB
mdefine_line|#define RR_L2_TO_LB&t;&t;0x00048 /* L2 cntrl intf to Local Block reg */
DECL|macro|RR_JBUS_CONTROL
mdefine_line|#define RR_JBUS_CONTROL&t;&t;0x00050 /* read/write timing for JBUS intf  */
DECL|macro|RR_SCRATCH_REG0
mdefine_line|#define RR_SCRATCH_REG0&t;&t;0x00100&t;/* Scratch 0 is 64 bits */
DECL|macro|RR_SCRATCH_REG1
mdefine_line|#define RR_SCRATCH_REG1&t;&t;0x00108&t;/* Scratch 1 is 64 bits */
DECL|macro|RR_SCRATCH_REG2
mdefine_line|#define RR_SCRATCH_REG2&t;&t;0x00110&t;/* Scratch 2 is 64 bits */
DECL|macro|RR_SCRATCH_REG3
mdefine_line|#define RR_SCRATCH_REG3&t;&t;0x00118&t;/* Scratch 3 is 1 bit */
DECL|macro|RR_SCRATCH_REG4
mdefine_line|#define RR_SCRATCH_REG4&t;&t;0x00120&t;/* Scratch 4 is 1 bit */
DECL|macro|RR_JBUS0
mdefine_line|#define RR_JBUS0(_D)&t;&t;(((_D) &amp; 0x7) &lt;&lt; 3 | 0x00200) /* JBUS0 addresses   */
DECL|macro|RR_JBUS1
mdefine_line|#define RR_JBUS1(_D)&t;&t;(((_D) &amp; 0x7) &lt;&lt; 3 | 0x00240) /* JBUS1 addresses   */
DECL|macro|RR_SCRATCH_REG0_WZ
mdefine_line|#define RR_SCRATCH_REG0_WZ&t;0x00500&t;/* Scratch 0 is 64 bits */
DECL|macro|RR_SCRATCH_REG1_WZ
mdefine_line|#define RR_SCRATCH_REG1_WZ&t;0x00508&t;/* Scratch 1 is 64 bits */
DECL|macro|RR_SCRATCH_REG2_WZ
mdefine_line|#define RR_SCRATCH_REG2_WZ&t;0x00510&t;/* Scratch 2 is 64 bits */
DECL|macro|RR_SCRATCH_REG3_SZ
mdefine_line|#define RR_SCRATCH_REG3_SZ&t;0x00518&t;/* Scratch 3 is 1 bit */
DECL|macro|RR_SCRATCH_REG4_SZ
mdefine_line|#define RR_SCRATCH_REG4_SZ&t;0x00520&t;/* Scratch 4 is 1 bit */
DECL|macro|RR_VECTOR_HW_BAR
mdefine_line|#define RR_VECTOR_HW_BAR(context) (0x08000 | (context)&lt;&lt;3) /* barrier config registers */
multiline_comment|/* Port-specific registers (_L is the link number from 1 to 8) */
DECL|macro|RR_PORT_PARMS
mdefine_line|#define RR_PORT_PARMS(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0000) /* LLP parameters     */
DECL|macro|RR_STATUS_ERROR
mdefine_line|#define RR_STATUS_ERROR(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0008) /* Port-related errs  */
DECL|macro|RR_CHANNEL_TEST
mdefine_line|#define RR_CHANNEL_TEST(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0010) /* Port LLP chan test */
DECL|macro|RR_RESET_MASK
mdefine_line|#define RR_RESET_MASK(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0018) /* Remote reset mask  */
DECL|macro|RR_HISTOGRAM0
mdefine_line|#define RR_HISTOGRAM0(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0020) /* Port usage histgrm */
DECL|macro|RR_HISTOGRAM1
mdefine_line|#define RR_HISTOGRAM1(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0028) /* Port usage histgrm */
DECL|macro|RR_HISTOGRAM0_WC
mdefine_line|#define RR_HISTOGRAM0_WC(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0030) /* Port usage histgrm */
DECL|macro|RR_HISTOGRAM1_WC
mdefine_line|#define RR_HISTOGRAM1_WC(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0038) /* Port usage histgrm */
DECL|macro|RR_ERROR_CLEAR
mdefine_line|#define RR_ERROR_CLEAR(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0088) /* Read/clear errors  */
DECL|macro|RR_GLOBAL_TABLE0
mdefine_line|#define RR_GLOBAL_TABLE0(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0100) /* starting address of global table for this port */
DECL|macro|RR_GLOBAL_TABLE
mdefine_line|#define RR_GLOBAL_TABLE(_L, _x) (RR_GLOBAL_TABLE0(_L) + ((_x) &lt;&lt; 3))
DECL|macro|RR_LOCAL_TABLE0
mdefine_line|#define RR_LOCAL_TABLE0(_L)&t;(((_L+1) &amp; 0xe) &lt;&lt; 15 | ((_L+1) &amp; 0x1) &lt;&lt; 11 | 0x0200) /* starting address of local table for this port */
DECL|macro|RR_LOCAL_TABLE
mdefine_line|#define RR_LOCAL_TABLE(_L, _x) (RR_LOCAL_TABLE0(_L) + ((_x) &lt;&lt; 3))
DECL|macro|RR_META_ENTRIES
mdefine_line|#define RR_META_ENTRIES&t;&t;16
DECL|macro|RR_LOCAL_ENTRIES
mdefine_line|#define RR_LOCAL_ENTRIES&t;128
multiline_comment|/*&n; * RR_STATUS_REV_ID mask and shift definitions&n; */
DECL|macro|RSRI_INPORT_SHFT
mdefine_line|#define RSRI_INPORT_SHFT&t;52
DECL|macro|RSRI_INPORT_MASK
mdefine_line|#define RSRI_INPORT_MASK&t;(UINT64_CAST 0xf &lt;&lt; 52)
DECL|macro|RSRI_LINKWORKING_BIT
mdefine_line|#define RSRI_LINKWORKING_BIT(_L) (35 + 2 * (_L))
DECL|macro|RSRI_LINKWORKING
mdefine_line|#define RSRI_LINKWORKING(_L)&t;(UINT64_CAST 1 &lt;&lt; (35 + 2 * (_L)))
DECL|macro|RSRI_LINKRESETFAIL
mdefine_line|#define RSRI_LINKRESETFAIL(_L)&t;(UINT64_CAST 1 &lt;&lt; (34 + 2 * (_L)))
DECL|macro|RSRI_LSTAT_SHFT
mdefine_line|#define RSRI_LSTAT_SHFT(_L)&t;(34 + 2 * (_L))
DECL|macro|RSRI_LSTAT_MASK
mdefine_line|#define RSRI_LSTAT_MASK(_L)&t;(UINT64_CAST 0x3 &lt;&lt; 34 + 2 * (_L))
DECL|macro|RSRI_LOCALSBERROR
mdefine_line|#define RSRI_LOCALSBERROR&t;(UINT64_CAST 1 &lt;&lt; 35)
DECL|macro|RSRI_LOCALSTUCK
mdefine_line|#define RSRI_LOCALSTUCK&t;&t;(UINT64_CAST 1 &lt;&lt; 34)
DECL|macro|RSRI_LOCALBADVEC
mdefine_line|#define RSRI_LOCALBADVEC&t;(UINT64_CAST 1 &lt;&lt; 33)
DECL|macro|RSRI_LOCALTAILERR
mdefine_line|#define RSRI_LOCALTAILERR&t;(UINT64_CAST 1 &lt;&lt; 32)
DECL|macro|RSRI_LOCAL_SHFT
mdefine_line|#define RSRI_LOCAL_SHFT &t;32
DECL|macro|RSRI_LOCAL_MASK
mdefine_line|#define RSRI_LOCAL_MASK&t;&t;(UINT64_CAST 0xf &lt;&lt; 32)
DECL|macro|RSRI_CHIPREV_SHFT
mdefine_line|#define RSRI_CHIPREV_SHFT&t;28
DECL|macro|RSRI_CHIPREV_MASK
mdefine_line|#define RSRI_CHIPREV_MASK&t;(UINT64_CAST 0xf &lt;&lt; 28)
DECL|macro|RSRI_CHIPID_SHFT
mdefine_line|#define RSRI_CHIPID_SHFT&t;12
DECL|macro|RSRI_CHIPID_MASK
mdefine_line|#define RSRI_CHIPID_MASK&t;(UINT64_CAST 0xffff &lt;&lt; 12)
DECL|macro|RSRI_MFGID_SHFT
mdefine_line|#define RSRI_MFGID_SHFT&t;&t;1
DECL|macro|RSRI_MFGID_MASK
mdefine_line|#define RSRI_MFGID_MASK&t;&t;(UINT64_CAST 0x7ff &lt;&lt; 1)
DECL|macro|RSRI_LSTAT_WENTDOWN
mdefine_line|#define RSRI_LSTAT_WENTDOWN&t;0
DECL|macro|RSRI_LSTAT_RESETFAIL
mdefine_line|#define RSRI_LSTAT_RESETFAIL&t;1
DECL|macro|RSRI_LSTAT_LINKUP
mdefine_line|#define RSRI_LSTAT_LINKUP&t;2
DECL|macro|RSRI_LSTAT_NOTUSED
mdefine_line|#define RSRI_LSTAT_NOTUSED&t;3
multiline_comment|/*&n; * RR_PORT_RESET mask definitions&n; */
DECL|macro|RPRESET_WARM
mdefine_line|#define RPRESET_WARM&t;&t;(UINT64_CAST 1 &lt;&lt; 9)
DECL|macro|RPRESET_LINK
mdefine_line|#define RPRESET_LINK(_L)&t;(UINT64_CAST 1 &lt;&lt; (_L))
DECL|macro|RPRESET_LOCAL
mdefine_line|#define RPRESET_LOCAL&t;&t;(UINT64_CAST 1)
multiline_comment|/*&n; * RR_PROT_CONF mask and shift definitions&n; */
DECL|macro|RPCONF_DIRCMPDIS_SHFT
mdefine_line|#define RPCONF_DIRCMPDIS_SHFT&t;13
DECL|macro|RPCONF_DIRCMPDIS_MASK
mdefine_line|#define RPCONF_DIRCMPDIS_MASK&t;(UINT64_CAST 1 &lt;&lt; 13)
DECL|macro|RPCONF_FORCELOCAL
mdefine_line|#define RPCONF_FORCELOCAL&t;(UINT64_CAST 1 &lt;&lt; 12)
DECL|macro|RPCONF_FLOCAL_SHFT
mdefine_line|#define RPCONF_FLOCAL_SHFT&t;12
DECL|macro|RPCONF_METAID_SHFT
mdefine_line|#define RPCONF_METAID_SHFT&t;8
DECL|macro|RPCONF_METAID_MASK
mdefine_line|#define RPCONF_METAID_MASK&t;(UINT64_CAST 0xf &lt;&lt; 8)
DECL|macro|RPCONF_RESETOK
mdefine_line|#define RPCONF_RESETOK(_L)&t;(UINT64_CAST 1 &lt;&lt; ((_L) - 1))
multiline_comment|/*&n; * RR_GLOBAL_PORT_DEF mask and shift definitions&n; */
DECL|macro|RGPD_MGLBLNHBR_ID_SHFT
mdefine_line|#define RGPD_MGLBLNHBR_ID_SHFT&t;12&t;/* -global neighbor ID */
DECL|macro|RGPD_MGLBLNHBR_ID_MASK
mdefine_line|#define RGPD_MGLBLNHBR_ID_MASK&t;(UINT64_CAST 0xf &lt;&lt; 12)
DECL|macro|RGPD_MGLBLNHBR_VLD_SHFT
mdefine_line|#define RGPD_MGLBLNHBR_VLD_SHFT&t;11&t;/* -global neighbor Valid */
DECL|macro|RGPD_MGLBLNHBR_VLD_MASK
mdefine_line|#define RGPD_MGLBLNHBR_VLD_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 11)
DECL|macro|RGPD_MGLBLPORT_SHFT
mdefine_line|#define RGPD_MGLBLPORT_SHFT&t;8&t;/* -global neighbor Port */
DECL|macro|RGPD_MGLBLPORT_MASK
mdefine_line|#define RGPD_MGLBLPORT_MASK&t;(UINT64_CAST 0x7 &lt;&lt; 8)
DECL|macro|RGPD_PGLBLNHBR_ID_SHFT
mdefine_line|#define RGPD_PGLBLNHBR_ID_SHFT&t;4&t;/* +global neighbor ID */
DECL|macro|RGPD_PGLBLNHBR_ID_MASK
mdefine_line|#define RGPD_PGLBLNHBR_ID_MASK&t;(UINT64_CAST 0xf &lt;&lt; 4)
DECL|macro|RGPD_PGLBLNHBR_VLD_SHFT
mdefine_line|#define RGPD_PGLBLNHBR_VLD_SHFT&t;3&t;/* +global neighbor Valid */
DECL|macro|RGPD_PGLBLNHBR_VLD_MASK
mdefine_line|#define RGPD_PGLBLNHBR_VLD_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 3)
DECL|macro|RGPD_PGLBLPORT_SHFT
mdefine_line|#define RGPD_PGLBLPORT_SHFT&t;0&t;/* +global neighbor Port */
DECL|macro|RGPD_PGLBLPORT_MASK
mdefine_line|#define RGPD_PGLBLPORT_MASK&t;(UINT64_CAST 0x7 &lt;&lt; 0)
DECL|macro|GLBL_PARMS_REGS
mdefine_line|#define GLBL_PARMS_REGS&t;&t;2&t;/* Two Global Parms registers */
multiline_comment|/*&n; * RR_GLOBAL_PARMS0 mask and shift definitions&n; */
DECL|macro|RGPARM0_ARB_VALUE_SHFT
mdefine_line|#define RGPARM0_ARB_VALUE_SHFT&t;54&t;/* Local Block Arbitration State */
DECL|macro|RGPARM0_ARB_VALUE_MASK
mdefine_line|#define RGPARM0_ARB_VALUE_MASK&t;(UINT64_CAST 0x7 &lt;&lt; 54)
DECL|macro|RGPARM0_ROTATEARB_SHFT
mdefine_line|#define RGPARM0_ROTATEARB_SHFT&t;53&t;/* Rotate Local Block Arbitration */
DECL|macro|RGPARM0_ROTATEARB_MASK
mdefine_line|#define RGPARM0_ROTATEARB_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 53)
DECL|macro|RGPARM0_FAIREN_SHFT
mdefine_line|#define RGPARM0_FAIREN_SHFT&t;52&t;/* Fairness logic Enable */
DECL|macro|RGPARM0_FAIREN_MASK
mdefine_line|#define RGPARM0_FAIREN_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 52)
DECL|macro|RGPARM0_LOCGNTTO_SHFT
mdefine_line|#define RGPARM0_LOCGNTTO_SHFT&t;40&t;/* Local grant timeout */
DECL|macro|RGPARM0_LOCGNTTO_MASK
mdefine_line|#define RGPARM0_LOCGNTTO_MASK&t;(UINT64_CAST 0xfff &lt;&lt; 40)
DECL|macro|RGPARM0_DATELINE_SHFT
mdefine_line|#define RGPARM0_DATELINE_SHFT&t;38&t;/* Dateline crossing router */
DECL|macro|RGPARM0_DATELINE_MASK
mdefine_line|#define RGPARM0_DATELINE_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 38)
DECL|macro|RGPARM0_MAXRETRY_SHFT
mdefine_line|#define RGPARM0_MAXRETRY_SHFT&t;28&t;/* Max retry count */
DECL|macro|RGPARM0_MAXRETRY_MASK
mdefine_line|#define RGPARM0_MAXRETRY_MASK&t;(UINT64_CAST 0x3ff &lt;&lt; 28)
DECL|macro|RGPARM0_URGWRAP_SHFT
mdefine_line|#define RGPARM0_URGWRAP_SHFT&t;20&t;/* Urgent wrap */
DECL|macro|RGPARM0_URGWRAP_MASK
mdefine_line|#define RGPARM0_URGWRAP_MASK&t;(UINT64_CAST 0xff &lt;&lt; 20)
DECL|macro|RGPARM0_DEADLKTO_SHFT
mdefine_line|#define RGPARM0_DEADLKTO_SHFT&t;16&t;/* Deadlock timeout */
DECL|macro|RGPARM0_DEADLKTO_MASK
mdefine_line|#define RGPARM0_DEADLKTO_MASK&t;(UINT64_CAST 0xf &lt;&lt; 16)
DECL|macro|RGPARM0_URGVAL_SHFT
mdefine_line|#define RGPARM0_URGVAL_SHFT&t;12&t;/* Urgent value */
DECL|macro|RGPARM0_URGVAL_MASK
mdefine_line|#define RGPARM0_URGVAL_MASK&t;(UINT64_CAST 0xf &lt;&lt; 12)
DECL|macro|RGPARM0_VCHSELEN_SHFT
mdefine_line|#define RGPARM0_VCHSELEN_SHFT&t;11&t;/* VCH_SEL_EN */
DECL|macro|RGPARM0_VCHSELEN_MASK
mdefine_line|#define RGPARM0_VCHSELEN_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 11)
DECL|macro|RGPARM0_LOCURGTO_SHFT
mdefine_line|#define RGPARM0_LOCURGTO_SHFT&t;9&t;/* Local urgent timeout */
DECL|macro|RGPARM0_LOCURGTO_MASK
mdefine_line|#define RGPARM0_LOCURGTO_MASK&t;(UINT64_CAST 0x3 &lt;&lt; 9)
DECL|macro|RGPARM0_TAILVAL_SHFT
mdefine_line|#define RGPARM0_TAILVAL_SHFT&t;5&t;/* Tail value */
DECL|macro|RGPARM0_TAILVAL_MASK
mdefine_line|#define RGPARM0_TAILVAL_MASK&t;(UINT64_CAST 0xf &lt;&lt; 5)
DECL|macro|RGPARM0_CLOCK_SHFT
mdefine_line|#define RGPARM0_CLOCK_SHFT&t;1&t;/* Global clock select */
DECL|macro|RGPARM0_CLOCK_MASK
mdefine_line|#define RGPARM0_CLOCK_MASK&t;(UINT64_CAST 0xf &lt;&lt; 1)
DECL|macro|RGPARM0_BYPEN_SHFT
mdefine_line|#define RGPARM0_BYPEN_SHFT&t;0
DECL|macro|RGPARM0_BYPEN_MASK
mdefine_line|#define RGPARM0_BYPEN_MASK&t;(UINT64_CAST 1)&t;/* Bypass enable */
multiline_comment|/*&n; * RR_GLOBAL_PARMS1 shift and mask definitions&n; */
DECL|macro|RGPARM1_TTOWRAP_SHFT
mdefine_line|#define RGPARM1_TTOWRAP_SHFT&t;12&t;/* Tail timeout wrap */
DECL|macro|RGPARM1_TTOWRAP_MASK
mdefine_line|#define RGPARM1_TTOWRAP_MASK&t;(UINT64_CAST 0xfffff &lt;&lt; 12)
DECL|macro|RGPARM1_AGERATE_SHFT
mdefine_line|#define RGPARM1_AGERATE_SHFT&t;8&t;/* Age rate */
DECL|macro|RGPARM1_AGERATE_MASK
mdefine_line|#define RGPARM1_AGERATE_MASK&t;(UINT64_CAST 0xf &lt;&lt; 8)
DECL|macro|RGPARM1_JSWSTAT_SHFT
mdefine_line|#define RGPARM1_JSWSTAT_SHFT&t;0&t;/* JTAG Sw Register bits */
DECL|macro|RGPARM1_JSWSTAT_MASK
mdefine_line|#define RGPARM1_JSWSTAT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 0)
multiline_comment|/*&n; * RR_DIAG_PARMS mask and shift definitions&n; */
DECL|macro|RDPARM_ABSHISTOGRAM
mdefine_line|#define RDPARM_ABSHISTOGRAM&t;(UINT64_CAST 1 &lt;&lt; 17)&t;/* Absolute histgrm */
DECL|macro|RDPARM_DEADLOCKRESET
mdefine_line|#define RDPARM_DEADLOCKRESET&t;(UINT64_CAST 1 &lt;&lt; 16)&t;/* Reset on deadlck */
DECL|macro|RDPARM_DISABLE
mdefine_line|#define RDPARM_DISABLE(_L)&t;(UINT64_CAST 1 &lt;&lt; ((_L) +  7))
DECL|macro|RDPARM_SENDERROR
mdefine_line|#define RDPARM_SENDERROR(_L)&t;(UINT64_CAST 1 &lt;&lt; ((_L) -  1))
multiline_comment|/*&n; * RR_DEBUG_ADDR mask and shift definitions&n; */
DECL|macro|RDA_DATA_SHFT
mdefine_line|#define RDA_DATA_SHFT&t;&t;10&t;/* Observed debug data */
DECL|macro|RDA_DATA_MASK
mdefine_line|#define RDA_DATA_MASK&t;&t;(UINT64_CAST 0xffff &lt;&lt; 10)
DECL|macro|RDA_ADDR_SHFT
mdefine_line|#define RDA_ADDR_SHFT&t;&t;0&t;/* debug address for data */
DECL|macro|RDA_ADDR_MASK
mdefine_line|#define RDA_ADDR_MASK&t;&t;(UINT64_CAST 0x3ff &lt;&lt; 0)
multiline_comment|/*&n; * RR_LB_TO_L2 mask and shift definitions&n; */
DECL|macro|RLBTOL2_DATA_VLD_SHFT
mdefine_line|#define RLBTOL2_DATA_VLD_SHFT&t;32&t;/* data is valid for JTAG controller */
DECL|macro|RLBTOL2_DATA_VLD_MASK
mdefine_line|#define RLBTOL2_DATA_VLD_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 32)
DECL|macro|RLBTOL2_DATA_SHFT
mdefine_line|#define RLBTOL2_DATA_SHFT&t;0&t;/* data bits for JTAG controller */
DECL|macro|RLBTOL2_DATA_MASK
mdefine_line|#define RLBTOL2_DATA_MASK&t;(UINT64_CAST 0xffffffff)
multiline_comment|/*&n; * RR_L2_TO_LB mask and shift definitions&n; */
DECL|macro|RL2TOLB_DATA_VLD_SHFT
mdefine_line|#define RL2TOLB_DATA_VLD_SHFT&t;33&t;/* data is valid from JTAG controller */
DECL|macro|RL2TOLB_DATA_VLD_MASK
mdefine_line|#define RL2TOLB_DATA_VLD_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 33)
DECL|macro|RL2TOLB_PARITY_SHFT
mdefine_line|#define RL2TOLB_PARITY_SHFT&t;32&t;/* sw implemented parity for data */
DECL|macro|RL2TOLB_PARITY_MASK
mdefine_line|#define RL2TOLB_PARITY_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 32)
DECL|macro|RL2TOLB_DATA_SHFT
mdefine_line|#define RL2TOLB_DATA_SHFT&t;0&t;/* data bits from JTAG controller */
DECL|macro|RL2TOLB_DATA_MASK
mdefine_line|#define RL2TOLB_DATA_MASK&t;(UINT64_CAST 0xffffffff)
multiline_comment|/*&n; * RR_JBUS_CONTROL mask and shift definitions&n; */
DECL|macro|RJC_POS_BITS_SHFT
mdefine_line|#define RJC_POS_BITS_SHFT&t;20&t;/* Router position bits */
DECL|macro|RJC_POS_BITS_MASK
mdefine_line|#define RJC_POS_BITS_MASK&t;(UINT64_CAST 0xf &lt;&lt; 20)
DECL|macro|RJC_RD_DATA_STROBE_SHFT
mdefine_line|#define RJC_RD_DATA_STROBE_SHFT&t;16&t;/* count when read data is strobed in */
DECL|macro|RJC_RD_DATA_STROBE_MASK
mdefine_line|#define RJC_RD_DATA_STROBE_MASK&t;(UINT64_CAST 0xf &lt;&lt; 16)
DECL|macro|RJC_WE_OE_HOLD_SHFT
mdefine_line|#define RJC_WE_OE_HOLD_SHFT&t;8&t;/* time OE or WE is held */
DECL|macro|RJC_WE_OE_HOLD_MASK
mdefine_line|#define RJC_WE_OE_HOLD_MASK&t;(UINT64_CAST 0xff &lt;&lt; 8)
DECL|macro|RJC_ADDR_SET_HLD_SHFT
mdefine_line|#define RJC_ADDR_SET_HLD_SHFT&t;0&t;/* time address driven around OE/WE */
DECL|macro|RJC_ADDR_SET_HLD_MASK
mdefine_line|#define RJC_ADDR_SET_HLD_MASK&t;(UINT64_CAST 0xff)
multiline_comment|/*&n; * RR_SCRATCH_REGx mask and shift definitions&n; *  note: these fields represent a software convention, and are not&n; *        understood/interpreted by the hardware. &n; */
DECL|macro|RSCR0_BOOTED_SHFT
mdefine_line|#define&t;RSCR0_BOOTED_SHFT&t;63
DECL|macro|RSCR0_BOOTED_MASK
mdefine_line|#define&t;RSCR0_BOOTED_MASK&t;(UINT64_CAST 0x1 &lt;&lt; RSCR0_BOOTED_SHFT)
DECL|macro|RSCR0_LOCALID_SHFT
mdefine_line|#define RSCR0_LOCALID_SHFT&t;56
DECL|macro|RSCR0_LOCALID_MASK
mdefine_line|#define RSCR0_LOCALID_MASK&t;(UINT64_CAST 0x7f &lt;&lt; RSCR0_LOCALID_SHFT)
DECL|macro|RSCR0_UNUSED_SHFT
mdefine_line|#define&t;RSCR0_UNUSED_SHFT&t;48
DECL|macro|RSCR0_UNUSED_MASK
mdefine_line|#define&t;RSCR0_UNUSED_MASK&t;(UINT64_CAST 0xff &lt;&lt; RSCR0_UNUSED_SHFT)
DECL|macro|RSCR0_NIC_SHFT
mdefine_line|#define RSCR0_NIC_SHFT&t;&t;0
DECL|macro|RSCR0_NIC_MASK
mdefine_line|#define RSCR0_NIC_MASK&t;&t;(UINT64_CAST 0xffffffffffff)
DECL|macro|RSCR1_MODID_SHFT
mdefine_line|#define RSCR1_MODID_SHFT&t;0
DECL|macro|RSCR1_MODID_MASK
mdefine_line|#define RSCR1_MODID_MASK&t;(UINT64_CAST 0xffff)
multiline_comment|/*&n; * RR_VECTOR_HW_BAR mask and shift definitions&n; */
DECL|macro|BAR_TX_SHFT
mdefine_line|#define BAR_TX_SHFT&t;&t;27&t;/* Barrier in trans(m)it when read */
DECL|macro|BAR_TX_MASK
mdefine_line|#define BAR_TX_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; BAR_TX_SHFT)
DECL|macro|BAR_VLD_SHFT
mdefine_line|#define BAR_VLD_SHFT&t;&t;26&t;/* Valid Configuration */
DECL|macro|BAR_VLD_MASK
mdefine_line|#define BAR_VLD_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; BAR_VLD_SHFT)
DECL|macro|BAR_SEQ_SHFT
mdefine_line|#define BAR_SEQ_SHFT&t;&t;24&t;/* Sequence number */
DECL|macro|BAR_SEQ_MASK
mdefine_line|#define BAR_SEQ_MASK&t;&t;(UINT64_CAST 3 &lt;&lt; BAR_SEQ_SHFT)
DECL|macro|BAR_LEAFSTATE_SHFT
mdefine_line|#define BAR_LEAFSTATE_SHFT&t;18&t;/* Leaf State */
DECL|macro|BAR_LEAFSTATE_MASK
mdefine_line|#define BAR_LEAFSTATE_MASK&t;(UINT64_CAST 0x3f &lt;&lt; BAR_LEAFSTATE_SHFT)
DECL|macro|BAR_PARENT_SHFT
mdefine_line|#define BAR_PARENT_SHFT&t;&t;14&t;/* Parent Port */
DECL|macro|BAR_PARENT_MASK
mdefine_line|#define BAR_PARENT_MASK&t;&t;(UINT64_CAST 0xf &lt;&lt; BAR_PARENT_SHFT)
DECL|macro|BAR_CHILDREN_SHFT
mdefine_line|#define BAR_CHILDREN_SHFT&t;6&t;/* Child Select port bits */
DECL|macro|BAR_CHILDREN_MASK
mdefine_line|#define BAR_CHILDREN_MASK&t;(UINT64_CAST 0xff &lt;&lt; BAR_CHILDREN_SHFT)
DECL|macro|BAR_LEAFCOUNT_SHFT
mdefine_line|#define BAR_LEAFCOUNT_SHFT&t;0&t;/* Leaf Count to trigger parent */
DECL|macro|BAR_LEAFCOUNT_MASK
mdefine_line|#define BAR_LEAFCOUNT_MASK&t;(UINT64_CAST 0x3f)
multiline_comment|/*&n; * RR_PORT_PARMS(_L) mask and shift definitions&n; */
DECL|macro|RPPARM_MIPRESETEN_SHFT
mdefine_line|#define RPPARM_MIPRESETEN_SHFT&t;29&t;/* Message In Progress reset enable */
DECL|macro|RPPARM_MIPRESETEN_MASK
mdefine_line|#define RPPARM_MIPRESETEN_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 29)
DECL|macro|RPPARM_UBAREN_SHFT
mdefine_line|#define RPPARM_UBAREN_SHFT&t;28&t;/* Enable user barrier requests */
DECL|macro|RPPARM_UBAREN_MASK
mdefine_line|#define RPPARM_UBAREN_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 28)
DECL|macro|RPPARM_OUTPDTO_SHFT
mdefine_line|#define RPPARM_OUTPDTO_SHFT&t;24&t;/* Output Port Deadlock TO value */
DECL|macro|RPPARM_OUTPDTO_MASK
mdefine_line|#define RPPARM_OUTPDTO_MASK&t;(UINT64_CAST 0xf &lt;&lt; 24)
DECL|macro|RPPARM_PORTMATE_SHFT
mdefine_line|#define RPPARM_PORTMATE_SHFT&t;21&t;/* Port Mate for the port */
DECL|macro|RPPARM_PORTMATE_MASK
mdefine_line|#define RPPARM_PORTMATE_MASK&t;(UINT64_CAST 0x7 &lt;&lt; 21)
DECL|macro|RPPARM_HISTEN_SHFT
mdefine_line|#define RPPARM_HISTEN_SHFT&t;20&t;/* Histogram counter enable */
DECL|macro|RPPARM_HISTEN_MASK
mdefine_line|#define RPPARM_HISTEN_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 20)
DECL|macro|RPPARM_HISTSEL_SHFT
mdefine_line|#define RPPARM_HISTSEL_SHFT&t;18
DECL|macro|RPPARM_HISTSEL_MASK
mdefine_line|#define RPPARM_HISTSEL_MASK&t;(UINT64_CAST 0x3 &lt;&lt; 18)
DECL|macro|RPPARM_DAMQHS_SHFT
mdefine_line|#define RPPARM_DAMQHS_SHFT&t;16
DECL|macro|RPPARM_DAMQHS_MASK
mdefine_line|#define RPPARM_DAMQHS_MASK&t;(UINT64_CAST 0x3 &lt;&lt; 16)
DECL|macro|RPPARM_NULLTO_SHFT
mdefine_line|#define RPPARM_NULLTO_SHFT&t;10
DECL|macro|RPPARM_NULLTO_MASK
mdefine_line|#define RPPARM_NULLTO_MASK&t;(UINT64_CAST 0x3f &lt;&lt; 10)
DECL|macro|RPPARM_MAXBURST_SHFT
mdefine_line|#define RPPARM_MAXBURST_SHFT&t;0
DECL|macro|RPPARM_MAXBURST_MASK
mdefine_line|#define RPPARM_MAXBURST_MASK&t;(UINT64_CAST 0x3ff)
multiline_comment|/*&n; * NOTE: Normally the kernel tracks only UTILIZATION statistics.&n; * The other 2 should not be used, except during any experimentation&n; * with the router.&n; */
DECL|macro|RPPARM_HISTSEL_AGE
mdefine_line|#define RPPARM_HISTSEL_AGE&t;0&t;/* Histogram age characterization.  */
DECL|macro|RPPARM_HISTSEL_UTIL
mdefine_line|#define RPPARM_HISTSEL_UTIL&t;1&t;/* Histogram link utilization &t;    */
DECL|macro|RPPARM_HISTSEL_DAMQ
mdefine_line|#define RPPARM_HISTSEL_DAMQ&t;2&t;/* Histogram DAMQ characterization. */
multiline_comment|/*&n; * RR_STATUS_ERROR(_L) and RR_ERROR_CLEAR(_L) mask and shift definitions&n; */
DECL|macro|RSERR_POWERNOK
mdefine_line|#define RSERR_POWERNOK&t;&t;(UINT64_CAST 1 &lt;&lt; 38)
DECL|macro|RSERR_PORT_DEADLOCK
mdefine_line|#define RSERR_PORT_DEADLOCK     (UINT64_CAST 1 &lt;&lt; 37)
DECL|macro|RSERR_WARMRESET
mdefine_line|#define RSERR_WARMRESET         (UINT64_CAST 1 &lt;&lt; 36)
DECL|macro|RSERR_LINKRESET
mdefine_line|#define RSERR_LINKRESET         (UINT64_CAST 1 &lt;&lt; 35)
DECL|macro|RSERR_RETRYTIMEOUT
mdefine_line|#define RSERR_RETRYTIMEOUT      (UINT64_CAST 1 &lt;&lt; 34)
DECL|macro|RSERR_FIFOOVERFLOW
mdefine_line|#define RSERR_FIFOOVERFLOW&t;(UINT64_CAST 1 &lt;&lt; 33)
DECL|macro|RSERR_ILLEGALPORT
mdefine_line|#define RSERR_ILLEGALPORT&t;(UINT64_CAST 1 &lt;&lt; 32)
DECL|macro|RSERR_DEADLOCKTO_SHFT
mdefine_line|#define RSERR_DEADLOCKTO_SHFT&t;28
DECL|macro|RSERR_DEADLOCKTO_MASK
mdefine_line|#define RSERR_DEADLOCKTO_MASK&t;(UINT64_CAST 0xf &lt;&lt; 28)
DECL|macro|RSERR_RECVTAILTO_SHFT
mdefine_line|#define RSERR_RECVTAILTO_SHFT&t;24
DECL|macro|RSERR_RECVTAILTO_MASK
mdefine_line|#define RSERR_RECVTAILTO_MASK&t;(UINT64_CAST 0xf &lt;&lt; 24)
DECL|macro|RSERR_RETRYCNT_SHFT
mdefine_line|#define RSERR_RETRYCNT_SHFT&t;16
DECL|macro|RSERR_RETRYCNT_MASK
mdefine_line|#define RSERR_RETRYCNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 16)
DECL|macro|RSERR_CBERRCNT_SHFT
mdefine_line|#define RSERR_CBERRCNT_SHFT&t;8
DECL|macro|RSERR_CBERRCNT_MASK
mdefine_line|#define RSERR_CBERRCNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 8)
DECL|macro|RSERR_SNERRCNT_SHFT
mdefine_line|#define RSERR_SNERRCNT_SHFT&t;0
DECL|macro|RSERR_SNERRCNT_MASK
mdefine_line|#define RSERR_SNERRCNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 0)
DECL|macro|PORT_STATUS_UP
mdefine_line|#define PORT_STATUS_UP&t;&t;(1 &lt;&lt; 0)&t;/* Router link up */
DECL|macro|PORT_STATUS_FENCE
mdefine_line|#define PORT_STATUS_FENCE&t;(1 &lt;&lt; 1)&t;/* Router link fenced */
DECL|macro|PORT_STATUS_RESETFAIL
mdefine_line|#define PORT_STATUS_RESETFAIL&t;(1 &lt;&lt; 2)&t;/* Router link didnot &n;&t;&t;&t;&t;&t;&t; * come out of reset */
DECL|macro|PORT_STATUS_DISCFAIL
mdefine_line|#define PORT_STATUS_DISCFAIL&t;(1 &lt;&lt; 3)&t;/* Router link failed after &n;&t;&t;&t;&t;&t;&t; * out of reset but before&n;&t;&t;&t;&t;&t;&t; * router tables were&n;&t;&t;&t;&t;&t;&t; * programmed&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PORT_STATUS_KERNFAIL
mdefine_line|#define PORT_STATUS_KERNFAIL&t;(1 &lt;&lt; 4)&t;/* Router link failed&n;&t;&t;&t;&t;&t;&t; * after reset and the &n;&t;&t;&t;&t;&t;&t; * router tables were&n;&t;&t;&t;&t;&t;&t; * programmed&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PORT_STATUS_UNDEF
mdefine_line|#define PORT_STATUS_UNDEF&t;(1 &lt;&lt; 5)&t;/* Unable to pinpoint&n;&t;&t;&t;&t;&t;&t; * why the router link&n;&t;&t;&t;&t;&t;&t; * went down&n;&t;&t;&t;&t;&t;&t; */&t;
DECL|macro|PROBE_RESULT_BAD
mdefine_line|#define PROBE_RESULT_BAD&t;(-1)&t;&t;/* Set if any of the router&n;&t;&t;&t;&t;&t;&t; * links failed after reset&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PROBE_RESULT_GOOD
mdefine_line|#define PROBE_RESULT_GOOD&t;(0)&t;&t;/* Set if all the router links&n;&t;&t;&t;&t;&t;&t; * which came out of reset &n;&t;&t;&t;&t;&t;&t; * are up&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Should be enough for 256 CPUs */
DECL|macro|MAX_RTR_BREADTH
mdefine_line|#define MAX_RTR_BREADTH&t;&t;64&t;&t;/* Max # of routers possible */
multiline_comment|/* Get the require set of bits in a var. corr to a sequence of bits  */
DECL|macro|GET_FIELD
mdefine_line|#define GET_FIELD(var, fname) &bslash;&n;        ((var) &gt;&gt; fname##_SHFT &amp; fname##_MASK &gt;&gt; fname##_SHFT)
multiline_comment|/* Set the require set of bits in a var. corr to a sequence of bits  */
DECL|macro|SET_FIELD
mdefine_line|#define SET_FIELD(var, fname, fval) &bslash;&n;        ((var) = (var) &amp; ~fname##_MASK | (uint64_t) (fval) &lt;&lt; fname##_SHFT)
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
DECL|struct|router_map_ent_s
r_typedef
r_struct
id|router_map_ent_s
(brace
DECL|member|nic
r_uint64
id|nic
suffix:semicolon
DECL|member|module
id|moduleid_t
id|module
suffix:semicolon
DECL|member|slot
id|slotid_t
id|slot
suffix:semicolon
DECL|typedef|router_map_ent_t
)brace
id|router_map_ent_t
suffix:semicolon
DECL|struct|rr_status_error_fmt
r_struct
id|rr_status_error_fmt
(brace
DECL|member|rserr_unused
r_uint64
id|rserr_unused
suffix:colon
l_int|30
comma
DECL|member|rserr_fifooverflow
id|rserr_fifooverflow
suffix:colon
l_int|1
comma
DECL|member|rserr_illegalport
id|rserr_illegalport
suffix:colon
l_int|1
comma
DECL|member|rserr_deadlockto
id|rserr_deadlockto
suffix:colon
l_int|4
comma
DECL|member|rserr_recvtailto
id|rserr_recvtailto
suffix:colon
l_int|4
comma
DECL|member|rserr_retrycnt
id|rserr_retrycnt
suffix:colon
l_int|8
comma
DECL|member|rserr_cberrcnt
id|rserr_cberrcnt
suffix:colon
l_int|8
comma
DECL|member|rserr_snerrcnt
id|rserr_snerrcnt
suffix:colon
l_int|8
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This type is used to store &quot;absolute&quot; counts of router events&n; */
DECL|typedef|router_count_t
r_typedef
r_int
id|router_count_t
suffix:semicolon
multiline_comment|/* All utilizations are on a scale from 0 - 1023. */
DECL|macro|RP_BYPASS_UTIL
mdefine_line|#define RP_BYPASS_UTIL&t;0
DECL|macro|RP_RCV_UTIL
mdefine_line|#define RP_RCV_UTIL&t;1
DECL|macro|RP_SEND_UTIL
mdefine_line|#define RP_SEND_UTIL&t;2
DECL|macro|RP_TOTAL_PKTS
mdefine_line|#define RP_TOTAL_PKTS&t;3&t;/* Free running clock/packet counter */
DECL|macro|RP_NUM_UTILS
mdefine_line|#define RP_NUM_UTILS&t;3
DECL|macro|RP_HIST_REGS
mdefine_line|#define RP_HIST_REGS&t;2
DECL|macro|RP_NUM_BUCKETS
mdefine_line|#define RP_NUM_BUCKETS  4
DECL|macro|RP_HIST_TYPES
mdefine_line|#define RP_HIST_TYPES&t;3
DECL|macro|RP_AGE0
mdefine_line|#define RP_AGE0&t;&t;0
DECL|macro|RP_AGE1
mdefine_line|#define RP_AGE1&t;&t;1
DECL|macro|RP_AGE2
mdefine_line|#define RP_AGE2&t;&t;2
DECL|macro|RP_AGE3
mdefine_line|#define RP_AGE3&t;&t;3
DECL|macro|RR_UTIL_SCALE
mdefine_line|#define RR_UTIL_SCALE&t;1024
multiline_comment|/*&n; * Router port-oriented information&n; */
DECL|struct|router_port_info_s
r_typedef
r_struct
id|router_port_info_s
(brace
DECL|member|rp_histograms
id|router_reg_t
id|rp_histograms
(braket
id|RP_HIST_REGS
)braket
suffix:semicolon
multiline_comment|/* Port usage info */
DECL|member|rp_port_error
id|router_reg_t
id|rp_port_error
suffix:semicolon
multiline_comment|/* Port error info */
DECL|member|rp_retry_errors
id|router_count_t
id|rp_retry_errors
suffix:semicolon
multiline_comment|/* Total retry errors */
DECL|member|rp_sn_errors
id|router_count_t
id|rp_sn_errors
suffix:semicolon
multiline_comment|/* Total sn errors */
DECL|member|rp_cb_errors
id|router_count_t
id|rp_cb_errors
suffix:semicolon
multiline_comment|/* Total cb errors */
DECL|member|rp_overflows
r_int
id|rp_overflows
suffix:semicolon
multiline_comment|/* Total count overflows */
DECL|member|rp_excess_err
r_int
id|rp_excess_err
suffix:semicolon
multiline_comment|/* Port has excessive errors */
DECL|member|rp_util
id|ushort
id|rp_util
(braket
id|RP_NUM_BUCKETS
)braket
suffix:semicolon
multiline_comment|/* Port utilization */
DECL|typedef|router_port_info_t
)brace
id|router_port_info_t
suffix:semicolon
DECL|macro|ROUTER_INFO_VERSION
mdefine_line|#define ROUTER_INFO_VERSION&t;7
r_struct
id|lboard_s
suffix:semicolon
multiline_comment|/*&n; * Router information&n; */
DECL|struct|router_info_s
r_typedef
r_struct
id|router_info_s
(brace
DECL|member|ri_version
r_char
id|ri_version
suffix:semicolon
multiline_comment|/* structure version&t;&t;    */
DECL|member|ri_cnode
id|cnodeid_t
id|ri_cnode
suffix:semicolon
multiline_comment|/* cnode of its legal guardian hub  */
DECL|member|ri_nasid
id|nasid_t
id|ri_nasid
suffix:semicolon
multiline_comment|/* Nasid of same &t;&t;    */
DECL|member|ri_ledcache
r_char
id|ri_ledcache
suffix:semicolon
multiline_comment|/* Last LED bitmap&t;&t;    */
DECL|member|ri_leds
r_char
id|ri_leds
suffix:semicolon
multiline_comment|/* Current LED bitmap&t;&t;    */
DECL|member|ri_portmask
r_char
id|ri_portmask
suffix:semicolon
multiline_comment|/* Active port bitmap&t;&t;    */
DECL|member|ri_stat_rev_id
id|router_reg_t
id|ri_stat_rev_id
suffix:semicolon
multiline_comment|/* Status rev ID value&t;&t;    */
DECL|member|ri_vector
id|net_vec_t
id|ri_vector
suffix:semicolon
multiline_comment|/* vector from guardian to router   */
DECL|member|ri_writeid
r_int
id|ri_writeid
suffix:semicolon
multiline_comment|/* router&squot;s vector write ID&t;    */
DECL|member|ri_timebase
r_int64
id|ri_timebase
suffix:semicolon
multiline_comment|/* Time of first sample&t;&t;    */
DECL|member|ri_timestamp
r_int64
id|ri_timestamp
suffix:semicolon
multiline_comment|/* Time of last sample&t;&t;    */
DECL|member|ri_port
id|router_port_info_t
id|ri_port
(braket
id|MAX_ROUTER_PORTS
)braket
suffix:semicolon
multiline_comment|/* per port info      */
DECL|member|ri_module
id|moduleid_t
id|ri_module
suffix:semicolon
multiline_comment|/* Which module are we in?&t;    */
DECL|member|ri_slotnum
id|slotid_t
id|ri_slotnum
suffix:semicolon
multiline_comment|/* Which slot are we in?&t;    */
DECL|member|ri_glbl_parms
id|router_reg_t
id|ri_glbl_parms
(braket
id|GLBL_PARMS_REGS
)braket
suffix:semicolon
multiline_comment|/* Global parms0&amp;1 register contents*/
DECL|member|ri_vertex
id|devfs_handle_t
id|ri_vertex
suffix:semicolon
multiline_comment|/* hardware graph vertex            */
DECL|member|ri_prot_conf
id|router_reg_t
id|ri_prot_conf
suffix:semicolon
multiline_comment|/* protection config. register&t;    */
DECL|member|ri_per_minute
r_int64
id|ri_per_minute
suffix:semicolon
multiline_comment|/* Ticks per minute&t;&t;    */
multiline_comment|/*&n;&t; * Everything below here is for kernel use only and may change at&t;&n;&t; * at any time with or without a change in teh revision number&n;&t; *&n;&t; * Any pointers or things that come and go with DEBUG must go at&n; &t; * the bottom of the structure, below the user stuff.&n;&t; */
DECL|member|ri_hist_type
r_char
id|ri_hist_type
suffix:semicolon
multiline_comment|/* histogram type&t;&t;    */
DECL|member|ri_guardian
id|devfs_handle_t
id|ri_guardian
suffix:semicolon
multiline_comment|/* guardian node for the router&t;    */
DECL|member|ri_last_print
r_int64
id|ri_last_print
suffix:semicolon
multiline_comment|/* When did we last print&t;    */
DECL|member|ri_print
r_char
id|ri_print
suffix:semicolon
multiline_comment|/* Should we print &t;&t;    */
DECL|member|ri_just_blink
r_char
id|ri_just_blink
suffix:semicolon
multiline_comment|/* Should we blink the LEDs         */
macro_line|#ifdef DEBUG
DECL|member|ri_deltatime
r_int64
id|ri_deltatime
suffix:semicolon
multiline_comment|/* Time it took to sample&t;    */
macro_line|#endif
DECL|member|ri_lock
id|lock_t
id|ri_lock
suffix:semicolon
multiline_comment|/* Lock for access to router info   */
DECL|member|ri_vecarray
id|net_vec_t
op_star
id|ri_vecarray
suffix:semicolon
multiline_comment|/* Pointer to array of vectors&t;    */
DECL|member|ri_brd
r_struct
id|lboard_s
op_star
id|ri_brd
suffix:semicolon
multiline_comment|/* Pointer to board structure&t;    */
DECL|member|ri_name
r_char
op_star
id|ri_name
suffix:semicolon
multiline_comment|/* This board&squot;s hwg path &t;    */
DECL|member|ri_port_maint
r_int
r_char
id|ri_port_maint
(braket
id|MAX_ROUTER_PORTS
)braket
suffix:semicolon
multiline_comment|/* should we send a &n;&t;&t;&t;&t;&t;message to availmon */
DECL|typedef|router_info_t
)brace
id|router_info_t
suffix:semicolon
multiline_comment|/* Router info location specifiers */
DECL|macro|RIP_PROMLOG
mdefine_line|#define RIP_PROMLOG&t;&t;&t;2&t;/* Router info in promlog */
DECL|macro|RIP_CONSOLE
mdefine_line|#define RIP_CONSOLE&t;&t;&t;4&t;/* Router info on console */
DECL|macro|ROUTER_INFO_PRINT
mdefine_line|#define ROUTER_INFO_PRINT(_rip,_where)&t;(_rip-&gt;ri_print |= _where)&t;
multiline_comment|/* Set the field used to check if a &n;&t;&t;&t;&t;&t; * router info can be printed&n;&t;&t;&t;&t;&t; */
DECL|macro|IS_ROUTER_INFO_PRINTED
mdefine_line|#define IS_ROUTER_INFO_PRINTED(_rip,_where)&t;&bslash;&n;&t;&t;&t;&t;&t;(_rip-&gt;ri_print &amp; _where)&t;
multiline_comment|/* Was the router info printed to&n;&t;&t;&t;&t;&t; * the given location (_where) ?&n;&t;&t;&t;&t;&t; * Mainly used to prevent duplicate&n;&t;&t;&t;&t;&t; * router error states.&n;&t;&t;&t;&t;&t; */
DECL|macro|ROUTER_INFO_LOCK
mdefine_line|#define ROUTER_INFO_LOCK(_rip,_s)&t;_s = mutex_spinlock(&amp;(_rip-&gt;ri_lock))
multiline_comment|/* Take the lock on router info&n;&t;&t;&t;&t;&t; * to gain exclusive access&n;&t;&t;&t;&t;&t; */
DECL|macro|ROUTER_INFO_UNLOCK
mdefine_line|#define ROUTER_INFO_UNLOCK(_rip,_s)&t;mutex_spinunlock(&amp;(_rip-&gt;ri_lock),_s)
multiline_comment|/* Release the lock on router info */
multiline_comment|/* &n; * Router info hanging in the nodepda &n; */
DECL|struct|nodepda_router_info_s
r_typedef
r_struct
id|nodepda_router_info_s
(brace
DECL|member|router_vhdl
id|devfs_handle_t
id|router_vhdl
suffix:semicolon
multiline_comment|/* vertex handle of the router &t;    */
DECL|member|router_port
r_int
id|router_port
suffix:semicolon
multiline_comment|/* port thru which we entered       */
DECL|member|router_portmask
r_int
id|router_portmask
suffix:semicolon
DECL|member|router_module
id|moduleid_t
id|router_module
suffix:semicolon
multiline_comment|/* module in which router is there  */
DECL|member|router_slot
id|slotid_t
id|router_slot
suffix:semicolon
multiline_comment|/* router slot&t;&t;&t;    */
DECL|member|router_type
r_int
r_char
id|router_type
suffix:semicolon
multiline_comment|/* kind of router &t;&t;    */
DECL|member|router_vector
id|net_vec_t
id|router_vector
suffix:semicolon
multiline_comment|/* vector from the guardian node    */
DECL|member|router_infop
id|router_info_t
op_star
id|router_infop
suffix:semicolon
multiline_comment|/* info hanging off the hwg vertex  */
DECL|member|router_next
r_struct
id|nodepda_router_info_s
op_star
id|router_next
suffix:semicolon
multiline_comment|/* pointer to next element &t;    */
DECL|typedef|nodepda_router_info_t
)brace
id|nodepda_router_info_t
suffix:semicolon
DECL|macro|ROUTER_NAME_SIZE
mdefine_line|#define ROUTER_NAME_SIZE&t;20&t;/* Max size of a router name */
DECL|macro|NORMAL_ROUTER_NAME
mdefine_line|#define NORMAL_ROUTER_NAME&t;&quot;normal_router&quot;
DECL|macro|NULL_ROUTER_NAME
mdefine_line|#define NULL_ROUTER_NAME&t;&quot;null_router&quot;
DECL|macro|META_ROUTER_NAME
mdefine_line|#define META_ROUTER_NAME&t;&quot;meta_router&quot;
DECL|macro|UNKNOWN_ROUTER_NAME
mdefine_line|#define UNKNOWN_ROUTER_NAME&t;&quot;unknown_router&quot; 
multiline_comment|/* The following definitions are needed by the router traversing&n; * code either using the hardware graph or using vector operations.&n; */
multiline_comment|/* Structure of the router queue element */
DECL|struct|router_elt_s
r_typedef
r_struct
id|router_elt_s
(brace
r_union
(brace
multiline_comment|/* queue element structure during router probing */
r_struct
(brace
multiline_comment|/* number-in-a-can (unique) for the router */
DECL|member|nic
id|nic_t
id|nic
suffix:semicolon
multiline_comment|/* vector route from the master hub to &n;&t;&t;&t; * this router.&n;&t;&t;&t; */
DECL|member|vec
id|net_vec_t
id|vec
suffix:semicolon
multiline_comment|/* port status */
DECL|member|status
r_uint64
id|status
suffix:semicolon
DECL|member|port_status
r_char
id|port_status
(braket
id|MAX_ROUTER_PORTS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|r_elt
)brace
id|r_elt
suffix:semicolon
multiline_comment|/* queue element structure during router guardian &n;&t;&t; * assignment&n;&t;&t; */
r_struct
(brace
multiline_comment|/* vertex handle for the router */
DECL|member|vhdl
id|devfs_handle_t
id|vhdl
suffix:semicolon
multiline_comment|/* guardian for this router */
DECL|member|guard
id|devfs_handle_t
id|guard
suffix:semicolon
multiline_comment|/* vector router from the guardian to the router */
DECL|member|vec
id|net_vec_t
id|vec
suffix:semicolon
DECL|member|k_elt
)brace
id|k_elt
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* easy to use port status interpretation */
DECL|typedef|router_elt_t
)brace
id|router_elt_t
suffix:semicolon
multiline_comment|/* structure of the router queue */
DECL|struct|router_queue_s
r_typedef
r_struct
id|router_queue_s
(brace
DECL|member|head
r_char
id|head
suffix:semicolon
multiline_comment|/* Point where a queue element is inserted */
DECL|member|tail
r_char
id|tail
suffix:semicolon
multiline_comment|/* Point where a queue element is removed */
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|array
id|router_elt_t
id|array
(braket
id|MAX_RTR_BREADTH
)braket
suffix:semicolon
multiline_comment|/* Entries for queue elements */
DECL|typedef|router_queue_t
)brace
id|router_queue_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
multiline_comment|/*&n; * RR_HISTOGRAM(_L) mask and shift definitions&n; * There are two 64 bit histogram registers, so the following macros take&n; * into account dealing with an array of 4 32 bit values indexed by _x&n; */
DECL|macro|RHIST_BUCKET_SHFT
mdefine_line|#define RHIST_BUCKET_SHFT(_x)&t;(32 * ((_x) &amp; 0x1))
DECL|macro|RHIST_BUCKET_MASK
mdefine_line|#define RHIST_BUCKET_MASK(_x)&t;(UINT64_CAST 0xffffffff &lt;&lt; RHIST_BUCKET_SHFT((_x) &amp; 0x1))
DECL|macro|RHIST_GET_BUCKET
mdefine_line|#define RHIST_GET_BUCKET(_x, _reg)&t;&bslash;&n;&t;((RHIST_BUCKET_MASK(_x) &amp; ((_reg)[(_x) &gt;&gt; 1])) &gt;&gt; RHIST_BUCKET_SHFT(_x))
multiline_comment|/*&n; * RR_RESET_MASK(_L) mask and shift definitions&n; */
DECL|macro|RRM_RESETOK
mdefine_line|#define RRM_RESETOK(_L)&t;&t;(UINT64_CAST 1 &lt;&lt; ((_L) - 1))
DECL|macro|RRM_RESETOK_ALL
mdefine_line|#define RRM_RESETOK_ALL&t;&t;(UINT64_CAST 0x3f)
multiline_comment|/*&n; * RR_META_TABLE(_x) and RR_LOCAL_TABLE(_x) mask and shift definitions&n; */
DECL|macro|RTABLE_SHFT
mdefine_line|#define RTABLE_SHFT(_L)&t;&t;(4 * ((_L) - 1))
DECL|macro|RTABLE_MASK
mdefine_line|#define RTABLE_MASK(_L)&t;&t;(UINT64_CAST 0x7 &lt;&lt; RTABLE_SHFT(_L))
DECL|macro|ROUTERINFO_STKSZ
mdefine_line|#define&t;ROUTERINFO_STKSZ&t;4096
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
macro_line|#if defined(_LANGUAGE_C_PLUS_PLUS)
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_int
id|router_reg_read
c_func
(paren
id|router_info_t
op_star
id|rip
comma
r_int
id|regno
comma
id|router_reg_t
op_star
id|val
)paren
suffix:semicolon
r_int
id|router_reg_write
c_func
(paren
id|router_info_t
op_star
id|rip
comma
r_int
id|regno
comma
id|router_reg_t
id|val
)paren
suffix:semicolon
r_int
id|router_get_info
c_func
(paren
id|devfs_handle_t
id|routerv
comma
id|router_info_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|router_init
c_func
(paren
id|cnodeid_t
id|cnode
comma
r_int
id|writeid
comma
id|nodepda_router_info_t
op_star
id|npda_rip
)paren
suffix:semicolon
r_int
id|router_set_leds
c_func
(paren
id|router_info_t
op_star
id|rip
)paren
suffix:semicolon
r_void
id|router_print_state
c_func
(paren
id|router_info_t
op_star
id|rip
comma
r_int
id|level
comma
r_void
(paren
op_star
id|pf
)paren
(paren
r_int
comma
r_char
op_star
comma
dot
dot
dot
)paren
comma
r_int
id|print_where
)paren
suffix:semicolon
r_void
id|capture_router_stats
c_func
(paren
id|router_info_t
op_star
id|rip
)paren
suffix:semicolon
r_int
id|probe_routers
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|get_routername
c_func
(paren
r_int
r_char
id|brd_type
comma
r_char
op_star
id|rtrname
)paren
suffix:semicolon
r_void
id|router_guardians_set
c_func
(paren
id|devfs_handle_t
id|hwgraph_root
)paren
suffix:semicolon
r_int
id|router_hist_reselect
c_func
(paren
id|router_info_t
op_star
comma
r_int64
)paren
suffix:semicolon
macro_line|#if defined(_LANGUAGE_C_PLUS_PLUS)
)brace
macro_line|#endif
macro_line|#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
macro_line|#endif /* _ASM_SN_SN1_ROUTER_H */
eof
