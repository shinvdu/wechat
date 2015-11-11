<?php

/**
 * The class used for wechat_response_message entities
 */
class WechatUser extends Entity {
  /**
   * The uid of Drupal user.
   *
   * @var integer
   */
  public $uid;
  
    /**
   * The unionid of wechat user.
   *
   * @var string
   */
    public $unionid;

    /**
   * The open_openid of wechat user.
   *
   * @var string
   */
    public $open_openid;

  /**
   * The openid of wechat user.
   *
   * @var string
   */
  public $wp_openid;
  
  /**
   * The subscribe status of wechat user.
   *
   * @var integer
   */
  public $subscribe;
  

  /**
   * The nickname of wechat user.
   *
   * @var string
   */
  public $nickname;
  
  /**
   * The sex of wechat user.
   *
   * @var integer
   */
  public $sex;  
  
  /**
   * The province of wechat user.
   *
   * @var string
   */
  public $province;
  
  /**
   * The city of wechat user.
   *
   * @var string
   */
  public $city;
  
  /**
   * The country of wechat user.
   *
   * @var string
   */
  public $country;
  
  /**
   * The headimgurl of wechat user.
   *
   * @var string
   */
  public $headimgurl; 
  
  /**
   * The subscribe time of wechat user.
   *
   * @var integer
   */
  public $subscribe_time;
  
  public function __construct($values = array()) {
    parent::__construct($values, 'wechat_user');
  }

  protected function defaultLabel() {
    return $this->unionid;
  }

  protected function defaultUri() {
    return array('path' => 'wechat-user/' . $this->unionid);
  }
  
  public function save() {
    parent::save();
  }
}

