var dewidth = 720;
var deheight = 540;
var dwidth = 0;
var dheight = 0;
var sdwidth = 0;
var sdheight = 0;
var seekbarwidth = -50;
var seekbarheight = -71;
var seekbarright = 0;
var seekbarbottom = 0;
var r;

var f;
var cp;
var sb;
var cb;
var ib;
var plh;

var controlpanellist = ["seekbar",
"controlbar",
"infobar"];

var seek = ["leftseekarrow",
"seekbarleft",
"seekslider",
"seekbarright",
"rightseekarrow"];

var seekimage = ["Imagesv093/Seekbar/seekarrownovideoleft.png",
"Imagesv093/Seekbar/seekbaredgeleft.png",
"Imagesv093/Seekbar/vlcseekslidernovideo.png",
"Imagesv093/Seekbar/seekbaredgeright.png",
"Imagesv093/Seekbar/seekarrownovideoright.png"];

var seektitle = ["Slower",
"",
"Seek",
"",
"Faster"];

var seekclass = ["button",
"",
"drag",
"",
"button"];

var control = ["playpause", 
"previous",
"stop",
"next",
"fullscreen",
"playlist",
"deinterlace",
"deinterlace2",
"mute",
"volumebar"];


var controltag = ["img",
"img",
"img",
"img",
"img",
"img",
"img",
"img",
"img",
"img"];

var controlimage = ["Imagesv093/Controlbar/vlcplaybutton.png",
"Imagesv093/Controlbar/vlcpreviousbutton.png",
"Imagesv093/Controlbar/vlcstopbutton.png",
"Imagesv093/Controlbar/vlcnextbutton.png",
"Imagesv093/Controlbar/vlcfullscreenbuttonfalse.png",
"Imagesv093/Controlbar/playlist.png",
"Imagesv093/Controlbar/vlcdeinterlacebutton.png",
"Imagesv093/Controlbar/vlcdeinterlace2button.png",
"Imagesv093/Controlbar/vlcvolumeindicator0.png",
"Imagesv093/Controlbar/volumebar50.png"];

var controltitle = ["Play",
"Play previous item in playlist",
"Stop",
"Play next item in playlist",
"Fullscreen",
"Playlist",
"Deinterlace",
"Deinterlace second video stream",
"Mute",
"Volume"];

var controlclass = ["button",
"button",
"button",
"button",
"button",
"button",
"button",
"button",
"button",
"button"];


var info = ["img",
"small",
"img",
"small",
"small"];

var infotitle = ["",
"Playback Status",
"",
"Rate",
"Clock"];

var infoimage = ["Imagesv093/Infobar/vlcinfobaredgeleft.png",
"",
"Imagesv093/Infobar/vlcinfobaredgeright.png",
"",
""];

var infotext = ["",
"Idling...",
"",
"1.00x",
"-- : -- / -- : --"];

var infoid = ["infobaredgeleft",
"vlcstatus",
"infobaredgeright",
"rate",
"clock"];

var plheadings = ["Position",
"Name",
"Duration"/*,
"Options"*/];


function vwcpsetup()
    {
    findPosition();
    vwcpdisplay();
    vwcpshow();
    filepath();
    resize();
    playlistload();
    vlc.audio.volume = volumevalue;
    slider = document.getElementById("seekslider");
    }

