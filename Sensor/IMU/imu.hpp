// DFR_Libraries/Sensor/IMU/imu.hpp
#ifndef DFR_LIBRARIES_SENSOR_IMU_IMU_HPP_
#define DFR_LIBRARIES_SENSOR_IMU_IMU_HPP_

#include "../Gyroscope/LSM6DSOXGyroscope.hpp"
#include "../Accelerometer/LSM6DSOXAccelerometer.hpp"


namespace sensor {

class LSM6DSOX_IMU : public IGyroscope, public IAccelerometer {
public:
    LSM6DSOX_IMU(I2C_HandleTypeDef &hi2c);
    virtual ~LSM6DSOX_IMU() = default;

    void Initialize();

    void init() override;
    void calibrate() override;
    void ComputeAcceleration() override;
    float* GetAcceleration() override;

    short* DegreesPerSecond() override;
    float* RadiansPerSecond() override;

    void updateSensorData(); //moved to public


private:
    LSM6DSOX_Gyroscope gyroscope_;
    LSM6DSOX_Accelerometer accelerometer_;


    float acceleration_[3] = {0};
    short angular_velocity_[3] = {0};
};

}

#endif // DFR_LIBRARIES_SENSOR_IMU_IMU_HPP_
