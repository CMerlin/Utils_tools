var fullscreen = "false";
var playpause = "true";
var instop = 0;

var level = 1;
var mutevalue = 0;
var volumevalue = 50;
var tracknumber = 0;
var subtrack = 0;
var subtitles = stitem[0];
var currenttrack = plitem[0];
var options = "";
var t;
var tracker;
var pltrack = "";
var pltime = "";
var playtrack = 0;
var l;

var plitemrow = "";
var pos = "";
var list = "";
var dur = "";
var opt = "";

var rightclock = "";
var rsect;
var rseca;
var rsec;
var rmin;
var rmint;
var rmina;
var rhour;
var c;

function playlistload()
    {
    vlc.playlist.items.clear();
    var f = 0;
    var playlistheight = 30;
    var plheight = 30;
    for (t in plitem)
        {
        plheight += 30;
        f++;
        pltrack = plitem[t];
        pltime = plduration[t];
	var _ploption = ploption[t];
        tracker = nativedirectory + videodirectory + pltrack;
	var options;
	if (typeof _ploption != "undefined" && _ploption != "")
		options = new Array(":rtsp-tcp", ":no-video-title-show", ":sout-all", ":rtsp-caching=200", _ploption);
		//options = new Array(":vout=opengl", ":no-video-title-show", ":sout-all", _ploption);
	else
        	options = new Array(":rtsp-tcp", ":no-video-title-show", ":rtsp-caching=200");
        	//options = new Array(":vout=opengl", ":no-video-title-show");
        vlc.playlist.add(tracker, null, options);
        var tblBody = document.getElementById("playlisted").tBodies[0];
        var plitemrow = tblBody.insertRow(-1);
        var plitemposition = plitemrow.insertCell(0);
        var plitemname = plitemrow.insertCell(1);
        var plitemduration = plitemrow.insertCell(2);
        //var plitemoptions = plitemrow.insertCell(3);
        plitemposition.appendChild(document.createTextNode(f + "."));
        plitemname.appendChild(document.createTextNode(pltrack));
        plitemduration.appendChild(document.createTextNode(pltime));
        //plitemoptions.appendChild(document.createTextNode(options));
        plitemrow.id = "plitem" + f;
        plitemrow.className = "playlistbutton";
        var plitemf = "plitem" + f;
        if (f == 1)
            {
            document.getElementById(plitemf).onmouseover = plitem1mouseover;
            document.getElementById(plitemf).onmouseout = plitem1mouseout;
            document.getElementById(plitemf).onclick = plitem1click;
            }
        else if (f == 2)
            {
            document.getElementById(plitemf).onmouseover = plitem2mouseover;
            document.getElementById(plitemf).onmouseout = plitem2mouseout;
            document.getElementById(plitemf).onclick = plitem2click;
            }
        else if (f == 3)
            {
            document.getElementById(plitemf).onmouseover = plitem3mouseover;
            document.getElementById(plitemf).onmouseout = plitem3mouseout;
            document.getElementById(plitemf).onclick = plitem3click;
            }
        else if (f == 4)
            {
            document.getElementById(plitemf).onmouseover = plitem4mouseover;
            document.getElementById(plitemf).onmouseout = plitem4mouseout;
            document.getElementById(plitemf).onclick = plitem4click;
            }
        else if (f == 5)
            {
            document.getElementById(plitemf).onmouseover = plitem5mouseover;
            document.getElementById(plitemf).onmouseout = plitem5mouseout;
            document.getElementById(plitemf).onclick = plitem5click;
            }
        else if (f == 6)
            {
            document.getElementById(plitemf).onmouseover = plitem6mouseover;
            document.getElementById(plitemf).onmouseout = plitem6mouseout;
            document.getElementById(plitemf).onclick = plitem6click;
            }
        else if (f == 7)
            {
            document.getElementById(plitemf).onmouseover = plitem7mouseover;
            document.getElementById(plitemf).onmouseout = plitem7mouseout;
            document.getElementById(plitemf).onclick = plitem7click;
            }
        else if (f == 8)
            {
            document.getElementById(plitemf).onmouseover = plitem8mouseover;
            document.getElementById(plitemf).onmouseout = plitem8mouseout;
            document.getElementById(plitemf).onclick = plitem8click;
            }
        else if (f == 9)
            {
            document.getElementById(plitemf).onmouseover = plitem9mouseover;
            document.getElementById(plitemf).onmouseout = plitem9mouseout;
            document.getElementById(plitemf).onclick = plitem9click;
            }
        else if (f == 10)
            {
            document.getElementById(plitemf).onmouseover = plitem10mouseover;
            document.getElementById(plitemf).onmouseout = plitem10mouseout;
            document.getElementById(plitemf).onclick = plitem10click;
            }
        else
            {
            document.getElementById(plitemf).onmouseover = plitem11mouseover;
            document.getElementById(plitemf).onmouseout = plitem11mouseout;
            document.getElementById(plitemf).onclick = plitem11click;
            }
        document.getElementById("playlister").style.height = playlistheight + plheight + "px";
        }
    }

