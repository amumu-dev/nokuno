#!/usr/bin/ruby -s
# -*- Ruby -*-

# 「プログラミングのための線形代数」サンプルコード
# (平岡和幸, 堀玄, オーム社, 2004. ISBN 4-274-06578-2)
# http://ssl.ohmsha.co.jp/cgi-bin/menu.cgi?ISBN=4-274-06578-2

# $Id: mymatrix.rb,v 1.13 2004/10/06 09:18:00 hira Exp $

# Copyright (c) 2004, HIRAOKA Kazuyuki <hira@ics.saitama-u.ac.jp>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#    * Redistributions of source code must retain the above copyright
#      notice,this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above
#      copyright notice, this list of conditions and the following
#      disclaimer in the documentation and/or other materials provided
#      with the distribution.
#    * Neither the name of the HIRAOKA Kazuyuki nor the names of its
#      contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#########################################################

# 「加減乗算」や「LU 分解による逆行列・一次方程式」の学習用コードです.
# あくまでも, 計算手順を示すのが目的.
# 実用には, matrix.rb (ruby に標準添付)などを使う方が良いでしょう.

# Ruby 使いの皆様へ:
#
# ごめんなさい. Ruby らしい書き方を極力避けています.
# 目標は「できるだけ多くの人が読んでわかる」なので.

# Ruby 使いでない皆様へ:
#
# 「動く擬似コード」として読んでください.
# 何かメジャーな言語を使った経験があれば, 勘で理解できると思います
# (本気の Ruby がこんなぎこちないものだと誤解しないようにだけお願いします).
# 見てのとおり, 「#」から行末まではコメントです.
#
# ▼は「特に言語依存な部分」. 中身は気にしなくて構いません.
# 例をながめて, 使い方だけ確認してください.

#########################################################
# ▼Usage

def matrix_usage()
  name = File::basename $0
  print <<EOU
#{name}: 行列計算のサンプルコード
(各種テスト)
  #{name} -t=make   → 生成
  #{name} -t=print  → 表示
  #{name} -t=arith  → 和・定数倍・積
  #{name} -t=op     → + - *
  #{name} -t=lu    → LU 分解
  #{name} -t=det    → 行列式
  #{name} -t=sol    → 連立一次方程式
  #{name} -t=inv    → 逆行列
  #{name} -t=plu    → LU 分解 (pivoting つき)
EOU
end

def matrix_test(section)
  standalone = (__FILE__ == $0)  # 直接起動か(他から load されたのでなく)
  matched = (section == $t)  # -t=○○ と section が一致するか
  return (standalone and matched)
end

if (matrix_test(nil)) # 直接起動かつ -t なしの場合は…
  matrix_usage()
end

#########################################################
# ▼ベクトル・行列の生成とアクセス

# 引数の範囲チェックはサボリ

### ベクトル

class MyVector
  def initialize(n)
    @a = Array::new(n)
    for i in 0...n
      @a[i] = nil
    end
  end
  def [](i)
    return @a[i-1]
  end
  def []=(i, x)
    @a[i-1] = x
  end
  def dim
    return @a.length
  end
end

def make_vector(dim)
  return MyVector::new(dim)
end
def vector(elements)
  dim = elements.length
  vec = make_vector(dim)
  for i in 1..dim
    vec[i] = elements[i-1]
  end
  return vec
end
def vector_size(vec)
  return vec.dim
end
def vector_copy(vec)
  dim = vector_size(vec)
  new_vec = make_vector(dim)
  for i in 1..dim
    new_vec[i] = vec[i]
  end
  return new_vec
end

### 行列

class MyMatrix
  def initialize(m, n)
    @a = Array::new(m)
    for i in 0...m
      @a[i] = Array::new(n)
      for j in 0...n
        @a[i][j] = nil
      end
    end
  end
  def [](i, j)
    return @a[i-1][j-1]
  end
  def []=(i, j, x)
    @a[i-1][j-1] = x
  end
  def dim
    return @a.length, @a[0].length
  end
end

def make_matrix(rows, cols)
  return MyMatrix::new(rows, cols)
end
def matrix(elements)
  rows = elements.length
  cols = elements[0].length
  mat = make_matrix(rows, cols)
  for i in 1..rows
    for j in 1..cols
      mat[i,j] = elements[i-1][j-1]
    end
  end
  return mat
