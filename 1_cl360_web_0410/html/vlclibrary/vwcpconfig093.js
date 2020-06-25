/*VLC Web Control Panel: Configuration File*/



//Directory Settings

/*You can set these variables to point to image or video files
in other folders than the one containing your HTML file.  Please 
make sure to leave the images in their respective folders in
the "Imagesv092" folder, or your filepaths will be incorrect.*/

/*If you wish to place the .js libraries or external CSS file
in another directory you will need to set the references manually
in the head of your HTML file.  By default the filepaths are set
to whatever folder contains your HTML file.*/

var nativedirectory = "";
var videodirectory = "";
var imagedirectory = "";
var harddirectory = "Imagesv093/";
var seekimages = "Seekbar/";
var controlimages = "Controlbar/";
var infoimages = "Infobar/";


//Display Settings

/*You may set the height and width of the webplugin to be displayed 
in the webpage by setting the variables to the proper dimensions.
The control panel will mimic the plugins width.*/

var displaywidth = 480;

var displayheight = 360;


//Playlist Settings

/*Set this variable to 1 to enable playlist functions.  Do not enable 
them unless you plan to play more than one video in the player.  
Default is disabled.*/

var playlistenabled = 1;

/*specify the filenames for the files in the playlist in the "plitem" array.*/

var plitem = [];

/*Specify the subtitle tracks for each file, if any. 0 disables subtitles. Use -1 for no subtitles.*/

var stitem = [-1, -1];

/*Specify file durations in "mm:ss" format. (Vlc does not allow input length to be read from
a file while it is not playing.)*/

var plduration = ["9999:59", "9999:59"];

/*
 * play item options
 */
var ploption = [];
