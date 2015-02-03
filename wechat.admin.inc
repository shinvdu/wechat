<?php

/**
 * @file
 * wechat admin pages.
 */
 
function wechat_config_form($form, $form_state) {
  $form['wechat_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Token'),
    '#description' => t('The token that you use in wechat public platform.'),
    '#default_value' => variable_get('wechat_token', ''),
    '#required' => TRUE,
  );
  $form['wechat_appid'] = array(
    '#type' => 'textfield',
    '#title' => t('AppID'),
    '#description' => t('Account APPID'),
    '#default_value' => variable_get('wechat_appid', ""),
    '#required' => true,
  );
  $form['wechat_appsecret'] = array(
    '#type' => 'textfield',
    '#title' => t('AppSecret'),
    '#description' => t('Account AppSecret'),
    '#default_value' => variable_get('wechat_appsecret', ""),
    '#required' => true,
  );
  return system_settings_form($form);
}
function wechat_default_message_config_form($form, $form_state) {
  $form['wechat_default_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Auto reply message'),
    '#description' => t('The WeChat module will send this message to user if no other Modules '),
    '#default_value' => variable_get('wechat_default_message', "hello, I'm wechat"),
    '#required' => true,
  );
  $form['wechat_follow_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Auto reply message after follow.'),
    '#description' => '',
    '#default_value' => variable_get('wechat_follow_message', "hello, I'm wechat"),
    '#required' => false,
  );
  return system_settings_form($form);
}

function wechat_update_menu_form($form, $form_state) {
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Menu'),
    '#submit' => array('wechat_admin_update_menu_submit'),
  );
  return $form;
} 

/**
 * update wechat menu
 */
function wechat_admin_update_menu_submit($form, &$form_state){
  $menu_arr = _wechat_menu_arr();
  if(empty($menu_arr['button'])){
    drupal_set_message('Empty WeChat Menu', 'error');
  }
  else{
	  $weObj = _wechat_init_obj();
    if($weObj->createMenu($menu_arr))
  	{
      drupal_set_message('Update menu success.');
  	}
  	else{
  	  drupal_set_message($weObj->errMsg.'-'.$weObj->errCode, 'error');
  	}
  }
  return;
}

/**
 * drupal menu to wechat menu array
 */
function _wechat_menu_arr(){
  $menu_tree = menu_build_tree('wechat', array('max_depth'=>2));
  $menu_arr = array();
  $menu_arr['button'] = array();
  foreach($menu_tree as $val){
    if($val['link']['hidden']){
      continue;
    }
    $element = array();
    $element['name'] = $val['link']['link_title'];
    $element['sub_button'] = array();
    if(!empty($val['below'])){
      foreach($val['below'] as $subval){
        if($subval['link']['hidden']){
          continue;
        }
        $element['sub_button'][] = _wechat_menu_item($subval);
      }
    }
    if(empty($element['sub_button'])){
      unset($element['sub_button']);
      $element = _wechat_menu_item($val);
    }
    $menu_arr['button'][] = $element;
  }
  return $menu_arr;
}

/**
 * Drupal menu to wechat menu
 */
function _wechat_menu_item($subval){
  $subelement = array();
  $subelement['name'] = $subval['link']['link_title'];
  if(isset($subval['link']['options']['attributes']['wechat_type'])
      && $subval['link']['options']['attributes']['wechat_type'] == 'click'){
	  $subelement['type'] = 'click';
	  $subelement['key'] = $subval['link']['options']['attributes']['wechat_key'];
  }
  else{
    $subelement['type'] = 'view';
	  $subelement['url'] = $subval['link']['options']['attributes']['wechat_url'];
  }
  return $subelement;
}

/**
 * UI controller.
 */
 
class WechatRequestMessageTypeUIController extends EntityDefaultUIController {

}

/**
 * UI controller.
 */
 
class WechatResponseMessageTypeUIController extends EntityDefaultUIController {

}

/**
 * Generates the profile type editing form.
 */
function wechat_request_message_type_form($form, &$form_state, $message_type, $op = 'edit') {

  if ($op == 'clone') {
    $message_type->label .= ' (cloned)';
    $message_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $message_type->label,
    '#description' => t('The human-readable name of this message type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($message_type->type) ? $message_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $message_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'wechat_request_message_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this message type. It must only contain lowercase letters, numbers, and underscores.'),
  );


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save message type'),
    '#weight' => 40,
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => $message_type->weight,
    '#description' => t('When showing message types, those with lighter (smaller) weights get listed before message types with heavier (larger) weights.'),
    '#weight' => 10,
  );

  if (!$message_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete message type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('wechat_request_message_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function wechat_request_message_type_form_submit(&$form, &$form_state) {
  $wechat_request_message_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $wechat_request_message_type->save();
  $form_state['redirect'] = 'admin/structure/wechat-request-messages';
}

/**
 * Form API submit callback for the delete button.
 */
function wechat_request_message_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/wechat-request-messages/manage/' . $form_state['message_type']->type . '/delete';
}

/**
 * Generates the profile type editing form.
 */
function wechat_response_message_type_form($form, &$form_state, $message_type, $op = 'edit') {
  //print debug($message_type);
  if ($op == 'clone') {
    $message_type->label .= ' (cloned)';
    $message_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $message_type->label,
    '#description' => t('The human-readable name of this message type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($message_type->type) ? $message_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $message_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'wechat_response_message_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this message type. It must only contain lowercase letters, numbers, and underscores.'),
  );


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save message type'),
    '#weight' => 40,
	'#submit' => array('wechat_response_message_type_form_submit')
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => $message_type->weight,
    '#description' => t('When showing message types, those with lighter (smaller) weights get listed before message types with heavier (larger) weights.'),
    '#weight' => 10,
  );

  if (!$message_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete message type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('wechat_response_message_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function wechat_response_message_type_form_submit(&$form, &$form_state) {
  $wechat_response_message_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  //print debug($wechat_response_message_type);
  $wechat_response_message_type->save();
  $form_state['redirect'] = 'admin/structure/wechat-response-messages';
}

/**
 * Form API submit callback for the delete button.
 */
function wechat_response_message_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/wechat-response-messages/manage/' . $form_state['message_type']->type . '/delete';
}
