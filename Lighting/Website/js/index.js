var nb_of_lights = "<?php echo $nb_of_lights; ?>";
var States = "<?php echo json_encode($State);?>";
for(var i = 1; i <= nb_of_lights; i++){

  document.getElementById("Light-" + i + "-div").style.backgroundImage = "url(../css/imgs/2x2-grid.png)";

  if(States[i - 1]){
    document.getElementById("state-" + i + "-div").style.background = "rgba(54,191,90,0.65)";
  }
  else{
    document.getElementById("state-" + i + "-div").style.background = "rgba(191,54,54,0.65)";
  }

  // this code is useless at the present time i was just making tests 

}
