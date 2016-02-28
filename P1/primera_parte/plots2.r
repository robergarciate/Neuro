png("doc/graficas/P1_perc_tasa.png", width = 720, height = 720)

par(mfrow =c(2,2))
t<-read.table("adaptacionp.data")
t1<-read.table("adaptacionp1.data")
ta<-read.table("adaptacionpa.data")
ta1<-read.table("adaptacionpa1.data")

plot(t[,1], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="perceptron")
lines(t1[,1], col="red")
legend(x= 6000 , y= 0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("tasa=0.1", "tasa=0.01"))


plot(t[,1][2:999], type="l", col="blue", ylim=c(0,max(t[,1][2:999])), ylab="adaptacion", xlab="etapas", main="aumentado")
lines(t1[,1][2:999], col="red")

legend(x= 600 , y=0.75*(max(t[,1][2:999])-min(t[,1][2:999])) ,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("tasa=0.1", "tasa=0.01"))



plot(ta[,1], type="l", col="blue", ylim=c(0,1), ylab="adaptacion", xlab="etapas", main="adaline")
lines(ta1[,1], col="red")
legend(x= 6000 , y= 0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("tasa=0.1", "tasa=0.01"))


plot(ta[,1][2:999], type="l", col="blue", ylim=c(0,max(ta[,1][2:999])), ylab="adaptacion", xlab="etapas", main="aumentado")
lines(ta1[,1][2:999], col="red")

legend(x= 600 , y=0.75*(max(t[,1][2:999])-min(ta[,1][2:999])) ,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("tasa=0.1", "tasa=0.01"))




rect(1, 5, 3, 7, col = "white")
dev.off()