end
def matrix_size(mat)
  return mat.dim
end
def matrix_copy(mat)
  rows, cols = matrix_size(mat)
  new_mat = make_matrix(rows, cols)
  for i in 1..rows
    for j in 1..cols
      new_mat[i,j] = mat[i,j]
    end
  end
  return new_mat
end

### 例

if (matrix_test('make'))
  puts('- vector -')  # → 「- vector -」と表示して改行

  puts('Make vector v = [2,9,4]^T, show v[2] and size of v.')
  v = make_vector(3)  # 3 次元縦ベクトルを生成
  v[1] = 2
  v[2] = 9
  v[3] = 4
  puts(v[2])  # → 9 と表示して改行
  puts(vector_size(v))  # → 3 (次元)

  puts('Make vector w = [2,9,4]^T and show w[2].')
  w = vector([2,9,4])  # 同じベクトルを生成する別法
  puts(w[2])  # → 9

  puts('Copy v to x and show x[2].')
  x = vector_copy(v)  # 複製
  puts(x[2])  # → 9
  puts('Modify x[2] and show x[2] again.')
  x[2] = 0
  puts(x[2])  # → 0
  puts('Original v[2] is not modified.')
  puts(v[2])  # → 9

  puts('- matrix -')

  puts('Make matrix A = [[2 9 4] [7 5 3]] and show a[2,1].')
  a = make_matrix(2, 3)  # 2×3 行列を生成
  a[1,1] = 2
  a[1,2] = 9
  a[1,3] = 4
  a[2,1] = 7
  a[2,2] = 5
  a[2,3] = 3
  puts(a[2,1])  # → 7
  puts('Show size of A.')
  rows, cols = matrix_size(a)  # a のサイズを取得
  puts(rows)  # → 2
  puts(cols)  # → 3

  puts('Make matrix B = [[2 9 4] [7 5 3]] and show b[2,1].')
  b = matrix([[2,9,4], [7,5,3]])  # 同じ行列を生成する別法
  puts(b[2,1])  # → 7

  puts('Copy A to C and show c[2,1].')
  c = matrix_copy(a)  # 複製
  puts(c[2,1])  # → 7
  puts('Modify c[2,1] and show c[2,1] again.')
  c[2,1] = 0
  puts(c[2,1])  # → 0
  puts('Original a[2,1] is not modified.')
  puts(a[2,1])  # → 7
end

#########################################################
# ベクトル・行列の表示

# ベクトルを表示する関数 vector_print を定義. 使い方は例を参照.
def vector_print(vec)
  dim = vector_size(vec)
  for i in 1..dim  # i = 1, 2, ..., dim についてループ (end まで)
    printf('%5.4g ', vec[i])  # 5文字分の幅を確保して4桁まで表示
    puts('')  # 改行
  end
  puts('')
end

def matrix_print(mat)
  rows, cols = matrix_size(mat)
  for i in 1..rows
    for j in 1..cols
      printf('%5.4g ', mat[i,j])
    end
    puts('')
  end
  puts('')
end

# いちいち「vector_print」「matrix_print」は長いので…
def vp(mat)
  vector_print(mat)
end
def mp(mat)
  matrix_print(mat)
end

### 例

if (matrix_test('print'))
  puts('Print vector [3,1,4]^T twice.')
  v = vector([3,1,4])
  vector_print(v)
  vp(v)
  puts('Print matrix [[2 9 4] [7 5 3]] twice.')
  a = matrix([[2,9,4], [7,5,3]])
  matrix_print(a)
  mp(a)
end

#########################################################
# ベクトル・行列の和・定数倍・積

### ベクトル

# 和 (ベクトル a にベクトル b を足し込む: a ← a+b) --- 「#」以降はコメント
def vector_add(a, b)       # 関数定義 (end まで)
  a_dim = vector_size(a)   # 各ベクトルの次元を取得
  b_dim = vector_size(b)
  if (a_dim != b_dim)      # 次元が等しくなければ… (end まで)
    raise 'Size mismatch.' # エラー
  end
  # ここからが本題
  for i in 1..a_dim        # ループ (end まで): i = 1, 2, ..., a_dim
    a[i] = a[i] + b[i]     # 成分ごとに足し込む
  end
