multiline_comment|/*&n;    ac97_plugin_ad1980.c  Copyright (C) 2003 Red Hat, Inc. All rights reserved.&n;&n;   The contents of this file are subject to the Open Software License version 1.1&n;   that can be found at http://www.opensource.org/licenses/osl-1.1.txt and is &n;   included herein by reference. &n;   &n;   Alternatively, the contents of this file may be used under the&n;   terms of the GNU General Public License version 2 (the &quot;GPL&quot;) as &n;   distributed in the kernel source COPYING file, in which&n;   case the provisions of the GPL are applicable instead of the&n;   above.  If you wish to allow the use of your version of this file&n;   only under the terms of the GPL and not to allow others to use&n;   your version of this file under the OSL, indicate your decision&n;   by deleting the provisions above and replace them with the notice&n;   and other provisions required by the GPL.  If you do not delete&n;   the provisions above, a recipient may use your version of this&n;   file under either the OSL or the GPL.&n;   &n;   Authors: &t;Alan Cox &lt;alan@redhat.com&gt;&n;&n;   This is an example codec plugin. This one switches the connections&n;   around to match the setups some vendors use with audio switched to&n;   non standard front connectors not the normal rear ones&n;&n;   This code primarily exists to demonstrate how to use the codec&n;   interface&n;&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ac97_codec.h&gt;
multiline_comment|/**&n; *&t;ad1980_remove&t;&t;-&t;codec remove callback&n; *&t;@codec: The codec that is being removed&n; *&n; *&t;This callback occurs when an AC97 codec is being removed. A&n; *&t;codec remove call will not occur for a codec during that codec&n; *&t;probe callback.&n; *&n; *&t;Most drivers will need to lock their remove versus their &n; *&t;use of the codec after the probe function.&n; */
DECL|function|ad1980_remove
r_static
r_void
id|ad1980_remove
c_func
(paren
r_struct
id|ac97_codec
op_star
id|codec
)paren
(brace
multiline_comment|/* Nothing to do in the simple example */
)brace
multiline_comment|/**&n; *&t;ad1980_probe&t;&t;-&t;codec found callback&n; *&t;@codec: ac97 codec matching the idents&n; *&t;@driver: ac97_driver it matched&n; *&n; *&t;This entry point is called when a codec is found which matches&n; *&t;the driver. At the point it is called the codec is basically&n; *&t;operational, mixer operations have been initialised and can&n; *&t;be overriden. Called in process context. The field driver_private&n; *&t;is available for the driver to use to store stuff.&n; *&n; *&t;The caller can claim the device by returning zero, or return&n; *&t;a negative error code. &n; */
DECL|function|ad1980_probe
r_static
r_int
id|ad1980_probe
c_func
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
r_struct
id|ac97_driver
op_star
id|driver
)paren
(brace
id|u16
id|control
suffix:semicolon
DECL|macro|AC97_AD_MISC
mdefine_line|#define AC97_AD_MISC&t;0x76
multiline_comment|/* Switch the inputs/outputs over (from Dell code) */
id|control
op_assign
id|codec
op_member_access_from_pointer
id|codec_read
c_func
(paren
id|codec
comma
id|AC97_AD_MISC
)paren
suffix:semicolon
id|codec
op_member_access_from_pointer
id|codec_write
c_func
(paren
id|codec
comma
id|AC97_AD_MISC
comma
id|control
op_or
l_int|0x0420
)paren
suffix:semicolon
multiline_comment|/* We could refuse the device since we dont need to hang around,&n;&t;   but we will claim it */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ad1980_driver
r_static
r_struct
id|ac97_driver
id|ad1980_driver
op_assign
(brace
id|codec_id
suffix:colon
l_int|0x41445370
comma
id|codec_mask
suffix:colon
l_int|0xFFFFFFFF
comma
id|name
suffix:colon
l_string|&quot;AD1980 example&quot;
comma
id|probe
suffix:colon
id|ad1980_probe
comma
id|remove
suffix:colon
id|__devexit_p
c_func
(paren
id|ad1980_remove
)paren
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;ad1980_exit&t;&t;-&t;module exit path&n; *&n; *&t;Our module is being unloaded. At this point unregister_driver&n; *&t;will call back our remove handler for any existing codecs. You&n; *&t;may not unregister_driver from interrupt context or from a &n; *&t;probe/remove callback.&n; */
DECL|function|ad1980_exit
r_static
r_void
id|ad1980_exit
c_func
(paren
r_void
)paren
(brace
id|ac97_unregister_driver
c_func
(paren
op_amp
id|ad1980_driver
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ad1980_init&t;&t;-&t;set up ad1980 handlers&n; *&n; *&t;After we call the register function it will call our probe&n; *&t;function for each existing matching device before returning to us.&n; *&t;Any devices appearing afterwards whose id&squot;s match the codec_id&n; *&t;will also cause the probe function to be called.&n; *&t;You may not register_driver from interrupt context or from a &n; *&t;probe/remove callback.&n; */
DECL|function|ad1980_init
r_static
r_int
id|ad1980_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ac97_register_driver
c_func
(paren
op_amp
id|ad1980_driver
)paren
suffix:semicolon
)brace
DECL|variable|ad1980_init
id|module_init
c_func
(paren
id|ad1980_init
)paren
suffix:semicolon
DECL|variable|ad1980_exit
id|module_exit
c_func
(paren
id|ad1980_exit
)paren
suffix:semicolon
eof
