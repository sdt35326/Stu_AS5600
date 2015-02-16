#pragma once

#include "AS5600_Registers.h"
#include <I2C.h>
#include "Arduino.h"


typedef enum{
  MH = 0,   //  AGC minimum gain overflow, magnet too strong
  ML ,      //  AGC maximum gain overflow, magnet too weak
  MD ,      //  Magnet was detected
  READ_ERROR

}AGC_e;

typedef enum{
  analog_full = 0 ,
  analog_reduced ,
  digital_PWM

}out_mode_e;

class Stu_AS5600 {

public:
  Stu_AS5600( void );

  void
    begin( void ),
    setOutPinMode( out_mode_e mode );

  bool
    setZeroPosition( void ),
    setStopPosition( void ),
    setMaxAngle( void );



  uint16_t
    getRawAngle( void ),
    getAngle( void );

  AGC_e
    getAGC( void ) ;

private:

  typedef union {

      struct{

        uint16_t lb:8;
        uint16_t hb:4;


      };
      uint16_t i:12;

      uint8_t b[2];





  } mag_data_t;


  typedef enum{
    angle_raw = 0,
    angle_filtered

  }angle_e;

  uint8_t const
    _I2CAddress;

  uint8_t
    _readI2C( uint8_t regAddress );

  uint16_t
    _readAngle(angle_e e);


  void
    _readI2C( uint8_t regAddress, int16_t numBytes, uint8_t* destAry ),
    _writeI2C( uint8_t regAddress, uint8_t value ),
    _overWriteI2C( uint8_t regAddress, uint8_t value );




};
