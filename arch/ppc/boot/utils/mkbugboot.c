multiline_comment|/*&n; * arch/ppc/pp3boot/mkbugboot.c&n; * &n; * Makes a Motorola PPCBUG ROM bootable image which can be flashed &n; * into one of the FLASH banks on a Motorola PowerPlus board. &n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
DECL|macro|ELF_HEADER_SIZE
mdefine_line|#define ELF_HEADER_SIZE&t;65536
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#ifdef __i386__
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x) le32_to_cpu(x)
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x) le16_to_cpu(x)
macro_line|#else
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x) (x)
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x) (x)
macro_line|#endif
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) le32_to_cpu((x))
DECL|function|le32_to_cpu
r_int
r_int
id|le32_to_cpu
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
op_amp
l_int|0x000000ffU
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0x0000ff00U
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0x00ff0000U
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff000000U
)paren
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) le16_to_cpu((x))
DECL|function|le16_to_cpu
r_int
r_int
id|le16_to_cpu
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
op_amp
l_int|0x00ff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* size of read buffer */
DECL|macro|SIZE
mdefine_line|#define SIZE 0x1000
multiline_comment|/* typedef long int32_t; */
DECL|typedef|uint32_t
r_typedef
r_int
r_int
r_uint32
suffix:semicolon
DECL|typedef|uint16_t
r_typedef
r_int
r_int
r_uint16
suffix:semicolon
DECL|typedef|uint8_t
r_typedef
r_int
r_char
r_uint8
suffix:semicolon
multiline_comment|/* PPCBUG ROM boot header */
DECL|struct|bug_boot_header
r_typedef
r_struct
id|bug_boot_header
(brace
DECL|member|magic_word
r_uint8
id|magic_word
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* &quot;BOOT&quot; */
DECL|member|entry_offset
r_uint32
id|entry_offset
suffix:semicolon
multiline_comment|/* Offset from top of header to code */
DECL|member|routine_length
r_uint32
id|routine_length
suffix:semicolon
multiline_comment|/* Length of code */
DECL|member|routine_name
r_uint8
id|routine_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Name of the boot code */
DECL|typedef|bug_boot_header_t
)brace
id|bug_boot_header_t
suffix:semicolon
DECL|macro|HEADER_SIZE
mdefine_line|#define HEADER_SIZE&t;sizeof(bug_boot_header_t)
DECL|function|copy_image
r_uint32
id|copy_image
c_func
(paren
r_int32
id|in_fd
comma
r_int32
id|out_fd
)paren
(brace
r_uint8
id|buf
(braket
id|SIZE
)braket
suffix:semicolon
r_int
id|n
suffix:semicolon
r_uint32
id|image_size
op_assign
l_int|0
suffix:semicolon
r_uint8
id|zero
op_assign
l_int|0
suffix:semicolon
id|lseek
c_func
(paren
id|in_fd
comma
id|ELF_HEADER_SIZE
comma
id|SEEK_SET
)paren
suffix:semicolon
multiline_comment|/* Copy an image while recording its size */
r_while
c_loop
(paren
(paren
id|n
op_assign
id|read
c_func
(paren
id|in_fd
comma
id|buf
comma
id|SIZE
)paren
)paren
OG
l_int|0
)paren
(brace
id|image_size
op_assign
id|image_size
op_plus
id|n
suffix:semicolon
id|write
c_func
(paren
id|out_fd
comma
id|buf
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/* BUG romboot requires that our size is divisible by 2 */
multiline_comment|/* align image to 2 byte boundary */
r_if
c_cond
(paren
id|image_size
op_mod
l_int|2
)paren
(brace
id|image_size
op_increment
suffix:semicolon
id|write
c_func
(paren
id|out_fd
comma
op_amp
id|zero
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|image_size
suffix:semicolon
)brace
DECL|function|write_bugboot_header
r_void
id|write_bugboot_header
c_func
(paren
r_int32
id|out_fd
comma
r_uint32
id|boot_size
)paren
(brace
r_uint8
id|header_block
(braket
id|HEADER_SIZE
)braket
suffix:semicolon
id|bug_boot_header_t
op_star
id|bbh
op_assign
(paren
id|bug_boot_header_t
op_star
)paren
op_amp
id|header_block
(braket
l_int|0
)braket
suffix:semicolon
id|bzero
c_func
(paren
id|header_block
comma
id|HEADER_SIZE
)paren
suffix:semicolon
multiline_comment|/* Fill in the PPCBUG ROM boot header */
id|strncpy
c_func
(paren
id|bbh-&gt;magic_word
comma
l_string|&quot;BOOT&quot;
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* PPCBUG magic word */
id|bbh-&gt;entry_offset
op_assign
id|cpu_to_be32
c_func
(paren
id|HEADER_SIZE
)paren
suffix:semicolon
multiline_comment|/* Entry address */
id|bbh-&gt;routine_length
op_assign
id|cpu_to_be32
c_func
(paren
id|HEADER_SIZE
op_plus
id|boot_size
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Routine length */
id|strncpy
c_func
(paren
id|bbh-&gt;routine_name
comma
l_string|&quot;LINUXROM&quot;
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Routine name   */
multiline_comment|/* Output the header and bootloader to the file */
id|write
c_func
(paren
id|out_fd
comma
id|header_block
comma
id|HEADER_SIZE
)paren
suffix:semicolon
)brace
DECL|function|calc_checksum
r_uint16
id|calc_checksum
c_func
(paren
r_int32
id|bug_fd
)paren
(brace
r_uint32
id|checksum_var
op_assign
l_int|0
suffix:semicolon
r_uint8
id|buf
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|n
suffix:semicolon
multiline_comment|/* Checksum loop */
r_while
c_loop
(paren
(paren
id|n
op_assign
id|read
c_func
(paren
id|bug_fd
comma
id|buf
comma
l_int|2
)paren
)paren
)paren
(brace
id|checksum_var
op_assign
id|checksum_var
op_plus
op_star
(paren
r_uint16
op_star
)paren
id|buf
suffix:semicolon
multiline_comment|/* If we carry out, mask it and add one to the checksum */
r_if
c_cond
(paren
id|checksum_var
op_rshift
l_int|16
)paren
id|checksum_var
op_assign
(paren
id|checksum_var
op_amp
l_int|0x0000ffff
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|checksum_var
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_int32
id|image_fd
comma
id|bugboot_fd
suffix:semicolon
r_int
id|argptr
op_assign
l_int|1
suffix:semicolon
r_uint32
id|kernel_size
op_assign
l_int|0
suffix:semicolon
r_uint16
id|checksum
op_assign
l_int|0
suffix:semicolon
r_uint8
id|bugbootname
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|argc
op_ne
l_int|3
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s &lt;kernel_image&gt; &lt;bugboot&gt;&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Get file args */
multiline_comment|/* kernel image file */
r_if
c_cond
(paren
(paren
id|image_fd
op_assign
id|open
c_func
(paren
id|argv
(braket
id|argptr
)braket
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
m_exit
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|argptr
op_increment
suffix:semicolon
multiline_comment|/* bugboot file */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|argptr
)braket
comma
l_string|&quot;-&quot;
)paren
)paren
id|bugboot_fd
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* stdout */
r_else
r_if
c_cond
(paren
(paren
id|bugboot_fd
op_assign
id|creat
c_func
(paren
id|argv
(braket
id|argptr
)braket
comma
l_int|0755
)paren
)paren
OL
l_int|0
)paren
m_exit
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|bugbootname
comma
id|argv
(braket
id|argptr
)braket
)paren
suffix:semicolon
id|argptr
op_increment
suffix:semicolon
multiline_comment|/* Set file position after ROM header block where zImage will be written */
id|lseek
c_func
(paren
id|bugboot_fd
comma
id|HEADER_SIZE
comma
id|SEEK_SET
)paren
suffix:semicolon
multiline_comment|/* Copy kernel image into bugboot image */
id|kernel_size
op_assign
id|copy_image
c_func
(paren
id|image_fd
comma
id|bugboot_fd
)paren
suffix:semicolon
id|close
c_func
(paren
id|image_fd
)paren
suffix:semicolon
multiline_comment|/* Set file position to beginning where header/romboot will be written */
id|lseek
c_func
(paren
id|bugboot_fd
comma
l_int|0
comma
id|SEEK_SET
)paren
suffix:semicolon
multiline_comment|/* Write out BUG header/romboot */
id|write_bugboot_header
c_func
(paren
id|bugboot_fd
comma
id|kernel_size
)paren
suffix:semicolon
multiline_comment|/* Close bugboot file */
id|close
c_func
(paren
id|bugboot_fd
)paren
suffix:semicolon
multiline_comment|/* Reopen it as read/write */
id|bugboot_fd
op_assign
id|open
c_func
(paren
id|bugbootname
comma
id|O_RDWR
)paren
suffix:semicolon
multiline_comment|/* Calculate checksum */
id|checksum
op_assign
id|calc_checksum
c_func
(paren
id|bugboot_fd
)paren
suffix:semicolon
multiline_comment|/* Write out the calculated checksum */
id|write
c_func
(paren
id|bugboot_fd
comma
op_amp
id|checksum
comma
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
