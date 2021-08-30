import mysql.connector

nb_of_lights = 3

mydb = mysql.connector.connect(
    host= "10.0.0.14",
    user = "pi",
    password = "***********",
    database = "Lighting"
)
mycursor = mydb.cursor()

sql = "create table State ("
for i in nb_of_lights:
    if(i + 1) != nb_of_lights:
        sql += "Light-" + i + " BOOLEAN, Date-" + i + " TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,"

    else:
        sql += "Light-" + i + " BOOLEAN, Date-" + i + " TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP);"


mycursor.execute(sql)
