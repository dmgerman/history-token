multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1999 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Defines, definitions and includes which are heavily dependant&n;*                on O/S, host, compiler, etc. This file is tailored for:&n;*                 Linux v2.0.0 and later&n;*                 Gnu gcc c2.7.2&n;*                 80x86 architecture&n;*&n;*******************************************************************************/
macro_line|#ifndef I2OS_H    /* To prevent multiple includes */
DECL|macro|I2OS_H
mdefine_line|#define I2OS_H 1
DECL|macro|VERSION
mdefine_line|#define VERSION(ver,rel,seq) (((ver)&lt;&lt;16) | ((rel)&lt;&lt;8) | (seq))
singleline_comment|//-------------------------------------------------
singleline_comment|// Required Includes
singleline_comment|//-------------------------------------------------
macro_line|#include &quot;ip2types.h&quot;
macro_line|#include &lt;asm/io.h&gt;  /* For inb, etc */
macro_line|#include &lt;linux/version.h&gt;
singleline_comment|//------------------------------------
singleline_comment|// Defines for I/O instructions:
singleline_comment|//------------------------------------
DECL|macro|INB
mdefine_line|#define INB(port)                inb(port)
DECL|macro|OUTB
mdefine_line|#define OUTB(port,value)         outb((value),(port))
DECL|macro|INW
mdefine_line|#define INW(port)                inw(port)
DECL|macro|OUTW
mdefine_line|#define OUTW(port,value)         outw((value),(port))
DECL|macro|OUTSW
mdefine_line|#define OUTSW(port,addr,count)   outsw((port),(addr),(((count)+1)/2))
DECL|macro|OUTSB
mdefine_line|#define OUTSB(port,addr,count)   outsb((port),(addr),(((count)+1))&amp;-2)
DECL|macro|INSW
mdefine_line|#define INSW(port,addr,count)    insw((port),(addr),(((count)+1)/2))
DECL|macro|INSB
mdefine_line|#define INSB(port,addr,count)    insb((port),(addr),(((count)+1))&amp;-2)
singleline_comment|//--------------------------------------------
singleline_comment|// Interrupt control
singleline_comment|//--------------------------------------------
macro_line|#if LINUX_VERSION_CODE &lt; 0x00020100
DECL|typedef|spinlock_t
r_typedef
r_int
id|spinlock_t
suffix:semicolon
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init() 
DECL|macro|spin_lock
mdefine_line|#define spin_lock(a)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(a)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(a,b)&t;&t;&t;{save_flags((b));cli();}
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(a,b)&t;&t;{restore_flags((b));}
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(a,b)&t;&t;&t;spin_lock_irqsave(a,b)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(a,b)&t;spin_unlock_irqrestore(a,b)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(a,b)&t;&t;&t;spin_lock_irqsave(a,b)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(a,b)&t;&t;spin_unlock_irqrestore(a,b)
macro_line|#endif
singleline_comment|//#define SAVE_AND_DISABLE_INTS(a,b)&t;spin_lock_irqsave(a,b)
singleline_comment|//#define RESTORE_INTS(a,b)         &t;spin_unlock_irqrestore(a,b)
DECL|macro|LOCK_INIT
mdefine_line|#define LOCK_INIT(a)&t;rwlock_init(a)
DECL|macro|SAVE_AND_DISABLE_INTS
mdefine_line|#define SAVE_AND_DISABLE_INTS(a,b) { &bslash;&n;&t;/* printk(&quot;get_lock: 0x%x,%4d,%s&bslash;n&quot;,(int)a,__LINE__,__FILE__);*/ &bslash;&n;&t;spin_lock_irqsave(a,b); &bslash;&n;}
DECL|macro|RESTORE_INTS
mdefine_line|#define RESTORE_INTS(a,b) { &bslash;&n;&t;/* printk(&quot;rel_lock: 0x%x,%4d,%s&bslash;n&quot;,(int)a,__LINE__,__FILE__);*/ &bslash;&n;&t;spin_unlock_irqrestore(a,b); &bslash;&n;}
DECL|macro|READ_LOCK_IRQSAVE
mdefine_line|#define READ_LOCK_IRQSAVE(a,b) { &bslash;&n;&t;/* printk(&quot;get_read_lock: 0x%x,%4d,%s&bslash;n&quot;,(int)a,__LINE__,__FILE__);*/ &bslash;&n;&t;read_lock_irqsave(a,b); &bslash;&n;}
DECL|macro|READ_UNLOCK_IRQRESTORE
mdefine_line|#define READ_UNLOCK_IRQRESTORE(a,b) { &bslash;&n;&t;/* printk(&quot;rel_read_lock: 0x%x,%4d,%s&bslash;n&quot;,(int)a,__LINE__,__FILE__);*/ &bslash;&n;&t;read_unlock_irqrestore(a,b); &bslash;&n;}
DECL|macro|WRITE_LOCK_IRQSAVE
mdefine_line|#define WRITE_LOCK_IRQSAVE(a,b) { &bslash;&n;&t;/* printk(&quot;get_write_lock: 0x%x,%4d,%s&bslash;n&quot;,(int)a,__LINE__,__FILE__);*/ &bslash;&n;&t;write_lock_irqsave(a,b); &bslash;&n;}
DECL|macro|WRITE_UNLOCK_IRQRESTORE
mdefine_line|#define WRITE_UNLOCK_IRQRESTORE(a,b) { &bslash;&n;&t;/* printk(&quot;rel_write_lock: 0x%x,%4d,%s&bslash;n&quot;,(int)a,__LINE__,__FILE__);*/ &bslash;&n;&t;write_unlock_irqrestore(a,b); &bslash;&n;}
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Hardware-delay loop
singleline_comment|//
singleline_comment|// Probably used in only one place (see i2ellis.c) but this helps keep things
singleline_comment|// together. Note we have unwound the IN instructions. On machines with a
singleline_comment|// reasonable cache, the eight instructions (1 byte each) should fit in cache
singleline_comment|// nicely, and on un-cached machines, the code-fetch would tend not to dominate.
singleline_comment|// Note that cx is shifted so that &quot;count&quot; still reflects the total number of
singleline_comment|// iterations assuming no unwinding.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//#define  DELAY1MS(port,count,label)
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Macros to switch to a new stack, saving stack pointers, and to restore the
singleline_comment|// old stack (Used, for example, in i2lib.c) &quot;heap&quot; is the address of some
singleline_comment|// buffer which will become the new stack (working down from highest address).
singleline_comment|// The two words at the two lowest addresses in this stack are for storing the
singleline_comment|// SS and SP.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//#define  TO_NEW_STACK(heap,size)
singleline_comment|//#define  TO_OLD_STACK(heap)
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Macros to save the original IRQ vectors and masks, and to patch in new ones.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//#define  SAVE_IRQ_MASKS(dest)
singleline_comment|//#define  WRITE_IRQ_MASKS(src)
singleline_comment|//#define  SAVE_IRQ_VECTOR(value,dest)
singleline_comment|//#define  WRITE_IRQ_VECTOR(value,src)
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Macro to copy data from one far pointer to another.
singleline_comment|//------------------------------------------------------------------------------
DECL|macro|I2_MOVE_DATA
mdefine_line|#define  I2_MOVE_DATA(fpSource,fpDest,count) memmove(fpDest,fpSource,count);
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Macros to issue eoi&squot;s to host interrupt control (IBM AT 8259-style).
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//#define MASTER_EOI
singleline_comment|//#define SLAVE_EOI
macro_line|#endif   /* I2OS_H */
eof
