#!/usr/bin/env Rscript

fc = file("data/data")
lines = readLines(fc)
close(fc)

numeric = as.numeric(lines)
xaxis = 1:length(numeric)

X11()
plot(xaxis, numeric)

print('press ENTER to quit')
invisible(readLines("stdin", n=1))
print('done')

