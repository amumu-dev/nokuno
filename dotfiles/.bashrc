# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific aliases and functions
PS1="[\h \w]$ "
stty stop undef

export LANG=ja_JP.UTF-8
export EDITOR=vim
export SVN_EDITOR=vim
export SVN_ROOT=https://nokuno.googlecode.com/svn/trunk
export PYTHONPATH=/home/nokuno/install/lib64/python/:$PYTHONPATH

export PATH=$HOME/install/bin:$PATH
export PATH=$HOME/nokuno/python/ngram/:$PATH

alias ls='ls --color=auto'
alias sort='sort -S 1000000'
alias mecab='mecab -b 1000000'

function cdls() {
    command cd $@;
    ls;
}
alias cd=cdls
alias ll="ls -lh"
alias la="ls -ah"
alias lla="ls -alh"
