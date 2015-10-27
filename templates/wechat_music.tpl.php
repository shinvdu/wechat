<xml>
    <ToUserName><![CDATA[<?php print $to_user_name; ?>]]></ToUserName>
  <FromUserName><![CDATA[<?php print $from_user_name; ?>]]></FromUserName>
  <CreateTime><?php print $request_time; ?></CreateTime>
  <MsgType><![CDATA[music]]></MsgType>
  <Music>
    <Title><![CDATA[<?php print $title; ?>]]></Title>
    <Description><![CDATA[<?php print $description; ?>]]></Description>
    <MusicUrl><![CDATA[<?php print $music_url; ?>]]></MusicUrl>
    <HQMusicUrl><![CDATA[<?php print $hq_music_url; ?>]]></HQMusicUrl>
    <ThumbMediaId><![CDATA[<?php print $thumb_media_id; ?>]]></ThumbMediaId>
</Music>
</xml>