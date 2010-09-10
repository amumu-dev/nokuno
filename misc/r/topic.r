install.packages("MCMCpack")
library(MCMCpack)

# Dirichlet
plot(rdirichlet(1000, c(1,1,1))[,1:2], cex=0.1)
plot(rdirichlet(1000, c(0.05,0.04,0.03))[,1:2], xlim=c(0,1), ylim=c(0,1), cex=0.1)
plot(rdirichlet(1000, c(0.5,0.4,0.3))[,1:2], xlim=c(0,1), ylim=c(0,1), cex=0.1)
plot(rdirichlet(1000, c(5,4,3))[,1:2], xlim=c(0,1), ylim=c(0,1), cex=0.1)
plot(rdirichlet(1000, c(50,40,30))[,1:2], xlim=c(0,1), ylim=c(0,1), cex=0.1)

# Dirichlet Mixture
x <- rdirichlet(1000, c(10,5,4))[,1:2]
y <- rdirichlet(1000, c(1,1,9))[,1:2]
plot(rbind(x, y), xlim=c(0,1), ylim=c(0,1), cex=0.1)
x <- rdirichlet(1000, c(10,5,4))[,1:2], rdirichlet(1000, c(0.1,0.1,0.9))[,1:2], rdirichlet(1000, c(20,50,50))[,1:2]
plot(rbind(x, y, z), xlim=c(0,1), ylim=c(0,1), cex=0.1)

# LDA
x <- rdirichlet(1000, c(0.5,0.5,0.5))[,1:2]
linear <- function(x) {x %*% matrix(c(0.6,0.05,0.15,0.7),nrow=2) + c(0.1,0.1)}
plot(linear(x),xlim=c(0,1), ylim=c(0,1), cex=0.1)

x <- rdirichlet(1000, c(0.8,1,10))[,1:2]
plot(linear(x),xlim=c(0,1), ylim=c(0,1), cex=0.1)

