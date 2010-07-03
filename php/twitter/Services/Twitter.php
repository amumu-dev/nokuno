<?php
/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**
 * Twitter Client Class
 *
 * PHP versions 4 and 5
 *
 * LICENSE: This source file is subject to version 3.0 of the PHP license
 * that is available through the world-wide-web at the following URI:
 * http://www.php.net/license/3_0.txt.  If you did not receive a copy of
 * the PHP License and are unable to obtain it through the web, please
 * send a note to license@php.net so we can mail you a copy immediately.
 *
 * @category  Services
 * @package   Services_Twitter
 * @author    Takeshi KAWAMOTO <takeshi@transrain.net>
 * @copyright 2007 Takeshi KAWAMOTO <takeshi@transrain.net>
 * @license   http://www.php.net/license/3_01.txt PHP License 3.01
 * @version   CVS: $Id:$
 * @link      http://www.transrain.net/product/services_twitter/
 */
require_once 'Services/Twitter/Connector.php';

/**
 * Twitter Client Class
 *
 * @category  Services
 * @package   Services_Twitter
 * @author    Takeshi KAWAMOTO <takeshi@transrain.net>
 * @copyright 2007 Takeshi KAWAMOTO <takeshi@transrain.net>
 * @license   http://www.php.net/license/3_01.txt PHP License 3.01
 * @version   Release: @package_version@
 * @link      http://www.transrain.net/product/services_twitter/
 */
class Services_Twitter
{
    /**
     * Status Methods
     */
    var $sm_public          = 'http://twitter.com/statuses/public_timeline.json';
    var $sm_friends         = 'http://twitter.com/statuses/friends_timeline.json';
    var $sm_friends_target  = 'http://twitter.com/statuses/friends_timeline/%s.json';
    var $sm_user            = 'http://twitter.com/statuses/user_timeline.json';
    var $sm_user_target     = 'http://twitter.com/statuses/user_timeline/%s.json';
    var $sm_show            = 'http://twitter.com/statuses/show/%d.json';
    var $sm_update          = 'http://twitter.com/statuses/update.json';
    var $sm_replies         = 'http://twitter.com/statuses/replies.json';
    var $sm_destroy         = 'http://twitter.com/statuses/destroy/%s.json';
    
    /**
     * User Methods
     */
    var $um_friends         = 'http://twitter.com/statuses/friends.json';
    var $um_friends_target  = 'http://twitter.com/statuses/friends/%s.json';
    var $um_featured        = 'http://twitter.com/statuses/featured.json';
    var $um_followers       = 'http://twitter.com/statuses/followers.json';
    var $um_show            = 'http://twitter.com/users/show/%s.json';
    
    /**
     * Direct Message Methods
     */
    var $dm_show            = 'http://twitter.com/direct_messages.json';
    var $dm_new             = 'http://twitter.com/direct_messages/new.json';

    /**
     * Friendship Methods
     */
    var $fm_create          = 'http://twitter.com/friendships/create/%s.json';
    var $fm_destroy         = 'http://twitter.com/friendships/destroy/%s.json';
    
    /**
     * Account Methods
     */
    var $am_verify          = 'http://twitter.com/account/verify_credentials';
    var $am_endsess         = 'http://twitter.com/end_session';
    

    var $_user;
    var $_pass;


    var $_app_name;
    var $_app_ver;
    var $_app_url;
    
    var $_etag;
    var $_last_modified;
    
    var $_json_convert;
    var $_modified_check;
    
    var $_cache_dir;
    
    /**
     * class constructor
     *
     * @access public
     *
     * @param string $user     username of twitter
     * @param string $password password of twitter
     *
     */
    function Services_Twitter($user, $password)
    {
        $this->_user = $user;
        $this->_pass = $password;
    }
    
    /**
     * set application's name
     *
     * @access public
     *
     * @param string $name application's name
     *
     * @return string setup value
     */
    function setAppName($name)
    {
        $this->_app_name = $name;
        return $this->_app_name;
    }
    
    /**
     * set application's version
     *
     * @access public
     *
     * @param string $ver application's version
     *
     * @return string setup value
     */
    function setAppVersion($ver)
    {
        $this->_app_ver = $ver;
        return $this->_app_ver;
    }
    
