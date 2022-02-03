/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include "ia_css_types.h"
#include "sh_css_defs.h"
#include "ia_css_debug.h"
#include "assert_support.h"

#include "ia_css_sc.host.h"

void
ia_css_sc_encode(
	struct sh_css_isp_sc_params *to,
	struct ia_css_shading_table **from,
	unsigned size)
{
	(void)size;
	to->gain_shift = (*from)->fraction_bits;
}

void
ia_css_sc_dump(
	const struct sh_css_isp_sc_params *sc,
	unsigned level)
{
	if (!sc) return;
	ia_css_debug_dtrace(level, "Shading Correction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"sc_gain_shift", sc->gain_shift);
}

/* ------ deprecated(bz675) : from ------ */
/* It looks like @parameter{} (in *.pipe) is used to generate the process/get/set functions,
   for parameters which should be used in the isp kernels.
   However, the ia_css_shading_settings structure has a parameter which is used only in the css,
   and does not have a parameter which is used in the isp kernels.
   Then, I did not use @parameter{} to generate the get/set function
   for the ia_css_shading_settings structure. (michie) */
void
sh_css_get_shading_settings(const struct ia_css_isp_parameters *params,
			struct ia_css_shading_settings *settings)
{
	if (settings == NULL)
		return;
	assert(params != NULL);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
		"ia_css_get_shading_settings() enter: settings=%p\n", settings);

	*settings = params->shading_settings;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
		"ia_css_get_shading_settings() leave: settings.enable_shading_table_conversion=%d\n",
		settings->enable_shading_table_conversion);
}

void
sh_css_set_shading_settings(struct ia_css_isp_parameters *params,
			const struct ia_css_shading_settings *settings)
{
	if (settings == NULL)
		return;
	assert(params != NULL);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
		"ia_css_set_shading_settings() enter: settings.enable_shading_table_conversion=%d\n",
		settings->enable_shading_table_conversion);

	params->shading_settings = *settings;
	params->shading_settings_changed = true;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
		"ia_css_set_shading_settings() leave: return_void\n");
}
/* ------ deprecated(bz675) : to ------ */
