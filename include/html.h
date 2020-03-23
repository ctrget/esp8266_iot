static const char indexPage[] PROGMEM = "<!DOCTYPE html>\
<html lang=\"zh-cmn-Hans\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width,initial-scale=1,user-scalable=0,viewport-fit=cover\">\
    <title>ESP8266开发板设置</title>\
    <link rel=\"stylesheet\" href=\"https://cdn.bootcss.com/weui/2.2.0/style/weui.min.css\"/>\
	\
</head>\
<body ontouchstart>\
    <div class=\"weui-toptips weui-toptips_warn js_tooltips\">错误提示</div>\
\
<div class=\"page form_page js_show\">\
  <div class=\"weui-form\">\
    <div class=\"weui-form__text-area\">\
      <h2 class=\"weui-form__title\">欢迎使用!</h2>\
      <div class=\"weui-form__desc\">开发板参数设置</div>\
    </div>\
    <div class=\"weui-form__control-area\">\
      <div class=\"weui-cells__group weui-cells__group_form\">\
        <div class=\"weui-cells__title\">网络配置</div>\
        <div class=\"weui-cells weui-cells_form\">\
		\
		<form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/form\"> \
		  <input name=\"method\" value=\"setup\" type=\"hidden\">\
          <div class=\"weui-cell weui-cell_active\">\
            <div class=\"weui-cell__hd\"><label class=\"weui-label\">SSID</label></div>\
            <div class=\"weui-cell__bd\">\
                <input id=\"ssid\" name=\"wifi-ssid\" class=\"weui-input\" pattern=\"[A-z]*\" maxlength=\"32\" placeholder=\"填写需要连接的热点名称\">\
            </div>\
          </div>\
		  \
          <div class=\"weui-cell weui-cell_active\">\
            <div class=\"weui-cell__hd\"><label class=\"weui-label\">密码</label></div>\
            <div class=\"weui-cell__bd\">\
                <input id=\"password\" name=\"wifi-password\" type=\"password\" class=\"weui-input\" pattern=\"[A-z]*\" maxlength=\"16\" placeholder=\"填写热点的密码\">\
            </div>\
          </div>\
		  \
		  <div class=\"weui-cells__title\">API相关</div>\
\
		  <div class=\"weui-cells\">\
            <a class=\"weui-cell  weui-cell_access\" href=\"http://tianqiapi.com/\" target=\"_blank\">\
                <div class=\"weui-cell__bd\">\
                    <p>点击申请天气API接口</p>\
                </div>\
                <div class=\"weui-cell__ft\">\
                </div>\
            </a>\
        </div>\
		\
\
		\
		<div class=\"weui-cell weui-cell_active\">\
            <div class=\"weui-cell__hd\"><label class=\"weui-label\">APPID</label></div>\
            <div class=\"weui-cell__bd\">\
                <input id=\"appid\" name=\"weather_appid\" class=\"weui-input\" pattern=\"[A-z]*\" maxlength=\"17\" placeholder=\"填写天气APPID\">\
            </div>\
          </div>\
		  \
		  <div class=\"weui-cell weui-cell_active\">\
            <div class=\"weui-cell__hd\"><label class=\"weui-label\">APPSECRET</label></div>\
            <div class=\"weui-cell__bd\">\
                <input id=\"appsecret\" name=\"weather_appsecret\" class=\"weui-input\" pattern=\"[A-z]*\" maxlength=\"17\" placeholder=\"填写天气APPSECRET\">\
            </div>\
          </div>\
		  \
		  <div class=\"weui-cells\">\
            <a class=\"weui-cell  weui-cell_access\" href=\"#\">\
                <div class=\"weui-cell__bd\">\
                    <p>如区域判断不正确请设置城市</p>\
                </div>\
                <div class=\"weui-cell__ft\">\
                </div>\
            </a>\
        </div>\
		  \
		  <div class=\"weui-cell weui-cell_active\">\
            <div class=\"weui-cell__hd\"><label class=\"weui-label\">城市名称</label></div>\
            <div class=\"weui-cell__bd\">\
                <input id=\"city\" name=\"weather_city\" class=\"weui-input\" pattern=\"[A-z]*\" maxlength=\"17\" placeholder=\"填写城市名称\">\
            </div>\
          </div>\
		  \
        </form>\
		\
        </div>\
      </div>\
    </div>\
	\
    <!--<div class=\"weui-form__tips-area\">\
      <p class=\"weui-form__tips\">\
        表单页提示，居中对齐\
      </p>\
    </div>-->\
	\
    <div class=\"weui-form__opr-area\">\
      <a class=\"weui-btn weui-btn_primary weui-btn_disabled\" href=\"javascript:\" id=\"showTooltips\">保存配置</a>\
	  <a href=\"javascript:;\" class=\"weui-btn weui-btn_warn\" onclick=\"reset();\">复位开发板</a>\
    </div>\
	\
    <!--<div class=\"weui-form__tips-area\">\
      <p class=\"weui-form__tips\">\
        表单页提示，居中对齐\
      </p>\
    </div>-->\
	\
    <div class=\"weui-form__extra-area\">\
      <div class=\"weui-footer\">\
        <p class=\"weui-footer__links\">\
          <a href=\"https://github.com/certer\" class=\"weui-footer__link\">github</a>\
        </p>\
        <p class=\"weui-footer__text\">Copyright © 2008-2019 CerTer</p>\
      </div>\
    </div>\
  </div>\
\
</div>\
 \
<!--\
<div class=\"container\" id=\"container\">\
<div class=\"page form_switch js_show\">\
  <div class=\"weui-form\">\
    <div class=\"weui-form__text-area\">\
      <h2 class=\"weui-form__title\">开关样式展示</h2>\
    </div>\
    <div class=\"weui-form__control-area\">\
      <div class=\"weui-cells__group weui-cells__group_form\">\
        <div class=\"weui-cells weui-cells_form\">\
            <div class=\"weui-cell weui-cell_active weui-cell_switch\">\
                <div class=\"weui-cell__bd\">标题文字</div>\
                <div class=\"weui-cell__ft\">\
                    <input class=\"weui-switch\" type=\"checkbox\">\
                </div>\
            </div>\
            <div class=\"weui-cell weui-cell_active weui-cell_switch\">\
                <div class=\"weui-cell__bd\">兼容IE Edge的版本</div>\
                <div class=\"weui-cell__ft\">\
                    <label for=\"switchCP\" class=\"weui-switch-cp\">\
                        <input id=\"switchCP\" class=\"weui-switch-cp__input\" type=\"checkbox\" checked=\"checked\">\
                        <div class=\"weui-switch-cp__box\"></div>\
                    </label>\
                </div>\
            </div>\
        </div>\
      </div>\
    </div>\
    <div class=\"weui-form__opr-area\">\
      <a class=\"weui-btn weui-btn_primary\" href=\"javascript:\" id=\"showTooltips\">确定</a>\
    </div>\
  </div>\
  <div id=\"js_toast\" style=\"display: none;\">\
      <div class=\"weui-mask_transparent\"></div>\
      <div class=\"weui-toast\">\
          <i class=\"weui-icon-success-no-circle weui-icon_toast\"></i>\
          <p class=\"weui-toast__content\">已完成</p>\
      </div>\
  </div>\
</div>\
</div>\
-->\
    <script src=\"http://libs.baidu.com/jquery/2.0.0/jquery.min.js\"></script>\
    <script src=\"https://res.wx.qq.com/open/libs/weuijs/1.2.1/weui.min.js\"></script>\
	<script type=\"text/javascript\">\
	\
	    function doAjax(url, data)\
		{\
			var jqxhr = $.ajax(\
	        {\
			    url: url,\
                data: data,\
                cache: false,\
                async: true,\
                type: \"POST\",\
                dataType: 'json'\
            });\
		\
		\
		    jqxhr.done(function(result)\
		    {\
		        code = result.code;\
			    msg = result.msg;\
				\
				if (code != 0)\
				{\
					weui.topTips('操作失败' + msg);\
					return;\
				}\
				\
				\
				weui.toast('操作成功', 3000);\
		    });\
			\
            jqxhr.fail(function()\
		    {\
			    weui.topTips('网络出错请重试！');\
		    });\
		}\
		\
		\
	\
		function saveConfig()\
		{\
		    var data= {};\
		    data.wifi_ssid = $(\"#ssid\").val();\
			data.wifi_password = $(\"#password\").val();\
			data.weather_appid = $(\"#appid\").val();\
            data.weather_appsecret = $(\"#appsecret\").val();\
			data.weather_city = $(\"#city\").val();\
			\
			if (data.wifi_ssid == \"\" || data.wifi_password == \"\" || data.weather_appid == \"\" || data.weather_appsecret == \"\")\
			{\
			    weui.topTips('请输入配置!');\
				return;\
			}\
			\
			data.method = \"save_config\";\
			doAjax(\"/form\", data);\
		}\
		\
		\
		\
		\
		function reset()\
		{\
		    weui.confirm('确定要复位开发板吗？所有设置将会丢失！', function(){ \
			    var data = {};\
			    data.method = \"reset\";\
			    doAjax(\"/form\", data);\
			  }\
			  , function(){ \
			  \
			  console.log('no'); \
			});\
		}\
		\
 $(function(){\
\
      $.ajax({\
            type : \"GET\",\
            contentType: \"application/json\",\
            url : \"/api?get_config\",\
            data : JSON.stringify(\"\"),\
            success : function(result) \
			{\
			  console.log(result);\
			    if (result.code == 0)\
				{\
				  var data = result.data;\
				   $(\"#ssid\").val(data.wifi_ssid);\
				   $(\"#password\").val(data.wifi_password);\
				   $(\"#appid\").val(data.weather_appid);\
				   $(\"#appsecret\").val(data.weather_appsecret);\
				   \
				   if (typeof(data.weather_city) != \"undefined\")\
				     $(\"#city\").val(data.weather_city);\
				   \
				}\
            },\
            error : function(e){\
                console.log(e.status);\
                console.log(e.responseText);\
            }\
        });\
\
	  \
      var $input = $('.weui-input');\
      $input.on('input', function(){\
        if ($input.val()){\
          $('#showTooltips').removeClass('weui-btn_disabled');\
        }else{\
          $('#showTooltips').addClass('weui-btn_disabled');\
        }\
      });\
	  \
      $('#showTooltips').on('click', function(){\
        if ($(this).hasClass('weui-btn_disabled')) return;\
\
        $('.page.cell').removeClass('slideIn');\
        saveConfig();\
		\
\
      });\
    });\
\
    </script>\
</body>\
</html>";


