1,本模块，采用dodge开发的PHP版本微信SDK，里面包含微信的几乎所有功能，Drupal端只需要简单调用即可。项目地址：
https://github.com/dodgepudding/wechat-php-sdk
这个项目在git官网，评价很高。

2，本模块，里面的自定义菜单，Wechat对象的初始化，用户的认证，等等相关代码，还有使用dodge开发的PHP版本微信SDK，直接复制自yplam编写的模块，模块地址：
https://github.com/yplam/wechat
http://drupalchina.cn/node/3060
https://www.drupal.org/sandbox/yplam/2229507

3，本模块的其余部分，主要是wechat_request_message, wechat_response_message两种实体类型的定义，由老葛编写。

我对于这个模块的所有设想，源自一年前，就是将微信的request_message，还有response_message封装成Drupal里面的实体，基于entity API。
这个模块的编写，也早在一年前，就已经动工，中间断断续续，大约在半年前，跑通了基本的请求、相应流程，完成了request_message，response_message
实体化封装，就是现在这个模块的骨架，出于各种原因，一直没有发布我写的微信模块；2015-2-3日，在drupachina上面，发现了yplam微信模块，将自己写的微信模块与之合并，引用并更新了dodge的微信SDK，上传到了官方网站上。

Drupal微信（公众平台）接口，提供以下基本功能：
•自定义菜单管理
•微信消息（事件）钩子
•自动回复简单消息与菜单点击事件
•微信用户登录与管理
•微信的请求和响应，采用Entity API的形式。
•支持客服接口。
•语音识别
•Oauth网页授权
•生成带参数二维码
•获取用户地理位置
•获取用户基本信息
•用户分组接口
•上传下载多媒体文件
•高级群发接口

这个模块的其中一个好处，就是微信请求过来以后，直接保存为Drupal的request_message实体，这个是基于entity API的，可以与各种模块相整合。消息的不同种类，对应于Drupal中的不同的bundle。

消息的回应，将来将会由response_message完成，我们只需要构建这样的一个实体即可，前期由dodge微信SDK里面的wechat对象完成。

基本思路就是模仿symfony里面的HTTP request, HTTP response的架构，后续版本，消息的回应，将会采用这种形式：

$response_message->send();

客服回应：
$response_message->sendCustomMessage();

我们只需要在Drupal端，封装$response_message对象，封装完成后，调用它的消息相应即可。

将wechat-php-sdk里面封装的功能，逐步的封装成Drupal模块可以直接使用的形式，需要在项目中，陆续的完成。

相关模块

1， wechat views,提供自定义菜单与Views的绑定功能。
2，

作者

1，yplam 是这个模块的最初作者，并最早贡献到drupal.org上面来，早在2014年3月31号，就将模块贡献到了drupa.org上，因为是sandbox的形式，没有引起更多人的注意。我也是先在drupalchina上找到，GIT上面下载下来，通过搜索yplam，才在drupal.org发现，很早就传上来了。
2，老葛，将自己写的微信模块，与yplam的合并，增加了实体化的支持。

https://www.drupal.org/project/wechat