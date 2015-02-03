<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class WechatRequestMessageMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info['wechat_request_message']['properties'];

    $properties['to_user_name'] = array(
      'type' => 'text',
      'label' => t('To user name'),
      'description' => t('To user name of wechat request message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat request message',
      'schema field' => 'to_user_name',
	  'required' => TRUE,
    );
	
    $properties['from_user_name'] = array(
      'type' => 'text',
      'label' => t('From user name'),
      'description' => t('From user name of wechat request message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat request message',
      'schema field' => 'from_user_name',
	  'required' => TRUE,
    );
	
    $properties['msg_type'] = array(
      'label' => t('Message type'),
      'description' => t('Message type of wechat request message.'),
      'type' => 'token',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat request message',
      'options list' => 'wechat_request_message_type_options_list',
      'required' => TRUE,
      'schema field' => 'msg_type',	  
    );
	
    $properties['create_time'] = array(
      'type' => 'integer',
      'label' => t('Create time'),
      'description' => t('Create time of wechat request message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat request message',
      'schema field' => 'create_time',
	  'required' => TRUE,
    );	
	
    $properties['msg_id'] = array(
      'label' => t('Message ID'),
      'description' => t('Unique ID of wechat request message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat request message',	  
      'type' => 'text',
      'schema field' => 'msg_id',
    );	
		
    return $info;
  }
}

class WechatResponseMessageMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info['wechat_response_message']['properties'];

    $properties['to_user_name'] = array(
      'type' => 'text',
      'label' => t('To user name'),
      'description' => t('To user name of wechat response message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat response message',
      'schema field' => 'to_user_name',
	  'required' => TRUE,
    );
	
    $properties['from_user_name'] = array(
      'type' => 'text',
      'label' => t('From user name'),
      'description' => t('From user name of wechat response message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat response message',
      'schema field' => 'from_user_name',
	  'required' => TRUE,
    );
	
    $properties['msg_type'] = array(
      'label' => t('Message type'),
      'description' => t('Message type of wechat response message.'),
      'type' => 'token',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat response message',
      'options list' => 'wechat_request_message_type_options_list',
      'required' => TRUE,
      'schema field' => 'msg_type',	  
    );
	
    $properties['create_time'] = array(
      'type' => 'integer',
      'label' => t('Create time'),
      'description' => t('Create time of wechat response message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat response message',
      'schema field' => 'create_time',
	  'required' => TRUE,
    );
	
    $properties['func_flag'] = array(
      'type' => 'integer',
      'label' => t('Function flag'),
      'description' => t('Function flag of wechat response message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer wechat response message',
      'schema field' => 'func_flag',
	  'required' => TRUE,
    );	
		
    return $info;
  }
}