    /**
     * set url of application's information xml
     *
     * @access public
     *
     * @param string $url url of application's information xml
     *
     * @return string setup value
     */
    function setAppURL($url)
    {
        $this->_app_url = $url;
        return $this->_app_url;
    }

    /**
     * set append etag(If-None-Match) to next request
     *
     * @access public
     *
     * @param string $etag send etag to next request
     *
     * @return string setup value
     */
    function setEtag($etag)
    {
        $this->_etag = $etag;
        return $this->_etag;
    }
    
    /**
     * get etag(If-None-Match) from previous request
     *
     * @access public
     *
     * @return string etag from previous request
     */
    function getEtag()
    {
        return $this->_etag;
    }
    
    /**
     * set append last_modified(last_modified) to next request
     *
     * @access public
     *
     * @param string $last_modified send last_modified to next request
     *
     * @return string setup value
     */
    function setLastModified($last_modified)
    {
        $this->_last_modified = $last_modified;
        return $this->_last_modified;
    }
    
    /**
     * get last_modified(last_modified)from previous request
     *
     * @access public
     *
     * @return string last_modified from previous request
     */
    function getLastModified()
    {
        return $this->_last_modified;
    }
    
    /**
     * set modified check file cache direcotry path
     *
     * @access public
     *
     * @param string $dir cache direcotry path
     *
     * @return string last_modified from previous request
     */
    function setCacheDir($dir)
    {
        $this->_cache_dir = $dir;
        return $this->_cache_dir;
    }
    
    /**
     * json convert function enable
     *
     * @access public
     *
     * @return string last_modified from previous request
     */
    function enableJsonConvert()
    {
        $this->_json_convert = true;
        return $this->_json_convert;
    }
    
    /**
     * json convert function disable
     *
     * @access public
     *
     * @return string last_modified from previous request
     */
    function disableJsonConvert()
    {
        $this->_json_convert = false;
        return $this->_json_convert;
    }
    
    /**
     * Modified check enable
     *
     * @access public
     *
     * @return string last_modified from previous request
     */
    function enableModifiedCheck()
    {
        $this->_modified_check = true;
        return $this->_modified_check;
    }
    
    /**
     * Modified check disable
     *
     * @access public
     *
     * @return string last_modified from previous request
     */
    function disableModifiedCheck()
    {
        $this->_modified_check = false;
        return $this->_modified_check;
    }
    
    /**
     * send update request
     *
     * @access private
     *
     * @param string $url     call update API's URL
     * @param mixed  $values  send values (if array, key is POST name and value is POST value) 
     * @param array  $headers send headers (key is header name and value is header value)
     *
     * @return mixed processed success, return response body. and processed faild, return false.
     */
    function _setData($url, $values, $headers = null)
    {
        $req =& new Services_Twitter_Connector();
        
        if (!$this->checkAuth()) {
            $req->enableBasicAuth($this->_user, $this->_pass);
        }
        
        $req->addHeader('User-Agent', 'PHP/' . phpversion());
        
        if ($this->_app_name !== null) {
            $req->addHeader('X-Twitter-Client', $this->_app_name);
        }
        
        if ($this->_app_ver !== null) {
            $req->addHeader('X-Twitter-Client-Version', $this->_app_ver);
        }
        
        if ($this->_app_url !== null) {
            $req->addHeader('X-Twitter-Client-URL', $this->_app_url);
        }
        
        // header setting
        if ($headers !== null && is_array($headers)) {
            foreach ($headers as $key => $value) {
                $req->addHeader($key, $value);
            }
        }
        
        if (is_array($values)) {
            foreach ($values as $key => $value) {
                $req->addPostData($key, $value);
            }
        } else {
            $req->addBodyData($values);
        }
        
        $response = $req->sendRequest($url, 'POST');
        
        $resp = explode("\r\n", $response);
        $bst  = false;
        $chk  = false;
        $body = array();
        foreach ($resp as $line) {
            if (!$bst && !$chk) {
                // HTTP status validation
                if (preg_match('/^HTTP\\/[0-9]\.[0-9] ([0-9]{3}) .+$/', $line, $matches)) {
                    $status = intval($matches[1]);
                    if ($status !== 200) {
                        return false;
                    } else {
                        $chk = true;
                    }
                }
            }
            if ($bst) {
                $body[] = $line;
            }
            if ($line == '') {
                $bst = true;
            }
        }
        
        $body = implode("\r\n", $body);
        
        if ($this->_json_convert) {
            if (@include_once 'Jsphon.php') {
                include_once 'Services/Twitter/Jsphon.php';
                $body = Services_Twitter_Jsphon::decode($body);
            }
        }
        
        return $body;
    }
    
