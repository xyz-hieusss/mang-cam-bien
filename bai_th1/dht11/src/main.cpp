#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 4       // Chân kết nối DHT11 (GPIO4)
#define DHTTYPE DHT11  // Loại cảm biến DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("Khởi động DHT11...");
    dht.begin();
}

void loop() {
    float humidity = dht.readHumidity();     // Đọc độ ẩm
    float temperature = dht.readTemperature(); // Đọc nhiệt độ (°C)

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Lỗi! Không thể đọc dữ liệu từ DHT11");
    } else {
        Serial.print("Nhiệt độ: ");
        Serial.print(temperature);
        Serial.print("°C  -  Độ ẩm: ");
        Serial.print(humidity);
        Serial.println("%");
    }

    delay(2000); // Đọc dữ liệu mỗi 2 giây
}
