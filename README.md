# ESP32 DHT11 Sensor Data Sender

This Arduino sketch is designed to run on an ESP32 microcontroller with a DHT11 sensor connected. It sends temperature and humidity data to a specified server using HTTP POST requests.

## Requirements

- ESP32 microcontroller
- DHT11 temperature and humidity sensor
- WiFi network
- Server with an API endpoint to receive sensor data

## Installation

1. Upload the sketch to your ESP32 board using the Arduino IDE or platformio.
2. Connect the DHT11 sensor to the ESP32 board. 
3. Update the `ssid`, `password`, and `serverUrl` variables in the sketch with your WiFi credentials and server URL.

## How It Works

1. The sketch initializes the DHT11 sensor and establishes a WiFi connection.
2. If the WiFi connection is successful, it reads the temperature and humidity data from the sensor.
3. It then constructs a JSON payload with the sensor ID and the temperature and humidity values.
4. The payload is sent to the server using an HTTP POST request.
5. If the request is successful, an LED connected to the ESP32 blinks briefly to indicate data transmission.

## LED Status

- **Blue LED**: Blinks rapidly during WiFi connection attempt. Remains solid if connection is successful.
- **Green LED**: Blinks briefly after each successful data transmission.

## Server Endpoint

Ensure your server has an endpoint to receive the sensor data in the specified JSON format:

```json
{
    "sensorId": 1,
    "value": "{temp: 25, hum: 70}"
}