function rightclocker()
    {
    rsect = Math.floor(vlc.input.length / 1000);
    rseca = Math.floor(rsect / 60);
    rsec = (rsect - rseca * 60);
    rmin = Math.floor(rsect / 60);
    rmina = Math.floor(rmin / 60);
    rhour = rmina;
    rmin = rmin - rhour*60;
    if (rhour < 1)
        {
        if (rmin < 10)
            {
            if (rsec < 10)
                {
                rightclock = ("/" + "0" + rmin + ":" + "0" + rsec);
                }
            else
                {
                rightclock = ("/" + "0" + rmin + ":" + rsec);
                }
            }
        else
            {
            if (rsec < 10)
                {
                rightclock = ("/" + rmin + ":" + "0" + rsec);
                }
            else
                {
                rightclock = ("/" + rmin + ":" + rsec);
                }
            }
        }
    else
        {
        if (rmin < 10)
            {
            if (rsec < 10)
                {
                rightclock = ("/" + rhour + ":" + "0" + rmin + ":" + "0" + rsec);
                }
            else
                {
                rightclock = ("/" + rhour + ":" + "0" + rmin + ":" + rsec);
                }
            }
        else
            {
            if (rsec < 10)
                {
                rightclock = ("/" + rhour + ":" + rmin + ":" + "0" + rsec);
                }
            else
                {
                rightclock = ("/" + rhour + ":" + rmin + ":" + rsec);
                }
            }
        }
    timeron = 1;
    }

function plitem1mouseover()
    {
    document.getElementById("plitem1").style.backgroundColor = "#7de5ed";
    }
function plitem1mouseout()
    {
    document.getElementById("plitem1").style.backgroundColor = "#fbfad6";
    }
function plitem2mouseover()
    {
    document.getElementById("plitem2").style.backgroundColor = "#7de5ed";
    }
function plitem2mouseout()
    {
    document.getElementById("plitem2").style.backgroundColor = "#fbfad6";
    }
function plitem3mouseover()
    {
    document.getElementById("plitem3").style.backgroundColor = "#7de5ed";
    }
function plitem3mouseout()
    {
    document.getElementById("plitem3").style.backgroundColor = "#fbfad6";
    }
function plitem4mouseover()
    {
    document.getElementById("plitem4").style.backgroundColor = "#7de5ed";
    }
function plitem4mouseout()
    {
    document.getElementById("plitem4").style.backgroundColor = "#fbfad6";
    }
function plitem5mouseover()
    {
    document.getElementById("plitem5").style.backgroundColor = "#7de5ed";
    }
function plitem5mouseout()
    {
    document.getElementById("plitem5").style.backgroundColor = "#fbfad6";
    }
function plitem6mouseover()
    {
    document.getElementById("plitem6").style.backgroundColor = "#7de5ed";
    }
function plitem6mouseout()
    {
    document.getElementById("plitem6").style.backgroundColor = "#fbfad6";
    }
function plitem7mouseover()
    {
    document.getElementById("plitem7").style.backgroundColor = "#7de5ed";
    }
function plitem7mouseout()
    {
    document.getElementById("plitem7").style.backgroundColor = "#fbfad6";
    }
function plitem8mouseover()
    {
    document.getElementById("plitem8").style.backgroundColor = "#7de5ed";
    }
function plitem8mouseout()
    {
    document.getElementById("plitem8").style.backgroundColor = "#fbfad6";
    }
function plitem9mouseover()
    {
    document.getElementById("plitem9").style.backgroundColor = "#7de5ed";
    }
function plitem9mouseout()
    {
    document.getElementById("plitem9").style.backgroundColor = "#fbfad6";
    }
function plitem10mouseover()
    {
    document.getElementById("plitem10").style.backgroundColor = "#7de5ed";
    }
function plitem10mouseout()
    {
    document.getElementById("plitem10").style.backgroundColor = "#fbfad6";
    }
function plitem11mouseover()
    {
    document.getElementById("plitem11").style.backgroundColor = "#7de5ed";
    }
function plitem11mouseout()
    {
    document.getElementById("plitem11").style.backgroundColor = "#fbfad6";
    }


function plitemdblclick()
    {
    clearTimeout(s, i);
    timeron = 0;
    playpause = "true";
    document.getElementById("playlister").style.display = "none";
    playpausemouseup();
    }

function plitem1click()
    {
    tracknumber = 0;
    playtrack = 0;
    subtrack = 0;
    plitemdblclick();
    }

function plitem2click()
    {
    tracknumber = 1;
    playtrack = 1;
    subtrack = 1;
    plitemdblclick();
    }

function plitem3click()
    {
    tracknumber = 2;
    playtrack = 2;
    subtrack = 2;
    plitemdblclick();
    }

function plitem4click()
    {
    tracknumber = 3;
    playtrack = 3;
    subtrack = 3;
    plitemdblclick();
    }

function plitem5click()
    {
    tracknumber = 4;
    playtrack = 4;
    subtrack = 4;
    plitemdblclick();
    }

function plitem6click()
    {
    tracknumber = 5;
    playtrack = 5;
    subtrack = 5;
    plitemdblclick();
    }

function plitem7click()
    {
    tracknumber = 6;
    playtrack = 6;
    subtrack = 6;
    plitemdblclick();
    }

function plitem8click()
    {
    tracknumber = 7;
    playtrack = 7;
    subtrack = 7;
    plitemdblclick();
    }

function plitem9click()
    {
    tracknumber = 8;
    playtrack = 8;
    subtrack = 8;
    plitemdblclick();
    }

function plitem10click()
    {
    tracknumber = 9;
    playtrack = 9;
    subtrack = 9;
    plitemdblclick();
    }

function plitem11click()
    {
    tracknumber = 10;
    playtrack = 10;
    subtrack = 10;
    plitemdblclick();
    }

function ploptionsclose()
    {
    document.getElementById("playlister").style.display = "none";
    }
