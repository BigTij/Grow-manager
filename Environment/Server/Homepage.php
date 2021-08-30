<?php
  require ('GetData.php');
 ?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title></title>
    <link rel="stylesheet" href="CSS/Homepage.css" type="text/css">
    <script
			  src="https://code.jquery.com/jquery-3.4.1.js"
			  integrity="sha256-WpOohJOqMqqyKL9FccASB9O0KwACQJpFTUBLTYOVvVU="
			  crossorigin="anonymous">
    </script>
    <script type="text/javascript" src="js/Reload.js"></script>
  </head>
  <body>
    <div class="Main">
      <div class="Title">
        <h1>Grow room environment</h1>
      </div>
      <div class="Environment_Container">
        <div class="Environment">
          <p class="mesure_label">Actual reading</p>
          <div class="mesure_container">
            <p class="Humidity_mesure"><?php echo $Humidity[count($Humidity) - 1]; ?>%</p>
            <p class="Temperature_mesure"><?php echo $Temperature[count($Temperature) - 1]; ?>&#186;C</p>
          </div>
        </div>
      </div>
      <div class="Graph">
        <canvas id="Data" width="60%" height="40%" class="line-chart"></canvas>
        <script src="js/Homepage.js"></script>
        <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
        <script>
          var Temperature = <?php echo json_encode($Temperature); ?>;
          var Humidity = <?php echo json_encode($Humidity); ?>;

          var canvas = document.getElementById('Data').getContext('2d');
          var DataChart = new Chart(canvas, {
            type: 'line',
            data: {
              labels: ['1h','2h','3h','4h','5h','6h','7h','8h','9h','10h','11h','12h','13h','14h','15h','16h','17h','18h','19h','20h','21h','22h','23h','24h'],
              datasets: [{
                label: 'Humidity(%)',

                data: [{
                  x: 0,
                  y: Humidity[Humidity.length - 1]
                },{
                  x: 1,
                  y: Humidity[Humidity.length - 2]
                },{
                  x: 2,
                  y: Humidity[Humidity.length - 3]
                },{
                  x: 3,
                  y: Humidity[Humidity.length - 4]
                },{
                  x: 4,
                  y: Humidity[Humidity.length - 5]
                },{
                  x: 5,
                  y: Humidity[Humidity.length - 6]
                },{
                  x: 6,
                  y: Humidity[Humidity.length - 7]
                },{
                  x: 7,
                  y: Humidity[Humidity.length - 8]
                },{
                  x: 8,
                  y: Humidity[Humidity.length - 9]
                },{
                  x: 9,
                  y: Humidity[Humidity.length - 10]
                },{
                  x: 10,
                  y: Humidity[Humidity.length - 11]
                },{
                  x: 11,
                  y: Humidity[Humidity.length - 12]
                },{
                  x: 12,
                  y: Humidity[Humidity.length -13]
                },{
                  x: 13,
                  y: Humidity[Humidity.length - 14]
                },{
                  x: 14,
                  y: Humidity[Humidity.length - 15]
                },{
                  x: 15,
                  y: Humidity[Humidity.length - 16]
                },{
                  x: 16,
                  y: Humidity[Humidity.length - 17]
                },{
                  x: 17,
                  y: Humidity[Humidity.length - 18]
                },{
                  x: 18,
                  y: Humidity[Humidity.length - 19]
                },{
                  x: 19,
                  y: Humidity[Humidity.length - 20]
                },{
                  x: 20,
                  y: Humidity[Humidity.length - 21]
                },{
                  x: 21,
                  y: Humidity[Humidity.length - 22]
                },{
                  x: 22,
                  y: Humidity[Humidity.length - 23]
                },{
                  x: 23,
                  y: Humidity[Humidity.length - 24]
                },{
                  x: 24,
                  y: Humidity[Humidity.length - 25]
                }],
                borderColor: '#32CCFF'
              }, {
                label: 'Temperature(Celsius)',
                data: [{
                  x: 0,
                  y: Temperature[Temperature.length - 1]
                },{
                  x: 1,
                  y: Temperature[Temperature.length - 2]
                },{
                  x: 2,
                  y: Temperature[Temperature.length - 3]
                },{
                  x: 3,
                  y: Temperature[Temperature.length - 4]
                },{
                  x: 4,
                  y: Temperature[Temperature.length - 5]
                },{
                  x: 5,
                  y: Temperature[Temperature.length - 6]
                },{
                  x: 6,
                  y: Temperature[Temperature.length - 7]
                },{
                  x: 7,
                  y: Temperature[Temperature.length - 8]
                },{
                  x: 8,
                  y: Temperature[Temperature.length - 9]
                },{
                  x: 9,
                  y: Temperature[Temperature.length - 10]
                },{
                  x: 10,
                  y: Temperature[Temperature.length - 11]
                },{
                  x: 11,
                  y: Temperature[Temperature.length - 12]
                },{
                  x: 12,
                  y: Temperature[Temperature.length - 13]
                },{
                  x: 13,
                  y: Temperature[Temperature.length - 14]
                },{
                  x: 14,
                  y: Temperature[Temperature.length - 15]
                },{
                  x: 15,
                  y: Temperature[Temperature.length - 16]
                },{
                  x: 16,
                  y: Temperature[Temperature.length - 17]
                },{
                  x: 17,
                  y: Temperature[Temperature.length - 18]
                },{
                  x: 18,
                  y: Temperature[Temperature.length - 19]
                },{
                  x: 19,
                  y: Temperature[Temperature.length - 20]
                },{
                  x: 20,
                  y: Temperature[Temperature.length - 21]
                },{
                  x: 21,
                  y: Temperature[Temperature.length - 22]
                },{
                  x: 22,
                  y: Temperature[Temperature.length - 23]
                },{
                  x: 23,
                  y: Temperature[Temperature.length - 24]
                },{
                  x: 24,
                  y: Temperature[Temperature.length - 25]
                }],
                borderColor: '#FFCC32'
              }]
            },
            options: {
              scales: {
                yAxes: [{
                  ticks: {
                    beginAtZero: true
                  }
                }]
              }
            }
          });
        </script>
      </div>
    </div>
  </body>
</html>
