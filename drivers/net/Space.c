multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Holds initial configuration information for devices.&n; *&n; * Version:&t;@(#)Space.c&t;1.0.7&t;08/12/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@scyld.com&gt;&n; *&n; * Changelog:&n; *&t;&t;Paul Gortmaker (03/2002)&n;&t;&t;- struct init cleanup, enable multiple ISA autoprobes.&n; *&t;&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; - 09/1999&n; *&t;&t;- fix sbni: s/device/net_device/&n; *&t;&t;Paul Gortmaker (06/98): &n; *&t;&t; - sort probes in a sane way, make sure all (safe) probes&n; *&t;&t;   get run once &amp; failed autoprobes don&squot;t autoprobe again.&n; *&n; *&t;FIXME:&n; *&t;&t;Phase out placeholder dev entries put in the linked list&n; *&t;&t;here in favour of drivers using init_etherdev(NULL, ...)&n; *&t;&t;combined with a single find_all_devs() function (for 2.3)&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/divert.h&gt;
DECL|macro|NEXT_DEV
mdefine_line|#define&t;NEXT_DEV&t;NULL
multiline_comment|/* A unified ethernet device probe.  This is the easiest way to have every&n;   ethernet adaptor have the name &quot;eth[0123...]&quot;.&n;   */
r_extern
r_int
id|ne2_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|hp100_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ultra_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ultra32_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|wd_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|el2_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ne_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|hp_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|hp_plus_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|express_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eepro_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|at1500_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|at1700_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|fmv18x_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eth16i_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|depca_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i82596_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ewrk3_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|de4x5_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|el1_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|wavelan_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|arlan_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|el16_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elmc_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|skmca_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elplus_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ac3200_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|es_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|lne390_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ne3210_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|e2100_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ni5010_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ni52_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ni65_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sonic_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|SK_init
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|seeq8005_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|smc_init
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sgiseeq_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atarilance_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sun3lance_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sun3_82586_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|apne_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|bionet_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pamsnet_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cs89x0_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ethertap_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|hplance_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|bagetlance_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mvme147lance_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|tc515_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|lance_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|mace_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|macsonic_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|mac8390_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|mac89x0_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|mc32_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Detachable devices (&quot;pocket adaptors&quot;) */
r_extern
r_int
id|de620_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
multiline_comment|/* FDDI adapters */
r_extern
r_int
id|skfp_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Fibre Channel adapters */
r_extern
r_int
id|iph5526_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* SBNI adapters */
r_extern
r_int
id|sbni_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|struct|devprobe
r_struct
id|devprobe
(brace
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* non-zero if autoprobe has failed */
)brace
suffix:semicolon
multiline_comment|/*&n; * probe_list walks a list of probe functions and calls each so long&n; * as a non-zero ioaddr is given, or as long as it hasn&squot;t already failed &n; * to find a card in the past (as recorded by &quot;status&quot;) when asked to&n; * autoprobe (i.e. a probe that fails to find a card when autoprobing&n; * will not be asked to autoprobe again).  It exits when a card is found.&n; */
DECL|function|probe_list
r_static
r_int
id|__init
id|probe_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|devprobe
op_star
id|plist
)paren
(brace
r_struct
id|devprobe
op_star
id|p
op_assign
id|plist
suffix:semicolon
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
macro_line|#ifdef CONFIG_NET_DIVERT
r_int
id|ret
suffix:semicolon
macro_line|#endif /* CONFIG_NET_DIVERT */
r_while
c_loop
(paren
id|p-&gt;probe
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|base_addr
op_logical_and
id|p
op_member_access_from_pointer
id|probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* probe given addr */
macro_line|#ifdef CONFIG_NET_DIVERT
id|ret
op_assign
id|alloc_divert_blk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
macro_line|#endif /* CONFIG_NET_DIVERT */
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;status
op_eq
l_int|0
)paren
(brace
multiline_comment|/* has autoprobe failed yet? */
id|p-&gt;status
op_assign
id|p
op_member_access_from_pointer
id|probe
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* no, try autoprobe */
r_if
c_cond
(paren
id|p-&gt;status
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_NET_DIVERT
id|ret
op_assign
id|alloc_divert_blk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
macro_line|#endif /* CONFIG_NET_DIVERT */
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|p
op_increment
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a bit of an artificial separation as there are PCI drivers&n; * that also probe for EISA cards (in the PCI group) and there are ISA&n; * drivers that probe for EISA cards (in the ISA group).  These are the&n; * EISA only driver probes, and also the legacy PCI probes&n; */
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|eisa_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_DE4X5             /* DEC DE425, DE434, DE435 adapters */
(brace
id|de4x5_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ULTRA32 
(brace
id|ultra32_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AC3200&t;
(brace
id|ac3200_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ES3210
(brace
id|es_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_LNE390
(brace
id|lne390_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NE3210
(brace
id|ne3210_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|mca_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_NE2_MCA
(brace
id|ne2_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ELMC&t;&t;/* 3c523 */
(brace
id|elmc_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ELMC_II&t;&t;/* 3c527 */
(brace
id|mc32_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SKMC              /* SKnet Microchannel */
(brace
id|skmca_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * ISA probes that touch addresses &lt; 0x400 (including those that also&n; * look for EISA/PCI/MCA cards in addition to ISA cards).&n; */
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|isa_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_HP100 &t;&t;/* ISA, EISA &amp; PCI */
(brace
id|hp100_probe
comma
l_int|0
)brace
comma
macro_line|#endif&t;
macro_line|#ifdef CONFIG_3C515
(brace
id|tc515_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ULTRA 
(brace
id|ultra_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_WD80x3 
(brace
id|wd_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EL2 &t;&t;/* 3c503 */
(brace
id|el2_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EL3
(brace
id|el3_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_HPLAN
(brace
id|hp_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_HPLAN_PLUS
(brace
id|hp_plus_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_E2100&t;&t;/* Cabletron E21xx series. */
(brace
id|e2100_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NE2000&t;&t;/* ISA (use ne2k-pci for PCI cards) */
(brace
id|ne_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_LANCE&t;&t;/* ISA/VLB (use pcnet32 for PCI cards) */
(brace
id|lance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SMC9194
(brace
id|smc_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SEEQ8005 
(brace
id|seeq8005_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AT1500
(brace
id|at1500_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_CS89x0
(brace
id|cs89x0_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AT1700
(brace
id|at1700_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FMV18X&t;&t;/* Fujitsu FMV-181/182 */
(brace
id|fmv18x_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ETH16I
(brace
id|eth16i_probe
comma
l_int|0
)brace
comma
multiline_comment|/* ICL EtherTeam 16i/32 */
macro_line|#endif
macro_line|#ifdef CONFIG_EEXPRESS&t;&t;/* Intel EtherExpress */
(brace
id|express_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EEXPRESS_PRO&t;/* Intel EtherExpress Pro/10 */
(brace
id|eepro_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_DEPCA&t;&t;/* DEC DEPCA */
(brace
id|depca_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EWRK3             /* DEC EtherWORKS 3 */
(brace
id|ewrk3_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_APRICOT) || defined(CONFIG_MVME16x_NET) || defined(CONFIG_BVME6000_NET)&t;/* Intel I82596 */
(brace
id|i82596_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EL1&t;&t;/* 3c501 */
(brace
id|el1_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_WAVELAN&t;&t;/* WaveLAN */
(brace
id|wavelan_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ARLAN&t;&t;/* Aironet */
(brace
id|arlan_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EL16&t;&t;/* 3c507 */
(brace
id|el16_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ELPLUS&t;&t;/* 3c505 */
(brace
id|elplus_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SK_G16
(brace
id|SK_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NI5010
(brace
id|ni5010_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NI52
(brace
id|ni52_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NI65
(brace
id|ni65_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|parport_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_DE620&t;&t;/* D-Link DE-620 adapter */
(brace
id|de620_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|m68k_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_ATARILANCE&t;/* Lance-based Atari ethernet boards */
(brace
id|atarilance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3LANCE         /* sun3 onboard Lance chip */
(brace
id|sun3lance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3_82586        /* sun3 onboard Intel 82586 chip */
(brace
id|sun3_82586_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_APNE&t;&t;/* A1200 PCMCIA NE2000 */
(brace
id|apne_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI_BIONET&t;/* Atari Bionet Ethernet board */
(brace
id|bionet_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI_PAMSNET&t;/* Atari PAMsNet Ethernet board */
(brace
id|pamsnet_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_HPLANCE&t;&t;/* HP300 internal Ethernet */
(brace
id|hplance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MVME147_NET&t;/* MVME147 internal Ethernet */
(brace
id|mvme147lance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MACMACE&t;&t;/* Mac 68k Quadra AV builtin Ethernet */
(brace
id|mace_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MACSONIC&t;&t;/* Mac SONIC-based Ethernet of all sorts */ 
(brace
id|macsonic_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MAC8390           /* NuBus NS8390-based cards */
(brace
id|mac8390_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MAC89x0
(brace
id|mac89x0_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|sgi_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_SGISEEQ
(brace
id|sgiseeq_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|devprobe
id|mips_probes
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_MIPS_JAZZ_SONIC
(brace
id|sonic_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BAGETLANCE        /* Lance-based Baget ethernet boards */
(brace
id|bagetlance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Unified ethernet device probe, segmented per architecture and&n; * per bus interface. This drives the legacy devices only for now.&n; */
DECL|function|ethif_probe
r_static
r_int
id|__init
id|ethif_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* &n;&t; * Backwards compatibility - historically an I/O base of 1 was &n;&t; * used to indicate not to probe for this ethN interface &n;&t; */
r_if
c_cond
(paren
id|base_addr
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* ENXIO */
multiline_comment|/* &n;&t; * The arch specific probes are 1st so that any on-board ethernet&n;&t; * will be probed before other ISA/EISA/MCA/PCI bus cards.&n;&t; */
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|m68k_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|mips_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|sgi_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|eisa_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|mca_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|isa_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_list
c_func
(paren
id|dev
comma
id|parport_probes
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FDDI
DECL|function|fddiif_probe
r_static
r_int
id|__init
id|fddiif_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|base_addr
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* ENXIO */
r_if
c_cond
(paren
l_int|1
macro_line|#ifdef CONFIG_APFDDI
op_logical_and
id|apfddi_init
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_SKFP
op_logical_and
id|skfp_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
op_logical_and
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* -ENODEV or -EAGAIN would be more accurate. */
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_NET_FC
DECL|function|fcif_probe
r_static
r_int
id|fcif_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;base_addr
op_eq
op_minus
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|1
macro_line|#ifdef CONFIG_IPHASE5526
op_logical_and
id|iph5526_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
op_logical_and
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* -ENODEV or -EAGAIN would be more accurate. */
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif  /* CONFIG_NET_FC */
macro_line|#ifdef CONFIG_ETHERTAP
DECL|variable|tap0_dev
r_static
r_struct
id|net_device
id|tap0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tap0&quot;
comma
dot
id|base_addr
op_assign
id|NETLINK_TAPBASE
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|ethertap_probe
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV&t;(&amp;tap0_dev)
macro_line|#endif
macro_line|#ifdef CONFIG_SDLA
r_extern
r_int
id|sdla_init
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|variable|sdla0_dev
r_static
r_struct
id|net_device
id|sdla0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sdla0&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|sdla_init
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV&t;(&amp;sdla0_dev)
macro_line|#endif
macro_line|#if defined(CONFIG_LTPC)
r_extern
r_int
id|ltpc_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|variable|dev_ltpc
r_static
r_struct
id|net_device
id|dev_ltpc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lt0&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|ltpc_probe
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV&t;(&amp;dev_ltpc)
macro_line|#endif  /* LTPC */
macro_line|#if defined(CONFIG_COPS)
r_extern
r_int
id|cops_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|variable|cops2_dev
r_static
r_struct
id|net_device
id|cops2_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lt2&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|cops_probe
comma
)brace
suffix:semicolon
DECL|variable|cops1_dev
r_static
r_struct
id|net_device
id|cops1_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lt1&quot;
comma
dot
id|next
op_assign
op_amp
id|cops2_dev
comma
dot
id|init
op_assign
id|cops_probe
comma
)brace
suffix:semicolon
DECL|variable|cops0_dev
r_static
r_struct
id|net_device
id|cops0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lt0&quot;
comma
dot
id|next
op_assign
op_amp
id|cops1_dev
comma
dot
id|init
op_assign
id|cops_probe
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV     (&amp;cops0_dev)
macro_line|#endif  /* COPS */
DECL|variable|eth7_dev
r_static
r_struct
id|net_device
id|eth7_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth6_dev
r_static
r_struct
id|net_device
id|eth6_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth7_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth5_dev
r_static
r_struct
id|net_device
id|eth5_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth6_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth4_dev
r_static
r_struct
id|net_device
id|eth4_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth5_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth3_dev
r_static
r_struct
id|net_device
id|eth3_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth4_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth2_dev
r_static
r_struct
id|net_device
id|eth2_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth3_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth1_dev
r_static
r_struct
id|net_device
id|eth1_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth2_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|variable|eth0_dev
r_static
r_struct
id|net_device
id|eth0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eth%d&quot;
comma
dot
id|next
op_assign
op_amp
id|eth1_dev
comma
dot
id|init
op_assign
id|ethif_probe
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV&t;(&amp;eth0_dev)
macro_line|#ifdef CONFIG_TR
multiline_comment|/* Token-ring device probe */
r_extern
r_int
id|ibmtr_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|smctr_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_static
r_int
DECL|function|trif_probe
id|trif_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
l_int|1
macro_line|#ifdef CONFIG_IBMTR
op_logical_and
id|ibmtr_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_SMCTR
op_logical_and
id|smctr_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
op_logical_and
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* -ENODEV or -EAGAIN would be more accurate. */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tr7_dev
r_static
r_struct
id|net_device
id|tr7_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr6_dev
r_static
r_struct
id|net_device
id|tr6_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr7_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr5_dev
r_static
r_struct
id|net_device
id|tr5_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr6_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr4_dev
r_static
r_struct
id|net_device
id|tr4_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr5_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr3_dev
r_static
r_struct
id|net_device
id|tr3_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr4_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr2_dev
r_static
r_struct
id|net_device
id|tr2_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr3_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr1_dev
r_static
r_struct
id|net_device
id|tr1_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr2_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|variable|tr0_dev
r_static
r_struct
id|net_device
id|tr0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tr%d&quot;
comma
dot
id|next
op_assign
op_amp
id|tr1_dev
comma
dot
id|init
op_assign
id|trif_probe
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef       NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define      NEXT_DEV        (&amp;tr0_dev)
macro_line|#endif 
macro_line|#ifdef CONFIG_FDDI
DECL|variable|fddi7_dev
r_static
r_struct
id|net_device
id|fddi7_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi7&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi6_dev
r_static
r_struct
id|net_device
id|fddi6_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi6&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi7_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi5_dev
r_static
r_struct
id|net_device
id|fddi5_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi5&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi6_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi4_dev
r_static
r_struct
id|net_device
id|fddi4_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi4&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi5_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi3_dev
r_static
r_struct
id|net_device
id|fddi3_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi3&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi4_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi2_dev
r_static
r_struct
id|net_device
id|fddi2_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi2&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi3_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi1_dev
r_static
r_struct
id|net_device
id|fddi1_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi1&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi2_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|variable|fddi0_dev
r_static
r_struct
id|net_device
id|fddi0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fddi0&quot;
comma
dot
id|next
op_assign
op_amp
id|fddi1_dev
comma
dot
id|init
op_assign
id|fddiif_probe
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define&t;NEXT_DEV&t;(&amp;fddi0_dev)
macro_line|#endif 
macro_line|#ifdef CONFIG_NET_FC
DECL|variable|fc1_dev
r_static
r_struct
id|net_device
id|fc1_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fc1&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|fcif_probe
)brace
suffix:semicolon
DECL|variable|fc0_dev
r_static
r_struct
id|net_device
id|fc0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fc0&quot;
comma
dot
id|next
op_assign
op_amp
id|fc1_dev
comma
dot
id|init
op_assign
id|fcif_probe
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef       NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define      NEXT_DEV        (&amp;fc0_dev)
macro_line|#endif
macro_line|#ifdef CONFIG_SBNI
DECL|variable|sbni7_dev
r_static
r_struct
id|net_device
id|sbni7_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni7&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni6_dev
r_static
r_struct
id|net_device
id|sbni6_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni6&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni7_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni5_dev
r_static
r_struct
id|net_device
id|sbni5_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni5&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni6_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni4_dev
r_static
r_struct
id|net_device
id|sbni4_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni4&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni5_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni3_dev
r_static
r_struct
id|net_device
id|sbni3_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni3&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni4_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni2_dev
r_static
r_struct
id|net_device
id|sbni2_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni2&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni3_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni1_dev
r_static
r_struct
id|net_device
id|sbni1_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni1&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni2_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|variable|sbni0_dev
r_static
r_struct
id|net_device
id|sbni0_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sbni0&quot;
comma
dot
id|next
op_assign
op_amp
id|sbni1_dev
comma
dot
id|init
op_assign
id|sbni_probe
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define&t;NEXT_DEV&t;(&amp;sbni0_dev)
macro_line|#endif 
multiline_comment|/*&n; *&t;The loopback device is global so it can be directly referenced&n; *&t;by the network code. Also, it must be first on device list.&n; */
r_extern
r_int
id|loopback_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|loopback_dev
r_struct
id|net_device
id|loopback_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lo&quot;
comma
dot
id|next
op_assign
id|NEXT_DEV
comma
dot
id|init
op_assign
id|loopback_init
)brace
suffix:semicolon
multiline_comment|/*&n; * The @dev_base list is protected by @dev_base_lock and the rtln&n; * semaphore.&n; *&n; * Pure readers hold dev_base_lock for reading.&n; *&n; * Writers must hold the rtnl semaphore while they loop through the&n; * dev_base list, and hold dev_base_lock for writing when they do the&n; * actual updates.  This allows pure readers to access the list even&n; * while a writer is preparing to update it.&n; *&n; * To put it another way, dev_base_lock is held for writing only to&n; * protect against pure readers; the rtnl semaphore provides the&n; * protection against other writers.&n; *&n; * See, for example usages, register_netdevice() and&n; * unregister_netdevice(), which must be called with the rtnl&n; * semaphore held.&n; */
DECL|variable|dev_base
r_struct
id|net_device
op_star
id|dev_base
op_assign
op_amp
id|loopback_dev
suffix:semicolon
DECL|variable|dev_base_lock
id|rwlock_t
id|dev_base_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
eof
