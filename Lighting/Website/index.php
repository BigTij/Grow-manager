<?php
  require("php/GetData.php");
 ?>

 <!DOCTYPE html>
 <html lang="en" dir="ltr">
   <head>
     <meta charset="utf-8">
     <title>Lighting</title>
     <link rel="stylesheet" href="/css/index.css">
   </head>
   <body>

     <?php for($i = 1; $i <= $nb_of_lights; $i++)
     {
       ?>
       <div class="container" id="Light-<?php echo $i; ?>-div">
         <script type="text/javascript">
         var nb_of_lights = "<?php echo $nb_of_lights; ?>";
         var States = "<?php echo json_encode($State);?>";
         for(var i = 1; i <= nb_of_lights; i++){

           if(States[i-1]){
             document.getElementById("state-" + i + "-div").style.background = "rgba(54,191,90,0.65)";
           }
           else{
             document.getElementById("state-" + i + "-div").style.background = "rgba(191,54,54,0.65)";
           }

         }

         </script>
         <div class="state-<?php echo $i; ?>-div" id="state-<?php echo $i; ?>-div">
           <p class="state-<?php echo $i; ?>-p" id="state-<?php echo $i; ?>-p"><?php
           if($State[($i - 1)]){
             echo "on";
           }
           else{
            echo "off";
           }
           ?></p>
         </div>
       </div>
     <?php
     }
       ?>

   </body>
 </html>
