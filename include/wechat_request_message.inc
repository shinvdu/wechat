<?php 

/**
 * The class used for wechat request message entities
 */
class WechatRequestMessage extends Entity {
  /**
   * The message id.
   *
   * @var integer
   */
  public $id;
  
  /**
   * The message id.
   *
   * @var string
   */
  public $msg_id;
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
    parent::__construct($values, 'wechat_request_message');
  }

  protected function defaultLabel() {
    return $this->msg_id;
  }

  protected function defaultUri() {
    return array('path' => 'message/' . $this->id);
  }
  
  public function save() {
    parent::save();
  }
}

/**
 * Use a separate class for wechat_request_message types so we can specify some defaults
 * modules may alter.
 */
class WechatRequestMessageType extends Entity {


  public $type;
  public $label;
  public $weight = 0;

  public function __construct($values = array()) {
    parent::__construct($values, 'wechat_request_message_type');
  }

  /**
   * Returns whether the wechat_request_message type is locked, thus may not be deleted or renamed.
   *
   * Wechat_request_message types provided in code are automatically treated as locked, as well
   * as any fixed wechat_request_message type.
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
