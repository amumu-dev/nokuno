# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

if [ $TERM = "xterm" -o $SHLVL = '1' ] ; then
    screen -xR
fi

