#include "seeed_bme680.h"
#include "SparkFun_SCD4x_Arduino_Library.h"
#include <WioCellular.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define REG_POWER_CTL (0x2d)
#define IIC_ADDR  uint8_t(0x76)

Seeed_BME680 bme680(IIC_ADDR); /* IIC PROTOCOL */
SCD4x mySensor;

void setup() {    
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Serial start!!!");
    delay(100);
    WioCellular.begin();
    WioCellular.enableGrovePower();
    while (!bme680.init()) {
        Serial.println("bme680 init failed ! can't find device!");
        delay(10000);
    }
    while (mySensor.begin() == false)
    {
      Serial.println("Sensor not detected. Please check wiring");
      delay(100000);
    }

    Serial.println("init!");
}

void loop() {
    if (bme680.read_sensor_data()) {
        Serial.println("Failed to perform reading :(");
        return;
    }
    Serial.println("***BME6800***");
    Serial.print("temperature ===>> ");
    Serial.print(bme680.sensor_result_value.temperature);
    Serial.println(" C");

    Serial.print("pressure ===>> ");
    Serial.print(bme680.sensor_result_value.pressure / 1000.0);
    Serial.println(" KPa");

    Serial.print("humidity ===>> ");
    Serial.print(bme680.sensor_result_value.humidity);
    Serial.println(" %");

    Serial.print("gas ===>> ");
    Serial.print(bme680.sensor_result_value.gas / 1000.0);
    Serial.println(" Kohms");

    if (mySensor.readMeasurement()) {
      float temperature = mySensor.getTemperature();
      float humidity = mySensor.getHumidity();
      uint16_t co2 = mySensor.getCO2();
      Serial.println("");
      Serial.println("***SCD40***");
      Serial.printf("temperature ===>> %.2f C\n",temperature);
      Serial.printf("humidity ===>> %.2f %%\n",humidity);
      Serial.printf("gas ===>> %d ppm\n",co2);
    }
    Serial.println();
    Serial.println();

    delay(2000);
}
