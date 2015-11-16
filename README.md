前言： 
模块是在 https://www.drupal.org/project/wechat 这个模块的基础上进行的修改。 

桌面扫码登陆的功能我加上去了，不过， 因为改动太大，没法自动升级。所以，要用的话，得是全新的安装。 

原来的wechat_user的主键是openid, 因为微信开放平台那又有appid 和appsecret, 他们openid是不同，所以只能用unionid作为唯一主键 , entity 里面的属性需要改。 就因为这个，我没法写自动升级。

还有， 如果不是同时有服务公众号和开放平台的帐号也没法用。 因为， 服务公众号和开放平台的帐号绑定在一块时，才会有unionid出现。

基本使用： 

1. 申请公众号以取得公众号的appid / appsecret key / token， 及绑定回调的安全域名（在权限列表那里设置）

2. 注册开放平台， 申请网站登陆，绑定公从号（这样才会有unionid） 

3. 把这样配置信息放到drupal的后台，就可以使用了。 

基本功能：
1. 使用微信进行注册登陆， 绑定己有的网站用户， 绑定后可直接使用微信登陆（同时支持微信内置的浏览器和电脑端的浏览器）

2. 在网站的后台扫描二维码绑定微信号

3. 接收并存储用户发过来的消息， 回复用户的消息。 

4. 更新菜单 