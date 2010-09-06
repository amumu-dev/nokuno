$(function() {
    setInterval("frame()",100);
});
var time = 0;
function frame() {
    var screen = document.getElementById('screen');
    var ctx = screen.getContext('2d');
    //ctx.clearRect(0,0,320,480);
    ctx.fillStyle   = 'rgb(255, 255, 255)';
    ctx.strokeStyle = 'rgb(255, 0, 0)';
    ctx.lineWidth = 2;
    var num = 10;
    for (var i = 0; i < num; i++) {
        var t = Math.PI*2*(i+time/3)/num;
        ctx.beginPath();
        ctx.arc(160 + 5 * time * Math.sin(t), 240 + 5 * time * Math.cos(t), 5, 0, Math.PI*2, false);
        ctx.fill();
        ctx.stroke();
    }
    time ++;
}
