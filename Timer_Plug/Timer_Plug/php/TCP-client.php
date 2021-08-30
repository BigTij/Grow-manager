
<?php
  require("db.php");

  $address = '10.0.0.111';
  $port = 1025;

  $nb_plug = 1;
  $P;
  $hr_on;
  $min_on;
  $hr_off;
  $min_off;
  for($i = 0; $i < $nb_plug; $i++){
    $P[$i] = FetchData($i + 1);
    $hr_on[$i] = $P[$i][0];
    $min_on[$i] = $P[$i][1];
    $hr_off[$i] = $P[$i][2];
    $min_off[$i] = $P[$i][3];
  }

  if($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP) === false){
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
  }
  else{
    echo "socket created succesfully.";
  }
  if (socket_connect($sock, $address, $port) === false) {
    echo "socket_connect() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
  }
  else{
    echo "socket connected succesfully.";
  }
  for($i = 0; $i < $nb_plug; $i++){
    if(isset($_POST["submit-P" . ($i + 1)])){
      $hr_on[$i] = $_POST['hr_on'];
      $min_on[$i] = $_POST['min_on'];
      $hr_off[$i] = $_POST['hr_off'];
      $min_off[$i] = $_POST['min_off'];

      $time_on = ((int)$hr_on[$i] * 3600) + ((int)$min_on[$i] * 60);
      $time_off = ((int)$hr_off[$i] * 3600) + ((int)$min_off[$i] * 60);
      $str = "timer-set P". ($i + 1) ." ". $time_on . " " . $time_off;

      socket_write($sock,$str,strlen($str));

      InsertData($hr_on[$i],$min_on[$i],$hr_off[$i],$min_off[$i],($i + 1));
    }
  }
  socket_close($sock);
 ?>
