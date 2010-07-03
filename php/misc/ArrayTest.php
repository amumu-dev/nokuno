<?php
require_once 'PHPUnit/Framework.php';

class ArrayTest extends PHPUnit_Framework_TestCase
{
    public function testNewArrayIsEmpty()
    {
        // 配列を作成します。
        $fixture = array();

        // 配列のサイズは 0 です。
        $this->assertEquals(0, sizeof($fixture));
    }

    /**
     * メソッド名がtestで始まっていないが，「@test」
     * アノテーションを使用していることに注意
     *
     * @test
     */
    public function arrayContainsAnElementTest()
    {
        // 配列を作成します。
        $fixture = array();

        // 配列にひとつの要素を追加します。
        $fixture[] = 'Element';

        // 配列のサイズは 1 です。
        $this->assertEquals(1, sizeof($fixture));
    }
}
