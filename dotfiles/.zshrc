# Source global settings
if [ -f /etc/zshrc ]; then
    . /etc/zshrc
fi

# auto screen
if [ $SHLVL = 1 ];then
    screen -xR
fi

# Prompt
PROMPT="[%m %~] $ "
PROMPT2='> '
RPROMPT=''

# Alias
alias ls='ls -F --color=auto'
alias ll='ls -lh'
alias la='ls -lha'
alias lt='ls -lht'
alias sort='LC_ALL=C sort -S 1000000'
alias mecab='mecab -b 1000000'

# Command complete
autoload -U compinit
compinit

# Zsh option
setopt auto_cd
setopt auto_pushd
setopt auto_menu
setopt list_packed
setopt nolistbeep
setopt no_beep
setopt pushd_ignore_dups
setopt extended_glob

# key bind
bindkey -e
bindkey "^?"    backward-delete-char
bindkey "^H"    backward-delete-char
bindkey "^[[3~" delete-char
bindkey "^[[1~" beginning-of-line
bindkey "^[[4~" end-of-line

# History
HISTFILE=~/.zsh_history
HISTSIZE=10000
SAVEHIST=10000
setopt share_history
setopt hist_ignore_dups
setopt hist_save_no_dups

# Path
path=($HOME/bin(N) $HOME/nokuno/python/*(N) $path)
typeset -U path

# SVN
export SVN_SSH="ssh -1"
export SVN_EDITOR=vim

# Misc
export LANG=ja_JP.UTF-8
export EDITOR=vim

# cd and ls
function chpwd() { ls }