    /**
     * send get data request
     *
     * @access private
     *
     * @param string $method  HTTP request method (POST or GET)
     * @param string $url     call get data API's URL
     * @param string $etagkey etag cache key setting
     *
     * @return mixed processed success, return response body. and processed faild, return false.
     */
    function _getData($method, $url, $etagkey) 
    {
        $id = sha1($etagkey);
        
        if ($this->_modified_check && $this->_cache_dir !== null) {
            $modf = realpath($this->_cache_dir) . DIRECTORY_SEPARATOR . $id . '.modified';
            $tagf = realpath($this->_cache_dir) . DIRECTORY_SEPARATOR . $id . '.etag';
            
            if (file_exists($modf)) {
                $this->setLastModified(file_get_contents($modf));
            }
            if (file_exists($tagf)) {
                $this->setEtag(file_get_contents($tagf));
            }
        }
        
        $req =& new Services_Twitter_Connector();
        
        if (!$this->checkAuth()) {
            $req->enableBasicAuth($this->_user, $this->_pass);
        }
        
        $req->addHeader('User-Agent', 'PHP/' . phpversion());
        
        if ($this->_app_name !== null) {
            $req->addHeader('X-Twitter-Client', $this->_app_name);
        }
        
        if ($this->_app_ver !== null) {
            $req->addHeader('X-Twitter-Client-Version', $this->_app_ver);
        }
        
        if ($this->_app_url !== null) {
            $req->addHeader('X-Twitter-Client-URL', $this->_app_url);
        }
        
        if ($this->getEtag() !== null) {
            $req->addHeader('If-None-Match', $this->getEtag());
        }
        
        if ($this->getLastModified() !== null) {
            $req->addHeader('If-Modified-Since', $this->getLastModified());
        }
        
        $response = $req->sendRequest($url, $method);
        $response = explode("\r\n", $response);
        
        $this->setEtag(null);
        $this->setLastModified(null);
        
        $bst  = false;
        $body = array();
        foreach ($response as $line) {
            if (!$bst) {
                // HTTP status validation
                if (preg_match('/^HTTP\\/[0-9]\.[0-9] ([0-9]{3}) .+$/', $line, $matches)) {
                    $status = intval($matches[1]);
                    if ($status !== 200) {
                        return false;
                    }
                }
                
                // get etag header value
                if (preg_match('/^ETag: (.+)$/', $line, $matches)) {
                    $this->setEtag($matches[1]);
                }
                
                // get last modified header value
                if (preg_match('/^Last-Modified: (.+)$/', $line, $matches)) {
                    $this->setLastModified($matches[1]);
                }
            }
            if ($bst) {
                $body[] = $line;
            }
            if ($line == '') {
                $bst = true;
            }
        }

        if ($this->_modified_check && $this->_cache_dir !== null) {
            $modf = realpath($this->_cache_dir) . DIRECTORY_SEPARATOR . $id . '.modified';
            $tagf = realpath($this->_cache_dir) . DIRECTORY_SEPARATOR . $id . '.etag';
            
            if ($this->getLastModified() !== null) {
                $fp = fopen($modf, 'w');
                flock($fp, LOCK_EX);
                fwrite($fp, $this->getLastModified());
                fclose($fp);
            }
            if ($this->getEtag() !== null) {
                $fp = fopen($tagf, 'w');
                flock($fp, LOCK_EX);
                fwrite($fp, $this->getEtag());
                fclose($fp);
            }
        }
        
        $body = implode("\r\n", $body);
        
        if ($this->_json_convert) {
            if (@include_once 'Jsphon.php') {
                include_once 'Services/Twitter/Jsphon.php';
                $body = Services_Twitter_Jsphon::decode($body);
            }
        }
        
        return $body;
    }

