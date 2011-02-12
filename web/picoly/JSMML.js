/*
 * Author: Yuichi Tateno
 * http://rails2u.com/
 *
 * The MIT Licence.
 */

JSMML = (function() {
  return function(swfurl) {
    this.mmlPlayer = document.getElementById(JSMML.mmlID);
    this.initialize.call(this);
  }
})();

JSMML.VESION = '1.0.2';
JSMML.setSWFVersion = function(v) { JSMML.SWF_VERSION = v };
JSMML.SWF_VERSION = 'SWF don\'t load, yet.';
JSMML.toString = function() {
    return 'JSMML VERSION: ' + JSMML.VESION + ', SWF_VERSION: ' + JSMML.SWF_VERSION;
};

JSMML.swfurl = 'JSMML.swf';
JSMML.mmlDivID = 'jsmmlDiv';
JSMML.mmlID = 'jsmml';
JSMML.onLoad = function() {};
JSMML.loaded = false;
JSMML.instances = {};

JSMML.init = function(swfurl) {
    if (! document.getElementById(JSMML.mmlDivID)) {
        // init
        var swfname = (swfurl ? swfurl : JSMML.swfurl) + '?' + (new Date()).getTime();
        var div = document.createElement('div');
        div.id = JSMML.mmlDivID;
        div.style.display = 'inline';
        div.width = 1;
        div.height = 1;
        document.body.appendChild(div);

        if (navigator.plugins && navigator.mimeTypes && navigator.mimeTypes.length) {
            var o = document.createElement('object');
            o.id = JSMML.mmlID;
            o.classid = 'clsid:D27CDB6E-AE6D-11cf-96B8-444553540000';
            o.width = 1;
            o.height = 1;
            o.setAttribute('data', swfname);
            o.setAttribute('type', 'application/x-shockwave-flash');
            var p = document.createElement('param');
            p.setAttribute('name', 'allowScriptAccess');
            p.setAttribute('value', 'always');
            o.appendChild(p);
            div.appendChild(o);
        } else {
            // IE
            var object = '<object id="' + JSMML.mmlID + '" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="1" height="1"><param name="movie" value="' + swfname + '" /><param name="bgcolor" value="#FFFFFF" /><param name="quality" value="high" /><param name="allowScriptAccess" value="always" /></object>';
            div.innerHTML = object;
        }
    }
}

// call from swf
JSMML.initASFinish = function() {
    JSMML.loaded = true;
    JSMML.onLoad();
}

JSMML.eventInit = function() {
    JSMML.init();
}

JSMML.prototype = {
    initialize: function() {
        this.onFinish = function() {};
        this.pauseNow = false;
    },
    uNum: function() {
        if (!this._uNum) {
            this._uNum = this.mmlPlayer._create();
            JSMML.instances[this._uNum] = this;
        }
        return this._uNum;
    },
    play: function(_mml) {
        if (!_mml && this.pauseNow) {
            this.mmlPlayer._play(this.uNum());
        } else {
            if (_mml) this.score = _mml;
            this.mmlPlayer._play(this.uNum(), this.score);
        }
        this.pauseNow = false;
    },
    stop: function() {
        this.mmlPlayer._stop(this.uNum());
    },
    pause: function() {
        this.pauseNow = true;
        this.mmlPlayer._pause(this.uNum());
    },
    destroy: function() {
        this.mmlPlayer._destroy(this.uNum());
        delete JSMML.instances[this.uNum()];
    }
    /*
    ,
    time: function() {
        return this.mmlPlayer._time(this.uNum());
    }
    */
};
/*
if (window.addEventListener) {
    window.addEventListener('load', JSMML.eventInit, false);
} else {
    window.attachEvent('onload', JSMML.eventInit);
}
*/

