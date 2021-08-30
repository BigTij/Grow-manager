<?php
  $servername = "localhost";
  $username = "RaspberryPi";
  $password = "***************";
  $dbname = "Plug_Logs";

  function InsertData($hr_on,$min_on,$hr_off,$min_off,$P){
    global $servername, $username, $password, $dbname;
    $conn = mysqli_connect($servername,$username,$password,$dbname);

    if(mysqli_connect_errno()){
      die('Connection failed: '. mysqli_connect_error());
    }
    if($P == 1 || $P == 2 || $P == 3 || $P == 4){

      $sql = "DELETE FROM P" . $P . ";";

      if(!mysqli_query($conn,$sql)){
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
      }

      $sql = "INSERT INTO P". $P . " (hr_on, min_on, hr_off, min_off) VALUES (". $hr_on . ", " . $min_on. ", " . $hr_off . ", ". $min_off . ");";
      if(!mysqli_query($conn,$sql)){
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
      }
    }

    mysqli_close($conn);
  }
  function FetchData($P){
    global $servername, $username, $password, $dbname;
    $conn = mysqli_connect($servername, $username, $password, $dbname);

    if(!$conn){
      die("Connection failed: ". mysqli_connect_errno());
    }
    $hr_on = array();
    $min_on = array();
    $hr_off = array();
    $min_off = array();

    if($P == 1 || $P == 2 || $P == 3 || $P == 4){
      $sql = "SELECT hr_on, min_on, hr_off, min_off FROM P" . $P . ";";
      if($result = mysqli_query($conn, $sql)){
        while($row = mysqli_fetch_row($result)){
          $hr_on[] = $row[0];
          $min_on[] = $row[1];
          $hr_off[] = $row[2];
          $min_off[] = $row[3];
        }
        mysqli_free_result($result);
        return array($hr_on[count($hr_on) - 1], $min_on[count($min_on) - 1], $hr_off[count($hr_off) - 1], $min_off[count($min_off) - 1]);
      }
    }

    mysqli_close($conn);
  }
 ?>