//============================================================================================================================================================================================================================
static const char initPage[] PROGMEM = "<!DOCTYPE html>\
<html>\
<head>\
  <style>\
html{font-size:62.5%;}\
body{text-align: center;}\
.left{width:80%; float:left} \
.right{width:30%; float:right;}\
.input{width: 90%;height:4rem; margin-top:5rem;}\
.select_left{width: 70%;height:4rem; float:left;margin-left:1.8rem;}\
.button_right{width:20%; height:4rem;float:right;margin-right:1.8rem;}\
.button{margin-top:40%;background-color:#07c160;position: relative;display: block;width: 100%;height:4rem; margin-left: auto;margin-right: auto;padding: 8px 24px;box-sizing: border-box;font-weight: 700;font-size: 17px;text-align: center;text-decoration: none;color: #fff;line-height: 1.41176471;border-radius: 4px;overflow: hidden;-webkit-tap-highlight-color: rgba(0,0,0,0);}\
.container{margin-top:50%;}\
  </style>\
  <script charset=\"UTF-8\">\
function scanWifi()\
{\
             document.getElementById(\"scanbtn\").disabled = true;\
            var http = new XMLHttpRequest();\
            http.open('GET', '/api?scan_wifi');\
            http.onreadystatechange = function()\
			{\
                if (http.status === 200 && http.readyState === 4)\
				{\
                    console.log(http.responseText);\
                    var res = http.responseText;\
                    var json = JSON.parse(res);\
				    \
					if (json.code == 0)\
					{\
					    var cbxwifi = document.getElementById(\"cbxwifi\");\
					    cbxwifi.options.length=0;\
						cbxwifi.options.add(new Option(\"请选择\", \"0\"));\
						\
						json.data.forEach(v=>\
					    {  \
						    cbxwifi.options.add(new Option(v.ssid, v.ssid));\
                        });\
					}\
                }\
\
				document.getElementById(\"scanbtn\").disabled = false;\
				\
            };\
\
            http.send();\
}\
\
function selectChange() \
{\
        var cbxwifi = document.getElementById(\"cbxwifi\");\
        var ssid = cbxwifi.options[cbxwifi.selectedIndex].value;\
		\
		if (ssid !== \"0\")\
		{\
		    document.getElementById(\"ssid\").value = ssid;\
		}\
\
}\
		\
function checkInput()\
{\
  var ssid = document.getElementById('ssid').value;\
  var password = document.getElementById('password').value;\
  \
  if (ssid == \"\" || password == \"\")\
   {\
      alert('请输入完整');\
      return;\
   }\
  \
   document.getElementById('form').submit();\
}\
\
  </script>\
  <meta charset=\"UTF-8\">\
  <meta name=\"viewport\" content=\"width=device-width,initial-scale=1,user-scalable=0,viewport-fit=cover\">\
  <title>ESP8266_IOT 初始化配置</title>\
  <style>\
  </style>\
</head>\
<body>\
\
\
  <div class=\"container\">\
    <h1>请输入需要连接的热点信息</h1>\
    <form id=\"form\" method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/form\">\
      <input type=\"hidden\" name=\"method\" value=\"init_config\"><br>\
	  <div class=\"div\">\
            <select class=\"select_left\" id=\"cbxwifi\" onchange=\"selectChange()\">\
                <option selected=\"selected\" value=\"0\">请扫描或者手动输入</option>\
            </select>\
    </div>\
	\
	<input type=\"button\" id=\"scanbtn\" class=\"button_right\" value=\"扫描\" onclick=\"scanWifi();\">\
\
      <input id=\"ssid\" type=\"text\" class=\"input\" name=\"wifi_ssid\" placeholder=\"请输入要连接的热点名称\"><br>\
      <input id=\"password\" type=\"password\" class=\"input\" name=\"wifi_password\" placeholder=\"请输入要连接的热点密码\"><br>\
      <input type=\"button\" class=\"button\" value=\"提交\" onclick=\"checkInput();\">\
    </form>\
  </div>\
\
\
</body>\
\
</html>";



