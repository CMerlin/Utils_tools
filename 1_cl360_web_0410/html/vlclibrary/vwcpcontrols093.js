var ing = 0;
var pering = " ";

var seekwidth = 0;
var seekheight = 0;
var seekpos;
var seektime;
var slider;
var sliderpos = 0;
var seekallow = 657;

var time;
var timed;
var swidth;
var sheight;
var spos;
var stime;
var ssect;
var sseca;
var ssec;
var smin;

var timeron = 0;
var playing = 0;
var deinterlace = 0;
var deinterlace2 = 0;
var s;
var i;
var itos = 250;
var sect = 0;
var seca = 0;
var sec = 0;
var min = 0;
var ff = 1;

var IE = document.all?true:false;
var dragapproved = 0;
var z, x, y;


document.onclick = seekt;
document.onmousemove = timetellert;

function togglePlaying()
    {
    if (!playing)
        {
        playing = 1;
        }
    else
        {
        playing = 0;
        }
    }

function seekt(e)
    {
    if (playing)
        {
        _seek(e);
        }
    }

function timetellert(e)
    {
    if (playing)
        {
        timeteller(e);
        }
    }

function CancelMouseDown(e)
    {
    if (e === undefined)
        e = window.event;
    if (e.cancelable === undefined)
        {
        e.returnValue = false;
        drags(e);
        }
    else 
        {
        if (e.cancelable)
            {
            e.preventDefault();
            drags(e);
            }
        }
    }


function ingstate()
    {
    if (ing == 1)
        {
        pering = ".";
        ing++;
        i=setTimeout("ingstate()", itos);
        }
    else if (ing == 2)
        {
        pering = "..";
        ing++;
        i=setTimeout("ingstate()", itos);
        }
    else if (ing == 3)
        {
        pering = "...";
        ing = 0;
        i=setTimeout("ingstate()", itos);
        }
    else
        {
        pering = " ";
        ing++;
        i=setTimeout("ingstate()", itos);
        }
    }

function vlcstate()
    {
    if (vlc.input.state == 0)
        {
        document.getElementById("vlcstatus").innerHTML = ("Idling" + pering);
        s=setTimeout("vlcstate()", 1);
        }
    else if (vlc.input.state == 1)
        {
        document.getElementById("vlcstatus").innerHTML = ("Opening " + currenttrack + pering);
        s=setTimeout("vlcstate()", 1);
        }
    else if (vlc.input.state == 2)
        {
        document.getElementById("vlcstatus").innerHTML = ("Buffering " + currenttrack + pering);
        s=setTimeout("vlcstate()", 1);
        }
    else if (vlc.input.state == 3)
        {
        c = setTimeout("rightclocker()", 500);
        document.getElementById("vlcstatus").innerHTML = ("Playing " + currenttrack + pering);
        sect = Math.floor(vlc.input.time / 1000);
        seca = Math.floor(sect / 60);
        sec = (sect - seca * 60);
        min = Math.floor(sect / 60);
        if (timeron)
            { 
            if (min < 10)
                {
                if (sec < 10)
                    {
                    document.getElementById("clock").innerHTML = ("0" + min + ":" + "0" + sec + rightclock);
                    }
                else
                    {
                    document.getElementById("clock").innerHTML = ("0" + min + ":" + sec + rightclock);
                    }
                }
            else
                {
                if (sec < 10)
                    {
                    document.getElementById("clock").innerHTML = (min + ":" + "0" + sec + rightclock);
                    }
                else
                    {
                    document.getElementById("clock").innerHTML = (min + ":" + sec + rightclock);
                    }
                }
            }
        else
            {
            document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekslider.png";
            document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowleft.png";
            document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowright.png";
            document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbutton.png";
            document.getElementById("clock").innerHTML = ("0" + "0" + ":" + "0" + "0" + "/00:00");
            timeron = 1;
            }
        sliderpos = ((vlc.input.time / vlc.input.length) * seekallow);
        if (sliderpos < 0)
            {
            sliderpos = 0;
            }
        if (IE)
            {
            slider.style.pixelLeft = sliderpos + 27;
            }
        else
            {
            slider.style.left = sliderpos + 27;
            }
        playpause = "false";
        s=setTimeout("vlcstate()", 1);
        }
    else if (vlc.input.state == 4)
        {
        document.getElementById("vlcstatus").innerHTML = ("Paused " + currenttrack);
        playpause = "true";
        s=setTimeout("vlcstate()", 1);
        }
    else if (vlc.input.state == 5)
        {
        document.getElementById("vlcstatus").innerHTML = ("Stopping " + currenttrack + pering);
        s=setTimeout("vlcstate()", 1);
        }
    else if (vlc.input.state == 6)
        {
        tracknumber++;
        playtrack++;
        subtrack++;
        if (tracknumber < vlc.playlist.items.count)
            {
            clearTimeout(s, i);
            timeron = 0;
            playpause = "true";
            playpausemouseup();
            }
        else
            {
            instop = 1;
            }
        if (instop)
            {
            sliderpos = 0;
            if (IE)
                {
                slider.style.pixelLeft = sliderpos + 27;
                }
            else
                {
                slider.style.left = sliderpos + 27;
                }
            timeron = 0;
            playing = 0;
            sec = 0;
            min = 0;
            ff = 1;
            itos = 250;
            playpause = "true";
            tracknumber = 0;
            playtrack = 0;
            subtrack = 0;
            document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbuttonfalse.png";
            document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybutton.png";
            document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekslidernovideo.png";
            document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrownovideoleft.png";
            document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrownovideoright.png";
            document.getElementById("stop").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcstopbuttonpress.png"
            document.getElementById("clock").innerHTML = ("-- : -- / -- : --");
            instop = 0;
            document.getElementById("vlcstatus").innerHTML = ("Ended");
            clearTimeout(s, i);
            playlistload();
            }
        }
    else if (vlc.input.state == 7)
        {
        document.getElementById("vlcstatus").innerHTML = ("Error!");
        s=setTimeout("vlcstate()", 1);
        }
    else
        {
        document.getElementById("vlcstatus").innerHTML = ("Error!"); 
        s=setTimeout("vlcstate()", 1);       
        }
    }


