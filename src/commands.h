/*
 * commands.h
 *
 *  Created on: Jun 6, 2014
 *      Author: casey.kuhns
 */


#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "commandContexts.h"

#define COMMAND 14
#define OBJECT  9
#define PARAMETER 4
#define SUB_PARAMETER 0



typedef struct command_table_entry
{
     char* commandName;
     char* abreviatedCommandName;
     uint8_t commandContext;

}command_table;

//----------------------------------------------------------//
//Lower case only for all tokens!
#define COMMAND_COUNT 4
static const command_table commands[COMMAND_COUNT] =
{
	{"get"		,"g"	,Gxx},
	{"set"		,"s"	,xSx},
	{"reset"	,"r"	,xxR},

	{"help"		,"h"	,0xff}
};

const PROGMEM char commands_get_help_message[]  	= "retrieve a parameter or variable.\r\n   Type \"get help\" for more info";
const PROGMEM char commands_set_help_message[]  	= "enter a parameter or variable.\r\n   Type \"set help\" for more info";
const PROGMEM char commands_reset_help_message[]  	= "resets the parameter to last saved configuration.\r\n   Type  \"set help\" for more info";

const PROGMEM char * const commands_help_messages[COMMAND_COUNT - 1]  =
{
	commands_get_help_message,
	commands_set_help_message,
	commands_reset_help_message
};

//----------------------------------------------------------//
//G		S	R
//Get 	Set Reset

#define OBJECT_COUNT 6
static const command_table objects[OBJECT_COUNT] =
{
	{"channel"		,"ch"	,GSR},
	{"motor"		,"m"	,GSR},
	{"servo"		,"s"	,GSR},
	{"controller"	,"c"	,GSR},
	{"all"			,"a"	,GxR},

	{"help"			,"h"	,0xff}
};

const PROGMEM char objects_channel_help_message[] PROGMEM 	= "objects_channel_help_message";
const PROGMEM char objects_motor_help_message[] PROGMEM 		= "objects_motor_help_message";
const PROGMEM char objects_servo_help_message[] PROGMEM 		= "objects_servo_help_message";
const PROGMEM char objects_controller_help_message[] PROGMEM 	= "objects_controller_help_message";
const PROGMEM char objects_all_help_message[] PROGMEM 		= "objects_all_help_message";

const PROGMEM char * const objects_help_messages[OBJECT_COUNT - 1]  =
//const PROGMEM char *objects_help_messages[]  =
{
		objects_channel_help_message,
		objects_motor_help_message,
		objects_servo_help_message,
		objects_controller_help_message,
		objects_all_help_message
};

//----------------------------------------------------------//
//G		S	R		C		M		S		C
//Get 	Set Reset 	Channel Motor 	Servo	Controller

#define PARAMETER_COUNT 23
#define PARAMETER_WITH_SUB_PARAMETER 3
static const command_table parameters[PARAMETER_COUNT] =
{

	{"encoder"			,"enc"	, GSRxMSx },	//Has sub parameters *see sub_parameters[]
	{"limit"			,"lim"	, GSxxxSx },	//Has sub parameters *see sub_parameters[]
	{"potentiometer"	,"pot"	, GSRxxSx },	//Has sub parameters *see sub_parameters[]

	{"absolute_distance","abs"	, GSRxMxx },
	{"acceleration"		,"acc"	, GSRxMSx },
	{"current"			,"cur"	, GxxCMSC },
	{"derivative"		,"der"	, GSRxMSx },
	{"direction"		,"dir"	, GSRCMSx },
	{"distance"			,"dst"	, GSxxMxx },
	{"input"			,"in"	, GSxxxSx },
	{"integral"			,"int"	, GSRxMSx },
	{"lipo_protection"	,"lip"	, GSRxMSC },
	{"lipo_status"		,"lis"	, GxxxxxC },
	{"max_current"		,"mxc"	, GSRCMSC },
	{"max_temperature"	,"mxt"	, GSRxxxC },
	{"max_velocity"		,"mxv"	, GSRxMSx },
	{"mode"				,"m"	, GSRCxxx },
	{"position"			,"pos"	, GSRxMSx },
	{"power"			,"pwr"	, GSRxMxx },
	{"proportional"		,"prp"	, GSRxMSx },
	{"temperature"		,"t"	, GxxCMSC },
	{"velocity"			,"v"	, GSxxMSx },

	{"help"				,"h"	,0xff}
};

const PROGMEM char parameters_encoder_help_message[] PROGMEM 			= "parameters_encoder_help_message";
const PROGMEM char parameters_limit_help_message[] PROGMEM 			= "parameters_limit_help_message";
const PROGMEM char parameters_potentiometer_help_message[] PROGMEM 	= "parameters_potentiometer_help_message";

