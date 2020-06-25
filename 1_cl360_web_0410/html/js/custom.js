/*
* ENC1260函数库
*/

function initPageMenu() {
	//导航外观初始化
	roller.init('wm-main-top', 'v', -42, 0, 143, 20, 5);
	//导航行为初始化
	initRollerAction();
	
}

function showLeftMenuToSysInfo() {
	jQuery('#menu').hide();
	jQuery('#menu-right').css({
		"width": "965px",
		"margin-left": "15px"
	});
	jQuery('#maincontent').css({
		"width": "920px",
		"text-align": "center"
	});
}

function showLeftMenuFromSysInfo() {
	jQuery('#menu').show();
	jQuery('#menu-right').css({
		"width": "805px",
		"margin-left": "-2px"
	});
	jQuery('#maincontent').css({
		"width": "770px",
		"text-align": "left"
	});
}

function showleftMenuAnimate() {
	jQuery('#nav').hide();
	jQuery('#nav').show(500);
}

function showMainContentAnimate() {
	jQuery('#menu-right').animate({width:"toggle"}, 0);
	jQuery('#menu-right').animate({width:"toggle"}, 500);
}

function initRollerAction() {
	//加载系统信息页面
	jQuery('#nav_sysinfo').click(function() {
		if(!window.sysinfoRefreshTimestamp || (new Date().getTime() - window.sysinfoRefreshTimestamp) > 500) {
			window.sysinfoRefreshTimestamp = new Date().getTime();
			closeAllPrompt();
			jQuery('#wmform').html('');
			//roller.firstClicked = true;
			if((new Date().getTime()-roller.lastClickedTime) < 500) {
				return false;
			}
			roller.lastClickedTime = new Date().getTime();
			jQueryAjaxHtml({
				data: {"actioncode": "303"}
			});
			showLeftMenuToSysInfo();
			//showMainContentAnimate();
		} else {
			return false;
		}
	});	
	
	//加载文件管理菜单
	jQuery('#nav_filemgr').click(function() {
		if(!window.sysinfoRefreshTimestamp || (new Date().getTime() - window.sysinfoRefreshTimestamp) > 500) {
			openUploading();
			
			window.sysinfoRefreshTimestamp = new Date().getTime();
			closeAllPrompt();
			jQuery('#wmform').html('');
			//roller.firstClicked = true;
			if((new Date().getTime()-roller.lastClickedTime) < 500) {
				return false;
			}
			roller.lastClickedTime = new Date().getTime();
			jQueryAjaxHtml({
				data: {"actioncode": "323"},
				success: function(retHTML){
					if(this.renderToID) {
						closeUploading();
						
						jQuery('#' + this.renderToID).html(retHTML);
					}
				}
			});
			showLeftMenuToSysInfo();
			//showMainContentAnimate();
		} else {
			return false;
		}
	});	
	
	//加载录制、直播管理菜单
	jQuery('#nav_recordmgr').click(function() {
		if(!window.sysinfoRefreshTimestamp || (new Date().getTime() - window.sysinfoRefreshTimestamp) > 500) {
			window.sysinfoRefreshTimestamp = new Date().getTime();
			closeAllPrompt();
			jQuery('#wmform').html('');
			//roller.firstClicked = true;
			if((new Date().getTime()-roller.lastClickedTime) < 500) {
				return false;
			}
			roller.lastClickedTime = new Date().getTime();
			jQueryAjaxHtml({
				data: {"actioncode": "328"}
			});
			showLeftMenuToSysInfo();
			//showMainContentAnimate();
		} else {
			return false;
		}
	});	
	
	//加载参数设置菜单
	jQuery('#nav_paramset').click(function() {
		//roller.firstClicked = true;
		if((new Date().getTime()-roller.lastClickedTime) < 500) {
			return false;
		}
		roller.lastClickedTime = new Date().getTime();
		jQueryAjaxHtml({
			data: {"actioncode": "301"},
			renderToID: 'nav'
		});
		showLeftMenuFromSysInfo();
		showleftMenuAnimate();
	});
	
	//加载系统设置菜单
	jQuery('#nav_sysset').click(function() {
		//roller.firstClicked = true;
		if((new Date().getTime()-roller.lastClickedTime) < 500) {
			return false;
		}
		roller.lastClickedTime = new Date().getTime();
		jQueryAjaxHtml({
			data: {"actioncode": "302"},
			renderToID: 'nav'
		});
		showLeftMenuFromSysInfo();
		showleftMenuAnimate();
	});
	
	//点击第一个导航
	//jQuery('#nav_sysinfo').click();
	jQuery('#nav_recordmgr').click();
}

