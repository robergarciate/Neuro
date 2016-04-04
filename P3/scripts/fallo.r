#!/usr/bin/Rscript
png("doc/graficas/P1_ecm_fallo.png", width = 720, height = 720)

t<-read.table("ecm.data")
ta<-read.table("adaptacion.data")

plot(t[,1], type="l", col="blue", ylim=c(0,1), ylab="ecm/fallo", xlab="etapas", main="p1 ECM y fallo")
lines(ta[,1], col="red")
legend(x= 1500 , y=0.75,lty=c(1,1),lwd=c(2.5,2.5),col=c("blue","red"), legend=c("ECM", "fallo"))
rect(1, 5, 3, 7, col = "white")
dev.off()
