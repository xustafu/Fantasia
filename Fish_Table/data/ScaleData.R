file <- list.files(pattern = "*.csv")

data <- read.csv(file[1], header = FALSE)
data <- data$V1
data <- data[1:256]



data <-((data - min(data))*(32767-(-32767)))/(max(data)-min(data)) -32767
data <- round(data)

png("YourWaveSample.png", width = 20, height = 10, units = "cm", res = 300)
plot(data, type="l", col="purple", xlab = "Time", ylab="Your data", lwd = 2)
dev.off()

