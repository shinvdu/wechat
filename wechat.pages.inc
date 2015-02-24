<?php

/**
 * @file
 * wechat callback pages.
 */
 
/**
 * auto reply message
 */
function wechat_callback() {
  $we_obj = _wechat_init_obj();
  $we_obj->valid();
  $type = $we_obj->getRev()->getRevType();
  $request_data = $we_obj->getRevData();
 
  //drupal_set_message('123');
  $request_message = wechat_build_request_message($request_data);
  $response_message = wechat_build_response_message($request_message);
  $response_message->send();
  /* remove the old code.
  //print debug($request_message);
  module_invoke_all('wechat_message', $we_obj);
  module_invoke_all('wechat_message_alter', $we_obj);
  if (!is_array($we_obj->Message(''))) { // add default option
    $type = $we_obj->getRev()->getRevType();
    switch ($type)  {
      case Wechat::MSGTYPE_EVENT:
        $event = $we_obj->getRevEvent();
        if (!$event) {
          break;
        }
        elseif ($event['event']=='subscribe') {
          $we_obj->text(variable_get("wechat_follow_message", variable_get("wechat_default_message", 'Hi, WeChat!')));
        }
        elseif ($event['event']=='CLICK') {
          $message = _wechat_menu_default_message($event);
          $message && $we_obj->text($message);
        }
        break;
    }
  }
  if (!is_array($we_obj->Message(''))) {
    $we_obj->text(variable_get("wechat_default_message", "Hi, WeChat!"));
  }
  $we_obj->reply();
  */
  exit;
}


function wechat_build_response_message($request_message) {
  //转换回来
  $request_message_wrapper = entity_metadata_wrapper('wechat_request_message', $request_message);
  $response_message = entity_create('wechat_response_message', array('msg_type' => 'text'));
  $response_message_wrapper = entity_metadata_wrapper('wechat_response_message', $response_message);
  $response_message_wrapper->to_user_name->set($request_message_wrapper->from_user_name->value());
  $response_message_wrapper->from_user_name->set($request_message_wrapper->to_user_name->value());
  $response_message_wrapper->create_time->set(REQUEST_TIME);
  $response_message_wrapper->rm_id->set($request_message->id);
  //我们这里设置一个save标记，其它模块同构后面的钩子可以修改这个值，它表示保存相应消息到数据库中。也可以不保存。
  $response_message->save = TRUE;
  
  module_invoke_all('wechat_build_response_message', $response_message, $request_message);
  //default reply.
  $wechat_content = $response_message_wrapper->wechat_content->value();
  if ($response_message->msg_type == 'text' && empty($wechat_content)) {
    if ($request_message->msg_type == 'event') {
      if ($request_message_wrapper->wechat_event->value() == 'subscribe') {
        $default_message_content = variable_get("wechat_follow_message", variable_get("wechat_default_message", 'Hi, WeChat!'));
        $response_message_wrapper->wechat_content->set($default_message_content); 
      }
      elseif ($request_message_wrapper->wechat_event->value() == 'CLICK') {
        $event = array();
        $event['key'] = $request_message_wrapper->wechat_event_key->value();
        $default_message_content = _wechat_menu_default_message($event);
        $response_message_wrapper->wechat_content->set($default_message_content);
      }
    }
    $wechat_content = $response_message_wrapper->wechat_content->value();	
    if (empty($wechat_content)) {
      $default_message_content = variable_get("wechat_default_message", "Hi, WeChat!");
      $response_message_wrapper->wechat_content->set($default_message_content);
    }
  }
  //The saved Flag default to TRUE. we could change it through hook_wechat_build_response_message.
  if (isset($response_message->save)) {
    $response_message_wrapper->save(true);
  }
  return $response_message;
}

/**
 * ****** unstable *****
 * login user
 */
function wechat_auth() {
  global $user;
  $we_obj = _wechat_init_obj();
  $state = isset($_GET['state']) ? $_GET['state'] : 0;
  $onerror = isset($_GET['onerror']) ? $_GET['onerror'] : '';
  $destination = isset($_GET['destination']) ? $_GET['destination'] : '';
  $code = isset($_GET['code']) ? $_GET['code'] : '';
  // user has logined
  if ($user->uid) {
    drupal_goto($destination);
  }
  
  // error
  if ((!$state) || (!$code)) { // error
    drupal_goto($onerror);
  }

  $access_data = $we_obj->getOauthAccessToken();
  if (empty($access_data)) {
    drupal_goto($onerror);
  }
  // check if already connectted
  if ($curuser = wechat_get_user_by_openid($access_data['openid'])) {
    _wechat_user_login($curuser->uid);
    // todo update user info
    drupal_goto($destination);
  }
  
  // auto register
  $user_name = 'wechat_' . substr($access_data['openid'], 0, 15);
  while (user_load_by_name($user_name)) {
    $user_name = $user_name . rand(0, 100);
  }
  $new_user = array(
    'name' => $user_name,
    'pass' => user_password(),
    'mail' => $user_name . '@' . $_SERVER['SERVER_NAME'],
    'init' => $user_name . '@' . $_SERVER['SERVER_NAME'],
    'status' => 1,
  );
  // $account returns user object
  $account = user_save(null, $new_user);
  if (!$account) {
    drupal_goto($onerror);
  }
  _wechat_user_login($account->uid);
  $wechat_user = array(
    'uid' => $user->uid,
    'openid' => $access_data['openid'],
    'extend' => array(),
  );
  // also save user wechat information.
  if ($state == 2) {
    $user_info = $we_obj->getOauthUserinfo($access_data['access_token'], $access_data['openid']);
    if (!empty($user_info)) {
      module_invoke_all('wechat_userinfo', $user_info);
      $wechat_user['nickname'] = $user_info['nickname'];
      $wechat_user['sex'] = $user_info['sex'];
      $wechat_user['province'] = $user_info['province'];
      $wechat_user['city'] = $user_info['city'];
      $wechat_user['country'] = $user_info['country'];
      $wechat_user['headimgurl'] = $user_info['headimgurl'];
    }
  }
  if (!drupal_write_record('wechat_user', $wechat_user)) {
    drupal_goto($onerror);
  }

  drupal_goto($destination);
}

/**
 * find the default message
 */
function _wechat_menu_default_message($event) {
  // get all click menu key
  $key = isset($event['key']) ? $event['key'] : '';
  if (!$key) {
    return '';
  }
  $menu_tree = menu_build_tree('wechat', array('max_depth' => 2));
  foreach ($menu_tree as $val) {
    if ($val['link']['hidden']) {
      continue;
    }
    if (!empty($val['below'])) {
      foreach ($val['below'] as $subval) {
        if ($subval['link']['hidden']) {
          continue;
        }
        if ($subval['link']['options']['attributes']['wechat_key'] == $key) {
          return $subval['link']['options']['attributes']['wechat_default_message'];
        }
      }
    }
    elseif ($val['link']['options']['attributes']['wechat_key'] == $key) {
      return $val['link']['options']['attributes']['wechat_default_message'];
    }
  }
  return '';
}
