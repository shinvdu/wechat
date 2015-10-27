<?php 

/**
 * The class used for wechat_response_message entities
 */
class WechatResponseMessage extends Entity {
  /**
   * The message id.
   *
   * @var integer
   */
  public $id;
  
  /**
   * The save flag.
   *
   * @var integer
   */
  public $save;
  
  /**
   * The wechat request message id.
   *
   * @var integer
   */
  public $rm_id;
  
  /**
   * The func flag.
   *
   * @var integer
   */
  public $func_flag;

  /**
   * The to user name of wechat request message.
   *
   * @var string
   */
  public $to_user_name;
  
  /**
   * The from user name of wechat request message.
   *
   * @var string
   */
  public $from_user_name;
  
  /**
   * The message type of wechat request message.
   *
   * @var string
   */
  public $msg_type;
  
  /**
   * The creat time of wechat request message.
   *
   * @var integer
   */
  public $create_time;
  
  public function __construct($values = array()) {
    parent::__construct($values, 'wechat_response_message');
  }

  protected function defaultLabel() {
    return $this->id;
  }

  protected function defaultUri() {
    return array('path' => 'response-message/' . $this->id);
  }
  
  public function save() {
    parent::save();
  }
  
  public function send() {
    $result_str = wechat_response_message_obj_to_xml($this);
    echo $result_str;
  }

  public function sendCustomMessage() {
    $array_data = wechat_response_message_obj_to_array($this);
  
    $appid = variable_get('wechat_appid', "");
    $appsecret =variable_get('wechat_appsecret', "");
    $access_token = wechat_get_access_token($appid, $appsecret);
    $we_obj = _wechat_init_obj();
    $we_obj->checkAuth($appid, $appsecret, $access_token);
    $result = $we_obj->sendCustomMessage($array_data);
 
    if (!empty($result)) {
      //Todo: Error.
      return $result;
    }
    else{
      return FALSE;
    }
  }
}


/**
 * Use a separate class for wechat_response_message types so we can specify some defaults
 * modules may alter.
 */
class WechatResponseMessageType extends Entity {


  public $type;
  public $label;
  public $weight = 0;

  public function __construct($values = array()) {
    parent::__construct($values, 'wechat_response_message_type');
  }

  /**
   * Returns whether the wechat_response_message type is locked, thus may not be deleted or renamed.
   *
   * Wechat response message types provided in code are automatically treated as locked, as well
   * as any fixed wechat_response_message type.
   */
  public function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }


  /**
   * Overrides Entity::save().
   */
  public function save() {
    parent::save();
    // Clear field info caches such that any changes to extra fields get
    // reflected.
    field_info_cache_clear();
  }
}
