multiline_comment|/*!*****************************************************************************&n;*!&n;*!  Implements an interface for i2c compatible eeproms to run under linux.&n;*!  Supports 2k, 8k(?) and 16k. Uses adaptive timing adjustents by&n;*!  Johan.Adolfsson@axis.com&n;*!&n;*!  Probing results:&n;*!    8k or not is detected (the assumes 2k or 16k)&n;*!    2k or 16k detected using test reads and writes.&n;*!&n;*!------------------------------------------------------------------------&n;*!  HISTORY&n;*!&n;*!  DATE          NAME              CHANGES&n;*!  ----          ----              -------&n;*!  Aug  28 1999  Edgar Iglesias    Initial Version&n;*!  Aug  31 1999  Edgar Iglesias    Allow simultaneous users.&n;*!  Sep  03 1999  Edgar Iglesias    Updated probe.&n;*!  Sep  03 1999  Edgar Iglesias    Added bail-out stuff if we get interrupted&n;*!                                  in the spin-lock.&n;*!&n;*!  $Log: eeprom.c,v $&n;*!  Revision 1.5  2001/06/14 14:39:51  jonashg&n;*!  Forgot to use name when registering the driver.&n;*!&n;*!  Revision 1.4  2001/06/14 14:35:47  jonashg&n;*!  * Gave driver a name and used it in printk&squot;s.&n;*!  * Cleanup.&n;*!&n;*!  Revision 1.3  2001/03/19 16:04:46  markusl&n;*!  Fixed init of fops struct&n;*!&n;*!  Revision 1.2  2001/03/19 10:35:07  markusl&n;*!  2.4 port of eeprom driver&n;*!&n;*!  Revision 1.8  2000/05/18 10:42:25  edgar&n;*!  Make sure to end write cycle on _every_ write&n;*!&n;*!  Revision 1.7  2000/01/17 17:41:01  johana&n;*!  Adjusted probing and return -ENOSPC when writing outside EEPROM&n;*!&n;*!  Revision 1.6  2000/01/17 15:50:36  johana&n;*!  Added adaptive timing adjustments and fixed autoprobing for 2k and 16k(?)&n;*!  EEPROMs&n;*!&n;*!  Revision 1.5  1999/09/03 15:07:37  edgar&n;*!  Added bail-out check to the spinlock&n;*!&n;*!  Revision 1.4  1999/09/03 12:11:17  bjornw&n;*!  Proper atomicity (need to use spinlocks, not if&squot;s). users -&gt; busy.&n;*!&n;*!&n;*!        (c) 1999 Axis Communications AB, Lund, Sweden&n;*!*****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;i2c.h&quot;
DECL|macro|D
mdefine_line|#define D(x) 
multiline_comment|/* If we should use adaptive timing or not: */
singleline_comment|//#define EEPROM_ADAPTIVE_TIMING      
DECL|macro|EEPROM_MAJOR_NR
mdefine_line|#define EEPROM_MAJOR_NR 122  /* use a LOCAL/EXPERIMENTAL major for now */
DECL|macro|EEPROM_MINOR_NR
mdefine_line|#define EEPROM_MINOR_NR 0
DECL|macro|MAX_WRITEDELAY_US
mdefine_line|#define MAX_WRITEDELAY_US 10000 /* 10 ms according to spec for 2KB EEPROM */
multiline_comment|/* This one defines how many times to try when eeprom fails. */
DECL|macro|EEPROM_RETRIES
mdefine_line|#define EEPROM_RETRIES 10
DECL|macro|EEPROM_2KB
mdefine_line|#define EEPROM_2KB (2 * 1024)
multiline_comment|/*#define EEPROM_4KB (4 * 1024)*/
multiline_comment|/* Exists but not used in Axis products */
DECL|macro|EEPROM_8KB
mdefine_line|#define EEPROM_8KB (8 * 1024 - 1 ) /* Last byte has write protection bit */
DECL|macro|EEPROM_16KB
mdefine_line|#define EEPROM_16KB (16 * 1024)
DECL|macro|i2c_delay
mdefine_line|#define i2c_delay(x) udelay(x)
multiline_comment|/*&n; *  This structure describes the attached eeprom chip.&n; *  The values are probed for.&n; */
DECL|struct|eeprom_type
r_struct
id|eeprom_type
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|sequential_write_pagesize
r_int
r_int
id|sequential_write_pagesize
suffix:semicolon
DECL|member|select_cmd
r_int
r_char
id|select_cmd
suffix:semicolon
DECL|member|usec_delay_writecycles
r_int
r_int
id|usec_delay_writecycles
suffix:semicolon
multiline_comment|/* Min time between write cycles&n;&t;&t;&t;&t;&t;   (up to 10ms for some models) */
DECL|member|usec_delay_step
r_int
r_int
id|usec_delay_step
suffix:semicolon
multiline_comment|/* For adaptive algorithm */
DECL|member|adapt_state
r_int
id|adapt_state
suffix:semicolon
multiline_comment|/* 1 = To high , 0 = Even, -1 = To low */
multiline_comment|/* this one is to keep the read/write operations atomic */
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:semicolon
DECL|member|retry_cnt_addr
r_int
id|retry_cnt_addr
suffix:semicolon
multiline_comment|/* Used to keep track of number of retries for&n;                         adaptive timing adjustments */
DECL|member|retry_cnt_read
r_int
id|retry_cnt_read
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|eeprom_open
c_func
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
suffix:semicolon
r_static
id|loff_t
id|eeprom_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
r_static
id|ssize_t
id|eeprom_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
suffix:semicolon
r_static
id|ssize_t
id|eeprom_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
suffix:semicolon
r_static
r_int
id|eeprom_close
c_func
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
suffix:semicolon
r_static
r_int
id|eeprom_address
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_static
r_int
id|read_from_eeprom
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_int
id|eeprom_write_buf
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_int
id|eeprom_read_buf
c_func
(paren
r_int
r_int
id|addr
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|eeprom_disable_write_protect
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|eeprom_name
r_static
r_const
r_char
id|eeprom_name
(braket
)braket
op_assign
l_string|&quot;eeprom&quot;
suffix:semicolon
multiline_comment|/* chip description */
DECL|variable|eeprom
r_static
r_struct
id|eeprom_type
id|eeprom
suffix:semicolon
multiline_comment|/* This is the exported file-operations structure for this device. */
DECL|variable|eeprom_fops
r_struct
id|file_operations
id|eeprom_fops
op_assign
(brace
id|llseek
suffix:colon
id|eeprom_lseek
comma
id|read
suffix:colon
id|eeprom_read
comma
id|write
suffix:colon
id|eeprom_write
comma
id|open
suffix:colon
id|eeprom_open
comma
id|release
suffix:colon
id|eeprom_close
)brace
suffix:semicolon
multiline_comment|/* eeprom init call. Probes for different eeprom models. */
DECL|function|eeprom_init
r_int
id|__init
id|eeprom_init
c_func
(paren
r_void
)paren
(brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
id|eeprom.busy
op_assign
l_int|0
suffix:semicolon
macro_line|#if CONFIG_ETRAX_I2C_EEPROM_PROBE
DECL|macro|EETEXT
mdefine_line|#define EETEXT &quot;Found&quot;
macro_line|#else
mdefine_line|#define EETEXT &quot;Assuming&quot;
macro_line|#endif
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|EEPROM_MAJOR_NR
comma
id|eeprom_name
comma
op_amp
id|eeprom_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unable to get major %d for eeprom device&bslash;n&quot;
comma
id|eeprom_name
comma
id|EEPROM_MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;EEPROM char device v0.3, (c) 2000 Axis Communications AB&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;   *  Note: Most of this probing method was taken from the printserver (5470e)&n;   *        codebase. It did not contain a way of finding the 16Kb chips&n;   *        (M24128 or variants). The method used here might not work&n;   *        for all models. If you encounter problems the easiest way&n;   *        is probably to define your model within #ifdef&squot;s, and hard-&n;   *        code it.&n;   */
id|eeprom.size
op_assign
l_int|0
suffix:semicolon
id|eeprom.usec_delay_writecycles
op_assign
l_int|4000
suffix:semicolon
multiline_comment|/*MAX_WRITEDELAY_US / EEPROM_RETRIES;*/
id|eeprom.usec_delay_step
op_assign
l_int|128
suffix:semicolon
id|eeprom.adapt_state
op_assign
l_int|0
suffix:semicolon
macro_line|#if CONFIG_ETRAX_I2C_EEPROM_PROBE
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* It&squot;s not 8k.. */
r_int
id|success
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|buf_2k_start
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Im not sure this will work... :) */
multiline_comment|/* assume 2Kb, if failure go for 16Kb */
multiline_comment|/* Test with 16kB settings.. */
multiline_comment|/* If it&squot;s a 2kB EEPROM and we address it outside it&squot;s range&n;     * it will mirror the address space:&n;     * 1. We read two locations (that are mirrored), &n;     *    if the content differs * it&squot;s a 16kB EEPROM.&n;     * 2. if it doesn&squot;t differ - write diferent value to one of the locations,&n;     *    check the other - if content still is the same it&squot;s a 2k EEPROM,&n;     *    restore original data.&n;     */
DECL|macro|LOC1
mdefine_line|#define LOC1 8
DECL|macro|LOC2
mdefine_line|#define LOC2 (0x1fb) /*1fb, 3ed, 5df, 7d1 */
multiline_comment|/* 2k settings */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
id|eeprom.select_cmd
op_assign
l_int|0xA0
suffix:semicolon
id|eeprom.sequential_write_pagesize
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_read_buf
c_func
(paren
l_int|0
comma
id|buf_2k_start
comma
l_int|16
)paren
op_eq
l_int|16
)paren
(brace
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;2k start: &squot;%16.16s&squot;&bslash;n&quot;
comma
id|buf_2k_start
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Failed to read in 2k mode!&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
)brace
multiline_comment|/* 16k settings */
id|eeprom.size
op_assign
id|EEPROM_16KB
suffix:semicolon
id|eeprom.select_cmd
op_assign
l_int|0xA0
suffix:semicolon
id|eeprom.sequential_write_pagesize
op_assign
l_int|64
suffix:semicolon
(brace
r_int
r_char
id|loc1
(braket
l_int|4
)braket
comma
id|loc2
(braket
l_int|4
)braket
comma
id|tmp
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_read_buf
c_func
(paren
id|LOC2
comma
id|loc2
comma
l_int|4
)paren
op_eq
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|eeprom_read_buf
c_func
(paren
id|LOC1
comma
id|loc1
comma
l_int|4
)paren
op_eq
l_int|4
)paren
(brace
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;0 loc1: (%i) &squot;%4.4s&squot; loc2 (%i) &squot;%4.4s&squot;&bslash;n&quot;
comma
id|LOC1
comma
id|loc1
comma
id|LOC2
comma
id|loc2
)paren
)paren
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|loc1
comma
id|loc2
comma
l_int|4
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* It&squot;s 16k */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 16k detected in step 1&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|eeprom.size
op_assign
id|EEPROM_16KB
suffix:semicolon
id|success
op_assign
l_int|1
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
multiline_comment|/* Do step 2 check */
multiline_comment|/* Invert value */
id|loc1
(braket
l_int|0
)braket
op_assign
op_complement
id|loc1
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_write_buf
c_func
(paren
id|LOC1
comma
id|loc1
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* If 2k EEPROM this write will actually write 10 bytes&n;               * from pos 0&n;               */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;1 loc1: (%i) &squot;%4.4s&squot; loc2 (%i) &squot;%4.4s&squot;&bslash;n&quot;
comma
id|LOC1
comma
id|loc1
comma
id|LOC2
comma
id|loc2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_read_buf
c_func
(paren
id|LOC1
comma
id|tmp
comma
l_int|4
)paren
op_eq
l_int|4
)paren
(brace
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;2 loc1: (%i) &squot;%4.4s&squot; tmp &squot;%4.4s&squot;&bslash;n&quot;
comma
id|LOC1
comma
id|loc1
comma
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|loc1
comma
id|tmp
comma
l_int|4
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: read and write differs! Not 16kB&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|loc1
(braket
l_int|0
)braket
op_assign
op_complement
id|loc1
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_write_buf
c_func
(paren
id|LOC1
comma
id|loc1
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|success
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Restore 2k failed during probe,&quot;
l_string|&quot; EEPROM might be corrupt!&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Go to 2k mode and write original data */
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
id|eeprom.select_cmd
op_assign
l_int|0xA0
suffix:semicolon
id|eeprom.sequential_write_pagesize
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_write_buf
c_func
(paren
l_int|0
comma
id|buf_2k_start
comma
l_int|16
)paren
op_eq
l_int|16
)paren
(brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Failed to write back 2k start!&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
)brace
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|success
)paren
(brace
r_if
c_cond
(paren
id|eeprom_read_buf
c_func
(paren
id|LOC2
comma
id|loc2
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;0 loc1: (%i) &squot;%4.4s&squot; loc2 (%i) &squot;%4.4s&squot;&bslash;n&quot;
comma
id|LOC1
comma
id|loc1
comma
id|LOC2
comma
id|loc2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|loc1
comma
id|loc2
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Data the same, must be mirrored -&gt; 2k */
multiline_comment|/* Restore data */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 2k detected in step 2&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|loc1
(braket
l_int|0
)braket
op_assign
op_complement
id|loc1
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_write_buf
c_func
(paren
id|LOC1
comma
id|loc1
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|success
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Restore 2k failed during probe,&quot;
l_string|&quot; EEPROM might be corrupt!&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
)brace
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 16k detected in step 2&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|loc1
(braket
l_int|0
)braket
op_assign
op_complement
id|loc1
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Data differs, assume 16k */
multiline_comment|/* Restore data */
r_if
c_cond
(paren
id|eeprom_write_buf
c_func
(paren
id|LOC1
comma
id|loc1
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|success
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Restore 16k failed during probe,&quot;
l_string|&quot; EEPROM might be corrupt!&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
)brace
id|eeprom.size
op_assign
id|EEPROM_16KB
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
multiline_comment|/* read LOC1 */
)brace
multiline_comment|/* address LOC1 */
r_if
c_cond
(paren
op_logical_neg
id|success
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Probing failed!, using 2KB!&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
)brace
)brace
multiline_comment|/* read */
)brace
)brace
r_else
(brace
id|i2c_outbyte
c_func
(paren
l_int|0x00
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* No 8k */
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
)brace
r_else
(brace
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
l_int|0x81
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* It&squot;s a 8kB */
id|i2c_inbyte
c_func
(paren
)paren
suffix:semicolon
id|eeprom.size
op_assign
id|EEPROM_8KB
suffix:semicolon
)brace
)brace
)brace
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ETRAX_I2C_EEPROM_16KB)
id|eeprom.size
op_assign
id|EEPROM_16KB
suffix:semicolon
macro_line|#elif defined(CONFIG_ETRAX_I2C_EEPROM_8KB)
id|eeprom.size
op_assign
id|EEPROM_8KB
suffix:semicolon
macro_line|#elif defined(CONFIG_ETRAX_I2C_EEPROM_2KB)
id|eeprom.size
op_assign
id|EEPROM_2KB
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|eeprom.size
)paren
(brace
r_case
(paren
id|EEPROM_2KB
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: &quot;
id|EETEXT
l_string|&quot; i2c compatible 2Kb eeprom.&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|eeprom.sequential_write_pagesize
op_assign
l_int|16
suffix:semicolon
id|eeprom.select_cmd
op_assign
l_int|0xA0
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|EEPROM_8KB
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: &quot;
id|EETEXT
l_string|&quot; i2c compatible 8Kb eeprom.&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|eeprom.sequential_write_pagesize
op_assign
l_int|16
suffix:semicolon
id|eeprom.select_cmd
op_assign
l_int|0x80
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|EEPROM_16KB
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: &quot;
id|EETEXT
l_string|&quot; i2c compatible 16Kb eeprom.&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|eeprom.sequential_write_pagesize
op_assign
l_int|64
suffix:semicolon
id|eeprom.select_cmd
op_assign
l_int|0xA0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|eeprom.size
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Did not find a supported eeprom&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|eeprom_disable_write_protect
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Opens the device. */
DECL|function|eeprom_open
r_static
r_int
id|eeprom_open
c_func
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
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_ne
id|EEPROM_MINOR_NR
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_ne
id|EEPROM_MAJOR_NR
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eeprom.size
OG
l_int|0
)paren
(brace
multiline_comment|/* OK */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* No EEprom found */
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* Changes the current file position. */
DECL|function|eeprom_lseek
r_static
id|loff_t
id|eeprom_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
multiline_comment|/*&n; *  orig 0: position from begning of eeprom&n; *  orig 1: relative from current position&n; *  orig 2: position from last eeprom address&n; */
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|file-&gt;f_pos
op_assign
id|eeprom.size
op_minus
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* truncate position */
r_if
c_cond
(paren
id|file-&gt;f_pos
OL
l_int|0
)paren
(brace
id|file-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
id|eeprom.size
)paren
(brace
id|file-&gt;f_pos
op_assign
id|eeprom.size
op_minus
l_int|1
suffix:semicolon
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
)brace
r_return
(paren
id|file-&gt;f_pos
)paren
suffix:semicolon
)brace
multiline_comment|/* Reads data from eeprom. */
DECL|function|eeprom_read_buf
r_static
r_int
id|eeprom_read_buf
c_func
(paren
r_int
r_int
id|addr
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|file
id|f
suffix:semicolon
id|f.f_pos
op_assign
id|addr
suffix:semicolon
r_return
id|eeprom_read
c_func
(paren
op_amp
id|f
comma
id|buf
comma
id|count
comma
op_amp
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Reads data from eeprom. */
DECL|function|eeprom_read
r_static
id|ssize_t
id|eeprom_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_int
id|i
comma
id|read
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_int
r_char
id|page
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|eeprom.size
)paren
multiline_comment|/* Address i 0 - (size-1) */
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_while
c_loop
(paren
id|eeprom.busy
)paren
(brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
multiline_comment|/* bail out if we get interrupted */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
id|eeprom.busy
op_increment
suffix:semicolon
id|page
op_assign
(paren
r_int
r_char
)paren
(paren
id|p
op_rshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eeprom_address
c_func
(paren
id|p
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Read failed to address the eeprom: &quot;
l_string|&quot;0x%08X (%i) page: %i&bslash;n&quot;
comma
id|eeprom_name
comma
id|p
comma
id|p
comma
id|page
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t forget to wake them up */
id|eeprom.busy
op_decrement
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|p
op_plus
id|count
)paren
OG
id|eeprom.size
)paren
(brace
multiline_comment|/* truncate count */
id|count
op_assign
id|eeprom.size
op_minus
id|p
suffix:semicolon
)brace
multiline_comment|/* stop dummy write op and initiate the read op */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* special case for small eeproms */
r_if
c_cond
(paren
id|eeprom.size
OL
id|EEPROM_16KB
)paren
(brace
id|i2c_outbyte
c_func
(paren
id|eeprom.select_cmd
op_or
l_int|1
op_or
(paren
id|page
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* go on with the actual read */
id|read
op_assign
id|read_from_eeprom
c_func
(paren
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
OG
l_int|0
)paren
(brace
id|file-&gt;f_pos
op_add_assign
id|read
suffix:semicolon
)brace
id|eeprom.busy
op_decrement
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/* Writes data to eeprom. */
DECL|function|eeprom_write_buf
r_static
r_int
id|eeprom_write_buf
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|file
id|f
suffix:semicolon
id|f.f_pos
op_assign
id|addr
suffix:semicolon
r_return
id|eeprom_write
c_func
(paren
op_amp
id|f
comma
id|buf
comma
id|count
comma
op_amp
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Writes data to eeprom. */
DECL|function|eeprom_write
r_static
id|ssize_t
id|eeprom_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_int
id|i
comma
id|written
comma
id|restart
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|p
suffix:semicolon
r_while
c_loop
(paren
id|eeprom.busy
)paren
(brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
multiline_comment|/* bail out if we get interrupted */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
id|eeprom.busy
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|EEPROM_RETRIES
)paren
op_logical_and
(paren
id|restart
OG
l_int|0
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|restart
op_assign
l_int|0
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_while
c_loop
(paren
(paren
id|written
OL
id|count
)paren
op_logical_and
(paren
id|p
OL
id|eeprom.size
)paren
)paren
(brace
multiline_comment|/* address the eeprom */
r_if
c_cond
(paren
op_logical_neg
id|eeprom_address
c_func
(paren
id|p
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Write failed to address the eeprom: &quot;
l_string|&quot;0x%08X (%i) &bslash;n&quot;
comma
id|eeprom_name
comma
id|p
comma
id|p
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t forget to wake them up */
id|eeprom.busy
op_decrement
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
macro_line|#ifdef EEPROM_ADAPTIVE_TIMING      
multiline_comment|/* Adaptive algorithm to adjust timing */
r_if
c_cond
(paren
id|eeprom.retry_cnt_addr
OG
l_int|0
)paren
(brace
multiline_comment|/* To Low now */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;&gt;D=%i d=%i&bslash;n&quot;
comma
id|eeprom.usec_delay_writecycles
comma
id|eeprom.usec_delay_step
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom.usec_delay_step
OL
l_int|4
)paren
(brace
id|eeprom.usec_delay_step
op_increment
suffix:semicolon
id|eeprom.usec_delay_writecycles
op_add_assign
id|eeprom.usec_delay_step
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|eeprom.adapt_state
OG
l_int|0
)paren
(brace
multiline_comment|/* To Low before */
id|eeprom.usec_delay_step
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|eeprom.usec_delay_step
OG
l_int|2
)paren
(brace
id|eeprom.usec_delay_step
op_decrement
suffix:semicolon
)brace
id|eeprom.usec_delay_writecycles
op_add_assign
id|eeprom.usec_delay_step
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|eeprom.adapt_state
OL
l_int|0
)paren
(brace
multiline_comment|/* To High before (toggle dir) */
id|eeprom.usec_delay_writecycles
op_add_assign
id|eeprom.usec_delay_step
suffix:semicolon
r_if
c_cond
(paren
id|eeprom.usec_delay_step
OG
l_int|1
)paren
(brace
id|eeprom.usec_delay_step
op_div_assign
l_int|2
suffix:semicolon
id|eeprom.usec_delay_step
op_decrement
suffix:semicolon
)brace
)brace
)brace
id|eeprom.adapt_state
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* To High (or good) now */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;&lt;D=%i d=%i&bslash;n&quot;
comma
id|eeprom.usec_delay_writecycles
comma
id|eeprom.usec_delay_step
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom.adapt_state
OL
l_int|0
)paren
(brace
multiline_comment|/* To High before */
r_if
c_cond
(paren
id|eeprom.usec_delay_step
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|eeprom.usec_delay_step
OG
l_int|0
)paren
(brace
id|eeprom.usec_delay_step
op_mul_assign
l_int|2
suffix:semicolon
id|eeprom.usec_delay_step
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eeprom.usec_delay_writecycles
OG
id|eeprom.usec_delay_step
)paren
(brace
id|eeprom.usec_delay_writecycles
op_sub_assign
id|eeprom.usec_delay_step
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|eeprom.adapt_state
OG
l_int|0
)paren
(brace
multiline_comment|/* To Low before (toggle dir) */
r_if
c_cond
(paren
id|eeprom.usec_delay_writecycles
OG
id|eeprom.usec_delay_step
)paren
(brace
id|eeprom.usec_delay_writecycles
op_sub_assign
id|eeprom.usec_delay_step
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eeprom.usec_delay_step
OG
l_int|1
)paren
(brace
id|eeprom.usec_delay_step
op_div_assign
l_int|2
suffix:semicolon
id|eeprom.usec_delay_step
op_decrement
suffix:semicolon
)brace
id|eeprom.adapt_state
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eeprom.adapt_state
OG
op_minus
l_int|100
)paren
(brace
id|eeprom.adapt_state
op_decrement
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Restart adaption */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;#Restart&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|eeprom.usec_delay_step
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif /* EEPROM_ADAPTIVE_TIMING */
multiline_comment|/* write until we hit a page boundary or count */
r_do
(brace
id|i2c_outbyte
c_func
(paren
id|buf
(braket
id|written
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|restart
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: write error, retrying. %d&bslash;n&quot;
comma
id|eeprom_name
comma
id|i
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|written
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|written
OL
id|count
op_logical_and
(paren
id|p
op_mod
id|eeprom.sequential_write_pagesize
)paren
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* end write cycle */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|eeprom.usec_delay_writecycles
)paren
suffix:semicolon
)brace
multiline_comment|/* while */
)brace
multiline_comment|/* for  */
id|eeprom.busy
op_decrement
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|eeprom.wait_q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
op_eq
l_int|0
op_logical_and
id|file-&gt;f_pos
op_ge
id|eeprom.size
)paren
(brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|file-&gt;f_pos
op_add_assign
id|written
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
multiline_comment|/* Closes the device. */
DECL|function|eeprom_close
r_static
r_int
id|eeprom_close
c_func
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
multiline_comment|/* do nothing for now */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Sets the current address of the eeprom. */
DECL|function|eeprom_address
r_static
r_int
id|eeprom_address
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_char
id|page
comma
id|offset
suffix:semicolon
id|page
op_assign
(paren
r_int
r_char
)paren
(paren
id|addr
op_rshift
l_int|8
)paren
suffix:semicolon
id|offset
op_assign
(paren
r_int
r_char
)paren
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EEPROM_RETRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* start a dummy write for addressing */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom.size
op_eq
id|EEPROM_16KB
)paren
(brace
id|i2c_outbyte
c_func
(paren
id|eeprom.select_cmd
)paren
suffix:semicolon
id|i2c_getack
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|i2c_outbyte
c_func
(paren
id|eeprom.select_cmd
op_or
(paren
id|page
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* retry */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Must have a delay here.. 500 works, &gt;50, 100-&gt;works 5th time*/
id|i2c_delay
c_func
(paren
id|MAX_WRITEDELAY_US
op_div
id|EEPROM_RETRIES
op_star
id|i
)paren
suffix:semicolon
multiline_comment|/* The chip needs up to 10 ms from write stop to next start */
)brace
r_else
(brace
id|i2c_outbyte
c_func
(paren
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* retry */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
)brace
id|eeprom.retry_cnt_addr
op_assign
id|i
suffix:semicolon
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%i&bslash;n&quot;
comma
id|eeprom.retry_cnt_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom.retry_cnt_addr
op_eq
id|EEPROM_RETRIES
)paren
(brace
multiline_comment|/* failed */
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Reads from current adress. */
DECL|function|read_from_eeprom
r_static
r_int
id|read_from_eeprom
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|i
comma
id|read
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EEPROM_RETRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|eeprom.size
op_eq
id|EEPROM_16KB
)paren
(brace
id|i2c_outbyte
c_func
(paren
id|eeprom.select_cmd
op_or
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
suffix:semicolon
)brace
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|EEPROM_RETRIES
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: failed to read from eeprom&bslash;n&quot;
comma
id|eeprom_name
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|read
OL
id|count
)paren
)paren
(brace
id|buf
(braket
id|read
op_increment
)braket
op_assign
id|i2c_inbyte
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;     *  make sure we don&squot;t ack last byte or you will get very strange&n;     *  results!&n;     */
r_if
c_cond
(paren
id|read
OL
id|count
)paren
(brace
id|i2c_sendack
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* stop the operation */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/* Disables write protection if applicable. */
DECL|macro|DBP_SAVE
mdefine_line|#define DBP_SAVE(x)
DECL|macro|ax_printf
mdefine_line|#define ax_printf printk
DECL|function|eeprom_disable_write_protect
r_static
r_void
id|eeprom_disable_write_protect
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Disable write protect */
r_if
c_cond
(paren
id|eeprom.size
op_eq
id|EEPROM_8KB
)paren
(brace
multiline_comment|/* Step 1 Set WEL = 1 (write 00000010 to address 1FFFh */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
l_int|0xbe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_outbyte
c_func
(paren
l_int|0xFF
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 2&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_outbyte
c_func
(paren
l_int|0x02
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 3&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Step 2 Set RWEL = 1 (write 00000110 to address 1FFFh */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
l_int|0xbe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 55&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_outbyte
c_func
(paren
l_int|0xFF
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 52&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_outbyte
c_func
(paren
l_int|0x06
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 53&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Step 3 Set BP1, BP0, and/or WPEN bits (write 00000110 to address 1FFFh */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
l_int|0xbe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 56&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_outbyte
c_func
(paren
l_int|0xFF
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 57&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_outbyte
c_func
(paren
l_int|0x06
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|DBP_SAVE
c_func
(paren
id|ax_printf
c_func
(paren
l_string|&quot;Get ack returns false 58&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Write protect disabled */
)brace
)brace
DECL|variable|eeprom_init
id|module_init
c_func
(paren
id|eeprom_init
)paren
suffix:semicolon
eof
