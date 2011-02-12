var $j = jQuery.noConflict();

JSMML.swfurl = 'JSMML.swf';
JSMML.onLoad = function() {
	mml = new JSMML();
}
function init(octave, section) {
	JSMML.eventInit();
	
	var pianoroll = $("pianoroll");
	var offset = pianoroll.positionedOffset();
	pianoroll.innerHTML = "";
	
	/* 1オクターブずつ追加 */
	for(var i=0; i<octave; i++) {	
		var raw = new Element("div");
		raw.className = "raw";
		
		/* 鍵盤を追加 */
		var piano = new Element("div");
		piano.className = "piano";
		var img = new Element("img");
		img.src = "data/Piano_12.png";
		img.alt = "pianoroll";
		img.style.width = "100px";
		img.style.height = "144px";
		piano.appendChild(img);
		raw.appendChild(piano);
		
		/* 小節（ブロック）を追加 */
		for(var j=0; j<section; j++) {
			var block = new Element("div");
			block.className = "block";
			block.id = "block" + i + "_" + j;
			var left = offset[0] + 100 + j * 120;
			var top = offset[1] + i * 144;
			block.style.left = left + "px";
			block.style.top = top + "px";
			/* 12音階を追加 */
			for(var m=0; m<12; m++) {
				var line = new Element("div");
				if(m==1 || m==3 || m==5 || m==8 || m==10) {
					line.className = "black";
				}
				/* 4拍子追加 */
				for(var k=0; k<4; k++) {
					var grid = new Element("div");
					grid.className= "grid";
					grid.style.poisition = "absolute";
					grid.style.left = (k * 30) + "px";
					grid.style.top = (m * 12) + "px";
					line.insert(grid);
				}
				block.insert(line);
			}
			raw.appendChild(block);
		}
		pianoroll.appendChild(raw);
	}
	
	/* イベントを追加 */
	Event.observe(pianoroll, 'click', clicked, false);
	Event.observe("play_button", 'click', play, false);
}
function clicked(evt) {
	var pianoroll = $("pianoroll");
	var offset = pianoroll.positionedOffset();
	var left = Event.pointerX(evt) - Event.pointerX(evt) % 30 + 1;
	var top = Event.pointerY(evt) - Event.pointerY(evt) % 12 - 1;
	var bar = new Element("div");
	bar.className = "bar";
	bar.style.left = left + "px";
	bar.style.top = top + "px";
	pianoroll.appendChild(bar);
}
function play(evt) {
	var text = "t120 " + convert();
	$("mml-text").value = text;
	mml.play(text);
	//mml.play("t60l16 o5r cdefedc8 efgagfe8 c4 c4 c4 c4 ccddeeffe8d8c4");
}