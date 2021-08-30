<?php
  require('db.php');

  $Humidity = array();
  $Temperature = array();

  // Create connection
   $conn = mysqli_connect($servername,$username,$password,$dbname);
   // Check connection
   if(mysqli_connect_errno()){
     die('Connection failed: '. mysqli_connect_errno());
   }

   $sql = 'SELECT Humidity, Temperature FROM HumiditySensor';
   if($result = mysqli_query($conn, $sql)){
     //print_r($result);

     while($row = mysqli_fetch_row($result)){
       //printf("%s (%s)\n", $row[0], $row[1]);
       $Humidity[] = $row[0];
       $Temperature[] = $row[1];
     }
     mysqli_free_result($result);
   }
   mysqli_close($conn);
 ?>
