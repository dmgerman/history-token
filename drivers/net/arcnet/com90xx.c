multiline_comment|/*&n; * Linux ARCnet driver - COM90xx chipset (memory-mapped buffers)&n; * &n; * Written 1994-1999 by Avery Pennarun.&n; * Written 1999 by Martin Mares &lt;mj@ucw.cz&gt;.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: COM90xx chipset support&bslash;n&quot;
multiline_comment|/* Define this to speed up the autoprobe by assuming if only one io port and&n; * shmem are left in the list at Stage 5, they must correspond to each&n; * other.&n; *&n; * This is undefined by default because it might not always be true, and the&n; * extra check makes the autoprobe even more careful.  Speed demons can turn&n; * it on - I think it should be fine if you only have one ARCnet card&n; * installed.&n; *&n; * If no ARCnet cards are installed, this delay never happens anyway and thus&n; * the option has no effect.&n; */
DECL|macro|FAST_PROBE
macro_line|#undef FAST_PROBE
multiline_comment|/* Internal function declarations */
r_static
r_int
id|com90xx_found
c_func
(paren
r_int
id|ioaddr
comma
r_int
id|airq
comma
id|u_long
id|shmem
)paren
suffix:semicolon
r_static
r_void
id|com90xx_command
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
id|com90xx_status
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
id|com90xx_setmask
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
id|com90xx_reset
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
id|com90xx_copy_to_card
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
id|com90xx_copy_from_card
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
multiline_comment|/* Known ARCnet cards */
DECL|variable|cards
r_static
r_struct
id|net_device
op_star
id|cards
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|numcards
r_static
r_int
id|numcards
suffix:semicolon
multiline_comment|/* Handy defines for ARCnet specific stuff */
multiline_comment|/* The number of low I/O ports used by the card */
DECL|macro|ARCNET_TOTAL_SIZE
mdefine_line|#define ARCNET_TOTAL_SIZE&t;16
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
DECL|macro|_CONFIG
mdefine_line|#define _CONFIG  (ioaddr+2)&t;/* Configuration register */
DECL|macro|_RESET
mdefine_line|#define _RESET   (ioaddr+8)&t;/* software reset (on read) */
DECL|macro|_MEMDATA
mdefine_line|#define _MEMDATA (ioaddr+12)&t;/* Data port for IO-mapped memory */
DECL|macro|_ADDR_HI
mdefine_line|#define _ADDR_HI (ioaddr+15)&t;/* Control registers for said */
DECL|macro|_ADDR_LO
mdefine_line|#define _ADDR_LO (ioaddr+14)
DECL|macro|ASTATUS
macro_line|#undef ASTATUS
DECL|macro|ACOMMAND
macro_line|#undef ACOMMAND
DECL|macro|AINTMASK
macro_line|#undef AINTMASK
DECL|macro|ASTATUS
mdefine_line|#define ASTATUS()&t;inb(_STATUS)
DECL|macro|ACOMMAND
mdefine_line|#define ACOMMAND(cmd) &t;outb((cmd),_COMMAND)
DECL|macro|AINTMASK
mdefine_line|#define AINTMASK(msk)&t;outb((msk),_INTMASK)
DECL|variable|__initdata
r_static
r_int
id|com90xx_skip_probe
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Module parameters */
DECL|variable|io
r_static
r_int
id|io
suffix:semicolon
multiline_comment|/* use the insmod io= irq= shmem= options */
DECL|variable|irq
r_static
r_int
id|irq
suffix:semicolon
DECL|variable|shmem
r_static
r_int
id|shmem
suffix:semicolon
DECL|variable|device
r_static
r_char
id|device
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* use eg. device=arc1 to change name */
id|module_param
c_func
(paren
id|io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|shmem
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param_string
c_func
(paren
id|device
comma
id|device
comma
r_sizeof
(paren
id|device
)paren
comma
l_int|0
)paren
suffix:semicolon
DECL|function|com90xx_probe
r_static
r_void
id|__init
id|com90xx_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|count
comma
id|status
comma
id|ioaddr
comma
id|numprint
comma
id|airq
comma
id|openparen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|airqmask
suffix:semicolon
r_int
id|ports
(braket
(paren
l_int|0x3f0
op_minus
l_int|0x200
)paren
op_div
l_int|16
op_plus
l_int|1
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|u_long
id|shmems
(braket
(paren
l_int|0xFF800
op_minus
l_int|0xA0000
)paren
op_div
l_int|2048
op_plus
l_int|1
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
id|numports
comma
id|numshmems
comma
op_star
id|port
suffix:semicolon
id|u_long
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io
op_logical_and
op_logical_neg
id|irq
op_logical_and
op_logical_neg
id|shmem
op_logical_and
op_logical_neg
op_star
id|device
op_logical_and
id|com90xx_skip_probe
)paren
r_return
suffix:semicolon
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
multiline_comment|/* set up the arrays where we&squot;ll store the possible probe addresses */
id|numports
op_assign
id|numshmems
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|io
)paren
id|ports
(braket
id|numports
op_increment
)braket
op_assign
id|io
suffix:semicolon
r_else
r_for
c_loop
(paren
id|count
op_assign
l_int|0x200
suffix:semicolon
id|count
op_le
l_int|0x3f0
suffix:semicolon
id|count
op_add_assign
l_int|16
)paren
id|ports
(braket
id|numports
op_increment
)braket
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|shmem
)paren
id|shmems
(braket
id|numshmems
op_increment
)braket
op_assign
id|shmem
suffix:semicolon
r_else
r_for
c_loop
(paren
id|count
op_assign
l_int|0xA0000
suffix:semicolon
id|count
op_le
l_int|0xFF800
suffix:semicolon
id|count
op_add_assign
l_int|2048
)paren
id|shmems
(braket
id|numshmems
op_increment
)braket
op_assign
id|count
suffix:semicolon
multiline_comment|/* Stage 1: abandon any reserved ports, or ones with status==0xFF&n;&t; * (empty), and reset any others by reading the reset port.&n;&t; */
id|numprint
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
op_amp
id|ports
(braket
l_int|0
)braket
suffix:semicolon
id|port
op_minus
id|ports
OL
id|numports
suffix:semicolon
id|port
op_increment
)paren
(brace
id|numprint
op_increment
suffix:semicolon
id|numprint
op_mod_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numprint
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;S1: &quot;
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;%Xh &quot;
comma
op_star
id|port
)paren
suffix:semicolon
id|ioaddr
op_assign
op_star
id|port
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
comma
l_string|&quot;arcnet (90xx)&quot;
)paren
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(request_region)&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S1: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
op_star
id|port
op_decrement
op_assign
id|ports
(braket
op_decrement
id|numports
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ASTATUS
c_func
(paren
)paren
op_eq
l_int|0xFF
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(empty)&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S1: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
id|release_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
op_star
id|port
op_decrement
op_assign
id|ports
(braket
op_decrement
id|numports
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|inb
c_func
(paren
id|_RESET
)paren
suffix:semicolon
multiline_comment|/* begin resetting card */
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S1: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numports
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;S1: No ARCnet cards found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Stage 2: we have now reset any possible ARCnet cards, so we can&squot;t&n;&t; * do anything until they finish.  If D_INIT, print the list of&n;&t; * cards that are left.&n;&t; */
id|numprint
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
op_amp
id|ports
(braket
l_int|0
)braket
suffix:semicolon
id|port
OL
id|ports
op_plus
id|numports
suffix:semicolon
id|port
op_increment
)paren
(brace
id|numprint
op_increment
suffix:semicolon
id|numprint
op_mod_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numprint
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;S2: &quot;
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;%Xh &quot;
comma
op_star
id|port
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
suffix:semicolon
multiline_comment|/* Stage 3: abandon any shmem addresses that don&squot;t have the signature&n;&t; * 0xD1 byte in the right place, or are read-only.&n;&t; */
id|numprint
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|shmems
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|shmems
op_plus
id|numshmems
suffix:semicolon
id|p
op_increment
)paren
(brace
id|u_long
id|ptr
op_assign
op_star
id|p
suffix:semicolon
id|numprint
op_increment
suffix:semicolon
id|numprint
op_mod_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numprint
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;S3: &quot;
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;%lXh &quot;
comma
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
op_star
id|p
comma
id|BUFFER_SIZE
comma
l_string|&quot;arcnet (90xx)&quot;
)paren
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(request_mem_region)&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Stage 3: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_decrement
op_assign
id|shmems
(braket
op_decrement
id|numshmems
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isa_readb
c_func
(paren
id|ptr
)paren
op_ne
id|TESTvalue
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(%02Xh != %02Xh)&bslash;n&quot;
comma
id|isa_readb
c_func
(paren
id|ptr
)paren
comma
id|TESTvalue
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S3: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
id|release_mem_region
c_func
(paren
op_star
id|p
comma
id|BUFFER_SIZE
)paren
suffix:semicolon
op_star
id|p
op_decrement
op_assign
id|shmems
(braket
op_decrement
id|numshmems
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* By writing 0x42 to the TESTvalue location, we also make&n;&t;&t; * sure no &quot;mirror&quot; shmem areas show up - if they occur&n;&t;&t; * in another pass through this loop, they will be discarded&n;&t;&t; * because *cptr != TESTvalue.&n;&t;&t; */
id|isa_writeb
c_func
(paren
l_int|0x42
comma
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isa_readb
c_func
(paren
id|ptr
)paren
op_ne
l_int|0x42
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(read only)&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S3: &quot;
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
op_star
id|p
comma
id|BUFFER_SIZE
)paren
suffix:semicolon
op_star
id|p
op_decrement
op_assign
id|shmems
(braket
op_decrement
id|numshmems
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S3: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numshmems
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;S3: No ARCnet cards found.&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
op_amp
id|ports
(braket
l_int|0
)braket
suffix:semicolon
id|port
OL
id|ports
op_plus
id|numports
suffix:semicolon
id|port
op_increment
)paren
id|release_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Stage 4: something of a dummy, to report the shmems that are&n;&t; * still possible after stage 3.&n;&t; */
id|numprint
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|shmems
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|shmems
op_plus
id|numshmems
suffix:semicolon
id|p
op_increment
)paren
(brace
id|numprint
op_increment
suffix:semicolon
id|numprint
op_mod_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numprint
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;S4: &quot;
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;%lXh &quot;
comma
op_star
id|p
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Stage 5: for any ports that have the correct status, can disable&n;&t; * the RESET flag, and (if no irq is given) generate an autoirq,&n;&t; * register an ARCnet device.&n;&t; *&n;&t; * Currently, we can only register one device per probe, so quit&n;&t; * after the first one is found.&n;&t; */
id|numprint
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
op_amp
id|ports
(braket
l_int|0
)braket
suffix:semicolon
id|port
OL
id|ports
op_plus
id|numports
suffix:semicolon
id|port
op_increment
)paren
(brace
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|numprint
op_increment
suffix:semicolon
id|numprint
op_mod_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numprint
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;S5: &quot;
)paren
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;%Xh &quot;
comma
op_star
id|port
)paren
suffix:semicolon
id|ioaddr
op_assign
op_star
id|port
suffix:semicolon
id|status
op_assign
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x9D
)paren
op_ne
(paren
id|NORXflag
op_or
id|RECONflag
op_or
id|TXFREEflag
op_or
id|RESETflag
)paren
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(status=%Xh)&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S5: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
id|release_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
op_star
id|port
op_decrement
op_assign
id|ports
(braket
op_decrement
id|numports
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ACOMMAND
c_func
(paren
id|CFLAGScmd
op_or
id|RESETclear
op_or
id|CONFIGclear
)paren
suffix:semicolon
id|status
op_assign
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RESETflag
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot; (eternal reset, status=%Xh)&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S5: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
id|release_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
op_star
id|port
op_decrement
op_assign
id|ports
(braket
op_decrement
id|numports
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* skip this completely if an IRQ was given, because maybe&n;&t;&t; * we&squot;re on a machine that locks during autoirq!&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|irq
)paren
(brace
multiline_comment|/* if we do this, we&squot;re sure to get an IRQ since the&n;&t;&t;&t; * card has just reset and the NORXflag is on until&n;&t;&t;&t; * we tell it to start receiving.&n;&t;&t;&t; */
id|airqmask
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
id|AINTMASK
c_func
(paren
id|NORXflag
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|AINTMASK
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|airq
op_assign
id|probe_irq_off
c_func
(paren
id|airqmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|airq
op_le
l_int|0
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;(airq=%d)&bslash;n&quot;
comma
id|airq
)paren
suffix:semicolon
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;S5: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
id|release_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
op_star
id|port
op_decrement
op_assign
id|ports
(braket
op_decrement
id|numports
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_else
(brace
id|airq
op_assign
id|irq
suffix:semicolon
)brace
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;(%d,&quot;
comma
id|airq
)paren
suffix:semicolon
id|openparen
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Everything seems okay.  But which shmem, if any, puts&n;&t;&t; * back its signature byte when the card is reset?&n;&t;&t; *&n;&t;&t; * If there are multiple cards installed, there might be&n;&t;&t; * multiple shmems still in the list.&n;&t;&t; */
macro_line|#ifdef FAST_PROBE
r_if
c_cond
(paren
id|numports
OG
l_int|1
op_logical_or
id|numshmems
OG
l_int|1
)paren
(brace
id|inb
c_func
(paren
id|_RESET
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* just one shmem and port, assume they match */
id|isa_writeb
c_func
(paren
id|TESTvalue
comma
id|shmems
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
id|inb
c_func
(paren
id|_RESET
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|shmems
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|shmems
op_plus
id|numshmems
suffix:semicolon
id|p
op_increment
)paren
(brace
id|u_long
id|ptr
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|isa_readb
c_func
(paren
id|ptr
)paren
op_eq
id|TESTvalue
)paren
(brace
multiline_comment|/* found one */
id|BUGMSG2
c_func
(paren
id|D_INIT
comma
l_string|&quot;%lXh)&bslash;n&quot;
comma
op_star
id|p
)paren
suffix:semicolon
id|openparen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* register the card */
r_if
c_cond
(paren
id|com90xx_found
c_func
(paren
op_star
id|port
comma
id|airq
comma
op_star
id|p
)paren
op_eq
l_int|0
)paren
id|found
op_assign
l_int|1
suffix:semicolon
id|numprint
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* remove shmem from the list */
op_star
id|p
op_assign
id|shmems
(braket
op_decrement
id|numshmems
)braket
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* go to the next I/O port */
)brace
r_else
(brace
id|BUGMSG2
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;%Xh-&quot;
comma
id|isa_readb
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|openparen
)paren
(brace
id|BUGLVL
c_func
(paren
id|D_INIT
)paren
id|printk
c_func
(paren
l_string|&quot;no matching shmem)&bslash;n&quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|printk
c_func
(paren
l_string|&quot;S5: &quot;
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|numprint
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|release_region
c_func
(paren
op_star
id|port
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
op_star
id|port
op_decrement
op_assign
id|ports
(braket
op_decrement
id|numports
)braket
suffix:semicolon
)brace
id|BUGLVL
c_func
(paren
id|D_INIT_REASONS
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Now put back TESTvalue on all leftover shmems. */
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|shmems
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|shmems
op_plus
id|numshmems
suffix:semicolon
id|p
op_increment
)paren
(brace
id|isa_writeb
c_func
(paren
id|TESTvalue
comma
op_star
id|p
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
op_star
id|p
comma
id|BUFFER_SIZE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Set up the struct net_device associated with this card.  Called after&n; * probing succeeds.&n; */
DECL|function|com90xx_found
r_static
r_int
id|__init
id|com90xx_found
c_func
(paren
r_int
id|ioaddr
comma
r_int
id|airq
comma
id|u_long
id|shmem
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
id|u_long
id|first_mirror
comma
id|last_mirror
suffix:semicolon
r_int
id|mirror_size
suffix:semicolon
multiline_comment|/* allocate struct net_device */
id|dev
op_assign
id|alloc_arcdev
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|BUGMSG2
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;com90xx: Can&squot;t allocate device!&bslash;n&quot;
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|shmem
comma
id|BUFFER_SIZE
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
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
id|release_mem_region
c_func
(paren
id|shmem
comma
id|BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
)paren
r_goto
id|err_free_dev
suffix:semicolon
multiline_comment|/* reserve the irq */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|airq
comma
op_amp
id|arcnet_interrupt
comma
l_int|0
comma
l_string|&quot;arcnet (90xx)&quot;
comma
id|dev
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Can&squot;t get IRQ %d!&bslash;n&quot;
comma
id|airq
)paren
suffix:semicolon
r_goto
id|err_release_mem
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|airq
suffix:semicolon
multiline_comment|/* Initialize the rest of the device structure. */
id|lp-&gt;card_name
op_assign
l_string|&quot;COM90xx&quot;
suffix:semicolon
id|lp-&gt;hw.command
op_assign
id|com90xx_command
suffix:semicolon
id|lp-&gt;hw.status
op_assign
id|com90xx_status
suffix:semicolon
id|lp-&gt;hw.intmask
op_assign
id|com90xx_setmask
suffix:semicolon
id|lp-&gt;hw.reset
op_assign
id|com90xx_reset
suffix:semicolon
id|lp-&gt;hw.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|lp-&gt;hw.copy_to_card
op_assign
id|com90xx_copy_to_card
suffix:semicolon
id|lp-&gt;hw.copy_from_card
op_assign
id|com90xx_copy_from_card
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
id|err_free_irq
suffix:semicolon
)brace
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
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;COM90xx station %02Xh found at %03lXh, IRQ %d, &quot;
l_string|&quot;ShMem %lXh (%ld*%xh).&bslash;n&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;base_addr
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
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
)paren
r_goto
id|err_unmap
suffix:semicolon
id|cards
(braket
id|numcards
op_increment
)braket
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_unmap
suffix:colon
id|iounmap
c_func
(paren
id|lp-&gt;mem_start
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
id|err_release_mem
suffix:colon
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
id|err_free_dev
suffix:colon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|com90xx_command
r_static
r_void
id|com90xx_command
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|ACOMMAND
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|com90xx_status
r_static
r_int
id|com90xx_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_return
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|com90xx_setmask
r_static
r_void
id|com90xx_setmask
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|AINTMASK
c_func
(paren
id|mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a hardware reset on the card, and set up necessary registers.&n; * &n; * This should be called as little as possible, because it disrupts the&n; * token on the network (causes a RECON) and requires a significant delay.&n; *&n; * However, it does make sure the card is in a defined state.&n; */
DECL|function|com90xx_reset
r_int
id|com90xx_reset
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
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_INIT
comma
l_string|&quot;Resetting (status=%02Xh)&bslash;n&quot;
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
multiline_comment|/* reset the card */
id|inb
c_func
(paren
id|_RESET
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
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
multiline_comment|/* don&squot;t do this until we verify that it doesn&squot;t hurt older cards! */
multiline_comment|/* outb(inb(_CONFIG) | ENABLE16flag, _CONFIG); */
multiline_comment|/* verify that the ARCnet signature byte is present */
r_if
c_cond
(paren
id|readb
c_func
(paren
id|lp-&gt;mem_start
)paren
op_ne
id|TESTvalue
)paren
(brace
r_if
c_cond
(paren
id|really_reset
)paren
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;reset failed: TESTvalue not present.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* enable extended (512-byte) packets */
id|ACOMMAND
c_func
(paren
id|CONFIGcmd
op_or
id|EXTconf
)paren
suffix:semicolon
multiline_comment|/* clean out all the memory to make debugging make more sense :) */
id|BUGLVL
c_func
(paren
id|D_DURING
)paren
id|memset_io
c_func
(paren
id|lp-&gt;mem_start
comma
l_int|0x42
comma
l_int|2048
)paren
suffix:semicolon
multiline_comment|/* done!  return success. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|com90xx_copy_to_card
r_static
r_void
id|com90xx_copy_to_card
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
id|dev-&gt;priv
suffix:semicolon
r_void
id|__iomem
op_star
id|memaddr
op_assign
id|lp-&gt;mem_start
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
DECL|function|com90xx_copy_from_card
r_static
r_void
id|com90xx_copy_from_card
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
id|dev-&gt;priv
suffix:semicolon
r_void
id|__iomem
op_star
id|memaddr
op_assign
id|lp-&gt;mem_start
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|com90xx_init
r_static
r_int
id|__init
id|com90xx_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
id|irq
op_assign
l_int|9
suffix:semicolon
id|com90xx_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|numcards
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|com90xx_exit
r_static
r_void
id|__exit
id|com90xx_exit
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
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
r_int
id|count
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|numcards
suffix:semicolon
id|count
op_increment
)paren
(brace
id|dev
op_assign
id|cards
(braket
id|count
)braket
suffix:semicolon
id|lp
op_assign
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
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|ARCNET_TOTAL_SIZE
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
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|com90xx_init
id|module_init
c_func
(paren
id|com90xx_init
)paren
suffix:semicolon
DECL|variable|com90xx_exit
id|module_exit
c_func
(paren
id|com90xx_exit
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|com90xx_setup
r_static
r_int
id|__init
id|com90xx_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
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
op_logical_and
op_logical_neg
op_star
id|s
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;com90xx: Disabled.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
l_string|&quot;com90xx: Too many arguments.&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* Mem address */
id|shmem
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
id|irq
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
id|io
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
id|snprintf
c_func
(paren
id|device
comma
r_sizeof
(paren
id|device
)paren
comma
l_string|&quot;%s&quot;
comma
id|s
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;com90xx=&quot;
comma
id|com90xx_setup
)paren
suffix:semicolon
macro_line|#endif
eof
