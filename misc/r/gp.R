curve_fitting <- data.frame(
	x=c(0.000000,0.111111,0.222222,0.333333,0.444444,0.555556,0.666667,0.777778,0.888889,1.000000),
	t=c(0.349486,0.830839,1.007332,0.971507,0.133066,0.166823,-0.848307,-0.445686,-0.563567,0.261502))

gp <- function(beta, sigma) {
	kernel <- function(x1, x2) exp(-(x1-x2)^2/(2*sigma^2));
	K <- outer(curve_fitting$x, curve_fitting$x, kernel);
	C_N <- K + diag(dim(curve_fitting)[1])/beta
	m <- function(x) (outer(x, curve_fitting$x, kernel) %*% solve(C_N) %*% curve_fitting$t)

	plot(m, xlim=c(0,1), ylim=c(-1,1), xlab="", ylab="")
	par(new=T)
	plot(curve_fitting, xlim=c(0,1), ylim=c(-1,1), xlab=paste("beta=",beta,", sigma=",sigma), ylab="")
}

par(mfrow=c(2,2)) 