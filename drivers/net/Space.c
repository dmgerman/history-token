multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Holds initial configuration information for devices.&n; *&n; * Version:&t;@(#)Space.c&t;1.0.7&t;08/12/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@scyld.com&gt;&n; *&n; * Changelog:&n; *&t;&t;Paul Gortmaker (03/2002)&n;&t;&t;- struct init cleanup, enable multiple ISA autoprobes.&n; *&t;&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; - 09/1999&n; *&t;&t;- fix sbni: s/device/net_device/&n; *&t;&t;Paul Gortmaker (06/98): &n; *&t;&t; - sort probes in a sane way, make sure all (safe) probes&n; *&t;&t;   get run once &amp; failed autoprobes don&squot;t autoprobe again.&n; *&n; *&t;FIXME:&n; *&t;&t;Phase out placeholder dev entries put in the linked list&n; *&t;&t;here in favour of drivers using init_etherdev(NULL, ...)&n; *&t;&t;combined with a single find_all_devs() function (for 2.3)&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/divert.h&gt;
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
macro_line|#ifdef CONFIG_SDLA
r_extern
r_struct
id|net_device
op_star
id|sdla_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_COPS
r_extern
r_struct
id|net_device
op_star
id|cops_probe
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LTPC
r_extern
r_struct
id|net_device
op_star
id|ltpc_probe
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
r_void
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
r_int
id|ret
suffix:semicolon
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
multiline_comment|/*&n; * This is a bit of an artificial separation as there are PCI drivers&n; * that also probe for EISA cards (in the PCI group) and there are ISA&n; * drivers that probe for EISA cards (in the ISA group).  These are the&n; * legacy EISA only driver probes, and also the legacy PCI probes&n; */
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
macro_line|#if defined(CONFIG_NE2000) || defined(CONFIG_NE2K_CBUS)&t;/* ISA &amp; PC-9800 CBUS (use ne2k-pci for PCI cards) */
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
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|dev
op_assign
id|alloc_etherdev
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|netdev_boot_setup_check
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Backwards compatibility - historically an I/O base of 1 was &n;&t; * used to indicate not to probe for this ethN interface &n;&t; */
r_if
c_cond
(paren
id|dev-&gt;base_addr
op_eq
l_int|1
)paren
(brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
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
op_logical_or
id|probe_list
c_func
(paren
id|dev
comma
id|mips_probes
)paren
op_eq
l_int|0
op_logical_or
id|probe_list
c_func
(paren
id|dev
comma
id|eisa_probes
)paren
op_eq
l_int|0
op_logical_or
id|probe_list
c_func
(paren
id|dev
comma
id|mca_probes
)paren
op_eq
l_int|0
op_logical_or
id|probe_list
c_func
(paren
id|dev
comma
id|isa_probes
)paren
op_eq
l_int|0
op_logical_or
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
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
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
id|sk_isa_probe
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proteon_probe
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
DECL|function|trif_probe
r_static
id|__init
r_int
id|trif_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|dev
op_assign
id|alloc_trdev
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|netdev_boot_setup_check
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
macro_line|#ifdef CONFIG_IBMTR
id|ibmtr_probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
op_logical_or
macro_line|#endif
macro_line|#ifdef CONFIG_SKISA
id|sk_isa_probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
op_logical_or
macro_line|#endif
macro_line|#ifdef CONFIG_PROTEON
id|proteon_probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
op_logical_or
macro_line|#endif
macro_line|#ifdef CONFIG_SMCTR
id|smctr_probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
op_logical_or
macro_line|#endif
l_int|0
)paren
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;The loopback device is global so it can be directly referenced&n; *&t;by the network code. Also, it must be first on device list.&n; */
r_extern
r_int
id|loopback_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*  Statically configured drivers -- order matters here. */
DECL|function|probe_old_netdevs
r_void
id|__init
id|probe_old_netdevs
c_func
(paren
r_void
)paren
(brace
r_int
id|num
suffix:semicolon
r_if
c_cond
(paren
id|loopback_init
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Network loopback device setup failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SBNI
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|num
OL
l_int|8
suffix:semicolon
op_increment
id|num
)paren
r_if
c_cond
(paren
id|sbni_probe
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TR
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|num
OL
l_int|8
suffix:semicolon
op_increment
id|num
)paren
r_if
c_cond
(paren
id|trif_probe
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|num
OL
l_int|8
suffix:semicolon
op_increment
id|num
)paren
r_if
c_cond
(paren
id|ethif_probe
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_COPS
id|cops_probe
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|cops_probe
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|cops_probe
c_func
(paren
l_int|2
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LTPC
id|ltpc_probe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SDLA
id|sdla_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * The @dev_base list is protected by @dev_base_lock and the rtln&n; * semaphore.&n; *&n; * Pure readers hold dev_base_lock for reading.&n; *&n; * Writers must hold the rtnl semaphore while they loop through the&n; * dev_base list, and hold dev_base_lock for writing when they do the&n; * actual updates.  This allows pure readers to access the list even&n; * while a writer is preparing to update it.&n; *&n; * To put it another way, dev_base_lock is held for writing only to&n; * protect against pure readers; the rtnl semaphore provides the&n; * protection against other writers.&n; *&n; * See, for example usages, register_netdevice() and&n; * unregister_netdevice(), which must be called with the rtnl&n; * semaphore held.&n; */
DECL|variable|dev_base
r_struct
id|net_device
op_star
id|dev_base
suffix:semicolon
DECL|variable|dev_base_lock
id|rwlock_t
id|dev_base_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
eof
