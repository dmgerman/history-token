multiline_comment|/*&n; * Linux ARCnet driver - &quot;RIM I&quot; (entirely mem-mapped) cards&n; * &n; * Written 1994-1999 by Avery Pennarun.&n; * Written 1999-2000 by Martin Mares &lt;mj@suse.cz&gt;.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: RIM I (entirely mem-mapped) support&bslash;n&quot;
multiline_comment|/* Internal function declarations */
r_static
r_int
id|arcrimi_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|arcrimi_found
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|arcrimi_command
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|command
)paren
suffix:semicolon
r_static
r_int
id|arcrimi_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|arcrimi_setmask
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mask
)paren
suffix:semicolon
r_static
r_int
id|arcrimi_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|really_reset
)paren
suffix:semicolon
r_static
r_void
id|arcrimi_openclose
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_bool
id|open
)paren
suffix:semicolon
r_static
r_void
id|arcrimi_copy_to_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|arcrimi_copy_from_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Handy defines for ARCnet specific stuff */
multiline_comment|/* Amount of I/O memory used by the card */
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE (512)
DECL|macro|MIRROR_SIZE
mdefine_line|#define MIRROR_SIZE (BUFFER_SIZE*4)
multiline_comment|/* COM 9026 controller chip --&gt; ARCnet register addresses */
DECL|macro|_INTMASK
mdefine_line|#define _INTMASK (ioaddr+0)&t;/* writable */
DECL|macro|_STATUS
mdefine_line|#define _STATUS  (ioaddr+0)&t;/* readable */
DECL|macro|_COMMAND
mdefine_line|#define _COMMAND (ioaddr+1)&t;/* writable, returns random vals on read (?) */
DECL|macro|_RESET
mdefine_line|#define _RESET  (ioaddr+8)&t;/* software reset (on read) */
DECL|macro|_MEMDATA
mdefine_line|#define _MEMDATA  (ioaddr+12)&t;/* Data port for IO-mapped memory */
DECL|macro|_ADDR_HI
mdefine_line|#define _ADDR_HI  (ioaddr+15)&t;/* Control registers for said */
DECL|macro|_ADDR_LO
mdefine_line|#define _ADDR_LO  (ioaddr+14)
DECL|macro|_CONFIG
mdefine_line|#define _CONFIG  (ioaddr+2)&t;/* Configuration register */
DECL|macro|ASTATUS
macro_line|#undef ASTATUS
DECL|macro|ACOMMAND
macro_line|#undef ACOMMAND
DECL|macro|AINTMASK
macro_line|#undef AINTMASK
DECL|macro|ASTATUS
mdefine_line|#define ASTATUS()&t;readb(_STATUS)
DECL|macro|ACOMMAND
mdefine_line|#define ACOMMAND(cmd)&t;writeb((cmd),_COMMAND)
DECL|macro|AINTMASK
mdefine_line|#define AINTMASK(msk)&t;writeb((msk),_INTMASK)
DECL|macro|SETCONF
mdefine_line|#define SETCONF()&t;writeb(lp-&gt;config,_CONFIG)
multiline_comment|/*&n; * We cannot probe for a RIM I card; one reason is I don&squot;t know how to reset&n; * them.  In fact, we can&squot;t even get their node ID automatically.  So, we&n; * need to be passed a specific shmem address, IRQ, and node ID.&n; */
DECL|function|arcrimi_probe
r_static
r_int
id|__init
id|arcrimi_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|BUGLVL
c_func
(paren
id|D_NORMAL
)paren
id|printk
c_func
(paren
id|VERSION
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_NORMAL
)paren
id|printk
c_func
(paren
l_string|&quot;E-mail me if you actually test the RIM I driver, please!&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Given: node %02Xh, shmem %lXh, irq %d&bslash;n&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_le
l_int|0
op_logical_or
id|dev-&gt;irq
op_le
l_int|0
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;No autoprobe for RIM I; you &quot;
l_string|&quot;must specify the shmem and irq!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_mem_region
c_func
(paren
id|dev-&gt;mem_start
comma
id|BUFFER_SIZE
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Card memory already allocated&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;You need to specify your card&squot;s station &quot;
l_string|&quot;ID!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|arcrimi_found
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the struct net_device associated with this card.  Called after&n; * probing succeeds.&n; */
DECL|function|arcrimi_found
r_static
r_int
id|__init
id|arcrimi_found
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
id|u_long
id|first_mirror
comma
id|last_mirror
comma
id|shmem
suffix:semicolon
r_int
id|mirror_size
suffix:semicolon
multiline_comment|/* reserve the irq */
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|arcnet_interrupt
comma
l_int|0
comma
l_string|&quot;arcnet (RIM I)&quot;
comma
id|dev
)paren
)paren
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Can&squot;t get IRQ %d!&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|shmem
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|isa_writeb
c_func
(paren
id|TESTvalue
comma
id|shmem
)paren
suffix:semicolon
id|isa_writeb
c_func
(paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|shmem
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* actually the node ID */
multiline_comment|/* find the real shared memory start/end points, including mirrors */
multiline_comment|/* guess the actual size of one &quot;memory mirror&quot; - the number of&n;&t; * bytes between copies of the shared memory.  On most cards, it&squot;s&n;&t; * 2k (or there are no mirrors at all) but on some, it&squot;s 4k.&n;&t; */
id|mirror_size
op_assign
id|MIRROR_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|isa_readb
c_func
(paren
id|shmem
)paren
op_eq
id|TESTvalue
op_logical_and
id|isa_readb
c_func
(paren
id|shmem
op_minus
id|mirror_size
)paren
op_ne
id|TESTvalue
op_logical_and
id|isa_readb
c_func
(paren
id|shmem
op_minus
l_int|2
op_star
id|mirror_size
)paren
op_eq
id|TESTvalue
)paren
id|mirror_size
op_mul_assign
l_int|2
suffix:semicolon
id|first_mirror
op_assign
id|last_mirror
op_assign
id|shmem
suffix:semicolon
r_while
c_loop
(paren
id|isa_readb
c_func
(paren
id|first_mirror
)paren
op_eq
id|TESTvalue
)paren
id|first_mirror
op_sub_assign
id|mirror_size
suffix:semicolon
id|first_mirror
op_add_assign
id|mirror_size
suffix:semicolon
r_while
c_loop
(paren
id|isa_readb
c_func
(paren
id|last_mirror
)paren
op_eq
id|TESTvalue
)paren
id|last_mirror
op_add_assign
id|mirror_size
suffix:semicolon
id|last_mirror
op_sub_assign
id|mirror_size
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|first_mirror
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|last_mirror
op_plus
id|MIRROR_SIZE
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|BUFFER_SIZE
op_star
l_int|0
suffix:semicolon
id|dev-&gt;rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
id|BUFFER_SIZE
op_star
l_int|2
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* initialize the rest of the device structure. */
id|lp
op_assign
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Can&squot;t allocate device data!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_free_irq
suffix:semicolon
)brace
id|lp-&gt;card_name
op_assign
l_string|&quot;RIM I&quot;
suffix:semicolon
id|lp-&gt;hw.command
op_assign
id|arcrimi_command
suffix:semicolon
id|lp-&gt;hw.status
op_assign
id|arcrimi_status
suffix:semicolon
id|lp-&gt;hw.intmask
op_assign
id|arcrimi_setmask
suffix:semicolon
id|lp-&gt;hw.reset
op_assign
id|arcrimi_reset
suffix:semicolon
id|lp-&gt;hw.open_close
op_assign
id|arcrimi_openclose
suffix:semicolon
id|lp-&gt;hw.copy_to_card
op_assign
id|arcrimi_copy_to_card
suffix:semicolon
id|lp-&gt;hw.copy_from_card
op_assign
id|arcrimi_copy_from_card
suffix:semicolon
id|lp-&gt;mem_start
op_assign
id|ioremap
c_func
(paren
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
id|dev-&gt;mem_start
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;mem_start
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Can&squot;t remap device memory!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_free_dev_priv
suffix:semicolon
)brace
multiline_comment|/* Fill in the fields of the device structure with generic&n;&t; * values.&n;&t; */
id|arcdev_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* get and check the station ID from offset 1 in shmem */
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|readb
c_func
(paren
id|lp-&gt;mem_start
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* reserve the memory region - guaranteed to work by check_region */
id|request_mem_region
c_func
(paren
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
id|dev-&gt;mem_start
op_plus
l_int|1
comma
l_string|&quot;arcnet (90xx)&quot;
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;ARCnet RIM I: station %02Xh found at IRQ %d, &quot;
l_string|&quot;ShMem %lXh (%ld*%d bytes).&bslash;n&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;irq
comma
id|dev-&gt;mem_start
comma
(paren
id|dev-&gt;mem_end
op_minus
id|dev-&gt;mem_start
op_plus
l_int|1
)paren
op_div
id|mirror_size
comma
id|mirror_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_free_dev_priv
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a hardware reset on the card, and set up necessary registers.&n; *&n; * This should be called as little as possible, because it disrupts the&n; * token on the network (causes a RECON) and requires a significant delay.&n; *&n; * However, it does make sure the card is in a defined state.&n; */
DECL|function|arcrimi_reset
r_static
r_int
id|arcrimi_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|really_reset
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_void
op_star
id|ioaddr
op_assign
id|lp-&gt;mem_start
op_plus
l_int|0x800
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_INIT
comma
l_string|&quot;Resetting %s (status=%02Xh)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ASTATUS
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|really_reset
)paren
(brace
id|writeb
c_func
(paren
id|TESTvalue
comma
id|ioaddr
op_minus
l_int|0x800
)paren
suffix:semicolon
multiline_comment|/* fake reset */
r_return
l_int|0
suffix:semicolon
)brace
id|ACOMMAND
c_func
(paren
id|CFLAGScmd
op_or
id|RESETclear
)paren
suffix:semicolon
multiline_comment|/* clear flags &amp; end reset */
id|ACOMMAND
c_func
(paren
id|CFLAGScmd
op_or
id|CONFIGclear
)paren
suffix:semicolon
multiline_comment|/* enable extended (512-byte) packets */
id|ACOMMAND
c_func
(paren
id|CONFIGcmd
op_or
id|EXTconf
)paren
suffix:semicolon
multiline_comment|/* done!  return success. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|arcrimi_openclose
r_static
r_void
id|arcrimi_openclose
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|open
)paren
(brace
r_if
c_cond
(paren
id|open
)paren
id|MOD_INC_USE_COUNT
suffix:semicolon
r_else
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|arcrimi_setmask
r_static
r_void
id|arcrimi_setmask
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_void
op_star
id|ioaddr
op_assign
id|lp-&gt;mem_start
op_plus
l_int|0x800
suffix:semicolon
id|AINTMASK
c_func
(paren
id|mask
)paren
suffix:semicolon
)brace
DECL|function|arcrimi_status
r_static
r_int
id|arcrimi_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_void
op_star
id|ioaddr
op_assign
id|lp-&gt;mem_start
op_plus
l_int|0x800
suffix:semicolon
r_return
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|arcrimi_command
r_static
r_void
id|arcrimi_command
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|cmd
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_void
op_star
id|ioaddr
op_assign
id|lp-&gt;mem_start
op_plus
l_int|0x800
suffix:semicolon
id|ACOMMAND
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|arcrimi_copy_to_card
r_static
r_void
id|arcrimi_copy_to_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_void
op_star
id|memaddr
op_assign
id|lp-&gt;mem_start
op_plus
l_int|0x800
op_plus
id|bufnum
op_star
l_int|512
op_plus
id|offset
suffix:semicolon
id|TIME
c_func
(paren
l_string|&quot;memcpy_toio&quot;
comma
id|count
comma
id|memcpy_toio
c_func
(paren
id|memaddr
comma
id|buf
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|arcrimi_copy_from_card
r_static
r_void
id|arcrimi_copy_from_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_void
op_star
id|memaddr
op_assign
id|lp-&gt;mem_start
op_plus
l_int|0x800
op_plus
id|bufnum
op_star
l_int|512
op_plus
id|offset
suffix:semicolon
id|TIME
c_func
(paren
l_string|&quot;memcpy_fromio&quot;
comma
id|count
comma
id|memcpy_fromio
c_func
(paren
id|buf
comma
id|memaddr
comma
id|count
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|my_dev
r_static
r_struct
id|net_device
op_star
id|my_dev
suffix:semicolon
multiline_comment|/* Module parameters */
DECL|variable|node
r_static
r_int
id|node
op_assign
l_int|0
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* &lt;--- EDIT THESE LINES FOR YOUR CONFIGURATION */
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* or use the insmod io= irq= shmem= options */
DECL|variable|device
r_static
r_char
op_star
id|device
suffix:semicolon
multiline_comment|/* use eg. device=&quot;arc1&quot; to change name */
id|MODULE_PARM
c_func
(paren
id|node
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|device
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
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
suffix:semicolon
id|dev
op_assign
id|dev_alloc
c_func
(paren
id|device
ques
c_cond
suffix:colon
l_string|&quot;arc%d&quot;
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|node
op_logical_and
id|node
op_ne
l_int|0xff
)paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|node
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|arcrimi_probe
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|my_dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|my_dev
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|lp-&gt;mem_start
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
id|dev-&gt;mem_start
op_plus
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|arcrimi_setup
r_static
r_int
id|__init
id|arcrimi_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|ints
(braket
l_int|8
)braket
suffix:semicolon
id|s
op_assign
id|get_options
c_func
(paren
id|s
comma
l_int|8
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ints
(braket
l_int|0
)braket
)paren
r_return
l_int|1
suffix:semicolon
id|dev
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
id|dev-&gt;init
op_assign
id|arcrimi_probe
suffix:semicolon
r_switch
c_cond
(paren
id|ints
(braket
l_int|0
)braket
)paren
(brace
r_default
suffix:colon
multiline_comment|/* ERROR */
id|printk
c_func
(paren
l_string|&quot;arcrimi: Too many arguments.&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* Node ID */
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* IRQ */
id|dev-&gt;irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* IO address */
id|dev-&gt;mem_start
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|s
)paren
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|s
comma
l_int|9
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;arc%d&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;arc-rimi: Cannot register arcnet device&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;arcrimi=&quot;
comma
id|arcrimi_setup
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
eof
