macro_line|#ifndef _IF_LMC_LINUXVER_
DECL|macro|_IF_LMC_LINUXVER_
mdefine_line|#define _IF_LMC_LINUXVER_
multiline_comment|/*&n;  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)&n;  * All rights reserved.  www.lanmedia.com&n;  *&n;  * This code is written by:&n;  * Andrew Stanley-Jones (asj@cban.com)&n;  * Rob Braun (bbraun@vix.com),&n;  * Michael Graff (explorer@vix.com) and&n;  * Matt Thomas (matt@3am-software.com).&n;  *&n;  * This software may be used and distributed according to the terms&n;  * of the GNU Public License version 2, incorporated herein by reference.&n;  */
multiline_comment|/*&n;  * This file defines and controls all linux version&n;  * differences.&n;  *&n;  * This is being done to keep 1 central location where all linux&n;  * version differences can be kept and maintained.  as this code was&n;  * found version issues where pepered throughout the source code and&n;  * made the souce code not only hard to read but version problems hard&n;  * to track down.  If I&squot;m overiding a function/etc with something in&n;  * this file it will be prefixed by &quot;LMC_&quot; which will mean look&n;  * here for the the version dependant change that&squot;s been done.&n;  *&n;  */
macro_line|#if LINUX_VERSION_CODE &lt; 0x20363
DECL|macro|net_device
mdefine_line|#define net_device device
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20363
DECL|macro|LMC_XMITTER_BUSY
mdefine_line|#define LMC_XMITTER_BUSY(x) (x)-&gt;tbusy = 1
DECL|macro|LMC_XMITTER_FREE
mdefine_line|#define LMC_XMITTER_FREE(x) (x)-&gt;tbusy = 0
DECL|macro|LMC_XMITTER_INIT
mdefine_line|#define LMC_XMITTER_INIT(x) (x)-&gt;tbusy = 0
macro_line|#else
DECL|macro|LMC_XMITTER_BUSY
mdefine_line|#define LMC_XMITTER_BUSY(x) netif_stop_queue(x)
DECL|macro|LMC_XMITTER_FREE
mdefine_line|#define LMC_XMITTER_FREE(x) netif_wake_queue(x)
DECL|macro|LMC_XMITTER_INIT
mdefine_line|#define LMC_XMITTER_INIT(x) netif_start_queue(x)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20100
singleline_comment|//typedef unsigned int u_int32_t;
DECL|macro|LMC_SETUP_20_DEV
mdefine_line|#define  LMC_SETUP_20_DEV {&bslash;&n;                             int indx; &bslash;&n;                             for (indx = 0; indx &lt; DEV_NUMBUFFS; indx++) &bslash;&n;                                skb_queue_head_init (&amp;dev-&gt;buffs[indx]); &bslash;&n;                          } &bslash;&n;                          dev-&gt;family = AF_INET; &bslash;&n;                          dev-&gt;pa_addr = 0; &bslash;&n;                          dev-&gt;pa_brdaddr = 0; &bslash;&n;                          dev-&gt;pa_mask = 0xFCFFFFFF; &bslash;&n;                          dev-&gt;pa_alen = 4;&t;&t;/* IP addr.  sizeof(u32) */
macro_line|#else
DECL|macro|LMC_SETUP_20_DEV
mdefine_line|#define LMC_SETUP_20_DEV
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20155 /* basically 2.2 plus */
DECL|macro|LMC_DEV_KFREE_SKB
mdefine_line|#define LMC_DEV_KFREE_SKB(skb) dev_kfree_skb((skb), FREE_WRITE)
DECL|macro|LMC_PCI_PRESENT
mdefine_line|#define LMC_PCI_PRESENT() pcibios_present()
macro_line|#else /* Mostly 2.0 kernels */
DECL|macro|LMC_DEV_KFREE_SKB
mdefine_line|#define LMC_DEV_KFREE_SKB(skb) dev_kfree_skb(skb)
DECL|macro|LMC_PCI_PRESENT
mdefine_line|#define LMC_PCI_PRESENT() pci_present()
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20200
macro_line|#else
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20100
DECL|macro|LMC_SKB_FREE
mdefine_line|#define LMC_SKB_FREE(skb, val) (skb-&gt;free = val)
macro_line|#else
DECL|macro|LMC_SKB_FREE
mdefine_line|#define LMC_SKB_FREE(skb, val)
macro_line|#endif
macro_line|#if (LINUX_VERSION_CODE &gt;= 0x20200)
DECL|macro|LMC_SPIN_FLAGS
mdefine_line|#define LMC_SPIN_FLAGS                unsigned long flags;
DECL|macro|LMC_SPIN_LOCK_INIT
mdefine_line|#define LMC_SPIN_LOCK_INIT(x)         spin_lock_init(&amp;(x)-&gt;lmc_lock);
DECL|macro|LMC_SPIN_UNLOCK
mdefine_line|#define LMC_SPIN_UNLOCK(x)            ((x)-&gt;lmc_lock = SPIN_LOCK_UNLOCKED)
DECL|macro|LMC_SPIN_LOCK_IRQSAVE
mdefine_line|#define LMC_SPIN_LOCK_IRQSAVE(x)      spin_lock_irqsave (&amp;(x)-&gt;lmc_lock, flags);
DECL|macro|LMC_SPIN_UNLOCK_IRQRESTORE
mdefine_line|#define LMC_SPIN_UNLOCK_IRQRESTORE(x) spin_unlock_irqrestore (&amp;(x)-&gt;lmc_lock, flags);
macro_line|#else
DECL|macro|LMC_SPIN_FLAGS
mdefine_line|#define LMC_SPIN_FLAGS
DECL|macro|LMC_SPIN_LOCK_INIT
mdefine_line|#define LMC_SPIN_LOCK_INIT(x)
DECL|macro|LMC_SPIN_UNLOCK
mdefine_line|#define LMC_SPIN_UNLOCK(x)
DECL|macro|LMC_SPIN_LOCK_IRQSAVE
mdefine_line|#define LMC_SPIN_LOCK_IRQSAVE(x)
DECL|macro|LMC_SPIN_UNLOCK_IRQRESTORE
mdefine_line|#define LMC_SPIN_UNLOCK_IRQRESTORE(x)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20100
DECL|macro|LMC_COPY_FROM_USER
mdefine_line|#define LMC_COPY_FROM_USER(x, y, z) if(copy_from_user ((x), (y), (z))) return -EFAULT
DECL|macro|LMC_COPY_TO_USER
mdefine_line|#define LMC_COPY_TO_USER(x, y, z) if(copy_to_user ((x), (y), (z))) return -EFAULT
macro_line|#else
DECL|macro|LMC_COPY_FROM_USER
mdefine_line|#define LMC_COPY_FROM_USER(x, y, z) if(verify_area(VERIFY_READ, (y), (z))) &bslash;&n;&t;&t;&t;               return -EFAULT; &bslash;&n;                                    memcpy_fromfs ((x), (y), (z))
DECL|macro|LMC_COPY_TO_USER
mdefine_line|#define LMC_COPY_TO_USER(x, y, z)   if(verify_area(VERIFY_WRITE, (x), (z))) &bslash;&n;&t;                               return -EFAULT; &bslash;&n;                                    memcpy_tofs ((x), (y), (z))
macro_line|#endif
macro_line|#endif
eof
