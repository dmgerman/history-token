multiline_comment|/*&n; *&t;WaveLAN ISA driver&n; *&n; *&t;&t;Jean II - HPLB &squot;96&n; *&n; * Reorganisation and extension of the driver.&n; *&n; * This file contains all definitions and declarations necessary for the&n; * WaveLAN ISA driver.  This file is a private header, so it should&n; * be included only in wavelan.c!&n; */
macro_line|#ifndef WAVELAN_P_H
DECL|macro|WAVELAN_P_H
mdefine_line|#define WAVELAN_P_H
multiline_comment|/************************** DOCUMENTATION ***************************/
multiline_comment|/*&n; * This driver provides a Linux interface to the WaveLAN ISA hardware.&n; * The WaveLAN is a product of Lucent (http://www.wavelan.com/).&n; * This division was formerly part of NCR and then AT&amp;T.&n; * WaveLANs are also distributed by DEC (RoamAbout DS) and Digital Ocean.&n; *&n; * To learn how to use this driver, read the NET3 HOWTO.&n; * If you want to exploit the many other functionalities, read the comments&n; * in the code.&n; *&n; * This driver is the result of the effort of many people (see below).&n; */
multiline_comment|/* ------------------------ SPECIFIC NOTES ------------------------ */
multiline_comment|/*&n; * Web page&n; * --------&n; *&t;I try to maintain a web page with the Wireless LAN Howto at :&n; *&t;    http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux/Wavelan.html&n; *&n; * SMP&n; * ---&n; *&t;We now are SMP compliant (I eventually fixed the remaining bugs).&n; *&t;The driver has been tested on a dual P6-150 and survived my usual&n; *&t;set of torture tests.&n; *&t;Anyway, I spent enough time chasing interrupt re-entrancy during&n; *&t;errors or reconfigure, and I designed the locked/unlocked sections&n; *&t;of the driver with great care, and with the recent addition of&n; *&t;the spinlock (thanks to the new API), we should be quite close to&n; *&t;the truth.&n; *&t;The SMP/IRQ locking is quite coarse and conservative (i.e. not fast),&n; *&t;but better safe than sorry (especially at 2 Mb/s ;-).&n; *&n; *&t;I have also looked into disabling only our interrupt on the card&n; *&t;(via HACR) instead of all interrupts in the processor (via cli),&n; *&t;so that other driver are not impacted, and it look like it&squot;s&n; *&t;possible, but it&squot;s very tricky to do right (full of races). As&n; *&t;the gain would be mostly for SMP systems, it can wait...&n; *&n; * Debugging and options&n; * ---------------------&n; *&t;You will find below a set of &squot;#define&quot; allowing a very fine control&n; *&t;on the driver behaviour and the debug messages printed.&n; *&t;The main options are :&n; *&t;o SET_PSA_CRC, to have your card correctly recognised by&n; *&t;  an access point and the Point-to-Point diagnostic tool.&n; *&t;o USE_PSA_CONFIG, to read configuration from the PSA (EEprom)&n; *&t;  (otherwise we always start afresh with some defaults)&n; *&n; * wavelan.o is too darned big&n; * ---------------------------&n; *&t;That&squot;s true!  There is a very simple way to reduce the driver&n; *&t;object by 33%!  Comment out the following line:&n; *&t;&t;#include &lt;linux/wireless.h&gt;&n; *&t;Other compile options can also reduce the size of it...&n; *&n; * MAC address and hardware detection:&n; * -----------------------------------&n; *&t;The detection code for the WaveLAN checks that the first three&n; *&t;octets of the MAC address fit the company code.  This type of&n; *&t;detection works well for AT&amp;T cards (because the AT&amp;T code is&n; *&t;hardcoded in wavelan.h), but of course will fail for other&n; *&t;manufacturers.&n; *&n; *&t;If you are sure that your card is derived from the WaveLAN,&n; *&t;here is the way to configure it:&n; *&t;1) Get your MAC address&n; *&t;&t;a) With your card utilities (wfreqsel, instconf, etc.)&n; *&t;&t;b) With the driver:&n; *&t;&t;&t;o compile the kernel with DEBUG_CONFIG_INFO enabled&n; *&t;&t;&t;o Boot and look the card messages&n; *&t;2) Set your MAC code (3 octets) in MAC_ADDRESSES[][3] (wavelan.h)&n; *&t;3) Compile and verify&n; *&t;4) Send me the MAC code.  I will include it in the next version.&n; *&n; */
multiline_comment|/* --------------------- WIRELESS EXTENSIONS --------------------- */
multiline_comment|/*&n; * This driver is the first to support &quot;wireless extensions&quot;.&n; * This set of extensions provides a standard way to control the wireless&n; * characteristics of the hardware.  Applications such as mobile IP may&n; * take advantage of it.&n; *&n; * You will need to enable the CONFIG_NET_RADIO define in the kernel&n; * configuration to enable the wireless extensions (this is the one&n; * giving access to the radio network device choice).&n; *&n; * It might also be a good idea as well to fetch the wireless tools to&n; * configure the device and play a bit.&n; */
multiline_comment|/* ---------------------------- FILES ---------------------------- */
multiline_comment|/*&n; * wavelan.c:&t;&t;actual code for the driver:  C functions&n; *&n; * wavelan.p.h:&t;&t;private header:  local types and variables for driver&n; *&n; * wavelan.h:&t;&t;description of the hardware interface and structs&n; *&n; * i82586.h:&t;&t;description of the Ethernet controller&n; */
multiline_comment|/* --------------------------- HISTORY --------------------------- */
multiline_comment|/*&n; * This is based on information in the drivers&squot; headers. It may not be&n; * accurate, and I guarantee only my best effort.&n; *&n; * The history of the WaveLAN drivers is as complicated as the history of&n; * the WaveLAN itself (NCR -&gt; AT&amp;T -&gt; Lucent).&n; *&n; * It all started with Anders Klemets &lt;klemets@paul.rutgers.edu&gt;&n; * writing a WaveLAN ISA driver for the Mach microkernel.  Girish&n; * Welling &lt;welling@paul.rutgers.edu&gt; had also worked on it.&n; * Keith Moore modified this for the PCMCIA hardware.&n; * &n; * Robert Morris &lt;rtm@das.harvard.edu&gt; ported these two drivers to BSDI&n; * and added specific PCMCIA support (there is currently no equivalent&n; * of the PCMCIA package under BSD).&n; *&n; * Jim Binkley &lt;jrb@cs.pdx.edu&gt; ported both BSDI drivers to FreeBSD.&n; *&n; * Bruce Janson &lt;bruce@cs.usyd.edu.au&gt; ported the BSDI ISA driver to Linux.&n; *&n; * Anthony D. Joseph &lt;adj@lcs.mit.edu&gt; started to modify Bruce&squot;s driver&n; * (with help of the BSDI PCMCIA driver) for PCMCIA.&n; * Yunzhou Li &lt;yunzhou@strat.iol.unh.edu&gt; finished this work.&n; * Joe Finney &lt;joe@comp.lancs.ac.uk&gt; patched the driver to start&n; * 2.00 cards correctly (2.4 GHz with frequency selection).&n; * David Hinds &lt;dhinds@hyper.stanford.edu&gt; integrated the whole in his&n; * PCMCIA package (and bug corrections).&n; *&n; * I (Jean Tourrilhes - jt@hplb.hpl.hp.com) then started to make some&n; * patches to the PCMCIA driver.  Later, I added code in the ISA driver&n; * for Wireless Extensions and full support of frequency selection&n; * cards.  Then, I did the same to the PCMCIA driver, and did some&n; * reorganisation.  Finally, I came back to the ISA driver to&n; * upgrade it at the same level as the PCMCIA one and reorganise&n; * the code.&n; * Loeke Brederveld &lt;lbrederv@wavelan.com&gt; from Lucent has given me&n; * much needed information on the WaveLAN hardware.&n; */
multiline_comment|/* The original copyrights and literature mention others&squot; names and&n; * credits.  I don&squot;t know what their part in this development was.&n; */
multiline_comment|/* By the way, for the copyright and legal stuff:&n; * almost everybody wrote code under the GNU or BSD license (or similar),&n; * and want their original copyright to remain somewhere in the&n; * code (for myself, I go with the GPL).&n; * Nobody wants to take responsibility for anything, except the fame.&n; */
multiline_comment|/* --------------------------- CREDITS --------------------------- */
multiline_comment|/*&n; * This software was developed as a component of the&n; * Linux operating system.&n; * It is based on other device drivers and information&n; * either written or supplied by:&n; *&t;Ajay Bakre &lt;bakre@paul.rutgers.edu&gt;,&n; *&t;Donald Becker &lt;becker@cesdis.gsfc.nasa.gov&gt;,&n; *&t;Loeke Brederveld &lt;Loeke.Brederveld@Utrecht.NCR.com&gt;,&n; *&t;Brent Elphick &lt;belphick@uwaterloo.ca&gt;,&n; *&t;Anders Klemets &lt;klemets@it.kth.se&gt;,&n; *&t;Vladimir V. Kolpakov &lt;w@stier.koenig.ru&gt;,&n; *&t;Marc Meertens &lt;Marc.Meertens@Utrecht.NCR.com&gt;,&n; *&t;Pauline Middelink &lt;middelin@polyware.iaf.nl&gt;,&n; *&t;Robert Morris &lt;rtm@das.harvard.edu&gt;,&n; *&t;Jean Tourrilhes &lt;jt@hpl.hp.com&gt;,&n; *&t;Girish Welling &lt;welling@paul.rutgers.edu&gt;,&n; *&t;Clark Woodworth &lt;clark@hiway1.exit109.com&gt;&n; *&t;Yongguang Zhang &lt;ygz@isl.hrl.hac.com&gt;&n; *&n; * Thanks go also to:&n; *&t;James Ashton &lt;jaa101@syseng.anu.edu.au&gt;,&n; *&t;Alan Cox &lt;alan@redhat.com&gt;,&n; *&t;Allan Creighton &lt;allanc@cs.usyd.edu.au&gt;,&n; *&t;Matthew Geier &lt;matthew@cs.usyd.edu.au&gt;,&n; *&t;Remo di Giovanni &lt;remo@cs.usyd.edu.au&gt;,&n; *&t;Eckhard Grah &lt;grah@wrcs1.urz.uni-wuppertal.de&gt;,&n; *&t;Vipul Gupta &lt;vgupta@cs.binghamton.edu&gt;,&n; *&t;Mark Hagan &lt;mhagan@wtcpost.daytonoh.NCR.COM&gt;,&n; *&t;Tim Nicholson &lt;tim@cs.usyd.edu.au&gt;,&n; *&t;Ian Parkin &lt;ian@cs.usyd.edu.au&gt;,&n; *&t;John Rosenberg &lt;johnr@cs.usyd.edu.au&gt;,&n; *&t;George Rossi &lt;george@phm.gov.au&gt;,&n; *&t;Arthur Scott &lt;arthur@cs.usyd.edu.au&gt;,&n; *&t;Stanislav Sinyagin &lt;stas@isf.ru&gt;&n; *&t;and Peter Storey for their assistance and advice.&n; *&n; * Additional Credits:&n; *&n; *&t;My development has been done initially under Debian 1.1 (Linux 2.0.x)&n; *&t;and now&t;under Debian 2.2, initially with an HP Vectra XP/60, and now&n; *&t;an HP Vectra XP/90.&n; *&n; */
multiline_comment|/* ------------------------- IMPROVEMENTS ------------------------- */
multiline_comment|/*&n; * I proudly present:&n; *&n; * Changes made in first pre-release:&n; * ----------------------------------&n; *&t;- reorganisation of the code, function name change&n; *&t;- creation of private header (wavelan.p.h)&n; *&t;- reorganised debug messages&n; *&t;- more comments, history, etc.&n; *&t;- mmc_init:  configure the PSA if not done&n; *&t;- mmc_init:  correct default value of level threshold for PCMCIA&n; *&t;- mmc_init:  2.00 detection better code for 2.00 initialization&n; *&t;- better info at startup&n; *&t;- IRQ setting (note:  this setting is permanent)&n; *&t;- watchdog:  change strategy (and solve module removal problems)&n; *&t;- add wireless extensions (ioctl and get_wireless_stats)&n; *&t;  get/set nwid/frequency on fly, info for /proc/net/wireless&n; *&t;- more wireless extensions:  SETSPY and GETSPY&n; *&t;- make wireless extensions optional&n; *&t;- private ioctl to set/get quality and level threshold, histogram&n; *&t;- remove /proc/net/wavelan&n; *&t;- suppress useless stuff from lp (net_local)&n; *&t;- kernel 2.1 support (copy_to/from_user instead of memcpy_to/fromfs)&n; *&t;- add message level (debug stuff in /var/adm/debug and errors not&n; *&t;  displayed at console and still in /var/adm/messages)&n; *&t;- multi device support&n; *&t;- start fixing the probe (init code)&n; *&t;- more inlines&n; *&t;- man page&n; *&t;- many other minor details and cleanups&n; *&n; * Changes made in second pre-release:&n; * -----------------------------------&n; *&t;- clean up init code (probe and module init)&n; *&t;- better multiple device support (module)&n; *&t;- name assignment (module)&n; *&n; * Changes made in third pre-release:&n; * ----------------------------------&n; *&t;- be more conservative on timers&n; *&t;- preliminary support for multicast (I still lack some details)&n; *&n; * Changes made in fourth pre-release:&n; * -----------------------------------&n; *&t;- multicast (revisited and finished)&n; *&t;- avoid reset in set_multicast_list (a really big hack)&n; *&t;  if somebody could apply this code for other i82586 based drivers&n; *&t;- share onboard memory 75% RU and 25% CU (instead of 50/50)&n; *&n; * Changes made for release in 2.1.15:&n; * -----------------------------------&n; *&t;- change the detection code for multi manufacturer code support&n; *&n; * Changes made for release in 2.1.17:&n; * -----------------------------------&n; *&t;- update to wireless extensions changes&n; *&t;- silly bug in card initial configuration (psa_conf_status)&n; *&n; * Changes made for release in 2.1.27 &amp; 2.0.30:&n; * --------------------------------------------&n; *&t;- small bug in debug code (probably not the last one...)&n; *&t;- remove extern keyword for wavelan_probe()&n; *&t;- level threshold is now a standard wireless extension (version 4 !)&n; *&t;- modules parameters types (new module interface)&n; *&n; * Changes made for release in 2.1.36:&n; * -----------------------------------&n; *&t;- byte count stats (courtesy of David Hinds)&n; *&t;- remove dev_tint stuff (courtesy of David Hinds)&n; *&t;- encryption setting from Brent Elphick (thanks a lot!)&n; *&t;- &squot;ioaddr&squot; to &squot;u_long&squot; for the Alpha (thanks to Stanislav Sinyagin)&n; *&n; * Other changes (not by me) :&n; * -------------------------&n; *&t;- Spelling and gramar &quot;rectification&quot;.&n; *&n; * Changes made for release in 2.0.37 &amp; 2.2.2 :&n; * ------------------------------------------&n; *&t;- Correct status in /proc/net/wireless&n; *&t;- Set PSA CRC to make PtP diagnostic tool happy (Bob Gray)&n; *&t;- Module init code don&squot;t fail if we found at least one card in&n; *&t;  the address list (Karlis Peisenieks)&n; *&t;- Missing parenthesis (Christopher Peterson)&n; *&t;- Correct i82586 configuration parameters&n; *&t;- Encryption initialisation bug (Robert McCormack)&n; *&t;- New mac addresses detected in the probe&n; *&t;- Increase watchdog for busy environments&n; *&n; * Changes made for release in 2.0.38 &amp; 2.2.7 :&n; * ------------------------------------------&n; *&t;- Correct the reception logic to better report errors and avoid&n; *&t;  sending bogus packet up the stack&n; *&t;- Delay RU config to avoid corrupting first received packet&n; *&t;- Change config completion code (to actually check something)&n; *&t;- Avoid reading out of bound in skbuf to transmit&n; *&t;- Rectify a lot of (useless) debugging code&n; *&t;- Change the way to `#ifdef SET_PSA_CRC&squot;&n; *&n; * Changes made for release in 2.2.11 &amp; 2.3.13 :&n; * -------------------------------------------&n; *&t;- Change e-mail and web page addresses&n; *&t;- Watchdog timer is now correctly expressed in HZ, not in jiffies&n; *&t;- Add channel number to the list of frequencies in range&n; *&t;- Add the (short) list of bit-rates in range&n; *&t;- Developp a new sensitivity... (sens.value &amp; sens.fixed)&n; *&n; * Changes made for release in 2.2.14 &amp; 2.3.23 :&n; * -------------------------------------------&n; *&t;- Fix check for root permission (break instead of exit)&n; *&t;- New nwid &amp; encoding setting (Wireless Extension 9)&n; *&n; * Changes made for release in 2.3.49 :&n; * ----------------------------------&n; *&t;- Indentation reformating (Alan)&n; *&t;- Update to new network API (softnet - 2.3.43) :&n; *&t;&t;o replace dev-&gt;tbusy (Alan)&n; *&t;&t;o replace dev-&gt;tstart (Alan)&n; *&t;&t;o remove dev-&gt;interrupt (Alan)&n; *&t;&t;o add SMP locking via spinlock in splxx (me)&n; *&t;&t;o add spinlock in interrupt handler (me)&n; *&t;&t;o use kernel watchdog instead of ours (me)&n; *&t;&t;o increase watchdog timeout (kernel is more sensitive) (me)&n; *&t;&t;o verify that all the changes make sense and work (me)&n; *&t;- Fixup a potential gotcha when reconfiguring and thighten a bit&n; *&t;&t;the interactions with Tx queue.&n; *&n; * Changes made for release in 2.4.0 :&n; * ---------------------------------&n; *&t;- Fix spinlock stupid bugs that I left in. The driver is now SMP&n; *&t;&t;compliant and doesn&squot;t lockup at startup.&n; *&n; * Changes made for release in 2.5.2 :&n; * ---------------------------------&n; *&t;- Use new driver API for Wireless Extensions :&n; *&t;&t;o got rid of wavelan_ioctl()&n; *&t;&t;o use a bunch of iw_handler instead&n; *&n; * Wishes &amp; dreams:&n; * ----------------&n; *&t;- roaming (see Pcmcia driver)&n; */
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include&t;&lt;linux/module.h&gt;
macro_line|#include&t;&lt;linux/kernel.h&gt;
macro_line|#include&t;&lt;linux/sched.h&gt;
macro_line|#include&t;&lt;linux/types.h&gt;
macro_line|#include&t;&lt;linux/fcntl.h&gt;
macro_line|#include&t;&lt;linux/interrupt.h&gt;
macro_line|#include&t;&lt;linux/stat.h&gt;
macro_line|#include&t;&lt;linux/ptrace.h&gt;
macro_line|#include&t;&lt;linux/ioport.h&gt;
macro_line|#include&t;&lt;linux/in.h&gt;
macro_line|#include&t;&lt;linux/string.h&gt;
macro_line|#include&t;&lt;linux/delay.h&gt;
macro_line|#include&t;&lt;asm/system.h&gt;
macro_line|#include&t;&lt;asm/bitops.h&gt;
macro_line|#include&t;&lt;asm/io.h&gt;
macro_line|#include&t;&lt;asm/dma.h&gt;
macro_line|#include&t;&lt;asm/uaccess.h&gt;
macro_line|#include&t;&lt;linux/errno.h&gt;
macro_line|#include&t;&lt;linux/netdevice.h&gt;
macro_line|#include&t;&lt;linux/etherdevice.h&gt;
macro_line|#include&t;&lt;linux/skbuff.h&gt;
macro_line|#include&t;&lt;linux/slab.h&gt;
macro_line|#include&t;&lt;linux/timer.h&gt;
macro_line|#include&t;&lt;linux/init.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;&t;&t;/* Wireless extensions */
macro_line|#include &lt;net/iw_handler.h&gt;&t;&t;/* Wireless handlers */
multiline_comment|/* WaveLAN declarations */
macro_line|#include&t;&quot;i82586.h&quot;
macro_line|#include&t;&quot;wavelan.h&quot;
multiline_comment|/************************** DRIVER OPTIONS **************************/
multiline_comment|/*&n; * `#define&squot; or `#undef&squot; the following constant to change the behaviour&n; * of the driver...&n; */
DECL|macro|SET_PSA_CRC
macro_line|#undef SET_PSA_CRC&t;&t;/* Calculate and set the CRC on PSA (slower) */
DECL|macro|USE_PSA_CONFIG
mdefine_line|#define USE_PSA_CONFIG&t;&t;/* Use info from the PSA. */
DECL|macro|STRUCT_CHECK
macro_line|#undef STRUCT_CHECK&t;&t;/* Verify padding of structures. */
DECL|macro|EEPROM_IS_PROTECTED
macro_line|#undef EEPROM_IS_PROTECTED&t;/* doesn&squot;t seem to be necessary */
DECL|macro|MULTICAST_AVOID
mdefine_line|#define MULTICAST_AVOID&t;&t;/* Avoid extra multicast (I&squot;m sceptical). */
DECL|macro|SET_MAC_ADDRESS
macro_line|#undef SET_MAC_ADDRESS&t;&t;/* Experimental */
macro_line|#ifdef WIRELESS_EXT&t;/* If wireless extensions exist in the kernel */
multiline_comment|/* Warning:  this stuff will slow down the driver. */
DECL|macro|WIRELESS_SPY
mdefine_line|#define WIRELESS_SPY&t;&t;/* Enable spying addresses. */
DECL|macro|HISTOGRAM
macro_line|#undef HISTOGRAM&t;&t;/* Enable histogram of signal level. */
macro_line|#endif
multiline_comment|/****************************** DEBUG ******************************/
DECL|macro|DEBUG_MODULE_TRACE
macro_line|#undef DEBUG_MODULE_TRACE&t;/* module insertion/removal */
DECL|macro|DEBUG_CALLBACK_TRACE
macro_line|#undef DEBUG_CALLBACK_TRACE&t;/* calls made by Linux */
DECL|macro|DEBUG_INTERRUPT_TRACE
macro_line|#undef DEBUG_INTERRUPT_TRACE&t;/* calls to handler */
DECL|macro|DEBUG_INTERRUPT_INFO
macro_line|#undef DEBUG_INTERRUPT_INFO&t;/* type of interrupt and so on */
DECL|macro|DEBUG_INTERRUPT_ERROR
mdefine_line|#define DEBUG_INTERRUPT_ERROR&t;/* problems */
DECL|macro|DEBUG_CONFIG_TRACE
macro_line|#undef DEBUG_CONFIG_TRACE&t;/* Trace the config functions. */
DECL|macro|DEBUG_CONFIG_INFO
macro_line|#undef DEBUG_CONFIG_INFO&t;/* what&squot;s going on */
DECL|macro|DEBUG_CONFIG_ERROR
mdefine_line|#define DEBUG_CONFIG_ERROR&t;/* errors on configuration */
DECL|macro|DEBUG_TX_TRACE
macro_line|#undef DEBUG_TX_TRACE&t;&t;/* transmission calls */
DECL|macro|DEBUG_TX_INFO
macro_line|#undef DEBUG_TX_INFO&t;&t;/* header of the transmitted packet */
DECL|macro|DEBUG_TX_FAIL
macro_line|#undef DEBUG_TX_FAIL&t;&t;/* Normal failure conditions */
DECL|macro|DEBUG_TX_ERROR
mdefine_line|#define DEBUG_TX_ERROR&t;&t;/* Unexpected conditions */
DECL|macro|DEBUG_RX_TRACE
macro_line|#undef DEBUG_RX_TRACE&t;&t;/* transmission calls */
DECL|macro|DEBUG_RX_INFO
macro_line|#undef DEBUG_RX_INFO&t;&t;/* header of the received packet */
DECL|macro|DEBUG_RX_FAIL
macro_line|#undef DEBUG_RX_FAIL&t;&t;/* Normal failure conditions */
DECL|macro|DEBUG_RX_ERROR
mdefine_line|#define DEBUG_RX_ERROR&t;&t;/* Unexpected conditions */
DECL|macro|DEBUG_PACKET_DUMP
macro_line|#undef DEBUG_PACKET_DUMP&t;/* Dump packet on the screen if defined to 32. */
DECL|macro|DEBUG_IOCTL_TRACE
macro_line|#undef DEBUG_IOCTL_TRACE&t;/* misc. call by Linux */
DECL|macro|DEBUG_IOCTL_INFO
macro_line|#undef DEBUG_IOCTL_INFO&t;&t;/* various debugging info */
DECL|macro|DEBUG_IOCTL_ERROR
mdefine_line|#define DEBUG_IOCTL_ERROR&t;/* what&squot;s going wrong */
DECL|macro|DEBUG_BASIC_SHOW
mdefine_line|#define DEBUG_BASIC_SHOW&t;/* Show basic startup info. */
DECL|macro|DEBUG_VERSION_SHOW
macro_line|#undef DEBUG_VERSION_SHOW&t;/* Print version info. */
DECL|macro|DEBUG_PSA_SHOW
macro_line|#undef DEBUG_PSA_SHOW&t;&t;/* Dump PSA to screen. */
DECL|macro|DEBUG_MMC_SHOW
macro_line|#undef DEBUG_MMC_SHOW&t;&t;/* Dump mmc to screen. */
DECL|macro|DEBUG_SHOW_UNUSED
macro_line|#undef DEBUG_SHOW_UNUSED&t;/* Show unused fields too. */
DECL|macro|DEBUG_I82586_SHOW
macro_line|#undef DEBUG_I82586_SHOW&t;/* Show i82586 status. */
DECL|macro|DEBUG_DEVICE_SHOW
macro_line|#undef DEBUG_DEVICE_SHOW&t;/* Show device parameters. */
multiline_comment|/************************ CONSTANTS &amp; MACROS ************************/
macro_line|#ifdef DEBUG_VERSION_SHOW
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;wavelan.c : v24 (SMP + wireless extensions) 11/12/01&bslash;n&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/* Watchdog temporisation */
DECL|macro|WATCHDOG_JIFFIES
mdefine_line|#define&t;WATCHDOG_JIFFIES&t;(512*HZ/100)
multiline_comment|/* Macro to get the number of elements in an array */
DECL|macro|NELS
mdefine_line|#define&t;NELS(a)&t;&t;&t;&t;(sizeof(a) / sizeof(a[0]))
multiline_comment|/* ------------------------ PRIVATE IOCTL ------------------------ */
DECL|macro|SIOCSIPQTHR
mdefine_line|#define SIOCSIPQTHR&t;SIOCIWFIRSTPRIV&t;&t;/* Set quality threshold */
DECL|macro|SIOCGIPQTHR
mdefine_line|#define SIOCGIPQTHR&t;SIOCIWFIRSTPRIV + 1&t;/* Get quality threshold */
DECL|macro|SIOCSIPHISTO
mdefine_line|#define SIOCSIPHISTO&t;SIOCIWFIRSTPRIV + 2&t;/* Set histogram ranges */
DECL|macro|SIOCGIPHISTO
mdefine_line|#define SIOCGIPHISTO&t;SIOCIWFIRSTPRIV + 3&t;/* Get histogram values */
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
multiline_comment|/*&n; * Static specific data for the interface.&n; *&n; * For each network interface, Linux keeps data in two structures:  &quot;device&quot;&n; * keeps the generic data (same format for everybody) and &quot;net_local&quot; keeps&n; * additional specific data.&n; * Note that some of this specific data is in fact generic (en_stats, for&n; * example).&n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|next
id|net_local
op_star
id|next
suffix:semicolon
multiline_comment|/* linked list of the devices */
DECL|member|dev
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* reverse link */
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
multiline_comment|/* Serialize access to the hardware (SMP) */
DECL|member|stats
id|en_stats
id|stats
suffix:semicolon
multiline_comment|/* Ethernet interface statistics */
DECL|member|nresets
r_int
id|nresets
suffix:semicolon
multiline_comment|/* number of hardware resets */
DECL|member|reconfig_82586
id|u_char
id|reconfig_82586
suffix:semicolon
multiline_comment|/* We need to reconfigure the controller. */
DECL|member|promiscuous
id|u_char
id|promiscuous
suffix:semicolon
multiline_comment|/* promiscuous mode */
DECL|member|mc_count
r_int
id|mc_count
suffix:semicolon
multiline_comment|/* number of multicast addresses */
DECL|member|hacr
id|u_short
id|hacr
suffix:semicolon
multiline_comment|/* current host interface state */
DECL|member|tx_n_in_use
r_int
id|tx_n_in_use
suffix:semicolon
DECL|member|rx_head
id|u_short
id|rx_head
suffix:semicolon
DECL|member|rx_last
id|u_short
id|rx_last
suffix:semicolon
DECL|member|tx_first_free
id|u_short
id|tx_first_free
suffix:semicolon
DECL|member|tx_first_in_use
id|u_short
id|tx_first_in_use
suffix:semicolon
macro_line|#ifdef WIRELESS_EXT
DECL|member|wstats
id|iw_stats
id|wstats
suffix:semicolon
multiline_comment|/* Wireless-specific statistics */
macro_line|#endif
macro_line|#ifdef WIRELESS_SPY
DECL|member|spy_number
r_int
id|spy_number
suffix:semicolon
multiline_comment|/* number of addresses to spy */
DECL|member|spy_address
id|mac_addr
id|spy_address
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
multiline_comment|/* the addresses to spy */
DECL|member|spy_stat
id|iw_qual
id|spy_stat
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
multiline_comment|/* statistics gathered */
macro_line|#endif&t;/* WIRELESS_SPY */
macro_line|#ifdef HISTOGRAM
DECL|member|his_number
r_int
id|his_number
suffix:semicolon
multiline_comment|/* number of intervals */
DECL|member|his_range
id|u_char
id|his_range
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* boundaries of interval ]n-1; n] */
DECL|member|his_sum
id|u_long
id|his_sum
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* sum in interval */
macro_line|#endif&t;/* HISTOGRAM */
)brace
suffix:semicolon
multiline_comment|/**************************** PROTOTYPES ****************************/
multiline_comment|/* ----------------------- MISC. SUBROUTINES ------------------------ */
r_static
r_inline
r_void
id|wv_splhi
c_func
(paren
id|net_local
op_star
comma
multiline_comment|/* Disable interrupts, lock driver */
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* flags */
r_static
r_inline
r_void
id|wv_splx
c_func
(paren
id|net_local
op_star
comma
multiline_comment|/* Enable interrupts, unlock driver */
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* flags */
r_static
id|u_char
id|wv_irq_to_psa
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_int
id|wv_psa_to_irq
c_func
(paren
id|u_char
)paren
suffix:semicolon
multiline_comment|/* ------------------- HOST ADAPTER SUBROUTINES ------------------- */
r_static
r_inline
id|u_short
multiline_comment|/* data */
id|hasr_read
c_func
(paren
id|u_long
)paren
suffix:semicolon
multiline_comment|/* Read the host interface:  base address */
r_static
r_inline
r_void
id|hacr_write
c_func
(paren
id|u_long
comma
multiline_comment|/* Write to host interface:  base address */
id|u_short
)paren
comma
multiline_comment|/* data */
id|hacr_write_slow
c_func
(paren
id|u_long
comma
id|u_short
)paren
comma
id|set_chan_attn
c_func
(paren
id|u_long
comma
multiline_comment|/* ioaddr */
id|u_short
)paren
comma
multiline_comment|/* hacr   */
id|wv_hacr_reset
c_func
(paren
id|u_long
)paren
comma
multiline_comment|/* ioaddr */
id|wv_16_off
c_func
(paren
id|u_long
comma
multiline_comment|/* ioaddr */
id|u_short
)paren
comma
multiline_comment|/* hacr   */
id|wv_16_on
c_func
(paren
id|u_long
comma
multiline_comment|/* ioaddr */
id|u_short
)paren
comma
multiline_comment|/* hacr   */
id|wv_ints_off
c_func
(paren
id|device
op_star
)paren
comma
id|wv_ints_on
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* ----------------- MODEM MANAGEMENT SUBROUTINES ----------------- */
r_static
r_void
id|psa_read
c_func
(paren
id|u_long
comma
multiline_comment|/* Read the Parameter Storage Area. */
id|u_short
comma
multiline_comment|/* hacr */
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
id|u_long
comma
multiline_comment|/* Write to the PSA. */
id|u_short
comma
multiline_comment|/* hacr */
r_int
comma
multiline_comment|/* offset in PSA */
id|u_char
op_star
comma
multiline_comment|/* buffer in memory */
r_int
)paren
suffix:semicolon
multiline_comment|/* length of buffer */
r_static
r_inline
r_void
id|mmc_out
c_func
(paren
id|u_long
comma
multiline_comment|/* Write 1 byte to the Modem Manag Control. */
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
multiline_comment|/* Write n bytes to the MMC. */
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
multiline_comment|/* Read 1 byte from the MMC. */
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
multiline_comment|/* Read n bytes from the MMC. */
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
multiline_comment|/* Wait for frequency EEPROM:  base address */
r_int
comma
multiline_comment|/* base delay to wait for */
r_int
)paren
suffix:semicolon
multiline_comment|/* time to wait */
r_static
r_void
id|fee_read
c_func
(paren
id|u_long
comma
multiline_comment|/* Read the frequency EEPROM:  base address */
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
multiline_comment|/* ---------------------- I82586 SUBROUTINES ----------------------- */
r_static
multiline_comment|/*inline*/
r_void
id|obram_read
c_func
(paren
id|u_long
comma
multiline_comment|/* ioaddr */
id|u_short
comma
multiline_comment|/* o */
id|u_char
op_star
comma
multiline_comment|/* b */
r_int
)paren
suffix:semicolon
multiline_comment|/* n */
r_static
r_inline
r_void
id|obram_write
c_func
(paren
id|u_long
comma
multiline_comment|/* ioaddr */
id|u_short
comma
multiline_comment|/* o */
id|u_char
op_star
comma
multiline_comment|/* b */
r_int
)paren
suffix:semicolon
multiline_comment|/* n */
r_static
r_void
id|wv_ack
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|wv_synchronous_cmd
c_func
(paren
id|device
op_star
comma
r_const
r_char
op_star
)paren
comma
id|wv_config_complete
c_func
(paren
id|device
op_star
comma
id|u_long
comma
id|net_local
op_star
)paren
suffix:semicolon
r_static
r_int
id|wv_complete
c_func
(paren
id|device
op_star
comma
id|u_long
comma
id|net_local
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|wv_82586_reconfig
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* ------------------- DEBUG &amp; INFO SUBROUTINES ------------------- */
macro_line|#ifdef DEBUG_I82586_SHOW
r_static
r_void
id|wv_scb_show
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
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
r_static
r_void
id|wavelan_set_multicast_list
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* ----------------------- PACKET RECEPTION ----------------------- */
r_static
r_inline
r_void
id|wv_packet_read
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Read a packet from a frame. */
id|u_short
comma
r_int
)paren
comma
id|wv_receive
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Read all packets waiting. */
multiline_comment|/* --------------------- PACKET TRANSMISSION --------------------- */
r_static
r_inline
r_int
id|wv_packet_write
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Write a packet to the Tx buffer. */
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
multiline_comment|/* Send a packet. */
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
comma
multiline_comment|/* Initialize the modem. */
id|wv_ru_start
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Start the i82586 receiver unit. */
id|wv_cu_start
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Start the i82586 command unit. */
id|wv_82586_start
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Start the i82586. */
r_static
r_void
id|wv_82586_config
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Configure the i82586. */
r_static
r_inline
r_void
id|wv_82586_stop
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
r_static
r_int
id|wv_hw_reset
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Reset the WaveLAN hardware. */
id|wv_check_ioaddr
c_func
(paren
id|u_long
comma
multiline_comment|/* ioaddr */
id|u_char
op_star
)paren
suffix:semicolon
multiline_comment|/* mac address (read) */
multiline_comment|/* ---------------------- INTERRUPT HANDLING ---------------------- */
r_static
r_void
id|wavelan_interrupt
c_func
(paren
r_int
comma
multiline_comment|/* interrupt handler */
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
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* transmission watchdog */
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
multiline_comment|/* Open the device. */
id|wavelan_close
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Close the device. */
id|wavelan_config
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Configure one device. */
r_extern
r_int
id|wavelan_probe
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* See Space.c. */
multiline_comment|/**************************** VARIABLES ****************************/
multiline_comment|/*&n; * This is the root of the linked list of WaveLAN drivers&n; * It is use to verify that we don&squot;t reuse the same base address&n; * for two different drivers and to clean up when removing the module.&n; */
DECL|variable|wavelan_list
r_static
id|net_local
op_star
id|wavelan_list
op_assign
(paren
id|net_local
op_star
)paren
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * This table is used to translate the PSA value to IRQ number&n; * and vice versa.&n; */
DECL|variable|irqvals
r_static
id|u_char
id|irqvals
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0
comma
l_int|0x08
comma
l_int|0
comma
l_int|0
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0x40
comma
l_int|0
comma
l_int|0
comma
l_int|0x80
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Table of the available I/O addresses (base addresses) for WaveLAN&n; */
DECL|variable|iobase
r_static
r_int
r_int
id|iobase
(braket
)braket
op_assign
(brace
macro_line|#if&t;0
multiline_comment|/* Leave out 0x3C0 for now -- seems to clash with some video&n;   * controllers.&n;   * Leave out the others too -- we will always use 0x390 and leave&n;   * 0x300 for the Ethernet device.&n;   * Jean II:  0x3E0 is fine as well.&n;   */
l_int|0x300
comma
l_int|0x390
comma
l_int|0x3E0
comma
l_int|0x3C0
macro_line|#endif&t;/* 0 */
l_int|0x390
comma
l_int|0x3E0
)brace
suffix:semicolon
macro_line|#ifdef&t;MODULE
multiline_comment|/* Parameters set by insmod */
DECL|variable|io
r_static
r_int
id|io
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|name
r_static
r_char
id|name
(braket
l_int|4
)braket
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-4i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;1-4i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|name
comma
l_string|&quot;1-4c&quot;
id|__MODULE_STRING
c_func
(paren
id|IFNAMSIZ
)paren
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;WaveLAN I/O base address(es),required&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;WaveLAN IRQ number(s)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|name
comma
l_string|&quot;WaveLAN interface neme(s)&quot;
)paren
suffix:semicolon
macro_line|#endif&t;/* MODULE */
macro_line|#endif&t;/* WAVELAN_P_H */
eof
