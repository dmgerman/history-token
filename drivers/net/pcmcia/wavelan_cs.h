multiline_comment|/*&n; *&t;Wavelan Pcmcia driver&n; *&n; *&t;&t;Jean II - HPLB &squot;96&n; *&n; * Reorganisation and extension of the driver.&n; *&n; * This file contain all definition and declarations necessary for the&n; * wavelan pcmcia driver. This file is a private header, so it should&n; * be included only on wavelan_cs.c !!!&n; */
macro_line|#ifndef WAVELAN_CS_H
DECL|macro|WAVELAN_CS_H
mdefine_line|#define WAVELAN_CS_H
multiline_comment|/************************** DOCUMENTATION **************************/
multiline_comment|/*&n; * This driver provide a Linux interface to the Wavelan Pcmcia hardware&n; * The Wavelan is a product of Lucent (http://www.wavelan.com/).&n; * This division was formerly part of NCR and then AT&amp;T.&n; * Wavelan are also distributed by DEC (RoamAbout DS)...&n; *&n; * To know how to use this driver, read the PCMCIA HOWTO.&n; * If you want to exploit the many other fonctionalities, look comments&n; * in the code...&n; *&n; * This driver is the result of the effort of many peoples (see below).&n; */
multiline_comment|/* ------------------------ SPECIFIC NOTES ------------------------ */
multiline_comment|/*&n; * Web page&n; * --------&n; *&t;I try to maintain a web page with the Wireless LAN Howto at :&n; *&t;    http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux/Wavelan.html&n; *&n; * Debugging and options&n; * ---------------------&n; *&t;You will find below a set of &squot;#define&quot; allowing a very fine control&n; *&t;on the driver behaviour and the debug messages printed.&n; *&t;The main options are :&n; *&t;o WAVELAN_ROAMING, for the experimental roaming support.&n; *&t;o SET_PSA_CRC, to have your card correctly recognised by&n; *&t;  an access point and the Point-to-Point diagnostic tool.&n; *&t;o USE_PSA_CONFIG, to read configuration from the PSA (EEprom)&n; *&t;  (otherwise we always start afresh with some defaults)&n; *&n; * wavelan_cs.o is darn too big&n; * -------------------------&n; *&t;That&squot;s true ! There is a very simple way to reduce the driver&n; *&t;object by 33% (yes !). Comment out the following line :&n; *&t;&t;#include &lt;linux/wireless.h&gt;&n; *&t;Other compile options can also reduce the size of it...&n; *&n; * MAC address and hardware detection :&n; * ----------------------------------&n; *&t;The detection code of the wavelan chech that the first 3&n; *&t;octets of the MAC address fit the company code. This type of&n; *&t;detection work well for AT&amp;T cards (because the AT&amp;T code is&n; *&t;hardcoded in wavelan.h), but of course will fail for other&n; *&t;manufacturer.&n; *&n; *&t;If you are sure that your card is derived from the wavelan,&n; *&t;here is the way to configure it :&n; *&t;1) Get your MAC address&n; *&t;&t;a) With your card utilities (wfreqsel, instconf, ...)&n; *&t;&t;b) With the driver :&n; *&t;&t;&t;o compile the kernel with DEBUG_CONFIG_INFO enabled&n; *&t;&t;&t;o Boot and look the card messages&n; *&t;2) Set your MAC code (3 octets) in MAC_ADDRESSES[][3] (wavelan.h)&n; *&t;3) Compile &amp; verify&n; *&t;4) Send me the MAC code - I will include it in the next version...&n; *&n; */
multiline_comment|/* --------------------- WIRELESS EXTENSIONS --------------------- */
multiline_comment|/*&n; * This driver is the first one to support &quot;wireless extensions&quot;.&n; * This set of extensions provide you some way to control the wireless&n; * caracteristics of the hardware in a standard way and support for&n; * applications for taking advantage of it (like Mobile IP).&n; *&n; * You will need to enable the CONFIG_NET_RADIO define in the kernel&n; * configuration to enable the wireless extensions (this is the one&n; * giving access to the radio network device choice).&n; *&n; * It might also be a good idea as well to fetch the wireless tools to&n; * configure the device and play a bit.&n; */
multiline_comment|/* ---------------------------- FILES ---------------------------- */
multiline_comment|/*&n; * wavelan_cs.c :&t;The actual code for the driver - C functions&n; *&n; * wavelan_cs.h :&t;Private header : local types / vars for the driver&n; *&n; * wavelan.h :&t;&t;Description of the hardware interface &amp; structs&n; *&n; * i82593.h :&t;&t;Description if the Ethernet controller&n; */
multiline_comment|/* --------------------------- HISTORY --------------------------- */
multiline_comment|/*&n; * The history of the Wavelan drivers is as complicated as history of&n; * the Wavelan itself (NCR -&gt; AT&amp;T -&gt; Lucent).&n; *&n; * All started with Anders Klemets &lt;klemets@paul.rutgers.edu&gt;,&n; * writting a Wavelan ISA driver for the MACH microkernel. Girish&n; * Welling &lt;welling@paul.rutgers.edu&gt; had also worked on it.&n; * Keith Moore modify this for the Pcmcia hardware.&n; * &n; * Robert Morris &lt;rtm@das.harvard.edu&gt; port these two drivers to BSDI&n; * and add specific Pcmcia support (there is currently no equivalent&n; * of the PCMCIA package under BSD...).&n; *&n; * Jim Binkley &lt;jrb@cs.pdx.edu&gt; port both BSDI drivers to FreeBSD.&n; *&n; * Bruce Janson &lt;bruce@cs.usyd.edu.au&gt; port the BSDI ISA driver to Linux.&n; *&n; * Anthony D. Joseph &lt;adj@lcs.mit.edu&gt; started modify Bruce driver&n; * (with help of the BSDI PCMCIA driver) for PCMCIA.&n; * Yunzhou Li &lt;yunzhou@strat.iol.unh.edu&gt; finished is work.&n; * Joe Finney &lt;joe@comp.lancs.ac.uk&gt; patched the driver to start&n; * correctly 2.00 cards (2.4 GHz with frequency selection).&n; * David Hinds &lt;dhinds@pcmcia.sourceforge.org&gt; integrated the whole in his&n; * Pcmcia package (+ bug corrections).&n; *&n; * I (Jean Tourrilhes - jt@hplb.hpl.hp.com) then started to make some&n; * patchs to the Pcmcia driver. After, I added code in the ISA driver&n; * for Wireless Extensions and full support of frequency selection&n; * cards. Now, I&squot;m doing the same to the Pcmcia driver + some&n; * reorganisation.&n; * Loeke Brederveld &lt;lbrederv@wavelan.com&gt; from Lucent has given me&n; * much needed informations on the Wavelan hardware.&n; */
multiline_comment|/* By the way : for the copyright &amp; legal stuff :&n; * Almost everybody wrote code under GNU or BSD license (or alike),&n; * and want that their original copyright remain somewhere in the&n; * code (for myself, I go with the GPL).&n; * Nobody want to take responsibility for anything, except the fame...&n; */
multiline_comment|/* --------------------------- CREDITS --------------------------- */
multiline_comment|/*&n; * Credits:&n; *    Special thanks to Jan Hoogendoorn of AT&amp;T GIS Utrecht and&n; *&t;Loeke Brederveld of Lucent for providing extremely useful&n; *&t;information about WaveLAN PCMCIA hardware&n; *&n; *    This driver is based upon several other drivers, in particular:&n; *&t;David Hinds&squot; Linux driver for the PCMCIA 3c589 ethernet adapter&n; *&t;Bruce Janson&squot;s Linux driver for the AT-bus WaveLAN adapter&n; *&t;Anders Klemets&squot; PCMCIA WaveLAN adapter driver&n; *&t;Robert Morris&squot; BSDI driver for the PCMCIA WaveLAN adapter&n; *&n; * Additional Credits:&n; *&n; *    This software was originally developed under Linux 1.2.3&n; *&t;(Slackware 2.0 distribution).&n; *    And then under Linux 2.0.x (Debian 1.1 - pcmcia 2.8.18-23) with&n; *&t;HP OmniBook 4000 &amp; 5500.&n; *&n; *    It is based on other device drivers and information either written&n; *    or supplied by:&n; *&t;James Ashton (jaa101@syseng.anu.edu.au),&n; *&t;Ajay Bakre (bakre@paul.rutgers.edu),&n; *&t;Donald Becker (becker@super.org),&n; *&t;Jim Binkley &lt;jrb@cs.pdx.edu&gt;,&n; *&t;Loeke Brederveld &lt;lbrederv@wavelan.com&gt;,&n; *&t;Allan Creighton (allanc@cs.su.oz.au),&n; *&t;Brent Elphick &lt;belphick@uwaterloo.ca&gt;,&n; *&t;Joe Finney &lt;joe@comp.lancs.ac.uk&gt;,&n; *&t;Matthew Geier (matthew@cs.su.oz.au),&n; *&t;Remo di Giovanni (remo@cs.su.oz.au),&n; *&t;Mark Hagan (mhagan@wtcpost.daytonoh.NCR.COM),&n; *&t;David Hinds &lt;dhinds@pcmcia.sourceforge.org&gt;,&n; *&t;Jan Hoogendoorn (c/o marteijn@lucent.com),&n; *      Bruce Janson &lt;bruce@cs.usyd.edu.au&gt;,&n; *&t;Anthony D. Joseph &lt;adj@lcs.mit.edu&gt;,&n; *&t;Anders Klemets (klemets@paul.rutgers.edu),&n; *&t;Yunzhou Li &lt;yunzhou@strat.iol.unh.edu&gt;,&n; *&t;Marc Meertens (mmeertens@lucent.com),&n; *&t;Keith Moore,&n; *&t;Robert Morris (rtm@das.harvard.edu),&n; *&t;Ian Parkin (ian@cs.su.oz.au),&n; *&t;John Rosenberg (johnr@cs.su.oz.au),&n; *&t;George Rossi (george@phm.gov.au),&n; *&t;Arthur Scott (arthur@cs.su.oz.au),&n; *&t;Stanislav Sinyagin &lt;stas@isf.ru&gt;&n; *&t;Peter Storey,&n; *&t;Jean Tourrilhes &lt;jt@hpl.hp.com&gt;,&n; *&t;Girish Welling (welling@paul.rutgers.edu)&n; *&t;Clark Woodworth &lt;clark@hiway1.exit109.com&gt;&n; *&t;Yongguang Zhang &lt;ygz@isl.hrl.hac.com&gt;...&n; */
multiline_comment|/* ------------------------- IMPROVEMENTS ------------------------- */
multiline_comment|/*&n; * I proudly present :&n; *&n; * Changes made in 2.8.22 :&n; * ----------------------&n; *&t;- improved wv_set_multicast_list&n; *&t;- catch spurious interrupt&n; *&t;- correct release of the device&n; *&n; * Changes mades in release :&n; * ------------------------&n; *&t;- Reorganisation of the code, function name change&n; *&t;- Creation of private header (wavelan_cs.h)&n; *&t;- Reorganised debug messages&n; *&t;- More comments, history, ...&n; *&t;- Configure earlier (in &quot;insert&quot; instead of &quot;open&quot;)&n; *        and do things only once&n; *&t;- mmc_init : configure the PSA if not done&n; *&t;- mmc_init : 2.00 detection better code for 2.00 init&n; *&t;- better info at startup&n; *&t;- Correct a HUGE bug (volatile &amp; uncalibrated busy loop)&n; *&t;  in wv_82593_cmd =&gt; config speedup&n; *&t;- Stop receiving &amp; power down on close (and power up on open)&n; *&t;  use &quot;ifconfig down&quot; &amp; &quot;ifconfig up ; route add -net ...&quot;&n; *&t;- Send packets : add watchdog instead of pooling&n; *&t;- Receive : check frame wrap around &amp; try to recover some frames&n; *&t;- wavelan_set_multicast_list : avoid reset&n; *&t;- add wireless extensions (ioctl &amp; get_wireless_stats)&n; *&t;  get/set nwid/frequency on fly, info for /proc/net/wireless&n; *&t;- Suppress useless stuff from lp (net_local), but add link&n; *&t;- More inlines&n; *&t;- Lot of others minor details &amp; cleanups&n; *&n; * Changes made in second release :&n; * ------------------------------&n; *&t;- Optimise wv_85893_reconfig stuff, fix potential problems&n; *&t;- Change error values for ioctl&n; *&t;- Non blocking wv_ru_stop() + call wv_reset() in case of problems&n; *&t;- Remove development printk from wavelan_watchdog()&n; *&t;- Remove of the watchdog to wavelan_close instead of wavelan_release&n; *&t;  fix potential problems...&n; *&t;- Start debugging suspend stuff (but it&squot;s still a bit weird)&n; *&t;- Debug &amp; optimize dump header/packet in Rx &amp; Tx (debug)&n; *&t;- Use &quot;readb&quot; and &quot;writeb&quot; to be kernel 2.1 compliant&n; *&t;- Better handling of bogus interrupts&n; *&t;- Wireless extension : SETSPY and GETSPY&n; *&t;- Remove old stuff (stats - for those needing it, just ask me...)&n; *&t;- Make wireless extensions optional&n; *&n; * Changes made in third release :&n; * -----------------------------&n; *&t;- cleanups &amp; typos&n; *&t;- modif wireless ext (spy -&gt; only one pointer)&n; *&t;- new private ioctl to set/get quality &amp; level threshold&n; *&t;- Init : correct default value of level threshold for pcmcia&n; *&t;- kill watchdog in hw_reset&n; *&t;- more 2.1 support (copy_to/from_user instead of memcpy_to/fromfs)&n; *&t;- Add message level (debug stuff in /var/adm/debug &amp; errors not&n; *&t;  displayed at console and still in /var/adm/messages)&n; *&n; * Changes made in fourth release :&n; * ------------------------------&n; *&t;- multicast support (yes !) thanks to Yongguang Zhang.&n; *&n; * Changes made in fifth release (2.9.0) :&n; * -------------------------------------&n; *&t;- Revisited multicast code (it was mostly wrong).&n; *&t;- protect code in wv_82593_reconfig with dev-&gt;tbusy (oups !)&n; *&n; * Changes made in sixth release (2.9.1a) :&n; * --------------------------------------&n; *&t;- Change the detection code for multi manufacturer code support&n; *&t;- Correct bug (hang kernel) in init when we were &quot;rejecting&quot; a card &n; *&n; * Changes made in seventh release (2.9.1b) :&n; * ----------------------------------------&n; *&t;- Update to wireless extensions changes&n; *&t;- Silly bug in card initial configuration (psa_conf_status)&n; *&n; * Changes made in eigth release :&n; * -----------------------------&n; *&t;- Small bug in debug code (probably not the last one...)&n; *&t;- 1.2.13 support (thanks to Clark Woodworth)&n; *&n; * Changes made for release in 2.9.2b :&n; * ----------------------------------&n; *&t;- Level threshold is now a standard wireless extension (version 4 !)&n; *&t;- modules parameters types for kernel &gt; 2.1.17&n; *&t;- updated man page&n; *&t;- Others cleanup from David Hinds&n; *&n; * Changes made for release in 2.9.5 :&n; * ---------------------------------&n; *&t;- byte count stats (courtesy of David Hinds)&n; *&t;- Remove dev_tint stuff (courtesy of David Hinds)&n; *&t;- Others cleanup from David Hinds&n; *&t;- Encryption setting from Brent Elphick (thanks a lot !)&n; *&t;- &squot;base&squot; to &squot;u_long&squot; for the Alpha (thanks to Stanislav Sinyagin)&n; *&n; * Changes made for release in 2.9.6 :&n; * ---------------------------------&n; *&t;- fix bug : no longuer disable watchdog in case of bogus interrupt&n; *&t;- increase timeout in config code for picky hardware&n; *&t;- mask unused bits in status (Wireless Extensions)&n; *&n; * Changes integrated by Justin Seger &lt;jseger@MIT.EDU&gt; &amp; David Hinds :&n; * -----------------------------------------------------------------&n; *&t;- Roaming &quot;hack&quot; from Joe Finney &lt;joe@comp.lancs.ac.uk&gt;&n; *&t;- PSA CRC code from Bob Gray &lt;rgray@bald.cs.dartmouth.edu&gt;&n; *&t;- Better initialisation of the i82593 controller&n; *&t;  from Joseph K. O&squot;Sullivan &lt;josullvn+@cs.cmu.edu&gt;&n; *&n; * Changes made for release in 3.0.10 :&n; * ----------------------------------&n; *&t;- Fix eject &quot;hang&quot; of the driver under 2.2.X :&n; *&t;&t;o create wv_flush_stale_links()&n; *&t;&t;o Rename wavelan_release to wv_pcmcia_release &amp; move up&n; *&t;&t;o move unregister_netdev to wavelan_detach()&n; *&t;&t;o wavelan_release() no longer call wavelan_detach()&n; *&t;&t;o Suppress &quot;release&quot; timer&n; *&t;&t;o Other cleanups &amp; fixes&n; *&t;- New MAC address in the probe&n; *&t;- Reorg PSA_CRC code (endian neutral &amp; cleaner)&n; *&t;- Correct initialisation of the i82593 from Lucent manual&n; *&t;- Put back the watchdog, with larger timeout&n; *&t;- TRANSMIT_NO_CRC is a &quot;normal&quot; error, so recover from it&n; *&t;  from Derrick J Brashear &lt;shadow@dementia.org&gt;&n; *&t;- Better handling of TX and RX normal failure conditions&n; *&t;- #ifdef out all the roaming code&n; *&t;- Add ESSID &amp; &quot;AP current address&quot; ioctl stubs&n; *&t;- General cleanup of the code&n; *&n; * Changes made for release in 3.0.13 :&n; * ----------------------------------&n; *&t;- Re-enable compilation of roaming code by default, but with&n; *&t;  do_roaming = 0&n; *&t;- Nuke `nwid=nwid^ntohs(beacon-&gt;domain_id)&squot; in wl_roam_gather&n; *&t;  at the demand of John Carol Langford &lt;jcl@gs176.sp.cs.cmu.edu&gt;&n; *&t;- Introduced WAVELAN_ROAMING_EXT for incomplete ESSID stuff.&n; *&n; * Changes made for release in 3.0.15 :&n; * ----------------------------------&n; *&t;- Change e-mail and web page addresses&n; *&t;- Watchdog timer is now correctly expressed in HZ, not in jiffies&n; *&t;- Add channel number to the list of frequencies in range&n; *&t;- Add the (short) list of bit-rates in range&n; *&t;- Developp a new sensitivity... (sens.value &amp; sens.fixed)&n; *&n; * Changes made for release in 3.1.2 :&n; * ---------------------------------&n; *&t;- Fix check for root permission (break instead of exit)&n; *&t;- New nwid &amp; encoding setting (Wireless Extension 9)&n; *&n; * Wishes &amp; dreams:&n; * ----------------&n; *&t;- Cleanup and integrate the roaming code&n; *&t;  (std debug, set DomainID, decay avg and co...)&n; */
multiline_comment|/***************************** INCLUDES *****************************/
multiline_comment|/* Linux headers that we need */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#ifdef CONFIG_NET_PCMCIA_RADIO
macro_line|#include &lt;linux/wireless.h&gt;&t;&t;/* Wireless extensions */
macro_line|#endif&t;/* CONFIG_NET_PCMCIA_RADIO */
multiline_comment|/* Pcmcia headers that we need */
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
multiline_comment|/* Wavelan declarations */
macro_line|#include &quot;i82593.h&quot;&t;/* Definitions for the Intel chip */
macro_line|#include &quot;wavelan.h&quot;&t;/* Others bits of the hardware */
multiline_comment|/************************** DRIVER OPTIONS **************************/
multiline_comment|/*&n; * `#define&squot; or `#undef&squot; the following constant to change the behaviour&n; * of the driver...&n; */
DECL|macro|WAVELAN_ROAMING
mdefine_line|#define WAVELAN_ROAMING&t;&t;/* Include experimental roaming code */
DECL|macro|WAVELAN_ROAMING_EXT
macro_line|#undef WAVELAN_ROAMING_EXT&t;/* Enable roaming wireless extensions */
DECL|macro|SET_PSA_CRC
macro_line|#undef SET_PSA_CRC&t;&t;/* Set the CRC in PSA (slower) */
DECL|macro|USE_PSA_CONFIG
mdefine_line|#define USE_PSA_CONFIG&t;&t;/* Use info from the PSA */
DECL|macro|STRUCT_CHECK
macro_line|#undef STRUCT_CHECK&t;&t;/* Verify padding of structures */
DECL|macro|EEPROM_IS_PROTECTED
macro_line|#undef EEPROM_IS_PROTECTED&t;/* Doesn&squot;t seem to be necessary */
DECL|macro|MULTICAST_AVOID
mdefine_line|#define MULTICAST_AVOID&t;&t;/* Avoid extra multicast (I&squot;m sceptical) */
DECL|macro|SET_MAC_ADDRESS
macro_line|#undef SET_MAC_ADDRESS&t;&t;/* Experimental */
macro_line|#ifdef WIRELESS_EXT&t;/* If wireless extension exist in the kernel */
multiline_comment|/* Warning : these stuff will slow down the driver... */
DECL|macro|WIRELESS_SPY
mdefine_line|#define WIRELESS_SPY&t;&t;/* Enable spying addresses */
DECL|macro|HISTOGRAM
macro_line|#undef HISTOGRAM&t;&t;/* Enable histogram of sig level... */
macro_line|#endif
multiline_comment|/****************************** DEBUG ******************************/
DECL|macro|DEBUG_MODULE_TRACE
macro_line|#undef DEBUG_MODULE_TRACE&t;/* Module insertion/removal */
DECL|macro|DEBUG_CALLBACK_TRACE
macro_line|#undef DEBUG_CALLBACK_TRACE&t;/* Calls made by Linux */
DECL|macro|DEBUG_INTERRUPT_TRACE
macro_line|#undef DEBUG_INTERRUPT_TRACE&t;/* Calls to handler */
DECL|macro|DEBUG_INTERRUPT_INFO
macro_line|#undef DEBUG_INTERRUPT_INFO&t;/* type of interrupt &amp; so on */
DECL|macro|DEBUG_INTERRUPT_ERROR
mdefine_line|#define DEBUG_INTERRUPT_ERROR&t;/* problems */
DECL|macro|DEBUG_CONFIG_TRACE
macro_line|#undef DEBUG_CONFIG_TRACE&t;/* Trace the config functions */
DECL|macro|DEBUG_CONFIG_INFO
macro_line|#undef DEBUG_CONFIG_INFO&t;/* What&squot;s going on... */
DECL|macro|DEBUG_CONFIG_ERRORS
mdefine_line|#define DEBUG_CONFIG_ERRORS&t;/* Errors on configuration */
DECL|macro|DEBUG_TX_TRACE
macro_line|#undef DEBUG_TX_TRACE&t;&t;/* Transmission calls */
DECL|macro|DEBUG_TX_INFO
macro_line|#undef DEBUG_TX_INFO&t;&t;/* Header of the transmitted packet */
DECL|macro|DEBUG_TX_FAIL
macro_line|#undef DEBUG_TX_FAIL&t;&t;/* Normal failure conditions */
DECL|macro|DEBUG_TX_ERROR
mdefine_line|#define DEBUG_TX_ERROR&t;&t;/* Unexpected conditions */
DECL|macro|DEBUG_RX_TRACE
macro_line|#undef DEBUG_RX_TRACE&t;&t;/* Transmission calls */
DECL|macro|DEBUG_RX_INFO
macro_line|#undef DEBUG_RX_INFO&t;&t;/* Header of the transmitted packet */
DECL|macro|DEBUG_RX_FAIL
macro_line|#undef DEBUG_RX_FAIL&t;&t;/* Normal failure conditions */
DECL|macro|DEBUG_RX_ERROR
mdefine_line|#define DEBUG_RX_ERROR&t;&t;/* Unexpected conditions */
DECL|macro|DEBUG_PACKET_DUMP
macro_line|#undef DEBUG_PACKET_DUMP&t;/* Dump packet on the screen */
DECL|macro|DEBUG_IOCTL_TRACE
macro_line|#undef DEBUG_IOCTL_TRACE&t;/* Misc call by Linux */
DECL|macro|DEBUG_IOCTL_INFO
macro_line|#undef DEBUG_IOCTL_INFO&t;&t;/* Various debug info */
DECL|macro|DEBUG_IOCTL_ERROR
mdefine_line|#define DEBUG_IOCTL_ERROR&t;/* What&squot;s going wrong */
DECL|macro|DEBUG_BASIC_SHOW
mdefine_line|#define DEBUG_BASIC_SHOW&t;/* Show basic startup info */
DECL|macro|DEBUG_VERSION_SHOW
macro_line|#undef DEBUG_VERSION_SHOW&t;/* Print version info */
DECL|macro|DEBUG_PSA_SHOW
macro_line|#undef DEBUG_PSA_SHOW&t;&t;/* Dump psa to screen */
DECL|macro|DEBUG_MMC_SHOW
macro_line|#undef DEBUG_MMC_SHOW&t;&t;/* Dump mmc to screen */
DECL|macro|DEBUG_SHOW_UNUSED
macro_line|#undef DEBUG_SHOW_UNUSED&t;/* Show also unused fields */
DECL|macro|DEBUG_I82593_SHOW
macro_line|#undef DEBUG_I82593_SHOW&t;/* Show i82593 status */
DECL|macro|DEBUG_DEVICE_SHOW
macro_line|#undef DEBUG_DEVICE_SHOW&t;/* Show device parameters */
multiline_comment|/************************ CONSTANTS &amp; MACROS ************************/
macro_line|#ifdef DEBUG_VERSION_SHOW
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;wavelan_cs.c : v21 (wireless extensions) 18/10/99&bslash;n&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/* Watchdog temporisation */
DECL|macro|WATCHDOG_JIFFIES
mdefine_line|#define&t;WATCHDOG_JIFFIES&t;(256*HZ/100)
multiline_comment|/* Fix a bug in some old wireless extension definitions */
macro_line|#ifndef IW_ESSID_MAX_SIZE
DECL|macro|IW_ESSID_MAX_SIZE
mdefine_line|#define IW_ESSID_MAX_SIZE&t;32
macro_line|#endif
multiline_comment|/* ------------------------ PRIVATE IOCTL ------------------------ */
multiline_comment|/* Wireless Extension Backward compatibility - Jean II&n; * If the new wireless device private ioctl range is not defined,&n; * default to standard device private ioctl range */
macro_line|#ifndef SIOCIWFIRSTPRIV
DECL|macro|SIOCIWFIRSTPRIV
mdefine_line|#define SIOCIWFIRSTPRIV&t;SIOCDEVPRIVATE
macro_line|#endif /* SIOCIWFIRSTPRIV */
DECL|macro|SIOCSIPQTHR
mdefine_line|#define SIOCSIPQTHR&t;SIOCIWFIRSTPRIV&t;&t;/* Set quality threshold */
DECL|macro|SIOCGIPQTHR
mdefine_line|#define SIOCGIPQTHR&t;SIOCIWFIRSTPRIV + 1&t;/* Get quality threshold */
DECL|macro|SIOCSIPROAM
mdefine_line|#define SIOCSIPROAM     SIOCIWFIRSTPRIV + 2&t;/* Set roaming state */
DECL|macro|SIOCGIPROAM
mdefine_line|#define SIOCGIPROAM     SIOCIWFIRSTPRIV + 3&t;/* Get roaming state */
DECL|macro|SIOCSIPHISTO
mdefine_line|#define SIOCSIPHISTO&t;SIOCIWFIRSTPRIV + 6&t;/* Set histogram ranges */
DECL|macro|SIOCGIPHISTO
mdefine_line|#define SIOCGIPHISTO&t;SIOCIWFIRSTPRIV + 7&t;/* Get histogram values */
multiline_comment|/*************************** WaveLAN Roaming  **************************/
macro_line|#ifdef WAVELAN_ROAMING&t;&t;/* Conditional compile, see above in options */
DECL|macro|WAVELAN_ROAMING_DEBUG
mdefine_line|#define WAVELAN_ROAMING_DEBUG&t; 0&t;/* 1 = Trace of handover decisions */
multiline_comment|/* 2 = Info on each beacon rcvd... */
DECL|macro|MAX_WAVEPOINTS
mdefine_line|#define MAX_WAVEPOINTS&t;&t;7&t;/* Max visible at one time */
DECL|macro|WAVEPOINT_HISTORY
mdefine_line|#define WAVEPOINT_HISTORY&t;5&t;/* SNR sample history slow search */
DECL|macro|WAVEPOINT_FAST_HISTORY
mdefine_line|#define WAVEPOINT_FAST_HISTORY&t;2&t;/* SNR sample history fast search */
DECL|macro|SEARCH_THRESH_LOW
mdefine_line|#define SEARCH_THRESH_LOW&t;10&t;/* SNR to enter cell search */
DECL|macro|SEARCH_THRESH_HIGH
mdefine_line|#define SEARCH_THRESH_HIGH&t;13&t;/* SNR to leave cell search */
DECL|macro|WAVELAN_ROAMING_DELTA
mdefine_line|#define WAVELAN_ROAMING_DELTA&t;1&t;/* Hysteresis value (+/- SNR) */
DECL|macro|CELL_TIMEOUT
mdefine_line|#define CELL_TIMEOUT&t;&t;2*HZ&t;/* in jiffies */
DECL|macro|FAST_CELL_SEARCH
mdefine_line|#define FAST_CELL_SEARCH&t;1&t;/* Boolean values... */
DECL|macro|NWID_PROMISC
mdefine_line|#define NWID_PROMISC&t;&t;1&t;/* for code clarity. */
DECL|struct|wavepoint_beacon
r_typedef
r_struct
id|wavepoint_beacon
(brace
DECL|member|dsap
r_int
r_char
id|dsap
comma
multiline_comment|/* Unused */
DECL|member|ssap
id|ssap
comma
multiline_comment|/* Unused */
DECL|member|ctrl
id|ctrl
comma
multiline_comment|/* Unused */
DECL|member|O
DECL|member|U
DECL|member|I
id|O
comma
id|U
comma
id|I
comma
multiline_comment|/* Unused */
DECL|member|spec_id1
id|spec_id1
comma
multiline_comment|/* Unused */
DECL|member|spec_id2
id|spec_id2
comma
multiline_comment|/* Unused */
DECL|member|pdu_type
id|pdu_type
comma
multiline_comment|/* Unused */
DECL|member|seq
id|seq
suffix:semicolon
multiline_comment|/* WavePoint beacon sequence number */
DECL|member|domain_id
r_int
r_int
id|domain_id
comma
multiline_comment|/* WavePoint Domain ID */
DECL|member|nwid
id|nwid
suffix:semicolon
multiline_comment|/* WavePoint NWID */
DECL|typedef|wavepoint_beacon
)brace
id|wavepoint_beacon
suffix:semicolon
DECL|struct|wavepoint_history
r_typedef
r_struct
id|wavepoint_history
(brace
DECL|member|nwid
r_int
r_int
id|nwid
suffix:semicolon
multiline_comment|/* WavePoint&squot;s NWID */
DECL|member|average_slow
r_int
id|average_slow
suffix:semicolon
multiline_comment|/* SNR running average */
DECL|member|average_fast
r_int
id|average_fast
suffix:semicolon
multiline_comment|/* SNR running average */
DECL|member|sigqual
r_int
r_char
id|sigqual
(braket
id|WAVEPOINT_HISTORY
)braket
suffix:semicolon
multiline_comment|/* Ringbuffer of recent SNR&squot;s */
DECL|member|qualptr
r_int
r_char
id|qualptr
suffix:semicolon
multiline_comment|/* Index into ringbuffer */
DECL|member|last_seq
r_int
r_char
id|last_seq
suffix:semicolon
multiline_comment|/* Last seq. no seen for WavePoint */
DECL|member|next
r_struct
id|wavepoint_history
op_star
id|next
suffix:semicolon
multiline_comment|/* Next WavePoint in table */
DECL|member|prev
r_struct
id|wavepoint_history
op_star
id|prev
suffix:semicolon
multiline_comment|/* Previous WavePoint in table */
DECL|member|last_seen
r_int
r_int
id|last_seen
suffix:semicolon
multiline_comment|/* Time of last beacon recvd, jiffies */
DECL|typedef|wavepoint_history
)brace
id|wavepoint_history
suffix:semicolon
DECL|struct|wavepoint_table
r_struct
id|wavepoint_table
(brace
DECL|member|head
id|wavepoint_history
op_star
id|head
suffix:semicolon
multiline_comment|/* Start of ringbuffer */
DECL|member|num_wavepoints
r_int
id|num_wavepoints
suffix:semicolon
multiline_comment|/* No. of WavePoints visible */
DECL|member|locked
r_int
r_char
id|locked
suffix:semicolon
multiline_comment|/* Table lock */
)brace
suffix:semicolon
macro_line|#endif&t;/* WAVELAN_ROAMING */
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/* Shortcuts */
DECL|typedef|device
r_typedef
r_struct
id|net_device
id|device
suffix:semicolon
DECL|typedef|en_stats
r_typedef
r_struct
id|net_device_stats
id|en_stats
suffix:semicolon
DECL|typedef|iw_stats
r_typedef
r_struct
id|iw_statistics
id|iw_stats
suffix:semicolon
DECL|typedef|iw_qual
r_typedef
r_struct
id|iw_quality
id|iw_qual
suffix:semicolon
DECL|typedef|iw_freq
r_typedef
r_struct
id|iw_freq
id|iw_freq
suffix:semicolon
DECL|typedef|net_local
r_typedef
r_struct
id|net_local
id|net_local
suffix:semicolon
DECL|typedef|timer_list
r_typedef
r_struct
id|timer_list
id|timer_list
suffix:semicolon
multiline_comment|/* Basic types */
DECL|typedef|mac_addr
r_typedef
id|u_char
id|mac_addr
(braket
id|WAVELAN_ADDR_SIZE
)braket
suffix:semicolon
multiline_comment|/* Hardware address */
multiline_comment|/*&n; * Static specific data for the interface.&n; *&n; * For each network interface, Linux keep data in two structure. &quot;device&quot;&n; * keep the generic data (same format for everybody) and &quot;net_local&quot; keep&n; * the additional specific data.&n; * Note that some of this specific data is in fact generic (en_stats, for&n; * example).&n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
multiline_comment|/* ???? What is this stuff ???? */
DECL|member|dev
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Reverse link... */
DECL|member|link
id|dev_link_t
op_star
id|link
suffix:semicolon
multiline_comment|/* pcmcia structure */
DECL|member|stats
id|en_stats
id|stats
suffix:semicolon
multiline_comment|/* Ethernet interface statistics */
DECL|member|nresets
r_int
id|nresets
suffix:semicolon
multiline_comment|/* Number of hw resets */
DECL|member|configured
id|u_char
id|configured
suffix:semicolon
multiline_comment|/* If it is configured */
DECL|member|reconfig_82593
id|u_char
id|reconfig_82593
suffix:semicolon
multiline_comment|/* Need to reconfigure the controller */
DECL|member|promiscuous
id|u_char
id|promiscuous
suffix:semicolon
multiline_comment|/* Promiscuous mode */
DECL|member|allmulticast
id|u_char
id|allmulticast
suffix:semicolon
multiline_comment|/* All Multicast mode */
DECL|member|mc_count
r_int
id|mc_count
suffix:semicolon
multiline_comment|/* Number of multicast addresses */
DECL|member|watchdog
id|timer_list
id|watchdog
suffix:semicolon
multiline_comment|/* To avoid blocking state */
DECL|member|status
id|u_char
id|status
suffix:semicolon
multiline_comment|/* Current i82593 status */
DECL|member|stop
r_int
id|stop
suffix:semicolon
multiline_comment|/* Current i82593 Stop Hit Register */
DECL|member|rfp
r_int
id|rfp
suffix:semicolon
multiline_comment|/* Last DMA machine receive pointer */
DECL|member|overrunning
r_int
id|overrunning
suffix:semicolon
multiline_comment|/* Receiver overrun flag */
macro_line|#ifdef WIRELESS_EXT
DECL|member|wstats
id|iw_stats
id|wstats
suffix:semicolon
multiline_comment|/* Wireless specific stats */
macro_line|#endif
macro_line|#ifdef WIRELESS_SPY
DECL|member|spy_number
r_int
id|spy_number
suffix:semicolon
multiline_comment|/* Number of addresses to spy */
DECL|member|spy_address
id|mac_addr
id|spy_address
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
multiline_comment|/* The addresses to spy */
DECL|member|spy_stat
id|iw_qual
id|spy_stat
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
multiline_comment|/* Statistics gathered */
macro_line|#endif&t;/* WIRELESS_SPY */
macro_line|#ifdef HISTOGRAM
DECL|member|his_number
r_int
id|his_number
suffix:semicolon
multiline_comment|/* Number of intervals */
DECL|member|his_range
id|u_char
id|his_range
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Boundaries of interval ]n-1; n] */
DECL|member|his_sum
id|u_long
id|his_sum
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Sum in interval */
macro_line|#endif&t;/* HISTOGRAM */
macro_line|#ifdef WAVELAN_ROAMING
DECL|member|domain_id
id|u_long
id|domain_id
suffix:semicolon
multiline_comment|/* Domain ID we lock on for roaming */
DECL|member|filter_domains
r_int
id|filter_domains
suffix:semicolon
multiline_comment|/* Check Domain ID of beacon found */
DECL|member|wavepoint_table
r_struct
id|wavepoint_table
id|wavepoint_table
suffix:semicolon
multiline_comment|/* Table of visible WavePoints*/
DECL|member|curr_point
id|wavepoint_history
op_star
id|curr_point
suffix:semicolon
multiline_comment|/* Current wavepoint */
DECL|member|cell_search
r_int
id|cell_search
suffix:semicolon
multiline_comment|/* Searching for new cell? */
DECL|member|cell_timer
r_struct
id|timer_list
id|cell_timer
suffix:semicolon
multiline_comment|/* Garbage collection */
macro_line|#endif&t;/* WAVELAN_ROAMING */
)brace
suffix:semicolon
multiline_comment|/**************************** PROTOTYPES ****************************/
macro_line|#ifdef WAVELAN_ROAMING
multiline_comment|/* ---------------------- ROAMING SUBROUTINES -----------------------*/
id|wavepoint_history
op_star
id|wl_roam_check
c_func
(paren
r_int
r_int
id|nwid
comma
id|net_local
op_star
id|lp
)paren
suffix:semicolon
id|wavepoint_history
op_star
id|wl_new_wavepoint
c_func
(paren
r_int
r_int
id|nwid
comma
r_int
r_char
id|seq
comma
id|net_local
op_star
id|lp
)paren
suffix:semicolon
r_void
id|wl_del_wavepoint
c_func
(paren
id|wavepoint_history
op_star
id|wavepoint
comma
id|net_local
op_star
id|lp
)paren
suffix:semicolon
r_void
id|wl_cell_expiry
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
id|wavepoint_history
op_star
id|wl_best_sigqual
c_func
(paren
r_int
id|fast_search
comma
id|net_local
op_star
id|lp
)paren
suffix:semicolon
r_void
id|wl_update_history
c_func
(paren
id|wavepoint_history
op_star
id|wavepoint
comma
r_int
r_char
id|sigqual
comma
r_int
r_char
id|seq
)paren
suffix:semicolon
r_void
id|wv_roam_handover
c_func
(paren
id|wavepoint_history
op_star
id|wavepoint
comma
id|net_local
op_star
id|lp
)paren
suffix:semicolon
r_void
id|wv_nwid_filter
c_func
(paren
r_int
r_char
id|mode
comma
id|net_local
op_star
id|lp
)paren
suffix:semicolon
r_void
id|wv_roam_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|wv_roam_cleanup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;/* WAVELAN_ROAMING */
multiline_comment|/* ----------------------- MISC SUBROUTINES ------------------------ */
r_static
r_void
id|cs_error
c_func
(paren
id|client_handle_t
comma
multiline_comment|/* Report error to cardmgr */
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ----------------- MODEM MANAGEMENT SUBROUTINES ----------------- */
r_static
r_inline
id|u_char
multiline_comment|/* data */
id|hasr_read
c_func
(paren
id|u_long
)paren
suffix:semicolon
multiline_comment|/* Read the host interface : base address */
r_static
r_inline
r_void
id|hacr_write
c_func
(paren
id|u_long
comma
multiline_comment|/* Write to host interface : base address */
id|u_char
)paren
comma
multiline_comment|/* data */
id|hacr_write_slow
c_func
(paren
id|u_long
comma
id|u_char
)paren
suffix:semicolon
r_static
r_void
id|psa_read
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Read the Parameter Storage Area */
r_int
comma
multiline_comment|/* offset in PSA */
id|u_char
op_star
comma
multiline_comment|/* buffer to fill */
r_int
)paren
comma
multiline_comment|/* size to read */
id|psa_write
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Write to the PSA */
r_int
comma
multiline_comment|/* Offset in psa */
id|u_char
op_star
comma
multiline_comment|/* Buffer in memory */
r_int
)paren
suffix:semicolon
multiline_comment|/* Length of buffer */
r_static
r_inline
r_void
id|mmc_out
c_func
(paren
id|u_long
comma
multiline_comment|/* Write 1 byte to the Modem Manag Control */
id|u_short
comma
id|u_char
)paren
comma
id|mmc_write
c_func
(paren
id|u_long
comma
multiline_comment|/* Write n bytes to the MMC */
id|u_char
comma
id|u_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
id|u_char
multiline_comment|/* Read 1 byte from the MMC */
id|mmc_in
c_func
(paren
id|u_long
comma
id|u_short
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mmc_read
c_func
(paren
id|u_long
comma
multiline_comment|/* Read n bytes from the MMC */
id|u_char
comma
id|u_char
op_star
comma
r_int
)paren
comma
id|fee_wait
c_func
(paren
id|u_long
comma
multiline_comment|/* Wait for frequency EEprom : base address */
r_int
comma
multiline_comment|/* Base delay to wait for */
r_int
)paren
suffix:semicolon
multiline_comment|/* Number of time to wait */
r_static
r_void
id|fee_read
c_func
(paren
id|u_long
comma
multiline_comment|/* Read the frequency EEprom : base address */
id|u_short
comma
multiline_comment|/* destination offset */
id|u_short
op_star
comma
multiline_comment|/* data buffer */
r_int
)paren
suffix:semicolon
multiline_comment|/* number of registers */
multiline_comment|/* ---------------------- I82593 SUBROUTINES ----------------------- */
r_static
r_int
id|wv_82593_cmd
c_func
(paren
id|device
op_star
comma
multiline_comment|/* synchronously send a command to i82593 */
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_int
id|wv_diag
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Diagnostique the i82593 */
r_static
r_int
id|read_ringbuf
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Read a receive buffer */
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|wv_82593_reconfig
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Reconfigure the controller */
multiline_comment|/* ------------------- DEBUG &amp; INFO SUBROUTINES ------------------- */
r_static
r_inline
r_void
id|wv_init_info
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* display startup info */
multiline_comment|/* ------------------- IOCTL, STATS &amp; RECONFIG ------------------- */
r_static
id|en_stats
op_star
id|wavelan_get_stats
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Give stats /proc/net/dev */
multiline_comment|/* ----------------------- PACKET RECEPTION ----------------------- */
r_static
r_inline
r_int
id|wv_start_of_frame
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Seek beggining of current frame */
r_int
comma
multiline_comment|/* end of frame */
r_int
)paren
suffix:semicolon
multiline_comment|/* start of buffer */
r_static
r_inline
r_void
id|wv_packet_read
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Read a packet from a frame */
r_int
comma
r_int
)paren
comma
id|wv_packet_rcv
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Read all packets waiting */
multiline_comment|/* --------------------- PACKET TRANSMISSION --------------------- */
r_static
r_inline
r_void
id|wv_packet_write
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Write a packet to the Tx buffer */
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|wavelan_packet_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
comma
multiline_comment|/* Send a packet */
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* -------------------- HARDWARE CONFIGURATION -------------------- */
r_static
r_inline
r_int
id|wv_mmc_init
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Initialize the modem */
r_static
r_int
id|wv_ru_stop
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Stop the i82593 receiver unit */
id|wv_ru_start
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Start the i82593 receiver unit */
r_static
r_int
id|wv_82593_config
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Configure the i82593 */
r_static
r_inline
r_int
id|wv_pcmcia_reset
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Reset the pcmcia interface */
r_static
r_int
id|wv_hw_config
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Reset &amp; configure the whole hardware */
r_static
r_inline
r_void
id|wv_hw_reset
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Same, + start receiver unit */
r_static
r_inline
r_int
id|wv_pcmcia_config
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Configure the pcmcia interface */
r_static
r_void
id|wv_pcmcia_release
c_func
(paren
id|u_long
)paren
comma
multiline_comment|/* Remove a device */
id|wv_flush_stale_links
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* &quot;detach&quot; all possible devices */
multiline_comment|/* ---------------------- INTERRUPT HANDLING ---------------------- */
r_static
r_void
id|wavelan_interrupt
c_func
(paren
r_int
comma
multiline_comment|/* Interrupt handler */
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|wavelan_watchdog
c_func
(paren
id|u_long
)paren
suffix:semicolon
multiline_comment|/* Transmission watchdog */
multiline_comment|/* ------------------- CONFIGURATION CALLBACKS ------------------- */
r_static
r_int
id|wavelan_open
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Open the device */
id|wavelan_close
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Close the device */
id|wavelan_init
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Do nothing */
r_static
id|dev_link_t
op_star
id|wavelan_attach
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Create a new device */
r_static
r_void
id|wavelan_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Destroy a removed device */
r_static
r_int
id|wavelan_event
c_func
(paren
id|event_t
comma
multiline_comment|/* Manage pcmcia events */
r_int
comma
id|event_callback_args_t
op_star
)paren
suffix:semicolon
multiline_comment|/**************************** VARIABLES ****************************/
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;wavelan_cs&quot;
suffix:semicolon
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
suffix:semicolon
multiline_comment|/* Linked list of devices */
multiline_comment|/* WARNING : the following variable MUST be volatile&n; * It is used by wv_82593_cmd to syncronise with wavelan_interrupt */
DECL|variable|wv_wait_completed
r_static
r_volatile
r_int
id|wv_wait_completed
suffix:semicolon
multiline_comment|/*&n; * Parameters that can be set with &squot;insmod&squot;&n; * The exact syntax is &squot;insmod wavelan_cs.o &lt;var&gt;=&lt;value&gt;&squot;&n; */
multiline_comment|/* Bit map of interrupts to choose from */
multiline_comment|/* This means pick from 15, 14, 12, 11, 10, 9, 7, 5, 4 and 3 */
DECL|variable|irq_mask
r_static
r_int
id|irq_mask
op_assign
l_int|0xdeb8
suffix:semicolon
DECL|variable|irq_list
r_static
r_int
id|irq_list
(braket
l_int|4
)braket
op_assign
(brace
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* Shared memory speed, in ns */
DECL|variable|mem_speed
r_static
r_int
id|mem_speed
suffix:semicolon
multiline_comment|/* New module interface */
id|MODULE_PARM
c_func
(paren
id|irq_mask
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq_list
comma
l_string|&quot;1-4i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mem_speed
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#ifdef WAVELAN_ROAMING&t;&t;/* Conditional compile, see above in options */
multiline_comment|/* Enable roaming mode ? No ! Please keep this to 0 */
DECL|variable|do_roaming
r_static
r_int
id|do_roaming
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|do_roaming
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif&t;/* WAVELAN_ROAMING */
macro_line|#endif&t;/* WAVELAN_CS_H */
eof
