library(ggplot2)
library(reshape2)
library(scales)
library(plyr)

args <- commandArgs(trailingOnly = TRUE)
name <- args[1]

svg(paste(name, ".svg", sep=""), width=8, height=6)

best <- read.table(paste("./datasetscalc/", name , ".best", sep=""), col.names=c('cost'))

data <- read.table(paste("./datasetscalc/", name, sep=""), col.names=c('nodes', 'cost1', 'runtime1', 'cost2', 'runtime2'))
d <- ddply(data,~nodes,summarise,h1=mean(cost1),h2=mean(cost2))
d2 <- ddply(data,~nodes,summarise,cost1=mean(cost1),runtime1=mean(runtime1),cost2=mean(cost2),runtime2=mean(runtime2))
dm <- melt(d, id.var='nodes')

ggplot(dm, aes(factor(nodes), value, fill=variable)) +
  geom_bar(stat = "identity", position="dodge", , show_guide = TRUE) +
  theme(legend.justification=c(1,0), legend.position=c(1,0), legend.title = element_blank()) +
  xlab("Anzahl Knoten") +
  ylab("Laufzeit [ms]") +
  ggtitle(name)

dev.off()