end

# 定数倍 (ベクトル vec を数 num 倍)
def vector_times(vec, num)
  dim = vector_size(vec)
  for i in 1..dim
    vec[i] = num * vec[i]
  end
end

### 行列

# 和 (行列 a に行列 b を足し込む: a ← a+b)
def matrix_add(a, b)
  a_rows, a_cols = matrix_size(a)
  b_rows, b_cols = matrix_size(b)
  if (a_rows != b_rows)
    raise 'Size mismatch (rows).'
  end
  if (a_cols != b_cols)
    raise 'Size mismatch (cols).'
  end
  for i in 1..a_rows
    for j in 1..a_cols
      a[i,j] = a[i,j] + b[i,j]
    end
  end
end

# 定数倍 (行列 mat を数 num 倍)
def matrix_times(mat, num)
  rows, cols = matrix_size(mat)
  for i in 1..rows
    for j in 1..cols
      mat[i,j] = num * mat[i,j]
    end
  end
end

# 行列 a とベクトル v の積をベクトル r に格納
def matrix_vector_prod(a, v, r)
  # サイズを取得
  a_rows, a_cols = matrix_size(a)
  v_dim = vector_size(v)
  r_dim = vector_size(r)
  # 積が定義されるか確認
  if (a_cols != v_dim or a_rows != r_dim)
    raise 'Size mismatch.'
  end
  # ここからが本題. a の各行について…
  for i in 1..a_rows
    # a と v の対応する成分をかけあわせ, その合計を求める
    s = 0
    for k in 1..a_cols
      s = s + a[i,k] * v[k]
    end
    # 結果を r に格納
    r[i] = s
  end
end

# 行列 a と行列 b の積を行列 r に格納
def matrix_prod(a, b, r)
  # サイズを取得し, 積が定義されるか確認
  a_rows, a_cols = matrix_size(a)
  b_rows, b_cols = matrix_size(b)
  r_rows, r_cols = matrix_size(r)
  if (a_cols != b_rows or a_rows != r_rows or b_cols != r_cols)
    raise 'Size mismatch.'
  end
  # ここからが本題. a の各行、b の各列について…
  for i in 1..a_rows
    for j in 1..b_cols
      # a と b の対応する成分をかけあわせ, その合計を求める
      s = 0
      for k in 1..a_cols
        s = s + a[i,k] * b[k,j]
      end
      # 結果を r に格納
      r[i,j] = s
    end
  end
end

### 例

if (matrix_test('arith'))
  puts('- vector -')

  v = vector([1,2])
  w = vector([3,4])

  c = vector_copy(v)
  vector_add(c,w)
  puts('v, w, v+w, and 10 v')
  vp(v)
  vp(w)
  vp(c)

  c = vector_copy(v)
  vector_times(c,10)
  vp(c)

  puts('- matrix -')

  a = matrix([[3,1], [4,1]])
  b = matrix([[10,20], [30,40]])

  c = matrix_copy(a)
  matrix_add(c, b)
  puts('A, B, A+B, and 10 A')
  mp(a)
  mp(b)
  mp(c)

  c = matrix_copy(a)
  matrix_times(c, 10)
  mp(c)

  r = make_vector(2)
  matrix_vector_prod(a, v, r)
  puts('A, v, and A v')
  mp(a)
  vp(v)
  vp(r)

  r = make_matrix(2,2)
  matrix_prod(a, b, r)
  puts('A, B, and A B')
  mp(a)
  mp(b)
  mp(r)
end

#########################################################
# ▼a + b などと書けるよう

class MyVector
  def +(vec)
    c = vector_copy(self)
    vector_add(c, vec)
    return c
  end
  def -@()  # 単項演算子「-」
    c = vector_copy(self)
    vector_times(c, -1)
    return c
  end
  def -(vec)
    return self + (- vec)
  end
  def *(x)
    dims = vector_size(self)
    if (dims == 1)
      return x * self[1]
    elsif x.is_a? Numeric
      c = vector_copy(self)
      vector_times(c, x)
      return c
    else
      raise 'Type mismatch.'
    end
  end
  def coerce(other)
    if other.is_a? Numeric
      return vector([other]), self
    else
      raise 'Unsupported type.'
    end
  end
