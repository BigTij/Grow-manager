import mysql.connector
from mysql.connector import Error
from mysql.connector import errorcode

try:
    connection = mysql.connector.connect(host='192.168.0.14',
                                         database='SensorData',
                                         user='root',
                                         password='**************')
    #mySql_insert_query = """INSERT INTO Laptop (Id, Name, Price, Purchase_date)
    #                       VALUES
    #                       (10, 'Lenovo ThinkPad P71', 6459, '2019-08-14') """

    #cursor = connection.cursor()
    #cursor.execute(mySql_insert_query)
    #connection.commit()
    #print(cursor.rowcount, "Record inserted successfully into Laptop table")
    #cursor.close()

except mysql.connector.Error as error:
    print("Failed to insert record into Laptop table {}".format(error))

finally:
    if (connection.is_connected()):
        connection.close()
        print("MySQL connection is closed")
