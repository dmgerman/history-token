multiline_comment|/*&n; * Tape class device support&n; *&n; * Author: Stefan Bader &lt;shbader@de.ibm.com&gt;&n; * Based on simple class device code by Greg K-H&n; */
macro_line|#ifndef __TAPE_CLASS_H__
DECL|macro|__TAPE_CLASS_H__
mdefine_line|#define __TAPE_CLASS_H__
macro_line|#if 0
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/kobj_map.h&gt;
macro_line|#include &lt;linux/cdev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
DECL|macro|TAPE390_INTERNAL_CLASS
mdefine_line|#define TAPE390_INTERNAL_CLASS
multiline_comment|/*&n; * Register a tape device and return a pointer to the cdev structure.&n; *&n; * device&n; *&t;The pointer to the struct device of the physical (base) device.&n; * drivername&n; *&t;The pointer to the drivers name for it&squot;s character devices.&n; * dev&n; *&t;The intended major/minor number. The major number may be 0 to&n; *&t;get a dynamic major number.&n; * fops&n; *&t;The pointer to the drivers file operations for the tape device.&n; * devname&n; *&t;The pointer to the name of the character device.&n; */
r_struct
id|cdev
op_star
id|register_tape_dev
c_func
(paren
r_struct
id|device
op_star
id|device
comma
id|dev_t
id|dev
comma
r_struct
id|file_operations
op_star
id|fops
comma
r_char
op_star
id|devname
)paren
suffix:semicolon
r_void
id|unregister_tape_dev
c_func
(paren
r_struct
id|cdev
op_star
id|cdev
)paren
suffix:semicolon
macro_line|#ifdef TAPE390_INTERNAL_CLASS
r_int
id|tape_setup_class
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|tape_cleanup_class
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __TAPE_CLASS_H__ */
eof
