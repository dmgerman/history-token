multiline_comment|/* $Id: mtd.h,v 1.26 2000/10/30 17:18:04 sjhill Exp $ */
macro_line|#ifndef __MTD_MTD_H__
DECL|macro|__MTD_MTD_H__
mdefine_line|#define __MTD_MTD_H__
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#endif /* __KERNEL__ */
DECL|struct|erase_info_user
r_struct
id|erase_info_user
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtd_oob_buf
r_struct
id|mtd_oob_buf
(brace
DECL|member|start
id|loff_t
id|start
suffix:semicolon
DECL|member|length
id|ssize_t
id|length
suffix:semicolon
DECL|member|ptr
r_int
r_char
op_star
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MTD_CHAR_MAJOR
mdefine_line|#define MTD_CHAR_MAJOR 90
DECL|macro|MTD_BLOCK_MAJOR
mdefine_line|#define MTD_BLOCK_MAJOR 31
DECL|macro|MAX_MTD_DEVICES
mdefine_line|#define MAX_MTD_DEVICES 16
DECL|macro|MTD_ABSENT
mdefine_line|#define MTD_ABSENT&t;&t;0
DECL|macro|MTD_RAM
mdefine_line|#define MTD_RAM&t;&t;&t;1
DECL|macro|MTD_ROM
mdefine_line|#define MTD_ROM&t;&t;&t;2
DECL|macro|MTD_NORFLASH
mdefine_line|#define MTD_NORFLASH&t;&t;3
DECL|macro|MTD_NANDFLASH
mdefine_line|#define MTD_NANDFLASH&t;&t;4
DECL|macro|MTD_PEROM
mdefine_line|#define MTD_PEROM&t;&t;5
DECL|macro|MTD_OTHER
mdefine_line|#define MTD_OTHER&t;&t;14
DECL|macro|MTD_UNKNOWN
mdefine_line|#define MTD_UNKNOWN&t;&t;15
DECL|macro|MTD_CLEAR_BITS
mdefine_line|#define MTD_CLEAR_BITS&t;&t;1       
singleline_comment|// Bits can be cleared (flash)
DECL|macro|MTD_SET_BITS
mdefine_line|#define MTD_SET_BITS&t;&t;2       
singleline_comment|// Bits can be set
DECL|macro|MTD_ERASEABLE
mdefine_line|#define MTD_ERASEABLE&t;&t;4       
singleline_comment|// Has an erase function
DECL|macro|MTD_WRITEB_WRITEABLE
mdefine_line|#define MTD_WRITEB_WRITEABLE&t;8       
singleline_comment|// Direct IO is possible
DECL|macro|MTD_VOLATILE
mdefine_line|#define MTD_VOLATILE&t;&t;16      
singleline_comment|// Set for RAMs
DECL|macro|MTD_XIP
mdefine_line|#define MTD_XIP&t;&t;&t;32&t;
singleline_comment|// eXecute-In-Place possible
DECL|macro|MTD_OOB
mdefine_line|#define MTD_OOB&t;&t;&t;64&t;
singleline_comment|// Out-of-band data (NAND flash)
DECL|macro|MTD_ECC
mdefine_line|#define MTD_ECC&t;&t;&t;128&t;
singleline_comment|// Device capable of automatic ECC
singleline_comment|// Some common devices / combinations of capabilities
DECL|macro|MTD_CAP_ROM
mdefine_line|#define MTD_CAP_ROM&t;&t;0
DECL|macro|MTD_CAP_RAM
mdefine_line|#define MTD_CAP_RAM&t;&t;(MTD_CLEAR_BITS|MTD_SET_BITS|MTD_WRITEB_WRITEABLE)
DECL|macro|MTD_CAP_NORFLASH
mdefine_line|#define MTD_CAP_NORFLASH        (MTD_CLEAR_BITS|MTD_ERASEABLE)
DECL|macro|MTD_CAP_NANDFLASH
mdefine_line|#define MTD_CAP_NANDFLASH       (MTD_CLEAR_BITS|MTD_ERASEABLE|MTD_OOB)
DECL|macro|MTD_WRITEABLE
mdefine_line|#define MTD_WRITEABLE&t;&t;(MTD_CLEAR_BITS|MTD_SET_BITS)
singleline_comment|// Types of automatic ECC/Checksum available
DECL|macro|MTD_ECC_NONE
mdefine_line|#define MTD_ECC_NONE&t;&t;0 &t;
singleline_comment|// No automatic ECC available
DECL|macro|MTD_ECC_RS_DiskOnChip
mdefine_line|#define MTD_ECC_RS_DiskOnChip&t;1&t;
singleline_comment|// Automatic ECC on DiskOnChip
DECL|macro|MTD_ECC_SW
mdefine_line|#define MTD_ECC_SW&t;&t;2&t;
singleline_comment|// SW ECC for Toshiba &amp; Samsung devices
DECL|struct|mtd_info_user
r_struct
id|mtd_info_user
(brace
DECL|member|type
id|u_char
id|type
suffix:semicolon
DECL|member|flags
id|u_long
id|flags
suffix:semicolon
DECL|member|size
id|u_long
id|size
suffix:semicolon
singleline_comment|// Total size of the MTD
DECL|member|erasesize
id|u_long
id|erasesize
suffix:semicolon
DECL|member|oobblock
id|u_long
id|oobblock
suffix:semicolon
singleline_comment|// Size of OOB blocks (e.g. 512)
DECL|member|oobsize
id|u_long
id|oobsize
suffix:semicolon
singleline_comment|// Amount of OOB data per block (e.g. 16)
DECL|member|ecctype
id|u_long
id|ecctype
suffix:semicolon
DECL|member|eccsize
id|u_long
id|eccsize
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MEMGETINFO
mdefine_line|#define MEMGETINFO              _IOR(&squot;M&squot;, 1, struct mtd_info_user)
DECL|macro|MEMERASE
mdefine_line|#define MEMERASE                _IOW(&squot;M&squot;, 2, struct erase_info_user)
DECL|macro|MEMWRITEOOB
mdefine_line|#define MEMWRITEOOB             _IOWR(&squot;M&squot;, 3, struct mtd_oob_buf)
DECL|macro|MEMREADOOB
mdefine_line|#define MEMREADOOB              _IOWR(&squot;M&squot;, 4, struct mtd_oob_buf)
DECL|macro|MEMLOCK
mdefine_line|#define MEMLOCK                 _IOW(&squot;M&squot;, 5, struct erase_info_user)
DECL|macro|MEMUNLOCK
mdefine_line|#define MEMUNLOCK               _IOW(&squot;M&squot;, 6, struct erase_info_user)
macro_line|#ifndef __KERNEL__
DECL|typedef|mtd_info_t
r_typedef
r_struct
id|mtd_info_user
id|mtd_info_t
suffix:semicolon
DECL|typedef|erase_info_t
r_typedef
r_struct
id|erase_info_user
id|erase_info_t
suffix:semicolon
multiline_comment|/* User-space ioctl definitions */
macro_line|#else /* __KERNEL__ */
DECL|macro|MTD_ERASE_PENDING
mdefine_line|#define MTD_ERASE_PENDING      &t;0x01
DECL|macro|MTD_ERASING
mdefine_line|#define MTD_ERASING&t;&t;0x02
DECL|macro|MTD_ERASE_SUSPEND
mdefine_line|#define MTD_ERASE_SUSPEND&t;0x04
DECL|macro|MTD_ERASE_DONE
mdefine_line|#define MTD_ERASE_DONE          0x08
DECL|macro|MTD_ERASE_FAILED
mdefine_line|#define MTD_ERASE_FAILED        0x10
DECL|struct|erase_info
r_struct
id|erase_info
(brace
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|addr
id|u_long
id|addr
suffix:semicolon
DECL|member|len
id|u_long
id|len
suffix:semicolon
DECL|member|time
id|u_long
id|time
suffix:semicolon
DECL|member|retries
id|u_long
id|retries
suffix:semicolon
DECL|member|dev
id|u_int
id|dev
suffix:semicolon
DECL|member|cell
id|u_int
id|cell
suffix:semicolon
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|erase_info
op_star
id|self
)paren
suffix:semicolon
DECL|member|priv
id|u_long
id|priv
suffix:semicolon
DECL|member|state
id|u_char
id|state
suffix:semicolon
DECL|member|next
r_struct
id|erase_info
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtd_info
r_struct
id|mtd_info
(brace
DECL|member|type
id|u_char
id|type
suffix:semicolon
DECL|member|flags
id|u_long
id|flags
suffix:semicolon
DECL|member|size
id|u_long
id|size
suffix:semicolon
singleline_comment|// Total size of the MTD
DECL|member|erasesize
id|u_long
id|erasesize
suffix:semicolon
DECL|member|oobblock
id|u_long
id|oobblock
suffix:semicolon
singleline_comment|// Size of OOB blocks (e.g. 512)
DECL|member|oobsize
id|u_long
id|oobsize
suffix:semicolon
singleline_comment|// Amount of OOB data per block (e.g. 16)
DECL|member|ecctype
id|u_long
id|ecctype
suffix:semicolon
DECL|member|eccsize
id|u_long
id|eccsize
suffix:semicolon
singleline_comment|// Kernel-only stuff starts here.
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|bank_size
id|u_long
id|bank_size
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|erase
r_int
(paren
op_star
id|erase
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|erase_info
op_star
id|instr
)paren
suffix:semicolon
multiline_comment|/* This stuff for eXecute-In-Place */
DECL|member|point
r_int
(paren
op_star
id|point
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
op_star
id|mtdbuf
)paren
suffix:semicolon
multiline_comment|/* We probably shouldn&squot;t allow XIP if the unpoint isn&squot;t a NULL */
DECL|member|unpoint
r_void
(paren
op_star
id|unpoint
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|addr
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|read_ecc
r_int
(paren
op_star
id|read_ecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
comma
id|u_char
op_star
id|eccbuf
)paren
suffix:semicolon
DECL|member|write_ecc
r_int
(paren
op_star
id|write_ecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
comma
id|u_char
op_star
id|eccbuf
)paren
suffix:semicolon
DECL|member|read_oob
r_int
(paren
op_star
id|read_oob
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|write_oob
r_int
(paren
op_star
id|write_oob
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* iovec-based read/write methods. We need these especially for NAND flash,&n;&t;   with its limited number of write cycles per erase.&n;&t;   NB: The &squot;count&squot; parameter is the number of _vectors_, each of &n;&t;   which contains an (ofs, len) tuple.&n;&t;*/
DECL|member|readv
r_int
(paren
op_star
id|readv
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|iovec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|from
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
DECL|member|writev
r_int
(paren
op_star
id|writev
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|iovec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
multiline_comment|/* Sync */
DECL|member|sync
r_void
(paren
op_star
id|sync
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
multiline_comment|/* Chip-supported device locking */
DECL|member|lock
r_int
(paren
op_star
id|lock
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|unlock
r_int
(paren
op_star
id|unlock
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* Power Management functions */
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Kernel-side ioctl definitions */
r_extern
r_int
id|add_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_extern
r_int
id|del_mtd_device
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_extern
r_struct
id|mtd_info
op_star
id|__get_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|num
)paren
suffix:semicolon
DECL|function|get_mtd_device
r_static
r_inline
r_struct
id|mtd_info
op_star
id|get_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|num
)paren
(brace
r_struct
id|mtd_info
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|__get_mtd_device
c_func
(paren
id|mtd
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
id|ret-&gt;module
op_logical_and
op_logical_neg
id|try_inc_mod_count
c_func
(paren
id|ret-&gt;module
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|put_mtd_device
r_static
r_inline
r_void
id|put_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_if
c_cond
(paren
id|mtd-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|mtd-&gt;module
)paren
suffix:semicolon
)brace
DECL|struct|mtd_notifier
r_struct
id|mtd_notifier
(brace
DECL|member|add
r_void
(paren
op_star
id|add
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|next
r_struct
id|mtd_notifier
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|register_mtd_user
(paren
r_struct
id|mtd_notifier
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
id|unregister_mtd_user
(paren
r_struct
id|mtd_notifier
op_star
id|old
)paren
suffix:semicolon
macro_line|#ifndef MTDC
DECL|macro|MTD_ERASE
mdefine_line|#define MTD_ERASE(mtd, args...) (*(mtd-&gt;erase))(mtd, args)
DECL|macro|MTD_POINT
mdefine_line|#define MTD_POINT(mtd, a,b,c,d) (*(mtd-&gt;point))(mtd, a,b,c, (u_char **)(d))
DECL|macro|MTD_UNPOINT
mdefine_line|#define MTD_UNPOINT(mtd, arg) (*(mtd-&gt;unpoint))(mtd, (u_char *)arg)
DECL|macro|MTD_READ
mdefine_line|#define MTD_READ(mtd, args...) (*(mtd-&gt;read))(mtd, args)
DECL|macro|MTD_WRITE
mdefine_line|#define MTD_WRITE(mtd, args...) (*(mtd-&gt;write))(mtd, args)
DECL|macro|MTD_READV
mdefine_line|#define MTD_READV(mtd, args...) (*(mtd-&gt;readv))(mtd, args)
DECL|macro|MTD_WRITEV
mdefine_line|#define MTD_WRITEV(mtd, args...) (*(mtd-&gt;writev))(mtd, args)
DECL|macro|MTD_READECC
mdefine_line|#define MTD_READECC(mtd, args...) (*(mtd-&gt;read_ecc))(mtd, args)
DECL|macro|MTD_WRITEECC
mdefine_line|#define MTD_WRITEECC(mtd, args...) (*(mtd-&gt;write_ecc))(mtd, args)
DECL|macro|MTD_READOOB
mdefine_line|#define MTD_READOOB(mtd, args...) (*(mtd-&gt;read_oob))(mtd, args)
DECL|macro|MTD_WRITEOOB
mdefine_line|#define MTD_WRITEOOB(mtd, args...) (*(mtd-&gt;write_oob))(mtd, args)
DECL|macro|MTD_SYNC
mdefine_line|#define MTD_SYNC(mtd) do { if (mtd-&gt;sync) (*(mtd-&gt;sync))(mtd);  } while (0) 
macro_line|#endif /* MTDC */
multiline_comment|/*&n; * Debugging macro and defines&n; */
DECL|macro|MTD_DEBUG_LEVEL0
mdefine_line|#define MTD_DEBUG_LEVEL0&t;(0)&t;/* Quiet   */
DECL|macro|MTD_DEBUG_LEVEL1
mdefine_line|#define MTD_DEBUG_LEVEL1&t;(1)&t;/* Audible */
DECL|macro|MTD_DEBUG_LEVEL2
mdefine_line|#define MTD_DEBUG_LEVEL2&t;(2)&t;/* Loud    */
DECL|macro|MTD_DEBUG_LEVEL3
mdefine_line|#define MTD_DEBUG_LEVEL3&t;(3)&t;/* Noisy   */
macro_line|#ifdef CONFIG_MTD_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)&t;&t;&t;&bslash;&n;&t;if (n &lt;=  CONFIG_MTD_DEBUG_VERBOSE) {&t;&bslash;&n;&t;&t;printk(KERN_INFO args);&t;&bslash;&n;&t;}
macro_line|#else /* CONFIG_MTD_DEBUG */
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif /* CONFIG_MTD_DEBUG */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __MTD_MTD_H__ */
eof
