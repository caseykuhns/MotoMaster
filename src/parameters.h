/*
 * parameters.h
 *
 *  Created on: May 24, 2014
 *      Author: caseykuhns
 */

typedef struct EncoderVariables{
	int32_t ABSDistance;
	int32_t relativeDistance;
	int16_t velocity;
} Encoder;

typedef struct EncoderParameters{
	uint16_t countsPerRev;
	double gearRatio;
	uint16_t wheelDiameter;

}Encode;

typedef struct PIDParameters{
	double P;
	double I;
	double D;
} PID;

typedef struct LimitSwitchParameters{
} Limit;

typedef struct ChannelParameters{
	PID pid;
	Limit limit0;
	Limit limit1;
	uint16_t max_velocity;
} Parameters ;

typedef struct ChannelVariable{



} Variables ;

typedef struct ChannelData{
	Parameters parameter;
	Variables variable;
} DriverChannel;