end

class MyMatrix
  def +(mat)
    c = matrix_copy(self)
    matrix_add(c, mat)
    return c
  end
  def -@()  # 単項演算子「-」
    c = matrix_copy(self)
    matrix_times(c, -1)
    return c
  end
  def -(mat)
    return self + (- mat)
  end
  def *(x)
    rows, cols = matrix_size(self)
    if (rows == 1 and cols == 1)
      return x * self[1,1]
    elsif x.is_a? Numeric
      c = matrix_copy(self)
      matrix_times(c, x)
      return c
    elsif x.is_a? MyVector
      r = make_vector(cols)
      matrix_vector_prod(self, x, r)
      return r
    elsif x.is_a? MyMatrix
      x_rows, x_cols = matrix_size(x)
      r = make_matrix(rows, x_cols)
      matrix_prod(self, x, r)
      return r
    else
      raise 'Type mismatch.'
    end
  end
  def coerce(other)
    if other.is_a? Numeric
      return matrix([[other]]), self
    else
      raise 'Unsupported type.'
    end
  end
end

### 例

if (matrix_test('op'))
  puts('- vector -')
  x = vector([1,2])
  y = vector([3,4])
  puts('x, y')
  vp(x)
  vp(y)
  puts('x+y, -x, y-x, x*10, 10*x')
  vp(x + y)
  vp(- x)
  vp(y - x)
  vp(x * 10)
  vp(10 * x)

  puts('- matrix -')
  a = matrix([[3,1], [4,1]])
  b = matrix([[10,20], [30,40]])
  puts('A, B')
  mp(a)
  mp(b)
  puts('A+B, -A, B-A, A*10, 10*A, A*B')
  mp(a + b)
  mp(- a)
  mp(b - a)
  mp(a * 10)
  mp(10 * a)
  mp(a * b)
  puts('A, x, and A*x')
  mp(a)
  vp(x)
  vp(a * x)
end

#########################################################
# LU 分解 (pivoting なし)

# LU 分解 (pivoting なし).
# 行列によってはゼロ割りエラーが出る.
# 結果は mat 自身に上書き(左下部分が L, 右上部分が U).
def lu_decomp(mat)
  rows, cols = matrix_size(mat)
  # 行数(rows)と列数(cols)とで短い方を s と置く
  if (rows < cols)
    s = rows
  else
    s = cols
  end
  # ここからが本題
  for k in 1..s
    # この段階で, mat は次のとおり (u, l は U, L の完成部分. r は残差.)
    #     u u u u u u
    #     l u u u u u
    #     l l r r r r  ←第 k 行
    #     l l r r r r
    #     l l r r r r
    # 【ア】 U の第 k 行は, この段階での残差そのもの → 何もしなくてよい
    # 【イ】 L の第 k 列を計算
    # 一般に割り算は手間がかかるので、割り算の回数を減らすために小細工する
    x = 1.0 / mat[k,k]  # (mat[k,k] が 0 だと, ここでゼロ割りエラー)
    for i in (k+1)..rows
      mat[i,k] = mat[i,k] * x  # 要するに mat[i,k] / mat[k,k]
    end
    # 【ウ】 残差を更新
    for i in (k+1)..rows
      for j in (k+1)..cols
        mat[i,j] = mat[i,j] - mat[i,k] * mat[k,j]
      end
    end
  end
end

# LU 分解の結果を, 二つの行列 L, U に分割
def lu_split(lu)
  rows, cols = matrix_size(lu)
  # 行数と列数とで短い方を r と置く
  if (rows < cols)
    r = rows
  else
    r = cols
  end
  # L は rows×r, R は r×cols
  lmat = make_matrix(rows, r)
  umat = make_matrix(r, cols)
  # L を求める
  for i in 1..rows
    for j in 1..r
      if (i > j)
        x = lu[i,j]
      elsif (i == j)  # else if
        x = 1
      else
        x = 0
      end
      lmat[i,j] = x
    end
  end
  # R を求める
  for i in 1..r
    for j in 1..cols
      if (i > j)
        x = 0
      else
        x = lu[i,j]
      end
      umat[i,j] = x
    end
  end
  return [lmat, umat]  # lmat と umat の組を返す
