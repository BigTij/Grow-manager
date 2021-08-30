import Adafruit_DHT
import time
import mysql.connector
from mysql.connector import Error
from mysql.connector import errorcode

DHT_SENSOR = Adafruit_DHT.DHT22

DHT_PIN = 4

while True:
    humidity, temperature = Adafruit_DHT.read_retry(DHT_SENSOR, DHT_PIN)
    if humidity is not None and temperature is not None:
        print("Temp={0:0.1f}*C  Humidity={1:0.1f}%".format(temperature, humidity))
        try:
            con = mysql.connector.connect(host = '192.168.0.14',
                user = 'RaspberryPi',
                password = '**************',
                database = 'SensorData'
            )
            print("Im connected")
            query = "INSERT INTO HumiditySensor (Humidity,Temperature) VALUES ({0:0.1f},{1:0.1f})".format(humidity,temperature)
            cursor = con.cursor()
            cursor.execute(query)
            con.commit()
            cursor.close()
        except mysql.connector.Error as error:
            print("Failed to insert record into HumiditySensor table {}".format(error))
        finally:
            if (con.is_connected()):
                con.close()
                print("MySQL connection is closed")
    else:
        print("Failed to retrieve data from humidity sensor")
    time.sleep(3600)
