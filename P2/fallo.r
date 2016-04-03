png("doc/graficas/P1_perc.png", width = 720, height = 720)

par(mfrow =c(2,2))
t<-read.table("adaptacionp.data")
ta<-read.table("adaptacion.data")

plot(t[,1], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="p1 perceptrony adaline")
lines(ta[,1], col="red")
legend(x= 6000 , y=0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("perceptron", "adaline"))
plot(t[,1][2:999], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="primer tramo")
lines(ta[,1][2:999], col="red")
legend(x= 600 , y=0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("perceptron", "adaline"))

plot(t[,1][5000:5999], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="tramo medio")
lines(ta[,1][5000:5999], col="red")

legend(x= 600 , y=0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("perceptron", "adaline"))
plot(t[,1][9000:9999], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="ultimo tramo")
lines(ta[,1][9000:9999], col="red")
legend(x= 600 , y=0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("perceptron", "adaline"))
rect(1, 5, 3, 7, col = "white")
dev.off()
