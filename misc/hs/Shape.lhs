これは文芸的プログラミングの例です．
データ構造を定義します．

> data Shape = Rectangle Float Float
>           | Square Float

面積を計算する関数を定義します．

> area :: Shape -> Float
> area (Rectangle l w) = l * w
> area (Square s)      = s * s

