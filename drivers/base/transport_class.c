multiline_comment|/*&n; * transport_class.c - implementation of generic transport classes&n; *                     using attribute_containers&n; *&n; * Copyright (c) 2005 - James Bottomley &lt;James.Bottomley@steeleye.com&gt;&n; *&n; * This file is licensed under GPLv2&n; *&n; * The basic idea here is to allow any &quot;device controller&quot; (which&n; * would most often be a Host Bus Adapter&quot; to use the services of one&n; * or more tranport classes for performing transport specific&n; * services.  Transport specific services are things that the generic&n; * command layer doesn&squot;t want to know about (speed settings, line&n; * condidtioning, etc), but which the user might be interested in.&n; * Thus, the HBA&squot;s use the routines exported by the transport classes&n; * to perform these functions.  The transport classes export certain&n; * values to the user via sysfs using attribute containers.&n; *&n; * Note: because not every HBA will care about every transport&n; * attribute, there&squot;s a many to one relationship that goes like this:&n; *&n; * transport class&lt;-----attribute container&lt;----class device&n; *&n; * Usually the attribute container is per-HBA, but the design doesn&squot;t&n; * mandate that.  Although most of the services will be specific to&n; * the actual external storage connection used by the HBA, the generic&n; * transport class is framed entirely in terms of generic devices to&n; * allow it to be used by any physical HBA in the system.&n; */
macro_line|#include &lt;linux/attribute_container.h&gt;
macro_line|#include &lt;linux/transport_class.h&gt;
multiline_comment|/**&n; * transport_class_register - register an initial transport class&n; *&n; * @tclass:&t;a pointer to the transport class structure to be initialised&n; *&n; * The transport class contains an embedded class which is used to&n; * identify it.  The caller should initialise this structure with&n; * zeros and then generic class must have been initialised with the&n; * actual transport class unique name.  There&squot;s a macro&n; * DECLARE_TRANSPORT_CLASS() to do this (declared classes still must&n; * be registered).&n; *&n; * Returns 0 on success or error on failure.&n; */
DECL|function|transport_class_register
r_int
id|transport_class_register
c_func
(paren
r_struct
id|transport_class
op_star
id|tclass
)paren
(brace
r_return
id|class_register
c_func
(paren
op_amp
id|tclass
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
)brace
DECL|variable|transport_class_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_class_register
)paren
suffix:semicolon
multiline_comment|/**&n; * transport_class_unregister - unregister a previously registered class&n; *&n; * @tclass: The transport class to unregister&n; *&n; * Must be called prior to deallocating the memory for the transport&n; * class.&n; */
DECL|function|transport_class_unregister
r_void
id|transport_class_unregister
c_func
(paren
r_struct
id|transport_class
op_star
id|tclass
)paren
(brace
id|class_unregister
c_func
(paren
op_amp
id|tclass
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
)brace
DECL|variable|transport_class_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_class_unregister
)paren
suffix:semicolon
DECL|function|anon_transport_dummy_function
r_static
r_int
id|anon_transport_dummy_function
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* do nothing */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * anon_transport_class_register - register an anonymous class&n; *&n; * @atc: The anon transport class to register&n; *&n; * The anonymous transport class contains both a transport class and a&n; * container.  The idea of an anonymous class is that it never&n; * actually has any device attributes associated with it (and thus&n; * saves on container storage).  So it can only be used for triggering&n; * events.  Use prezero and then use DECLARE_ANON_TRANSPORT_CLASS() to&n; * initialise the anon transport class storage.&n; */
DECL|function|anon_transport_class_register
r_int
id|anon_transport_class_register
c_func
(paren
r_struct
id|anon_transport_class
op_star
id|atc
)paren
(brace
r_int
id|error
suffix:semicolon
id|atc-&gt;container
dot
r_class
op_assign
op_amp
id|atc-&gt;tclass
dot
r_class
suffix:semicolon
id|attribute_container_set_no_classdevs
c_func
(paren
op_amp
id|atc-&gt;container
)paren
suffix:semicolon
id|error
op_assign
id|attribute_container_register
c_func
(paren
op_amp
id|atc-&gt;container
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|atc-&gt;tclass.setup
op_assign
id|anon_transport_dummy_function
suffix:semicolon
id|atc-&gt;tclass.remove
op_assign
id|anon_transport_dummy_function
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|anon_transport_class_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|anon_transport_class_register
)paren
suffix:semicolon
multiline_comment|/**&n; * anon_transport_class_unregister - unregister an anon class&n; *&n; * @atc: Pointer to the anon transport class to unregister&n; *&n; * Must be called prior to deallocating the memory for the anon&n; * transport class.&n; */
DECL|function|anon_transport_class_unregister
r_void
id|anon_transport_class_unregister
c_func
(paren
r_struct
id|anon_transport_class
op_star
id|atc
)paren
(brace
id|attribute_container_unregister
c_func
(paren
op_amp
id|atc-&gt;container
)paren
suffix:semicolon
)brace
DECL|variable|anon_transport_class_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|anon_transport_class_unregister
)paren
suffix:semicolon
DECL|function|transport_setup_classdev
r_static
r_int
id|transport_setup_classdev
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|class_device
op_star
id|classdev
)paren
(brace
r_struct
id|transport_class
op_star
id|tclass
op_assign
id|class_to_transport_class
c_func
(paren
id|cont
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tclass-&gt;setup
)paren
id|tclass
op_member_access_from_pointer
id|setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * transport_setup_device - declare a new dev for transport class association&n; *&t;&t;&t;    but don&squot;t make it visible yet.&n; *&n; * @dev: the generic device representing the entity being added&n; *&n; * Usually, dev represents some component in the HBA system (either&n; * the HBA itself or a device remote across the HBA bus).  This&n; * routine is simply a trigger point to see if any set of transport&n; * classes wishes to associate with the added device.  This allocates&n; * storage for the class device and initialises it, but does not yet&n; * add it to the system or add attributes to it (you do this with&n; * transport_add_device).  If you have no need for a separate setup&n; * and add operations, use transport_register_device (see&n; * transport_class.h).&n; */
DECL|function|transport_setup_device
r_void
id|transport_setup_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|attribute_container_add_device
c_func
(paren
id|dev
comma
id|transport_setup_classdev
)paren
suffix:semicolon
)brace
DECL|variable|transport_setup_device
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_setup_device
)paren
suffix:semicolon
DECL|function|transport_add_class_device
r_static
r_int
id|transport_add_class_device
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|class_device
op_star
id|classdev
)paren
(brace
r_int
id|error
op_assign
id|attribute_container_add_class_device
c_func
(paren
id|classdev
)paren
suffix:semicolon
r_struct
id|transport_container
op_star
id|tcont
op_assign
id|attribute_container_to_transport_container
c_func
(paren
id|cont
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
id|tcont-&gt;statistics
)paren
id|error
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|classdev-&gt;kobj
comma
id|tcont-&gt;statistics
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * transport_add_device - declare a new dev for transport class association&n; *&n; * @dev: the generic device representing the entity being added&n; *&n; * Usually, dev represents some component in the HBA system (either&n; * the HBA itself or a device remote across the HBA bus).  This&n; * routine is simply a trigger point used to add the device to the&n; * system and register attributes for it.&n; */
DECL|function|transport_add_device
r_void
id|transport_add_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|attribute_container_device_trigger
c_func
(paren
id|dev
comma
id|transport_add_class_device
)paren
suffix:semicolon
)brace
DECL|variable|transport_add_device
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_add_device
)paren
suffix:semicolon
DECL|function|transport_configure
r_static
r_int
id|transport_configure
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|transport_class
op_star
id|tclass
op_assign
id|class_to_transport_class
c_func
(paren
id|cont
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tclass-&gt;configure
)paren
id|tclass
op_member_access_from_pointer
id|configure
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * transport_configure_device - configure an already set up device&n; *&n; * @dev: generic device representing device to be configured&n; *&n; * The idea of configure is simply to provide a point within the setup&n; * process to allow the transport class to extract information from a&n; * device after it has been setup.  This is used in SCSI because we&n; * have to have a setup device to begin using the HBA, but after we&n; * send the initial inquiry, we use configure to extract the device&n; * parameters.  The device need not have been added to be configured.&n; */
DECL|function|transport_configure_device
r_void
id|transport_configure_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|attribute_container_trigger
c_func
(paren
id|dev
comma
id|transport_configure
)paren
suffix:semicolon
)brace
DECL|variable|transport_configure_device
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_configure_device
)paren
suffix:semicolon
DECL|function|transport_remove_classdev
r_static
r_int
id|transport_remove_classdev
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|class_device
op_star
id|classdev
)paren
(brace
r_struct
id|transport_container
op_star
id|tcont
op_assign
id|attribute_container_to_transport_container
c_func
(paren
id|cont
)paren
suffix:semicolon
r_struct
id|transport_class
op_star
id|tclass
op_assign
id|class_to_transport_class
c_func
(paren
id|cont
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tclass-&gt;remove
)paren
id|tclass
op_member_access_from_pointer
id|remove
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tclass-&gt;remove
op_ne
id|anon_transport_dummy_function
)paren
(brace
r_if
c_cond
(paren
id|tcont-&gt;statistics
)paren
id|sysfs_remove_group
c_func
(paren
op_amp
id|classdev-&gt;kobj
comma
id|tcont-&gt;statistics
)paren
suffix:semicolon
id|attribute_container_class_device_del
c_func
(paren
id|classdev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * transport_remove_device - remove the visibility of a device&n; *&n; * @dev: generic device to remove&n; *&n; * This call removes the visibility of the device (to the user from&n; * sysfs), but does not destroy it.  To eliminate a device entirely&n; * you must also call transport_destroy_device.  If you don&squot;t need to&n; * do remove and destroy as separate operations, use&n; * transport_unregister_device() (see transport_class.h) which will&n; * perform both calls for you.&n; */
DECL|function|transport_remove_device
r_void
id|transport_remove_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|attribute_container_device_trigger
c_func
(paren
id|dev
comma
id|transport_remove_classdev
)paren
suffix:semicolon
)brace
DECL|variable|transport_remove_device
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_remove_device
)paren
suffix:semicolon
DECL|function|transport_destroy_classdev
r_static
r_void
id|transport_destroy_classdev
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|class_device
op_star
id|classdev
)paren
(brace
r_struct
id|transport_class
op_star
id|tclass
op_assign
id|class_to_transport_class
c_func
(paren
id|cont
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tclass-&gt;remove
op_ne
id|anon_transport_dummy_function
)paren
id|class_device_put
c_func
(paren
id|classdev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * transport_destroy_device - destroy a removed device&n; *&n; * @dev: device to eliminate from the transport class.&n; *&n; * This call triggers the elimination of storage associated with the&n; * transport classdev.  Note: all it really does is relinquish a&n; * reference to the classdev.  The memory will not be freed until the&n; * last reference goes to zero.  Note also that the classdev retains a&n; * reference count on dev, so dev too will remain for as long as the&n; * transport class device remains around.&n; */
DECL|function|transport_destroy_device
r_void
id|transport_destroy_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|attribute_container_remove_device
c_func
(paren
id|dev
comma
id|transport_destroy_classdev
)paren
suffix:semicolon
)brace
DECL|variable|transport_destroy_device
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|transport_destroy_device
)paren
suffix:semicolon
eof
