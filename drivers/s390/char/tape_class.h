multiline_comment|/*&n; * (C) Copyright IBM Corp. 2004   All Rights Reserved.&n; * tape_class.h ($Revision: 1.4 $)&n; *&n; * Tape class device support&n; *&n; * Author: Stefan Bader &lt;shbader@de.ibm.com&gt;&n; * Based on simple class device code by Greg K-H&n; */
macro_line|#ifndef __TAPE_CLASS_H__
DECL|macro|__TAPE_CLASS_H__
mdefine_line|#define __TAPE_CLASS_H__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/kobj_map.h&gt;
macro_line|#include &lt;linux/cdev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
DECL|macro|TAPECLASS_NAME_LEN
mdefine_line|#define TAPECLASS_NAME_LEN&t;32
DECL|struct|tape_class_device
r_struct
id|tape_class_device
(brace
DECL|member|char_device
r_struct
id|cdev
op_star
id|char_device
suffix:semicolon
DECL|member|class_device
r_struct
id|class_device
op_star
id|class_device
suffix:semicolon
DECL|member|device_name
r_char
id|device_name
(braket
id|TAPECLASS_NAME_LEN
)braket
suffix:semicolon
DECL|member|mode_name
r_char
id|mode_name
(braket
id|TAPECLASS_NAME_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Register a tape device and return a pointer to the tape class device&n; * created by the call.&n; *&n; * device&n; *&t;The pointer to the struct device of the physical (base) device.&n; * dev&n; *&t;The intended major/minor number. The major number may be 0 to&n; *&t;get a dynamic major number.&n; * fops&n; *&t;The pointer to the drivers file operations for the tape device.&n; * device_name&n; *&t;Pointer to the logical device name (will also be used as kobject name&n; *&t;of the cdev). This can also be called the name of the tape class&n; *&t;device.&n; * mode_name&n; *&t;Points to the name of the tape mode. This creates a link with that&n; *&t;name from the physical device to the logical device (class).&n; */
r_struct
id|tape_class_device
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
id|device_name
comma
r_char
op_star
id|node_name
)paren
suffix:semicolon
r_void
id|unregister_tape_dev
c_func
(paren
r_struct
id|tape_class_device
op_star
id|tcd
)paren
suffix:semicolon
macro_line|#endif /* __TAPE_CLASS_H__ */
eof
