multiline_comment|/*&n; * gfx.c: support for SGI&squot;s /dev/graphics, /dev/opengl&n; *&n; * Author: Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *         Ralf Baechle (ralf@gnu.org)&n; *         Ulf Carlsson (ulfc@bun.falkenberg.se)&n; *&n; * On IRIX, /dev/graphics is [10, 146]&n; *          /dev/opengl   is [10, 147]&n; *&n; * From a mail with Mark J. Kilgard, /dev/opengl and /dev/graphics are&n; * the same thing, the use of /dev/graphics seems deprecated though.&n; *&n; * The reason that the original SGI programmer had to use only one&n; * device for all the graphic cards on the system will remain a&n; * mistery for the rest of our lives.  Why some ioctls take a board&n; * number and some others not?  Mistery.  Why do they map the hardware&n; * registers into the user address space with an ioctl instead of&n; * mmap?  Mistery too.  Why they did not use the standard way of&n; * making ioctl constants and instead sticked a random constant?&n; * Mistery too.&n; *&n; * We implement those misterious things, and tried not to think about&n; * the reasons behind them.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;gconsole.h&quot;
macro_line|#include &quot;graphics.h&quot;
macro_line|#include &quot;usema.h&quot;
macro_line|#include &lt;asm/gfx.h&gt;
macro_line|#include &lt;asm/rrm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;video/newport.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
multiline_comment|/* The boards */
r_extern
r_struct
id|graphics_ops
op_star
id|newport_probe
(paren
r_int
comma
r_const
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|variable|cards
r_static
r_struct
id|graphics_ops
id|cards
(braket
id|MAXCARDS
)braket
suffix:semicolon
DECL|variable|boards
r_static
r_int
id|boards
suffix:semicolon
DECL|macro|GRAPHICS_CARD
mdefine_line|#define GRAPHICS_CARD(inode) 0
multiline_comment|/*&n;void enable_gconsole(void) {};&n;void disable_gconsole(void) {};&n;*/
r_int
DECL|function|sgi_graphics_open
id|sgi_graphics_open
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|newport_regs
op_star
id|nregs
op_assign
(paren
r_struct
id|newport_regs
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|cards
(braket
l_int|0
)braket
dot
id|g_regs
)paren
suffix:semicolon
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
id|nregs-&gt;set.wrmask
op_assign
l_int|0xffffffff
suffix:semicolon
id|nregs-&gt;set.drawmode0
op_assign
(paren
id|NPORT_DMODE0_DRAW
op_or
id|NPORT_DMODE0_BLOCK
op_or
id|NPORT_DMODE0_DOSETUP
op_or
id|NPORT_DMODE0_STOPX
op_or
id|NPORT_DMODE0_STOPY
)paren
suffix:semicolon
id|nregs-&gt;set.colori
op_assign
l_int|1
suffix:semicolon
id|nregs-&gt;set.xystarti
op_assign
(paren
l_int|0
op_lshift
l_int|16
)paren
op_or
l_int|0
suffix:semicolon
id|nregs-&gt;go.xyendi
op_assign
(paren
l_int|1280
op_lshift
l_int|16
)paren
op_or
l_int|1024
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|sgi_graphics_ioctl
id|sgi_graphics_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|board
suffix:semicolon
r_int
r_int
id|devnum
op_assign
id|GRAPHICS_CARD
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_ge
id|RRM_BASE
)paren
op_logical_and
(paren
id|cmd
op_le
id|RRM_CMD_LIMIT
)paren
)paren
r_return
id|rrm_command
(paren
id|cmd
op_minus
id|RRM_BASE
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|GFX_GETNUM_BOARDS
suffix:colon
r_return
id|boards
suffix:semicolon
r_case
id|GFX_GETBOARD_INFO
suffix:colon
(brace
r_struct
id|gfx_getboardinfo_args
op_star
id|bia
op_assign
(paren
r_void
op_star
)paren
id|arg
suffix:semicolon
r_void
op_star
id|dest_buf
suffix:semicolon
r_int
id|max_len
suffix:semicolon
id|i
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|gfx_getboardinfo_args
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
(paren
id|board
comma
op_amp
id|bia-&gt;board
)paren
op_logical_or
id|__get_user
(paren
id|dest_buf
comma
op_amp
id|bia-&gt;buf
)paren
op_logical_or
id|__get_user
(paren
id|max_len
comma
op_amp
id|bia-&gt;len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|board
op_ge
id|boards
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|max_len
OL
r_sizeof
(paren
r_struct
id|gfx_getboardinfo_args
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|max_len
OG
id|cards
(braket
id|board
)braket
dot
id|g_board_info_len
)paren
id|max_len
op_assign
id|cards
(braket
id|boards
)braket
dot
id|g_board_info_len
suffix:semicolon
id|i
op_assign
id|verify_area
(paren
id|VERIFY_WRITE
comma
id|dest_buf
comma
id|max_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
id|dest_buf
comma
id|cards
(braket
id|board
)braket
dot
id|g_board_info
comma
id|max_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|max_len
suffix:semicolon
)brace
r_case
id|GFX_ATTACH_BOARD
suffix:colon
(brace
r_struct
id|gfx_attach_board_args
op_star
id|att
op_assign
(paren
r_void
op_star
)paren
id|arg
suffix:semicolon
r_void
op_star
id|vaddr
suffix:semicolon
r_int
id|r
suffix:semicolon
id|i
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|gfx_attach_board_args
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
(paren
id|board
comma
op_amp
id|att-&gt;board
)paren
op_logical_or
id|__get_user
(paren
id|vaddr
comma
op_amp
id|att-&gt;vaddr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Ok for now we are assuming /dev/graphicsN -&gt; head N even&n;&t;&t; * if the ioctl api suggests that this is not quite the case.&n;&t;&t; *&n;&t;&t; * Otherwise we fail, we use this assumption in the mmap code&n;&t;&t; * below to find our board information.&n;&t;&t; */
r_if
c_cond
(paren
id|board
op_ne
id|devnum
)paren
(brace
id|printk
(paren
l_string|&quot;Parameter board does not match the current board&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|board
op_ge
id|boards
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* If it is the first opening it, then make it the board owner */
r_if
c_cond
(paren
op_logical_neg
id|cards
(braket
id|board
)braket
dot
id|g_owner
)paren
id|cards
(braket
id|board
)braket
dot
id|g_owner
op_assign
id|current
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ok, we now call mmap on this file, which will end up calling&n;&t;&t; * sgi_graphics_mmap&n;&t;&t; */
id|disable_gconsole
(paren
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|r
op_assign
id|do_mmap
(paren
id|file
comma
(paren
r_int
r_int
)paren
id|vaddr
comma
id|cards
(braket
id|board
)braket
dot
id|g_regs_size
comma
id|PROT_READ
op_or
id|PROT_WRITE
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/* Strange, the real mapping seems to be done at GFX_ATTACH_BOARD,&n;&t; * GFX_MAPALL is not even used by IRIX X server&n;&t; */
r_case
id|GFX_MAPALL
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|GFX_LABEL
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Version check&n;&t;&t; * for my IRIX 6.2 X server, this is what the kernel returns&n;&t;&t; */
r_case
l_int|1
suffix:colon
r_return
l_int|3
suffix:semicolon
multiline_comment|/* Xsgi does not use this one, I assume minor is the board being queried */
r_case
id|GFX_IS_MANAGED
suffix:colon
r_if
c_cond
(paren
id|devnum
OG
id|boards
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
(paren
id|cards
(braket
id|devnum
)braket
dot
id|g_owner
op_ne
l_int|0
)paren
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|cards
(braket
id|devnum
)braket
dot
id|g_ioctl
)paren
r_return
(paren
op_star
id|cards
(braket
id|devnum
)braket
dot
id|g_ioctl
)paren
(paren
id|devnum
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_int
DECL|function|sgi_graphics_close
id|sgi_graphics_close
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|board
op_assign
id|GRAPHICS_CARD
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
multiline_comment|/* Tell the rendering manager that one client is going away */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|rrm_close
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
multiline_comment|/* Was this file handle from the board owner?, clear it */
r_if
c_cond
(paren
id|current
op_eq
id|cards
(braket
id|board
)braket
dot
id|g_owner
)paren
(brace
id|cards
(braket
id|board
)braket
dot
id|g_owner
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cards
(braket
id|board
)braket
dot
id|g_reset_console
)paren
(paren
op_star
id|cards
(braket
id|board
)braket
dot
id|g_reset_console
)paren
(paren
)paren
suffix:semicolon
id|enable_gconsole
(paren
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * This is the core of the direct rendering engine.&n; */
r_struct
id|page
op_star
DECL|function|sgi_graphics_nopage
id|sgi_graphics_nopage
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|no_share
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|board
op_assign
id|GRAPHICS_CARD
(paren
id|vma-&gt;vm_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
r_int
id|virt_add
comma
id|phys_add
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;Got a page fault for board %d address=%lx guser=%lx&bslash;n&quot;
comma
id|board
comma
id|address
comma
(paren
r_int
r_int
)paren
id|cards
(braket
id|board
)braket
dot
id|g_user
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Figure out if another process has this mapped, and revoke the mapping&n;&t; * in that case. */
r_if
c_cond
(paren
id|cards
(braket
id|board
)braket
dot
id|g_user
op_logical_and
id|cards
(braket
id|board
)braket
dot
id|g_user
op_ne
id|current
)paren
(brace
multiline_comment|/* FIXME: save graphics context here, dump it to rendering&n;&t;&t; * node? */
id|remove_mapping
c_func
(paren
id|cards
(braket
id|board
)braket
dot
id|g_user
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
)paren
suffix:semicolon
)brace
id|cards
(braket
id|board
)braket
dot
id|g_user
op_assign
id|current
suffix:semicolon
multiline_comment|/* Map the physical address of the newport registers into the address&n;&t; * space of this process */
id|virt_add
op_assign
id|address
op_amp
id|PAGE_MASK
suffix:semicolon
id|phys_add
op_assign
id|cards
(braket
id|board
)braket
dot
id|g_regs
op_plus
id|virt_add
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|remap_page_range
c_func
(paren
id|virt_add
comma
id|phys_add
comma
id|PAGE_SIZE
comma
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_return
id|pte_page
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We convert a GFX ioctl for mapping hardware registers, in a nice sys_mmap&n; * call, which takes care of everything that must be taken care of.&n; *&n; */
DECL|variable|graphics_mmap
r_static
r_struct
id|vm_operations_struct
id|graphics_mmap
op_assign
(brace
id|nopage
suffix:colon
id|sgi_graphics_nopage
comma
multiline_comment|/* our magic no-page fault handler */
)brace
suffix:semicolon
r_int
DECL|function|sgi_graphics_mmap
id|sgi_graphics_mmap
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|uint
id|size
suffix:semicolon
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
multiline_comment|/* 1. Set our special graphic virtualizer  */
id|vma-&gt;vm_ops
op_assign
op_amp
id|graphics_mmap
suffix:semicolon
multiline_comment|/* 2. Set the special tlb permission bits */
id|vma-&gt;vm_page_prot
op_assign
id|PAGE_USERIO
suffix:semicolon
multiline_comment|/* final setup */
id|vma-&gt;vm_file
op_assign
id|file
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* Do any post card-detection setup on graphics_ops */
r_static
r_void
id|graphics_ops_post_init
(paren
r_int
id|slot
)paren
(brace
multiline_comment|/* There is no owner for the card initially */
id|cards
(braket
id|slot
)braket
dot
id|g_owner
op_assign
(paren
r_struct
id|task_struct
op_star
)paren
l_int|0
suffix:semicolon
id|cards
(braket
id|slot
)braket
dot
id|g_user
op_assign
(paren
r_struct
id|task_struct
op_star
)paren
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|sgi_graphics_fops
r_struct
id|file_operations
id|sgi_graphics_fops
op_assign
(brace
id|ioctl
suffix:colon
id|sgi_graphics_ioctl
comma
id|mmap
suffix:colon
id|sgi_graphics_mmap
comma
id|open
suffix:colon
id|sgi_graphics_open
comma
id|release
suffix:colon
id|sgi_graphics_close
comma
)brace
suffix:semicolon
multiline_comment|/* /dev/graphics */
DECL|variable|dev_graphics
r_static
r_struct
id|miscdevice
id|dev_graphics
op_assign
(brace
id|SGI_GRAPHICS_MINOR
comma
l_string|&quot;sgi-graphics&quot;
comma
op_amp
id|sgi_graphics_fops
)brace
suffix:semicolon
multiline_comment|/* /dev/opengl */
DECL|variable|dev_opengl
r_static
r_struct
id|miscdevice
id|dev_opengl
op_assign
(brace
id|SGI_OPENGL_MINOR
comma
l_string|&quot;sgi-opengl&quot;
comma
op_amp
id|sgi_graphics_fops
)brace
suffix:semicolon
multiline_comment|/* This is called later from the misc-init routine */
DECL|function|gfx_register
r_void
id|__init
id|gfx_register
(paren
r_void
)paren
(brace
id|misc_register
(paren
op_amp
id|dev_graphics
)paren
suffix:semicolon
id|misc_register
(paren
op_amp
id|dev_opengl
)paren
suffix:semicolon
)brace
DECL|function|gfx_init
r_void
id|__init
id|gfx_init
(paren
r_const
r_char
op_star
op_star
id|name
)paren
(brace
macro_line|#if 0
r_struct
id|console_ops
op_star
id|console
suffix:semicolon
r_struct
id|graphics_ops
op_star
id|g
suffix:semicolon
macro_line|#endif
id|printk
(paren
l_string|&quot;GFX INIT: &quot;
)paren
suffix:semicolon
id|shmiq_init
(paren
)paren
suffix:semicolon
id|usema_init
(paren
)paren
suffix:semicolon
id|boards
op_increment
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|g
op_assign
id|newport_probe
(paren
id|boards
comma
id|name
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|cards
(braket
id|boards
)braket
op_assign
op_star
id|g
suffix:semicolon
id|graphics_ops_post_init
(paren
id|boards
)paren
suffix:semicolon
id|boards
op_increment
suffix:semicolon
id|console
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Add more graphic drivers here */
multiline_comment|/* Keep passing console around */
macro_line|#endif
r_if
c_cond
(paren
id|boards
OG
id|MAXCARDS
)paren
id|printk
(paren
id|KERN_WARNING
l_string|&quot;Too many cards found on the system&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
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
r_static
r_int
id|initiated
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SGI Newport Graphics version %i.%i.%i&bslash;n&quot;
comma
l_int|42
comma
l_int|54
comma
l_int|69
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initiated
op_increment
)paren
(brace
id|shmiq_init
c_func
(paren
)paren
suffix:semicolon
id|usema_init
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Adding first board&bslash;n&quot;
)paren
suffix:semicolon
id|boards
op_increment
suffix:semicolon
id|cards
(braket
l_int|0
)braket
dot
id|g_regs
op_assign
l_int|0x1f0f0000
suffix:semicolon
id|cards
(braket
l_int|0
)braket
dot
id|g_regs_size
op_assign
r_sizeof
(paren
r_struct
id|newport_regs
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Boards: %d&bslash;n&quot;
comma
id|boards
)paren
suffix:semicolon
id|misc_register
(paren
op_amp
id|dev_graphics
)paren
suffix:semicolon
id|misc_register
(paren
op_amp
id|dev_opengl
)paren
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
id|printk
c_func
(paren
l_string|&quot;Shutting down SGI Newport Graphics&bslash;n&quot;
)paren
suffix:semicolon
id|misc_deregister
(paren
op_amp
id|dev_graphics
)paren
suffix:semicolon
id|misc_deregister
(paren
op_amp
id|dev_opengl
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
