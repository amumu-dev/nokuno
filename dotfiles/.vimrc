" basic
set nocompatible
set autoread
set history=10000

" display
set number
set laststatus=2
set linespace=0
set wildmenu
set showcmd

" use iconv for status line
if has('iconv')
    set statusline=%<[%n]%m%r%h%w%{'['.(&fenc!=''?&fenc:&enc).':'.&ff.']'}%y\ %F%=[%{GetB()}]\ %l,%c%V%8P
else
    set statusline=%<%f\ %m\ %r%h%w%{'['.(&fenc!=''?&fenc:&enc).']['.&ff.']'}%=\ (%v,%l)/%L%8P
endif

" syntax color
syntax on

" custom colors
highlight Constant ctermfg=LightRed
highlight Comment ctermfg=LightCyan
highlight Statement ctermfg=LightBlue
highlight PreProc ctermfg=LightCyan
highlight Type ctermfg=LightGreen
highlight Special ctermfg=Magenta
highlight SpecialKey ctermfg=DarkGray
highlight LineNr ctermfg=DarkGray

"display tab and zenkaku space
set list
set listchars=tab:>-,trail:-
highlight JpSpace cterm=underline ctermfg=blue   "display JpSpace blue underline
au BufRead,BufNew * match JpSpace /　/

" statusline
highlight LineNr ctermfg=darkgrey
highlight Comment ctermfg=DarkCyan

" search
set ignorecase
set smartcase
set wrapscan
set hlsearch

" edit
set autoindent
set showmatch
set backspace=indent,eol,start
set smartindent
filetype plugin on
filetype plugin indent on
autocmd FileType python setl smartindent cinwords=if,elif,else,for,while,try,except,finally,def,class

" tab
set expandtab
set tabstop=4
set shiftwidth=4
set softtabstop=0
set shiftround

" graphical move
nmap j gj
nmap k gk
vmap j gj
vmap k gk

" no highright
nnoremap  gh :nohlsearch<Return>

" let query center
nmap n nzz 
nmap N Nzz 
nmap * *zz 
nmap # #zz 
nmap g* g*zz 
nmap g# g#zz

" change encoding
nmap ,U :set fileencoding=utf-8<cr>
nmap ,e :set fileencoding=euc-jp<cr>
nmap ,s :set fileencoding=shift-jis<cr>

" auto encoding
" see http://www.kawaz.jp/pukiwiki/?vim#cb691f26
if &encoding !=# 'utf-8'
  set encoding=japan
  set fileencoding=japan
endif
if has('iconv')
  let s:enc_euc = 'euc-jp'
  let s:enc_jis = 'iso-2022-jp'
  if iconv("\x87\x64\x87\x6a", 'cp932', 'eucjp-ms') == "\xad\xc5\xad\xcb"
    let s:enc_euc = 'eucjp-ms'
    let s:enc_jis = 'iso-2022-jp-3'
  elseif iconv("\x87\x64\x87\x6a", 'cp932','euc-jisx0213') ==# "\xad\xc5\xad\xcb"
    let s:enc_euc = 'euc-jisx0213'
    let s:enc_jis = 'iso-2022-jp-3'
  endif
  if &encoding ==# 'utf-8'
    let s:fileencodings_default = &fileencodings
    let &fileencodings = s:enc_jis .','. s:enc_euc .',cp932'
    let &fileencodings = &fileencodings .','.s:fileencodings_default
    unlet s:fileencodings_default
  else
    let &fileencodings = &fileencodings .','. s:enc_jis
    set fileencodings+=utf-8,ucs-2le,ucs-2
    if &encoding =~#
      '^\(euc-jp\|euc-jisx0213\|eucjp-ms\)$'
      set fileencodings+=cp932
      set fileencodings-=euc-jp
      set fileencodings-=euc-jisx0213
      set fileencodings-=eucjp-ms
      let &encoding = s:enc_euc
      let &fileencoding = s:enc_euc
    else
      let &fileencodings =&fileencodings.','s:enc_euc
    endif
  endif
  unlet s:enc_euc
  unlet s:enc_jis
endif
if has('autocmd')
  function! AU_ReCheck_FENC()
    if &fileencoding =~# 'iso-2022-jp' && search("[^\x01-\x7e]", 'n') == 0
      let &fileencoding=&encoding
    endif
  endfunction
  autocmd BufReadPost * call AU_ReCheck_FENC()
endif
" line break
set fileformats=unix,dos,mac
if exists('&ambiwidth')
  set ambiwidth=double
endif


"statusline encoding
function! GetB()
    let c = matchstr(getline('.'), '.', col('.') - 1)
    let c = iconv(c, &enc, &fenc)
    return s:String2Hex(c)
endfunction

" :help eval-examples
" The function Nr2Hex() returns the Hex string of a number.
function! s:Nr2Hex(nr)
    let n = a:nr
    let r = ''
    while n
        let r = '0123456789ABCDEF'[n % 16] . r
        let n = n / 16
    endwhile
    return r
endfunc

" The function String2Hex() converts each character in a string to a two
" character Hex string.
function! s:String2Hex(str)
    let out = ''
    let ix = 0
    while ix < strlen(a:str)
        let out = out . s:Nr2Hex(char2nr(a:str[ix]))
        let ix = ix + 1
    endwhile
    return out
endfunc
