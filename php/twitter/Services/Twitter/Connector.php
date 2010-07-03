<?php
/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**
 * Twitter Network connection class
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

/**
 * Twitter Network connection class
 *
 * @category  Services
 * @package   Services_Twitter
 * @author    Takeshi KAWAMOTO <takeshi@transrain.net>
 * @copyright 2007 Takeshi KAWAMOTO <takeshi@transrain.net>
 * @license   http://www.php.net/license/3_01.txt PHP License 3.01
 * @version   Release: @package_version@
 * @link      http://www.transrain.net/product/services_twitter/
 */
class Services_Twitter_Connector
{
    var $_user;
    var $_pass;
    var $_basic_auth;
    var $_headers;
    var $_postdata;
    var $_body;
    
    /**
     * Class constructor
     *
     * @access public
     * @param string $user BASIC Auth's user name
     * @param string $pass BASIC Auth's password
     */
    function Services_Twitter_Connector($user = null, $pass = null)
    {
        if ($user !== null) {
            $this->_user = $user;
        }
        if ($pass !== null) {
            $this->_pass = $pass;
        }
        
        $this->_basic_auth  = false;
        $this->_headers     = array();
        $this->_body        = array();
    }
    
    /**
     * Send request method
     *
     * @access public
     * @param string $url    send to this url
     * @param string $method (Optional) send request method. default is GET.
     *
     * @return string response body
     */
    function sendRequest($url, $method = 'GET')
    {
        $request    = '';
        $body       = '';
        $url        = parse_url($url);
        
        if (!isset($url['port'])) {
            $url['port'] = 80;
        }
        
        // set basic auth header
        if ($this->_basic_auth) {
            $hash = base64_encode($this->_user . ":" . $this->_pass);
            $this->addHeader('Authorization', 'Basic ' . $hash);
        }
        
        // set Content-length
        if (count($this->_postdata) > 0) {
            $first = false;
            foreach ($this->_postdata as $key => $value) {
                if ($first) {
                    $body .= '&amp;';
                }
                $body .= $key . '=' . $value;
                $first = true;
            }
        }
        
        if (count($this->_body) > 0) {
            foreach ($this->_body as $line) {
                $body .= $line . "\r\n";
            }
        }
        $this->addHeader('Content-Length', strlen($body));
        
        // create path
        $path = $url['path'];
        if (isset($url['query'])) {
            $path .= '?' . $url['query'];
        }
        
        // definity send target
        $request .= $method . ' ' . $path . ' HTTP/1.1'."\r\n";
        $request .= 'HOST: ' . $url['host'] . "\r\n";
        
        // set header
        if (count($this->_headers) > 0) {
            foreach ($this->_headers as $name => $value) {
                $request .= $name . ': ' . $value . "\r\n";
            }
        }
        
        // set separator
        $request .= "\r\n";
        
        // set body
        $request .= $body;
        
        // send request
        $fp  = fsockopen($url['host'], $url['port']);
        if (!$fp) return false;
        fputs($fp, $request);
        $response = '';
        while (!feof($fp)) $response .= fgets($fp, 4096);
        fclose($fp);

        return $response;
    }
    
    /**
     * append to post data method
     *
     * @access public
     * @param string $name  post parameter name
     * @param string $value post parameter value
     *
     * @return array setup value
     */
    function addPostData($name, $value)
    {
        $this->_postdata[$name] = $value;
        return $this->_postdata;
    }
    
    /**
     * append data method
     *
     * @access public
     * @param string $value body value
     *
     * @return array setup value
     */
    function addBodyData($value)
    {
        $this->_body[] = $value;
        return $this->_body;
    }
    
    /**
     * append HTTP header
     *
     * @access public
     * @param string $name  HTTP header name
     * @param string $value HTTP header value
     *
     * @return array setup value
     */
    function addHeader($name, $value)
    {
        $this->_headers[$name] = $value;
        return $this->_headers;
    }
    
    /**
     * remove HTTP header
     *
     * @access public
     * @param string $name HTTP header name
     *
     * @return array setup value
     */
    function removeHeader($name)
    {
        if (isset($this->_headers[$name])) {
            $this->_headers[$name] = null;
        }
        return $this->_headers;
    }

    /**
     * enabled basic auth method
     *
     * @access public
     * @param string $user BASIC Auth's user name
     * @param string $pass BASIC Auth's password
     *
     * @return boolean basic auth status
     */
    function enableBasicAuth($user = null, $pass = null)
    {
        if ($user !== null) {
            $this->_user = $user;
        }
        if ($pass !== null) {
            $this->_pass = $pass;
        }
        $this->_basic_auth = true;
        return $this->_basic_auth;
    }
    

    /**
     * disabled basic auth method
     *
     * @access public
     * @return boolean basic auth status
     */
    function disableBasicAuth()
    {
        $this->_basic_auth = false;
        return $this->_basic_auth;
    }
    
}