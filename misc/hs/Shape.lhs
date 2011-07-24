これは文芸的プログラミングの例です．
データ構造を定義します．

> data Shape = Rectangle Float Float
>           | Square Float
>           | Circle Float

面積を計算する関数を定義します．

> area :: Shape -> Float
> area (Rectangle l w) = l * w
> area (Square s)      = s * s
> area (Circle r)      = pi * r * r

周囲の長さを計算する関数を定義します．

> perimeter :: Shape -> Float
> perimeter (Rectangle l w) = 2 * (l + w)
> perimeter (Square s)      = 4 * s
> perimeter (Circle r)      = 2 * pi * r