    /**
     * send auth check request
     *
     * @access private
     *
     * @param string $method  HTTP request method (POST or GET)
     * @param string $url     call get data API's URL
     *
     * @return mixed processed success, return true. and processed faild, return false.
     */
    function _authConnect($method, $url) 
    {
        $req =& new Services_Twitter_Connector();
        $req->addHeader('User-Agent', 'PHP/' . phpversion());
        $response = $req->sendRequest($url, $method);
        $response = explode("\r\n", $response);
        
        foreach ($response as $line) {
//        var_dump($line);
            // HTTP status validation
            if (preg_match('/^HTTP\\/[0-9]\.[0-9] ([0-9]{3}) .+$/', $line, $matches)) {
                $status = intval($matches[1]);
                if ($status !== 200) {
                    return false;
                }
            }
        }
        return true;
    }
    
    /**
     * public_timeline access
     *
     * @access public
     *
     * @param array $id (Optional) request options(since_id)
     *
     * @return mixed false or response data.
     */
    function getPublicTimeline($id = false)
    {
        if (!$id) {
            // not settings parameters
            return $this->_getData('GET', $this->sm_public, 'getPublicTimeline');
        } else {
            $url = $this->sm_public;
            $url .= '?since_id=' . urlencode($id);
            // on settings parameter
            return $this->_getData('GET', $url, 'getPublicTimeline');
        }
    }
    
    /**
     * friends_timeline access
     *
     * @access public
     *
     * @param array $options (Optional) request options(id, since, page)
     *
     * @return mixed false or response data.
     */
    function getFriendsTimeline($options = false)
    {
        if (!$options) {
            // not settings parameters
            return $this->_getData('GET', $this->sm_friends, 'getFriendsTimeline');
        } else {
            // parameter 'ID' setted.
            if (isset($options['id'])) {
                $url = sprintf($this->sm_friends_target, urlencode($options['id']));
            } else {
                $url = $this->sm_friends;
            }
            
            $appended = false;
            
            // parameter 'SINCE' setted.
            if (isset($options['since'])) {
                if (!$appended) {
                    $url .= '?';
                    $appended = true;
                } else {
                    $url .= '&';
                }
                $url .= 'since=' . urlencode($options['since']);
            }
            
            // parameter 'PAGE' setted.
            if (isset($options['page'])) {
                if (!$appended) {
                    $url .= '?';
                    $appended = true;
                } else {
                    $url .= '&';
                }
                $url .= 'page=' . intval($options['page']);
            }
            
            // on settings parameter
            return $this->_getData('GET', $url, 'getFriendsTimeline');
        }
    }
    
    /**
     * user_timeline access
     *
     * @access public
     *
     * @param array $options (Optional) request options(id, count, since)
     *
     * @return mixed false or response data.
     */
    function getUserTimeline($options = false)
    {
        if (!$options) {
            return $this->_getData('GET', $this->sm_user, 'getUserTimeline');
        } else {
            if (isset($options['id'])) {
                $url = sprintf($this->sm_user_target, urlencode($options['id']));
            } else {
                $url = $this->sm_user;
            }
            
            $first = true;
            if (isset($options['count'])) {
                if ($first) {
                    $url .= '?count=' . urlencode($options['count']);
                    $first = false;
                } else {
                    $url .= '&amp;count=' . urlencode($options['count']);
                }
            }
            if (isset($options['since'])) {
                if ($first) {
                    $url .= '?since=' . urlencode($options['since']);
                    $first = false;
                } else {
                    $url .= '&amp;since=' . urlencode($options['since']);
                }
            }
            
            return $this->_getData('GET', $url, 'getUserTimeline');
        }
    }
        
    /**
     * show(status method) access
     *
     * @access public
     *
     * @param array $id (Optional) post id
     *
     * @return mixed false or response data.
     */
    function getStatusShow($id)
    {
        return $this->_getData('GET', sprintf($this->sm_show, $id), 'getStatusShow');
    }
    
