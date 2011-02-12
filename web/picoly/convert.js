function convert() {
	var pianoroll = $("pianoroll");
	var offset = pianoroll.positionedOffset();
	var bars = $$(".bar");
	var result = "";
	for(var i=0; i<bars.length; i++) {
		var x = parseInt(bars[i].style.left) - offset[0] -101;
		var y = parseInt(bars[i].style.top) - offset[1] -1;
		var height = (420-y) / 12;
		//alert(x + " , " + y + " , " + code(height));
		result += code(height) + " ";
	}
	return result;
}
function code(height) {
	var result;
	var octave = Math.floor(height/12) + 3;
	switch(height % 12) {
	case 0:
		result = "c";
		break;
	case 1:
		result = "c#";
		break;
	case 2:
		result = "d";
		break;
	case 3:
		result = "d#";
		break;
	case 4:
		result = "e";
		break;
	case 5:
		result = "f";
		break;
	case 6:
		result = "f#";
		break;
	case 7:
		result = "g";
		break;
	case 8:
		result = "g#";
		break;
	case 9:
		result = "a";
		break;
	case 10:
		result = "a#";
		break;
	case 11:
		result = "b";
		break;
	}
	return "o" + octave + result;
}
