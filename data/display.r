#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly = TRUE)

if (is.na(args[1])) {
	#filename = "data/data"
	filename = "data"
} else {
	#filename = paste(c("data", args[1]), collapse="/")
	filename = args[1]
}

fc = file(filename)
lines = readLines(fc)
close(fc)

numeric = as.numeric(lines)
xaxis = 1:length(numeric)

X11()
plot(xaxis, numeric)

print('press ENTER to quit')
invisible(readLines("stdin", n=1))