    /**
     * update access
     *
     * @access public
     *
     * @param string $value update status sentence.
     *
     * @return mixed false or response data.
     */
    function setUpdate($value)
    {
        return $this->_setData($this->sm_update,
            array(
                'status'    => urlencode($value)
            ),
            array(
                'Content-Type'    => 'application/x-www-form-urlencoded'
            ));
    }
    
    /**
     * Replies access
     *
     * @access public
     *
     * @return mixed false or response data.
     */
    function getReplies($page = false)
    {
        $url = $this->sm_replies;
        
        if ($page) {
            $url .= '?page=' . intval($page);
        }

        return $this->_getData('GET', $url, 'getReplies');
    }
    
    /**
     * friends access
     *
     * @access public
     *
     * @param array $id (Optional) user id
     *
     * @return mixed false or response data.
     */
    function getFriends($id = null)
    {
        if (!$id) {
            // not settings parameters
            return $this->_getData('GET', $this->um_friends, 'getFriends');
        } else {
            $url = sprintf($this->um_friends_target, $id);
            // on settings parameter
            return $this->_getData('GET', $url, 'getFriends');
        }
    }
    
    /**
     * followers access
     *
     * @access public
     *
     * @return mixed false or response data.
     */
    function getFollowers()
    {
        return $this->_getData('GET', $this->um_followers, 'getFollowers');
    }
    
    /**
     * featured access
     *
     * @access public
     *
     * @return mixed false or response data.
     */
    function getFeatured()
    {
        return $this->_getData('POST', $this->um_featured, 'getFeatured');
    }
    
    /**
     * show(user method) access
     *
     * @access public
     *
     * @param string $id user id
     *
     * @return mixed false or response data.
     */
    function getUserShow($id)
    {
        return $this->_getData('GET', sprintf($this->um_show, $id), 'getUserShow');
    }
    
    /**
     * direct message access
     *
     * @access public
     *
     * @param array $options (Optional) request options(since, page)
     *
     * @return mixed false or response data.
     */
    function getDirectMessage($options = false)
    {
        if (!$options) {
            // not settings parameters
            return $this->_getData('GET', $this->dm_show, 'getDirectMessage');
        } else {
            $url = $this->dm_show;
            
            $appended = false;
            if (isset($options['since'])) {
                if (!$appended) {
                    $url .= '?';
                } else {
                    $url .= '&';
                }
                $url .= 'since=' . urlencode($options['since']);
            }
            
            if (isset($options['page'])) {
                if (!$appended) {
                    $url .= '?';
                } else {
                    $url .= '&';
                }
                $url .= 'page=' . intval($options['page']);
            }

            // on settings parameter
            return $this->_getData('GET', $url, 'getDirectMessage');
        }
    }
    
    /**
     * direct message new access
     *
     * @access public
     *
     * @param string $id   user id.
     * @param string $text send directmessage text.
     *
     * @return mixed false or response data.
     */
    function setDirectMessage($id, $text)
    {
        return $this->_setData($this->dm_new,
            array(
                'user'    => urlencode($id),
                'text'    => urlencode($text)
            ),
            array(
                'Content-Type'    => 'application/x-www-form-urlencoded'
            ));
    }
    
    /**
     * add new friend
     *
     * @access public
     *
     * @param string $id target user id
     *
     * @return mixed false or response data.
     */
    function addFriend($id)
    {
        return $this->_setData(sprintf($this->fm_create, $id), null);
    }
    
    /**
     * remove friend
     *
     * @access public
     *
     * @param string $id target user id
     *
     * @return mixed false or response data.
     */
    function removeFriend($id)
    {
        return $this->_setData(sprintf($this->fm_destroy, $id), null);
    }
    
    /**
     * verify credentials
     *
     * @access public
     *
     * @return boolean If "Authrized" return true
     */
    function checkAuth()
    {
        $result = $this->_authConnect('POST', $this->am_verify);
        if ($result !== false) {
            return true;
        } else {
            return false;
        }
    }
    
    /**
     * end session
     *
     * @access public
     *
     * @return boolean If "success" return true
     */
    function endAuth()
    {
        $result = $this->_authConnect('POST', $this->am_endsess);
        if ($result !== false) {
            return true;
        } else {
            return false;
        }
    }
}
