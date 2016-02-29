png("doc/graficas/P1_perc.png", width = 720, height = 720)

t<-read.table("adaptacionp.data")
ta<-read.table("adaptacion.data")

plot(t[,1][1:100], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="p1 perceptrony adaline")
lines(ta[,1], col="red")
legend(x= 60 , y=0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("perceptron", "adaline"))
rect(1, 5, 3, 7, col = "white")
dev.off()
