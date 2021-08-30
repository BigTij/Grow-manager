<?php
  require('config.php');

  $State = array();

  // Create connection
   $conn = mysqli_connect($servername,$username,$password,$dbname);
   // Check connection
   if(mysqli_connect_errno()){
     die('Connection failed: '. mysqli_connect_errno());
   }

   $sql = 'SELECT State FROM STATE_01';
   if($result = mysqli_query($conn, $sql)){
     //print_r($result);

     while($row = mysqli_fetch_row($result)){
       //printf("%s (%s)\n", $row[0], $row[1]);
       $State[] = $row[0];
     }
     mysqli_free_result($result);
   }
   mysqli_close($conn);
 ?>
