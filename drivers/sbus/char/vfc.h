macro_line|#ifndef _LINUX_VFC_H_
DECL|macro|_LINUX_VFC_H_
mdefine_line|#define _LINUX_VFC_H_
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
multiline_comment|/*&n; * The control register for the vfc is at offset 0x4000&n; * The first field ram bank is located at offset 0x5000&n; * The second field ram bank is at offset 0x7000&n; * i2c_reg address the Phillips PCF8584(see notes in vfc_i2c.c) &n; *    data and transmit register.&n; * i2c_s1 controls register s1 of the PCF8584&n; * i2c_write seems to be similar to i2c_write but I am not &n; *    quite sure why sun uses it&n; * &n; * I am also not sure whether or not you can read the fram bank as a&n; * whole or whether you must read each word individually from offset&n; * 0x5000 as soon as I figure it out I will update this file */
DECL|struct|vfc_regs
r_struct
id|vfc_regs
(brace
DECL|member|pad1
r_char
id|pad1
(braket
l_int|0x4000
)braket
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
multiline_comment|/* Offset 0x4000 */
DECL|member|pad2
r_char
id|pad2
(braket
l_int|0xffb
)braket
suffix:semicolon
multiline_comment|/* from offset 0x4004 to 0x5000 */
DECL|member|fram_bank1
r_int
r_int
id|fram_bank1
suffix:semicolon
multiline_comment|/* Offset 0x5000 */
DECL|member|pad3
r_char
id|pad3
(braket
l_int|0xffb
)braket
suffix:semicolon
multiline_comment|/* from offset 0x5004 to 0x6000 */
DECL|member|i2c_reg
r_int
r_int
id|i2c_reg
suffix:semicolon
multiline_comment|/* Offset 0x6000 */
DECL|member|i2c_magic2
r_int
r_int
id|i2c_magic2
suffix:semicolon
multiline_comment|/* Offset 0x6004 */
DECL|member|i2c_s1
r_int
r_int
id|i2c_s1
suffix:semicolon
multiline_comment|/* Offset 0x6008 */
DECL|member|i2c_write
r_int
r_int
id|i2c_write
suffix:semicolon
multiline_comment|/* Offset 0x600c */
DECL|member|pad4
r_char
id|pad4
(braket
l_int|0xff0
)braket
suffix:semicolon
multiline_comment|/* from offset 0x6010 to 0x7000 */
DECL|member|fram_bank2
r_int
r_int
id|fram_bank2
suffix:semicolon
multiline_comment|/* Offset 0x7000 */
DECL|member|pad5
r_char
id|pad5
(braket
l_int|0x1000
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VFC_SAA9051_NR
mdefine_line|#define VFC_SAA9051_NR (13)
DECL|macro|VFC_SAA9051_ADDR
mdefine_line|#define VFC_SAA9051_ADDR (0x8a)
multiline_comment|/* The saa9051 returns the following for its status &n;&t; * bit 0 - 0&n;&t; * bit 1 - SECAM color detected (1=found,0=not found)&n;&t; * bit 2 - COLOR detected (1=found,0=not found)&n;&t; * bit 3 - 0&n;&t; * bit 4 - Field frequency bit (1=60Hz (NTSC), 0=50Hz (PAL))&n;&t; * bit 5 - 1&n;&t; * bit 6 - horizontal frequency lock (1=transmitter found,&n;&t; *                                    0=no transmitter)&n;&t; * bit 7 - Power on reset bit (1=reset,0=at least one successful &n;&t; *                                       read of the status byte)&n;&t; */
DECL|macro|VFC_SAA9051_PONRES
mdefine_line|#define VFC_SAA9051_PONRES (0x80)
DECL|macro|VFC_SAA9051_HLOCK
mdefine_line|#define VFC_SAA9051_HLOCK (0x40)
DECL|macro|VFC_SAA9051_FD
mdefine_line|#define VFC_SAA9051_FD (0x10)
DECL|macro|VFC_SAA9051_CD
mdefine_line|#define VFC_SAA9051_CD (0x04)
DECL|macro|VFC_SAA9051_CS
mdefine_line|#define VFC_SAA9051_CS (0x02)
multiline_comment|/* The various saa9051 sub addresses */
DECL|macro|VFC_SAA9051_IDEL
mdefine_line|#define VFC_SAA9051_IDEL (0) 
DECL|macro|VFC_SAA9051_HSY_START
mdefine_line|#define VFC_SAA9051_HSY_START (1)
DECL|macro|VFC_SAA9051_HSY_STOP
mdefine_line|#define VFC_SAA9051_HSY_STOP (2)
DECL|macro|VFC_SAA9051_HC_START
mdefine_line|#define VFC_SAA9051_HC_START (3)
DECL|macro|VFC_SAA9051_HC_STOP
mdefine_line|#define VFC_SAA9051_HC_STOP (4)
DECL|macro|VFC_SAA9051_HS_START
mdefine_line|#define VFC_SAA9051_HS_START (5)
DECL|macro|VFC_SAA9051_HORIZ_PEAK
mdefine_line|#define VFC_SAA9051_HORIZ_PEAK (6)
DECL|macro|VFC_SAA9051_HUE
mdefine_line|#define VFC_SAA9051_HUE (7)
DECL|macro|VFC_SAA9051_C1
mdefine_line|#define VFC_SAA9051_C1 (8)
DECL|macro|VFC_SAA9051_C2
mdefine_line|#define VFC_SAA9051_C2 (9)
DECL|macro|VFC_SAA9051_C3
mdefine_line|#define VFC_SAA9051_C3 (0xa)
DECL|macro|VFC_SAA9051_SECAM_DELAY
mdefine_line|#define VFC_SAA9051_SECAM_DELAY (0xb)
multiline_comment|/* Bit settings for saa9051 sub address 0x06 */
DECL|macro|VFC_SAA9051_AP1
mdefine_line|#define VFC_SAA9051_AP1 (0x01)
DECL|macro|VFC_SAA9051_AP2
mdefine_line|#define VFC_SAA9051_AP2 (0x02)
DECL|macro|VFC_SAA9051_COR1
mdefine_line|#define VFC_SAA9051_COR1 (0x04)
DECL|macro|VFC_SAA9051_COR2
mdefine_line|#define VFC_SAA9051_COR2 (0x08)
DECL|macro|VFC_SAA9051_BP1
mdefine_line|#define VFC_SAA9051_BP1 (0x10)
DECL|macro|VFC_SAA9051_BP2
mdefine_line|#define VFC_SAA9051_BP2 (0x20)
DECL|macro|VFC_SAA9051_PF
mdefine_line|#define VFC_SAA9051_PF (0x40)
DECL|macro|VFC_SAA9051_BY
mdefine_line|#define VFC_SAA9051_BY (0x80)
multiline_comment|/* Bit settings for saa9051 sub address 0x08 */
DECL|macro|VFC_SAA9051_CCFR0
mdefine_line|#define VFC_SAA9051_CCFR0 (0x01)
DECL|macro|VFC_SAA9051_CCFR1
mdefine_line|#define VFC_SAA9051_CCFR1 (0x02)
DECL|macro|VFC_SAA9051_YPN
mdefine_line|#define VFC_SAA9051_YPN (0x04)
DECL|macro|VFC_SAA9051_ALT
mdefine_line|#define VFC_SAA9051_ALT (0x08)
DECL|macro|VFC_SAA9051_CO
mdefine_line|#define VFC_SAA9051_CO (0x10)
DECL|macro|VFC_SAA9051_VTR
mdefine_line|#define VFC_SAA9051_VTR (0x20)
DECL|macro|VFC_SAA9051_FS
mdefine_line|#define VFC_SAA9051_FS (0x40)
DECL|macro|VFC_SAA9051_HPLL
mdefine_line|#define VFC_SAA9051_HPLL (0x80)
multiline_comment|/* Bit settings for saa9051 sub address 9 */
DECL|macro|VFC_SAA9051_SS0
mdefine_line|#define VFC_SAA9051_SS0 (0x01)
DECL|macro|VFC_SAA9051_SS1
mdefine_line|#define VFC_SAA9051_SS1 (0x02)
DECL|macro|VFC_SAA9051_AFCC
mdefine_line|#define VFC_SAA9051_AFCC (0x04)
DECL|macro|VFC_SAA9051_CI
mdefine_line|#define VFC_SAA9051_CI (0x08)
DECL|macro|VFC_SAA9051_SA9D4
mdefine_line|#define VFC_SAA9051_SA9D4 (0x10) /* Don&squot;t care bit */
DECL|macro|VFC_SAA9051_OEC
mdefine_line|#define VFC_SAA9051_OEC (0x20)
DECL|macro|VFC_SAA9051_OEY
mdefine_line|#define VFC_SAA9051_OEY (0x40)
DECL|macro|VFC_SAA9051_VNL
mdefine_line|#define VFC_SAA9051_VNL (0x80)
multiline_comment|/* Bit settings for saa9051 sub address 0x0A */
DECL|macro|VFC_SAA9051_YDL0
mdefine_line|#define VFC_SAA9051_YDL0 (0x01)
DECL|macro|VFC_SAA9051_YDL1
mdefine_line|#define VFC_SAA9051_YDL1 (0x02)
DECL|macro|VFC_SAA9051_YDL2
mdefine_line|#define VFC_SAA9051_YDL2 (0x04)
DECL|macro|VFC_SAA9051_SS2
mdefine_line|#define VFC_SAA9051_SS2 (0x08)
DECL|macro|VFC_SAA9051_SS3
mdefine_line|#define VFC_SAA9051_SS3 (0x10)
DECL|macro|VFC_SAA9051_YC
mdefine_line|#define VFC_SAA9051_YC (0x20)
DECL|macro|VFC_SAA9051_CT
mdefine_line|#define VFC_SAA9051_CT (0x40)
DECL|macro|VFC_SAA9051_SYC
mdefine_line|#define VFC_SAA9051_SYC (0x80)
DECL|macro|VFC_SAA9051_SA
mdefine_line|#define VFC_SAA9051_SA(a,b) ((a)-&gt;saa9051_state_array[(b)+1])
DECL|macro|vfc_update_saa9051
mdefine_line|#define vfc_update_saa9051(a) (vfc_i2c_sendbuf((a),VFC_SAA9051_ADDR,&bslash;&n;&t;&t;&t;&t;&t;    (a)-&gt;saa9051_state_array,&bslash;&n;&t;&t;&t;&t;&t;    VFC_SAA9051_NR))
DECL|struct|vfc_dev
r_struct
id|vfc_dev
(brace
DECL|member|regs
r_volatile
r_struct
id|vfc_regs
op_star
id|regs
suffix:semicolon
DECL|member|phys_regs
r_struct
id|vfc_regs
op_star
id|phys_regs
suffix:semicolon
DECL|member|control_reg
r_int
r_int
id|control_reg
suffix:semicolon
DECL|member|de
id|devfs_handle_t
id|de
suffix:semicolon
DECL|member|device_lock_sem
r_struct
id|semaphore
id|device_lock_sem
suffix:semicolon
DECL|member|poll_timer
r_struct
id|timer_list
id|poll_timer
suffix:semicolon
DECL|member|poll_wait
id|wait_queue_head_t
id|poll_wait
suffix:semicolon
DECL|member|instance
r_int
id|instance
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:semicolon
DECL|member|which_io
r_int
r_int
id|which_io
suffix:semicolon
DECL|member|saa9051_state_array
r_int
r_char
id|saa9051_state_array
(braket
id|VFC_SAA9051_NR
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|vfc_dev
op_star
op_star
id|vfc_dev_lst
suffix:semicolon
r_void
id|captstat_reset
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_void
id|memptr_reset
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_int
id|vfc_pcf8584_init
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_void
id|vfc_i2c_delay_no_busy
c_func
(paren
r_struct
id|vfc_dev
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|vfc_i2c_delay
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_int
id|vfc_i2c_sendbuf
c_func
(paren
r_struct
id|vfc_dev
op_star
comma
r_int
r_char
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|vfc_i2c_recvbuf
c_func
(paren
r_struct
id|vfc_dev
op_star
comma
r_int
r_char
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|vfc_i2c_reset_bus
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_int
id|vfc_init_i2c_bus
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_void
id|vfc_lock_device
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
r_void
id|vfc_unlock_device
c_func
(paren
r_struct
id|vfc_dev
op_star
)paren
suffix:semicolon
DECL|macro|VFC_CONTROL_DIAGMODE
mdefine_line|#define VFC_CONTROL_DIAGMODE  0x10000000
DECL|macro|VFC_CONTROL_MEMPTR
mdefine_line|#define VFC_CONTROL_MEMPTR    0x20000000
DECL|macro|VFC_CONTROL_CAPTURE
mdefine_line|#define VFC_CONTROL_CAPTURE   0x02000000
DECL|macro|VFC_CONTROL_CAPTRESET
mdefine_line|#define VFC_CONTROL_CAPTRESET 0x04000000
DECL|macro|VFC_STATUS_CAPTURE
mdefine_line|#define VFC_STATUS_CAPTURE    0x08000000
macro_line|#ifdef VFC_IOCTL_DEBUG
DECL|macro|VFC_IOCTL_DEBUG_PRINTK
mdefine_line|#define VFC_IOCTL_DEBUG_PRINTK(a) printk a
macro_line|#else
DECL|macro|VFC_IOCTL_DEBUG_PRINTK
mdefine_line|#define VFC_IOCTL_DEBUG_PRINTK(a)
macro_line|#endif
macro_line|#ifdef VFC_I2C_DEBUG
DECL|macro|VFC_I2C_DEBUG_PRINTK
mdefine_line|#define VFC_I2C_DEBUG_PRINTK(a) printk a
macro_line|#else
DECL|macro|VFC_I2C_DEBUG_PRINTK
mdefine_line|#define VFC_I2C_DEBUG_PRINTK(a)
macro_line|#endif
macro_line|#endif /* _LINUX_VFC_H_ */
eof
