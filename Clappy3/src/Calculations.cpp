/*
 * Calculations.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: Garrick Craft
 */

#include <cmath>
#include "Calculations.h"

namespace Calculations
{
	double HorizontalDistanceFromCameraGround(double ph)
	{
		return cameraHeight * std::tan(pi / 180 * (angleOffset - vFOV/2 + ((pMax - ph) * vFOV / pMax)));
	}

	double HorizontalDistanceFromCameraTape(double ph)
	{
		return (cameraHeight - tapeHeight) * std::tan(pi / 180 * (angleOffset - vFOV/2 + ((pMax - ph) * vFOV / pMax)));
	}

	double GearArmSpeed(double difference)
	{
		return std::abs(0.8 /(1 + std::exp(difference)) - 0.4);
	}

	double DriveMotorSpeed(double scalar, double input, double sens)
	{
		return (2 * scalar / (1 + std::exp(sens * input))) - scalar;
	}

	double DriveMotorLeft(double y, double z)
	{
		return -(y + z);
	}

	double DriveMotorRight(double y, double z)
	{
		return y - z;
	}

	double TwistAxisScalar(double y, double z)
	{
		return std::abs((2 / (1 + std::exp((y==0) ? z/0.01 : z/y)) - 1));
	}
}

