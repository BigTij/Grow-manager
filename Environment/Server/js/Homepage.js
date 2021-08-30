
var width = document.documentElement.clientWidth;
var height = document.documentElement.clientHeight;


//document.write('<p> Screen width: ' + width + '</p>');
//document.write('<p> Screen height: ' + height + '</p>');

if(height >= width){

  // reset canvas size
  var canvas = document.getElementById("Data");
  var newWidth = Math.round(0.6 * width);
  var newHeight = Math.round(0.6 * height);
  canvas.width = newWidth.toString();
  canvas.height = newHeight.toString();

}
else if (height >= (1.2 * width)) {
  var Environment = document.querySelector("#div.Environment");
  Environment.style.height = "20%";
  //$("div.Environment").css("height","20%");
}