function vwcpshow()
    {
    for (cp in controlpanellist)
        {
        var controldiv = document.getElementById("vlccontrolpanel").appendChild(document.createElement("div"));
        controldiv.id = controlpanellist[cp];
        if (cp == 0)
            {
            controldiv.title= "Time";
            controldiv.className = "button";
            }
        }
        document.getElementById("seekbar").ondblclick = seekt;
    for (sb in seek)
        {
        var seekimg = document.getElementById("seekbar").appendChild(document.createElement("img"));
        seekimg.id = seek[sb];
        if (seekimage[sb] != "")
            {
            seekimg.src = seekimage[sb];
            }
        if (seektitle[sb] != "")
            {
            seekimg.title = seektitle[sb];
            }
        if (seekclass[sb] != "")
            {
            seekimg.className = seekclass[sb];
            }
        }
    document.getElementById("leftseekarrow").onmouseout = leftseekarrowmouseout;
    document.getElementById("leftseekarrow").onmouseover = leftseekarrowmouseover;
    document.getElementById("leftseekarrow").onmouseup = leftseekarrowmouseup;
    document.getElementById("leftseekarrow").onmousedown = leftseekarrowmousedown;
    document.getElementById("rightseekarrow").onmouseout = rightseekarrowmouseout;
    document.getElementById("rightseekarrow").onmouseover = rightseekarrowmouseover;
    document.getElementById("rightseekarrow").onmouseup = rightseekarrowmouseup;
    document.getElementById("rightseekarrow").onmousedown = rightseekarrowmousedown;
    document.getElementById("seekslider").onmouseout = seekslidermouseout;
    document.getElementById("seekslider").onmouseover = seekslidermouseover;
    document.getElementById("seekslider").onmousedown = CancelMouseDown;
    for (cb in control)
        {
        var controlimg = document.getElementById("controlbar").appendChild(document.createElement(controltag[cb]));
        controlimg.id = control[cb];
        if (controlimage[cb] != "")
            {
            controlimg.src = controlimage[cb];
            }
        if (controltitle[cb] != "")
            {
            controlimg.title = controltitle[cb];
            }
        if (controlclass[cb] != "")
            {
            controlimg.className = controlclass[cb];
            }
        }
    document.getElementById("playpause").onmouseout = playpausemouseout;
    document.getElementById("playpause").onmouseover = playpausemouseover;
    document.getElementById("playpause").onmouseup = playpausemouseup;
    document.getElementById("playpause").onmousedown = playpausemouseout;
    document.getElementById("previous").onmouseout = previousmouseout;
    document.getElementById("previous").onmouseover = previousmouseover;
    document.getElementById("previous").onmouseup = previousmouseup;
    document.getElementById("previous").onmousedown = previousmousedown;
    document.getElementById("stop").onmouseout = stopmouseout;
    document.getElementById("stop").onmouseover = stopmouseover;
    document.getElementById("stop").onmouseup = stopmouseup;
    document.getElementById("stop").onmousedown = stopmousedown;
    document.getElementById("next").onmouseout = nextmouseout;
    document.getElementById("next").onmouseover = nextmouseover;
    document.getElementById("next").onmouseup = nextmouseup;
    document.getElementById("next").onmousedown = nextmousedown;
    document.getElementById("fullscreen").onmouseout = fullscreenmouseout;
    document.getElementById("fullscreen").onmouseover = fullscreenmouseover;
    document.getElementById("fullscreen").onmouseup = fullscreenmouseup;
    document.getElementById("fullscreen").onmousedown = fullscreenmousedown;
    document.getElementById("deinterlace").onmouseout = deinterlacemouseout;
    document.getElementById("deinterlace").onmouseover = deinterlacemouseover;
    document.getElementById("deinterlace").onmouseup = deinterlacemouseup;
    document.getElementById("deinterlace").onmousedown = deinterlacemousedown;
    document.getElementById("deinterlace2").onmouseout = deinterlace2mouseout;
    document.getElementById("deinterlace2").onmouseover = deinterlace2mouseover;
    document.getElementById("deinterlace2").onmouseup = deinterlace2mouseup;
    document.getElementById("deinterlace2").onmousedown = deinterlace2mousedown;
    document.getElementById("playlist").onmouseout = playlistmouseout;
    document.getElementById("playlist").onmouseover = playlistmouseover;
    document.getElementById("playlist").onmouseup = playlistmouseup;
    document.getElementById("playlist").onmousedown = playlistmousedown;
    document.getElementById("mute").onmouseup = mute;
    document.getElementById("volumebar").onmouseup = volumelevel;
    for (ib in info)
        {
        var imgid = document.getElementById("infobar").appendChild(document.createElement(info[ib]));
        imgid.id = infoid[ib];
        infoname = infoid[ib];
        if (infotext[ib] != "")
            {
            imgid.appendChild(document.createTextNode(infotext[ib]));
            }
        if (infoimage[ib] != "")
            {
            imgid.src = infoimage[ib];
            }
        if (infotitle[ib] != "")
            {
            imgid.title = infotitle[ib];
            }
        }
    var pler = document.getElementById("controlbar").appendChild(document.createElement("div"));
    pler.id = "playlister";
    var plab = document.getElementById("playlister").appendChild(document.createElement("div"));
    plab.id = "pllabel";
    plab.appendChild(document.createTextNode("Playlist"));
    var pled = document.getElementById("playlister").appendChild(document.createElement("table"));
    pled.id = "playlisted";
    var plbody = document.getElementById("playlisted").appendChild(document.createElement("tbody"));
    var plheadrow = plbody.insertRow(0);
    plheadrow.className = "playlisthead";
    for (plh in plheadings)
        {
        var plheader = plheadrow.insertCell(plh);
        plheader.appendChild(document.createTextNode(plheadings[plh]));
        }
    var ploped = document.getElementById("playlister").appendChild(document.createElement("table"));
    ploped.id = "ploptions";
    var plopbody = document.getElementById("ploptions").appendChild(document.createElement("tbody"));
    var ploprow = plopbody.insertRow(0);
    var plopcell = ploprow.insertCell(0);
    if (IE)
        {
        var pladd = plopcell.appendChild(document.createElement("button"));
        pladd.id = "close";
        pladd.value = "Close";
        pladd.className = "plobutton";
        pladd.onclick = ploptionsclose;
        }
    else
        {
        var pladd = plopcell.appendChild(document.createElement("input"));
        pladd.id = "close";
        pladd.type = "button";
        pladd.value = "Close";
        pladd.className = "plobutton";
        pladd.onclick = ploptionsclose;
        }
    }

