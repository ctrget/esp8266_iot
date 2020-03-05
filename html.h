static const String indexPage = "<!DOCTYPE html>\
<html lang=\"zh-cmn-Hans\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width,initial-scale=1,user-scalable=0,viewport-fit=cover\">\
    <title>WeUI</title>\
    <link rel=\"stylesheet\" href=\"https://cdn.bootcss.com/weui/2.2.0/style/weui.min.css\"/>\
  \
</head>\
<body ontouchstart>\
    <div class=\"weui-toptips weui-toptips_warn js_tooltips\">错误提示</div>\
\
<div class=\"page form_page js_show\">\
  <div class=\"weui-form\">\
    <div class=\"weui-form__text-area\">\
      <h2 class=\"weui-form__title\">Hello World!</h2>\
      <div class=\"weui-form__desc\">首次使用请配置开发板</div>\
    </div>\
    <div class=\"weui-form__control-area\">\
      <div class=\"weui-cells__group weui-cells__group_form\">\
        <div class=\"weui-cells__title\">网络配置</div>\
        <div class=\"weui-cells weui-cells_form\">\
    \
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/form/\"> \
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
    function initConfig()\
    {\
    \
        var ssid = $(\"#ssid\").val();\
      var pass = $(\"#password\").val();\
\
      \
      if (ssid == \"\" || pass == \"\")\
      {\
          weui.topTips('请输入配置!');\
        return;\
      }\
      \
      var data= {};\
      data.wifi_ssid = ssid;\
      data.wifi_password = pass;\
      data.method = \"init_config\";\
      doAjax(/form/, data);\
\
    }\
    \
    function reset()\
    {\
        weui.confirm('确定要复位开发板吗？所有设置将会丢失！', function(){ \
          var data = {};\
          data.method = \"reset\";\
          doAjax(/form/, data);\
        }\
        , function(){ \
        \
        console.log('no'); \
      });\
    }\
    \
 $(function(){\
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
        initConfig();\
    \
\
      });\
    });\
\
    </script>\
</body>\
</html>";


//============================================================================================================================================================================================================================
static const String initPage = "<html>\
  <head>\
    <meta charset=\"UTF-8\">\
    <title>ESP8266_IOT 初始化配置</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>请输入需要连接的热点信息</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/form/\">\
      <input type=\"hidden\" name=\"method\" value=\"init_config\"><br>\
      <input type=\"text\" name=\"wifi_ssid\" value=\"\"><br>\
      <input type=\"text\" name=\"wifi_password\" value=\"\"><br>\
      <input type=\"submit\" value=\"提交\">\
    </form>\
  </body>\
</html>";
