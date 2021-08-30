var P1 = true;
var P2 = true;
var P3 = true;
var P4 = true;

var plug_nb = 4;
var P = [];

$(window).resize(function(){location.reload();});

let width = $(window).width();
let height = $(window).height();
var msg;
var P_height = 0;
var body = document.getElementByTagName('body')[0];

for (var i = 1; i <= plug_nb; i++){
  var div_P = document.createElement('div');
  P_div.id = 'P' + i + '_div';
  body.appendChild(div_P);
    var P_init = document.createElement('p');
    P_init.innerText = '';
    P_init.onclick(change_P_state(i));
    P_div.appendChild(P_init);

    var img = document.createElement('img');
    img.className = 'wall_plug';
    img.src = 'css/imgs/wall_plug.png';
    P_div.appendChild(img);

    var P_timer_container = document.createElement('div');
    P_timer_container.className = 'P_timer_container';
    P_div.appendChild(P_timer_container);

      var P_timer = document.createElement('p');
      P_timer.className = 'P_timer';

  msg += '<div class="P' + i + '" id="P' + i + '_div">';
  msg +=  '<p class="P_init" id="P'+ i +'_state" onclick="change_P_state(' + i + ')">on</p>';
  msg +=  '<img class="wall_plug" src="css/imgs/wall_plug.png" alt="">';
  msg +=  '<div class="P_timer_container">';
  msg +=   '<p class="P_timer">Set a timer</p>';
  msg +=   '<form class="P_container" action="index.php" method="post">';
  msg +=      '<script src="js/restrict_input.js"></script>';
  msg +=     '<label for="on">On</label>';
  msg +=     '<input class="hr_on" type="text" name="hr_on" value="<?php echo $hr_on['+ (i - 1) +']; ?>" onkeypress="return isNumberKey(event)">';
  msg +=     '<label for="">:</label>';
  msg +=     '<input class="min_on"type="text" name="min_on" value="<?php echo $min_on['+ (i - 1) +']; ?>" onkeypress="return isNumberKey(event)">';
  msg +=     '<label for="off">Off</label>';
  msg +=     '<input class="hr_off" type="text" name="hr_off" value="<?php echo $hr_off['+ (i - 1) +']; ?>" onkeypress="return isNumberKey(event)">';
  msg +=     '<label for="">:</label>';
  msg +=     '<input class="min_off" type="text" name="min_off" value="<?php echo $min_off['+ (i - 1) +']; ?>" onkeypress="return isNumberKey(event)">';
  msg +=     '<input type="submit" name="submit-P'+ i +'" value="Set">';
  msg +=   '</form>';
  msg +=  '</div>';
  msg += '</div>';

}
el.innerHTML = msg;
for (var i = 1; i <= plug_nb; i++){
  document.getElementById('P' + i + '_div').style.border = "4px solid";
  document.getElementById('P' + i + '_div').style.border-radius = "10px";
  document.getElementById('P' + i + '_div').style.width = "18%";
  document.getElementById('P' + i + '_div').style.textAlign = "center";
  document.getElementById('P' + i + '_div').style.backgroundPosition = "center";
  document.getElementById('P' + i + '_div').style.position = "relative";
  document.getElementById('P' + i + '_div').style.backgroundColor = "rgba(0,0,0,0.3)";
  if(i % 4 == 0){
    P_height += 30;
  }
  document.getElementById('P' + i + '_div').style.marginTop = ((15 + P_height) + "%";
  document.getElementById('P' + i + '_div').style.marginBottom = "10%";
  document.getElementById('P' + i + '_div').style.marginLeft = "5%";
  document.getElementById('P' + i + '_div').style.float = "left";

  document.getElementById('P' + i + '_on_container').style.height = "20px";
  document.getElementById('P' + i + '_on_container').style.width = "100%";
  document.getElementById('P' + i + '_off_container').style.height = ;
}
document.body.style.width = '${width}px';
document.body.style.height = '${height}px';

if(height > width){

  for(var i = 1; i <= plug_nb; i++){
    document.getElementById('P' + i + '_div').style.width = "80%";
    document.getElementById('P' + i + '_div').style.marginLeft = '10%';
  }
}
function change_P_state(i){
  P[i] = !P[i];
  var p = document.getElementById("P" + i + "_state");
  if(P[i]){
    p.style.backgroundColor = 'green';
    p.innerHTML = "on";
  }
  else{
    p.style.backgroundColor = "red";
    p.innerHTML = "off";
  }
}
