multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions of the socket-level I/O control calls.&n; *&n; * Version:&t;@(#)sockios.h&t;1.0.2&t;03/09/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_SOCKIOS_H
DECL|macro|_LINUX_SOCKIOS_H
mdefine_line|#define _LINUX_SOCKIOS_H
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/* Linux-specific socket ioctls */
DECL|macro|SIOCINQ
mdefine_line|#define SIOCINQ&t;&t;FIONREAD
DECL|macro|SIOCOUTQ
mdefine_line|#define SIOCOUTQ&t;TIOCOUTQ
multiline_comment|/* Routing table calls. */
DECL|macro|SIOCADDRT
mdefine_line|#define SIOCADDRT&t;0x890B&t;&t;/* add routing table entry&t;*/
DECL|macro|SIOCDELRT
mdefine_line|#define SIOCDELRT&t;0x890C&t;&t;/* delete routing table entry&t;*/
DECL|macro|SIOCRTMSG
mdefine_line|#define SIOCRTMSG&t;0x890D&t;&t;/* call to routing system&t;*/
multiline_comment|/* Socket configuration controls. */
DECL|macro|SIOCGIFNAME
mdefine_line|#define SIOCGIFNAME&t;0x8910&t;&t;/* get iface name&t;&t;*/
DECL|macro|SIOCSIFLINK
mdefine_line|#define SIOCSIFLINK&t;0x8911&t;&t;/* set iface channel&t;&t;*/
DECL|macro|SIOCGIFCONF
mdefine_line|#define SIOCGIFCONF&t;0x8912&t;&t;/* get iface list&t;&t;*/
DECL|macro|SIOCGIFFLAGS
mdefine_line|#define SIOCGIFFLAGS&t;0x8913&t;&t;/* get flags&t;&t;&t;*/
DECL|macro|SIOCSIFFLAGS
mdefine_line|#define SIOCSIFFLAGS&t;0x8914&t;&t;/* set flags&t;&t;&t;*/
DECL|macro|SIOCGIFADDR
mdefine_line|#define SIOCGIFADDR&t;0x8915&t;&t;/* get PA address&t;&t;*/
DECL|macro|SIOCSIFADDR
mdefine_line|#define SIOCSIFADDR&t;0x8916&t;&t;/* set PA address&t;&t;*/
DECL|macro|SIOCGIFDSTADDR
mdefine_line|#define SIOCGIFDSTADDR&t;0x8917&t;&t;/* get remote PA address&t;*/
DECL|macro|SIOCSIFDSTADDR
mdefine_line|#define SIOCSIFDSTADDR&t;0x8918&t;&t;/* set remote PA address&t;*/
DECL|macro|SIOCGIFBRDADDR
mdefine_line|#define SIOCGIFBRDADDR&t;0x8919&t;&t;/* get broadcast PA address&t;*/
DECL|macro|SIOCSIFBRDADDR
mdefine_line|#define SIOCSIFBRDADDR&t;0x891a&t;&t;/* set broadcast PA address&t;*/
DECL|macro|SIOCGIFNETMASK
mdefine_line|#define SIOCGIFNETMASK&t;0x891b&t;&t;/* get network PA mask&t;&t;*/
DECL|macro|SIOCSIFNETMASK
mdefine_line|#define SIOCSIFNETMASK&t;0x891c&t;&t;/* set network PA mask&t;&t;*/
DECL|macro|SIOCGIFMETRIC
mdefine_line|#define SIOCGIFMETRIC&t;0x891d&t;&t;/* get metric&t;&t;&t;*/
DECL|macro|SIOCSIFMETRIC
mdefine_line|#define SIOCSIFMETRIC&t;0x891e&t;&t;/* set metric&t;&t;&t;*/
DECL|macro|SIOCGIFMEM
mdefine_line|#define SIOCGIFMEM&t;0x891f&t;&t;/* get memory address (BSD)&t;*/
DECL|macro|SIOCSIFMEM
mdefine_line|#define SIOCSIFMEM&t;0x8920&t;&t;/* set memory address (BSD)&t;*/
DECL|macro|SIOCGIFMTU
mdefine_line|#define SIOCGIFMTU&t;0x8921&t;&t;/* get MTU size&t;&t;&t;*/
DECL|macro|SIOCSIFMTU
mdefine_line|#define SIOCSIFMTU&t;0x8922&t;&t;/* set MTU size&t;&t;&t;*/
DECL|macro|SIOCSIFNAME
mdefine_line|#define SIOCSIFNAME&t;0x8923&t;&t;/* set interface name */
DECL|macro|SIOCSIFHWADDR
mdefine_line|#define&t;SIOCSIFHWADDR&t;0x8924&t;&t;/* set hardware address &t;*/
DECL|macro|SIOCGIFENCAP
mdefine_line|#define SIOCGIFENCAP&t;0x8925&t;&t;/* get/set encapsulations       */
DECL|macro|SIOCSIFENCAP
mdefine_line|#define SIOCSIFENCAP&t;0x8926&t;&t;
DECL|macro|SIOCGIFHWADDR
mdefine_line|#define SIOCGIFHWADDR&t;0x8927&t;&t;/* Get hardware address&t;&t;*/
DECL|macro|SIOCGIFSLAVE
mdefine_line|#define SIOCGIFSLAVE&t;0x8929&t;&t;/* Driver slaving support&t;*/
DECL|macro|SIOCSIFSLAVE
mdefine_line|#define SIOCSIFSLAVE&t;0x8930
DECL|macro|SIOCADDMULTI
mdefine_line|#define SIOCADDMULTI&t;0x8931&t;&t;/* Multicast address lists&t;*/
DECL|macro|SIOCDELMULTI
mdefine_line|#define SIOCDELMULTI&t;0x8932
DECL|macro|SIOCGIFINDEX
mdefine_line|#define SIOCGIFINDEX&t;0x8933&t;&t;/* name -&gt; if_index mapping&t;*/
DECL|macro|SIOGIFINDEX
mdefine_line|#define SIOGIFINDEX&t;SIOCGIFINDEX&t;/* misprint compatibility :-)&t;*/
DECL|macro|SIOCSIFPFLAGS
mdefine_line|#define SIOCSIFPFLAGS&t;0x8934&t;&t;/* set/get extended flags set&t;*/
DECL|macro|SIOCGIFPFLAGS
mdefine_line|#define SIOCGIFPFLAGS&t;0x8935
DECL|macro|SIOCDIFADDR
mdefine_line|#define SIOCDIFADDR&t;0x8936&t;&t;/* delete PA address&t;&t;*/
DECL|macro|SIOCSIFHWBROADCAST
mdefine_line|#define&t;SIOCSIFHWBROADCAST&t;0x8937&t;/* set hardware broadcast addr&t;*/
DECL|macro|SIOCGIFCOUNT
mdefine_line|#define SIOCGIFCOUNT&t;0x8938&t;&t;/* get number of devices */
DECL|macro|SIOCGIFBR
mdefine_line|#define SIOCGIFBR&t;0x8940&t;&t;/* Bridging support&t;&t;*/
DECL|macro|SIOCSIFBR
mdefine_line|#define SIOCSIFBR&t;0x8941&t;&t;/* Set bridging options &t;*/
DECL|macro|SIOCGIFTXQLEN
mdefine_line|#define SIOCGIFTXQLEN&t;0x8942&t;&t;/* Get the tx queue length&t;*/
DECL|macro|SIOCSIFTXQLEN
mdefine_line|#define SIOCSIFTXQLEN&t;0x8943&t;&t;/* Set the tx queue length &t;*/
DECL|macro|SIOCGIFDIVERT
mdefine_line|#define SIOCGIFDIVERT&t;0x8944&t;&t;/* Frame diversion support */
DECL|macro|SIOCSIFDIVERT
mdefine_line|#define SIOCSIFDIVERT&t;0x8945&t;&t;/* Set frame diversion options */
DECL|macro|SIOCETHTOOL
mdefine_line|#define SIOCETHTOOL&t;0x8946&t;&t;/* Ethtool interface&t;&t;*/
DECL|macro|SIOCGMIIPHY
mdefine_line|#define SIOCGMIIPHY&t;0x8947&t;&t;/* Get address of MII PHY in use. */
DECL|macro|SIOCGMIIREG
mdefine_line|#define SIOCGMIIREG&t;0x8948&t;&t;/* Read MII PHY register.&t;*/
DECL|macro|SIOCSMIIREG
mdefine_line|#define SIOCSMIIREG&t;0x8949&t;&t;/* Write MII PHY register.&t;*/
DECL|macro|SIOCDEVICE
mdefine_line|#define SIOCDEVICE&t;0x894A&t;&t;/* get/set netdev parameters&t;*/
multiline_comment|/* ARP cache control calls. */
multiline_comment|/*  0x8950 - 0x8952  * obsolete calls, don&squot;t re-use */
DECL|macro|SIOCDARP
mdefine_line|#define SIOCDARP&t;0x8953&t;&t;/* delete ARP table entry&t;*/
DECL|macro|SIOCGARP
mdefine_line|#define SIOCGARP&t;0x8954&t;&t;/* get ARP table entry&t;&t;*/
DECL|macro|SIOCSARP
mdefine_line|#define SIOCSARP&t;0x8955&t;&t;/* set ARP table entry&t;&t;*/
multiline_comment|/* RARP cache control calls. */
DECL|macro|SIOCDRARP
mdefine_line|#define SIOCDRARP&t;0x8960&t;&t;/* delete RARP table entry&t;*/
DECL|macro|SIOCGRARP
mdefine_line|#define SIOCGRARP&t;0x8961&t;&t;/* get RARP table entry&t;&t;*/
DECL|macro|SIOCSRARP
mdefine_line|#define SIOCSRARP&t;0x8962&t;&t;/* set RARP table entry&t;&t;*/
multiline_comment|/* Driver configuration calls */
DECL|macro|SIOCGIFMAP
mdefine_line|#define SIOCGIFMAP&t;0x8970&t;&t;/* Get device parameters&t;*/
DECL|macro|SIOCSIFMAP
mdefine_line|#define SIOCSIFMAP&t;0x8971&t;&t;/* Set device parameters&t;*/
multiline_comment|/* DLCI configuration calls */
DECL|macro|SIOCADDDLCI
mdefine_line|#define SIOCADDDLCI&t;0x8980&t;&t;/* Create new DLCI device&t;*/
DECL|macro|SIOCDELDLCI
mdefine_line|#define SIOCDELDLCI&t;0x8981&t;&t;/* Delete DLCI device&t;&t;*/
DECL|macro|SIOCGIFVLAN
mdefine_line|#define SIOCGIFVLAN&t;0x8982&t;&t;/* 802.1Q VLAN support&t;&t;*/
DECL|macro|SIOCSIFVLAN
mdefine_line|#define SIOCSIFVLAN&t;0x8983&t;&t;/* Set 802.1Q VLAN options &t;*/
multiline_comment|/* bonding calls */
DECL|macro|SIOCBONDENSLAVE
mdefine_line|#define SIOCBONDENSLAVE&t;0x8990&t;&t;/* enslave a device to the bond */
DECL|macro|SIOCBONDRELEASE
mdefine_line|#define SIOCBONDRELEASE 0x8991&t;&t;/* release a slave from the bond*/
DECL|macro|SIOCBONDSETHWADDR
mdefine_line|#define SIOCBONDSETHWADDR      0x8992&t;/* set the hw addr of the bond  */
DECL|macro|SIOCBONDSLAVEINFOQUERY
mdefine_line|#define SIOCBONDSLAVEINFOQUERY 0x8993   /* rtn info about slave state   */
DECL|macro|SIOCBONDINFOQUERY
mdefine_line|#define SIOCBONDINFOQUERY      0x8994&t;/* rtn info about bond state    */
DECL|macro|SIOCBONDCHANGEACTIVE
mdefine_line|#define SIOCBONDCHANGEACTIVE   0x8995   /* update to a new active slave */
multiline_comment|/* Device private ioctl calls */
multiline_comment|/*&n; *&t;These 16 ioctls are available to devices via the do_ioctl() device&n; *&t;vector. Each device should include this file and redefine these names&n; *&t;as their own. Because these are device dependent it is a good idea&n; *&t;_NOT_ to issue them to random objects and hope.&n; *&n; *&t;THESE IOCTLS ARE _DEPRECATED_ AND WILL DISAPPEAR IN 2.5.X -DaveM&n; */
DECL|macro|SIOCDEVPRIVATE
mdefine_line|#define SIOCDEVPRIVATE&t;0x89F0&t;/* to 89FF */
multiline_comment|/*&n; *&t;These 16 ioctl calls are protocol private&n; */
DECL|macro|SIOCPROTOPRIVATE
mdefine_line|#define SIOCPROTOPRIVATE 0x89E0 /* to 89EF */
macro_line|#endif&t;/* _LINUX_SOCKIOS_H */
eof