function vwcpdisplay()
    {
    if (!playlistenabled)
        {
        document.getElementById("stop").style.left = "60px";
        document.getElementById("fullscreen").style.left = "90px";
        document.getElementById("previous").style.display = "none";
        document.getElementById("next").style.display = "none";
        }
    }

function findPosition()
    {
    var offbase = document.getElementById("vlcset");
    var seektop = 0;
    var seekleft = 0;
    do
        {
        seektop += offbase.offsetTop;
        seekleft += offbase.offsetLeft;
        }
    while (offbase = offbase.offsetParent);
    seekbarheight = (seekbarheight + seektop - 15);
    seekbarwidth = (seekbarwidth + seekleft - 10);
    }


function filepath()
    {
    document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrownovideoleft.png";
    document.getElementById("seekbarleft").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekbaredgeleft.png";
    document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekslidernovideo.png";
    document.getElementById("seekbarright").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekbaredgeright.png";
    document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrownovideoright.png";
    document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybutton.png";
    document.getElementById("previous").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpreviousbutton.png";
    document.getElementById("stop").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcstopbutton.png";
    document.getElementById("next").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcnextbutton.png";
    document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbuttonfalse.png";
    document.getElementById("playlist").src = nativedirectory + imagedirectory + harddirectory + controlimages + "playlist.png";
    document.getElementById("deinterlace").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlacebutton.png";
    document.getElementById("deinterlace2").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlace2button.png";
    document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator0.png";
    document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar50.png";
    document.getElementById("infobaredgeleft").src = nativedirectory + imagedirectory + harddirectory + infoimages + "vlcinfobaredgeleft.png";
    document.getElementById("infobaredgeright").src = nativedirectory + imagedirectory + harddirectory + infoimages + "vlcinfobaredgeright.png";
    document.getElementById("seekbar").style.backgroundImage = "url(" + nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekbar.png" + ")";
    document.getElementById("controlbar").style.backgroundImage = "url(" + nativedirectory + imagedirectory + harddirectory + controlimages + "vlccontrolbar.png" + ")";
    document.getElementById("infobar").style.backgroundImage = "url(" + nativedirectory + imagedirectory + harddirectory + infoimages + "vlcinfobar.png" + ")";
    }

function resize()
    {
    /*dwidth = displaywidth;
    dheight = displayheight;
    document.getElementById("vlc").style.width = dwidth + "px";
    document.getElementById("vlc").style.height = dheight + "px";
    document.getElementById("screen").style.width = dwidth + "px";
    document.getElementById("screen").style.height = dheight + "px";
    document.getElementById("vlcplayer").style.width = dwidth + "px";
    document.getElementById("vlcset").style.width = dwidth + "px";
    sdwidth = dewidth - dwidth;
    sdheight = deheight - dheight;
    seekbarright = (seekbarright + sdwidth);
    seekbarbottom = (seekbarbottom - sdheight);
    seekallow = (seekallow - sdwidth);
*/
    }
