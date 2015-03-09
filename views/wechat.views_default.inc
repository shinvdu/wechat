<?php
/**
 * @file
 * Provide default_views for wechat.
 */

/**
 * Implements hook_views_default_views().
 */
function wechat_views_default_views() {
$view = new view();
$view->name = 'request_messages';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'wechat_request_message';
$view->human_name = 'request messages';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'request messages';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'create_time' => 'create_time',
  'wechat_event' => 'wechat_event',
  'wechat_event_key' => 'wechat_event_key',
  'from_user_name' => 'from_user_name',
  'wechat_latitude' => 'wechat_latitude',
  'wechat_location_x' => 'wechat_location_x',
  'wechat_location_y' => 'wechat_location_y',
  'wechat_longitude' => 'wechat_longitude',
  'msg_id' => 'msg_id',
  'msg_type' => 'msg_type',
  'wechat_scale' => 'wechat_scale',
  'wechat_ticket' => 'wechat_ticket',
  'to_user_name' => 'to_user_name',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'create_time' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_event' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_event_key' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'from_user_name' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_latitude' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_location_x' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_location_y' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_longitude' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'msg_id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'msg_type' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_scale' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wechat_ticket' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'to_user_name' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Field: Wechat request message: Wechat request message ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'wechat_request_message';
$handler->display->display_options['fields']['id']['field'] = 'id';
/* Field: Wechat request message: Create time */
$handler->display->display_options['fields']['create_time']['id'] = 'create_time';
$handler->display->display_options['fields']['create_time']['table'] = 'wechat_request_message';
$handler->display->display_options['fields']['create_time']['field'] = 'create_time';
/* Field: Wechat request message: From user name */
$handler->display->display_options['fields']['from_user_name']['id'] = 'from_user_name';
$handler->display->display_options['fields']['from_user_name']['table'] = 'wechat_request_message';
$handler->display->display_options['fields']['from_user_name']['field'] = 'from_user_name';
/* Field: Wechat request message: Message ID */
$handler->display->display_options['fields']['msg_id']['id'] = 'msg_id';
$handler->display->display_options['fields']['msg_id']['table'] = 'wechat_request_message';
$handler->display->display_options['fields']['msg_id']['field'] = 'msg_id';
/* Field: Wechat request message: Message type */
$handler->display->display_options['fields']['msg_type']['id'] = 'msg_type';
$handler->display->display_options['fields']['msg_type']['table'] = 'wechat_request_message';
$handler->display->display_options['fields']['msg_type']['field'] = 'msg_type';
/* Field: Wechat request message: Rendered wechat request message */
$handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
$handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_wechat_request_message';
$handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
$handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
$handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
$handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'full';
$handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '文本回复';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '文本';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'response-message/add/text?rm_id=[id]';
$handler->display->display_options['fields']['nothing']['alter']['target'] = '_blank';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['label'] = '图片回复';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '图片';
$handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'response-message/add/image?rm_id=[id]';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/wechat/messages/request';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Request messages';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;  
  return $views;
}