function leftseekarrowmouseover()
    {
    if (playing)
        {
        document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowleftpress.png";
        }
    }
function leftseekarrowmouseout()
    {
    if (playing)
        {
        document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowleft.png";
        document.getElementById("rate").innerHTML = ("1.00x");
        ff = 1;
        vlc.input.rate = 1.0;
        itos = 250;
        }
    }
function leftseekarrowmousedown()
    {
    if (playing)
        {
        document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowleftclick.png";
        }
    }
function leftseekarrowmouseup()
    {
    if (playing)
        {
        document.getElementById("leftseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowleftpress.png";
        if (ff > 0.50)
            {
            ff /= 2;
            document.getElementById("rate").innerHTML = (ff + "0x");
            vlc.input.rate *= ff;
            itos /= ff;
            }
        else
            {
            if (ff > 0.25)
                {
                ff /= 2;
                document.getElementById("rate").innerHTML = (ff + "x");
                vlc.input.rate *= ff;
                itos /= ff;   
                }
            }
        }
    }

function rightseekarrowmouseover()
    {
    if (playing)
        {
        document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowrightpress.png";
        }
    }
function rightseekarrowmouseout()
    {
    if (playing)
        {
        document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowright.png";
        document.getElementById("rate").innerHTML = ("1.00x");
        ff = 1;
        vlc.input.rate = 1.0;
        itos = 250;
        }
    }
function rightseekarrowmousedown()
    {
    if (playing)
        {
        document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowrightclick.png";
        }
    }
function rightseekarrowmouseup()
    {
    if (playing)
        {
        document.getElementById("rightseekarrow").src = nativedirectory + imagedirectory + harddirectory + seekimages + "seekarrowrightpress.png";
        if (ff < 4)
            {
            ff *= 2;
            document.getElementById("rate").innerHTML = (ff + ".00x");
            vlc.input.rate *= ff;
            itos /= ff;
            }
        }
    }

function seekslidermouseover()
    {
    if (playing)
        {
        document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseeksliderpress.png";
        }
    }
function seekslidermouseout()
    {
    if (playing)
        {
        document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekslider.png";
        }
    }


function playpausemouseover()
    {
    if (playpause == "true")
        {
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybuttonpress.png";
        }
    else
        {
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpausebuttonpress.png";
        }
    }
function playpausemouseout()
    {
    if (playpause == "true")
        {
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybutton.png";
        }
    else
        {
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpausebutton.png";
        }
    }
function playpausemousedown()
    {
    if (playpause == "true")
        {
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybuttonclick.png";
        }
    else
        {
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpausebuttonclick.png";
        }
    }
function playpausemouseup()
    {
    if (vlc.playlist.items.count == 0)
        {
        document.getElementById("vlcstatus").innerHTML = ("Error! The playlist is empty!");
        document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybuttonpress.png";
        }
    else
        {
        if (playpause == "true")
            {
            if (!timeron)
                {
                vlc.playlist.playItem(tracknumber);
                currenttrack = plitem[playtrack];
                subtitles = stitem[subtrack];
                vlcstate();
                ingstate();
                }
            else
                {
                vlc.playlist.play();
                }
            document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpausebuttonpress.png";
            }
        else
            {
            vlc.playlist.togglePause();
            document.getElementById("playpause").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcplaybuttonpress.png";
            }
        }
    playing = 1;
    }

function previousmouseover()
    {
    document.getElementById("previous").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpreviousbuttonpress.png";
    }
function previousmouseout()
    {
    document.getElementById("previous").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpreviousbutton.png";
    }
function previousmousedown()
    {
    document.getElementById("previous").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpreviousbuttonclick.png";
    }
function previousmouseup()
    {
    document.getElementById("previous").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcpreviousbuttonpress.png";
    tracknumber--;
    playtrack--;
    subtrack--;
    if (tracknumber >= 0)
        {
        clearTimeout(s, i);
        timeron = 0;
        playpause = "true";
        playpausemouseup();
        }
    else
        {
        stopmouseup();
        }
    }


function stopmouseover()
    {
    document.getElementById("stop").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcstopbuttonpress.png";
    }
function stopmouseout()
    {
    document.getElementById("stop").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcstopbutton.png";
    }
function stopmousedown()
    {
    document.getElementById("stop").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcstopbuttonclick.png";
    }
function stopmouseup()
    {
    document.getElementById("stop").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcstopbuttonpress.png";
    instop = 1;
    tracknumber = vlc.playlist.items.count - 1;
    vlc.playlist.stop();
    }

function nextmouseover()
    {
    document.getElementById("next").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcnextbuttonpress.png";
    }
function nextmouseout()
    {
    document.getElementById("next").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcnextbutton.png";
    }
function nextmousedown()
    {
    document.getElementById("next").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcnextbuttonclick.png";
    }
function nextmouseup()
    {
    document.getElementById("next").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcnextbuttonpress.png";
    tracknumber++;
    playtrack++;
    subtrack++;
    if (tracknumber < vlc.playlist.items.count)
        {
        clearTimeout(s, i);
        timeron = 0;
        playpause = "true";
        playpausemouseup();
        }
    else
        {
        stopmouseup();
        }
    }


function fullscreenmouseover()
    {
    if (playing)
        {
        document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbuttonpress.png";
        }
    }
function fullscreenmouseout()
    {
    if (playing)
        {
        document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbutton.png";
        }
    }
function fullscreenmousedown()
    {
    if (playing)
        {
        document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbuttonclick.png";
        }
    }
function fullscreenmouseup()
    {
    if (playing)
        {
        document.getElementById("fullscreen").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcfullscreenbuttonpress.png";
        vlc.video.toggleFullscreen();
        }
    }
function fullscreenexitclick()
    {
    if (fullscreen=="true")
        {
        vlc.video.toggleFullscreen();
        fullscreen = "false";
        }
    }

function deinterlacemouseover()
    {
    if (playing)
        {
        document.getElementById("deinterlace").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlacebuttonpress.png";
        }
    }
function deinterlacemouseout()
    {
    if (playing)
        {
        document.getElementById("deinterlace").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlacebutton.png";
        }
    }
function deinterlacemousedown()
    {
    if (playing)
        {
        document.getElementById("deinterlace").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlacebuttonclick.png";
        }
    }
function deinterlacemouseup()
    {
    if (playing)
        {
        document.getElementById("deinterlace").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlacebuttonpress.png";
	if (deinterlace == 0) {
            vlc.video.deinterlaceEnable(1, "x");
	    deinterlace = 1;
	} else { 
            vlc.video.deinterlaceDisable(1);
	    deinterlace = 0;
	}
        }
    }

function deinterlace2mouseover()
    {
    if (playing)
        {
        document.getElementById("deinterlace2").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlace2buttonpress.png";
        }
    }
function deinterlace2mouseout()
    {
    if (playing)
        {
        document.getElementById("deinterlace2").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlace2button.png";
        }
    }
function deinterlace2mousedown()
    {
    if (playing)
        {
        document.getElementById("deinterlace2").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlace2buttonclick.png";
        }
    }
function deinterlace2mouseup()
    {
    if (playing)
        {
        document.getElementById("deinterlace2").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcdeinterlace2buttonpress.png";
	if (deinterlace2 == 0) {
            vlc.video.deinterlaceEnable(2, "x");
	    deinterlace2 = 1;
	} else { 
            vlc.video.deinterlaceDisable(2);
	    deinterlace2 = 0;
	}
        }
    }

function playlistmouseover()
    {
    document.getElementById("playlist").src = nativedirectory + imagedirectory + harddirectory + controlimages + "playlistpress.png";
    }
function playlistmouseout()
    {
    document.getElementById("playlist").src = nativedirectory + imagedirectory + harddirectory + controlimages + "playlist.png";
    }
function playlistmousedown()
    {
    document.getElementById("playlist").src = nativedirectory + imagedirectory + harddirectory + controlimages + "playlistclick.png";
    }
function playlistmouseup()
    {
    document.getElementById("playlist").src = nativedirectory + imagedirectory + harddirectory + controlimages + "playlistpress.png";
    document.getElementById("playlister").style.display = "inline";
    }

function mute()
    {
    if (!mutevalue)
        {
        vlc.audio.toggleMute();
        document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicatormute.png";
        document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebarmute.png";
        mutevalue = 1;
        }
    else
        {
        document.getElementById("mute").src = indicatorvalue;
        mutevalue = 0;
        level = level - 1;
        volumelevel();
        }
    }

function volumelevel()
    {
    if (level==1)
        {
        if (mutevalue)
            {
            mute();
            }
        else
            {
            document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator1.png";
            document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar100.png";
            level++;
            vlc.audio.volume = 100;
            indicatorvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator1.png";
            volumebarvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar100.png";
            }
        }
    else if (level==2)
        {
        if (mutevalue)
            {
            mute();
            }
        else
            {
            document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator2.png";
            document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar150.png";
            level++;
            vlc.audio.volume = 150;
            indicatorvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator2.png";
            volumebarvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar150.png";
            }
        }
    else if (level==3)
        {
        if (mutevalue)
            {
            mute();
            }
        else
            {
            document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator3.png";
            document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebarfull.png";
            level++;
            vlc.audio.volume = 200;
            indicatorvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator3.png";
            volumebarvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebarfull.png";
            }
        }
    else if (level==4)
        {
        if (mutevalue)
            {
            mute();
            }
        else
            {
            document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicatormute.png";
            document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebarmute.png";
            level = 0;
            vlc.audio.volume = 0;
            indicatorvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicatormute.png";
            volumebarvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebarmute.png";
            }
        }
    else
        {
        if (mutevalue)
            {
            mute();
            }
        else
            {
            document.getElementById("mute").src = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator0.png";
            document.getElementById("volumebar").src = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar50.png";
            level++;
            vlc.audio.volume = 50;
            indicatorvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "vlcvolumeindicator0.png";
            volumebarvalue = nativedirectory + imagedirectory + harddirectory + controlimages + "volumebar50.png";
            }
        }
    }


function _seek(e) 
    {
    if (IE)
        {
        seekwidth = event.clientX + document.body.scrollLeft - seekbarwidth;
        seekheight = event.clientY + document.body.scrollTop - seekbarheight - seekbarbottom;
        }
    else 
        {
        seekwidth = e.pageX - seekbarwidth;
        seekheight = e.pageY - seekbarheight - seekbarbottom;
        } 
    if (seekwidth < 0)
        {
        seekwidth = 0;
        }
    if (seekheight < 0)
        {
        seekheight = 0;
        }
    if (vlc.input.state > 2 && vlc.input.state < 5)
        {
        if (seekwidth > 84 && seekwidth < 751 - seekbarright)
            {
            if (seekheight > 627 && seekheight < 665)
                {
                seekpos = seekwidth - 92;
                seektime = seekpos * (vlc.input.length / seekallow);
                vlc.input.time = seektime;
                seekwidth = 0;
                seekheight = 0;
                }
            }
        }
    }

function move(e)
    {
    if (IE)
        {
        seekwidth = event.clientX + document.body.scrollLeft - seekbarwidth;
        seekheight = event.clientY + document.body.scrollTop - seekbarheight - seekbarbottom;
        }
    else 
        {
        seekwidth = e.pageX - seekbarwidth;
        seekheight = e.pageY - seekbarheight - seekbarbottom;
        }  
    if (seekwidth < 0)
        {
        seekwidth = 0;
        }
    if (seekheight < 0)
        {
        seekheight = 0;
        }
    seekpos = seekwidth - 92;
    if (dragapproved)
        {
        if (vlc.input.state > 2 && vlc.input.state < 5)
            {
            if (seekwidth > 88  && seekwidth < 751 - seekbarright)
                {
                if (seekheight > 627 && seekheight < 665)
                    {
                    if (IE)
                        {
                        z.style.pixelLeft = temp1 + event.clientX - x;
                        seektime = seekpos * (vlc.input.length / seekallow);
                        vlc.input.time = seektime;
                        document.getElementById("seekbar").onmouseup = undrags;
                        return false;
                        }
                    else
                        {
                        z.style.left = temp1 + e.pageX - x;
                        seektime = seekpos * (vlc.input.length / seekallow);
                        vlc.input.time = seektime;
                        document.getElementById("seekbar").onmouseup = undrags;
                        return false;
                        }
                    }
                return false;
                }
            return false;
            }
        }
    document.getElementById("seekbar").title = seektime;
    }

function drags(e)
    {
    if (IE)
        {
        if (event.srcElement.className == "drag")
            {
            dragapproved = 1;
            z = event.srcElement;
            temp1 = z.style.pixelLeft;
            x = event.clientX;
            temp2 = z.style.pixelTop;
            y = event.clientY;
            document.getElementById("seekslider").onmousemove = move;
            }
        }
    else
        {
        if (e.target.className == "drag")
            {
            dragapproved = 1;
            z = e.target;
            temp1 = z.style.left;
            x = e.pageX;
            temp2 = z.style.top;
            y = e.pageY;
            document.getElementById("seekslider").onmousemove = move;
            }
        }
    if (vlc.input.state > 2 && vlc.input.state < 5)
        {
        document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseeksliderclick.png";
        }
    }

function undrags()
    {
    dragapproved = 0;
    if (vlc.input.state > 2 && vlc.input.state < 5)
        {
        if (seekwidth > 88  && seekwidth < 751  - seekbarright)
            {
            if (seekheight > 627 && seekheight < 665)
                {
                document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseeksliderpress.png";
                }
            else
                {
                document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekslider.png";
                }
            }
        }
    else
        {
        document.getElementById("seekslider").src = nativedirectory + imagedirectory + harddirectory + seekimages + "vlcseekslider.png";
        }
    }


function timeteller(e)
    {
    if (IE)
        {
        swidth = event.clientX + document.body.scrollLeft - seekbarwidth;
        sheight = event.clientY + document.body.scrollTop - seekbarheight - seekbarbottom;
        }
    else 
        {
        swidth = e.pageX - seekbarwidth;
        sheight = e.pageY - seekbarheight - seekbarbottom;
        }  
    if (swidth < 0)
        {
        swidth = 0;
        }
    if (sheight < 0)
        {
        sheight = 0;
        }
    spos = swidth - 92;
    if (vlc.input.state > 2 && vlc.input.state < 5)
        {
        if (seekwidth > 88  && seekwidth < 751 - seekbarright)
            {
            if (seekheight > 627 && seekheight < 665)
                {
                timed = spos * (vlc.input.length / seekallow);
                ssect = Math.floor(timed / 1000);
                sseca = Math.floor(ssect / 60);
                ssec = (ssect - sseca * 60);
                smin = Math.floor(ssect / 60);
                if (smin < 10)
                    {
                    if (ssec < 10)
                        {
                        document.getElementById("seekbar").title = ("0" + smin + ":" + "0" + ssec + rightclock);
                        }
                    else
                        {
                        document.getElementById("seekbar").title = ("0" + smin + ":" + ssec + rightclock);
                        }
                    }
                else
                    {
                    if (ssec < 10)
                        {
                        document.getElementById("seekbar").title = (smin + ":" + "0" + ssec + rightclock);
                        }
                    else
                        {
                        document.getElementById("seekbar").title = (smin + ":" + ssec + rightclock);
                        }
                    }
                }
            }
        }
    }