end

### 例

if (matrix_test('lu'))
  a = matrix([[2,6,4], [5,7,9]])
  c = matrix_copy(a)
  lu_decomp(c)
  l, u = lu_split(c)
  puts('A, L, U, and L U')
  mp(a)
  mp(l)
  mp(u)
  mp(l * u)  # a と等しくなる
end

#########################################################
# 行列式

# 行列式. 元の行列は破壊される.
def det(mat)
  # 正方行列なことを確認
  rows, cols = matrix_size(mat)
  if (rows != cols)
    raise 'Not square.'
  end
  # ここからが本題. LU 分解して…
  lu_decomp(mat)
  # U の対角成分の積を答える
  x = 1
  for i in 1..rows
    x = x * mat[i,i]
  end
  return x
end

### 例

if (matrix_test('det'))
  a = matrix([[2,1,3,2], [6,6,10,7], [2,7,6,6], [4,5,10,9]])
  puts('A and det A = -12')
  mp(a)
  puts det(a)  # → -12
end

#########################################################
# 連立一次方程式

# 方程式 A x = y を解く (A: 正方行列, y: ベクトル).
# A は破壊され, 解は y に上書きされる.
def sol(a, y)
  # サイズ確認は省略
  # まず LU 分解
  lu_decomp(a)
  # あとは下請けにまかせる
  sol_lu(a, y)
end

# (下請け) 方程式 L U x = y を解く. 解は y に上書きされる.
# L, U は正方行列 A の LU 分解 (まとめて一つの行列に格納しておく)
def sol_lu(lu, y)
  # サイズを取得
  n = vector_size(y)
  # L z = y を解く. 解 z は y に上書き.
  sol_l(lu, y, n)
  # U x = y (中身は z)を解く. 解 x は y に上書き.
  sol_u(lu, y, n)
end

# (孫請け) L z = y を解く. 解 z は y に上書き. n は y のサイズ.
# L, U は正方行列 A の LU 分解 (まとめて一つの行列に格納しておく)
def sol_l(lu, y, n)
  for i in 1..n
    # z[i] = y[i] - L[i,1] z[1] - ... - L[i,i-1] z[i-1] を計算する
    # すでに求まった解 z[1], ..., z[i-1] は y[1], ..., y[i-1] に格納されている
    for j in 1..(i-1)
      y[i] = y[i] - lu[i,j] * y[j]  # 実質は y[i] - L[i,j] * z[j]
    end
  end
end

# (孫請け) U x = y を解く. 解 x は y に上書き. n は y のサイズ.
# L, U は正方行列 A の LU 分解 (まとめて一つの行列に格納しておく)
def sol_u(lu, y, n)
  # i = n, n-1, ..., 1 の順で処理
  #   ※ 念のため注意:
  #   本物のRubyがこんなぎこちない言語だと誤解しないでください.
  #   Rubyを知らなくても読めるよう, 便利な機能・記法は封印しています.
  for k in 0..(n-1)
    i = n - k
    # x[i] = (y[i] - U[i,i+1] x[i+1] - ... - U[i,n] x[n]) / U[i,i] を計算する
    # すでに求まった解 x[i+1], ..., x[n] は y[i+1], ..., y[n] に格納されている
    for j in (i+1)..n
      y[i] = y[i] - lu[i,j] * y[j]  # 実質は y[i] - U[i,j] * x[j]
    end
    y[i] = y[i] / lu[i,i]
  end
end

### 例

if (matrix_test('sol'))
  a = matrix([[2,3,3], [3,4,2], [-2,-2,3]])
  c = matrix_copy(a)
  y = vector([9,9,2])
  puts('A, y, and solution x of A x = y.')
  mp(a)
  vp(y)
  sol(c, y)
  vp(y)
  puts('A x')
  vp(a*y)
end

#########################################################
# 逆行列

