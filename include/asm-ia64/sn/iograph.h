multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_IOGRAPH_H
DECL|macro|_ASM_SN_IOGRAPH_H
mdefine_line|#define _ASM_SN_IOGRAPH_H
multiline_comment|/*&n; * During initialization, platform-dependent kernel code establishes some&n; * basic elements of the hardware graph.  This file contains edge and&n; * info labels that are used across various platforms -- it serves as an&n; * ad-hoc registry.&n; */
multiline_comment|/* edges names */
DECL|macro|EDGE_LBL_BUS
mdefine_line|#define EDGE_LBL_BUS&t;&t;&t;&quot;bus&quot;
DECL|macro|EDGE_LBL_CONN
mdefine_line|#define EDGE_LBL_CONN&t;&t;&t;&quot;.connection&quot;
DECL|macro|EDGE_LBL_ECP
mdefine_line|#define EDGE_LBL_ECP&t;&t;&t;&quot;ecp&quot;&t;&t;/* EPP/ECP plp */
DECL|macro|EDGE_LBL_ECPP
mdefine_line|#define EDGE_LBL_ECPP&t;&t;&t;&quot;ecpp&quot;
DECL|macro|EDGE_LBL_GUEST
mdefine_line|#define EDGE_LBL_GUEST&t;&t;&t;&quot;.guest&quot;&t;/* For IOC3 */
DECL|macro|EDGE_LBL_HOST
mdefine_line|#define EDGE_LBL_HOST&t;&t;&t;&quot;.host&quot;&t;&t;/* For IOC3 */
DECL|macro|EDGE_LBL_PERFMON
mdefine_line|#define EDGE_LBL_PERFMON&t;&t;&quot;mon&quot;
DECL|macro|EDGE_LBL_USRPCI
mdefine_line|#define EDGE_LBL_USRPCI&t;&t;&t;&quot;usrpci&quot;
DECL|macro|EDGE_LBL_VME
mdefine_line|#define EDGE_LBL_VME&t;&t;&t;&quot;vmebus&quot;
DECL|macro|EDGE_LBL_BLOCK
mdefine_line|#define EDGE_LBL_BLOCK&t;&t;&t;&quot;block&quot;
DECL|macro|EDGE_LBL_BOARD
mdefine_line|#define EDGE_LBL_BOARD&t;&t;&t;&quot;board&quot;
DECL|macro|EDGE_LBL_CHAR
mdefine_line|#define EDGE_LBL_CHAR&t;&t;&t;&quot;char&quot;
DECL|macro|EDGE_LBL_CONTROLLER
mdefine_line|#define EDGE_LBL_CONTROLLER&t;&t;&quot;controller&quot;
DECL|macro|EDGE_LBL_CPU
mdefine_line|#define EDGE_LBL_CPU&t;&t;&t;&quot;cpu&quot;
DECL|macro|EDGE_LBL_CPUNUM
mdefine_line|#define EDGE_LBL_CPUNUM&t;&t;&t;&quot;cpunum&quot;
DECL|macro|EDGE_LBL_DISABLED
mdefine_line|#define EDGE_LBL_DISABLED&t;&t;&quot;disabled&quot;
DECL|macro|EDGE_LBL_DISK
mdefine_line|#define EDGE_LBL_DISK&t;&t;&t;&quot;disk&quot;
DECL|macro|EDGE_LBL_DMA_ENGINE
mdefine_line|#define EDGE_LBL_DMA_ENGINE             &quot;dma_engine&quot;    /* Only available on&n;&t;&t;&t;&t;&t;&t;&t;   VMEbus now        */
DECL|macro|EDGE_LBL_NET
mdefine_line|#define EDGE_LBL_NET&t;&t;&t;&quot;net&quot;&t;&t;/* all nw. devs */
DECL|macro|EDGE_LBL_EF
mdefine_line|#define EDGE_LBL_EF&t;&t;&t;&quot;ef&quot;&t;&t;/* For if_ef ethernet */
DECL|macro|EDGE_LBL_ET
mdefine_line|#define EDGE_LBL_ET&t;&t;&t;&quot;et&quot;&t;&t;/* For if_ee ethernet */
DECL|macro|EDGE_LBL_EC
mdefine_line|#define EDGE_LBL_EC&t;&t;&t;&quot;ec&quot;&t;&t;/* For if_ec2 ether */
DECL|macro|EDGE_LBL_ECF
mdefine_line|#define EDGE_LBL_ECF&t;&t;&t;&quot;ec&quot;&t;&t;/* For if_ecf enet */
DECL|macro|EDGE_LBL_EM
mdefine_line|#define EDGE_LBL_EM&t;&t;&t;&quot;ec&quot;&t;&t;/* For O2 ether */
DECL|macro|EDGE_LBL_IPG
mdefine_line|#define EDGE_LBL_IPG&t;&t;&t;&quot;ipg&quot;&t;&t;/* For IPG FDDI */
DECL|macro|EDGE_LBL_XPI
mdefine_line|#define EDGE_LBL_XPI&t;&t;&t;&quot;xpi&quot;&t;&t;/* For IPG FDDI */
DECL|macro|EDGE_LBL_HIP
mdefine_line|#define EDGE_LBL_HIP&t;&t;&t;&quot;hip&quot;&t;&t;/* For HIPPI */
DECL|macro|EDGE_LBL_GSN
mdefine_line|#define EDGE_LBL_GSN                    &quot;gsn&quot;           /* For GSN */
DECL|macro|EDGE_LBL_ATM
mdefine_line|#define EDGE_LBL_ATM&t;&t;&t;&quot;atm&quot;&t;&t;/* For ATM */
DECL|macro|EDGE_LBL_FXP
mdefine_line|#define EDGE_LBL_FXP&t;&t;&t;&quot;fxp&quot;&t;&t;/* For FXP ether */
DECL|macro|EDGE_LBL_EP
mdefine_line|#define EDGE_LBL_EP&t;&t;&t;&quot;ep&quot;&t;&t;/* For eplex ether */
DECL|macro|EDGE_LBL_VFE
mdefine_line|#define EDGE_LBL_VFE&t;&t;&t;&quot;vfe&quot;&t;&t;/* For VFE ether */
DECL|macro|EDGE_LBL_GFE
mdefine_line|#define EDGE_LBL_GFE&t;&t;&t;&quot;gfe&quot;&t;&t;/* For GFE ether */
DECL|macro|EDGE_LBL_RNS
mdefine_line|#define EDGE_LBL_RNS&t;&t;&t;&quot;rns&quot;&t;&t;/* RNS PCI FDDI card */
DECL|macro|EDGE_LBL_MTR
mdefine_line|#define EDGE_LBL_MTR&t;&t;&t;&quot;mtr&quot;&t;&t;/* MTR PCI 802.5 card */
DECL|macro|EDGE_LBL_FV
mdefine_line|#define EDGE_LBL_FV&t;&t;&t;&quot;fv&quot;&t;&t;/* FV VME 802.5 card */
DECL|macro|EDGE_LBL_GTR
mdefine_line|#define EDGE_LBL_GTR&t;&t;&t;&quot;gtr&quot;&t;&t;/* GTR GIO 802.5 card */
DECL|macro|EDGE_LBL_ISDN
mdefine_line|#define EDGE_LBL_ISDN                   &quot;isdn&quot;&t;&t;/* Digi PCI ISDN-BRI card */
DECL|macro|EDGE_LBL_EISA
mdefine_line|#define EDGE_LBL_EISA&t;&t;&t;&quot;eisa&quot;
DECL|macro|EDGE_LBL_ENET
mdefine_line|#define EDGE_LBL_ENET&t;&t;&t;&quot;ethernet&quot;
DECL|macro|EDGE_LBL_FLOPPY
mdefine_line|#define EDGE_LBL_FLOPPY&t;&t;&t;&quot;floppy&quot;
DECL|macro|EDGE_LBL_PFD
mdefine_line|#define EDGE_LBL_PFD&t;&t;&t;&quot;pfd&quot;&t;&t;/* For O2 pfd floppy */
DECL|macro|EDGE_LBL_FOP
mdefine_line|#define EDGE_LBL_FOP                    &quot;fop&quot;           /* Fetchop pseudo device */
DECL|macro|EDGE_LBL_GIO
mdefine_line|#define EDGE_LBL_GIO&t;&t;&t;&quot;gio&quot;
DECL|macro|EDGE_LBL_HEART
mdefine_line|#define EDGE_LBL_HEART&t;&t;&t;&quot;heart&quot;&t;&t;/* For RACER */
DECL|macro|EDGE_LBL_HPC
mdefine_line|#define EDGE_LBL_HPC&t;&t;&t;&quot;hpc&quot;
DECL|macro|EDGE_LBL_GFX
mdefine_line|#define EDGE_LBL_GFX&t;&t;&t;&quot;gfx&quot;
DECL|macro|EDGE_LBL_HUB
mdefine_line|#define EDGE_LBL_HUB&t;&t;&t;&quot;hub&quot;&t;&t;/* For SN0 */
DECL|macro|EDGE_LBL_IBUS
mdefine_line|#define EDGE_LBL_IBUS&t;&t;&t;&quot;ibus&quot;&t;&t;/* For EVEREST */
DECL|macro|EDGE_LBL_INTERCONNECT
mdefine_line|#define EDGE_LBL_INTERCONNECT&t;&t;&quot;link&quot;
DECL|macro|EDGE_LBL_IO
mdefine_line|#define EDGE_LBL_IO&t;&t;&t;&quot;io&quot;
DECL|macro|EDGE_LBL_IO4
mdefine_line|#define EDGE_LBL_IO4&t;&t;&t;&quot;io4&quot;&t;&t;/* For EVEREST */
DECL|macro|EDGE_LBL_IOC3
mdefine_line|#define EDGE_LBL_IOC3&t;&t;&t;&quot;ioc3&quot;
DECL|macro|EDGE_LBL_LUN
mdefine_line|#define EDGE_LBL_LUN                    &quot;lun&quot;
DECL|macro|EDGE_LBL_MACE
mdefine_line|#define EDGE_LBL_MACE                   &quot;mace&quot; &t;&t;/* O2 mace */
DECL|macro|EDGE_LBL_MACHDEP
mdefine_line|#define EDGE_LBL_MACHDEP                &quot;machdep&quot;       /* Platform depedent devices */
DECL|macro|EDGE_LBL_MASTER
mdefine_line|#define EDGE_LBL_MASTER&t;&t;&t;&quot;.master&quot;
DECL|macro|EDGE_LBL_MEMORY
mdefine_line|#define EDGE_LBL_MEMORY&t;&t;&t;&quot;memory&quot;
DECL|macro|EDGE_LBL_META_ROUTER
mdefine_line|#define EDGE_LBL_META_ROUTER&t;&t;&quot;metarouter&quot;
DECL|macro|EDGE_LBL_MIDPLANE
mdefine_line|#define EDGE_LBL_MIDPLANE&t;&t;&quot;midplane&quot;
DECL|macro|EDGE_LBL_MODULE
mdefine_line|#define EDGE_LBL_MODULE&t;&t;&t;&quot;module&quot;
DECL|macro|EDGE_LBL_NODE
mdefine_line|#define EDGE_LBL_NODE&t;&t;&t;&quot;node&quot;
DECL|macro|EDGE_LBL_NODENUM
mdefine_line|#define EDGE_LBL_NODENUM&t;&t;&quot;nodenum&quot;
DECL|macro|EDGE_LBL_NVRAM
mdefine_line|#define EDGE_LBL_NVRAM&t;&t;&t;&quot;nvram&quot;
DECL|macro|EDGE_LBL_PARTITION
mdefine_line|#define EDGE_LBL_PARTITION&t;&t;&quot;partition&quot;
DECL|macro|EDGE_LBL_PCI
mdefine_line|#define EDGE_LBL_PCI&t;&t;&t;&quot;pci&quot;
DECL|macro|EDGE_LBL_PORT
mdefine_line|#define EDGE_LBL_PORT&t;&t;&t;&quot;port&quot;
DECL|macro|EDGE_LBL_PROM
mdefine_line|#define EDGE_LBL_PROM&t;&t;&t;&quot;prom&quot;
DECL|macro|EDGE_LBL_RACK
mdefine_line|#define EDGE_LBL_RACK&t;&t;&t;&quot;rack&quot;
DECL|macro|EDGE_LBL_RDISK
mdefine_line|#define EDGE_LBL_RDISK&t;&t;&t;&quot;rdisk&quot;
DECL|macro|EDGE_LBL_REPEATER_ROUTER
mdefine_line|#define EDGE_LBL_REPEATER_ROUTER&t;&quot;repeaterrouter&quot;
DECL|macro|EDGE_LBL_ROUTER
mdefine_line|#define EDGE_LBL_ROUTER&t;&t;&t;&quot;router&quot;
DECL|macro|EDGE_LBL_RPOS
mdefine_line|#define EDGE_LBL_RPOS&t;&t;&t;&quot;bay&quot;&t;&t;/* Position in rack */
DECL|macro|EDGE_LBL_SCSI
mdefine_line|#define EDGE_LBL_SCSI&t;&t;&t;&quot;scsi&quot;
DECL|macro|EDGE_LBL_SCSI_CTLR
mdefine_line|#define EDGE_LBL_SCSI_CTLR&t;&t;&quot;scsi_ctlr&quot;
DECL|macro|EDGE_LBL_SLOT
mdefine_line|#define EDGE_LBL_SLOT&t;&t;&t;&quot;slot&quot;
DECL|macro|EDGE_LBL_TAPE
mdefine_line|#define EDGE_LBL_TAPE&t;&t;&t;&quot;tape&quot;
DECL|macro|EDGE_LBL_TARGET
mdefine_line|#define EDGE_LBL_TARGET                 &quot;target&quot;
DECL|macro|EDGE_LBL_UNKNOWN
mdefine_line|#define EDGE_LBL_UNKNOWN&t;&t;&quot;unknown&quot;
DECL|macro|EDGE_LBL_VOLUME
mdefine_line|#define EDGE_LBL_VOLUME&t;&t;&t;&quot;volume&quot;
DECL|macro|EDGE_LBL_VOLUME_HEADER
mdefine_line|#define EDGE_LBL_VOLUME_HEADER&t;&t;&quot;volume_header&quot;
DECL|macro|EDGE_LBL_XBOW
mdefine_line|#define EDGE_LBL_XBOW&t;&t;&t;&quot;xbow&quot;
DECL|macro|EDGE_LBL_XIO
mdefine_line|#define&t;EDGE_LBL_XIO&t;&t;&t;&quot;xio&quot;
DECL|macro|EDGE_LBL_XSWITCH
mdefine_line|#define EDGE_LBL_XSWITCH&t;&t;&quot;.xswitch&quot;
DECL|macro|EDGE_LBL_XTALK
mdefine_line|#define EDGE_LBL_XTALK&t;&t;&t;&quot;xtalk&quot;
DECL|macro|EDGE_LBL_XWIDGET
mdefine_line|#define EDGE_LBL_XWIDGET&t;&t;&quot;xwidget&quot;
DECL|macro|EDGE_LBL_ELSC
mdefine_line|#define EDGE_LBL_ELSC&t;&t;&t;&quot;elsc&quot;
DECL|macro|EDGE_LBL_L1
mdefine_line|#define EDGE_LBL_L1&t;&t;&t;&quot;L1&quot;
DECL|macro|EDGE_LBL_MADGE_TR
mdefine_line|#define EDGE_LBL_MADGE_TR               &quot;Madge-tokenring&quot;
DECL|macro|EDGE_LBL_XPLINK
mdefine_line|#define EDGE_LBL_XPLINK&t;&t;&t;&quot;xplink&quot; &t;/* Cross partition */
DECL|macro|EDGE_LBL_XPLINK_NET
mdefine_line|#define&t;EDGE_LBL_XPLINK_NET&t;&t;&quot;net&quot; &t;&t;/* XP network devs */
DECL|macro|EDGE_LBL_XPLINK_RAW
mdefine_line|#define&t;EDGE_LBL_XPLINK_RAW&t;&t;&quot;raw&quot;&t;&t;/* XP Raw devs */
DECL|macro|EDGE_LBL_XPLINK_KERNEL
mdefine_line|#define&t;EDGE_LBL_XPLINK_KERNEL&t;&t;&quot;kernel&quot;&t;/* XP kernel devs */
DECL|macro|EDGE_LBL_XPLINK_ADMIN
mdefine_line|#define&t;EDGE_LBL_XPLINK_ADMIN&t;&t;&quot;admin&quot;&t;   &t;/* Partition admin */
DECL|macro|EDGE_LBL_KAIO
mdefine_line|#define&t;EDGE_LBL_KAIO&t;&t;&t;&quot;kaio&quot;&t;   &t;/* Kernel async i/o poll */
DECL|macro|EDGE_LBL_RPS
mdefine_line|#define EDGE_LBL_RPS                    &quot;rps&quot;           /* redundant power supply */ 
DECL|macro|EDGE_LBL_XBOX_RPS
mdefine_line|#define EDGE_LBL_XBOX_RPS               &quot;xbox_rps&quot;      /* redundant power supply for xbox unit */ 
DECL|macro|EDGE_LBL_IOBRICK
mdefine_line|#define EDGE_LBL_IOBRICK&t;&t;&quot;iobrick&quot;
DECL|macro|EDGE_LBL_PBRICK
mdefine_line|#define EDGE_LBL_PBRICK&t;&t;&t;&quot;Pbrick&quot;
DECL|macro|EDGE_LBL_IBRICK
mdefine_line|#define EDGE_LBL_IBRICK&t;&t;&t;&quot;Ibrick&quot;
DECL|macro|EDGE_LBL_XBRICK
mdefine_line|#define EDGE_LBL_XBRICK&t;&t;&t;&quot;Xbrick&quot;
DECL|macro|EDGE_LBL_CPUBUS
mdefine_line|#define EDGE_LBL_CPUBUS&t;&t;&t;&quot;cpubus&quot;&t;/* CPU Interfaces (SysAd) */
multiline_comment|/* vertex info labels in hwgraph */
DECL|macro|INFO_LBL_CNODEID
mdefine_line|#define INFO_LBL_CNODEID&t;&t;&quot;_cnodeid&quot;
DECL|macro|INFO_LBL_CONTROLLER_NAME
mdefine_line|#define INFO_LBL_CONTROLLER_NAME&t;&quot;_controller_name&quot;
DECL|macro|INFO_LBL_CPUBUS
mdefine_line|#define INFO_LBL_CPUBUS&t;&t;&t;&quot;_cpubus&quot;
DECL|macro|INFO_LBL_CPUID
mdefine_line|#define INFO_LBL_CPUID&t;&t;&t;&quot;_cpuid&quot;
DECL|macro|INFO_LBL_CPU_INFO
mdefine_line|#define INFO_LBL_CPU_INFO&t;&t;&quot;_cpu&quot;
DECL|macro|INFO_LBL_DETAIL_INVENT
mdefine_line|#define INFO_LBL_DETAIL_INVENT&t;&t;&quot;_detail_invent&quot; /* inventory data*/
DECL|macro|INFO_LBL_DEVICE_DESC
mdefine_line|#define INFO_LBL_DEVICE_DESC&t;&t;&quot;_device_desc&quot;
DECL|macro|INFO_LBL_DIAGVAL
mdefine_line|#define INFO_LBL_DIAGVAL                &quot;_diag_reason&quot;   /* Reason disabled */
DECL|macro|INFO_LBL_DKIOTIME
mdefine_line|#define INFO_LBL_DKIOTIME&t;&t;&quot;_dkiotime&quot;
DECL|macro|INFO_LBL_DRIVER
mdefine_line|#define INFO_LBL_DRIVER&t;&t;&t;&quot;_driver&quot;&t;/* points to attached device_driver_t */
DECL|macro|INFO_LBL_ELSC
mdefine_line|#define INFO_LBL_ELSC&t;&t;&t;&quot;_elsc&quot;
DECL|macro|INFO_LBL_SUBCH
mdefine_line|#define&t;INFO_LBL_SUBCH&t;&t;&t;&quot;_subch&quot;&t;/* system controller subchannel */
DECL|macro|INFO_LBL_L1SCP
mdefine_line|#define INFO_LBL_L1SCP&t;&t;&t;&quot;_l1scp&quot;&t;/* points to l1sc_t */
DECL|macro|INFO_LBL_FC_PORTNAME
mdefine_line|#define INFO_LBL_FC_PORTNAME&t;&t;&quot;_fc_portname&quot;
DECL|macro|INFO_LBL_GIOIO
mdefine_line|#define INFO_LBL_GIOIO&t;&t;&t;&quot;_gioio&quot;
DECL|macro|INFO_LBL_GFUNCS
mdefine_line|#define INFO_LBL_GFUNCS&t;&t;&t;&quot;_gioio_ops&quot;&t;/* ops vector for gio providers */
DECL|macro|INFO_LBL_HUB_INFO
mdefine_line|#define INFO_LBL_HUB_INFO&t;&t;&quot;_hubinfo&quot;
DECL|macro|INFO_LBL_HWGFSLIST
mdefine_line|#define INFO_LBL_HWGFSLIST&t;&t;&quot;_hwgfs_list&quot;
DECL|macro|INFO_LBL_TRAVERSE
mdefine_line|#define INFO_LBL_TRAVERSE&t;&t;&quot;_hwg_traverse&quot; /* hwgraph traverse function */
DECL|macro|INFO_LBL_INVENT
mdefine_line|#define INFO_LBL_INVENT &t;&t;&quot;_invent&quot;&t;/* inventory data */
DECL|macro|INFO_LBL_MLRESET
mdefine_line|#define INFO_LBL_MLRESET&t;&t;&quot;_mlreset&quot;&t;/* present if device preinitialized */
DECL|macro|INFO_LBL_MODULE_INFO
mdefine_line|#define INFO_LBL_MODULE_INFO&t;&t;&quot;_module&quot;&t;/* module data ptr */
DECL|macro|INFO_LBL_MONDATA
mdefine_line|#define INFO_LBL_MONDATA&t;&t;&quot;_mon&quot;&t;&t;/* monitor data ptr */
DECL|macro|INFO_LBL_MDPERF_DATA
mdefine_line|#define INFO_LBL_MDPERF_DATA&t;&t;&quot;_mdperf&quot;&t;/* mdperf monitoring*/
DECL|macro|INFO_LBL_NIC
mdefine_line|#define INFO_LBL_NIC&t;&t;&t;&quot;_nic&quot;
DECL|macro|INFO_LBL_NODE_INFO
mdefine_line|#define INFO_LBL_NODE_INFO&t;&t;&quot;_node&quot;
DECL|macro|INFO_LBL_PCIBR_HINTS
mdefine_line|#define&t;INFO_LBL_PCIBR_HINTS&t;&t;&quot;_pcibr_hints&quot;
DECL|macro|INFO_LBL_PCIIO
mdefine_line|#define INFO_LBL_PCIIO&t;&t;&t;&quot;_pciio&quot;
DECL|macro|INFO_LBL_PFUNCS
mdefine_line|#define INFO_LBL_PFUNCS&t;&t;&t;&quot;_pciio_ops&quot;&t;/* ops vector for gio providers */
DECL|macro|INFO_LBL_PERMISSIONS
mdefine_line|#define INFO_LBL_PERMISSIONS&t;&t;&quot;_permissions&quot;&t;/* owner, uid, gid */
DECL|macro|INFO_LBL_ROUTER_INFO
mdefine_line|#define INFO_LBL_ROUTER_INFO&t;&t;&quot;_router&quot;
DECL|macro|INFO_LBL_SUBDEVS
mdefine_line|#define INFO_LBL_SUBDEVS&t;&t;&quot;_subdevs&quot;&t;/* subdevice enable bits */
DECL|macro|INFO_LBL_VME_FUNCS
mdefine_line|#define INFO_LBL_VME_FUNCS&t;&t;&quot;_vmeio_ops&quot;&t;/* ops vector for VME providers */
DECL|macro|INFO_LBL_XSWITCH
mdefine_line|#define INFO_LBL_XSWITCH&t;&t;&quot;_xswitch&quot;
DECL|macro|INFO_LBL_XSWITCH_ID
mdefine_line|#define INFO_LBL_XSWITCH_ID&t;&t;&quot;_xswitch_id&quot;
DECL|macro|INFO_LBL_XSWITCH_VOL
mdefine_line|#define INFO_LBL_XSWITCH_VOL&t;&t;&quot;_xswitch_volunteer&quot;
DECL|macro|INFO_LBL_XFUNCS
mdefine_line|#define INFO_LBL_XFUNCS&t;&t;&t;&quot;_xtalk_ops&quot;&t;/* ops vector for gio providers */
DECL|macro|INFO_LBL_XWIDGET
mdefine_line|#define INFO_LBL_XWIDGET&t;&t;&quot;_xwidget&quot;
DECL|macro|INFO_LBL_GRIO_DSK
mdefine_line|#define INFO_LBL_GRIO_DSK&t;&t;&quot;_grio_disk&quot;&t;/* guaranteed rate I/O */
DECL|macro|INFO_LBL_ASYNC_ATTACH
mdefine_line|#define INFO_LBL_ASYNC_ATTACH           &quot;_async_attach&quot;&t;/* parallel attachment */
DECL|macro|INFO_LBL_GFXID
mdefine_line|#define INFO_LBL_GFXID&t;&t;&t;&quot;_gfxid&quot;&t;/* gfx pipe ID #s */
multiline_comment|/* Device/Driver  Admin directive labels  */
DECL|macro|ADMIN_LBL_INTR_TARGET
mdefine_line|#define ADMIN_LBL_INTR_TARGET&t;&t;&quot;INTR_TARGET&quot;&t;/* Target cpu for device interrupts*/
DECL|macro|ADMIN_LBL_INTR_SWLEVEL
mdefine_line|#define ADMIN_LBL_INTR_SWLEVEL&t;&t;&quot;INTR_SWLEVEL&quot;&t;/* Priority level of the ithread */
DECL|macro|ADMIN_LBL_DMATRANS_NODE
mdefine_line|#define&t;ADMIN_LBL_DMATRANS_NODE&t;&t;&quot;PCIBUS_DMATRANS_NODE&quot; /* Node used for&n;&t;&t;&t;&t;&t;&t;&t;&t;* 32-bit Direct&n;&t;&t;&t;&t;&t;&t;&t;&t;* Mapping I/O&n;&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|ADMIN_LBL_DISABLED
mdefine_line|#define ADMIN_LBL_DISABLED&t;&t;&quot;DISABLE&quot;&t;/* Device has been disabled */
DECL|macro|ADMIN_LBL_DETACH
mdefine_line|#define ADMIN_LBL_DETACH&t;&t;&quot;DETACH&quot;&t;/* Device has been detached */
DECL|macro|ADMIN_LBL_THREAD_PRI
mdefine_line|#define ADMIN_LBL_THREAD_PRI&t;&t;&quot;thread_priority&quot; 
multiline_comment|/* Driver adminstrator&n;&t;&t;&t;&t;&t;&t;&t; * hint parameter for &n;&t;&t;&t;&t;&t;&t;&t; * thread priority&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|macro|ADMIN_LBL_THREAD_CLASS
mdefine_line|#define ADMIN_LBL_THREAD_CLASS&t;&t;&quot;thread_class&quot; 
multiline_comment|/* Driver adminstrator&n;&t;&t;&t;&t;&t;&t;&t; * hint parameter for &n;&t;&t;&t;&t;&t;&t;&t; * thread priority&n;&t;&t;&t;&t;&t;&t;&t; * default class&n;&t;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Special reserved info labels (also hwgfs attributes) */
DECL|macro|_DEVNAME_ATTR
mdefine_line|#define _DEVNAME_ATTR&t;&t;&quot;_devname&quot;&t;/* device name */
DECL|macro|_DRIVERNAME_ATTR
mdefine_line|#define _DRIVERNAME_ATTR&t;&quot;_drivername&quot;&t;/* driver name */
DECL|macro|_INVENT_ATTR
mdefine_line|#define _INVENT_ATTR&t;&t;&quot;_inventory&quot;&t;/* device inventory data */
DECL|macro|_MASTERNODE_ATTR
mdefine_line|#define _MASTERNODE_ATTR&t;&quot;_masternode&quot;&t;/* node that &quot;controls&quot; device */
multiline_comment|/* Info labels that begin with &squot;_&squot; cannot be overwritten by an attr_set call */
DECL|macro|INFO_LBL_RESERVED
mdefine_line|#define INFO_LBL_RESERVED(name) ((name)[0] == &squot;_&squot;)
macro_line|#if defined(__KERNEL__)
r_void
id|init_all_devices
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;&t;/* For get MAX_PORT_NUM */
r_int
id|io_brick_map_widget
c_func
(paren
r_char
comma
r_int
)paren
suffix:semicolon
r_int
id|io_path_map_widget
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
multiline_comment|/*&n; * Map a brick&squot;s widget number to a meaningful int&n; */
DECL|struct|io_brick_map_s
r_struct
id|io_brick_map_s
(brace
DECL|member|ibm_type
r_char
id|ibm_type
suffix:semicolon
multiline_comment|/* brick type, e.g. */
multiline_comment|/* &squot;I&squot; for Ibrick   */
DECL|member|ibm_map_wid
r_int
id|ibm_map_wid
(braket
id|MAX_PORT_NUM
)braket
suffix:semicolon
multiline_comment|/* wid to int map */
)brace
suffix:semicolon
macro_line|#endif /* _ASM_SN_IOGRAPH_H */
eof
