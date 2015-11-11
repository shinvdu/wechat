前言： 
模块是在 https://www.drupal.org/project/wechat 这个模块的基础上进行的修改。 

桌面扫码登陆的功能我加上去了，不过， 因为改动太大，没法自动升级。所以，要用的话，得是全新的安装。 

原来的wechat_user的主键是openid, 因为微信开放平台那又有appid 和appsecret, 他们openid是不同，所以只能用unionid作为唯一主键 , entity 里面的属性需要改。 就因为这个，我没法写自动升级。

还有， 如果不是同时有服务公众号和开放平台的帐号也没法用。 因为， 服务公众号和开放平台的帐号绑定在一块时，才会有unionid出现。