const PROGMEM char parameters_abs_distance_help_message[] PROGMEM 	= "parameters_abs_distance_help_message";
const PROGMEM char parameters_acceleration_help_message[] PROGMEM		= "parameters_acceleration_help_message";
const PROGMEM char parameters_current_help_message[] PROGMEM 			= "parameters_current_help_message";
const PROGMEM char parameters_derivative_help_message[] PROGMEM 		= "parameters_derivative_help_message";
const PROGMEM char parameters_direction_help_message[] PROGMEM 		= "parameters_direction_help_message";
const PROGMEM char parameters_distance_help_message[] PROGMEM 		= "parameters_distance_help_message";
const PROGMEM char parameters_input_help_message[] PROGMEM 			= "parameters_input_help_message";
const PROGMEM char parameters_integral_help_message[] PROGMEM 		= "parameters_integral_help_message";
const PROGMEM char parameters_lipo_protection_help_message[] PROGMEM 	= "parameters_lipo_protection_help_message";
const PROGMEM char parameters_lipo_status_help_message[] PROGMEM 		= "parameters_lipo_status_help_message";
const PROGMEM char parameters_max_current_help_message[] PROGMEM 		= "parameters_max_current_help_message";
const PROGMEM char parameters_max_temperature_help_message[] PROGMEM 	= "parameters_max_temperature_help_message";
const PROGMEM char parameters_max_velocity_help_message[] PROGMEM 	= "parameters_max_velocity_help_message";
const PROGMEM char parameters_mode_help_message[] PROGMEM 			= "parameters_mode_help_message";
const PROGMEM char parameters_position_help_message[] PROGMEM 		= "parameters_position_help_message";
const PROGMEM char parameters_power_help_message[] PROGMEM 			= "parameters_power_help_message";
const PROGMEM char parameters_proportional_help_message[] PROGMEM 	= "parameters_proportional_help_message";
const PROGMEM char parameters_temperature_help_message[] PROGMEM 		= "parameters_temperature_help_message";
const PROGMEM char parameters_velocity_help_message[] PROGMEM 		= "parameters_velocity_help_message";

const PROGMEM char * const parameters_help_messages[PARAMETER_COUNT - 1]  =
{
	parameters_encoder_help_message,
	parameters_limit_help_message,
	parameters_potentiometer_help_message,
	parameters_abs_distance_help_message,
	parameters_acceleration_help_message,
	parameters_current_help_message,
	parameters_derivative_help_message,
	parameters_direction_help_message,
	parameters_distance_help_message,
	parameters_input_help_message,
	parameters_integral_help_message,
	parameters_lipo_protection_help_message,
	parameters_lipo_status_help_message,
	parameters_max_current_help_message,
	parameters_max_temperature_help_message,
	parameters_max_velocity_help_message,
	parameters_mode_help_message,
	parameters_position_help_message,
	parameters_power_help_message,
	parameters_proportional_help_message,
	parameters_temperature_help_message,
	parameters_velocity_help_message
};

//----------------------------------------------------------//
//E			L		P
//Encoder	Limit	Potentiometer

#define SUB_PARAMETER_COUNT 13
#define SUB_PARAMETER_WITH_SUB_PARAMETER 2
static const command_table sub_parameters[SUB_PARAMETER_COUNT] =
{
	{"0"				,"0"	, xLx },
	{"1"				,"1"	, xLx },

	{"center"			,"c"	, ExP },
	{"count_per_rev"	,"cpr"	, Exx },
	{"direction"		,"dir"	, ExP },
	{"gear_ratio"		,"gr"	, Exx },
	{"high_range"		,"hr"	, ExP },
	{"low_range"		,"lr"	, ExP },
	{"mode"				,"m"	, xLx },
	{"position"			,"pos"	, ExP },
	{"rev_per_deg"		,"cpd"	, Exx },
	{"wheel_size"		,"ws"	, Exx },

	{"help"				,"h"	, 0xff }
};

const PROGMEM char sub_parameters_0_help_message[]  				= "sub_parameters_0_help_message";
const PROGMEM char sub_parameters_1_help_message[]  				= "sub_parameters_1_help_message";
const PROGMEM char sub_parameters_center_help_message[]  			= "sub_parameters_center_help_message";
const PROGMEM char sub_parameters_count_per_rev_help_message[] 	= "sub_parameters_count_per_rev_help_message";
const PROGMEM char sub_parameters_direction_help_message[]  		= "sub_parameters_direction_help_message";
const PROGMEM char sub_parameters_gear_ratio_help_message[]  		= "sub_parameters_gear_ratio_help_message";
const PROGMEM char sub_parameters_high_range_help_message[]  		= "sub_parameters_high_range_help_message";
const PROGMEM char sub_parameters_low_range_help_message[]  		= "sub_parameters_low_range_help_message";
const PROGMEM char sub_parameters_mode_help_message[]  			= "sub_parameters_mode_help_message";
const PROGMEM char sub_parameters_position_help_message[]  		= "sub_parameters_position_help_message";
const PROGMEM char sub_parameters_rev_per_deg_help_message[]  		= "sub_parameters_rev_per_deg_help_message";
const PROGMEM char sub_parameters_wheel_size_help_message[]  		= "sub_parameters_wheel_size_help_message";

const PROGMEM char * const sub_parameters_help_messages[SUB_PARAMETER_COUNT - 1]  =
{
		sub_parameters_0_help_message,
		sub_parameters_1_help_message,
		sub_parameters_center_help_message,
		sub_parameters_count_per_rev_help_message,
		sub_parameters_direction_help_message,
		sub_parameters_gear_ratio_help_message,
		sub_parameters_high_range_help_message,
		sub_parameters_low_range_help_message,
		sub_parameters_mode_help_message,
		sub_parameters_position_help_message,
		sub_parameters_rev_per_deg_help_message,
		sub_parameters_wheel_size_help_message
};


//----------------------------------------------------------//

#define LIMIT_SUB_PARAMETER_COUNT 3
static const command_table limit_sub_parameters[LIMIT_SUB_PARAMETER_COUNT] =
{
	{"mode"		,"m"	, 0xff },
	{"status"	,"s"	, 0xff },

	{"help"		,"h"	, 0xff }
};

const PROGMEM char limit_sub_parameters_mode_help_message[]		= "limit_sub_parameters_mode_help_message";
const PROGMEM char limit_sub_parameters_status_help_message[]	= "limit_sub_parameters_status_help_message";

const PROGMEM char * const limit_sub_parameters_help_messages[LIMIT_SUB_PARAMETER_COUNT - 1]  =
{
		sub_parameters_0_help_message,
		sub_parameters_1_help_message
};

#endif /* COMMANDS_H_ */
