
aplanar <- function(t){
	x<-c(t[1,])
	for(i in 2:nrow(t)){
		x<-c(x, t[i])
	}
	return (x)
}