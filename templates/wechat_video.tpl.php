<xml>
  <ToUserName><![CDATA[<?php print $to_user_name; ?>]]></ToUserName>
  <FromUserName><![CDATA[<?php print $from_user_name; ?>]]></FromUserName>
  <CreateTime><?php print $request_time; ?></CreateTime>
  <MsgType><![CDATA[video]]></MsgType>
  <Video>
    <MediaId><![CDATA[<?php print $media_id ?>]]></MediaId>
    <ThumbMediaId><![CDATA[<?php print $thumb_media_id ?>]]></ThumbMediaId>
  </Video> 
</xml>