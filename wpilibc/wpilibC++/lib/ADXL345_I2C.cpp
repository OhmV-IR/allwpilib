/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "ADXL345_I2C.h"
#include "DigitalModule.h"
//#include "NetworkCommunication/UsageReporting.h"
#include "I2C.h"

const uint8_t ADXL345_I2C::kAddress;
const uint8_t ADXL345_I2C::kPowerCtlRegister;
const uint8_t ADXL345_I2C::kDataFormatRegister;
const uint8_t ADXL345_I2C::kDataRegister;
constexpr double ADXL345_I2C::kGsPerLSB;

/**
 * Constructor.
 *
 * @param range The range (+ or -) that the accelerometer will measure.
 */
ADXL345_I2C::ADXL345_I2C(Port port, ADXL345_I2C::DataFormat_Range range):
		I2C(port, kAddress)
{
		//m_i2c = new I2C((I2C::Port)port, kAddress);

		// Turn on the measurements
		Write(kPowerCtlRegister, kPowerCtl_Measure);
		// Specify the data format to read
		Write(kDataFormatRegister, kDataFormat_FullRes | (uint8_t)range);

		HALReport(HALUsageReporting::kResourceType_ADXL345, HALUsageReporting::kADXL345_I2C, 0);
}

/**
 * Destructor.
 */
ADXL345_I2C::~ADXL345_I2C()
{
	//delete m_i2c;
	//m_i2c = NULL;
}

/**
 * Get the acceleration of one axis in Gs.
 *
 * @param axis The axis to read from.
 * @return Acceleration of the ADXL345 in Gs.
 */
double ADXL345_I2C::GetAcceleration(ADXL345_I2C::Axes axis)
{
	int16_t rawAccel = 0;
	//if(m_i2c)
	//{
		Read(kDataRegister + (uint8_t)axis, sizeof(rawAccel), (uint8_t *)&rawAccel);
	//}
	return rawAccel * kGsPerLSB;
}

/**
 * Get the acceleration of all axes in Gs.
 *
 * @return Acceleration measured on all axes of the ADXL345 in Gs.
 */
ADXL345_I2C::AllAxes ADXL345_I2C::GetAccelerations()
{
	AllAxes data = AllAxes();
	int16_t rawData[3];
	//if (m_i2c)
	//{
		Read(kDataRegister, sizeof(rawData), (uint8_t*)rawData);

		data.XAxis = rawData[0] * kGsPerLSB;
		data.YAxis = rawData[1] * kGsPerLSB;
		data.ZAxis = rawData[2] * kGsPerLSB;
	//}
	return data;
}