# 逆行列を返す. 元の行列は破壊される.
def inv(mat)
  rows, cols = matrix_size(mat)
  # 正方行列なことを確認
  rows, cols = matrix_size(mat)
  if (rows != cols)
    raise 'Not square.'
  end
  # 結果の格納場所を用意. 初期化して単位行列にしておく.
  ans = make_matrix(rows, cols)
  for i in 1..rows
    for j in 1..cols
      if (i == j)
        ans[i,j] = 1
      else
        ans[i,j] = 0
      end
    end
  end
  # ここからが本題. LU 分解して…
  lu_decomp(mat)
  for j in 1..rows
    # ans の各列を右辺として, 連立一次方程式 A x = y を解く.
    #   ※ 本当は, ans の各列を直接切り出して sol_lu に渡せるとよいのだが,
    #   その方法は言語依存. 仕方ないので, ここではわざわざ,
    #   (1)コピー, (2)計算, (3)結果を書き戻す, としている.
    v = make_vector(cols)
    for i in 1..cols
      v[i] = ans[i,j]
    end
    sol_lu(mat, v)
    for i in 1..cols
      ans[i,j] = v[i]
    end
  end
  return(ans)
end

if (matrix_test('inv'))
  a = matrix([[2,3,3], [3,4,2], [-2,-2,3]])
  c = matrix_copy(a)
  b = inv(c)
  puts('A and B = inverse of A.')
  mp(a)
  mp(b)
  puts('A B and B A')
  mp(a*b)
  mp(b*a)
end

#########################################################
# LU 分解 (pivoting つき)
# 結果は mat 自身に上書きし, 戻り値として, pivot table (ベクトル p)を返す.
#
# 得られる結果は,
# A' = L U (A' は A の行を入れかえたもの, L は上三角, U は下三角) という分解.
# A' の i 行目は元の行列 A の p[i] 行目.
# p_ref(mat, i, j, p) で, L (i>j)または U (i<=j)の i,j 成分が得られる.
def plu_decomp(mat)
  rows, cols = matrix_size(mat)
  # pivot table を用意し,
  # pivot された行列の各行が元の行列のどの行に対応しているかを記録する.
  # mat[i,j] への直接アクセスは避け, 必ず関数 p_ref(値参照), p_set(値変更)を
  # 介して「pivot された行列」へアクセスすることにより,
  # lu_decomp のコードを流用できる.
  p = make_vector(rows)
  for i in 1..rows
    p[i] = i  # pivot table の初期化. 初期値は「i 行目が i 行目」
  end
  # 行数(rows)と列数(cols)とで短い方を s と置く
  if (rows < cols)
    s = rows
  else
    s = cols
  end
  # ここからが本題
  for k in 1..s
    # まず pivoting をしておく
    p_update(mat, k, rows, p)
    # ここから先は, lu_decomp をこうおきかえただけ
    #   mat[i,j] → p_ref(mat, i, j, p)
    #   mat[i,j] = y → p_set(mat, i, j, p, y)
    # 【ア】 U の第 k 行は, この段階での残差そのもの → 何もしなくてよい
    # 【イ】 L の第 k 列を計算
    x = 1.0 / p_ref(mat, k, k, p)
    for i in (k+1)..rows
      y = p_ref(mat, i, k, p) * x
      p_set(mat, i, k, p, y)
    end
    # 【ウ】 残差を更新
    for i in (k+1)..rows
      x = p_ref(mat, i, k, p)
      for j in (k+1)..cols
        y = p_ref(mat, i, j, p) - x * p_ref(mat, k, j, p)
        p_set(mat, i, j, p, y)
      end
    end
  end
  # pivot table を戻り値として返す.
  return(p)
end

# pivoting を行う.
# 具体的には, k 列目の未処理箇所のうちで絶対値が最大の成分を k 行目にもってくる.
def p_update(mat, k, rows, p)
  # 候補(k 列目の未処理箇所)のうちでチャンピオン(絶対値が最大の成分)を探す.
  max_val = -777  # 最弱の初代チャンピオン. 誰にも負ける.
  max_index = 0
  for i in k..rows
    x = abs(p_ref(mat, i, k, p))
    if (x > max_val)  # チャンピオンを倒したら
      max_val = x
      max_index = i
    end
  end
  # 現在行(k)とチャンピオン行(max_index)をいれかえ
  pk = p[k]
  p[k] = p[max_index]
  p[max_index] = pk
end

# pivot された行列の (i,j) 成分の値を返す
def p_ref(mat, i, j, p)
  return(mat[p[i], j])