/*
 * 初始化透明度滑动条
 * */
function initBrightnessSlider() {
	window.cap_sliderbar = new Slider("cap_bright_slider", "cap_bright_bar", {
		onMove: function(){
			if(jQuery.browser.msie) {
				O("cap_brightness").value = Math.round(this.GetValue()) - 1;
			} else {
				O("cap_brightness").value = Math.round(this.GetValue());
			}
			
		}
	});
	
	jQuery('#cap_brightness').change(function() {
		var value = O("cap_brightness").value;
		if(isNaN(value)) {
			value = 100;
		}
		cap_sliderbar.SetValue(parseInt(value, 10));
	});
	
	window.logo_sliderbar = new Slider("logo_bright_slider", "logo_bright_bar", {
		onMove: function(){
			if(jQuery.browser.msie) {
				O("logo_brightness").value = Math.round(this.GetValue()) - 1;
			} else {
				O("logo_brightness").value = Math.round(this.GetValue());
			}
			
		}
	});
	jQuery('#logo_brightness').change(function() {
		var value = O("logo_brightness").value;
		if(isNaN(value)) {
			value = 100;
		}
		logo_sliderbar.SetValue(parseInt(value, 10));
	});
	
}

/*
 * 修正表单赋值后滑动条没反正的问题
 */
function fixBrightnessSlider() {
	var value = O("cap_brightness").value;
	if(isNaN(value)) {
		value = 100;
	}
	cap_sliderbar.SetValue(parseInt(value, 10));
	
	var value = O("logo_brightness").value;
	if(isNaN(value)) {
		value = 100;
	}
	logo_sliderbar.SetValue(parseInt(value, 10));
}

/*
 * 表单美化
 * */
function formBeautify() {
	zebraTransform.update();
}


/*
 * 初始化抬头信息
 * */
function initTopInfo() {
	var loginUserName = jQuery.cookies.get('user');
	if(loginUserName) {
		jQuery('#loginUserName').html(loginUserName);
	}
	jQuery('#logoutLink').click(function() {
		jQueryAjaxCmd({
			data: {"actioncode": "200"},
			success: function(ret) {
				eval(ret);
			}
		});
	});
}


/*
 * 显示和隐藏uploading提示层
 */
function openUploading() {
	jQuery('#uploadingDiv').width(document.body.scrollWidth);
	jQuery('#uploadingDiv').height(document.body.scrollHeight);
	jQuery('#uploadingDiv').show();
}

function closeUploading() {
	jQuery('#uploadingDiv').hide();
}

function clickLogoMenu(){
	jQuery("#menue").click();
}

//如果浏览器是IE，并且安装有vlc插件，则返回true；此判断方法不可用于firefox
function isInsalledIEVLC(){ 
    var vlcObj = null;
    var vlcInstalled= false;
    
    try {
        vlcObj = new ActiveXObject("VideoLAN.Vlcplugin.1"); 
        if( vlcObj != null ){ 
            vlcInstalled = true 
        }
    } catch (e) {
        vlcInstalled= false;
    }        
    return vlcInstalled;
} 

//仅适用于firefox浏览器是，并且安装有vlc插件，则返回true；  
  function isInsalledFFVLC(){  
        var numPlugins=navigator.plugins.length;  
         for  (i=0;i<numPlugins;i++){   
              plugin=navigator.plugins[i];  
              if(plugin.name.indexOf("VideoLAN") > -1 || plugin.name.indexOf("VLC") > -1){   
               return true;  
            }  
        }  
        return false;  
  } 
 /* 浏览器检测 */  
  function checkBrowser(){  
      var browser=navigator.appName;
      var b_version=navigator.appVersion.toLowerCase() ; 
      var version=parseFloat(b_version);
      if ( browser=="Netscape"  && version>=4 && b_version.indexOf("trident") <0) {  
          if(isInsalledFFVLC()){  
              return true;
         }else{  
        	  return false;
          }  
       }else if((browser=="Microsoft Internet Explorer" && version>=4) || (browser=="Netscape"  && version>=4 && b_version.indexOf("trident") >0)) {  
           if(isInsalledIEVLC()){  
        	   return true; 
          }else{  
        	  return false; 
         }  
       }  
  }  
  
 function getSysType(){  
      var os = navigator.platform.match(/(Win|Mac|Linux)/);//系统  
      var x = os && os[1];  
      return x.toLowerCase();  
}
  
  


