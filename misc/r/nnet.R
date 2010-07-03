library(nnet)

#training data
x <- c(0.000000,0.111111,0.222222,0.333333,0.444444,0.555556,0.666667,0.777778,0.888889,1.000000)
t <- c(0.349486,0.830839,1.007332,0.971507,0.133066,0.166823,-0.848307,-0.445686,-0.563567,0.261502)

#learning phase
nn <- nnet(x, t, size=100, linout=TRUE)

#predicting phase
input <- seq(0, 1, length=100)
output <- predict(nn, matrix(input))

#display
plot(x, t, xlim=c(0,1), ylim=c(-1,1))
par(new=T)
plot(input, output, type="l", xlim=c(0,1), ylim=c(-1,1), xlab="", ylab="")

#evaluation
test <- sin(2*pi*input)
error <- sqrt(sum((output-test)^2))
print( paste('ERROR: ', error) )

rmse <- function(size) {
	nn <- nnet(x, t, size=size, linout=TRUE)
	output <- predict(nn, matrix(input))
	error <- sqrt(sum((output-test)^2))
	return(error)
}