/*
*	OXWARE developed by oxiKKK
*	Copyright (c) 2023
* 
*	This program is licensed under the MIT license. By downloading, copying, 
*	installing or using this software you agree to this license.
*
*	License Agreement
*
*	Permission is hereby granted, free of charge, to any person obtaining a 
*	copy of this software and associated documentation files (the "Software"), 
*	to deal in the Software without restriction, including without limitation 
*	the rights to use, copy, modify, merge, publish, distribute, sublicense, 
*	and/or sell copies of the Software, and to permit persons to whom the 
*	Software is furnished to do so, subject to the following conditions:
*
*	The above copyright notice and this permission notice shall be included 
*	in all copies or substantial portions of the Software. 
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
*	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
*	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
*	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
*	IN THE SOFTWARE.
*/

#include "precompiled.h"

VarBoolean customvision_enable("customvision_enable", "Enables CustomVision packet manipulation", false);
VarInteger customvision_mode("customvision_mode", "CustomVision mode (0: Disabled, 1: Enabled)", 0, 0, 1);
VarInteger customvision_buffer_size("customvision_buffer_size", "Buffer size for packet manipulation", 0, 0, 1000);

// Interpolation settings
VarFloat customvision_lerp_time("customvision_lerp_time", "CustomVision lerp interpolation time", 255.0f, 0.0f, 255.0f);
VarFloat customvision_msec_time("customvision_msec_time", "CustomVision millisecond time (speed)", 0.0f, 0.0f, 100.0f);

// View angles
VarFloat customvision_yaw("customvision_yaw", "CustomVision yaw rotation", 0.0f, -360.0f, 360.0f);
VarFloat customvision_pitch("customvision_pitch", "CustomVision pitch rotation", 0.0f, -360.0f, 360.0f);
VarFloat customvision_roll("customvision_roll", "CustomVision roll rotation", 0.0f, -360.0f, 360.0f);

// Movement
VarFloat customvision_forward_move("customvision_forward_move", "CustomVision forward movement", 0.0f, -450.0f, 450.0f);
VarFloat customvision_side_move("customvision_side_move", "CustomVision side movement", 0.0f, -450.0f, 450.0f);
VarFloat customvision_up_move("customvision_up_move", "CustomVision upward movement", 0.0f, -320.0f, 320.0f);

// Packet fields
VarInteger customvision_light_level("customvision_light_level", "CustomVision light level", 101, 0, 255);
VarInteger customvision_buttons("customvision_buttons", "CustomVision buttons state", 0, 0, 65535);
VarInteger customvision_weapon_select("customvision_weapon_select", "CustomVision weapon selection", 101, 0, 255);
VarInteger customvision_impulse("customvision_impulse", "CustomVision impulse command", 255, 0, 255);

// Impact coordinates
VarInteger customvision_impact_x("customvision_impact_x", "CustomVision impact X coordinate", 214983547, -999999999, 999999999);
VarInteger customvision_impact_y("customvision_impact_y", "CustomVision impact Y coordinate", -262144, -999999999, 999999999);
VarInteger customvision_impact_z("customvision_impact_z", "CustomVision impact Z coordinate", -262144, -999999999, 999999999);

void CCustomVision::update(hl::usercmd_t* cmd)
{
	if (!customvision_enable.get_value())
	{
		return;
	}

	apply_vision_manipulation(cmd);
}

void CCustomVision::apply_vision_manipulation(hl::usercmd_t* cmd)
{
	// Apply buffer size limit if mode is enabled
	if (customvision_mode.get_value() == 1)
	{
		// Mode is enabled - apply manipulations
		
		// Apply interpolation settings
		if (customvision_lerp_time.get_value() != 0.0f)
		{
			cmd->lerp_msec = (short)customvision_lerp_time.get_value();
		}
		
		if (customvision_msec_time.get_value() != 0.0f)
		{
			cmd->msec = (byte)customvision_msec_time.get_value();
		}

		// Apply view angles
		if (customvision_yaw.get_value() != 0.0f)
		{
			cmd->viewangles.x += customvision_yaw.get_value();
		}
		if (customvision_pitch.get_value() != 0.0f)
		{
			cmd->viewangles.y += customvision_pitch.get_value();
		}
		if (customvision_roll.get_value() != 0.0f)
		{
			cmd->viewangles.z += customvision_roll.get_value();
		}

		// Apply movement overrides
		if (customvision_forward_move.get_value() != 0.0f)
		{
			cmd->forwardmove = customvision_forward_move.get_value();
		}
		if (customvision_side_move.get_value() != 0.0f)
		{
			cmd->sidemove = customvision_side_move.get_value();
		}
		if (customvision_up_move.get_value() != 0.0f)
		{
			cmd->upmove = customvision_up_move.get_value();
		}

		// Apply packet field overrides
		cmd->lightlevel = (byte)customvision_light_level.get_value();
		cmd->buttons = (unsigned short)customvision_buttons.get_value();
		cmd->weaponselect = (byte)customvision_weapon_select.get_value();
		cmd->impulse = (byte)customvision_impulse.get_value();
	}
}
