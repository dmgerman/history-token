multiline_comment|/*********************************************************************&n; *&n; * Filename:      irias_object.c&n; * Version:       0.3&n; * Description:   IAS object database and functions&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Thu Oct  1 22:50:04 1998&n; * Modified at:   Wed Dec 15 11:23:16 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *&n; *     Copyright (c) 1998-1999 Dag Brattli, All Rights Reserved.&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is&n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
DECL|variable|objects
id|hashbin_t
op_star
id|objects
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; *  Used when a missing value needs to be returned&n; */
DECL|variable|missing
r_struct
id|ias_value
id|missing
op_assign
(brace
id|IAS_MISSING
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Function strndup (str, max)&n; *&n; *    My own kernel version of strndup!&n; *&n; * Faster, check boundary... Jean II&n; */
DECL|function|strndup
r_char
op_star
id|strndup
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|max
)paren
(brace
r_char
op_star
id|new_str
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* Check string */
r_if
c_cond
(paren
id|str
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Check length, truncate */
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|max
)paren
(brace
id|len
op_assign
id|max
suffix:semicolon
)brace
multiline_comment|/* Allocate new string */
id|new_str
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_str
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to kmalloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Copy and truncate */
id|memcpy
c_func
(paren
id|new_str
comma
id|str
comma
id|len
)paren
suffix:semicolon
id|new_str
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|new_str
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ias_new_object (name, id)&n; *&n; *    Create a new IAS object&n; *&n; */
DECL|function|irias_new_object
r_struct
id|ias_object
op_star
id|irias_new_object
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|id
)paren
(brace
r_struct
id|ias_object
op_star
id|obj
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|obj
op_assign
(paren
r_struct
id|ias_object
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_object
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj
op_eq
l_int|NULL
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Unable to allocate object!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|obj
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_object
)paren
)paren
suffix:semicolon
id|obj-&gt;magic
op_assign
id|IAS_OBJECT_MAGIC
suffix:semicolon
id|obj-&gt;name
op_assign
id|strndup
c_func
(paren
id|name
comma
id|IAS_MAX_CLASSNAME
)paren
suffix:semicolon
id|obj-&gt;id
op_assign
id|id
suffix:semicolon
multiline_comment|/* Locking notes : the attrib spinlock has lower precendence&n;&t; * than the objects spinlock. Never grap the objects spinlock&n;&t; * while holding any attrib spinlock (risk of deadlock). Jean II */
id|obj-&gt;attribs
op_assign
id|hashbin_new
c_func
(paren
id|HB_LOCK
)paren
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_delete_attrib (attrib)&n; *&n; *    Delete given attribute and deallocate all its memory&n; *&n; */
DECL|function|__irias_delete_attrib
r_void
id|__irias_delete_attrib
c_func
(paren
r_struct
id|ias_attrib
op_star
id|attrib
)paren
(brace
id|ASSERT
c_func
(paren
id|attrib
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|attrib-&gt;magic
op_eq
id|IAS_ATTRIB_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrib-&gt;name
)paren
id|kfree
c_func
(paren
id|attrib-&gt;name
)paren
suffix:semicolon
id|irias_delete_value
c_func
(paren
id|attrib-&gt;value
)paren
suffix:semicolon
id|attrib-&gt;magic
op_assign
op_complement
id|IAS_ATTRIB_MAGIC
suffix:semicolon
id|kfree
c_func
(paren
id|attrib
)paren
suffix:semicolon
)brace
DECL|function|__irias_delete_object
r_void
id|__irias_delete_object
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
)paren
(brace
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;name
)paren
id|kfree
c_func
(paren
id|obj-&gt;name
)paren
suffix:semicolon
id|hashbin_delete
c_func
(paren
id|obj-&gt;attribs
comma
(paren
id|FREE_FUNC
)paren
id|__irias_delete_attrib
)paren
suffix:semicolon
id|obj-&gt;magic
op_assign
op_complement
id|IAS_OBJECT_MAGIC
suffix:semicolon
id|kfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_delete_object (obj)&n; *&n; *    Remove object from hashbin and deallocate all attributes assosiated with&n; *    with this object and the object itself&n; *&n; */
DECL|function|irias_delete_object
r_int
id|irias_delete_object
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
)paren
(brace
r_struct
id|ias_object
op_star
id|node
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|node
op_assign
id|hashbin_remove_this
c_func
(paren
id|objects
comma
(paren
id|irda_queue_t
op_star
)paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Already removed */
id|__irias_delete_object
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_delete_attrib (obj)&n; *&n; *    Remove attribute from hashbin and, if it was the last attribute of&n; *    the object, remove the object as well.&n; *&n; */
DECL|function|irias_delete_attrib
r_int
id|irias_delete_attrib
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
comma
r_struct
id|ias_attrib
op_star
id|attrib
)paren
(brace
r_struct
id|ias_attrib
op_star
id|node
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|attrib
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Remove attribute from object */
id|node
op_assign
id|hashbin_remove_this
c_func
(paren
id|obj-&gt;attribs
comma
(paren
id|irda_queue_t
op_star
)paren
id|attrib
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Already removed or non-existent */
multiline_comment|/* Deallocate attribute */
id|__irias_delete_attrib
c_func
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/* Check if object has still some attributes */
id|node
op_assign
(paren
r_struct
id|ias_attrib
op_star
)paren
id|hashbin_get_first
c_func
(paren
id|obj-&gt;attribs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
id|irias_delete_object
c_func
(paren
id|obj
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_insert_object (obj)&n; *&n; *    Insert an object into the LM-IAS database&n; *&n; */
DECL|function|irias_insert_object
r_void
id|irias_insert_object
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
)paren
(brace
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|hashbin_insert
c_func
(paren
id|objects
comma
(paren
id|irda_queue_t
op_star
)paren
id|obj
comma
l_int|0
comma
id|obj-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_find_object (name)&n; *&n; *    Find object with given name&n; *&n; */
DECL|function|irias_find_object
r_struct
id|ias_object
op_star
id|irias_find_object
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|ASSERT
c_func
(paren
id|name
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Unsafe (locking), object might change */
r_return
id|hashbin_lock_find
c_func
(paren
id|objects
comma
l_int|0
comma
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_find_attrib (obj, name)&n; *&n; *    Find named attribute in object&n; *&n; */
DECL|function|irias_find_attrib
r_struct
id|ias_attrib
op_star
id|irias_find_attrib
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|ias_attrib
op_star
id|attrib
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|name
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|attrib
op_assign
id|hashbin_lock_find
c_func
(paren
id|obj-&gt;attribs
comma
l_int|0
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrib
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Unsafe (locking), attrib might change */
r_return
id|attrib
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_add_attribute (obj, attrib)&n; *&n; *    Add attribute to object&n; *&n; */
DECL|function|irias_add_attrib
r_void
id|irias_add_attrib
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
comma
r_struct
id|ias_attrib
op_star
id|attrib
comma
r_int
id|owner
)paren
(brace
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|attrib
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|attrib-&gt;magic
op_eq
id|IAS_ATTRIB_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Set if attrib is owned by kernel or user space */
id|attrib-&gt;value-&gt;owner
op_assign
id|owner
suffix:semicolon
id|hashbin_insert
c_func
(paren
id|obj-&gt;attribs
comma
(paren
id|irda_queue_t
op_star
)paren
id|attrib
comma
l_int|0
comma
id|attrib-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_object_change_attribute (obj_name, attrib_name, new_value)&n; *&n; *    Change the value of an objects attribute.&n; *&n; */
DECL|function|irias_object_change_attribute
r_int
id|irias_object_change_attribute
c_func
(paren
r_char
op_star
id|obj_name
comma
r_char
op_star
id|attrib_name
comma
r_struct
id|ias_value
op_star
id|new_value
)paren
(brace
r_struct
id|ias_object
op_star
id|obj
suffix:semicolon
r_struct
id|ias_attrib
op_star
id|attrib
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Find object */
id|obj
op_assign
id|hashbin_lock_find
c_func
(paren
id|objects
comma
l_int|0
comma
id|obj_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to find object: %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|obj_name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Slightly unsafe (obj might get removed under us) */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|obj-&gt;attribs-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Find attribute */
id|attrib
op_assign
id|hashbin_find
c_func
(paren
id|obj-&gt;attribs
comma
l_int|0
comma
id|attrib_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrib
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to find attribute: %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|attrib_name
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|obj-&gt;attribs-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attrib-&gt;value-&gt;type
op_ne
id|new_value-&gt;type
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), changing value type not allowed!&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|obj-&gt;attribs-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Delete old value */
id|irias_delete_value
c_func
(paren
id|attrib-&gt;value
)paren
suffix:semicolon
multiline_comment|/* Insert new value */
id|attrib-&gt;value
op_assign
id|new_value
suffix:semicolon
multiline_comment|/* Success */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|obj-&gt;attribs-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_object_add_integer_attrib (obj, name, value)&n; *&n; *    Add an integer attribute to an LM-IAS object&n; *&n; */
DECL|function|irias_add_integer_attrib
r_void
id|irias_add_integer_attrib
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
comma
r_char
op_star
id|name
comma
r_int
id|value
comma
r_int
id|owner
)paren
(brace
r_struct
id|ias_attrib
op_star
id|attrib
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|name
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|attrib
op_assign
(paren
r_struct
id|ias_attrib
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_attrib
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrib
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to allocate attribute!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|attrib
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_attrib
)paren
)paren
suffix:semicolon
id|attrib-&gt;magic
op_assign
id|IAS_ATTRIB_MAGIC
suffix:semicolon
id|attrib-&gt;name
op_assign
id|strndup
c_func
(paren
id|name
comma
id|IAS_MAX_ATTRIBNAME
)paren
suffix:semicolon
multiline_comment|/* Insert value */
id|attrib-&gt;value
op_assign
id|irias_new_integer_value
c_func
(paren
id|value
)paren
suffix:semicolon
id|irias_add_attrib
c_func
(paren
id|obj
comma
id|attrib
comma
id|owner
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_add_octseq_attrib (obj, name, octet_seq, len)&n; *&n; *    Add a octet sequence attribute to an LM-IAS object&n; *&n; */
DECL|function|irias_add_octseq_attrib
r_void
id|irias_add_octseq_attrib
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
comma
r_char
op_star
id|name
comma
id|__u8
op_star
id|octets
comma
r_int
id|len
comma
r_int
id|owner
)paren
(brace
r_struct
id|ias_attrib
op_star
id|attrib
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|name
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|octets
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|attrib
op_assign
(paren
r_struct
id|ias_attrib
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_attrib
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrib
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to allocate attribute!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|attrib
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_attrib
)paren
)paren
suffix:semicolon
id|attrib-&gt;magic
op_assign
id|IAS_ATTRIB_MAGIC
suffix:semicolon
id|attrib-&gt;name
op_assign
id|strndup
c_func
(paren
id|name
comma
id|IAS_MAX_ATTRIBNAME
)paren
suffix:semicolon
id|attrib-&gt;value
op_assign
id|irias_new_octseq_value
c_func
(paren
id|octets
comma
id|len
)paren
suffix:semicolon
id|irias_add_attrib
c_func
(paren
id|obj
comma
id|attrib
comma
id|owner
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_object_add_string_attrib (obj, string)&n; *&n; *    Add a string attribute to an LM-IAS object&n; *&n; */
DECL|function|irias_add_string_attrib
r_void
id|irias_add_string_attrib
c_func
(paren
r_struct
id|ias_object
op_star
id|obj
comma
r_char
op_star
id|name
comma
r_char
op_star
id|value
comma
r_int
id|owner
)paren
(brace
r_struct
id|ias_attrib
op_star
id|attrib
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|obj-&gt;magic
op_eq
id|IAS_OBJECT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|name
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|value
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|attrib
op_assign
(paren
r_struct
id|ias_attrib
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_attrib
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrib
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to allocate attribute!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|attrib
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_attrib
)paren
)paren
suffix:semicolon
id|attrib-&gt;magic
op_assign
id|IAS_ATTRIB_MAGIC
suffix:semicolon
id|attrib-&gt;name
op_assign
id|strndup
c_func
(paren
id|name
comma
id|IAS_MAX_ATTRIBNAME
)paren
suffix:semicolon
id|attrib-&gt;value
op_assign
id|irias_new_string_value
c_func
(paren
id|value
)paren
suffix:semicolon
id|irias_add_attrib
c_func
(paren
id|obj
comma
id|attrib
comma
id|owner
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_new_integer_value (integer)&n; *&n; *    Create new IAS integer value&n; *&n; */
DECL|function|irias_new_integer_value
r_struct
id|ias_value
op_star
id|irias_new_integer_value
c_func
(paren
r_int
id|integer
)paren
(brace
r_struct
id|ias_value
op_star
id|value
suffix:semicolon
id|value
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_value
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to kmalloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|value
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_value
)paren
)paren
suffix:semicolon
id|value-&gt;type
op_assign
id|IAS_INTEGER
suffix:semicolon
id|value-&gt;len
op_assign
l_int|4
suffix:semicolon
id|value-&gt;t.integer
op_assign
id|integer
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_new_string_value (string)&n; *&n; *    Create new IAS string value&n; *&n; * Per IrLMP 1.1, 4.3.3.2, strings are up to 256 chars - Jean II&n; */
DECL|function|irias_new_string_value
r_struct
id|ias_value
op_star
id|irias_new_string_value
c_func
(paren
r_char
op_star
id|string
)paren
(brace
r_struct
id|ias_value
op_star
id|value
suffix:semicolon
id|value
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_value
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to kmalloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|value
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_value
)paren
)paren
suffix:semicolon
id|value-&gt;type
op_assign
id|IAS_STRING
suffix:semicolon
id|value-&gt;charset
op_assign
id|CS_ASCII
suffix:semicolon
id|value-&gt;t.string
op_assign
id|strndup
c_func
(paren
id|string
comma
id|IAS_MAX_STRING
)paren
suffix:semicolon
id|value-&gt;len
op_assign
id|strlen
c_func
(paren
id|value-&gt;t.string
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_new_octseq_value (octets, len)&n; *&n; *    Create new IAS octet-sequence value&n; *&n; * Per IrLMP 1.1, 4.3.3.2, octet-sequence are up to 1024 bytes - Jean II&n; */
DECL|function|irias_new_octseq_value
r_struct
id|ias_value
op_star
id|irias_new_octseq_value
c_func
(paren
id|__u8
op_star
id|octseq
comma
r_int
id|len
)paren
(brace
r_struct
id|ias_value
op_star
id|value
suffix:semicolon
id|value
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_value
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to kmalloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|value
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_value
)paren
)paren
suffix:semicolon
id|value-&gt;type
op_assign
id|IAS_OCT_SEQ
suffix:semicolon
multiline_comment|/* Check length */
r_if
c_cond
(paren
id|len
OG
id|IAS_MAX_OCTET_STRING
)paren
(brace
id|len
op_assign
id|IAS_MAX_OCTET_STRING
suffix:semicolon
)brace
id|value-&gt;len
op_assign
id|len
suffix:semicolon
id|value-&gt;t.oct_seq
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value-&gt;t.oct_seq
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to kmalloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|value-&gt;t.oct_seq
comma
id|octseq
comma
id|len
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|irias_new_missing_value
r_struct
id|ias_value
op_star
id|irias_new_missing_value
c_func
(paren
r_void
)paren
(brace
r_struct
id|ias_value
op_star
id|value
suffix:semicolon
id|value
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ias_value
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|NULL
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s: Unable to kmalloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|value
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ias_value
)paren
)paren
suffix:semicolon
id|value-&gt;type
op_assign
id|IAS_MISSING
suffix:semicolon
id|value-&gt;len
op_assign
l_int|0
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irias_delete_value (value)&n; *&n; *    Delete IAS value&n; *&n; */
DECL|function|irias_delete_value
r_void
id|irias_delete_value
c_func
(paren
r_struct
id|ias_value
op_star
id|value
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|value
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|value-&gt;type
)paren
(brace
r_case
id|IAS_INTEGER
suffix:colon
multiline_comment|/* Fallthrough */
r_case
id|IAS_MISSING
suffix:colon
multiline_comment|/* No need to deallocate */
r_break
suffix:semicolon
r_case
id|IAS_STRING
suffix:colon
multiline_comment|/* If string, deallocate string */
r_if
c_cond
(paren
id|value-&gt;t.string
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|value-&gt;t.string
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IAS_OCT_SEQ
suffix:colon
multiline_comment|/* If byte stream, deallocate byte stream */
r_if
c_cond
(paren
id|value-&gt;t.oct_seq
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|value-&gt;t.oct_seq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Unknown value type!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
eof