end

# pivot された行列の (i,j) 成分の値を val に変更
def p_set(mat, i, j, p, val)
  mat[p[i], j] = val
end

# ▼絶対値(を関数記法で書けるように)
def abs(x)
  return(x.abs)
end

# LU 分解の結果を, 二つの行列 L, U に分割
def plu_split(lu, p)
  rows, cols = matrix_size(lu)
  # 行数と列数とで短い方を r と置く
  if (rows < cols)
    r = rows
  else
    r = cols
  end
  # L は rows×r, R は r×cols
  lmat = make_matrix(rows, r)
  umat = make_matrix(r, cols)
  # L を求める
  for i in 1..rows
    for j in 1..r
      if (i > j)
        x = p_ref(lu, i, j, p)
      elsif (i == j)  # else if
        x = 1
      else
        x = 0
      end
      lmat[i,j] = x
    end
  end
  # R を求める
  for i in 1..r
    for j in 1..cols
      if (i > j)
        x = 0
      else
        x = p_ref(lu, i, j, p)
      end
      umat[i,j] = x
    end
  end
  return [lmat, umat]  # lmat と umat の組を返す
end

### 例

if (matrix_test('plu'))
  a = matrix([[2,6,4], [5,7,9]])
  c = matrix_copy(a)
  p = plu_decomp(c)
  l, u = plu_split(c, p)
  puts('A, L, U, and pivot table')
  mp(a)
  mp(l)
  mp(u)
  vp(p)
  puts('L U')
  mp(l * u)
end

#########################################################
# ▼動作チェック
# matrix.rb と結果を照らしあわせてチェック.
# ここから先は読まなくて構いません (「封印」を解く)

if ($c)
  require 'matrix'
  $eps = 1e-10
  class MyVector
    def to_a
     @a
    end
  end
  class MyMatrix
    def to_a
     @a
    end
  end
  def rmat(a)
    Matrix.rows a
  end
  def to_array_or_number(x)
    [Array, Matrix, Vector, MyVector, MyMatrix].find{|c| x.is_a? c} ? x.to_a : x
  end
  def aeq?(x, y)
    x = to_array_or_number x
    y = to_array_or_number y
    if x.is_a? Numeric
      y.is_a? Numeric and (x - y).abs < $eps
    elsif x.is_a? Array
      y.is_a? Array and
        x.size == y.size and
        not (0 ... x.size).map{|i| aeq? x[i], y[i]}.member? false
    else
      raise 'Bad type.'
    end
  end
  def rand_ary1(n)
    (1..n).map{|i| rand - 0.5}
  end
  def rand_ary2(m,n)
    (1..m).map{|i| rand_ary1 n}
  end
  def check_matmul(l,m,n)
    a = rand_ary2 l, m
    b = rand_ary2 m, n
    aeq? rmat(a) * rmat(b), matrix(a) * matrix(b)
  end
  def check_det(n)
    a = rand_ary2 n, n
    aeq? rmat(a).det, det(matrix(a))
  end
  def check_inv(n)
    a = rand_ary2 n, n
    aeq? rmat(a).inv, inv(matrix(a))
  end
  def check(label, repeat, proc)
    (1..repeat).each{|t| raise "#{label}" if !proc.call}
    puts "#{label}: ok"
  end
  [
    ['matmul', 100, lambda{check_matmul 6,5,4}],
    ['det', 100, lambda{check_det 7}],
    ['inv', 100, lambda{check_det 7}],
    ['aeq?', 1,
      lambda{
        ![
          # all pairs must be !aeq?
          [3, 3.14],
          [Vector[3], 3],
          [3, vector([3])],
          [Vector[1,2,3], vector([1,2,3,4])],
          [Vector[1,2,3,4], vector([1,2,3])],
          [Vector[1.1,2.2,3.3], vector([1.1,2.2000001,3.3])],
          [rmat([[1,2,3], [4,5,6]]), matrix([[1,2,3], [4.0000001,5,6]])],
        ].map{|a| !aeq?(*a)}.member? false}],
    ['----------- All Tests -----------', 1, lambda{true}],
    ['This must fail. OK if you see an error.', 1, lambda{aeq? 7.77, 7.76}],
  ].each{|a| check *a}
end
